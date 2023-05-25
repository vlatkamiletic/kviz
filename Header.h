#ifndef HEADER_H
#define HEADER_H
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
typedef struct igrac
{
	char ime[20];
	int br;
}IGRAC;
IGRAC igrac;
void izbornik(void);
void unos(void);
void izlaz(void);
void ponoviIgru(int);
void upis_score(int);
void tablica_rez(void);
void sort(IGRAC*, IGRAC*);
void sortiranje_imena(IGRAC*, const int);
void sortiranje_rezultata(IGRAC*, const int);
void ispis_imena(IGRAC*, const int);
void ispis_rezultata(IGRAC*, const int);
void povratak(void);
void broj_igraca(void);
void pretrazivanje_igraca(void);
void ponovno_pretrazivanje(void);
void informacije(void);

#endif //Header.h
