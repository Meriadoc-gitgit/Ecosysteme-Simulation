#include <assert.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>


#include "ecosys.h"



int main(void) {
  int k;
  Animal *liste_Proie = NULL;
  Animal *liste_Predateur = NULL;
  int energie=10;

  srand(time(NULL));

  Animal *a1 = creer_animal(0,10, energie);
  Animal *a2 = creer_animal(15,35, energie);
  Animal *a3 = creer_animal(2,42, energie);
  Animal *a4 = creer_animal(18,13, energie);
  
  a1->suivant=a2;
  a2->suivant=a3;
  a3->suivant=a4;

  liste_Proie=a1;

  Animal *a5 = creer_animal(2,5, energie);
  Animal *a6 = creer_animal(15,35, energie);
  Animal *a7 = creer_animal(9,22, energie);
  Animal *a8 = creer_animal(17,3, energie);
  
  a5->suivant=a6;
  a6->suivant=a7;
  a7->suivant=a8;

  liste_Predateur=a5;
  

  afficher_ecosys(liste_Proie,liste_Predateur);  
  ecrire_ecosys("pptestPreProcess.txt", liste_Predateur, liste_Proie);

  /* Creation de tableau */
  int monde[SIZE_X][SIZE_Y];
  for (unsigned i=0; i<SIZE_X;++i) {
    for (unsigned j=0; j<SIZE_Y; ++j) 
      monde[i][j] = rand() % 100;
  }

  /* Bouger + Reproduce */
  bouger_animaux(liste_Predateur);
  bouger_animaux(liste_Proie);

  reproduce(&liste_Predateur, p_reproduce_predateur);
  reproduce(&liste_Proie, p_reproduce_proie);

  ecrire_ecosys("pptestAlterProcess.txt", liste_Predateur, liste_Proie);
  afficher_ecosys(liste_Proie, liste_Predateur);

  /* Rafraichissement */
  rafraichir_predateurs(&liste_Predateur, &liste_Proie);
  rafraichir_proies(&liste_Proie, monde);
  rafraichir_monde(monde);

  ecrire_ecosys("pptestRafr.txt", liste_Predateur, liste_Proie);
  afficher_ecosys(liste_Proie, liste_Predateur);




  /* D'AUTRES JEU DE TESTS */
  Animal *liste_proie = creer_animal(4, 5, 20);
  Animal *liste_pred = creer_animal(4, 5, 20);
  afficher_ecosys(liste_proie, liste_pred);
  for (int i=0;i<200;i++) {
    if (compte_animal_it(liste_pred)>4000 || compte_animal_it(liste_proie) > 4000 || compte_animal_it(liste_proie)==0) 
      break;
    printf("TOUR NO.%d\n",i);
    rafraichir_proies(&liste_proie, monde);
    rafraichir_predateurs(&liste_pred, &liste_proie);
    rafraichir_monde(monde);
    afficher_ecosys(liste_proie, liste_pred);
  }
  
}