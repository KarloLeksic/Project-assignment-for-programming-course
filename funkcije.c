#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "zaglavlje.h"


//dinamicki zauzimanje memorije za polje artikla
ARTIKL* zauzimanje_memorije(int broj_artikala) {
	ARTIKL* artikli = NULL;
	artikli = (ARTIKL*)calloc(broj_artikala, sizeof(ARTIKL));
	if (artikli == NULL) {
		return NULL;
	}

	return artikli;
}

//funkcija za unasanje podataka u strukture
void unos_u_strukture(ARTIKL* artikli, int pocni_od, int zavrsi) {
	int i;
	for (i = pocni_od; i < zavrsi; i++) {
		system("cls");
		printf("*************** %d. ARTIKL ***************", i + 1);
		printf("\nUnesi ime artikla: ");
		scanf(" %49[^\n]", (artikli + i)->ime);
		printf("\nUnesi sifru artikla: ");
		scanf(" %d", &(artikli + i)->sifra);
		printf("\nUnesi kolicinu: ");
		scanf(" %d", &(artikli + i)->kolicina);
		printf("\nUnesi cijenu: ");
		do {
			scanf(" %f", &(artikli + i)->cijena);
			if ((artikli + i)->cijena < 0) {
				printf("\nPogresno unesena cijena! Pokusajte ponovo\n");
			}
		} while ((artikli + i)->cijena < 0);
		printf("\n*****************************************\n");
	}

	return;
}

//funkcija za ispis na ekran
void ispis_na_ekran(ARTIKL* artikli, int ukupan_broj_artikala) {
	int i;
	for (i = 0; i < ukupan_broj_artikala; i++) {
		printf("\n***** %d. ARTIKL *****", i + 1);
		printf("\nIme :%s", (artikli + i)->ime);
		printf("\nSifra :%d", (artikli + i)->sifra);
		printf("\nKolicina: %d", (artikli + i)->kolicina);
		printf("\nCijena: %.2f kn", (artikli + i)->cijena);
		printf("\n*********************\n\n");
	}

	return;
}

//upis u txt datoteku
void upis_u_txt_datoteku(ARTIKL* artikli, int broj_artikala) {
	char ime_datoteke[50];
	float ukupna_vrijednost = 0;
	FILE* fp;
	printf("\nUnesi ime datoteke i ekstenziju: "); //cilja se na txt datoteku
	scanf(" %49[^\n]", ime_datoteke);
	fp = fopen(ime_datoteke, "w");
	if (fp == NULL) {
		printf("\nDoslo je do pogreske...");
	}
	else {
		fprintf(fp, "Ukupno %d artik%sl%s:\n", broj_artikala, broj_artikala <= 4 ? "" : "a", broj_artikala == 1 ? "" : "a");
		for (int i = 0; i < broj_artikala; i++) {
			fprintf(fp, "\n***** %d. ARTIKL *****", i + 1);
			fprintf(fp, "\nIme: %s", (artikli + i)->ime);
			fprintf(fp, "\nSifra: %d", (artikli + i)->sifra);
			fprintf(fp, "\nKolicina: %d", (artikli + i)->kolicina);
			fprintf(fp, "\nCijena: %.2f kn", (artikli + i)->cijena);
			fprintf(fp, "\n*********************\n");
			ukupna_vrijednost += (artikli + i)->cijena * (artikli + i)->kolicina;
		}
		fprintf(fp, "\nUkupna vrijednost u skladistu je %.2f kn", ukupna_vrijednost);
		system("cls");
		printf("Uspjesno upisano");
		fclose(fp);
	}

	return;
}

