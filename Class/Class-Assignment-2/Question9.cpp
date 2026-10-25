#include <iostream>
using namespace std;
struct Patient
{
    int id;
    string name;
    string condition;
    int priority;
    Patient *next;

    Patient(int i, string n, string c, int p)
    {
        id = i;
        name = n;
        condition = c;
        priority = p;
        next = nullptr;
    }
};
class Emergency
{
    Patient *front = nullptr;

public:
    ~Emergency()
    {
        while (front != nullptr)
        {
            Patient *temp = front;
            front = front->next;
            delete temp;
        }
    }

    bool isEmpty()
    {
        return front == nullptr;
    }

    void addPatient(int i, string n, string c, int p)
    {
        if (p < 1 || p > 4)
        {
            cout << "Invalid priority " << p << " for " << n << ". Must be 1 to 4.\n";
            return;
        }
        Patient *newPatient = new Patient(i, n, c, p);

        if (isEmpty() || p < front->priority)
        {
            newPatient->next = front;
            front = newPatient;
            cout << n << " (priority " << p << ") added.\n";
            return;
        }

        Patient *temp = front;
        while (temp->next != nullptr && temp->next->priority <= p)
        {
            temp = temp->next;
        }
        newPatient->next = temp->next;
        temp->next = newPatient;
        cout << n << " (priority " << p << ") added.\n";
    }

    void treatNextPatient()
    {
        if (isEmpty())
        {
            cout << "The queue is empty. No patient to treat.\n";
            return;
        }
        Patient *temp = front;
        front = front->next;
        cout << "Treating: " << temp->name << " (ID " << temp->id
             << ", priority " << temp->priority << ", " << temp->condition << ")\n";
        delete temp;
    }

    void viewNextPatient()
    {
        if (isEmpty())
        {
            cout << "The queue is empty. No patient waiting.\n";
            return;
        }
        cout << "Next patient: " << front->name << " (ID " << front->id
             << ", priority " << front->priority << ", " << front->condition << ")\n";
    }

    void displayAllPatients()
    {
        if (isEmpty())
        {
            cout << "No patients waiting.\n";
            return;
        }
        cout << "Waiting patients (treatment order):\n";
        Patient *temp = front;
        while (temp != nullptr)
        {
            cout << "  P" << temp->priority << " | " << temp->name << " | ID " << temp->id
                 << " | " << temp->condition << endl;
            temp = temp->next;
        }
    }
};

int main()
{
    cout << "===== Test 1: empty queue =====\n";
    Emergency e1;
    e1.treatNextPatient();
    e1.viewNextPatient();
    e1.displayAllPatients();

    cout << "\n===== Test 2: given example =====\n";
    Emergency e2;
    e2.addPatient(1, "Rafay", "Mental stress", 4);
    e2.displayAllPatients();
    e2.addPatient(2, "Ahmad", "Heart attack", 1);
    e2.displayAllPatients();
    e2.addPatient(3, "Tabeer", "Fever", 3);
    e2.displayAllPatients();
    e2.addPatient(4, "Berrii", "pain ", 2);
    e2.displayAllPatients();
    e2.viewNextPatient();

    cout << "\n===== Test 3: treat in priority order =====\n";
    e2.treatNextPatient();
    e2.treatNextPatient();
    e2.displayAllPatients();

    cout << "\n===== Test 4: same priority keeps arrival order =====\n";
    Emergency e3;
    e3.addPatient(10, "Rafay", "Chest pain", 2);
    e3.addPatient(11, "Hammad", "Breathing issue", 1);
    e3.addPatient(12, "Asad", "Burn", 2);
    e3.addPatient(13, "Tabeer", " bleeding", 1);
    e3.addPatient(14, "Shahab", "Sprain", 2);
    e3.displayAllPatients();

    cout << "\n===== Test 5: all patients equal priority  =====\n";
    Emergency e4;
    e4.addPatient(20, "A", "x", 3);
    e4.addPatient(21, "B", "y", 3);
    e4.addPatient(22, "C", "z", 3);
    e4.displayAllPatients();

    cout << "\n===== Test 6: invalid priority =====\n";
    e4.addPatient(23, "D", "w", 0);
    e4.addPatient(24, "E", "v", 5);
    e4.displayAllPatients();

    cout << "\n===== Test 7: treat everyone =====\n";
    e4.treatNextPatient();
    e4.treatNextPatient();
    e4.treatNextPatient();
    e4.treatNextPatient();
    e4.displayAllPatients();

    return 0;
}