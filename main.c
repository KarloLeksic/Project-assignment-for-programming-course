#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
//#include <stdlib.h>
//#include <string.h>
//#include <time.h>
#include "zaglavlje.h"



int main(void) {
	int broj_artikala; 
	char* jed_loz;
	char odabir, odabir2;	
	ARTIKL* artikli = NULL;	
	FILE* binarna = NULL; 

	srand((unsigned)time(NULL));	

	while (1) {
		jed_loz = generiranje_jednokratne_lozinke();
		if (upisivanje_jednokratne_lozinke_u_datoteku(jed_loz) == -1) {
			printf("\nGreska!");
			return 1;
		}
		system("cls");
		//if (1) { // odkomentirati ovu i zakomentirati liniju ispod da netreba lozinka
		if( dozvola(jed_loz) ) { 

			do {			
				odabir = glavni_izbornik();
				switch (odabir) {

				case '1':	//Unos robe iznova
					
					unos_robe_iznova();

					break;

				case '2': //Dodavanje robe				
					
					dodavanje_robe(); //misli se na naknadno dodavanje (odabrat opciju 1 ako dode do greske)

					break;

				case '3': //Sortiranje robe

					odabir_sortiranje();

					break;

				case '4': //Pretraživanje robe -> kad pretraži može promijeniti stanje ili obrisati

					odabir2 = pretrazivanje_robe_izbornik();

					pretrazivanje_robe(odabir2);

					break;

				case '5': //Brisanje artikla 

					system("cls");
					printf("\nZa brisanje artikla potrebno je pretraziti\nBirajte opciju 4!");
					

					break;

				case '6': //Upis trenutnog stanja u drugu datoteku
					
					if (upis_u_drugu_datoteku(artikli) == -1) {
						printf("\nDoslo je do greske!");
					}

					break;

				case '7': //Stanje skladista					

					if (stanje_skladista() == -1) {
						printf("\nDoslo je do greske!");
					}

					break;
				}

				if (odabir != '8') {
					printf("\n\nPritisni bilo koju tipku za nastavak...");
					getch();
					system("cls");
				}
				else {
					system("cls");
				}
			} 
			while (odabir != '8');
		}
		else {
			
			cekanje_zbog_krivih_podataka(13);

		}		
	}

	return 0;
}

