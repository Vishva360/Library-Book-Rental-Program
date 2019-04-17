// Vishva Patel
// Section #2
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include "person.cpp"
#include "book.cpp"

using namespace std;

//Person * findPerson(personVec, cardID)
void viewBooks(vector<Book *> myBooks);
int readPersons(vector<Person *> & cardholders);
void readBooks(vector<Book *> & books);
void bookReturn(vector<Book *> &books, int & id);
void bookCheckout(vector<Book *> & books, vector<Person *> & cardholders);
void viewHolderRentals(vector<Book *> myBooks, int id);
void printMenu() {
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
/*
 You are not obligated to use these function declarations - they're just given as examples
void readBooks(vector<Book *> & myBooks) {
    return;
}

int readPersons(vector<Person *> & myCardholders) {
    return 0;
}

void readRentals(vector<Book *> & myBooks, vector<Person *> myCardholders) {
    return;
}

void openCard(vector<Person *> & myCardholders, int nextID) {
    return;
}

Book * searchBook(vector<Book *> myBooks, int id) {
    return nullptr;
}
*/

int main()
{
    int id = 0;
    vector<Book *> books;
    vector<Person *> cardholders;
    readBooks(books);
    readPersons(cardholders);

    int choice;
    do
    {
        // If you use cin anywhere, don't forget that you have to handle the <ENTER> key that
        // the user pressed when entering a menu option. This is still in the input stream.
        printMenu();
        cin >> choice;
        switch(choice)
        {
            case 1:
                bookCheckout(books, cardholders);
                // Book checkout
                break;

            case 2:
                 bookReturn(books,id);
                // Book return
                break;

            case 3:
                viewBooks(books);
                // View all available books
                break;

            case 4:

                // View all outstanding rentals
                break;

            case 5:
            {
            cout << "Please enter the card ID: ";
              int id;
              cin >> id;
              bool validate = false;
              for (int i = 0; i < cardholders.size(); i++) {
                  if(cardholders.at(i)->getId() == id) {
                      string cardholder = cardholders.at(i)->fullName();
                      validate = true;
                      break;
                  }
              }
              if (validate == false) {
                cout << "Card ID not found";
              }
              else {
                cout << endl;
                viewHolderRentals(books, id);
              }
              break;
                // View outstanding rentals for a cardholder
              }


            case 6:
                // Open new library card
                break;

            case 7:
                // Close library card
                break;

            case 8:
                // Must update records in files here before exiting the program
                break;

            default:
                cout << "Invalid entry" << endl;
                break;
        }
        cout << endl;
   } while(choice != 8);
      return 0;
}
void readBooks(vector<Book *> & books){
  ifstream inData;
  int id;
  string bookName;
  string auth;
  string cat;
  string line;

  inData.open("books.txt", ios::in);

  while(inData >> id){
    getline(inData,line);
    getline(inData,bookName);
    getline(inData,auth);
    getline(inData,cat);

    Book * temp = new Book(id, bookName, auth, cat);
    books.push_back(temp);

    //cout << temp->getId()<< endl << temp->getTitle() << endl << temp->getAuthor() << endl << temp->getCategory() << endl;
  }



inData.close();
}


int readPersons(vector<Person *> & cardholders){
  ifstream inData;
  int cardNo;
  bool active;
  string fName;
  string lName;

  inData.open("persons.txt", ios::in);
  while(inData >> cardNo){
    inData >> active >> fName >> lName;
    Person * temp = new Person(cardNo, active,fName,lName);
    cardholders.push_back(temp);
  //  cout << cardNo << " " << temp->isActive() << " " << temp->fullName() << endl;
  }
  inData.close();
}
void bookReturn(vector<Book *> & books, int & id) {
      cout << "Please enter the book ID to return:" << endl;
      cin >> id;
      bool validID = false;
      for (int i = 0; i < books.size(); i++) {
          if (id == books.at(i)->getId()) {
              cout << "Title: " << books.at(i)->getTitle() << endl;
              cout << "Return Completed" << endl;
              validID = true;
        }
    }
      if (validID == false) {
          cout << "Book ID not found" << endl;
    }

}

void bookCheckout(vector<Book *> &books, vector<Person *> &cardholders){

              int id = 0;

              bool validate = false;
              string cardholder;

                cout << "Please enter the card ID: ";
                cin >> id;
              for (int i = 0; i < cardholders.size(); i++) {
                  if(cardholders.at(i)->getId() == id) {
                     cardholder = cardholders[i]->fullName();
                      validate = true;
                      break;
                  }
                }
                if (validate == false) {
                  cout << "Card ID not found" << endl;
                  return;
                }
                validate = false; // reset

              cout << "Cardholder: " << cardholder << endl;
              cout << "Please enter the book ID: ";
              int bookId;
              cin >> bookId;
              string title;
            for(int i = 0; i < books.size(); i++){
              if(books.at(i)->getId() == bookId){
                title = books[i]->getTitle();
                validate = true;
                break;
              }
            }
              if(validate == false){
                cout << "Book ID not found" << endl;
                return;
              }

              cout << "Title:  " << title << endl;
              cout << "Rental Completed " << endl;


}
void returnBook(vector<Book *> books, int id) {
  	for (int i = 0; i < books.size(); i++) {
      	if(books.at(i)->getId() == id) {
        		if(books.at(i)->getPersonPtr() != NULL) {
              	books.at(i)->setPersonPtr(nullptr);
              	cout << "Return Completed" << endl;
              	return;
            }
          	else{
            		cout << "Book is not checked out!" << endl;
            }
        }
    }
		cout << "Book ID not found" << endl;
  	return;
}

void viewBooks(vector<Book *> myBooks) {
  	bool found = false;
  	for(int i = 0; i < myBooks.size(); i++) {
      	if(myBooks.at(i)->getPersonPtr() == NULL) {
          	cout << "Book ID: " << myBooks.at(i)->getId() << endl;
          	cout << "Title: " << myBooks.at(i)->getTitle() << endl;
          	cout << "Author: " << myBooks.at(i)->getAuthor() << endl;
          	cout << "Category: " << myBooks.at(i)->getCategory() << endl;
            cout << endl;
          	found = true;
        }
    }
  	if(found == false) {
      	cout << "No available books" << endl;
    }
  	return;
}

void viewHolderRentals(vector<Book *> myBooks, int id) {
  	bool checkedOut = false;
  	for (int i = 0; i < myBooks.size(); i++) {
      	Person * cardholder = myBooks.at(i)->getPersonPtr();
        if(cardholder->getId() == id) {
          	cout << "Books ID: " << myBooks.at(i)->getId() << endl;
          	cout << "Title: " << myBooks.at(i)->getTitle() << endl;
          	cout << "Author: " << myBooks.at(i)->getAuthor() << endl;
          	cout << endl;
          	checkedOut = true;
        }
    }
  	if (checkedOut == false) {
        cout << "No books currently checked out" << endl;
    }
    return;
}
/*
Person * findPerson(personVec, cardID){
  for()
  if card are equal return pointer
}
// if i made it here, i did not find the card so:
return nullptr;
}
*/
