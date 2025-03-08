# Lecture Notes - C

## Formatting

```shell
for file in $(find . -name "*.*" | grep -E "\.(c|h)$"); do
  echo $file
  clang-format --style=file:/home/docker/clang-format/.clang-format-knr -i $file
  chmod 755 $file
done
```

## Markdown Template

```markdown
---
marp: true
theme: notes
style: |
    img[alt~="center"] {
      display: block;
      margin: 0 auto;
    }
math: mathjax
---
```

## Converting Markdowns

```shell
marp --pdf -w --allow-local-files --theme ../theme.css README.md
marp --pdf --allow-local-files --theme ../theme.css README.md
marp --pptx --allow-local-files --theme ../theme.css README.md
```
