#include <stdio.h>
#include <string.h>

#include "highscore.h"
#include "effacer.h"
#include "couleur.h"
#include "menuPrincipal.h"
#include "personnage.h"

void lireInformationHighscore(FILE *fichierHighscore, Highscore baseHighscore[NB_HIGHSCORE])
{
	compteur indexScore;

	for(indexScore = 0; indexScore < NB_HIGHSCORE; ++indexScore)
	{
		char buffer[TAILLE_MAX];
		char ligne[TAILLE_MAX];
		compteur indexTab, indexBuffer;

		lire(fichierHighscore, ligne);

		for(indexTab = 0; ligne[indexTab] != '|'; ++indexTab)
			baseHighscore[indexScore].nom[indexTab] = ligne[indexTab];

		baseHighscore[indexScore].nom[indexTab] = '\0';
		++indexTab;

		for(indexBuffer = 0; ligne[indexTab] != '\0'; ++indexTab, ++indexBuffer)
			buffer[indexBuffer] = ligne[indexTab];

		buffer[indexBuffer] = '\0';

		sscanf(buffer, "%s %s %d %d\n", baseHighscore[indexScore].race, baseHighscore[indexScore].metier, 
		&(baseHighscore[indexScore].lvl), &(baseHighscore[indexScore].niveau));
	}
}

void ecrireInformationHighscore(FILE *fichier, const Highscore baseHighscore[NB_HIGHSCORE])
{
	compteur indexScore;

	for(indexScore = 0; indexScore < NB_HIGHSCORE; ++indexScore)
	{
		fprintf(fichier, "%s|%s %s %d %d\n", baseHighscore[indexScore].nom, baseHighscore[indexScore].race, 
		baseHighscore[indexScore].metier, baseHighscore[indexScore].lvl, baseHighscore[indexScore].niveau);
	}
}

void afficherHighscoreIndividuel(const Highscore *baseHighscore)
{
	coloration(baseHighscore->nom, BLEU);
	putchar(' ');
	coloration(baseHighscore->race, VERT);
	putchar(' ');
	coloration(baseHighscore->metier, VERT);
	printf(" %d lvl %d niveaux", baseHighscore->lvl, baseHighscore->niveau);
}

void afficherHighscore(void)
{
	FILE *fichierHighscore;
	Highscore baseHighscore[NB_HIGHSCORE];
	compteur indexScore;

	effacer();
	titre("Highscore", VERT);

	fichierHighscore = ouvrirFichier("Highscore/Highscore.txt", "r",
	"fichier \"Highscore.txt\", fonction \"afficherHighscore\"");

	lireInformationHighscore(fichierHighscore, baseHighscore);

	fermerFichier(fichierHighscore,
	"fichier \"Highscore.txt\", fonction \"afficherHighscore\"");

	if(strcmp("Rien", baseHighscore[0].nom) == 0)
		printf("Vous n'avez aucun record d'enregistrer pour le moment :(\n");
	else
	{
		printf("Voici votre Highscore :\n\n");

		for(indexScore = 0; indexScore < NB_HIGHSCORE; ++indexScore)
		{
			if(strcmp("Rien", baseHighscore[indexScore].nom) != 0)
			{
				printf("\t%2d - ", indexScore + 1);
				afficherHighscoreIndividuel(&(baseHighscore[indexScore]));
				putchar('\n');
			}
			else
				break;
		}
	}

	putchar('\n');
}

void ajouterHighscore(void)
{
	compteur indexScore, indexTab;
	FILE *fichierHighscore;
	Highscore baseHighscore[NB_HIGHSCORE];

	indexScore = 0;

	fichierHighscore = ouvrirFichier("Highscore/Highscore.txt", "r",
	"fichier \"Highscore.txt\", fonction \"ajouterHighscore\"");

	lireInformationHighscore(fichierHighscore, baseHighscore);

	fermerFichier(fichierHighscore,
	"fichier \"Highscore.txt\", fonction \"ajouterHighscore\"");

	while(indexScore < NB_HIGHSCORE && strcmp("Rien", baseHighscore[indexScore].nom) != 0 && 
	         baseHighscore[indexScore].niveau >= personnage.niveauActuel)
		++indexScore;

	for(indexTab = NB_HIGHSCORE - 1; indexTab > indexScore; --indexTab)
	{
		strcpy(baseHighscore[indexTab].nom, baseHighscore[indexTab - 1].nom);
		strcpy(baseHighscore[indexTab].race, baseHighscore[indexTab - 1].race);
		strcpy(baseHighscore[indexTab].metier, baseHighscore[indexTab - 1].metier);
		baseHighscore[indexTab].lvl = baseHighscore[indexTab - 1].lvl;
		baseHighscore[indexTab].niveau = baseHighscore[indexTab - 1].niveau;
	}

	if(indexScore != NB_HIGHSCORE)
	{
		strcpy(baseHighscore[indexScore].nom, personnage.nom);
		strcpy(baseHighscore[indexScore].race, personnage.race);
		strcpy(baseHighscore[indexScore].metier, personnage.metier);
		baseHighscore[indexScore].lvl = personnage.lvl;
		baseHighscore[indexScore].niveau = personnage.niveauActuel;

		fichierHighscore = ouvrirFichier("Highscore/Highscore.txt", "",
		"fichier \"Highscore.txt\", fonction \"ajouterHighscore\"");

		ecrireInformationHighscore(fichierHighscore, baseHighscore);

		fermerFichier(fichierHighscore,
		"fichier \"Highscore.txt\", fonction \"ajouterHighscore\"");
	}
}

void highscore(void)
{
	afficherHighscore();
	appuyezEntree("Appuyez sur ENTREE pour revenir au menu principal...");
	menuPrincipal();
}
