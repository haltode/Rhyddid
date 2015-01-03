#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>

#include "fonctionsUtiles.h"
#include "couleur.h"
#include "effacer.h"

/* Fonction qui vide le buffer */
void viderBuffer(void)
{
	int c;
		    
	c = 0;
	    
	while(c != '\n' && c != EOF)		
	        c = getchar();
}

/* Fonction qui tire un nombre en min et max au hasard */
unsigned int hasard(const unsigned int min, const unsigned int max)
{
	return (rand() % (max - min + 1)) + min;
}

/* Fonction qui indique le message donne en parametre et quitte le programme */
void erreur(const char *message)
{
	printf("ERREUR : %s\n", message);
	exit(EXIT_FAILURE);
}

/* Fonction qui ouvre un fichier donne en paremetre dans le mode donne en parametre de 
maniere securisee et retourne un pointeur sur le fichier */
FILE *ouvrirFichier(const char *chemin, const char *mode, const char *messageErreur)
{
	/* On ouvre le fichier donne en parametre, on teste le retour et on gere l'erreur si besoin */

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

/* Ferme le fichier donne en parametre */
void fermerFichier(FILE *fichier, const char *messageErreur)
{
	/* Ferme le fichier donne en parametre et gere l'erreur si besoin */
	if(fclose(fichier) == EOF)
	{
		printf("fermerFichier : \n");
		erreur(messageErreur);
	}
}

/* Fonction qui lit du texte sur un flux indique par chemin et l'affiche en entree */
void lireEtAfficher(const char *chemin)
{
	/* Ouvre un fichier et l'affiche en entree */

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

/* Fonction qui lit du texte sur un flux indique par flux */
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

/* Affiche le texte donne en parametre et demande au joueur d'appuyez sur ENTREE */
void appuyezEntree(const char *texte)
{
	printf("%s\n", texte);
	getchar();
}

/* Fonction qui affiche un titre donne en parametre dans une couleur donnee en parametre */
void titre(const char *s, const unsigned int typeCouleur)
{
	effacer();
	
	couleur(typeCouleur);
	printf("\t\t\t\t%s\n\n", s);
	couleur(BLANC);
}

/* Fonction qui permet de faire son choix lors d'un menu */
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

/* Fonction qui permet de faire son choix lors d'un menu sans possibilite de revenir en 
arriere ou de quitter */
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

/* Affiche une separation de texte avec des - */
void separationTexte(void)
{
	compteur indexSeparation;

	putchar('\n');

	for(indexSeparation = 0; indexSeparation < NB_SEPARATION; ++indexSeparation)
		putchar('-');

	printf("\n\n");
}

/* Attend un nombre de secondes precises en parametre */
void attendre(const float temps)
{
	clock_t arrivee;
	
	arrivee = clock() + (clock_t)(temps * CLOCKS_PER_SEC);
	
	while(clock() < arrivee)
		;
}

/* Demande la comfirmation de faire quelque chose */
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

/* Tire min chance sur max et renvoie 1 si le joueur a la chance et 0 sinon */
unsigned int tirerChance(const unsigned int min, const unsigned int max)
{
	unsigned int chance;

	/* On tire la chance */
	chance = hasard(min, max);

	/* On renvoie 1 si la chance est egale a 1 et 0 sinon */
	return chance == 1;
}

/* Renvoie 1 si la distance est a la portee indiquee en parametre et 0 sinon */
unsigned int estAportee(const unsigned int distanceLig, const unsigned int distanceCol, 
	const unsigned int portee)
{ 
	int distance;

	/* On calcule la distance */
	distance = sqrt(distanceLig * distanceLig + distanceCol * distanceCol);

	return distance <= portee;
}
