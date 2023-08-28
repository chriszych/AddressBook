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

enum MessageType {
    dataAlreadyExist,
    onlyDigitsAllowed,
    onlySingleCharacter,
    doYouWantContinue,
    pressAnyKeyToContinue,
    errorOpeningFile,
    newPersonSucessfullyAdded,
    noPersonInAddressBook,
    fileNotFound,
    noFileNewCreate,
    personNotFound,
    onlyYNAllowed,
    errorDeleteFile,
    errorRenameFile,
    inputPersonToDelete,
    personDeleteSuccess,
    okToDelete,
    modifyPersonSummary,
    inputPersonToModify,
    inputNewData,
    noEnteredPersonInAddressBook,
    inputData,
    currentData,
    dataSuccessfullyChanged,
    onlyNumbers16Allowed,
    onlyNumbers17Allowed,
    userLoggedIn,
    enterPassword,
    incorrectPassword3Times,
    userNameExist,
    emptyUserNotAllowed,
    userSuccessfullyRegistered,
    passSuccessfullyChanged,
    noUserFound,
} ;

const string ADDRESSBOOK_FILE = "addressBook.txt";
const string USERS_FILE = "users.txt";

void displayMessage(MessageType displayMessageType);
void displayMessage(MessageType displayMessageType, string dataToDisplay);
void displayMessage(MessageType displayMessageType, string dataToDisplay, string additionalData);
void displayPausePrompt();
void displayRecordsByIndex(const Person person);
string makeFullnameString(string firstname, string lastname);
string makeFileString(int idLoggedUser, const Person& persons);
string clearPhoneNumber(string stringToClear);
string makeUserString(const User& users);
string getLineString();
bool checkIfDataAlreadyExist(string stringToSearch, DataType personsDataType, vector <Person>& persons);
bool checkNewPersonData(string personData, DataType personsDataType, vector <Person>& persons);
bool isNumber(string textNumber);
bool displayYesNoChoice();
char getLineChar();
int getLineInt();
char displayMainMenu();
char displayEditSubMenu();
void addNewPerson(vector <Person>& persons);
void displayAllPersons(vector <Person>& persons);
void loadDataFromFile(int idLoggedUser, vector <Person>& persons);
void saveDataFile(int idLoggedUser, const vector <Person>& persons);
void deletePerson(int idLoggedUser, vector <Person>& persons);
void modifyFirstname(Person& person);
void modifyLastname(Person& person);
void modifyPhone(Person& person);
void modifyEmail(Person& person);
void modifyAddress(Person& person);
void modifyGivenPersonData(int personId, DataType personsDataType, vector <Person>& persons);
void modifyPerson(int idLoggedUser, vector <Person>& persons);
void searchVectorByString(string dataTypeToSearch, DataType personsDataType, vector <Person>& persons);
int manageMainMenu(int idLoggedUser, vector <Person>& persons, vector <User>& users);
int loginUser(vector <User>& users);
bool checkIfUserNameExist(string userName, vector <User>& users);
bool checkIfUserDataEmpty(string userData);
void registerUser(vector <User>& users);
void changeUserPassword(int idLoggedUser, vector <User>& users);
void loadUsersFromFile(vector <User>& users);
void saveUsersFile(const vector <User>& users);
char displayUserMenu();
void manageUsersMenu(vector <Person>& persons, vector <User>& users);

int main() {

    vector <Person> persons;
    vector <User> users;

    manageUsersMenu(persons, users);

    return 0;
}

