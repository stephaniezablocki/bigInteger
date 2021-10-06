#include <iostream>;
#include <iterator>;
#include <regex>;
#include <vector>;
#include <stack>;
#include <locale>;

using namespace std;

union Element
{
    int i;
    char c;
};

void parse();
Element *elements;
Element *postfix;
string exp;

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

    postfix = new Element[exp.length()]; //initially the postfix string is empty
    Element *it_infix = elements;
    Element *it_postfix = postfix;

    for (int j = 0; j < exp.length(); j++)
    {
        if (isdigit((*it_infix).c))
        {
            *it_postfix = *it_infix; //add to postfix when character is letter or number
            it_postfix++;
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
                it_postfix++;
                stk.pop();
            }
            stk.pop(); //remove the '(' from stack
        }
        else
        {
            if (preced((*it_infix).c) > preced((stk.top()).c))
                stk.push(*it_infix); //push if precedence is high
            else
            {
                while ((stk.top()).c != '#' && preced((*it_infix).c) <= preced(stk.top().c))
                {
                    *it_postfix = stk.top(); //store and pop until higher precedence is found
                    it_postfix++;
                    stk.pop();
                }
                stk.push(*it_infix);
            }
        }
        it_infix++;
    }

    while (stk.top().c != '#')
    {
        *it_postfix = stk.top(); //store and pop until stack is not empty.
        it_postfix++;
        stk.pop();
    }
}
void parse() // Place numbers and characters from expression string into array as elements
{
    //Element *elements = new Element[exp.length()];
    Element *iterator = elements;
    for (int j = 0; j < exp.length(); j++)
    {
        Element e;
        if (isdigit(exp[j])) // If the number is multiple digits, add the whole number to the array as a single element
        {
            int n = exp[j];
            while (isdigit(exp[j + 1]))
            {
                j++;
                n = (n * 10) + exp[j];
            }
            //cout << "Number: " << n << "\n";
            e.i = n;
        }
        else // If the character is not a number, add it to the array
        {
            e.c = exp[j];
        }
        *iterator = e;
        //cout << "Value at iterator = " << (*iterator).i;
        iterator++;
    }
}

int main()
{
    cout << "Enter expression: ";
    getline(cin, exp);
    elements = new Element[exp.length()];
    parse();
    inToPost();
    cout << "Char1: " << (*postfix).c << "\n";
    postfix++;
    cout << "Char2: " << (*postfix).c << "\n";
    postfix++;
    cout << "Char3: " << (*postfix).c << "\n";
    postfix++;
    cout << "Char3: " << (*postfix).c << "\n";
    postfix++;
    cout << "Char3: " << (*postfix).c << "\n";

    cout << "\n";
}