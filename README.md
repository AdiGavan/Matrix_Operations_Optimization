"Copyright [2019] Gavan Adrian-George, 334CA"

Nume, prenume: Gavan, Adrian-George

Grupa, seria: 334CA

Tema 2 ASC - Matrix Operations Optimization

A. Continut arhiva:
===================

1. Fisierele din schelet:
- main.c
- utils.h
- compare.c
- Makefile - modificat conform cerintelor
- Makefile.icc - modificat conform cerintelor
- input
- solver_blas.c - contine implementarea utilizand functii blas
- solver_neopt.c - contine implementarea neoptimizata
- solver_opt.c - contine implemantarea optimizata

2. Scripturi pentru testare:
- script_gcc.sh - script pentru aflarea timpilor de rulare si pentru verificarea
corectitudinii pentru "input", pentru toate functiile, utilizand "gcc".
- script_icc.sh - script pentru aflarea timpilor de rulare si pentru verificarea
corectitudinii pentru "input", pentru toate functiile, utilizand "icc".
- script_gcc_grafice - script pentru aflarea timpilor de rulare pentru testul
"input_custom_grafice". Acest fisier contine 10 teste de diferite dimensiuni,
iar timpii rezultati vor fi utilizati pentru trasarea graficelor. Se calculeaza
timpii pentru toate functiile si se utilizeaza "gcc".
- script_icc_grafice - script pentru aflarea timpilor de rulare pentru testul
"input_custom_grafice". Acest fisier contine 10 teste de diferite dimensiuni,
iar timpii rezultati vor fi utilizati pentru trasarea graficelor. Se calculeaza
timpii pentru toate functiile si se utilizeaza "icc".

3. Grafice:
- gcc_graph.png - Grafic pentru analiza comparativa a celor 4 functii cu "gcc".
- icc_graph.png - Grafic pentru analiza comparativa a celor 4 functii cu "icc".
- gcc_vs_icc_graph.png - Grafic pentru analiza comparativa intre "gcc" si "icc".

4. Rezultate:
- gcc_results - fisier cu rezultate utilizat pentru generarea graficelor
- icc_results - fisier cu rezultate utilizat pentru generarea graficelor
- script_gcc_grafice.sh.o1079376 - fisier cu rezultatele utilizate in grafice
pentru "gcc", utilizand script_gcc_grafice.
- script_icc_grafice.sh.o1079370 - fisier cu rezultatele utilizate in grafice
pentru "icc", utilizand script_icc_grafice.
- script_gcc.sh.o1079332 - fisier cu rezultatele timpilor si corectitudinea
testului "input" pentru toate functiile, utilizand "gcc" (script_gcc.sh).
- script_icc.sh.o1079335 - fisier cu rezultatele timpilor si corectitudinea
testului "input" pentru toate functiile, utilizand "icc" (script_icc.sh).

5. Makefile_graphs - makefile utilizat pentru generarea graficelor

B. Implementari variante
=========================

1. Implementare variantei blas:
- Pentru implementarea blas s-au utilizat 2 functii: cblas_dsyr2k si cblas_dgemm.
- Urmarind documentatia de pe netlib.org am aflat ca functia cblas_dsyr2k poate
calcula "C := alpha*A*B**T + alpha*B*A**T + beta*C" sau "C := alpha*A**T*B +
alpha*B**T*A + beta*C". Am utilizat cea de-a 2-a varianta, iar rezultatul a fost
stocat intr-o matrice auxiliara. Aceasta functie refera si doar partea superior
triunghiulara a lui C. De aceea s-au utilizat parametrii CblasUpper(superior
triunghiulara) si CblasTrans(a doua varianta). Scalarii alpha si beta vor fi 1.0.
- Utilizand prima functie, avem in acest moment calculata o mare parte din
formula: zerotr(At * B + Bt * A).
- A doua functie blas este folosita pentru ridicarea la patrat. Functia
cblas_dgemm realizeza operatia "C := alpha*op( A )*op( B ) + beta*C", A si B pot
fi sau nu transpuse, iar rezultatul este stocat in C. Am apelat functia cu
parametrii CblasNoTrans pentru A si B si am considerat A = Aux si B = tot cu Aux.
Scalarul alpha va fi 1.0, iar beta va fi 0.0 (C este plina cu 0 deci nu este
nicio problema).
- Pentru a putea utiliza functiile cblas s-a adaugat "#include <cblas.h>" in
fisier, iar in Makefile si Makefile.icc au fost adaugate:
LIBDIRS=-L/usr/lib64/atlas
LIBS=-lsatlas

