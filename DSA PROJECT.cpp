#include <iostream>
#include <string>
#include <fstream>
#include <conio.h> // for getch() on Windows
#include <unistd.h> // for sleep()
#include <windows.h>
#include <limits>
#include <vector>
#include <algorithm>
#include <cstdlib> 
#include <sstream>  
#include <cstring>
#include <string>
#include <cstdlib> // for system("CLS")
#include <iomanip> // for setprecision
#include <sstream> // for ostringstream
#include <algorithm> // for sort
#include <cctype> // for toupper


using namespace std;

struct Order {
    string fruit;
    int quantity;
    double totalCost;
};

struct Fruit {
    string name;
    double price;
};

bool compareByPrice(const string &a, const string &b) {
    size_t posA = a.find_first_of('(');
    size_t posB = b.find_first_of('(');
    double priceA = atof(a.substr(posA + 4, a.find(')') - posA - 4).c_str());
    double priceB = atof(b.substr(posB + 4, b.find(')') - posB - 4).c_str());
    return priceA < priceB;
}

class one {
public:
    void menu1();
};

void clearOrderFile() {
        // Open order.txt in truncation mode to clear its contents
        ofstream clearFile("order.txt", ios::trunc);
        if (!clearFile) {
            cout << "Error clearing file 'order.txt'!" << endl;
        }
        clearFile.close();
    }
 
void editOrder() {
    // Read existing orders from order.txt
    ifstream read("order.txt");
    if (!read) {
        cout << "Unable to open file 'order.txt'!" << endl;
        return;
    }

    vector<Order> orders;
    string line;
    while (getline(read, line)) {
        if (line.find("YOU ORDERED") != string::npos) {
            Order order;
            size_t pos = line.find(" : ");
            order.fruit = line.substr(12, pos - 12); // Extract fruit name
            
            getline(read, line); // Read quantity line
            pos = line.find(": ");
            order.quantity = atoi(line.substr(pos + 2).c_str()); // Convert string to integer
            
            getline(read, line); // Read total cost line
            pos = line.find(": RM ");
            order.totalCost = atof(line.substr(pos + 5).c_str()); // Convert string to double
            
            orders.push_back(order);
        }
    }
    read.close();

    if (orders.empty()) {
        cout << "\n\n\t\t\t\t\t\tNo orders found to edit!" << endl;
        system("PAUSE");
        return;
    }

    // Display current orders
    cout << "\n\n\t\t\t\t\t\t==============================";
    cout << "\n\t\t\t\t\t\t  CURRENT ORDERS";
    cout << "\n\t\t\t\t\t\t==============================\n";
    for (size_t i = 0; i < orders.size(); ++i) {
        cout << "\t\t\t\t\t\t[" << i + 1 << "] " << orders[i].fruit << ": Quantity = " << orders[i].quantity << ", Total Cost = RM " << orders[i].totalCost << endl;
    }

    int choice;
    cout << "\n\tEnter the order number you want to edit (0 to cancel): ";
    while (!(cin >> choice) || choice < 0 || choice > static_cast<int>(orders.size())) {
        cin.clear(); // Clear the error flag set by invalid input
        cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Ignore the invalid input
        cout << "\nInvalid input! Please enter a number between 0 and " << orders.size() << ": ";
    }

    if (choice == 0) {
        return; // Cancel editing
    }

    int editChoice;
    cout << "\n\t[1] Edit Quantity \t[2] Delete Order \n\tEnter your choice (1-2): ";
    while (!(cin >> editChoice) || editChoice < 1 || editChoice > 2) {
        cin.clear(); // Clear the error flag set by invalid input
        cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Ignore the invalid input
        cout << "\nInvalid input! Please enter 1 or 2: ";
    }

    if (editChoice == 1) {
        int newQuantity;
        cout << "\n\tEnter new quantity for " << orders[choice - 1].fruit << ": ";
        while (!(cin >> newQuantity) || newQuantity < 1) {
            cin.clear(); // Clear the error flag set by invalid input
            cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Ignore the invalid input
            cout << "\nInvalid input! Please enter a valid quantity: ";
        }
        double pricePerUnit = orders[choice - 1].totalCost / orders[choice - 1].quantity;
        orders[choice - 1].quantity = newQuantity;
        orders[choice - 1].totalCost = pricePerUnit * newQuantity;
    } else if (editChoice == 2) {
        orders.erase(orders.begin() + choice - 1); // Delete the selected order
    }

    // Save the updated orders back to order.txt
    ofstream write("order.txt", ios::trunc); // Open file in truncation mode to overwrite
    if (!write) {
        cout << "Unable to open file 'order.txt'!" << endl;
        return;
    }

    for (size_t i = 0; i < orders.size(); ++i) {
        write << "YOU ORDERED " << orders[i].fruit << " : RM " << orders[i].totalCost / orders[i].quantity << " \n";
        write << "NUMBER OF FRUITS : " << orders[i].quantity << "\n";
        write << "TOTAL COST : RM " << orders[i].totalCost << "\n\n";
    }
    write.close();

    cout << "\n\n\t\t\t\t\t\tOrder updated successfully!" << endl;
    system("PAUSE");
}

