#include <stdio.h>
#include <string.h>

#include "tresor.h"
#include "inventaire.h"
#include "personnage.h"
#include "couleur.h"
#include "coffre.h"

void initialiserTresorInventaire(void)
{
	FILE *fichierTresor;
	char chemin[TAILLE_MAX];
	compteur indexTresor;

	sprintf(chemin, "Sauvegarde/%s/Inventaire/tresor.txt", personnage.nom);

	fichierTresor = ouvrirFichier(chemin, "w+",
	"fichier \"armure.txt\", fonction \"initialiserTresorInventaire\"");

	for(indexTresor = 0; indexTresor < NB_TRESOR_MAX; ++indexTresor)
	{
		fprintf(fichierTresor, "Rien\n");
		fprintf(fichierTresor, "0\n");
	}

	fprintf(fichierTresor, "0\n");

	fermerFichier(fichierTresor,
	"fichier \"armure.txt\", fonction \"initialiserTresorInventaire\"");
}

void chargerTresorInventaire(void)
{
	FILE *fichierTresor;
	char chemin[TAILLE_MAX];
	compteur indexTresor;

	sprintf(chemin, "Sauvegarde/%s/Inventaire/tresor.txt", personnage.nom);

	fichierTresor = ouvrirFichier(chemin, "r",
	"fichier \"armure.txt\", fonction \"chargerTresorInventaire\"");

	for(indexTresor = 0; indexTresor < NB_TRESOR_MAX; ++indexTresor)
	{
		lire(fichierTresor, inventaire.tresor[indexTresor].nom);
		fscanf(fichierTresor, "%d\n", &(inventaire.tresor[indexTresor].cout));
	}

	fscanf(fichierTresor, "%d\n", &(inventaire.tresorActuel));

	fermerFichier(fichierTresor,
	"fichier \"armure.txt\", fonction \"chargerTresorInventaire\"");
}

void sauvegarderTresorInventaire(void)
{
	FILE *fichierTresor;
	char chemin[TAILLE_MAX];
	compteur indexTresor;

	sprintf(chemin, "Sauvegarde/%s/Inventaire/tresor.txt", personnage.nom);

	fichierTresor = ouvrirFichier(chemin, "w+",
	"fichier \"armure.txt\", fonction \"sauvegarderTresorInventaire\"");

	for(indexTresor = 0; indexTresor < NB_TRESOR_MAX; ++indexTresor)
	{
		fprintf(fichierTresor, "%s\n", inventaire.tresor[indexTresor].nom);
		fprintf(fichierTresor, "%d\n", inventaire.tresor[indexTresor].cout);
	}

	fprintf(fichierTresor, "%d\n", inventaire.tresorActuel);

	fermerFichier(fichierTresor,
	"fichier \"armure.txt\", fonction \"sauvegarderTresorInventaire\"");
}

void afficherTresorIndividuelInventaire(const unsigned int indexTresor)
{
	coloration(inventaire.tresor[indexTresor].nom, BLEU);
	printf(" | vaut ");
	couleur(VERT);
	printf("%d ", inventaire.tresor[indexTresor].cout);
	couleur(BLANC);
	printf("tek");
}

void afficherTresorInventaire(void)
{
	compteur indexTresor;

	coloration("Tresor", VERT);
	printf(" : \n\n");

	if(strcmp(inventaire.tresor[0].nom, "Rien") == 0)
	{
		printf("\t- ");
		coloration("Aucun", BLEU);
	}
	else
	{
		for(indexTresor = 0; indexTresor < NB_TRESOR_MAX; ++indexTresor)
		{	
			if(strcmp(inventaire.tresor[indexTresor].nom, "Rien") != 0)
			{
				printf("\t- ");
				afficherTresorIndividuelInventaire(indexTresor);
				printf("\n");
			}
		}
	}

	printf("\n\n");
}

