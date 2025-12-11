#include <iostream>
#include <fstream>
#include <string>
using namespace std;

class temp {
    string username, email, password;
    string searchName, searchPass, searchEmail;
    string mobile_number;          // use string for easier IO/parsing
    fstream file;
public:
    void login();
    void signup();
    void forgotPassword();
};

int main() {
    char choice;
    cout << "1-Login\n";
    cout << "2-Sign Up\n";
    cout << "3-Forgot Password\n";
    cout << "4-Exit\n";
    cout << "Enter your choice: ";
    cin >> choice;
    cin.ignore(); // flush newline

    temp obj;
    if (choice == '1') {
        obj.login();
    } else if (choice == '2') {
        obj.signup();
    } else if (choice == '3') {
        obj.forgotPassword();
    } else if (choice == '4') {
        return 0;
    } else {
        cout << "Invalid Input\n";
    }
    return 0;
}

void temp::signup() {
    cout << "Enter Name :: " << endl;
    getline(cin, username);
    cout << "Enter Email : " << endl;
    getline(cin, email);
    cout << "Enter Password : " << endl;
    getline(cin, password);
    cout << "Enter Phone : " << endl;
    getline(cin, mobile_number);

    file.open("loginData.txt", ios::out | ios::app);
    if (!file.is_open()) {
        cerr << "Error opening file for signup.\n";
        return;
    }
    // Use consistent delimiter: username*email*password*mobile\n
    file << username << "*" << email << "*" << password << "*" << mobile_number << "\n";
    file.close();
    cout << "Signup complete.\n";
}

void temp::login() {
    cout << "--------LOGIN--------" << endl;
    cout << "Enter Username : " << endl;
    getline(cin, searchName);
    cout << "Enter Password : " << endl;
    getline(cin, searchPass);

    file.open("loginData.txt", ios::in);
    if (!file.is_open()) {
        cerr << "Could not open loginData.txt\n";
        return;
    }

    bool found = false;
    // Read record-by-record matching the exact delimiter pattern
    while (getline(file, username, '*')) {
        getline(file, email, '*');
        getline(file, password, '*');
        getline(file, mobile_number); // read till end of line

        if (username == searchName) {
            found = true;
            if (password == searchPass) {
                cout << "Login Successful...!\n";
                cout << "Username : " << username << endl;
                cout << "Email : " << email << endl;
                cout << "Phone : " << mobile_number << endl;
            } else {
                cout << "Password Incorrect..Try Again\n";
            }
            break; // we found the user — stop reading further
        }
    }

    if (!found) {
        cout << "Username not found...\n";
    }

    file.close();
}

void temp::forgotPassword() {
    cout << "--------FORGOT PASSWORD--------" << endl;
    cout << "Enter Username : " << endl;
    getline(cin, searchName);
    cout << "Enter Email : " << endl;
    getline(cin, searchEmail);

    file.open("loginData.txt", ios::in);
    if (!file.is_open()) {
        cerr << "Could not open loginData.txt\n";
        return;
    }

    bool found = false;
    while (getline(file, username, '*')) {
        getline(file, email, '*');
        getline(file, password, '*');
        getline(file, mobile_number); // rest of line

        if (username == searchName && email == searchEmail) {
            found = true;
            cout << "Account Found...!" << endl;
            cout << "Your Password : " << password << endl;
            break;
        }
    }

    if (!found) {
        cout << "No matching account found.\n";
    }

    file.close();
}
