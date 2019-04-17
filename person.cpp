#include "person.h"

Person::Person(int cardNo, bool act, string fName, string lName) {
    // complete constructor
    firstName = fName;
    lastName = lName;
    cardID = cardNo;
    active = act;
}

string Person::getFirstName() {
    return firstName; // complete
}

string Person::getLastName() {
    return lastName; // complete
}

int Person::getId() {
    return cardID; // complete
}

void Person::setActive(bool act) {
    active = act;
    return;
} // complete

bool Person::isActive() {
    return active; // complete
}

string Person::fullName() {
    string fuName = firstName + " " + lastName;
    return fuName; // complete
}
