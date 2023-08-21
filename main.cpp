#include <iostream>
#include <windows.h>
#include <fstream>
#include <conio.h>
#include <vector>
#include <iomanip>
#include <stdio.h>

using namespace std;

struct User {
    int id;
    string username, password;
};

struct Person {
    int id;
    string firstname;
    string lastname;
    string phone;
    string email;
    string address;
};

enum DataType {
    firstname,
    lastname,
    email,
    phone,
    address,
    fullname
} ;

const string ADDRESSBOOK_FILE = "addressBook.txt";
const string USERS_FILE = "users.txt";

void displayPausePrompt();
void displayRecordByTableIndex(const Person person);
bool searchTableByString(string stringToSearch, DataType personsDataType, vector <Person>& persons);
string getLineString();
char getLineChar();
bool isNumber(string s);
int getLineInt();
char displayMainMenu();
string makeFileString(int idLoggedUser, const Person& persons);
void addNewPerson(vector <Person>& persons);
void displayAllPersons(vector <Person>& persons);
void loadDataFromTextFile(int idLoggedUser, vector <Person>& persons);
bool displayYesNoChoice();
string removeSpacesAndDashesFromString(string stringToClear);
void saveDataFile(int idLoggedUser, const vector <Person>& persons);
void deletePerson(int idLoggedUser, vector <Person>& persons);
char displayEditSubMenu();
void modifyPerson(int idLoggedUser, vector <Person>& persons);
int manageMainMenu(int idLoggedUser, vector <Person>& persons, vector <User>& users);
int loginUser(vector <User>& users);
bool checkIfUserNameAlreadyExist(string userName, vector <User>& users);
bool checkIfUserDataEmpty(string userData);
void registerUser(vector <User>& users);
void changeUserPassword(int idLoggedUser, vector <User>& users);
void loadUserDataFromTextFile(vector <User>& users);
void rewriteUsersFile(const vector <User>& users);
void manageUsersMenu(vector <Person>& persons, vector <User>& users);

int main() {

    vector <Person> persons;
    vector <User> users;

    manageUsersMenu(persons, users);

    return 0;
}

void displayPausePrompt() {
    cout << "Press any key to continue ...";
    getchar();
}

void displayRecordByTableIndex(const Person person) {
    cout << "(" << person.id << "). " << person.firstname << " " << person.lastname << ", " << person.email << ", " << person.phone << ", " << person.address <<  endl;
}

bool searchTableByString(string stringToSearch, DataType personsDataType, vector <Person>& persons) {
    bool searchResult = false;

    for(Person person : persons) {
        if (personsDataType == DataType(firstname)) {
            if (person.firstname.find(stringToSearch) != string::npos) {
                displayRecordByTableIndex(person);
                searchResult = true;
            }
        } else if (personsDataType == DataType(lastname)) {
            if (person.lastname.find(stringToSearch) != string::npos) {
                displayRecordByTableIndex(person);
                searchResult = true;
            }
        } else if (personsDataType == DataType(email)) {
            if (person.email == stringToSearch) {
                displayRecordByTableIndex(person);
                searchResult = true;
            }
        } else if (personsDataType == DataType(phone)) {
            if (person.phone == stringToSearch) {
                displayRecordByTableIndex(person);
                searchResult = true;
            }

        } else if (personsDataType == DataType(fullname)) {
            string fname = "";
            fname.append(person.firstname);
            fname.append(" ");
            fname.append(person.lastname);

            if (fname == stringToSearch) {
                displayRecordByTableIndex(person);
                searchResult = true;
            }
        }
    }

    return searchResult;
}

string getLineString() {
    string dataString;

    cin.sync();
    getline(cin, dataString);

    return dataString;
}

bool isNumber(string textNumber) {

    if(textNumber.size() == 0) {
        return false;
    }
    for(size_t i = 0; i < textNumber.size(); ++i) {
        if(!(textNumber[i] >= '0' && textNumber[i] <= '9')) {
            return false;
        }
    }
    return true;
}

int getLineInt() {
    string dataString;

    while(true) {
        dataString = getLineString();

        if (isNumber(dataString)) {
            break;
        } else {
            cout << "Only digits are allowed, type a digit : ";
        }
    }
    return stoi(dataString);
}

