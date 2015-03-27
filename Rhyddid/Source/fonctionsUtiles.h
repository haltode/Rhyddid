#ifndef FONCTIONS_UTILES_H
#define FONCTIONS_UTILES_H

/* fonctionsUtiles.c/fonctionsUtiles.h : permet d'avoir plusieurs fonctions utiles de toutes
sortes */

/* ----- A inclure ----- */


/* ----- Define ----- */

#define TAILLE_MAX 200

#define REVENIR_ARRIERE -1
#define QUITTER 0

#define NB_SEPARATION 80

#define NON 0
#define OUI 1

#define PAS_SEPARATION 0
#define SEPARATION 1

/* ----- Structure + Enumeration ----- */

typedef unsigned int compteur;

/* ----- Prototype ----- */

void viderBuffer(void);


unsigned int hasard(const unsigned int min, const unsigned int max);


void erreur(const char *message);


FILE *ouvrirFichier(const char *chemin, const char *mode, const char *messageErreur);


void fermerFichier(FILE *fichier, const char *messageErreur);


void lireEtAfficher(const char *chemin);


unsigned int lire(FILE *flux, char ligne[TAILLE_MAX]);


void appuyezEntree(const char *texte);


void titre(const char *s, const unsigned int typeCouleur);


int choisirMenu(const unsigned int maximum);


unsigned int choisirMenuSansOperationPossible(const unsigned int maximum);


void separationTexte(void);


void attendre(const float temps);


unsigned int demanderConfirmation(const char *message, const unsigned int separation);


unsigned int tirerChance(const unsigned int min, const unsigned int max);


unsigned int estAportee(const unsigned int distanceLig, const unsigned int distanceCol, 
	const unsigned int portee);

/* ----- Declaration ----- */


#endif
