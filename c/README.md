# Lecture Notes - C

## Formatting Codes

```shell
for file in $(find . -name "*.*" | grep -E "\.(c|h)$"); do
  echo $file
  clang-format --style=file:/home/docker/clang-format/.clang-format-knr -i $file
  chmod 755 $file
done
```

## Test Codes

```shell
FILE_NAME="error_file_lists.txt"
MY_FLAGS="-c -fsyntax-only -ansi -Wall -Wextra -Werror"
> "$FILE_NAME"
for file in $(find . -name "*.*" | grep -E "\.c$"); do
  echo $file
  gcc $file $MY_FLAGS
  if [ $? -ne 0 ]; then
    echo "$file" >> "$FILE_NAME"
  fi
done
sort "$FILE_NAME" -o "$FILE_NAME"
```

## Converting Markdowns

```shell
CHAPTER=01

marp --pdf -w --allow-local-files --theme ../theme.css ${CHAPTER}/README.md -o $HOME/share/README.pdf
marp --pdf --allow-local-files --theme ../theme.css ${CHAPTER}/README.md
marp --pptx --allow-local-files --theme ../theme.css ${CHAPTER}/README.md
```
