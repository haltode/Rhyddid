#include <stdio.h>

#include "tek.h"
#include "inventaire.h"
#include "personnage.h"
#include "fonctionsUtiles.h"
#include "couleur.h"
#include "coffre.h"

void initialiserTekInventaire(void)
{
	FILE *fichierTek;
	char chemin[TAILLE_MAX];

	sprintf(chemin, "Sauvegarde/%s/Inventaire/tek.txt", personnage.nom);

	fichierTek = ouvrirFichier(chemin, "w+",
	"fichier \"tek.txt\", fonction \"initialiserTekInventaire\"");

	fprintf(fichierTek, "0\n");

	fermerFichier(fichierTek,
	"fichier \"tek.txt\", fonction \"initialiserTekInventaire\"");
}

void chargerTekInventaire(void)
{
	FILE *fichierTek;
	char chemin[TAILLE_MAX];

	sprintf(chemin, "Sauvegarde/%s/Inventaire/tek.txt", personnage.nom);

	fichierTek = ouvrirFichier(chemin, "r",
	"fichier \"tek.txt\", fonction \"chargerTekInventaire\"");

	fscanf(fichierTek, "%d\n", &(inventaire.tek.nbTek));

	fermerFichier(fichierTek,
	"fichier \"tek.txt\", fonction \"chargerTekInventaire\"");
}

void sauvegarderTekInventaire(void)
{
	FILE *fichierTek;
	char chemin[TAILLE_MAX];

	sprintf(chemin, "Sauvegarde/%s/Inventaire/tek.txt", personnage.nom);

	fichierTek = ouvrirFichier(chemin, "w+",
	"fichier \"tek.txt\", fonction \"sauvegarderTekInventaire\"");

	fprintf(fichierTek, "%d\n", inventaire.tek.nbTek);

	fermerFichier(fichierTek,
	"fichier \"tek.txt\", fonction \"sauvegarderTekInventaire\"");
}

void afficherTekInventaire(void)
{
	coloration("Tek", VERT);
	printf(" : ");
	couleur(BLEU);
	printf("%d\n\n", inventaire.tek.nbTek);
	couleur(BLANC);
}

void ajouterTekInventaire(const unsigned int nbTek)
{
	inventaire.tek.nbTek += nbTek;
}

void enleverTekInventaire(const unsigned int nbTek)
{
	inventaire.tek.nbTek -= nbTek;
}

void genererTekCoffre(Tek *tek)
{
	tek->nbTek = 0;

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

void afficherTekCoffre(const Coffre *coffre)
{
	coloration("Tek", VERT);
	printf(" : ");
	couleur(BLEU);
	printf("%d\n", coffre->inventaire.tek.nbTek);
	couleur(BLANC);
}

void prendreTekCoffre(const Tek *tek)
{
	ajouterTekInventaire(tek->nbTek);
}