//sortiranje strukturi po imenu -> (samo po prvom slovu) - silazno
void selection_sort_ime_s(ARTIKL* artikli, int ukupan_broj_artikala) {
	char prvo_slovo1, prvo_slovo2;
	ARTIKL pom;
	int min;

	for (int i = 0; i < ukupan_broj_artikala - 1; i++) {
		min = i;
		prvo_slovo1 = (artikli + i)->ime[0] >= 'a' && (artikli + i)->ime[0] <= 'z' ? (artikli + i)->ime[0] : (artikli + i)->ime[0] + 32;
		for (int j = i + 1; j < ukupan_broj_artikala; j++) {
			prvo_slovo2 = (artikli + j)->ime[0] >= 'a' && (artikli + j)->ime[0] <= 'z' ? (artikli + j)->ime[0] : (artikli + j)->ime[0] + 32;
			if (prvo_slovo1 < prvo_slovo2) {
				min = j;
				prvo_slovo1 = (artikli + j)->ime[0] >= 'a' && (artikli + j)->ime[0] <= 'z' ? (artikli + j)->ime[0] : (artikli + j)->ime[0] + 32;
			}
		}
		//zamjena imena
		strcpy(pom.ime, (artikli + i)->ime);
		strcpy((artikli + i)->ime, (artikli + min)->ime);
		strcpy((artikli + min)->ime, pom.ime);
		//zamjena cjene
		pom.cijena = (artikli + i)->cijena;
		(artikli + i)->cijena = (artikli + min)->cijena;
		(artikli + min)->cijena = pom.cijena;
		//zamjena kolicine
		pom.kolicina = (artikli + i)->kolicina;
		(artikli + i)->kolicina = (artikli + min)->kolicina;
		(artikli + min)->kolicina = pom.kolicina;
		//zamjena sifre
		pom.sifra = (artikli + i)->sifra;
		(artikli + i)->sifra = (artikli + min)->sifra;
		(artikli + min)->sifra = pom.sifra;
	}

	return;
}

//sortiranje strukturi po imenu -> (samo po prvom slovu) - uzlazno
void selection_sort_ime_u(ARTIKL* artikli, int ukupan_broj_artikala) {
	char prvo_slovo1, prvo_slovo2;
	ARTIKL pom;
	int max;

	for (int i = 0; i < ukupan_broj_artikala - 1; i++) {
		max = i;
		prvo_slovo1 = (artikli + i)->ime[0] >= 'A' && (artikli + i)->ime[0] <= 'Z' ? (artikli + i)->ime[0] : (artikli + i)->ime[0] - 32;
		for (int j = i + 1; j < ukupan_broj_artikala; j++) {
			prvo_slovo2 = (artikli + j)->ime[0] >= 'A' && (artikli + j)->ime[0] <= 'Z' ? (artikli + j)->ime[0] : (artikli + j)->ime[0] - 32;
			if (prvo_slovo1 > prvo_slovo2) {
				max = j;
				prvo_slovo1 = (artikli + j)->ime[0] >= 'A' && (artikli + j)->ime[0] <= 'Z' ? (artikli + j)->ime[0] : (artikli + j)->ime[0] - 32;
			}
		}
		//zamjena imena
		strcpy(pom.ime, (artikli + i)->ime);
		strcpy((artikli + i)->ime, (artikli + max)->ime);
		strcpy((artikli + max)->ime, pom.ime);
		//zamjena cjene
		pom.cijena = (artikli + i)->cijena;
		(artikli + i)->cijena = (artikli + max)->cijena;
		(artikli + max)->cijena = pom.cijena;
		//zamjena kolicine
		pom.kolicina = (artikli + i)->kolicina;
		(artikli + i)->kolicina = (artikli + max)->kolicina;
		(artikli + max)->kolicina = pom.kolicina;
		//zamjena sifre
		pom.sifra = (artikli + i)->sifra;
		(artikli + i)->sifra = (artikli + max)->sifra;
		(artikli + max)->sifra = pom.sifra;
	}

	return;
}

//sortiranje strukturi po cijeni  -> od najmanjeg do najveceg - uzlazno
void selection_sort_cijena_u(ARTIKL* artikli, int broj_artikala) {
	ARTIKL pom;
	int min;
	for (int i = 0; i < broj_artikala - 1; i++) {
		min = i;
		for (int j = i + 1; j < broj_artikala; j++) {
			if ((artikli + j)->cijena < (artikli + min)->cijena) {
				min = j;
			}
		}
		//zamjena imena
		strcpy(pom.ime, (artikli + i)->ime);
		strcpy((artikli + i)->ime, (artikli + min)->ime);
		strcpy((artikli + min)->ime, pom.ime);
		//zamjena cjene
		pom.cijena = (artikli + i)->cijena;
		(artikli + i)->cijena = (artikli + min)->cijena;
		(artikli + min)->cijena = pom.cijena;
		//zamjena kolicine
		pom.kolicina = (artikli + i)->kolicina;
		(artikli + i)->kolicina = (artikli + min)->kolicina;
		(artikli + min)->kolicina = pom.kolicina;
		//zamjena sifre
		pom.sifra = (artikli + i)->sifra;
		(artikli + i)->sifra = (artikli + min)->sifra;
		(artikli + min)->sifra = pom.sifra;
	}

	return;
}

