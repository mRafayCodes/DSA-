#include <iostream>
using namespace std;
class Passenger
{
public:
    string passengerName;
    string category;
    int seatNumber;

    Passenger()
    {
        passengerName = "";
        category = "";
        seatNumber = 0;
    }

    Passenger(string p, string c, int s)
    {
        passengerName = p;
        category = c;
        seatNumber = s;
    }
};
const int SIZE = 5;
class Reservation
{
    Passenger p[SIZE];
    int front = -1;
    int rear = -1;

public:
    bool isEmpty()
    {
        return front == -1;
    }
    bool isFull()
    {
        return front == (rear + 1) % SIZE;
    }
    void bookAtFront(string name, int seat)
    {
        if (isFull())
        {
            cout << "The deque is full. Cannot book " << name << ".\n";
            return;
        }
        if (isEmpty())
        {
            front = 0;
            rear = 0;
        }
        else
        {
            front = (front - 1 + SIZE) % SIZE; // FIX: + SIZE
        }
        p[front] = Passenger(name, "VIP", seat);
        cout << "Booked at front: " << name << " (VIP, seat " << seat << ").\n";
    }
    void bookAtRear(string name, int seat)
    {
        if (isFull())
        {
            cout << "The deque is full. Cannot book " << name << ".\n";
            return;
        }
        if (isEmpty())
        {
            front = 0;
            rear = 0;
        }
        else
        {
            rear = (rear + 1) % SIZE;
        }
        p[rear] = Passenger(name, "Regular", seat);
        cout << "Booked at rear: " << name << " (Regular, seat " << seat << ").\n";
    }
    void cancelFromFront()
    {
        if (isEmpty())
        {
            cout << "The deque is empty. No reservation to cancel.\n";
            return;
        }
        Passenger temp = p[front];
        if (front == rear)
        {
            front = -1;
            rear = -1;
        }
        else
        {
            front = (front + 1) % SIZE;
        }
        cout << "Cancelled from front: " << temp.passengerName
             << " (" << temp.category << ", seat " << temp.seatNumber << ")\n";
    }
    void cancelFromRear()
    {
        if (isEmpty())
        {
            cout << "The deque is empty. No reservation to cancel.\n";
            return;
        }
        Passenger temp = p[rear];
        if (front == rear)
        {
            front = -1;
            rear = -1;
        }
        else
        {
            rear = (rear - 1 + SIZE) % SIZE;
        }
        cout << "Cancelled from rear: " << temp.passengerName
             << " (" << temp.category << ", seat " << temp.seatNumber << ")\n";
    }
    void viewFrontReservation()
    {
        if (isEmpty())
        {
            cout << "The deque is empty. No reservation to view.\n";
            return;
        }
        cout << "Front Reservation -> Passenger: " << p[front].passengerName
             << " | Category: " << p[front].category
             << " | Seat Number: " << p[front].seatNumber << endl;
    }
    void viewRearReservation()
    {
        if (isEmpty())
        {
            cout << "The deque is empty. No reservation to view.\n";
            return;
        }
        cout << "Rear Reservation -> Passenger: " << p[rear].passengerName
             << " | Category: " << p[rear].category
             << " | Seat Number: " << p[rear].seatNumber << endl;
    }
    void displayAllReservations()
    {
        if (isEmpty())
        {
            cout << "No reservations.\n";
            return;
        }
        cout << "Reservations (front to rear):\n";
        int i = front;
        while (true)
        {
            cout << "  " << p[i].passengerName << " | " << p[i].category
                 << " | Seat " << p[i].seatNumber << endl;
            if (i == rear)
                break;
            i = (i + 1) % SIZE;
        }
    }
};

int main()
{
    Reservation r;

    cout << "===== Test 1: empty deque =====\n";
    r.cancelFromFront();
    r.cancelFromRear();
    r.viewFrontReservation();
    r.viewRearReservation();
    r.displayAllReservations();

    cout << "\n===== Test 2: first booking, regular  =====\n";
    r.bookAtRear("Rafay", 11);
    r.bookAtRear("Tabeer", 12);

    cout << "\n===== Test 3: VIP at front =====\n";
    r.bookAtFront("Tabeer", 1);
    r.displayAllReservations();

    cout << "\n===== Test 4: overflow =====\n";
    r.bookAtRear("Shanwar", 13);
    r.bookAtFront("Awais", 2);
    r.displayAllReservations();
    r.bookAtRear("Hammad", 14);
    r.bookAtFront("Asad", 3);

    cout << "\n===== Test 5: view both ends =====\n";
    r.viewFrontReservation();
    r.viewRearReservation();

    cout << "\n===== Test 6: cancel from both ends =====\n";
    r.cancelFromRear();
    r.cancelFromFront();
    r.displayAllReservations();

    cout << "\n===== Test 7: reuse (wrap-around at rear) =====\n";
    r.bookAtRear("Hina", 14);
    r.bookAtRear("Danish", 15);
    r.displayAllReservations();

    cout << "\n===== Test 8: cancel until single element, then empty =====\n";
    r.cancelFromFront();
    r.cancelFromFront();
    r.cancelFromRear();
    r.displayAllReservations();
    r.cancelFromRear();
    r.cancelFromFront();
    r.cancelFromFront();

    return 0;
}