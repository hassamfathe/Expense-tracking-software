#include<string>
using namespace std;


struct Node {
    int ItemNumber;
    string ItemName;
    double Expense;
    string DateTime;
    Node* next;
    Node* related;
    
    Node(int number,string name,double exp,string dt){
    	ItemNumber = number;
    	ItemName = name;
    	Expense = exp;
    	DateTime = dt;
        next = nullptr;
        related = nullptr;
	}
};