================
Doctor Clanglove
================
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^
Or: How I Learned to Stop Worrying and Love the Compiler
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

------------------
Primer: Acceptance
------------------

Before working with my software, it is important for you to come to terms with a
few essential truths. Once you have accepted these, time spent with my codebase
will be less painful.

 * clang developers are clever, motivated, well-educated, numerous, funded and
   well-organized. I am none of these things.

 * I have a rationale for everything I do. Sometimes, you will think my rationale
   is bad/erroneous (often you may be right). However, thought does go into
   everything.

 * I really and sincerely appreciate feedback, but I reserve the right to ignore
   it. If you don't like how I do things, fork my code and do things your way.
   If your way turns out to be better, I will almost certainly shamelessly admit
   my error and steal your code.

 * I generally assume that you, the user of ariel, have an expert command of the
   C++ language and a familiarity with the Boost C++ libraries and template
   metaprogramming. No knowledge of clang/LLVM is assumed.

--------------------------
Crash Course in clang/LLVM
--------------------------

The first and most important thing to understand about the clang and LLVM is what
these two superb pieces of software are. I think most people make the mistake of
assuming that clang and/or LLVM is primarily a compiler. This is wrong.

LLVM is a compiler **infrastructure**, and clang is a C-language frontend
extending that **infrastructure**. These two codebases are, first and foremost,
a set of libraries with a well defined **application programming interface**.
Yes, clang and LLVM ship with multiple drivers and utilities. However, these are
merely use cases of the API. The clang/LLVM designers seek to create reusable
compiler components, something that (to my knowledge) has never been done on this
scale before.
