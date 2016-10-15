#ifndef MAIN_H_INCLUDED
#define MAIN_H_INCLUDED

char lireCaractere();
int comparer(char lettre, const char motSecret[], char motEssai[], const int tailleMotSecret);
int initialiserMot(char mot[], const int nbLettre);
void motMaj(char mot[], const int taillemot);
void cacherMot();
int lire(char *chaine, int longueur);

#endif // MAIN_H_INCLUDED
