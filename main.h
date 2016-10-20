#ifndef MAIN_H_INCLUDED
#define MAIN_H_INCLUDED

char lireCaractere();
int comparer(const char lettre, const char motSecret[], char motEssai[], const int tailleMotSecret);
int initialiserMot(char mot[], const int nbLettre);
void motMaj(char mot[], const int taillemot);
void cacherMot();
int lire(char *chaine, int longueur);
int modeMulti(char motSecret[], int tailleMotSecret, int tailleMotEssai);
int modeSolo(char motSecret[], int tailleMotSecret, int tailleMotEssai);
int rand_a_b(int a, int b);
int supprEnter(char *chaine);
#endif // MAIN_H_INCLUDED
