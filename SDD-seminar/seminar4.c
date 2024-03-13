#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <malloc.h>


struct Aeroport
{
	int id;
	char* nume;
	int nrTerminale;
};

struct Aeroport* adaugaAeroport(struct Aeroport* vector, struct Aeroport aeroport, int* dimensiune)
{
	struct Aeroport* copie = (struct Aeroport*)malloc(sizeof(struct Aeroport) * ((*dimensiune) + 1));

	copie[(*dimensiune)] = aeroport;

	for (int i = 0; i < (*dimensiune); i++)
	{
		copie[i] = vector[i];
	}
	free(vector);

	(*dimensiune)++;
	return copie;
}


void citireMatriceFisier(const char* numeFisier, int* nrAeroporturiLinie, int nrClustere,
	struct Aeroport** aeroporturi)
{
	FILE* f = fopen(numeFisier, "r");

	if (f != NULL)
	{
		char buffer[100];
		while (fgets(buffer, 99, f) != NULL)//returneaza un pointer la char, adresa la care a citit
		{
			struct Aeroport aeroport;
			char delimitator[] = ",\n";
			char* token = strtok(buffer, delimitator);
			aeroport.id = atoi(token); //ascii to integer
			token = strtok(NULL, delimitator);
			aeroport.nume = malloc(sizeof(char) * (strlen(token) + 1));
			strcpy(aeroport.nume, token);

			token = strtok(NULL, delimitator);
			aeroport.nrTerminale = atoi(token);
			int poz = aeroport.nrTerminale % 2 != 0;


			aeroporturi[poz] = adaugaAeroport(aeroporturi[poz], aeroport, &(nrAeroporturiLinie[poz]));

		}
		fclose(f);
	}
}

void afisareAeroport(struct Aeroport* aeroport)
{
	printf("%d.%s are %d terminale.\t", aeroport->id, aeroport->nume, aeroport->nrTerminale);
	// \t = \tab
}
void afisareVectorAeroporturi(struct Aeroport* aeroporturi, int dim)
{
	printf("Afisare vector: \n");

	for (int i = 0; i < dim; i++)
	{
		afisareAeroport(&aeroporturi[i]);
	}
}

void afisareMatrice(struct Aeroport** matrice, int nrClustere, int* nrColoane)
{
	for (int i = 0; i < nrClustere; i++)
	{
		for (int j = 0; j < nrColoane[i]; j++)
		{
			afisareAeroport(&matrice[i][j]);
		}
		printf("\n");
	}
}

void dezalocareVector(struct Aeroport** aeroporturi, int* dim)
{
	for (int i = 0; i < (*dim); i++)
	{
		free((*aeroporturi)[i].nume);
	}
	free(*aeroporturi);
	(*aeroporturi) = NULL;
	(*dim) = 0;
}

void main()
{
	struct Aeroport** aeroporturi;
	int nrLinii = 2;
	int* nrColoane = (int*)malloc(sizeof(int) * nrLinii);

	aeroporturi = (struct Aeroport**)malloc(sizeof(struct Aeroport) * nrLinii);

	for (int i = 0; i < nrLinii; i++)
	{
		nrColoane[i] = 0;
		aeroporturi[i] = NULL;

	}

	citireMatriceFisier("aeroporturi.txt", nrColoane, nrLinii, aeroporturi);
	afisareMatrice(aeroporturi, nrLinii, nrColoane);
}