#pragma once
#include <iostream>
#include <string>
#include <vector>
#include <memory>
#include <sstream>
#include "IObject.h"
#include "Exceptii.h"
#include "DesignPatterns.h"

using namespace std;

class Persoana : public IObject
{
protected:
    std::string nume;

public:
    Persoana(const std::string &n = "N/A") : nume(n) { cout << "[Persoana] Constructor apelat pentru: " << nume << endl; }
    virtual ~Persoana() noexcept = default;
    virtual void afiseazaRol() const = 0;
    virtual bool esteActiv() const = 0;
    std::string getNume() const { return nume; }
    void setNume(const std::string &n) { nume = n; }
};

class ContractInfo
{
private:
    int durataLuni;
    float salariuLunar;

public:
    ContractInfo();
    ContractInfo(int durata, float salariu);
    ContractInfo(int durata);
    ~ContractInfo() noexcept;

    friend ostream &operator<<(ostream &out, const ContractInfo &c);
    friend istream &operator>>(istream &in, ContractInfo &c);

    float operator[](int index) const;
    ContractInfo &operator++();
    ContractInfo operator++(int);
    ContractInfo operator+(float bonus);
    friend ContractInfo operator+(float bonus, const ContractInfo &c);
    bool operator==(const ContractInfo &c) const;
    bool operator<(const ContractInfo &c) const;

    int getDurata() const { return durataLuni; }
    float getSalariu() const { return salariuLunar; }
    void setDurata(int d)
    {
        if (d < 0)
            throw ExceptieContract("Durata in luni nu poate fi negativa!", d);
        durataLuni = d;
    }
    void setSalariu(float s)
    {
        if (s < 0)
            throw ExceptieContract("Salariul nu poate fi negativ!", s);
        salariuLunar = s;
    }
};

class Jucator : public Persoana
{
protected:
    char pozitie;
    float inaltime;
    int numar;
    bool starter;
    ContractInfo contract;

public:
    Jucator() : Persoana("N/A"), contract(12, 1000.0), pozitie('-'), inaltime(0.0), numar(0), starter(false) { cout << "[Jucator] Constructor apelat." << endl; }
    Jucator(const std::string &nume, char pozitie, float inaltime, int numar, bool starter, int luniContract, float salariuContract)
        : Persoana(nume), contract(luniContract, salariuContract), pozitie(pozitie), inaltime(inaltime), numar(numar), starter(starter)
    {
        if (numar < 0 || numar >= 100)
            throw ExceptieJucator("Numarul de tricou trebuie sa fie intre 0 si 99!", numar);
    }
    Jucator(const std::string &nume, char pozitie, float inaltime, int numar, bool starter)
        : Persoana(nume), contract(12, 2000.0), pozitie(pozitie), inaltime(inaltime), numar(numar), starter(starter)
    {
        if (numar < 0 || numar >= 100)
            throw ExceptieJucator("Numarul de tricou trebuie sa fie intre 0 si 99!", numar);
    }
    Jucator(const std::string &nume, char pozitie) : Persoana(nume), pozitie(pozitie), inaltime(0.0), numar(0), starter(false) {}
    Jucator(const std::string &nume, int numar) : Persoana(nume), pozitie('-'), inaltime(0.0), numar(numar), starter(false)
    {
        if (numar < 0 || numar >= 100)
            throw ExceptieJucator("Numarul de tricou trebuie sa fie intre 0 si 99!", numar);
    }
    Jucator(const std::string &nume, char pozitie, float inaltime) : Persoana(nume), pozitie(pozitie), inaltime(inaltime), numar(0), starter(false) {}
    Jucator(const Jucator &jucator) : Persoana(jucator), contract(jucator.contract), pozitie(jucator.pozitie), inaltime(jucator.inaltime), numar(jucator.numar), starter(jucator.starter) {}
    virtual ~Jucator() noexcept override { cout << "[Jucator] Destructor apelat." << endl; }

    Jucator &operator=(const Jucator &jucator)
    {
        if (this == &jucator)
            return *this;
        Persoana::operator=(jucator);
        contract = jucator.contract;
        pozitie = jucator.pozitie;
        inaltime = jucator.inaltime;
        numar = jucator.numar;
        starter = jucator.starter;
        return *this;
    }
    virtual void afiseazaRol() const override { cout << "Rol: JUCATOR. Nume: " << nume << " (Poarta numarul " << numar << ")" << endl; }
    virtual bool esteActiv() const override { return true; }
    std::string toString() const override
    {
        std::ostringstream out;
        out << "ID Jucator: " << getId() << "\n"
            << nume << " poarta numarul " << numar << "\nPozitie: " << pozitie << "\nInaltime: " << inaltime << " cm\nJoaca in starting lineup: " << (starter ? "DA" : "NU") << "\n";
        return out.str();
    }
    friend istream &operator>>(istream &in, Jucator &j)
    {
        std::string numeTemp;
        cout << "Introduceti numele jucatorului: ";
        in >> ws;
        std::getline(in, numeTemp);
        j.setNume(numeTemp);
        cout << "Introduceti pozitia jucatorului: (C/F/G) ";
        in >> j.pozitie;
        cout << "Introduceti inaltimea jucatorului: ";
        in >> j.inaltime;
        int nrTemp;
        cout << "Introduceti numarul jucatorului: ";
        in >> nrTemp;
        j.setNumar(nrTemp);
        cout << "Este acest jucator in starting lineup (1-DA/0-Nu): ";
        in >> j.starter;
        return in;
    }

