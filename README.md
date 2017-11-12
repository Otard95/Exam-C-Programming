# Exam C-Programming

This is a simple implementation of a [B-Tree](https://en.wikipedia.org/wiki/B-tree "Wikipedia")

Although `main.c` is not directly specific to the `test_text.txt` text file, it does run the `tests()` from `tests.c` which is. The intent is that the user test's the program by compiling it (`make` in the terminal), and then runs it as is with the included `test_text.txt`.  
Then if there is no error's the user can then replace the call to `tests()`(and whatever else they like) with their own code.

### Make and Run

Assuming you already have the zip downloaded and extracted the containing folder. Open the terminal and navigate to the folder folder you extracted. And run:
```
$ make
Making main ...
Done!
$ ./main test_text.txt
```

Read through the output and make sure it ran as expected.  
You can also use the `help` target like so `$ make help` to see the all your options.

### TODO

 - Fix sorted insert
 - Binary search when searching tree

### Test's

Solution tested 'in - on':
 - Project folder - Origin Computer (Full Install Ubuntu).
 - Random directory - Origin Computer (Full Install Ubuntu).
 - Random directory - Origin Computer (VM Ubuntu).
 - Random directory - Another Computer (VM Ubuntu).
