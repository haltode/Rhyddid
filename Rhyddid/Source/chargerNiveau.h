#ifndef CHARGER_NIVEAU_H
#define CHARGER_NIVEAU_H

/* ----- A inclure ----- */


/* ----- Define ----- */


/* ----- Structure + Enumeration ----- */


/* ----- Prototype ----- */

/* Charge la forme de la salle indexSalle */
void chargerFormeSalleIndividuelleNiveau(const unsigned int indexSalle);
/* Charge les infos de la salle indexSalle (nbCoffre, nbEnnemi, caracteristique ennemi etc.) */
void chargerInfoSalleIndiviuelleNiveau(const unsigned int indexSalle);
/* Charge la caverne du niveau */
void chargerCaverneNiveau(void);
/* Charge les salles d'un niveau deja genere */
void chargerSalleNiveau(void);
/* Charge la position du joueur dans le niveau deja genere */
void chargerPositionJoueurNiveau(void);
/* Charge un niveau deja genere */
void chargerNiveau(void);

/* ----- Declaration ----- */

#endif
