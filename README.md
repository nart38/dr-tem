# Dr.TEm
Dramatic Terminal Emulator.

Clone of [eduterm](https://www.uninformativ.de/git/eduterm/file/README.html) with a twist.

Yet another learning project of mine.

## How to Build
### Linux
You need to link raylib. If raylib is already installed on your system you can run `build.sh`.

Or simply run:
```sh
cc src/window.c -o drtem -W all -W extra -l raylib
```

## Inspirations
- [The very basics of a terminal emulator](https://www.uninformativ.de/blog/postings/2018-02-24/0/POSTING-en.html)
- [ded - Dramatic Editor](https://github.com/tsoding/ded)
