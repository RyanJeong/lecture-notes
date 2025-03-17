# Lecture Notes - C

## Notation

* `*_ignore.c` or `*_ignore.h`

Code snippets required for lecture notes. Skip checking syntax.

* `*_part1.c`, `*_part2.c`, ... , `*partn.c`

Split code for attaching in lecture notes. Skip checking syntax.

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
