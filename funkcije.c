#define _CRT_SECURE_NO_WARNINGS
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include "Header.h"

void izbornik(void) { //10.
	int izbor = 0; //1.
	printf("\t\tDobro dosli na kviz: ");

	do {
		printf("\n\n1. Pokreni kviz\n2. Rezultat\n3. Upute za igranje\n4. Resetiranje tablice\n5. Izlaz\n\n");
		scanf("%d", &izbor);

		switch (izbor) {
		case 1:
			system("cls");
			unos();
			break;
		case 2:
			system("cls");
			tablica_rez();
			break;
		case 3:
			system("cls");
			informacije();
			break;
		case 4:
			system("cls");
			brisanje_datoteke();
			break;
		case 5:
			system("cls");
			izlaz();
		default: //11.
			system("cls");
			while ((getchar()) != '\n');
			printf("Opcija nije dozvoljena, unesite ponovo\n");
		}
	} while (1);
}




void unos() {
	int bodovi = 0;
	Pitanje pitanja[15];//12.

	FILE* file = fopen("Pitanja.txt", "r");
	if (file == NULL) {
		perror("Greska pri otvaranju datoteke!");//19.
		return;
	}

	for (int i = 0; i < 15; i++) {
		fscanf(file, "%[^?]?%*c", pitanja[i].pitanje);
		fscanf(file, "A) %[^\n]%*c", pitanja[i].opcijaA);
		fscanf(file, "B) %[^\n]%*c", pitanja[i].opcijaB);
		fscanf(file, "C) %[^\n]%*c", pitanja[i].opcijaC);
		fscanf(file, "D) %[^\n]%*c", pitanja[i].opcijaD);
		fscanf(file, " %c%*c", &pitanja[i].tocanOdgovor);
	}

	fclose(file);

	char odgovor[256];
	for (int i = 0; i < 15; i++) {
		printf("%s\n", pitanja[i].pitanje);
		printf("A) %s\n", pitanja[i].opcijaA);
		printf("B) %s\n", pitanja[i].opcijaB);
		printf("C) %s\n", pitanja[i].opcijaC);
		printf("D) %s\n", pitanja[i].opcijaD);

		do {
			printf("Unesite odgovor (A, B, C, D): ");
			scanf(" %s%*c", odgovor);

			if (strlen(odgovor) != 1) {
				printf("Neispravan unos. Molim vas, unesite samo jedan znak odgovora (A, B, C ili D).\n");
				continue;
			}

			char uneseniOdgovor = toupper(odgovor[0]);
			if (uneseniOdgovor != 'A' && uneseniOdgovor != 'B' && uneseniOdgovor != 'C' && uneseniOdgovor != 'D') {
				printf("Neispravan unos. Molim vas, unesite jedan od znakova (A, B, C ili D).\n");
			}
			else {
				break;
			}
		} while (1);

		char uneseniOdgovor = toupper(odgovor[0]);

		if (uneseniOdgovor == pitanja[i].tocanOdgovor) {
			bodovi += 1234;
			printf("Tocan odgovor!\n");
		}
		else {
			printf("Netocan odgovor! Tocan odgovor je: %c\n", pitanja[i].tocanOdgovor);
		}
		printf("\n\Trenutni broj bodova: %d\n", bodovi);

	}

	printf("\n\nKonacni broj bodova: %d\n", bodovi);
	upis_score(bodovi);
}




