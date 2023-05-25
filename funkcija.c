#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Header.h"

void izbornik(void) { //10. //7.
	int izbor = 0; //1.
	do {
		printf("Dobro dosli na kviz:\n\n1. Pokreni kviz\n2. Rezultat\n3. Upute za igranje\n4. Izlaz\n\n");
		scanf("%d", &izbor);

		switch (izbor) {
		case 1:
			unos();
			break;
		case 2:
			tablica_rez();
			break;
		case 3:
			informacije();
			break;
		case 4:
			izlaz();
			break;
		case 5:
			return;
		default:
			system("cls");
			while ((getchar()) != '\n');
			printf("Opcija nije dozvoljena, unesite ponovo\n");
		}
	} while (1);
}



void unos(void) { //10.
	int i, score = 0;
	int broj = 0;

	char linija[256]; //11.
	FILE* fp;
	char opcija[200], opcija1[200], opcija2[200], opcija3[200], opcija4[200], tocno[200] ;

	fp = fopen("Pitanja.txt", "r"); //16. tekstualna datoteka
	if (fp == NULL) { //16.
		printf("Nije moguce otvoriti tekstualnu datoteku Pitanja.txt");
		exit(1);
	}

	for (i = 0; i < 15; i++) { // Ucitavanje 15 pitanja iz datoteke
		fgets(linija, sizeof(linija), fp); // Ucitavanje pitanja
		printf("\nPitanje %d %s", i + 1, linija);

		fgets(linija, sizeof(linija), fp); // Ucitavanje opcije A
		strncpy(opcija1, linija, 50);
		printf("%s", linija);

		fgets(linija, sizeof(linija), fp); // Ucitavanje opcije B
		strncpy(opcija2, linija, 50);
		printf("%s", linija);

		fgets(linija, sizeof(linija), fp); // Ucitavanje opcije C
		strncpy(opcija3, linija, 50);
		printf("%s", linija);

		fgets(linija, sizeof(linija), fp); // Ucitavanje opcije D
		strncpy(opcija4, linija, 50);
		printf("%s", linija);

		//fgets(linija, sizeof(linija), fp); // Ucitavanje tocnog odgovora
		//strncpy(tocno, linija, 50);
		//printf("\n%s (ovo je tocan odgovor)\n", tocno);

		char odgovor[200]; //2.
		printf("Unesite odgovor (A/B/C/D): ");
		scanf("%s", odgovor);
		//getchar(); 
		//int getchar(void);


		if (strcmp(odgovor, tocno) == 0) { // Usporedba odgovora s tocnim odgovorom
			printf("Tocan odgovor!\n");
			score += 10; // Dodavanje bodova za točan odgovor
		}
		else {
			printf("Netocan odgovor!\n");
		}
		printf("Trenutni broj bodova: %d\n", score);
	}

	broj = score;
	printf("\nUkupno osvojeno %d bodova.\n", score);

	fclose(fp);

	ponoviIgru(broj); // Funkcija koja ispisuje broj osvojenih bodova i pita za ponovno igranje
}


void izlaz(void) // funkcija za izlaz iz programa
{
	char da[] = "da"; //2.
	char ne[] = "ne";
	char choose[3] = { 0 };
	printf("Jeste li sigurni da zelite izaci iz kviza?\nDa\nNe\n");
	scanf("%s", &choose);
	if (_strcmpi(da, choose) == 0) //strcmpi - usporedba dva stringa                          
	{
		exit(1);
	}
	if (_strcmpi(ne, choose) == 0)
	{
		system("cls");
		izbornik();
	}
	else
	{
		system("cls");
		printf("\n('da'/'ne')\n");
		izlaz();
	}
}


void ponoviIgru(int broj) { //funkcija koja nam opciju da ponovno pokrenemo kviz

	char da[] = "da";
	char ne[] = "ne";
	char choose[3] = { 0 };
	printf("\nRezultat: %d kn\n", broj);
	printf("Pokusaj ponovno?\nDa\nNe\n\n");
	scanf("%s", &choose);
	if (_strcmpi(da, choose) == 0)
	{
		unos();
	}
	if (_strcmpi(ne, choose) == 0)
	{
		upis_score(broj); //poziva funkciju za upis imena i bodova 
	}
	else
	{
		system("cls");
		printf("\n('da'/'ne')\n\n");
		ponoviIgru(broj);
	}
}


