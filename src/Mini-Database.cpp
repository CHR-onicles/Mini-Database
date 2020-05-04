//Mini Database project with a few upgrades
#include <iostream>
#include <conio.h> //for _getch()...apparently getch() is deprecated
#include <fstream>
#include <limits>
using namespace std;

struct Person {
    string fname;
    string surname;
    short age = 0; //used short because of range
    string pnumber;
};

//default stuff
const short MAX_PEOPLE = 20;
Person people[MAX_PEOPLE]; //Person array of 20 people
short PeopleInDatabase; //initialized to 0 by default

//prototypes
void title();
void pressEnter();
void firstLetterCaps(string&);
void clearAndIgnore();
//void checkForText(string&); //kinda hard to implement
void addPerson();
void displayPeople();
void menu();
void saveToFile();
void loadPeopleFromFile();
void searchForPerson();
void removePerson();
void clearDatabase();

//damn this main's cute lol...literally the smallest main i've ever coded XD
int main() {
    title();
    loadPeopleFromFile();
    menu();
    return 0;
}

//title
void title() {
    cout << "WELCOME TO CHR DATABASE SERVICE" << endl;   //pfftt lame ik...
    cout << "-------------------------------" << endl << endl;
}

//function to convert first letter to uppercase and the rest lowercase
void firstLetterCaps(string& word) {
    word[0] = toupper(word[0]);
    for (size_t i{ 1 }; i < word.length(); ++i) {
        word[i] = tolower(word[i]);
    }
}

//function to pause, ask user to press Enter and clear screen before proceeding with program
void pressEnter() {
    cout << "Press Enter to continue..." << endl;
    while (_getch() != 13); //13 - Enter in ASCII
    system("cls");
}

/*function to clear input error flags and ignore previous input in buffer.
had to do this because the repetition was getting too much */
void clearAndIgnore() {
    cin.clear();
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
}

//function to add people to database
void addPerson() {
    if (PeopleInDatabase == 20) {
        cerr << "Max number of people reached!" << endl;
    }
    else {
        cout << "How many people do you want to add?: ";
        char peopleToAdd = cin.peek();
        if (peopleToAdd > '0' && peopleToAdd < '9') { //making sure user entered numbers..checking with ascii characters
            short peopleToAdd{}; //coincidence?...i think not...
            cin >> peopleToAdd;
            if ((peopleToAdd + PeopleInDatabase) > MAX_PEOPLE)
                cerr << "Error: exceeding max boundary!" << endl;
            else {
                clearAndIgnore();
                for (short i{ 0 }; i < peopleToAdd; ++i) {
                    bool istext = false;
                    bool isnum = false;

                    do {
                        cout << "Enter first name: ";
                        char check = cin.peek();
                        if ((check > 'a' && check < 'z') || (check > 'A' && check < 'Z')) {
                            cin >> people[PeopleInDatabase].fname;
                            firstLetterCaps(people[PeopleInDatabase].fname);
                            clearAndIgnore();
                            istext = true;
                        }
                        else {
                            cerr << "Name should be text!" << endl;
                            clearAndIgnore();
                            istext = false;
                        }
                    } while (!istext);

                    istext = false;

                    do {
                        cout << "Enter surname: ";
                        char check = cin.peek();
                        if ((check > 'a' && check < 'z') || (check > 'A' && check < 'Z')) {
                            cin >> people[PeopleInDatabase].surname;
                            firstLetterCaps(people[PeopleInDatabase].surname);
                            clearAndIgnore();
                            istext = true;
                        }
                        else {
                            cerr << "Name should be text!" << endl;
                            clearAndIgnore();
                            istext = false;
                        }
                    } while (!istext);

                    do {
                        cout << "Enter age: ";
                        char num = cin.peek();
                        if (num > '0' && num < '9') {
                            cin >> people[PeopleInDatabase].age;
                            clearAndIgnore();
                            isnum = true;
                        }
                        else {
                            cerr << "Age should be a number!" << endl;
                            clearAndIgnore();
                            isnum = false;
                        }
                    } while (!isnum);

                    cout << "Enter phone number: "; //no verification for you LMAO XD... but mostly should be numbers
                    cin >> people[PeopleInDatabase].pnumber;
                    clearAndIgnore();
                    cout << "\nPerson added successfully!" << endl;
                    PeopleInDatabase++;
                }
            }
        }
        else {
            cerr << "Invalid number!" << endl;
            clearAndIgnore();
        }
    }
}

//function to display people in database
void displayPeople() {
    if (PeopleInDatabase > 0) {
        for (int i{ 0 }; i < PeopleInDatabase; ++i) {
            cout << "\nPerson index: " << (i + 1) << endl;
            cout << "First name: " << people[i].fname << endl;
            cout << "Surname: " << people[i].surname << endl;
            cout << "Age: " << people[i].age << endl;
            cout << "Phone number: " << people[i].pnumber << endl;
        }
    }
    else
        cerr << "Database is empty!" << endl;
    cout << endl;
}

//function to save people to database
void saveToFile() {
    ofstream file;
    file.open("database.txt");
    if (!file) {
        std::cerr << "Error opening file!" << std::endl;
        exit(1);
    }
    if (PeopleInDatabase > 0) {
        file << PeopleInDatabase << endl;   //total number of people in database
        for (int i{ 0 }; i < PeopleInDatabase; ++i) {
            file << people[i].fname << endl;
            file << people[i].surname << endl;
            file << people[i].age << endl;
            file << people[i].pnumber << endl;
        }
        cout << "Saved successfully!" << endl;
    }
    else cerr << "Nothing to save!" << endl;
    file.close();
}

