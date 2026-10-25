#include <iostream>
using namespace std;

class Order
{
public:
    int orderID;
    string restaurantName;
    string customerAddress;
    string itemList;
    int preparationTime;
    string orderTime;
    Order *next;

    Order()
    {
        orderID = 0;
        restaurantName = "";
        customerAddress = "";
        itemList = "";
        preparationTime = 0;
        orderTime = "";
        next = nullptr;
    }

    Order(int id, string r, string a, string items, int p, string t)
    {
        orderID = id;
        restaurantName = r;
        customerAddress = a;
        itemList = items;
        preparationTime = p;
        orderTime = t;
        next = nullptr;
    }
};

class DeliverySystem
{
    Order *front = nullptr;
    Order *rear = nullptr;

public:
    ~DeliverySystem() // bache hue orders ki memory free
    {
        while (front != nullptr)
        {
            Order *t = front;
            front = front->next;
            delete t;
        }
        rear = nullptr;
    }

    bool isEmpty()
    {
        return front == nullptr;
    }

    void addOrder(int id, string r, string a, string items, int p, string t)
    {
        Order *o = new Order(id, r, a, items, p, t);
        if (isEmpty())
        {
            front = rear = o;
            cout << "Order " << id << " added.\n";
        }
        else if (p <= 10) // quick order -> front
        {
            o->next = front;
            front = o;
            cout << "Order " << id << " added at front (quick, " << p << " min).\n";
        }
        else // normal order -> rear
        {
            rear->next = o;
            rear = o;
            cout << "Order " << id << " added at rear (" << p << " min).\n";
        }
    }

    void dispatchOrder()
    {
        if (isEmpty())
        {
            cout << "No order to dispatch. Queue is empty.\n";
            return;
        }
        Order *temp = front;
        cout << "Dispatching order " << temp->orderID << " (" << temp->restaurantName
             << " -> " << temp->customerAddress << ")\n";
        front = front->next;
        if (front == nullptr)
        {
            rear = nullptr;
        }
        delete temp;
    }

    void viewNextOrder()
    {
        if (isEmpty())
        {
            cout << "No pending orders.\n";
            return;
        }
        cout << "Next order -> ID: " << front->orderID
             << ", Restaurant: " << front->restaurantName
             << ", Address: " << front->customerAddress
             << ", Items: " << front->itemList
             << ", Prep: " << front->preparationTime << " min"
             << ", Time: " << front->orderTime << endl;
    }

    void displayAllOrders()
    {
        if (isEmpty())
        {
            cout << "No pending orders.\n";
            return;
        }
        cout << "Pending orders :\n";
        Order *temp = front;
        while (temp != nullptr)
        {
            cout << "  ID " << temp->orderID << " | " << temp->restaurantName
                 << " | " << temp->customerAddress << " | " << temp->itemList
                 << " | " << temp->preparationTime << " min | " << temp->orderTime << endl;
            temp = temp->next;
        }
    }

    void cancelOrder(int id)
    {
        if (isEmpty())
        {
            cout << "No order is available.\n";
            return;
        }

        if (front->orderID == id)
        {
            Order *del = front;
            front = front->next;

            if (front == nullptr)
                rear = nullptr;

            delete del;
            cout << "Order " << id << " cancelled successfully.\n";
            return;
        }

        Order *temp = front;

        while (temp->next != nullptr && temp->next->orderID != id)
        {
            temp = temp->next;
        }

        if (temp->next == nullptr)
        {
            cout << "No order available with ID " << id << "\n";
            return;
        }

        Order *del = temp->next;
        temp->next = del->next;

        if (del == rear)
            rear = temp;

        delete del;
        cout << "Order " << id << " cancelled successfully.\n";
    }
};

int main()
{
    DeliverySystem d;

    cout << "===== Test 1: empty queue =====\n";
    d.dispatchOrder();
    d.viewNextOrder();
    d.displayAllOrders();
    d.cancelOrder(1);

    cout << "\n===== Test 2: quick and normal orders =====\n";
    d.addOrder(1, "Pizza Hut", "House 5", "Pizza", 5, "12:00");     // quick
    d.addOrder(2, "KFC", "House 9", "Zinger", 20, "12:01");         // normal
    d.addOrder(3, "Subway", "House 2", "Sub", 8, "12:02");          // quick
    d.addOrder(4, "BBQ Tonight", "House 7", "Karahi", 25, "12:03"); // normal
    d.addOrder(5, "Burger Lab", "House 1", "Burger", 10, "12:04");  // quick (10 <= 10)
    d.displayAllOrders();                                           // 5, 3, 1, 2, 4
    d.viewNextOrder();

    cout << "\n===== Test 3: dispatch from front =====\n";
    d.dispatchOrder();
    d.displayAllOrders();

    cout << "\n===== Test 4: cancel middle order =====\n";
    d.cancelOrder(1);
    d.displayAllOrders();

    cout << "\n===== Test 5: cancel last (rear) order, then add normal =====\n";
    d.cancelOrder(4);
    d.displayAllOrders();
    d.addOrder(6, "Pizza Hut", "House 8", "Fries", 30, "12:05"); // rear sahi hona chahiye
    d.displayAllOrders();

    cout << "\n===== Test 6: cancel first order =====\n";
    d.cancelOrder(3);
    d.displayAllOrders();

    cout << "\n===== Test 7: cancel non-existing order =====\n";
    d.cancelOrder(99);
    d.displayAllOrders();

    cout << "\n===== Test 8: single order, cancel it =====\n";
    d.dispatchOrder();    // 2
    d.displayAllOrders(); // sirf 6
    d.cancelOrder(6);
    d.displayAllOrders();
    d.dispatchOrder();

    cout << "\n===== Test 9: reuse after empty =====\n";
    d.addOrder(7, "KFC", "House 3", "Wings", 15, "12:10");
    d.addOrder(8, "Subway", "House 4", "Sub", 6, "12:11");
    d.displayAllOrders();

    cout << "\n===== Test 10: leave orders (destructor frees) =====\n";
    d.addOrder(9, "BBQ Tonight", "House 6", "Tikka", 22, "12:12");
    d.displayAllOrders();

    return 0;
}