#include <stdio.h>
#include <string.h>

#include "highscore.h"
#include "effacer.h"
#include "couleur.h"
#include "menuPrincipal.h"
#include "personnage.h"

/* Lit le fichier "Highscore.txt" et le charge dans la structure Highscore */
void lireInformationHighscore(FILE *fichierHighscore, Highscore baseHighscore[NB_HIGHSCORE])
{
	compteur indexScore;

	/* Pour chaque ligne du highscore */
	for(indexScore = 0; indexScore < NB_HIGHSCORE; ++indexScore)
	{
		char buffer[TAILLE_MAX];
		char ligne[TAILLE_MAX];
		compteur indexTab, indexBuffer;

		/* On lit la ligne du fichier */
		lire(fichierHighscore, ligne);

		/* On separe le nom du highscore du reste de la ligne et on le sauvegarde*/
		for(indexTab = 0; ligne[indexTab] != '|'; ++indexTab)
			baseHighscore[indexScore].nom[indexTab] = ligne[indexTab];

		baseHighscore[indexScore].nom[indexTab] = '\0';
		++indexTab;

		/* On copie tout le reste de la ligne dans un buffer (sans le nom du highscore donc) */
		for(indexBuffer = 0; ligne[indexTab] != '\0'; ++indexTab, ++indexBuffer)
			buffer[indexBuffer] = ligne[indexTab];

		buffer[indexBuffer] = '\0';

		/* On lit ensuite la race, le metier, le lvl, le niveau */
		sscanf(buffer, "%s %s %d %d\n", baseHighscore[indexScore].race, baseHighscore[indexScore].metier, 
		&(baseHighscore[indexScore].lvl), &(baseHighscore[indexScore].niveau));
	}
}

/* Ecrit dans le fichier "Highscore.txt" la structure Highscore */
void ecrireInformationHighscore(FILE *fichier, const Highscore baseHighscore[NB_HIGHSCORE])
{
	compteur indexScore;

	/* Pour chaque highscore */
	for(indexScore = 0; indexScore < NB_HIGHSCORE; ++indexScore)
	{
		/* On ecrit le nom, la race, le metier, le lvl et le niveau */
		fprintf(fichier, "%s|%s %s %d %d\n", baseHighscore[indexScore].nom, baseHighscore[indexScore].race, 
		baseHighscore[indexScore].metier, baseHighscore[indexScore].lvl, baseHighscore[indexScore].niveau);
	}
}

/* Affiche individuellement un highscore */
void afficherHighscoreIndividuel(const Highscore *baseHighscore)
{
	/* Affiche le nom, la race, le metier, le lvl et le niveau */

	coloration(baseHighscore->nom, BLEU);
	putchar(' ');
	coloration(baseHighscore->race, VERT);
	putchar(' ');
	coloration(baseHighscore->metier, VERT);
	printf(" %d lvl %d niveaux", baseHighscore->lvl, baseHighscore->niveau);
}

/* Affiche le highscore en entier */
void afficherHighscore(void)
{
	FILE *fichierHighscore;
	Highscore baseHighscore[NB_HIGHSCORE];
	compteur indexScore;

	effacer();
	titre("Highscore", VERT);

	/* On ouvre le fichier "Highscore.txt" */
	fichierHighscore = ouvrirFichier("Highscore/Highscore.txt", "r",
	"fichier \"Highscore.txt\", fonction \"afficherHighscore\"");

	/* On lit toutes les informations du highscore et on le stocke */
	lireInformationHighscore(fichierHighscore, baseHighscore);

	/* On ferme le fichier "Highscore.txt" */
	fermerFichier(fichierHighscore,
	"fichier \"Highscore.txt\", fonction \"afficherHighscore\"");

	/* Si on a aucun highscore on affiche un message */
	if(strcmp("Rien", baseHighscore[0].nom) == 0)
		printf("Vous n'avez aucun record d'enregistrer pour le moment :(\n");
	/* Sinon */
	else
	{
		printf("Voici votre Highscore :\n\n");

		/* Pour chaque highscore */
		for(indexScore = 0; indexScore < NB_HIGHSCORE; ++indexScore)
		{
			/* Si le highscore n'est pas vide */
			if(strcmp("Rien", baseHighscore[indexScore].nom) != 0)
			{
				/* On affiche les informations du highscore */

				printf("\t%2d - ", indexScore + 1);
				afficherHighscoreIndividuel(&(baseHighscore[indexScore]));
				putchar('\n');
			}
			/* Sinon */
			else
				/* On arrete la boucle puisqu'il y a plus rien apres */
				break;
		}
	}

	putchar('\n');
}

