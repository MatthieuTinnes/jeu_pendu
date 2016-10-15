#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <stdbool.h>
#include <string.h>
#include "main.h"
#define TAILLEMOTDEFAUT 30
int main()
{
    char motSecret[TAILLEMOTDEFAUT];
    int nbEssai = 10;
    int tailleMotSecret,tailleMotEssai;
    char lettreEssai;
    printf("Bienvenue dans le jeu du pendu !\n");
    printf("------------------------------------------------\n");
    printf("Entrez le mot secret : \n");
    lire(motSecret,TAILLEMOTDEFAUT);
    cacherMot();
    tailleMotSecret = strlen(motSecret);
    tailleMotEssai = tailleMotSecret;
    char motEssai[tailleMotEssai];
    initialiserMot(motEssai,tailleMotEssai);
    motMaj(motSecret,tailleMotSecret); //on met le mot secret en majuscule
    
    int i;
    while(nbEssai>0) //boucle nb essai
        {
            printf("Vous avez encore %d essai !\n",nbEssai);
            printf("Quel est le mot secret ? %s \n", motEssai);
            lettreEssai = lireCaractere(lettreEssai);//On lit le caractere essai
            if(comparer(lettreEssai, motSecret, motEssai,tailleMotSecret) == 0)//On regarde si la lettre est dans le mot
                nbEssai--;
            if(strcmp(motEssai, motSecret) == 0)
            {
                printf("Le mot secret est %s \n",motSecret);
                printf("Bravo vous avez trouve le mot secret !\n");
                return 0;
            }
        }
    printf("Vous n'avez pas reussi a trouve le mot secret ... \nLa reponse etait : %s \n",motSecret);
    return 0;
}


int comparer(char lettre,const char motSecret[], char motEssai[], const int tailleMotSecret)
{
    int taille;
    int i;
    int succes = 0;
    for(i = 0; i < tailleMotSecret; i++) //on parcoure le mot essai
    {
        if(motSecret[i] == lettre)
        {
            motEssai[i] = lettre;
            succes++;
        }
    }
    if (succes == 0)
        return 0;
    else
        return 1;
}
int initialiserMot(char mot[], const int nbLettre)
{
    int i;
    for(i = 0; i < nbLettre; i++)
    {
        mot[i] = '*';
    }

    return 0;
}
char lireCaractere()
{
    char caractere = 0;
    caractere = getchar(); // On lit le premier caractère
    caractere = toupper(caractere); // On met la lettre en majuscule si elle ne l'est pas déjà
    // On lit les autres caractères mémorisés un à un jusqu'au \n (pour les effacer)
    while (getchar() != '\n') ;
    return caractere; // On retourne le premier caractère qu'on a lu
}
void motMaj(char mot[], const int taillemot)
{
    int i = 0;
    for(i = 0; i < taillemot; i++)
    {
        mot[i] = toupper(mot[i]);
    }
}

void cacherMot()//pour cacher le mot en affichant des espaces
{
    int compteurLignes;
    for (compteurLignes = 0; compteurLignes < 100; compteurLignes++) 
            {
                printf("\n");
            }
}

int lire(char *chaine, int longueur)
{
    char *positionEntree = NULL;
 
    // On lit le texte saisi au clavier
    if (fgets(chaine, longueur, stdin) != NULL)  // Pas d'erreur de saisie ?
    {
        positionEntree = strchr(chaine, '\n'); // On recherche l'"Entrée"
        if (positionEntree != NULL) // Si on a trouvé le retour à la ligne
        {
            *positionEntree = '\0'; // On remplace ce caractère par \0
        }
        return 1; // On renvoie 1 si la fonction s'est déroulée sans erreur
    }
    else
    {
        return 0; // On renvoie 0 s'il y a eu une erreur
    }
}