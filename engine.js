// engine.js
const { default: markdownItShiki } = require('markdown-it-shiki');

module.exports = ({ marp }) =>
  marp.use(markdownItShiki, { theme: 'light-plus' })
