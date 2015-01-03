#ifndef ATTAQUE_H
#define ATTAQUE_H

/* attaque.c/attaque.h : permet au joueur d'attaquer un ennemi */

/* ----- A inclure ----- */


/* ----- Define ----- */


/* ----- Structure + Enumeration ----- */

typedef struct Attaque Attaque;
struct Attaque
{
	unsigned int aAttaqueEnnemi;
	unsigned int indexEnnemiAttaque;
};

/* ----- Prototype ----- */

/* Inflige des degats indiques en paramtre a l'ennemi indique en parametre */
void inffligerDegatEnnemi(const unsigned int indexEnnemi, const unsigned int degat);


/* Renvoie un nombre different de 0 si le joueur peut attaque l'ennemi indique en parametre */
unsigned int joueurPeutAttaquerEnnemi(const unsigned int indexEnnemi);
/* Permet au joueur d'attaquer un ennemi */
void attaquerEnnemi(void);

/* ----- Declaration ----- */

#endif
