#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>
#include <stdlib.h>


typedef struct Kartica {
	char brKartice[10];
	int pin;
}Kartica;

typedef struct Racun {
	char brRacuna[15];
	double stanje;
	Kartica kartica;
}Racun;

typedef struct Korisnik {
	char ime[15];
	char prezime[15];
	Racun racun;
}Korisnik;

void upisUFajl(FILE* fajl, Korisnik* lista, int brojKorisnika) {
	fajl = fopen("korisnici.txt", "w");

	for (int i = 0; i < brojKorisnika; i++) {
		if (i == brojKorisnika - 1)
		{
			fprintf(fajl, "%s*%d*%s*%.2lf*%s*%s", lista[i].racun.kartica.brKartice, lista[i].racun.kartica.pin, lista[i].racun.brRacuna, lista[i].racun.stanje, lista[i].ime, lista[i].prezime);
		}
		else {
			fprintf(fajl, "%s*%d*%s*%.2lf*%s*%s\n", lista[i].racun.kartica.brKartice, lista[i].racun.kartica.pin, lista[i].racun.brRacuna, lista[i].racun.stanje, lista[i].ime, lista[i].prezime);
		}
	}
	fclose(fajl);
}

void ucitajIzFajla(Korisnik* lista, FILE* fajl) {

	int firstCounter = 0;
	while (!feof(fajl)) {
		char podaci[200];
		fgets(podaci, 200, fajl);

		Kartica kartica;
		Racun racun;
		Korisnik korisnik;
		int secondCounter = 0;
		char* token = strtok(podaci, "*");

		while (token != NULL) {
			if (secondCounter == 0) {
				strcpy(kartica.brKartice, token);
				secondCounter++;
			}
			else if (secondCounter == 1) {
				kartica.pin = atoi(token);
				secondCounter++;
			}
			else if (secondCounter == 2) {
				strcpy(racun.brRacuna, token);
				secondCounter++;
			}
			else if (secondCounter == 3) {
				racun.stanje = atof(token);
				secondCounter++;
			}
			else if (secondCounter == 4) {
				strcpy(korisnik.ime, token);
				secondCounter++;
			}
			else {
				if (token[strlen(token) - 1] == '\n') {
					token[strlen(token) - 1] = '\0';
				}
				strcpy(korisnik.prezime, token);
				secondCounter = 0;
			}
			token = strtok(NULL, "*");
		}
		racun.kartica = kartica;
		korisnik.racun = racun;
		lista[firstCounter] = korisnik;
		firstCounter++;
	}
}

int brKorisnika(FILE* fajl) {
	int brojac = 0;
	while (!feof(fajl)) {
		char podaci[200];
		fgets(podaci, 200, fajl);
		brojac++;
	}
	return brojac;
}

