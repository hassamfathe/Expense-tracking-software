Expense-Tracking-Software

A C++ Expense Tracking Software built using Linked List data structures.

📌 Overview

This project is designed to track daily expenses in a simple yet efficient way using C++ and Linked Lists. It allows users to add, delete, and view their expenses dynamically without worrying about fixed-size arrays.

⚙️ Features

Add new expense entries (with item name, amount, and timestamp).

Delete or update expenses.

Display all recorded expenses in a structured way.

Maintains a sequential list of all expenses using a singly linked list.

Automatically records the date and time of each entry.

🏗️ Project Structure

The project follows a modular structure for better encapsulation and maintainability:

ExpenseModule.h → Contains the Node structure (for each expense).

ExpenseTracker.h → Contains the ExpenseTracker class which manages the linked list operations (add, remove, display, etc.).

main.cpp → The driver file which integrates everything and provides the user interface.

🧩 Implementation Details

Node Structure: Stores expense details such as ItemNumber, ItemName, ExpenseAmount, and DateTime.

Linked List: Used for dynamic memory allocation so expenses can grow as needed without predefined limits.

Encapsulation: Achieved by separating implementation into header files (.h) and keeping logic modular.

🚀 Future Improvements

Add file handling to save and load expenses.

Provide search and filter features (e.g., search by date or category).

Generate summary reports (monthly, weekly, total).

Add a simple menu-driven interface for better usability.




