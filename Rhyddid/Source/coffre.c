#include <stdio.h>

#include "coffre.h"
#include "fonctionsUtiles.h"
#include "effacer.h"
#include "couleur.h"
#include "niveau.h"
#include "deplacement.h"
#include "personnage.h"
#include "jeu.h"
#include "genererNiveau.h"

/* Place aleatoirement les coffres dans la salle indexSalle du niveau */
void placerCoffreAleatoireNouveauNiveau(const unsigned int indexSalle, 
	unsigned int nbCoffre, const unsigned int estCaverne)
{
	unsigned int indexLig, indexCol;

	/* Pour chaque coffre a generer */
	while(nbCoffre > 0)	
	{
		/* On tire des coordonnes pour le coffre */
		tirerCoordonneeAleatoireNiveau(indexSalle, &indexLig, &indexCol, estCaverne);

		/* On place le coffre sur la map */

		if(estCaverne)
			niveauActuel.salle[indexSalle].caverne.mapSalle[indexLig][indexCol] = '?';
		else
			niveauActuel.salle[indexSalle].mapSalle[indexLig][indexCol] = '?';

		/* On decremente le nombre de coffre a generer */
		--nbCoffre;	
	}
}

/* Initialise le contenu du coffre donne en parametre */
void initialiserContenuCoffre(Coffre *coffre)
{
	/* On initialise tous ses composants (tek, armure, arme, tresor, potion) a NON */
	coffre->tek = NON;
	coffre->armure = NON;
	coffre->arme = NON;
	coffre->tresor = NON;
	coffre->potion = NON;	
}

/* Decide du contenu du coffre donne en parametre */
void deciderContenuCoffre(Coffre *coffre)
{
	/* On tire la probabilite d'avoir chaque composant, si on reussit on indique OUI a la 
	variable du composant */
	if(tirerChance(1, CHANCE_MAX_TEK))
		coffre->tek = OUI;
	if(tirerChance(1, CHANCE_MAX_ARMURE))
		coffre->armure = OUI;
	if(tirerChance(1, CHANCE_MAX_ARME))
		coffre->arme = OUI;
	if(tirerChance(1, CHANCE_MAX_TRESOR))
		coffre->tresor = OUI;
	if(tirerChance(1, CHANCE_MAX_POTION))
		coffre->potion = OUI;
}

/* Remplit le contenu du coffre donne en parametre */
void remplirContenuCoffre(Coffre *coffre)
{
	/* On teste chaque composant du coffre, s'il y a ce composant dans le coffre on le genere */
	if(coffre->tek == OUI)
		genererTekCoffre(&(coffre->inventaire.tek));
	if(coffre->armure == OUI)
		genererArmureCoffre(&(coffre->inventaire.armure));
	if(coffre->arme == OUI)
		genererArmeCoffre(&(coffre->inventaire.arme));
	if(coffre->tresor == OUI)
		genererTresorCoffre(&(coffre->inventaire.tresor[0]));
	if(coffre->potion == OUI)
		genererPotionCoffre(&(coffre->typePotion), &(coffre->niveauPotion));
}

/* Genenere le contenu du coffre donne en parametre */
void genererContenuCoffre(Coffre *coffre)
{
	/* On decide du contenu du coffre */
	deciderContenuCoffre(coffre);
	/* Puis on le remplit avec ce dernier */
	remplirContenuCoffre(coffre);
}

/* Affiche le contenu du coffre donne en parametre */
void afficherContenuCoffre(const Coffre *coffre)
{
	effacer();
	titre("Coffre", VERT);

	separationTexte();

	/* On affiche l'armure et l'arme actuelle du joueur */
	printf("Equipement : \n\n");

	afficherArmureInventaire();
	afficherArmeInventaire();

	separationTexte();

	/* On affiche le contenu du coffre */
	printf("Voici le contenu du coffre :\n\n");

	if(coffre->tek == OUI && coffre->inventaire.tek.nbTek != 0)
		afficherTekCoffre(coffre);
	if(coffre->armure == OUI)
		afficherArmureCoffre(coffre);
	if(coffre->arme == OUI)
		afficherArmeCoffre(coffre);
	if(coffre->tresor == OUI)
		afficherTresorCoffre(coffre);
	if(coffre->potion == OUI)
		afficherPotionCoffre(&(coffre->typePotion), &(coffre->niveauPotion));
}

/* Prend le contenu du coffre donne en parametre */
void prendreContenuCoffre(const Coffre *coffre)
{
	/* On teste chaque composant, s'il y a ce composant on l'ajoute a l'inventaire du joueur */
	if(coffre->tek == OUI)
		prendreTekCoffre(&(coffre->inventaire.tek));
	if(coffre->armure == OUI)
		prendreArmureCoffre(&(coffre->inventaire.armure));
	if(coffre->arme == OUI)
		prendreArmeCoffre(&(coffre->inventaire.arme));
	if(coffre->tresor == OUI)
		prendreTresorCoffre(&(coffre->inventaire.tresor[0]));
	if(coffre->potion == OUI)
		prendrePotionCoffre(&(coffre->typePotion), &(coffre->niveauPotion));
}

