#include <vector>
#include <climits>
#include <iostream>
#include <algorithm>

using namespace std;

// Animal Inheritance, 20181115
class Animal {
protected:
    bool isMammal;
    bool isCarnivorous;

public:
    Animal(bool isMammal, bool isCarnivorous) {
        this->isMammal = isMammal;
        this->isCarnivorous = isCarnivorous;
    }

    bool getIsMammal() {
        return this->isMammal;
    }

    bool getIsCarnivorous() {
        return this->isCarnivorous;
    }

    virtual string getGreeting() = 0;

    void printAnimal(string name) {
        cout << "A " << name << " says '" << this->getGreeting()
             << "', is " << (this->getIsCarnivorous() ? "" : "not ")
             << "carnivorous, and is " << (this->getIsMammal() ? "" : "not ")
             << "a mammal." << endl;
    }
};

/**
 *   Dog class
 **/
class Dog : public Animal {
public:
    Dog() : Animal(true, true) {

    }

    string getGreeting() {
        return "ruff";
    }
};

/**
 *   Cow class
 **/
class Cow : public Animal {
public:
    Cow() : Animal(true, false) {

    }

    string getGreeting() {
        return "moo";
    }
};

/**
 *   Duck class
 **/
class Duck : public Animal {
public:
    Duck() : Animal(false, false) {

    }

    string getGreeting() {
        return "quack";
    }
};

int main(int argc, char **argv) {

    Dog dog;
    Animal *pointer = &dog;
    dog.printAnimal("dog");

    Cow cow;
    pointer = &cow;
    cow.printAnimal("cow");

    Duck duck;
    pointer = &duck;
    duck.printAnimal("duck");

    return 0;
}
