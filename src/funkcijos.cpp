#include "funkcijos.h"
#include <fstream>
#include <iostream>
#include <cstdlib>
#include <iomanip>
#include <stdexcept>
#include <algorithm>
#include <vector>
#include <chrono>

using std::ofstream;
using std::cout;
using std::cin;
using std::endl;
using std::setw;
using std::left;
using std::vector;
using std::string;
using std::sort;
using std::setprecision;

void generuotiFaila(const std::string& failoPavadinimas, int studentuKiekis, int ndKiekis) {

    ofstream failas(failoPavadinimas);

    if (!failas.is_open()) {
        cout << "Nepavyko sukurti failo!" << endl;
        return;
    }
    
    failas << left << setw(20) << "Vardas" << left << setw(20) << "Pavarde";

    for (int i = 0; i < ndKiekis; i++) {
        failas << left << setw(5) << ("ND" + std::to_string(i + 1));
    }

    failas << left << setw(5) << "Egz." << endl;

    for (int i = 0; i < studentuKiekis; i++) {
        failas << left << setw(20) << ("Vardas" + std::to_string(i + 1)) << left << setw(20) << ("Pavarde" + std::to_string(i + 1));

        for (int j = 0; j < ndKiekis; j++) {
            int paz = rand() % 10 + 1;
            failas << left << setw(5) << paz;
        }

        int egz = rand() % 10 + 1;
        failas << left << setw(5) << egz << endl;
    }

    failas.close();

    cout << "Failas sugeneruotas: " << failoPavadinimas << endl;
}

void outputas(const Vector<Studentas>& grupe, char pasirinkimas) {
    cout << std::fixed << std::setprecision(2);

    cout << left << setw(15) << "Vardas" << left << setw(20) << "Pavarde";

    if (pasirinkimas == 'm') {
        cout << setw(15) << "Galutinis (Med.)" << endl;
    } else {
        cout << setw(15) << "Galutinis (Vid.)" << endl;
    }

    cout << string(50, '-') << endl;

    for (const auto& A : grupe) {
        cout << left << setw(15) << A.getVardas() << left << setw(20) << A.getPavarde();
        double nd_rez = (pasirinkimas == 'm') ? mediana(A.getPaz()) : vidurkis(A.getPaz());
        double galutinis = 0.4 * nd_rez + 0.6 * A.getEgz();
        cout << setw(15) << galutinis << endl;
    }
}

void spausdinimas(const Vector<Studentas>& grupe, char pasirinkimas) {
    ofstream file("rezultatai.txt");

    try {
        if (!file.is_open()) {
        throw std::runtime_error("Nepavyko sukurti failo");
    }
    } catch (std::exception& e) {
        cout << "Klaida: " << e.what() << endl;
        return;
    }

    file << std::fixed << std::setprecision(2);
    file << left << setw(15) << "Vardas" << left << setw(20) << "Pavarde";

    if (pasirinkimas == 'm') {
        file << setw(15) << "Galutinis (Med.)" << endl;
    } else {
        file << setw(15) << "Galutinis (Vid.)" << endl;
    }

    file << string(50, '-') << endl;

    for (const auto& A : grupe) {
        file << left << setw(15) << A.getVardas() << left << setw(20) << A.getPavarde();
        double nd_rez = (pasirinkimas == 'm') ? mediana(A.getPaz()) : vidurkis(A.getPaz());
        double galutinis = 0.4 * nd_rez + 0.6 * A.getEgz();
        file << setw(15) << galutinis << endl;
    }

    cout << "Rezultatai irasyti i faila 'rezultatai.txt'" << endl;
}

void inputas(Vector<Studentas>& grupe) {
    int ii = 0;

    while (true) {
        Studentas A;
        ii++;

        string vardas;
        cout << "Iveskite " << ii << "-ojo studento varda ('Baigti' - baigti ivedima): ";
        cin >> vardas;
        A.setVardas(vardas);

        if (A.getVardas() == "Baigti") {
            break;
        }

        string pavarde;
        cout << "Iveskite " << ii << "-ojo studento pavarde: ";
        cin >> pavarde;
        A.setPavarde(pavarde);

        while (true) {
            int nd;
            cout << "Iveskite " << ii << "-ojo studento " << A.getPaz().size() + 1 << "-aji namu darbo ivertinima (1-10, 0 - baigti): ";
            cin >> nd;

            if (!cin.fail() && nd == 0) {
                break;
            }

            if (!cin.fail() && nd >= 1 && nd <= 10) {
                A.pridetiPaz(nd);
            } else {
                cin.clear();
                cin.ignore(10000, '\n');
                cout << "Ivedete neteisingai, bandykite dar karta! (1-10, 0 - baigti)" << endl;
            }
        }

        while (A.getPaz().empty()) {
            int nd;
            cout << "Neivestas nei vienas ND. Iveskite bent viena pazymi (1-10): ";
            cin >> nd;

            if (!cin.fail() && nd >= 1 && nd <= 10) {
                A.pridetiPaz(nd);
                break;
            }

            cin.clear();
            cin.ignore(10000, '\n');
            cout << "Ivedete neteisingai, bandykite dar karta! (1-10)" << endl;
        }

        while (true) {
            int egz;
            cout << "Iveskite studento egzamino rezultata (0-10): ";
            cin >> egz;

            if (!cin.fail() && egz >= 0 && egz <= 10) {
                A.setEgz(egz);
                break;
            }

            cin.clear();
            cin.ignore(10000, '\n');
            cout << "Ivedete neteisingai, bandykite dar karta! (0-10)" << endl;
        }

        A.setRez(0);
        A.setGalutinisVid(0.4 * vidurkis(A.getPaz()) + 0.6 * A.getEgz());
        A.setGalutinisMed(0.4 * mediana(A.getPaz()) + 0.6 * A.getEgz());
        A.setRez(A.getGalutinisVid());
        grupe.push_back(A);
    }
}