//sortiranje strukturi po cijeni  -> od najmanjeg do najveceg - silazno
void selection_sort_cijena_s(ARTIKL* artikli, int broj_artikala) {
	ARTIKL pom;
	int max;
	for (int i = 0; i < broj_artikala - 1; i++) {
		max = i;
		for (int j = i + 1; j < broj_artikala; j++) {
			if ((artikli + j)->cijena > (artikli + max)->cijena) {
				max = j;
			}
		}
		//zamjena imena
		strcpy(pom.ime, (artikli + i)->ime);
		strcpy((artikli + i)->ime, (artikli + max)->ime);
		strcpy((artikli + max)->ime, pom.ime);
		//zamjena cjene
		pom.cijena = (artikli + i)->cijena;
		(artikli + i)->cijena = (artikli + max)->cijena;
		(artikli + max)->cijena = pom.cijena;
		//zamjena kolicine
		pom.kolicina = (artikli + i)->kolicina;
		(artikli + i)->kolicina = (artikli + max)->kolicina;
		(artikli + max)->kolicina = pom.kolicina;
		//zamjena sifre
		pom.sifra = (artikli + i)->sifra;
		(artikli + i)->sifra = (artikli + max)->sifra;
		(artikli + max)->sifra = pom.sifra;
	}

	return;
}

//sortiranje strukturi po kolicini	-> od najmanjeg do najveceg - uzlazno
void selection_sort_kolicina_u(ARTIKL* artikli, int broj_artikala) {
	ARTIKL pom;
	int min;
	for (int i = 0; i < broj_artikala - 1; i++) {
		min = i;
		for (int j = i + 1; j < broj_artikala; j++) {
			if ((artikli + j)->kolicina < (artikli + min)->kolicina) {
				min = j;
			}
		}
		//zamjena imena
		strcpy(pom.ime, (artikli + i)->ime);
		strcpy((artikli + i)->ime, (artikli + min)->ime);
		strcpy((artikli + min)->ime, pom.ime);
		//zamjena cjene
		pom.cijena = (artikli + i)->cijena;
		(artikli + i)->cijena = (artikli + min)->cijena;
		(artikli + min)->cijena = pom.cijena;
		//zamjena kolicine
		pom.kolicina = (artikli + i)->kolicina;
		(artikli + i)->kolicina = (artikli + min)->kolicina;
		(artikli + min)->kolicina = pom.kolicina;
		//zamjena sifre
		pom.sifra = (artikli + i)->sifra;
		(artikli + i)->sifra = (artikli + min)->sifra;
		(artikli + min)->sifra = pom.sifra;
	}

	return;
}



//sortiranje strukturi po kolicini	-> od najmanjeg do najveceg - silazno
void selection_sort_kolicina_s(ARTIKL* artikli, int broj_artikala) {
	ARTIKL pom;
	int max;
	for (int i = 0; i < broj_artikala - 1; i++) {
		max = i;
		for (int j = i + 1; j < broj_artikala; j++) {
			if ((artikli + j)->kolicina > (artikli + max)->kolicina) {
				max = j;
			}
		}
		//zamjena imena
		strcpy(pom.ime, (artikli + i)->ime);
		strcpy((artikli + i)->ime, (artikli + max)->ime);
		strcpy((artikli + max)->ime, pom.ime);
		//zamjena cjene
		pom.cijena = (artikli + i)->cijena;
		(artikli + i)->cijena = (artikli + max)->cijena;
		(artikli + max)->cijena = pom.cijena;
		//zamjena kolicine
		pom.kolicina = (artikli + i)->kolicina;
		(artikli + i)->kolicina = (artikli + max)->kolicina;
		(artikli + max)->kolicina = pom.kolicina;
		//zamjena sifre
		pom.sifra = (artikli + i)->sifra;
		(artikli + i)->sifra = (artikli + max)->sifra;
		(artikli + max)->sifra = pom.sifra;
	}

	return;
}

