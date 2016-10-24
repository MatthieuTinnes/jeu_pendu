#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <stdbool.h>
#include <string.h>
#include "main.h"
#define TAILLEMOTDEFAUT 30
int main()
{
    char modeJeu;
    char play;
    char motSecret[TAILLEMOTDEFAUT];
    int tailleMotSecret,tailleMotEssai;
    do
    {
        printf("Bienvenue dans le jeu du pendu !\n");
        printf("------------------------------------------------\n");
        printf("Voulez vous jouer en mode solo ou 2 joueurs ? (1/2) \n");
        modeJeu = lireCaractere(modeJeu);
        if(modeJeu == '1')
            {
                if(modeSolo(motSecret,tailleMotSecret,tailleMotEssai) == EXIT_FAILURE)
                    return EXIT_FAILURE;
            }

        else if(modeJeu == '2')
            modeMulti(motSecret,tailleMotSecret,tailleMotEssai);
        else
            printf("Veuillez entrez 1 ou 2\n");


        printf("Voulez vous rejouer ? (O/N)\n");
        play = lireCaractere(play);
    } while(play == 'O');
    return 0;
}

int modeMulti(char motSecret[], int tailleMotSecret, int tailleMotEssai) //mode 2 joueurs sans dico
{
	printf("Entrez le mot secret : \n");
    lire(motSecret,TAILLEMOTDEFAUT);
    cacherMot();
    tailleMotSecret = strlen(motSecret);
    tailleMotEssai = tailleMotSecret;
    char motEssai[tailleMotEssai];
    initialiserMot(motEssai,tailleMotEssai);
    motMaj(motSecret,tailleMotSecret); //on met le mot secret en majuscule
    boucleEssai(motSecret,motEssai,tailleMotSecret);
    return 0;
}

int modeSolo(char motSecret[], int tailleMotSecret, int tailleMotEssai)
{
	FILE* dico = NULL;
	int caractereCourant,ligneRandom,i;
	int nbLignes = 0;
	dico = fopen("dico.txt", "r");
	if (dico != NULL)
	{
		do
		{
		    caractereCourant = fgetc(dico);
			if(caractereCourant == '\n')
				nbLignes++;

		}while(caractereCourant != EOF); //on compte le nb de lignes du fichier
		rewind(dico);
		ligneRandom = rand_a_b(0,nbLignes+1);
		for(i = 0; i != ligneRandom; i++)
		{
			fgets(motSecret, TAILLEMOTDEFAUT, dico); //selection d'un mot random dans le fichier
		}
	}
		else
		{
			printf("Erreur lors du l'ouverture du fichier dico.txt");
			return EXIT_FAILURE;
		}
	fclose(dico);
	supprEnter(motSecret);
	tailleMotSecret = strlen(motSecret);
    tailleMotEssai = tailleMotSecret;
	char motEssai[tailleMotEssai];
    initialiserMot(motEssai,tailleMotEssai);
    boucleEssai(motSecret,motEssai,tailleMotSecret);
}

int comparer(const char lettre,const char motSecret[], char motEssai[], const int tailleMotSecret)
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

int lire(char *chaine, const int longueur)
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

int boucleEssai(const char motSecret[], char motEssai[], const int tailleMotSecret)
{
    int i;
    int nbEssai = 10;
    char lettreEssai;
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
    return 1;
}

int rand_a_b(int a, int b)
{
    return rand()%(b-a) +a;
}

int supprEnter(char *chaine)
{
    char *positionEntree = NULL;

    positionEntree = strchr(chaine, '\n'); // On recherche l'"Entrée"
    if (positionEntree != NULL) // Si on a trouvé le retour à la ligne
    {
    	*positionEntree = '\0'; // On remplace ce caractère par \0
    }
    return 1; // On renvoie 1 si la fonction s'est déroulée sans erreur
}
