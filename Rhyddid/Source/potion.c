#include <stdio.h>
#include <string.h>
#include <ctype.h>

#include "potion.h"
#include "inventaire.h"
#include "personnage.h"
#include "fonctionsUtiles.h"
#include "couleur.h"
#include "jeu.h"

void initialiserPotionInventaire(void)
{
	FILE *fichierPotion;
	char chemin[TAILLE_MAX];

	sprintf(chemin, "Sauvegarde/%s/Inventaire/potion.txt", personnage.nom);

	fichierPotion = ouvrirFichier(chemin, "w+",
	"fichier \"potion.txt\", fonction \"initialiserPotionInventaire\"");

	fprintf(fichierPotion, "0 0 -1 0\n");
	fprintf(fichierPotion, "0 0 -1 0\n");
	fprintf(fichierPotion, "0 0 -1 0\n");

	fermerFichier(fichierPotion,
	"fichier \"potion.txt\", fonction \"initialiserPotionInventaire\"");
}

void chargerPotionInventaire(void)
{
	FILE *fichierPotion;
	char chemin[TAILLE_MAX];

	sprintf(chemin, "Sauvegarde/%s/Inventaire/potion.txt", personnage.nom);

	fichierPotion = ouvrirFichier(chemin, "r",
	"fichier \"potion.txt\", fonction \"chargerPotionInventaire\"");

	fscanf(fichierPotion, "%d %d %d %d\n", &(inventaire.sante.nbPotionForce1), &(inventaire.sante.nbPotionForce2), &(inventaire.sante.nbTourPotionActive), &(inventaire.sante.nbBonus));
	fscanf(fichierPotion, "%d %d %d %d\n", &(inventaire.force.nbPotionForce1), &(inventaire.force.nbPotionForce2), &(inventaire.force.nbTourPotionActive), &(inventaire.force.nbBonus));
	fscanf(fichierPotion, "%d %d %d %d\n", &(inventaire.resistance.nbPotionForce1), &(inventaire.resistance.nbPotionForce2), &(inventaire.resistance.nbTourPotionActive), &(inventaire.resistance.nbBonus));

	fermerFichier(fichierPotion,
	"fichier \"potion.txt\", fonction \"chargerPotionInventaire\"");
}

void sauvegarderPotionInventaire(void)
{
	FILE *fichierPotion;
	char chemin[TAILLE_MAX];

	sprintf(chemin, "Sauvegarde/%s/Inventaire/potion.txt", personnage.nom);

	fichierPotion = ouvrirFichier(chemin, "w+",
	"fichier \"potion.txt\", fonction \"sauvegarderPotionInventaire\"");

	fprintf(fichierPotion, "%d %d %d %d\n", inventaire.sante.nbPotionForce1, inventaire.sante.nbPotionForce2, inventaire.sante.nbTourPotionActive, inventaire.sante.nbBonus);
	fprintf(fichierPotion, "%d %d %d %d\n", inventaire.force.nbPotionForce1, inventaire.force.nbPotionForce2, inventaire.force.nbTourPotionActive, inventaire.force.nbBonus);
	fprintf(fichierPotion, "%d %d %d %d\n", inventaire.resistance.nbPotionForce1, inventaire.resistance.nbPotionForce2, inventaire.resistance.nbTourPotionActive, inventaire.resistance.nbBonus);

	fermerFichier(fichierPotion,
	"fichier \"potion.txt\", fonction \"sauvegarderPotionInventaire\"");
}

