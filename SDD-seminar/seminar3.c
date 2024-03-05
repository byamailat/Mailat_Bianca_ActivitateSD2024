#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include<malloc.h>
#define _CRT_SECURE_NO_WARNINGS


//FISIERE//

struct Aeroport {
	int id;
	char* nume;
	int nrTerminale;
};


struct Aeroport* citireFisier(const char* numeFisier,int* nrAeroporturi)  {
	struct Aeroport* vectorAeroporturi;
	vectorAeroporturi = NULL;

	//deschidem fisierul
	FILE* f = fopen(numeFisier, "r"); 

	//vede daca fisierul a fost deschis cu succes daca e dif de null adica
	if (f != NULL) {
		(*nrAeroporturi) = 0;
		//citim
		//fgets citeste doar pana la un anumit caracter/la fel si fread
		//fgets(linia pe care o citimi, cate caractere,streamul de pe  care citim)
		char buffer[100]; //alocam static
		while (fgets(buffer, 99, f) != NULL){
			struct Aeroport aeroport;
			//bufferul e efectiv linia din fisier text
			char delimitator=",\n" //nu are ptr ca sa il putem initializa direct pe stiva
			char* token=strtok(buffer, delimitator); //e un separator 
			//declaram o variabila ca sa avem aceste delimitatoare/separatoare ca sa nu mai modificam peste tot in cazul in care e nevoie
			aeroport.id = atoi(token);
			//dezalocam strtok
			//strtok cauta apelul anterior si unde a lasat cursorul si va marca cu null unde a ramas, si noi plecam de la acel null
			token = strtok(NULL, delimitator);
			aeroport.nume = malloc(sizeof(char) * (strlen(token) + 1));
			strcpy(aeroport.nume, token);
			token = strtok(NULL, delimitator);
			aeroport.nrTerminale = atoi(token);


			vectorAeroporturi = adaugaAeroport(vectorAeroporturi, nrAeroporturi);

			

		}
		fclose(f);//inchidem fisierul
	}
	return vectorAeroporturi;
}



void afisareAeroport(struct Aeroport* aeroport) {
	printf("Aeroportul cu id: &s are %d terminale\n", aeroport->id, aeroport->id,aeroport->nume,aeroport->nrTerminale); //prin sageata ca fiind ptr trb si deferentiere
}
void afisareVectorAeroporturi(struct Aeroport* aeroporturi, int dim) {
	printf("Afisare vector:\n");
	for (int i = 0; i < dim; i++)
	{
		afisareAeroport(&aeroporturi[i]);
	}
}

//citire end//
//adaugare start//
struct Aeroport* adaugaAeroport(struct Aeroport* vector, struct Aeroport aeroport, int* dimensiune) //dimensiunea o dam prin 
	//ptr pt ca o vom incrementa
{
	//alocam o noua zona de mem pt vector
	struct Aeroport* copie = (struct Aeroport*)malloc(sizeof(struct Aeroport) * ((*dimensiune) + 1));

	//alocam aerportul nou pe ultima pozitie
	copie[(*dimensiune)] = aeroport;

	//for ca sa parcurgem vect initial si sa cop elem respective in noul ...
	for (int i = 0; i < (*dimensiune); i++) {
		copie[i] = vector[i];
	}
	if (vector = !NULL) {
		free(vector);
	}
	(*dimensiune)++; //crestem dim
	//iniante sa stergem un vect trb mai intai sa l dezalocam
	return copie;
}


//sa mi returneze un aeroport dupa un id dat
//struct Aeroport idCautat(struct Aeroport* aeroporturi, int dim, int idCautat) {
//	for (int i = 0; i < dim; i++) {
//		if (aeroporturi[i].id == idCautat) {
//			return aeroporturi[i];
//		}
//		
//	}
//	struct Aeroport aeroport;
//	aeroport.id = -1;
//
//}
//
//void dezalocareVector(struct Aeroport )//



void main(){
	int dimensiune=3;
	struct Aeroport* aeroporturi = NULL; //ca n avem niciun aeroport momentan
	aeroporturi=citireFisier("Aeroporturi.txt", &dimensiune);

	afisareVectorAeroporturi(aeroporturi, dimensiune);


}