#include <stdio.h>
#include <string.h>

#include "arme.h"
#include "inventaire.h"
#include "personnage.h"
#include "couleur.h"
#include "coffre.h"

/* Initialise l'arme de l'inventaire dans le fichier Inventaire/arme.txt */
void initialiserArmeInventaire(void)
{
	FILE *fichierArme;
	char chemin[TAILLE_MAX];

	sprintf(chemin, "Sauvegarde/%s/Inventaire/arme.txt", personnage.nom);

	/* On ouvre le fichier Inventaire/arme.txt */
	fichierArme = ouvrirFichier(chemin, "w+",
	"fichier \"arme.txt\", fonction \"initialiserArmeInventaire\"");

	/* On ecrit les donnees de l'arme de base avec le nom, les degats et la portee 
	(Poing, 1 de degat, 1 de portee) */
	fprintf(fichierArme, "Poing\n");
	fprintf(fichierArme, "1\n");
	fprintf(fichierArme, "1\n");

	/* On ferme le fichier Inventaire/arme.txt */
	fermerFichier(fichierArme, 
	"fichier \"arme.txt\", fonction \"initialiserArmeInventaire\"");
}

/* Charge l'arme de l'inventaire grace au fichier Inventaire/arme.txt */
void chargerArmeInventaire(void)
{
	FILE *fichierArme;
	char chemin[TAILLE_MAX];

	sprintf(chemin, "Sauvegarde/%s/Inventaire/arme.txt", personnage.nom);

	/* On ouvre le fichier Inventaire/arme.txt */
	fichierArme = ouvrirFichier(chemin, "r",
	"fichier \"arme.txt\", fonction \"chargerArmeInventaire\"");

	/* On recupere les donnees de l'arme avec le nom, les degats et la portee */
	lire(fichierArme, inventaire.arme.nom);
	fscanf(fichierArme, "%d\n", &(inventaire.arme.degat));
	fscanf(fichierArme, "%d\n", &(inventaire.arme.portee));

	/* On ferme le fichier Inventaire/arme.txt */
	fermerFichier(fichierArme,
	"fichier \"arme.txt\", fonction \"chargerArmeInventaire\"");
}

/* Sauvegarde l'arme de l'inventaire dans le fichier Inventaire/arme.txt */
void sauvegarderArmeInventaire(void)
{
	FILE *fichierArme;
	char chemin[TAILLE_MAX];

	sprintf(chemin, "Sauvegarde/%s/Inventaire/arme.txt", personnage.nom);

	/* On ouvre le fichier Inventaire/arme.txt */
	fichierArme = ouvrirFichier(chemin, "w+",
	"fichier \"arme.txt\", fonction \"sauvegarderArmeInventaire\"");

	/* On ecrit les donnees de l'arme avec le nom, les degats et la portee */
	fprintf(fichierArme, "%s\n", inventaire.arme.nom);
	fprintf(fichierArme, "%d\n", inventaire.arme.degat);
	fprintf(fichierArme, "%d\n", inventaire.arme.portee);

	/* On ferme le fichier Inventaire/arme.txt */
	fermerFichier(fichierArme,
	"fichier \"arme.txt\", fonction \"sauvegarderArmeInventaire\"");
}

/* Affiche la section Arme de l'inventaire lorsqu'on ouvre l'inventaire */
void afficherArmeInventaire(void)
{
	/* On affiche le nom de la categorie de l'inventaire en vert (ici Arme) */
	coloration("Arme", VERT);
	printf(" : ");

	/* On affiche le nom de l'arme en bleu, puis les degats en vert et la portee en vert */
	coloration(inventaire.arme.nom, BLEU);
	printf(" | ");
	couleur(VERT);
	printf("+%d ", inventaire.arme.degat);
	couleur(BLANC);
	printf("de degat");
	printf(" | ");
	couleur(VERT);
	printf("%d ", inventaire.arme.portee);
	couleur(BLANC);
	printf("de portee");

	printf("\n\n");
}

