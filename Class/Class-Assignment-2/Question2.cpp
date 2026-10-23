#include <iostream>
using namespace std;

struct Node
{
    string title;
    string url;
    string time;
    Node *next;

    Node(string t, string u, string tm)
    {
        title = t;
        url = u;
        time = tm;
        next = nullptr;
    }
};

class BrowserHistory
{
    Node *top = nullptr;

public:
    ~BrowserHistory()
    {
        while (top != nullptr)
        {
            Node *temp = top;
            top = top->next;
            delete temp;
        }
    }

    bool isEmpty() { return top == nullptr; }

    void visitPage(string title, string url, string time)
    {
        Node *newnode = new Node(title, url, time);
        newnode->next = top;
        top = newnode;
        cout << "Visited: " << title << endl;
    }

    void goBack()
    {
        if (isEmpty())
        {
            cout << "Underflow: history is empty.\n";
            return;
        }
        if (top->next == nullptr)
        {
            cout << "No previous page available.\n";
            return;
        }
        Node *temp = top;
        top = top->next;
        delete temp;
    }

    void viewCurrentPage()
    {
        if (isEmpty())
        {
            cout << "No current page. History is empty.\n";
            return;
        }
        cout << "Current page -> Title: " << top->title
             << ", URL: " << top->url
             << ", Time: " << top->time << endl;
    }

    void displayHistory()
    {
        if (isEmpty())
        {
            cout << "History is empty.\n";
            return;
        }
        cout << "History (latest first):\n";
        Node *temp = top;
        while (temp != nullptr)
        {
            cout << "  " << temp->title << " | " << temp->url << " | " << temp->time << endl;
            temp = temp->next;
        }
    }
};

int main()
{
    BrowserHistory h;

    cout << "--- empty history ---\n";
    h.viewCurrentPage();
    h.displayHistory();
    h.goBack();

    cout << "\n--- Visit 3 pages ---\n";
    h.visitPage("Google", "www.google.com", "10:00");
    h.visitPage("YouTube", "www.youtube.com", "10:05");
    h.visitPage("COMSATS", "www.comsats.edu.pk", "10:10");
    h.viewCurrentPage();
    h.displayHistory();

    cout << "\n--- goBack  ---\n";
    h.goBack();
    h.viewCurrentPage();
    h.goBack();
    h.viewCurrentPage();

    cout << "\n---  single page ---\n";
    h.goBack();
    h.viewCurrentPage();
    h.displayHistory();

    return 0;
}