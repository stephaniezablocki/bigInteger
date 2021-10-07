Math Expression Evaluator!

This is a C++ program written to evaluate mathematical expressions. The purpose was to practice C++.

The program runs through the following steps for each expression:
1) Reads the string
2) Separates integers and operators into element objects and puts them in an array. Element objects can be either an int or a char.
3) The array of elements are ordered in infix order. The elements are reorganized into an array in postfix order.
4) The program evaluates the postfix array by iterating through the elements once.

Constraints:
- The numbers can only be integers. No decimals.
- The operators supported are +, -, *, /, and ^.
- There is no support for invalid expressions.


Skills I learned:
- Pointers
- Unions
- Stacks in C++
- Return type constraints in C++
- Debugging in VS Code