2. Implementarea variantei neoptimizata:
- Pentru a fi complet neoptimizata ar fi insemnat sa fac fiecare operatie
(de transpunere, inmultire, adunare) pe rand. Adica sa fac mai intai fiecare
transpunere, apoi At * B etc. Acest lucru dura foarte mult si, conform temei,
complexitatea variantei optimizate trebuie sa fie aceeasi cu cea a variantei
neoptime. Am facut cele 2 transpunse in aceeasi secventa, apoi am calculat
in aceeasi secventa At * B + Bt * A, iar apoi am facut ridicarea la patrat.
- Au fost nevoie de 4 matrici, cate una pentru fiecare transpunsa, una pentru
C si una auxiliara.
- Tot pentru a pastra aceeasi complexitate, in secventa At * B + Bt * A se va
calcula doar matricea superior triunghiulara => mai putine calcule + nu se mai
face dupa o secventa speciala doar pentru a pune zero-uri in matrice.

3. Implementarea variantei optimizate:
- S-a pastrat aceeasi idee ca si la varianta neoptimizata.
- Mai intai se aloca matricile, apoi intr-o secventa se calculeaza At si Bt,
apoi in alta secventa se calculeaza At * B + Bt * A, iar in ultima secventa se
face ridicarea la patrat.
- S-au utilizat indicatiile din laboratorul 5 de ASC.
- Am inceput prin a inversa ordinea celor 3 for-uri. In loc de ordinea i, j, k
am folosit ordinea i, k, j.
- Se calculeaza doar elementele pentru partea superior triunghiulara a matricii.
- Dupa aceea am facut variabilele i, j si k register.
- Am incercat sa folosesc cat mai multi registrii si pointeri, cum am invatat la
laborator, pentru a fi mai optim codul si pentru a scapa de referiri de tipul
A[i].
- Incercasem initial sa nu mai calculez transpusele separat, ci sa lucrez direct
cu elementele corespunzatoare din matricea A fara sa o mai transpun, doar ca
timpii erau mai mici.
- Utilizand optimizarile de la laborator, in secventele in care se calculeaza
At*B+Bt*A si cea in care se ridica la patrat, in ultimul for avem doar pointeri
si registrii, ceea ce este foarte eficient.
- Utilizand aceste optimizari invatate la laborator, am reusit sa scriu un
cod eficient. Pe testul de 1600 de elemente, pentru gcc, programul ruleaza in
12-13 secunde, ceea ce este un timp foarte bun. Consider ca am implementat si
bonusul, pentru ca se cerea ca timpul de executie sa fie mai mic de 19 secunde.

4. Implementarea variantei folosind flaguri de optimizare:
- Am folosit flagul -Ofast atat pentru gcc cat si pentru icc.
- Flagul Ofast face tot ce face si O3 dar aduce si alte lucruri in plus, care
pot fi sau nu valabile in functie de compilator.
- Conform scheletului, flagul este folosit pentru compilarea variantei
neoptimizate. Optimizarea este enorma, programul ruland de 4 ori mai rapid.
- Am folosit acelasi flag pentru ambele compilatoare pentru a face o analiza
cat mai corecta. Se poate observa si pe graficele rezultate ce diferenta enorma
este intre panta pentru varianta neoptimizata si panta acestei variante.

C. Analiza performantei:
========================

1. Analiza performantei blas vs neopt vs opt_m vs opt_f pentru gcc:
- Varianta cea mai rapida este de departe varianta in care se utilizeaza blas.
Nicio alta varianta nici macar nu se apropie de rezultatele acesteia. Timpul
este extraordinar de mic, ruland in putin peste 2 secunde testul cu dimensiunea
de 1600. Este de 30 de ori mai rapid decat varianta neoptimizata si de 6-7 ori
mai rapid decat varianta optimizata manual sau optimizata cu flaguri. Se poate
observa si pe grafic ca panta acestei variante este foarte apropiata de axa OX
chiar si pentru cele mai mari teste.
- Varianta cea mai ineficienta este clar varianta neoptimizata, care pentru
testul de 1600 de elemente ruleaza in peste 66 de secunde. Ruleaza de 4 ori
mai incet decat varianta optimizata manual sau cea optimizata cu flag-uri.
Folosind doar referiri de genul A[i], nefolosind pointeri sau registrii este
evident faptul ca nu se poate compara cu celelalte variante. Se poate observa si
pe grafice cum panta acestei variante creste mult mai rapid fata de celelalte.
- Varianta optimizata cu flag-uri este mult mai rapida decat varianta neoptima,
facand foarte multe optimizari codului. Compilatorul face aceste optimizari in
functie de ceea ce stie deja despre program. Acelasi cod neoptimizat fara flag
ruleaza in 66 de secunde, iar cu flag ruleaza in 16-17 secunde, fiind de 4 ori
mai rapid.
- Varianta cea mai buna (dupa blas bineinteles) a fost varianta optimizata
manual. Pe testul cu dimensiunea 1600 scoate putin peste 12 secunde, ceea ce
este un rezultat foarte bun. Merge mai rapid chiar si fata de varianta
optimizata cu flag-uri. Este de 5 ori mai rapid decat varianta neoptimizata.
Tot acest speedup a fost adus doar de inversarea for-urilor, utilizarea
pointerilor pentru a evita referintele de genul A[i] si utilizarea registrelor.
Chiar si cu aceste optimizari, eficienta codului nu se apropie de varianta cu
blas. Initial uitasem sa fac si indicii i, j si k registrii si obtineam 21-22 de
secunde pe cluster. Acest lucru mi-a aratat inca o data ca o mica neatentie face
o diferenta enorma. Doar facand acei indici registrii, durata testului aproape
s-a injumatatit.

