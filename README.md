# get_next_line

`Get_next_line` is a function that reads an entire line
from a file indexed by a file descriptor `fd`.
It then alocates a string with the contents
of that line without the linebreak `'\n'` and points `line` to it.

We don't have to pass anything allocated to `get_next_line`,
we just pass the address of a pointer that will point to the allocated string.
`line` should be freeable with `free()` after the function call
unless an error occured.

We will incrementally read the file with `read()`,
which advances its position in the file dexample escriptor automatically.

We need to use a static pointer as a read buffer
to access what was read in previous calls.

We need to handle the following situations:

1. If the read buffer doesn't have a `'\n'`, we concatenate
   with the previous buffer and call read again.
2. If the read buffer has a `'\n'`,
   we concatenate with the previous buffer up to `'\n'`.
3. If we reach the end of the file (`read() == 0`),
   we concatenate with the previous buffer.
4. We finally point `line` to an allocated string
   that contains the entire line without the `'\n'`.
   Then we release the memory allocated in the intermediate strings
   and return `1` or `0` for `'\n'` and `end_of_file` respectively.
5. If the parameters have any problems (`BUFFER_SIZE <= 0`),
   or if in any operation we were unable to allocate memory,
   we free whatever memory was allocated and return -1.

## Usage

The function is written in C language and thus needs the **`gcc` compiler** and some standard **C libraries** to run.

To use the function in your code, simply include its header:

```C
#include "get_next_line.h"
```

and, when compiling your code, add the source files and the required flag:

```shell
get_next_line.c get_next_line_utils.c -D BUFFER_SIZE=<size>
```

## Testing

You only have to edit the get_next_line.c file and uncomment the main function and headers inside it.
You can edit test.txt files to put another text if you wish to test othe cases.
Then simply run this command (change "xx" with desired buffer size) :

```shell
gcc -Wall -Werror -Wextra -D BUFFER_SIZE=xx get_next_line.c get_next_line_utils.c && ./a.out
```

Or you can also use this third party tester to fully test the project

* [Tripouille/gnlTester](https://github.com/Tripouille/gnlTester)
