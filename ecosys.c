#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "ecosys.h"

/* PARTIE 1*/
/* Fourni: Part 1, exercice 4, question 2 */
Animal *creer_animal(int x, int y, float energie) {
  Animal *na = (Animal *)malloc(sizeof(Animal));
  assert(na);
  na->x = x;
  na->y = y;
  na->energie = energie;
  na->dir[0] = rand() % 3 - 1;
  na->dir[1] = rand() % 3 - 1;
  na->suivant = NULL;
  return na;
}


/* Fourni: Part 1, exercice 4, question 3 */
Animal *ajouter_en_tete_animal(Animal *liste, Animal *animal) {
  assert(animal);
  assert(!animal->suivant);
  animal->suivant = liste;
  return animal;
}

/* A faire. Part 1, exercice 6, question 2 */
void ajouter_animal(int x, int y,  float energie, Animal **liste_animal) {
  // J'ajoute à la fin de la liste chaînée
  Animal *tmp = *liste_animal;
  assert(tmp);

  while (tmp) {
    if (tmp->suivant == NULL) {
      tmp->suivant = creer_animal(x, y, energie);
      return ;
    }
    tmp = tmp->suivant;
  }
}

/* A Faire. Part 1, exercice 5, question 5 */
void enlever_animal(Animal **liste, Animal *animal) {
  Animal *tmp;
  // assert(tmp);

  if ((*liste)->x==animal->x && (*liste)->y==animal->y) {
    tmp = (*liste);
    *liste = (*liste)->suivant;
    free(tmp);
  }
  else enlever_animal(&(*liste)->suivant, animal);
  return ;
}

/* A Faire. Part 1, exercice 6, question 7 */
Animal* liberer_liste_animaux(Animal *liste) {
  // assert(liste);
  Animal *tmp;

  while (liste) {
    tmp = liste->suivant;
    free(liste);
    liste = tmp; 
  }

  return NULL;
}

/* Fourni: part 1, exercice 4, question 4 */
unsigned int compte_animal_rec(Animal *la) {
  if (!la) return 0;
  return 1 + compte_animal_rec(la->suivant);
}

/* Fourni: part 1, exercice 4, question 4 */
unsigned int compte_animal_it(Animal *la) {
  int cpt=0;
  while (la) {
    ++cpt;
    la=la->suivant;
  }
  return cpt;
}



/* Part 1. Exercice 5, question 1, ATTENTION, ce code est susceptible de contenir des erreurs... */
void afficher_ecosys(Animal *liste_proie, Animal *liste_predateur) {
  unsigned int i, j;
  char ecosys[SIZE_X][SIZE_Y];
  Animal *pa=NULL;

  /* on initialise le tableau */
  for (i = 0; i < SIZE_X; ++i) {
    for (j = 0; j < SIZE_Y; ++j) 
      ecosys[i][j]=' ';
  }

  /* on ajoute les proies */
  pa = liste_proie;
  while (pa) {
    ecosys[pa->x][pa->y] = '*';
    pa=pa->suivant;
  }

  /* on ajoute les predateurs */
  pa = liste_predateur;
  while (pa) {
      if ((ecosys[pa->x][pa->y] == '@') || (ecosys[pa->x][pa->y] == '*'))  /* proies aussi present */
        ecosys[pa->x][pa->y] = '@';
      else 
        ecosys[pa->x][pa->y] = 'O';

    pa = pa->suivant;
  }

  /* on affiche le tableau */
  printf("+");
  for (j = 0; j < SIZE_Y; ++j) 
    printf("-");
  
  printf("+\n");

  for (i = 0; i < SIZE_X; ++i) {
    printf("|");
    for (j = 0; j < SIZE_Y; ++j) 
      putchar(ecosys[i][j]); 
    
    printf("|\n");
  }

  printf("+");
  for (j = 0; j<SIZE_Y; ++j) 
    printf("-");
  
  printf("+\n");

  int nbproie=compte_animal_it(liste_proie);
  int nbpred=compte_animal_it(liste_predateur);
  
  printf("Nb proies : %5d\tNb predateurs : %5d\n", nbproie, nbpred);
}


void clear_screen() {
  printf("\x1b[2J\x1b[1;1H");  /* code ANSI X3.4 pour effacer l'ecran */
}

/*
==================================================
==================================================
==================================================
*/


/* PARTIE 2*/

/* Part 2. Exercice 4, question 1 */
void bouger_animaux(Animal *la) {
  Animal *ap = la;
  // assert(ap);

  while (ap) {
    if (rand()/(float)RAND_MAX < p_ch_dir) {
      ap->dir[0] = rand() % 3 - 1;
      ap->dir[1] = rand() % 3 - 1;
    }
    ap->x = (ap->x + ap->dir[0] + SIZE_X) % SIZE_X;
    ap->y = (ap->y + ap->dir[1] + SIZE_Y) % SIZE_Y;

    ap = ap->suivant;
  }
}

/* Part 2. Exercice 4, question 3 */
void reproduce(Animal **liste_animal, float p_reproduce) {
  Animal *ap = *liste_animal;
  // assert(ap);

  while (ap) {
    if (rand()/(float)RAND_MAX < p_reproduce) {
      ajouter_animal(ap->x, ap->y, ap->energie/2, liste_animal);
      ap->energie = ap->energie/2;
    }
    ap = ap->suivant;
  }
}


