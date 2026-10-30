#pragma once
#include <string>
#include <iostream>

using namespace std;

class IObject
{
private:
    static int contor; // partajat de toate instantele

protected:
    const int id; // unic per obiect, imutabil

    // Constructorul este protected: IObject nu se instantiaza direct, numai prin derivate.
    IObject() : id(++contor) {}

    // Copy constructor: id-ul NOU la copiere (fiecare copie e un obiect nou)
    IObject(const IObject &) : id(++contor) {}
    IObject &operator=(const IObject &alt) noexcept { return *this; }

    // REZOLVAREA ERORII:
    // Definim explicit operatorul de atribuire pentru a permite derivatelor să îl folosească.
    // ID-ul fiind unic și constant, NU trebuie copiat/suprascris!

public:
    virtual ~IObject() noexcept = default;
    int getId() const noexcept { return id; }
    virtual std::string toString() const = 0;

    // operator<< apeleaza toString() polimorfic
    friend ostream &operator<<(ostream &os, const IObject &obj) { return os << obj.toString(); }

    // operator== compara id-urile (identitate, nu valoare)
    bool operator==(const IObject &alt) const noexcept { return id == alt.id; }
};