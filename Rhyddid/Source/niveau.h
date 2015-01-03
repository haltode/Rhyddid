#ifndef NIVEAU_H
#define NIVEAU_H

/* niveau.c/niveau.h : permet de gerer le niveau (affichage, generation, chargement, 
sauvegarde, etc.) */

/* ----- A inclure ----- */

#include "ennemi.h"
#include "caverne.h"

/* ----- Define ----- */

#define NB_SALLE_NIVEAU 9

#define LARGUEUR_SALLE 40
#define LONGUEUR_SALLE 80

#define NB_FORME_SALLE 6

#define NB_COFFRE_MIN 0
#define NB_COFFRE_MAX 3

#define NB_ENNEMI_MIN 2
#define NB_ENNEMI_MAX 5

#define NB_OBSTACLE_MIN 5
#define NB_OBSTACLE_MAX 12

#define NB_LONGUEUR_OBSTACLE_MIN 2
#define NB_LONGUEUR_OBSTACLE_MAX 5

#define CHANCE_MAX_CAVERNE 3

#define NB_ELEMENT_CARACTERE_NIVEAU 15


/* NB_ENNEMI_MAX_PAR_SALLE est de taille NB_ENNEMI_MAX + NB_COFFRE_MAX pour prendre en compte le 
nombre max d'ennemi possible par salle et le nombre de coffre max par salle (dans le cas d'un coffre 
piege ou un ennemi apparait) */

#define NB_ENNEMI_MAX_PAR_SALLE NB_ENNEMI_MAX + NB_COFFRE_MAX

/* ----- Structure + Enumeration ----- */

typedef struct Salle Salle;
struct Salle
{
	char mapSalle[LARGUEUR_SALLE][LONGUEUR_SALLE];
	Ennemi ennemi[NB_ENNEMI_MAX_PAR_SALLE];
	unsigned int nbCoffre;
	unsigned int nbEnnemi;

	Caverne caverne;
};

typedef struct Niveau Niveau;
struct Niveau
{
	Salle salle[NB_SALLE_NIVEAU];
	unsigned int salleActuelle;
	int salleCaverne;
	unsigned int estDansCaverne;
};

typedef struct ElementNiveau ElementNiveau;
struct ElementNiveau
{
	char caractereSauvegarde;
	char caractereAffiche;
	unsigned int couleurCaractere;
};

/* ----- Prototype ----- */

/* Retourne 1 si le caractere donne en parametre est l'entree du niveau et 0 sinon */
unsigned int estCaractereEntreeNiveau(const char caractere);
/* Retourne 1 si le caractere donne en parametre est la sortie du niveau et 0 sinon */
unsigned int estCaractereSortieNiveau(const char caractere);
/* Retourne 1 si le caractere donne en parametre est une porte du niveau et 0 sinon */
unsigned int estCaracterePorteNiveau(const char caractere);


/* Affecte un element dans la table de donnee des caracteres du niveau */
void affecterElementTableCaractereNiveau(const char caractereSauvegardeTable, 
	const char caractereAfficheTable, const unsigned int couleurCaractereTable);
/* Cree la table de donnee des caracteres du niveau */
void creerTableCaractereNiveau(void);


/* Affiche un caractere de la salle donne en parametre */
void afficherCaractereNiveau(const char caractere);
/* Affiche un ennemi aux coordonees ligne colonne */
void afficherEnnemi(const unsigned int ligne, const unsigned int colonne);
/* Affiche la salle actuelle du niveau ou se trouve le joueur */
void afficherSalleActuelle(void);


/* Recherche les coordonnes de l'entree d'une nouvelle salle et les place dans indexLigEntree 
et indexColEntree */
void rechercherCoordoneeEntreeNouvelleSalleNiveau(const char indexSalle, 
	unsigned int *indexLigEntree, unsigned int *indexColEntree);


/* Change le joueur de salle */
void changerSalleNiveau(const unsigned int indexAncienneSalle, 
	const unsigned int indexNouvelleSalle);

/* ----- Declaration ----- */

Niveau niveauActuel;

#endif
