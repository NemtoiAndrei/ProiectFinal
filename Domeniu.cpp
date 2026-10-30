#include "Domeniu.h"

int IObject::contor = 0;

ContractInfo::ContractInfo() : durataLuni(12), salariuLunar(1000.0) { cout << "[ContractInfo] Constructor apelat." << endl; }
ContractInfo::ContractInfo(int durata, float salariu) : durataLuni(durata), salariuLunar(salariu)
{
    if (durata < 0)
        throw ExceptieContract("Durata invalida la creare contract!", durata);
    if (salariu < 0)
        throw ExceptieContract("Salariu invalid la creare contract!", salariu);
    cout << "[ContractInfo] Constructor apelat." << endl;
}
ContractInfo::ContractInfo(int durata) : durataLuni(durata), salariuLunar(1000.0)
{
    if (durata < 0)
        throw ExceptieContract("Durata invalida la creare contract!", durata);
    cout << "[ContractInfo] Constructor apelat." << endl;
}
ContractInfo::~ContractInfo() noexcept { cout << "[ContractInfo] Destructor apelat." << endl; }

ostream &operator<<(ostream &out, const ContractInfo &c)
{
    out << "Contract -> Durata: " << c.durataLuni << " luni | Salariu: " << c.salariuLunar << " $";
    return out;
}
istream &operator>>(istream &in, ContractInfo &c)
{
    int d;
    float s;
    cout << "Durata contractului (luni): ";
    in >> d;
    cout << "Salariu lunar ($): ";
    in >> s;
    c.setDurata(d);
    c.setSalariu(s);
    return in;
}
float ContractInfo::operator[](int index) const
{
    if (index == 0)
        return (float)durataLuni;
    if (index == 1)
        return salariuLunar;
    return -1.0f;
}
ContractInfo &ContractInfo::operator++()
{
    durataLuni++;
    return *this;
}
ContractInfo ContractInfo::operator++(int)
{
    ContractInfo temp = *this;
    durataLuni++;
    return temp;
}
ContractInfo ContractInfo::operator+(float bonus)
{
    ContractInfo temp = *this;
    temp.salariuLunar += bonus;
    return temp;
}
ContractInfo operator+(float bonus, const ContractInfo &c)
{
    ContractInfo temp = c;
    temp.salariuLunar += bonus;
    return temp;
}
bool ContractInfo::operator==(const ContractInfo &c) const { return durataLuni == c.durataLuni && salariuLunar == c.salariuLunar; }
bool ContractInfo::operator<(const ContractInfo &c) const { return salariuLunar < c.salariuLunar; }

