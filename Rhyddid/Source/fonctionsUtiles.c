#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>

#include "fonctionsUtiles.h"
#include "couleur.h"
#include "effacer.h"

void viderBuffer(void)
{
	int c;
		    
	c = 0;
	    
	while(c != '\n' && c != EOF)		
	        c = getchar();
}

unsigned int hasard(const unsigned int min, const unsigned int max)
{
	return (rand() % (max - min + 1)) + min;
}

void erreur(const char *message)
{
	printf("ERREUR : %s\n", message);
	exit(EXIT_FAILURE);
}

FILE *ouvrirFichier(const char *chemin, const char *mode, const char *messageErreur)
{
	FILE *testFichier;
	
	testFichier = NULL;
	testFichier = fopen(chemin, mode);
	
	if(testFichier == NULL)
	{
		printf("ouvrirFichier : \n");
		erreur(messageErreur);
	}
	
	return testFichier;
}

void fermerFichier(FILE *fichier, const char *messageErreur)
{
	if(fclose(fichier) == EOF)
	{
		printf("fermerFichier : \n");
		erreur(messageErreur);
	}
}

void lireEtAfficher(const char *chemin)
{
	FILE *fichier;
	char buffer[TAILLE_MAX];
	
	fichier = ouvrirFichier(chemin, "r",
	"fonction \"lireEtAfficher\"");
		
	while(!feof(fichier))
	{
		fgets(buffer, TAILLE_MAX, fichier);
		
		if(!feof(fichier))
			printf("%s", buffer);
	}

	fermerFichier(fichier,
	"fonction \"lireEtAfficher\"");
}

unsigned int lire(FILE *flux, char ligne[TAILLE_MAX])
{
	compteur longueur;
	
	if(fgets(ligne, TAILLE_MAX, flux) == NULL)
		return 0;
			
	for(longueur = 0; ligne[longueur] != '\n' && ligne[longueur] != '\0'; ++longueur)
		;
		
	ligne[longueur] = '\0';	

	return 1;
}

void appuyezEntree(const char *texte)
{
	printf("%s\n", texte);
	getchar();
}

void titre(const char *s, const unsigned int typeCouleur)
{
	effacer();
	
	couleur(typeCouleur);
	printf("\t\t\t\t%s\n\n", s);
	couleur(BLANC);
}

int choisirMenu(const unsigned int maximum)
{
	int choixJoueur;
	unsigned int compteurErreur;

	compteurErreur = 0;

	do
	{
		if(compteurErreur > 0)
		{
			printf("Veuillez entrer un nombre correct !\n");
			viderBuffer();
		}

		printf("> ");
		scanf("%d", &choixJoueur);

		++compteurErreur;

	} while(choixJoueur < REVENIR_ARRIERE && choixJoueur > maximum);

	viderBuffer();

	return choixJoueur;
}

unsigned int choisirMenuSansOperationPossible(const unsigned int maximum)
{
	int choixJoueur;
	unsigned int compteurErreur;

	compteurErreur = 0;

	do
	{
		if(choixJoueur == REVENIR_ARRIERE || (choixJoueur == QUITTER && compteurErreur > 0))
		{
			printf("Operation impossible !\n");
			viderBuffer();
		}
		else if(compteurErreur > 0)
		{
			printf("Veuillez entrer un nombre correct !\n");
			viderBuffer();
		}

		printf("> ");
		scanf("%d", &choixJoueur);

		++compteurErreur;

	}while(choixJoueur < 1 || choixJoueur > maximum);

	viderBuffer();

	return choixJoueur;
}

void separationTexte(void)
{
	compteur indexSeparation;

	putchar('\n');

	for(indexSeparation = 0; indexSeparation < NB_SEPARATION; ++indexSeparation)
		putchar('-');

	printf("\n\n");
}

void attendre(const float temps)
{
	clock_t arrivee;
	
	arrivee = clock() + (clock_t)(temps * CLOCKS_PER_SEC);
	
	while(clock() < arrivee)
		;
}

unsigned int demanderConfirmation(const char *message, const unsigned int separation)
{
	int choixJoueur;
	unsigned int compteurErreur;

	compteurErreur = 0;

	if(separation == OUI)
		separationTexte();

	do
	{
		if(compteurErreur > 0)
		{
			printf("Veuillez entrer 0 pour refuser et 1 pour accepter !\n");
			viderBuffer();
		}

		printf("%s\n", message);
		printf("> ");
		scanf("%d", &choixJoueur);

		++compteurErreur;

	} while(choixJoueur != NON && choixJoueur != OUI);

	viderBuffer();

	return choixJoueur;
}

unsigned int tirerChance(const unsigned int min, const unsigned int max)
{
	unsigned int chance;

	chance = hasard(min, max);

	return chance == 1;
}

unsigned int estAportee(const unsigned int distanceLig, const unsigned int distanceCol, 
	const unsigned int portee)
{ 
	int distance;

	distance = sqrt(distanceLig * distanceLig + distanceCol * distanceCol);

	return distance <= portee;
}