void displayMessage(MessageType displayMessageType) {
    switch (displayMessageType) {
    case onlyDigitsAllowed:
        cout << "Only digits are allowed, type a digit : ";
        break;
    case onlySingleCharacter:
        cout << "Enter single character only!" << endl;
        break;
    case pressAnyKeyToContinue:
        cout << "Press any key to continue ...";
        break;
    case doYouWantContinue:
        cout << "Do you wish to continue (Y/N)?";
        break;
    case noPersonInAddressBook:
        cout << "No persons in your AddressBook!" << endl;
        break;
    case onlyYNAllowed:
        cout << "Only Y/N are allowed." << endl;
        break;
    case errorDeleteFile:
        cout << "Error deleting AddressBook file!";
        break;
    case errorRenameFile:
        cout << "Error renaming AddressBook file!";
        break;
    case inputPersonToDelete:
        cout << "Input proper person ID to delete : ";
        break;
    case inputPersonToModify:
        cout << "Input proper person ID to modify : ";
        break;
    case noEnteredPersonInAddressBook:
        cout << "No such person in your AddressBook!" << endl;
        break;
    case onlyNumbers16Allowed:
        cout << "Only 1, 2, 3, 4, 5, 6 and 9 are allowed." << endl;
        break;
    case onlyNumbers17Allowed:
        cout << "Only 1, 2, 3, 4, 5, 6, 7 and 9 are allowed." << endl;
        break;
    case userLoggedIn:
        cout << "You are successfully logged in." << endl;
        break;
    case incorrectPassword3Times:
        cout << "You have entered incorrect password 3 times. Wait 3 seconds before next attempt." << endl;
        break;
    case noUserFound:
        cout << "No user with entered login" << endl;
        break;
    case userNameExist:
        cout << "User name already exist. Enter different user name." << endl;
        break;
    case emptyUserNotAllowed:
        cout << "Empty field is not allowed. You have to enter proper data." << endl;
        break;
    case userSuccessfullyRegistered:
        cout << "User account successfully registered." << endl;
        break;
    case passSuccessfullyChanged:
        cout << "Password successfully changed." << endl;
        break;
    default:
        break;
    }
}

void displayMessage(MessageType displayMessageType, string dataToDisplay) {

    switch (displayMessageType) {
    case dataAlreadyExist:
        cout << "The specified " << dataToDisplay << " is already in use for an existing user(s)!" << endl;
        break;
    case newPersonSucessfullyAdded:
        cout << "New person: " << dataToDisplay << " added successfully to your AddressBook!" << endl;
        break;
    case fileNotFound:
        cout << "Error opening file: " << dataToDisplay << endl;
        break;
    case noFileNewCreate:
        cout << "File "<< dataToDisplay  <<" not found, new file will be created after adding first person!" << endl;
        break;
    case personNotFound:
        cout << "Person with ID: " << dataToDisplay << " not found in AddressBook database!" << endl;
        break;
    case personDeleteSuccess:
        cout << "Person with ID : " << dataToDisplay << " successfully deleted." << endl;
        break;
    case okToDelete:
        cout << "You are going to delete: " << dataToDisplay << ", ";
        break;
    case modifyPersonSummary:
        cout << "You are modifying: " <<  dataToDisplay << " data." << endl;
        break;
    case inputNewData:
        cout << "Input new " << dataToDisplay << ": ";
        break;
    case inputData:
        cout << "Input " << dataToDisplay << ": ";
        break;
    case enterPassword:
        cout << "Enter password. Attempts left: " << dataToDisplay << ": ";
        break;
    default:
        break;
    }
}

void displayMessage(MessageType displayMessageType, string dataToDisplay, string additionalData) {

    switch (displayMessageType) {
    case currentData:
        cout << "Current " << additionalData << ": " << dataToDisplay << endl;
        break;
    case dataSuccessfullyChanged:
        cout << additionalData << " sucessfully changed to: " << dataToDisplay << endl;
        break;
    default:
        break;
    }
}

void displayPausePrompt() {
    displayMessage(pressAnyKeyToContinue);
    getchar();
}

void displayRecordsByIndex(const Person person) {
    cout << "(" << person.id << "). " << person.firstname << " " << person.lastname << ", " << person.email << ", " << person.phone << ", " << person.address <<  endl;
}