//funkcija za sortiranje
void sortiranje(ARTIKL* artikli, int ukupan_broj_artikala) {
	char odabir2, odabir3;
	char izabrano[20];
	system("cls");
	printf("Odaberite kriterij sortiranja:");
	printf("\n1. Ime\n2. Kolicina\n3. Cijena\n");
	do {
		odabir2 = getch();
		if (odabir2 < '1' || odabir2 > '3') {
			printf("\nPogresan odabir! Pokusajte ponovo: ");
		}
	} while (odabir2 < '1' || odabir2 > '3');
	printf("\nI redosljed:\n1. Uzlazno\n2. Sizalno\n");
	do {
		odabir3 = getch();
		if (odabir3 < '1' || odabir3 > '2') {
			printf("\nPogresan odabir! Pokusajte ponovo: ");
		}
	} while (odabir3 < '1' || odabir3 > '2');

	switch (odabir2) {
	case '1': if (odabir3 == '1') {
		selection_sort_ime_u(artikli, ukupan_broj_artikala);
		strcpy(izabrano, "Ime - uzlazno");
	}
			else {
		selection_sort_ime_s(artikli, ukupan_broj_artikala);
		strcpy(izabrano, "Ime - silazno");
	}
			break;
	case '2': if (odabir3 == '1') {
		selection_sort_kolicina_u(artikli, ukupan_broj_artikala);
		strcpy(izabrano, "Kolicina - uzlazno");
	}
			else {
		selection_sort_kolicina_s(artikli, ukupan_broj_artikala);
		strcpy(izabrano, "Kolicina - silazno");
	}
			break;
	case '3': if (odabir3 == '1') {
		selection_sort_cijena_u(artikli, ukupan_broj_artikala);
		strcpy(izabrano, "Cijena - uzlazno");
	}
			else {
		selection_sort_cijena_s(artikli, ukupan_broj_artikala);
		strcpy(izabrano, "Cijena - silazno");

	}
			break;
	}
	system("cls");
	printf("Izabran sort: %s\n", izabrano);
	printf("Podaci sortirani\n");

	return;
}

//traziti korisnicko ime, sifru i jednokratnu lozinku -> vraca 1 za tocno unesene podatke
int unos_username_i_password(char* jednokratna_lozinka) {
	char username[] = { "karlo.leksic" };
	char password[] = { "123456" };
	char unos_username[13], unos_password[7] = { '\0' }, unos_jednokratna[7] = { '\0' };
	int f1 = 0, f2 = 0, f3 = 0;
	printf("Korisnicko ime: ");
	scanf(" %12[^\n]", unos_username);
	if (strcmp(username, unos_username) == 0) {
		f1 = 1;
	}
	printf("Sifra: ");
	for (int i = 0; i < 6; i++) {
		unos_password[i] = getch();
		printf("*");
	}
	if (strcmp(unos_password, password) == 0) {
		f2 = 1;
	}
	printf("\nJednokratna lozinka: ");
	scanf(" %6[^\n]", unos_jednokratna);
	if (strcmp(unos_jednokratna, jednokratna_lozinka) == 0) {
		f3 = 1;
	}

	return f1 && f2 && f3;
}

//dozvola vraca 1 ako je od bilo kojeg pokusaja uneseno dobro username, sifra i jednokratna lozinka
int dozvola(char* jednokratna_lozinka) {
	int f = 0;
	if (unos_username_i_password(jednokratna_lozinka)) {
		system("cls");
		printf("Ispravno uneseni podaci za prijavu\n\n");
		f = 1;
	}
	else {
		int broj_pokusaja = 3;
		while (broj_pokusaja > 0) {
			system("cls");
			printf("Neispravni podaci za prijavu!");
			printf("\nPreostalo pokusaja: %d\n\n", broj_pokusaja);
			if (unos_username_i_password(jednokratna_lozinka)) {
				system("cls");
				printf("Ispravno uneseni podaci za prijavu\n\n");
				f = 1;
				break;
			}
			broj_pokusaja--;
		}
	}

	return f;
}

