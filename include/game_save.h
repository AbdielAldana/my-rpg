#ifndef GAME_SAVE_H
#define GAME_SAVE_H

#include <stdint.h>
#include "bn_type_traits.h"
#include "passive_shop.h"

namespace game_save
{

constexpr int max_run_bytes = 16000;

struct Records
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
    passive_shop::State shop;
    uint8_t pending_shop_potions = 0;
    uint8_t pending_shop_keys = 0;
    uint8_t pending_shop_medikits = 0;
};

Records& records();
bool load();
bool has_run();
uint8_t* run_buffer();
int run_size();
void commit_run(int bytes);
void commit_records();
void clear_run();

class Writer
{
public:
    Writer() :
        _buffer(run_buffer())
    {
    }

    template<typename Type>
    void value(const Type& source)
    {
        static_assert(bn::is_trivially_copyable<Type>(), "Save values must be trivially copyable");
        if(!_good)
            return;
        if(sizeof(Type) > unsigned(max_run_bytes - _position))
        {
            _good = false;
            return;
        }
        __builtin_memcpy(_buffer + _position, &source, sizeof(Type));
        _position += int(sizeof(Type));
    }

    bool good() const { return _good; }
    int size() const { return _position; }

private:
    uint8_t* _buffer;
    int _position = 0;
    bool _good = true;
};

class Reader
{
public:
    Reader() :
        _buffer(run_buffer()),
        _bytes(run_size())
    {
    }

    template<typename Type>
    void value(Type& destination)
    {
        static_assert(bn::is_trivially_copyable<Type>(), "Save values must be trivially copyable");
        if(!_good)
            return;
        if(sizeof(Type) > unsigned(_bytes - _position))
        {
            _good = false;
            return;
        }
        __builtin_memcpy(&destination, _buffer + _position, sizeof(Type));
        _position += int(sizeof(Type));
    }

    bool good() const { return _good; }
    int size() const { return _position; }
    bool finished() const { return _good && _position == _bytes; }

private:
    const uint8_t* _buffer;
    int _bytes;
    int _position = 0;
    bool _good = true;
};

}

#endif
