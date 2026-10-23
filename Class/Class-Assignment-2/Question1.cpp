#include <iostream>
using namespace std;

const int SIZE = 5;

class request
{
public:
    int id;
    string name;
    string reason;
    string date;

    request()
    {
        id = -1;
        name = reason = date = "";
    }
    request(int i, string n, string r, string d)
    {
        id = i;
        name = n;
        reason = r;
        date = d;
    }
};

class Stack
{
    int top = -1;
    request r[SIZE];

public:
    bool isFull() { return top == SIZE - 1; }
    bool isEmpty() { return top == -1; }

    void PushReturnRequest(request r1)
    {
        if (isFull())
        {
            cout << "\nOverflow: stack is full. Request " << r1.id << " not added.\n";
            return;
        }
        top++;
        r[top] = r1;
        cout << "\nRequest " << r1.id << " added.\n";
    }

    void popReturnRequest()
    {
        if (isEmpty())
        {
            cout << "\nUnderflow: Stack is empty.\n";
            return;
        }
        request temp = r[top];
        cout << "\nRequest id " << temp.id << " is removed successfully\n";
        top--;
    }

    void peekLatestRequest()
    {
        if (isEmpty())
        {
            cout << "\nNo requests to view. Stack is empty.\n";
            return;
        }
        cout << "\nThe most recent request is:\n";
        cout << "ID: " << r[top].id << ", Name: " << r[top].name
             << ", Reason: " << r[top].reason << ", Date: " << r[top].date << endl;
    }

    void displayAllRequests()
    {
        if (isEmpty())
        {
            cout << "\nNo requests to display. Stack is empty.\n";
            return;
        }
        cout << "\nAll requests :\n";
        for (int i = top; i >= 0; i--) // top se 0 tak ulta
        {
            cout << "ID: " << r[i].id << ", Name: " << r[i].name
                 << ", Reason: " << r[i].reason << ", Date: " << r[i].date << endl;
        }
    }
};

int main()
{
    Stack s;

    cout << "===  operations on empty stack ===";
    s.popReturnRequest();
    s.peekLatestRequest();
    s.displayAllRequests();

    cout << "\n--- Push 5 requests  ---";
    s.PushReturnRequest(request(101, "Rafay", "Damaged item", "20-10-2026"));
    s.PushReturnRequest(request(102, "Tabeer", "Wrong size", "21-10-2026"));
    s.PushReturnRequest(request(103, "Usama", "late delivery", "21-10-2026"));
    s.PushReturnRequest(request(104, "Hina", "Defective", "22-10-2026"));
    s.PushReturnRequest(request(105, "Bilal", "damaged", "23-10-2026"));

    cout << "\n==== push on full stack (overflow) ====";
    s.PushReturnRequest(request(106, "Zara", "Changed mind", "23-10-2026"));

    s.displayAllRequests();
    s.peekLatestRequest();

    cout << "\n--- Pop two ---";
    s.popReturnRequest();
    s.popReturnRequest();
    s.displayAllRequests();
    s.peekLatestRequest();

    cout << "\n=== Push again ===";
    s.PushReturnRequest(request(107, "Noor", "Wrong colour", "23-10-2026"));
    s.displayAllRequests();

    return 0;
}