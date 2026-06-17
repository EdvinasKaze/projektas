#include <iostream>
#include <fstream>
#include <vector>
#include <sstream>
#include <algorithm>
#include <iomanip>
#include <limits>

using namespace std;

struct Preke {
    int id;
    string pavadinimas;
    string kategorija;
    double kaina;
    int kiekis;
};

const string FAILO_PAVADINIMAS = "prekes.txt";

void isvalytiIvesta() {
    cin.clear();
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
}

int nuskaitytiSveikaSkaiciu(string tekstas) {
    int skaicius;
    while (true) {
        cout << tekstas;
        cin >> skaicius;
        if (!cin.fail()) {
            isvalytiIvesta();
            return skaicius;
        }
        cout << "Klaida: iveskite sveika skaiciu.\n";
        isvalytiIvesta();
    }
}

double nuskaitytiRealuSkaiciu(string tekstas) {
    double skaicius;
    while (true) {
        cout << tekstas;
        cin >> skaicius;
        if (!cin.fail()) {
            isvalytiIvesta();
            return skaicius;
        }
        cout << "Klaida: iveskite skaiciu.\n";
        isvalytiIvesta();
    }
}

vector<Preke> nuskaitytiIsFailo(string failoPavadinimas) {
    vector<Preke> prekes;
    ifstream failas(failoPavadinimas);

    if (!failas.is_open()) {
        cout << "Nepavyko atidaryti failo: " << failoPavadinimas << "\n";
        return prekes;
    }

    string eilute;
    while (getline(failas, eilute)) {
        if (eilute.empty()) continue;

        stringstream ss(eilute);
        string idTekstas, pavadinimas, kategorija, kainaTekstas, kiekisTekstas;

        getline(ss, idTekstas, ';');
        getline(ss, pavadinimas, ';');
        getline(ss, kategorija, ';');
        getline(ss, kainaTekstas, ';');
        getline(ss, kiekisTekstas, ';');

        Preke preke;
        preke.id = stoi(idTekstas);
        preke.pavadinimas = pavadinimas;
        preke.kategorija = kategorija;
        preke.kaina = stod(kainaTekstas);
        preke.kiekis = stoi(kiekisTekstas);

        prekes.push_back(preke);
    }

    failas.close();
    return prekes;
}

void issaugotiIFaila(const vector<Preke>& prekes, string failoPavadinimas) {
    ofstream failas(failoPavadinimas);

    if (!failas.is_open()) {
        cout << "Nepavyko issaugoti duomenu i faila.\n";
        return;
    }

    for (const Preke& preke : prekes) {
        failas << preke.id << ";"
               << preke.pavadinimas << ";"
               << preke.kategorija << ";"
               << fixed << setprecision(2) << preke.kaina << ";"
               << preke.kiekis << "\n";
    }

    failas.close();
}

void rodytiPreke(const Preke& preke) {
    cout << left << setw(5) << preke.id
         << setw(22) << preke.pavadinimas
         << setw(18) << preke.kategorija
         << setw(10) << fixed << setprecision(2) << preke.kaina
         << setw(8) << preke.kiekis << "\n";
}

void rodytiAntraste() {
    cout << left << setw(5) << "ID"
         << setw(22) << "Pavadinimas"
         << setw(18) << "Kategorija"
         << setw(10) << "Kaina"
         << setw(8) << "Kiekis" << "\n";
    cout << string(63, '-') << "\n";
}

void rodytiVisasPrekes(const vector<Preke>& prekes) {
    if (prekes.empty()) {
        cout << "Prekiu sarasas tuscias.\n";
        return;
    }

    rodytiAntraste();
    for (const Preke& preke : prekes) {
        rodytiPreke(preke);
    }
}

int rastiPrekesIndeksaPagalId(const vector<Preke>& prekes, int id) {
    for (int i = 0; i < (int)prekes.size(); i++) {
        if (prekes[i].id == id) {
            return i;
        }
    }
    return -1;
}

int sugeneruotiNaujaId(const vector<Preke>& prekes) {
    int didziausiasId = 0;
    for (const Preke& preke : prekes) {
        if (preke.id > didziausiasId) {
            didziausiasId = preke.id;
        }
    }
    return didziausiasId + 1;
}

void pridetiPreke(vector<Preke>& prekes) {
    Preke naujaPreke;
    naujaPreke.id = sugeneruotiNaujaId(prekes);

    cout << "Iveskite prekes pavadinima: ";
    getline(cin, naujaPreke.pavadinimas);

    cout << "Iveskite kategorija: ";
    getline(cin, naujaPreke.kategorija);

    naujaPreke.kaina = nuskaitytiRealuSkaiciu("Iveskite kaina: ");
    naujaPreke.kiekis = nuskaitytiSveikaSkaiciu("Iveskite kieki: ");

    prekes.push_back(naujaPreke);
    cout << "Preke sekmingai prideta. Jai suteiktas ID: " << naujaPreke.id << "\n";
}