    char getPozitie() const { return pozitie; }
    float getInaltime() const { return inaltime; }
    int getNumar() const { return numar; }
    bool getStarter() const { return starter; }

    void setNumar(int numar)
    {
        if (numar < 0 || numar >= 100)
            throw ExceptieJucator("Numarul de tricou trebuie sa fie intre 0 si 99!", numar);
        this->numar = numar;
    }
    void setPozitie(char pozitie)
    {
        if (pozitie == 'C' || pozitie == 'G' || pozitie == 'F')
            this->pozitie = pozitie;
    }

    char operator[](int index) const
    {
        if (index >= 0 && index < (int)this->nume.length())
            return this->nume[index];
        return '\0';
    }
    Jucator &operator++()
    {
        numar++;
        return *this;
    }
    Jucator operator++(int)
    {
        Jucator t = *this;
        numar++;
        return t;
    }
    bool operator==(const Jucator &j) const { return nume == j.nume && numar == j.numar; }
    bool operator<(const Jucator &j) const { return numar < j.numar; }
    friend Jucator operator+(float bonus, const Jucator &j) { return Jucator(j.nume, j.pozitie, j.inaltime + bonus, j.numar, j.starter); }
    friend Jucator operator+(const Jucator &j, float bonus) { return Jucator(j.nume, j.pozitie, j.inaltime + bonus, j.numar, j.starter); }
};

class Capitan : public Jucator
{
private:
    float bonusBani;

public:
    Capitan() : Jucator(), bonusBani(0.0) {}
    Capitan(const std::string &nume, char pozitie, float inaltime, int numar, bool starter, int luniContract, float salariuContract, float bonus)
        : Jucator(nume, pozitie, inaltime, numar, starter, luniContract, salariuContract)
    {
        if (bonus < 0)
            throw ExceptieContract("Bonusul capitanului nu poate fi negativ!", bonus);
        this->bonusBani = bonus;
    }
    Capitan(const std::string &nume, char pozitie, float inaltime, int numar, bool starter, float bonus)
        : Jucator(nume, pozitie, inaltime, numar, starter)
    {
        if (bonus < 0)
            throw ExceptieContract("Bonusul capitanului nu poate fi negativ!", bonus);
        this->bonusBani = bonus;
    }
    Capitan(const Capitan &c) : Jucator(c), bonusBani(c.bonusBani) {}
    virtual ~Capitan() noexcept override {}

    Capitan &operator=(const Capitan &c)
    {
        if (this == &c)
            return *this;
        Jucator::operator=(c);
        this->bonusBani = c.bonusBani;
        return *this;
    }
    virtual void afiseazaRol() const override { cout << "Rol: CAPITAN. Nume: " << nume << " (Poarta bandobanda de lider si numarul " << numar << ")" << endl; }
    std::string toString() const override
    {
        std::ostringstream out;
        out << Jucator::toString() << "Functie suplimentara: Capitanul echipei\nBonus de capitan: " << bonusBani << " $\n";
        return out.str();
    }
    friend istream &operator>>(istream &in, Capitan &c)
    {
        in >> static_cast<Jucator &>(c);
        float bonusTemp;
        cout << "Introduceti bonusul de capitan ($): ";
        in >> bonusTemp;
        c.setBonusBani(bonusTemp);
        return in;
    }

    float getBonusBani() const { return bonusBani; }
    void setBonusBani(float bonus)
    {
        if (bonus < 0)
            throw ExceptieContract("Bonusul capitanului nu poate fi negativ!", bonus);
        this->bonusBani = bonus;
    }
    Capitan operator+(float suma)
    {
        Capitan temp = *this;
        temp.bonusBani += suma;
        return temp;
    }
    friend Capitan operator+(float suma, const Capitan &c)
    {
        Capitan temp = c;
        temp.bonusBani += suma;
        return temp;
    }
    bool operator==(const Capitan &c) const { return Jucator::operator==(c) && this->bonusBani == c.bonusBani; }
    bool operator<(const Capitan &c) const { return this->bonusBani < c.bonusBani; }
};

class Antrenor : public Persoana
{
private:
    long long salariu;
    std::vector<int> victoriiPeSezon;

public:
    Antrenor();
    Antrenor(const std::string &nume, long long salariu, const std::vector<int> &victoriiPeSezon);
    Antrenor(const std::string &nume, long long salariu);
    Antrenor(const std::vector<int> &victoriiPeSezon);
    ~Antrenor() noexcept override;

    std::string toString() const override;
    friend istream &operator>>(istream &in, Antrenor &a);
    int &operator[](int index);
    const int &operator[](int index) const;
    Antrenor &operator++();
    Antrenor operator++(int);
    Antrenor operator-(long long penalizare);
    friend Antrenor operator+(long long bonus, const Antrenor &a);
    friend Antrenor operator+(const Antrenor &a, long long bonus);
    bool operator==(const Antrenor &a) const;
    bool operator<(const Antrenor &a) const;

