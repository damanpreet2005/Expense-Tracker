#include <iostream>
#include <string>
#include <vector>
using namespace std;

// Expense class
class Expense {
    float amount;
    string description;

public:
    Expense(float amt, const string& desc) : amount(amt), description(desc) {}

    float getAmount() const { return amount; }
    string getDescription() const { return description; }
};

// Category class
class Category {
    string name;
    float budgetLimit = 0, amountSpent = 0;
    vector<Expense> expenses;

public:
    Category(const string& categoryName) : name(categoryName) {}

    // Set the budget for this category
    void setBudget(float budget) {
        budgetLimit = budget;
        cout << "Budget for category \"" << name << "\" set to " << budgetLimit << "\n";
    }

    // Add an expense to this category
    void addExpense(float amount, const string& description) {
        expenses.push_back(Expense(amount, description));
        amountSpent += amount;
        cout << "Added expense: \"" << description << "\" (" << amount << ") to category \"" << name << "\"\n";
    }

    // Display the category information
    void displayInfo() const {
        cout << "\n--- Category: " << name << " ---\n";
        cout << "Budget Limit: " << budgetLimit << "\n";
        cout << "Amount Spent: " << amountSpent << "\n";
        cout << "Remaining Budget: " << (budgetLimit - amountSpent) << "\n";
        
        cout << "\nExpenses:\n";
        for (const auto& expense : expenses) {
            cout << "- " << expense.getDescription() << ": " << expense.getAmount() << "\n";
        }
    }

    string getName() const { return name; }
};

// Main program
int main() {
    vector<Category> categories;
    int choice;

    while (true) {
        cout << "\n--- Personal Budget Tracker ---\n";
        cout << "1. Add Category\n";
        cout << "2. Set Budget for a Category\n";
        cout << "3. Add Expense to Category\n";
        cout << "4. Display Category Info\n";
        cout << "5. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        if (choice == 1) {
            // Add a new category
            cin.ignore();  // To clear the input buffer
            string categoryName;
            cout << "Enter category name: ";
            getline(cin, categoryName);
            categories.push_back(Category(categoryName));
            cout << "Category \"" << categoryName << "\" added successfully!\n";

        } else if (choice == 2) {
            // Set budget for an existing category
            int index;
            float budget;

            if (categories.empty()) {
                cout << "No categories available. Add a category first.\n";
                continue;
            }

            cout << "Enter category index to set budget (0 - " << categories.size() - 1 << "): ";
            cin >> index;

            if (index >= 0 && index < categories.size()) {
                cout << "Enter budget for \"" << categories[index].getName() << "\": ";
                cin >> budget;
                categories[index].setBudget(budget);
            } else {
                cout << "Invalid category index.\n";
            }

        } else if (choice == 3) {
            // Add an expense to a category
            int index;
            float amount;
            string description;

            if (categories.empty()) {
                cout << "No categories available. Add a category first.\n";
                continue;
            }

            cout << "Enter category index to add expense (0 - " << categories.size() - 1 << "): ";
            cin >> index;

            if (index >= 0 && index < categories.size()) {
                cin.ignore();  // To clear the input buffer
                cout << "Enter expense description: ";
                getline(cin, description);
                cout << "Enter expense amount: ";
                cin >> amount;
                categories[index].addExpense(amount, description);
            } else {
                cout << "Invalid category index.\n";
            }

        } else if (choice == 4) {
            // Display information for all categories
            if (categories.empty()) {
                cout << "No categories available to display.\n";
                continue;
            }

            for (const auto& category : categories) {
                category.displayInfo();
            }

        } else if (choice == 5) {
            // Exit the program
            cout << "Exiting program...\n";
            break;

        } else {
            cout << "Invalid choice. Please try again.\n";
        }
    }

    return 0;
}