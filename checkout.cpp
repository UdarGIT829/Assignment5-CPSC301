// Viraat Udar
// 301
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include "person.cpp"
#include "book.cpp"

using namespace std;

void printMenu()
{
    cout << "----------Library Book Rental System----------" << endl;
    cout << "1.  Book checkout" << endl;
    cout << "2.  Book return" << endl;
    cout << "3.  View all available books" << endl;
    cout << "4.  View all outstanding rentals" << endl;
    cout << "5.  View outstanding rentals for a cardholder" << endl;
    cout << "6.  Open new library card" << endl;
    cout << "7.  Close library card" << endl;
    cout << "8.  Exit system" << endl;
    cout << "Please enter a choice: ";
}

/* You are not obligated to use these function declarations - they're just given as examples
*/
void readBooks(vector<Book *> &myBooks) // myBooks will contain pointers to Books
{
    //Input from books.txt
    string title;
    string author;
    string category;
    int bookID;
    string line;

    fstream booksFile;
    booksFile.open("books.txt");
    if (booksFile)
    {
        while (booksFile >> bookID)
        {
			getline(booksFile, line);
            getline(booksFile, title);
            //cout << title <<endl;
            getline(booksFile, author);
            getline(booksFile, category);
            getline(booksFile, line);
            Book *bookPtr = nullptr;
            bookPtr = new Book(bookID, title, author, category);
			bookPtr->setPersonPtr(nullptr);

            myBooks.push_back(bookPtr);
            //cout << bookPtr->getTitle();
            //cout << myBooks.size() <<endl;

        }
    }

    booksFile.close();

    return;
}

int readPersons(vector<Person *> &myCardholders)
{
    //Input from persons.txt
    int cardID;
    int active;
    string fName;
    string lName;
    string line;
    int lastID = 0;
    fstream personFile;
    personFile.open("persons.txt");
    if (personFile)
    {
        while (personFile >> cardID >> active >> fName >> lName)
        {
            getline(personFile, line);
            Person *personPtr = nullptr;
            personPtr = new Person(cardID, active, fName, lName);
            myCardholders.push_back(personPtr);
            lastID = personPtr->getId();
            //cout << lastID << endl;
        }
        lastID += 1;
    }

    personFile.close();
	
    return lastID;
}

void readRentals(vector<Book *> &myBooks, vector<Person *> myCardholders)
{
    int bookID;
    int personID;
    Person *personPtr;
    Book *bookPtr;

    fstream rentalFile;
    rentalFile.open("rentals.txt");
    if (rentalFile)
    {
        //

        while (rentalFile >> bookID >> personID)
        {

            for (int i = 0; i < myCardholders.size(); i++)
            {

                if (myCardholders[i]->getId() == personID)
                {
                    personPtr = myCardholders[i];
                }
            }

            for (int j = 0; j < myBooks.size(); j++)
            {
                if (myBooks[j]->getId() == bookID)
                {
                    bookPtr = myBooks[j];
                }
            }
            bookPtr->setPersonPtr(personPtr);
            //cout << bookPtr->getTitle();
        }
    }

    rentalFile.close();

    return;
}

Person *searchPerson(vector<Person *> &myCardHolders, int cardID){

            for(int i = 0;i < myCardHolders.size();i++){
                if(myCardHolders.at(i)->getId() == cardID){
                        return myCardHolders.at(i);
                    }
                }
    return nullptr; 
}

Person *searchPersonByName(vector<Person *> &myCardHolders, string fName, string lName){

            for(int i = 0;i < myCardHolders.size();i++){
                if((myCardHolders.at(i)->getFirstName() == fName)&&(myCardHolders.at(i)->getLastName() == lName)){
                        return myCardHolders.at(i);
                    }
                }
    return nullptr; 
}

int openCard(vector<Person *> &myCardholders, int nextID)
{
    //Adds to persons.txt
    string fName, lName;
    string activationChoice;
    Person *personPtr = searchPerson(myCardholders, nextID);
    if(personPtr == nullptr){
        cout << "Enter your first name" << endl;
        cin >> fName;
        cout << "Enter your last name" << endl;
        cin >> lName;
        Person *personPtr = new Person(nextID, true, fName, lName);
        myCardholders.push_back(personPtr);
        cout << "Your card is active!" << endl;
        cout << "Your card ID is : " << nextID << endl;
        nextID +=1;
    }
    else{
		cout << "Your card is already active!" << endl;
    }
    return nextID;
}

Book *searchBook(vector<Book *> myBooks, int id)
{
    //Returns book that whose ID was found in search vector
    //Call from Helper functions
    for(int i = 0;i < myBooks.size();i++){
                if(myBooks.at(i)->getId() == id){
                    return myBooks.at(i);
                    }
                }
    return nullptr;
}


void checkoutBook(vector<Book *> &myBooks, int bookID, vector<Person *> &myCardHolders, int cardID)
{
    //First Helper function

    //Pass appropriate parameters to searchBook to find book

    //Then check that the book hasnt already been checked out

    //Then change the peoplePtr to the checking out person, and display the appropriate info

    Book *bookPtr = searchBook(myBooks, bookID);
    if(bookPtr == nullptr){
        cout << "That book does not exist!" << endl;
    }
    else{
        if(bookPtr->getPersonPtr() == nullptr){
            cout << "This book has not been checked out";
            Person *personPtr = searchPerson(myCardHolders, cardID);
            if(personPtr != nullptr){
                bookPtr->setPersonPtr(personPtr);
                cout << "You have now checked out this fantastic book" << endl;
            }
            else{
                cout << "You do not have a library card!" << endl;
            }
        }
    }

    return;
}

