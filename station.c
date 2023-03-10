#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "station.h"

/* Creeaza o gara cu un numar fix de peroane.
 *
 * platforms_no: numarul de peroane ale garii
 *
 * return: gara creata
 */
TrainStation *open_train_station(int platforms_no)
{
    /*Aceasta functie aloca memorie pentru un train_station chiar nush 
    ce as putea sa zic aici. Am atribuit pointerelor zonele de memorie de respectivul lor size pe heap
    Am atribuit memorie pentru vectorul de pointeri, iar apoi am atribuit memorie pentru fiecare peron in parte
    si am marcat fiecare peron fara locomitva pe el cu locomotive_power = -1*/
    TrainStation *station = malloc(sizeof(TrainStation));
    station->platforms_no = platforms_no;
    station->platforms = malloc(platforms_no * sizeof(Train *));
    for (int i = 0; i < station->platforms_no; i++)
    {
        station->platforms[i] = malloc(sizeof(Train));
        station->platforms[i]->train_cars = NULL;
        station->platforms[i]->locomotive_power = -1;
    }

    return station;
}

void close_train_station(TrainStation *station)
{
    /*Am dezalocat toate memoria dintr-un trainstation parcurgand fiecare 
    vagon dandu-i free , apoi acest proces se repeta pentru fiecare peron , apoi pentru vectorul de ponteri si la final se elivereaza
    variabila station*/
    if (station == NULL)
        return;
    if (station->platforms == NULL)
        free(station);
    for (int i = 0; i < station->platforms_no; i++)
    {
        TrainCar *prev = NULL, *head = station->platforms[i]->train_cars;
        while (head != NULL)
        {
            prev = head;
            head = head->next;
            free(prev);
        }
        free(station->platforms[i]);
    }
    free(station->platforms);
    free(station);
}

/* Afiseaza trenurile stationate in gara.
 *
 * station: gara existenta
 * f: fisierul in care se face afisarea
 */
void show_existing_trains(TrainStation *station, FILE *f)
{
    /*Aceasta functie printeaza indicii fiecarui peron , si daca este cazul puterea locomotivei daca aceasta  exista si vagoanele
     de pe acel peron Intr-un fisier primit ca si parametru*/
    if (station == NULL)
        return;
    for (int i = 0; i < station->platforms_no; i++)
    {
        fprintf(f, "%d: ", i);
        if (station->platforms[i]->locomotive_power != -1)
        {
            fprintf(f, "(%d)", station->platforms[i]->locomotive_power);
            TrainCar *head = NULL;
            head = station->platforms[i]->train_cars;
            while (head != NULL)
            {
                fprintf(f, "-|%d|", head->weight);
                head = head->next;
            }
        }
        fprintf(f, "\n");
    }
}

/* Adauga o locomotiva pe un peron.
 *
 * station: gara existenta
 * platform: peronul pe care se adauga locomotiva
 * locomotive_power: puterea de tractiune a locomotivei
 */
void arrive_train(TrainStation *station, int platform, int locomotive_power)
{
    /*Aceasta functie pune o locomotiva pe un peron mai precis ii  modifica puterea locomotivei (daca aceasta este = -1 asigurandu se ca nu introduc
    2 locomotive pe un peron )*/
    if (platform < 0 || platform >= station->platforms_no)
        return;
    if (locomotive_power < 0)
        return;
    if (station->platforms[platform]->locomotive_power != -1)
        return;
    station->platforms[platform]->locomotive_power = locomotive_power;
}

/* Elibereaza un peron.
 *
 * station: gara existenta
 * platform: peronul de pe care pleaca trenul
 */
void leave_train(TrainStation *station, int platform)
{
    /*Aceasta functie elibereaza vagoanele de pe un peron , modul in care acestea sunt eliminitate
    este  modul de stergere a unei liste simplu inlantuite*/
    if (platform < 0 || platform >= station->platforms_no)
        return;
    if (station->platforms[platform]->locomotive_power == -1)
        return;
    station->platforms[platform]->locomotive_power = -1;
    TrainCar *prev, *head;
    head = station->platforms[platform]->train_cars;
    while (head != NULL)
    {
        prev = head;
        head = head->next;
        free(prev);
    }
    station->platforms[platform]->train_cars = NULL;
}

