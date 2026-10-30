#pragma once
#include <iostream>
#include <string>
#include <vector>
#include <memory>

using namespace std;

class Logger
{
private:
    std::vector<std::string> jurnal;

    // Constructor privat - nu permite instanțierea directă din exterior
    Logger() { jurnal.push_back("Sistemul de logare a fost initializat."); }

public:
    // 1. Varianta Meyers: instanța statică locala
    static Logger &getInstanta()
    {
        static Logger instanta;
        return instanta;
    }

    // 2. Dezactivăm explicit copierea și atribuirea conform baremului
    Logger(const Logger &) = delete;
    Logger &operator=(const Logger &) = delete;

    void adaugaMesaj(const std::string &actiune) { jurnal.push_back(actiune); }
    void afiseazaJurnal() const
    {
        std::cout << "\n=========================================" << std::endl;
        std::cout << "         JURNAL APLICATIE (LOGGER)       " << std::endl;
        std::cout << "=========================================" << std::endl;
        for (size_t i = 0; i < jurnal.size(); i++)
            std::cout << i + 1 << ". " << jurnal[i] << std::endl;
        std::cout << "=========================================\n"
                  << std::endl;
    }
};

// 1. INTERFEȚE PENTRU PRODUSE ABSTRACTE
class IMinge
{
public:
    virtual ~IMinge() = default;
    virtual std::string descriereMinge() const = 0;
};

class ITricou
{
public:
    virtual ~ITricou() = default;
    virtual std::string descriereTricou() const = 0;
};

// 2. PRODUSE CONCRETE(Conferința Est)
class MingeEst : public IMinge
{
public:
    std::string descriereMinge() const override { return "Minge Oficiala EST (Design Albastru-Rosu, Grip Superior)"; }
};

class TricouEst : public ITricou
{
public:
    std::string descriereTricou() const override { return "Tricou Oficial EST (Material Ultra-Light, Slim-Fit)"; }
};
// 3. PRODUSE CONCRETE (Conferința Vest)
class MingeVest : public IMinge
{
public:
    std::string descriereMinge() const override { return "Minge Oficiala VEST (Design Galben-Mov, Bounce Optim)"; }
};

class TricouVest : public ITricou
{
public:
    std::string descriereTricou() const override { return "Tricou Oficial VEST (Material Clasic, Rezistenta la uzura)"; }
};
// 4.Fabrica abstracta
class IFabricaEchipamente
{
public:
    virtual ~IFabricaEchipamente() = default;
    virtual std::unique_ptr<IMinge> creazaMinge() const = 0;
    virtual std::unique_ptr<ITricou> creazaTricou() const = 0;
};
// 5.Fabrici concrete(fiecare produce o familie diferita)
class FabricaEst : public IFabricaEchipamente
{
public:
    std::unique_ptr<IMinge> creazaMinge() const override
    {
        Logger::getInstanta().adaugaMesaj("[AbstractFactory] Fabrica EST a produs o minge.");
        return std::make_unique<MingeEst>();
    }
    std::unique_ptr<ITricou> creazaTricou() const override
    {
        Logger::getInstanta().adaugaMesaj("[AbstractFactory] Fabrica EST a produs un tricou.");
        return std::make_unique<TricouEst>();
    }
};

class FabricaVest : public IFabricaEchipamente
{
public:
    std::unique_ptr<IMinge> creazaMinge() const override
    {
        Logger::getInstanta().adaugaMesaj("[AbstractFactory] Fabrica VEST a produs o minge.");
        return std::make_unique<MingeVest>();
    }
    std::unique_ptr<ITricou> creazaTricou() const override
    {
        Logger::getInstanta().adaugaMesaj("[AbstractFactory] Fabrica VEST a produs un tricou.");
        return std::make_unique<TricouVest>();
    }
};
// 6.CLientul(ruleaza independent de familii)
class ManagerEchipamente
{
private:
    std::unique_ptr<IMinge> mingeEchipa;
    std::unique_ptr<ITricou> tricouEchipa;

public:
    ManagerEchipamente(const IFabricaEchipamente &fabrica)
    {
        mingeEchipa = fabrica.creazaMinge();
        tricouEchipa = fabrica.creazaTricou();
    }
    void afiseazaKitComplet() const
    {
        std::cout << "\n=== KIT ECHIPAMENT GENERAT ===" << std::endl;
        std::cout << " - MINGE:  " << mingeEchipa->descriereMinge() << std::endl;
        std::cout << " - TRICOU: " << tricouEchipa->descriereTricou() << std::endl;
        std::cout << "==============================\n"
                  << std::endl;
    }
};