void sortMenu() {
    ifstream read("menu.txt");
    if (!read) {
        cout << "Unable to open file 'menu.txt'!" << endl;
        return;
    }

    vector<string> menuItems;
    string line;
    while (getline(read, line)) {
        if (!line.empty()) {
            menuItems.push_back(line);
        }
    }
    read.close();

    int sortChoice;
    cout << "\n\t[1] Sort by Alphabetical \t[2] Sort by Price \n\tEnter your choice (1-2): ";
    while (!(cin >> sortChoice) || sortChoice < 1 || sortChoice > 2) {
        cin.clear(); // Clear the error flag set by invalid input
        cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Ignore the invalid input
        cout << "\nInvalid input! Please enter 1 or 2: ";
    }

    if (sortChoice == 1) {
        // Sort by alphabetical order using insertion sort
        for (size_t i = 1; i < menuItems.size(); ++i) {
            string key = menuItems[i];
            int j = i - 1;

            while (j >= 0 && menuItems[j] > key) {
                menuItems[j + 1] = menuItems[j];
                j = j - 1;
            }
            menuItems[j + 1] = key;
        }
    } else if (sortChoice == 2) {
        // Sort by price using insertion sort
        for (size_t i = 1; i < menuItems.size(); ++i) {
            string key = menuItems[i];
            size_t startKey = key.find("RM ") + 3;
            size_t endKey = key.find(")", startKey);
            double keyPrice = atof(key.substr(startKey, endKey - startKey).c_str());

            int j = i - 1;
            while (j >= 0) {
                size_t startCurrent = menuItems[j].find("RM ") + 3;
                size_t endCurrent = menuItems[j].find(")", startCurrent);
                double currentPrice = atof(menuItems[j].substr(startCurrent, endCurrent - startCurrent).c_str());

                if (currentPrice > keyPrice) {
                    menuItems[j + 1] = menuItems[j];
                    j = j - 1;
                } else {
                    break;
                }
            }
            menuItems[j + 1] = key;
        }
    }

    ofstream write("menu.txt", ios::trunc);
    if (!write) {
        cout << "Unable to open file 'menu.txt'!" << endl;
        return;
    }

    for (size_t i = 0; i < menuItems.size(); ++i) {
        write << menuItems[i] << "\n";
    }
    write.close();

    cout << "\n\n\t\t\t\t\t\tMenu sorted successfully!" << endl;
    system("PAUSE");
}

void searchMenu() {
    ifstream read("menu.txt");
    if (!read) {
        cout << "Unable to open file 'menu.txt'!" << endl;
        return;
    }

    vector<string> menuItems;
    string line;
    while (getline(read, line)) {
        if (!line.empty()) {
            menuItems.push_back(line);
        }
    }
    read.close();

    int searchChoice;
    cout << "\n\t[1] Search by Fruit Name \t[2] Search by Number \n\tEnter your choice (1-2): ";
    while (!(cin >> searchChoice) || searchChoice < 1 || searchChoice > 2) {
        cin.clear(); // Clear the error flag set by invalid input
        cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Ignore the invalid input
        cout << "\nInvalid input! Please enter 1 or 2: ";
    }

    if (searchChoice == 1) {
        // Search by fruit name
        string searchName;
        cout << "\n\tEnter the fruit name to search: ";
        cin.ignore(); // Ignore newline left in the buffer
        getline(cin, searchName);

        bool found = false;
        cout << "\n\t\t\t\t\t\t===============================";
        cout << "\n\t\t\t\t\t\t   SEARCH RESULTS";
        cout << "\n\t\t\t\t\t\t===============================" << endl;

        for (size_t i = 0; i < menuItems.size(); ++i) {
            if (menuItems[i].find(searchName) != string::npos) {
                cout << "\t\t\t\t\t\t " << menuItems[i] << endl;
                found = true;
            }
        }

        if (!found) {
            cout << "\n\t\t\t\t\t\t===============================";
            cout << "\n\t\t\t\t\t\t   NO MATCH FOUND";
            cout << "\n\t\t\t\t\t\t===============================" << endl;
        }
    } else if (searchChoice == 2) {
        // Search by number
        int searchNumber;
        cout << "\n\tEnter the fruit number to search: ";
        while (!(cin >> searchNumber) || searchNumber < 1 || searchNumber > static_cast<int>(menuItems.size())) {
            cin.clear(); // Clear the error flag set by invalid input
            cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Ignore the invalid input
            cout << "\nInvalid input! Please enter a valid fruit number: ";
        }

        cout << "\n\t\t\t\t\t\t===============================";
        cout << "\n\t\t\t\t\t\t   SEARCH RESULTS";
        cout << "\n\t\t\t\t\t\t===============================" << endl;
        cout << "\t\t\t\t\t\t[" << searchNumber << "] " << menuItems[searchNumber - 1] << endl;
    }
    system("PAUSE");
}

class two : public one {
protected:
    int fruits, ch, s;
    string y, ye;
    ofstream write;

public:
    two() : fruits(0), ch(0), s(0) {} // Constructor to initialize data members

    void show1() {
        menu1();
        menu2();
    }
    
