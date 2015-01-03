#include <stdio.h>
#include <string.h>
#include <ctype.h>

#include "potion.h"
#include "inventaire.h"
#include "personnage.h"
#include "fonctionsUtiles.h"
#include "couleur.h"
#include "jeu.h"

/* Initialise les potions de l'inventaire dans le fichier Inventaire/potion.txt */
void initialiserPotionInventaire(void)
{
	FILE *fichierPotion;
	char chemin[TAILLE_MAX];

	sprintf(chemin, "Sauvegarde/%s/Inventaire/potion.txt", personnage.nom);

	/* On ouvre le fichier Inventaire/potion.txt */
	fichierPotion = ouvrirFichier(chemin, "w+",
	"fichier \"potion.txt\", fonction \"initialiserPotionInventaire\"");

	/* On ecrit les donnees des potions de base avec le nombre de potion de niveau 1 et 2, le 
	nombre de tour actif de la potion en cours */
	fprintf(fichierPotion, "0 0 -1 0\n");
	fprintf(fichierPotion, "0 0 -1 0\n");
	fprintf(fichierPotion, "0 0 -1 0\n");

	/* On ferme le fichier Inventaire/potion.txt */
	fermerFichier(fichierPotion,
	"fichier \"potion.txt\", fonction \"initialiserPotionInventaire\"");
}

/* Charge les potions de l'inventaire grace au fichier Inventaire/potion.txt */
void chargerPotionInventaire(void)
{
	FILE *fichierPotion;
	char chemin[TAILLE_MAX];

	sprintf(chemin, "Sauvegarde/%s/Inventaire/potion.txt", personnage.nom);

	/* On ouvre le fichier Inventaire/potion.txt */
	fichierPotion = ouvrirFichier(chemin, "r",
	"fichier \"potion.txt\", fonction \"chargerPotionInventaire\"");

	/* On lit les donnees des potions avec le nombre de potion de niveau 1 et 2, le nombre de 
	tour actif de la potion en cours */
	fscanf(fichierPotion, "%d %d %d %d\n", &(inventaire.sante.nbPotionForce1), &(inventaire.sante.nbPotionForce2), &(inventaire.sante.nbTourPotionActive), &(inventaire.sante.nbBonus));
	fscanf(fichierPotion, "%d %d %d %d\n", &(inventaire.force.nbPotionForce1), &(inventaire.force.nbPotionForce2), &(inventaire.force.nbTourPotionActive), &(inventaire.force.nbBonus));
	fscanf(fichierPotion, "%d %d %d %d\n", &(inventaire.resistance.nbPotionForce1), &(inventaire.resistance.nbPotionForce2), &(inventaire.resistance.nbTourPotionActive), &(inventaire.resistance.nbBonus));

	/* On ferme le fichier Inventaire/potion.txt */
	fermerFichier(fichierPotion,
	"fichier \"potion.txt\", fonction \"chargerPotionInventaire\"");
}

/* Sauvegarde oles potions de l'inventaire dans le fichier Inventaire/potion.txt */
void sauvegarderPotionInventaire(void)
{
	FILE *fichierPotion;
	char chemin[TAILLE_MAX];

	sprintf(chemin, "Sauvegarde/%s/Inventaire/potion.txt", personnage.nom);

	/* On ouvre le fichier Inventaire/potion.txt */
	fichierPotion = ouvrirFichier(chemin, "w+",
	"fichier \"potion.txt\", fonction \"sauvegarderPotionInventaire\"");

	/* On ecrit les donnees des potions avec le nombre de potion de niveau 1 et 2, le nombre de 
	tour actif de la potion en cours */
	fprintf(fichierPotion, "%d %d %d %d\n", inventaire.sante.nbPotionForce1, inventaire.sante.nbPotionForce2, inventaire.sante.nbTourPotionActive, inventaire.sante.nbBonus);
	fprintf(fichierPotion, "%d %d %d %d\n", inventaire.force.nbPotionForce1, inventaire.force.nbPotionForce2, inventaire.force.nbTourPotionActive, inventaire.force.nbBonus);
	fprintf(fichierPotion, "%d %d %d %d\n", inventaire.resistance.nbPotionForce1, inventaire.resistance.nbPotionForce2, inventaire.resistance.nbTourPotionActive, inventaire.resistance.nbBonus);

	/* On ferme le fichier Inventaire/potion.txt */
	fermerFichier(fichierPotion,
	"fichier \"potion.txt\", fonction \"sauvegarderPotionInventaire\"");
}

