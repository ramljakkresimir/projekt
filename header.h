#ifndef HEADER_H
#define HEADER_H

typedef struct korisnik		//3	
{
	char ime[20];
	char prezime[20];		//2
	int idPutovanja;
}KORISNIK;


typedef struct linije {			//10
	int idPutovanja;
	char ime[64];				//1
	char drzava[64];
	int brojSlobodnihMjesta;
	float cijena;
	float vrijemePolaska;
}LINIJE;

void unosLinija(const char* imeDat);

int izbornik();

void unesiPodatkeIKupiKartu(const char* imeDatKupci); 
void pretraziKupce(const char* imeDatKupci);
void odjaviKupca(const char* imeDatKupci);

void ispisLinija(const char* imeDat);			//4

LINIJE* procitajLinijeIzDatoteke(const char* imeDatLinije);
int procitajBrojLinija(const char* imeDatLinije);


void ispisBrojaSjedala(const char* imeDatLinije);

void izlaz();
#endif // HEADER_H
