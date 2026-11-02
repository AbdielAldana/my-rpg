#include "game_save.h"
#include "bn_sram.h"
#include "bn_span.h"

namespace game_save
{
namespace
{

constexpr int bank_bytes = 16384;
constexpr int checksum_chunk_bytes = 64;
constexpr uint32_t save_magic = 0x47535631u;
constexpr uint32_t save_version_v1 = 1;
constexpr uint32_t save_version_v2 = 2;
constexpr uint32_t save_version = 3;
constexpr uint32_t crc_polynomial = 0xEDB88320u;

struct LegacyRecords
{
    uint32_t floors_explored = 0;
    uint32_t rooms_explored = 0;
    uint32_t deaths = 0;
    uint32_t adventurers_saved = 0;
    uint32_t best_floor = 0;
    uint32_t best_rooms = 0;
    uint8_t active_items_discovered = 0;
    uint8_t enemies_seen = 0;
    uint16_t coins = 0;
};

struct LegacyBankHeader
{
    uint32_t magic = 0;
    uint32_t version = 0;
    uint32_t sequence = 0;
    uint32_t run_bytes = 0;
    LegacyRecords records;
    uint32_t crc32 = 0;
};

struct BankHeader
{
    uint32_t magic = 0;
    uint32_t version = 0;
    uint32_t sequence = 0;
    uint32_t run_bytes = 0;
    Records records;
    uint32_t crc32 = 0;
};

static_assert(sizeof(LegacyBankHeader) == 48, "Unexpected legacy save header layout");
static_assert(sizeof(BankHeader) + max_run_bytes <= bank_bytes, "Save payload exceeds a bank");
static_assert(bn::sram::size() == bank_bytes * 2, "Save backend requires 32 KB SRAM");

BN_DATA_EWRAM_BSS uint8_t saved_run[max_run_bytes] = {};
BN_DATA_EWRAM_BSS uint8_t checksum_chunk[checksum_chunk_bytes] = {};
BN_DATA_EWRAM_BSS Records saved_records = {};
BN_DATA_EWRAM_BSS BankHeader headers[2] = {};
BN_DATA_EWRAM_BSS LegacyBankHeader legacy_headers[2] = {};
BN_DATA_EWRAM_BSS uint32_t bank_versions[2] = {};
// Zero means no valid bank; one and two identify SRAM banks zero and one.
BN_DATA_EWRAM_BSS int active_bank_plus_one = 0;
BN_DATA_EWRAM_BSS uint32_t active_sequence = 0;
BN_DATA_EWRAM_BSS int committed_run_bytes = 0;

uint32_t extend_crc(uint32_t crc, const uint8_t* data, int bytes)
{
    for(int index = 0; index < bytes; ++index)
    {
        crc ^= data[index];
        for(int bit = 0; bit < 8; ++bit)
        {
            uint32_t low_bit_mask = 0u - (crc & 1u);
            crc = (crc >> 1) ^ (crc_polynomial & low_bit_mask);
        }
    }
    return crc;
}

template<typename Type>
uint32_t field_crc(uint32_t crc, const Type& field)
{
    return extend_crc(crc, reinterpret_cast<const uint8_t*>(&field), int(sizeof(Type)));
}

uint32_t metadata_crc(const BankHeader& header)
{
    // Hash actual fields, excluding compiler padding, the commit marker and CRC itself.
    uint32_t crc = 0xFFFFFFFFu;
    crc = field_crc(crc, header.version);
    crc = field_crc(crc, header.sequence);
    crc = field_crc(crc, header.run_bytes);
    crc = field_crc(crc, header.records.floors_explored);
    crc = field_crc(crc, header.records.rooms_explored);
    crc = field_crc(crc, header.records.deaths);
    crc = field_crc(crc, header.records.adventurers_saved);
    crc = field_crc(crc, header.records.best_floor);
    crc = field_crc(crc, header.records.best_rooms);
    crc = field_crc(crc, header.records.active_items_discovered);
    crc = field_crc(crc, header.records.enemies_seen);
    crc = field_crc(crc, header.records.coins);
    crc = field_crc(crc, header.records.shop.purchased_mask);
    crc = field_crc(crc, header.records.shop.random_state);
    crc = field_crc(crc, header.records.shop.options);
    crc = field_crc(crc, header.records.shop.initialized);
    crc = field_crc(crc, header.records.pending_shop_potions);
    crc = field_crc(crc, header.records.pending_shop_keys);
    crc = field_crc(crc, header.records.pending_shop_medikits);
    return crc;
}

uint32_t legacy_metadata_crc(const LegacyBankHeader& header)
{
    uint32_t crc = 0xFFFFFFFFu;
    crc = field_crc(crc, header.version);
    crc = field_crc(crc, header.sequence);
    crc = field_crc(crc, header.run_bytes);
    crc = field_crc(crc, header.records.floors_explored);
    crc = field_crc(crc, header.records.rooms_explored);
    crc = field_crc(crc, header.records.deaths);
    crc = field_crc(crc, header.records.adventurers_saved);
    crc = field_crc(crc, header.records.best_floor);
    crc = field_crc(crc, header.records.best_rooms);
    crc = field_crc(crc, header.records.active_items_discovered);
    crc = field_crc(crc, header.records.enemies_seen);
    if(header.version >= save_version_v2)
        crc = field_crc(crc, header.records.coins);
    return crc;
}

bool valid_bank(int bank)
{
    int bank_offset = bank * bank_bytes;
    LegacyBankHeader& legacy = legacy_headers[bank];
    bn::sram::read_offset(legacy, bank_offset);
    if(legacy.magic != save_magic ||
       (legacy.version != save_version_v1 && legacy.version != save_version_v2 &&
        legacy.version != save_version) || legacy.run_bytes > unsigned(max_run_bytes))
    {
        return false;
    }

    bank_versions[bank] = legacy.version;
    uint32_t crc = 0;
    int remaining = int(legacy.run_bytes);
    int read_offset = bank_offset;
    uint32_t expected_crc = 0;
    if(legacy.version == save_version)
    {
        BankHeader& header = headers[bank];
        bn::sram::read_offset(header, bank_offset);
        crc = metadata_crc(header);
        read_offset += int(sizeof(BankHeader));
        expected_crc = header.crc32;
    }
    else
    {
        crc = legacy_metadata_crc(legacy);
        read_offset += int(sizeof(LegacyBankHeader));
        expected_crc = legacy.crc32;
    }
    while(remaining > 0)
    {
        int chunk_bytes = remaining < checksum_chunk_bytes ? remaining : checksum_chunk_bytes;
        bn::span<uint8_t> chunk(checksum_chunk, chunk_bytes);
        bn::sram::read_span_offset(chunk, read_offset);
        crc = extend_crc(crc, checksum_chunk, chunk_bytes);
        read_offset += chunk_bytes;
        remaining -= chunk_bytes;
    }
    return (crc ^ 0xFFFFFFFFu) == expected_crc;
}

bool sequence_is_newer(uint32_t candidate, uint32_t previous)
{
    uint32_t difference = candidate - previous;
    return difference != 0 && difference < 0x80000000u;
}

uint32_t bank_sequence(int bank)
{
    return bank_versions[bank] == save_version ? headers[bank].sequence : legacy_headers[bank].sequence;
}

void commit_payload(int bytes)
{
    int destination_bank = active_bank_plus_one == 1 ? 1 : 0;
    int bank_offset = destination_bank * bank_bytes;
    BankHeader& header = headers[destination_bank];
    header = BankHeader();
    header.version = save_version;
    header.sequence = active_sequence + 1u;
    header.run_bytes = unsigned(bytes);
    header.records = saved_records;
    uint32_t crc = metadata_crc(header);
    crc = extend_crc(crc, saved_run, bytes);
    header.crc32 = crc ^ 0xFFFFFFFFu;

    // Invalidate only the destination. The previous committed bank stays untouched.
    constexpr uint32_t invalid_magic = 0;
    bn::sram::write_offset(invalid_magic, bank_offset);
    bn::sram::write_offset(header, bank_offset);
    if(bytes > 0)
    {
        bn::span<const uint8_t> payload(saved_run, bytes);
        bn::sram::write_span_offset(payload, bank_offset + int(sizeof(BankHeader)));
    }
    // The bank becomes valid only after metadata, records and payload have been written.
    bn::sram::write_offset(save_magic, bank_offset);
    header.magic = save_magic;
    active_bank_plus_one = destination_bank + 1;
    active_sequence = header.sequence;
    committed_run_bytes = bytes;
}

}

Records& records()
{
    return saved_records;
}

bool load()
{
    active_bank_plus_one = 0;
    active_sequence = 0;
    committed_run_bytes = 0;
    saved_records = Records();
    bool first_valid = valid_bank(0);
    bool second_valid = valid_bank(1);
    if(!first_valid && !second_valid)
        return false;

    int selected_bank = 0;
    if(second_valid && (!first_valid || sequence_is_newer(bank_sequence(1), bank_sequence(0))))
        selected_bank = 1;
    int payload_offset = selected_bank * bank_bytes;
    if(bank_versions[selected_bank] == save_version)
    {
        const BankHeader& header = headers[selected_bank];
        saved_records = header.records;
        active_sequence = header.sequence;
        committed_run_bytes = int(header.run_bytes);
        payload_offset += int(sizeof(BankHeader));
    }
    else
    {
        const LegacyBankHeader& header = legacy_headers[selected_bank];
        const LegacyRecords& legacy = header.records;
        saved_records.floors_explored = legacy.floors_explored;
        saved_records.rooms_explored = legacy.rooms_explored;
        saved_records.deaths = legacy.deaths;
        saved_records.adventurers_saved = legacy.adventurers_saved;
        saved_records.best_floor = legacy.best_floor;
        saved_records.best_rooms = legacy.best_rooms;
        saved_records.active_items_discovered = legacy.active_items_discovered;
        saved_records.enemies_seen = legacy.enemies_seen;
        saved_records.coins = header.version == save_version_v1 ? 0 : legacy.coins;
        active_sequence = header.sequence;
        committed_run_bytes = int(header.run_bytes);
        payload_offset += int(sizeof(LegacyBankHeader));
    }
    active_bank_plus_one = selected_bank + 1;
    if(committed_run_bytes > 0)
    {
        bn::span<uint8_t> payload(saved_run, committed_run_bytes);
        bn::sram::read_span_offset(payload, payload_offset);
    }
    return true;
}

bool has_run()
{
    return committed_run_bytes > 0;
}

uint8_t* run_buffer()
{
    return saved_run;
}

int run_size()
{
    return committed_run_bytes;
}

void commit_run(int bytes)
{
    BN_ASSERT(bytes > 0 && bytes <= max_run_bytes, "Invalid run save size: ", bytes);
    if(bytes <= 0 || bytes > max_run_bytes)
        return;
    commit_payload(bytes);
}

void commit_records()
{
    commit_payload(committed_run_bytes);
}

void clear_run()
{
    // Both banks become tombstones, so fallback cannot restore a completed/dead run.
    commit_payload(0);
    commit_payload(0);
}

}