    void menu2() {
        clearOrderFile();
        write.open("order.txt", ios::app); // Open file in append mode
        if (!write) {
            cout << "File cannot open" << endl;
            exit(-1);
        }

        int action;
        do {
            system("cls");
            menu1();

            cout << "\n\n\tENTER YOUR CHOICE (1-7): ";
            while (!(cin >> action) || action < 1 || action > 7) {
                cin.clear(); // Clear the error flag set by invalid input
                cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Ignore the invalid input
                cout << "\nInvalid input! Please enter a number between 1 and 7: ";
            }

            switch (action) {
                case 1:
                    displayAvailableFruits();
                    break;
                case 2:
                    placeOrder();
                    break;
                case 3:
                    viewTotalCost();
                    break;
                case 4:
                    editOrder();
                    break;
                case 5:
                    sortMenu();
                    break;
                case 6:
                    searchMenu();
                    break;
                case 7:
                    cout << "\n\t\t\t\t\tThank you for shopping..." << endl;
                    return; 
            }

        } while (action != 7);

        write.close(); // Close the file after writing all orders
    }

private:
    void placeOrder() {
    ifstream menuFile("menu.txt");
    if (!menuFile) {
        cout << "Unable to open file 'menu.txt'!" << endl;
        return;
    }

    // Read fruits and prices from menu.txt
    vector<string> fruitNames;
    vector<double> fruitPrices;
    string line;

    while (getline(menuFile, line)) {
        size_t pricePos = line.find("(RM ");
        if (pricePos != string::npos) {
            string name = line.substr(0, pricePos - 1);
            string priceStr = line.substr(pricePos + 4, line.find(")") - pricePos - 4);
            double price = atof(priceStr.c_str()); // Use atof to handle decimals correctly
            fruitNames.push_back(name);
            fruitPrices.push_back(price);
        }
    }
    menuFile.close();

    ofstream write("order.txt", ios::app); // Open file in append mode
    if (!write) {
        cout << "Unable to open file 'order.txt'!" << endl;
        return;
    }

    double totalCost = 0;
    string continueOrder;

    do {
        system("cls");
        displayAvailableFruits();

        int ch = 0;
        cin.clear();
        cout << "\n\n\tENTER YOUR ORDER INDEX: ";
        while (!(cin >> ch) || ch < 1 || ch > fruitNames.size()) {
            cin.clear(); // Clear the error flag set by invalid input
            cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Ignore the invalid input
            system("cls");
            displayAvailableFruits();
            cout << "\nInvalid input! Please enter a valid index: ";
        }
        
        

        int fruits = 0;
        cout << "\n\n\tHOW MANY FRUITS YOU WANT: ";
        while (!(cin >> fruits) || fruits < 1) {
            cin.clear(); // Clear the error flag set by invalid input
            cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Ignore the invalid input
            cout << "\nInvalid input! Please enter a valid number of fruits: ";
        }

        int index = ch - 1; // Adjusting for 0-based index
        double price = fruitPrices[index];
        string fruitName = fruitNames[index];

        totalCost += price * fruits;

        // Write order details to order.txt
        write << "YOU ORDERED " << fruitName << " : RM " << price << " \n";
        write << "NUMBER OF FRUITS : " << fruits << "\n";
        write << "TOTAL COST : RM " << price * fruits << "\n\n";

        cout << "\n\n\n\tYOU ORDERED " << fruitName << " \n\tYOUR ORDER HAS BEEN SUCCESSFULLY SAVED " << endl;

        // Prompt to add more fruits
        while (true) {
            cout << "\n\tDO YOU WANT TO ADD MORE FRUITS? (y/n): ";
            cin >> continueOrder;
            if (continueOrder == "y" || continueOrder == "Y") {
                break; // Continue to enter new order
            } else if (continueOrder == "n" || continueOrder == "N") {
                write.close();
                return; // Exit to action menu
            } else {
                cout << "\nInvalid input! Please enter 'y' or 'n'.\n";
            }
        }

    } while (continueOrder == "y" || continueOrder == "Y");

    write.close();
}

void viewTotalCost() {
    ifstream read("order.txt");
    if (!read) {
        cout << "Unable to open file 'order.txt'!" << endl;
        return;
    }

    double total = 0.0;
    string line;
    vector<string> orderDetails; // To store all order details for displaying later

    while (getline(read, line)) {
        if (line.find("YOU ORDERED") != string::npos) {
            // Store the current order line
            string orderLine = line;

            // Read the quantity line
            if (!getline(read, line)) {
                cout << "Error reading quantity line." << endl;
                break;
            }
            string quantityLine = line;

            // Read the total cost line
            if (!getline(read, line)) {
                cout << "Error reading total cost line." << endl;
                break;
            }
            string totalCostLine = line;

            // Extract total cost from the total cost line
            size_t pos = totalCostLine.find(": RM ");
            if (pos != string::npos) {
                double cost = atof(totalCostLine.substr(pos + 5).c_str()); // Use atof to handle decimals correctly
                total += cost;
            } else {
                cout << "Error parsing cost from: " << totalCostLine << endl; // Debug print
            }

            // Store the order details
            orderDetails.push_back(orderLine);
            orderDetails.push_back(quantityLine);
            orderDetails.push_back(totalCostLine);
        }
    }

    read.close();

    // Display all order details
    if (!orderDetails.empty()) {
        cout << "\n\n\t\t\t\t\t\t==============================";
        cout << "\n\t\t\t\t\t\t  YOUR ORDER DETAILS";
        cout << "\n\t\t\t\t\t\t==============================\n";

        for (size_t i = 0; i < orderDetails.size(); ++i) {
            cout << "\t\t\t\t\t\t" << orderDetails[i] << endl;
        }

        // Display total cost
        cout << "\n\n\t\t\t\t\t\t==============================";
        cout << "\n\t\t\t\t\t\tTOTAL BILL IS RM " << total;
        cout << "\n\t\t\t\t\t\t==============================" << endl;

        // Payment confirmation
        string confirmPayment;
        cout << "\n\t\t\t\t\t\tDo you want to pay the bill? (Y/N): ";
        while (true) {
            cin >> confirmPayment;
            if (confirmPayment == "y" || confirmPayment == "Y") {
                // Display payment successful message
                system("cls");
                cout << "\n\t\t\t\t\t\tPayment successful!" << endl;
                
                // Display the bill in order.txt
                ifstream orderFile("order.txt");
                if (orderFile) {
                    cout << "\n\t\t\t\t\t\t==============================";
                    cout << "\n\t\t\t\t\t\t   YOUR BILL";
                    cout << "\n\t\t\t\t\t\t==============================\n";
                    while (getline(orderFile, line)) {
                        cout << "\t\t\t\t\t\t" << line << endl;
                    }
                    cout << "\n\n\t\t\t\t\t\t==============================";
                    cout << "\n\t\t\t\t\t\tTOTAL BILL IS RM " << total;
                    cout << "\n\t\t\t\t\t\t==============================" << endl;
                    orderFile.close();
                } else {
                    cout << "\n\t\t\t\t\t\tUnable to open file 'order.txt' for displaying bill." << endl;
                }

                // Clear the orders in order.txt
                clearOrderFile();
                break;
            } else if (confirmPayment == "n" || confirmPayment == "N") {
                cout << "\n\t\t\t\t\t\tPayment canceled." << endl;
                break;
            } else {
                cout << "\n\t\t\t\t\t\tInvalid input! Please enter 'y' or 'n': ";
            }
        }
    } else {
        cout << "\n\n\t\t\t\t\t\tNo orders found!" << endl;
    }

    system("PAUSE");
}

