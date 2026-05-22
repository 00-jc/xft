# Style Rules

## Naming
- Structs prefixed `s_`, typedefs `t_`, unions `u_`, enums `e_`, globals `g_`.
- All identifiers use lowercase snake_case only.
- File and directory names use lowercase snake_case only.
- No non-ASCII characters outside literal strings/chars.
- Identifiers must be explicit or mnemonic, readable in English.
- Non-const, non-static global variables are forbidden.

## Formatting
- Max 25 lines per function (excluding its own braces).
- Max 80 columns per line, comments included (tabs count as their visual width).
- Functions separated by at least one empty line.
- Indent with real tabs (4-char width, ASCII 9).
- Braces on their own line, except in struct/enum/union declarations.
- Empty lines must be truly empty (no trailing spaces/tabs).
- Lines never end with spaces or tabs.
- No two consecutive empty lines. No two consecutive spaces.
- Variable declarations at the top of a function.
- Variable names aligned on the same column within their scope.
- Pointer asterisks stick to the variable name.
- One variable declaration per line.
- No simultaneous declaration and initialization (except globals, statics, constants).
- One empty line between declarations and the rest of the function; no other empty lines inside functions.
- One instruction or control structure per line.
- Long lines split with indentation; operators go at the start of the new line.
- Commas and semicolons followed by a space (unless end of line).
- One space around each operator/operand.
- Space after C keywords, except type keywords and `sizeof`.
- Control structures use braces unless they contain a single instruction on a single line.

## Functions
- Max 4 named parameters.
- No-argument functions prototyped with `void`.
- Prototype parameters must be named.
- Max 5 variable declarations per function.
- Return values in parentheses; void returns have none.
- One tab between return type and function name.
- All functions should be annotated with all pertinent attributes

## Typedef, Struct, Enum, Union
- Space between the keyword and the name.
- Regular indentation rules inside braces.
- Structure names aligned on the same column within their scope.
- Structs cannot be declared in `.c` files.

## Headers
- Headers may only contain: includes, declarations, defines, prototypes, macros.
- All includes at the top of the file.
- Never include a `.c` file.
- Double-inclusion protection via bystander macro (`FT_FOO_H` for `ft_foo.h`).
- No unused header inclusions.

## 42 Header
- Every `.c` and `.h` file starts with the standard 42 header.
- Header must have up-to-date creator, login, email, creation date, and last update info.

## Macros & Preprocessor
- `#define` only for literal and constant values.
- No defines to bypass the norm or obfuscate code.
- Standard library macros allowed only if completely necessary.
- No multiline macros.
- Macro names all uppercase.
- Indent preprocessor directives inside `#if`/`#ifdef`/`#ifndef`.
- Preprocessor instructions only in global scope.

## Forbidden
- `for`, `do...while`, `switch`, `case`, `goto`.
- Ternary operator (`?`).
- Variable Length Arrays.
- Implicit types in declarations.

## Comments
- No comments inside function bodies (only end-of-line or own line).
- Comments in English and useful.
- Comments don't justify bad or carryall functions.

## Files
- Never include a `.c` file in another `.c` file.
- Max 5 function definitions per `.c` file.

## Project-Specific Additions
- All logic must be contained in functions, no logic or control flow in macros.
- No inlining via preprocessor or logic in headers.
- Cross-translation-unit inlining is handled via LTO at the toolchain level.
- Cyclomatic complexity must NOT exceed 9 for any function (using GNU complexity).

All contributions or addtions to the code *MUST* follow these, including tests, fuzzes
or benchmarks, any C code, even if included in the library or not, must follow these rules.