char getLineChar() {
    string dataString;
    char dataChar;

    cin.sync();

    while(true) {
        getline(cin, dataString);

        if(dataString.length() == 1) {
            dataChar = dataString[0];
            break;
        } else {
            cout << "Enter single character only!" << endl;
            break;
        }
    }
    return dataChar;
}

char displayMainMenu() {
    char menuSelection;

    system("cls");
    cout << ">> ADDRESS BOOK MAIN MENU <<" << endl;
    cout << "-----------------------------" << endl;
    cout << "1. Add new person" << endl;
    cout << "2. Search by firstname" << endl;
    cout << "3. Search by lastname" << endl;
    cout << "4. List all persons" << endl;
    cout << "5. Delete person" << endl;
    cout << "6. Modify person" << endl;
    cout << "7. Change user password" << endl;
    cout << "9. Logout" << endl;
    cout << "-----------------------------" << endl;
    cout << "Enter your choice (1-7,9): ";

    menuSelection = getLineChar();
    return menuSelection;
}

void addNewPerson(int idLoggedUser, vector <Person>& persons) {
    ofstream dataFile;
    Person newPersonToAdd;
    string fname = "";

    newPersonToAdd.id = !persons.size() ? 1 : persons.back().id + 1;

    cout << "Input firstname: ";
    newPersonToAdd.firstname = getLineString();
    cout << "Input lastname: ";
    newPersonToAdd.lastname = getLineString();
    if (persons.size() > 0) {
        fname.append(newPersonToAdd.firstname);
        fname.append(" ");
        fname.append(newPersonToAdd.lastname);

        if(searchTableByString(fname, DataType(fullname), persons)) {
            cout << "The specified firstname & lastname is already in use for an existing user(s)!" << endl;
            cout << "Do you wish to continue (Y/N)?";
            if(!displayYesNoChoice()) {
                return;
            }
        }
    }

    cout << "Input e-mail: ";
    newPersonToAdd.email = getLineString();
    if (persons.size() > 0) {
        if(searchTableByString(newPersonToAdd.email, DataType(email), persons)) {
            cout << "The specified email is already in use for an existing user(s)!" << endl;
            cout << "Do you wish to continue (Y/N)?";

            if(!displayYesNoChoice()) {
                return;
            }
        }
    }

    cout << "Input phone number: ";
    newPersonToAdd.phone = removeSpacesAndDashesFromString(getLineString());
    if (persons.size() > 0) {
        if(searchTableByString(newPersonToAdd.phone, DataType(phone), persons)) {
            cout << "The specified phone number is already in use for an existing user(s)!" << endl;
            cout << "Do you wish to continue (Y/N)?";
            if(!displayYesNoChoice()) {
                return;
            }
        }
    }

    cout << "Input address: ";
    newPersonToAdd.address = getLineString();

    persons.push_back(newPersonToAdd);

    dataFile.open(ADDRESSBOOK_FILE, ios::out | ios::app);

    if (!dataFile.good()) {
        cout << "Error opening file: addressBook.txt!" << endl;
        displayPausePrompt();
    }
    dataFile << makeFileString(idLoggedUser, newPersonToAdd) << endl;
    dataFile.close();

    cout << "New person: " << newPersonToAdd.firstname << " " << newPersonToAdd.lastname << " added successfully to your AddressBook!" << endl;
    displayPausePrompt();
}

void displayAllPersons(vector <Person>& persons) {

    system("cls");
    if(persons.size() > 0) {

        for (auto person : persons) {
            displayRecordByTableIndex(person);
        }
    } else {
        cout << "No persons in your AddressBook!" << endl;
    }
    displayPausePrompt();
}

