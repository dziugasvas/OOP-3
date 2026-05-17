# Projekto aprašymas

Ši programa skirta studentų duomenų apdorojimui ir analizavimui. Vartotojas gali:
- įvesti studentų duomenis ranka;
- automatiškai sugeneruoti pažymius arba studentų įrašus;
- nuskaityti studentų duomenis iš failo;
- sugeneruoti testinius failus;
- atlikti skirtingų konteinerių ir studentų skirstymo strategijų veikimo spartos tyrimų.

Programoje taip pat realizuotos trys studentų skirstymo strategijos, kurių veikimo laikas lyginamas su skirtingo dydžio duomenų failais ir naudojant vector, list bei deque konteinerius.

# Diegimas ir paleidimas
1. Nusiklonuokite repozitoriją:
```
git clone https://github.com/dziugasvas/OOP-3.git
cd OOP-3
```
2. Įsidiekite reikalingus įrankius (jei jų dar neturite):

macOS:
```
xcode-select --install
```

Linux (Ubuntu/Debian):
```
sudo apt update
sudo apt install build-essential
```
3. Sukompiliuokite programą:
```
make
```
4. Paleiskite programą:
```
make run
```
5. Paleiskite testus:
```
make gtest
```

# Naudojimosi instrukcija

Paleidus programą pateikiamas meniu, kuriame galima pasirinkti norimą veiksmą.

Pagrindiniai pasirinkimai:
- įvesti studentų duomenis ranka;
- generuoti pažymius arba studentų įrašus;
- nuskaityti studentus iš failo;
- generuoti testinius failus;
- atlikti veikimo spartos tyrimus su skirtingais konteineriais ir strategijomis;
- išvesti rezultatus.

Pasirinkus atitinkamą meniu punktą, programa pateikia papildomas instrukcijas ekrane.

# Kompiuterio specifikacijos

|       CPU                |  RAM |    SSD     | 
|--------------------------|------|------------| 
| Apple M4 (10 branduolių) | 24GB | NVMe 512GB |      
------------------------------------------------

## v3.0 rezultatai

### Funkcijos

| Funkcija | Aprašymas |
|----------|-----------|
| `push_back(value)` | Prideda elementą į pabaigą |
| `pop_back()` | Pašalina paskutinį elementą |
| `resize(n)` | Pakeičia dydį |
| `reserve(n)` | Rezervuoja atmintį |
| `shrink_to_fit()` | Sumažina atmintį iki dydžio |
| `insert(pos, value)` | Įterpia elementą |
| `erase(pos)` | Pašalina elementą |
| `at(pos)` | Grąžina elementą su ribų tikrinimu |

### std::vector ir Vector spartos analizė

Testas: tuščias konteineris užpildomas `int` elementais naudojant `push_back()`.

| Elementų sk. | std::vector (s) | Vector (s) |
|--------------|-----------------|------------|
| 10000        | 0.000330        | 0.000125   |
| 100000       | 0.002975        | 0.001081   |
| 1000000      | 0.022968        | 0.006187   |
| 10000000     | 0.105178        | 0.036033   |
| 100000000    | 0.969883        | 0.356048   |

### Atminties perskirstymų palyginimas

Testas: konteineris užpildomas 100,000,000 `int` elementų. Perskirstymas įvyksta kai `capacity() == size()`.

| Konteineris | Perskirstymų skaičius |
|-------------|----------------------|
| std::vector | 28                   |
| Vector      | 26                   |

Išvada: Vector pradeda su `capacity = 2`, todėl atlieka 2 perskirstymais mažiau nei `std::vector`.

## v2.0 rezultatai

Šioje versijoje pridėti Google Test unit testai ir Doxygen dokumentacija (HTML + PDF).

### Unit testai

Testai parašyti naudojant Google Test framework'ą:

