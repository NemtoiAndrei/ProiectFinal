#pragma once
#include <exception>
#include <string>
#include "DesignPatterns.h"

// Clasa de bază pentru excepțiile aplicației noastre
class ExceptieBaschet : public std::exception
{
protected:
    std::string mesaj;

public:
    ExceptieBaschet(const std::string &msg) : mesaj(msg) { Logger::getInstanta().adaugaMesaj("[EROARE SYSTEM]: " + msg); }
    const char *what() const noexcept override { return mesaj.c_str(); }
};

// Excepție specifică pentru erori legate de Contracte (salariu sau durata negative)
class ExceptieContract : public ExceptieBaschet
{
private:
    float valoareGresita;

public:
    ExceptieContract(const std::string &msg, float val) : ExceptieBaschet(msg), valoareGresita(val)
    {
        mesaj = "Eroare Contract [Valoare introdusa: " + std::to_string(val) + "] -> " + msg;
    }
    float getValoareGresita() const noexcept { return valoareGresita; }
    const char *what() const noexcept override { return mesaj.c_str(); }
};
// Excepție specifică pentru erori legate de Jucători (ex: număr tricou invalid)
class ExceptieJucator : public ExceptieBaschet
{
private:
    int numarTricou;

public:
    ExceptieJucator(const std::string &msg, int numar) : ExceptieBaschet(msg), numarTricou(numar)
    {
        mesaj = "Eroare Jucator [Numar " + std::to_string(numar) + "] -> " + msg;
    }
    int getNumarTricou() const noexcept { return numarTricou; }
    const char *what() const noexcept override { return mesaj.c_str(); }
};
// Excepție specifică pentru erori legate de Echipa (ex: conferinta invalida)
class ExceptieEchipa : public ExceptieBaschet
{
private:
    std::string numeGresit;

public:
    ExceptieEchipa(const std::string &msg, const std::string &nume) : ExceptieBaschet(msg), numeGresit(nume)
    {
        mesaj = "Eroare Echipa [" + nume + "] -> " + msg;
    }
    const char *what() const noexcept override { return mesaj.c_str(); }
};