//funkcija za generiranje jednokratne lozinke
char* generiranje_jednokratne_lozinke() {
	int i, pom;
	char* jednokratna_lozinka;
	jednokratna_lozinka = (char*)malloc(7 * sizeof(char));
	for (i = 0; i < 6; i++) {
		pom = rand() % 3;
		if (pom == 0) {
			*(jednokratna_lozinka + i) = rand() % (57 - 48 + 1) + 48;
		}
		else if (pom == 1) {
			*(jednokratna_lozinka + i) = rand() % (90 - 65 + 1) + 65;
		}
		else if (pom == 2) {
			*(jednokratna_lozinka + i) = rand() % (122 - 97 + 1) + 97;
		}
	}
	*(jednokratna_lozinka + 6) = '\0';

	return jednokratna_lozinka;
}

//upisivanje jednokratne lozinke u datoteku
int upisivanje_jednokratne_lozinke_u_datoteku(char* jed_loz) {
	FILE* fp = NULL;
	fp = fopen("jednokratna lozinka.txt", "w");
	if (fp == NULL) {
		return -1;
	}
	else {
		fprintf(fp, "%s", jed_loz);
		fclose(fp);
		return 0;
	}
}

void ispis_pronadenog(ARTIKL* artikli, int index_pronadenog) {
	system("cls");
	printf("Artikl pronaden:\n");
	printf("\nIme : %s", (artikli + index_pronadenog)->ime);
	printf("\nSifra : %d", (artikli + index_pronadenog)->sifra);
	printf("\nKolicina: %d", (artikli + index_pronadenog)->kolicina);
	printf("\nCijena: %.2f kn\n", (artikli + index_pronadenog)->cijena);

	return;
}

//trazenje po imenu
int trazenje_imena(ARTIKL* artikli, int broj_artikala, char* ime) {
	int i, f = 0;
	for (i = 0; i < broj_artikala; i++) {
		if (strcmp(ime, (artikli + i)->ime) == 0) {
			f = 1;
			break;
		}
	}
	if (f == 1) {
		return i;
	}
	else {
		return -1;
	}
}

//trazenje po sifri
int trazenje_sifre(ARTIKL* artikli, int broj_artikala, int sifra) {
	int i, f = 0;
	for (i = 0; i < broj_artikala; i++) {
		if (sifra == (artikli + i)->sifra) {
			f = 1;
			break;
		}
	}
	if (f == 1) {
		return i;
	}
	else {
		return -1;
	}
}

//trazenje po cijeni
int trazenje_cijene(ARTIKL* artikli, int broj_artikala, float cijena) {
	int i, f = 0;
	for (i = 0; i < broj_artikala; i++) {
		if (cijena == (artikli + i)->cijena) {
			f = 1;
			break;
		}
	}
	if (f == 1) {
		return i;
	}
	else {
		return -1;
	}
}

//trazenje po kolicini
int trazenje_kolicine(ARTIKL* artikli, int broj_artikala, int kolicina) {
	int i, f = 0;
	for (i = 0; i < broj_artikala; i++) {
		if (kolicina == (artikli + i)->kolicina) {
			f = 1;
			break;
		}
	}
	if (f == 1) {
		return i;
	}
	else {
		return -1;
	}
}

//upis u binarnu datoteku iznova
int upis_u_datoteku(ARTIKL* artikli, int broj_artikala) {
	FILE* binarna = NULL;
	binarna = fopen("skladiste.bin", "wb");
	if (binarna == NULL) {
		printf("\nGreska sa datotekom!");
		return -1;
	}
	else {
		fwrite(&broj_artikala, sizeof(int), 1, binarna);
		fwrite(artikli, sizeof(ARTIKL), broj_artikala, binarna);
		fclose(binarna);
		return 0;
	}
}

//radnje koje zelimo ako naðemo artikl
int radnje_pretrazivanja(ARTIKL* artikli, int broj_artikala, int index_pronadenog) {
	if (index_pronadenog != -1) {
		int novoStanje, f = -1;
		char odabir3;
		printf("\nOdaberite:\n");
		printf("1. Promjena stanja\n");
		printf("2. Brisanje artikla\n");
		printf("3. Nista\n\n");
		do {
			odabir3 = getch();
			if (odabir3 < '1' || odabir3 > '3') {
				printf("Pogresan odabir! Pokusajte ponovo: ");
			}
		} while (odabir3 < '1' || odabir3 > '3');
		switch (odabir3) {
		case '1'://Promjena stanja
			printf("Unesite novo stanje: ");
			scanf(" %d", &novoStanje);
			(artikli + index_pronadenog)->kolicina = novoStanje;
			if (upis_u_datoteku(artikli, broj_artikala) == -1) {
				printf("\nDoslo je do greske!");
			}
			else {
				printf("\nStanje uspijesno promijenjeno\n");
			}
			break;

		case '2': //Brisanje artikla								
			f = brisanje(index_pronadenog, artikli, broj_artikala);
			if (f == -1) {
				return -1;
			}
			break;
		case '3': //Nista od navedenog
			break;
		}
		return 0;
	}
	else {
		return -1;
	}
}