double mediana(const vector<int>& paz) {
    int n = paz.size();

    if (n == 0) {
        return 0.0;
    }

    vector<int> temp = paz;
    sort(temp.begin(), temp.end());

    if (n % 2 != 0) {
        return temp[n / 2];
    } else {
        return (temp[n / 2 - 1] + temp[n / 2]) / 2.0;
    }
}

double vidurkis(const vector<int>& paz) {
    if (paz.empty()) {
        return 0.0;
    }
    int sum = 0;
    for (int x : paz) {
        sum += x;
    }
    return sum * 1.0 / paz.size();
}

void tyrimas1(const string& failoPavadinimas, int studentuKiekis, int ndKiekis) {
    cout << "Pirmo tyrimo failo kurimas: " << failoPavadinimas << endl;

    auto t1 = std::chrono::high_resolution_clock::now();

    ofstream failas(failoPavadinimas);
    if (!failas.is_open()) {
        cout << "Klaida: nepavyko sukurti failo!" << endl;
        return;
    }

    failas << std::left << std::setw(20) << "Vardas" << std::setw(20) << "Pavarde";
    for (int i = 0; i < ndKiekis; i++) {
        failas << std::setw(5) << ("ND" + std::to_string(i + 1));
    }
    failas << std::setw(5) << "Egz." << endl;

    for (int i = 0; i < studentuKiekis; i++) {
        failas << std::left << std::setw(20) << ("Vardas" + std::to_string(i + 1)) << std::setw(20) << ("Pavarde" + std::to_string(i + 1));
        for (int j = 0; j < ndKiekis; j++) {
            failas << std::setw(5) << (rand() % 10 + 1);
        }
        failas << std::setw(5) << (rand() % 10 + 1) << endl;
    }

    failas.close();

    auto t2 = std::chrono::high_resolution_clock::now();
    cout << "Failo kurimo laikas: " << std::fixed << std::setprecision(5) << std::chrono::duration<double>(t2 - t1).count() << " s" << endl;
}

void tyrimas2(const string& failoPavadinimas, char budas) {
    cout << "Antro tyrimo duomenu apdorojimas: " << failoPavadinimas << endl;

    Vector<Studentas> grupe;

    auto t_start = std::chrono::high_resolution_clock::now();
    nuskaitymas(grupe, failoPavadinimas);
    auto t2 = std::chrono::high_resolution_clock::now();
    cout << "Nuskaitymo laikas: " << std::fixed << std::setprecision(5) << std::chrono::duration<double>(t2 - t_start).count() << " s" << endl;

    Vector<Studentas> vargsiukai, kietakai;

    auto t3 = std::chrono::high_resolution_clock::now();
    padalintiStudentus1(grupe, vargsiukai, kietakai, budas);
    auto t4 = std::chrono::high_resolution_clock::now();
    cout << "Rusiavimo laikas: " << std::fixed << std::setprecision(5) << std::chrono::duration<double>(t4 - t3).count() << " s" << endl;

    auto t5 = std::chrono::high_resolution_clock::now();
    spausdintiIFaila(vargsiukai, "vargsiukai.txt", budas);
    spausdintiIFaila(kietakai, "kietakai.txt", budas);
    auto t6 = std::chrono::high_resolution_clock::now();
    cout << "Isvedimo laikas: " << std::fixed << std::setprecision(5) << std::chrono::duration<double>(t6 - t5).count() << " s" << endl;

    cout << "Bendras laikas: " << std::fixed << std::setprecision(5) << std::chrono::duration<double>(t6 - t_start).count() << " s" << endl;
    cout << "Vargsiukai: " << vargsiukai.size() << " | Kietakai: " << kietakai.size() << endl;
}