string makeFullnameString(string firstname, string lastname) {

    string fname = "";
    fname.append(firstname);
    fname.append(" ");
    fname.append(lastname);

    return fname;
}

bool checkIfDataAlreadyExist(string stringToSearch, DataType personsDataType, Person person) {

    bool searchResult = false;
    string fname = "";

    switch (personsDataType) {
    case firstname:
        if (person.firstname.find(stringToSearch) != string::npos) {
            displayRecordsByIndex(person);
            searchResult = true;
        }
        break;
    case lastname:
        if (person.lastname.find(stringToSearch) != string::npos) {
            displayRecordsByIndex(person);
            searchResult = true;
        }
        break;
    case email:
        if (person.email == stringToSearch) {
            displayRecordsByIndex(person);
            searchResult = true;
        }
        break;
    case phone:
        if (person.phone == stringToSearch) {
            displayRecordsByIndex(person);
            searchResult = true;
        }
        break;
    case fullname:
        fname = makeFullnameString(person.firstname, person.lastname);
        if (fname == stringToSearch) {
            displayRecordsByIndex(person);
            searchResult = true;
        }
        break;
    default:
        break;
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
            displayMessage(onlyDigitsAllowed);
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
            displayMessage(onlySingleCharacter);
            break;
        }
    }
    return dataChar;
}

char displayMainMenu() {

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

    return getLineChar();
}

bool checkNewPersonData(string personData, DataType personsDataType, vector <Person>& persons) {

    for(Person person : persons) {
        if(checkIfDataAlreadyExist(personData, personsDataType, person)) {
            displayMessage(dataAlreadyExist, personData);
            displayMessage(doYouWantContinue);

            if(!displayYesNoChoice()) {
                return 1;
            }
        }
    }
    return 0;
}

void addNewPerson(int idLoggedUser, vector <Person>& persons) {
    ofstream dataFile;
    Person newPersonToAdd;
    string fname = "";

    newPersonToAdd.id = !persons.size() ? 1 : persons.back().id + 1;

    displayMessage(inputData, "firstname");
    newPersonToAdd.firstname = getLineString();
    displayMessage(inputData, "lastname");
    newPersonToAdd.lastname = getLineString();

    if (persons.size() > 0) {

        fname = makeFullnameString(newPersonToAdd.firstname, newPersonToAdd.lastname);
        if(checkNewPersonData(fname, fullname, persons)) {
            return;
        }
    }

    displayMessage(inputData, "e-mail");
    newPersonToAdd.email = getLineString();

    if (persons.size() > 0) {
        if(checkNewPersonData(newPersonToAdd.email, email, persons)) {
            return;
        }
    }

    displayMessage(inputData, "phone number");
    newPersonToAdd.phone = clearPhoneNumber(getLineString());

    if (persons.size() > 0) {
        if(checkNewPersonData(newPersonToAdd.phone, phone, persons)) {
            return;
        }
    }

    displayMessage(inputData, "address");
    newPersonToAdd.address = getLineString();

    persons.push_back(newPersonToAdd);

    dataFile.open(ADDRESSBOOK_FILE, ios::out | ios::app);

    if (!dataFile.good()) {
        displayMessage(errorOpeningFile, ADDRESSBOOK_FILE);
        displayPausePrompt();
    }
    dataFile << makeFileString(idLoggedUser, newPersonToAdd) << endl;
    dataFile.close();

    displayMessage(newPersonSucessfullyAdded, fname);
    displayPausePrompt();
}

void displayAllPersons(vector <Person>& persons) {

    system("cls");
    if(persons.size() > 0) {

        for (auto person : persons) {
            displayRecordsByIndex(person);
        }
    } else {
        displayMessage(noPersonInAddressBook);
    }
    displayPausePrompt();
}