/* Affiche une potion individuellement de l'inventaire */
void afficherPotionIndividuelleInventaire(const char *nomPotion, 
	const unsigned int nbPotionNiveau1, const unsigned int nbPotionNiveau2)
{
	/* On affiche seulement les potions que le joueur possede dans son inventaire */

	printf("\t- ");
	coloration(nomPotion, VERT);
	printf(" : \n");
		
	if(nbPotionNiveau1 != 0 || nbPotionNiveau2 != 0)
	{	
		if(nbPotionNiveau1 != 0)
		{
			printf("\t\t- ");
			couleur(BLEU);
			printf("%d", nbPotionNiveau1);
			couleur(BLANC);
			printf(" x %s I\n", nomPotion);
		}	

		if(nbPotionNiveau2 != 0)
		{
			printf("\t\t- ");
			couleur(BLEU);
			printf("%d", nbPotionNiveau2);
			couleur(BLANC);
			printf(" x %s II\n\n", nomPotion);
		}
	}
	else
	{
		printf("\t\t- ");
		coloration("Aucune", BLEU);

		printf("\n\n");
	}
}

/* Affiche la partie potion de l'inventaire */
void afficherPotionInventaire(void)
{
	/* On affiche chaque type de potion possible */

	coloration("Potion", VERT);
	printf(" : \n\n");
	
	afficherPotionIndividuelleInventaire("Sante", inventaire.sante.nbPotionForce1, inventaire.sante.nbPotionForce2);
	afficherPotionIndividuelleInventaire("Force", inventaire.force.nbPotionForce1, inventaire.force.nbPotionForce2);
	afficherPotionIndividuelleInventaire("Resistance", inventaire.resistance.nbPotionForce1, inventaire.resistance.nbPotionForce2);
}

/* Ajoute quantitePotion de potion de type nomPotion de niveau niveauPotion dans l'inventaire
du joueur */
void ajouterPotionInventaire(const unsigned int quantitePotion, const unsigned int typePotion, 
	const unsigned int niveauPotion)
{
	/* Contient un pointeur vers le nombre de potion de niveau 1 et 2 de chaque potion */
	static unsigned int *nbPotionInventaire[NB_POTION][NB_NIVEAU_POTION] = 
	{
		{&(inventaire.sante.nbPotionForce1),			&(inventaire.sante.nbPotionForce2)}, 
		{&(inventaire.force.nbPotionForce1),			&(inventaire.force.nbPotionForce2)},
		{&(inventaire.resistance.nbPotionForce1),		&(inventaire.resistance.nbPotionForce2)}
	};

	/* On ajoute quantitePotion au pointeur du type de la potion typePotion et de niveau 
	niveauPotion */
	*(nbPotionInventaire[typePotion][niveauPotion]) += quantitePotion;
}

/* Enleve quantitePotion potion de type typePotion de niveau niveauPotion de l'inventaire du
joueur */
void enleverPotionInventaire(const unsigned int quantitePotion, const unsigned int typePotion, 
	const unsigned int niveauPotion)
{
	/* Contient un pointeur vers le nombre de potion de niveau 1 et 2 de chaque potion */
	static unsigned int *nbPotionInventaire[NB_POTION][NB_NIVEAU_POTION] = 
	{
		{&(inventaire.sante.nbPotionForce1),			&(inventaire.sante.nbPotionForce2)}, 
		{&(inventaire.force.nbPotionForce1),			&(inventaire.force.nbPotionForce2)},
		{&(inventaire.resistance.nbPotionForce1),		&(inventaire.resistance.nbPotionForce2)}
	};

	/* On enleve quantitePotion au pointeur du type de la potion typePotion et de niveau 
	niveauPotion */
	*(nbPotionInventaire[typePotion][niveauPotion]) -= quantitePotion;
}