int main() {
	int pinBrPokusaja = 0;
	int pin;
	int opcije;
	int drugaOpcija;
	int izbor;
	int iznos;
	int podizanjeIznos;
	int depozitIznos;
	int racun;
	FILE* fajl = fopen("korisnici.txt", "r");
	int brojKorisnika = brKorisnika(fajl);
	int maxBrojPokusaja = 3;
	fclose(fajl);
	fajl = fopen("korisnici.txt", "r");

	Korisnik* kNiz = (Korisnik*)calloc(brojKorisnika, sizeof(Korisnik));
	ucitajIzFajla(kNiz, fajl);
	fclose(fajl);

	Korisnik* korisnik = NULL;

	printf("***************   Dobrodosli!    ***************\n");

	printf("Unesite svoj PIN: \n");
	scanf("%d", &pin);


	while (pinBrPokusaja < maxBrojPokusaja)
	{
		for (int i = 0; i < brojKorisnika; i++) {
			if (pin == kNiz[i].racun.kartica.pin) {


				pinBrPokusaja = 3;
				printf("\n Ime: %s\n Prezime: %s\n Broj racuna: %s\n Broj kartice: %s\n", kNiz[i].ime, kNiz[i].prezime, kNiz[i].racun.brRacuna, kNiz[i].racun.kartica.brKartice);

				printf("\nDa li zelite racun: \n 1(DA)/2(NE) \n");
				scanf("%d", &racun);
				printf("Izaberite sledece:\n");
				printf("1. Brz Kes\n2. Podigni novac\n3. Deponuj\n4. Proveri stanje na racunu\n5. Izbaci karticu \n");
				printf("Unesi opciju: ");
				scanf("%d", &opcije);
				while (opcije <= 5)
				{
					switch (opcije)
					{
					case 1:
						//Brz kes
						printf("\n**************************** ");
						printf("\n1. 1000 dinara\n2. 2000 dinara\n3. 5000 dinara\n4. 10 000 dinara\n5. Izadji \n");
						printf("Izaberi iznos: ");
						scanf("%d", &izbor);

						switch (izbor)
						{
						case 1:
							iznos = 1000;
							if (kNiz[i].racun.stanje < iznos) {
								printf("Nemate dovoljno novca za ovu trasnakciju! \n");
							}
							else {
								printf("Uspesno ste podigli %d dinara\n", iznos);
								kNiz[i].racun.stanje = kNiz[i].racun.stanje - iznos;

							}
							break;
						case 2:
							iznos = 2000;
							if (kNiz[i].racun.stanje < iznos) {
								printf("Nemate dovoljno novca za ovu trasnakciju! \n");
							}
							else {
								printf("Uspesno ste podigli %d dinara\n", iznos);
								kNiz[i].racun.stanje = kNiz[i].racun.stanje - iznos;

							}
							break;
						case 3:
							iznos = 5000;
							if (kNiz[i].racun.stanje < iznos) {
								printf("Nemate dovoljno novca za ovu trasnakciju! \n");
							}
							else {
								printf("Uspesno ste podigli %d dinara\n", iznos);
								kNiz[i].racun.stanje = kNiz[i].racun.stanje - iznos;

							}
							break;

						case 4:
							iznos = 10000;
							if (kNiz[i].racun.stanje < iznos) {
								printf("Nemate dovoljno novca za ovu trasnakciju! \n");
							}
							else {
								printf("Uspesno ste podigli %d dinara\n", iznos);
								kNiz[i].racun.stanje = kNiz[i].racun.stanje - iznos;

							}
							break;

						case 5:
							break;
						}
						break;

					case 2:
						//Podizanje novca
						printf("****************************\n ");
						printf("Unesite iznos novca koji zelite da podignete: \n ");
						scanf("%d", &podizanjeIznos);
						if (kNiz[i].racun.stanje < podizanjeIznos) {
							printf("Nemate dovoljno novca za ovu transkacjiu! \n");
						}
						else {
							kNiz[i].racun.stanje -= podizanjeIznos;
							printf("Uspesno ste podigli! \n");
						}
						break;

					case 3:
						//depozit
						printf("****************************\n");
						printf("Unesite iznos novca koji zelite da deponujete:\n ");
						scanf("%d", &depozitIznos);
						kNiz[i].racun.stanje += depozitIznos;
						break;

					case 4:
						//provera stanja
						printf("****************************\n ");
						printf("Vase trenutno stanje na racunu je: %.2lf\n", kNiz[i].racun.stanje);
						break;

						//izbacivanje kartice
					case 5:
						printf("****************************\n ");
						drugaOpcija == 2;
						printf("Kartica je uspesno izbacena! \n");
						
						exit(0);
					default:
						printf("Greska! Pokusatje ponovo! \n");
						break;

					}

					printf("\nDa li zelite jos jednu transakciju: 1(DA)/2(NE) \n");
					scanf("%d", &drugaOpcija);
					if (drugaOpcija == 1)
					{
						printf("*********  Nova Transakcija  *********\n");
						printf("1. Brz Kes\n2. Podignite novac\n3. Deponujte novac\n4. Proveri stanje na racunu\n5. Izbaci karticu \n");
						printf("Unesite opciju: ");
						scanf("%d", &opcije);
					}

					else
					{
						opcije = 5;
						upisUFajl(fajl, kNiz, brojKorisnika);
						printf("Hvala na upotrebi!\n");
						exit(0);
					}
				}

			}
		}
		pinBrPokusaja++;
		if (pinBrPokusaja == maxBrojPokusaja) {
			printf("Zao mi je, ne mozete nastaviti, vise od 3 puta ste probali! \n");
			exit(0);
		}
		else {
			printf("Neispravan PIN, pokusajte ponovo!\n");
			scanf("%d", &pin);
		}
	}
	free(kNiz);
	return 0;
}