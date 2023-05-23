#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "header.h"

void rezIspis(const char* imeDatLinije, const char* imeDatKupci) {
	system("cls");

	ispisLinija(imeDatLinije);

	int odabir;
	do {
		printf("Unesi broj linije: ");
		scanf("%d", &odabir);
	} while (odabir < 0 || odabir > 5);

	rezervacija(odabir, imeDatLinije, imeDatKupci);

}

void ispisLinija(const char* imeDatLinije) {

	LINIJE* autobusi = procitajLinijeIzDatoteke(imeDatLinije);
	int brojLinija = procitajBrojLinija(imeDatLinije);


	for (int i = 0; i < brojLinija; i++) {
		printf("\n");

		printf("Broj linije: %d\n", autobusi[i].idPutovanja);

		printf("Ime linije: %s\n", autobusi[i].ime);

		printf("Drzava linije: %s\n", autobusi[i].drzava);

		printf("Broj slobodnih mjesta linije: %d\n", autobusi[i].brojSlobodnihMjesta);

		printf("Cijena linije: %.2f\n", autobusi[i].cijena);

		printf("\n");
	}

	free(autobusi);									//14
}

LINIJE* procitajLinijeIzDatoteke(const char* imeDatLinije) {
	FILE* linije = fopen(imeDatLinije, "rb");
	if (linije == NULL) exit(EXIT_FAILURE);

	int brojLinija;
	fread(&brojLinija, sizeof(int), 1, linije);

	LINIJE* autobusi = (LINIJE*)malloc(brojLinija * sizeof(LINIJE));  //14
	if (autobusi == NULL) exit(EXIT_FAILURE);

	fread(autobusi, sizeof(LINIJE), brojLinija, linije);

	fclose(linije);

	return autobusi;
}

int procitajBrojLinija(const char* imeDatLinije) {
	int brojLinija;
	FILE* linije = fopen(imeDatLinije, "rb");
	if (linije == NULL) exit(EXIT_FAILURE);

	fread(&brojLinija, sizeof(int), 1, linije);

	fclose(linije);

	return brojLinija;
}

void rezervacija(int odabir, const char* imeDatLinije, const char* imeDatKupci)
{
	KORISNIK kupac;
	unesiPodatkeKorisnika(&kupac);
	kupac.idPutovanja = odabir;

	int brojLinija = procitajBrojLinija(imeDatLinije);
	LINIJE* autobusi = procitajLinijeIzDatoteke(imeDatLinije);

	for (int i = 0; i < brojLinija; i++) {
		if (odabir == autobusi[i].idPutovanja) {
			autobusi[i].brojSlobodnihMjesta--;
			zapisiPutnikaUDatoteku(&kupac, imeDatKupci);
			zapisiLinije(autobusi, brojLinija, imeDatLinije);
		}
	}
}

int postojiDat(const char* imeDatKupci) {
	if (fopen(imeDatKupci, "rb") == NULL) return 0;
	else return 1;
}

void zapisiPutnikaUDatoteku(KORISNIK* kupac, const char* imeDatKupci) {

	if (postojiDat(imeDatKupci)) {

		int brojKorisnika;

		FILE* korisnici = fopen(imeDatKupci, "rb");
		if (korisnici == NULL) exit(EXIT_FAILURE);

		fread(&brojKorisnika, sizeof(int), 1, korisnici);

		KORISNIK* sviKorisnici = (KORISNIK*)malloc(brojKorisnika * sizeof(KORISNIK));
		if (sviKorisnici == NULL) exit(EXIT_FAILURE);

		fread(sviKorisnici, sizeof(KORISNIK), brojKorisnika, korisnici);

		fclose(korisnici);

		korisnici = fopen(imeDatKupci, "wb");

		brojKorisnika++;

		fwrite(&brojKorisnika, sizeof(int), 1, korisnici);

		fwrite(sviKorisnici, sizeof(KORISNIK), brojKorisnika - 1, korisnici);

		fwrite(kupac, sizeof(KORISNIK), 1, korisnici);

		fclose(korisnici);

	}
	else {
		FILE* korisnici = fopen(imeDatKupci, "wb");
		if (korisnici == NULL) exit(EXIT_FAILURE);
		int broj = 1;
		fwrite(&broj, sizeof(int), 1, korisnici);
		fwrite(kupac, sizeof(KORISNIK), 1, korisnici);
		fclose(korisnici);
	}
}