void loadDataFromTextFile(int idLoggedUser, vector <Person>& persons) {

    const char DATA_LIMITER = '|';
    ifstream dataFile;
    string textLine, field;
    Person newPersonToAdd;
    int userId;

    dataFile.open(ADDRESSBOOK_FILE, ios::in);

    if (!dataFile.good()) {
        cout << "File addressBook.txt not found, new file will be created after adding first person!" << endl;
        displayPausePrompt();
    }

    while(getline(dataFile,textLine)) {

        istringstream iss(textLine);

        getline(iss, field, DATA_LIMITER);
        newPersonToAdd.id = stoi(field);
        getline(iss, field, DATA_LIMITER);
        userId = stoi(field);
        getline(iss, newPersonToAdd.firstname, DATA_LIMITER);
        getline(iss, newPersonToAdd.lastname, DATA_LIMITER);
        getline(iss, newPersonToAdd.email, DATA_LIMITER);
        getline(iss, newPersonToAdd.phone, DATA_LIMITER);
        getline(iss, newPersonToAdd.address, DATA_LIMITER);

        if (userId == idLoggedUser) {
            persons.push_back(newPersonToAdd);
        }
    }
    dataFile.close();
}

bool displayYesNoChoice() {
    char yesNoChar;
    bool yesNoAnswer;

    while(true) {
        yesNoChar = getLineChar();
        if((yesNoChar == 'Y') || (yesNoChar == 'y') || (yesNoChar == 'n') || (yesNoChar == 'N')) {
            break;
        } else {
            cout << "Only Y/N are allowed." << endl;
            cout << "Do you wish to continue (Y/N)?";
        }
    }
    ((yesNoChar == 'N') || (yesNoChar == 'n')) ? yesNoAnswer = false : yesNoAnswer = true;

    return yesNoAnswer;
}

string removeSpacesAndDashesFromString(string stringToClear) {
    while(stringToClear.find(" ")!=string::npos) {
        stringToClear.erase(stringToClear.find(" "),1);
    }
    while(stringToClear.find("-")!=string::npos) {
        stringToClear.erase(stringToClear.find("-"),1);
    }
    return stringToClear;
}

string makeFileString(int idLoggedUser, const Person& persons) {

    string fileString;

    fileString.append(to_string(persons.id));
    fileString.append("|");
    fileString.append(to_string(idLoggedUser));
    fileString.append("|");
    fileString.append(persons.firstname);
    fileString.append("|");
    fileString.append(persons.lastname);
    fileString.append("|");
    fileString.append(persons.email);
    fileString.append("|");
    fileString.append(persons.phone);
    fileString.append("|");
    fileString.append(persons.address);
    fileString.append("|");

    return fileString;
}

void saveDataFile(int idLoggedUser, const vector <Person>& persons) {

    const char DATA_LIMITER = '|';
    string textLine, field;
    int userId, personId;
    fstream addressBookFile(ADDRESSBOOK_FILE, ios::in);
    fstream tempBookFile("tempBook.txt", ios::out | ios::trunc);

    if (!addressBookFile.good()) {
        cout << "Error opening file: addressBook.txt!" << endl;
        displayPausePrompt();
    }
    while(getline(addressBookFile,textLine)) {

        istringstream iss(textLine);
        getline(iss, field, DATA_LIMITER);
        personId = stoi(field);

        getline(iss, field, DATA_LIMITER);
        userId = stoi(field);

        if(userId == idLoggedUser) {

            for (Person person : persons) {
                if (person.id == personId)
                    tempBookFile << makeFileString(idLoggedUser, person) << endl;
            }
        } else {
            tempBookFile << textLine << endl;
        }
    }

    addressBookFile.close();
    tempBookFile.close();
    if (remove(ADDRESSBOOK_FILE.c_str()) != 0) {
        cout << "Error deleting AddressBook file!";
        displayPausePrompt();
    }
    if (rename("tempBook.txt", ADDRESSBOOK_FILE.c_str()) != 0) {
        cout << "Error renaming AddressBook file!";
        displayPausePrompt();
    }
}

