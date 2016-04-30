cppassist
=======

cppassist is a collection of C++ functions, classes and libraries that are too small to be standalone.
It acts like a storage point for useful and reusable code for everyone using C++.
cppassist is a cross-platform library licenced under the [MIT license](http://opensource.org/licenses/MIT).

The current modules in cppassist are:
 * [io](#io)
 * [logging](#logging)
 * [threading](#threading)
 * [string](#string)
 * [cmdline](#cmdline)


### Dependencies

The following dev-libraries and programs need to be provided for correct CMake configuration:
* C++11 compatible compiler (e.g. gcc 4.7, VS 2013)
* CMake (>= 3.0): http://www.cmake.org/
* Optional: boost

io
------

io contains a function to read a file into an std::string.

logging
-----------

logging provides stream like logging functionality with customizable outputs (default output is to the console).


threading
-------------

threading provides a `parallel_for` function that uses either OpenMP or the `std::thread` classes to execute a for loop concurrently.


string
-------------

string utilities like conversion between string and numeric data types and convenience functions for string operations.

cmdline
-------------

command line arguments parser for console applications.
