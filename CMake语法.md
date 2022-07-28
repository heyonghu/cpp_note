# CMake 概述

CMake 语言由注释、命令和变量组成。

其中命令是不区分大小写的，但命令中的参数和变量则是大小写敏感的；

# CMake 命令

## cmake_minimum_required 

```cmake
cmake_minimum_required(VERSION <min>[...<policy_max>] [FATAL_ERROR])
```

需要最低版本的 cmake。

```cmake
cmake_minimum_required(VERSION 3.10)
```

## project

```cmake
project(<PROJECT-NAME> [<language-name>...])
project(<PROJECT-NAME>
        [VERSION <major>[.<minor>[.<patch>[.<tweak>]]]]
        [DESCRIPTION <project-description-string>]
        [HOMEPAGE_URL <url-string>]
        [LANGUAGES <language-name>...])
```

设置项目的名称，并将其存储在变量 `PROJECT_NAME` 中。 当从顶层调用时，CMakeLists.txt 还将项目名称存储在变量 CMAKE_PROJECT_NAME 中。

```cmake
project(Tutorial VERSION 1.0)
```

## add_executable

```cmake
add_executable(<name> [WIN32] [MACOSX_BUNDLE]
               [EXCLUDE_FROM_ALL]
               [source1] [source2 ...])
```

使用指定的源文件将可执行文件添加到项目中。

```cmake
add_executable(Tutorial tutorial.cxx)
```

## set

```cmake
set(<variable> <value>... [PARENT_SCOPE])
```

`<variable>`在当前函数或目录范围内设置给定的值。

如果PARENT_SCOPE给出选项，则变量将设置在当前范围之上的范围内。每个新目录或函数都会创建一个新范围。此命令会将变量的值设置到父目录或调用函数（以适用于手头的情况为准）。变量值的先前状态在当前范围内保持不变（例如，如果它之前未定义，它仍然是未定义的，如果它有一个值，它仍然是那个值）。

```cmake
set(srcs a.c b.c c.c) # sets "srcs" to "a.c;b.c;c.c"
set(x a "b;c") # sets "x" to "a;b;c", not "a;b\;c"
```

## configure_file

将文件复制到另一个位置并修改其内容。

```cmake
configure_file(<input> <output>
               [NO_SOURCE_PERMISSIONS | USE_SOURCE_PERMISSIONS |
                FILE_PERMISSIONS <permissions>...]
               [COPYONLY] [ESCAPE_QUOTES] [@ONLY]
               [NEWLINE_STYLE [UNIX|DOS|WIN32|LF|CRLF] ])
```

将文件复制`<input>`到文件并替换在输入文件内容中`<output>`引用的变量值`@VAR@`。`${VAR}`每个变量引用都将替换为变量的当前值，如果未定义变量，则替换为空字符串。此外，表格的输入行

## target_include_directories

```cmake
target_include_directories(<target> [SYSTEM] [AFTER|BEFORE]
  <INTERFACE|PUBLIC|PRIVATE> [items1...]
  [<INTERFACE|PUBLIC|PRIVATE> [items2...] ...])
```

Add include directories to a target.

Specifies include directories to use when compiling a given target. The named `<target>` must have been created by a command such as `add_executable()` or `add_library()` and must not be an ALIAS target.

By using `AFTER` or `BEFORE` explicitly, you can select between appending and prepending, independent of the default.(通过显式使用 `AFTER` 或 `BEFORE`，您可以在附加和前置之间进行选择，与默认值无关。)

