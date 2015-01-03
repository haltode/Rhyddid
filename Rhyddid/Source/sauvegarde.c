#include <stdio.h>
#include <string.h>

#include "sauvegarde.h"
#include "couleur.h"
#include "personnage.h"
#include "nouvelleSauvegarde.h"
#include "chargerSauvegarde.h"
#include "supprimerSauvegarde.h"
#include "quitter.h"
#include "menuPrincipal.h"

/* Recupere le nom des sauvegardes */
void recupererNomSauvegarde(char baseNomSauvegarde[NB_SAUVEGARDE][TAILLE_MAX])
{
	FILE *fichierSauvegarde;
	compteur indexSauvegarde;

	/* On ouvre le fichier contenant les noms des sauvegardes */
	fichierSauvegarde = ouvrirFichier("Sauvegarde/nom_sauvegarde.txt", "r",
	"fichier \"nom_sauvegarde.txt\", fonction \"recupererNomSauvegarde\"");

	/* Pour chaque nom de sauvegarde */
	for(indexSauvegarde = 0; indexSauvegarde < NB_SAUVEGARDE; ++indexSauvegarde)
		/* On lit le nom de sauvegarde et on l'enregistre dans baseNomSauvegarde */
		lire(fichierSauvegarde, baseNomSauvegarde[indexSauvegarde]);

	/* On ferme le fichier contenant les noms des sauvegardes */
	fermerFichier(fichierSauvegarde,
	"fichier \"nom_sauvegarde.txt\", fonction \"recupererNomSauvegarde\"");
}

/* Recupere les informations du personnage nomPersonnage */
void recupererInformationPersonnage(const char *nomPersonnage)
{
	FILE *infoPersonnage;
	char chemin[TAILLE_MAX];

	sprintf(chemin, "Sauvegarde/%s/detail_personnage.txt", nomPersonnage);

	/* On ouvre le fichier contenant les infos sur le personnage */
	infoPersonnage = ouvrirFichier(chemin, "r", 
	"fichier \"detail_personnage.txt\", fonction \"recupererInformationPersonnage\"");

	/* On lit toutes les informations du personnage (nom, race, EXP etc.) */

	lire(infoPersonnage, personnage.nom);
	lire(infoPersonnage, personnage.race);
	fscanf(infoPersonnage, "%d\n", &(personnage.niveauEXPActuel));
	fscanf(infoPersonnage, "%d\n", &(personnage.niveauActuel));
	fscanf(infoPersonnage, "%d\n", &(personnage.lvl));
	lire(infoPersonnage, personnage.metier);
	fscanf(infoPersonnage, "%d\n", &(personnage.sante));
	fscanf(infoPersonnage, "%d\n", &(personnage.santeActuelle));
	fscanf(infoPersonnage, "%d\n", &(personnage.protection));
	fscanf(infoPersonnage, "%d\n", &(personnage.degatParTour));
	fscanf(infoPersonnage, "%d\n", &(personnage.attaque.aAttaqueEnnemi));
	fscanf(infoPersonnage, "%d\n", &(personnage.attaque.indexEnnemiAttaque));

	/* On ferme le fichier contenant les infos sur le personnage */
	fermerFichier(infoPersonnage, 
	"fichier \"detail_personnage.txt\", fonction \"recupererInformationPersonnage\"");
}

/* Affiche les informations sur le personnage */
void afficherInformationPersonnageSauvegarde(void)
{
	coloration(personnage.nom, BLEU);
	couleur(VERT);
	printf("\tNiv. %d\n", personnage.niveauActuel);
	printf("\t    %s\tLVL %d\n", personnage.race, personnage.lvl);
	printf("\t    %s\tEXP %d/%d\n\n", personnage.metier, personnage.niveauEXPActuel, NB_EXP_NIVEAU_MAX);

	couleur(BLANC);
}