void redaguotiPreke(vector<Preke>& prekes) {
    int id = nuskaitytiSveikaSkaiciu("Iveskite redaguojamos prekes ID: ");
    int indeksas = rastiPrekesIndeksaPagalId(prekes, id);

    if (indeksas == -1) {
        cout << "Preke su tokiu ID nerasta.\n";
        return;
    }

    cout << "Dabartiniai prekes duomenys:\n";
    rodytiAntraste();
    rodytiPreke(prekes[indeksas]);

    cout << "Iveskite nauja pavadinima: ";
    getline(cin, prekes[indeksas].pavadinimas);

    cout << "Iveskite nauja kategorija: ";
    getline(cin, prekes[indeksas].kategorija);

    prekes[indeksas].kaina = nuskaitytiRealuSkaiciu("Iveskite nauja kaina: ");
    prekes[indeksas].kiekis = nuskaitytiSveikaSkaiciu("Iveskite nauja kieki: ");

    cout << "Prekes duomenys sekmingai atnaujinti.\n";
}

void pasalintiPreke(vector<Preke>& prekes) {
    int id = nuskaitytiSveikaSkaiciu("Iveskite salinamos prekes ID: ");
    int indeksas = rastiPrekesIndeksaPagalId(prekes, id);

    if (indeksas == -1) {
        cout << "Preke su tokiu ID nerasta.\n";
        return;
    }

    prekes.erase(prekes.begin() + indeksas);
    cout << "Preke sekmingai pasalinta.\n";
}

void ieskotiPagalPavadinima(const vector<Preke>& prekes) {
    string paieska;
    cout << "Iveskite ieskoma pavadinimo dali: ";
    getline(cin, paieska);

    bool rasta = false;
    rodytiAntraste();

    for (const Preke& preke : prekes) {
        if (preke.pavadinimas.find(paieska) != string::npos) {
            rodytiPreke(preke);
            rasta = true;
        }
    }

    if (!rasta) {
        cout << "Pagal ivesta pavadinima prekiu nerasta.\n";
    }
}

void rikiuotiPagalKaina(vector<Preke>& prekes) {
    sort(prekes.begin(), prekes.end(), [](const Preke& a, const Preke& b) {
        return a.kaina < b.kaina;
    });

    cout << "Prekes surikiuotos pagal kaina didejimo tvarka.\n";
    rodytiVisasPrekes(prekes);
}

void skaiciuotiBendraVerte(const vector<Preke>& prekes) {
    double bendraVerte = 0;

    for (const Preke& preke : prekes) {
        bendraVerte += preke.kaina * preke.kiekis;
    }

    cout << fixed << setprecision(2);
    cout << "Bendra visu prekiu verte sandelyje: " << bendraVerte << " EUR\n";
}

void filtruotiPagalKategorija(const vector<Preke>& prekes) {
    string kategorija;
    cout << "Iveskite kategorija: ";
    getline(cin, kategorija);

    bool rasta = false;
    rodytiAntraste();

    for (const Preke& preke : prekes) {
        if (preke.kategorija == kategorija) {
            rodytiPreke(preke);
            rasta = true;
        }
    }

    if (!rasta) {
        cout << "Sioje kategorijoje prekiu nerasta.\n";
    }
}

void rodytiMeniu() {
    cout << "\n===== PARDUOTUVES PREKIU APSKAITA =====\n";
    cout << "1. Rodyti visas prekes\n";
    cout << "2. Prideti nauja preke\n";
    cout << "3. Redaguoti preke\n";
    cout << "4. Pasalinti preke\n";
    cout << "5. Ieskoti prekes pagal pavadinima\n";
    cout << "6. Rikiuoti prekes pagal kaina\n";
    cout << "7. Skaiciuoti bendra prekiu verte\n";
    cout << "8. Filtruoti pagal kategorija\n";
    cout << "9. Issaugoti duomenis\n";
    cout << "0. Issaugoti ir baigti darba\n";
    cout << "Pasirinkite veiksma: ";
}

int main() {
    vector<Preke> prekes = nuskaitytiIsFailo(FAILO_PAVADINIMAS);

    int pasirinkimas;

    do {
        rodytiMeniu();
        cin >> pasirinkimas;

        if (cin.fail()) {
            cout << "Klaida: pasirinkimas turi buti skaicius.\n";
            isvalytiIvesta();
            continue;
        }
        isvalytiIvesta();

        switch (pasirinkimas) {
            case 1:
                rodytiVisasPrekes(prekes);
                break;
            case 2:
                pridetiPreke(prekes);
                break;
            case 3:
                redaguotiPreke(prekes);
                break;
            case 4:
                pasalintiPreke(prekes);
                break;
            case 5:
                ieskotiPagalPavadinima(prekes);
                break;
            case 6:
                rikiuotiPagalKaina(prekes);
                break;
            case 7:
                skaiciuotiBendraVerte(prekes);
                break;
            case 8:
                filtruotiPagalKategorija(prekes);
                break;
            case 9:
                issaugotiIFaila(prekes, FAILO_PAVADINIMAS);
                cout << "Duomenys issaugoti faile.\n";
                break;
            case 0:
                issaugotiIFaila(prekes, FAILO_PAVADINIMAS);
                cout << "Duomenys issaugoti. Programa baigia darba.\n";
                break;
            default:
                cout << "Tokio pasirinkimo nera. Bandykite dar karta.\n";
        }
    } while (pasirinkimas != 0);

    return 0;
}