void zapisiLinije(LINIJE* autobusi, int brojLinija, const char* imeDatLinije) {
	FILE* linije = fopen(imeDatLinije, "wb");
	if (linije == NULL) exit(EXIT_FAILURE);

	fwrite(&brojLinija, sizeof(int), 1, linije);
	fwrite(autobusi, sizeof(LINIJE), brojLinija, linije);

	fclose(linije);
}

void unesiPodatkeKorisnika(KORISNIK* kupac) {
	printf("Unesite svoje ime: ");
	scanf("%s", kupac->ime);
	printf("Unesite svoje prezime: ");
	scanf("%s", kupac->prezime);
	printf("Unesite broj linije: ");
	scanf("%d", &kupac->idPutovanja);
}


void unosLinija(const char* imeDat) {
	printf("Unesi broj linija: ");
	int brojLinija;
	scanf("%d", &brojLinija);

	LINIJE* autobusi = (LINIJE*)malloc(brojLinija * sizeof(LINIJE));  //14
	if (autobusi == NULL) exit(EXIT_FAILURE);

	for (int i = 0; i < brojLinija; i++) {

		autobusi[i].idPutovanja = i;

		printf("Unesi ime linije: ");
		scanf("%64s", autobusi[i].ime);

		printf("Unesi drzavu linije: ");
		scanf("%64s", autobusi[i].drzava);

		printf("Unesi broj slobodnih mjesta linije: ");
		scanf("%d", &autobusi[i].brojSlobodnihMjesta);

		printf("Unesi cijenu linije: ");
		scanf("%f", &autobusi[i].cijena);
	}

	FILE* linijeData = fopen(imeDat, "wb");
	if (linijeData == NULL) exit(EXIT_FAILURE);

	fwrite(&brojLinija, sizeof(int), 1, linijeData);

	fwrite(autobusi, sizeof(LINIJE), brojLinija, linijeData);

	fclose(linijeData);
	free(autobusi);													//14
}

void ispisBrojaSjedala(const char* imeDatLinije) {

	LINIJE* autobusi = procitajLinijeIzDatoteke(imeDatLinije);
	int brojLinija = procitajBrojLinija(imeDatLinije);

	int i;
	for (i = 0; i < brojLinija; i++) {
		printf("\nAutobus %d - %d\n", i, autobusi[i].brojSlobodnihMjesta);
	}

	system("pause");
	system("cls");
}

KORISNIK* pretrazivanje(const char* imeDatKupci) {		//pretrazivanje	

	KORISNIK* kupac = (KORISNIK*)malloc(sizeof(KORISNIK));
	if (kupac == NULL) exit(EXIT_FAILURE);
	unesiPodatkeKorisnika(kupac);

	FILE* kupci = fopen(imeDatKupci, "rb");
	if (kupci == NULL) exit(EXIT_FAILURE);

	KORISNIK usporedba;

	int brojKupaca;
	fread(&brojKupaca, sizeof(int), 1, kupci);

	while ((fread(&usporedba, sizeof(KORISNIK), 1, kupci)) != 0) {
		if (!strcmp(usporedba.ime, kupac->ime) && !strcmp(usporedba.prezime, kupac->prezime) && usporedba.idPutovanja == kupac->idPutovanja) {
			fclose(kupci);
			return kupac;
		}
	}

	fclose(kupci);
	return NULL;
}

