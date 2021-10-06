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

string inToPost(string infix)
{
    stack<char> stk;
    stk.push('#');       //add some extra character to avoid underflow
    string postfix = ""; //initially the postfix string is empty
    string::iterator it;

    for (it = infix.begin(); it != infix.end(); it++)
    {
        if (isalnum(char(*it)))
            postfix += *it; //add to postfix when character is letter or number
        else if (*it == '(')
            stk.push('(');
        else if (*it == '^')
            stk.push('^');
        else if (*it == ')')
        {
            while (stk.top() != '#' && stk.top() != '(')
            {
                postfix += stk.top(); //store and pop until ( has found
                stk.pop();
            }
            stk.pop(); //remove the '(' from stack
        }
        else
        {
            if (preced(*it) > preced(stk.top()))
                stk.push(*it); //push if precedence is high
            else
            {
                while (stk.top() != '#' && preced(*it) <= preced(stk.top()))
                {
                    postfix += stk.top(); //store and pop until higher precedence is found
                    stk.pop();
                }
                stk.push(*it);
            }
        }
    }

    while (stk.top() != '#')
    {
        postfix += stk.top(); //store and pop until stack is not empty.
        stk.pop();
    }

    return postfix;
}

int main()
{
    cout << "Enter expression: ";
    getline(cin, exp);
    elements = new Element[exp.length()];
    parse();
    cout << (*elements).i - 48 << "\n";
    elements++;
    cout << (*elements).c << "\n";
    elements++;
    cout << (*elements).i - 48 << "\n";

    cout << "\n";
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
/*int eval(Element *elements)
{
    Element *start_of_array = elements;
    while (*elements != NULL)
    {
    }
}*/