void loadDataFromFile(int idLoggedUser, vector <Person>& persons) {

    const char DATA_LIMITER = '|';
    ifstream dataFile;
    string textLine, field;
    Person newPersonToAdd;
    int userId;

    dataFile.open(ADDRESSBOOK_FILE, ios::in);

    if (!dataFile.good()) {
        displayMessage(noFileNewCreate, ADDRESSBOOK_FILE);
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
            displayMessage(onlyYNAllowed);
            displayMessage(doYouWantContinue);
        }
    }
    ((yesNoChar == 'N') || (yesNoChar == 'n')) ? yesNoAnswer = false : yesNoAnswer = true;

    return yesNoAnswer;
}

string clearPhoneNumber(string stringToClear) {
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
        displayMessage(errorOpeningFile, ADDRESSBOOK_FILE);
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
        displayMessage(errorDeleteFile, ADDRESSBOOK_FILE);
        displayPausePrompt();
    }
    if (rename("tempBook.txt", ADDRESSBOOK_FILE.c_str()) != 0) {
        displayMessage(errorRenameFile, ADDRESSBOOK_FILE);
        displayPausePrompt();
    }
}

void deletePerson(int idLoggedUser, vector <Person>& persons) {
    int personId;
    bool personFound = false;
    fstream dataFile;
    string fname ="";

    dataFile.open(ADDRESSBOOK_FILE, ios::in);

    if (!dataFile.good()) {
        displayMessage(fileNotFound, ADDRESSBOOK_FILE);
        displayPausePrompt();

    } else {
        dataFile.close();

        do {
            displayMessage(inputPersonToDelete);
            personId = getLineInt();
        } while((personId < 1 ) || (personId > persons.back().id));

        for(vector <Person> :: iterator itr = persons.begin(); itr != persons.end(); ++itr) {

            if ((*itr).id == personId) {
                personFound = true;

                fname = makeFullnameString((*itr).firstname, (*itr).lastname);
                displayMessage(okToDelete, fname);
                displayMessage(doYouWantContinue);
                if (displayYesNoChoice()) {
                    persons.erase(itr--);
                    saveDataFile(idLoggedUser, persons);
                    displayMessage(personDeleteSuccess, to_string(personId));
                    displayPausePrompt();
                }
            }
        }
        if (!personFound) {
            displayMessage(personNotFound, to_string(personId));
            displayPausePrompt();
        }
    }
}

char displayEditSubMenu() {

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

    return getLineChar();
}


void modifyFirstname(Person& person) {

    string tempFirstname;
    string tempFullname;

    displayMessage(currentData, person.firstname, "firstname");
    displayMessage(inputNewData, "firstname");

    tempFirstname = getLineString();
    tempFullname = makeFullnameString(tempFirstname, person.lastname);

    if(checkIfDataAlreadyExist(tempFullname, DataType(fullname), person)) {
        displayMessage(dataAlreadyExist, "firstname & lastname");
        displayMessage(doYouWantContinue);
        if(!displayYesNoChoice()) {
            return;
        }
    }
    person.firstname = tempFirstname;
    displayMessage(dataSuccessfullyChanged, person.firstname, "firstname");
    displayPausePrompt();

}

void modifyLastname(Person& person) {

    string tempLastname;
    string tempFullname;

    displayMessage(currentData, person.lastname, "lastname");
    displayMessage(inputNewData, "lastname");

    tempLastname = getLineString();
    tempFullname = makeFullnameString(person.firstname, tempLastname);

    if(checkIfDataAlreadyExist(tempFullname, DataType(fullname), person)) {
        displayMessage(dataAlreadyExist, tempFullname);
        displayMessage(doYouWantContinue);

        if(!displayYesNoChoice()) {
            return;
        }
    }
    person.lastname = tempLastname;

    displayMessage(dataSuccessfullyChanged, person.lastname, "lastname");
    displayPausePrompt();

}

