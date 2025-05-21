# Codebase Overview
This file contains the documentation of my entire repository. Individual header files contain varying levels of documentation, but this file is where I will just write whatever I feel like explaining. Hopefully, it's too much detail rather than not enough. This file is not a getting started or how to use tutorial, it's an I want to fork this repo or copy a function how do I do it file.
## Top Level Folders
### /nodejs/
This folder is designed to wrap the library into a nodejs library.
### /src/
This folder is where my actual code that does useful things lives.

## Matrix
This directory is for linear algebra and working with matrices. Most of the code lives in /structures/array.(hpp/tpp). array.hpp is probably the most heavily documented file in the library at the time I'm writing this so, I will just go through the basics of the functions.
arr[i]: gives you the ith element or row of arr. If row, returns a n-1D array object, with the same memory.
arr.copy(): gives you a copy of the array, with it's data in a different block of memory
arr.zeros(): gives you a zeroed out array of the same shape