    void displayAvailableFruits() {
    ifstream menuFile("menu.txt");
    if (!menuFile) {
        cout << "Unable to open file 'menu.txt'!" << endl;
        return;
    }

    string line;
    int index = 1;
    vector<string> fruits;
    system("cls");
    cout << "\n\n\n\t\t\t\t\t\t===============================";
    cout << "\n\t\t\t\t\t\t   AVAILABLE FRUITS MENU";
    cout << "\n\t\t\t\t\t\t===============================" << endl;

    while (getline(menuFile, line)) {
        cout << "\t\t\t\t\t\t[" << index++ << "] " << line << endl;
        fruits.push_back(line);
    }
    menuFile.close();
	system("pause");	
}


    void menu1() {
        cout << "\n\n\n\t\t\t\t\t\t ========== WELCOME TO FRUITS ORDERING SYSTEM ==========\n\n\n\n\n" << endl;
        cout << "\t\t\t\t\t\t ============= MENU OPTIONS =============" << endl;
        cout << "\t\t\t\t\t\t1. Display Available Fruits" << endl;
        cout << "\t\t\t\t\t\t2. Place Order" << endl;
        cout << "\t\t\t\t\t\t3. View Total Cost" << endl;
        cout << "\t\t\t\t\t\t4. Edit Order" << endl;
        cout << "\t\t\t\t\t\t5. Sort Menu" << endl;
        cout << "\t\t\t\t\t\t6. Search Menu" << endl;
        cout << "\t\t\t\t\t\t7. Exit" << endl;
        cout << "\t\t\t\t\t\t=========================================" << endl;
    }
};

class three : public two {
    struct User {
        string username;
        string password;
    };

    vector<User> users;

public:
    void total() {
        string userType;

        while (true) {
            cout << "\n\n\t\t\t\t\t\t\t==============================";
            cout << "\n\t\t\t\t\t\t\tWELCOME TO FRUITS ORDER SYSTEM";
            cout << "\n\t\t\t\t\t\t\t==============================";
            cout << "\n\n\t\t\t\t\t\t\tAre you a Customer (C) or Staff (S)? : ";
            cin >> userType;

            if (userType.length() == 1) {
                userType[0] = toupper(userType[0]);
            }

            if (userType == "C") {
                userLogin();
                break;
            } else if (userType == "S") {
                staffLogin();
                break;
            } else {
                system("cls");
                cout << "\nInvalid choice. Please enter 'C' for Customer or 'S' for Staff.\n";
            }
        }
    }

    void registerUser() {
        User newUser;
        system("cls");
        cout << "\n\n\t\t\t\t\t\t\t==============================";
        cout << "\n\t\t\t\t\t\t\tWELCOME TO FRUITS ORDER SYSTEM";
        cout << "\n\t\t\t\t\t\t\t==============================";
        cout << "\n\t\t\t\t\t\t\tEnter username: ";
        cin >> newUser.username;
        cout << "\n\t\t\t\t\t\t\tEnter password: ";
        cin >> newUser.password;

        saveUsers(newUser); // Save only the new user
        cout << "Registration successful!" << endl;
    }

    bool loginUser() {
        string username, password;
        system("cls");
        cout << "\n\n\t\t\t\t\t\t\t==============================";
        cout << "\n\t\t\t\t\t\t\tWELCOME TO FRUITS ORDER SYSTEM";
        cout << "\n\t\t\t\t\t\t\t==============================";
        cout << "\n\t\t\t\t\t\t\tEnter username: ";
        cin >> username;
        cout << "\n\t\t\t\t\t\t\tEnter password: ";
        cin >> password;

        loadUsers(users);
        for (size_t i = 0; i < users.size(); ++i) {
            if (users[i].username == username && users[i].password == password) {
                return true;
            }
        }
        return false;
    }

    void forgotPassword() {
        string username;
        system("cls");
        cout << "\n\n\t\t\t\t\t\t\t==============================";
        cout << "\n\t\t\t\t\t\t\tWELCOME TO FRUITS ORDER SYSTEM";
        cout << "\n\t\t\t\t\t\t\t==============================";
        cout << "\n\t\t\t\t\t\t\tEnter your username: ";
        cin >> username;

        loadUsers(users);
        for (size_t i = 0; i < users.size(); ++i) {
            if (users[i].username == username) {
                cout << "Your password is: " << users[i].password << endl;
                return;
            }
        }
        cout << "Username not found!" << endl;
    }

    void saveUsers(const User& newUser) {
        ofstream file("users.txt", ios::app); // Open in append mode
        if (file.is_open()) {
            file << newUser.username << "/" << newUser.password << endl;
            file.close();
        } else {	
            cout << "Unable to open file for saving users!" << endl;
        }
    }

