# Flashback

Recollector program to help learners review technical references.

## Introduction

Flashback can be used to write technical notes in order to frequently refer to them later.

## Setup

```sh
git clone https://github.com/briansalehi/flashback.git
cmake -S flashback -B flashback-build -D CMAKE_BUILD_TYPE:STRING=release
cmake --build flashback-build --target all --parallel
cmake --install flashback-build --prefix $HOME/.local
```

## Usage

Then start your session by following command:

```sh
flashback start
```

## License

This work is licensed under [GNU General Public License Version 3](LICENSE.md).