void upis_score(int broj) { //upisuje rezultat u tablicu

	int n = 0, m = 0; //1.
	FILE* ft = NULL;
	ft = fopen("tablica.bin", "rb"); //16. read bin
	if (ft == NULL)
	{
		fflush(ft); //16.
		ft = fopen("tablica.bin", "wb");//Ako ne postoji tablica.bin program ju napravi, // write bin

		fwrite(&n, sizeof(int), 1, ft);
	}
	fclose(ft); //16.
	IGRAC* igrac = NULL; //9.
	igrac = (IGRAC*)calloc(1, sizeof(IGRAC));
	if (igrac == NULL) {
		exit(1);
	}
	FILE* fp = NULL;
	fp = fopen("tablica.bin", "rb+");
	if (fp == NULL)
	{
		exit(1);
	}
	else
	{
		fread(&m, sizeof(int), 1, fp); //17.
		m++;
		fseek(fp, 0, SEEK_SET); //17.
		fwrite(&m, sizeof(int), 1, fp); //17.
		fseek(fp, 0, SEEK_END);
		printf("Osvojen iznos: %d\n", broj);
		printf("Ime igraca: ");
		scanf(" %[^\n]%*c", igrac->ime);
		igrac->br = broj;
		fwrite(igrac, sizeof(IGRAC), 1, fp);
		system("cls");
	}
	fclose(fp);
}



void tablica_rez(void) { //tablica rezultata koja sortira i pretrazuje //8
	int m = 0, n = 0;
	system("cls");
	FILE* fp = NULL;
	fp = fopen("tablica.bin", "rb+"); //16. bin
	if (fp == NULL)
	{
		printf("Nema prijasnjih rezultata"); //vraca nas na izbornik ukoliko nema odigranih kvizova
		exit(1);
	}
	else
	{

		fread(&m, sizeof(int), 1, fp); //ucitava podatke iz filea u polje koje je dano preko pokazivaca
		IGRAC* igrac = NULL;
		igrac = (IGRAC*)calloc(m, sizeof(IGRAC)); //14. alociramo memoriju
		if (igrac == NULL) { //14.
			printf("Error");
			exit(1);
		}
		fread(igrac, sizeof(IGRAC), m, fp);//u polje igrac ucitavamo podatke iz datoteke

		do {

			while ((getchar()) != '\n');
			broj_igraca(); // funkcija koja prati broj igraca
			printf("Tablica rezultata:\n(1)Pretraga igraca\n(2)Pretraga igraca po imenu\n(3)Pretraga igraca po bodovima\n(4)Povratak na izbornik\n\n");
			scanf("%d", &n);
			switch (n) {

			case 1:
				system("cls"); //brisanje sadržaja konzole
				pretrazivanje_igraca();
				break;
			case 2:
				system("cls");
				sortiranje_imena(igrac, m); // funkcija za sortiranje po imenu
				ispis_imena(igrac, m);
				povratak();
				break;
			case 3:
				system("cls");
				sortiranje_rezultata(igrac, m);// funkcija za sortiranje po osvojenom iznosu
				ispis_rezultata(igrac, m);
				povratak();
				break;
			case 4:
				system("cls");
				izbornik(); //vraca nas na izbornik
			default:
				system("cls");
				printf("Unesite jednu od danih opcija\n\n");
			}
		} while (1);
	}
}


void sortiranje_rezultata(IGRAC* igrac, const int n) { // funkcija za sortiranje rezultata //20
	if (igrac == NULL) {
		printf("Error");
		exit(1);
	}
	int min = 0;
	for (int i = 0; i < n - 1; i++)
	{
		min = i;
		for (int j = i + 1; j < n; j++)
		{
			if ((igrac + j)->br > (igrac + min)->br)
			{
				min = j;
			}
		}
		sort((igrac + i), (igrac + min));
	}
}


void sortiranje_imena(IGRAC* igrac, const int n) //funkcija za sortiranje imenav //20
{
	if (igrac == NULL) {
		printf("Error");
		exit(1);
	}
	int min = 0;
	for (int i = 0; i < n - 1; i++)
	{
		min = i;
		for (int j = i + 1; j < n; j++)
		{
			if (strcmp((igrac + j)->ime, (igrac + min)->ime) < 0)
			{
				min = j;
			}
		}
		sort((igrac + i), (igrac + min));
	}
}


void sort(IGRAC* veci, IGRAC* manji) // sortiranje (selection sort) //9. //20
{
	IGRAC temp;
	if (veci == NULL || manji == NULL) {
		printf("Error");
		exit(1);
	}
	temp = *manji;
	*manji = *veci;
	*veci = temp;
}