    void loadUsers(vector<User>& users) {
        ifstream file("users.txt");
        if (file.is_open()) {
            User user;
            users.clear();
            string line;
            while (getline(file, line)) {
                size_t pos = line.find('/');
                if (pos != string::npos) {
                    user.username = line.substr(0, pos);
                    user.password = line.substr(pos + 1);
                    users.push_back(user);
                }
            }
            file.close();
        } else {
            cout << "Unable to open file for loading users!" << endl;
        }
    }

    void userLogin() {
    int choice;
    while (true) {
        system("cls");
        cout << "\n\n\t\t\t\t\t\t\t==============================";
        cout << "\n\t\t\t\t\t\t\tWELCOME TO FRUITS ORDER SYSTEM";
        cout << "\n\t\t\t\t\t\t\t==============================";
        cout << "\n\t\t\t\t\t\t\t1. Register\n\t\t\t\t\t\t\t2. Login\n\t\t\t\t\t\t\t3. Forgot Password\n\t\t\t\t\t\t\t4. Exit\n\t\t\t\t\t\t\tEnter your choice: ";

        while (!(cin >> choice) || choice < 1 || choice > 4) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            system("cls"); 
            cout << "Invalid choice! Please enter a number between 1 and 4: ";
            cout << "\n\n\t\t\t\t\t\t\t==============================";
	        cout << "\n\t\t\t\t\t\t\tWELCOME TO FRUITS ORDER SYSTEM";
	        cout << "\n\t\t\t\t\t\t\t==============================";
	        cout << "\n\t\t\t\t\t\t\t1. Register\n\t\t\t\t\t\t\t2. Login\n\t\t\t\t\t\t\t3. Forgot Password\n\t\t\t\t\t\t\t4. Exit\n\t\t\t\t\t\t\tEnter your choice: ";
        }

        switch (choice) {
            case 1:
                registerUser();
                break;
            case 2:
                if (loginUser()) {
                    show1();
                    return;
                } else {
                    cout << "Login failed! Please try again." << endl;
                    system("PAUSE");
                }
                break;
            case 3:
                forgotPassword();
                system("PAUSE");
                break;
            case 4:
            	system("cls");
                cout << "\n\t\t\t\t\t Thank you for Shopping";
                total();
            default:
                break;
        }
    }
}

    void staffLogin() {
    string staffId, staffPwd;
    cout << "\n\n\n\n\n\n\n\n\t\t\t\t\t\t\t---------------------";
    cout << "\n\t\t\t\t\t\t\tEnter Staff ID: ";
    cin >> staffId;
    cout << "\t\t\t\t\t\t\t---------------------";

    ifstream staffFile("staff.txt");
    if (!staffFile) {
        cout << "\nUnable to open file 'staff.txt'!" << endl;
        return;
    }

    string storedId, storedPwd;
    bool validId = false;
    while (staffFile >> storedId >> storedPwd) {
        if (staffId == storedId) {
            validId = true;
            break;
        }
    }
    staffFile.close();

    if (!validId) {
        cout << "\nIncorrect ID. Access Denied.\n";
        return;
    }

    cout << "\n\n\n\t\t\t\t\t\t\tPassword: ";
    staffPwd = "";
    char c;
p:
    c = _getch();  // Use _getch() for Windows, change to getch() for other platforms if needed
    cout << "*"; // for printing * instead for password
    if (c != 13) {
        staffPwd = staffPwd + c; // for concatenating the string
        goto p;
    }

    if (staffPwd == storedPwd) {
        cout << "\n\n\t\t\t\t\t\t\tAccess Granted. Welcome to the staff interface\n\n\n";
        system("PAUSE");
        system("CLS");
        staffInterface();
    } else {
        cout << "\nWrong Password. Access Denied.\n";
    }
}

void staffInterface() {
	system("CLS");
    int choice;
    do {
        cout << "\n\n\t\t\t\t\t\t===========================";
        cout << "\n\t\t\t\t\t\tSTAFF INTERFACE";
        cout << "\n\t\t\t\t\t\t===========================";
        cout << "\n\n\t\t\t\t\t\t1. Display all Available Fruits"; 
        cout << "\n\t\t\t\t\t\t2. View All Active Users"; 
        cout << "\n\t\t\t\t\t\t3. View All Orders";
        cout << "\n\t\t\t\t\t\t4. View Staff List"; 
        cout << "\n\t\t\t\t\t\t5. LogOut";
        cout << "\n\n\t\t\t\t\t\tEnter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1:
                displayAllAvailableFruits();
                break;
            case 2:
                viewAllActiveUsers();
                break;
            case 3:
                viewAllOrders(); 
                break;    
            case 4:
                viewStaffList();  // New case for viewing staff list
                break;
            case 5:
            	system("cls");
                cout << "\n\t\t\t\t\t Thank you Admin";
                total();
                break;    
            default:
                cout << "\nInvalid choice. Please try again.\n";
        }
    } while (choice != 5);
}

void viewAllOrders() {
    ifstream read;
    read.open("order.txt");
    if (!read) {
        cout << "File cannot open" << endl;
        exit(-1);
    }

    string line;
    system("CLS");
    cout << "\n\n\n\t\t\t\t\t\t===============================";
    cout << "\n\t\t\t\t\t\t\t   ALL ORDERS";
    cout << "\n\t\t\t\t\t\t===============================" << endl;
    while (getline(read, line)) {
        cout << line << endl;
    }
    read.close();
    
    system("PAUSE");
    system("CLS");
    staffInterface();
}
   
   void viewAllActiveUsers() {
    ifstream usersFile("users.txt");
    if (!usersFile) {
        cout << "Unable to open file 'users.txt'!" << endl;
        return;
    }

    string line;
    system("CLS");
    string usersContent;
    while (getline(usersFile, line)) {
        usersContent += line + "\n\t\t\t\t\t\t";
    }
    usersFile.close();

    // Displaying framed users content
    cout << "\n\n\n\t\t\t\t\t\t===============================";
    cout << "\n\t\t\t\t\t\t   ACTIVE USERS LIST";
    cout << "\n\t\t\t\t\t\t===============================" << endl;
    cout << "\t\t\t\t\t\tUSERNAME / PASSWORD " << endl;
    cout << "\t\t\t\t\t\t" << usersContent;
    cout << "\n\t\t\t\t\t\t===============================" << endl;
    
    system("PAUSE");
    system("CLS");
    staffInterface();
    
}


