#include <iostream>
#include <fstream>
using namespace std;

class temp
{
    string userName, Email, Password;
    string searchName, searchPass, searchEmail;
    fstream file;

public:
    void login();
    void signup();
    void forgot();

} obj;
int main()
{
    char choice;
    cout << "1- login " << "\n";
    cout << "2- Sign-Up " << "\n";
    cout << "3- Forgot Password " << "\n";
    cout << "4- Exit " << "\n";
    cin >> choice;
    switch (choice)
    {
    case '1':
        obj.login();
        break;

    case '2':
        obj.signup();
        break;

    case '3':
        obj.forgot();
        break;

    case '4':
        return 0;
        break;

    default:
        cout << "wrong input";
    }
    return 0;
}
void temp ::signup()
{
    cin.ignore();
    cout << "\n enter your username :: ";
    getline(cin, userName);
    cout << "\n ener your email address :: ";
    getline(cin, Email);
    cout << "\n enter the password :: ";
    getline(cin, Password);

    file.open("loginData.txt", ios ::out | ios ::app);
    file << userName << "*" << Email << "*" << Password << endl;
    file.close();
}

void temp ::login()
{
    cin.ignore();
    string searchName, searchPass;
    cout << "------------login------------" << endl;
    cout << "\n enter your username :: ";
    getline(cin, searchName);
    cout << "\n enter your password :: ";
    getline(cin, searchPass);

    file.open("loginData.txt", ios ::in);
    getline(file, userName, '*');
    getline(file, Email, '*');
    getline(file, Password, '\n');
    while (!file.eof())
    {
        if (userName == searchName)
        {
            if (Password == searchPass)
            {
                cout << "login sucessful!" << endl;
            }
            else
                cout << "incorrect password" << endl;
        }
        getline(file, userName, '*');
        getline(file, Email, '*');
        getline(file, Password, '\n');
    }
    file.close();
}

void temp::forgot()
{
    cin.ignore();
    cout << "Enter your username: ";
    getline(cin, userName);
    cout << "Enter your Email: ";
    getline(cin, Email);

    bool found = false;
    string line, uname, mail, pass;
    ifstream infile("loginData.txt");
    ofstream outfile("temp.txt");
    while (getline(infile, line))
    {
        size_t pos1 = line.find('*');
        size_t pos2 = line.find('*', pos1 + 1);
        if (pos1 != string::npos && pos2 != string::npos)
        {
            uname = line.substr(0, pos1);
            mail = line.substr(pos1 + 1, pos2 - pos1 - 1);
            pass = line.substr(pos2 + 1);

            if (uname == userName && mail == Email)
            {
                found = true;
                cout << "Account found!\n";
                cout << "Your password: " << pass << endl;
                cout << "Do you want to change your password? (y/n): ";
                char ch;
                cin >> ch;
                cin.ignore();
                if (ch == 'y' || ch == 'Y')
                {
                    cout << "Enter new password: ";
                    string newPass;
                    getline(cin, newPass);
                    outfile << uname << "*" << mail << "*" << newPass << endl;
                    cout << "Password changed successfully!\n";
                }
                else
                {
                    outfile << line << endl;
                }
            }
            else
            {
                outfile << line << endl;
            }
        }
    }
    infile.close();
    outfile.close();

    // Replace old file with updated file
    remove("loginData.txt");
    rename("temp.txt", "loginData.txt");

    if (!found)
        cout << "Account not found!\n";
}
