#include <iostream>
#include <vector>
#include <memory>
#include <algorithm>
#include <map>
#include <set>
#include "Domeniu.h"
#include "Templateuri.h"

using namespace std;

int main()
{

    std::vector<Echipa> liga;
    // Inlocuim tablourile alocate dinamic cu containere STL sigure
    //  Justificare STL: std::vector oferă gestionare automată a memoriei, redimensionare în O(1) amortizat la push_back
    //  și ne scapă complet de pointeri periculoși și delete[] manual.
    std::vector<std::unique_ptr<Persoana>> staffLiga;
    // Pentru colecția polimorfică, folosim un vector de unique_ptr pentru a păstra polimorfismul
    // și a asigura eliberarea automată a memoriei fără memory leaks.

    int optiune;

    // Invelim intregul meniu sau operatiile critice intr-un bloc try/catch general
    // pentru a preveni prabusirea programului daca utilizatorul introduce date greșite.
    do
    {
        try
        {
            cout << "\n=========================================" << endl;
            cout << "         LIGA DE BASCHET            " << endl;
            cout << "=========================================" << endl;
            cout << "1. Creaza o noua Echipa" << endl;
            cout << "2. Afiseaza toate Echipele" << endl;
            cout << "3. Gestioneaza o Echipa (Adauga Jucatori/Antrenor)" << endl;
            cout << "4. Sterge o Echipa" << endl;
            cout << "5. Gestionare Staff liga" << endl;
            cout << "6. Testare Stack Unwinding (Demonstratie)" << endl;
            cout << "7. Demonstratie Template-uri " << endl;
            cout << "8. Design Pattern: Abstract Factory (Generare Echipament)" << endl;
            cout << "9. Algoritmi STL - Analiza Ligii " << endl;
            cout << "10. Afiseaza Jurnalul Aplicatiei (Singleton Logger)" << endl;
            cout << "0. Iesire" << endl;

            cout << "Optiune: ";
            cin >> optiune;

            switch (optiune)
            {
            case 1:
            {
                cout << "\nCREARE ECHIPA NOUA" << endl;
                Echipa eNoua;
                cin >> eNoua; // Dacă se introduce o conferință greșită, se va arunca ExceptieEchipa aici!

                // Datorită STL, adăugarea se face într-o singură linie sigură!
                liga.push_back(eNoua);
                cout << endl
                     << "Echipa a fost inregistrata in liga!" << endl;
                break;
            }
            case 2:
            {
                cout << "\nLISTA ECHIPELOR" << endl;
                if (liga.empty())
                    cout << "Nu exista echipe inregistrate." << endl;
                for (size_t i = 0; i < liga.size(); i++)
                {
                    cout << endl
                         << "[" << i + 1 << "] Echipa: " << liga[i].getNume();
                    cout << " | Jucatori: " << liga[i].getNrJucatori();
                    cout << " | Antrenor: " << (liga[i].areAntrenor() ? liga[i].getAntrenor().getNume() : "FARA ANTRENOR") << endl;
                }
                break;
            }
            case 3:
            {
                if (liga.empty())
                {
                    cout << "\nNu exista echipe de gestionat." << endl;
                    break;
                }
                cout << "\nIntroduceti numarul echipei pe care vreti sa o gestionati (1 - " << liga.size() << "): ";
                int id;
                cin >> id;
                id--;

                if (id >= 0 && id < (int)liga.size())
                {
                    int optGestiune;
                    do
                    {
                        try
                        {
                            cout << "\nGESTIONARE ECHIPA: " << liga[id].getNume() << endl;
                            cout << "1. Adauga jucator nou in lot\n2. Sterge jucator din lot\n3. Angajeaza/Schimba Antrenor\n4. Afiseaza date complete\n0. Inapoi\nOptiune: ";
                            cin >> optGestiune;
                            switch (optGestiune)
                            {
                            case 1:
                            {
                                cout << "\nADAUGARE JUCATOR\n";
                                Jucator j;
                                cin >> j; // Poate arunca ExceptieJucator sau ExceptieContract
                                liga[id].adaugaJucator(j);
                                cout << "\nJucator adaugat!" << endl;
                                break;
                            }
                            case 2:
                            {
                                cout << "\nCONCEDIERE JUCATOR\n";
                                if (liga[id].getNrJucatori() == 0)
                                {
                                    cout << "Echipa nu are jucatori" << endl;
                                    break;
                                }
                                for (int i = 0; i < liga[id].getNrJucatori(); i++)
                                    cout << i + 1 << ". " << liga[id][i].getNume() << endl;
                                cout << "Alegeti numarul jucatorului de sters: ";
                                int indexJ;
                                cin >> indexJ;
                                liga[id].stergeJucator(indexJ - 1);
                                cout << "\nJucator sters" << endl;
                                break;
                            }
                            case 3:
                            {
                                cout << "\nCREATI ANTRENOR\n";
                                Antrenor a;
                                cin >> a;
                                liga[id].setAntrenor(a);
                                cout << "\nAntrenor creat" << endl;
                                break;
                            }
                            case 4:
                            {
                                cout << "\nDETALII COMPLETE ECHIPA\n"
                                     << liga[id] << "\n\nJUCATORI DIN LOT\n";
                                if (liga[id].getNrJucatori() == 0)
                                    cout << "Nu exista jucatori." << endl;
                                for (int i = 0; i < liga[id].getNrJucatori(); i++)
                                    cout << liga[id][i] << endl;
                                if (liga[id].areAntrenor())
                                    cout << "\nDATE COMPLETE ANTRENOR\n"
                                         << liga[id].getAntrenor() << endl;
                                break;
                            }
                            case 0:
                                break;
                            default:
                                cout << "\nOptiune invalida" << endl;
                            }
                        }
                        catch (const ExceptieBaschet &e)
                        {
                            cout << "\n[Eroare Gestiune Echipa]: " << e.what() << " Reincercati operația!" << endl;
                        }
                    } while (optGestiune != 0);
                }
                else
                    cout << "\nEchipa invalida" << endl;
                break;
            }
            case 4:
            {
                if (liga.empty())
                {
                    cout << "\nNu exista echipe de sters." << endl;
                    break;
                }
                cout << "Introduceti numarul echipei de sters (1 - " << liga.size() << "): ";
                int del;
                cin >> del;
                del--;
                if (del >= 0 && del < (int)liga.size())
                {
                    liga.erase(liga.begin() + del); // Ștergere nativă și sigură prin STL vector
                    cout << "\nEchipa stearsa" << endl;
                }
                else
                    cout << "\nIndex invalid!" << endl;
                break;
            }
            case 5:
            {
                int optStaff;
                do
                {
                    try
                    {
                        cout << "\n--- MENIU STAFF POLIMORFIC ---\n1. Adauga Jucator simplu\n2. Adauga Capitan\n3. Adauga Antrenor\n4. Afiseaza tot Staff-ul\n5. Cauta Capitanii\n0. Inapoi\nOptiune: ";
                        cin >> optStaff;
                        if (optStaff == 1)
                        {
                            staffLiga.push_back(std::make_unique<Jucator>("Michael Jordan", 'G', 198.0, 23, true, 12, 5000));
                            cout << "Jucator adaugat!\n";
                        }
                        else if (optStaff == 2)
                        {
                            staffLiga.push_back(std::make_unique<Capitan>("LeBron James", 'F', 206.0, 23, true, 12, 4000.0, 1000.0));
                            cout << "Capitan adaugat!\n";
                        }
                        else if (optStaff == 3)
                        {
                            staffLiga.push_back(std::make_unique<Antrenor>("Phil Jackson", 10000000));
                            cout << "Antrenor adaugat!\n";
                        }
                        else if (optStaff == 4)
                        {
                            if (staffLiga.empty())
                                cout << "Staff gol.\n";
                            for (size_t i = 0; i < staffLiga.size(); i++)
                            {
                                cout << "\n--- Membrul " << i + 1 << " ---" << endl;
                                // Aici se intampla LATE BINDING: compilatorul decide la runtime
                                // ce implementare sa apeleze, desi pointerul este de tip Persoana*.
                                staffLiga[i]->afiseazaRol();
                            }
                        }
                        else if (optStaff == 5)
                        {
                            if (staffLiga.empty())
                                cout << "Staff gol.\n";
                            for (size_t i = 0; i < staffLiga.size(); i++)
                            {
                                cout << "Analizam: " << staffLiga[i]->getNume() << "... ";

                                // Folosim dynamic_cast și nu static_cast
                                Capitan *cap = dynamic_cast<Capitan *>(staffLiga[i].get());
                                if (cap != nullptr)
                                    cout << "ESTE CAPITAN! Bonus: " << cap->getBonusBani() << " $" << endl;
                                else
                                    cout << "Esec downcast." << endl;
                            }
                        }
                    }
                    catch (const ExceptieBaschet &e)
                    {
                        cout << "\n[Eroare Staff]: " << e.what() << endl;
                    }
                } while (optStaff != 0);
                break;
            }
            case 6:
            {
                cout << "\n=== DEMONSTRATIE STACK UNWINDING ===" << endl;
                try
                {
                    Jucator jTest("Test Stack Unwinding", 'G', 190.0, 10, true);
                    cout << "Obiectul a fost creat cu succes. Fortam o exceptie..." << endl;
                    jTest.setNumar(250); // Aceasta linie va arunca ExceptieJucator!
                }
                catch (const ExceptieJucator &e)
                {
                    cout << "\n[Bloc Catch Intern]: S-a prins ExceptieJucator: " << e.what() << endl;
                }
                break;
            }
            case 7:
            {
                cout << "\n=== DEMONSTRATIE TEMPLATE-URI ===" << endl;
                try
                {
                    ColectieFixa<int, 5> statistici;
                    statistici.adaugaElement(85);
                    statistici.adaugaElement(115);
                    statistici.adaugaElement(90);
                    afiseazaColectieGenerica(statistici, "Statistici Puncte (Nesortate)");
                    sorteazaColectieGenerica(statistici);
                    afiseazaColectieGenerica(statistici, "Statistici Puncte (Dupa Specializarea de Sortare)");
                    ColectieFixa<float, 5> statisticiFloat;
                    statisticiFloat.copiazaDin(statistici);
                    afiseazaColectieGenerica(statisticiFloat, "Statistici Copiate ca FLOAT");
                    statistici.adaugaElement(102);
                    statistici.adaugaElement(105);
                    statistici.adaugaElement(120); // Aici arunca overflow_error!
                }
                catch (const std::exception &e)
                {
                    cout << "\n[CATCH TEMPLATE LOCAL] S-a interceptat eroarea: " << e.what() << endl;
                }
                break;
            }
            case 8:
            {
                cout << "\n=== ABSTRACT FACTORY: GENERARE ECHIPAMENT ===\nAlege familia (1- EST, 2- VEST): ";
                int conf;
                cin >> conf;
                std::unique_ptr<IFabricaEchipamente> fabrica = nullptr;
                if (conf == 1)
                    fabrica = std::make_unique<FabricaEst>();
                else if (conf == 2)
                    fabrica = std::make_unique<FabricaVest>();
                else
                {
                    cout << "Optiune invalida." << endl;
                    break;
                }
                // DEPENDENCY INJECTION: transmitem fabrica abstracta clientului
                ManagerEchipamente manager(*fabrica);
                manager.afiseazaKitComplet();
                break;
            }
            case 9:
            {
                cout << "\n=== ALGORITMI STL: ANALIZA LIGII ===" << endl;
                if (liga.empty())
                {
                    cout << "Liga nu are echipe inregistrate." << endl;
                    break;
                }

                std::sort(liga.begin(), liga.end(), [](const Echipa &a, const Echipa &b)
                          { return a.getFaniAdevarati() > b.getFaniAdevarati(); });
                cout << "-> [sort] Echipele au fost sortate descrescator dupa popularitate (fani)!" << endl;

                cout << "Clasamentul popularitatii:" << endl;
                std::for_each(liga.begin(), liga.end(), [](const Echipa &e)
                              { cout << " - " << e.getNume() << " (Fani: " << e.getFaniAdevarati() << ")" << endl; });

                int echipeEst = std::count_if(liga.begin(), liga.end(), [](const Echipa &e)
                                              { return e.getConferinta() == "Est"; });
                cout << "\n-> [count_if] Numar echipe in conferinta EST: " << echipeEst << endl;

                bool echipeUriage = std::any_of(liga.begin(), liga.end(), [](const Echipa &e)
                                                { return e.getFaniAdevarati() >= 50000; });
                cout << "-> [any_of] Exista vreo echipa cu peste 50.000 de fani in liga? " << (echipeUriage ? "DA" : "NU") << endl;

                std::map<std::string, int> evidentaConferinte;
                for (const auto &e : liga)
                    evidentaConferinte[e.getConferinta()]++;
                cout << "\n-> [std::map] Evidenta echipelor pe conferinte:" << endl;
                for (const auto &pereche : evidentaConferinte)
                    cout << "   " << pereche.first << " : " << pereche.second << " echipe" << endl;

                std::set<std::string> numeUnice;
                std::transform(liga.begin(), liga.end(), std::inserter(numeUnice, numeUnice.begin()), [](const Echipa &e)
                               { return e.getNume(); });
                cout << "\n-> [std::set + transform] Numele unice ale echipelor din liga (alfabetic):" << endl;
                for (const auto &nume : numeUnice)
                    cout << "   " << nume << endl;

                // 7. Demonstrare idioma erase-remove_if ceruta in barem !
                cout << "\n-> [erase-remove_if] Eliminam din liga echipele fara fani (fani == 0)..." << endl;
                liga.erase(std::remove_if(liga.begin(), liga.end(), [](const Echipa &e)
                                          { return e.getFaniAdevarati() == 0; }),
                           liga.end());

                Logger::getInstanta().adaugaMesaj("[STL] S-au rulat algoritmii de analiza pe liga de baschet.");
                break;
            }
            case 10:
            {
                Logger::getInstanta().afiseazaJurnal();
                break;
            }
            case 0:
                cout << "\nProgramul s a terminat" << endl;
                break;
            default:
                cout << "\nOptiune invalida!" << endl;
            }
        }
        // Prindem mai intai exceptiile derivate specifice, apoi cele din baza, apoi catch
        catch (const ExceptieJucator &e)
        {
            cout << "\n[CATCH SPECIFIC] Eroare la un jucator! Numar implicat: " << e.getNumarTricou() << " | Detalii: " << e.what() << endl;
        }
        catch (const ExceptieContract &e)
        {
            cout << "\n[CATCH SPECIFIC] Eroare finatara! Valoare gresita: " << e.getValoareGresita() << " | Detalii: " << e.what() << endl;
        }
        catch (const ExceptieEchipa &e)
        {
            cout << "\n[CATCH SPECIFIC] Eroare la configurarea echipei! Detalii: " << e.what() << endl;
        }
        catch (const ExceptieBaschet &e)
        {
            cout << "\n[CATCH BAZA] A aparut o problema in aplicatie: " << e.what() << endl;
        }
        catch (const std::exception &e)
        {
            cout << "\n[CATCH STANDARD] O exceptie standard C++ neasteptata: " << e.what() << endl;
        }
        catch (...)
        {
            cout << "\n[CATCH UNIVERSAL] S-a prins o eroare necunoscuta!" << endl;
        }

    } while (optiune != 0);

    // Datorită migrării complete la std::vector și std::unique_ptr, am eliminat COMPLET
    // buclele manuale de delete și delete[] care existau la finalul Proiectului 2
    // Colectiile își eliberează automat memoria în siguranță la ieșirea din scope-ul funcției main.

    return 0;
}