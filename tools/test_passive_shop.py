"""Compile-time regression tests for the passive shop logic."""

from pathlib import Path
import shutil
import subprocess
import tempfile
import unittest


ROOT = Path(__file__).resolve().parents[1]


class PassiveShopTests(unittest.TestCase):
    def test_compile_time_shop_contracts(self):
        compiler = shutil.which('arm-none-eabi-g++')
        if compiler is None:
            bundled = Path(r'C:\devkitPro\devkitARM\bin\arm-none-eabi-g++.exe')
            compiler = str(bundled) if bundled.exists() else None
        self.assertIsNotNone(compiler, 'arm-none-eabi-g++ is required for the constexpr tests')
        with tempfile.TemporaryDirectory() as temporary:
            output = Path(temporary) / 'passive_shop_tests.o'
            subprocess.run([
                compiler, '-std=gnu++17', '-Wall', '-Wextra', '-Werror',
                '-I', str(ROOT / 'include'), '-c',
                str(ROOT / 'tests' / 'passive_shop_tests.cpp'), '-o', str(output)
            ], check=True, capture_output=True, text=True)
            self.assertTrue(output.exists())


if __name__ == '__main__':
    unittest.main()
