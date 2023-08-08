#include <iostream>
#include <windows.h>
#include <fstream>
#include <conio.h>
#include <vector>
#include <iomanip>

using namespace std;

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

void displayPausePrompt();
void displayRecordByTableIndex(Person persons);
bool searchTableByString(string stringToSearch, DataType personsDataType, vector <Person>& persons);
string getLineString();
char getLineChar();
bool isNumber(string s);
int getLineInt();
char displayMainMenu();
void addNewPerson(vector <Person>& persons);
void displayAllPersons(vector <Person>& persons);
void loadDataFromTextFile(vector <Person>& persons);
bool displayYesNoChoice();
string removeSpacesAndDashesFromString(string stringToClear);
void rewriteDataFile(const vector <Person>& persons);
void deletePerson(vector <Person>& persons);
char displayEditSubMenu();
void modifyPerson(vector <Person>& persons);

int main() {
    vector <Person> persons;
    char menuSelection;
    string stringToSearch;


    loadDataFromTextFile(persons);

    while (true) {
        menuSelection = displayMainMenu();

        switch (menuSelection) {
        case '1':
            addNewPerson(persons);
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
            deletePerson(persons);
            break;
        case '6':
            modifyPerson(persons);
            break;
        case '9':
            exit(0);
        case '0':
            system("cls");
        default:
            cout << "Only 1, 2, 3, 4, 5, 6 and 9 are allowed." << endl;
            displayPausePrompt();
        }
    }
    return 0;
}

void displayPausePrompt() {
    cout << "Press any key to continue ...";
    getchar();
}

void displayRecordByTableIndex(Person persons) {
    cout << "(" << persons.id << "). " << persons.firstname << " " << persons.lastname << ", " << persons.email << ", " << persons.phone << ", " << persons.address <<  endl;
}

