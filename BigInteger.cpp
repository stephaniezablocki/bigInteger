#include <iostream>;
#include <iterator>;
#include <regex>;
#include <vector>;

using namespace std;

union Element
{
    int i;
    double d;
    char c;
};

Element *parse();
string exp;

int main()
{
    cout << "Enter expression: ";
    getline(cin, exp);
    //cout << exp + "\n";
    cout << "Length of string: " << exp.length() << "\n";
    cout << (*parse()).c;
    cout << "\n";
}
Element *parse()
{
    Element *elements = new Element[exp.length()];
    for (int j = 0; j < exp.length(); j++)
    {
        Element e;
        if (isdigit(exp[j]))
        {
            int n;
            while (isdigit(exp[j]))
            {
                n = (n * 10) + exp[j];
                j++;
                cout << "num\n";
            }
            e.i = n;
        }
        else
        {
            e.c = exp[j];
            cout << "char\n";
        }
    }
    return elements;
}