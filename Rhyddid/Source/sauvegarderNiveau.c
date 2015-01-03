#include <stdio.h>

#include "sauvegarderNiveau.h"
#include "niveau.h"
#include "personnage.h"
#include "deplacement.h"
#include "fonctionsUtiles.h"
#include "couleur.h"
#include "effacer.h"
#include "creerDossier.h"
#include "jeu.h"
#include "inventaire.h"
#include "quitter.h"

/* Cree les dossiers necessaires pour la sauvegarde */
void creerDossierNecessaireSauvegardeNiveau(void)
{
	char chemin[TAILLE_MAX];
	compteur indexSalle;

	sprintf(chemin, "Sauvegarde/%s/Niveau", personnage.nom);

	creerNouveauDossier(chemin);

	for(indexSalle = 0; indexSalle < NB_SALLE_NIVEAU; ++indexSalle)
	{
		sprintf(chemin, "Sauvegarde/%s/Niveau/Salle_%d", personnage.nom, indexSalle + 1);
		creerNouveauDossier(chemin);
	}

	sprintf(chemin, "Sauvegarde/%s/Niveau/Caverne", personnage.nom);

	creerNouveauDossier(chemin);
}

/* Sauvegarde la forme de la salle indexSalle */
void sauvegarderFormeSalleIndividuelleNiveau(const unsigned int indexSalle)
{
	FILE *salle;
	char chemin[TAILLE_MAX];
	compteur indexLig, indexCol;

	sprintf(chemin, "Sauvegarde/%s/Niveau/Salle_%d/salle_%d.txt", personnage.nom, indexSalle + 1, indexSalle + 1);

	/* On ouvre le fichier contenant la forme de la salle */
	salle = ouvrirFichier(chemin, "w+",
	"fichier \"salle\", fonction \"sauvegarderFormeSalleIndividuelleNiveau\"");

	/* Pour chaque ligne de la salle */
	for(indexLig = 0; indexLig < LARGUEUR_SALLE; ++indexLig)
	{
		/* Pour chaque colonne de la salle */
		for(indexCol = 0; indexCol < LONGUEUR_SALLE; ++indexCol)
		{
			/* On la sauvegarde dans le fichier */
			fprintf(salle, "%c", niveauActuel.salle[indexSalle].mapSalle[indexLig][indexCol]);
		}
		
		fprintf(salle, "\n");
	}	

	/* On ferme le fichier contenant la forme de la salle */
	fermerFichier(salle,
	"fichier \"salle\", fonction \"sauvegarderFormeSalleIndividuelleNiveau\"");
}

/* Sauvegarde les infos de la salle indexSalle (nbCoffre, nbEnnemi, caracteristique ennemi 
etc.) */
void sauvegarderInfoSalleIndiviuelleNiveau(const unsigned int indexSalle)
{	
	FILE *infoSalle, *infoEnnemi;
	char chemin[TAILLE_MAX];
	compteur indexEnnemi;

	sprintf(chemin, "Sauvegarde/%s/Niveau/Salle_%d/info_salle.txt", personnage.nom, indexSalle + 1);

	/* On ouvre le fichier contenant les infos de la salle */
	infoSalle = ouvrirFichier(chemin, "w+",
	"fichier \"info_salle.txt\", fonction \"sauvegarderInfoSalleIndiviuelleNiveau\"");

	/* On ecrit les infos de la salle */

	fprintf(infoSalle, "%d\n", niveauActuel.salle[indexSalle].nbCoffre);
	fprintf(infoSalle, "%d\n", niveauActuel.salle[indexSalle].nbEnnemi);

	/* On ferme le fichier contenant les infos de la salle */
	fermerFichier(infoSalle,
	"fichier \"info_salle.txt\", fonction \"sauvegarderInfoSalleIndiviuelleNiveau\"");


	sprintf(chemin, "Sauvegarde/%s/Niveau/Salle_%d/info_ennemi.txt", personnage.nom, indexSalle + 1);

	/* On ouvre le fichier contenant les infos des ennemis de la salle */
	infoEnnemi = ouvrirFichier(chemin, "w+",
	"fichier \"info_ennemi.txt\", fonction \"sauvegarderInfoSalleIndiviuelleNiveau\"");

	/* Pour chaque ennemi */
	for(indexEnnemi = 0; indexEnnemi < niveauActuel.salle[indexSalle].nbEnnemi; ++indexEnnemi)
	{
		/* On ecrit ses caracteristiques */

		fprintf(infoEnnemi, "%d\n", niveauActuel.salle[indexSalle].ennemi[indexEnnemi].position[LIG]);
		fprintf(infoEnnemi, "%d\n", niveauActuel.salle[indexSalle].ennemi[indexEnnemi].position[COL]);

		fprintf(infoEnnemi, "%d\n", niveauActuel.salle[indexSalle].ennemi[indexEnnemi].nbVie);
		fprintf(infoEnnemi, "%d\n", niveauActuel.salle[indexSalle].ennemi[indexEnnemi].degatAttaque);
		fprintf(infoEnnemi, "%d\n", niveauActuel.salle[indexSalle].ennemi[indexEnnemi].protection);
		fprintf(infoEnnemi, "%d\n", niveauActuel.salle[indexSalle].ennemi[indexEnnemi].porteeAttaque);

		fprintf(infoEnnemi, "%d\n", niveauActuel.salle[indexSalle].ennemi[indexEnnemi].estModeFocus);
		fprintf(infoEnnemi, "%d\n", niveauActuel.salle[indexSalle].ennemi[indexEnnemi].nbTourFocus);
		fprintf(infoEnnemi, "%d\n\n", niveauActuel.salle[indexSalle].ennemi[indexEnnemi].nbTourAttendreFocus);
	}

	/* On ferme le fichier contenant les infos des ennemis de la salle */
	fermerFichier(infoEnnemi,
	"fichier \"info_ennemi.txt\", fonction \"sauvegarderInfoSalleIndiviuelleNiveau\"");
}