    long long getSalariu() const { return salariu; }
    int getNrSezoane() const { return victoriiPeSezon.size(); }
    std::vector<int> getVendoriiPeSezon() const { return victoriiPeSezon; }
    void setSalariu(long long salariu)
    {
        if (salariu < 0)
            throw ExceptieContract("Salariul antrenorului nu poate fi negativ!", static_cast<float>(salariu));
        this->salariu = salariu;
    }
    void setVictoriiPeSezon(const std::vector<int> &victorii);
    void afiseazaRol() const override;
    bool esteActiv() const override;
    float medieSucces() const
    {
        if (victoriiPeSezon.empty())
            return 0.0f;
        int totalVictorii = 0;
        int totalMeciuriPosibile = victoriiPeSezon.size() * 82;
        for (size_t i = 0; i < victoriiPeSezon.size(); i++)
            totalVictorii += victoriiPeSezon[i];
        return ((float)totalVictorii / totalMeciuriPosibile) * 100;
    }
};

class Echipa : public IObject
{
private:
    std::string nume;
    std::vector<Jucator> listaJucatori;
    long long faniAdevarati;
    string conferinta;
    std::unique_ptr<Antrenor> antrenorPrincipal;

public:
    Echipa();
    Echipa(const std::string &nume, int nrJucatori, const std::vector<Jucator> &listaJucatori, long long faniAdevarati, string conferinta, const Antrenor &antrenorPrincipal);
    Echipa(const std::string &nume, int nrJucatori, const std::vector<Jucator> &listaJucatori, string conferinta, const Antrenor &antrenorPrincipal);
    Echipa(int nrJucatori, const std::vector<Jucator> &listaJucatori, long long faniAdevarati, string conferinta, const Antrenor &antrenorPrincipal);
    Echipa(const Echipa &);
    ~Echipa() noexcept = default;

    Echipa &operator=(const Echipa &);
    std::string toString() const override;
    friend istream &operator>>(istream &, Echipa &);
    void operator++();
    void operator--();
    long long operator+(long long quantity);
    friend long long operator+(long long quantity, Echipa &);
    long long operator-(long long quantity);
    bool operator==(const Echipa &) const;
    bool operator<(const Echipa &) const;
    Jucator &operator[](int index);
    const Jucator &operator[](int index) const;

    std::string getNume() const { return nume; }
    long long getFaniAdevarati() const { return faniAdevarati; }
    int getNrJucatori() const { return listaJucatori.size(); }
    string getConferinta() const { return conferinta; }

    void setNume(const std::string &nume) { this->nume = nume; }
    void setFaniAdevarati(long long faniAdevarati) { this->faniAdevarati = faniAdevarati; }
    void setConferinta(string conferinta)
    {
        if (conferinta != "Est" && conferinta != "Vest")
            throw ExceptieEchipa("Conferinta echipei trebuie sa fie 'Est' sau 'Vest'!", nume);
        this->conferinta = conferinta;
    }
    void setAntrenor(const Antrenor &a);
    bool areAntrenor() const { return antrenorPrincipal != nullptr; }
    Antrenor getAntrenor() const { return *antrenorPrincipal; }
    void adaugaJucator(const Jucator &j);
    void stergeJucator(int index);
};

class Meci : public IObject
{
private:
    std::string adversar;
    std::vector<int> punctePeSfert;
    bool acasa;

public:
    Meci();
    Meci(const std::string &adversar, const std::vector<int> &puncte, bool acasa);
    Meci(const std::string &adversar, bool acasa);
    Meci(const std::vector<int> &puncte);
    virtual ~Meci() noexcept = default;

    std::string toString() const override;
    friend istream &operator>>(istream &in, Meci &m);
    int &operator[](int index);
    const int &operator[](int index) const;
    Meci &operator++();
    Meci operator++(int);
    Meci operator-(int penalizare);
    friend Meci operator+(int bonus, const Meci &m);
    friend Meci operator+(const Meci &m, int bonus);
    bool operator==(const Meci &m) const;
    bool operator<(const Meci &m) const;

    std::string getAdversar() const { return adversar; }
    int getNrSferturi() const { return punctePeSfert.size(); }
    std::vector<int> getPunctePeSfert() const { return punctePeSfert; }
    bool getAcasa() const { return acasa; }

    void setAdversar(const std::string &adv) { adversar = adv; }
    void setAcasa(bool acasa) { this->acasa = acasa; }
    void setPunctePeSfert(const std::vector<int> &puncte)
    {
        if (puncte.empty())
            throw ExceptieBaschet("Nu se pot seta punctele! Vectorul de sferturi nu poate fi gol.");
        punctePeSfert = puncte;
    }
    float MediaPunctelor() const
    {
        if (punctePeSfert.empty())
            return 0.0f;
        int totalPuncte = 0;
        for (int puncte : punctePeSfert)
            totalPuncte += puncte;
        return (float)totalPuncte / punctePeSfert.size();
    }
};