The `INTERFACE`, `PUBLIC` and `PRIVATE` keywords are required to specify the scope of the following arguments. `PRIVATE` and `PUBLIC` items will populate the [`INCLUDE_DIRECTORIES`](https://cmake.org/cmake/help/latest/prop_tgt/INCLUDE_DIRECTORIES.html#prop_tgt:INCLUDE_DIRECTORIES) property of `<target>`. `PUBLIC` and `INTERFACE` items will populate the [`INTERFACE_INCLUDE_DIRECTORIES`](https://cmake.org/cmake/help/latest/prop_tgt/INTERFACE_INCLUDE_DIRECTORIES.html#prop_tgt:INTERFACE_INCLUDE_DIRECTORIES) property of `<target>`. The following arguments specify include directories.

## option

```cmake
option(<variable> "<help_text>" [value])
```

提供用户可以选择的布尔选项。

如果没有`<value>`提供初始值，则布尔值`OFF`是默认值。如果`<variable>`已设置为普通或缓存变量，则该命令不执行任何操作。

对于依赖于其他选项值的选项;

在 CMake 项目模式下，使用选项值创建一个布尔缓存变量。在 CMake 脚本模式下，使用选项值设置一个布尔变量。

## list

```cmake
Reading
  list(LENGTH <list> <out-var>)
  list(GET <list> <element index> [<index> ...] <out-var>)
  list(JOIN <list> <glue> <out-var>)
  list(SUBLIST <list> <begin> <length> <out-var>)

Search
  list(FIND <list> <value> <out-var>)

Modification
  list(APPEND <list> [<element>...])
  list(FILTER <list> {INCLUDE | EXCLUDE} REGEX <regex>)
  list(INSERT <list> <index> [<element>...])
  list(POP_BACK <list> [<out-var>...])
  list(POP_FRONT <list> [<out-var>...])
  list(PREPEND <list> [<element>...])
  list(REMOVE_ITEM <list> <value>...)
  list(REMOVE_AT <list> <index>...)
  list(REMOVE_DUPLICATES <list>)
  list(TRANSFORM <list> <ACTION> [...])

Ordering
  list(REVERSE <list>)
  list(SORT <list> [...])
```

列表操作

## add_subdirectory

```cpp
add_subdirectory(source_dir [binary_dir] [EXCLUDE_FROM_ALL])
```

Add a subdirectory to the build.

将子目录添加到构建。`source_dir` 指定源 CMakeLists.txt 和代码文件所在的目录。如果它是相对路径，它将相对于当前目录进行评估（典型用法），但它也可能是绝对路径。`binary_dir`指定放置输出文件的目录。如果它是相对路径，它将相对于当前输出目录进行评估，但它也可能是绝对路径。如果`binary_dir`未指定，则 在展开`source_dir`任何相对路径之前，将使用 的值（典型用法）。指定源目录中的 CMakeLists.txt 文件将由 CMake 立即处理，然后在当前输入文件中的处理继续超出此命令。

如果`EXCLUDE_FROM_ALL`提供了参数，则默认情况下子目录中的目标不会包含在`ALL`父目录的目标中，并且将从 IDE 项目文件中排除。用户必须在子目录中显式构建目标。这适用于子目录包含项目的单独部分有用但不必要的情况，例如一组示例。通常子目录应该包含它自己的`project()` 命令调用，以便在子目录中生成完整的构建系统（例如 VS IDE 解决方案文件）。请注意，目标间依赖项取代了此排除项。如果父项目构建的目标依赖于子目录中的目标，则依赖目标将包含在父项目构建系统中以满足依赖关系。

## add_library

```cmake
add_library(<name> [STATIC | SHARED | MODULE]
            [EXCLUDE_FROM_ALL]
            [<source>...])
```

使用指定的源文件将库添加到项目中。

Add a library to the project using the specified source files.

添加一个库目标，称为`<name>`从命令调用中列出的源文件构建。对应于逻辑目标名称，`<name>` 并且在项目中必须是全局唯一的。构建的库的实际文件名是根据本机平台的约定（例如`lib<name>.a`或 `<name>.lib`）构建的。

## target_link_libraries

```cmake
target_link_libraries(<target> ... <item>... ...)
```

Specify libraries or flags to use when linking a given target and/or its dependents. [Usage requirements](https://cmake.org/cmake/help/latest/manual/cmake-buildsystem.7.html#target-usage-requirements) from linked library targets will be propagated. Usage requirements of a target's dependencies affect compilation of its own sources.

指定链接给定目标或其依赖项时要使用的库或标志。 来自链接库的目标将被传播。 目标依赖项的使用要求会影响其自身源的编译。

# CMake 变量

## PROJECT_BINARY_DIR

Full path to build directory for project.

项目构建目录的完整路径。即build的路径；

```cmake
PROJECT_BINARY_DIR:/home/heyonghu/Desktop/test01/build
```

## PROJECT_SOURCE_DIR

这是最后一次调用的源目录 `project()`在当前目录范围或其父目录之一中执行的命令。请注意，它不受调用的影响 `project()`在子目录范围内（即从调用`add_subdirectory()`从当前范围）。

```cmake
PROJECT_SOURCE_DIR:/home/heyonghu/Desktop/test01
```

## aux_source_directory

```cpp
aux_source_directory(<dir> <variable>)
```

Find all source files in a directory.

收集指定目录中所有源文件的名称，并将列表存储在`<variable>`提供的. 此命令旨在供使用显式模板实例化的项目使用。模板实例化文件可以存储在 `Templates`子目录中，并使用此命令自动收集，以避免手动列出所有实例化。

使用此命令来避免为库或可执行目标编写源文件列表是很有诱惑力的。虽然这似乎可行，但 CMake 无法生成一个知道何时添加新源文件的构建系统。通常，生成的构建系统知道何时需要重新运行 CMake，因为`CMakeLists.txt`文件已被修改以添加新源。当源只是添加到目录而不修改此文件时，必须手动重新运行 CMake 以生成包含新文件的构建系统。



# CMake 样例

