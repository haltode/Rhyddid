#include <stdio.h>
#include <string.h>
#include <ctype.h>

#include "touche.h"
#include "deplacement.h"
#include "sauvegarderNiveau.h"
#include "pause.h"
#include "inventaire.h"
#include "attaque.h"
#include "fonctionsUtiles.h"
#include "personnage.h"

/* Touche de Rhyddid :

z = haut
s = bas
q = gauche
d = droite

n = sauvegarder et quitter
m = sauvegarder

ECHAP = pause

e = inventaire

t = attaquer ennemi

h = potion de sante niveau I
j = potion de force niveau I
k = potion de resistance niveau I

H = potion de sante niveau II
J = potion de force niveau II
K = potion de resistance niveau II

*/

/* Retourne 1 si la touche donnee en parametre indique une direction a prendre et 0 sinon */
unsigned int estDirection(const char touche)
{
	/* Contient toutes les lettres possibles pour se deplacer */
	static const char basedirectionPossible[] = "zZsSqQdD";

	/* On recherche si la lettre entree est dans la base de lettre */

	/* On retourne 1 si la touche est une direction et 0 sinon */
	return strchr(basedirectionPossible, touche) != NULL;
}

/* Renvoie 1 si la touche est ECHAP et 0 sinon */
unsigned int estMenuPause(const unsigned int touche)
{
	/* On renvoie 1 si la touche est ECHAP et 0 sinon */
	return touche == ECHAP;
}

/* Renvoie 1 si la touche donnee en parametre est la meme que actionTouche et 0 sinon */
unsigned int testerTouche(const char touche, const char actionTouche)
{
	char minuscule, majuscule;
	
	minuscule = tolower(actionTouche);
	majuscule = toupper(actionTouche);

	/* On renvoie 1 si la touche est soit la minuscule de actionTouche soit la majuscule et 0
	sinon */
	return touche == minuscule || touche == majuscule;
}

/* Effectue une action en fonction de la touche entree */
void effectuerActionToucheEntree(const char toucheEntree)
{
	/* Contient des touches et un pointeur sur la fonction correspondante */
	static const Touche baseTouche[NB_TOUCHE] =
	{
		{'n', 	&sauvegarderEtQuitterNiveau},
		{'m', 	&sauvegarderNiveau},
		{'e', 	&ouvrirInventaire},
		{'t', 	&attaquerEnnemi}
	};
	compteur indexTouche;

	/* Si c'est une touche normale (ne necessitant pas de parametre ou autre pour la fonction) */

	/* Pour chaque touche */
	for(indexTouche = 0; indexTouche < NB_TOUCHE; ++indexTouche)
	{
		/* On teste la touche */

		/* Si c'est celle entree, on execute le pointeur sur fonction */
		if(testerTouche(toucheEntree, baseTouche[indexTouche].touche))
			baseTouche[indexTouche].pointeurFonction();
	}


	/* Si c'est une touche pour se deplacer (z, q, s, d) */
	if(estDirection(toucheEntree))
	{
		unsigned int directionTouche;
	
		/* On recupere la direction de la touche (Haut, Bas, Gauche, Droite) */
		directionTouche = recupererDirectionTouche(toucheEntree);

		/* On deplace le joueur dans la direction */
		deplacerJoueurDirection(directionTouche, personnage.positionJoueur);
	}
	/* Si c'est la touche pour entrer dans le menu de pause */
	else if(estMenuPause(toucheEntree))
		/* On appelle la fonction menuPause */
		menuPause();
	/* Si c'est la touche pour utiliser une potion de sante */
	else if(testerTouche(toucheEntree, 'h'))
		/* On appelle la fonction utiliserPotionSante */
		utiliserPotionSante(toucheEntree);
	/* Si c'est la touche pour utiliser une potion de force */
	else if(testerTouche(toucheEntree, 'j'))
		/* On appelle la fonction utiliserPotionForce */
		utiliserPotionForce(toucheEntree);
	/* Si c'est la touche pour utiliser une potion de resistance */
	else if(testerTouche(toucheEntree, 'k'))
		/* On appelle la fonction utiliserPotionResistance */
		utiliserPotionResistance(toucheEntree);
}