void viewStaffList() {
    ifstream staffFile("staff.txt");
    if (!staffFile) {
        cout << "Unable to open file 'staff.txt'!" << endl;
        return;
    }

    string line;
    system("CLS");
    cout << "\n\n\t\t\t\t\t\t======== STAFF LIST ========\n";
    cout << "\t\t\t\t\t\tSTAFF ID / PASSWORD " << endl;
    while (getline(staffFile, line)) {
        cout << "\t\t\t\t\t\t" << line << endl;
    }
    cout << "\t\t\t\t\t\t===========================\n";
    staffFile.close();

    int choice;
    cout << "\n\n\t\t\t\t\t\t1. Add New Staff";
    cout << "\n\t\t\t\t\t\t2. Edit Staff";
    cout << "\n\t\t\t\t\t\t3. Back to Main Menu";
    cout << "\n\n\t\t\t\t\t\tEnter your choice: ";
    cin >> choice;

    switch (choice) {
        case 1:
            addNewStaff();
            break;
        case 2:
            editStaff();
            break;
        case 3:
            system("CLS");
            staffInterface();
            break;
        default:
            cout << "\nInvalid choice. Please try again.\n";
            system("PAUSE");
            system("CLS");
            staffInterface();
    }
}

void addNewStaff() {
    string username, password, confirmPassword;

    cout << "\nEnter the username of the new staff: ";
    cin >> username;

    cout << "Enter the password of the new staff: ";
    cin >> password;

    cout << "Confirm the password: ";
    cin >> confirmPassword;

    if (password != confirmPassword) {
        cout << "\nPasswords do not match. Try again.\n";
        addNewStaff();
        return;
    }

    ofstream staffFile("staff.txt", ios::app);
    if (!staffFile) {
        cout << "Unable to open file 'staff.txt'!" << endl;
        return;
    }

    staffFile << username << " " << password << endl;
    staffFile.close();

    cout << "\nNew staff added successfully.\n";
    system("PAUSE");
    system("CLS");
    staffInterface();
}

void editStaff() {
    ifstream staffFile("staff.txt");
    if (!staffFile) {
        cout << "Unable to open file 'staff.txt'!" << endl;
        return;
    }

    string line;
    vector<string> staffList;
    cout << "\n\n\t\t\t\t\t\t======== STAFF LIST ========\n";
    while (getline(staffFile, line)) {
        cout << "\t\t\t\t\t\t" << line << endl;
        staffList.push_back(line);
    }
    cout << "\t\t\t\t\t\t===========================\n";
    staffFile.close();

    string username;
    cout << "\nEnter the username of the staff to edit: ";
    cin >> username;

    bool found = false;
    for (vector<string>::iterator it = staffList.begin(); it != staffList.end(); ++it) {
        if (it->find(username) != string::npos) {
            found = true;
            break;
        }
    }

    if (!found) {
        cout << "\nStaff not found.\n";
        system("PAUSE");
        system("CLS");
        staffInterface();
        return;
    }

    int choice;
    cout << "\n1. Edit Staff Password";
    cout << "\n2. Delete Staff";
    cout << "\n\nEnter your choice: ";
    cin >> choice;

    switch (choice) {
        case 1:
            editStaffPassword(username);
            break;
        case 2:
            deleteStaff(username);
            break;
        default:
            cout << "\nInvalid choice. Please try again.\n";
            system("PAUSE");
            system("CLS");
            staffInterface();
    }
}

void editStaffPassword(const string& username) {
    ifstream staffFile("staff.txt");
    if (!staffFile) {
        cout << "Unable to open file 'staff.txt'!" << endl;
        return;
    }

    string line;
    vector<string> staffList;
    while (getline(staffFile, line)) {
        staffList.push_back(line);
    }
    staffFile.close();

    string newPassword, confirmPassword;
    cout << "\nEnter the new password for " << username << ": ";
    cin >> newPassword;

    cout << "Confirm the new password: ";
    cin >> confirmPassword;

    if (newPassword != confirmPassword) {
        cout << "\nPasswords do not match. Try again.\n";
        editStaffPassword(username);
        return;
    }

    for (vector<string>::iterator it = staffList.begin(); it != staffList.end(); ++it) {
        if (it->find(username) != string::npos) {
            size_t pos = it->find(' ');
            if (pos != string::npos) {
                *it = username + " " + newPassword;
            }
            break;
        }
    }

    ofstream outFile("staff.txt");
    if (!outFile) {
        cout << "Unable to open file 'staff.txt'!" << endl;
        return;
    }
    for (vector<string>::iterator it = staffList.begin(); it != staffList.end(); ++it) {
        outFile << *it << endl;
    }
    outFile.close();

    cout << "\nPassword changed successfully.\n";
    system("PAUSE");
    system("CLS");
    staffInterface();
}

struct DeleteStaffFunctor {
    string username;
    DeleteStaffFunctor(const string& uname) : username(uname) {}
    bool operator()(const string& staff) const {
        return staff.find(username) != string::npos;
    }
};

