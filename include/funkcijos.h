#ifndef FUNKCIJOS_H
#define FUNKCIJOS_H

#include "Vector.h"
#include "Zmogus.h"
#include "Studentas.h"
#include <vector>
#include <string>
#include <fstream>
#include <sstream>
#include <stdexcept>
#include <iostream>
#include <algorithm>
#include <type_traits>
#include <list>
#include <iomanip>
#include <deque>
#include <chrono>

void generuotiFaila(const std::string& failoPavadinimas, int kiekStudentu, int ndKiekis);
void outputas(const Vector<Studentas>& grupe, char pasirinkimas);
void spausdinimas(const Vector<Studentas>& grupe, char pasirinkimas);
void inputas(Vector<Studentas>& grupe);
double mediana(const Vector<int>& paz);
double vidurkis(const Vector<int>& paz);
void tyrimas1(const std::string& failoPavadinimas, int studentuKiekis, int ndKiekis);
void tyrimas2(const std::string& failoPavadinimas, char budas);
void vektoriunSpartosTestas();

template <typename konteineris>
void nuskaitymas(konteineris& grupe, std::string failas) {
    std::ifstream input(failas);

    try {
        if (!input.is_open()) {
            throw std::runtime_error("Nepavyko  failo: " + failas);
        }
    } catch (std::exception& e) {
        std::cout << "Klaida: " << e.what() << std::endl;
        return;
    }

    grupe.clear();

    std::string eilute;
    std::getline(input, eilute);

    while (std::getline(input, eilute)) {
        if (eilute.empty()) {
            continue;
        }

        std::stringstream ss(eilute);
        Studentas s;

        std::string vardas, pavarde;
        ss >> vardas >> pavarde;

        s.setVardas(vardas);
        s.setPavarde(pavarde);

        if (s.getVardas().empty() || s.getPavarde().empty()) {
            continue;
        }

        Vector<int> paz;
        int x;

        while (ss >> x) {
            paz.push_back(x);
        }

        if (paz.empty()) {
            continue;
        }

        s.setEgz(paz.back());
        paz.pop_back(); 

        s.setPaz(paz);
        s.setGalutinisVid(0.4 * vidurkis(s.getPaz()) + 0.6 * s.getEgz());
        s.setGalutinisMed(0.4 * mediana(s.getPaz()) + 0.6 * s.getEgz());

        grupe.push_back(s);
    }
}

template <typename konteineris>
void padalintiStudentus1(const konteineris& grupe, konteineris& vargsiukai, konteineris& kietakai, char budas) {
    vargsiukai.clear();
    kietakai.clear();

    for (const auto& A : grupe) {
        double galutinis = (budas == 'm') ? A.getGalutinisMed() : A.getGalutinisVid();

        if (galutinis < 5.0) {
            vargsiukai.push_back(A);
        } else {
            kietakai.push_back(A);
        }
    }
}

template <typename konteineris>
void padalintiStudentus2(konteineris& grupe, konteineris& vargsiukai, char budas) {
    vargsiukai.clear();

    if constexpr (std::is_same_v<konteineris, std::list<Studentas>>) {
        grupe.sort([budas](const Studentas& A, const Studentas& B) {
            return (budas == 'm') ? A.getGalutinisMed() > B.getGalutinisMed() : A.getGalutinisVid() > B.getGalutinisVid();
        });
    } else {
        std::sort(grupe.begin(), grupe.end(), [budas](const Studentas& A, const Studentas& B) {
            return (budas == 'm') ? A.getGalutinisMed() > B.getGalutinisMed() : A.getGalutinisVid() > B.getGalutinisVid();
        });
    }

    auto it = grupe.end();

    while (it != grupe.begin()) {
        --it;

        double galutinis = (budas == 'm') ? it->getGalutinisMed() : it->getGalutinisVid();

        if (galutinis < 5.0) {
            vargsiukai.push_back(*it);
            it = grupe.erase(it);
        } else {
            break;
        }
    }
}

