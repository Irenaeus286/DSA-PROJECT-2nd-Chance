#include <iostream>
#include <string>
#include <fstream>
#include <conio.h>
#include <unistd.h>
#include <windows.h>
#include <limits>
#include <vector>
#include <algorithm>
#include <cstdlib> 
#include <sstream>  
#include <cstring>
#include <string>
#include <cstdlib>
using namespace std;

struct Order {
    string fruit;
    int quantity;
    double totalCost;
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
        if (line.find("YOU ORDER") != string::npos) {
            Order order;
            size_t pos = line.find(":");
            order.fruit = line.substr(9, pos - 9 - 1); // Extract fruit name
            
            getline(read, line); // Read quantity line
            pos = line.find(":");
            order.quantity = atoi(line.substr(pos + 2).c_str()); // Convert string to integer
            
            getline(read, line); // Read total cost line
            pos = line.find(":");
            order.totalCost = atof(line.substr(pos + 2).c_str()); // Convert string to double
            
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
        cout << "\t\t\t\t\t\t[" << i + 1 << "] " << orders[i].fruit << ": Quantity = " << orders[i].quantity << ", Total Cost = RM." << orders[i].totalCost << endl;
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
        write << "YOU ORDER " << orders[i].fruit << " : " << orders[i].totalCost / orders[i].quantity << " \n";
        write << "NUMBER OF FRUITS IS : " << orders[i].quantity << "\n";
        write << "TOTAL COST IS : " << orders[i].totalCost << "\n\n";
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
    cout << "\n\t[1] Sort by Number \t[2] Sort by Price \n\tEnter your choice (1-2): ";
    while (!(cin >> sortChoice) || sortChoice < 1 || sortChoice > 2) {
        cin.clear(); // Clear the error flag set by invalid input
        cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Ignore the invalid input
        cout << "\nInvalid input! Please enter 1 or 2: ";
    }

    if (sortChoice == 1) {
        // Sort by number
        for (size_t i = 1; i < menuItems.size(); ++i) {
            string key = menuItems[i];
            int keyNumber = atoi(key.substr(1, key.find(']') - 1).c_str());
            int j = i - 1;
            while (j >= 0) {
                int currentNumber = atoi(menuItems[j].substr(1, menuItems[j].find(']') - 1).c_str());
                if (currentNumber > keyNumber) {
                    menuItems[j + 1] = menuItems[j];
                    j = j - 1;
                } else {
                    break;
                }
            }
            menuItems[j + 1] = key;
        }
    } else if (sortChoice == 2) {
        // Sort by price using a basic sorting algorithm
        for (size_t i = 0; i < menuItems.size(); ++i) {
            for (size_t j = i + 1; j < menuItems.size(); ++j) {
                size_t startA = menuItems[i].find("RM.") + 3;
                size_t endA = menuItems[i].find(")", startA);
                double priceA = atof(menuItems[i].substr(startA, endA - startA).c_str());
                
                size_t startB = menuItems[j].find("RM.") + 3;
                size_t endB = menuItems[j].find(")", startB);
                double priceB = atof(menuItems[j].substr(startB, endB - startB).c_str());

                if (priceA > priceB) {
                    swap(menuItems[i], menuItems[j]);
                }
            }
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
    	ofstream write("order.txt", ios::app); // Open file in append mode
    if (!write) {
        cout << "Unable to open file 'order.txt'!" << endl;
        return;
    }
        do {
            system("cls");
            menu1();

            cout << "\n\n\tENTER YOUR ORDER (1-15): ";
            while (!(cin >> ch) || ch < 1 || ch > 15) {
                cin.clear(); // Clear the error flag set by invalid input
                cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Ignore the invalid input
                system("cls");
                menu1();
                cout << "\nInvalid input! Please enter a number between 1 and 15: ";
            }

            cout << "\n\n\tHOW MANY FRUITS YOU WANT: ";
            while (!(cin >> fruits) || fruits < 1) {
                cin.clear(); // Clear the error flag set by invalid input
                cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Ignore the invalid input
                cout << "\nInvalid input! Please enter a valid number of fruits: ";
            }

            int price = 0;
            string fruitName;
            switch (ch) {
                case 1:
                    price = 48;
                    fruitName = "Banana";
                    break;
                case 2:
                    price = 44;
                    fruitName = "Watermelon";
                    break;
                case 3:
                    price = 58;
                    fruitName = "Blueberry";
                    break;
                case 4:
                    price = 52;
                    fruitName = "Blackberry";
                    break;
                case 5:
                    price = 35;
                    fruitName = "Cranberry";
                    break;
                case 6:
                    price = 40;
                    fruitName = "Mango";
                    break;
                case 7:
                    price = 42;
                    fruitName = "Grape fruit";
                    break;
                case 8:
                    price = 54;
                    fruitName = "Grapes";
                    break;
                case 9:
                    price = 54.8;
                    fruitName = "Dragon fruit";
                    break;
                case 10:
                    price = 39;
                    fruitName = "Lemon";
                    break;
                case 11:
                    price = 52.5;
                    fruitName = "Longon";
                    break;
                case 12:
                    price = 42.5;
                    fruitName = "Mangosteen";
                    break;
                case 13:
                    price = 33.5;
                    fruitName = "Orange";
                    break;
                case 14:
                    price = 32.4;
                    fruitName = "Papaya";
                    break;
                case 15:
                    price = 36;
                    fruitName = "Pineapple";
                    break;
            }

            s += price * fruits;

            // Write order details to order.txt
            write << "YOU ORDER " << fruitName << " : " << price << " \n";
        write << "NUMBER OF FRUITS IS : " << fruits << "\n";
        write << "TOTAL COST IS : " << price * fruits << "\n\n";

        cout << "\n\n\n\tYOU ORDER " << fruitName << " \n\tYOUR ORDER SUCCESSFULLY SAVED " << endl;

        // Prompt to add more fruits
        while (true) {
            cout << "\n\tDO YOU WANT TO ADD MORE FRUITS? (y/n): ";
            cin >> ye;
            if (ye == "y" || ye == "Y") {
                break; // Continue to enter new order
            } else if (ye == "n" || ye == "N") {
                return; // Exit to action menu
            } else {
                cout << "\nInvalid input! Please enter 'y' or 'n'.\n";
            }
        }

    } while (ye == "y" || ye == "Y");

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
        if (line.find("YOU ORDER") != string::npos) {
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

            // Extract price from the order line
            size_t pos = orderLine.find(":");
            double price = atof(orderLine.substr(pos + 2).c_str()); // Convert string to double

            // Extract quantity from the quantity line
            pos = quantityLine.find(":");
            int quantity = atoi(quantityLine.substr(pos + 2).c_str()); // Convert string to integer

            // Extract total cost from the total cost line
            pos = totalCostLine.find(":");
            double cost = atof(totalCostLine.substr(pos + 2).c_str()); // Convert string to double

            // Add to total
            total += cost;

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
        cout << "\n\t\t\t\t\t\tTOTAL BILL IS RM." << total;
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
                    string line;
                    while (getline(orderFile, line)) {
                        cout << "\t\t\t\t\t\t" << line << endl;
                    }
                    cout << "\n\n\t\t\t\t\t\t==============================";
        			cout << "\n\t\t\t\t\t\tTOTAL BILL IS RM." << total;
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
    string menuContent;
    while (getline(menuFile, line)) {
        menuContent += line + "\n\t\t\t\t\t\t";
    }
    menuFile.close();

    // Displaying framed menu content
    cout << "\n\n\n\t\t\t\t\t\t===============================";
    cout << "\n\t\t\t\t\t\t   AVAILABLE FRUITS MENU";
    cout << "\n\t\t\t\t\t\t===============================" << endl;
    cout << "\t\t\t\t\t\t" << menuContent;
    cout << "\n\t\t\t\t\t\t===============================" << endl;

    system("PAUSE");	
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

        if (staffId != "007") {
            cout << "\nIncorrect ID. Access Denied.\n";
            return;
        }

        cout << "\n\n\n\t\t\t\t\t\t\tPassword: ";
        staffPwd = "";
        char c;
    p:
        c = getch();
        cout << "*"; //for printing * instead for password
        if (c != 13) {
            staffPwd = staffPwd + c; //for concatenating the string
            goto p;
        }

        if (staffPwd == "2806") {
            cout << "\n\n\t\t\t\t\t\t\tAccess Granted. Welcome to the staff interface\n\n\n";
            system("PAUSE");
            system("CLS");
            staffInterface();
        } else {
            cout << "\nWrong Password. Access Denied.\n";
        }
    }

    void staffInterface() {
        int choice;
        do {
            cout << "\n\n\t\t\t\t\t\t===========================";
            cout << "\n\t\t\t\t\t\tSTAFF INTERFACE";
            cout << "\n\t\t\t\t\t\t===========================";
            cout << "\n\n\t\t\t\t\t\t1. View All Orders";
            cout << "\n\t\t\t\t\t\t2. View Generated Bills";
            cout << "\n\t\t\t\t\t\t3. Exit";
            cout << "\n\n\t\t\t\t\t\tEnter your choice: ";
            cin >> choice;

            switch (choice) {
                case 1:
                    viewAllOrders();
                    break;
                case 2:
                    viewGeneratedBills();
                    break;
                case 3:
                    cout << "\nExiting Staff Interface...\n";
                    break;
                default:
                    cout << "\nInvalid choice. Please try again.\n";
            }
        } while (choice != 3);
    }

    void viewAllOrders() {
        ifstream read;
        read.open("order.txt");
        if (!read) {
            cout << "File cannot open" << endl;
            exit(-1);
        }

        string line;
        cout << "\n\n\t\t\t\t\t\t======== ALL ORDERS ========\n";
        while (getline(read, line)) {
            cout << line << endl;
        }
        read.close();
    }

    void viewGeneratedBills() {
        ifstream read;
        read.open("bills.txt");
        if (!read) {
            cout << "File cannot open" << endl;
            exit(-1);
        }

        string line;
        cout << "\n\n\t\t\t\t\t\t======== GENERATED BILLS ========";
        while (getline(read, line)) {
            cout << line << endl;
        }
        read.close();
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