/* Affiche le menu sauvegarde */
void afficherMenuSauvegarde(char baseNomSauvegarde[NB_SAUVEGARDE][TAILLE_MAX])
{
	compteur indexSauvegarde;

	/* On recupere le nom des sauvegardes */
	recupererNomSauvegarde(baseNomSauvegarde);

	/* Pour chaque sauvegarde */
	for(indexSauvegarde = 0; indexSauvegarde < NB_SAUVEGARDE; ++indexSauvegarde)
	{
		/* Si la sauvegarde indexSauvegarde est vide */
		if(strcmp(baseNomSauvegarde[indexSauvegarde], "Vide") == 0)
		{
			/* On affiche les infos d'une sauvegarde vide */

			printf("\t%d - ", indexSauvegarde + 1);
			coloration("Vide", BLEU);
			printf("\n\n");
		}
		/* Sinon */
		else
		{	
			/* On affiche les infos d'une sauvegarde non vide */

			printf("\t%d - ", indexSauvegarde + 1);

			/* On recupere les informations du personnage indexSauvegarde */
			recupererInformationPersonnage(baseNomSauvegarde[indexSauvegarde]);
			/* On affiche les informations du personnage */
			afficherInformationPersonnageSauvegarde();
		}
	}

	putchar('\n');
}

/* Permet de faire une action (charger ou supprimer) sur la sauvegarde indexSauvegarde */
void actionSauvegarde(char baseNomSauvegarde[NB_SAUVEGARDE][TAILLE_MAX],
	const unsigned int indexSauvegarde)
{
	/* Si c'est un emplacement de sauvegarde vide, on cree directement une 
	nouvelle sauvegarde */
	if(strcmp(baseNomSauvegarde[indexSauvegarde], "Vide") == 0)
		nouvelleSauvegarde(indexSauvegarde);
	/* Sinon, on demande ce que l'utilisateur veut faire (charger ou supprimer) */
	else
	{
		int choixJoueur;
		unsigned int compteurErreur;

		compteurErreur = 0;

		separationTexte();

		/* On affiche ce que le joueur peut faire tant qu'il n'a pas entrer un bon
		nombre */
		
		do
		{
			if(compteurErreur > 0)
				printf("Veuillez entrer un nombre correct !\n");

			printf("Que souhaitez-vous faire ?\n\n");
			printf("\t1 - Charger\n");
			printf("\t2 - Supprimer\n\n");

			choixJoueur = choisirMenu(NB_ACTION_SAUVEGARDE);

			++compteurErreur;

		} while (choixJoueur != QUITTER &&
			 choixJoueur != REVENIR_ARRIERE &&
			 choixJoueur != CHARGER &&
			 choixJoueur != SUPPRIMER);
		

		/* Si l'utilisateur veut quitter */
		if(choixJoueur == QUITTER)
			/* On appelle la fonction quitter */
			quitter();
		/* Sinon si l'utilisateur veut revenir en arriere */
		else if(choixJoueur == REVENIR_ARRIERE)
			/* On appelle la fonction sauvegarde */
			sauvegarde();
		/* Si l'utilisateur veut charger la sauvegarde indexSauvegarde */
		else if(choixJoueur == CHARGER)
			/* On appelle la fonction chargerSauvegarde */
			chargerSauvegarde(baseNomSauvegarde[indexSauvegarde]);
		/* Sinon (l'utilisateur veut supprimer la sauvegarde indexSauvegarde) */
		else
			/* On appelle la fonction supprimerSauvegarde */
			supprimerSauvegarde(baseNomSauvegarde[indexSauvegarde]);
	}
}

/* Menu sauvegarde */
void sauvegarde(void)
{
	int choixJoueur;
	char baseNomSauvegarde[NB_SAUVEGARDE][TAILLE_MAX];

	titre("Sauvegarde", VERT);

	/* On affiche le menu sauvegarde */
	afficherMenuSauvegarde(baseNomSauvegarde);
	/* On demande ce que le joueur veut faire */
	choixJoueur = choisirMenu(NB_SAUVEGARDE);

	/* S'il veut retourner en arriere */
	if(choixJoueur == REVENIR_ARRIERE)
		/* On appelle menuPrincipal */
		menuPrincipal();
	/* Sinon s'il veut quitter */
	else if(choixJoueur == QUITTER)
		/* On appelle quitter */
		quitter();
	/* Sinon */
	else
		/* On execute ce qu'il veut faire */
		actionSauvegarde(baseNomSauvegarde, choixJoueur - 1);
}
