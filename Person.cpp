#include "Person.h"
#include <cstring>
#include <iostream>

int PersonID::getSeries() const {
    return series;
}

int PersonID::getNumber() const {
    return number;
}

std::string PersonID::getID() const {
    return std::to_string(series) + " " + std::to_string(number);
}

void PersonID::increaseID() {
    if (lastNumber == 9) {
        ++lastSeries;
        lastNumber = 0;
    }
    series = lastSeries;
    number = lastNumber++;
}

std::string Person::getID() const {
    return personID.getID();
}

int Person::getSeries() const {
    return personID.getSeries();
}

int Person::getNumber() const {
    return personID.getNumber();
}

std::string Person::getFullName() const {
    return firstName + " " + secondName + " " + thirdName;
}

std::string Person::getFirstName() const {
    return firstName;
}

std::string Person::getSecondName() const {
    return secondName;
}

std::ostream& operator<<(std::ostream& os, const Person& person) {
    os << "| ";
    if (person.thirdName == "" && person.dateOfBirth == "") {
        os << person.firstName << " " << person.secondName;
    }
    if (person.thirdName == "") {
        os << person.firstName << " " << person.secondName << " " << person.dateOfBirth;
    } else {
        os << person.firstName << " " << person.secondName << " " << person.thirdName << " " << person.dateOfBirth;
    }
    os << " ID: " << person.getID() << " |";
    return os;
}

std::istream& operator>>(std::istream& is, Person& person) {
    if (person.firstName != "") return is;
    std::cout << "\nFirst name = ";
    is >> person.firstName;
    std::cout << "Second name = ";
    is >> person.secondName;
    std::cout << "Date of birth = ";
    is >> person.dateOfBirth;
    person.personID.increaseID();
    return is;
}

bool operator<(const Teacher& teacher, const Student& student) {
    return false;
}

bool operator>(const Teacher& teacher, const Student& student) {
    return true;
}

bool operator<(const Student& student, const Teacher& teacher) {
    return true;
}

bool operator>(const Student& student, const Teacher& teacher) {
    return false;
}

bool operator<(const Teacher& firstTeacher, const Teacher& secondTeacher) {
    if (firstTeacher.getSeries() < secondTeacher.getSeries()) return true;
    if (firstTeacher.getSeries() > secondTeacher.getSeries()) return false;
    if (firstTeacher.getNumber() < secondTeacher.getNumber()) return true;
    return false;
}

bool operator<(const Student& firstStudent, const Student& secondStudent) {
    if (firstStudent.getSeries() < secondStudent.getSeries()) return true;
    if (firstStudent.getSeries() > secondStudent.getSeries()) return false;
    if (firstStudent.getNumber() < secondStudent.getNumber()) return true;
    return false;
}

bool operator>(const Teacher& firstTeacher, const Teacher& secondTeacher) {
    if (firstTeacher.getSeries() < secondTeacher.getSeries()) return false;
    if (firstTeacher.getSeries() > secondTeacher.getSeries()) return true;
    if (firstTeacher.getNumber() < secondTeacher.getNumber()) return false;
    return true;
}

bool operator>(const Student& firstStudent, const Student& secondStudent) {
    if (firstStudent.getSeries() < secondStudent.getSeries()) return false;
    if (firstStudent.getSeries() > secondStudent.getSeries()) return true;
    if (firstStudent.getNumber() < secondStudent.getNumber()) return false;
    return true;
}
