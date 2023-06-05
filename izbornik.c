#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "header.h"


int izbornik(void) {
	int korisnickiOdabir;

	const char* imeDatLinije = "linije.txt";	//16
	const char* imeDatKupci = "kupci.txt";

	printf("=================================\n");		//8
	printf("|-------------------------------|\n");
	printf("|      Autobusni kolodvor     |\n");
	printf("|-------------------------------|\n");
	printf("=================================\n\n");
	printf("%d. Ispis linija\n", 1);
	printf("%d. Rezervacija karata\n", 2);
	printf("%d. Ispis broja slobodnih sjedala\n", 3);
	printf("%d. Odjava rezervacije\n", 4);
	printf("%d. Pretrazivanje\n", 5);
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
		ispisLinija(imeDatLinije);
		break;

	case 2:
		unesiPodatkeIKupiKartu(imeDatKupci);
		break;

	case 3:
		ispisBrojaSjedala(imeDatLinije);
		break;
	case 4:
		odjaviKupca(imeDatKupci);
		break;
	case 5:
		pretraziKupce(imeDatKupci);
		break;
	case 6:
		izlaz();
		break;
	default:
		break;
	}

	return korisnickiOdabir;
}
