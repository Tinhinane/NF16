#ifndef TP3_H_INCLUDED
#define TP3_H_INCLUDED

#include <stdio.h>
#include <stdlib.h>
#define NB 15

/* Produit */

typedef struct Produit T_Produit;

struct Produit {
    char marque [NB];
    float prix;
    char qualite;
    int quantite_en_stock;
    T_Produit* suivant;
};

/* Rayon */

typedef struct Rayon T_Rayon;

struct Rayon {
    char nom_rayon [NB];
    int nombre_produits;
    T_Produit* premier;
    T_Rayon* suivant;
};

/* Magasin */

typedef struct Magasin T_Magasin;

struct Magasin {
    char nom [NB];
    T_Rayon* premier;
};

/* Fonctions de creation */

T_Produit *creerProduit(char *marque, float prix, char qualite, int quantite);
T_Rayon *creerRayon(char *nom);
T_Magasin *creerMagasin(char *nom);

/* Fonctions d'ajout */

int ajouterProduit(T_Rayon *rayon, T_Produit *produit);
int ajouterRayon(T_Magasin *magasin, T_Rayon *rayon);

/* Fonctions d'affichage */

void afficherMagasin(T_Magasin *magasin);
void afficherRayon(T_Rayon *rayon, T_Magasin* magasin);

/* Fonctions de gestion */

int retirerProduit(T_Rayon *rayon, char* nom_produit);
void supprimerRayon(T_Magasin *magasin, char *nom_rayon);
void rechercheProduits(T_Magasin *magasin, float prix_min, float prix_max);
void traiterListeAchat(T_Magasin *magasin);

/* Fonctions complementaires */

void viderBuffer();
T_Produit* copierProduit(T_Produit* p);
T_Rayon* existeRayon (T_Magasin* magasin, char* nomRayon);
T_Rayon* existeProduit (T_Magasin* magasin, char* nomProduit);
char* rayonProduit (T_Magasin* magasin, T_Produit* produit);
T_Produit* existeProduitDansRayon (T_Rayon* rayon, char* nomProduit);
void afficherListeAchat (T_Rayon* produits_dispo, T_Rayon* produits_indispo);
#endif // TP3_H_INCLUDED
