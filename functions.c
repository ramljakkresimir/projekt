#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "header.h"

void ispisLinija(const char* imeDatLinije) {
	static int brojLinije = 0;		//5
	LINIJE* autobusi = procitajLinijeIzDatoteke(imeDatLinije, &brojLinije);		//9
	//= procitajBrojLinija(imeDatLinije);


	for (int i = 0; i < brojLinije; i++) {
		printf("\n");

		printf("Broj linije: %d\n", autobusi[i].idPutovanja);

		printf("Ime linije: %s\n", autobusi[i].ime);

		printf("Drzava linije: %s\n", autobusi[i].drzava);

		printf("Broj slobodnih mjesta linije: %d\n", autobusi[i].brojSlobodnihMjesta);

		printf("Cijena linije: %.2f $\n", autobusi[i].cijena);

		printf("Vrijeme polaska linije: %.2f\n", autobusi[i].vrijemePolaska);

		printf("\n");
	}

	free(autobusi);									//15
}

LINIJE* procitajLinijeIzDatoteke(const char* imeDatLinije, int* brojLinije) {
	FILE* linije = fopen(imeDatLinije, "r");
	if (linije == NULL) {
		perror("Pogreska pri otvaranju datoteke");
		exit(EXIT_FAILURE);
	}

	errno = 0;
	fscanf(linije, "%d", brojLinije);
	if (errno != 0) {											//19
		perror("Pogreska pri citanju broja linija iz datoteke");
		exit(EXIT_FAILURE);
	}

	int n = *brojLinije;
	LINIJE* autobusi = (LINIJE*)malloc(n * sizeof(LINIJE));		//13
	if (autobusi == NULL) {										//14
		perror("Pogreska pri alokaciji memorije");
		exit(EXIT_FAILURE);
	}

	for (int i = 0; i < n; i++)
	{
		errno = 0;
		int res = fscanf(linije, "%d %s %s %d %f %f", &autobusi[i].idPutovanja, autobusi[i].ime, autobusi[i].drzava, &autobusi[i].brojSlobodnihMjesta, &autobusi[i].cijena, &autobusi[i].vrijemePolaska);
		if (errno != 0) {
			perror("Pogreska pri citanju linije iz datoteke");
			exit(EXIT_FAILURE);
		}
		if (res != 6) {
			fprintf(stderr, "Greska: neispravan format linije u datoteci\n");
			exit(EXIT_FAILURE);
		}
	}

	fclose(linije);

	return autobusi;
}
int procitajBrojLinija(const char* imeDatLinije) {
	int brojLinija;
	FILE* linije = fopen(imeDatLinije, "r");
	if (linije == NULL) exit(EXIT_FAILURE);

	fread(&brojLinija, sizeof(int), 1, linije);

	fclose(linije);

	return brojLinija;
}

void ispisBrojaSjedala(const char* imeDatLinije) {
	int brojLinija = procitajBrojLinija(imeDatLinije);
	LINIJE* autobusi = procitajLinijeIzDatoteke(imeDatLinije, &brojLinija);


	int i;
	for (i = 0; i < brojLinija; i++) {
		printf("\nAutobus %d - %d\n", i + 1, autobusi[i].brojSlobodnihMjesta);
	}

	system("pause");
	system("cls");
}
void izlaz(void) {
	exit(EXIT_SUCCESS);
	return 0;
}
void unesiPodatkeIKupiKartu(const char* imeDatKupci) {
	KORISNIK kupac;
	printf("Unesite svoje ime: ");
	scanf("%s", kupac.ime);
	printf("Unesite svoje prezime: ");
	scanf("%s", kupac.prezime);
	printf("Unesite broj linije: ");
	scanf("%d", &kupac.idPutovanja);

	FILE* dat = fopen(imeDatKupci, "a");
	if (dat == NULL) {
		printf("Pogreska pri otvaranju datoteke %s.\n", imeDatKupci);
		return;
	}
	fprintf(dat, "%s %s %d\n", kupac.ime, kupac.prezime, kupac.idPutovanja);
	fclose(dat);

	printf("Uspjesno ste kupili kartu!\n");
}
void pretraziKupce(const char* imeDatKupci) {
	char ime[50], prezime[50];
	printf("Unesite ime kupca: ");
	scanf("%s", ime);
	printf("Unesite prezime kupca: ");
	scanf("%s", prezime);

	FILE* dat = fopen(imeDatKupci, "r");
	if (dat == NULL) {
		printf("Pogreska pri otvaranju datoteke %s.\n", imeDatKupci);
		return;
	}

	char imeDat[50], prezimeDat[50];
	int idPutovanja;
	while (fscanf(dat, "%s %s %d", imeDat, prezimeDat, &idPutovanja) == 3) {
		if (strcmp(ime, imeDat) == 0 && strcmp(prezime, prezimeDat) == 0) {
			printf("Kupac %s %s je rezervirao kartu i putuje %d linijom.\n", ime, prezime, idPutovanja);
			fclose(dat);
			return;
		}
	}

	printf("Kupac %s %s nije pronađen.\n", ime, prezime);
	fclose(dat);
}
void odjaviKupca(const char* imeDatKupci) {
	char ime[50], prezime[50];
	printf("Unesite ime kupca kojeg zelite odjaviti: ");
	scanf("%s", ime);
	printf("Unesite prezime kupca kojeg zelite odjaviti: ");
	scanf("%s", prezime);

	FILE* ulaz = fopen(imeDatKupci, "r");
	if (ulaz == NULL) {
		printf("Pogreska pri otvaranju datoteke %s.\n", imeDatKupci);
		return;
	}

	char imeDat[50], prezimeDat[50];
	int idPutovanja;
	long pozicija = -1L;
	while (fscanf(ulaz, "%s %s %d", imeDat, prezimeDat, &idPutovanja) == 3) {
		if (strcmp(ime, imeDat) == 0 && strcmp(prezime, prezimeDat) == 0) {
			pozicija = ftell(ulaz) - strlen(imeDat) - strlen(prezimeDat) - 3;
			break;
		}
	}

	fclose(ulaz);

	if (pozicija == -1L) {
		printf("Kupac %s %s nije pronadjen u datoteci %s.\n", ime, prezime, imeDatKupci);
		return;
	}

	FILE* izlaz = fopen("temp.txt", "w");
	if (izlaz == NULL) {
		printf("Pogreska pri otvaranju datoteke temp.txt.\n");
		return;
	}

	ulaz = fopen(imeDatKupci, "r");
	if (ulaz == NULL) {
		printf("Pogreska pri otvaranju datoteke %s.\n", imeDatKupci);
		fclose(izlaz);
		remove("temp.txt");
		return;
	}

	char linija[100];
	long trenutnaPozicija = 0L;
	while (fgets(linija, 100, ulaz) != NULL) {
		if (trenutnaPozicija != pozicija) {
			fputs(linija, izlaz);
		}
		trenutnaPozicija = ftell(ulaz);
	}

	fclose(ulaz);
	fclose(izlaz);

	if (remove(imeDatKupci) != 0) {
		printf("Pogreska pri brisanju datoteke %s.\n", imeDatKupci);
		return;
	}

	if (rename("temp.txt", imeDatKupci) != 0) {										//18
		printf("Pogreska pri preimenovanju datoteke temp.txt u %s.\n", imeDatKupci);
		return;
	}

	printf("Kupac %s %s je uspjesno odjavljen.\n", ime, prezime);
}
