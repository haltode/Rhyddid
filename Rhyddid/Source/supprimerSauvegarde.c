#include <stdio.h>
#include <string.h>

#include "supprimerSauvegarde.h"
#include "fonctionsUtiles.h"
#include "sauvegarde.h"
#include "niveau.h"

void viderDossierNiveauSauvegardeSalle(const char *nomPartie)
{
	char chemin[TAILLE_MAX];
	compteur indexSalle;

	for(indexSalle = 0; indexSalle < NB_SALLE_NIVEAU; ++indexSalle)
	{
		sprintf(chemin, "Sauvegarde/%s/Niveau/Salle_%d/salle_%d.txt", nomPartie, indexSalle + 1, indexSalle + 1);
		remove(chemin);

		sprintf(chemin, "Sauvegarde/%s/Niveau/Salle_%d/info_salle.txt", nomPartie, indexSalle + 1);
		remove(chemin);

		sprintf(chemin, "Sauvegarde/%s/Niveau/Salle_%d/info_ennemi.txt", nomPartie, indexSalle + 1);
		remove(chemin);

		sprintf(chemin, "Sauvegarde/%s/Niveau/Salle_%d", nomPartie, indexSalle + 1);
		rmdir(chemin);
	}
}

void viderDossierNiveauSauvegardeCaverne(const char *nomPartie)
{
	char chemin[TAILLE_MAX];

	sprintf(chemin, "Sauvegarde/%s/Niveau/Caverne/info_caverne.txt", nomPartie);
	remove(chemin);

	sprintf(chemin, "Sauvegarde/%s/Niveau/Caverne", nomPartie);
	rmdir(chemin);
}

void viderDossierNiveauSauvegarde(const char *nomPartie)
{
	char chemin[TAILLE_MAX];

	viderDossierNiveauSauvegardeSalle(nomPartie);
	viderDossierNiveauSauvegardeCaverne(nomPartie);

	sprintf(chemin, "Sauvegarde/%s/Niveau/salle_actuelle.txt", nomPartie);
	remove(chemin);
	sprintf(chemin, "Sauvegarde/%s/Niveau/position_joueur.txt", nomPartie);
	remove(chemin);

	sprintf(chemin, "Sauvegarde/%s/Niveau", nomPartie);
	rmdir(chemin);
}

void viderDossierInventaireSauvegarde(const char *nomPartie)
{
	char chemin[TAILLE_MAX];

	sprintf(chemin, "Sauvegarde/%s/Inventaire/tek.txt", nomPartie);
	remove(chemin);
	sprintf(chemin, "Sauvegarde/%s/Inventaire/armure.txt", nomPartie);
	remove(chemin);
	sprintf(chemin, "Sauvegarde/%s/Inventaire/arme.txt", nomPartie);
	remove(chemin);
	sprintf(chemin, "Sauvegarde/%s/Inventaire/tresor.txt", nomPartie);
	remove(chemin);
	sprintf(chemin, "Sauvegarde/%s/Inventaire/potion.txt", nomPartie);
	remove(chemin);
	sprintf(chemin, "Sauvegarde/%s/Inventaire/cle.txt", nomPartie);
	remove(chemin);

	sprintf(chemin, "Sauvegarde/%s/Inventaire", nomPartie);
	rmdir(chemin);
}

void viderDossierSauvegarde(const char *nomPartie)
{
	char chemin[TAILLE_MAX];
	
	viderDossierNiveauSauvegarde(nomPartie);
	viderDossierInventaireSauvegarde(nomPartie);

	sprintf(chemin, "Sauvegarde/%s/detail_personnage.txt", nomPartie);
	remove(chemin);

	sprintf(chemin, "Sauvegarde/%s", nomPartie);
	rmdir(chemin);
}

void supprimerNomSauvegarde(const char *nomPartie)
{
	FILE *nomSauvegarde;
	char chemin[TAILLE_MAX];
	char buffer[NB_SAUVEGARDE][TAILLE_MAX];
	compteur indexLig, indexSauvegarde;

	sprintf(chemin, "Sauvegarde/nom_sauvegarde.txt");

	nomSauvegarde = ouvrirFichier(chemin, "r", 
	"fichier \"nom_sauvegarde.txt\", fonction \"supprimerNomSauvegarde\"");

	for(indexLig = 0; indexLig < NB_SAUVEGARDE; ++indexLig)
	{
		lire(nomSauvegarde, buffer[indexLig]);

		if(strcmp(buffer[indexLig], nomPartie) == 0)
			indexSauvegarde = indexLig;
	}

	strcpy(buffer[indexSauvegarde], "Vide");

	fermerFichier(nomSauvegarde, 
	"fichier \"nom_sauvegarde.txt\", fonction \"supprimerNomSauvegarde\"");

	sprintf(chemin, "Sauvegarde/nom_sauvegarde.txt");

	nomSauvegarde = ouvrirFichier(chemin, "w+", 
	"fichier \"nom_sauvegarde.txt\", fonction \"supprimerNomSauvegarde\"");

	for(indexLig = 0; indexLig < NB_SAUVEGARDE; ++indexLig)
		fprintf(nomSauvegarde, "%s\n", buffer[indexLig]);

	fermerFichier(nomSauvegarde, 
	"fichier \"nom_sauvegarde.txt\", fonction \"supprimerNomSauvegarde\"");
}

void supprimerSauvegardePartie(const char *nomPartie)
{
	viderDossierSauvegarde(nomPartie);
	supprimerNomSauvegarde(nomPartie);
}

void supprimerSauvegarde(const char *nomPartie)
{
	unsigned int confirmation;

	confirmation = demanderConfirmation("Etes vous sur de vouloir supprimer cette partie ? (0/1)", SEPARATION);

	if(confirmation == OUI)
	{
		viderDossierSauvegarde(nomPartie);
		supprimerNomSauvegarde(nomPartie);
	}
	
	sauvegarde();
}