2. Analiza performantei blas vs neopt vs opt_m vs opt_f pentru icc:
- Rezultatele dintre variante sunt asemanatoare cu cele de la gcc, cu exceptia
variantei optimizate manual. Proportiile s-au pastrat in mare parte, varianta
blas este si aici de departe cea mai rapida, varianta neoptimizata este cea mai
lenta si varianta optimizata cu flag este mult mai optima, dar nu se compara cu
blas. Ruleaza tot de 4 ori mai repede decat varianta neoptimizata. Ceea ce
difera foarte mult si m-a surprins este timpul pentru varianta opimizata manual,
pentru ca aici pe testul cu 1600 se obtin in jur de 23 de secunde. In acest caz,
optimizarea cu flag a fost mult mai buna decat optimizarea manuala, fiind cu
7 secunde mai rapida pe testul cu 1600. Chiar si asa, varianta optimizata manual
ruleaza de aproape 3 ori mai rapid decat varianta neoptimizata.

3. Analiza performantei gcc vs icc:
- Din rezultatele obtinute, reiese faptul ca varianta cu blas are cam acelasi
timp pentru ambele compilatoare. Variantele neoptimizate si optimizata cu flag
au avut rezultate foarte putin diferite. Pentru unele teste a fost putin mai
rapid icc, pentru alte teste a fost putin mai repid gcc. Pentru testele mari,
din rezultatele obtinute din rularea pe coada ibm-dp.q a clusterului, reiese ca
icc a avut timpi putini mai buni (cam cu o secunda). Dar aceste mici diferente
pot fi date si de momentul rularii si de cat de incarcata era coada respectiva.
Diferenta foarte mare poate fi observata insa la varianta optimizata manual,
unde gcc a obtinut timpi mult mai buni, aproape de 2 ori mai buni.

4. Realizarea graficelor:
- Pentru realizarea graficelor se folosesc fisiere gcc_results si icc_results.
Acestea contin rezultatele obtinute din rularea scripturilor care utilizau
testul "input_custom_grafice", tocmai pentru a avea mai multi timpi si mai multe
dimensiuni. S-a utilizat gnuplot. Pentru refacerea graficelor se poate folosi
makefileul inclus in arhiva, "Makefile_graphs", utilizand comanda "make -f
Makefile_graphs". Aceasta comanda genereaza 3 fisiere de tip .png, unul pentru
rezultatele gcc, unul pentru rezultatele icc si unul pentru a le putea compara
pe amandoua.

D. Testare si mediu de testare
===============================

- Tema a fost testata pe clusterul facultatii, pe coada ibm-dp.q, conform
indicatiilor din tema.
- Ma logam pe cluster si apoi ma logam pe coada folosind comanda "qlogin -q
ibm-dp.q"
- Mai deschideam un terminal unde ma logam doar pe cluser.
- Am creat diferite scripturi pentru testarea timpului si corectitudinea
programului. Am creat cate un script pentru gcc si icc care testeaza timpul si
corectitudinea programului pentru testul input. Apoi am creat cate un script
pentru gcc si icc care ruleaza mai multe teste pentru a avea mai multe date in
reprezentarea graficelor.
- Trebuie sa se compileze mai intai fisierul compare.c si executabilul sa se
numeasca compare.
- Apoi se foloseste comanda "qsub -cwd -q ibm-dp.q <nume_script>" din terminalul
in care nu suntem logati pe coada.
- Se asteapta obtinerea rezultatelor.
- Fisierele out si executabilele nu sunt sterse la finalul executiei scriptului.
- Graficele au fost realizate local dupa ce am obtinut datele pe cluster.

E. Observatii
=============

- Bonusul a fost implementat prin obtinerea unui timp de putin peste 12 secunde
pe varianta optimizata manual folosing gcc.
- Dupa ce scripturile sunt rulate pe coada, fisierele out si executabilele nu
sunt sterse.
- In graficul ce compara icc si gcc, cele 2 linii de la blas sunt suprapuse si
se vede doar una dintre ele.
- Inainte de trimiterea scripturilor sa fie rulate pe coada, trebuie compilat
programul compare.c in executabilul compare, pentru ca scripturile folosesc
executabilul pentru a verifica rezultatele.
- Scripturile ce testeaza testul custom pentru a obtine mai multe date pentru
grafice dureaza destul de mult (se pot insuma timpii din gcc_results sau
icc_results).