/* Sauvegarde la caverne du niveau */
void sauvegarderCaverneNiveau(void)
{
	FILE *infoCaverne;
	char chemin[TAILLE_MAX];
	compteur indexLig, indexEnnemi;

	sprintf(chemin, "Sauvegarde/%s/Niveau/Caverne/info_caverne.txt", personnage.nom);

	/* On ouvre le fichier contenant toutes les infos sur la caverne */
	infoCaverne = ouvrirFichier(chemin, "w+",
	"fichier \"info_caverne.txt\", fonction \"sauvegarderCaverneNiveau\"");

	/* On ecrit les infos principales sur la caverne */
	fprintf(infoCaverne, "%d\n", niveauActuel.salleCaverne);
	fprintf(infoCaverne, "%d\n", niveauActuel.estDansCaverne);

	/* Si il y a une caverne dans le niveau */
	if(niveauActuel.salleCaverne != -1)
	{
		/* On ecrit les caracteristiques de la caverne (position, forme, ennemi) */

		/* Position */

		fprintf(infoCaverne, "%d\n", niveauActuel.salle[niveauActuel.salleCaverne].caverne.directionEntree);
		fprintf(infoCaverne, "%d\n", niveauActuel.salle[niveauActuel.salleCaverne].caverne.ligDebut);
		fprintf(infoCaverne, "%d\n", niveauActuel.salle[niveauActuel.salleCaverne].caverne.colDebut);
		
		/* Forme */

		for(indexLig = 0; indexLig < LARGUEUR_SALLE; ++indexLig)
			fprintf(infoCaverne, "%s", niveauActuel.salle[niveauActuel.salleCaverne].caverne.mapSalle[indexLig]);

		/* Ennemi */

		fprintf(infoCaverne, "%d\n", niveauActuel.salle[niveauActuel.salleCaverne].caverne.nbEnnemi);

		for(indexEnnemi = 0; indexEnnemi < niveauActuel.salle[niveauActuel.salleCaverne].caverne.nbEnnemi; ++indexEnnemi)
		{
			fprintf(infoCaverne, "%d\n", niveauActuel.salle[niveauActuel.salleCaverne].caverne.ennemi[indexEnnemi].position[LIG]);
			fprintf(infoCaverne, "%d\n", niveauActuel.salle[niveauActuel.salleCaverne].caverne.ennemi[indexEnnemi].position[COL]);

			fprintf(infoCaverne, "%d\n", niveauActuel.salle[niveauActuel.salleCaverne].caverne.ennemi[indexEnnemi].nbVie);
			fprintf(infoCaverne, "%d\n", niveauActuel.salle[niveauActuel.salleCaverne].caverne.ennemi[indexEnnemi].degatAttaque);
			fprintf(infoCaverne, "%d\n", niveauActuel.salle[niveauActuel.salleCaverne].caverne.ennemi[indexEnnemi].protection);
			fprintf(infoCaverne, "%d\n", niveauActuel.salle[niveauActuel.salleCaverne].caverne.ennemi[indexEnnemi].porteeAttaque);

			fprintf(infoCaverne, "%d\n", niveauActuel.salle[niveauActuel.salleCaverne].caverne.ennemi[indexEnnemi].estModeFocus);
			fprintf(infoCaverne, "%d\n", niveauActuel.salle[niveauActuel.salleCaverne].caverne.ennemi[indexEnnemi].nbTourFocus);
			fprintf(infoCaverne, "%d\n\n", niveauActuel.salle[niveauActuel.salleCaverne].caverne.ennemi[indexEnnemi].nbTourAttendreFocus);
		}
	}

	/* On ferme le fichier contenant toutes les infos sur la caverne */
	fermerFichier(infoCaverne,
	"fichier \"info_caverne.txt\", fonction \"sauvegarderCaverneNiveau\"");
}

