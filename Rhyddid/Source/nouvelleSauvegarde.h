#ifndef NOUVELLE_SAUVEGARDE_H
#define NOUVELLE_SAUVEGARDE_H

/* nouvelleSauvegarde.c/nouvelleSauvegarde.h : permet de gerer les nouvelles 
sauvegardes */

/* ----- A inclure ----- */


/* ----- Define ----- */


/* ----- Structure + Enumeration ----- */


/* ----- Prototype ----- */

void demanderNomNouveauPersonnage(void);


void creerNouveauPersonnage(void);


void creerDossierSauvegardeNouveauPersonnage(void);


void ajouterNomSauvegardeNouvellePartie(const unsigned int indexSauvegarde);


void afficherTexteNouvellePartie(void);


void nouvelleSauvegarde(const unsigned int indexSauvegarde);

/* ----- Declaration ----- */

#endif