/* Adauga un vagon la capatul unui tren.
 *
 * station: gara existenta
 * platform: peronul pe care se afla trenul
 * weight: greutatea vagonului adaugat
 */
void add_train_car(TrainStation *station, int platform, int weight)
{
    /*Aceasta functie insereaza un vagon intr-un peron verificand daca acesta este primul vagon sau nu ( in functie de aceasta
    verificare */
    if (platform < 0 || platform >= station->platforms_no)
        return;
    if (weight < 0)
        return;
    TrainCar *insert = malloc(sizeof(TrainCar));
    insert->weight = weight;
    insert->next = NULL;
    if (station->platforms[platform]->train_cars == NULL)
    {
        station->platforms[platform]->train_cars = insert;
    }
    else
    {
        TrainCar *head;
        head = station->platforms[platform]->train_cars;
        while (head->next != NULL)
        {
            head = head->next;
        }
        head->next = insert;
    }
}

/* Scoate vagoanele de o anumita greutate dintr-un tren.
 *
 * station: gara existenta
 * platform: peronul pe care se afla trenul
 * weight: greutatea vagonului scos
 */


void remove_train_cars(TrainStation *station, int platform, int weight)
{
    /*In aceasta functie am sters toate vagoanele cu o anumite greutate dupa o paltforma
    si initial verific cazul in care am o scucesiuni de vagoane ce trebueisc sterse de la inceputul peronului dupa care
    sterg elementele fix dupa modelul de stergere a nodurilor dintr-o lista simplu inlantuita*/
    if (platform < 0 || platform >= station->platforms_no)
        return;
    if (weight < 0)
        return;
    if (station->platforms[platform]->locomotive_power != 1 && weight >= 0)
    {
        TrainCar *head, *prev = NULL;
    head = station->platforms[platform]->train_cars;
    if (head == NULL)
    {
        return;
    }
    while(head != NULL && head->weight == weight){
        prev = head;
        head = head->next;
        free(prev);
    }
    station->platforms[platform]->train_cars = head;
    while (head != NULL)
    {

        if (head->weight == weight)
        {
            prev->next = head->next;
            free(head);
            head = prev->next;
        }
        else
        {
            prev = head;
            head = head->next;
        }
    }
    }
    return;
}

/* Muta o secventa de vagoane dintr-un tren in altul.
 *
 * station: gara existenta
 * platform_a: peronul pe care se afla trenul de unde se scot vagoanele
 * pos_a: pozitia primului vagon din secventa
 * cars_no: lungimea secventei
 * platform_b: peronul pe care se afla trenul unde se adauga vagoanele
 * pos_b: pozitia unde se adauga secventa de vagoane
 */
int lenght(TrainCar *head)
{
    // functie pentru a determina lungimea unei secvente de vagoane
    int nr = 0;
    while (head != NULL)
    {
        nr++;
        head = head->next;
    }
    return nr;
}