/* Renvoie 1 si le joueur peut utiliser la potion typePotion de niveau niveauPotion et une 
erreur sinon */
unsigned int peutUtiliserPotion(const unsigned int typePotion, const unsigned int niveauPotion)
{
	unsigned int nbPotionForce1, nbPotionForce2;
	int nbTourPotionActive;

	/* On recupere le nombre de tour de la potion active, le nombre de potion de niveau 1 et 2
	pour chaque potion */
	switch(typePotion)
	{
		case SANTE:
			nbTourPotionActive = inventaire.sante.nbTourPotionActive;
			nbPotionForce1 = inventaire.sante.nbPotionForce1;
			nbPotionForce2 = inventaire.sante.nbPotionForce2;
		break;

		case FORCE:
			nbTourPotionActive = inventaire.force.nbTourPotionActive;
			nbPotionForce1 = inventaire.force.nbPotionForce1;
			nbPotionForce2 = inventaire.force.nbPotionForce2;
		break;

		case RESISTANCE:
			nbTourPotionActive = inventaire.resistance.nbTourPotionActive;
			nbPotionForce1 = inventaire.resistance.nbPotionForce1;
			nbPotionForce2 = inventaire.resistance.nbPotionForce2;
		break;
	}

	/* Si le joueur veut utiliser une potion de niveau 1 et qu'il en a pas */
	if(niveauPotion == NIVEAU_1 && nbPotionForce1 == 0)
		/* On renvoie l'erreur AUCUNE_POTION */
		return AUCUNE_POTION;
	/* Si le joueur veut utiliser une potion de niveau 2 et qu'il en a pas */
	else if(niveauPotion == NIVEAU_2 && nbPotionForce2 == 0)
		/* On renvoie l'erreur AUCUNE_POTION */
		return AUCUNE_POTION;

	/* Si le joueur est deja sous l'effet d'une potion du meme type que celle qu'il veut 
	utiliser */
	if(nbTourPotionActive > 0)
		/* On renvoie l'erreur NON_UTILISABLE */
		return NON_UTILISABLE;

	/* Si le joueur veut utiliser une potion de sante et qu'il a deja sa sante au maximum */
	if(typePotion == SANTE && personnage.santeActuelle == personnage.sante)
		/* On renvoie l'erreur VIE_MAXIMUM */
		return VIE_MAXIMUM;

	/* Sinon le joueur peut utiliser la potion, on retourne 1 */
	return 1;
}

/* Affiche la raison de l'erreur typeErreurPotion */
void afficherErreurPotion(const unsigned int typeErreurPotion)
{
	/* On teste chaque cas d'erreur possible et on affiche le message correspondant */

	if(typeErreurPotion == AUCUNE_POTION)
		ajouterMessageZoneInformation("Vous n'avez pas de potion de ce type !", ROUGE);
	else if(typeErreurPotion == NON_UTILISABLE)
		ajouterMessageZoneInformation("Vous devez attendre la fin de la potion avant d'en utiliser une autre !", ROUGE);
	else if(typeErreurPotion == VIE_MAXIMUM)
		ajouterMessageZoneInformation("Vous avez deja votre vie au maximum !", ROUGE);
}

/* Utilise une potion */
void utiliserPotion(const char toucheEntree, const unsigned int typePotion, 
	void (*pointeurFonctionEffetPotion)(const unsigned int effetPotion), 
	const unsigned int effetNiveau1, const unsigned int effetNiveau2)
{
	unsigned int niveauPotion;
	unsigned int retourTestPotion;

	/* On determine le niveau de la potion en fonction du caractere entree (toucheEntree) */

	/* Si c'est une minuscule, c'est une potion de niveau 1 */
	if(islower(toucheEntree))
		niveauPotion = NIVEAU_1;
	/* Sinon c'est une potion de niveau 2 (majuscule) */
	else
		niveauPotion = NIVEAU_2;

	/* On regarde si le joueur peut utiliser la potion typePotion de niveau niveauPotion */
	retourTestPotion = peutUtiliserPotion(typePotion, niveauPotion);

	/* S'il peut l'utiliser */
	if(retourTestPotion == 1)
	{
		/* On appelle la fonction permettant de faire l'effet de la potion typePotion */

		if(niveauPotion == NIVEAU_1)
			pointeurFonctionEffetPotion(effetNiveau1);
		else
			pointeurFonctionEffetPotion(effetNiveau2);

		/* On enleve 1 potion  de type typePotion et de niveau niveauPotion de l'inventaire du
		joueur */
		enleverPotionInventaire(1, typePotion, niveauPotion);

		/* On intialise le nombre de tour durant lesquels la potion est active */
		initialiserNbTourPotionActive(typePotion, niveauPotion);
	}
	/* Sinon */
	else
	{
		/* On affiche le message correspondant a l'erreur */
		afficherErreurPotion(retourTestPotion);

		/* On quitte la fonction */
		return ;
	}
}

