#include <stdio.h>

#include "tek.h"
#include "inventaire.h"
#include "personnage.h"
#include "fonctionsUtiles.h"
#include "couleur.h"
#include "coffre.h"

/* Initialise les teks de l'inventaire dans le fichier Inventaire/tek.txt */
void initialiserTekInventaire(void)
{
	FILE *fichierTek;
	char chemin[TAILLE_MAX];

	sprintf(chemin, "Sauvegarde/%s/Inventaire/tek.txt", personnage.nom);

	/* On ouvre le fichier Inventaire/tek.txt */
	fichierTek = ouvrirFichier(chemin, "w+",
	"fichier \"tek.txt\", fonction \"initialiserTekInventaire\"");

	/* On ecrit les donnees des teks de base avec le nombre de tek initial (0) */
	fprintf(fichierTek, "0\n");

	/* On ferme le fichier Inventaire/tek.txt */
	fermerFichier(fichierTek,
	"fichier \"tek.txt\", fonction \"initialiserTekInventaire\"");
}

/* Charge les teks de l'inventaire dans le fichier Inventaire/tek.txt */
void chargerTekInventaire(void)
{
	FILE *fichierTek;
	char chemin[TAILLE_MAX];

	sprintf(chemin, "Sauvegarde/%s/Inventaire/tek.txt", personnage.nom);

	/* On ouvre le fichier Inventaire/tek.txt */
	fichierTek = ouvrirFichier(chemin, "r",
	"fichier \"tek.txt\", fonction \"chargerTekInventaire\"");

	/* On recupere les donnees des teks avec le nombre de tek */
	fscanf(fichierTek, "%d\n", &(inventaire.tek.nbTek));

	/* On ferme le fichier Inventaire/tek.txt */
	fermerFichier(fichierTek,
	"fichier \"tek.txt\", fonction \"chargerTekInventaire\"");
}

/* Sauvegarde les teks de l'inventaire dans le fichier Inventaire/tek.txt */
void sauvegarderTekInventaire(void)
{
	FILE *fichierTek;
	char chemin[TAILLE_MAX];

	sprintf(chemin, "Sauvegarde/%s/Inventaire/tek.txt", personnage.nom);

	/* On ouvre le fichier Inventaire/tek.txt */
	fichierTek = ouvrirFichier(chemin, "w+",
	"fichier \"tek.txt\", fonction \"sauvegarderTekInventaire\"");

	/* On ecrit les donnees des teks avec le nombre de tek */
	fprintf(fichierTek, "%d\n", inventaire.tek.nbTek);

	/* On ferme le fichier Inventaire/tek.txt */
	fermerFichier(fichierTek,
	"fichier \"tek.txt\", fonction \"sauvegarderTekInventaire\"");
}

/* Affiche la section Tek de l'inventaire lorsqu'on ouvre l'inventaire */
void afficherTekInventaire(void)
{
	coloration("Tek", VERT);
	printf(" : ");
	couleur(BLEU);
	printf("%d\n\n", inventaire.tek.nbTek);
	couleur(BLANC);
}

/* Ajoute nbTek a l'inventaire du joueur */
void ajouterTekInventaire(const unsigned int nbTek)
{
	/* On ajoute le nombre de tek */
	inventaire.tek.nbTek += nbTek;
}

/* Enleve nbTek a l'inventaire du joueur */
void enleverTekInventaire(const unsigned int nbTek)
{
	/* On enleve le nombre de tek */
	inventaire.tek.nbTek -= nbTek;
}

/* Genere des teks au hasard situes dans un coffre */
void genererTekCoffre(Tek *tek)
{
	/* On initialise le nombre de tek du coffre a 0 */
	tek->nbTek = 0;

	/* On teste pour chaque niveau de tek (20 teks, 50 teks, 70 teks, 120 teks) avec la 
	probabilite que le joueur l'ai */

	/* Pour 20 teks */
	if(tirerChance(1, CHANCE_MAX_NB_TEK_NIVEAU_1))
	{
		tek->nbTek = NB_TEK_NIVEAU_1;
		return ;
	}
	/* Pour 50 teks */
	if(tirerChance(1, CHANCE_MAX_NB_TEK_NIVEAU_2))
	{
		tek->nbTek = NB_TEK_NIVEAU_2;
		return ;
	}
	/* Pour 70 teks */
	if(tirerChance(1, CHANCE_MAX_NB_TEK_NIVEAU_3))
	{
		tek->nbTek = NB_TEK_NIVEAU_3;
		return ;
	}
	/* Pour 120 teks */
	if(tirerChance(1, CHANCE_MAX_NB_TEK_NIVEAU_4))
	{
		tek->nbTek = NB_TEK_NIVEAU_4;
		return ;
	}
}

/* Affiche la section Tek d'un coffre lorsqu'on l'ouvre */
void afficherTekCoffre(const Coffre *coffre)
{
	coloration("Tek", VERT);
	printf(" : ");
	couleur(BLEU);
	printf("%d\n", coffre->inventaire.tek.nbTek);
	couleur(BLANC);
}

/* Prend les teks situes dans le coffre que le joueur vient d'ouvrir (donne en parametre) */
void prendreTekCoffre(const Tek *tek)
{
	/* On ajoute le nombre de tek du coffre dans l'inventaire du joueur */
	ajouterTekInventaire(tek->nbTek);
}
