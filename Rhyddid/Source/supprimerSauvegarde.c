#include <stdio.h>
#include <string.h>

#include "supprimerSauvegarde.h"
#include "fonctionsUtiles.h"
#include "sauvegarde.h"
#include "niveau.h"

/* Vide tous les fichiers du dossier de sauvegarde Niveau concernant les salles du niveau */
void viderDossierNiveauSauvegardeSalle(const char *nomPartie)
{
	char chemin[TAILLE_MAX];
	compteur indexSalle;

	/* Pour chaque salle du niveau */
	for(indexSalle = 0; indexSalle < NB_SALLE_NIVEAU; ++indexSalle)
	{
		/* On supprime les fichiers salle_indexSalle.txt, info_salle.txt, info_ennemi.txt */

		sprintf(chemin, "Sauvegarde/%s/Niveau/Salle_%d/salle_%d.txt", nomPartie, indexSalle + 1, indexSalle + 1);
		remove(chemin);

		sprintf(chemin, "Sauvegarde/%s/Niveau/Salle_%d/info_salle.txt", nomPartie, indexSalle + 1);
		remove(chemin);

		sprintf(chemin, "Sauvegarde/%s/Niveau/Salle_%d/info_ennemi.txt", nomPartie, indexSalle + 1);
		remove(chemin);

		/* On supprime le dossier vide Salle_indexSalle */

		sprintf(chemin, "Sauvegarde/%s/Niveau/Salle_%d", nomPartie, indexSalle + 1);
		rmdir(chemin);
	}
}

/* Vide tous les fichiers du dossier de sauvegarde Niveau concernant la caverne du niveau */
void viderDossierNiveauSauvegardeCaverne(const char *nomPartie)
{
	char chemin[TAILLE_MAX];

	/* On supprime le fichier info_caverne.txt */

	sprintf(chemin, "Sauvegarde/%s/Niveau/Caverne/info_caverne.txt", nomPartie);
	remove(chemin);

	/* On supprime le dossier vide Caverne */

	sprintf(chemin, "Sauvegarde/%s/Niveau/Caverne", nomPartie);
	rmdir(chemin);
}

/* Vide le dossier de sauvegarde Niveau de la partie nomPartie */
void viderDossierNiveauSauvegarde(const char *nomPartie)
{
	char chemin[TAILLE_MAX];

	viderDossierNiveauSauvegardeSalle(nomPartie);
	viderDossierNiveauSauvegardeCaverne(nomPartie);

	/* On supprime le fichier salle_actuelle.txt et position_joueur.txt */

	sprintf(chemin, "Sauvegarde/%s/Niveau/salle_actuelle.txt", nomPartie);
	remove(chemin);
	sprintf(chemin, "Sauvegarde/%s/Niveau/position_joueur.txt", nomPartie);
	remove(chemin);

	/* On supprime le dossier vide Niveau */

	sprintf(chemin, "Sauvegarde/%s/Niveau", nomPartie);
	rmdir(chemin);
}

/* Vide le dossier de sauvegarde Inventaire de la partie nomPartie */
void viderDossierInventaireSauvegarde(const char *nomPartie)
{
	char chemin[TAILLE_MAX];

	/* On supprime les fichiers tek.txt, armure.txt, arme.txt, tresor.txt, potion.txt, cle.txt */

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

	/* On supprime le dossier vide Inventaire */

	sprintf(chemin, "Sauvegarde/%s/Inventaire", nomPartie);
	rmdir(chemin);
}

/* Vide les dossiers de sauvegarde de la partie nomPartie */
void viderDossierSauvegarde(const char *nomPartie)
{
	char chemin[TAILLE_MAX];
	
	/* On supprime le dossier Niveau et son contenu */
	viderDossierNiveauSauvegarde(nomPartie);
	/* On supprime le dossier Inventaire et son contenu */
	viderDossierInventaireSauvegarde(nomPartie);

	/* On supprime le fichier detail_personnage.txt */

	sprintf(chemin, "Sauvegarde/%s/detail_personnage.txt", nomPartie);
	remove(chemin);

	/* On supprime le dossier vide nomPartie */

	sprintf(chemin, "Sauvegarde/%s", nomPartie);
	rmdir(chemin);
}