/* Pour chaque potion on appelle la fonction utiliserPotion avec comme argument :

	- toucheEntree : la touche que le joueur a presse pour utiliser une potion, soit en 
	minuscule pour une potion de niveau 1, soit en masjuscule pour une potion de niveau 2
	- typePotion : le type de la potion a utiliser
	- pointeurFonctionEffetPotion : un pointeur sur la fonction permettant d'affecter le 
	joueur en fonction de la potion utilisee 
	- effetNiveau1 : l'effet de la potion typePotion de niveau 1
	- effetNiveau2 : l'effet de la potion typePotion de niveau 2
*/

/* Utilise une potion de sante */
void utiliserPotionSante(const char toucheEntree)
{
	utiliserPotion(toucheEntree, SANTE, &ajouterEffetPotionSantePersonnage, NB_VIE_POTION_SANTE_NIVEAU_1, NB_VIE_POTION_SANTE_NIVEAU_2);
}

/* Utilise une potion de force */
void utiliserPotionForce(const char toucheEntree)
{
	utiliserPotion(toucheEntree, FORCE, &ajouterEffetPotionForcePersonnage, NB_FORCE_POTION_FORCE_NIVEAU_1, NB_FORCE_POTION_FORCE_NIVEAU_2);
}

/* Utilise une potion de resistance */
void utiliserPotionResistance(const char toucheEntree)
{
	utiliserPotion(toucheEntree, RESISTANCE, &ajouterEffetPotionResistancePersonnage, NB_RESISTANCE_POTION_RESISTANCE_NIVEAU_1, NB_RESISTANCE_POTION_RESISTANCE_NIVEAU_2);
}

/* Initialise le nombre de tour durant lesquels la potion typePotion de niveau niveauPotion est
active */
void initialiserNbTourPotionActive(const unsigned int typePotion,
	const unsigned int niveauPotion)
{
	/* Contient des pointeurs pour chaque potion pointant sur la variable nbTourPotionActive de 
	la potion */
	static int *nbTourPotionActiveInventaire[NB_POTION] = 
	{
		&(inventaire.sante.nbTourPotionActive),
		&(inventaire.force.nbTourPotionActive),
		&(inventaire.resistance.nbTourPotionActive)
	};

	/* On initialise la valeur de nbTourPotionActive grace a la fonction 
	rerecupererNbTourPotionActive */
	*(nbTourPotionActiveInventaire[typePotion]) = recupererNbTourPotionActive(typePotion, niveauPotion);
}

/* Renvoie le nombre de tour durant lesquels la potion typePotion de niveau niveauPotion est
active */
unsigned int recupererNbTourPotionActive(const unsigned int typePotion,
	const unsigned int niveauPotion)
{
	/* Contient pour chaque potion de chaque niveau le nombre de tour durant lesquels la potion
	est active */
	static const unsigned int nbTourPotionActive[NB_POTION][NB_NIVEAU_POTION] = 
	{
		{3, 8},
		{5, 10},
		{5, 10}
	};

	/* On renvoie le nombre de tour durant lesquels la potion est active */
	return nbTourPotionActive[typePotion][niveauPotion - 1];
}

