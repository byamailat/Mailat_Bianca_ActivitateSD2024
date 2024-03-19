#include <stdio.h>
#include <malloc.h>


//LISTE
//lista=str de data liniara, omogena, elementele sunt stocate la adrese diferite 
//adresa primului nod este capul listei


typedef struct Biblioteca Biblioteca;
typedef struct Nod Nod;


struct Biblioteca {
	char* nume;
	int nrCarti;
	int nrCititori;
};

struct Nod {
	Biblioteca info;
	Nod* next;
};

Biblioteca initializare(const char* nume, int nrCarti, int nrCititori) {
	Biblioteca b; //cream ob
	b.nume = (char*)malloc(sizeof(char) * (strlen(nume) + 1));
	strcpy(b.nume, nume);
	b.nrCarti = nrCarti;
	b.nrCititori = nrCititori;
	return b;
}

Nod* inserareInceput(Nod* cap, Biblioteca b) {
	Nod* nou = (Nod*)malloc(sizeof(Nod));
	nou->info = initializare(b.nume, b.nrCarti, b.nrCititori); //deep copy
	//adresa urm nod il setam (adica capul)
	nou->next = cap;
	return nou;
}

void afisareLista(Nod* cap) {
	while (cap != NULL) //il parcurgem pana la capat adica pana la null
	{
		//procesare, il parcurgem=orice parcurgere din listele noastre asa le vom face
		printf("Biblioteca  %s are %d carti si %d cititori.\n", cap->info.nume, cap->info.nrCarti, cap->info.nrCititori);
		cap = cap->next;

	}
}

//unde avem cele mai multe carti per cititor
char* getBibliotecaNrCartiPerCititor(Nod* cap) {
	//o var unde sa stocam media maxima
	float max = 0;
	char* nume_aux = NULL;

	while (cap) {

		//proceasarea, verificam daca
		if (cap->info.nrCarti / cap->info.nrCititori > max) {
			max = cap->info.nrCarti / cap->info.nrCititori;
			nume_aux = cap->info.nume;
		}
		cap = cap->next;
	}
	char* nume = (char*)malloc(sizeof(char) * (strlen(nume_aux) + 1));
	strcpy(nume, nume_aux);
	return nume;
}
void InserareLaSfarsit(Nod** cap, Biblioteca b) {
	Nod* sfarsit = (Nod*)malloc(sizeof(Nod)); //ii aloc memorie
	//creez un nod:
	//deep copy sa copiem toate elem si dupa sa alocam iar spatiu si tot asa
	//ii dam parametrii din biblioteca noastra b

	sfarsit->info = initializare(b.nume, b.nrCarti, b.nrCititori);
	sfarsit->next = NULL;
	if ((*cap) != NULL) //daca exista cap parcurgem pana ne oprim de ult nod
	{
		Nod* capA = (*cap);
		while (capA->next != NULL) {
			capA = capA->next;
		}
		//cand ajunge la null vr sa imi pointeze la alt nod si asa ca am adaugat un nou nod la sfarsit:
		capA->next = sfarsit;
	}
	else {
		*cap = sfarsit;

	}
}
void stergeLista(Nod** cap) {
	while ((*cap) != NULL) {
		free((*cap)->info.nume);
		Nod* copie = *cap;
		*cap = (*cap)->next;

		free(copie);
	}
}
void main() {
	//declaram o lista
	//o lista o identif prin adresa primului nod si pt ca la inceput n avem niciun elemn il initializam pe acel nod cu null
	Nod* cap = NULL;
	Biblioteca b1 = initializare("Mihai Eminescu", 150, 20);
	cap = inserareInceput(cap, b1); //in loc sa trimit tot blocul trimit adresa ..?
	Biblioteca b2 = initializare("Ioan Slavici", 200, 30);
	cap = inserareInceput(cap, b2); //in loc sa trimit tot blocul trimit adresa ..?
	Biblioteca b3 = initializare("Tudor Arghezi", 100, 15);
	cap = inserareInceput(cap, b3); //in loc sa trimit tot blocul trimit adresa ..?


	afisareLista(cap);
	char* numeDeAfisat = getBibliotecaNrCartiPerCititor(cap);
	printf("Biblioteca cu media maxima: %s \n", getBibliotecaNrCartiPerCititor(cap));
	free(numeDeAfisat);
	Biblioteca b4 = initializare("Radu Tudoran", 100, 15);
	InserareLaSfarsit(&cap, b4);
	afisareLista(cap);
	stergeLista(&cap);
	afisareLista(cap);

	free(b1.nume); //pt ca avem deep
	free(b2.nume);
	free(b3.nume);
	free(b4.nume);
}