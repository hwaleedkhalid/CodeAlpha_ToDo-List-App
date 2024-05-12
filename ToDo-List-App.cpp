#include <iostream>
#include <string>
#include <windows.h>
#include <queue>

using namespace std;

void AddTask();
void currentTask();
void markComplete();
void viewAll();
void removeTask();

struct MyToDo
{
    string description;
    int priority;
    string dueDate; 

    bool operator < (const MyToDo& other) const
    {
        // Higher priority tasks come first (ascending order)
        return priority > other.priority;
    } 
};

std::priority_queue <MyToDo> q;

int main()
{
    int choice = 0;
    while (choice != 6)
    {
        cout << endl;
        cout << "------------------------------------------" << endl;
        cout << "|          ToDo List Application         |" << endl;
        cout << "|----------------------------------------|" << endl;
        cout << "|    1.  Add Task                        |" << endl;
        cout << "|    2.  View Current Task               |" << endl;
        cout << "|    3.  Mark Task as Complete           |" << endl;
        cout << "|    4.  View All Task                   |" << endl;
        cout << "|    5.  Remove Task                     |" << endl;
        cout << "|    6.  Exit                            |" << endl;
        cout << "------------------------------------------" << endl;
        cout << endl;
        cout << "            Choose an Option: ";
        cin >> choice;
        if(cin.fail())
        {
            cout << "Invalid input! Please enter a number." << endl;
            Sleep(500);
            cin.clear();
            cin.ignore();
            choice = 0;
            continue;
        }
        if(choice == 1)
        {
            AddTask();
        }
        else if(choice == 2)
        {
            currentTask();
        }
        else if(choice == 3)
        {
            markComplete();
        }
        else if(choice == 4)
        {
            viewAll();
        }
        else if(choice == 5)
        {
            removeTask();
        }
        else if(choice == 6)
        {
            cout << "System is Shutting Down....." << endl << endl;
        }
        else
        {
            cout << "Invalid Input!!!" << endl;
            cout << "Please Try Again..." << endl;
        }
    }
    

    return 0;
}



void AddTask()
{
    string desc, date;
    int priority;
    cout << endl;
    cin.ignore();
    cout << "Enter Task Description: ";
    getline(cin, desc);
    cout << "Enter Priority of your task (1 - 5): ";
    cin >> priority;
    while (cin.fail() || priority < 1 || priority > 5)
    {
        cout << "Invalid priority! Please enter a number between 1 and 5: ";
        cin.clear();
        cin.ignore();
        cin >> priority;
    }
    cout << "Enter due date: ";
    cin >> date;

    
    MyToDo newtask;
    newtask.description = desc;
    newtask.priority = priority;
    newtask.dueDate = date;


    q.push(newtask);

    cout << endl;
    cout << "Congratulations! Task added successfully." << endl;
    Sleep(1000);
}


void currentTask()
{
    MyToDo current = q.top();

    if(!q.empty())
    {
        cout << "+-------- Current Task is ----------+" << endl;
        cout << "=> Description: " << current.description << endl;
        cout << "=> Priority: " << current.priority << endl;
        cout << "=> Due Date: " << current.dueDate << endl;
        cout << endl;
    }
    else
    {
        cout << "No task in the list." << endl;
    }
}


void markComplete()
{
    MyToDo complete = q.top();

    if(!q.empty())
    {
        cout << "+----- Current Task marked as completed and removed from list ------+" << endl;
        q.pop();
    }
    else 
    {
        cout << "Error!!  No task to mark as complete. The queue is empty." << endl;
    }

}



void viewAll()
{
    std::priority_queue display = q;

    if(!display.empty())
    {
        while(!display.empty())
        {
            cout << "-------------------------------" << endl;
            cout << "Description: " << display.top().description << endl;
            cout << "Priority: " << display.top().priority << endl;
            cout << "Due Date: " << display.top().dueDate << endl;
            cout << endl;
            display.pop();
        }
    }
    else
    {
        cout << "No task in the list." << endl;
    }
    
}

void removeTask()
{
    cin.ignore();
    string desc;
    cout << "Enter the description of the task you want to remove: ";
    getline(cin, desc);

    std::priority_queue<MyToDo> temp;

    while (!q.empty())
    {
        MyToDo current = q.top();
        q.pop();

        if (current.description != desc)
        {
            temp.push(current);
        }
    }

    while (!temp.empty())
    {
        q.push(temp.top());
        temp.pop();
    }

    if (!q.empty() && q.top().description == desc)
    {
        cout << "Task removed successfully!" << endl;
    }
    else
    {
        cout << "Task not found / already removed." << endl;
    }
}
