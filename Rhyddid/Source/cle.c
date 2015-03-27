#include <stdio.h>

#include "cle.h"
#include "inventaire.h"
#include "personnage.h"
#include "fonctionsUtiles.h"

void initialiserCleInventaire(void)
{
	FILE *fichierCle;
	char chemin[TAILLE_MAX];

	sprintf(chemin, "Sauvegarde/%s/Inventaire/cle.txt", personnage.nom);

	fichierCle = ouvrirFichier(chemin, "w+",
	"fichier \"cle.txt\", fonction \"initialiserCleInventaire\"");

	fprintf(fichierCle, "0\n");

	fermerFichier(fichierCle,
	"fichier \"cle.txt\", fonction \"initialiserCleInventaire\"");
}

void chargerCleInventaire(void)
{
	FILE *fichierCle;
	char chemin[TAILLE_MAX];

	sprintf(chemin, "Sauvegarde/%s/Inventaire/cle.txt", personnage.nom);

	fichierCle = ouvrirFichier(chemin, "r",
	"fichier \"cle.txt\", fonction \"chargerCleInventaire\"");

	fscanf(fichierCle, "%d\n", &(inventaire.possedeCleFinNiveau));

	fermerFichier(fichierCle,
	"fichier \"cle.txt\", fonction \"chargerCleInventaire\"");
}

void sauvegarderCleInventaire(void)
{
	FILE *fichierCle;
	char chemin[TAILLE_MAX];

	sprintf(chemin, "Sauvegarde/%s/Inventaire/cle.txt", personnage.nom);

	fichierCle = ouvrirFichier(chemin, "w+",
	"fichier \"cle.txt\", fonction \"sauvegarderCleInventaire\"");

	fprintf(fichierCle, "%d\n", inventaire.possedeCleFinNiveau);

	fermerFichier(fichierCle,
	"fichier \"cle.txt\", fonction \"sauvegarderCleInventaire\"");
}

void afficherCleInventaire(void)
{
	if(inventaire.possedeCleFinNiveau)
		lireEtAfficher("ASCII_Art/ASCII_Art_Cle.txt");
	putchar('\n');
}

void ajouterCleInventaire(void)
{
	inventaire.possedeCleFinNiveau = 1;
}