/* Part 2. Exercice 6, question 1 */
void rafraichir_proies(Animal **liste_proie, int monde[SIZE_X][SIZE_Y]) { // WORKEDDDDD!!!!!
  /* Bouger les proies */
  Animal *tmp = *liste_proie;
  bouger_animaux(tmp);

  /* Parcourir les listes */
  /* Baisser l'energie */
  while (tmp) {
    if (monde[tmp->x][tmp->y]>0) {
      tmp->energie += monde[tmp->x][tmp->y];
      monde[tmp->x][tmp->y] = temps_repousse_herbe;
    }
    else tmp->energie -= 1;

    if (tmp->energie<0) 
      enlever_animal(liste_proie, tmp);

    tmp = tmp->suivant;
  }

  /* Reproduce */
  reproduce(liste_proie, p_reproduce_proie);
}

/* Part 2. Exercice 7, question 1 */
Animal *animal_en_XY(Animal *l, int x, int y) {
  
  Animal *tmp = l;
  while (tmp) {
    if (tmp->x==x && tmp->y==y) 
      return tmp;
    
    tmp = tmp->suivant;
  }
  return NULL;
} 

/* Part 2. Exercice 7, question 2 */
void rafraichir_predateurs(Animal **liste_predateur, Animal **liste_proie) {
  /* Bouger les predateurs */
  Animal *pred = *liste_predateur, *proie;
  bouger_animaux(pred);

  /* Parcourir les listes */
  while (pred) {
    /* Code un peu longue (mais ca marche) */
    if (animal_en_XY((*liste_proie), pred->x, pred->y)) {
      while (*liste_proie) {
        if ((*liste_proie)->x==pred->x && (*liste_proie)->y==pred->y) {
          proie =  *liste_proie;
          pred->energie += proie->energie;
          enlever_animal(liste_proie, proie); 
        }
        else *liste_proie = (*liste_proie)->suivant;
      }
    }
    else pred->energie -= 1; 

    pred = pred->suivant;
  }

  /* Reproduce */
  reproduce(liste_predateur, p_reproduce_predateur);
}

/* Part 2. Exercice 5, question 2 */
void rafraichir_monde(int monde[SIZE_X][SIZE_Y]){
  for (unsigned i=0;i<SIZE_X;++i) {
    for (unsigned j=0;j<SIZE_Y;++j) 
      monde[i][j] += 1;
  }
}




/* Ecrire ecosysteme */
void ecrire_ecosys(const char *nom_fichier, Animal *liste_pred, Animal *liste_proie) {
  FILE *f = fopen(nom_fichier, "w");
  if (f == NULL) {
    printf("Erreur lors de l'ouverture\n");
    return ;
  }

  /* Ecrire liste proies */
  fprintf(f, "<proies>\n");
  Animal *tmp = liste_proie;
  while (tmp) {
    fprintf(f, "x = %d, y = %d, dir = [%d %d], e = %f\n", tmp->x, tmp->y, tmp->dir[0], tmp->dir[1], tmp->energie);
    tmp = tmp->suivant;
  }
  fprintf(f, "</proies>\n");

  /* Ecrire liste predateurs */
  fprintf(f, "<predateur>\n");
  tmp = liste_pred;
  while (tmp) {
    fprintf(f, "x = %d, y = %d, dir = [%d %d], e = %f\n", tmp->x, tmp->y, tmp->dir[0], tmp->dir[1], tmp->energie);
    tmp = tmp->suivant;
  }
  fprintf(f, "</predateur>\n");
  fclose(f);
}

/* Lecture fichier */
void lire_ecosys(const char *nom_fichier, Animal **liste_pred, Animal **liste_proie) {
  FILE *f = fopen(nom_fichier, "r");
  if (f==NULL) {
    printf("Erreur d'ouverture\n");
    return ;
  }
  
  char buffer[256];
  fgets(buffer, 256, f);
  assert(strncmp(buffer, "<proies>", 8) == 0);
  fgets(buffer, 256, f);
  
  int x_lu, y_lu, dir_lu[2];
  float e_lu;

  /* Lire liste proies */
  while (strncmp(buffer, "</proies>", 9)!=0) {
    sscanf(buffer, "x = %d, y = %d, dir = [%d %d], e = %f\n", &x_lu, &y_lu, &dir_lu[0], &dir_lu[1], &e_lu);
    Animal *a_lu = creer_animal(x_lu, y_lu, e_lu);
    a_lu->dir[0] = dir_lu[0];
    a_lu->dir[1] = dir_lu[1];
    a_lu->suivant = *liste_proie;
    *liste_proie = a_lu;
    fgets(buffer, 256, f);
  }

  fgets(buffer, 256, f);
  assert(strncmp(buffer, "<predateur>", 11) == 0); // a modifier apres
  fgets(buffer, 256, f);

  /* Lire liste predateurs */
  while (strncmp(buffer, "</predateur>", 12)!=0) {
    sscanf(buffer, "x = %d, y = %d, dir = [%d %d], e = %f\n", &x_lu, &y_lu, &dir_lu[0], &dir_lu[1], &e_lu);
    Animal *a_lu = creer_animal(x_lu, y_lu, e_lu);
    a_lu->dir[0] = dir_lu[0];
    a_lu->dir[1] = dir_lu[1];
    a_lu->suivant = *liste_pred;
    *liste_pred = a_lu;
    fgets(buffer, 256, f);
  }

  fclose(f);
}