void afficherPotionIndividuelleInventaire(const char *nomPotion, 
	const unsigned int nbPotionNiveau1, const unsigned int nbPotionNiveau2)
{
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

void afficherPotionInventaire(void)
{
	coloration("Potion", VERT);
	printf(" : \n\n");
	
	afficherPotionIndividuelleInventaire("Sante", inventaire.sante.nbPotionForce1, inventaire.sante.nbPotionForce2);
	afficherPotionIndividuelleInventaire("Force", inventaire.force.nbPotionForce1, inventaire.force.nbPotionForce2);
	afficherPotionIndividuelleInventaire("Resistance", inventaire.resistance.nbPotionForce1, inventaire.resistance.nbPotionForce2);
}

void ajouterPotionInventaire(const unsigned int quantitePotion, const unsigned int typePotion, 
	const unsigned int niveauPotion)
{
	static unsigned int *nbPotionInventaire[NB_POTION][NB_NIVEAU_POTION] = 
	{
		{&(inventaire.sante.nbPotionForce1),			&(inventaire.sante.nbPotionForce2)}, 
		{&(inventaire.force.nbPotionForce1),			&(inventaire.force.nbPotionForce2)},
		{&(inventaire.resistance.nbPotionForce1),		&(inventaire.resistance.nbPotionForce2)}
	};

	*(nbPotionInventaire[typePotion][niveauPotion]) += quantitePotion;
}

void enleverPotionInventaire(const unsigned int quantitePotion, const unsigned int typePotion, 
	const unsigned int niveauPotion)
{
	static unsigned int *nbPotionInventaire[NB_POTION][NB_NIVEAU_POTION] = 
	{
		{&(inventaire.sante.nbPotionForce1),			&(inventaire.sante.nbPotionForce2)}, 
		{&(inventaire.force.nbPotionForce1),			&(inventaire.force.nbPotionForce2)},
		{&(inventaire.resistance.nbPotionForce1),		&(inventaire.resistance.nbPotionForce2)}
	};

	*(nbPotionInventaire[typePotion][niveauPotion]) -= quantitePotion;
}

unsigned int peutUtiliserPotion(const unsigned int typePotion, const unsigned int niveauPotion)
{
	unsigned int nbPotionForce1, nbPotionForce2;
	int nbTourPotionActive;

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

	if(niveauPotion == NIVEAU_1 && nbPotionForce1 == 0)
		return AUCUNE_POTION;
	else if(niveauPotion == NIVEAU_2 && nbPotionForce2 == 0)
		return AUCUNE_POTION;

	if(nbTourPotionActive > 0)
		return NON_UTILISABLE;

	if(typePotion == SANTE && personnage.santeActuelle == personnage.sante)
		return VIE_MAXIMUM;

	return 1;
}

void afficherErreurPotion(const unsigned int typeErreurPotion)
{
	if(typeErreurPotion == AUCUNE_POTION)
		ajouterMessageZoneInformation("Vous n'avez pas de potion de ce type !", ROUGE);
	else if(typeErreurPotion == NON_UTILISABLE)
		ajouterMessageZoneInformation("Vous devez attendre la fin de la potion avant d'en utiliser une autre !", ROUGE);
	else if(typeErreurPotion == VIE_MAXIMUM)
		ajouterMessageZoneInformation("Vous avez deja votre vie au maximum !", ROUGE);
}

void utiliserPotion(const char toucheEntree, const unsigned int typePotion, 
	void (*pointeurFonctionEffetPotion)(const unsigned int effetPotion), 
	const unsigned int effetNiveau1, const unsigned int effetNiveau2)
{
	unsigned int niveauPotion;
	unsigned int retourTestPotion;

	if(islower(toucheEntree))
		niveauPotion = NIVEAU_1;
	else
		niveauPotion = NIVEAU_2;

	retourTestPotion = peutUtiliserPotion(typePotion, niveauPotion);

	if(retourTestPotion == 1)
	{
		if(niveauPotion == NIVEAU_1)
			pointeurFonctionEffetPotion(effetNiveau1);
		else
			pointeurFonctionEffetPotion(effetNiveau2);

		enleverPotionInventaire(1, typePotion, niveauPotion);
		initialiserNbTourPotionActive(typePotion, niveauPotion);
	}
	else
	{
		afficherErreurPotion(retourTestPotion);
		return ;
	}
}

void utiliserPotionSante(const char toucheEntree)
{
	utiliserPotion(toucheEntree, SANTE, &ajouterEffetPotionSantePersonnage, NB_VIE_POTION_SANTE_NIVEAU_1, NB_VIE_POTION_SANTE_NIVEAU_2);
}

void utiliserPotionForce(const char toucheEntree)
{
	utiliserPotion(toucheEntree, FORCE, &ajouterEffetPotionForcePersonnage, NB_FORCE_POTION_FORCE_NIVEAU_1, NB_FORCE_POTION_FORCE_NIVEAU_2);
}

void utiliserPotionResistance(const char toucheEntree)
{
	utiliserPotion(toucheEntree, RESISTANCE, &ajouterEffetPotionResistancePersonnage, NB_RESISTANCE_POTION_RESISTANCE_NIVEAU_1, NB_RESISTANCE_POTION_RESISTANCE_NIVEAU_2);
}

void initialiserNbTourPotionActive(const unsigned int typePotion,
	const unsigned int niveauPotion)
{
	static int *nbTourPotionActiveInventaire[NB_POTION] = 
	{
		&(inventaire.sante.nbTourPotionActive),
		&(inventaire.force.nbTourPotionActive),
		&(inventaire.resistance.nbTourPotionActive)
	};

	*(nbTourPotionActiveInventaire[typePotion]) = recupererNbTourPotionActive(typePotion, niveauPotion);
}

unsigned int recupererNbTourPotionActive(const unsigned int typePotion,
	const unsigned int niveauPotion)
{
	static const unsigned int nbTourPotionActive[NB_POTION][NB_NIVEAU_POTION] = 
	{
		{3, 8},
		{5, 10},
		{5, 10}
	};

	return nbTourPotionActive[typePotion][niveauPotion - 1];
}

void decrementezNbTourPotionActive(void)
{
	if(inventaire.sante.nbTourPotionActive > 0)
		--(inventaire.sante.nbTourPotionActive);
	if(inventaire.force.nbTourPotionActive > 0)
		--(inventaire.force.nbTourPotionActive);
	if(inventaire.resistance.nbTourPotionActive > 0)
		--(inventaire.resistance.nbTourPotionActive);

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

void genererPotionCoffre(unsigned int *typePotion, unsigned int *niveauPotion)
{
	if(tirerChance(1, CHANCE_MAX_POTION_NIVEAU_2))
		*niveauPotion = NIVEAU_2;
	else
		*niveauPotion = NIVEAU_1;

	if(tirerChance(1, CHANCE_MAX_POTION_SANTE))
		*typePotion = SANTE;
	else if(tirerChance(1, CHANCE_MAX_POTION_FORCE))
		*typePotion = FORCE;
	else
		*typePotion = RESISTANCE;
}

void afficherPotionCoffre(const unsigned int *typePotion, const unsigned int *niveauPotion)
{
	static const char *baseNomPotion[NB_POTION] =
	{
		"Sante",
		"Force",
		"Resistance"
	};

	coloration("Potion", VERT);
	printf(" : ");
	
	printf("1 x %s ", baseNomPotion[*typePotion]);

	if(*niveauPotion == NIVEAU_1)
		putchar('I');
	else if(*niveauPotion == NIVEAU_2)
		printf("II");

	putchar('\n');
}

void prendrePotionCoffre(const unsigned int *typePotion, const unsigned int *niveauPotion)
{
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

void formaterNomPotion(char *typePotion)
{
	compteur indexTab;

	for(indexTab = 0; typePotion[indexTab] != '\0'; ++indexTab)
		if(isupper(typePotion[indexTab]))
			typePotion[indexTab] = tolower(typePotion[indexTab]);
}

unsigned int recupererTypePotion(const char *nomPotion)
{
	if(strcmp(nomPotion, "sante") == 0)
		return SANTE;
	else if(strcmp(nomPotion, "force") == 0)
		return FORCE;
	else if(strcmp(nomPotion, "resistance") == 0)
		return RESISTANCE;

	return ERREUR_POTION;
}
