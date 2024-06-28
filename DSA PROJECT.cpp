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

using namespace std;

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
    ifstream read("order.txt");
    ofstream temp("temp.txt");

    if (!read || !temp) {
        cout << "Unable to open file 'order.txt' or 'temp.txt'!" << endl;
        return;
    }

    string line;
    bool found = false;
    while (getline(read, line)) {
        if (line.find("YOU ORDER") != string::npos) {
            // Display order details for editing
            cout << line << endl;
            if (!getline(read, line)) // Read the next line which contains quantity info
                break;
            cout << line << endl;

            found = true;

            // Prompt for edit or delete
            cout << "\nDo you want to edit/delete this order (edit/delete/no): ";
            string choice;
            cin >> choice;

            if (choice == "edit") {
                // Update quantity
                int newQuantity;
                cout << "Enter new quantity: ";
                cin >> newQuantity;

                // Update the quantity in the order line
                size_t pos = line.find(":");
                stringstream ss;
                ss << line.substr(0, pos + 2) << " " << newQuantity;
                temp << ss.str() << endl; // Write the updated line
                temp << line << endl; // Write the original quantity line
            } else if (choice == "delete") {
                // Skip writing this order to temp file
                if (!getline(read, line)) // Skip the quantity line
                    break;
                continue; // Skip writing this order to temp file
            } else if (choice == "no") {
                temp << line << endl; // Write the original order line
                if (!getline(read, line)) // Read the quantity line
                    break;
                temp << line << endl; // Write the original quantity line
                continue; // Keep the order unchanged in temp file
            } else {
                cout << "Invalid choice, order will remain unchanged." << endl;
                temp << line << endl; // Write the original order line
                if (!getline(read, line)) // Read the quantity line
                    break;
                temp << line << endl; // Write the original quantity line
                continue; // Keep the order unchanged in temp file
            }
        } else {
            temp << line << endl; // Write other lines unchanged
        }
    }

    read.close();
    temp.close(); // Close temp file to ensure all changes are saved

    // Replace order.txt with temp.txt
    if (remove("order.txt") != 0) {
        cout << "Error removing file order.txt!" << endl;
        return;
    }
    if (rename("temp.txt", "order.txt") != 0) {
        cout << "Error renaming file temp.txt to order.txt!" << endl;
        return;
    }

    if (!found) {
        cout << "No orders found to edit." << endl;
    } else {
        cout << "Orders updated successfully." << endl;
    }

    // Pause system to view output
    system("PAUSE");
}

void sortMenu() {
    string fruits[] = {
        "Banana", "Watermelon", "Blueberry", "Blackberry", "Cranberry",
        "Mango", "Grape fruit", "Grapes", "Dragon fruit", "Lemon",
        "Longon", "Mangosteen", "Orange", "Papaya", "Pineapple"
    };
    double prices[] = {
        48.00, 44.00, 58.00, 52.00, 35.00,
        40.00, 42.00, 54.00, 54.80, 39.00,
        52.50, 42.50, 33.50, 32.40, 36.00
    };

    int n = sizeof(fruits) / sizeof(fruits[0]);

    // Perform Selection Sort
    for (int i = 0; i < n - 1; ++i) {
        int minIndex = i;
        for (int j = i + 1; j < n; ++j) {
            if (fruits[j] < fruits[minIndex]) {
                minIndex = j;
            }
        }
        // Swap fruit names
        swap(fruits[i], fruits[minIndex]);
        // Swap prices accordingly
        swap(prices[i], prices[minIndex]);
    }

    // Display sorted menu
    cout << "\n\n\t===========================\t\t\t==============================\t\t\t\t===========================" << endl;
    cout << "\t[1] " << fruits[0] << " (RM." << prices[0] << ")\t\t\t\t[2] " << fruits[1] << " (RM." << prices[1] << ")\t\t\t\t[3] " << fruits[2] << " (RM." << prices[2] << ")\n";
    cout << "\t[4] " << fruits[3] << " (RM." << prices[3] << ")\t\t\t\t[5] " << fruits[4] << " (RM." << prices[4] << ")\t\t\t\t[6] " << fruits[5] << " (RM." << prices[5] << ")\n";
    cout << "\t[7] " << fruits[6] << " (RM." << prices[6] << ")\t\t\t\t[8] " << fruits[7] << " (RM." << prices[7] << ")\t\t\t\t[9] " << fruits[8] << " (RM." << prices[8] << ")\n";
    cout << "\t[10] " << fruits[9] << " (RM." << prices[9] << ")\t\t\t[11] " << fruits[10] << " (RM." << prices[10] << ")\t\t\t[12] " << fruits[11] << " (RM." << prices[11] << ")\n";
    cout << "\t[13] " << fruits[12] << " (RM." << prices[12] << ")\t\t\t[14] " << fruits[13] << " (RM." << prices[13] << ")\t\t\t[15] " << fruits[14] << " (RM." << prices[14] << ")\n";
    cout << "\t===========================\t\t\t==============================\t\t\t\t===========================" << endl;
}

