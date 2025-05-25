#include <iostream>
#include <string>
#include <ctime>
using namespace std;

struct Node {
    int ItemNumber;
    string ItemName;
    double Expense;
    string DateTime;
    Node* next;
    
    Node(int number,string name,double exp,string dt){
    	ItemNumber = number;
    	ItemName = name;
    	Expense = exp;
    	DateTime = dt;
	}
};

struct ExpenseList {
    Node* head;
    ExpenseList* next;
    
    ExpenseList() {
    	head = NULL;
    	next = NULL;
	}
};

class ExpenseTracker {
private:
    ExpenseList* masterlist;
    int Total;
    
    string getCurrentDateTime() {
        time_t now = time(0);
        char* dt = ctime(&now);
        string dateTime(dt);
        dateTime.pop_back(); 
        return dateTime;
    }
    
public:
    ExpenseTracker() {
    	masterlist = NULL;
    	Total = 0;
	}

    void addExpense() {
        int itemnumber;
        string itemname;
        double expense;
        
        cout << "Enter item number: "<<endl;
        cin >> itemnumber;
        cin.ignore();
        cout << "Enter item name: " <<endl;
        getline(cin, itemname);
        cout << "Enter expense amount: "<<endl;
        cin >> expense;
        
        string dateTime = getCurrentDateTime();
        
        ExpenseList* newList = new ExpenseList();
        newList->head = new Node(itemnumber, itemname, expense, dateTime);
        
        if (!masterlist) {
            masterlist = newList;
        } else {
            ExpenseList* temp = masterlist;
            while (temp->next) temp = temp->next;
            temp->next = newList;
        }
        
        Total++;
        cout << "Expense added successfully!"<<endl;
    }
    
    void displayAll() {
        if (!masterlist) {
            cout << "No expenses recorded."<<endl;
            return;
        }
        
        cout << " ... ALL EXPENSES ... "<<endl;
        ExpenseList* temp = masterlist;
        double total = 0;
        
        while (temp) {
            Node* node = temp->head;
            cout << "Item No: " << node->ItemNumber 
                 << " | Name: " << node->ItemName 
                 << " | Amount: Rs: " << node->Expense 
                 << " | Date: " << node->DateTime << endl;
            total += node->Expense;
            temp = temp->next;
        }
        
        cout << "TOTAL BILL: Rs: " << total << endl;
        cout << "Total Items: " << Total << endl;
    }
    
    void displaySpecific() {
        int itemNumber;
        cout << "Enter item number to display: ";
        cin >> itemNumber;
        
        ExpenseList* temp = masterlist;
        while (temp) {
            if (temp->head->ItemNumber == itemNumber) {
                Node* node = temp->head;
                cout << " === ITEM DETAILS === "<<endl;
                cout << "Item No: " << node->ItemNumber << endl;
                cout << "Item Name: " << node->ItemName << endl;
                cout << "Item Expense: $" << node->Expense << endl;
                cout << "Date & Time: " << node->DateTime << endl;
                return;
            }
            temp = temp->next;
        }
        cout << "Item not found! "<<endl;
    }
    
    void deleteExpense() {
        int itemNo;
        cout << "Enter item number to delete: ";
        cin >> itemNo;
        
        if (!masterlist) {
            cout << "No expenses to delete."<<endl;
            return;
        }
        
        if (masterlist->head->ItemNumber == itemNo) {
            ExpenseList* toDelete = masterlist;
            masterlist = masterlist->next;
            delete toDelete->head;
            delete toDelete;
            Total--;
            cout << "Expense deleted successfully!"<<endl;
            return;
        }
        
        ExpenseList* previous = masterlist;
        ExpenseList* current = masterlist->next;
        
        while (current) {
            if (current->head->ItemNumber == itemNo) {
                previous->next = current->next;
                delete current->head;
                delete current;
                Total--;
                cout << "Expense deleted successfully!"<<endl;
                return;
            }
            previous = current;
            current = current->next;
        }
        
        cout << "Item not found!"<<endl;
    }
    
    void menu() {
        int choice;
        
        while (true) {
            cout << " ... EXPENSE TRACKER ..."<<endl;
            cout << "1. Add Expense."<<endl;
            cout << "2. Display All Expenses."<<endl;
            cout << "3. Display Specific Item."<<endl;
            cout << "4. Delete Expense."<<endl;
            cout << "5. Exit."<<endl;
            cout << "Enter choice: ";
            cin >> choice;
            
            switch (choice) {
                case 1: addExpense(); 
						break;
                case 2: displayAll();
					 	break;
                case 3: displaySpecific();
						break;
                case 4: deleteExpense();
						break;
                case 5: 
                    cout << "Thank you for using Expense Tracker!"<<endl;
                    return;
                		default: 
                    cout << "Invalid choice!"<<endl;
            }
        }
    }
    
    ~ExpenseTracker() {
        while (masterlist) {
            ExpenseList* temp = masterlist;
            masterlist = masterlist->next;
            delete temp->head;
            delete temp;
        }
    }
};

int main() {
    ExpenseTracker tracker;
    tracker.menu();
    return 0;
}