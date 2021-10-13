Math Expression Evaluator!

This is a C++ program written to evaluate mathematical expressions. The purpose was to practice C++.

The program runs through the following steps for each expression:
1) Reads the string
2) Separates integers and operators into element objects and puts them in an array. Element objects can be either an int or a char.
3) The array of elements are ordered in infix order. The elements are reorganized into an array in postfix order.
4) The program evaluates the postfix array by iterating through the elements once.

Constraints:
- The numbers can only be integers. No decimals.
- The output will only be accurate if it is <= 2147483647.
- Negative numbers are not supported (subtraction is).
- The operators supported are +, -, *, /, and ^.
- There is no support for invalid expressions.

If I redid the program I would make the functions self-contained instead of using global variables, because I wasn't able to write modular test cases this way. Also, I would nix the parse() and inToPost() functions in favor of just passing the input string to the postfix evaluator. The reason I had wanted to separate numbers and operations into elements was to keep multi-digit numbers in tact. However, I believe that it would be easier to have a short helper function to check the next characters in the string for multiple digits. This would make checking the type of character (number or operator) easier because there is no distinction in the union. This would also be more readable and more efficient since ints and strings are both 4 bytes, so not having the extra bool array would save space.
