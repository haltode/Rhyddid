#include <stdio.h>

#include "chargerSauvegarde.h"
#include "sauvegarde.h"
#include "jeu.h"

void chargerSauvegarde(const char *nomSauvegarde)
{
	recupererInformationPersonnage(nomSauvegarde);
	jeu();
}
