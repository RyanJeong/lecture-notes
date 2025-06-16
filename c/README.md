# Lecture Notes - C

## TODOS

- Constant: .text vs. .rodata
- Check table bottom margin
- Replace text block with bash shell when it's relative with terminal commands
- Continuous code (refer to ch01 - External Variables and Scope)
- Add tree information for examples at ch4, ch5, ch6, and ch7 and remove redundant files and headers
- Replace all Koreans in codes with English because of character encoding issues
- `volatile` -> Appendix of chapter 5
- Check cp02(Data Types and Sizes (Cont'd - 9), Data Types and Sizes (Cont'd - 18)) - Confirm to modify formula size
- Add an OT note
- Create a tokenizer to check each words is redundant (or typo)
- Add a dockerfile (add pedantic-errors)
  - Add a dockerfile and use it when evaluates assignments (refer to `./assignment`)
- Add a description how to setup a build environment using the dockerfile
- check GENERAL RULES of this file to keep consistency
- Consider how to manage snippet code
- 1) lint (ignore postfix files e.g., *_nolint*.c)
- 2) check (ignore postfix files e.g., *_nocheck*.c, add pedantic-errors)
- 3) split codes and snippets
* ./c/06/bsearch_exam/bsearch.c_[0:4]
```c
/* bsearch_exam/bsearch.c */  <<< 0

#include <stdio.h>
#include <stdlib.h>
/* continued on next slide */
```
* ./c/06/bsearch_exam/bsearch.c_[4:7]
```c
/* continued from previous slide */

    qsort(arr, SIZE, sizeof(int), cmp);

    printf("After sorting:\n");
    for (i = 0; i < SIZE; ++i)
        printf("%d ", arr[i]);

/* continued on next slide */
```
* ./c/06/bsearch_exam/bsearch.c_[7:]
```
/* continued from previous slide */
    int target = 16;
    printf("%d %s\n", target,
           (bsearch(&target, arr, SIZE, sizeof(int), cmp)
                ? "is found"
                : "is not found"));

    return 0;
}
```
* test1.c_snippet
```c
int main(void)
{
    int a;
}
```
->
```c
    int a;
```
* test2.c_snippet
```c
int a;

void skipped(void)
{
    int b;
}
```
->
```c
int a;

/* ... skipped ... */  << find skipped function, replace it with comment, append newline

    int b;
```
- Rename code and images, move not using contents to the directory `duplicated`
- Watermark (email address)
- add to build process to generate pptx's

## MARKDOWN WRITING GUIDELINES FOR NOTES

### GENERAL RULES

- Capitalize **every word** in headings like `#`, `##`, `###`, etc., but keep conjunctions and prepositions like **and**, **or** in lowercase.

- Begin **only the first word** with a capital letter in regular sentences.

- Use **bullet points (`-`)** for concise, list-style sentences.

- Use **bold (`**`)** text for emphasis.

- Use **blockquotes (`>`)** for quotations and full-sentence content not written in list format.

- Treat **each table cell** as a regular sentence.

- Use **backticks (`)** to highlight values, expressions, function names, and keywords in code.

- Write **mathematical expressions** using **MathJax**.

- Use **superscript characters** such as `⁰ ¹ ² ³ ⁴ ⁵ ⁶ ⁷ ⁸ ⁹ ⁺ ⁻ ⁽ ⁾` for inline power or notation expressions when MathJax is unnecessary or unavailable.

- Insert a space between a word and the opening parenthesis when using inline parentheses.

- Useful characters: → ← ≠ ± × ÷ ⎮⎮ ` `(half-space inside the quotes)  ≡ (identically equal)

### Files

- `1.c` or `1.h`

Codes for attaching in lecture notes.

- `*_ignore.c` or `*_ignore.h`

Code snippets required for lecture notes. Skip checking syntax.

- `*_part1.c`, `*_part2.c`, ... , `*partn.c`

Split codes for attaching in lecture notes. Skip checking syntax.

## Formatting

```shell
CHAPTER=01

cd $CHAPTER
../lint.sh
```

## Checking Syntax

```shell
CHAPTER=01

cd $CHAPTER
../check_syntax.sh
```

## Converting Markdowns

```shell
CHAPTER=01

marp --pdf -w --allow-local-files --theme ../theme.css ${CHAPTER}/README.md -o $HOME/share/README.pdf
marp --pdf --allow-local-files --theme ../theme.css ${CHAPTER}/README.md
marp --pptx --allow-local-files --theme ../theme.css ${CHAPTER}/README.md
```

## References

- ANSI X3.159-1989 (ANSI C (C89) §3.2.1.5 — "Floating Promoions")