void deletePerson(int idLoggedUser, vector <Person>& persons) {
    int personId;
    bool personFound = false;
    fstream dataFile;

    dataFile.open(ADDRESSBOOK_FILE, ios::in);

    if (!dataFile.good()) {

        cout << "File addressBook.txt not found, no records to delete!" << endl;
        displayPausePrompt();

    } else {
        dataFile.close();

        do {
            cout << "Input proper person ID to delete : ";
            personId = getLineInt();
        } while((personId < 1 ) || (personId > persons.back().id));

        for(vector <Person> :: iterator itr = persons.begin(); itr != persons.end(); ++itr) {

            if ((*itr).id == personId) {
                personFound = true;
                cout << "You are going to delete: " << (*itr).firstname << " " << (*itr).lastname << ", Do you wish to continue (Y/N) ? ";
                if (displayYesNoChoice()) {
                    persons.erase(itr--);
                    saveDataFile(idLoggedUser, persons);
                    cout << "Person with ID : " << personId << " successfully deleted." << endl;
                    displayPausePrompt();
                }
            }
        }
        if (!personFound) {
            cout << "Person with ID: " << personId << " not found in AddressBook database!" << endl;
            displayPausePrompt();
        }
    }
}

char displayEditSubMenu() {
    char menuSelection;

    system("cls");
    cout << ">> What data do you want to modify? <<" << endl;
    cout << "-----------------------------------" << endl;
    cout << "1. Firstname" << endl;
    cout << "2. Lastname" << endl;
    cout << "3. Phone number" << endl;
    cout << "4. e-mail" << endl;
    cout << "5. Address" << endl;
    cout << "6. Display current user data" << endl;
    cout << "9. Return to Main Menu" << endl;
    cout << "-----------------------------------" << endl;
    cout << "Enter your choice (1-6, 9): ";

    menuSelection = getLineChar();
    return menuSelection;
}

void modifyGivenPersonData(int personId, DataType personsDataType, vector <Person>& persons) {
    string tempPhone;
    string tempEmail;
    string tempFirstname;
    string tempLastname;
    string tempFullname;

    for(Person& person : persons) {
        if (person.id == personId) {
            cout << "You are modifing: " <<  person.firstname << " " << person.lastname << " data." << endl;
            if (personsDataType == DataType(firstname)) {
                cout << "Current firstname: " << person.firstname << endl;
                cout << "Type new firstname: ";

                tempFirstname = getLineString();
                tempFullname.append(tempFirstname);
                tempFullname.append(" ");
                tempFullname.append(person.lastname);

                if(searchTableByString(tempFullname, DataType(fullname), persons)) {
                    cout << "The specified firstname & lastname is already in use for an existing user(s)!" << endl;
                    cout << "Do you wish to continue (Y/N)?";
                    if(!displayYesNoChoice()) {
                        return;
                    }
                }
                person.firstname = tempFirstname;
                cout << "Firstname sucessfully changed to: " << person.firstname << endl;
                person.firstname = tempFirstname;
                displayPausePrompt();
            } else if (personsDataType == DataType(lastname)) {
                cout << "Current lastname: " << person.lastname << endl;
                cout << "Type new lastname: ";

                tempLastname = getLineString();
                tempFullname.append(person.firstname);
                tempFullname.append(" ");
                tempFullname.append(tempLastname);

                if(searchTableByString(tempFullname, DataType(fullname), persons)) {
                    cout << "The specified firstname & lastname is already in use for an existing user(s)!" << endl;
                    cout << "Do you wish to continue (Y/N)?";
                    if(!displayYesNoChoice()) {
                        return;
                    }
                }

                person.lastname = tempLastname;

                cout << "Lastname sucessfully changed to: " << person.lastname << endl;
                displayPausePrompt();
            } else if (personsDataType == DataType(phone)) {
                cout << "Current phone No.: " << person.phone << endl;
                cout << "Type new phone No.: ";
                tempPhone = removeSpacesAndDashesFromString(getLineString());
                if(searchTableByString(tempPhone, DataType(phone), persons)) {
                    cout << "The specified phone number is already in use for an existing user(s)!" << endl;
                    cout << "Do you wish to continue (Y/N)?";
                    if(!displayYesNoChoice()) {
                        return;
                    }
                }
                person.phone = tempPhone;
                cout << "Phone No. sucessfully changed to: " << person.phone << endl;
                displayPausePrompt();
            } else if (personsDataType == DataType(email)) {
                cout << "Current e-mail: " << person.email << endl;
                cout << "Type new e-mail: ";
                tempEmail = getLineString();
                if(searchTableByString(tempEmail, DataType(email), persons)) {
                    cout << "The specified email is already in use for an existing user(s)!" << endl;
                    cout << "Do you wish to continue (Y/N)?";
                    if(!displayYesNoChoice()) {
                        return;
                    }
                }
                person.email = tempEmail;
                cout << "e-mail sucessfully changed to: " << person.email << endl;
                displayPausePrompt();
            } else if (personsDataType == DataType(address)) {
                cout << "Current address: " << person.address << endl;
                cout << "Type new address: ";
                person.address = getLineString();
                cout << "Address sucessfully changed to: " << person.address << endl;
                displayPausePrompt();
            }
        }
    }
}