Antrenor::Antrenor() : Persoana("N/A"), salariu(0.0) { cout << "[Antrenor] Constructor fara parametri apelat." << endl; }
Antrenor::Antrenor(const std::string &nume, long long salariu, const std::vector<int> &victoriiPeSezon) : Persoana(nume), victoriiPeSezon(victoriiPeSezon)
{
    if (salariu < 0)
        throw ExceptieContract("Salariul antrenorului nu poate fi negativ!", static_cast<float>(salariu));
    this->salariu = salariu;
    cout << "[Antrenor] Constructor apelat." << endl;
}
Antrenor::Antrenor(const std::string &nume, long long salariu) : Persoana(nume)
{
    if (salariu < 0)
        throw ExceptieContract("Salariul antrenorului nu poate fi negativ!", static_cast<float>(salariu));
    this->salariu = salariu;
    cout << "[Antrenor] Constructor apelat." << endl;
}
Antrenor::Antrenor(const std::vector<int> &victoriiPeSezon) : Persoana("N/A"), salariu(0.0), victoriiPeSezon(victoriiPeSezon) { cout << "[Antrenor] Constructor apelat." << endl; }
Antrenor::~Antrenor() noexcept { cout << "[Antrenor] Destructor apelat." << endl; }
std::string Antrenor::toString() const
{
    std::ostringstream out;
    out << "ID Antrenor: " << getId() << "\nNume Antrenor: " << nume << "\nSalariu curent: " << salariu << " $\nSezoane antrenate: " << victoriiPeSezon.size() << "\n";
    if (!victoriiPeSezon.empty())
    {
        int total = 0;
        out << "Victorii pe sezon: ";
        for (size_t i = 0; i < victoriiPeSezon.size(); i++)
        {
            out << victoriiPeSezon[i] << " ";
            total += victoriiPeSezon[i];
        }
        out << "\nTotal victorii in cariera: " << total << "\n";
    }
    else
    {
        out << "Nu are istoric de meciuri inregistrat.\n";
    }
    return out.str();
}
istream &operator>>(istream &in, Antrenor &a)
{
    std::string temp;
    cout << "Introduceti numele antrenorului: ";
    in >> ws;
    std::getline(in, temp);
    a.setNume(temp);
    long long salTemp;
    cout << "Introduceti salariul: ";
    in >> salTemp;
    a.setSalariu(salTemp);
    cout << "Introduceti numarul de sezoane antrenate: ";
    int nrSz;
    in >> nrSz;
    a.victoriiPeSezon.clear();
    if (nrSz > 0)
    {
        for (int i = 0; i < nrSz; i++)
        {
            int val;
            cout << "Victorii obtinute in sezonul " << i + 1 << ": ";
            in >> val;
            a.victoriiPeSezon.push_back(val);
        }
    }
    return in;
}
int &Antrenor::operator[](int index)
{
    if (index >= 0 && index < (int)victoriiPeSezon.size())
        return victoriiPeSezon[index];
    static int eroare = -1;
    return eroare;
}
const int &Antrenor::operator[](int index) const
{
    if (index >= 0 && index < (int)victoriiPeSezon.size())
        return victoriiPeSezon[index];
    static int eroare = -1;
    return eroare;
}
Antrenor &Antrenor::operator++()
{
    victoriiPeSezon.push_back(0);
    return *this;
}
Antrenor Antrenor::operator++(int)
{
    Antrenor copie = *this;
    ++(*this);
    return copie;
}
Antrenor operator+(long long bonus, const Antrenor &a)
{
    Antrenor copie = a;
    copie.salariu += bonus;
    return copie;
}
Antrenor operator+(const Antrenor &a, long long bonus) { return bonus + a; }
Antrenor Antrenor::operator-(long long penalizare)
{
    Antrenor copie = *this;
    copie.salariu -= penalizare;
    return copie;
}
bool Antrenor::operator==(const Antrenor &a) const { return nume == a.nume && victoriiPeSezon.size() == a.victoriiPeSezon.size(); }
bool Antrenor::operator<(const Antrenor &a) const
{
    int total1 = 0, total2 = 0;
    for (size_t i = 0; i < victoriiPeSezon.size(); i++)
        total1 += victoriiPeSezon[i];
    for (size_t i = 0; i < a.victoriiPeSezon.size(); i++)
        total2 += a.victoriiPeSezon[i];
    return total1 < total2;
}
void Antrenor::setVictoriiPeSezon(const std::vector<int> &victorii) { this->victoriiPeSezon = victorii; }
void Antrenor::afiseazaRol() const { cout << "Rol: ANTRENOR PRINCIPAL. Nume: " << nume << " (ID: " << getId() << ")" << endl; }
bool Antrenor::esteActiv() const { return !victoriiPeSezon.empty(); }

