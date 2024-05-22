# **Muzikos grojimo programėlė**

**Komandos nariai:** Tomas Kazonas, Nojus Sandovas, Levon Airapetian

**Komandos pavadinimas:** Špotify

## **Projekto aprašymas**

Muzikos grojimo programėlė vartotojams suteikia įvairias galimybes,
įskaitant muzikos grojimą, naujų grojaraščių kūrimą ir jų tvarkymą. Vartotojai
gali lengvai valdyti dainas, kurti grojaraščius pagal savo skonį ir mėgstamas
dainas bei reguliuoti garso lygį. Programėlė leidžia vartotojams naudotis
įvairiomis funkcijomis, įskaitant:

•    **Grojaraščių valdymas:**
Vartotojai gali personalizuoti savo grojaraščius, pridėdami, šalindami dainas,
redaguodami grojaraščio pavadinimą. Yra galimybė pasirinkti, ar grojaraščius
norima sugroti vieną kartą arba juos kartoti. Taip pat yra galimybė sumaišyti
dainų eilės tvarką grojaraščiuose, kad dainos grotų atsitiktine tvarka.

•    **Dainų valdymas:**
Programėlė leidžia vartotojams groti, stabdyti, tęsti, dainas. Taip pat yra
galimybė pereiti prie ankstesnės arba sekančios dainos grojaraštyje.

•    **Garso reguliavimas:**
Vartotojai gali reguliuoti garso lygį pagal savo pageidavimus, kad būtų patogu
klausytis muzikos.

### [**Proof of concept**](https://www.youtube.com/watch?v=BZN2oEVn90A)

### Darbo apimties ir laiko ataskaita bei pažymio pasiskirstymas

|                   | Tomas                                        | Nojus                                                                       | Levon                                                                               |
| ----------------- | -------------------------------------------- | --------------------------------------------------------------------------- | ----------------------------------------------------------------------------------- |
| Darbas            | Projekto struktūra,<br />activity diagramos | Proof of concept +<br />demonstracija YouTube,<br />sukurta GitLab saugykla | Sugalvotas komandos<br /> pavadinimas, projekto <br />aprašymas, use-case diagrama |
| Laikas (iš viso) | 300 min.                                     | 45 min.                                                                     | 50 min.                                                                             |
| Pažymys          | 40%                                          | 30%                                                                         | 30%                                                                                 |

## Back-end (P2)

### Panaudoti / atpažinti projektavimo šablonai

1. **Singleton Pattern:**
   „Player“ klasė elgiasi kaip viena, nes ji valdo muzikos ir grojaraščių grojimą visoje programoje. Tai užtikrina, kad yra tik vienas grotuvas
2. **Factory method šablonas:**

„Playlist“ klasėje yra metodas „getTrackListFromCurrentFolder()“, kuris veikia kaip factory-method. Jis sukuria ir grąžina „Track“ objektų sąrašą pagal dabartiniame aplanke esančius muzikos failus.

3. **Observer šablonas:**

Grotuvas leidžia vartotojams groti, pristabdyti, sustabdyti, pereiti prie kitos dainos arba grįžti į ankstesnį dainos. Šiuos veiksmus atlieka klasė „Player“. Kitos klasės, pvz., „Track“ ir „Playlist“, yra observer‘iai, reaguojantys į atkūrimo būsenos pokyčius.

4. **Iterator šablonas:**

„Player“ klasė kartoja grojaraščius ir grojaraščių takelius, naudodama indeksu pagrįstą iteraciją, leidžiančią vartotojams naršyti grojaraščius ir pasirinkti konkrečius takelius, kuriuos nori groti.

5. **Command šablonas:**

Player‘io valdymo srautas primena komandų modelio struktūrą. Vartotojo įvestys interpretuojamos player‘io, atliekant atitinkamus veiksmus, tokius kaip grojimas, sustojimas, praleidimas ir kt.

##### Šie dizaino šablonai pagerina kodų bazės:

* Kodo organizavimo ir priežiūros tobulinimą.
* Funkcionalumo enkapsuliavimą
* Lengvesnis išplėtimas, leidžiantis lengviau pridėti naujų funkcijų ar modifikacijų.
* Kūrėjų kodo skaitomumo ir supratimo gerinimas.

### Klasių diagrama

![1715329641293](image/Readme/1715329641293.png)

### Darbo apimties ir laiko ataskaita bei pažymio pasiskirstymas

|                   | Tomas                                                                                                             | Nojus            | Levon                                                                                                                                                                          |
| ----------------- | ----------------------------------------------------------------------------------------------------------------- | ---------------- | ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------ |
| Darbas            | Grojaraščių valdymas<br />(sukurti, ištrinti, pervadinti,<br /> paleisti grojaraštį),<br /> garso valdymas. | Dainų valdymas. | Grojaraščių valdymas<br />(pridėti, ištrinti dainą, kartoti, maišyti <br />grojaraštį, paleisti vieną kartą), <br />panaudoti / atpažinti projektavimo šablonai. |
| Laikas (iš viso) | 300 min.                                                                                                          | 120 min.         | 150 min.                                                                                                                                                                       |
| Pažymys          | 40%                                                                                                               | 30%              | 30%                                                                                                                                                                            |

### Programos paleidimas

Pirmiausia reikia programą sukompiliuoti.