void modifyPerson(int idLoggedUser, vector <Person>& persons) {
    char menuSelection;
    int personId;
    bool personFound = false;
    fstream dataFile;

    dataFile.open(ADDRESSBOOK_FILE, ios::in);

    if (!dataFile.good()) {

        cout << "File addressBook.txt not found, no records to modify!" << endl;
        displayPausePrompt();

    } else {
        dataFile.close();

        do {
            cout << "Input proper person ID to modify : ";
            personId = getLineInt();
        } while((personId < 1 ) || (personId > persons.back().id));

        for(Person& person : persons) {
            if (person.id == personId) {
                personFound = true;

                while (true) {
                    menuSelection = displayEditSubMenu();

                    switch (menuSelection) {
                    case '1':
                        modifyGivenPersonData(personId, firstname, persons);
                        break;
                    case '2':
                        modifyGivenPersonData(personId, lastname, persons);
                        break;
                    case '3':
                        modifyGivenPersonData(personId, phone, persons);
                        break;
                    case '4':
                        modifyGivenPersonData(personId, email, persons);
                        break;
                    case '5':
                        modifyGivenPersonData(personId, address, persons);
                        break;
                    case '6':
                        displayRecordByTableIndex(person);
                        displayPausePrompt();
                        break;
                    case '9':
                        saveDataFile(idLoggedUser, persons);
                        return;
                    default:
                        cout << "Only 1, 2, 3, 4, 5, 6 and 9 are allowed." << endl;
                        displayPausePrompt();
                    }
                }
            }
        }

        if (!personFound) {
            cout << "Person with ID: " << personId << " not found in AddressBook database!" << endl;
            displayPausePrompt();
        }
    }
}

int manageMainMenu(int idLoggedUser, vector <Person>& persons, vector <User>& users) {

    char menuSelection;
    string stringToSearch;

    while (true) {

        menuSelection = displayMainMenu();

        switch (menuSelection) {
        case '1':
            addNewPerson(idLoggedUser, persons);
            break;
        case '2':
            cout << "Input firstname: ";
            stringToSearch = getLineString();

            if (!searchTableByString(stringToSearch, DataType(firstname), persons)) {
                cout << "No such person in your AddressBook!" << endl;
            }
            displayPausePrompt();
            break;
        case '3':
            cout << "Input lastname: ";
            stringToSearch = getLineString();

            if (!searchTableByString(stringToSearch, DataType(lastname), persons)) {
                cout << "No such person in your AddressBook!" << endl;
            }
            displayPausePrompt();
            break;
        case '4':
            displayAllPersons(persons);
            break;
        case '5':
            deletePerson(idLoggedUser, persons);
            break;
        case '6':
            modifyPerson(idLoggedUser, persons);
            break;
        case '7':
            changeUserPassword(idLoggedUser, users);
            break;
        case '9':
            idLoggedUser = 0;
            persons.clear();
            return idLoggedUser;
        case '0':
            system("cls");
        default:
            cout << "Only 1, 2, 3, 4, 5, 6, 7 and 9 are allowed." << endl;
            displayPausePrompt();
        }
    }
}

int loginUser(vector <User>& users) {

    string userName, userPassword;
    cout << "Input login: ";
    userName = getLineString();

    for(User& user : users) {
        if (user.username == userName) {

            for (int loginAttempts = 0; loginAttempts < 3; ++loginAttempts) {
                cout << "Enter password. Attempts left: " << 3 - loginAttempts << ": ";
                userPassword = getLineString();
                if (user.password == userPassword) {
                    cout << "You are logged in." << endl;
                    Sleep(1000);
                    return user.id;
                }
            }
            cout << "You have entered incorrect password 3 times. Wait 3 seconds before next attempt." << endl;
            Sleep(3000);
            return 0;
        }
    }
    cout << "No user with entered login" << endl;
    Sleep(1500);
    return 0;
}

