#include <stdio.h>
#include <string.h>

#include "armure.h"
#include "inventaire.h"
#include "personnage.h"
#include "couleur.h"
#include "coffre.h"

/* Initialise l'armure de l'inventaire dans le fichier Inventaire/armure.txt */
void initialiserArmureInventaire(void)
{
	FILE *fichierArmure;
	char chemin[TAILLE_MAX];

	sprintf(chemin, "Sauvegarde/%s/Inventaire/armure.txt", personnage.nom);

	/* On ouvre le fichier Inventaire/armure.txt */
	fichierArmure = ouvrirFichier(chemin, "w+",
	"fichier \"armure.txt\", fonction \"initialiserArmureInventaire\"");

	/* On ecrit les donnees de l'armure de base avec le nom, et la protection (Rien, 
	0 de protection) */
	fprintf(fichierArmure, "Rien\n");
	fprintf(fichierArmure, "0\n");

	/* On ferme le fichier Inventaire/armure.txt */
	fermerFichier(fichierArmure,
	"fichier \"armure.txt\", fonction \"initialiserArmureInventaire\"");
}

/* Charge l'armure de l'inventaire grace au fichier Inventaire/armure.txt */
void chargerArmureInventaire(void)
{
	FILE *fichierArmure;
	char chemin[TAILLE_MAX];

	sprintf(chemin, "Sauvegarde/%s/Inventaire/armure.txt", personnage.nom);

	/* On ouvre le fichier Inventaire/armure.txt */
	fichierArmure = ouvrirFichier(chemin, "r",
	"fichier \"armure.txt\", fonction \"chargerArmureInventaire\"");

	/* On recupere les donnees de l'armure avec le nom, et la protection */
	lire(fichierArmure, inventaire.armure.nom);
	fscanf(fichierArmure, "%d\n", &(inventaire.armure.protection));

	/* On ferme le fichier Inventaire/armure.txt */
	fermerFichier(fichierArmure,
	"fichier \"armure.txt\", fonction \"chargerArmureInventaire\"");
}

/* Sauvegarde l'armure de l'inventaire dans le fichier Inventaire/armure.txt */
void sauvegarderArmureInventaire(void)
{
	FILE *fichierArmure;
	char chemin[TAILLE_MAX];

	sprintf(chemin, "Sauvegarde/%s/Inventaire/armure.txt", personnage.nom);

	/* On ouvre le fichier Inventaire/armure.txt */
	fichierArmure = ouvrirFichier(chemin, "w+",
	"fichier \"armure.txt\", fonction \"sauvegarderArmureInventaire\"");

	/* On ecrit les donnees de l'armure avec le nom, et la protection */
	fprintf(fichierArmure, "%s\n", inventaire.armure.nom);
	fprintf(fichierArmure, "%d\n", inventaire.armure.protection);

	/* On ferme le fichier Inventaire/armure.txt */
	fermerFichier(fichierArmure,
	"fichier \"armure.txt\", fonction \"sauvegarderArmureInventaire\"");
}

/* Affiche la section Armure de l'inventaire lorsqu'on ouvre l'inventaire */
void afficherArmureInventaire(void)
{
	/* On affiche le nom de la categorie de l'inventaire en vert (ici Armure) */
	coloration("Armure", VERT);
	printf(" : ");

	/* Si le joueur n'a pas d'armure, on affiche "Aucune" */
	if(strcmp(inventaire.armure.nom, "Rien") == 0)
		coloration("Aucune", BLEU);
	else
	{
		/* Sinon on affiche le nom de l'armure en bleu, et la protection en vert */

		coloration(inventaire.armure.nom, BLEU);
		printf(" | ");
		couleur(VERT);
		printf("+%d ", inventaire.armure.protection);
		couleur(BLANC);
		printf("de protection");
	}

	printf("\n\n");
}

/* Genere une armure au hasard situee dans un coffre */
void genererArmureCoffre(Armure *armure)
{
	/* Pour generer une armure au hasard, on utilise la base de donnees baseArmure, on tire un 
	index au hasard, on fait un teste pour savoir si on peut avoir l'armure situee a l'index 
	(1 chance sur x, x ici est l'index precedemment tire), si on reussi alors on copie toutes 
	les donnes dans la variable armure donnee en parametre, sinon on copie les donnees de 
	l'armure la plus nul situee a l'index 0 du tableau baseArmure */

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

	/* On tire un nombre au hasard entre 1 et NB_ARMURE - 1 */
	indexArmure = hasard(1, NB_ARMURE - 1);

	/* On fait le test 1 chance sur indexArmure */
	if(tirerChance(1, indexArmure))
	{
		/* Si on reussi le test, on copie les donnees (nom, proctection) de l'armure situee a 
		l'index indexArmure */
		strcpy(armure->nom, baseArmure[indexArmure].nom);
		armure->protection = baseArmure[indexArmure].protection;
	}
	else
	{
		/* Sinon on copie les donnees (nom, protection) de l'armure la plus nulle situee a 
		l'index 0 */
		strcpy(armure->nom, baseArmure[0].nom);
		armure->protection = baseArmure[0].protection;
	}
}

/* Affiche la section Armure d'un coffre lorsqu'on l'ouvre */
void afficherArmureCoffre(const Coffre *coffre)
{
	/* On affiche la categorie du coffre en vert (ici Armure) */
	coloration("Armure", VERT);
	printf(" : ");
	
	/* On affiche les donnees de l'armure (le nom en bleu, la protection en vert) */
	coloration(coffre->inventaire.armure.nom, BLEU);
	printf(" | ");
	couleur(VERT);
	printf("+%d ", coffre->inventaire.armure.protection);
	couleur(BLANC);
	printf("de protection");

	putchar('\n');
}

/* Prend l'armure situee dans le coffre que le joueur vient d'ouvrir (donne en parametre) */
void prendreArmureCoffre(const Armure *armure)
{
	unsigned int choixJoueur;

	/* On demande si le joueur veut prendre l'armure ou non */
	printf("Si vous prenez cette armure vous perdrez celle que vous avez actuellement !\n");
	choixJoueur = demanderConfirmation("Voulez-vous prendre cette armure ? (0/1)", 
	PAS_SEPARATION);

	/* Si il veut prendre l'armure, on copie les donnees de l'armure (nom, protection) dans son
	inventaire */
	if(choixJoueur == OUI)
	{
		strcpy(inventaire.armure.nom, armure->nom);
		inventaire.armure.protection = armure->protection;
	}
}
