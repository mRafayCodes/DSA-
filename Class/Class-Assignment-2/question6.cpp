#include <iostream>
using namespace std;
struct Node
{
    string pname;
    int id;
    string dname;
    string time;
    Node *next;

    Node(string p, int i, string d, string t)
    {
        pname = p;
        id = i;
        dname = d;
        time = t;
        next = nullptr;
    }
};
class Hospital
{
    Node *front = nullptr;
    Node *rear = nullptr;

public:
    ~Hospital()
    {
        while (front != nullptr)
        {
            Node *temp = front;
            front = front->next;
            delete temp;
        }
        rear = nullptr;
    }

    bool isEmpty()
    {
        return front == nullptr;
    }
    void addPatient(string pname, int id, string dname, string time)

    {
        Node *newnode = new Node(pname, id, dname, time);
        if (isEmpty())
        {
            front = newnode;
            rear = newnode;
        }
        else
        {
            rear->next = newnode;
            rear = newnode;
        }
    }
    void callNextPatient()
    {
        if (isEmpty())
        {
            cout << "The Queue is empty.\n";
            return;
        }
        Node *temp = front;
        cout << "Calling: " << temp->pname << " (ID " << temp->id
             << ") for Dr. " << temp->dname << " at " << temp->time << endl;
        if (front == rear)
        {

            front = rear = nullptr;
        }
        else
        {
            front = front->next;
        }
        delete temp;
    }
    void viewNextPatient()
    {
        if (isEmpty())
        {
            cout << "Queue is empty. No next patient.\n";
            return;
        }
        Node *temp = front;
        cout << "The next patient is: " << temp->pname << " (ID " << temp->id
             << ") for Dr. " << temp->dname << " at " << temp->time << endl;
    }
    void displayAllPatients()
    {
        if (isEmpty())
        {
            cout << "Queue is empty. No  patient.\n";
            return;
        }
        Node *temp = front;
        cout << "Waiting patients (front to rear):\n";
        while (temp != nullptr)
        {
            cout << "  " << temp->pname << " (ID " << temp->id
                 << ") for Dr. " << temp->dname << " at " << temp->time << endl;
            temp = temp->next;
        }
    }
};

int main()
{
    Hospital h;

    cout << "===== Test 1: empty queue =====\n";
    h.callNextPatient();
    h.viewNextPatient();
    h.displayAllPatients();

    cout << "\n===== Test 2: add patients =====\n";
    h.addPatient("Rafay", 1, "Khan", "09:00");
    h.addPatient("Tabeer", 2, "khan", "09:15");
    h.addPatient("Zafar", 3, "Khan", "09:30");
    h.displayAllPatients();
    h.viewNextPatient();

    cout << "\n===== Test 3: call  =====\n";
    h.callNextPatient();
    h.callNextPatient();
    h.displayAllPatients();

    cout << "\n===== Test 4: last patient removed =====\n";
    h.callNextPatient();
    h.displayAllPatients();
    h.callNextPatient();

    cout << "\n===== Test 6: single patient display =====\n";
    h.callNextPatient();
    h.addPatient("Omar", 5, "Khan", "10:15");
    h.addPatient("Sana", 6, "Ali", "10:30");
    h.displayAllPatients();

    return 0;
}