Echipa::Echipa() : faniAdevarati(0), conferinta("N/A"), antrenorPrincipal(nullptr) { this->nume = "N/A"; }
Echipa::Echipa(const std::string &nume, int nrJucatori, const std::vector<Jucator> &listaJucatori, long long faniAdevarati, string conferinta, const Antrenor &antrenorPrincipal) : faniAdevarati(faniAdevarati)
{
    if (conferinta != "Est" && conferinta != "Vest")
        throw ExceptieEchipa("Conferinta echipei trebuie sa fie 'Est' sau 'Vest'!", nume);
    this->conferinta = conferinta;
    this->nume = nume;
    this->listaJucatori = listaJucatori;
    this->antrenorPrincipal = std::make_unique<Antrenor>(antrenorPrincipal);
    Logger::getInstanta().adaugaMesaj("[ECHIPA] Echipa completă " + nume + " a fost fondata în conferința " + conferinta);
}
Echipa::Echipa(const std::string &nume, int nrJucatori, const std::vector<Jucator> &listaJucatori, string conferinta, const Antrenor &antrenorPrincipal) : faniAdevarati(0)
{
    if (conferinta != "Est" && conferinta != "Vest")
        throw ExceptieEchipa("Conferinta echipei trebuie sa fie 'Est' sau 'Vest'!", nume);
    this->conferinta = conferinta;
    this->nume = nume;
    this->listaJucatori = listaJucatori;
    this->antrenorPrincipal = std::make_unique<Antrenor>(antrenorPrincipal);
    Logger::getInstanta().adaugaMesaj("[ECHIPA] Echipa noua " + nume + " a fost înregistrată.");
}
Echipa::Echipa(int nrJucatori, const std::vector<Jucator> &listaJucatori, long long faniAdevarati, string conferinta, const Antrenor &antrenorPrincipal) : faniAdevarati(faniAdevarati)
{
    if (conferinta != "Est" && conferinta != "Vest")
        throw ExceptieEchipa("Conferinta echipei trebuie sa fie 'Est' sau 'Vest'!", "N/A");
    this->conferinta = conferinta;
    this->nume = "N/A";
    this->listaJucatori = listaJucatori;
    this->antrenorPrincipal = std::make_unique<Antrenor>(antrenorPrincipal);
}
Echipa::Echipa(const Echipa &e) : IObject(e), faniAdevarati(e.faniAdevarati), conferinta(e.conferinta)
{
    this->nume = e.nume;
    this->listaJucatori = e.listaJucatori;
    if (e.antrenorPrincipal != nullptr)
        this->antrenorPrincipal = std::make_unique<Antrenor>(*(e.antrenorPrincipal));
    else
        this->antrenorPrincipal = nullptr;
}
Echipa &Echipa::operator=(const Echipa &e)
{
    if (this == &e)
        return *this;
    nume = e.nume;
    faniAdevarati = e.faniAdevarati;
    conferinta = e.conferinta;
    listaJucatori = e.listaJucatori;
    if (e.antrenorPrincipal != nullptr)
        antrenorPrincipal = std::make_unique<Antrenor>(*(e.antrenorPrincipal));
    else
        antrenorPrincipal = nullptr;
    return *this;
}
std::string Echipa::toString() const
{
    std::ostringstream out;
    out << "ID Echipa: " << getId() << "\nNumele echipei: " << nume << " ----> Joaca in conferinta de " << conferinta << "\nNumarul de jucatori in roster: " << listaJucatori.size() << "\nAceasta echipa are " << faniAdevarati << " fani ce vin saptamanal la meciuri\n";
    if (antrenorPrincipal != nullptr)
        out << "Antrenorul echipei este: " << antrenorPrincipal->getNume() << "\n";
    return out.str();
}
istream &operator>>(istream &in, Echipa &e)
{
    cout << "Introduceti numele echipei: ";
    in >> ws;
    std::getline(in, e.nume);
    int nrJuc;
    cout << "Introduceti numarul de jucatori din roster: ";
    in >> nrJuc;
    cout << "Introduceti numarul de fani adevarati: ";
    in >> e.faniAdevarati;
    string confTemp;
    cout << "Introduceti conferinta din care face parte (Est/Vest): ";
    in >> confTemp;
    e.setConferinta(confTemp);
    e.listaJucatori.clear();
    if (nrJuc > 0)
    {
        for (int i = 0; i < nrJuc; i++)
        {
            cout << "--- Date Jucator " << i + 1 << " ---" << endl;
            Jucator j;
            in >> j;
            e.listaJucatori.push_back(j);
        }
    }
    e.antrenorPrincipal = nullptr;
    return in;
}
Jucator &Echipa::operator[](int index)
{
    if (index < 0 || index >= (int)listaJucatori.size())
        throw ExceptieEchipa("Indexul jucatorului solicitat este in afara limitelor lotului!", nume);
    return listaJucatori[index];
}
const Jucator &Echipa::operator[](int index) const
{
    if (index < 0 || index >= (int)listaJucatori.size())
        throw ExceptieEchipa("Indexul jucatorului solicitat este in afara limitelor lotului!", nume);
    return listaJucatori[index];
}
void Echipa::operator++() { faniAdevarati++; }
void Echipa::operator--() { faniAdevarati--; }
long long Echipa::operator+(long long quantity) { return faniAdevarati + quantity; }
long long operator+(long long quantity, Echipa &echipa) { return echipa + quantity; }
long long Echipa::operator-(long long quantity) { return faniAdevarati - quantity; }
bool Echipa::operator<(const Echipa &e) const { return nume.length() < e.nume.length(); }
bool Echipa::operator==(const Echipa &e) const { return nume == e.nume; }
void Echipa::adaugaJucator(const Jucator &j) { listaJucatori.push_back(j); }
void Echipa::stergeJucator(int index)
{
    if (index < 0 || index >= (int)listaJucatori.size())
        throw ExceptieEchipa("Nu se poate sterge jucatorul! Indexul furnizat este invalid.", nume);
    listaJucatori.erase(listaJucatori.begin() + index);
}
void Echipa::setAntrenor(const Antrenor &a) { this->antrenorPrincipal = std::make_unique<Antrenor>(a); }

