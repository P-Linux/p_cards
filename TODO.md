# TODO


---


## Add extraction support for: debian dep files

see http://downloads.nutyx.org/8.0/x86_64/gui-extra/google-chrome/Pkgfile


## pkgmk.in supports now gettext translation files

* Need to translate them
* Decide where final PO files should be installed and add: `TEXTDOMAIN`, `TEXTDOMAINDIR`

Maybe suggestion:

    * export TEXTDOMAIN='pkgmk'
    * export TEXTDOMAINDIR='/etc/cards/pkgmk/locale'


IMPORTANT: a good number of messages still need to be changed to gettext


## Add documentation / man page info for PKGMK variables

Add documentation / man page info for ALL PKGMK options.

Split them into 2 categories:

* PKGMK.CONF VARIABLES: which can be set in the `pkgmk.conf`
* PKGMK INTERNAL VARIABLES: which should not be set in the `pkgmk.conf` but might be useful for developers.
    e.g. Pkgfiles

    * add info that PKGMK_ARCH variable exists: **currently I found 85 occurencies of `uname -m` in the 
        official Pkgfiles.


## Unify code style in `pkgmk.in`: backticks to parentheses style

Change all backticks to parentheses style [see](http://mywiki.wooledge.org/BashFAQ/082)


## Unify code style in `pkgmk.in`: Quoting Variables

Prefer quoted variables over unquoted. [see Quoting Variables](http://www.tldp.org/LDP/abs/html/quotingvar.html)

```
When referencing a variable, it is generally advisable to enclose its name in double quotes.
This prevents  reinterpretation of all special characters within the
quoted string -- except $, ` (backquote), and \ (escape).
```

## Unify code style in `pkgmk.in`: Double brackets

[see](http://mywiki.wooledge.org/BashFAQ/031)


## Re-write Documentation

* `pkgmk.in` rewrite info *Pkgfile: source (array)* (the big block at the top of the file)
    in the documentation and remove it from the `pkgmk.in` file
    

## CHECK: PKGMK.CONF VARIABLES: which can be set in the `pkgmk.conf`


## DIVERSE TODO

* Maybe: add Pkgfile syntax check for source=() array
