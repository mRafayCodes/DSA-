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

    Order()
    {
        orderID = 0;
        restaurantName = "";
        customerAddress = "";
        itemList = "";
        preparationTime = 0;
        orderTime = "";
    }

    Order(int id, string r, string a, string items, int p, string t)
    {
        orderID = id;
        restaurantName = r;
        customerAddress = a;
        itemList = items;
        preparationTime = p;
        orderTime = t;
    }
};