#include <iostream>
#include <sstream>
using namespace std;

const int SIZE = 100;

class IntStack
{
    int top;
    int arr[SIZE];

public:
    IntStack() { top = -1; }

    bool isFull() { return top == SIZE - 1; }
    bool isEmpty() { return top == -1; }

    void push(int value)
    {
        if (isFull())
        {
            cout << "Overflow\n";
            return;
        }
        top++;
        arr[top] = value;
    }

    int pop()
    {
        if (isEmpty())
        {
            cout << "Underflow\n";
            return 0;
        }
        int value = arr[top];
        top--;
        return value;
    }

    int size() { return top + 1; }
};

void evaluatePostfix(string expression)
{
    IntStack s;
    stringstream ss(expression);
    string token;

    while (ss >> token)
    {
        if (token == "+" || token == "-" || token == "*" || token == "/")
        {
            if (s.size() < 2)
            {
                cout << "Error: insufficient operands for '" << token << "'\n";
                return;
            }
            int b = s.pop();
            int a = s.pop();
            int result = 0;

            switch (token[0])
            {
            case '+':
                result = a + b;
                break;
            case '-':
                result = a - b;
                break;
            case '*':
                result = a * b;
                break;
            case '/':
                if (b == 0)
                {
                    cout << "Error: division by zero\n";
                    return;
                }
                result = a / b;
                break;
            }
            s.push(result);
        }
        else
        {
            s.push(stoi(token));
        }
    }

    if (s.size() == 1)
        cout << "Result: " << s.pop() << endl;
    else
        cout << "Error: invalid expression\n";
}

int main()
{
    cout << "Expression: 23 4 - 5 6 7 * + *\n";
    evaluatePostfix("23 4 - 5 6 7 * + *");

    cout << "\nExpression: 6 5 2 3 + 8 * + 3 + *\n";
    evaluatePostfix("6 5 2 3 + 8 * + 3 + *");

    cout << "\nExpression: 10 2 /\n";
    evaluatePostfix("10 2 /");

    cout << "\n--- Invalid cases ---\n";
    cout << "Expression: 5 +\n";
    evaluatePostfix("5 +");

    cout << "\nExpression: 8 0 /\n";
    evaluatePostfix("8 0 /");

    cout << "\nExpression: 5 3 (extra operand)\n";
    evaluatePostfix("5 3");

    cout << "\nExpression: (empty)\n";
    evaluatePostfix("");

    return 0;
}