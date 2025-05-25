#include <iostream>
#include <string>
#include <iomanip>
#include <ctime>
#include <limits>
struct ItemNumNode {
    int itemNumber;
    ItemNumNode* next;
    ItemNumNode(int num) : itemNumber(num), next(nullptr) {}
};

struct ItemNameNode {
    std::string itemName;
    ItemNameNode* next;
    ItemNameNode(const std::string& name) : itemName(name), next(nullptr) {}
};

struct ExpenseNode {
    double amount;
    ExpenseNode* next;
    ExpenseNode(double val) : amount(val), next(nullptr) {}
};

struct DateTimeNode {
    std::string dateTime;
    DateTimeNode* next;
    
    DateTimeNode(const std::string& dt) : dateTime(dt), next(nullptr) {}
};

struct MasterNode {
    void* data;
    std::string type;  
    MasterNode* next;
    MasterNode(void* head, const std::string& listType) : data(head), type(listType), next(nullptr) {}
};

class ExpenseTracker {
private:
    ItemNumNode* itemNumListHead;
    ItemNameNode* itemNameListHead;
    ExpenseNode* expenseListHead;
    DateTimeNode* dateTimeListHead;
    MasterNode* masterListHead;
    double totalBill;
    int itemCounter;
    
public:
    ExpenseTracker() : itemNumListHead(nullptr), itemNameListHead(nullptr), 
                       expenseListHead(nullptr), dateTimeListHead(nullptr), 
                       masterListHead(nullptr), totalBill(0.0), itemCounter(0) {}
    
    string getCurrentDateTime() {
        time_t now = time(0);
        struct tm timeinfo;
        char buffer[80];
        
        #ifdef _WIN32
            localtime_s(&timeinfo, &now);
        #else
            timeinfo = *localtime(&now);
        #endif
        
        strftime(buffer, sizeof(buffer), "%Y-%m-%d %H:%M:%S", &timeinfo);
        return std::string(buffer);
    }
    
    void addExpense() {
        std::string itemName;
        double amount;
        string dateTime;
        
        itemCounter++;
        int itemNum = itemCounter;
        
        cout << "Enter item name: ";
        getline(std::cin, itemName);

        cout << "Enter expense amount: $";
        while (!(std::cin >> amount) || amount < 0) {
            std::cout << "Invalid input. Please enter a positive number: $";
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        }
        
        
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        
        std::cout << "Use current date and time? (y/n): ";
        char choice;
        std::cin >> choice;
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        
        if (choice == 'y' || choice == 'Y') {
            dateTime = getCurrentDateTime();
        } else {
            std::cout << "Enter date and time (YYYY-MM-DD HH:MM:SS): ";
            std::getline(std::cin, dateTime);
        }
        
        // Update total bill
        totalBill += amount;
        
        // Add to item number list
        addToItemNumList(itemNum);
        
        // Add to item name list
        addToItemNameList(itemName);
        
        // Add to expense list
        addToExpenseList(amount);
        
        // Add to date-time list
        addToDateTimeList(dateTime);
        
        std::cout << "\nExpense added successfully!\n" << std::endl;
    }
    
    // Add to item number list
    void addToItemNumList(int itemNum) {
        ItemNumNode* newNode = new ItemNumNode(itemNum);
        
        if (!itemNumListHead) {
            itemNumListHead = newNode;
            return;
        }
        
        ItemNumNode* temp = itemNumListHead;
        while (temp->next) {
            temp = temp->next;
        }
        temp->next = newNode;
    }
    
    // Add to item name list
    void addToItemNameList(const std::string& itemName) {
        ItemNameNode* newNode = new ItemNameNode(itemName);
        
        if (!itemNameListHead) {
            itemNameListHead = newNode;
            return;
        }
        
        ItemNameNode* temp = itemNameListHead;
        while (temp->next) {
            temp = temp->next;
        }
        temp->next = newNode;
    }
    
