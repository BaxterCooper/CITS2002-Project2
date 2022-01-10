# CITS2002-Project2
A command line utility program written in C that detects and reports duplicate files in and below a named directory.


## Compilation

```bash
make
```

## Usage

```bash
./duplicates [options] directory1 [directory2]...
```

The available options are as follows:

```
-a          include directory entries whose names begin with a dot (.)
-A          report if the program attemps the advanced version
-f=FILENAME list all files whose SHA2 hash matches that of the indicated file
-h=HASH     list all files with the indicated SHA2 hash
-l          list all duplicate files
-q          quietly test if any duplicate files exist
```
