#include <stdio.h>
#include <string.h>

#include "tresor.h"
#include "inventaire.h"
#include "personnage.h"
#include "couleur.h"
#include "coffre.h"

/* Initialise les tresors de l'inventaire dans le fichier Inventaire/tresor.txt */
void initialiserTresorInventaire(void)
{
	FILE *fichierTresor;
	char chemin[TAILLE_MAX];
	compteur indexTresor;

	sprintf(chemin, "Sauvegarde/%s/Inventaire/tresor.txt", personnage.nom);

	/* On ouvre le fichier Inventaire/tresor.txt */
	fichierTresor = ouvrirFichier(chemin, "w+",
	"fichier \"armure.txt\", fonction \"initialiserTresorInventaire\"");

	/* On ecrit les donnees des tresors de base avec le nom, et le cout (pour les NB_TRESOR_MAX) */

	for(indexTresor = 0; indexTresor < NB_TRESOR_MAX; ++indexTresor)
	{
		fprintf(fichierTresor, "Rien\n");
		fprintf(fichierTresor, "0\n");
	}

	fprintf(fichierTresor, "0\n");

	/* On ferme le fichier Inventaire/tresor.txt */
	fermerFichier(fichierTresor,
	"fichier \"armure.txt\", fonction \"initialiserTresorInventaire\"");
}

/* Charge les tresors de l'inventaire dans le fichier Inventaire/tresor.txt */
void chargerTresorInventaire(void)
{
	FILE *fichierTresor;
	char chemin[TAILLE_MAX];
	compteur indexTresor;

	sprintf(chemin, "Sauvegarde/%s/Inventaire/tresor.txt", personnage.nom);

	/* On ouvre le fichier Inventaire/tresor.txt */
	fichierTresor = ouvrirFichier(chemin, "r",
	"fichier \"armure.txt\", fonction \"chargerTresorInventaire\"");

	/* On lit les donnees des tresors avec le nom, et le cout (pour les NB_TRESOR_MAX) */

	for(indexTresor = 0; indexTresor < NB_TRESOR_MAX; ++indexTresor)
	{
		lire(fichierTresor, inventaire.tresor[indexTresor].nom);
		fscanf(fichierTresor, "%d\n", &(inventaire.tresor[indexTresor].cout));
	}

	fscanf(fichierTresor, "%d\n", &(inventaire.tresorActuel));

	/* On ferme le fichier Inventaire/tresor.txt */
	fermerFichier(fichierTresor,
	"fichier \"armure.txt\", fonction \"chargerTresorInventaire\"");
}

/* Sauvegarde les tresors de l'inventaire dans le fichier Inventaire/tresor.txt */
void sauvegarderTresorInventaire(void)
{
	FILE *fichierTresor;
	char chemin[TAILLE_MAX];
	compteur indexTresor;

	sprintf(chemin, "Sauvegarde/%s/Inventaire/tresor.txt", personnage.nom);

	/* On ouvre le fichier Inventaire/tresor.txt */
	fichierTresor = ouvrirFichier(chemin, "w+",
	"fichier \"armure.txt\", fonction \"sauvegarderTresorInventaire\"");

	/* On ecrit les donnees des tresors avec le nom, et le cout (pour les NB_TRESOR_MAX) */

	for(indexTresor = 0; indexTresor < NB_TRESOR_MAX; ++indexTresor)
	{
		fprintf(fichierTresor, "%s\n", inventaire.tresor[indexTresor].nom);
		fprintf(fichierTresor, "%d\n", inventaire.tresor[indexTresor].cout);
	}

	fprintf(fichierTresor, "%d\n", inventaire.tresorActuel);

	/* On ferme le fichier Inventaire/tresor.txt */
	fermerFichier(fichierTresor,
	"fichier \"armure.txt\", fonction \"sauvegarderTresorInventaire\"");
}

/* Affiche une partie individuelle de la section Tresor de l'inventaire lorsqu'on ouvre 
l'inventaire */
void afficherTresorIndividuelInventaire(const unsigned int indexTresor)
{
	coloration(inventaire.tresor[indexTresor].nom, BLEU);
	printf(" | vaut ");
	couleur(VERT);
	printf("%d ", inventaire.tresor[indexTresor].cout);
	couleur(BLANC);
	printf("tek");
}