    // Add to expense list
    void addToExpenseList(double amount) {
        ExpenseNode* newNode = new ExpenseNode(amount);
        
        if (!expenseListHead) {
            expenseListHead = newNode;
            return;
        }
        
        ExpenseNode* temp = expenseListHead;
        while (temp->next) {
            temp = temp->next;
        }
        temp->next = newNode;
    }
    
    // Add to date-time list
    void addToDateTimeList(const std::string& dateTime) {
        DateTimeNode* newNode = new DateTimeNode(dateTime);
        
        if (!dateTimeListHead) {
            dateTimeListHead = newNode;
            return;
        }
        
        DateTimeNode* temp = dateTimeListHead;
        while (temp->next) {
            temp = temp->next;
        }
        temp->next = newNode;
    }
    
    // Create master list containing heads of all lists
    void createMasterList() {
        // Add item number list head to master list
        masterListHead = new MasterNode(itemNumListHead, "itemNum");
        
        // Add item name list head to master list
        MasterNode* itemNameMasterNode = new MasterNode(itemNameListHead, "itemName");
        masterListHead->next = itemNameMasterNode;
        
        // Add expense list head to master list
        MasterNode* expenseMasterNode = new MasterNode(expenseListHead, "expense");
        itemNameMasterNode->next = expenseMasterNode;
        
        // Add date-time list head to master list
        MasterNode* dateTimeMasterNode = new MasterNode(dateTimeListHead, "datetime");
        expenseMasterNode->next = dateTimeMasterNode;
    }
    
    // Display all expenses as a bill
    void displayBill() {
        if (!itemNumListHead || !itemNameListHead || !expenseListHead || !dateTimeListHead) {
            std::cout << "No expenses recorded yet!" << std::endl;
            return;
        }
        
        std::cout << "\n===================== EXPENSE BILL =====================\n" << std::endl;
        std::cout << std::left << std::setw(5) << "Item#" 
                  << std::setw(25) << "Item Name" 
                  << std::setw(10) << "Amount" 
                  << "Date & Time" << std::endl;
        std::cout << std::string(70, '-') << std::endl;
        
        ItemNumNode* itemNumPtr = itemNumListHead;
        ItemNameNode* itemNamePtr = itemNameListHead;
        ExpenseNode* expensePtr = expenseListHead;
        DateTimeNode* dateTimePtr = dateTimeListHead;
        
        while (itemNumPtr && itemNamePtr && expensePtr && dateTimePtr) {
            std::cout << std::left << std::setw(5) << itemNumPtr->itemNumber
                      << std::setw(25) << itemNamePtr->itemName 
                      << "$" << std::setw(9) << std::fixed << std::setprecision(2) << expensePtr->amount
                      << dateTimePtr->dateTime << std::endl;
            
            itemNumPtr = itemNumPtr->next;
            itemNamePtr = itemNamePtr->next;
            expensePtr = expensePtr->next;
            dateTimePtr = dateTimePtr->next;
        }
        
        std::cout << std::string(70, '-') << std::endl;
        std::cout << std::right << std::setw(31) << "Total Bill: $" 
                  << std::fixed << std::setprecision(2) << totalBill << std::endl;
        std::cout << std::string(70, '=') << std::endl;
    }
    
