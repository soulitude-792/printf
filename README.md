*This activity has been created as part of the 42 curriculum by imigdady.*

# ft_printf

## Description

**ft_printf** is a re-implementation of the C standard library function `printf`, built as a static library (`libftprintf.a`). The goal of the project is to learn how variadic functions work in C (`<stdarg.h>`) and to practice splitting a program into small, reusable helpers.

`ft_printf` reads a format string, prints ordinary characters as they are, and replaces each conversion specifier with the matching argument. It returns the number of characters printed, like the original.

Supported conversions:

| Specifier | Output |
|-----------|--------|
| `%c` | A single character |
| `%s` | A string (`(null)` if the pointer is `NULL`) |
| `%p` | A pointer in hexadecimal with `0x` prefix (`(nil)` if `NULL`) |
| `%d` / `%i` | A signed decimal integer |
| `%u` | An unsigned decimal integer |
| `%x` | An unsigned integer in lowercase hexadecimal |
| `%X` | An unsigned integer in uppercase hexadecimal |
| `%%` | A literal percent sign |

Only `write`, `malloc`, `free` and the `va_*` macros are used, as required by the subject.

### Project structure

| File | Content |
|------|---------|
| `printf.h` | Header with the prototypes |
| `printf.c` | `ft_printf`, the main loop |
| `printf2.c` | Output helpers: `ft_putchar`, `ft_putstr`, `ft_putnbr`, `ft_putunbr`, `puthex` |
| `printf3.c` | Conversion dispatch: `check_specifier`, `check_num`, `ft_putptr` |
| `Makefile` | Builds `libftprintf.a` |

### Algorithm and design choices

**Main loop.** `ft_printf` walks through the format string one character at a time, in a single pass.
- A normal character is written directly and adds 1 to the count.
- A `%` makes the loop move to the next character, which is the conversion letter. That letter is passed to `check_specifier`, and the number of characters it printed is added to the count. The index then moves past the letter so it is not printed as plain text.
- A lone `%` at the end of the string stops the loop, so the function never reads past the terminating `'\0'`.

**Reading the arguments.** A single `va_list` is created with `va_start` and a pointer to it (`va_list *`) is given to the helpers. Because the same `va_list` is shared, each `va_arg` call advances to the next argument, and the position is kept from one conversion to the next. This is why `va_copy` is not needed: every argument is read exactly once, in order. `va_end` is called before returning. Each conversion reads the type it needs: `int` for `%c`, `%d`, `%i`; `unsigned int` for `%u`, `%x`, `%X`; `char *` for `%s`; `void *` for `%p`.

**Dispatch.** `check_specifier` handles `%c`, `%s` and `%%`, and passes the other letters to `check_num`. An unknown conversion prints nothing and returns 0, so the count stays correct. The dispatch is split into two functions to respect the Norm limits.

**Printing numbers.** Digits are printed recursively: to print `123`, the function first prints `12` and then the last digit (`123 % 10`, turned into a character with `+ '0'`). This prints the most significant digit first without needing a buffer or any dynamic allocation. Every function returns the number of characters it wrote, so the total can be added up as the recursion unwinds.
- `ft_putnbr` stores the value in a `long` before negating it, so that `INT_MIN` does not overflow.
- `ft_putunbr` works directly on an `unsigned int`, since there is no sign and division can only make the value smaller.
- `puthex` takes the digit string as a parameter (`"0123456789abcdef"` or `"0123456789ABCDEF"`), so one function serves `%x`, `%X` and `%p`. It uses `unsigned long long` so that a 64-bit address fits on any platform.

**Data structures.** No custom data structure is needed. The only structure involved is the `va_list` provided by `<stdarg.h>`, which acts as a cursor over the unnamed arguments. Not allocating memory also means there are no leaks to manage.

## Instructions

**Compilation**

```sh
make
```

This builds `libftprintf.a` in the root of the repository. Other rules:

```sh
make clean    # remove object files
make fclean   # remove object files and libftprintf.a
make re       # fclean, then rebuild
```

**Usage**

Write a `main.c` that includes the header and link it with the library:

```c
#include "printf.h"

int main(void)
{
        int count;

        count = ft_printf("Hello %s, you are %d years old. Hex: %x\n", "world", 42, 255);
        ft_printf("Printed %d characters\n", count);
        return (0);
}
```

```sh
cc -Wall -Wextra -Werror main.c -L. -lftprintf -o test
./test
```

**Note on platforms.** The behavior of the real `printf` for `%p` and for `NULL` is platform-dependent. `ft_printf` follows the Linux (glibc) behavior: `%p` prints `0x...` and a `NULL` pointer prints `(nil)`. When comparing against the real `printf`, do it on Linux.

## Resources

**References**
- `man 3 printf`, the reference for conversion specifiers and the return value.
- `man 3 stdarg`, for `va_list`, `va_start`, `va_arg`, `va_copy` and `va_end`.
- `man 2 write`.
- The C standard (variadic functions and undefined behavior of invalid conversions).
- GeeksforGeeks articles on variadic functions in C.

**How AI was used**

AI (Claude) was used as a learning and review tool. The code was written by me.
- **Understanding concepts:** explanations of variadic functions and what `va_list`, `va_start`, `va_arg` and `va_end` do, the difference between compile time and runtime, macros and the preprocessor, and why `%d` and `%i` behave the same in `printf`. I rewrote these explanations in my own words.
- **Debugging and review:** reviewing my code to point out bugs (for example the wrong variable being written for `%c`, wrong character counting in the recursive number functions, and the missing `ft_putstr`), and explaining how to test against the real `printf`.
- **Support files:** generating drafts of the `Makefile` and the header file, which I then adapted to my files, and helping to split the conversion dispatch into smaller functions to satisfy the Norm.
- **Testing guidance:** suggesting edge cases (`INT_MIN`, `NULL` for `%s` and `%p`, lone `%` at the end of the format string).

AI was not used to write the conversion logic for me, and I checked its explanations against the man pages and by running my own tests.