//odabir za upis u drugu datoteku
int upis_u_drugu_datoteku(ARTIKL* artikli) {
	system("cls");
	int broj_artikala;
	FILE* binarna = NULL;
	binarna = fopen("skladiste.bin", "rb");
	if (binarna == NULL) {
		return -1;
	}
	else {
		fread(&broj_artikala, sizeof(int), 1, binarna);
		artikli = zauzimanje_memorije(broj_artikala);
		if (artikli == NULL) {
			return -1;
		}
		else {
			fread(artikli, sizeof(ARTIKL), broj_artikala, binarna);
			fclose(binarna);
			upis_u_txt_datoteku(artikli, broj_artikala);
			free(artikli);
			artikli = NULL;
			return broj_artikala;
		}
	}
}

//odabir 6 u glavnom izorniku - stanje skladista
int stanje_skladista() {
	system("cls");
	FILE* binarna = NULL;
	ARTIKL* artikli = NULL;
	int broj_artikala = -1;
	binarna = fopen("skladiste.bin", "rb");
	if (binarna == NULL) {
		return -1;
	}
	else {
		fread(&broj_artikala, sizeof(int), 1, binarna);
		printf("Ukupno %d artik%sl%s:\n", broj_artikala, broj_artikala <= 4 ? "" : "a", broj_artikala == 1 ? "" : "a");
		artikli = zauzimanje_memorije(broj_artikala);
		if (artikli == NULL) {
			return -1;
		}
		else {
			fread(artikli, sizeof(ARTIKL), broj_artikala, binarna);
			fclose(binarna);
			ispis_na_ekran(artikli, broj_artikala);
			free(artikli);
			artikli = NULL;
			return broj_artikala;
		}
	}
}

//odabir za pretrazivanje po cijeni
int pretrazivanje_po_cijeni(ARTIKL* artikli, int broj_artikala) {
	float trazena_cijena;
	int index_pronadenog;
	system("cls");
	printf("Unesi cijenu trazenog artikla: ");
	scanf(" %f", &trazena_cijena);
	index_pronadenog = trazenje_cijene(artikli, broj_artikala, trazena_cijena);
	if (index_pronadenog == -1) {
		printf("\nArtikl sa cijenom %.2f ne postoji!", trazena_cijena);
		return -1;
	}
	else {
		ispis_pronadenog(artikli, index_pronadenog);
		radnje_pretrazivanja(artikli, broj_artikala, index_pronadenog);
		return index_pronadenog;
	}
}

//odabir za pretraga po kolicini
int pretraga_po_kolicini(ARTIKL* artikli, int broj_artikala) {
	int trazena_kolicina, index_pronadenog;
	system("cls");
	printf("Unesi kolicinu trazenog artikla: ");
	scanf(" %d", &trazena_kolicina);
	index_pronadenog = trazenje_kolicine(artikli, broj_artikala, trazena_kolicina);
	if (index_pronadenog == -1) {
		printf("\nArtikl sa kolicinom %d ne postoji!", trazena_kolicina);
		return -1;
	}
	else {
		ispis_pronadenog(artikli, index_pronadenog);
		radnje_pretrazivanja(artikli, broj_artikala, index_pronadenog);
		return index_pronadenog;
	}
}

//odabir za pretrazivenje po sifri
int pretrazivanje_po_sifri(ARTIKL* artikli, int broj_artikala) {
	int trazena_sifra, index_pronadenog;
	system("cls");
	printf("Unesi sifru trazenog artikla: ");
	scanf(" %d", &trazena_sifra);
	index_pronadenog = trazenje_sifre(artikli, broj_artikala, trazena_sifra);
	if (index_pronadenog == -1) {
		printf("\nArtikl sa sifrom %d ne postoji!", trazena_sifra);
		return -1;
	}
	else {
		ispis_pronadenog(artikli, index_pronadenog);
		radnje_pretrazivanja(artikli, broj_artikala, index_pronadenog);
		return index_pronadenog;
	}
}

