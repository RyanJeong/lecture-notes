// engine.js
const { default: markdownItShiki } = require('markdown-it-shiki');

// node_modules/shiki/themes
// https://github.com/shikijs/textmate-grammars-themes/tree/main/packages/tm-themes
  // marp.use(markdownItShiki, { theme: 'solarized-dark' })
  // marp.use(markdownItShiki, { theme: 'vitesse-black' })
  // marp.use(markdownItShiki, { theme: 'vitesse-dark' })
  // marp.use(markdownItShiki, { theme: 'light-plus' })
  // marp.use(markdownItShiki, { theme: 'min-light' })
  // marp.use(markdownItShiki, { theme: 'rose-pine-dawn' })
  // marp.use(markdownItShiki, { theme: 'slack-ochin' })
  // marp.use(markdownItShiki, { theme: 'solarized-light' })
  // marp.use(markdownItShiki, { theme: 'vitesse-light' })
  // marp.use(markdownItShiki, { theme: 'material-theme-ocean' })
  // marp.use(markdownItShiki, { theme: 'min-dark' })
  // marp.use(markdownItShiki, { theme: 'nord' })
  // marp.use(markdownItShiki, { theme: 'one-dark-pro' })
  // marp.use(markdownItShiki, { theme: 'poimandres' })
  // marp.use(markdownItShiki, { theme: 'rose-pine-moon' })
  // marp.use(markdownItShiki, { theme: 'rose-pine' })
  // marp.use(markdownItShiki, { theme: 'slack-dark' })
  // marp.use(markdownItShiki, { theme: 'dracula' })
  // marp.use(markdownItShiki, { theme: 'dracula-soft' })
  // marp.use(markdownItShiki, { theme: 'material-theme-lighter' })
  // marp.use(markdownItShiki, { theme: 'dark-plus' })
  // marp.use(markdownItShiki, { theme: 'github-dark-dimmed' })
  // marp.use(markdownItShiki, { theme: 'material-theme-darker' })
  // marp.use(markdownItShiki, { theme: 'material-theme-palenight' })
  // marp.use(markdownItShiki, { theme: 'monokai' })
module.exports = ({ marp }) =>
  marp.use(markdownItShiki, { theme: 'github-light' })
  // marp.use(markdownItShiki, { theme: 'github-dark' })
  // marp.use(markdownItShiki, { theme: 'material-theme' })
