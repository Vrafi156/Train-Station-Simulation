Tema1 SDA Neacsu Iulian 311 CD
Pentru inceputul temei am implementat cele 3 functii precizate la sfarsitul cerintei:
(open_train_station , close_train_station si show_existing_trains)

Pentru open_train_station am alocat memorie unui pointer de tipul TrainStation iar dupa
am alocat memorie pentru vectorul de pointeri si pentru fiecare peron in parte.
Am marcat fiecare peron abia creat, punanadu-i puterea locomotivei -1 care reprezinta faptul 
ca acest peron este lipsit de locomotiva(gol).

Pentru functia close_train_station am parcurs fiecare peron, am eliberat memorie pentru (fiecare vagon) iar apoi
fiecare tren aflat pe un peron, iar dupa am dezalocat memoria fiecarui peron in parte.La sfarsit
am dezalocat memorie pentru vectorul de pointeri si in final pentru TrainStation;

Pentru functia show_existing_trains am folosit comanda fprintf pentru a scrie in respectivul fisier
si verificam daca un peron avea puterea locomotivei -1 (adica daca acesta nu avea locomotiva)
in caz negativ, afisam puterea locomotivei si greutatea fiecarul vagon in formatul prezentat
in cerinta.

Pentru Cerinta1 a trebuit sa implementez diferite functii precum:
-arrive_train In aceasta functie am verificat daca valorile parametrilor din antet 
sunt valide (adica daca platforma este un numar intre 0 si staion->platform_no, in caz contrat functia nu se executa)
si daca locomotiva care se adauga pe peron este valida >= 0). Am mai si verificat daca locomotiva se adauga pe un peron 
gold in caz contrar functia nu executa nimic.Dupa aceste
verificari functia atribuie unui anumit peron o locomotiva cu o anumita putere (puterea locomotivei este schimbata din )
-leave_train In aceasta functie verific daca peronul care urmeaza sa fie eliberat este unul valida
adica daca parametrul platform este valid ca mai sus.In cazul in care este valid
schimb puterea locomotivei in -1 (adica peronul n are locomotiva) si eliberez memoria
fiecarui vagon asemanator cu stergerea elementelor dintr o lista simplu
inlantuita
-add_train_car In aceasta functie verific daca greutatea este >= 0 si daca parametrul
peron prezinta o valoarea valid cum este verificat si mai sus. Dupa aceste verificari
ma uit daca peronul meu nu are niciun vagon. Daca nu are niciun vagon, cel pe care il inserez 
va fi primul (caz precizat si in code), altfel parcurg lista pana la ultimul element 
si ultimul meu element din lista va avea adresa celui nou creat.
-remove_train_cars In aceasta functie am facut verificarile precizate mai sus si am facut o functie
aditionala pentru stergerea trenurilor. In functia mea stergetren verific cazul in care
am la inceputul listei o succesiune de vagoane cu greutatea egala cu cea a vagoanelor ce trb sterse.
In acest caz sterg fiecare vagon, iar dupa sterg restul vagoanelor care nu se afla la inceputul
listei asemantor cu stergerea unui nod dintr-o lista dupa o anumita valoare.
-move_train_cars Aceasta functie a fost grea, dar experienta s-a meritat.Pentru aceasta
funcite am avut de verificat diferite conditii precum daca pozitiile de la care iau , respectiv pun vagoane 
sunt valide, daca peronul din care iau are vagoane sau nu, si daca in trenul in care inserez vagoane am sau nu vagoane. Am 
verificat si cazul particular cand trenul in care inserez nu are vagoane si pozitia pe care se insereaza 
 este 1. Dupa asta mi-am luat 2 pointeri si am parcurs vagoanele din amandoua pana am ajuns
