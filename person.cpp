/* 
Created: Viraat Udar
Description: This file delineates helper functions that provide access to private variables that 
    would belong to objects of the type "Person"

*/
#include "person.h"

Person::Person(int cardNo, bool act, string fName, string lName) {
    firstName = fName;
    lastName = lName;
    cardID = cardNo;
    active = act;
}

string Person::getFirstName() {
    return firstName; 
}

string Person::getLastName() {
    return lastName; 
}

int Person::getId() {
    return cardID; 
}

void Person::setActive(bool act) {
    active = act;
    return;
} 

bool Person::isActive() {
    return active; 
}

string Person::fullName() {
    string fuName = firstName + " " + lastName;
    return fuName; 
}