void odjava(const char* imeDatLinije, const char* imeDatKupci) {

	KORISNIK kupac;
	unesiPodatkeKorisnika(&kupac);

	LINIJE* autobusi = procitajLinijeIzDatoteke(imeDatLinije);
	int brojLinija = procitajBrojLinija(imeDatLinije);
	KORISNIK* kupci = procitajKorisnikeIzDatoteke(imeDatKupci);
	int brojKorisnika = procitajBrojKorisnika(imeDatKupci);

	if (kupacPostoji(&kupac, kupci, brojKorisnika)) {
		for (int i = 0; i < brojLinija; i++) {
			if (autobusi[i].idPutovanja == kupac.idPutovanja) {
				autobusi[i].brojSlobodnihMjesta++;
			}
		}
		zapisiLinije(autobusi, brojLinija, imeDatLinije);

		obrisi(&kupac, imeDatKupci);

		printf("\nKupac uspjesno obrisan.\n\n");
	}
	else {
		printf("\nKupac ne postoji.\n\n");
	}
}

int kupacPostoji(KORISNIK* trazeni, KORISNIK* sviKorisnici, int brojKorisnika) {
	int i;
	for (i = 0; i < brojKorisnika; i++) {
		if (!strcmp(trazeni->ime, sviKorisnici[i].ime) && !strcmp(trazeni->prezime, sviKorisnici[i].prezime) && trazeni->idPutovanja == sviKorisnici[i].idPutovanja) {
			return 1;
		}
	}
	return 0;
}

int procitajBrojKorisnika(const char* imeDatKupci) {
	FILE* kupciDat = fopen(imeDatKupci, "rb");
	if (kupciDat == NULL) exit(EXIT_FAILURE);

	int brojKupaca;

	fread(&brojKupaca, sizeof(int), 1, kupciDat);

	fclose(kupciDat);
	return brojKupaca;
}

KORISNIK* procitajKorisnikeIzDatoteke(const char* imeDatKupci) {
	FILE* kupciDat = fopen(imeDatKupci, "rb");
	if (kupciDat == NULL) exit(EXIT_FAILURE);

	int brojKupaca;
	fread(&brojKupaca, sizeof(int), 1, kupciDat);

	KORISNIK* kupci = (KORISNIK*)malloc(brojKupaca * sizeof(KORISNIK));			//14
	if (kupci == NULL) exit(EXIT_FAILURE);

	fread(kupci, sizeof(KORISNIK), brojKupaca, kupciDat);

	fclose(kupciDat);
	return kupci;
}

void obrisi(KORISNIK* kupac, const char* imeDatKupci) {
	FILE* kupci = fopen(imeDatKupci, "rb");
	if (kupci == NULL) exit(EXIT_FAILURE);

	FILE* noviKupci = fopen("kupciKopija.bin", "wb");
	if (noviKupci == NULL) exit(EXIT_FAILURE);

	KORISNIK usporedba;

	int brojKupaca;
	fread(&brojKupaca, sizeof(int), 1, kupci);
	brojKupaca--;

	fwrite(&brojKupaca, sizeof(int), 1, noviKupci);

	while ((fread(&usporedba, sizeof(KORISNIK), 1, kupci)) != 0) {
		if (!(!strcmp(usporedba.ime, kupac->ime) && !strcmp(usporedba.prezime, kupac->prezime) && usporedba.idPutovanja == kupac->idPutovanja)) {
			fwrite(&usporedba, sizeof(KORISNIK), 1, noviKupci);
		}
	}

	fclose(noviKupci);
	fclose(kupci);


	noviKupci = fopen("kupciKopija.bin", "rb");
	if (noviKupci == NULL) exit(EXIT_FAILURE);

	kupci = fopen(imeDatKupci, "wb");
	if (kupci == NULL) exit(EXIT_FAILURE);

	fread(&brojKupaca, sizeof(int), 1, noviKupci);
	fwrite(&brojKupaca, sizeof(int), 1, kupci);
	while ((fread(&usporedba, sizeof(KORISNIK), 1, noviKupci) != 0)) {
		fwrite(&usporedba, sizeof(KORISNIK), 1, kupci);
	}

	fclose(noviKupci);
	fclose(kupci);
}

void izlaz(void) {
	exit(EXIT_SUCCESS);
	return 0;
}
