#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <functional>
using namespace std;

const string DATA_FILE = "users.txt";

string getHash(string password)
{
    hash<string> makeHash;
    return to_string(makeHash(password));
}

bool checkUsername(string username)
{
    ifstream input(DATA_FILE);
    string line;

    while (getline(input, line))
    {
        string user;
        string pass;

        stringstream data(line);
        getline(data, user, ':');
        getline(data, pass, ':');

        if (user == username)
            return true;
    }

    return false;
}

string registerAccount(string username, string password)
{
    if (username.empty() || password.empty())
        return "Registration failed: Username and password cannot be empty.";

    if (password.size() < 6)
        return "Registration failed: Password must contain at least 6 characters.";

    if (checkUsername(username))
        return "Registration failed: Username already exists.";

    ofstream output(DATA_FILE, ios::app);
    output << username << ":" << getHash(password) << endl;
    output.close();

    return "Registration successful.";
}

string checkLogin(string username, string password)
{
    if (username.empty() || password.empty())
        return "Login failed: Username and password cannot be empty.";

    ifstream input(DATA_FILE);
    string line;

    while (getline(input, line))
    {
        string user;
        string pass;

        stringstream data(line);
        getline(data, user, ':');
        getline(data, pass, ':');

        if (user == username)
        {
            if (pass == getHash(password))
                return "Login successful.";

            return "Login failed: Invalid username or password.";
        }
    }

    return "Login failed: Invalid username or password.";
}

int main()
{
    ofstream reset(DATA_FILE);
    reset.close();

    int total;
    cin >> total;

    for (int i = 0; i < total; i++)
    {
        string command;
        string username;
        string password;

        cin >> command >> username >> password;

        if (command == "REGISTER")
        {
            cout << registerAccount(username, password) << endl;
        }
        else if (command == "LOGIN")
        {
            cout << checkLogin(username, password) << endl;
        }
        else
        {
            cout << "Invalid operation." << endl;
        }
    }

    return 0;
}