bool searchTableByString(string stringToSearch, DataType personsDataType, vector <Person>& persons) {
    bool searchResult = false;

    for(size_t i = 0; i < persons.size(); ++i) {
        if (personsDataType == DataType(firstname)) {
            if (persons[i].firstname.find(stringToSearch) != string::npos) {
                displayRecordByTableIndex(persons[i]);
                searchResult = true;
            }
        } else if (personsDataType == DataType(lastname)) {
            if (persons[i].lastname.find(stringToSearch) != string::npos) {
                displayRecordByTableIndex(persons[i]);
                searchResult = true;
            }
        } else if (personsDataType == DataType(email)) {
            if (persons[i].email == stringToSearch) {
                displayRecordByTableIndex(persons[i]);
                searchResult = true;
            }
        } else if (personsDataType == DataType(phone)) {
            if (persons[i].phone == stringToSearch) {
                displayRecordByTableIndex(persons[i]);
                searchResult = true;
            }

        } else if (personsDataType == DataType(fullname)) {
            string fname = "";
            fname.append(persons[i].firstname);
            fname.append(" ");
            fname.append(persons[i].lastname);

            if (fname == stringToSearch) {
                displayRecordByTableIndex(persons[i]);
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

bool isNumber(string s) {
    if(s.size()==0) return false;
    for(size_t i=0; i<s.size(); i++) {
        if(!(s[i]>='0' && s[i]<='9')) {
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
    cout << "9. Exit" << endl;
    cout << "-----------------------------" << endl;
    cout << "Enter your choice (1-6,9): ";

    menuSelection = getLineChar();
    return menuSelection;
}

void addNewPerson(vector <Person>& persons) {
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

    dataFile << newPersonToAdd.id << "|" << newPersonToAdd.firstname << "|" << newPersonToAdd.lastname << "|" << newPersonToAdd.email << "|" << newPersonToAdd.phone << "|" << newPersonToAdd.address << "|" << endl;

    dataFile.close();

    cout << "New person: " << newPersonToAdd.firstname << " " << newPersonToAdd.lastname << " added successfully to your AddressBook!" << endl;
    displayPausePrompt();
}

void displayAllPersons(vector <Person>& persons) {

    system("cls");
    if(persons.size() > 0) {
        for(size_t i = 0; i < persons.size(); ++i) {
            displayRecordByTableIndex(persons[i]);
        }
    } else {
        cout << "No persons in your AddressBook!" << endl;
    }

    displayPausePrompt();
}

void loadDataFromTextFile(vector <Person>& persons) {

    const char DATA_LIMITER = '|';
    ifstream dataFile;
    string textLine;
    Person newPersonToAdd;
    size_t dataLimiterPosition;

    dataFile.open(ADDRESSBOOK_FILE, ios::in);

    if (!dataFile.good()) {
        cout << "File addressBook.txt not found, creating new file!" << endl;
        displayPausePrompt();
    }

    while(getline(dataFile,textLine)) {
        dataLimiterPosition = textLine.find(DATA_LIMITER);
        newPersonToAdd.id = atoi(textLine.substr(0, dataLimiterPosition).c_str());
        textLine.erase(0, dataLimiterPosition + 1);

        dataLimiterPosition = textLine.find(DATA_LIMITER);
        newPersonToAdd.firstname = textLine.substr(0, dataLimiterPosition);
        textLine.erase(0, dataLimiterPosition + 1);

        dataLimiterPosition = textLine.find(DATA_LIMITER);
        newPersonToAdd.lastname = textLine.substr(0, dataLimiterPosition);
        textLine.erase(0, dataLimiterPosition + 1);

        dataLimiterPosition = textLine.find(DATA_LIMITER);
        newPersonToAdd.email = textLine.substr(0, dataLimiterPosition);
        textLine.erase(0, dataLimiterPosition + 1);

        dataLimiterPosition = textLine.find(DATA_LIMITER);
        newPersonToAdd.phone = textLine.substr(0, dataLimiterPosition);
        textLine.erase(0, dataLimiterPosition + 1);

        dataLimiterPosition = textLine.find(DATA_LIMITER);
        newPersonToAdd.address = textLine.substr(0, dataLimiterPosition);
        textLine.erase(0, dataLimiterPosition + 1);

        persons.push_back(newPersonToAdd);
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

void rewriteDataFile(const vector <Person>& persons) {
    ofstream addressBookFile(ADDRESSBOOK_FILE, ios::out | ios::trunc);

    if (!addressBookFile.good()) {
        cout << "Error opening file: addressBook.txt!" << endl;
        displayPausePrompt();
    }
    for (size_t i = 0; i < persons.size(); ++i) {
            addressBookFile << persons[i].id << "|" << persons[i].firstname << "|" << persons[i].lastname << "|" << persons[i].email << "|" << persons[i].phone << "|" << persons[i].address << "|" << endl;
        }
    addressBookFile.close();
}

void deletePerson(vector <Person>& persons) {
    int personId;
    bool personFound = false;

    do {
        cout << "Input proper person ID to delete : ";
        personId = getLineInt();
    } while((personId < 1 ) || (personId > persons.back().id));

    for(size_t i = 0; i < persons.size(); ++i) {
        if (persons[i].id == personId) {
            personFound = true;
            cout << "You are going to delete: " <<  persons[i].firstname << " " << persons[i].lastname << ", Do you wish to continue (Y/N) ? ";
            if (displayYesNoChoice()) {
                persons.erase (persons.begin() + i);
                rewriteDataFile(persons);
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

    for(size_t i = 0; i < persons.size(); ++i) {
        if (persons[i].id == personId) {
            cout << "You are modifing: " <<  persons[i].firstname << " " << persons[i].lastname << " data." << endl;
            if (personsDataType == DataType(firstname)) {
                cout << "Current firstname: " << persons[i].firstname << endl;
                cout << "Type new firstname: ";

                tempFirstname = getLineString();
                tempFullname.append(tempFirstname);
                tempFullname.append(" ");
                tempFullname.append(persons[i].lastname);

                if(searchTableByString(tempFullname, DataType(fullname), persons)) {
                    cout << "The specified firstname & lastname is already in use for an existing user(s)!" << endl;
                    cout << "Do you wish to continue (Y/N)?";
                    if(!displayYesNoChoice()) {
                        return;
                    }
                }
                persons[i].firstname = tempFirstname;
                cout << "Firstname sucessfully changed to: " << persons[i].firstname << endl;
                displayPausePrompt();
            } else if (personsDataType == DataType(lastname)) {
                cout << "Current lastname: " << persons[i].lastname << endl;
                cout << "Type new lastname: ";

                tempLastname = getLineString();
                tempFullname.append(persons[i].firstname);
                tempFullname.append(" ");
                tempFullname.append(tempLastname);

                if(searchTableByString(tempFullname, DataType(fullname), persons)) {
                    cout << "The specified firstname & lastname is already in use for an existing user(s)!" << endl;
                    cout << "Do you wish to continue (Y/N)?";
                    if(!displayYesNoChoice()) {
                        return;
                    }
                }

                persons[i].lastname = tempLastname;

                cout << "Lastname sucessfully changed to: " << persons[i].lastname << endl;
                displayPausePrompt();
            } else if (personsDataType == DataType(phone)) {
                cout << "Current phone No.: " << persons[i].phone << endl;
                cout << "Type new phone No.: ";
                tempPhone = removeSpacesAndDashesFromString(getLineString());
                if(searchTableByString(tempPhone, DataType(phone), persons)) {
                    cout << "The specified phone number is already in use for an existing user(s)!" << endl;
                    cout << "Do you wish to continue (Y/N)?";
                    if(!displayYesNoChoice()) {
                        return;
                    }
                }
                persons[i].phone = tempPhone;
                cout << "Phone No. sucessfully changed to: " << persons[i].phone << endl;
                displayPausePrompt();
            } else if (personsDataType == DataType(email)) {
                cout << "Current e-mail: " << persons[i].email << endl;
                cout << "Type new e-mail: ";
                tempEmail = getLineString();
                if(searchTableByString(tempEmail, DataType(email), persons)) {
                    cout << "The specified email is already in use for an existing user(s)!" << endl;
                    cout << "Do you wish to continue (Y/N)?";
                    if(!displayYesNoChoice()) {
                        return;
                    }
                }
                persons[i].email = tempEmail;
                cout << "e-mail sucessfully changed to: " << persons[i].email << endl;
                displayPausePrompt();
            } else if (personsDataType == DataType(address)) {
                cout << "Current address: " << persons[i].address << endl;
                cout << "Type new address: ";
                persons[i].address = getLineString();
                cout << "Address sucessfully changed to: " << persons[i].address << endl;
                displayPausePrompt();
            }
        }
    }
}

void modifyPerson(vector <Person>& persons) {
    char menuSelection;
    int personId;
    bool personFound = false;

    do {
        cout << "Input proper person ID to modify : ";
        personId = getLineInt();
    } while((personId < 1 ) || (personId > persons.back().id));

    for(size_t i = 0; i < persons.size(); ++i) {
        if (persons[i].id == personId) {
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
                    displayRecordByTableIndex(persons[i]);
                    displayPausePrompt();
                    break;
                case '9':
                    rewriteDataFile(persons);
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