void move_train_cars(TrainStation *station, int platform_a, int pos_a, int cars_no, int platform_b, int pos_b)
{
    /* Aceasta functie verifica initial cazurile pentru care programul nu face nimic , precum daca avem suficiente vagoane 
    , daac parametrii din functie au valori valide . In cadrul acestei functii care mi-a luat destul de mult , m am gandit sa lucrezi cu  schimbatul adreselor
    pointerilor pentru a muta vagoane. Asa ca m am gadnit sa mi iau 4 pointeri. La inceput am decis sa avansez cu 2 pointeri fiecare asignati unui tren pana ajung la urmtatorul element sa 
    fie primul din secventa ce urmeaza sa o sterg (Sorry daca sunt greseli de scriere pe aici imi e destul de somn in timp ce scriu asta) Dupa asta ma folosesc si de inca 2 pointeri pentru a stii mereu
    vadresa de inaintea primului element din secventa ce va fi afectata , respectiv urmtorul dupa terminarea secventei. Cu ultimii 2 ma folosesc pentru a reface conexiunile ce trebuiesc facut dupa ce 
    vagoanele au fost mutate. Evaluez si fiecare caz cand trebuie sa mut vagoane de exemplu daca mut vagoane de pe prima pozite a unui tren si daca le inserez in prima pozitie din celalalt tren si asa mai departe
    la inceputul functii verific si daca am destule vagoane sa pot sa fac operatii si daca parametrii primiti is valizi. */
    if (station == NULL)
        return;
    if (pos_a < 1)
        return;
    if (pos_b < 1)
        return;
    if (platform_a < 0 || platform_a >= station->platforms_no)
        return;
    if (platform_b < 0 || platform_b >= station->platforms_no)
        return;

    TrainCar *prev = NULL, *last = NULL, *head1 = station->platforms[platform_a]->train_cars;
    TrainCar *head2 = station->platforms[platform_b]->train_cars;

    if (head1 == NULL)
        return;
    if (head2 == NULL && pos_b != 1)
        return;
    int nra = 1, nrb = 1, l1, l2;
    l1 = lenght(head1);
    l2 = lenght(head2);
    if (pos_a > l1)
        return;
    if (pos_b > l2 + 1)
        return;
    if (pos_a + cars_no > l1 + 1)
        return;
    
    while (nra < pos_a - 1)
    {
        nra++;
        head1 = head1->next;
    }
    while (nrb < pos_b - 1)
    {
        nrb++;
        head2 = head2->next;
    }
    //head 1 si head2 sunt 2 pointeri asocitait unui tren anume si fiecare se deplaseaza pana la vagonul de inaintea modificarilor
    if (pos_a == 1)
    {
        prev = head1;
        while (1 < cars_no)
        {
            head1 = head1->next;
            cars_no--;
        }
        last = head1->next;
        // aici evaluam cazul in care luam vagoane de la inceputul trenului A si verificam daca tre sa introducem la interiorul trenului B
        // sau oriunde alt undeva
        // Parcurg  cu toate vagoanele din secventa a care trebuiesc mutate si pastrez in last urmatoare valoarea pentru a reface conexiunile trneului a dupa modificari
        if (pos_b == 1)
        {
            station->platforms[platform_b]->train_cars = station->platforms[platform_a]->train_cars;
            station->platforms[platform_a]->train_cars = last;
            head1->next = head2;
            return;
        }

        head1->next = head2->next;
        head2->next = station->platforms[platform_a]->train_cars;
        station->platforms[platform_a]->train_cars = last;
        // avem grija sa reparam legaturile din trenul A dupa terminea mutarii vagoanelor
        return;
    }
    //Spre deosebire de cazul n care luam trenuri de la inceputul vagonului A , aici avem nevoie si de un pointer prev , care are 
    //ca si adresa nod-ul de inaintea secventei ce trebuie mutata. Acest prev o sa ne ajute sa reparam trenul a;
    prev = head1;
    
        while (cars_no > 0)
        {
            head1 = head1->next;
            cars_no--;
        }
        last = head1->next;
        //Asemanator ca mai sus luam si cazul in care inseram vagoane la inceputul trenului b si la final avem grijs sa reparam trenurile
        if (pos_b == 1)
        {
            head1->next = head2;
            station->platforms[platform_b]->train_cars = prev->next;
            prev->next = last;
            return;
        }
        head1->next = head2->next;
        head2->next = prev->next;
        prev->next = last;
    
    return;
}

/* Gaseste trenul cel mai rapid.
 *
 * station: gara existenta
 *
 * return: peronul pe care se afla trenul
 */
int find_express_train(TrainStation *station)
{
    /*Aceasta functie este bazata pe ideea gasirii unui maxim dupa o anumita conditie
    in acest caz maximul se determina in func de cea mai mare diferinta dintre puterea
    locomotives si suma greutatilor vagoanelor > 0. Functia pastreaza in variabila iamspeed
    valoarea cea mai mare si in peron indicele peronului care o sa fie returnat*/
    int iamspeed = -1, peron = -1, weight = 0, vit = 0;
    TrainCar *head = NULL;
    for (int i = 0; i < station->platforms_no; i++)
    {
        weight = 0;
        vit = 0;
        if (station->platforms[i]->locomotive_power != -1)
        {
            head = station->platforms[i]->train_cars;
            while (head)
            {
                weight += head->weight;
                head = head->next;
            }
            vit = station->platforms[i]->locomotive_power - weight;
            if (iamspeed == -1)
            {
                iamspeed = vit;
                peron = i;
            }
            else if (vit > iamspeed)
            {
                iamspeed = vit;
                peron = i;
            }
        }
    }
    return peron;
}