```
make all
```

Tada paleidžiame programą:

```
MusicPlayer.exe
```

Esant reikalui galima viską išvalyti:

```
make clean
```

Arba perkurti:

```
make rebuild
```


# Front-end (P3)

## Projekto vizija

Projekto metu, siekėme sukurti windows aplikaciją - muzikos grotuvą. Projektavome jog programą turės šiuos funkcionalumus:

* Dainų valdymas - galimybė sustabdyti, pratęsti, pereiti prie kito ar ankstesnio muzikos takelio.
* Grojaraščių valdymas - galimybė kurti, redaguoti ir personalizuoti nuosavus muzikos grojaraščius, prie jų pridėti, šalinti dainas, keisti jų eiliškumą, grojaraščius kartoti, ar maišyti juose esančių dainų eiliškumą.
* Garso reguliavimas - tylinti, garsinti muzikos takelį.

## Projekto rezultatas

Galutinėje projekto versijoje mums pavyko įgyvendinti šiuos funkcionalumus:

* Dainų valdymą
* Grojaraščių valdymą (išskyrus galimybę turėti daugiau negu vieną grojaraštį)
* Garso reguliavimą

## Projekto vystymosi eiga ir sunkumai

Projekto (P2) etapas vyko sklandžiai, buvo sukurta programos terminalinė versija įgyvendinanti visus užsibrėžtus programos funkcionalumus ir galimybes. Tačiau (P3) etapo metu, iškilo nemažai kėblumų, kuriant aplikacinę programą ir jos GUI, kadangi nei vienam komandos nariui anksčiau neteko susidurti su GUI kūrimų naudojantis C++ kalba. Prieš pradedant darbą teko skirti nemažai laiko papildomos informacijos ir šaltinių paieškai apie C++ GUI kūrimo priemones ir galimybes. Užduočiai įgyvendinti pasirinkome `wxWidgets` GUI biblioteka, kadangi `Qt` biblioteka, kurią iš pradžių tikėjomis pasinaudoti buvo mokama. Dirbant su `wxWidgets` išryškėjo jos ribotumas ir trūkumai - biblioteka reikalavo ir konkretaus IDE įsidiegimo `Microsoft Visual Studio`, dėl šios priežasties kodo ir darbo dalijimasis tarp komandos narių tapo sudėtingesnis, kadangi eksportuojant ir importuojant kolegų darbą, teko sugaišti nemažai laiko iš naujo susikonfiguruojant IDE tam jog ji veiktų su instaliuota `wxWidgets` biblioteką. Įveikus šiuos trūkdžius programą pavyko užbaigti ir pasiekti norimą rezultatą, tačiau manau jog ateityje dirbant su panašiu projektu ar GUI rinktumėmis kitą biblioteką.

## Naudotos bibliotekos ir įrankiai

* `wxWidgets` - Šios bibliotekos įrankiais buvo sukurtas GUI.
* `windows.h` - Bilbioteka leidžia naudotis specifinėmis Windows funkcijomis, įgalinančiomis audio failų paleidimą, valdymą, pridėjimą ir t.t.
* `winmm.lib` - Biblioteka reikalinga garso takelių paleidimui ir valdymui.
* `filesystem` - Leidžia iteruoti per direktorijos failus pagal jų tipą, pasirinktiems failams atlikti tolimesnius veiksmus.
* `locale` - Teikia priemones lokalių nustatymų ir simbolių klasifikavimo valdymui.
* `codecvt` - Teikia įrankius simbolių koduotės konvertavimui tarp skirtingų simbolių rinkinių (pvz., iš wide string į string).
* Kitos įprastos C++ bibliotekos ir įrankiai: `vector`, `conio.h`, `algorithm`, `random`.

## Plėtimo galimybės

* Pridėti galimybė vartotojui sukurti daugiau negu vieną grojaraštį ir tarp jų rinktis.
* Pridėti galimybė vartotojui grojamą garso takelį sulėtinti, pagreitinti, atsukti ar persukti nuo nurodytos vietos.
* Patobulinti GUI vizualumą, padaryti jį patrauklesnį vartotojui.

## Darbo apimties ir laiko ataskaita bei pažymio pasiskirstymas

|                   | Tomas                                                                                                                                                                                                      | Nojus                                                                      | Levon                                                                                               |
| ----------------- | ---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- | -------------------------------------------------------------------------- | --------------------------------------------------------------------------------------------------- |
| Darbas            | GUI pradžia (frame),<br /> muzikos grotuvo mygtukai (play,<br />stop, next, previous), <br />padaryta, kad grotų visą grojaraštį<br />kai kurių backend <br />funkcijų pritaikymas veikimui su GUI. | Muzikos grotuvo mygtukai<br /> (repeat, shuffle),<br />garso reguliavimas. | Grojaraščių valdymo<br /> mygtukai (add, remove),<br />grojaraščio dainų <br />atvaizdavimas. |
| Laikas (iš viso) | 540 min.                                                                                                                                                                                                   | 300 min.                                                                  | 360 min.                                                                                            |
| Pažymys          | 33%                                                                                                                                                                                                        | 33%                                                                        | 33%                                                                                                 |


## Programos paleidimas

Galima paleisti jau sukompiliuotą programos versiją, tai yra atidaryti faila pavadinimu:

```
MusicPlayer.exe
```
