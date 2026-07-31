*This project has been created as part of the 42 curriculum by fnguegan.*

# get_next_line

## Description

get_next_line is a C project that implements a function named `get_next_line(int fd)`.
It reads a file descriptor one line at a time, returning the next available line each time it is called.
The goal of the project is to practice low-level file input/output, dynamic memory allocation, and stateful parsing in C.

This implementation is designed to work with arbitrary input sizes and to preserve unread characters between calls so that each invocation returns the next line without re-reading the whole file.

## Algorithm

The selected approach uses a persistent internal buffer, often called a pool, to keep the unread portion of the file between calls.

1. A static character buffer stores any leftover data that was not returned yet.
2. On each call, the function checks whether a newline has already been found in the buffer.
3. If no newline is present, it reads additional chunks from the file descriptor using `read()`.
4. Each chunk is appended to the existing buffer until a newline is found or the file reaches EOF.
5. The function extracts the current line up to the newline, returns it to the caller, and keeps the remainder in the buffer for the next call.
6. When the stream is exhausted and no more data remains, the buffer is released and the function returns `NULL`.

This algorithm was chosen because it is efficient for streaming input: it does not require reading the entire file at once, and it handles repeated calls naturally while keeping memory usage predictable.
It also fits the project’s educational objective by demonstrating how state can be preserved across function calls in C.

## Instructions

### Requirements

- A C compiler such as `gcc`
- Standard C libraries

### Compilation

From the repository root, compile the project with:

```sh
cc -Wall -Wextra -Werror -D BUFFER_SIZE=42 -o get_next_line get_next_line.c get_next_line_utils.c
```

You can change the buffer size at compile time if needed:

```sh
cc -Wall -Wextra -Werror -D BUFFER_SIZE=1000 -o get_next_line get_next_line.c get_next_line_utils.c
```

### Example usage

A simple test can be written like this:

```c
#include "get_next_line.h"
#include <fcntl.h>
#include <stdio.h>

int main(void)
{
    int fd = open("test.txt", O_RDONLY);
    char *line;

    while ((line = get_next_line(fd)) != NULL)
    {
        printf("%s", line);
        free(line);
    }
    close(fd);
    return (0);
}
```

## Resources

Classic references and documentation related to this topic:

- The Unix manual pages for `read(2)`, `open(2)`, `malloc(3)`, and `free(3)`
- C programming references covering dynamic memory management and string handling
- Tutorials on file descriptors and buffered input in C

### AI usage

AI tools were used to help:

- clarify the structure of the `get_next_line` logic and the role of the static buffer,
- review memory handling and edge cases such as empty lines and EOF,
- and draft this README in a clear, project-oriented format.

The implementation itself was written and verified manually as part of the project.
