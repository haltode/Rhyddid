#ifndef SUPPRIMER_SAUVEGARDE_H
#define SUPPRIMER_SAUVEGARDE_H

/* supprimerSauvegarde.c/supprimerSauvegarde.h : permet de gerer la suppression d'une 
sauvegarde */

/* ----- A inclure ----- */

#define _OPEN_SYS
#include <unistd.h>

/* ----- Define ----- */


/* ----- Structure + Enumeration ----- */


/* ----- Prototype ----- */

/* Vide tous les fichiers du dossier de sauvegarde Niveau concernant les salles du niveau */
void viderDossierNiveauSauvegardeSalle(const char *nomPartie);
/* Vide tous les fichiers du dossier de sauvegarde Niveau concernant la caverne du niveau */
void viderDossierNiveauSauvegardeCaverne(const char *nomPartie);
/* Vide le dossier de sauvegarde Niveau de la partie nomPartie */
void viderDossierNiveauSauvegarde(const char *nomPartie);
/* Vide le dossier de sauvegarde Inventaire de la partie nomPartie */
void viderDossierInventaireSauvegarde(const char *nomPartie);
/* Vide les dossiers de sauvegarde de la partie nomPartie */
void viderDossierSauvegarde(const char *nomPartie);


/* Met a jour le fichier nom_sauvegarde.txt en supprimant le nom de la partie nomPartie du 
fichier */
void supprimerNomSauvegarde(const char *nomPartie);


/* Supprime les dossiers de sauvegarde de la partie nomPartie */
void supprimerSauvegardePartie(const char *nomPartie);


/* Supprime une sauvegarde */
void supprimerSauvegarde(const char *nomPartie);

/* ----- Declaration ----- */

#endif