// odabir za pretrazivanje po imenu
int pretrazivanje_po_imenu(ARTIKL* artikli, int broj_artikala) {
	char trazeno_ime[50];
	int index_pronadenog;
	system("cls");
	printf("Unesi ime trazenog artikla: ");
	scanf(" %49[^\n]", trazeno_ime);
	index_pronadenog = trazenje_imena(artikli, broj_artikala, trazeno_ime);
	if (index_pronadenog == -1) {
		printf("\nArtikl sa imenom %s ne postoji!", trazeno_ime);
		return -1;
	}
	else {
		ispis_pronadenog(artikli, index_pronadenog);
		radnje_pretrazivanja(artikli, broj_artikala, index_pronadenog);
		return index_pronadenog;
	}
}

//ispis i odabir u glavnom izborniku
char glavni_izbornik() {
	char odabir;
	printf("Izaberite broj ispred zeljene radnje!\n");
	printf("1. Unos robe iznova\n");
	printf("2. Dodavanje robe\n");
	printf("3. Sortiranje robe\n");
	printf("4. Pretrazivanje robe\n"); // kad pretraži može promijeniti stanje ili obrisati
	printf("5. Brisanje artikla\n");
	printf("6. Upis trenutnog stanja u drugu datoteku (npr. txt)\n");
	printf("7. Stanje skladista\n");
	printf("8. Odjava\n");

	do {
		odabir = getch();
		if (odabir < '1' || odabir > '8') {
			printf("\nPogresan odabir! Pokusajte ponovo: ");
		}
	} while (odabir < '1' || odabir > '8');

	return odabir;
}

//odabir 3 u glavnom izorniku - pretraživanje robe 
char pretrazivanje_robe_izbornik() {
	char odabir;
	system("cls");
	printf("Izaberite nacin pretrazivanja:\n");
	printf("1. Pretrazivanje po imenu\n");
	printf("2. Pretrazivanje po sifri\n");
	printf("3. Pretrazivanje po cijeni\n");
	printf("4. Pretrazivanje po kolicini\n");
	do {
		odabir = getch();
		if (odabir < '1' || odabir > '4') {
			printf("\nGreska pri unosu! Pokusajte ponovo: ");
		}
	} while (odabir < '1' || odabir > '4');

	return odabir;
}

//odabir 1 u glavnom izorniku- unos robe iznova u bin atoteku skladista
void unos_robe_iznova() {
	ARTIKL* artikli = NULL;
	int broj_artikala;
	system("cls");
	printf("Unesi broj artikala: ");
	do {
		scanf("%d", &broj_artikala);
		if (broj_artikala < 1) printf("\nGreska pri unosu broja artikla!\nPOKUSAJTE PONOVO\n");
	} while (broj_artikala < 1);

	artikli = zauzimanje_memorije(broj_artikala);
	if (artikli == NULL) {
		printf("\nGreska pri zauzimanju memorije!");
	}
	else {

		unos_u_strukture(artikli, 0, broj_artikala);

		if (upis_u_datoteku(artikli, broj_artikala) == -1) {
			printf("\nDoslo je do greske!");
		}
		else {
			printf("\nPodaci uspjesno upisani u datoteku!");
		}
		free(artikli);
		artikli = NULL;
	}

	return;
}

//odabir 2 u glavnom izorniku - dodavanje robe
void dodavanje_robe() {
	system("cls");
	FILE* binarna = NULL;
	ARTIKL* artikli = NULL;
	int broj_artikala, dodaj;
	binarna = fopen("skladiste.bin", "rb");
	if (binarna == NULL) {
		printf("\nDoslo je do pogreske!");
	}
	else {
		printf("\nKoliko artikala zelite dodati?  ");
		scanf(" %d", &dodaj);
		fread(&broj_artikala, sizeof(int), 1, binarna);
		artikli = zauzimanje_memorije(broj_artikala + dodaj);
		if (artikli == NULL) {
			printf("\nGreska pri zauzimanju memorije!");
		}
		else {
			fread(artikli, sizeof(ARTIKL), broj_artikala, binarna);
			fclose(binarna);
			unos_u_strukture(artikli, broj_artikala, broj_artikala + dodaj);
			broj_artikala += dodaj;
			binarna = fopen("skladiste.bin", "wb");
			if (binarna == NULL) {
				printf("\nDoslo je do greske!");
			}
			else {
				fwrite(&broj_artikala, sizeof(int), 1, binarna);
				fwrite(artikli, sizeof(ARTIKL), broj_artikala, binarna);
				fclose(binarna);
				printf("\nPodaci uspjesno upisani u datoteku!");
			}
			free(artikli);
			artikli = NULL;
		}
	}

	return;
}