/* Gaseste trenul supraincarcat.
 *
 * station: gara existenta
 *
 * return: peronul pe care se afla trenul
 */
int find_overload_train(TrainStation *station)
{
  /*Functia returneaza primul indice pe care se afla o secventa
    a carei diferente dintre puterea locomotives si greutatea vagoanelor este ngativa*/
    if (station == NULL)
        return;
    TrainCar *head;
    int over, weight;
    for (int i = 0; i < station->platforms_no; i++)
    {
        weight = 0;
        if (station->platforms[i]->locomotive_power != -1)
        {
            head = station->platforms[i]->train_cars;
            while (head)
            {
                weight += head->weight;
                head = head->next;
            }
            if (station->platforms[i]->locomotive_power - weight < 0)
                return i;
        }
    }
    return -1;
}

/* Gaseste trenul cu incarcatura optima.
 *
 * station: gara existenta
 *
 * return: peronul pe care se afla trenul
 */
int find_optimal_train(TrainStation *station)
{
    /*Aceasta functie este bazata pe ideea gasirii unui maxim dupa o anumita conditie
    in acest caz maximul se determina in func de cea mai mica valoare care respescta conditia 
    ca diferenta dintre puterea locomotivei si greutatea vagoanelor sa fie > 0 Functia returneaza indicele 
    platformei pe care se afla acest tren*/
    if (station == NULL)
        return;
    int optim = -1, peron = -1, weight = 0, vit = 0;
    TrainCar *head = NULL;
    for (int i = 0; i < station->platforms_no; i++)
    {
        weight = 0;
        vit = 0;
        if (station->platforms[i]->locomotive_power != -1)
        {
            head = station->platforms[i]->train_cars;
            while (head)
            {
                weight += head->weight;
                head = head->next;
            }
            vit = station->platforms[i]->locomotive_power - weight;
            if (optim == -1)
            {
                optim = vit;
                peron = i;
            }
            else if (vit < optim)
            {
                optim = vit;
                peron = i;
            }
        }
    }
    return peron;
    return -1;
}

/* Gaseste trenul cu incarcatura nedistribuita bine.
 *
 * station: gara existenta
 * cars_no: lungimea secventei de vagoane
 *
 * return: peronul pe care se afla trenul
 */
int find_heaviest_sequence_train(TrainStation *station, int cars_no, TrainCar **start_car)
{
    /*Aceasta functie verifica daca parametrii au valori valide , si returneaza indicele platformei pe care se afla 
    heaviest_sequence si pastrea in *star_car primul nod de unde incepe aceasta secventa. Am aflat ca in orice  tren cu n vagoane , se pot construi
    l(lnr de vagoane dintr-un tren)-cars_no +1. Am construit fiecare secventa posibila pe fiecare peron si am folosit o variabila sa tin minte valoarea maxima precum
    si una peron pentru a pastra indicile care la final este returnat*/
    if (station == NULL)
        return;
    if (cars_no < 0)
        return;
    int maxim = -1, peron = -1;
    int l = 0, nr = 0;
    TrainCar *head = NULL;
    for (int i = 0; i < station->platforms_no; i++)
    {
        if (station->platforms[i]->locomotive_power != -1)
        {
            head = station->platforms[i]->train_cars;
            l = 0;
            while (head != NULL)
            {
                l++;
                head = head->next;
            }
            if (l >= cars_no)
            {
                head = station->platforms[i]->train_cars;
                nr = l - cars_no + 1;
                int k, greutate = 0;
                for (int j = 0; j < nr; j++)
                {
                    greutate = 0;
                    TrainCar *future = head;
                    for (int k = 0; k < cars_no; k++)
                    {
                        greutate += future->weight;
                        future = future->next;
                    }
                    if (maxim == -1 && greutate != 0)
                    {
                        maxim = greutate;
                        peron = i;
                        *start_car = head;
                    }
                    else if (greutate > maxim)
                    {
                        maxim = greutate;
                        peron = i;
                        *start_car = head;
                    }
                    head = head->next;
                }
            }
        }
    }
    if (peron == -1)
    {
        *start_car = NULL;
        return -1;
    }

    return peron;
}