-----------------------------
| Testas       | Rezultatas |
|----------------------|----|
| DefaultConstructor   | ✅ |
| CopyConstructor      | ✅ |
| CopyAssignment       | ✅ |
| MoveConstructor      | ✅ |
| MoveAssignment       | ✅ |
| Destructor           | ✅ |
| InputOutputOperators | ✅ |
| ZmogusAbstrakcija    | ✅ |
| Vidurkis             | ✅ |
| Mediana              | ✅ |
| GalutinisBalas       | ✅ |
-----------------------------

### Nuotrauka

<img width="449" height="602" alt="image" src="https://github.com/user-attachments/assets/1c9313f6-a9f3-448b-ba9f-16289ccdc9a7" />

## v1.5 rezultatai

Šioje versijoje programa išlieka veiksminga kaip ir v1.2, tačiau `Studentas` klasė dabar paveldi iš abstrakčios bazinės klasės `Zmogus`.

| Klasė       | Tipas    | Saugomi duomenys                                |
|-------------|----------|-------------------------------------------------|
| `Zmogus`    | Abstract | Vardas ir pavardė                               |
| `Studentas` | Derived  | Pažymiai, egzamino balas, galutiniai įverčiai   |
----------------------------------------------------------------------------

### Bandymas sukurti abstrakčios klasės objektą:

`Zmogus z("LeBron", "James");`

<img width="593" height="354" alt="image" src="https://github.com/user-attachments/assets/2f2e4af1-791d-41b8-a577-ed27e6f7c4a3" />

## v1.2 rezultatai (Rule of five)

| Metodas                     | Sintaksė                                       | Paskirtis                                       |
|-----------------------------|------------------------------------------------|-------------------------------------------------|
| Copy konstruktorius         | `Studentas(const Studentas& kitas)`            | Kuriama objekto kopija                          |
| Copy priskyrimo operatorius | `Studentas& operator=(const Studentas& kitas)` | Objekto kopijos priskyrimas - b = a             |
| Move konstruktorius         | `Studentas(Studentas&& kitas)`                 | Objekto perkėlimas - Studentas b = std::move(a) |
| Move priskyrimo operatorius | `Studentas& operator=(Studentas&& kitas)`      | Objekto perkėlimas - b = std::move(a)           |
| Destruktorius               | `~Studentas()`                                 | Objekto sunaikinimas (veikia automatiškai)      |
----------------------------------------------------------------------------------------------------------------------------------

### Testų nuotrauka

<img width="343" height="131" alt="Screenshot at Apr 26 20-51-33" src="https://github.com/user-attachments/assets/b449e0d0-504c-4785-8fbe-da3d9a6920c5" />

## v1.1 rezultatai

Šioje versijoje (v1.1) programa perrašyta naudojant `class` vietoje `struct`. 
Atliktas tyrimas siekiant palyginti šių dviejų realizacijų efektyvumą apdorojant studentų duomenis.

Testavimas atliktas:
- naudojant **vector konteinerį**
- taikant **3 skirstymo strategiją (partition)**
- su skirtingais kompiliatoriaus optimizavimo lygiais: **-O1, -O2, -O3**

# Tyrimo rezultatai

100000 studentų

| Optimizacija | Laikas (class) | Laikas (struct) | Failo dydis (class) | Failo dydis (struct) |
|--------------|----------------|-----------------|---------------------|----------------------|
| -O1          |  0.259675 s    | 0.246076 s      | 326 KB              |     339 KB           |
| -O2          |  0.249686 s    | 0.244191 s      | 309 KB              |     322 KB           |
| -O3          |  0.249245 s    | 0.247485 s      | 341 KB              |     323 KB           |
------------------------------------------------------------------------------------------------

1000000 studentų

| Optimizacija | Laikas (class) | Laikas (struct) | Failo dydis (class) | Failo dydis (struct) |
|--------------|----------------|-----------------|---------------------|----------------------|
| -O1          | 1.30572 s      | 1.23554 s       | 326 KB              |  339 KB              |
| -O2          | 1.25852 s      | 1.20096 s       | 309 KB              |  322 KB              |
| -O3          | 1.25299 s      | 1.20199 s       | 341 KB              |  323 KB              |
------------------------------------------------------------------------------------------------
