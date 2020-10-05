# ft_printf
21-School (Ecole42) 'ft_printf' project. Score 111/115

My own realization of printf (stdio.h) function.

Function implements `csdiupxXofne%` specificators with `-+ #0` flags and `h`, `hh`, `l`, `ll` modifiers, and considers `width` and `precision` parameters (https://en.wikipedia.org/wiki/Printf_format_string for more info)

# Usage:
`make` in the root of the repository to build library `libftprintf.a`, include `ft_printf.h` in program, compile program with this library.

# Example:
main.c
```
#include "ft_printf.h"

int main(void) 
{
  ft_printf("%.7s%c%0*d\n", "Example foo bar", ' ', 8, 999);
  return 0;
}
```
compile and launch
```
$> gcc main.c -L. -lftprintf -o a.out
$>./a.out
Example 00000999
```