template <typename konteineris>
void padalintiStudentus3(konteineris& grupe, konteineris& vargsiukai, char budas) {
    vargsiukai.clear();

    auto riba = std::partition(grupe.begin(), grupe.end(), [budas](const Studentas& A) {
        double galutinis = (budas == 'm') ? A.getGalutinisMed() : A.getGalutinisVid();
        return galutinis >= 5.0;
    });

    vargsiukai.insert(vargsiukai.end(), riba, grupe.end());
    grupe.erase(riba, grupe.end());
}

template <typename konteineris>
void rusiavimas(konteineris& grupe, char budas) {
    int kriterijus;
    while (true) {
        std::cout << "Pasirinkite kriteriju pagal kuri norite rusiuoti:" << std::endl;
        std::cout << "1 - Vardas" << std::endl;
        std::cout << "2 - Pavarde" << std::endl;
        std::cout << "3 - Galutinis (vidurkis arba mediana)" << std::endl;
        std::cin >> kriterijus;

        if (std::cin.fail()) {
            std::cin.clear();
            std::cin.ignore(10000, '\n');
            std::cout << "Klaida: iveskite skaiciu 1-3" << std::endl;
            continue;
        }

        if (kriterijus == 1 || kriterijus == 2 || kriterijus == 3) {
            break;
        }
        std::cout << "Neteisinga ivestis. Bandykite dar karta!" << std::endl;
    }

    if constexpr (std::is_same_v<konteineris, std::list<Studentas>>) {
        switch (kriterijus) {
            case 1:
                grupe.sort([](const Studentas& A, const Studentas& B) {
                    return A.getVardas() < B.getVardas();
                });
                break;
            case 2:
                grupe.sort([](const Studentas& A, const Studentas& B) {
                    return A.getPavarde() < B.getPavarde();
                });
                break;
            case 3:
                if (budas == 'v') {
                    grupe.sort([](const Studentas& A, const Studentas& B) {
                        double galutinisA = 0.4 * vidurkis(A.getPaz()) + 0.6 * A.getEgz();
                        double galutinisB = 0.4 * vidurkis(B.getPaz()) + 0.6 * B.getEgz();
                        return galutinisA > galutinisB;
                    });
                } else {
                    grupe.sort([](const Studentas& A, const Studentas& B) {
                        double galutinisA = 0.4 * mediana(A.getPaz()) + 0.6 * A.getEgz();
                        double galutinisB = 0.4 * mediana(B.getPaz()) + 0.6 * B.getEgz();
                        return galutinisA > galutinisB;
                    });
                }
            break;
    }
} else {
    switch (kriterijus) {
        case 1:
        std::sort(grupe.begin(), grupe.end(), [](const Studentas& A, const Studentas& B) {
            return A.getVardas() < B.getVardas();
        });
           break;
        case 2:
        std::sort(grupe.begin(), grupe.end(), [](const Studentas& A, const Studentas& B) {
            return A.getPavarde() < B.getPavarde();
        });
           break;
        case 3:
        if (budas == 'v') {
            std::sort(grupe.begin(), grupe.end(), [](const Studentas& A, const Studentas& B) {
                double galutinisA = 0.4 * vidurkis(A.getPaz()) + 0.6 * A.getEgz();
                double galutinisB = 0.4 * vidurkis(B.getPaz()) + 0.6 * B.getEgz();
                return galutinisA > galutinisB;
            });
        } else {
            std::sort(grupe.begin(), grupe.end(), [](const Studentas& A, const Studentas& B) {
                double galutinisA = 0.4 * mediana(A.getPaz()) + 0.6 * A.getEgz();
                double galutinisB = 0.4 * mediana(B.getPaz()) + 0.6 * B.getEgz();
                return galutinisA > galutinisB;
            });
        }
         break;
        }
    }
}