/* Affiche la section Tresor de l'inventaire lorsqu'on ouvre l'inventaire */
void afficherTresorInventaire(void)
{
	compteur indexTresor;

	/* On affiche seulement les tresors que possedent le joueur */

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

/* Genere un tresor au hasard situe dans un coffre */
void genererTresorCoffre(Tresor *tresor)
{
	/* Pour generer un tresor au hasard, on utilise la base de donnees baseTresor, on tire un 
	index au hasard, on fait un teste pour savoir si on peut avoir le tresor situe a l'index 
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

	/* On tire un nombre au hasard entre 1 et NB_TRESOR - 1 */
	indexTresor = hasard(1, NB_TRESOR - 1);

	/* On fait le test 1 chance sur indexTresor */
	if(tirerChance(1, indexTresor))
	{
		/* Si on reussi le test, on copie les donnees (nom, cout) du tresor situe a l'index 
		indexTresor */
		strcpy(tresor->nom, baseTresor[indexTresor].nom);
		tresor->cout = baseTresor[indexTresor].cout;
	}
	else
	{
		/* Sinon on copie les donnees (nom, cout) du tresor le moins precieux situe a l'index 0 */
		strcpy(tresor->nom, baseTresor[0].nom);
		tresor->cout = baseTresor[0].cout;
	}
}

/* Affiche la section Tresor d'un coffre lorsqu'on l'ouvre */
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

/* Prend le tresor situe dans le coffre que le joueur vient d'ouvrir (donne en parametre) */
void prendreTresorCoffre(const Tresor *tresor)
{
	/* Si le joueur n'a plus de place, car il a atteint le nombre de max de tresor qu'il peut
	transporter */
	if(inventaire.tresorActuel == NB_TRESOR_MAX - 1)
	{
		/* On affiche un message d'erreur */

		coloration("Vous avez trop de tresor sur vous, vous ne pouvez pas en prendre plus !\n", ROUGE);
		coloration("Faites un tour a la boutique pour en vendre et gagner des teks. ;)\n\n", ROUGE);
	}
	/* Sinon */
	else
	{
		/* On copie les donnes du tresor */

		strcpy(inventaire.tresor[inventaire.tresorActuel].nom, tresor->nom);
		inventaire.tresor[inventaire.tresorActuel].cout = tresor->cout;
	
		/* On incremente de 1 le tresorActuel */
		++(inventaire.tresorActuel);
	}
}

/* Renvoie 1 si le joueur possede au moins 1 tresor et 0 sinon */
unsigned int joueurPossedeTresor(void)
{
	/* On renvoie 1 si le joueur possede au moins 1 tresor et 0 sinon */
	return strcmp(inventaire.tresor[0].nom, "Rien") == 0;
}

/* Vend le tresor indexTresor */
void vendreTresor(const unsigned int indexTresor)
{
	compteur indexTab;

	/* On ajoute le nombre de tek que valait le tresor indexTresor que le joueur vient de 
	vendre */
	ajouterTekInventaire(inventaire.tresor[indexTresor].cout);

	/* On affiche un message indiquant le gaint de tek */
	printf("Vous avez gagne %d tek !\n", inventaire.tresor[indexTresor].cout);
	printf("Vous avez %d tek.\n", inventaire.tek.nbTek);

	/* On decale tous les tresors apres la vente */
	for(indexTab = indexTresor; indexTab < NB_TRESOR_MAX - 1; ++indexTab)
	{
		strcpy(inventaire.tresor[indexTab].nom, inventaire.tresor[indexTab + 1].nom);
		inventaire.tresor[indexTab].cout = inventaire.tresor[indexTab + 1].cout;
	}

	/* On met le tresor vendu a 0 */
	strcpy(inventaire.tresor[inventaire.tresorActuel].nom, "Rien");
	inventaire.tresor[inventaire.tresorActuel].cout = 0;

	/* On decremente de 1 l'index correspondant au tresor actuel */
	--(inventaire.tresorActuel);
}
