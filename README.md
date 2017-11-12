# Exam C-Programming

This is a simple implementation of a [B-Tree](https://en.wikipedia.org/wiki/B-tree "Wikipedia")

Although `main.c` in is not directly specific to the `test_text.txt` text file it does run the `tests()` from `tests.c` which is. The intent is that the user test's the program by compiling it (`make` in the terminal), and then runs it as is with the included `test_text.txt`.
Then if there is no error's the user can then replace the call to `tests()`(and whatever else they like) with their own code.

### TODO

 - GetText() - Will most likely use the Enumerate() to find the desired node
