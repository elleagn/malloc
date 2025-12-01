# malloc
This project is about implementing a dynamic memory allocation mechanism.

## What this project does

Reimplement 3 allocation functions using mmap and munmap:
- malloc
- realloc
- free

## Build and test

- Build the library:
``` make ```

- Build and run the test program:
``` make test
export LD_LIBRARY_PATH=$(pwd)
./test```
