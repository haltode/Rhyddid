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

/* Fonction qui vide le buffer */
void viderBuffer(void);


/* Fonction qui tire un nombre en min et max au hasard */
unsigned int hasard(const unsigned int min, const unsigned int max);


/* Fonction qui indique le message donne en parametre et quitte le programme */
void erreur(const char *message);


/* Fonction qui ouvre un fichier donne en paremetre dans le mode donne en parametre de 
maniere securisee et retourne un pointeur sur le fichier */
FILE *ouvrirFichier(const char *chemin, const char *mode, const char *messageErreur);


/* Ferme le fichier donne en parametre */
void fermerFichier(FILE *fichier, const char *messageErreur);


/* Fonction qui lit du texte sur un flux indique par chemin et l'affiche en entree */
void lireEtAfficher(const char *chemin);


/* Fonction qui lit du texte sur un flux indique par flux */
unsigned int lire(FILE *flux, char ligne[TAILLE_MAX]);


/* Affiche le texte donne en parametre et demande au joueur d'appuyez sur ENTREE */
void appuyezEntree(const char *texte);


/* Fonction qui affiche un titre donne en parametre dans une couleur donnee en parametre */
void titre(const char *s, const unsigned int typeCouleur);


/* Fonction qui permet de faire son choix lors d'un menu */
int choisirMenu(const unsigned int maximum);


/* Fonction qui permet de faire son choix lors d'un menu sans possibilite de revenir en 
arriere ou de quitter */
unsigned int choisirMenuSansOperationPossible(const unsigned int maximum);


/* Affiche une separation de texte avec des - */
void separationTexte(void);


/* Attend un nombre de secondes precises en parametre */
void attendre(const float temps);


/* Demande la comfirmation de faire quelque chose */
unsigned int demanderConfirmation(const char *message, const unsigned int separation);


/* Tire min chance sur max et renvoie 1 si le joueur a la chance et 0 sinon */
unsigned int tirerChance(const unsigned int min, const unsigned int max);


/* Renvoie 1 si la distance est a la portee indiquee en parametre et 0 sinon */
unsigned int estAportee(const unsigned int distanceLig, const unsigned int distanceCol, 
	const unsigned int portee);

/* ----- Declaration ----- */


#endif
