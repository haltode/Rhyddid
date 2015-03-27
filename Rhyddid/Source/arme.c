#include <stdio.h>
#include <string.h>

#include "arme.h"
#include "inventaire.h"
#include "personnage.h"
#include "couleur.h"
#include "coffre.h"

void initialiserArmeInventaire(void)
{
	FILE *fichierArme;
	char chemin[TAILLE_MAX];

	sprintf(chemin, "Sauvegarde/%s/Inventaire/arme.txt", personnage.nom);

	fichierArme = ouvrirFichier(chemin, "w+",
	"fichier \"arme.txt\", fonction \"initialiserArmeInventaire\"");

	fprintf(fichierArme, "Poing\n");
	fprintf(fichierArme, "1\n");
	fprintf(fichierArme, "1\n");

	fermerFichier(fichierArme, 
	"fichier \"arme.txt\", fonction \"initialiserArmeInventaire\"");
}

void chargerArmeInventaire(void)
{
	FILE *fichierArme;
	char chemin[TAILLE_MAX];

	sprintf(chemin, "Sauvegarde/%s/Inventaire/arme.txt", personnage.nom);

	fichierArme = ouvrirFichier(chemin, "r",
	"fichier \"arme.txt\", fonction \"chargerArmeInventaire\"");

	lire(fichierArme, inventaire.arme.nom);
	fscanf(fichierArme, "%d\n", &(inventaire.arme.degat));
	fscanf(fichierArme, "%d\n", &(inventaire.arme.portee));

	fermerFichier(fichierArme,
	"fichier \"arme.txt\", fonction \"chargerArmeInventaire\"");
}

void sauvegarderArmeInventaire(void)
{
	FILE *fichierArme;
	char chemin[TAILLE_MAX];

	sprintf(chemin, "Sauvegarde/%s/Inventaire/arme.txt", personnage.nom);

	fichierArme = ouvrirFichier(chemin, "w+",
	"fichier \"arme.txt\", fonction \"sauvegarderArmeInventaire\"");

	fprintf(fichierArme, "%s\n", inventaire.arme.nom);
	fprintf(fichierArme, "%d\n", inventaire.arme.degat);
	fprintf(fichierArme, "%d\n", inventaire.arme.portee);

	fermerFichier(fichierArme,
	"fichier \"arme.txt\", fonction \"sauvegarderArmeInventaire\"");
}

void afficherArmeInventaire(void)
{
	coloration("Arme", VERT);
	printf(" : ");

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

void genererArmeCoffre(Arme *arme)
{
	/* Pour generer une arme au hasard, on utilise la base de donnees baseArme, on tire un index
	au hasard, on fait un test pour savoir si on peut avoir l'arme situee a l'index (1 chance
	sur x, x ici est l'index precedemment tire), si on reussi alors on copie toutes les donnes
	dans la variable arme donnee en parametre, sinon on copie les donnees de l'arme la plus nulle
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

	indexArme = hasard(1, NB_ARME - 1);

	if(tirerChance(1, indexArme))
	{
		strcpy(arme->nom, baseArme[indexArme].nom);
		arme->degat = baseArme[indexArme].degat;
		arme->portee = baseArme[indexArme].portee;
	}
	else
	{
		strcpy(arme->nom, baseArme[0].nom);
		arme->degat = baseArme[0].degat;
		arme->portee = baseArme[0].portee;
	}
}

void afficherArmeCoffre(const Coffre *coffre)
{
	coloration("Arme", VERT);
	printf(" : ");

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

void prendreArmeCoffre(const Arme *arme)
{
	unsigned int choixJoueur;

	printf("Si vous prenez cette arme vous perdrez celle que vous avez actuellement !\n");
	choixJoueur = demanderConfirmation("Voulez-vous prendre cette arme ? (0/1)", 
	PAS_SEPARATION);

	if(choixJoueur == OUI)
	{
		strcpy(inventaire.arme.nom, arme->nom);
		inventaire.arme.degat = arme->degat;
		inventaire.arme.portee = arme->portee;
	}
}
