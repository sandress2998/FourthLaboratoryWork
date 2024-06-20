#include <iostream>
#include <cstring>

// почти весь класс Person и PersonID взят из третьей лабораторной
// добавлены операторы сравнения.
class PersonID {
private:
    inline static int lastNumber;
    inline static int lastSeries;
    int number;
    int series;
public:
    PersonID() {}

    int getSeries() const;

    int getNumber() const;

    std::string getID() const;

    void increaseID();
};

class Person {
private:
    PersonID personID;
    std::string firstName = "";
    std::string secondName = "";
    std::string thirdName = "";
    std::string dateOfBirth = "";

public:
    Person() {}

    Person(std::string firstName, std::string secondName, std::string thirdName, std::string dateOfBirth): firstName(firstName), secondName(secondName), thirdName(thirdName), dateOfBirth(dateOfBirth) {
        personID.increaseID();
    }

    Person(std::string firstName, std::string secondName, std::string dateOfBirth): firstName(firstName), secondName(secondName), dateOfBirth(dateOfBirth) {
        personID.increaseID();
    }

    Person(std::string firstName, std::string secondName): firstName(firstName), secondName(secondName) {
        personID.increaseID();
    }

    Person(const Person& other): firstName(other.firstName), secondName(other.secondName) {}

    virtual ~Person() {} // добавлено, чтобы создать vtable(если развивать программу).

    std::string getID() const;

    int getSeries() const;

    int getNumber() const;

    std::string getFullName() const;

    std::string getFirstName() const;

    std::string getSecondName() const;

    friend std::ostream& operator<<(std::ostream& os, const Person& person); // т.е. мы просто объявляем friend-функцию, которая не является методом.

    friend std::istream& operator>>(std::istream& is, Person& person);
};

class Teacher: public Person {
public:
    using Person::Person;
};

class Student: public Person {
public:
    using Person::Person;
};

bool operator<(const Teacher& teacher, const Student& student);

bool operator>(const Teacher& teacher, const Student& student);

bool operator<(const Student& student, const Teacher& teacher);

bool operator>(const Student& student, const Teacher& teacher);

bool operator<(const Teacher& firstTeacher, const Teacher& secondTeacher);

bool operator<(const Student& firstStudent, const Student& secondStudent);

bool operator>(const Teacher& firstTeacher, const Teacher& secondTeacher);

bool operator>(const Student& firstStudent, const Student& secondStudent);
