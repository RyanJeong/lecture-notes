# Notes

C++ 내용들을 정리한 디렉토리입니다.

## TODOs

* Create a Dockerfile to generate pdfs automatically using CI/CD
* Parse each README.md to name the generated pdf file
* Improve contents periodically (`move`, `thread`, `template-meta`, etc.)

## [WIP] Index

* [01 - C++ 기초](./01)
* [02 - 레퍼런스](./02)
* [03 - 클래스와 생성자](./03)
* [04 - 참조와 포인터](./04)
* [05 - 문자열](./05)
* [06 - 클래스 간의 관계](./06)

---

## References

* [cplusplus.com](https://cplusplus.com/)
* [cppreference.com](https://en.cppreference.com/w/)
* [Google C++ Style Guide](https://google.github.io/styleguide/cppguide.html)
* [씹어먹는 C++](https://modoocode.com/135)

## Appendix

### A. `Marp for VS Code`

* `settings.json`

```json
// After installing the VSCode extention: marp
"markdown.marp.themes": ["./notes/theme.css"]
```

* Command

```shell
# 1. install marp-cli to use useful commands on the terminal:
npm install -g @marp-team/marp-cli

# 2. run commands on the terminal as below:
marp --pdf -w --allow-local-files --theme ../theme.css README.md
marp --pdf --allow-local-files --theme ../theme.css README.md
marp --pptx --allow-local-files --theme ../theme.css README.md
```

### B. `Paste Image`

* How to Use

1. Install the VSCode extension `Paste Image`
2. Copy an image what you want to paste
3. Select some text as the image file name, press `CMD + Alt + V'
