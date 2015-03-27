#ifndef TEK_H
#define TEK_H

/* tek.c/tek.h : permet de gerer l'argent du jeu (tek) */

/* ----- A inclure ----- */

/* ----- Define ----- */

#define CHANCE_MAX_NB_TEK_NIVEAU_1 2
#define CHANCE_MAX_NB_TEK_NIVEAU_2 4
#define CHANCE_MAX_NB_TEK_NIVEAU_3 6
#define CHANCE_MAX_NB_TEK_NIVEAU_4 10

#define NB_TEK_NIVEAU_1 20
#define NB_TEK_NIVEAU_2 50
#define NB_TEK_NIVEAU_3 70
#define NB_TEK_NIVEAU_4 120

/* ----- Structure + Enumeration ----- */

typedef struct Coffre Coffre;

typedef struct Tek Tek;
struct Tek
{
	unsigned int nbTek;
};

/* ----- Prototype ----- */

void initialiserTekInventaire(void);
void chargerTekInventaire(void);
void sauvegarderTekInventaire(void);
void afficherTekInventaire(void);


void ajouterTekInventaire(const unsigned int nbTek);
void enleverTekInventaire(const unsigned int nbTek);

void genererTekCoffre(Tek *tek);
void afficherTekCoffre(const Coffre *coffre);
void prendreTekCoffre(const Tek *tek);

/* ----- Declaration ----- */

#endif