inaintea pozitiilor de pa care iau respectiv adaug trenuri. Am verificat daca pozitia de pe care iau trenuri este 
fix primul vagon. In aceset caz parcurg toate vagoanele pe care trebuie sa le iau. Cu ajutorul unui pointer de tip
TrainCar(head1) am luat adresa urmatorului vagon fix dupa cele care trebuiesc mutate(last = head1->next).Tot in cazul in care pos_a == 1;
verific daca pos_b == 1, in acest caz adresa primul vagon din platform_b devine adresa primul vagon din platform_A
iar dupa pun la loc restul de vagoane de pe platform_b inapoi zicand ca head1->next = head2->next pointeri (head2 este la fel cu head1 doar ca pentru trenul de pe platforma b). In final refac vagoanele
din platform_A puna ca prima adresa a acestuia devine last;
Tot in cazul in care pos_a == 1 execut si cazul in care pos_b != 1 iar aici head1->next devine head2->next;
iar head2 ia adresa primului vagon din platform_A
In cazul in care pos_a != 1 ma folosesc de inca un pointer prev care tine minte vagonul de inaintea primului care trebuie mutat
si iar iau cazul in care pos_b == 1, in acest caz adresa ultimului vagon care trb mutat de ->next devine head2;
si adresa primului element de pe platform_B devine station->platforms[platform_A]->TrainCar. Dupa asta refac legaturile
din trenul de pe platform_A zicand ca prev->next = last. iar dupa asta execut si cazul in care pos_b != 1. And that's all :)

Pentru Cerinta2 a trebuit sa implementez diferite functii precum:
-find_express_train: In acesta functie am folosit un simplu algoritm de cautare a unui maxim, respect cerinta
ca diferenta dintre puterea locomotivei si greutatea vagoanelor sa fie cat mai mare. Folosindu-ma de variabila
iamspeedd :) am retinut maximul si in variabila peron am retinut indicele peronului ce urmeaza
sa fie returnat ca rezultat;
-find_overload_train: Aceasta functie este rezolvata asemanator cu cea descrisa mai sus schimband doar conditia legata
de maximul pe care il cautam. In acest caz cautam trenul cu incarcatura cea mai mare in functie de puterea locomotivei sale
si il returnam
-find_optimal_train: Aceasta functie se rezolva similar cu cele descrisa mai sus. Insa aici cautam cea mai mica valoare
care respecta conditia ca diferenta dintre puterea locomotivei si greutatea vagoanelor sa fie minima si returnam
peronul pe care se afla.
-find_heaviest_sequence_train. In cadrul acestei functii am realizat verificarile basic.
si am realizat ca intr-un peron exista l (nr de vagoane) -cars_no +1 secventee. Am construit suma fiecarei secvente
si am aflat maxima din toate peroanele. In variabila peron am retinut indicele peronului
cu cea mai "grea" secventa si in *star_car am retinut primul vagon care incepe secventa respectiva.

Pentru Cerinta3 a trebuit sa implementez diferite functii precum:
-order_train M-am gandit ca o rezolvare la aceasta problema ar fi sa interschimb valorile in loc
sa schimb pointerii. Si am implementat un simplu buble sort bazat pe doua for-uri si o variabila aux
care ma ajuta la interschimbare. Dupa ce am realizat ca sa sortez valorile nu este o solutie valida
am decis sa sortez lista utilizandu-ma de principiul insertSort-ului care functioneaza pe urmatorulul principiu. Voi pleca
de la al 2 lea vagon, si mereu voi retine predecesorul acestuia. Principiul de inesrtion sort imi spune ca ce se afla in stanga
valorii curente este o lista sortata deja descrescator. Asa ca daca gasesc un caz in care elementul curent (head) are o greutate
mai mare decat predecesorul acestuia , inseamna ca trebuie sa-l inserez undeva in partea stanga a listei, astfel incat 
valorile sa fie ordonate. Asa ca verific cazul particular in care vagonul curent devine primul vagon de pe peron si interschimb adresele
, altfel verific dupa care element trebuie sa fie inserat head-ul curent. La final am grija ca head-ul sa-si recapete pozitia buna ca sa nu se parcurga lista
degeaba.
-fix_overload_train: Pentru aceasta functie am cautat vagonul cu cea mai mica greutate astfel incat 
acesta sa devina optim.I am tinut minte predecesorul si la final cand l am eliberat , am avut grija sa repar 
legatura dintre vagoane.

And that's all 🐧🐧