""" setup.py
Builds the test c-extension python module.
Author: Mark Murillo
"""

from distutils.core import setup, Extension

testModule = Extension(
    'testMod',
    include_dir=[],
    libraries=[],
    library_dirs=[],
     sources=['test.c']
)

setup(
    name='testMod',
    version='1.0',
    description='A library to test the c extension capabilities',
    ext_modules=[testModule]
)
