# Task №5 (`WW_io`)

A console application`./lab_05` that can read an ordered list of points from a specific text or binary file and perform the following actions: save the read points to another file in text or binary format, display the number of points and all points on the screen in the format specified as the command line parameter.

It is guaranteed that the coordinates do not exceed 5'000'000 modulo (five million).

### The format of text files.
A text file containing `N` dots consists of` N` lines.
Each line ends with a linefeed character.
Each line contains exactly two integers, separated by exactly one space:
The `x`- coordinate of the point and the` y`- coordinate of the point.
Other characters in the file are missing, leading zeros are missing.

### The format of binary files.
A binary file containing `N` points consists of` 6N` bytes.
Each point is stored as 6 consecutive bytes: three bytes store the coordinate
`x`, and the next three bytes store the` y` coordinate.

Non-negative numbers are stored byte: from low bytes to high.
For example, the number 1000 should be stored as three consecutive bytes with
values of `232, 3, 0`.

### Console application
The application is launched with the following command:
```
./lab_05 (loadtext | loadbin) <infile> <action...>
```

The following parameters are used here:

* `(loadtext | loadbin)` determines a type of input file: `loadtext` for text, `loadbin` for binary. One parameter.
* `<infile>` is a relative path to the input file, that contains points. One parameter.
* `<action...>` is an operation that should be executed for these points. It is defined by one or several parameters.
  * `(savetext | savebin) <outfile>` is an operation that saves read points to the file `<outfile>` in text (`savetext`) or binary (`savebin`) format;
  * `print <fmt>` is an operation that displays all points on the screen, printf-string `<fmt>` is used for output.
    There must be exactly two specifiers: the first `%d` corresponds to `x`-coordinate and the second corresponds to `y`-coordinate;
    Delimiters that are not specified in `<fmt>` should not be added (e. g. spaces).
    The program prints a line feed after execution.
  * `count` is an operation that prints the number of points and a line feed.

It is guaranteed that an input file matches the format.

Work example:

```
$ cat test.txt
1 2
4 3
5 5
$ ./lab_05 loadtext test.txt savetext out.txt
$ cat out.txt
1 2
4 3
5 5
$ ./lab_05 loadtext test.txt count
3
$ ./lab_05 loadtext test.txt print "[%d, %d] "
[1, 2] [4, 3] [5, 5] 
$ ./lab_05 loadtext test.txt print "[%d, %d]"
[1, 2][4, 3][5, 5]
$ ./lab_05 loadtext test.txt savebin out.bin
$ hexdump -C out.bin
00000000  01 00 00 02 00 00 04 00  00 03 00 00 05 00 00 05  |................|
00000010  00 00                                             |..|
00000012
$ ./lab_05 loadbin out.bin print "%d %d "
1 2 4 3 5 5 
```

### Implementation of `print` and `count` operations
Operations `print` and `count` are implemented using `apply` function.
`get_length` is not used for implementation of `count`.

`apply` executes some unary operation for all elements of the list
(for example, output on display).
It is implemented in files `clist.h` and `clist.c` and works for lists of elements of arbitrary type:

```C++
void apply(intrusive_list *list, void (*op)(intrusive_node *node, void *data), void *data);
```

Here, `data` parameter is not used by `apply` function directly, but passes it to `op` function as additional parameter.
It is necessary for passing arbitrary parameters (besides the list element) to `op` without changing the signature of `apply`.
`data` can also be used for getting arbitrary values from `op`.