void modifyPhone(Person& person) {

    string tempPhone;

    displayMessage(currentData, person.phone, "phone");
    displayMessage(inputNewData, "phone");
    tempPhone = clearPhoneNumber(getLineString());

    if(checkIfDataAlreadyExist(tempPhone, DataType(phone), person)) {
        displayMessage(dataAlreadyExist, "phone number");
        displayMessage(doYouWantContinue);

        if(!displayYesNoChoice()) {
            return;
        }
    }
    person.phone = tempPhone;
    displayMessage(dataSuccessfullyChanged, person.phone, "Phone number");
    displayPausePrompt();
}

void modifyEmail(Person& person) {

    string tempEmail;

    displayMessage(currentData, person.phone, "e-mail");
    displayMessage(inputNewData, "e-mail");

    tempEmail = getLineString();
    if(checkIfDataAlreadyExist(tempEmail, DataType(email), person)) {
        displayMessage(dataAlreadyExist, "e-mail");
        displayMessage(doYouWantContinue);

        if(!displayYesNoChoice()) {
            return;
        }
    }
    person.email = tempEmail;
    displayMessage(dataSuccessfullyChanged, person.email, "e-mail");
    displayPausePrompt();
}

void modifyAddress(Person& person) {

    displayMessage(currentData, person.address, "address");
    displayMessage(inputNewData, "address");

    person.address = getLineString();
    displayMessage(dataSuccessfullyChanged, person.address, "Address");

    displayPausePrompt();

}

void modifyGivenPersonData(int personId, DataType personsDataType, vector <Person>& persons) {

    string tempFullname = "";

    for(Person& person : persons) {
        if (person.id == personId) {

            tempFullname = makeFullnameString(person.firstname, person.lastname);
            displayMessage(modifyPersonSummary, tempFullname);

            switch (personsDataType) {
            case firstname:
                modifyFirstname(person);
                break;
            case lastname:
                modifyLastname(person);
                break;
            case phone:
                modifyPhone(person);
                break;
            case email:
                modifyEmail(person);
                break;
            case address:
                modifyAddress(person);
                break;
            default:
                break;

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

        displayMessage(fileNotFound, ADDRESSBOOK_FILE);
        displayPausePrompt();

    } else {
        dataFile.close();

        do {
            displayMessage(inputPersonToModify);
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
                        displayRecordsByIndex(person);
                        displayPausePrompt();
                        break;
                    case '9':
                        saveDataFile(idLoggedUser, persons);
                        return;
                    default:
                        displayMessage(onlyNumbers16Allowed);
                        displayPausePrompt();
                    }
                }
            }
        }

        if (!personFound) {
            displayMessage(personNotFound, to_string(personId));
            displayPausePrompt();
        }
    }
}

void searchVectorByString(string dataTypeToSearch, DataType personsDataType, vector <Person>& persons) {

    string stringToSearch;
    bool personFound = false;

    displayMessage(inputData, dataTypeToSearch);
    stringToSearch = getLineString();

    for(Person person : persons) {


        if (checkIfDataAlreadyExist(stringToSearch, personsDataType, person)) {
            personFound = true;
        }
    }
    if(!personFound) {
        displayMessage(noEnteredPersonInAddressBook);
    }
    displayPausePrompt();
}


int manageMainMenu(int idLoggedUser, vector <Person>& persons, vector <User>& users) {

    char menuSelection;

    while (true) {

        menuSelection = displayMainMenu();

        switch (menuSelection) {
        case '1':
            addNewPerson(idLoggedUser, persons);
            break;
        case '2':
            searchVectorByString("firstname", firstname, persons);
            break;
        case '3':
            searchVectorByString("lastname", lastname, persons);
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
            displayMessage(onlyNumbers17Allowed);
            displayPausePrompt();
        }
    }
}

