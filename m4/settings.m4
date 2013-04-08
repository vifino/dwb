include(includes.m4)
html_header(General)
html_input(auto-load-images, checkbox, Load images automatically)
html_input(auto-resize-window, checkbox, Autoresize the window)
html_input(auto-shrink-images, checkbox, Automatically shrink standalone images to fit)
html_input(default-encoding, text, Default encoding used to display text)
html_input(enable-private-browsing, checkbox, Whether to enable private browsing mode)
html_input(enable-spell-checking, checkbox, Whether to enable spell checking)
html_input(full-content-zoom, checkbox, Whether the full content is scaled when zooming)
html_input(load-on-focus, checkbox, Whether to defer loading uris until a tab gets focus)
html_input(resizable-text-areas, checkbox, Whether text areas should be resizable)
html_input(scroll-step, text, Scroll step)
html_input(spell-checking-languages, text, ``Languages used for spell checking, seperated by commas'')
html_input(startpage, text, The default homepage)
html_input(zoom-level, text, The default zoom level)
html_input(zoom-step, text, The zoom step)
dnl 
html_header(Network &amp Session)
html_input(accept-language, text, If set will be used for "Accept-Language" header in all requests)
ifdef(`WITH_LIBSOUP_2_38', 
html_input(addressbar-dns-lookup, checkbox, Whether to first perform a dns lookup for text typed in the addressbar before loading the site)
)
html_select(cookies-accept-policy, html_options(always, never, nothirdparty), ``The cookies to accept, affects also session cookies'')
html_select(cookies-store-policy, html_options(session, persistent, never), The storage policy for cookies)
html_input(do-not-track, checkbox, Whether to set do not track flag on request headers)
html_input(enable-dns-prefetching, checkbox, Whether webkit prefetches domain names)
html_input(proxy, checkbox, Whether to use a HTTP-proxy)
html_input(proxy-url, text, The HTTP-proxy url)
html_input(save-session, checkbox, Whether to Automatically save sessions)
html_input(single-instance, checkbox, Whether to have only one instance)
ifdef(`WITH_LIBSOUP_2_38', 
html_input(ssl-use-system-ca-file, checkbox, Whether to use the system certification file), 
html_input(ssl-ca-file, text, Path to ssl-certificate)
)
dnl SSL_CERTIFICATION
html_input(ssl-strict, checkbox, Whether to allow only safe ssl-certificates)
html_input(use-ntlm, checkbox, Whether to use ntlm-authentication)
html_input(user-agent, text, The user agent string)
dnl 
html_header(Fonts)
html_input(cursive-font-family, text, Cursive font family used to display text)
html_input(default-font-family, text, Default font family used to display text)
html_input(default-font-size, text, Default font size used to display text)
html_input(default-monospace-font-size, text, Default monospace font size used to display text)
html_input(fantasy-font-family, text, Fantasy font family used to display text)
html_input(font, text, Default font used for the ui)
html_input(font-entry, text, Font for the addressbar)
html_input(font-hidden-statusbar, text, Font for the status elements if statusbar is hidden )
html_input(font-nofocus, text, Font of tabs/completion items without focus)
html_input(minimum-font-size, text, Minimum font size used to display text)
html_input(minimum-logical-font-size, text, Minimum logical font size used to display text)
html_input(monospace-font-family, text, Monospace font family used to display text)
html_input(sans-serif-font-family, text, Sans serif font family used to display text)
html_input(serif-font-family, text, Serif font family used to display text)
dnl 
html_header(Colors)
html_input(active-completion-bg-color, text, Background color of the active completion item)
html_input(active-completion-fg-color, text, Foreground color of the active completion item)
html_input(background-color, text, Background color of the statusbar)
html_input(download-bg-color, text, Background color of the download bar)
html_input(download-fg-color, text, Foreground color of the download bar)
html_input(download-gradient-end, text, End color for download progress gradient color)
html_input(download-gradient-start, text, Start color for download progress gradient color)
html_input(error-color, text, Color for error messages)
html_input(foreground-color, text, Foreground color of the statusbar)
html_input(normal-completion-bg-color, text, Background color of normal completion items)
html_input(normal-completion-fg-color, text, Foreground color of normal completion items)
html_input(private-color, text, Statusbar color used with enable-private-browsing enabled)
html_input(progress-bar-empty-color, text, Color of the empty part of the progress bar)
html_input(progress-bar-full-color, text, Color of the full part of the progress bar)
html_input(prompt-color, text, Color for prompt messages)
html_input(ssl-trusted-color, text, ``Color for encrypted sites, trusted certificate'')
html_input(ssl-untrusted-color, text, ``Color for encrypted sites, untrusted certificate'')
html_input(status-allowed-color, text, ``Color for script blocker, status allowed'')
html_input(status-blocked-color, text, ``Color for script blocker, status blocked'')
html_input(tab-active-bg-color, text, Background color of the active tab)
html_input(tab-active-fg-color, text, Foreground color of the active tab)
html_input(tab-normal-bg-color-1, text, Background color 1 of the normal tab)
html_input(tab-normal-bg-color-2, text, Background color 2 of the normal tab)
html_input(tab-normal-fg-color-1, text, Foreground color 1 of the normal tab)
html_input(tab-normal-fg-color-2, text, Foreground color 2 of the normal tab)
html_input(tab-number-color, text, Color of the tabnumber)
html_input(tab-protected-color, text, Color of the tabnumber for protected tabs)
dnl 
html_header(Layout)
html_input(background-tabs, checkbox, Whether to open tabs in background)
html_input(bars-padding, text, ``Padding of the status, download, completion and tab bars'')
html_select(close-tab-focus-policy, html_options(right, left, rightmost, leftmost), Controls the focused tab when a tab is closed)
html_input(default-height, text, Default height of the window)
html_input(default-width, text, Default width of the window)
html_input(enable-favicon, checkbox, Whether to enable favicons in the tabbar)
html_input(enable-frame-flattening, checkbox, Whether to enable frame flattening)
html_input(enforce-96-dpi, checkbox, Enforce a resolution of 96 dpi)
html_input(factor, text, Zoom factor of the tiling area)
html_input(message-delay, text, ``Time messages are shown, in seconds'')
html_select(new-tab-position-policy, html_options(right, left, rightmost, leftmost), Controls the position of newly created tabs)
html_select(progress-bar-style, html_options(default, simple), The progress bar style)
html_input(show-single-tab, checkbox, Whether to show the tabbar if only one tab is open)
html_input(scrollbars, checkbox, Whether scrollbars should be enabled)
html_input(tabbar-visible, text, Number of seconds a hidden tabbar is visible when switching between tabs)
html_input(tabbed-browsing, checkbox, Whether to enable tabbed browsing)
html_input(user-stylesheet-uri, text, The uri of a stylesheet applied to every page)
html_input(widget-packing, text, ``Packing of the main widgets; t (T)=tabbar (hidden), w=webview, s (S)=statusbar (hidden), d=downloadbar'')
dnl 
html_header(Hints)
html_input(hint-active-color, text, Color of active links in hintmode)
html_input(hint-autofollow, checkbox, Whether to follow hints automatically if only one hint matches the typed letters)
html_input(hint-bg-color, text, Background color of hints)
html_input(hint-border, text, Border used for hints)
html_input(hint-fg-color, text, Foreground color of hints)
html_input(hint-font, text, Font used for hints)
html_input(hint-highlight-links, checkbox, Whether to highlight links)
html_input(hint-letter-seq, text, Letter sequence for letter hints)
html_input(hint-normal-color, text, Color of inactive links in hintmode)
html_input(hint-opacity, text, Opacity used for hints)
html_select(hint-style, html_options(letter, number), Whether to use 'number' or 'letter' hints)
html_input(hints-key-lock, text, Timeout in milliseconds all keypresses are ignored after following a hint)
dnl 
html_header(Plugins &amp Scripts)
html_input(adblocker, checkbox, Whether to block advertisements via a filterlist)
html_input(adblocker-filterlist, text, Path to a adblock plus compatible filterlist)
html_input(enable-java-applet, checkbox, Whether to enable java applets)
html_input(enable-plugins, checkbox, Whether to enable plugins)
html_input(enable-scripts, checkbox, Enable embedded scripting languages)
ifdef(`WITH_HSTS', 
html_input(hsts, checkbox, Whether HSTS support should be enabled)
)
html_input(javascript-can-access-clipboard, checkbox, Whether javascript can access the clipboard)
html_input(javascript-can-open-windows-automatically, checkbox, Whether javascript can open windows)
html_input(javascript-schemes, checkbox, Whether to allow loading url with scheme "javascript")
html_input(plugin-blocker, checkbox, Whether to block plugins and replace them with a clickable element)
dnl 
html_header(Completion)
html_input(auto-completion, checkbox, Whether to show possible shortcuts)
html_input(complete-bookmarks, checkbox, Whether to enable tabcompletion for bookmarks)
html_input(complete-history, checkbox, Whether to enable tabcompletion for browsing history)
html_input(complete-searchengines, checkbox, Whether to enable tabcompletion for searchengines)
html_input(complete-userscripts, checkbox, Whether to enable tabcompletion for userscripts)
html_input(max-visible-completions, text, The maximal number of visible completions)
dnl 
html_header(Miscellaneous)
html_input(auto-insert-mode, checkbox, Whether to automatically go in insert mode if an editable element has focus after loading)
html_select(cache-model, html_options(webbrowser, documentviewer), The cache-model used by webkit )
html_select(close-last-tab-policy, html_options(ignore, clear, close), Behaviour when the last tab is closed)
html_input(custom-encoding, text, The custom encoding of the view)
html_input(download-directory, text, Default download directory)
html_input(download-external-command, text, External application used for downloads)
html_input(download-no-confirm, checkbox, Whether to immediately start a download if download-directory is set)
html_input(download-use-external-program, checkbox, Whether to use an external download helper)
html_input(editable, checkbox, Whether content can be modified)
html_input(editor, text, External editor used for inputs/textareas)
html_input(enable-accelerated-compositing, checkbox, Whether to enable gpu accelerated compositing)
html_input(enable-caret-browsing, checkbox, Whether to enable caret browsing)
html_input(enable-default-context-menu, checkbox, Whether to enable the right click context menu)
html_input(enable-developer-extras, checkbox, Whether developer extensions should be enabled)
html_input(enable-dom-paste, checkbox, Whether to enable DOM paste)
html_input(enable-file-access-from-file-uris, checkbox, Whether file access from file uris is allowed)
html_input(enable-html5-database, checkbox, Enable HTML5 client side SQL-database support)
html_input(enable-html5-local-storage, checkbox, Enable HTML5 local storage)
html_input(enable-offline-web-application-cache, checkbox, Enable HTML5 offline web application cache)
html_input(enable-page-cache, checkbox, Enable page cache)
html_input(enable-site-specific-quirks, checkbox, Enable site specific compatibility workarounds)
html_input(enable-spatial-navigation, checkbox, Enable spatial navigation)
html_input(enable-universal-access-from-file-uris, checkbox, Whether to allow files loaded through file: )
html_input(enable-webgl, checkbox, Enable or disable webgl on pages)
html_input(enable-xss-auditor, checkbox, Whether to enable the xss auditor)
html_input(file-sync-interval, text, ``Interval to save files to hdd or 0 to directly write to hdd, see also sync-files'')
html_input(history-length, text, Length of the browsing history)
html_input(navigation-history-max, text, Length of the navigation history)
html_select(passthrough-keys, html_options(all, webkit, none), Pass keys to the website)
html_input(print-backgrounds, checkbox, Whether background images should be printed)
html_input(print-previewer, text, ``Program used for printing previews, %f will be replaced by the filename'')
html_input(scheme-handler, text, ``Application, or script that handles uris with schemes that cannot be handled by dwb '')
html_input(searchengine-submit-pattern, text, The pattern which will be replaced with the search terms)
html_select(sync-files, html_options(all, cookies, history, session, cookies_history, cookies_session, history_session), ``Files to sync, see also file-sync-interval'')
html_input(tab-key-cycles-through-elements, checkbox, Tab cycles through elements in insert mode)
html_input(update-search-delay, text, Delay before updating search results in milliseconds)
