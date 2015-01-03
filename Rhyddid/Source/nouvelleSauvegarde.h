#ifndef NOUVELLE_SAUVEGARDE_H
#define NOUVELLE_SAUVEGARDE_H

/* nouvelleSauvegarde.c/nouvelleSauvegarde.h : permet de gerer les nouvelles 
sauvegardes */

/* ----- A inclure ----- */


/* ----- Define ----- */


/* ----- Structure + Enumeration ----- */


/* ----- Prototype ----- */

/* Demande le nom du nouveau personnage */
void demanderNomNouveauPersonnage(void);


/* Cree un nouveau personnage */
void creerNouveauPersonnage(void);


/* Cree le dossier de sauvegarde pour le personnage */
void creerDossierSauvegardeNouveauPersonnage(void);


/* Ajoute le nom de la nouvelle partie dans le fichier nom_sauvegarde.txt */
void ajouterNomSauvegardeNouvellePartie(const unsigned int indexSauvegarde);


/* Affiche le texte de debut de nouvelle partie */
void afficherTexteNouvellePartie(void);


/* Cree une nouvelle sauvegarde et lance le jeu */
void nouvelleSauvegarde(const unsigned int indexSauvegarde);

/* ----- Declaration ----- */

#endif