// odabir 3 u glavnom izbornuku - pretraživanje robe
void pretrazivanje_robe(int odabir) {
	int broj_artikala;
	ARTIKL* artikli = NULL;
	FILE* binarna = NULL;
	binarna = fopen("skladiste.bin", "rb");
	if (binarna == NULL) {
		printf("\nDoslo je do pogreske!");
	}
	else {
		fread(&broj_artikala, sizeof(int), 1, binarna);
		artikli = zauzimanje_memorije(broj_artikala);
		if (artikli == NULL) {
			printf("\nGreska pri zauzimanju memorije!");
		}
		else {
			fread(artikli, sizeof(ARTIKL), broj_artikala, binarna);
			fclose(binarna);

			switch (odabir) {
			case '1': //Pretrazivanje po imenu

				pretrazivanje_po_imenu(artikli, broj_artikala);

				break;

			case '2': //Pretrazivanje po sifri

				pretrazivanje_po_sifri(artikli, broj_artikala);

				break;

			case '3': //Pretrazivanje po cijeni

				pretrazivanje_po_cijeni(artikli, broj_artikala);

				break;

			case '4': //Pretrazivanje po kolicini

				pretraga_po_kolicini(artikli, broj_artikala);

				break;
			}
			free(artikli);
			artikli = NULL;
		}
	}

	return;
}

//odabir 3 u glavnom izborniku - sortiranje
void odabir_sortiranje() {
	int broj_artikala;
	ARTIKL* artikli = NULL;
	FILE* binarna = NULL;
	binarna = fopen("skladiste.bin", "r");
	if (binarna == NULL) {
		printf("\nDoslo je do greske!");
	}
	else {
		fread(&broj_artikala, sizeof(int), 1, binarna);
		artikli = zauzimanje_memorije(broj_artikala);
		if (artikli == NULL) {
			printf("\nGreska pri zauzimanju memorije!");
		}
		else {
			fread(artikli, sizeof(ARTIKL), broj_artikala, binarna);
			fclose(binarna);
			sortiranje(artikli, broj_artikala);
			upis_u_datoteku(artikli, broj_artikala);
			free(artikli);
			artikli = NULL;
		}
	}

	return;
}

//cekanje zbog krivo unesenih korisnièkih podataka
void cekanje_zbog_krivih_podataka(int cekaj) { // vrijeme u sekundama
	time_t t1, t2;
	t1 = time(NULL);
	system("cls");
	while (1) {
		t2 = time(NULL);
		printf("Previse pokusaja!");
		printf("\nPricekajte %d sekundi za nastavak... %g", cekaj, cekaj - difftime(t2, t1));
		system("cls");
		if (difftime(t2, t1) == cekaj) {
			break;
		}
	}

	return;
}

//kad se pretraži artikl i želi ga se obrisati
int brisanje(int index_za_brisanje, ARTIKL* artikli, int broj_artikala) {
	FILE* binarna = NULL;
	int pom = broj_artikala;
	binarna = fopen("skladiste.bin", "wb");
	if (binarna == NULL) {
		printf("\nDoslo je do pogreske!");
		return -1;
	}
	else {
		upis_u_datoteku(artikli, broj_artikala);
		broj_artikala--;
		fwrite(&broj_artikala, 1, sizeof(int), binarna);
		for (int i = 0; i < pom; i++) {
			if (i == index_za_brisanje) {
				continue;
			}
			else {
				fwrite((artikli + i), sizeof(ARTIKL), 1, binarna);
			}
		}
		fclose(binarna);
		printf("\nArtikl uspjesno obrisan!");
		return 0;
	}
}