Meci::Meci() : adversar("N/A"), acasa(true) {}
Meci::Meci(const std::string &adversar, const std::vector<int> &puncte, bool acasa) : adversar(adversar), acasa(acasa)
{
    if (puncte.empty())
        throw ExceptieBaschet("Un meci nu poate fi creat cu o lista goala de sferturi!");
    this->punctePeSfert = puncte;
}
Meci::Meci(const std::string &adversar, bool acasa) : adversar(adversar), acasa(acasa) {}
Meci::Meci(const std::vector<int> &puncte) : adversar("N/A"), acasa(true)
{
    if (puncte.empty())
        throw ExceptieBaschet("Un meci nu poate fi creat cu o lista goala de sferturi!");
    this->punctePeSfert = puncte;
}
std::string Meci::toString() const
{
    std::ostringstream out;
    out << "ID Meci: " << getId() << "\nMeci jucat impotriva: " << adversar << (acasa ? " (ACASA)" : " (DEPLASARE)") << "\nNumar sferturi jucate: " << punctePeSfert.size() << "\n";
    if (!punctePeSfert.empty())
    {
        int total = 0;
        out << "Puncte pe sferturi: ";
        for (int p : punctePeSfert)
        {
            out << p << " ";
            total += p;
        }
        out << "\nTOTAL PUNCTE: " << total << "\n";
    }
    else
    {
        out << "Scorul nu a fost inregistrat.\n";
    }
    return out.str();
}
istream &operator>>(istream &in, Meci &m)
{
    cout << "Introduceti numele adversarului: ";
    in >> ws;
    std::getline(in, m.adversar);
    cout << "S-a jucat acasa? (1-Da/0-Nu): ";
    in >> m.acasa;
    cout << "Introduceti numarul de sferturi jucate: ";
    int nrSf;
    in >> nrSf;
    if (nrSf <= 0)
        throw ExceptieBaschet("Numarul de sferturi introduse pentru un meci trebuie sa fie mai mare decat 0!");
    m.punctePeSfert.clear();
    for (int i = 0; i < nrSf; i++)
    {
        int puncte;
        cout << "Puncte marcate in sfertul " << i + 1 << ": ";
        in >> puncte;
        m.punctePeSfert.push_back(puncte);
    }
    return in;
}
int &Meci::operator[](int index)
{
    if (index < 0 || index >= (int)punctePeSfert.size())
        throw ExceptieBaschet("Indexul sfertului solicitat depaseste limitele istoricului meciului!");
    return punctePeSfert[index];
}
const int &Meci::operator[](int index) const
{
    if (index < 0 || index >= (int)punctePeSfert.size())
        throw ExceptieBaschet("Indexul sfertului solicitat depaseste limitele istoricului meciului!");
    return punctePeSfert[index];
}
Meci &Meci::operator++()
{
    punctePeSfert.push_back(0);
    return *this;
}
Meci Meci::operator++(int)
{
    Meci copie = *this;
    punctePeSfert.push_back(0);
    return copie;
}
Meci operator+(int bonus, const Meci &m)
{
    Meci copie = m;
    for (size_t i = 0; i < copie.punctePeSfert.size(); i++)
        copie.punctePeSfert[i] += bonus;
    return copie;
}
Meci operator+(const Meci &m, int bonus) { return bonus + m; }
Meci Meci::operator-(int bonus)
{
    Meci copie = *this;
    for (size_t i = 0; i < copie.punctePeSfert.size(); i++)
        copie.punctePeSfert[i] -= bonus;
    return copie;
}
bool Meci::operator==(const Meci &m) const { return adversar == m.adversar && punctePeSfert.size() == m.punctePeSfert.size(); }
bool Meci::operator<(const Meci &m) const
{
    int total1 = 0, total2 = 0;
    for (int p : punctePeSfert)
        total1 += p;
    for (int p : m.punctePeSfert)
        total2 += p;
    return total1 < total2;
}