void searchMenu() {
    string fruits[] = {
        "Banana", "Watermelon", "Blueberry", "Blackberry", "Cranberry",
        "Mango", "Grape fruit", "Grapes", "Dragon fruit", "Lemon",
        "Longon", "Mangosteen", "Orange", "Papaya", "Pineapple"
    };
    double prices[] = {
        48.00, 44.00, 58.00, 52.00, 35.00,
        40.00, 42.00, 54.00, 54.80, 39.00,
        52.50, 42.50, 33.50, 32.40, 36.00
    };

    int n = sizeof(fruits) / sizeof(fruits[0]);

    string searchName;
    cout << "\nEnter the fruit name to search: ";
    cin.ignore(); // Ignore newline character left in the buffer
    getline(cin, searchName);

    // Perform Binary Search
    int low = 0, high = n - 1;
    while (low <= high) {
        int mid = low + (high - low) / 2;
        if (fruits[mid] == searchName) {
            // Found the fruit, display its details
            cout << "\n\n\t===========================\t\t\t==============================\t\t\t\t===========================" << endl;
            cout << "\tFruit: " << fruits[mid] << " (RM." << prices[mid] << ")" << endl;
            cout << "\t===========================\t\t\t==============================\t\t\t\t===========================" << endl;
            return;
        } else if (fruits[mid] < searchName) {
            low = mid + 1;
        } else {
            high = mid - 1;
        }
    }

    // If fruit is not found
    cout << "\n\n\t\t\t\t\t\t" << searchName << " not found in the menu!" << endl;
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
            cout << "\n\n\t\t\t\t\t\t ========== WELCOME TO FRUITS ORDERING SYSTEM ==========" << endl;
            cout << "\n\n\t\t\t\t\t\t\t       =====START YOUR ORDER=====" << endl;
            cout << "\n\n\n\t===========================\t\t\t==============================\t\t\t\t===========================" << endl;
            cout << "\t[1] Banana (RM.48.00)\t\t\t\t[2] Watermelon (RM.44.00)\t\t\t\t[3] Blueberry (RM.58.00)\n\t[4] Blackberry (RM.52.00)\t\t\t[5] Cranberry (RM.35.00)\t\t\t\t[6] Mango (RM.40.00)\n\t[7] Grape fruit (RM.42.00)\t\t\t[8] Grapes (RM.54.00)\t\t\t\t\t[9] Dragon fruit (RM.54.80)\n\t[10] Lemon (RM.39.00)\t\t\t\t[11] Longon (RM.52.50)\t\t\t\t\t[12] Mangosteen (RM.42.50)\n\t[13] Orange (RM.33.50)\t\t\t\t[14] Papaya (RM.32.40)\t\t\t\t\t[15] Pineapple (RM.36.00)\n\t===========================\t\t\t==============================\t\t\t\t===========================" << endl;
            cout << "\n\t=======================================================================================================================================" << endl;
            cout << "\n\n\t[1] Buy Fruits \t\t[2] View total cost \t\t[3] Edit \t\t[4] Sorting \t\t[5] Searching \t\t[6] Exit ";
            cout << "\n\t=======================================================================================================================================" << endl;

            cout << "\n\n\tENTER YOUR CHOICE (1-6): ";
            while (!(cin >> action) || action < 1 || action > 6) {
                cin.clear(); // Clear the error flag set by invalid input
                cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Ignore the invalid input
                cout << "\nInvalid input! Please enter a number between 1 and 6: ";
            }

            switch (action) {
                case 1:
                    placeOrder();
                    break;
                case 2:
                    viewTotalCost();
                    break;
                case 3:
                	editOrder();
                	break;
                	case 4:
                sortMenu();
                break;
            case 5:
                searchMenu();
                break;
                case 6:
                    cout << "\n\t\t\t\t\t Thank you for Shopping";
                    exit(0);
            }

        } while (action != 6);

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
    vector<string> orders; // To store all orders for displaying later

    while (getline(read, line)) {
        // Assuming each line contains an order and its cost in format "YOU ORDER <fruit> : <price>"
        if (line.find("YOU ORDER") != string::npos) {
            // Extract price from line
            size_t pos = line.find(":");
            string priceStr = line.substr(pos + 2); // Start after ": "
            double price = atof(priceStr.c_str()); // Convert string to double

            // Extract fruit name
            string fruitLine = line.substr(10, pos - 10); // Extract "YOU ORDER <fruit>"
            orders.push_back(fruitLine);

            // Extract quantity from the next line
            getline(read, line); // Read the next line which contains quantity info
            pos = line.find(":");
            string quantityStr = line.substr(pos + 2); // Start after ": "
            int quantity = atoi(quantityStr.c_str()); // Convert string to integer

            // Calculate total cost for this order considering quantity
            total += price * quantity;
        }
    }

    read.close();

    // Display all orders with quantities
    if (!orders.empty()) {
        cout << "\n\n\t\t\t\t\t\t==============================";
        cout << "\n\t\t\t\t\t\t  YOUR ORDER DETAILS";
        cout << "\n\t\t\t\t\t\t==============================\n";

        for (vector<string>::iterator it = orders.begin(); it != orders.end(); ++it) {
            cout << "\n\t\t\t\t\t\t" << *it << endl;

            // Find corresponding quantity line
            string quantityLine;
            for (vector<string>::iterator jt = it + 1; jt != orders.end(); ++jt) {
                if (jt->find("NUMBER OF FRUITS IS : ") != string::npos) {
                    quantityLine = *jt;
                    break;
                }
            }
            if (!quantityLine.empty()) {
                cout << "\t\t\t\t\t\t" << quantityLine << endl;
            }
        }
    } else {
        cout << "\n\n\t\t\t\t\t\tNo orders found!" << endl;
    }

    // Display total cost
    cout << "\n\n\t\t\t\t\t\t==============================";
    cout << "\n\t\t\t\t\t\tTOTAL BILL IS RM." << total;
    cout << "\n\t\t\t\t\t\t==============================" << endl;

    system("PAUSE");
}


    void menu1() {
        cout << "\n\n\n\t\t\t\t\t\t ========== WELCOME TO FRUITS ORDERING SYSTEM ==========" << endl;
        cout << "\n\n\t\t\t\t\t\t\t       =====START YOUR ORDER=====" << endl;
        cout << "\n\n\n\t===========================\t\t\t==============================\t\t\t\t===========================" << endl;
        cout << "\t[1] Banana (RM.48.00)\t\t\t\t[2] Watermelon (RM.44.00)\t\t\t\t[3] Blueberry (RM.58.00)\n\t[4] Blackberry (RM.52.00)\t\t\t[5] Cranberry (RM.35.00)\t\t\t\t[6] Mango (RM.40.00)\n\t[7] Grape fruit (RM.42.00)\t\t\t[8] Grapes (RM.54.00)\t\t\t\t\t[9] Dragon fruit (RM.54.80)\n\t[10] Lemon (RM.39.00)\t\t\t\t[11] Longon (RM.52.50)\t\t\t\t\t[12] Mangosteen (RM.42.50)\n\t[13] Orange (RM.33.50)\t\t\t\t[14] Papaya (RM.32.40)\t\t\t\t\t[15] Pineapple (RM.36.00)\n\t===========================\t\t\t==============================\t\t\t\t===========================" << endl;
        cout << "\n\t=======================================================================================================================================" << endl;
        cout << "\n\n\t[1] Buy Fruits \t\t[2] View total cost \t\t[3] Edit \t\t[4] Sorting \t\t[5] Searching \t\t[6] Exit ";
        cout << "\n\t=======================================================================================================================================" << endl;
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
                cout << "\n\t\t\t\t\t Thank you for Shopping";
                exit(0);
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
