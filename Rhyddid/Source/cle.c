#include <stdio.h>

#include "cle.h"
#include "inventaire.h"
#include "personnage.h"
#include "fonctionsUtiles.h"

/* Initialise la cle de fin de niveau de l'inventaire dans le fichier Inventaire/cle.txt */
void initialiserCleInventaire(void)
{
	FILE *fichierCle;
	char chemin[TAILLE_MAX];

	sprintf(chemin, "Sauvegarde/%s/Inventaire/cle.txt", personnage.nom);

	/* On ouvre le fichier Inventaire/cle.txt */
	fichierCle = ouvrirFichier(chemin, "w+",
	"fichier \"cle.txt\", fonction \"initialiserCleInventaire\"");

	/* On ecrit que le joueur de base ne possede pas la cle (on ecrit donc 0) */
	fprintf(fichierCle, "0\n");

	/* On ferme le fichier Inventaire/cle.txt */
	fermerFichier(fichierCle,
	"fichier \"cle.txt\", fonction \"initialiserCleInventaire\"");
}

/* Charge la cle de fin de niveau de l'inventaire grace au fichier Inventaire/cle.txt */
void chargerCleInventaire(void)
{
	FILE *fichierCle;
	char chemin[TAILLE_MAX];

	sprintf(chemin, "Sauvegarde/%s/Inventaire/cle.txt", personnage.nom);

	/* On ouvre le fichier Inventaire/cle.txt */
	fichierCle = ouvrirFichier(chemin, "r",
	"fichier \"cle.txt\", fonction \"chargerCleInventaire\"");

	/* On recupere le booleen permettant de savoir si le joueur possede ou non la cle de fin de
	niveau */
	fscanf(fichierCle, "%d\n", &(inventaire.possedeCleFinNiveau));

	/* On ferme le fichier Inventaire/cle.txt */
	fermerFichier(fichierCle,
	"fichier \"cle.txt\", fonction \"chargerCleInventaire\"");
}

/* Sauvegarde la cle de fin de niveau de l'inventaire dans le fichier Inventaire/cle.txt */
void sauvegarderCleInventaire(void)
{
	FILE *fichierCle;
	char chemin[TAILLE_MAX];

	sprintf(chemin, "Sauvegarde/%s/Inventaire/cle.txt", personnage.nom);

	/* On ouvre le fichier Inventaire/cle.txt */
	fichierCle = ouvrirFichier(chemin, "w+",
	"fichier \"cle.txt\", fonction \"sauvegarderCleInventaire\"");

	/* On ecrit le booleen permettant de savoir si le joueur possede ou non la cle de fin de
	niveau */
	fprintf(fichierCle, "%d\n", inventaire.possedeCleFinNiveau);

	/* On ferme le fichier Inventaire/cle.txt */
	fermerFichier(fichierCle,
	"fichier \"cle.txt\", fonction \"sauvegarderCleInventaire\"");
}

/* Affiche la section Cle de l'inventaire lorsqu'on ouvre l'inventaire */
void afficherCleInventaire(void)
{
	/* Si le joueur possede la cle de fin de niveau, on affiche le fichier cle.txt contenant
	un ASCII Art de la cle et une explication de son utilite */
	if(inventaire.possedeCleFinNiveau)
		lireEtAfficher("ASCII_Art/ASCII_Art_Cle.txt");

	putchar('\n');
}

/* Ajoute la cle de fin de niveau dans l'inventaire du joueur */
void ajouterCleInventaire(void)
{
	/* On affecte a possedeCleFinNiveau la valeur 1 disant que le joueur possede la cle de fin
	de niveau */
	inventaire.possedeCleFinNiveau = 1;
}