/* Ordoneaza vagoanele dintr-un tren in ordinea descrescatoare a greutatilor.
 *
 * station: gara existenta
 * platform: peronul pe care se afla trenul
 */

void order_train(TrainStation *station, int platform)
{
    /*Aceasta functie  initial verifica conditiile ca parametrii sa fie valizi si functioneaza asemanator pe InsertSort . Functioneaza pe urmatorulul principiu. Voi pleca
de la al 2 lea vagon, si mereu voi retine predecesorul acestuia. Principiul de inesrtion sort imi spune ca ce se afla in stanga
valorii curente este o lista sortata deja descrescator. Asa ca daca gasesc un caz in care elementul curent (head) are o greutate
mai mare decat predecesorul acestuia , inseamna ca trebuie sa-l inserez undeva in partea stanga a listei, astfel incat 
valorile sa fie ordonate. Asa ca verific cazul particular in care vagonul curent devine primul vagon de pe peron si interschimb adresele
, altfel verific dupa care element trebuie sa fie inserat head-ul curent. La final am grija ca head-ul sa-si recapete pozitia buna ca sa nu se parcurga lista
degeaba. */
    if (station == NULL)
        return;
    if (platform < 0 || platform >= station->platforms_no)
        return;
    if (station->platforms[platform]->locomotive_power == -1)
        return;
    TrainCar *head = station->platforms[platform]->train_cars;
    TrainCar *prev = NULL, *head2 = NULL ;
    if (head == NULL || head->next == NULL)
        return;
    int ok = 1;
    prev = head;
    head = head->next;
    while (head != NULL && prev->next != NULL)
    {
        ok = 0;
        if (head->weight > prev->weight)
        {
            ok = 1;
        }
        if (ok == 1)
        {
            if (station->platforms[platform]->train_cars->weight < head->weight)
            {
                prev->next = head->next;
                head->next = station->platforms[platform]->train_cars;
                station->platforms[platform]->train_cars = head;
                head = prev->next;
            }
            else
            {
                prev->next = head->next;
                head2 = station->platforms[platform]->train_cars;
                while(head2->next!= NULL && head2->next->weight > head->weight && head2 != NULL){
                    head2 = head2->next;
                }
                head->next = head2->next;
                head2->next = head;
                head = prev->next;
            }
        }
        else
        {
            prev = head;
            head = head->next;
        }
    }
    return;
}

/* Scoate un vagon din trenul supraincarcat.
 *
 * station: gara existenta
 */
void fix_overload_train(TrainStation *station)
{
    /*Aceasta functie  elibereaza un tren overloaded , cautat cea mai mica valoarea posibila, care prin eliminarea ei trenul
    rezutat ar fi unul optim. Am cautat vagonul respectiv pe cazul in care trenul este overloaded si am eliminat vagonul care era necesar
    folosind eliminarea unui nod dintr-o lista simplu inlantuita*/
    if (station == NULL)
        return;
    int j;
    j = find_overload_train(station);
    if (j == -1)
        return;
    TrainCar *head = station->platforms[j]->train_cars;
    TrainCar *cautat = NULL;
    int weight = 0;
    while (head != NULL)
    {
        weight += head->weight;
        head = head->next;
    }
    head = station->platforms[j]->train_cars;
    while (head != NULL)
    {
        if (station->platforms[j]->locomotive_power - (weight - head->weight) >= 0)
        {
            if (cautat == NULL)
            {
                cautat = head;
            }
            else if (head->weight < cautat->weight)
                cautat = head;
        }
        head = head->next;
    }
    head = station->platforms[j]->train_cars;
    if (head == cautat)
    {
        station->platforms[j]->train_cars = head->next;
        head = head->next;
        free(cautat);
        return;
    }
    while (head->next != cautat)
    {
        head = head->next;
    }
    head->next = cautat->next;
    free(cautat);
    return;
}