/* Met a jour le fichier nom_sauvegarde.txt en supprimant le nom de la partie nomPartie du 
fichier */
void supprimerNomSauvegarde(const char *nomPartie)
{
	FILE *nomSauvegarde;
	char chemin[TAILLE_MAX];
	char buffer[NB_SAUVEGARDE][TAILLE_MAX];
	compteur indexLig, indexSauvegarde;

	sprintf(chemin, "Sauvegarde/nom_sauvegarde.txt");

	/* On ouvre le fichier contenant le nom des sauvegardes */
	nomSauvegarde = ouvrirFichier(chemin, "r", 
	"fichier \"nom_sauvegarde.txt\", fonction \"supprimerNomSauvegarde\"");

	/* Pour chaque nom de sauvegarde */
	for(indexLig = 0; indexLig < NB_SAUVEGARDE; ++indexLig)
	{
		/* On lit le nom des sauvegardes et on les stocke dans buffer */
		lire(nomSauvegarde, buffer[indexLig]);

		/* On repere si le nom de la sauvegarde actuelle et le meme que celui que l'on veut
		supprimer (nomPartie) */
		/* Si c'est le cas */
		if(strcmp(buffer[indexLig], nomPartie) == 0)
			/* On enregistre l'index dans indexSauvegarde */
			indexSauvegarde = indexLig;
	}

	/* On met le nom de sauvegarde a l'index indexSauvegarde a "Vide" */
	strcpy(buffer[indexSauvegarde], "Vide");

	/* On ferme le fichier contenant le nom des sauvegardes */
	fermerFichier(nomSauvegarde, 
	"fichier \"nom_sauvegarde.txt\", fonction \"supprimerNomSauvegarde\"");

	sprintf(chemin, "Sauvegarde/nom_sauvegarde.txt");

	/* On ouvre le fichier contenant le nom des sauvegardes */
	nomSauvegarde = ouvrirFichier(chemin, "w+", 
	"fichier \"nom_sauvegarde.txt\", fonction \"supprimerNomSauvegarde\"");

	/* Pour chaque nom de sauvegarde */
	for(indexLig = 0; indexLig < NB_SAUVEGARDE; ++indexLig)
		/* On ecrit le nom des sauvegardes */
		fprintf(nomSauvegarde, "%s\n", buffer[indexLig]);

	/* On ferme le fichier contenant le nom des sauvegardes */
	fermerFichier(nomSauvegarde, 
	"fichier \"nom_sauvegarde.txt\", fonction \"supprimerNomSauvegarde\"");
}

/* Supprime les dossiers de sauvegarde de la partie nomPartie */
void supprimerSauvegardePartie(const char *nomPartie)
{
	/* On vide tous les fichiers et dossiers contenu dans la sauvegarde de nomPartie */
	viderDossierSauvegarde(nomPartie);
	/* On met a jour le fichier nom_sauvegarde.txt en supprimant le nom de la partie nomPartie */
	supprimerNomSauvegarde(nomPartie);
}

/* Supprime une sauvegarde */
void supprimerSauvegarde(const char *nomPartie)
{
	unsigned int confirmation;

	/* On demande confirmation de supprimer la partie */
	confirmation = demanderConfirmation("Etes vous sur de vouloir supprimer cette partie ? (0/1)", SEPARATION);

	/* Si le joueur veut on supprime sa partie */
	if(confirmation == OUI)
	{
		/* On vide tous les fichiers et dossiers contenu dans la sauvegarde de nomPartie */
		viderDossierSauvegarde(nomPartie);
		/* On met a jour le fichier nom_sauvegarde.txt en supprimant le nom de la partie nomPartie */
		supprimerNomSauvegarde(nomPartie);
	}

	/* Si le joueur ne veut pas on retourne tout simplement dans le menu sauvegarde */
	
	/* On retourne dans le menu sauvegarde */
	sauvegarde();
}