void izlaz(void) // funkcija za izlaz iz programa
{
	char da[] = "da"; //2.
	char ne[] = "ne";
	char opcija[3] = { 0 };
	printf("Jeste li sigurni da zelite izaci iz kviza?\nda\nne\n");
	scanf("%s", &opcija);
	if (_strcmpi(da, opcija) == 0)                          
	{
		exit(1);
	}
	if (_strcmpi(ne, opcija) == 0)
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




void upis_score(int broj) { //upisuje rezultat u tablicu

	int n = 0, m = 0; //1.
	FILE* ft = NULL;
	ft = fopen("tablica.bin", "rb"); //16. 
	if (ft == NULL)
	{
		fflush(ft); //16.
		ft = fopen("tablica.bin", "wb");

		fwrite(&n, sizeof(int), 1, ft);
	}
	fclose(ft); //16.
	IGRAC* igrac = NULL; //9.
	igrac = (IGRAC*)calloc(1, sizeof(IGRAC));//13.
	if (igrac == NULL) {
		exit(1);
	}
	FILE* fp = NULL;
	fp = fopen("tablica.bin", "rb+");
	if (fp == NULL) {
		perror("Greska pri otvaranju datoteke!");//19.
		return;
	}
	else {
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


void brisanje_datoteke() {
	char odgovor[3] = { 0 };

	printf("Jeste li sigurni da zelite izbrisati tablicu?\n");
	printf("'da' / 'ne'\n");
	scanf("%s", odgovor);

	if (_strcmpi(odgovor, "da") == 0) {
		if (remove("tablica.bin") == 0) {//18.
			printf("Tablica je uspjesno izbrisana.\n");
		}
		else {
			printf("Pogreska pri brisanju tablice.\n");
		}
	}
	else if (_strcmpi(odgovor, "ne") == 0) {
		printf("Tablica nije izbrisana.\n");
	}
	else {
		printf("Pogresan unos! Molim vas, unesite 'da' ili 'ne'.\n");
		brisanje_datoteke();
	}
	system("cls");
}




void tablica_rez(void) { //tablica rezultata koja sortira i pretrazuje //8 podizbornik
	int m = 0, n = 0;
	system("cls");
	FILE* fp = NULL;
	fp = fopen("tablica.bin", "rb+"); //16.
	if (fp == NULL)
	{
		printf("Nema prijasnjih rezultata");
	}
	else{
		fread(&m, sizeof(int), 1, fp); 
		IGRAC* igrac = NULL;
		igrac = (IGRAC*)calloc(m, sizeof(IGRAC)); //13. 14. 
		if (igrac == NULL) { //15.
			perror("Error"); //19.
			exit(1);
		}
		fread(igrac, sizeof(IGRAC), m, fp);

		do {

			while ((getchar()) != '\n');
			broj_igraca(); 
			printf("Tablica rezultata:\n1.Rezultati\n2.Ljestvica po bodovima\n3.Pretraga igraca po imenu\n4.Povratak na izbornik\n\n");
			scanf("%d", &n);
			switch (n) {

			case 1:
				system("cls");
				sortiranje_imena(igrac, m);
				ispis_imena(igrac, m);
				povratak();
				break;
			case 2:
				system("cls");
				sortiranje_rezultata(igrac, m);
				ispis_rezultata(igrac, m);
				povratak();
				break;
			case 3:
				system("cls"); 
				pretrazivanje_igraca();
				break;
			case 4:
				system("cls");
				izbornik();
			default://11.
				system("cls");
				printf("Unesite jednu od danih opcija\n\n");
			}
		} while (1);
		free(igrac); //15
	}
}


void sortiranje_rezultata(IGRAC* igrac, const int n) {//20.
	if (igrac == NULL) {
		perror("Error");
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


void sortiranje_imena(IGRAC* igrac, const int n) {//20.
	if (igrac == NULL) {
		perror("Error");
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


void sort(IGRAC* veci, IGRAC* manji) //9. //20
{
	IGRAC temp;
	if (veci == NULL || manji == NULL) {
		perror("Error");
		exit(1);
	}
	temp = *manji;
	*manji = *veci;
	*veci = temp;
}


void ispis_imena(IGRAC* igrac, const int n) { //4.
	int i;
	if (igrac == NULL) {
		perror("Error");
		exit(1);
	}

	for (i = 0; i < n; i++)
	{
		printf("\n%d. Ime: %s\nBodovi: %d\n", (i + 1), (igrac + i)->ime, (igrac + i)->br);
	}
}


void ispis_rezultata(IGRAC* igrac, const int n) { //11.
	int i;
	if (igrac == NULL) {
		perror("Error");
		exit(1);
	}

	for (i = 0; i < n; i++)
	{
		printf("\n%d. Ime: %s\nOsvojeno bodova: %d\n", (i + 1), (igrac + i)->ime, (igrac + i)->br);
	}
}


void povratak(void)
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
	static int BrojKvizova; //4. //5.
	FILE* fp;
	fp = fopen("tablica.bin", "rb+");
	rewind(fp);// 17.
	if (fp == NULL)
	{
		perror("Error");
		exit(1);
	}
	else
	{
		fseek(fp, 0, SEEK_END);
		BrojKvizova = ftell(fp) / sizeof(IGRAC);
		printf("Broj odigranih kvizova: %d\n\n", BrojKvizova);
	}
	fclose(fp);
}


void pretrazivanje_igraca(void) { //21.
	int brojac = 0; //5.
	FILE* fp = NULL;
	fp = fopen("tablica.bin", "rb+"); //16.
	if (fp == NULL)
	{
		perror("Greska pri otvaranju datoteke!");
		exit(1);
	}
	fseek(fp, 0, SEEK_END); //17.
	fseek(fp, sizeof(int), SEEK_SET);
	char polje[20] = { 0 }; //12.
	printf("Unesite ime: ");
	scanf(" %[^\n]%*c", polje);

	while (fread(&igrac, sizeof(igrac), 1, fp) == 1)
	{
		if (_strcmpi(igrac.ime, (polje)) == 0)
		{
			printf("\nIme: %s\nBroj bodova: %d\n", igrac.ime, igrac.br);
			brojac++;
		}
	}
	if (brojac == 0)                                                                     
	{
		printf("Ime nije pronadeno");
	}
	ponovno_pretrazivanje();
	fclose(fp);
}


void ponovno_pretrazivanje(void) {
	char da[] = "da";
	char ne[] = "ne";
	char opcija[3] = { 0 };
	printf("\n\nZelite li ponovo pretraziti igraca?\nDa\nNe\n");
	scanf("%s", &opcija);
	if (_strcmpi(da, opcija) == 0)
	{
		system("cls");
		pretrazivanje_igraca();
	}
	if (_strcmpi(ne, opcija) == 0)
	{
		system("cls");
		izbornik();
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
	povratak();
}