/* Retourne 1 si le coffre donne en parametre est vide et 0 sinon */
unsigned int estCoffreVide(const Coffre *coffre)
{
	/* On teste chaque composant pour savoir s'il y en a au moins 1 */

	if(coffre->tek == OUI && coffre->inventaire.tek.nbTek != 0)
		return 0;
	if(coffre->armure == OUI)
		return 0;
	if(coffre->arme == OUI)
		return 0;
	if(coffre->tresor == OUI)
		return 0;
	if(coffre->potion == OUI)
		return 0;

	/* Si il n'y a aucun composant on renvoit 1 */
	return 1;
}

/* Genere un coffre piege */
void coffrePiege(void)
{
	/* Si le joueur ouvre un coffre piege un ennemi apparait */

	unsigned int indexEnnemi;

	/* On recupere le nombre d'ennemi pour avoir l'index du prochain ennemi */
	if(niveauActuel.estDansCaverne)
		indexEnnemi = niveauActuel.salle[niveauActuel.salleActuelle].caverne.nbEnnemi;
	else	
		indexEnnemi = niveauActuel.salle[niveauActuel.salleActuelle].nbEnnemi;
	
	/* On initialise la position du nouvel ennemi sur la position du joueur (et du coffre donc) */
	if(niveauActuel.estDansCaverne)
	{
		niveauActuel.salle[niveauActuel.salleActuelle].caverne.ennemi[indexEnnemi].position[LIG] = personnage.positionJoueur[LIG];
		niveauActuel.salle[niveauActuel.salleActuelle].caverne.ennemi[indexEnnemi].position[COL] = personnage.positionJoueur[COL];
	}
	else
	{
		niveauActuel.salle[niveauActuel.salleActuelle].ennemi[indexEnnemi].position[LIG] = personnage.positionJoueur[LIG];
		niveauActuel.salle[niveauActuel.salleActuelle].ennemi[indexEnnemi].position[COL] = personnage.positionJoueur[COL];
	}

	/* On tire les competences de l'ennemi aleatoire */
	if(niveauActuel.estDansCaverne)
		tirerCompetenceEnnemieAleatoireNouveauNiveau(niveauActuel.salleActuelle, indexEnnemi, CAVERNE);
	else
		tirerCompetenceEnnemieAleatoireNouveauNiveau(niveauActuel.salleActuelle, indexEnnemi, NON_CAVERNE);

	/* On augmente le nombre d'ennemi du niveau de 1 */
	if(niveauActuel.estDansCaverne)
		++(niveauActuel.salle[niveauActuel.salleActuelle].caverne.nbEnnemi);
	else
		++(niveauActuel.salle[niveauActuel.salleActuelle].nbEnnemi);
}

/* Supprime un coffre */
void supprimerCoffre(void)
{
	/* Met la case ou se trouve le joueur (donc le coffre) comme etant un ' ' (vide) */

	if(niveauActuel.estDansCaverne)
		niveauActuel.salle[niveauActuel.salleActuelle].caverne.mapSalle[personnage.positionJoueur[LIG]][personnage.positionJoueur[COL]] = ' ';
	else
		niveauActuel.salle[niveauActuel.salleActuelle].mapSalle[personnage.positionJoueur[LIG]][personnage.positionJoueur[COL]] = ' ';
}

/* Ouvre un coffre */
void ouvrirCoffre(void)
{
	Coffre coffre;

	/* On choisit si le coffre est piege ou pas */

	/* Si le coffre est piege */
	if(tirerChance(1, CHANCE_MAX_COFFRE_PIEGE))
	{
		/* On affiche un message d'alerte */
		ajouterMessageZoneInformation("C'est un coffre piege ! Un ennemi est apparu !", ROUGE);
	
		/* On ouvre le coffre piege */
		coffrePiege();
	}
	/* Sinon le coffre est normal */
	else
	{
		unsigned int estVide;

		/* On initialise le contenu du coffre */
		initialiserContenuCoffre(&coffre);
		/* On genere le contenu du coffre */
		genererContenuCoffre(&coffre);

		/* On regarder si le coffre est vide */
		estVide = estCoffreVide(&coffre);

		/* S'il est vide */
		if(estVide)
			/* On affiche un message d'alerte */
			ajouterMessageZoneInformation("C'est un coffre vide ! :(", ROUGE);
		/* Sinon le coffre est rempli */
		else
		{
			/* On affiche le contenu du coffre */
			afficherContenuCoffre(&coffre);
			separationTexte();
			/* Le joueur prend le contenu du coffre */
			prendreContenuCoffre(&coffre);

			appuyezEntree("Appuyez sur ENTREE pour prendre le contenu du coffre et revenir en jeu...");
		}
	}

	/* On supprime le coffre */
	supprimerCoffre();
}
