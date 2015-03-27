#include <stdio.h>
#include <string.h>

#include "armure.h"
#include "inventaire.h"
#include "personnage.h"
#include "couleur.h"
#include "coffre.h"

void initialiserArmureInventaire(void)
{
	FILE *fichierArmure;
	char chemin[TAILLE_MAX];

	sprintf(chemin, "Sauvegarde/%s/Inventaire/armure.txt", personnage.nom);

	fichierArmure = ouvrirFichier(chemin, "w+",
	"fichier \"armure.txt\", fonction \"initialiserArmureInventaire\"");

	fprintf(fichierArmure, "Rien\n");
	fprintf(fichierArmure, "0\n");

	fermerFichier(fichierArmure,
	"fichier \"armure.txt\", fonction \"initialiserArmureInventaire\"");
}

void chargerArmureInventaire(void)
{
	FILE *fichierArmure;
	char chemin[TAILLE_MAX];

	sprintf(chemin, "Sauvegarde/%s/Inventaire/armure.txt", personnage.nom);

	fichierArmure = ouvrirFichier(chemin, "r",
	"fichier \"armure.txt\", fonction \"chargerArmureInventaire\"");

	lire(fichierArmure, inventaire.armure.nom);
	fscanf(fichierArmure, "%d\n", &(inventaire.armure.protection));

	fermerFichier(fichierArmure,
	"fichier \"armure.txt\", fonction \"chargerArmureInventaire\"");
}

void sauvegarderArmureInventaire(void)
{
	FILE *fichierArmure;
	char chemin[TAILLE_MAX];

	sprintf(chemin, "Sauvegarde/%s/Inventaire/armure.txt", personnage.nom);

	fichierArmure = ouvrirFichier(chemin, "w+",
	"fichier \"armure.txt\", fonction \"sauvegarderArmureInventaire\"");

	fprintf(fichierArmure, "%s\n", inventaire.armure.nom);
	fprintf(fichierArmure, "%d\n", inventaire.armure.protection);

	fermerFichier(fichierArmure,
	"fichier \"armure.txt\", fonction \"sauvegarderArmureInventaire\"");
}

void afficherArmureInventaire(void)
{
	coloration("Armure", VERT);
	printf(" : ");

	if(strcmp(inventaire.armure.nom, "Rien") == 0)
		coloration("Aucune", BLEU);
	else
	{
		coloration(inventaire.armure.nom, BLEU);
		printf(" | ");
		couleur(VERT);
		printf("+%d ", inventaire.armure.protection);
		couleur(BLANC);
		printf("de protection");
	}

	printf("\n\n");
}

void genererArmureCoffre(Armure *armure)
{
	/* Pour generer une armure au hasard, on utilise la base de donnees baseArmure, on tire un 
	index au hasard, on fait un test pour savoir si on peut avoir l'armure situee a l'index 
	(1 chance sur x, x ici est l'index precedemment tire), si on reussi alors on copie toutes 
	les donnes dans la variable armure donnee en parametre, sinon on copie les donnees de 
	l'armure la plus nulle situee a l'index 0 du tableau baseArmure */

	/* Base de donnee contenant chaque armure avec nom, protection */
	static const Armure baseArmure[NB_ARMURE] =
	{
		{"Tissu en soie", 1},
		{"Vetement en cuir souple", 2},
		{"Vetement en cuir rigide", 3},
		{"Manteau epais", 3},
		{"Armure en peau de bete", 4},
		{"Bouclier en cuir", 4},
		{"Bouclier en cuivre", 5},
		{"Bouclier en bronze", 5},
		{"Bouclier en fer", 5},
		{"Bouclier en acier", 6},
		{"Plastron", 6},
		{"Cuirasse", 6},
		{"Armure d'ecaille", 6},
		{"Armure en cuir", 7},
		{"Armure cloutee", 7},
		{"Armure en cote de maille", 7},
		{"Armure en bronze", 8},
		{"Armure en cuivre", 8},
		{"Armure en fer", 8},
		{"Armure de plates", 8},
		{"Armure en metal", 9},
		{"Armure en acier", 9},
		{"Armure lourde", 10},
		{"Armure blindee", 10},
		{"Bouclier anti-emeute", 10},
		{"Gilet pare-balles", 11},
		{"Kevlar", 12},
		{"Exosquelette", 14},
		{"Iron Man", 18},
		{"Amure Draconique", 20}
	};
	unsigned int indexArmure;

	indexArmure = hasard(1, NB_ARMURE - 1);

	if(tirerChance(1, indexArmure))
	{
		strcpy(armure->nom, baseArmure[indexArmure].nom);
		armure->protection = baseArmure[indexArmure].protection;
	}
	else
	{
		strcpy(armure->nom, baseArmure[0].nom);
		armure->protection = baseArmure[0].protection;
	}
}

void afficherArmureCoffre(const Coffre *coffre)
{
	coloration("Armure", VERT);
	printf(" : ");
	
	coloration(coffre->inventaire.armure.nom, BLEU);
	printf(" | ");
	couleur(VERT);
	printf("+%d ", coffre->inventaire.armure.protection);
	couleur(BLANC);
	printf("de protection");

	putchar('\n');
}

void prendreArmureCoffre(const Armure *armure)
{
	unsigned int choixJoueur;

	printf("Si vous prenez cette armure vous perdrez celle que vous avez actuellement !\n");
	choixJoueur = demanderConfirmation("Voulez-vous prendre cette armure ? (0/1)", 
	PAS_SEPARATION);

	if(choixJoueur == OUI)
	{
		strcpy(inventaire.armure.nom, armure->nom);
		inventaire.armure.protection = armure->protection;
	}
}