/* Genere une arme au hasard situee dans un coffre */
void genererArmeCoffre(Arme *arme)
{
	/* Pour generer une arme au hasard, on utilise la base de donnees baseArme, on tire un index
	au hasard, on fait un teste pour savoir si on peut avoir l'arme situee a l'index (1 chance
	sur x, x ici est l'index precedemment tire), si on reussi alors on copie toutes les donnes
	dans la variable arme donnee en parametre, sinon on copie les donnees de l'arme la plus nul
	situee a l'index 0 du tableau baseArme */

	/* Base de donnee contenant chaque arme avec nom, degat, portee */
	static const Arme baseArme[NB_ARME] =
	{
		{"Baton", 1, 1},
		{"Poing americain", 2, 1},
		{"Marteau", 3, 1},
		{"Gourdin", 4, 1},
		{"Matraque", 3, 2},
		{"Dague", 4, 1},
		{"Poignard", 4, 1},
		{"Couteau de poche", 4, 1},
		{"Couteau", 4, 1},
		{"Couteau de combat", 5, 1},
		{"Epee en bois", 2, 2},
		{"Epee en pierre", 3, 2},
		{"Hache", 6, 2},
		{"Sabre", 6, 2},
		{"Arc", 4, 3},
		{"Arbalette", 5, 2},
		{"Masse", 5, 3},
		{"Lance", 3, 4},
		{"Epee en bronze", 4, 2},
		{"Epee en cuivre", 5, 2},
		{"Epee en fer", 6, 2},
		{"Epee en acier", 7, 2},
		{"Pistolet", 5, 3},
		{"Revolver", 6, 3},
		{"Arquebuse", 6, 4},
		{"Fusil", 6, 5},
		{"Carabine", 6, 6},
		{"Fusil d'assaut", 8, 5},
		{"Fusil a pompe", 9, 2},
		{"Pistolet mitrailleur", 10, 1},
		{"Fusil de precision", 7, 6},
		{"Mitrailleuse", 8, 3},
		{"Lance-flammes", 11, 6},
		{"Sabre laser", 20, 2},
		{"Canon de plasma", 30, 10}
	};
	unsigned int indexArme;

	/* On tire un nombre au hasard entre 1 et NB_ARME - 1 */
	indexArme = hasard(1, NB_ARME - 1);

	/* On fait le test 1 chance sur indexArme */
	if(tirerChance(1, indexArme))
	{
		/* Si on reussi le test, on copie les donnees (nom, degat, portee) de l'arme situee a 
		l'index indexArme */
		strcpy(arme->nom, baseArme[indexArme].nom);
		arme->degat = baseArme[indexArme].degat;
		arme->portee = baseArme[indexArme].portee;
	}
	else
	{
		/* Sinon on copie les donnees (nom, degat, portee) de l'arme la plus nulle situee a 
		l'index 0 */
		strcpy(arme->nom, baseArme[0].nom);
		arme->degat = baseArme[0].degat;
		arme->portee = baseArme[0].portee;
	}
}

/* Affiche la section Arme d'un coffre lorsqu'on l'ouvre */
void afficherArmeCoffre(const Coffre *coffre)
{
	/* On affiche la categorie du coffre en vert (ici Arme) */
	coloration("Arme", VERT);
	printf(" : ");

	/* On affiche les donnees de l'arme (le nom en bleu, les degats en vert, la portee en vert) */
	coloration(coffre->inventaire.arme.nom, BLEU);
	printf(" | ");
	couleur(VERT);
	printf("+%d ", coffre->inventaire.arme.degat);
	couleur(BLANC);
	printf("de degat");
	printf(" | ");
	couleur(VERT);
	printf("%d ", coffre->inventaire.arme.portee);
	couleur(BLANC);
	printf("de portee");

	putchar('\n');
}

/* Prend l'arme situee dans le coffre que le joueur vient d'ouvrir (donnee en parametre) */
void prendreArmeCoffre(const Arme *arme)
{
	unsigned int choixJoueur;

	/* On demande si le joueur veut prendre l'arme ou non */
	printf("Si vous prenez cette arme vous perdrez celle que vous avez actuellement !\n");
	choixJoueur = demanderConfirmation("Voulez-vous prendre cette arme ? (0/1)", 
	PAS_SEPARATION);

	/* Si il veut prendre l'arme, on copie les donnees de l'arme (nom, degat, portee) dans son
	inventaire */
	if(choixJoueur == OUI)
	{
		strcpy(inventaire.arme.nom, arme->nom);
		inventaire.arme.degat = arme->degat;
		inventaire.arme.portee = arme->portee;
	}
}
