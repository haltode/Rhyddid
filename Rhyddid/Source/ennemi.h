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

void tirerCompetenceEnnemieAleatoireNouveauNiveau(const unsigned int indexSalle, 
	const unsigned int indexEnnemi, const unsigned int estCaverne);
void placerEnnemiAleatoireNouveauNiveau(const unsigned int indexSalle, 
	unsigned int nbEnnemi, const unsigned int estCaverne);


unsigned int determinerNiveauIAEnnemi(const unsigned int niveau);


unsigned int determinerNbTourFocusEnnemi(const unsigned int niveauIA);
unsigned int determinerNbTourAttendreFocusEnnemi(const unsigned int niveauIA);


unsigned int tirerVieAleatoireNouveauEnnemi(const unsigned int niveauIA);
unsigned int tirerDegatAleatoireNouveauEnnemi(const unsigned int niveauIA);
unsigned int tirerProtectionAleatoireNouveauEnnemi(const unsigned int niveauIA);
unsigned int tirerPorteeAleatoireNouveauEnnemi(const unsigned int niveauIA);


unsigned int peutAttaquerJoueur(const unsigned int indexEnnemi);
void attaquerJoueur(const unsigned int indexEnnemi);


void deplacerEnnemi(const unsigned int indexEnnemi, const unsigned int direction);
void deplacerEnnemiAleatoire(const unsigned int indexEnnemi);
void deplacerEnnemiFocus(const unsigned int indexEnnemi, int *nbTourFocus);


unsigned int peutFocusJoueur(const unsigned int indexEnnemi, const unsigned int niveauIA);
void defocusJoueurIAEnnemi(unsigned int *modeFocus, int *nbTourFocus, int *nbTourAttendreFocus, 
	const unsigned int niveauIA);
void focusJoueurIAEnnemi(unsigned int *modeFocus, int *nbTourFocus, int *nbTourAttendreFocus, 
	const unsigned int niveauIA);


void IAennemi(void);


int trouverIndexEnnemi(const unsigned int ligne, const unsigned int colonne);


unsigned int estMortEnnemi(const unsigned int indexEnnemi);


unsigned int nombreEnnemiNiveau(void);


void placerCleEnnemi(const unsigned int indexCle);
void initialiserEmplacementCleEnnemi(void);


void afficherCaracteristiqueEnnemi(const unsigned int indexEnnemi);

/* ----- Declaration ----- */

#endif
