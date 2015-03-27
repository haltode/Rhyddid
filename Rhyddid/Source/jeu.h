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

unsigned int estNouvellePartie(void);


void initialiserCarteNiveau(char carteNiveau[NB_LIGNE_CARTE][NB_COLONNE_CARTE]);
void mettreAjourCarteNiveau(char carteNiveau[NB_LIGNE_CARTE][NB_COLONNE_CARTE]);
void afficherLigneCarteNiveau(char carteNiveau[NB_LIGNE_CARTE][NB_COLONNE_CARTE],
	const unsigned int indexLigneCarte);
void afficherLigneEnnemiNiveau(const unsigned int indexLigneEnnemi);
void afficherInformationJeu(const char *description, const unsigned int nombre, 
	const unsigned int retourLigne);
void afficherLigneInformationNiveau(char carteNiveau[NB_LIGNE_CARTE][NB_COLONNE_CARTE],
	const unsigned int indexLigne);
void afficherInformationEtCarteJeu(char carteNiveau[NB_LIGNE_CARTE][NB_COLONNE_CARTE]);


void afficherZoneInformation(void);
void initialiserZoneInformation(void);
void ajouterMessageZoneInformation(const char *message, const unsigned int couleurMessage);


void afficherJeu(char carteNiveau[NB_LIGNE_CARTE][NB_COLONNE_CARTE]);


void preparatifJeu(char carteNiveau[NB_LIGNE_CARTE][NB_COLONNE_CARTE]);
void initialiserVariable(void);


void jeu(void);

/* ----- Declaration ----- */

ZoneInformation zoneInformation;

#endif