void ispis_imena(IGRAC* igrac, const int n) { //ispis po imenu //4.
	int i;
	if (igrac == NULL) {
		printf("Error");
		exit(1);
	}

	for (i = 0; i < n; i++)
	{
		printf("\n%d. Ime: %s\nBodovi: %d\n", (i + 1), (igrac + i)->ime, (igrac + i)->br);
	}
}


void ispis_rezultata(IGRAC* igrac, const int n) {  //ispis rezultata po osvojenom iznosu
	int i;
	if (igrac == NULL) {
		printf("Error");
		exit(1);
	}

	for (i = 0; i < n; i++)
	{
		printf("\n%d. Ime: %s\nOsvojen iznos: %d kn\n", (i + 1), (igrac + i)->ime, (igrac + i)->br);
	}
}


void povratak(void) // povratak na izbornik
{
	while ((getchar()) != '\n');
	char s;
	printf("\nPritisnite enter za povratak na izbornik ");
	s = fgetc(stdin);
	if (s == '\n')
	{
		system("cls");
		izbornik();
	}
	else
	{
		system("cls");
		printf("\nPogresan unos, pokusajte ponovno\n\n");
		povratak();
	}
}


void broj_igraca(void)
{
	int BrojKvizova; //4.
	FILE* fp;
	fp = fopen("tablica.bin", "rb+");
	rewind(fp);// 17. postavlja file poziciju na pocetak 
	if (fp == NULL)
	{
		printf("Error");
		exit(1);
	}
	else
	{
		fseek(fp, 0, SEEK_END);// kraj filea
		BrojKvizova = ftell(fp) / sizeof(IGRAC);//cita broj zapisanih igraca a ftell vraca trenutnu poziciju u fileu
		printf("Broj odigranih kvizova: %d\n\n", BrojKvizova);
	}
	fclose(fp);
}


void pretrazivanje_igraca(void) //funkcija koja pretrazuje igraca
{
	int brojac = 0;
	FILE* fp = NULL;
	fp = fopen("tablica.bin", "rb+");
	if (fp == NULL)
	{
		printf("Error");
		exit(1);
	}
	fseek(fp, 0, SEEK_END); // kraj filea
	fseek(fp, sizeof(int), SEEK_SET); //postavlja se na pocetak filea 
	char polje[20] = { 0 };
	printf("Unesite ime: ");
	scanf(" %[^\n]%*c", polje);

	while (fread(&igrac, sizeof(igrac), 1, fp) == 1)
	{
		if (_strcmpi(igrac.ime, (polje)) == 0) //_strcmpi usporeduje uneseno ime s imenima u strukturi(nije case sensitive nalazi se u string.h) //18.
		{
			printf("\nIme: %s\nBroj bodova: %d\n", igrac.ime, igrac.br);
			brojac++;
		}
	}
	if (brojac == 0) //ukoliko je brojac 0 onda nema trazenog imena                                                                    
	{
		printf("Ime nije pronadeno");
	}
	ponovno_pretrazivanje(); //ponovno trazenj
	fclose(fp);
}


void ponovno_pretrazivanje(void)
{
	char da[] = "da";
	char ne[] = "ne";
	char choose[3] = { 0 };
	printf("\n\nZelite li ponovo pretraziti igraca?\nDa\nNe\n");
	scanf("%s", &choose);
	if (_strcmpi(da, choose) == 0) //strcmpi usporedjuje stringove
	{
		system("cls");
		pretrazivanje_igraca(); // ako je da pozivamo funkciju za pretrazivanje igraca
	}
	if (_strcmpi(ne, choose) == 0)
	{
		system("cls");
		izbornik();   // ako je ne vracamo se na izbornik
	}
	else
	{
		system("cls");
		printf("('da'/'ne')\n\n");
		ponovno_pretrazivanje();   // 1. rekurzija
	}
}
void informacije(void)
{
	system("cls");
	printf("Kviz se sastoji od 15 pitanja, sa 3 ponudena odgovora di je samo jedan tocan odgovor.");
	printf("\nKako bi ste unijeli odgovor upisite jedno od opcija A B C D.");
	printf("\nSvoje rezultate i rezultate drugih igraca mozete vidjeti sortirane.");
	printf("\nSretno!:)");
	povratak();//vracam se na izbornik
}
