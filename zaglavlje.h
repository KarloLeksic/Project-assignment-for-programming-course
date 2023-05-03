#ifndef HEAD_H
#define HEAD_H

//struktura za artikl
typedef struct artikl {
	char ime[50];
	unsigned int sifra;
	unsigned int kolicina;
	float cijena;
}ARTIKL;

ARTIKL* zauzimanje_memorije(int broj_artikala); //dinamicki zauzimanje memorije za polje artikla

void unos_u_strukture(ARTIKL*, int, int); //funkcija za unasanje podataka u strukture

void ispis_na_ekran(ARTIKL*, int); //funkcija za ispis na ekran

void upis_u_txt_datoteku(ARTIKL*, int); //upis u txt datoteku

void selection_sort_ime_u(ARTIKL*, int); //sortiranje strukturi po imenu	 ->  (samo po prvom slovu) - uzlazno

void selection_sort_ime_s(ARTIKL*, int); //sortiranje strukturi po imenu	 ->  (samo po prvom slovu) - silazno

void selection_sort_kolicina_u(ARTIKL*, int); //sortiranje strukturi po kolicini  -> od najmanjeg do najveceg - uzlazno

void selection_sort_kolicina_s(ARTIKL*, int); //sortiranje strukturi po kolicini	-> od najmanjeg do najveceg - silazno

void sortiranje(ARTIKL*, int); //funkcija za sortiranje

int unos_username_i_password(char*); //traziti korisnicko ime, sifru i jednokratnu lozinku -> vraca 1 za tocno unesene podatke

int dozvola(char*); //dozvola vraca 1 ako je od bilo kojeg pokusaja uneseno dobro username, sifra i jednokratna lozinka

char* generiranje_jednokratne_lozinke(); //funkcija za generiranje jednokratne lozinke

int upisivanje_jednokratne_lozinke_u_datoteku(char*); //upisivanje jednokratne lozinke u datoteku

int trazenje_imena(ARTIKL*, int, char*); //trazenje po imenu

int trazenje_sifre(ARTIKL*, int, int); //trazenje po sifri

int trazenje_cijene(ARTIKL*, int, float); //trazenje po cijeni

int trazenje_kolicine(ARTIKL*, int, int); //trazenje po kolicini

int upis_u_datoteku(ARTIKL*, int); //upis u binarnu datoteku iznova

int radnje_pretrazivanja(ARTIKL*, int, int); //radnje koje zelimo ako nademo artikl

int upis_u_drugu_datoteku(ARTIKL*); //odabir za upis u drugu datoteku

int stanje_skladista(); //odabir 6 u glavnom izorniku - stanje skladista

int pretrazivanje_po_cijeni(ARTIKL*, int); //odabir za pretrazivanje po cijeni

int pretraga_po_kolicini(ARTIKL*, int); //odabir za pretraga po kolicini

int pretrazivanje_po_sifri(ARTIKL*, int); //odabir za pretrazivenje po sifri

int pretrazivanje_po_imenu(ARTIKL*, int); // odabir za pretrazivanje po imenu

char glavni_izbornik(); //ispis i odabir u glavnom izborniku

char pretrazivanje_robe_izbornik(); //odabir 3 u glavnom izorniku - pretraživanje robe 

void unos_robe_iznova(); //odabir 1 u glavnom izorniku- unos robe iznova u bin atoteku skladista

void dodavanje_robe(); //odabir 2 u glavnom izorniku - dodavanje robe

void pretrazivanje_robe(int); // odabir 3 u glavnom izbornuku - pretraživanje robe

void cekanje_zbog_krivih_podataka(int); //cekanje zbog krivo unesenih korisnièkih podataka

void odabir_sortiranje(); //odabir 3 u glavnom izborniku - sortiranje

int brisanje(int, ARTIKL*, int); //brisanje artikala na zeljenom indexu

void selection_sort_cijena_u(ARTIKL*, int); //sortiranje strukturi po cijeni  -> od najmanjeg do najveceg - uzlazno

void selection_sort_cijena_s(ARTIKL*, int); //sortiranje strukturi po cijeni  -> od najmanjeg do najveceg - silazno

#endif // HEAD_H