# Lecture Notes - C

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

- Useful characters: → ≠ ±

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
