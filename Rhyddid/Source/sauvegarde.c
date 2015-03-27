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

void recupererNomSauvegarde(char baseNomSauvegarde[NB_SAUVEGARDE][TAILLE_MAX])
{
	FILE *fichierSauvegarde;
	compteur indexSauvegarde;

	fichierSauvegarde = ouvrirFichier("Sauvegarde/nom_sauvegarde.txt", "r",
	"fichier \"nom_sauvegarde.txt\", fonction \"recupererNomSauvegarde\"");

	for(indexSauvegarde = 0; indexSauvegarde < NB_SAUVEGARDE; ++indexSauvegarde)
		lire(fichierSauvegarde, baseNomSauvegarde[indexSauvegarde]);

	fermerFichier(fichierSauvegarde,
	"fichier \"nom_sauvegarde.txt\", fonction \"recupererNomSauvegarde\"");
}

void recupererInformationPersonnage(const char *nomPersonnage)
{
	FILE *infoPersonnage;
	char chemin[TAILLE_MAX];

	sprintf(chemin, "Sauvegarde/%s/detail_personnage.txt", nomPersonnage);

	infoPersonnage = ouvrirFichier(chemin, "r", 
	"fichier \"detail_personnage.txt\", fonction \"recupererInformationPersonnage\"");

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

	fermerFichier(infoPersonnage, 
	"fichier \"detail_personnage.txt\", fonction \"recupererInformationPersonnage\"");
}

void afficherInformationPersonnageSauvegarde(void)
{
	coloration(personnage.nom, BLEU);
	couleur(VERT);
	printf("\tNiv. %d\n", personnage.niveauActuel);
	printf("\t    %s\tLVL %d\n", personnage.race, personnage.lvl);
	printf("\t    %s\tEXP %d/%d\n\n", personnage.metier, personnage.niveauEXPActuel, NB_EXP_NIVEAU_MAX);

	couleur(BLANC);
}

void afficherMenuSauvegarde(char baseNomSauvegarde[NB_SAUVEGARDE][TAILLE_MAX])
{
	compteur indexSauvegarde;

	recupererNomSauvegarde(baseNomSauvegarde);

	for(indexSauvegarde = 0; indexSauvegarde < NB_SAUVEGARDE; ++indexSauvegarde)
	{
		if(strcmp(baseNomSauvegarde[indexSauvegarde], "Vide") == 0)
		{
			printf("\t%d - ", indexSauvegarde + 1);
			coloration("Vide", BLEU);
			printf("\n\n");
		}
		else
		{	
			printf("\t%d - ", indexSauvegarde + 1);

			recupererInformationPersonnage(baseNomSauvegarde[indexSauvegarde]);
			afficherInformationPersonnageSauvegarde();
		}
	}

	putchar('\n');
}

void actionSauvegarde(char baseNomSauvegarde[NB_SAUVEGARDE][TAILLE_MAX],
	const unsigned int indexSauvegarde)
{
	if(strcmp(baseNomSauvegarde[indexSauvegarde], "Vide") == 0)
		nouvelleSauvegarde(indexSauvegarde);
	else
	{
		int choixJoueur;
		unsigned int compteurErreur;

		compteurErreur = 0;

		separationTexte();
		
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
		

		if(choixJoueur == QUITTER)
			quitter();
		else if(choixJoueur == REVENIR_ARRIERE)
			sauvegarde();
		else if(choixJoueur == CHARGER)
			chargerSauvegarde(baseNomSauvegarde[indexSauvegarde]);
		else
			supprimerSauvegarde(baseNomSauvegarde[indexSauvegarde]);
	}
}

void sauvegarde(void)
{
	int choixJoueur;
	char baseNomSauvegarde[NB_SAUVEGARDE][TAILLE_MAX];

	titre("Sauvegarde", VERT);

	afficherMenuSauvegarde(baseNomSauvegarde);
	choixJoueur = choisirMenu(NB_SAUVEGARDE);

	if(choixJoueur == REVENIR_ARRIERE)
		menuPrincipal();
	else if(choixJoueur == QUITTER)
		quitter();
	else
		actionSauvegarde(baseNomSauvegarde, choixJoueur - 1);
}
