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

void sauvegarderFormeSalleIndividuelleNiveau(const unsigned int indexSalle)
{
	FILE *salle;
	char chemin[TAILLE_MAX];
	compteur indexLig, indexCol;

	sprintf(chemin, "Sauvegarde/%s/Niveau/Salle_%d/salle_%d.txt", personnage.nom, indexSalle + 1, indexSalle + 1);

	salle = ouvrirFichier(chemin, "w+",
	"fichier \"salle\", fonction \"sauvegarderFormeSalleIndividuelleNiveau\"");

	for(indexLig = 0; indexLig < LARGUEUR_SALLE; ++indexLig)
	{
		for(indexCol = 0; indexCol < LONGUEUR_SALLE; ++indexCol)
			fprintf(salle, "%c", niveauActuel.salle[indexSalle].mapSalle[indexLig][indexCol]);
		
		fprintf(salle, "\n");
	}	

	fermerFichier(salle,
	"fichier \"salle\", fonction \"sauvegarderFormeSalleIndividuelleNiveau\"");
}

void sauvegarderInfoSalleIndiviuelleNiveau(const unsigned int indexSalle)
{	
	FILE *infoSalle, *infoEnnemi;
	char chemin[TAILLE_MAX];
	compteur indexEnnemi;

	sprintf(chemin, "Sauvegarde/%s/Niveau/Salle_%d/info_salle.txt", personnage.nom, indexSalle + 1);

	infoSalle = ouvrirFichier(chemin, "w+",
	"fichier \"info_salle.txt\", fonction \"sauvegarderInfoSalleIndiviuelleNiveau\"");

	fprintf(infoSalle, "%d\n", niveauActuel.salle[indexSalle].nbCoffre);
	fprintf(infoSalle, "%d\n", niveauActuel.salle[indexSalle].nbEnnemi);

	fermerFichier(infoSalle,
	"fichier \"info_salle.txt\", fonction \"sauvegarderInfoSalleIndiviuelleNiveau\"");

	sprintf(chemin, "Sauvegarde/%s/Niveau/Salle_%d/info_ennemi.txt", personnage.nom, indexSalle + 1);

	infoEnnemi = ouvrirFichier(chemin, "w+",
	"fichier \"info_ennemi.txt\", fonction \"sauvegarderInfoSalleIndiviuelleNiveau\"");

	for(indexEnnemi = 0; indexEnnemi < niveauActuel.salle[indexSalle].nbEnnemi; ++indexEnnemi)
	{
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

	fermerFichier(infoEnnemi,
	"fichier \"info_ennemi.txt\", fonction \"sauvegarderInfoSalleIndiviuelleNiveau\"");
}

void sauvegarderCaverneNiveau(void)
{
	FILE *infoCaverne;
	char chemin[TAILLE_MAX];
	compteur indexLig, indexEnnemi;

	sprintf(chemin, "Sauvegarde/%s/Niveau/Caverne/info_caverne.txt", personnage.nom);

	infoCaverne = ouvrirFichier(chemin, "w+",
	"fichier \"info_caverne.txt\", fonction \"sauvegarderCaverneNiveau\"");

	fprintf(infoCaverne, "%d\n", niveauActuel.salleCaverne);
	fprintf(infoCaverne, "%d\n", niveauActuel.estDansCaverne);

	if(niveauActuel.salleCaverne != -1)
	{
		fprintf(infoCaverne, "%d\n", niveauActuel.salle[niveauActuel.salleCaverne].caverne.directionEntree);
		fprintf(infoCaverne, "%d\n", niveauActuel.salle[niveauActuel.salleCaverne].caverne.ligDebut);
		fprintf(infoCaverne, "%d\n", niveauActuel.salle[niveauActuel.salleCaverne].caverne.colDebut);
		
		for(indexLig = 0; indexLig < LARGUEUR_SALLE; ++indexLig)
			fprintf(infoCaverne, "%s", niveauActuel.salle[niveauActuel.salleCaverne].caverne.mapSalle[indexLig]);

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

	fermerFichier(infoCaverne,
	"fichier \"info_caverne.txt\", fonction \"sauvegarderCaverneNiveau\"");
}

void sauvegarderSalleNiveau(void)
{
	compteur indexSalle;
	
	for(indexSalle = 0; indexSalle < NB_SALLE_NIVEAU; ++indexSalle)
	{
		sauvegarderFormeSalleIndividuelleNiveau(indexSalle);
		sauvegarderInfoSalleIndiviuelleNiveau(indexSalle);
	}

	sauvegarderCaverneNiveau();
}

void sauvegarderPositionJoueurNiveau(void)
{
	FILE *position;
	char chemin[TAILLE_MAX];

	sprintf(chemin, "Sauvegarde/%s/Niveau/position_joueur.txt", personnage.nom);

	position = ouvrirFichier(chemin, "w+",
	"fichier \"position_joueur.txt\", fonction \"sauvegarderPositionJoueurNiveau\"");

	fprintf(position, "%d\n", personnage.positionJoueur[LIG]);
	fprintf(position, "%d\n", personnage.positionJoueur[COL]);

	fermerFichier(position,
	"fichier \"position_joueur.txt\", fonction \"sauvegarderPositionJoueurNiveau\"");

	sprintf(chemin, "Sauvegarde/%s/Niveau/salle_actuelle.txt", personnage.nom);

	position = ouvrirFichier(chemin, "w+",
	"fichier \"salle_actuelle.txt\", fonction \"sauvegarderPositionJoueurNiveau\"");

	fprintf(position, "%d\n", niveauActuel.salleActuelle);

	fermerFichier(position,
	"fichier \"salle_actuelle.txt\", fonction \"sauvegarderPositionJoueurNiveau\"");
}

void sauvegarderNiveauActuel(void)
{
	if(estNouvellePartie())
		creerDossierNecessaireSauvegardeNiveau();
	
	sauvegarderSalleNiveau();
	sauvegarderPositionJoueurNiveau();
	sauvegarderPersonnage();
	sauvegarderInventaire();
}

void sauvegarderEtQuitterNiveau(void)
{
	unsigned int choixJoueur;

	effacer();
	titre("Sauvegarder et Quitter", VERT);

	choixJoueur = demanderConfirmation("Voulez-vous vraiment sauvegarder et quitter le niveau ici ? (0/1)", PAS_SEPARATION);

	if(choixJoueur == OUI)
	{
		sauvegarderNiveauActuel();
		coloration("\nSauvegarde terminee...\n", VERT);
		quitter();
	}
}

void sauvegarderNiveau(void)
{
	sauvegarderNiveauActuel();
	ajouterMessageZoneInformation("Sauvegarde terminee...", VERT);
}
