# malloc
A custom dynamic memory allocation library that reimplements `malloc`, `free`, and `realloc` using `mmap`/`munmap`.

## What this project does
Reimplements the standard allocation functions:
- `malloc`
- `free`
- `realloc`

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
