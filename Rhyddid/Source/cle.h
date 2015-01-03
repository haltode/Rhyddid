#ifndef CLE_H
#define CLE_H

/* armure.c/armure.h : permet de l'initialisation, le chargement, la sauvegarde, l'affichage etc. 
de la cle de fin de niveau */

/* ----- A inclure ----- */


/* ----- Define ----- */


/* ----- Structure + Enumeration ----- */


/* ----- Prototype ----- */

/* Initialise la cle de fin de niveau de l'inventaire dans le fichier Inventaire/cle.txt */
void initialiserCleInventaire(void);
/* Charge la cle de fin de niveau de l'inventaire grace au fichier Inventaire/cle.txt */
void chargerCleInventaire(void);
/* Sauvegarde la cle de fin de niveau de l'inventaire dans le fichier Inventaire/cle.txt */
void sauvegarderCleInventaire(void);
/* Affiche la section Cle de l'inventaire lorsqu'on ouvre l'inventaire */
void afficherCleInventaire(void);
/* Ajoute la cle de fin de niveau dans l'inventaire du joueur */
void ajouterCleInventaire(void);

/* ----- Declaration ----- */

#endif
