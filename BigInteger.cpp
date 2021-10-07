#include <iostream>
#include <iterator>
#include <regex>
#include <vector>
#include <stack>
#include <locale>
#include <math.h>

using namespace std;

union Element
{
    int i;
    char c;
};

void parse();
Element *elements;
bool *elements_is_int;
Element *postfix;
bool *postfix_is_int;
int num_elements;
string expression;

int preced(char ch)
{
    if (ch == '+' || ch == '-')
    {
        return 1; //Precedence of + or - is 1
    }
    else if (ch == '*' || ch == '/')
    {
        return 2; //Precedence of * or / is 2
    }
    else if (ch == '^')
    {
        return 3; //Precedence of ^ is 3
    }
    else
    {
        return 0;
    }
}

void inToPost()
{
    stack<Element> stk;

    Element *pound = new Element; //add some extra character to avoid underflow
    (*pound).c = '#';
    stk.push(*pound);

    postfix = new Element[expression.length()]; //initially the postfix string is empty
    postfix_is_int = new bool[expression.length()];
    Element *it_infix = elements;
    bool *it_infix_int = elements_is_int;
    Element *it_postfix = postfix;
    bool *it_postfix_int = postfix_is_int;

    for (int j = 0; j < expression.length(); j++)
    {
        if (*it_infix_int == true)
        {
            *it_postfix = *it_infix; //add to postfix when character is letter or number
            *it_postfix_int = *it_infix_int;
            it_postfix++;
            it_postfix_int++;
        }
        else if ((*it_infix).c == '(')
        {
            Element *symbol = new Element;
            (*symbol).c = '(';
            stk.push(*symbol);
        }
        else if ((*it_infix).c == '^')
        {
            Element *symbol = new Element;
            (*symbol).c = '^';
            stk.push(*symbol);
        }
        else if ((*it_infix).c == ')')
        {
            while ((stk.top()).c != '#' && (stk.top()).c != '(')
            {
                *it_postfix = stk.top(); //store and pop until ( has found
                *it_postfix_int = false;
                it_postfix++;
                it_postfix_int++;
                stk.pop();
            }
            stk.pop(); //remove the '(' from stack
        }
        else if ((*it_infix).c != '\0')
        {
            if (preced((*it_infix).c) > preced((stk.top()).c))
                stk.push(*it_infix); //push if precedence is high
            else
            {
                while ((stk.top()).c != '#' && preced((*it_infix).c) <= preced(stk.top().c))
                {
                    *it_postfix = stk.top(); //store and pop until higher precedence is found
                    it_postfix++;
                    *it_postfix_int = false;
                    it_postfix_int++;
                    stk.pop();
                }
                stk.push(*it_infix);
            }
        }
        it_infix++;
        it_infix_int++;
    }

    while (stk.top().c != '#')
    {
        *it_postfix = stk.top(); //store and pop until stack is not empty.
        it_postfix++;
        stk.pop();
    }
}

int charToInt(char c)
{
    return (c - 48);
}

void parse() // Place numbers and characters from expressionression string into array as elements
{
    //Element *elements = new Element[expression.length()];
    Element *iterator = elements;
    bool *type_iterator = elements_is_int;
    for (int j = 0; j < expression.length(); j++)
    {
        Element e;
        bool is_int;
        if (isdigit(expression[j])) // If the number is multiple digits, add the whole number to the array as a single element
        {
            int n = charToInt(expression[j]);
            while (isdigit(expression[j + 1]))
            {
                j++;
                n = (n * 10) + charToInt(expression[j]);
                num_elements--;
            }
            e.i = n;
            is_int = true;
        }
        else // If the character is not a number, add it to the array
        {
            e.c = expression[j];
            is_int = false;
        }
        *iterator = e;
        *type_iterator = is_int;
        iterator++;
        type_iterator++;
    }
}

int apply_operator(int x, int y, char op)
{
    switch (op)
    {
    case '+':
        return x + y;
        break;
    case '-':
        return x - y;
        break;
    case '*':
        return x * y;
        break;
    case '/':
        return x / y;
        break;
    case '^':
        return pow(x, y);
        break;
    default:
        return 0;
    }
}

int eval_postfix()
{
    stack<int> stk;

    Element *it_postfix = postfix;
    bool *it_postfix_int = postfix_is_int;

    for (int j = 0; j < num_elements; j++)
    {
        if (*it_postfix_int == true)
        {
            stk.push((*it_postfix).i);
        }
        else
        {
            int second_term = stk.top();
            stk.pop();
            int first_term = stk.top();
            stk.pop();
            char op = (*it_postfix).c;
            int result = apply_operator(first_term, second_term, op);
            stk.push(result);
        }
        it_postfix++;
        it_postfix_int++;
    }
    return stk.top();
}

void run()
{
    cout << "Enter expression: ";
    getline(cin, expression);
    elements = new Element[expression.length()];
    elements_is_int = new bool[expression.length()];
    num_elements = expression.length();
    parse();
    inToPost();
    int result = eval_postfix();
    cout << "FINAL RESULT = " << result;

    cout << "\nRun again? (Y/N): ";
    string repeat;
    getline(cin, repeat);
    if (tolower(repeat[0]) == 'y')
        run();
}

int main()
{
    run();
}