int loginUser(vector <User>& users) {

    string userName, userPassword;
    displayMessage(inputData, "login");
    userName = getLineString();

    for(User& user : users) {
        if (user.username == userName) {

            for (int loginAttempts = 0; loginAttempts < 3; ++loginAttempts) {
                displayMessage(enterPassword, to_string(3 - loginAttempts));
                userPassword = getLineString();
                //if (user.username == userName) {
                if (user.password == userPassword) {
                //if (user.password == userPassword && user.username == userName) {
                    displayMessage(userLoggedIn);
                    Sleep(1000);
                    return user.id;
                }
            }
            displayMessage(incorrectPassword3Times);
            Sleep(3000);
            return 0;
        }
    }
    displayMessage(noUserFound);
    displayPausePrompt();
    return 0;
}

bool checkIfUserNameExist(string userName, vector <User>& users) {

    bool userFound = false;

    for(User& user : users) {
        if (user.username == userName) {
            displayMessage(userNameExist);
            userFound = true;
        }
    }
    return userFound;
}

bool checkIfUserDataEmpty(string userData) {

    bool userDataEmpty = false;

    if (userData == "") {
        displayMessage(emptyUserNotAllowed);
        userDataEmpty = true;
    }
    return userDataEmpty;
}

void registerUser(vector <User>& users) {

    string userName, userPassword;
    User newUserToAdd;

    do {
        displayMessage(inputData, "user name");
        userName = getLineString();
    } while(checkIfUserNameExist(userName, users) || checkIfUserDataEmpty(userName));

    do {
        displayMessage(inputData, "password");
        userPassword = getLineString();
    } while(checkIfUserDataEmpty(userPassword));

    newUserToAdd.id = !users.size() ? 1 : users.back().id + 1;
    newUserToAdd.username = userName;
    newUserToAdd.password = userPassword;
    users.push_back(newUserToAdd);

    displayMessage(userSuccessfullyRegistered);
    Sleep (1000);
}

void changeUserPassword(int idLoggedUser, vector <User>& users) {

    string userPassword;
    displayMessage(inputData, "password");
    userPassword = getLineString();

    for(User& user : users) {
        if(user.id == idLoggedUser) {
            user.password = userPassword;
            displayMessage(passSuccessfullyChanged);
            displayPausePrompt();
        }
    }
}
void loadUsersFromFile(vector <User>& users) {

    const char DATA_LIMITER = '|';
    ifstream dataFile;
    string textLine, field;
    User newUserToAdd;

    dataFile.open(USERS_FILE, ios::in);

    if (!dataFile.good()) {
        displayMessage(noFileNewCreate, USERS_FILE);
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

void saveUsersFile(const vector <User>& users) {
    ofstream usersFile(USERS_FILE, ios::out | ios::trunc);

    if (!usersFile.good()) {
        displayMessage(fileNotFound, USERS_FILE);
        displayPausePrompt();
    }
    for (User user : users) {
        usersFile << makeUserString(user) << endl;
    }
    usersFile.close();
}

char displayUserMenu() {

    system("cls");
    cout << "   >> User Login Menu <<" << endl;
    cout << "----------------------------" << endl;
    cout << "1. Login" << endl;
    cout << "2. Register" << endl;
    cout << "9. Exit" << endl;
    cout << "----------------------------" << endl;
    cout << "Enter your choice (1-2, 9): ";

    return getLineChar();
}

void manageUsersMenu(vector <Person>& persons, vector <User>& users) {

    char menuSelection;
    int idLoggedUser = 0;

    loadUsersFromFile(users);

    while(1) {
        if (idLoggedUser == 0) {

            menuSelection = displayUserMenu();

            if (menuSelection == '1') {
                idLoggedUser = loginUser(users);

            } else if (menuSelection == '2') {
                registerUser(users);
            } else if (menuSelection == '9') {
                saveUsersFile(users);
                return;
            }
        } else {

            loadDataFromFile(idLoggedUser, persons);
            idLoggedUser = manageMainMenu(idLoggedUser, persons, users);
        }
    }
    return;
}
