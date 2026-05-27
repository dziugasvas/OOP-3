#ifndef STUDENTAS_H
#define STUDENTAS_H

#include "Vector.h"
#include "Zmogus.h"
#include <iostream>
#include <string>
#include <vector>
#include <sstream>

/**
 * @file Studentas.h
 * @brief Studento klases aprasas.
 * @author dziugasvas
 * @date 2026
 */

/**
 * @class Studentas
 * @brief Studento klase, paveldinti is Zmogus.
 * Saugo varda, pavarde, pazymius, egzamino rezultata ir galutinius ivertinimus.
 */

class Studentas : public Zmogus {
private:
    Vector<int> paz;  
    int egz;              
    double rez;            
    double galutinisVid;  
    double galutinisMed;   

public:
    /// @brief Numatytasis konstruktorius
    Studentas() 
       : Zmogus(), egz(0), rez(0.0), galutinisVid(0.0), galutinisMed(0.0) {}

    /// @brief Destruktorius
    ~Studentas() override {
        vardas.clear();
        pavarde.clear();
        paz.clear();
        egz = 0;
        rez = 0.0; 
        galutinisMed = 0.0;
        galutinisVid = 0.0;
    }

    /// @brief Kopijavimo konstruktorius
    Studentas(const Studentas& kitas) 
       : Zmogus(kitas.vardas, kitas.pavarde), 
       paz(kitas.paz), egz(kitas.egz), rez(kitas.rez), 
       galutinisVid(kitas.galutinisVid), galutinisMed(kitas.galutinisMed) {}

    /// @brief Perkelimo konstruktorius
    Studentas(Studentas&& kitas)
      : Zmogus(std::move(kitas)),
        paz(std::move(kitas.paz)), 
        egz(std::move(kitas.egz)),
        rez(std::move(kitas.rez)), 
        galutinisVid(std::move(kitas.galutinisVid)), 
        galutinisMed(std::move(kitas.galutinisMed)) {
       kitas.egz = 0;
       kitas.rez = 0.0;
       kitas.galutinisVid = 0.0;
       kitas.galutinisMed = 0.0;
    }

    /// @brief Kopijavimo priskyrimo operatorius
    Studentas& operator=(const Studentas& kitas) {
        if (this != &kitas) {
            vardas = kitas.vardas;
            pavarde = kitas.pavarde;
            paz = kitas.paz;
            egz = kitas.egz;
            rez = kitas.rez;
            galutinisVid = kitas.galutinisVid;
            galutinisMed = kitas.galutinisMed;
        }
        return *this;
    }

    /// @brief Perkelimo priskyrimo operatorius
    Studentas& operator=(Studentas&& kitas) {
        if (this != &kitas) {
            vardas = std::move(kitas.vardas);
            pavarde = std::move(kitas.pavarde);
            paz = std::move(kitas.paz);
            egz = std::move(kitas.egz);
            rez = std::move(kitas.rez);
            galutinisVid = std::move(kitas.galutinisVid);
            galutinisMed = std::move(kitas.galutinisMed);
            kitas.egz = 0;
            kitas.rez = 0.0;
            kitas.galutinisVid = 0.0;
            kitas.galutinisMed = 0.0;
        }
        return *this;
    }

    /// @brief Grazina varda
    const std::string& getVardas() const override { return vardas; }

    /// @brief Grazina pavarde
    const std::string& getPavarde() const override { return pavarde; }

    /// @brief Nustato varda
    void setVardas(const std::string& v) override { vardas = v; }

    /// @brief Nustato pavarde
    void setPavarde(const std::string& p) override { pavarde = p; }

    /// @brief Spausdina studento duomenis i srauta
    void print(std::ostream& os) const override {
        os << vardas << " " << pavarde << " ";
        for (int p : paz) os << p << " ";
        os << egz;
    }

    /// @brief Nuskaito studento duomenis is srauto
    void read(std::istream& in) override {
        std::string eilute;
        std::getline(in, eilute);
        std::stringstream ss(eilute);
        ss >> vardas >> pavarde;
        Vector<int> visi;
        int skaicius;
        while (ss >> skaicius) visi.push_back(skaicius);
        if (!visi.empty()) {
            egz = visi.back();
            visi.pop_back();
        }
        paz = visi;
    }

    /// @brief Grazina pazymiu vektoriu
    const Vector<int>& getPaz() const { return paz; }

    /// @brief Grazina egzamino pazymi
    int getEgz() const { return egz; }

    /// @brief Grazina rezultata
    double getRez() const { return rez; }

    /// @brief Grazina galutini vidurkiu
    double getGalutinisVid() const { return galutinisVid; }

    /// @brief Grazina galutini mediana
    double getGalutinisMed() const { return galutinisMed; }

    /// @brief Nustato pazymius
    void setPaz(const Vector<int>& naujiPaz) { paz = naujiPaz; }

    /// @brief Nustato egzamino pazymi
    void setEgz(int naujasEgz) { egz = naujasEgz; }

    /// @brief Nustato rezultata
    void setRez(double naujasRez) { rez = naujasRez; }

    /// @brief Nustato galutini vidurkiu
    void setGalutinisVid(double naujasGalutinisVid) { galutinisVid = naujasGalutinisVid; }

    /// @brief Nustato galutini mediana
    void setGalutinisMed(double naujasGalutinisMed) { galutinisMed = naujasGalutinisMed; }

    /// @brief Prideda viena pazymi
    void pridetiPaz(int pazymys) { paz.push_back(pazymys); }

    /// @brief Isvalo pazymius
    void isvalytiPaz() { paz.clear(); }
};

#endif