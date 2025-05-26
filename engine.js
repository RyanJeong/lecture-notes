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
    if (lang && hljs.getLanguage(lang)) {
      return hljs.highlight(code, { language: lang }).value
    }
    return hljs.highlightAuto(code).value
  }

  return marp
}
