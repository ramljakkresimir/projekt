#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "header.h"




int main()
{

	//unosLinija(imeDatLinije);

	int uvijet = 1;

	while (uvijet) {
		uvijet = izbornik();
	}
	printf("Zavrsetak programa!\n");

	return 0;
}
