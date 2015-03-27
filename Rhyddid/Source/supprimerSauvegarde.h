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

void viderDossierNiveauSauvegardeSalle(const char *nomPartie);
void viderDossierNiveauSauvegardeCaverne(const char *nomPartie);
void viderDossierNiveauSauvegarde(const char *nomPartie);
void viderDossierInventaireSauvegarde(const char *nomPartie);
void viderDossierSauvegarde(const char *nomPartie);


void supprimerNomSauvegarde(const char *nomPartie);


void supprimerSauvegardePartie(const char *nomPartie);


void supprimerSauvegarde(const char *nomPartie);

/* ----- Declaration ----- */

#endif
