#include <iostream>
#include <string>
#include <vector>
#include <fstream>
using namespace std;

// Expense class
class Expense {
private:
    float amount;
    string description;

public:
    Expense(float amt, string desc) : amount(amt), description(desc) {}

    float getAmount() const {
        return amount;
    }

    string getDescription() const {
        return description;
    }

    void saveToFile(ofstream &outFile) const {
        outFile << amount << "\n" << description << "\n";
    }

    static Expense loadFromFile(ifstream &inFile) {
        float amt;
        string desc;

        inFile >> amt;
        inFile.ignore(); // Ignore newline
        getline(inFile, desc);

        return Expense(amt, desc);
    }
};

// Category class
class Category {
private:
    string name;
    float budgetLimit;
    float amountSpent;
    vector<Expense> expenses;

public:
    // Constructor
    Category(string categoryName) : name(categoryName), budgetLimit(0), amountSpent(0) {}

    // Method to set the budget limit
    void setBudget(float budget) {
        budgetLimit = budget;
        cout << "Budget for category \"" << name << "\" set to " << budgetLimit << endl;
    }

    // Method to add an expense
    void addExpense(float amount, string description) {
        Expense newExpense(amount, description);
        expenses.push_back(newExpense);
        amountSpent += amount;
        cout << "Added expense: \"" << description << "\" (" << amount << ") to category \"" << name << "\"\n";
    }

    // Method to display category information
    void displayInfo() const {
        cout << "\n--- Category: " << name << " ---\n";
        cout << "Budget Limit: " << budgetLimit << "\n";
        cout << "Amount Spent: " << amountSpent << "\n";
        cout << "Remaining Budget: " << (budgetLimit - amountSpent) << "\n";

        cout << "\nExpenses:\n";
        for (const auto &expense : expenses) {
            cout << "- " << expense.getDescription() << ": " << expense.getAmount() << "\n";
        }
    }

    // Getter for category name
    string getName() const {
        return name;
    }

    // Save category data to a file
    void saveToFile(ofstream &outFile) const {
        outFile << name << "\n" << budgetLimit << "\n" << amountSpent << "\n";
        outFile << expenses.size() << "\n";
        for (const auto &expense : expenses) {
            expense.saveToFile(outFile);
        }
    }

    // Load category data from a file
    static Category loadFromFile(ifstream &inFile) {
        string categoryName;
        float budget, spent;
        size_t numExpenses;

        getline(inFile, categoryName);
        inFile >> budget >> spent >> numExpenses;
        inFile.ignore(); // Ignore newline character

        Category category(categoryName);
        category.budgetLimit = budget;
        category.amountSpent = spent;

        for (size_t i = 0; i < numExpenses; ++i) {
            category.expenses.push_back(Expense::loadFromFile(inFile));
        }

        return category;
    }
};

// Function to save all categories to a file
void saveCategoriesToFile(const vector<Category> &categories, const string &filename) {
    ofstream outFile(filename);
    if (!outFile) {
        cerr << "Error opening file for writing.\n";
        return;
    }

    outFile << categories.size() << "\n";
    for (const auto &category : categories) {
        category.saveToFile(outFile);
    }

    outFile.close();
    cout << "Data saved successfully to " << filename << endl;
}

// Function to load all categories from a file
void loadCategoriesFromFile(vector<Category> &categories, const string &filename) {
    ifstream inFile(filename);
    if (!inFile) {
        cerr << "Error opening file for reading. Starting fresh.\n";
        return;
    }

    size_t numCategories;
    inFile >> numCategories;
    inFile.ignore(); // Ignore newline character

    categories.clear(); // Ensure no leftover data
    for (size_t i = 0; i < numCategories; ++i) {
        categories.push_back(Category::loadFromFile(inFile));
    }

    inFile.close();
    cout << "Data loaded successfully from " << filename << endl;
}

// Main Program
int main() {
    vector<Category> categories;
    const string filename = "categories.txt";

    // Load data from file
    loadCategoriesFromFile(categories, filename);

    int choice;

    while (true) {
        cout << "\n--- Personal Budget Tracker ---\n";
        cout << "1. Add Category\n";
        cout << "2. Set Budget for a Category\n";
        cout << "3. Add Expense\n";
        cout << "4. Display Category Info\n";
        cout << "5. Save and Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        if (choice == 1) {
            // Add a new category
            cin.ignore();
            string categoryName;
            cout << "Enter category name: ";
            getline(cin, categoryName);
            categories.emplace_back(categoryName);
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
                cout << "Enter budget limit for \"" << categories[index].getName() << "\": ";
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
                cin.ignore(); 
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

            for (const auto &category : categories) {
                category.displayInfo();
            }

        } else if (choice == 5) {
            // Save data to file and exit
            saveCategoriesToFile(categories, filename);
            cout << "Exiting program...\n";
            break;

        } else {
            cout << "Invalid choice. Please try again.\n";
        }
    }

    return 0;
}