/* Decremente le nombre de tour ou les potions sont actives */
void decrementezNbTourPotionActive(void)
{
	/* Pour chaque potion, on teste si il y a une potion qui est active, si c'est le cas on la
	decremente de 1 */

	if(inventaire.sante.nbTourPotionActive > 0)
		--(inventaire.sante.nbTourPotionActive);
	if(inventaire.force.nbTourPotionActive > 0)
		--(inventaire.force.nbTourPotionActive);
	if(inventaire.resistance.nbTourPotionActive > 0)
		--(inventaire.resistance.nbTourPotionActive);

	/* Seules les potions de force et de resistance durent, la potion de sante est instantannee */
	/* Si la potion de force ou de resistance est terminee, on enleve le bonus de la potion,
	on indique la fin de la potion et on affiche un message indiquant la fin de la potio */

	if(inventaire.force.nbTourPotionActive == 0)
	{
		personnage.degatParTour -= inventaire.force.nbBonus;
		inventaire.force.nbTourPotionActive = -1;

		ajouterMessageZoneInformation("Votre potion de Force est terminee !", ROUGE);
	}
	if(inventaire.resistance.nbTourPotionActive == 0)
	{
		personnage.protection -= inventaire.resistance.nbBonus;
		inventaire.resistance.nbTourPotionActive = -1;

		ajouterMessageZoneInformation("Votre potion de Resistance est terminee !", ROUGE);
	}
}

/* Genere une potion dans un coffre et place le resultat dans typePotion et niveauPotion */
void genererPotionCoffre(unsigned int *typePotion, unsigned int *niveauPotion)
{
	/* Le joueur a 1 chance sur CHANCE_MAX_POTION_NIVEAU_2 d'avoir une potion de niveau 2,
	sinon il a une potion de niveau 1 */
	/* On determine le niveau de la potion */

	if(tirerChance(1, CHANCE_MAX_POTION_NIVEAU_2))
		*niveauPotion = NIVEAU_2;
	else
		*niveauPotion = NIVEAU_1;

	/* Le joueur a 1 chance sur CHANCE_MAX_POTION_SANTE d'avoir une potion de sante, sinon
	il a 1 chance sur CHANCE_MAX_POTION_FORCE d'avoir une potion de force, sinon il a une 
	potion de resistance */
	/* On determine le type de la potion */

	if(tirerChance(1, CHANCE_MAX_POTION_SANTE))
		*typePotion = SANTE;
	else if(tirerChance(1, CHANCE_MAX_POTION_FORCE))
		*typePotion = FORCE;
	else
		*typePotion = RESISTANCE;
}

/* Affiche la potion dans un coffre */
void afficherPotionCoffre(const unsigned int *typePotion, const unsigned int *niveauPotion)
{
	/* Contient chaque nom de potion */
	static const char *baseNomPotion[NB_POTION] =
	{
		"Sante",
		"Force",
		"Resistance"
	};

	/* Affiche le nom de la potion et son niveau */

	coloration("Potion", VERT);
	printf(" : ");
	
	printf("1 x %s ", baseNomPotion[*typePotion]);

	if(*niveauPotion == NIVEAU_1)
		putchar('I');
	else if(*niveauPotion == NIVEAU_2)
		printf("II");

	putchar('\n');
}

/* Prend la potion d'un coffre */
void prendrePotionCoffre(const unsigned int *typePotion, const unsigned int *niveauPotion)
{
	/* Pour chaque potion, on ajoute a l'inventaire du joueur la potion typePotion de niveau
	niveauPotion */

	switch(*typePotion)
	{
		case SANTE:
			ajouterPotionInventaire(1, recupererTypePotion("sante"), *niveauPotion);
		break;

		case FORCE:
			ajouterPotionInventaire(1, recupererTypePotion("force"), *niveauPotion);
		break;

		case RESISTANCE:
			ajouterPotionInventaire(1, recupererTypePotion("resistance"), *niveauPotion);
		break;
	}		
}

/* Formate le nom d'une potion de maniere correcte (SaNtE -> sante) */
void formaterNomPotion(char *typePotion)
{
	compteur indexTab;

	/* On parcourt la chaine de caractere et on met chaque caractere en minuscule */

	for(indexTab = 0; typePotion[indexTab] != '\0'; ++indexTab)
	{
		if(isupper(typePotion[indexTab]))
			typePotion[indexTab] = tolower(typePotion[indexTab]);
	}
}

/* Retourne le type de la potion grace a son nom donne en parametre */
unsigned int recupererTypePotion(const char *nomPotion)
{
	/* On teste chaque potion et on retourne le type correspondant */

	if(strcmp(nomPotion, "sante") == 0)
		return SANTE;
	else if(strcmp(nomPotion, "force") == 0)
		return FORCE;
	else if(strcmp(nomPotion, "resistance") == 0)
		return RESISTANCE;

	return ERREUR_POTION;
}