void genererTresorCoffre(Tresor *tresor)
{
	/* Pour generer un tresor au hasard, on utilise la base de donnees baseTresor, on tire un 
	index au hasard, on fait un test pour savoir si on peut avoir le tresor situe a l'index 
	(1 chance sur x, x ici est l'index precedemment tire), si on reussi alors on copie toutes 
	les donnes dans la variable tresor donnee en parametre, sinon on copie les donnees du tresor
	le moins precieux situe a l'index 0 du tableau baseTresor */

	/* Base de donnee contenant chaque tresor avec nom, cout */
	static const Tresor baseTresor[NB_TRESOR] =
	{
		{"Tapis rare", 10},
		{"Fossile rare", 20},
		{"Statue rare", 20},
		{"Vase rare", 20},
		{"Vase en ceramique", 30},
		{"Bague en rubis", 30},
		{"Pendentif d'emeraude", 30},
		{"Couronne sacree", 40},
		{"Relique sacree", 40},
		{"Collier magique", 40},
		{"Pierre precieuse", 50},
		{"Bracelet authentique", 50},
		{"Bracelet en diamant", 60},
		{"Statue en ivoire", 60},
		{"Lot de perle authentique", 70},
		{"Dague en argent", 70},
		{"Anneau sacre", 80},
		{"Statuette ancienne", 80},
		{"Harpe doree", 90},
		{"Manteau du roi Squalala", 90},
		{"Baton magique", 100},
		{"Lyre magique", 100},
		{"Epee enchantee", 110},
		{"Stele", 110},
		{"Bouclier magique", 125},
		{"Broche en or", 125},
		{"Trone dore", 125},
		{"Epee en or massif", 130},
		{"Stele inconnue", 130},
		{"Casque du chevalier Rhyddid", 150},
		{"Epee du chevalier Rhyddid", 150},
		{"Medaillon magique", 150},
		{"Broche en diamant", 150},
		{"Epee supreme", 150},
		{"Nunchaku en or massif", 175},
		{"Shuriken en argent", 200},
		{"Relique mystique", 200},
		{"Perle noire", 200},
		{"Lingot d'or", 225},
		{"Gemme de quartz", 250},
		{"Gemme de rubis", 275},
		{"Gemme d'emeraude", 300},
		{"Gemme de saphir", 325},
		{"Gemme de topaz", 350},
		{"Gemme d'opale", 375},
		{"Gemme de diamant", 400},
		{"La dague Ao", 500},
		{"Pierre philosophale", 650},
		{"Rubik's cube du developpeur", 1000},
		{"Clavier du developpeur", 1000}
	};
	unsigned int indexTresor;

	indexTresor = hasard(1, NB_TRESOR - 1);

	if(tirerChance(1, indexTresor))
	{
		strcpy(tresor->nom, baseTresor[indexTresor].nom);
		tresor->cout = baseTresor[indexTresor].cout;
	}
	else
	{
		strcpy(tresor->nom, baseTresor[0].nom);
		tresor->cout = baseTresor[0].cout;
	}
}

void afficherTresorCoffre(const Coffre *coffre)
{
	coloration("Tresor", VERT);
	printf(" : ");

	coloration(coffre->inventaire.tresor[0].nom, BLEU);
	printf(" | vaut ");
	couleur(VERT);
	printf("%d ", coffre->inventaire.tresor[0].cout);
	couleur(BLANC);
	printf("tek");

	putchar('\n');
}

void prendreTresorCoffre(const Tresor *tresor)
{
	if(inventaire.tresorActuel == NB_TRESOR_MAX - 1)
	{
		coloration("Vous avez trop de tresor sur vous, vous ne pouvez pas en prendre plus !\n", ROUGE);
		coloration("Faites un tour a la boutique pour en vendre et gagner des teks. ;)\n\n", ROUGE);
	}
	else
	{
		strcpy(inventaire.tresor[inventaire.tresorActuel].nom, tresor->nom);
		inventaire.tresor[inventaire.tresorActuel].cout = tresor->cout;
		++(inventaire.tresorActuel);
	}
}

unsigned int joueurPossedeTresor(void)
{
	return strcmp(inventaire.tresor[0].nom, "Rien") == 0;
}

void vendreTresor(const unsigned int indexTresor)
{
	compteur indexTab;

	ajouterTekInventaire(inventaire.tresor[indexTresor].cout);

	printf("Vous avez gagne %d tek !\n", inventaire.tresor[indexTresor].cout);
	printf("Vous avez %d tek.\n", inventaire.tek.nbTek);

	for(indexTab = indexTresor; indexTab < NB_TRESOR_MAX - 1; ++indexTab)
	{
		strcpy(inventaire.tresor[indexTab].nom, inventaire.tresor[indexTab + 1].nom);
		inventaire.tresor[indexTab].cout = inventaire.tresor[indexTab + 1].cout;
	}

	strcpy(inventaire.tresor[inventaire.tresorActuel].nom, "Rien");
	inventaire.tresor[inventaire.tresorActuel].cout = 0;
	--(inventaire.tresorActuel);
}