void deleteStaff(const string& username) {
    ifstream staffFile("staff.txt");
    if (!staffFile) {
        cout << "Unable to open file 'staff.txt'!" << endl;
        return;
    }

    string line;
    vector<string> staffList;
    while (getline(staffFile, line)) {
        staffList.push_back(line);
    }
    staffFile.close();

    char confirmation;
    cout << "\nAre you sure you want to delete the staff " << username << "? (y/n): ";
    cin >> confirmation;

    if (confirmation == 'y' || confirmation == 'Y') {
        vector<string>::iterator it = remove_if(staffList.begin(), staffList.end(), DeleteStaffFunctor(username));
        staffList.erase(it, staffList.end());

        ofstream outFile("staff.txt");
        if (!outFile) {
            cout << "Unable to open file 'staff.txt'!" << endl;
            return;
        }
        for (it = staffList.begin(); it != staffList.end(); ++it) {
            outFile << *it << endl;
        }
        outFile.close();

        cout << "\nStaff deleted successfully.\n";
    } else {
        cout << "\nDeletion canceled.\n";
    }

    system("PAUSE");
    system("CLS");
    staffInterface();
}

void displayAllAvailableFruits() {
    ifstream menuFile("menu.txt");
    if (!menuFile) {
        cout << "Unable to open file 'menu.txt'!" << endl;
        return;
    }

    string line;
    system("CLS");
    int index = 1;
    vector<string> fruits;
    cout << "\n\n\n\t\t\t\t\t\t===============================";
    cout << "\n\t\t\t\t\t\t   AVAILABLE FRUITS MENU";
    cout << "\n\t\t\t\t\t\t===============================" << endl;

    while (getline(menuFile, line)) {
        cout << "\t\t\t\t\t\t[" << index++ << "] " << line << endl;
        fruits.push_back(line);
    }
    menuFile.close();

    cout << "\t\t\t\t\t\t===============================" << endl;
    cout << "\n\t\t\t\t\t\t1. Add New Fruits";
    cout << "\n\t\t\t\t\t\t2. Edit Fruit Price";
    cout << "\n\t\t\t\t\t\t3. Delete Fruits";
    cout << "\n\t\t\t\t\t\t4. Sort Fruits in Alphabat Order";
    cout << "\n\t\t\t\t\t\t5. Search Fruits";
    cout << "\n\t\t\t\t\t\t6. Back to Main Menu";
    cout << "\n\n\t\t\t\t\t\tEnter your choice: ";

    int choice;  // Declare the variable here
    cin >> choice;

    switch (choice) {
        case 1:
            addNewFruits();
            break;
        case 2:
            editFruitPrice();
            break;
        case 3:
            deleteFruit();
            break;
        case 4:
            sortFruits();
            break;
        case 5:
            searchFruits();
            break;
        case 6:
            system("CLS");
            staffInterface();
            break;
        default:
            system("PAUSE");
            system("CLS");

    }

}

void addNewFruits() {
    ofstream menuFile("menu.txt", ios::app);
    if (!menuFile) {
        cout << "Unable to open file 'menu.txt'!" << endl;
        return;
    }

    string newFruit;
    double price;
    
    cout << "\nEnter the name of the new fruit to add: ";
    cin.ignore();  // Ignore the newline character left in the buffer
    getline(cin, newFruit);

    cout << "Enter the price of the new fruit (e.g., 54.80): RM ";
    cin >> price;

    menuFile << newFruit << " (RM " << fixed << setprecision(2) << price << ")" << endl;
    menuFile.close();

    cout << "\nNew fruit added successfully.\n";

    system("PAUSE");
    system("CLS");
    staffInterface();
}

void editFruitPrice() {
    ifstream menuFile("menu.txt");
    if (!menuFile) {
        cout << "Unable to open file 'menu.txt'!" << endl;
        return;
    }

    string line;
    system("CLS");
    vector<string> lines;
    while (getline(menuFile, line)) {
        lines.push_back(line);
    }
    menuFile.close();

    string fruitName;
    cout << "\nEnter the name of the fruit to edit the price: ";
    cin.ignore();
    getline(cin, fruitName);

    bool found = false;
    for (size_t i = 0; i < lines.size(); ++i) {
        if (lines[i].find(fruitName) != string::npos) {
            found = true;
            cout << "\nCurrent entry: " << lines[i] << endl;

            double newPrice;
            cout << "Enter the new price for " << fruitName << " (e.g., 54.80): RM ";
            cin >> newPrice;

            size_t startPos = lines[i].find("(RM");
            if (startPos != string::npos) {
                size_t endPos = lines[i].find(")", startPos);
                lines[i] = lines[i].substr(0, startPos) + "(RM " + to_string(newPrice) + lines[i].substr(endPos);
            }
            break;
        }
    }

    if (found) {
        ofstream outFile("menu.txt");
        for (size_t i = 0; i < lines.size(); ++i) {
            outFile << lines[i] << endl;
        }
        outFile.close();
        cout << "\nPrice updated successfully.\n";
    } else {
        cout << "\nFruit not found in the menu.\n";
    }
    system("PAUSE");
    system("CLS");
    staffInterface();
}

