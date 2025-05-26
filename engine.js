// engine.js
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
    const actualLang = (lang === 'c') ? 'cpp' : lang

    if (actualLang && hljs.getLanguage(actualLang)) {
      return hljs.highlight(code, { language: actualLang }).value
    }
    return hljs.highlightAuto(code).value
  }

  return marp
}

// DEBUG: what class is applied
const html1 = hljs.highlight('typedef int Length;', { language: 'cpp' }).value
console.log(html1)
const html2 = hljs.highlight('typedef int (*PFI)(char *, char *);', { language: 'cpp' }).value
console.log(html2)

// const html3 = hljs.highlight('char *alloc(), *str;', { language: 'cpp' }).value
// console.log(html3)
// const html4 = hljs.highlight('char *str, *alloc()', { language: 'cpp' }).value
// console.log(html4)

