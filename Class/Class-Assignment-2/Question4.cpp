#include <iostream>
using namespace std;

class Box
{
    int id;
    int weight;

public:
    Box()
    {
        id = 0;
        weight = 0;
    }
    Box(int i, int w)
    {
        id = i;
        weight = w;
    }
    int getId() { return id; }
    int getWeight() { return weight; }
};

const int SIZE = 50;

class BoxStack
{
    int top;
    Box arr[SIZE];

public:
    BoxStack() { top = -1; }

    bool isEmpty() { return top == -1; }
    bool isFull() { return top == SIZE - 1; }

    void push(Box box)
    {
        if (isFull())
        {
            cout << "Overflow: stack is full\n";
            return;
        }
        top++;
        arr[top] = box;
    }

    Box pop()
    {
        if (isEmpty())
        {
            cout << "Underflow: stack is empty\n";
            return Box();
        }
        Box box = arr[top];
        top--;
        return box;
    }

    Box peek()
    {
        if (isEmpty())
        {
            cout << "Stack is empty\n";
            return Box();
        }
        return arr[top];
    }

    void addBox(Box newBox)
    {
        while (!isEmpty() && peek().getWeight() < newBox.getWeight())
        {
            Box removed = pop();
            cout << "  Box " << removed.getId() << " (weight " << removed.getWeight()
                 << ") placed aside\n";
        }
        push(newBox);
        cout << "  Box " << newBox.getId() << " (weight " << newBox.getWeight()
             << ") pushed\n";
    }

    void removeTopBox()
    {
        if (isEmpty())
        {
            cout << "Underflow: no box to remove\n";
            return;
        }
        Box box = pop();
        cout << "Removed box " << box.getId() << " (weight " << box.getWeight() << ")\n";
    }

    void viewTopBox()
    {
        if (isEmpty())
        {
            cout << "Stack is empty\n";
            return;
        }
        cout << "Top box: ID " << arr[top].getId()
             << ", weight " << arr[top].getWeight() << endl;
    }

    void displayStack()
    {
        if (isEmpty())
        {
            cout << "Stack is empty\n";
            return;
        }
        for (int i = top; i >= 0; i--)
            cout << "ID " << arr[i].getId() << ", weight " << arr[i].getWeight() << endl;
    }
};

int main()
{
    cout << "===== Test 1 =====\n";
    BoxStack s1;
    s1.addBox(Box(1, 5));
    s1.addBox(Box(2, 3));
    s1.addBox(Box(3, 8));
    s1.addBox(Box(4, 2));
    s1.addBox(Box(5, 7));
    cout << "Final stack :\n";
    s1.displayStack();
    s1.viewTopBox();

    cout << "\n===== Test 2: empty stack operations =====\n";
    BoxStack s2;
    s2.viewTopBox();
    s2.removeTopBox();
    s2.displayStack();

    cout << "\n===== Test 3: single box =====\n";
    BoxStack s3;
    s3.addBox(Box(10, 4));
    s3.displayStack();
    s3.removeTopBox();
    s3.displayStack();

    cout << "\n===== Test 4: new box heavier than ALL boxes =====\n";
    BoxStack s4;
    s4.addBox(Box(21, 9));
    s4.addBox(Box(22, 6));
    s4.addBox(Box(23, 3));
    s4.addBox(Box(24, 50));
    cout << "Final stack :\n";
    s4.displayStack();

    cout << "\n===== Test 5: equal weights (pushed directly) =====\n";
    BoxStack s5;
    s5.addBox(Box(31, 5));
    s5.addBox(Box(32, 5));
    s5.addBox(Box(33, 5));
    cout << "Final stack (top to bottom):\n";
    s5.displayStack();

    cout << "\n===== Test 6: decreasing weights  =====\n";
    BoxStack s6;
    s6.addBox(Box(41, 9));
    s6.addBox(Box(42, 7));
    s6.addBox(Box(43, 2));
    s6.displayStack();

    return 0;
}