/* Ajoute une sauvegarde au highscore */
void ajouterHighscore(void)
{
	compteur indexScore, indexTab;
	FILE *fichierHighscore;
	Highscore baseHighscore[NB_HIGHSCORE];

	indexScore = 0;

	/* On ouvre le fichier "Highscore.txt" */
	fichierHighscore = ouvrirFichier("Highscore/Highscore.txt", "r",
	"fichier \"Highscore.txt\", fonction \"ajouterHighscore\"");

	/* On lit toutes les informations du highscore et on le stocke */
	lireInformationHighscore(fichierHighscore, baseHighscore);

	/* On ferme le fichier "Highscore.txt" */
	fermerFichier(fichierHighscore,
	"fichier \"Highscore.txt\", fonction \"ajouterHighscore\"");

	/* On cherche l'index du highscore dans le classement */

	/* Tant qu'on depasse pas le nombre max de highscore, tant que le highscore actuel n'est
	pas vide et que le highscore actuel a un niveau supperieur ou egal a celui de la partie */
	while(indexScore < NB_HIGHSCORE && strcmp("Rien", baseHighscore[indexScore].nom) != 0 && 
	         baseHighscore[indexScore].niveau >= personnage.niveauActuel)
		++indexScore;

	/* Pour chaque highscore */
	for(indexTab = NB_HIGHSCORE - 1; indexTab > indexScore; --indexTab)
	{
		/* On decale de 1 chaque highscore vers la droite */
		strcpy(baseHighscore[indexTab].nom, baseHighscore[indexTab - 1].nom);
		strcpy(baseHighscore[indexTab].race, baseHighscore[indexTab - 1].race);
		strcpy(baseHighscore[indexTab].metier, baseHighscore[indexTab - 1].metier);
		baseHighscore[indexTab].lvl = baseHighscore[indexTab - 1].lvl;
		baseHighscore[indexTab].niveau = baseHighscore[indexTab - 1].niveau;
	}

	/* Si le highscore est dans le classement */
	if(indexScore != NB_HIGHSCORE)
	{
		/* On copie toutes les informations necessaires du highscore (nom, race, metier, lvl,
		niveau) */

		strcpy(baseHighscore[indexScore].nom, personnage.nom);
		strcpy(baseHighscore[indexScore].race, personnage.race);
		strcpy(baseHighscore[indexScore].metier, personnage.metier);
		baseHighscore[indexScore].lvl = personnage.lvl;
		baseHighscore[indexScore].niveau = personnage.niveauActuel;

		/* On sauvegarde les modifications sur le highscore */

		/* On ouvre le fichier "Highscore.txt" */
		fichierHighscore = ouvrirFichier("Highscore/Highscore.txt", "",
		"fichier \"Highscore.txt\", fonction \"ajouterHighscore\"");

		/* On ecrit toutes les informations du highscore */
		ecrireInformationHighscore(fichierHighscore, baseHighscore);

		/* On ferme le fichier "Highscore.txt" */
		fermerFichier(fichierHighscore,
		"fichier \"Highscore.txt\", fonction \"ajouterHighscore\"");
	}
}

/* Affiche le highscore et retourne au menu principal */
void highscore(void)
{
	/* On affiche le highscore */
	afficherHighscore();

	appuyezEntree("Appuyez sur ENTREE pour revenir au menu principal...");

	/* On revient au menu principal */
	menuPrincipal();
}
