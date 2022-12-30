# Flashback

Recollection program to help learners review technical references and practice on subjects.

## Introduction

Using Flashback you can write technical notes in order to frequently review them and
practice the subjects of your interest, so that you are always ready for a challenge.

## Setup

You can build and optionally install the program by following these instructions:

- First get the source of the program using [Git](https://git-scm.com/downloads):

```sh
git clone https://github.com/briansalehi/flashback.git
```

- Then configure the project with [CMake](https://cmake.org/download/):

```sh
cmake -S flashback -B flashback-build -D CMAKE_BUILD_TYPE:STRING=release
```

- And then build the program as follows:

```sh
cmake --build flashback-build --target all --parallel
```

- **(optional)** If you want Flashback permanently on your system:

```sh
cmake --install flashback-build --prefix $HOME/.local
```

## Usage

Start using Flashback by running its command:

```sh
flashback
```

## License

This work is licensed under [GNU General Public License Version 3](LICENSE.md).
