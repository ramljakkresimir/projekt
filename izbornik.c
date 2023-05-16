#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "header.h"


int izbornik(void) {
	int korisnickiOdabir;

	const char* imeDatLinije = "linije.txt";
	const char* imeDatKupci = "kupci.bin";

	printf("=================================\n");
	printf("|-------------------------------|\n");
	printf("|      Autobusni kolodvor     |\n");
	printf("|-------------------------------|\n");
	printf("=================================\n\n");
	printf("%d. Rezervacija karata\n", 1);
	printf("%d. Ispis broja sjedala\n", 2);
	printf("%d. Pretrazivanje\n", 3);
	printf("%d. Odjava rezervacije\n", 4);
	printf("%d. Ispis linija\n", 5);
	printf("%d. Izlaz\n", 6);
	printf("Vas odabir:  ");
	do {
		scanf("%d", &korisnickiOdabir);
		if (1 > korisnickiOdabir || korisnickiOdabir > 6) {
			printf("Opcija za Vas unos ne postoji.\n Novi unos: ");
		}
	} while (!(1 <= korisnickiOdabir && korisnickiOdabir <= 6));

	switch (korisnickiOdabir) {
	case 1:
		rez_ispis(imeDatLinije, imeDatKupci);
		break;
	case 2:
		ispisBrojaSjedala(imeDatLinije);
		break;
	case 3: {
		KORISNIK* trazeni = pretrazivanje(imeDatKupci);
		if (trazeni == NULL) {
			printf("\nTrazeni kupac se ne nalazi u datoteci.\n\n");
		}
		else {
			printf("\n%s %s se nalazi u kupcima i putuje s linijom %d.\n\n", trazeni->ime, trazeni->prezime, trazeni->idPutovanja);
		}
		break;
	}
	case 4:
		odjava(imeDatLinije, imeDatKupci);
		break;
	case 5:
		ispisLinija(imeDatLinije);
		break;
	case 6:
		izlaz();
		break;
	default:
		break;
	}

	return korisnickiOdabir;
}
