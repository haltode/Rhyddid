#ifndef SAUVEGARDER_NIVEAU_H
#define SAUVEGARDER_NIVEAU_H

/* ----- A inclure ----- */


/* ----- Define ----- */


/* ----- Structure + Enumeration ----- */


/* ----- Prototype ----- */

/* Cree les dossiers necessaires pour la sauvegarde */
void creerDossierNecessaireSauvegardeNiveau(void);


/* Sauvegarde la forme de la salle indexSalle */
void sauvegarderFormeSalleIndividuelleNiveau(const unsigned int indexSalle);
/* Sauvegarde les infos de la salle indexSalle (nbCoffre, nbEnnemi, caracteristique ennemi 
etc.) */
void sauvegarderInfoSalleIndiviuelleNiveau(const unsigned int indexSalle);
/* Sauvegarde la caverne du niveau */
void sauvegarderCaverneNiveau(void);
/* Sauvegarde les salles d'un niveau deja genere */
void sauvegarderSalleNiveau(void);
/* Sauvegarde la position du joueur dans le niveau deja genere */
void sauvegarderPositionJoueurNiveau(void);
/* Sauvegarde le niveau actuel */
void sauvegarderNiveauActuel(void);
/* Sauvegarde le niveau et quitte le jeu */
void sauvegarderEtQuitterNiveau(void);
/* Sauvegarde le niveau */
void sauvegarderNiveau(void);

/* ----- Declaration ----- */

#endif
