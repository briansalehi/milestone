# Flashback

Recollector program for notations, references and practices to
help technical readers and learners review topics and domains.

## Introduction

## Setup

```sh
git clone https://github.com/briansalehi/flashback.git
cmake -S flashback -B flashback-build \
    -D CMAKE_BUILD_TYPE:STRING=release \
    -D FLASHBACK_DATABASE_PATH:PATH=$HOME/.config/flashback
cmake --build flashback-build --target all --parallel
cmake --install flashback-build --prefix $HOME/.local
```

## Usage

To start using Flashback, first create a database either by
long option or its abbreviation:

```sh
flashback --generate-database
flashback -g
```

Then start your session by following command:

```sh
flashback
```

## License

This work is licensed under [GNU General Public License Version 3](LICENSE.md).
