#include <iostream>
#include <string>
#include <ctime>
#include"NodeModule.h"
using namespace std;


class ExpenseTracker {
private:
    Node* masterlist;
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
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << "Enter item name: " <<endl;
        getline(cin, itemname);
        cout << "Enter expense amount: "<<endl;
        cin >> expense;
        string dateTime = getCurrentDateTime();
        
        Node* newExpense = new Node(itemnumber, itemname, expense, dateTime);

        
        if (!masterlist) {
            masterlist = newExpense;
        } else {
            Node* temp = masterlist;
            while (temp->next) temp = temp->next;
            temp->next = newExpense;
        }

        char choice;
        cout<<"Add related sub-items? (y/n):"<<endl;
        cin>>choice;
        cin.ignore();

        while (choice == 'y' || choice == 'Y') {

            cout << "Enter Related (subItems) number: "<<endl;
            cin >> itemnumber;
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout<<"Enter Related (subItems) name: "<<endl;
            getline(cin, itemname);
            cout << "Enter expense amount: "<<endl;
            cin >> expense;

            dateTime = getCurrentDateTime();
            Node* subExpense = new Node(itemnumber, itemname, expense, dateTime);


           if (!newExpense->related) {
            newExpense->related = subExpense;
           } else {
            Node* subTemp = newExpense->related;
            while (subTemp->related) subTemp = subTemp->related;
            subTemp->related = subExpense;
           }

           cout<<"Add more sub-items? (y/n):"<<endl;
           cin>>choice;
           cin.ignore();

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
        Node* temp = masterlist;
        double total = 0;
        
        while (temp) {
            cout << "Item No: " << temp->ItemNumber 
                 << " | Name: " << temp->ItemName 
                 << " | Amount: Rs: " << temp->Expense 
                 << " | Date: " << temp->DateTime << endl;
            total += temp->Expense;
            Node* sub = temp->related;
            while(sub) {
                cout << "Sub Item No: " << sub->ItemNumber
                 << " | Name: " << sub->ItemName
                 << " | Amount: Rs: " << sub->Expense 
                 << " | Date: " << sub->DateTime << endl;

                total += sub->Expense;
                sub = sub->related;
            }
            temp = temp->next;
        }
    
        cout << "TOTAL BILL: Rs: " << total << endl;
        cout << "Total Items: " << Total << endl;
    }
    
    void displaySpecific() {
        int itemNumber;
        cout << "Enter item number to display: ";
        cin >> itemNumber;
        
        Node* temp = masterlist;
        while (temp) {
            if (temp->ItemNumber == itemNumber) {
                cout << " === ITEM DETAILS === "<<endl;
                cout << "Item No: " << temp->ItemNumber << endl;
                cout << "Item Name: " << temp->ItemName << endl;
                cout << "Item Expense: $" << temp->Expense << endl;
                cout << "Date & Time: " << temp->DateTime << endl;

                Node* sub = temp->related;
                if (sub) cout<<"   Sub-Items   "<<endl;
                while(sub) {
                    cout << "   -> " << sub->ItemName
                         << " | Rs: " << sub->Expense
                         << " | Date: " << sub->DateTime << endl;
                    sub = sub->related;
                }
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
        
        if (masterlist->ItemNumber == itemNo) {
            Node* toDelete = masterlist;
            masterlist = masterlist->next;

            while (toDelete->related) {
                Node* sub = toDelete->related;
                toDelete->related = sub->related;
                delete sub;
            }
            delete toDelete;
            Total--;
            cout << "Expense deleted successfully!"<<endl;
            return;
        }
        
        Node* prev = masterlist;
        Node* curr = masterlist->next;
        
        while (curr) {
            if (curr->ItemNumber == itemNo) {
                prev->next = curr->next;
                while (curr->related) {
                    Node* sub = curr->related;
                    curr->related = sub->related;
                    delete sub;
                }
                delete curr;
                Total--;
                cout << "Expense deleted successfully!"<<endl;
                return;
            }
            prev = curr;
            curr = curr->next;
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
            Node* temp = masterlist;
            masterlist = masterlist->next;

            while (temp->related) {
                Node* sub = temp->related;
                temp->related = sub->related;
                delete sub;
            }
            delete temp;
        }
    }
};

