#include <stdio.h>

#include "chargerNiveau.h"
#include "niveau.h"
#include "personnage.h"
#include "deplacement.h"
#include "fonctionsUtiles.h"

void chargerFormeSalleIndividuelleNiveau(const unsigned int indexSalle)
{
	FILE *salle;
	char chemin[TAILLE_MAX];
	compteur indexLig;

	sprintf(chemin, "Sauvegarde/%s/Niveau/Salle_%d/salle_%d.txt", personnage.nom, indexSalle + 1, indexSalle + 1);

	salle = ouvrirFichier(chemin, "r",
	"fichier \"salle\", fonction \"chargerFormeSalleIndividuelleNiveau\"");

	for(indexLig = 0; indexLig < LARGUEUR_SALLE; ++indexLig)
		lire(salle, niveauActuel.salle[indexSalle].mapSalle[indexLig]);

	fermerFichier(salle,
	"fichier \"salle\", fonction \"chargerFormeSalleIndividuelleNiveau\"");
}

void chargerInfoSalleIndiviuelleNiveau(const unsigned int indexSalle)
{	
	FILE *infoSalle, *infoEnnemi;
	char chemin[TAILLE_MAX];
	compteur indexEnnemi;

	sprintf(chemin, "Sauvegarde/%s/Niveau/Salle_%d/info_salle.txt", personnage.nom, indexSalle + 1);

	infoSalle = ouvrirFichier(chemin, "r",
	"fichier \"info_salle.txt\", fonction \"chargerInfoSalleIndiviuelleNiveau\"");

	fscanf(infoSalle, "%d\n", &(niveauActuel.salle[indexSalle].nbCoffre));
	fscanf(infoSalle, "%d\n", &(niveauActuel.salle[indexSalle].nbEnnemi));

	fermerFichier(infoSalle,
	"fichier \"info_salle.txt\", fonction \"chargerInfoSalleIndiviuelleNiveau\"");


	sprintf(chemin, "Sauvegarde/%s/Niveau/Salle_%d/info_ennemi.txt", personnage.nom, indexSalle + 1);

	infoEnnemi = ouvrirFichier(chemin, "r",
	"fichier \"info_ennemi.txt\", fonction \"chargerInfoSalleIndiviuelleNiveau\"");

	for(indexEnnemi = 0; indexEnnemi < niveauActuel.salle[indexSalle].nbEnnemi; ++indexEnnemi)
	{
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

	fermerFichier(infoEnnemi,
	"fichier \"info_ennemi.txt\", fonction \"chargerInfoSalleIndiviuelleNiveau\"");
}

void chargerCaverneNiveau(void)
{
	FILE *infoCaverne;
	char chemin[TAILLE_MAX];
	compteur indexLig, indexEnnemi;

	sprintf(chemin, "Sauvegarde/%s/Niveau/Caverne/info_caverne.txt", personnage.nom);

	infoCaverne = ouvrirFichier(chemin, "r",
	"fichier \"info_caverne.txt\", fonction \"chargerCaverneNiveau\"");

	fscanf(infoCaverne, "%d\n", &(niveauActuel.salleCaverne));
	fscanf(infoCaverne, "%d\n", &(niveauActuel.estDansCaverne));

	if(niveauActuel.salleCaverne != -1)
	{
        fscanf(infoCaverne, "%d\n", &(niveauActuel.salle[niveauActuel.salleCaverne].caverne.directionEntree));
		fscanf(infoCaverne, "%d\n", &(niveauActuel.salle[niveauActuel.salleCaverne].caverne.ligDebut));
		fscanf(infoCaverne, "%d\n", &(niveauActuel.salle[niveauActuel.salleCaverne].caverne.colDebut));
		
		for(indexLig = 0; indexLig < LARGUEUR_SALLE; ++indexLig)
			lire(infoCaverne, niveauActuel.salle[niveauActuel.salleCaverne].caverne.mapSalle[indexLig]);

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

	fermerFichier(infoCaverne,
	"fichier \"info_caverne.txt\", fonction \"chargerCaverneNiveau\"");
}

void chargerSalleNiveau(void)
{
	compteur indexSalle;
	
	for(indexSalle = 0; indexSalle < NB_SALLE_NIVEAU; ++indexSalle)
	{
		chargerFormeSalleIndividuelleNiveau(indexSalle);
		chargerInfoSalleIndiviuelleNiveau(indexSalle);
	}

	chargerCaverneNiveau();
}

void chargerPositionJoueurNiveau(void)
{
	FILE *position;
	char chemin[TAILLE_MAX];

	sprintf(chemin, "Sauvegarde/%s/Niveau/position_joueur.txt", personnage.nom);

	position = ouvrirFichier(chemin, "r",
	"fichier \"position_joueur.txt\", fonction \"chargerPositionJoueurNiveau\"");


	fscanf(position, "%d\n", &personnage.positionJoueur[LIG]);
	fscanf(position, "%d\n", &personnage.positionJoueur[COL]);

	fermerFichier(position,
	"fichier \"position_joueur.txt\", fonction \"chargerPositionJoueurNiveau\"");


	sprintf(chemin, "Sauvegarde/%s/Niveau/salle_actuelle.txt", personnage.nom);

	position = ouvrirFichier(chemin, "r",
	"fichier \"salle_actuelle.txt\", fonction \"chargerPositionJoueurNiveau\"");

	fscanf(position, "%d\n", &(niveauActuel.salleActuelle));

	fermerFichier(position,
	"fichier \"salle_actuelle.txt\", fonction \"chargerPositionJoueurNiveau\"");
}

void chargerNiveau(void)
{
	chargerSalleNiveau();
	chargerPositionJoueurNiveau();
}