template <typename konteineris>
void spausdintiIFaila(const konteineris& grupe, const std::string& failoPavadinimas, char budas) {
    std::ofstream failas(failoPavadinimas);

    failas << std::left << std::setw(15) << "Vardas" << std::setw(15) << "Pavarde" << std::setw(20) << "Galutinis" << std::endl;

    failas << "---------------------------------------------" << std::endl;

    for (const auto& A : grupe) {

        double galutinis = (budas == 'm') ? A.getGalutinisMed() : A.getGalutinisVid();

        failas << std::left << std::setw(15) << A.getVardas() << std::setw(15) << A.getPavarde() << std::setw(20) << std::fixed << std::setprecision(2) << galutinis << std::endl;
    }

    failas.close();
}

template <typename konteineris>
void laikoSkaiciavimas(int strategija, int kriterijus, char budas, const std::string& konteinerioPavadinimas) {
    std::vector<int> dydziai = {1000, 10000, 100000, 1000000, 10000000};

    std::cout << "\n" << konteinerioPavadinimas << " konteineris:" << std::endl;
    std::cout << std::left << std::setw(12) << "Studentai" << std::setw(22) << "Nuskaitymo laikas" << std::setw(22) << "Rikiavimo laikas" << std::setw(22) << "Skirstymo laikas" << std::setw(22) << "Bendras laikas" << std::endl;

    for (int x : dydziai) {
        konteineris grupe;
        konteineris vargsiukai;
        konteineris kietakai;

        auto start1 = std::chrono::high_resolution_clock::now();
        nuskaitymas(grupe, "studentai" + std::to_string(x) + ".txt");
        auto end1 = std::chrono::high_resolution_clock::now();
        std::chrono::duration<double> diff1 = end1 - start1;

        auto start2 = std::chrono::high_resolution_clock::now();

        if constexpr (std::is_same_v<konteineris, std::list<Studentas>>) {
            switch (kriterijus) {
                case 1:
                    grupe.sort([](const Studentas& A, const Studentas& B) {
                        return A.getVardas() < B.getVardas();
                    });
                    break;

                case 2:
                    grupe.sort([](const Studentas& A, const Studentas& B) {
                        return A.getPavarde() < B.getPavarde();
                    });
                    break;
                    
                case 3:
                if (budas == 'v') {
                    grupe.sort([](const Studentas& A, const Studentas& B) {
                        return A.getGalutinisVid() > B.getGalutinisVid();
                    });
                } else {
                    grupe.sort([](const Studentas& A, const Studentas& B) {
                        return A.getGalutinisMed() > B.getGalutinisMed();
                    });
                }
                break;
            }
        } else {
            switch(kriterijus) {
                case 1:
                std::sort(grupe.begin(), grupe.end(), [](const Studentas& A, const Studentas& B) {
                    return A.getVardas() < B.getVardas();
                });
                break;

                case 2:
                std::sort(grupe.begin(), grupe.end(), [](const Studentas& A, const Studentas& B) {
                    return A.getPavarde() < B.getPavarde();
                });
                break;
                
                case 3:
                if (budas == 'v') {
                    std::sort(grupe.begin(), grupe.end(), [](const Studentas& A, const Studentas& B) {
                        return A.getGalutinisVid() > B.getGalutinisVid();
                    });
                } else {
                    std::sort(grupe.begin(), grupe.end(), [](const Studentas& A, const Studentas& B) {
                        return A.getGalutinisMed() > B.getGalutinisMed();
                    });
                }
                break;
            }
        }

        auto end2 = std::chrono::high_resolution_clock::now();
        std::chrono::duration<double> diff2 = end2 - start2;

        auto start3 = std::chrono::high_resolution_clock::now();

        if (strategija == 1) {
            padalintiStudentus1(grupe, vargsiukai, kietakai, budas);
        } else if (strategija == 2) {
            padalintiStudentus2(grupe, vargsiukai, budas);
        } else {
            padalintiStudentus3(grupe, vargsiukai, budas);
        }

        auto end3 = std::chrono::high_resolution_clock::now();
        std::chrono::duration<double> diff3 = end3 - start3;

        double bendras = diff1.count() + diff2.count() + diff3.count();
        
        std::cout << std::left << std::setw(12) << x << std::setw(22) << diff1.count() << std::setw(22) << diff2.count() << std::setw(22) << diff3.count() << std::setw(22) << bendras << std::endl;
    }
}

#endif
