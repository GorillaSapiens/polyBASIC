This directory should contain documentation specific to polyBASIC.

The DEVIATIONS.txt file contains notes about changes or differences from
other flavors of BASIC.

In general, 2 environment variables should be defined:
POLYBASICPATH specifies the directory with keyword translation files
POLYBASICLANG specifies the specific language to be used

Usage: polybasic [-f] [-t] [-l <language>] [<input.bas>]
      -f : debug flex parser output, and then run program
      -t : dump parse tree, do not run program
      -l : specify language, overriding POLYBASICLANG env variable
      if <input.bas> is omitted, read program from STDIN.
         this is not recommended, and may not play well with INPUT statements.