/* Sauvegarde les salles d'un niveau deja genere */
void sauvegarderSalleNiveau(void)
{
	compteur indexSalle;
	
	/* Pour chaque salle */
	for(indexSalle = 0; indexSalle < NB_SALLE_NIVEAU; ++indexSalle)
	{
		/* On sauvegarde la forme de la salle */
		sauvegarderFormeSalleIndividuelleNiveau(indexSalle);
		/* On sauvegarde les infos de la salle */
		sauvegarderInfoSalleIndiviuelleNiveau(indexSalle);
	}

	/* On sauvegarde la caverne du niveau */
	sauvegarderCaverneNiveau();
}

/* Sauvegarde la position du joueur dans le niveau deja genere */
void sauvegarderPositionJoueurNiveau(void)
{
	FILE *position;
	char chemin[TAILLE_MAX];

	sprintf(chemin, "Sauvegarde/%s/Niveau/position_joueur.txt", personnage.nom);

	/* On ouvre le fichier contenant la position du joueur */
	position = ouvrirFichier(chemin, "w+",
	"fichier \"position_joueur.txt\", fonction \"sauvegarderPositionJoueurNiveau\"");

	/* On ecrit la position du joueur */

	fprintf(position, "%d\n", personnage.positionJoueur[LIG]);
	fprintf(position, "%d\n", personnage.positionJoueur[COL]);

	/* On ferme le fichier contenant la position du joueur */
	fermerFichier(position,
	"fichier \"position_joueur.txt\", fonction \"sauvegarderPositionJoueurNiveau\"");


	sprintf(chemin, "Sauvegarde/%s/Niveau/salle_actuelle.txt", personnage.nom);

	/* On ouvre le fichier contenant la salle actuelle ou se trouve le joueur */
	position = ouvrirFichier(chemin, "w+",
	"fichier \"salle_actuelle.txt\", fonction \"sauvegarderPositionJoueurNiveau\"");

	/* On ecrit l'index de la salle ou se trouve le joueur */
	fprintf(position, "%d\n", niveauActuel.salleActuelle);

	/* On ferme le fichier contenant la salle actuelle ou se trouve le joueur */
	fermerFichier(position,
	"fichier \"salle_actuelle.txt\", fonction \"sauvegarderPositionJoueurNiveau\"");
}

/* Sauvegarde le niveau actuel */
void sauvegarderNiveauActuel(void)
{
	/* Si c'est une nouvelle partie on cree les dossier necessaires a la sauvegarde du niveau */
	if(estNouvellePartie())
		creerDossierNecessaireSauvegardeNiveau();
	
	/* On sauvegarde le niveau */
	sauvegarderSalleNiveau();
	sauvegarderPositionJoueurNiveau();

	/* On sauvegarde le personnage */
	sauvegarderPersonnage();

	/* On sauvegarde l'inventaire*/
	sauvegarderInventaire();
}

/* Sauvegarde le niveau et quitte le jeu */
void sauvegarderEtQuitterNiveau(void)
{
	unsigned int choixJoueur;

	effacer();
	titre("Sauvegarder et Quitter", VERT);

	/* On demande la confirmation du joueur */
	choixJoueur = demanderConfirmation("Voulez-vous vraiment sauvegarder et quitter le niveau ici ? (0/1)", PAS_SEPARATION);

	/* S'il veut bien sauvegarder et quitter le niveau */
	if(choixJoueur == OUI)
	{
		/* On sauvegarde le niveau */
		sauvegarderNiveauActuel();
		/* On affiche un texte indiquant la fin de la sauvegarde */
		coloration("\nSauvegarde terminee...\n", VERT);

		/* On quitte */
		quitter();
	}
}

/* Sauvegarde le niveau */
void sauvegarderNiveau(void)
{
	/* On sauvegarde le niveau */
	sauvegarderNiveauActuel();

	/* On affiche un message indiquant la fin de la sauvegarde du niveau */
	ajouterMessageZoneInformation("Sauvegarde terminee...", VERT);
}
