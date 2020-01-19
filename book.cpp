/* 
Created: Viraat Udar
Description: This file delineates helper functions that provide access to private variables that 
    would belong to objects of the type "Book"

*/
#include "book.h"

Book::Book(int id, string bookName, string auth, string cat) {
    bookID = id;
    title = bookName;
    author = auth;
    category = cat;
}

string Book::getTitle() {
    return title;
}

string Book::getAuthor() {
    return author;
}

string Book::getCategory() {
    return category; 
}

int Book::getId() {
    return bookID;
}
void Book::setPersonPtr(Person * ptr) {
    personPtr = ptr;
    return;
}

Person * Book::getPersonPtr() {
    return personPtr;
}
