# Activity 16 and 1/2: Arrays in Assembly
## Put your name(s) here

In this activity, you will explore how array access and pointer arithmetic work, and
how they are translated into assembly isntructions You will:
- Create a function that uses pointer arithmetic to sum up an array
- Examine how C code that stores boolean values is implemented in assembly
- Examine the effect of compiler optimizations in eliminating jumps by handling conditionals differently

## Provided Code

This activity has two main code files, one for a one-dimensional array and one
for a two-D array. It also has a Makefile that can make both as well as generating
assembly as before:
- `Makefile`
    - a makefile to automate the compilation process
- `array_indexing.c`
    - a C code file to demonstrate operations on an array with pointers and with brackets
- `2D_array.c`
    - a C code file to demonstrate operations on a 2D array


## Tasks


### Task 1: use pointer arithmetic to sum elements

The `array_indexing.c` file contains a `main` function that declares an array of 
ints called `A` of length `N`, where we use a `#define` statement to initially 
set `N` to 10 (look up C `#define` directive to learn how it works if this is still unfamiliar).

The `main` contains a number of `assert` statements: they won't pass until you complete
the tasks below. But you should compile and run the program as usual while implementing
and debugging the functions in the file.

Here is our first task for this code:

- Complete the definition of the function `sum_p` that:
    - Takes a pointer to an `int` called `arr_ptr`. This is assumed to be the 
    initial, or zeroth element in the array.
    - Uses a for loop that increases a pointer to access every element and add 
    its value to a variable called `sum`.
    - Returns the value of `sum`.
    - The general structure of the pointer arithmetic is in place: read the existing code
    and make sense of it
    - Revisit Chapter 2 in _Dive into Systems_ if you need a refresher about pointer
    arithmetic
    - Note when the code adds one to `next`, because `next` is a pointer to an `int`,  
    it will increase the actual memory address by 4 bytes (the size of an `int`) automatically
- Generate assembly code for this file, using the `-S` method that produces `array_indexing.s`
    - Before doing this, comment out all the `printf` lines in the `sum_p` function!
- Examine the assembly code comparing it to the code below
    - Copy the assembly code for `sum_p` into a separate file, and copy the
    comments shown below
    - Add comments to the file for the lines below that don't have them (and make changes if your assembly differs!)

```
sum_p:
.LFB8:
        .cfi_startproc
        movl    $0, %edx   # index i is in edx; init to 0
        movl    $0, %eax   # sum is in eax; init to 0
.L7:
        cmpl    $9, %edx      # for loop comparison of %edx to 9
        jg      .L9           #  when edx is > 9, then jump past label .L9 
		                      #  causes return from function
        addl    (%rdi), %eax
        addq    $4, %rdi
        addl    $1, %edx
        jmp     .L7           # jump back to top of loop
.L9:
        ret
        .cfi_endproc
```

### Task 2: Sum elements using array indexing

In the same file, complete the definition of a function, `sum_index`, that also
adds up the values in an array. This time, use the more "typical" approach of
a for loop that iterates over the indices of the array, and uses the square-bracket
notation to access elements of the loop (for instance, `A[i]`). Your function
should accumulate the sum of the values in the array in a variable `sum` and return
`sum` at the end (much like `sum_p`).

The `main` function calls the `sum_p` function and the `sum_index` function on an initialized array called `A`. Compile and run the program to make sure that
your functions work.

Copy the final assembly for `sum_index` into the same text file as you did for `sum_p` and add line-by-line comments to show what it is doing.


#### Examine the differences in the assembly

Finally, let's look at how the assembly varies if we change the optimization level.

- Add `array_indexing_opt01.s` to the `files` target in the Makefile
- Observe the differences and similarities between the assembly code created for your `sum_p` and `sum_index` functions at both optimization levels
    - Make sure you understand how this code matches your intended result in both cases 
    - You might add the optimized versions of each function to the text file from
    before and add comments there


### Task 3: 2D array storage

The second code file examines how to work with a 2D array, one represented as a
contiguous block of memory (like a statically-declared 2D array).

- In the Makefile, uncomment the references to `2D_array.c` so that it will compile that code file
- Study the file `2D_array.c` and make sure that it makes sense
    - Note the `typedef` command near the top of the file: this defines `Marray_t` to 
    be a new type, which is a 2d array of ints, with `M` rows and `N` columns
    - The `set_diag` function sets the values down the diagonal of the input array `A` to 2 (cells where the row index equals the column index: `A[0][0]`, `A[1][1]`, etc.)
    - Make sure you are very clear what the values `M` and `N` represent: add a comment
    to both `set_diag` and `set_diag_p` to state what they are

- Update the function called `set_diag_p`. This function should perform the same
task as `set_diag`, but should use pointer arithmetic to create a pointer into each
relevant cell of the array. This is analogous to the earlier tasks, where we saw how
to sum an array with pointer arithmetic and just direct access.

Notice that this line is to show you how the very last element of the array can be accessed using pointer arithmetic:

		int * last = Arow + (M-1)*N + (N-1);   // final element in 2D array

- Discuss this line with your teammates/neighbors. Does the calculation make sense to do? Add a comment to the code file with your explanation.


#### Why work out the pointer arithmetic method?

Our goal is for you to understand how the computer translates the high-level array access notation, `A[i][j]` into working assembly code.

Understanding the C pointer arithmetic is a big step in that direction.

The next step will be to look at the actual assembly, which of necessity works more
like the pointer arithmetic method!

**Note:** C stores arrays as contiguous blocks of memory in "row-major" form (each row of data
is contiguous). But other programming languages represent arrays in different ways, some
represent them as linked structures, some as in "column-major" form.

#### Study the assembly

- After you have `set_diag_p` working, generate and examie the assembly for both functions, `set_diag` and `set_diag_p`

- Discuss the resulting assembly with your neighbors and teammates. Make a copy of the
assembly for both functions, and comment it.

**Note:** There is more than one way to complete `set_diag_p`, which might change the assembly 
that is produced. 

## References

- x86-64 jump instruction reference
    - [Steve Friedl's Intel x86 JUMP quick reference](http://unixwiz.net/techtips/x86-jumps.html)
- Assembly language resources (x86, 64-bit)
    - [x86 Assembly/X86 Instructions](http://en.wikibooks.org/wiki/X86_Assembly/X86_Instructions)
    - [X86 Opcode and Instruction Reference](http://ref.x86asm.net/coder64.html)
    - [x86 assembly language](http://en.wikipedia.org/wiki/X86_assembly_language)
    - [x86 instruction listings](http://en.wikipedia.org/wiki/X86_instruction_listings)
- gcc compiler flag references
    - [Compiler Option Summary](https://gcc.gnu.org/onlinedocs/gcc/Option-Summary.html)
    - [Index of gcc compiler options](https://gcc.gnu.org/onlinedocs/gcc/Option-Index.html)
- `objdump` resources
    - [Overview of the `objdump` command](https://www.thegeekstuff.com/2012/09/objdump-examples/)
- Makefile guides
  - [An Introduction to Makefiles](https://www.gnu.org/software/make/manual/html_node/Introduction.html), by GNU
  - [Makefile Tutorials and Examples to Build From](https://earthly.dev/blog/make-tutorial/), by Aniket Bhattacharyea
  - [makefile basics - anthony explains](https://www.youtube.com/watch?v=20GC9mYoFGs)

