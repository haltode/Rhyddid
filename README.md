# Rhyddid


Rhyddid est un rogue-like, dans lequel vous incarnez un personnage dont vous choisissez la race et le métier. Vous traversez les niveaux, en combattant et  en découvrant des objets (armes, armures, trésors). Chaque niveau possède une clé pour accéder au niveau suivant, cette clé se trouve aléatoirement sur le niveau bien gardée par l'un des ennemis. Chaque niveau est composé de 9 salles, toutes différentes et contenant des coffres, des ennemis et même une caverne si vous êtes chanceux...

## Se déplacer dans les menus

Pour vous déplacer dans les menus il faut utiliser les chiffres, pour revenir en arrière tapez -1, pour quitter le jeu tapez 0.

### Menu principal

Le menu principal est compose de 4 sous-menus :

* Sauvegarde : permet de gérer vos sauvegardes (créer, charger, supprimer).
* Highscore : permet de consulter votre top 10 de vos performances.
* Aide : permet d’accéder à ce texte, c'est une aide complète.
* Quitter : permet de quitter le jeu.

#### Sauvegarde

Le menu Sauvegarde est composé de trois sauvegardes au maximum, vous pouvez créer une nouvelle partie en sélectionnant un espace de sauvegarde vide, vous pouvez charger et supprimer une sauvegarde en sélectionnant une sauvegarde non vide.

#### Highscore

Le highscore présente une liste de vos 10 meilleures performances en indiquant pour chacune le nom de la partie, la race du joueur, le métier du joueur, le lvl du joueur, et le dernier niveau atteint par le joueur.

#### Aide

L'aide vous sera très précieuse au début du jeu pour bien comprendre, je vous conseille de la lire au moins une fois.

## Nouvelle partie

Pour créer une nouvelle partie, sélectionnez un espace de sauvegarde vide,    entrez un nom de personnage, choisissez la race de votre nouveau personnage (vous pouvez aussi visualiser les races, ce qui vous permet de voir ses caractéristiques ainsi qu'un ASCII Art), puis choisissez un métier (chaque métier vous apporte des compétences supplémentaires à votre personnage). Un texte vous expliquant l'histoire de Rhyddid apparaît.

## Jeu

Après avoir charger ou créer une partie, vous verrez le jeu. En haut a gauche se situe la carte du niveau (le "E" indique l’entrée, le "S" indique la sortie, le "X" indique votre position), la carte est composée de 9 carrés représentant chacun une salle. A droite de la carte se trouve le résumé de votre personnage indiquant le niveau actuel où vous vous trouvez, son Lvl, son EXP, sa santé, ses dégâts, sa protection. En dessous, vous voyez la salle actuelle.

## Touches

Voici les différentes touches de Rhyddid :

z = haut
s = bas
q = gauche
d = droite

n = sauvegarder et quitter
m = sauvegarder

ECHAP = pause

e = inventaire

t = attaquer ennemi

h = potion de santé niveau I
j = potion de force niveau I
k = potion de résistance niveau I

H = potion de santé niveau II
J = potion de force niveau II
K = potion de résistance niveau II

## Boutique

Une boutique est mis a votre disposition, vous pouvez y accéder après avoir passé la porte de sortie du niveau. La boutique vous permet d'acheter des potions et de vendre des trésors contre des teks (la monnaie de Rhyddid).

Voici les prix des potions :

potion de santé I -> 30 teks
potion de force I -> 20 teks
potion de résistance I -> 20 teks

potion de santé II -> 70 teks
potion de force II -> 60 teks
potion de résistance II -> 60 teks

## Caverne

Il se peut que vous trouviez une caverne dans un niveau, celle-ci contient soit des coffres, soit beaucoup d'ennemis ...

Voici a quoi elle pourrait ressembler :

```
   _| |_  
 `/     \'
  |     | 
  |     | 
 ,\_____/.
```

## Ennemi

Les ennemis ont une IA qui évolue (en fonction du niveau dans lequel vous vous trouvez). Chaque ennemi a des caractéristiques différents (santé, dégât, protection), à partir d'un certain rayon de distance l'ennemi vous "focus", et vous suit de manière à vous tuer pendant un certain nombre de tour, après il arrête de vous suivre. Un ennemi choisi aléatoirement dans tout le niveau porte la clé de fin de niveau, vous devez le tuer pour avoir la clé.

## Combat

Pour attaquer un ennemi utiliser la touche 't'. Lorsque vous attaquez un ennemi la carte en haut à gauche se transforme en ASCII Art de l'ennemi et vous indique ses caractéristiques (santé, dégât, protection).

## Arme

Il existe 35 armes dans le jeu. Une arme se compose d'un nom, d'un nombre de dégât, et d'un nombre représentant la portée de l'arme.

## Armure

Il existe 30 armures dans le jeu. Une armure se compose d'un nom, et d'un nombre représentant la protection.

## Armure

Il existe 3 types de potions : potion de santé, force, résistance. Chacune affecte respectivement les caractéristiques du joueur : santé, dégât, protection. Il y a 2 niveaux de potions : le niveau I et le niveau II. Voici les effets des potions :

santé I -> 4 points de vie
santé II -> 10 points de vie

force I -> 4 points de dégât pendant 5 tours
force II -> 8 points de dégât pendant 10 tours

résistance I -> 3 point de résistance pendant 5 tours
résistance II -> 7 point de résistance pendant 10 tours

Vous ne pouvez pas utiliser plusieurs potions du même type quand vous avez déjà utilisé une potion de ce type et qu'elle n'a pas fini son effet.

La potion de santé I nécessite d'attendre 3 tours avant de réutiliser une potion de santé. La potion de santé II nécessite d'attendre 8 tours avant de réutiliser une potion de santé.

## Trésor

Il existe 50 trésors dans le jeu. Un trésor se compose d'un nom, d'un nombre de tek correspondant au coût de la vente du trésor. Vous pouvez vendre vos trésors dans la boutique et ainsi obtenir des teks.

## Clé

La clé de fin de niveau se trouve sur un ennemi dans le niveau, il faut tuer cet ennemi pour obtenir la clé. Une fois que vous avez la clé allez vers la sortie. Vous arriverez dans un nouveau niveau.

## EXP

L'EXP est donné par un ennemi lorsque vous le tuez, au bout de 100 EXP vous augmenter de Lvl ce qui vous permet d’améliorer une de vos caractéristiques (santé, dégât, protection).

## Coffre

Les coffres sont placés aléatoirement dans les salles, ils peuvent contenir des armes, des armures, des teks, des trésors, des potions. Ils peuvent être vides, ou même piégés et dans ce cas un ennemi apparaîtra.

## Inventaire

Votre inventaire est composé d'une arme, d'une armure, de potions, de tek, de 5 trésors au maximum.

## Mort

Lorsque vous mourrez, vos statistiques sont conservées dans le highscore, et votre partie est supprimée.