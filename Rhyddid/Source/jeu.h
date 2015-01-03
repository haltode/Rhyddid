#ifndef JEU_H
#define JEU_H

/* jeu.c/jeu.h : permet de jouer */

/* ----- A inclure ----- */

#include "fonctionsUtiles.h"

/* ----- Define ----- */

#define NB_LIGNE_CARTE 9
#define NB_COLONNE_CARTE 14

#define NB_LIGNE_ENNEMI 9
#define NB_COLONNE_ENNEMI 16

#define NON_RETOUR_LIGNE 0
#define RETOUR_LIGNE 1

#define NB_INFO_MAX 10

/* ----- Structure + Enumeration ----- */

typedef struct Message Message;
struct Message
{
	char texte[TAILLE_MAX];
	unsigned int couleur;
};

typedef struct ZoneInformation ZoneInformation;
struct ZoneInformation
{
	Message message[NB_INFO_MAX];
	unsigned int infoActuelle;
};

/* ----- Prototype ----- */

/* Retourne 1 si c'est une nouvelle partie et 0 sinon */
unsigned int estNouvellePartie(void);


/* Initialise la carte du niveau */
void initialiserCarteNiveau(char carteNiveau[NB_LIGNE_CARTE][NB_COLONNE_CARTE]);
/* Met a jour la carte du niveau (place un X dans la salle ou se trouve le joueur) */
void mettreAjourCarteNiveau(char carteNiveau[NB_LIGNE_CARTE][NB_COLONNE_CARTE]);
/* Affiche une ligne de la carte */
void afficherLigneCarteNiveau(char carteNiveau[NB_LIGNE_CARTE][NB_COLONNE_CARTE],
	const unsigned int indexLigneCarte);
/* Affiche une ligne de l'ennemi */
void afficherLigneEnnemiNiveau(const unsigned int indexLigneEnnemi);
/* Affiche les informations du joueur dans le jeu */
void afficherInformationJeu(const char *description, const unsigned int nombre, 
	const unsigned int retourLigne);
/* Affiche une ligne soit de la carte soit de l'ennemi */
void afficherLigneInformationNiveau(char carteNiveau[NB_LIGNE_CARTE][NB_COLONNE_CARTE],
	const unsigned int indexLigne);
/* Affiche les informations du joueur et la carte dans le jeu */
void afficherInformationEtCarteJeu(char carteNiveau[NB_LIGNE_CARTE][NB_COLONNE_CARTE]);


/* Affiche la zone d'information sur le jeu */
void afficherZoneInformation(void);
/* Initialise la zone d'information sur le jeu */
void initialiserZoneInformation(void);
/* Ajoute un message sur la zone d'information du jeu */
void ajouterMessageZoneInformation(const char *message, const unsigned int couleurMessage);


/* Affiche le jeu */
void afficherJeu(char carteNiveau[NB_LIGNE_CARTE][NB_COLONNE_CARTE]);


/* Fait tous les preparatifs avant le jeu */
void preparatifJeu(char carteNiveau[NB_LIGNE_CARTE][NB_COLONNE_CARTE]);
/* Initialise les variables importantes */
void initialiserVariable(void);


/* Lance le jeu */
void jeu(void);

/* ----- Declaration ----- */

/* Contient la zone d'information situee avant la salle affichee */
ZoneInformation zoneInformation;

#endif
