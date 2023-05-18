#ifndef HEADER_H
#define HEADER_H

typedef struct korisnik			//10  //3
{
	char ime[20];
	char prezime[20];
	int idPutovanja;
}KORISNIK;


typedef struct linije {
	int idPutovanja;
	char ime[64];
	char drzava[64];
	int brojSlobodnihMjesta;
	float cijena;
}LINIJE;

void unosLinija(const char* imeDat);		//10


int izbornik();

void rezIspis(const char* imeDatLinije, const char* imeDatKupci);  //4
void ispisLinija(const char* imeDat);

LINIJE* procitajLinijeIzDatoteke(const char* imeDatLinije);
int procitajBrojLinija(const char* imeDat);

void rezervacija(int odabir, const char* imeDatLinije, const char* imeDatKupci);
void unesiPodatkeKorisnika(KORISNIK* kupac);
void zapisiPutnikaUDatoteku(KORISNIK* kupac, const char* imeDatKupci);
void zapisiLinije(LINIJE* autobusi, int brojLinija, const char* imeDatLinije);

void ispisBrojaSjedala(const char* imeDatLinije);
KORISNIK* pretrazivanje(const char* imeDatKupci);
void odjava(const char* imeDatLinije, const char* imeDatKupci);
int kupacPostoji(KORISNIK* trazeni, KORISNIK* sviKorisnici, int brojKupaca);
int postojiDat(const char* imeDatKupci);
KORISNIK* procitajKorisnikeIzDatoteke(const char* imeDatKupci);
int procitajBrojKorisnika(const char* imeDatKupci);

void obrisi(KORISNIK* kupac, const char* imeDatKupci);

void izlaz();
#endif // HEADER_H


