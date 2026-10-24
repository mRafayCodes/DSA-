#include <iostream>
using namespace std;
class Car
{
public:
    int carNumber;
    string arrivalTime;
    int slotNumber;

    Car()
    {
        carNumber = 0;
        arrivalTime = "";
        slotNumber = 0;
    }

    Car(int c, string a, int s)
    {
        carNumber = c;
        arrivalTime = a;
        slotNumber = s;
    }
};
const int SIZE = 5;
class Parking
{
    Car c[SIZE];
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
    void parkCar(int carNumber, string arrivalTime)
    {
        if (isFull())
        {
            cout << "The parking lot is full. Car " << carNumber << " cannot park.\n";
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
        c[rear] = Car(carNumber, arrivalTime, rear + 1);
        cout << "Car " << carNumber << " parked in slot " << rear + 1 << ".\n";
    }
    void removeCar()
    {
        if (isEmpty())
        {
            cout << "The parking lot is empty. No car to remove.\n";
            return;
        }
        Car temp = c[front];
        if (front == rear)
        {
            front = -1;
            rear = -1;
        }
        else
        {
            front = (front + 1) % SIZE;
        }
        cout << "Car " << temp.carNumber << " left slot " << temp.slotNumber << ".\n";
    }
    void viewNextCar()
    {
        if (isEmpty())
        {
            cout << "The parking lot is empty. No car to view.\n";
            return;
        }
        cout << "Next car -> Slot " << c[front].slotNumber
             << " | Car " << c[front].carNumber
             << " | Arrival " << c[front].arrivalTime << endl;
    }
    void displayParkingStatus()
    {
        if (isEmpty())
        {
            cout << "The parking lot is empty.\n";
            return;
        }
        cout << "Parked cars (front to rear):\n";
        int i = front;
        while (true)
        {
            cout << "  Slot " << c[i].slotNumber << " | Car " << c[i].carNumber
                 << " | Arrival " << c[i].arrivalTime << endl;
            if (i == rear)
                break;
            i = (i + 1) % SIZE;
        }
    }
};

int main()
{
    Parking p;

    cout << "===== Test 1: empty lot =====\n";
    p.removeCar();
    p.viewNextCar();
    p.displayParkingStatus();

    cout << "\n===== Test 2: park until full =====\n";
    p.parkCar(1001, "08:00");

    p.parkCar(1002, "08:10");
    p.parkCar(1003, "08:20");
    p.parkCar(1004, "08:30");
    p.parkCar(1005, "08:40");

    p.displayParkingStatus();

    cout << "\n===== Test 3: full lot, 6th car rejected =====\n";
    p.parkCar(1006, "08:50");

    cout << "\n===== Test 4: view next, remove 3 cars =====\n";
    p.viewNextCar();
    p.removeCar();
    p.removeCar();
    p.removeCar();

    p.displayParkingStatus();

    cout << "\n===== Test 5: wrap-around (freed slots reused) =====\n";
    p.parkCar(2001, "09:00");
    p.parkCar(2002, "09:10");
    p.parkCar(2003, "09:20");
    p.displayParkingStatus();
    p.parkCar(2004, "09:30");

    cout << "\n===== Test 6: remove all, last car resets queue =====\n";
    p.removeCar();
    p.removeCar();
    p.removeCar();
    p.removeCar();
    p.removeCar();

    p.removeCar();

    cout << "\n===== Test 7: reuse after reset =====\n";
    p.parkCar(3001, "10:00");
    p.displayParkingStatus();

    return 0;
}