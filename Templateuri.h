#pragma once
#include <iostream>
#include <stdexcept>
#include <string>

// T reprezinta tipul elementelor, iar int N este un parametru non-tip care
// fixeaza dimensiunea maxima a colectiei direct la compilare (fara alocare dinamica pe heap).
template <typename T, int N>
class ColectieFixa
{
private:
    T elemente[N];
    int dimensiuneCurenta;

public:
    ColectieFixa() : dimensiuneCurenta(0) {}
    ~ColectieFixa() noexcept = default;

    void adaugaElement(const T &elem)
    {
        if (dimensiuneCurenta >= N)
            throw std::overflow_error("Eroare Colectie: Capacitatea maxima fixata la compilare a fost depasita!");
        elemente[dimensiuneCurenta++] = elem;
    }

    void stergeUltimul()
    {
        if (dimensiuneCurenta <= 0)
            throw std::underflow_error("Eroare Colectie: Nu se poate sterge, colectia este deja goala!");
        dimensiuneCurenta--;
    }

    T &operator[](int index)
    {
        if (index < 0 || index >= dimensiuneCurenta)
            throw std::out_of_range("Indexul solicitat este in afara limitelor colectiei!");
        return elemente[index];
    }

    const T &operator[](int index) const
    {
        if (index < 0 || index >= dimensiuneCurenta)
            throw std::out_of_range("Indexul solicitat este in afara limitelor colectiei!");
        return elemente[index];
    }

    int getDimensiune() const { return dimensiuneCurenta; }
    int getCapacitateMaxima() const { return N; }

    // Parametrul U este complet independent de tipul T al clasei.
    // Aceasta metoda permite copierea/conversia datelor dintr-o alta colectie de tip diferit,
    // demonstrand o interoperabilitate avansata intre tipuri compatibile.
    template <typename U>
    void copiazaDin(const ColectieFixa<U, N> &altaColectie)
    {
        this->dimensiuneCurenta = 0;
        for (int i = 0; i < altaColectie.getDimensiune(); i++)
            this->adaugaElement(static_cast<T>(altaColectie[i]));
    }
};

// Functia Template Libera 1: Functie generica pentru afisarea oricarui container ce suporta indexare
template <typename Container>
void afiseazaColectieGenerica(const Container &c, const std::string &titlu)
{
    std::cout << "\n--- " << titlu << " (Total: " << c.getDimensiune() << ") ---" << std::endl;
    if (c.getDimensiune() == 0)
    {
        std::cout << "Colectia este goala." << std::endl;
        return;
    }
    for (int i = 0; i < c.getDimensiune(); i++)
        std::cout << "[" << i + 1 << "] " << c[i] << std::endl;
}

// Functia Template Libera 2: Algoritm generic de sortare (Bubble Sort) aplicabil pe colectii indexabile
// Deducerea de tip se face automat la apel, in functie de tipul colectiei transmise.
template <typename Container>
void sorteazaColectieGenerica(Container &c)
{
    int n = c.getDimensiune();
    for (int i = 0; i < n - 1; i++)
    {
        for (int j = 0; j < n - i - 1; j++)
        {
            if (c[j + 1] < c[j])
            {
                auto temp = c[j];
                c[j] = c[j + 1];
                c[j + 1] = temp;
            }
        }
    }
}

template <>
inline void sorteazaColectieGenerica<ColectieFixa<int, 5>>(ColectieFixa<int, 5> &c)
{
    std::cout << "\n[Audit Template] Se executa specializarea totala optimizata pentru ColectieFixa de numere intregi!" << std::endl;
    int n = c.getDimensiune();
    for (int i = 0; i < n - 1; i++)
    {
        for (int j = 0; j < n - i - 1; j++)
        {
            if (c[j] > c[j + 1])
            {
                int temp = c[j];
                c[j] = c[j + 1];
                c[j + 1] = temp;
            }
        }
    }
}