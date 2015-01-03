#include <stdio.h>

#include "chargerNiveau.h"
#include "niveau.h"
#include "personnage.h"
#include "deplacement.h"
#include "fonctionsUtiles.h"

/* Charge la forme de la salle indexSalle */
void chargerFormeSalleIndividuelleNiveau(const unsigned int indexSalle)
{
	FILE *salle;
	char chemin[TAILLE_MAX];
	compteur indexLig;

	sprintf(chemin, "Sauvegarde/%s/Niveau/Salle_%d/salle_%d.txt", personnage.nom, indexSalle + 1, indexSalle + 1);

	/* On ouvre le fichier contenant la forme de la salle */
	salle = ouvrirFichier(chemin, "r",
	"fichier \"salle\", fonction \"chargerFormeSalleIndividuelleNiveau\"");

	/* Pour chaque ligne du fichier */
	for(indexLig = 0; indexLig < LARGUEUR_SALLE; ++indexLig)
		/* On la sauvegarde dans le niveau */
		lire(salle, niveauActuel.salle[indexSalle].mapSalle[indexLig]);

	/* On ferme le fichier contenant la forme de la salle */
	fermerFichier(salle,
	"fichier \"salle\", fonction \"chargerFormeSalleIndividuelleNiveau\"");
}

/* Charge les infos de la salle indexSalle (nbCoffre, nbEnnemi, caracteristique ennemi etc.) */
void chargerInfoSalleIndiviuelleNiveau(const unsigned int indexSalle)
{	
	FILE *infoSalle, *infoEnnemi;
	char chemin[TAILLE_MAX];
	compteur indexEnnemi;

	sprintf(chemin, "Sauvegarde/%s/Niveau/Salle_%d/info_salle.txt", personnage.nom, indexSalle + 1);

	/* On ouvre le fichier contenant les infos de la salle */
	infoSalle = ouvrirFichier(chemin, "r",
	"fichier \"info_salle.txt\", fonction \"chargerInfoSalleIndiviuelleNiveau\"");

	/* On lit les infos de la salle et on les sauvegarde dans le niveau */

	fscanf(infoSalle, "%d\n", &(niveauActuel.salle[indexSalle].nbCoffre));
	fscanf(infoSalle, "%d\n", &(niveauActuel.salle[indexSalle].nbEnnemi));

	/* On ferme le fichier contenant les infos de la salle */
	fermerFichier(infoSalle,
	"fichier \"info_salle.txt\", fonction \"chargerInfoSalleIndiviuelleNiveau\"");


	sprintf(chemin, "Sauvegarde/%s/Niveau/Salle_%d/info_ennemi.txt", personnage.nom, indexSalle + 1);

	/* On ouvre le fichier contenant les infos des ennemis de la salle */
	infoEnnemi = ouvrirFichier(chemin, "r",
	"fichier \"info_ennemi.txt\", fonction \"chargerInfoSalleIndiviuelleNiveau\"");

	/* Pour chaque ennemi */
	for(indexEnnemi = 0; indexEnnemi < niveauActuel.salle[indexSalle].nbEnnemi; ++indexEnnemi)
	{
		/* On lit ses caracteristiques et on les sauvegarde dans le niveau */

		fscanf(infoEnnemi, "%d\n", &(niveauActuel.salle[indexSalle].ennemi[indexEnnemi].position[LIG]));
		fscanf(infoEnnemi, "%d\n", &(niveauActuel.salle[indexSalle].ennemi[indexEnnemi].position[COL]));

		fscanf(infoEnnemi, "%d\n", &(niveauActuel.salle[indexSalle].ennemi[indexEnnemi].nbVie));
		fscanf(infoEnnemi, "%d\n", &(niveauActuel.salle[indexSalle].ennemi[indexEnnemi].degatAttaque));
		fscanf(infoEnnemi, "%d\n", &(niveauActuel.salle[indexSalle].ennemi[indexEnnemi].protection));
		fscanf(infoEnnemi, "%d\n", &(niveauActuel.salle[indexSalle].ennemi[indexEnnemi].porteeAttaque));

		fscanf(infoEnnemi, "%d\n", &(niveauActuel.salle[indexSalle].ennemi[indexEnnemi].estModeFocus));
		fscanf(infoEnnemi, "%d\n", &(niveauActuel.salle[indexSalle].ennemi[indexEnnemi].nbTourFocus));
		fscanf(infoEnnemi, "%d\n\n", &(niveauActuel.salle[indexSalle].ennemi[indexEnnemi].nbTourAttendreFocus));
	}

	/* On ferme le fichier contenant les infos des ennemis de la salle */
	fermerFichier(infoEnnemi,
	"fichier \"info_ennemi.txt\", fonction \"chargerInfoSalleIndiviuelleNiveau\"");
}

