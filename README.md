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
	 ```shell
	 gcc -c intal_sanity_check.c
	 gcc -Wall intal.c intal_sanity_check.o -lm -lrt -o intal.out
	 ```
2. Run a client file
	 ```shell
	 gcc -c client.c
	 gcc -Wall intal.c client.o -lm -lrt -o intal.out
	 ```