void deleteFruit() {
    ifstream menuFile("menu.txt");
    if (!menuFile) {
        cout << "Unable to open file 'menu.txt'!" << endl;
        return;
    }

    string line;
    system("CLS");
    vector<string> lines;
    while (getline(menuFile, line)) {
        lines.push_back(line);
    }
    menuFile.close();

    string fruitName;
    cout << "\nEnter the name of the fruit to delete: ";
    cin.ignore();
    getline(cin, fruitName);

    bool found = false;
    for (size_t i = 0; i < lines.size(); ++i) {
        if (lines[i].find(fruitName) != string::npos) {
            found = true;
            cout << "\nCurrent entry: " << lines[i] << endl;

            char confirmation;
            cout << "Are you sure you want to delete this fruit? (y/n): ";
            cin >> confirmation;

            if (confirmation == 'y' || confirmation == 'Y') {
                lines.erase(lines.begin() + i);
                cout << "\nFruit deleted successfully.\n";
            } else {
                cout << "\nDeletion cancelled.\n";
            }
            break;
        }
    }

    if (found) {
        ofstream outFile("menu.txt");
        for (size_t i = 0; i < lines.size(); ++i) {
            outFile << lines[i] << endl;
        }
        outFile.close();
    } else {
        cout << "\nFruit not found in the menu.\n";
    }
    system("PAUSE");
    system("CLS");
    staffInterface();
}

void sortFruits() {
    ifstream menuFile("menu.txt");
    if (!menuFile) {
        cout << "Unable to open file 'menu.txt'!" << endl;
        return;
    }

    string line;
    system("CLS");
    vector<string> lines;
    while (getline(menuFile, line)) {
        lines.push_back(line);
    }
    menuFile.close();

    // Insertion sort algorithm
    for (size_t i = 1; i < lines.size(); ++i) {
        string key = lines[i];
        int j = i - 1;

        while (j >= 0 && lines[j] > key) {
            lines[j + 1] = lines[j];
            j--;
        }
        lines[j + 1] = key;
    }

    cout << "\n\n\n\t\t\t\t\t\t===============================";
    cout << "\n\t\t\t\t\t\t   SORTED FRUITS MENU";
    cout << "\n\t\t\t\t\t\t===============================" << endl;
    for (size_t i = 0; i < lines.size(); ++i) {
        cout << "\t\t\t\t\t\t[" << i + 1 << "] " << lines[i] << endl;
    }
    cout << "\t\t\t\t\t\t===============================" << endl;

    system("PAUSE");
    system("CLS");
    staffInterface();
}

void searchFruits() {
    ifstream menuFile("menu.txt");
    if (!menuFile) {
        cout << "Unable to open file 'menu.txt'!" << endl;
        return;
    }

    string line;
    system("CLS");
    vector<string> fruits;
    while (getline(menuFile, line)) {
        fruits.push_back(line);
    }
    menuFile.close();

    cout << "\n\n\n\t\t\t\t\t\t===============================";
    cout << "\n\t\t\t\t\t\t   SEARCH FRUITS MENU";
    cout << "\n\t\t\t\t\t\t===============================" << endl;
    cout << "\n\t\t\t\t\t\t1. Search by Fruit Name";
    cout << "\n\t\t\t\t\t\t2. Search by Number";
    cout << "\n\n\t\t\t\t\t\tEnter your choice: ";

    int choice;
    cin >> choice;

    switch (choice) {
        case 1:
            searchByName(fruits);
            break;
        case 2:
            searchByNumber(fruits);
            break;
        default:
            cout << "\nInvalid choice. Please try again.\n";
    }
    system("PAUSE");
    system("CLS");
    staffInterface();
}

void searchByName(vector<string>& fruits) {
    string fruitName;
    system("CLS");
    cout << "\nEnter the name of the fruit to search: ";
    cin.ignore();
    getline(cin, fruitName);

    sort(fruits.begin(), fruits.end()); // Ensure fruits are sorted
    int left = 0, right = fruits.size() - 1;
    bool found = false;

    while (left <= right) {
        int mid = left + (right - left) / 2;
        if (fruits[mid].find(fruitName) != string::npos) {
            cout << "\nFruit found: " << fruits[mid] << endl;
            found = true;
            break;
        } else if (fruits[mid] < fruitName) {
            left = mid + 1;
        } else {
            right = mid - 1;
        }
    }

    if (!found) {
        cout << "\nInvalid Fruit - Not Found\n";
    }
    system("PAUSE");
    system("CLS");
    staffInterface();
}

void searchByNumber(vector<string>& fruits) {
    int number;
    cout << "\nEnter the number to search: ";
    cin >> number;

    if (number > 0 && number <= fruits.size()) {
        cout << "\nFruit found: " << fruits[number - 1] << endl;
    } else {
        cout << "\nInvalid Number - Not Found\n";
    }
    system("PAUSE");
    system("CLS");
    staffInterface();
}

string to_string(double value) {
    ostringstream os;
    os << fixed << setprecision(2) << value;
    return os.str();
}

};

void cls() {
    // Placeholder for the cls function, which clears the screen
    system("cls");
}

void ccolor(int color) {
    // Placeholder for the ccolor function, which changes the console color
    // This is just a stub. You need to implement it based on your requirements.
}

void pwellcome() {
    // Placeholder for the pwellcome function, which displays a welcome message
    printf("Welcome to Fruit House System\n");
}

void loadingbar(void) {
    for (int i = 15; i <= 100; i += 5) {
        cls();

        printf("\n\n\n\n\n\n\n\t\t\t\t");
        printf("%d %% Loading...\n\n\t\t", i);

        for (int j = 0; j < i; j += 2) {
            ccolor(160 + j);
            printf(" ");
            ccolor(26);
        }
        Sleep(100);
        if (i == 90 || i == 50 || i == 96 || i == 83) {
            Sleep(100);
        }
    }
}

int main() {
    system("title Fruit House System");
    system("mode con: cols=88 lines=30");

    loadingbar();
    cls();
    pwellcome();
    Sleep(300);
    cls();
    
    // Assuming three is a class and ob is an object of that class
    // Placeholder for the three class and its total method
    // three ob;
    // ob.total();
    
    
    three ob;
    ob.total();
    getch();
}
