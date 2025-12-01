# malloc
This project is about implementing a dynamic memory allocation mechanism.

## What this project does

Reimplement 3 allocation functions using mmap and munmap:
- malloc
- realloc
- free

## Build and test

- Build the library:
```bash
make
```

- Build and run the test program:
```bash
make test
export LD_LIBRARY_PATH=$(pwd)
./test
```
