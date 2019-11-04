# DecimalGamma (C++ implementation)

## Requirements

* cmake
* make
* C++14 compiler (GCC 4.9 and Clang 3.9 work)
* clang-format (from [clang-tools-extra](http://releases.llvm.org/download.html))
* coreutils (for ```realpath```)
* Python 3 with matplotlib and pandas

## How to clone

Do a *recursive* clone to get the submodules right away:

```bash
git clone --recursive <repository-url>
```

If you forgot to do a recursive clone or submodules
have been added or updated since your last update,
you can (initialize) and update them in your index the following way:

```bash
cd <repository-root>
git submodule update --init --recursive
```

## How to build

```bash
cd gen
cmake ../src
make
```

### Code formatting

You can check if some files do not adhere to the code format:
```bash
make check-format
```
To automatically apply the format, do this:
```bash
make fix-format
```

## Experiments and plots

Each experiments and each plot has a target
in the ```experiments``` and ```plots``` folder, respectively.
The require the executables to be built.
To run the experiments and make plots, do the following:

```bash
cd <repository-root>/experiments
make -j1
cd <repository-root>/plots
make
```