//function to load people from file
void loadPeopleFromFile() {
    ifstream file("database.txt");
    if (!file) {
        cerr << "Error opening file!" << endl;
        exit(1);
    }

    file.seekg(0, ios::end);    //setting pointer to end of file
    int filesize = file.tellg();    //get pointer location in bytes which is the size of file
    file.seekg(0, ios::beg);    //setting pointer back to beginning for reading
    if (filesize == 0) {
        cerr << "=> Nothing to load from database..." << endl << endl;
    }
    else {
        file >> PeopleInDatabase;   //loading back total number of people in database
        for (int i{ 0 }; i < PeopleInDatabase; ++i) {
            file >> people[i].fname;
            file >> people[i].surname;
            file >> people[i].age;
            file >> people[i].pnumber;
        }
        //using do-while loop, but for loop has less code soo...
       /*int i = 0;
       do {
           file >> people[i].fname;
           file >> people[i].surname;
           file >> people[i].age;
           file >> people[i].pnumber;
           i++;
       } while (!file.eof());*/

        cout << "=> People were loaded successfully from database..." << endl << endl;
        file.close();
    }
}

//function to search for a person in the database
void searchForPerson() {
    clearAndIgnore();
    if (PeopleInDatabase > 0) {
        string name;
        bool found = false;
        bool istext = false;
        do {
            cout << "Enter the name of the person to search for: ";
            char c = cin.peek();
            if (c > 'a' && c < 'z' || c > 'A' && c < 'Z') {
                cin >> name;
                firstLetterCaps(name);
                cout << "Results of search for " << name << " ..." << endl;
                clearAndIgnore();
                istext = true;
            }
            else {
                cerr << "Name needs to be text!" << endl;
                clearAndIgnore();
                istext = false;
            }
        } while (!istext);

        for (int i{ 0 }; i < PeopleInDatabase; ++i) {
            if (name == people[i].fname || name == people[i].surname) {
                cout << "\nPerson index: " << (i + 1) << endl;
                cout << "First name: " << people[i].fname << endl;
                cout << "Surname: " << people[i].surname << endl;
                cout << "Age: " << people[i].age << endl;
                cout << "Phone number: " << people[i].pnumber << endl;
                found = true;
            }
        }
        if (found == false)
            cout << "That person could not be found!" << endl;
    }
    else
        cerr << "Nothing to search for here!" << endl;
}

//function to remove a person from the database
void removePerson() {
    if (PeopleInDatabase > 0) {
        cout << "Who do you want to remove? Type index: ";
        short index;
        cin >> index;

        if (PeopleInDatabase >= index) {
            for (short i = index; i < PeopleInDatabase; ++i) {
                people[i - 1].fname = people[i].fname;
                people[i - 1].surname = people[i].surname;
                people[i - 1].age = people[i].age;
                people[i - 1].pnumber = people[i].pnumber;
            }
            PeopleInDatabase--;
            cout << "Delete successful!" << endl;
            saveToFile();
        }
        else cerr << "That index doesn't exist!" << endl;

    }
    else cerr << "No one to delete!" << endl;
}

//function to clear contents of database
void clearDatabase() {
    if (PeopleInDatabase > 0) {
        char x;
        do {
            cout << "Are you sure you want to remove all content in database?[Y/N]: " << endl;
            x = _getch();
            x = toupper(x);
        } while (x != 'Y' && x != 'N');

        if (x == 'Y') {
            fstream file;
            file.open("database.txt", ios::out | ios::trunc);
            if (!file) {
                std::cerr << "Error clearing database!" << std::endl;
                std::exit(1);
            }
            file.close();
            cout << "Database cleared successfully!" << endl;
            PeopleInDatabase = 0;
        }
        else if (x == 'N')
            cout << "Operation cancelled!" << endl;
    }
    else cerr << "Database is already empty!" << endl;
}

//menu of database...as if that isnt obvious smh
void menu() {
    char choice{};

    do {
        cout << "NUMBER OF PEOPLE IN DATABASE: " << PeopleInDatabase << endl;
        cout << "1 - Add Person to Database" << endl;
        cout << "2 - Display people in Database" << endl;
        cout << "3 - Save to database" << endl;
        cout << "4 - Load people from database" << endl;
        cout << "5 - Search for a person" << endl;
        cout << "6 - Remove a person" << endl;
        cout << "7 - Clear database" << endl;
        cout << "Esc - Exit" << endl;
        cout << "\nSelect an option: " << endl;
        choice = _getch(); // to instantly execute the choice instead of having to press Enter

        switch (choice) {
        case '1':
            addPerson();
            pressEnter();
            break;
        case '2':
            displayPeople();
            pressEnter();
            break;
        case '3':
            saveToFile();
            pressEnter();
            break;
        case '4':
            loadPeopleFromFile();
            pressEnter();
            break;
        case '5':
            searchForPerson();
            pressEnter();
            break;
        case '6':
            removePerson();
            pressEnter();
            break;
        case '7':
            clearDatabase();
            pressEnter();
            break;
        case 27:
            saveToFile();
            cout << "\nExiting program..." << endl << endl;
            break;
        default:
            cout << "Invalid option!" << endl << endl;
            clearAndIgnore();
            break;
        }
    } while (choice != 27); //27 - Escape ASCII
}