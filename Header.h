//6.
#ifndef HEADER_H
#define HEADER_H
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

typedef struct {
	char pitanje[256]; //13.
	char opcijaA[256];
	char opcijaB[256];
	char opcijaC[256];
	char opcijaD[256];
	char tocanOdgovor;
} Pitanje;

typedef struct igrac //3. 10.
{
	char ime[20];//13.
	int br;
}IGRAC;
IGRAC igrac;
void izbornik(void); //8.
void unos(void);
void izlaz(void);
void ponoviIgru(int);
void upis_score(int);
void brisanje_datoteke();
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
