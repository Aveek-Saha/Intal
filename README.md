# Integers of Arbitrary Length

Intal is short for **Int**egers of **A**rbitrary **L**ength. 

An intal (an integer of arbitrary length) is an object pointed to by a `void*` pointer. An intal can be created by `intal_create()` by providing a char string of a nonnegative integer provided in decimal digits. Some intals are created out of some functionalities like `intal_add()`, which creates a new intal.

Responsibility of destroying the intals created lies with the client by calling `intal_destroy()`, which will free whatever memory allocated during the creation of intal.

There is no theoretical limit to the size of the integer, except for memory limitations of the process (Operating System).


The operations that can be done on intals are-
* Addition
* Subtraction
* Multiplication(Karatsuba)
* Division
* Exponent
* Comparison
* Increment and decrement by 1


## How to run

1. To run the sanity check
	 ```
	 $ gcc -c intal_sanity_check.c
	 $ gcc -Wall intal.c intal_sanity_check.o -lm -lrt -o intal.out
	 $ ./intal.out
	 ```
2. Run a client file
	 ```
	 $ gcc -c client.c
	 $ gcc -Wall intal.c client.o -lm -lrt -o intal.out
	 $ ./intal.out
	 ```
### Test for memory leaks with valgrind
```
$ valgrind --tool=memcheck ./intal.out
```

For example if you run this after running the sanity check, the output will be something like this
```
==12256== Memcheck, a memory error detector
==12256== Copyright (C) 2002-2017, and GNU GPL'd, by Julian Seward et al.
==12256== Using Valgrind-3.15.0 and LibVEX; rerun with -h for copyright info
==12256== Command: ./intal.out
==12256== 
Sanity check done. If you don't see any "FAILED" messages above, everything works!.
==12256== 
==12256== HEAP SUMMARY:
==12256==     in use at exit: 0 bytes in 0 blocks
==12256==   total heap usage: 122 allocs, 122 frees, 1,855 bytes allocated
==12256== 
==12256== All heap blocks were freed -- no leaks are possible
==12256== 
==12256== For lists of detected and suppressed errors, rerun with: -s
==12256== ERROR SUMMARY: 0 errors from 0 contexts (suppressed: 0 from 0)
	 ```
	 
	 
	 
	 
