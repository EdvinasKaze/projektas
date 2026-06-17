# Parduotuvės prekių apskaitos sistema

## Projekto tikslas

Sukurti C++ konsolinę programą, kuri leidžia valdyti parduotuvės prekių duomenis ir pritaiko struktūrinio programavimo principus.

## Tema

Pasirinkta tema – parduotuvės prekių apskaita. Programa saugo prekių ID, pavadinimą, kategoriją, kainą ir kiekį sandėlyje.

## Funkcionalumas

Programa turi meniu principu veikiančią konsolinę sąsają.

Įgyvendintos CRUD operacijos:

- **Create** – naujos prekės pridėjimas;
- **Read** – visų prekių peržiūra;
- **Update** – prekės redagavimas pagal ID;
- **Delete** – prekės pašalinimas pagal ID.

Papildomos funkcijos:

- prekių paieška pagal pavadinimą;
- prekių rikiavimas pagal kainą;
- bendros prekių vertės sandėlyje skaičiavimas;
- prekių filtravimas pagal kategoriją.

## Naudojami failai

- `ParduotuvesPrekiuApskaita.cbp` – Code::Blocks projekto failas;
- `main.cpp` – programos kodas;
- `prekes.txt` – pradinis duomenų failas su prekių sąrašu.

Duomenų failo formatas:

```txt
ID;Pavadinimas;Kategorija;Kaina;Kiekis
```

Pavyzdys:

```txt
1;Duona;Maistas;1.20;30
```

## Paleidimas per Code::Blocks

1. Atsisiųskite ir išskleiskite projekto aplanką.
2. Atidarykite Code::Blocks programą.
3. Pasirinkite **File → Open**.
4. Atidarykite failą `ParduotuvesPrekiuApskaita.cbp`.
5. Paspauskite **Build and Run** arba klavišą **F9**.

Svarbu: `prekes.txt` turi būti tame pačiame aplanke kaip ir `main.cpp`, nes programa iš šio failo nuskaito pradinius duomenis ir į jį išsaugo pakeitimus.

## Panaudotos programavimo konstrukcijos

- kintamieji ir pagrindiniai duomenų tipai;
- `if`, `else`, `switch` sąlyginiai sakiniai;
- `for` ir `do-while` ciklai;
- funkcijos;
- vartotojo sukurta struktūra `struct Preke`;
- `vector` duomenų kolekcija;
- duomenų nuskaitymas iš tekstinio failo;
- duomenų įrašymas į tekstinį failą.

## Autorius

Darbą atliko: įrašykite savo vardą ir pavardę.
