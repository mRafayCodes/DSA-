#include <iostream>
using namespace std;

class Passengers
{
public:
    string name;
    string dest;
    string type;

    Passengers()
    {
        name = "";
        dest = "";
        type = "";
    }
    Passengers(string n, string d, string t)
    {
        name = n;
        dest = d;
        type = t;
    }
};

const int SIZE = 5;

class TicketingSystem
{
    int front = -1;
    int rear = -1;
    Passengers p[SIZE];

public:
    bool isFull() { return rear == SIZE - 1; }
    bool isEmpty() { return front == -1; }

    void enqueuePassenger(Passengers pass)
    {
        if (isFull())
        {
            cout << "Queue Overflow. Cannot add .\n";
            return;
        }
        if (isEmpty())
        {
            front = 0;
        }
        rear = rear + 1;
        p[rear] = pass;
        cout << pass.name << " added to the queue.\n";
    }

    void dequeuePassenger()
    {
        if (isEmpty())
        {
            cout << "Queue Underflow. No passenger to serve.\n";
            return;
        }
        Passengers temp = p[front];
        cout << "Served: " << temp.name << " | " << temp.dest << " | " << temp.type << endl;
        if (front == rear)
        {
            front = -1;
            rear = -1;
        }
        else
        {
            front++;
        }
    }

    void viewFrontPassenger()
    {
        if (isEmpty())
        {
            cout << "Queue is empty.\n";
            return;
        }
        cout << "Front passenger -> Name: " << p[front].name
             << ", Destination: " << p[front].dest
             << ", Ticket: " << p[front].type << endl;
    }

    void displayQueue()
    {
        if (isEmpty())
        {
            cout << "Queue is empty.\n";
            return;
        }
        cout << "All Passegers:\n";
        for (int i = front; i <= rear; i++)
        {
            cout << "  " << p[i].name << " | " << p[i].dest << " | " << p[i].type << endl;
        }
    }
};

int main()
{
    TicketingSystem q;

    cout << "===== Test 1: empty queue operations =====\n";
    q.dequeuePassenger();
    q.viewFrontPassenger();
    q.displayQueue();

    cout << "\n===== Test 2: enqueue until full, then overflow =====\n";
    q.enqueuePassenger(Passengers("Rafay", "Terminal A", "Regular"));

    q.enqueuePassenger(Passengers("Tabeer", "Terminal B", "VIP"));
    q.enqueuePassenger(Passengers("zafar", "Terminal C", "Regular"));
    q.enqueuePassenger(Passengers("Shanawr", "Terminal A", "VIP"));
    q.enqueuePassenger(Passengers("Awais", "Terminal B", "Regular"));

    q.enqueuePassenger(Passengers("hooren", "Terminal C", "Regular")); // overflow
    q.displayQueue();

    cout << "\n===== Test 3: FIFO =====\n";
    q.viewFrontPassenger();
    q.dequeuePassenger();
    q.dequeuePassenger();

    q.displayQueue();

    cout << "\n===== Test 5: serve everyone, then reset check =====\n";
    q.dequeuePassenger();
    q.dequeuePassenger();
    q.dequeuePassenger();

    q.dequeuePassenger();

    cout << "\n===== Test 6 =====\n";
    q.enqueuePassenger(Passengers("Noor", "Terminal A", "Regular"));

    q.displayQueue();

    return 0;
}