bool checkIfUserNameAlreadyExist(string userName, vector <User>& users) {

    bool userFound = false;

    for(User& user : users) {
        if (user.username == userName) {
            cout << "User name already exist. Enter different user name." << endl;
            userFound = true;
        }
    }
    return userFound;
}

bool checkIfUserDataEmpty(string userData) {

    bool userDataEmpty = false;

    if (userData == "") {
        cout << "Empty field is not allowed. You have to enter proper data." << endl;
        userDataEmpty = true;
    }
    return userDataEmpty;
}

void registerUser(vector <User>& users) {

    string userName, userPassword;
    User newUserToAdd;

    do {
        cout << "Enter user name: ";
        userName = getLineString();
    } while(checkIfUserNameAlreadyExist(userName, users) || checkIfUserDataEmpty(userName));

    do {
        cout << "Enter password: ";
        userPassword = getLineString();
    } while(checkIfUserDataEmpty(userPassword));

    newUserToAdd.id = !users.size() ? 1 : users.back().id + 1;
    newUserToAdd.username = userName;
    newUserToAdd.password = userPassword;
    users.push_back(newUserToAdd);

    cout << "User account successfully registered." << endl;
    Sleep (1000);
}

void changeUserPassword(int idLoggedUser, vector <User>& users) {

    string userPassword;
    cout << "Enter password: ";
    userPassword = getLineString();

    for(User& user : users) {
        if(user.id == idLoggedUser) {
            user.password = userPassword;
            cout << "Password successfully changed." << endl;
            Sleep(1500);
        }
    }
}
void loadUserDataFromTextFile(vector <User>& users) {

    const char DATA_LIMITER = '|';
    ifstream dataFile;
    string textLine, field;
    User newUserToAdd;

    dataFile.open(USERS_FILE, ios::in);

    if (!dataFile.good()) {
        cout << "File users.txt not found, new file will be created after adding first person!" << endl;
        displayPausePrompt();
    }
    while(getline(dataFile,textLine)) {

        istringstream iss (textLine);
        getline(iss, field, DATA_LIMITER);
        newUserToAdd.id = stoi(field);
        getline(iss, newUserToAdd.username, DATA_LIMITER);
        getline(iss, newUserToAdd.password, DATA_LIMITER);

        users.push_back(newUserToAdd);
    }
    dataFile.close();
}

string makeUserString(const User& users) {

    string fileUserString;

    fileUserString.append(to_string(users.id));
    fileUserString.append("|");
    fileUserString.append(users.username);
    fileUserString.append("|");
    fileUserString.append(users.password);
    fileUserString.append("|");

    return fileUserString;
}

void rewriteUsersFile(const vector <User>& users) {
    ofstream usersFile(USERS_FILE, ios::out | ios::trunc);

    if (!usersFile.good()) {
        cout << "Error opening file: users.txt!" << endl;
        displayPausePrompt();
    }
    for (User user : users) {
        usersFile << makeUserString(user) << endl;
    }
    usersFile.close();
}

void manageUsersMenu(vector <Person>& persons, vector <User>& users) {

    char menuSelection;
    int idLoggedUser = 0;

    loadUserDataFromTextFile(users);

    while(1) {
        if (idLoggedUser == 0) {

            system("cls");
            cout << "   >> User Login Menu <<" << endl;
            cout << "----------------------------" << endl;
            cout << "1. Login" << endl;
            cout << "2. Register" << endl;
            cout << "9. Exit" << endl;
            cout << "----------------------------" << endl;
            cout << "Enter your choice (1-2, 9): ";

            menuSelection = getLineChar();

            if (menuSelection == '1') {
                idLoggedUser = loginUser(users);

            } else if (menuSelection == '2') {
                registerUser(users);
            } else if (menuSelection == '9') {
                rewriteUsersFile(users);
                return;
            }
        } else {

            loadDataFromTextFile(idLoggedUser, persons);
            idLoggedUser = manageMainMenu(idLoggedUser, persons, users);
        }
    }
    return;
}
