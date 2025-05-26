# Using a Custom Highlight.js Build in Marp CLI via engine.js

This guide shows how to use a custom build of [highlight.js](https://highlightjs.org/) with Marp CLI by configuring `engine.js`. This allows for better control over syntax highlighting, especially when the default highlight.js fails to properly handle certain languages like C or C++.

## Overview

* Download a custom highlight.js bundle from the official site
* Use Node.js's `vm` module to execute the bundled code
* Integrate it into Marp's rendering engine via `engine.js`

---

## Prerequisites

```bash
npm install --save-dev @marp-team/marp-core @marp-team/marp-cli
```

## Step 1: Download Highlight.js Bundle

1. Go to [https://highlightjs.org/download](https://highlightjs.org/download)
2. Select the languages you need (e.g., `bash`, `c`, `cpp`, `plaintext`, etc.) (NB: All highlighting languages you're using on markdown files must be included.)
3. Click **Download**
4. Extract the downloaded archive and place `highlight.js` in your project:

```text
lecture-notes/
├── engine.js
├── highlight/
│   └── highlight.js  # <- Downloaded bundle
├── theme.css
└── c/06/temp.md
```

---

## Step 2: Configure `engine.js`

```js
const { Marp } = require('@marp-team/marp-core')
const vm = require('vm')
const fs = require('fs')
const path = require('path')

// 1. Load highlight.js bundle code
const highlightJsCode = fs.readFileSync(path.join(__dirname, 'highlight/highlight.js'), 'utf8')
const context = {
  module: {},
  exports: {},
  console: console,
}
vm.createContext(context)
vm.runInContext(highlightJsCode, context)

// 2. Extract hljs from module.exports
const hljs = context.module.exports || context.exports.hljs

// 3. Optional: Debug which languages are registered
console.log('Registered languages:', hljs.listLanguages())

// 4. Register custom Marp engine
module.exports = (opts) => {
  const marp = new Marp(opts)

  marp.highlighter = (code, lang) => {
    if (lang && hljs.getLanguage(lang)) {
      return hljs.highlight(code, { language: lang }).value
    }
    return hljs.highlightAuto(code).value
  }

  return marp
}
```

> `vm` allows executing the highlight.js bundle safely in an isolated context.

---

## Step 3: Run Marp CLI with Custom Engine

```bash
npx marp --engine ./engine.js <PATH_MARKDOWN> --pdf --theme <PATH_CSS> --allow-local-files
```

You should now see syntax-highlighted code blocks in your generated PDF.
