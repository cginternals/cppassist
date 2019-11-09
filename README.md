
<br><a href="https://github.com/cginternals/cppassist/"><img src="https://raw.githubusercontent.com/cginternals/cppassist/master/cppassist-logo.svg?sanitize=true" width="50%"></a>

*cppassist* is a collection of cross-platform C++ functions, classes and libraries that are too small to be standalone.
It acts like a storage point for useful and reusable code for everyone using C++.

![GitHub release](https://img.shields.io/github/release/cginternals/cppassist.svg)
[![Travis](https://img.shields.io/travis/cginternals/cppassist/master.svg?style=flat&logo=travis)](https://travis-ci.org/cginternals/cppassist)
[![Appveyor](https://img.shields.io/appveyor/ci/scheibel/cppassist/master.svg?style=flat&logo=appveyor)](https://ci.appveyor.com/project/scheibel/cppassist/branch/master)
[![Tokei](https://tokei.rs/b1/github/cginternals/cppassist)](https://github.com/Aaronepower/tokei)
[![Tokei](https://tokei.rs/b1/github/cginternals/cppassist?category=comments)](https://github.com/Aaronepower/tokei)


# Resources

##### Installation and Development

* [Build form Source](#build-instructions)
* [Tips for Linking](#tips-for-linking)

##### Module Introductions
 * [cmdline](#cmdline)
 * [error](#error)
 * [flags](#flags)
 * [fs](#fs)
 * [logging](#logging)
 * [memory](#memory)
 * [simd](#simd)
 * [string](#string)
 * [threading](#threading)
 * [tokenizer](#tokenizer)
 * [typelist](#typelist)


# Build Instructions

##### Prerequisites and Dependencies

The only mandatory run-time dependencies of *cppassist* are the STL of the used compiler. Building *cppassist* from source has several mandatory and optional dependencies:

* [CMake](https://cmake.org/) 3.0 or higher for building *cppassist* from source (mandatory for any build from source)
* [git](https://git-scm.com/) for version control and script supporting tasks
* [Doxygen](http://www.stack.nl/~dimitri/doxygen/) 1.8 or higher for generating the documentation on your system
  * [graphviz](http://www.graphviz.org/) for generating diagrams (optional)

##### Compile Instructions

For compilation, a C++11 compliant compiler, e.g., GCC 4.8, Clang 3.3, MSVC 2013 **Update 3**, is required.
First, download the source code [as archive](https://github.com/cginternals/cppassist/releases) or via git:

```bash
> git clone https://github.com/cginternals/cppassist.git
> cd cppassist
```

Then, depending on the version of *cppassist* you want to build, choose the appropriate tag or branch, e.g., for the 1.0.0 release:

```bash
> git fetch --tags
> git checkout v1.0.0
```

The actual compilation can be done using CMake and your favorite compiler and IDE.

For building *cppassist* CMake via command line can be used (should work on all systems):

First, create a build directory (we do not recommend in-source builds):

```bash
> mkdir build
> cd build
```

Configure *cppassist* with your preferred or default generator, e.g., for Visual Studio 2015 in x64 use
(note: some IDEs have integrated support for CMake projects, e.g., Qt Creator, and allow you to skip the manual project configuration):

```bash
> cmake .. -G "Visual Studio 14 2015 Win64"
```

In order to compile the project, either use you favorite Editor/IDE with the created project or use CMake as follows:

```bash
> cmake --build .
```


# cmdline

command line arguments parser for console applications.

```cpp
#include <cppassist/cmdline/ArgumentParser.h>
#include <cppassist/cmdline/CommandLineProgram.h>
#include <cppassist/cmdline/CommandLineAction.h>
#include <cppassist/cmdline/CommandLineCommand.h>
#include <cppassist/cmdline/CommandLineOption.h>
#include <cppassist/cmdline/CommandLineSwitch.h>
#include <cppassist/cmdline/CommandLineParameter.h>

// Declare program
CommandLineProgram program(
    "cmdline-example2",
    "cmdline-example2 " CPPASSIST_VERSION,
    "cmdline-example2 demonstrates how to parse (complex) command line options using the CommandLineProgram class in cppassist."
);

// Common options
CommandLineSwitch swVerbose("--verbose", "-v", "Make output more verbose");

// Action: 'help'
CommandLineAction actionHelp("help", "Print help text");
program.add(&actionHelp);

actionHelp.add(&swVerbose);

CommandLineSwitch swHelp("--help", "-h", "Print help text", CommandLineSwitch::NonOptional);
actionHelp.add(&swHelp);

CommandLineParameter paramCommand("command", CommandLineParameter::Optional);
actionHelp.add(&paramCommand);

// Action: 'count'
CommandLineAction actionCount("count", "Count from one number to another");
program.add(&actionCount);

actionCount.add(&swVerbose);

CommandLineCommand cmdCount("count");
actionCount.add(&cmdCount);

CommandLineOption optStep("--increment-by", "-i", "step", "Number that is added per iteration", CommandLineOption::Optional);
actionCount.add(&optStep);

CommandLineParameter paramFrom("from", CommandLineParameter::NonOptional);
actionCount.add(&paramFrom);

CommandLineParameter paramTo("to", CommandLineParameter::NonOptional);
actionCount.add(&paramTo);

// Action: 'cp'
CommandLineAction actionCopy("cp", "Copy files");
program.add(&actionCopy);

actionCopy.add(&swVerbose);

CommandLineCommand cmdCopy("cp");
actionCopy.add(&cmdCopy);

CommandLineParameter paramSrc("path", CommandLineParameter::NonOptional);
actionCopy.add(&paramSrc);

actionCopy.setOptionalParametersAllowed(true);
actionCopy.setOptionalParameterName("path");

// Parse command line
program.parse(argc, argv);

// Check if a valid action has been selected
if (program.selectedAction() && !program.hasErrors())
{
    // Execute 'help'
    if (program.selectedAction() == &actionHelp)
    {
    }

    // Execute 'count'
    else if (program.selectedAction() == &actionCount)
    {
    }

    // Execute 'cp'
    else if (program.selectedAction() == &actionCopy)
    {
    }

    // Exit with success
    exit(0);
}

// Print help
program.print(program.help(program.selectedAction()));
```


# error

The error module introduces a `Result` template (inspired from the `Result` template from Rust) and an explicit `Error` class.
The Result class can be used as follows:

```cpp
#include <cppassist/error/Result.h>

// void return value example

cppassist::Result<void> processIfValid(bool check)
{
    if (!check)
    {
        return cppassist::error<void>("Invalid");
    }

    process();

    return cppassist::ok();
}

const auto result_success = processIfValid(true);
const auto result_failure = processIfValid(false);

if (!result_failure.isValid())
{
    std::cout << result_failure.error().message() << '\n';
}

// return value example

cppassist::Result<std::int64_t> faculty(int n)
{
    if (n < 0 || n > 20)
    {
        return cppassist::error<std::int64_t>("n out of range");
    }

    if (n < 2)
    {
        return n;
    }

    std::int64_t result = 1;
    while (n > 1)
    {
        result *= n;
        --n;
    }

    return result;
}

const auto result_success = faculty(4);
const auto result_failure = faculty(30);

if (result_success.isValid())
{
    std::cout << "Faculty of 4 is " << result_success.value() << '\n';
}

if (!result_failure.isValid())
{
    std::cout << result_failure.error().message() << '\n';
}

```


# flags

Flags type to help using enums as flags.

```cpp
#include <cppassist/flags/Flags.h>

enum class MyEnum : unsigned int {
    Value1 = 1,
    Value2 = 2,
    Value3 = 4
};

const auto f = cppassist::makeFlags(MyEnum::Value1) | MyEnum::Value2 & MyEnum::Value3;
```


# fs

The fs module provides classes to access raw files and their key-value structured header information.

```cpp
#include <cppassist/fs/DescriptiveRawFile.h>

const auto file = cppassist::DescriptiveRawFile();
file.load("testfile.raw", true);

// access raw file contents (starting after header)
file.data();

// access string properties from header
file.stringProperty("author");

// access integer properties from header
file.intProperty("width");

// access floating point properties from header
file.doubleProperty("scaleFactor");
```


# logging

logging provides stream like logging functionality with customizable outputs (default output is to the console).

```cpp
#include <cppassist/logging/logging.h>

cppassist::setVerbosityLevel(LogMessage::Debug + 2);

cppassist::critical() << "A normal critical message.";
cppassist::error() << "A normal error message.";
cppassist::warning() << "A normal warning message.";
cppassist::info() << "A normal info message.";
cppassist::debug() << "A normal debug message.";
cppassist::debug(1) << "Another debug message.";

cppassist::info("A") << "Info message from context A";
cppassist::warning("B") << "Warning from context B";
cppassist::critical("C") << "Critical message from context C";
```


# memory

Low-level memory management helpers.

`make_unique.h`

```cpp
#include <cppassist/memory/make_unique.h>

int * value = cppassist::make_unique<int>(42);
```

`offsetof.h`

```cpp
class Foo
{
    int a;
    int b;
};

const auto offset = cppassist::offsetof(&Foo::b);
```


# simd

simd provides structures and algorithms for SIMD-like data processing, as introduced by GPUs.
This is achieved by compiler extensions as SSE, AVX2, and AVX512.

```cpp

#include <cppassist/simd/simd.h>
#include <cppassist/simd/vector.h>
#include <cppassist/simd/value.h>

const auto valueSize = 512ull * 512ull * 512ull * 2ull; // 1GB of consecutive data

cppassist::vector<float> values1(valueSize);
cppassist::vector<float> values2(valueSize);
std::fill(values1.valueBegin(), values1.valueEnd(), 2.0f);
std::fill(values2.valueBegin(), values2.valueEnd(), 4.0f);

// Traverse whole vectors and perform the operations using vectorization
cppassist::traverse([](const cppassist::vector<float>::value_type & chunk1, cppassist::vector<float>::value_type & chunk2)
{
    chunk2 = sqrt((sqrt(chunk1) * sqrt(chunk2) + 12.0f) * 0.125f + 5.0f);
}, values1, values2);
```

# string

This module provides string utilities like conversion between string and numeric data types, convenience functions for string operations, and some advanced regex functionality (either implemented using Boost or the C++ standard library).

`conversion.h`

```cpp
#include <cppassist/string/conversion.h>

const auto valueInt = cppassist::string::fromString<int>("42");
const auto valueBool = cppassist::string::fromString<bool>("True");

const auto valueString = cppassist::string::toString(3.14f);

// Encode string as UC32
const auto valueUC32 = cppassist::string::encode("Hello", cppassist::Encoding::ASCII);

//Decode string from UC32
const auto valueUTF8 = cppassist::string::decode(valueUC32, cppassist::Encoding::UTF8);
```

`manipulation.h`

```cpp
#include <cppassist/string/manipulation.h>

const auto commaSeparatedList = cppassist::join({ 1, 2, 3, 4, 5}, ",");
const auto stringVector = cppassist::split("1,2,3,4,5", ',', false);
const auto trimmedString = cppassist::trim("     Hallo     ");
const auto strippedString = cppassist::stripped("1-2-3-4-5-6", { '-' });
```

`regex.h`

```cpp
#include <cppassist/string/regex.h>

if (cppassist::matchesRegex(hexString, "([0-9A-Fa-f]{8}|[0-9A-Fa-f]{6})"))
{
    const auto componentList = cppassist::extract(hexString,
        "([0-9A-Fa-f]{2})([0-9A-Fa-f]{2})([0-9A-Fa-f]{2})([0-9A-Fa-f]{2})?");
}
```


# threading

The module threading provides functions that uses either OpenMP `#pragma omp` or the `std::thread` classes to execute a for loop concurrently.

```cpp
#include <cppassist/threading/parallelfor.h>

bool parallelize = size > 25; // use parallel computation if threshold is reached

// Beware that start and end are both inclusive
cppassist::forEach(0u, size, [this](std::uint32_t number)
{
    // concurrent calls of this with 0 <= number <= size
}, parallelize);
```


# tokenizer

Low-level tokenizer as base for more elaborate text parsers.

```cpp
#include <cppassist/tokenizer/Tokenizer.h>

// Create tokenizer for JSON
cppassist::Tokenizer tokenizer;

tokenizer.setOptions(
    cppassist::Tokenizer::OptionParseStrings
    | cppassist::Tokenizer::OptionParseNumber
    | cppassist::Tokenizer::OptionParseBoolean
    | cppassist::Tokenizer::OptionParseNull
    | cppassist::Tokenizer::OptionCStyleComments
    | cppassist::Tokenizer::OptionCppStyleComments
);

tokenizer.setQuotationMarks("\"");
tokenizer.setSingleCharacters("{}[],:");
```


# typelist

This module introduces a `TypeList` type that allows calling different instantiations of a templated method consecutively.

```cpp
#include <cppassist/typelist/TypeList.h>

class TypeListCallback
{
public:
    TypeListCallback();

    template <typename T>
    void invoke()
    {
        // gets instantiated and called with each type from SupportedTypes
    }
};

using SupportedTypes = cppassist::TypeList<char, int, long, float, double>;

// Iterates over all type within type list and call the invoke overload for each type
SupportedTypes::apply(*this);
```
