#ifndef ENNEMI_H
#define ENNEMI_H

/* ennemi.c/ennemi.h : permet de gerer les ennemis */

/* ----- A inclure ----- */


/* ----- Define ----- */

#define NB_NIVEAU_IA 3

#define MIN 0
#define MAX 1

/* ----- Structure + Enumeration ----- */

enum NiveauIA 
{
	NIVEAU_IA_1 = 0, 
	NIVEAU_IA_2 = 1,
	NIVEAU_IA_3 = 2
};

typedef struct Ennemi Ennemi;
struct Ennemi
{
	unsigned int position[2];
	int nbVie;
	unsigned int degatAttaque;
	unsigned int protection;
	unsigned int porteeAttaque;

	unsigned int estModeFocus;
	int nbTourFocus;
	int nbTourAttendreFocus;

	unsigned int possedeCle;
};

/* ----- Prototype ----- */

/* Tire des competences d'un ennemi aleatoirement */
void tirerCompetenceEnnemieAleatoireNouveauNiveau(const unsigned int indexSalle, 
	const unsigned int indexEnnemi, const unsigned int estCaverne);
	/* Place aleatoirement les ennemis dans la salle indexSalle du niveau */
void placerEnnemiAleatoireNouveauNiveau(const unsigned int indexSalle, 
	unsigned int nbEnnemi, const unsigned int estCaverne);


/* Permet de terminer le niveau de l'IA de l'ennemi en fonction du niveau ou se trouve le joueur */
unsigned int determinerNiveauIAEnnemi(const unsigned int niveau);


/* Determine le nombre de tour que l'ennemi doit focus le joueur en fonction du niveau de l'IA */
unsigned int determinerNbTourFocusEnnemi(const unsigned int niveauIA);
/* Determine le nombre de tour que l'ennemi doit attendre avant de pouvoir re-focus le joueur 
en fonction du niveau de l'IA */
unsigned int determinerNbTourAttendreFocusEnnemi(const unsigned int niveauIA);


/* Tire la vie d'un ennemi aleatoirement en fonction du niveau de l'IA */
unsigned int tirerVieAleatoireNouveauEnnemi(const unsigned int niveauIA);
/* Tire les degats d'un ennemi aleatoirement en fonction du niveau de l'IA */
unsigned int tirerDegatAleatoireNouveauEnnemi(const unsigned int niveauIA);
/* Tire la protection d'un ennemi aleatoirement en fonction du niveau de l'IA */
unsigned int tirerProtectionAleatoireNouveauEnnemi(const unsigned int niveauIA);
/* Tire la portee d'un ennemi aleatoirement en fonction du niveau de l'IA */
unsigned int tirerPorteeAleatoireNouveauEnnemi(const unsigned int niveauIA);


/* Renvoie 1 si l'ennemi indexEnnemi peut attaque le joueur  et 0 sinon */
unsigned int peutAttaquerJoueur(const unsigned int indexEnnemi);
/* Attaque le joueur */
void attaquerJoueur(const unsigned int indexEnnemi);


/* Deplace l'ennemi indexEnnemi dans la direction donnee en parametre */
void deplacerEnnemi(const unsigned int indexEnnemi, const unsigned int direction);
/* Deplace l'ennemi indexEnnemi aleatoirement */
void deplacerEnnemiAleatoire(const unsigned int indexEnnemi);
/* Deplace l'ennemi indexEnnemi de maniere intelligente car il focus le joueur */
void deplacerEnnemiFocus(const unsigned int indexEnnemi, int *nbTourFocus);


/* Retourne 1 si l'ennemi indexEnnemi peut focus le joueur et 0 sinon */
unsigned int peutFocusJoueur(const unsigned int indexEnnemi, const unsigned int niveauIA);
/* Defocus l'ennemi du joueur et met a jour les informations necessaires */
void defocusJoueurIAEnnemi(unsigned int *modeFocus, int *nbTourFocus, int *nbTourAttendreFocus, 
	const unsigned int niveauIA);
/* Focus le joueur et met a jour les informations necessaires */
void focusJoueurIAEnnemi(unsigned int *modeFocus, int *nbTourFocus, int *nbTourAttendreFocus, 
	const unsigned int niveauIA);


/* Gere l'IA de l'ennemi */
void IAennemi(void);


/* Renvoie l'index de l'ennemi sur les coordonnes ligne colonne */
int trouverIndexEnnemi(const unsigned int ligne, const unsigned int colonne);


/* Renvoie 1 si l'ennemi indexEnnemi est mort et 0 sinon */
unsigned int estMortEnnemi(const unsigned int indexEnnemi);


/* Renvoie le nombre d'ennemi dans le niveau */
unsigned int nombreEnnemiNiveau(void);


/* Place la cle de fin de niveau sur l'ennemi numero indexCle du niveau */
void placerCleEnnemi(const unsigned int indexCle);
/* Choisit l'emplacement de la cle de fin de niveau et la place sur l'ennemi choisit */
void initialiserEmplacementCleEnnemi(void);


/* Affiche les caracteristiques de l'ennemi indexEnnemi */
void afficherCaracteristiqueEnnemi(const unsigned int indexEnnemi);

/* ----- Declaration ----- */

#endif