void returnBook(vector<Book *> &myBooks, int bookID, vector<Person *> &myCardHolders, int cardID)
{
    //Second Helper Function
    //Pass appropriate parameters to searchBook to find book
    //Then check that the book has been checked out
    //Then change the peoplePtr to NULL, and display the appropriate info
    Book *bookPtr =  searchBook(myBooks, bookID);
        if(bookPtr->getPersonPtr() == nullptr){
                    bookPtr->setPersonPtr(nullptr);
                    cout << "You have returned : " << bookPtr->getTitle() << endl;
                }
    return;
}

void viewAllBooks(vector<Book *> &myBooks)
{
    for(int i = 0;i < myBooks.size();i++){
            cout << myBooks.at(i)->getTitle() << endl;
        
    }

    cout << "End of list reached." << endl;
    //Third Helper Function

    //Iterate through the vector
    //Check info to see if empty, If not
    // display the info

    //When empty display end of list

    return;
}

void viewAllRentals(vector<Book *> &myBooks, vector<Person *> &myCardHolders)
{
    //Forth Helper Function
    //Iterate through the vector
    //Check info
        for(int i = 0;i < myBooks.size();i++){
        if(myBooks.at(i)->getPersonPtr() != nullptr){
            cout << myBooks.at(i)->getTitle() << endl;
        }
    }

    cout << "End of list reached." << endl;

    return;
}

void viewCertainRentals(vector<Book *> &myBooks, vector<Person *> &myCardHolders, int cardID)
{
    //Fifth helper function

    //iterate through myCardHolders for the ptr that matches cardID

    //Iterate through myBooks for the ptr that was found before

    //Display every time there is a match and keep track of how many

    for(int i = 0;i < myBooks.size();i++){
        if((myBooks.at(i)->getPersonPtr() != nullptr)&&(myBooks.at(i)->getId()==cardID)){
            cout << myBooks.at(i)->getTitle();
        }
    }

    cout << "End of list reached." << endl;


}

void closeCard(vector<Person *> &myCardHolders, int cardID)
{
    string fName;
    string lName;
    bool notActive = 0;
        cout << "Enter your first name" << endl;
        cin >> fName;
        cout << "Enter your last name" << endl;
        cin >> lName;



    Person *personPtr = searchPersonByName(myCardHolders,fName,lName);
    personPtr->setActive(notActive);


    // Search myCardHolders for cardID

    //If the name exists then send it back here.

    //Confirm with user that the card should be deactivated.

    return;
}

void saveAndQuit(vector<Book *> &myBooks, vector<Person *> &myCardHolders)
{

    //Save myBooks to books.txt

    //Save myCardHolders to persons.txt

    //run viewAllRentals()

    fstream booksFile;
    booksFile.open("books.txt");
	fstream personsFile;
	personsFile.open("persons.txt");
    for(int i = 0;i < myBooks.size();i++){
		booksFile << myBooks.at(i)->getId() << endl;
		booksFile << myBooks.at(i)->getTitle() << endl;
		booksFile << myBooks.at(i)->getAuthor() << endl;
		booksFile << myBooks.at(i)->getCategory() << endl;
		booksFile << endl;
	}
	for(int j = 0; j < myCardHolders.size(); j++){
		personsFile << myCardHolders.at(j)->getId() << " " << myCardHolders.at(j)->isActive() << " " << myCardHolders.at(j)->fullName() << endl;
	}



    return;
}



int main()
{
    vector<Book *> books;
    vector<Person *> cardholders;
    int lastID = 0;
    int bookID;
    int cardID;


    readBooks(books); // inputs from books.txt and fills books vector
    lastID = readPersons(cardholders);// inputs from persons.txt and fills cardholders vector
    readRentals(books, cardholders);
	
    int choice;
    do
    {
        // If you use cin anywhere, don't forget that you have to handle the <ENTER> key that
        // the user pressed when entering a menu option. This is still in the input stream.
        printMenu();
        cin >> choice;
        switch (choice)
        {
        case 1:
            // Book checkout
            cout << "You are now checking out a book!" << endl;
            cout << "Enter the book ID : ";
            cin >> bookID;
            cout << "Enter the card ID : ";
            cin >> cardID;
            checkoutBook(books,bookID,cardholders,cardID);
            break;

        case 2:
			cout << "You are now returning a book!" << endl;
            cout << "Enter the book ID : ";
            cin >> bookID;
            cout << "Enter the card ID : ";
            cin >> cardID;
            returnBook(books, bookID, cardholders, cardID);
            break;

        case 3:
			cout << "Will now display all books in the library!" << endl;
            // View all available books
            viewAllBooks(books);
            break;

        case 4:
            // View all outstanding rentals
            cout << "Will now display all books that have been rented!" << endl;
            viewAllRentals(books,cardholders);
            break;

        case 5:
            // View outstanding rentals for a cardholder
            cout << "Will now display books that have been rented by the card ID." << endl;
            cout << "Enter the Card ID: ";
            cin >> cardID;
            viewCertainRentals(books,cardholders,cardID); // cin >> cardID
            break;

        case 6:
            // Open new library card
            cout << "Will now open a library card or reactivate your existing card." << endl;
            openCard(cardholders, lastID); 
            break;

        case 7:
            // Close library card
            cout << "Will deactivate the library card!" << endl;
            cout << "Enter your Card ID : " << endl;
            cin >> cardID;
            closeCard(cardholders,cardID); //cin >> cardID
            break;

        case 8:
            // Must update records in files here before exiting the program
            saveAndQuit(books,cardholders);
            break;

        default:
            cout << "Invalid entry" << endl;
            break;
        }
        cout << endl;
    } while (choice != 8);

    return 0;
}