    // Display all lists using the master list
    void displayAllListsViaMaster() {
        if (!masterListHead) {
            std::cout << "Master list is not created yet!" << std::endl;
            return;
        }
        
        std::cout << "\n===== All Lists Data (via Master List) =====\n" << std::endl;
        
        MasterNode* currentMaster = masterListHead;
        
        while (currentMaster) {
            std::cout << "List Type: " << currentMaster->type << std::endl;
            std::cout << std::string(30, '-') << std::endl;
            
            if (currentMaster->type == "itemNum") {
                ItemNumNode* itemNumPtr = static_cast<ItemNumNode*>(currentMaster->data);
                
                while (itemNumPtr) {
                    std::cout << "Item #" << itemNumPtr->itemNumber << std::endl;
                    itemNumPtr = itemNumPtr->next;
                }
            } 
            else if (currentMaster->type == "itemName") {
                ItemNameNode* itemNamePtr = static_cast<ItemNameNode*>(currentMaster->data);
                int count = 1;
                
                while (itemNamePtr) {
                    std::cout << "Entry " << count << ": " << itemNamePtr->itemName << std::endl;
                    itemNamePtr = itemNamePtr->next;
                    count++;
                }
            }
            else if (currentMaster->type == "expense") {
                ExpenseNode* expensePtr = static_cast<ExpenseNode*>(currentMaster->data);
                int count = 1;
                
                while (expensePtr) {
                    std::cout << "Entry " << count << ": $" << std::fixed << std::setprecision(2) << expensePtr->amount << std::endl;
                    expensePtr = expensePtr->next;
                    count++;
                }
            }
            else if (currentMaster->type == "datetime") {
                DateTimeNode* dateTimePtr = static_cast<DateTimeNode*>(currentMaster->data);
                int count = 1;
                
                while (dateTimePtr) {
                    std::cout << "Entry " << count << ": " << dateTimePtr->dateTime << std::endl;
                    dateTimePtr = dateTimePtr->next;
                    count++;
                }
            }
            
            std::cout << std::endl;
            currentMaster = currentMaster->next;
        }
        
        std::cout << "=== Total Bill: $" << std::fixed << std::setprecision(2) << totalBill << " ===" << std::endl;
    }
    
    // Destructor to free memory
    ~ExpenseTracker() {
        // Free item number list
        ItemNumNode* tempItemNum = itemNumListHead;
        while (tempItemNum) {
            ItemNumNode* next = tempItemNum->next;
            delete tempItemNum;
            tempItemNum = next;
        }
        
        // Free item name list
        ItemNameNode* tempItemName = itemNameListHead;
        while (tempItemName) {
            ItemNameNode* next = tempItemName->next;
            delete tempItemName;
            tempItemName = next;
        }
        
        // Free expense list
        ExpenseNode* tempExpense = expenseListHead;
        while (tempExpense) {
            ExpenseNode* next = tempExpense->next;
            delete tempExpense;
            tempExpense = next;
        }
        
        // Free date-time list
        DateTimeNode* tempDateTime = dateTimeListHead;
        while (tempDateTime) {
            DateTimeNode* next = tempDateTime->next;
            delete tempDateTime;
            tempDateTime = next;
        }
        
        // Free master list
        MasterNode* tempMaster = masterListHead;
        while (tempMaster) {
            MasterNode* next = tempMaster->next;
            delete tempMaster;
            tempMaster = next;
        }
    }
};

int main() {
    ExpenseTracker tracker;
    int choice;
    
    std::cout << "===== Expense Tracking System =====\n" << std::endl;
    
    do {
        std::cout << "Menu:" << std::endl;
        std::cout << "1. Add Expense Item" << std::endl;
        std::cout << "2. Display Expense Bill" << std::endl;
        std::cout << "3. Create Master List and Display All Data" << std::endl;
        std::cout << "4. Exit" << std::endl;
        std::cout << "Enter your choice: ";
        
        while (!(std::cin >> choice) || choice < 1 || choice > 4) {
            std::cout << "Invalid input. Please enter a number between 1 and 4: ";
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        }
        
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        
        switch (choice) {
            case 1:
                tracker.addExpense();
                break;
            case 2:
                tracker.displayBill();
                break;
            case 3:
                tracker.createMasterList();
                tracker.displayAllListsViaMaster();
                break;
            case 4:
                std::cout << "\nThank you for using the Expense Tracking System!" << std::endl;
                break;
        }
        
        if (choice != 4) {
            std::cout << "\nPress Enter to continue...";
            std::cin.get();
            std::cout << "\n";
        }
        
    } while (choice != 4);
    
    return 0;
}