/* Charge la caverne du niveau */
void chargerCaverneNiveau(void)
{
	FILE *infoCaverne;
	char chemin[TAILLE_MAX];
	compteur indexLig, indexEnnemi;

	sprintf(chemin, "Sauvegarde/%s/Niveau/Caverne/info_caverne.txt", personnage.nom);

	/* On ouvre le fichier contenant toutes les infos sur la caverne */
	infoCaverne = ouvrirFichier(chemin, "r",
	"fichier \"info_caverne.txt\", fonction \"chargerCaverneNiveau\"");

	/* On lit et sauvegarde les infos principales sur la caverne */
	fscanf(infoCaverne, "%d\n", &(niveauActuel.salleCaverne));
	fscanf(infoCaverne, "%d\n", &(niveauActuel.estDansCaverne));

	/* Si il y a une caverne dans le niveau */
	if(niveauActuel.salleCaverne != -1)
	{
		/* On lit les caracteristiques de la caverne (position, forme, ennemi) */

		/* Position */

		fscanf(infoCaverne, "%d\n", &(niveauActuel.salle[niveauActuel.salleCaverne].caverne.directionEntree));
		fscanf(infoCaverne, "%d\n", &(niveauActuel.salle[niveauActuel.salleCaverne].caverne.ligDebut));
		fscanf(infoCaverne, "%d\n", &(niveauActuel.salle[niveauActuel.salleCaverne].caverne.colDebut));
		
		/* Forme */

		for(indexLig = 0; indexLig < LARGUEUR_SALLE; ++indexLig)
			lire(infoCaverne, niveauActuel.salle[niveauActuel.salleCaverne].caverne.mapSalle[indexLig]);

		/* Ennemi */

		fscanf(infoCaverne, "%d\n", &(niveauActuel.salle[niveauActuel.salleCaverne].caverne.nbEnnemi));

		for(indexEnnemi = 0; indexEnnemi < niveauActuel.salle[niveauActuel.salleCaverne].caverne.nbEnnemi; ++indexEnnemi)
		{
			fscanf(infoCaverne, "%d\n", &(niveauActuel.salle[niveauActuel.salleCaverne].caverne.ennemi[indexEnnemi].position[LIG]));
			fscanf(infoCaverne, "%d\n", &(niveauActuel.salle[niveauActuel.salleCaverne].caverne.ennemi[indexEnnemi].position[COL]));

			fscanf(infoCaverne, "%d\n", &(niveauActuel.salle[niveauActuel.salleCaverne].caverne.ennemi[indexEnnemi].nbVie));
			fscanf(infoCaverne, "%d\n", &(niveauActuel.salle[niveauActuel.salleCaverne].caverne.ennemi[indexEnnemi].degatAttaque));
			fscanf(infoCaverne, "%d\n", &(niveauActuel.salle[niveauActuel.salleCaverne].caverne.ennemi[indexEnnemi].protection));
			fscanf(infoCaverne, "%d\n", &(niveauActuel.salle[niveauActuel.salleCaverne].caverne.ennemi[indexEnnemi].porteeAttaque));

			fscanf(infoCaverne, "%d\n", &(niveauActuel.salle[niveauActuel.salleCaverne].caverne.ennemi[indexEnnemi].estModeFocus));
			fscanf(infoCaverne, "%d\n", &(niveauActuel.salle[niveauActuel.salleCaverne].caverne.ennemi[indexEnnemi].nbTourFocus));
			fscanf(infoCaverne, "%d\n\n", &(niveauActuel.salle[niveauActuel.salleCaverne].caverne.ennemi[indexEnnemi].nbTourAttendreFocus));
		}
	}

	/* On ferme le fichier contenant toutes les infos sur la caverne */
	fermerFichier(infoCaverne,
	"fichier \"info_caverne.txt\", fonction \"chargerCaverneNiveau\"");
}

/* Charge les salles d'un niveau deja genere */
void chargerSalleNiveau(void)
{
	compteur indexSalle;
	
	/* Pour chaque salle */
	for(indexSalle = 0; indexSalle < NB_SALLE_NIVEAU; ++indexSalle)
	{
		/* On charge la forme de la salle */
		chargerFormeSalleIndividuelleNiveau(indexSalle);
		/* On charge les infos de la salle */
		chargerInfoSalleIndiviuelleNiveau(indexSalle);
	}

	/* On charge la caverne du niveau */
	chargerCaverneNiveau();
}

/* Charge la position du joueur dans le niveau deja genere */
void chargerPositionJoueurNiveau(void)
{
	FILE *position;
	char chemin[TAILLE_MAX];

	sprintf(chemin, "Sauvegarde/%s/Niveau/position_joueur.txt", personnage.nom);

	/* On ouvre le fichier contenant la position du joueur */
	position = ouvrirFichier(chemin, "r",
	"fichier \"position_joueur.txt\", fonction \"chargerPositionJoueurNiveau\"");

	/* On lit la position du joueur et on la sauvegarde dans positionJoueur */

	fscanf(position, "%d\n", &personnage.positionJoueur[LIG]);
	fscanf(position, "%d\n", &personnage.positionJoueur[COL]);

	/* On ferme le fichier contenant la position du joueur */
	fermerFichier(position,
	"fichier \"position_joueur.txt\", fonction \"chargerPositionJoueurNiveau\"");


	sprintf(chemin, "Sauvegarde/%s/Niveau/salle_actuelle.txt", personnage.nom);

	/* On ouvre le fichier contenant la salle actuelle ou se trouve le joueur */
	position = ouvrirFichier(chemin, "r",
	"fichier \"salle_actuelle.txt\", fonction \"chargerPositionJoueurNiveau\"");

	/* On lit l'index de la salle ou se trouve le joueur et on la sauvegarde dans niveau */
	fscanf(position, "%d\n", &(niveauActuel.salleActuelle));

	/* On ferme le fichier contenant la salle actuelle ou se trouve le joueur */
	fermerFichier(position,
	"fichier \"salle_actuelle.txt\", fonction \"chargerPositionJoueurNiveau\"");
}

/* Charge un niveau deja genere */
void chargerNiveau(void)
{
	/* On charge chaque salle du niveau */
	chargerSalleNiveau();
	/* On charge la position du joueur sur le niveau */
	chargerPositionJoueurNiveau();
}
