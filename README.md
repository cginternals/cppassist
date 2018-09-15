<br><a href="https://github.com/cginternals/cppassist/"><img src="https://raw.githubusercontent.com/cginternals/cppassist/master/cppassist-logo.svg?sanitize=true" width="50%"></a>

cppassist is a collection of C++ functions, classes and libraries that are too small to be standalone.
It acts like a storage point for useful and reusable code for everyone using C++.

[![Travis](https://img.shields.io/travis/cginternals/cppassist/master.svg?style=flat&logo=travis)](https://travis-ci.org/cginternals/cppassist)
[![Appveyor](https://img.shields.io/appveyor/ci/gruntjs/grunt/master.svg?style=flat&logo=appveyor)](https://ci.appveyor.com/project/scheibel/cppassist/branch/master)
[![Tokei](https://tokei.rs/b1/github/cginternals/cppassist)](https://github.com/Aaronepower/tokei)

cppassist is a cross-platform library licenced under the [MIT license](http://opensource.org/licenses/MIT).

The current modules in cppassist are:
 * [cmdline](#cmdline)
 * [flags](#flags)
 * [fs](#fs)
 * [logging](#logging)
 * [memory](#memory)
 * [simd](#simd)
 * [string](#string)
 * [threading](#threading)
 * [tokenizer](#tokenizer)
 * [typelist](#typelist)


### Dependencies

The following dev-libraries and programs need to be provided for correct CMake configuration:
* C++11 compatible compiler (e.g. gcc 4.7, VS 2013)
* CMake (>= 3.0): http://www.cmake.org/
* Optional: boost


cmdline
-------------

command line arguments parser for console applications.


flags
-------------

Flags type to help using enums as flags


fs
-------------

classes and methods for platform independent directory traversal and raw data import from files


logging
-------------

logging provides stream like logging functionality with customizable outputs (default output is to the console).


memory
-------------

low-level memory management helpers


simd
-------------

simd provides structures and algorithms for SIMD-like data processing, as introduced by GPUs.
This is achieved by compiler extensions as SSE, AVX2, and AVX512.


string
-------------

string utilities like conversion between string and numeric data types, convenience functions for string operations, and some advanced regex functionality


threading
-------------

threading provides a `parallel_for` function that uses either OpenMP or the `std::thread` classes to execute a for loop concurrently.


tokenizer
-------------

low-level tokenizer as base for more elaborate text parsers


typelist
-------------

TypeList type that allows calling different instantiations of a templated method consecutively
