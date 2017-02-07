#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "tp3.h"

//Fonction qui créé un produit

T_Produit *creerProduit(char *marque, float prix, char qualite, int quantite){
    T_Produit* new_produit = (T_Produit*)malloc(sizeof(T_Produit));
    if (new_produit == NULL) return NULL;
    strcpy(new_produit->marque, marque);
    new_produit->prix = prix;
    new_produit->qualite = qualite;
    new_produit->quantite_en_stock = quantite;
    new_produit->suivant = NULL;
    return new_produit;
}

//Fonction qui créé un rayon

T_Rayon *creerRayon(char *nom){
    T_Rayon* new_rayon = (T_Rayon*)malloc(sizeof(T_Rayon));
    if (new_rayon == NULL) return NULL;
    strcpy(new_rayon->nom_rayon, nom);
    new_rayon->nombre_produits = 0;
    new_rayon->premier = NULL;
    new_rayon->suivant = NULL;
    return new_rayon;
}

//Fonction qui créé un magasin

T_Magasin *creerMagasin(char *nom){
    T_Magasin* new_magasin = (T_Magasin*)malloc(sizeof(T_Magasin));
    if (new_magasin == NULL) return NULL;
    strcpy(new_magasin->nom, nom);
    new_magasin->premier = NULL;
    return new_magasin;
}

//Fonction qui ajoute un produit dans un rayon

int ajouterProduit(T_Rayon *rayon, T_Produit *produit){
    if(rayon == NULL || produit == NULL) return 0; // erreur
    T_Produit* produit_actuel = rayon->premier; // pointeur vers le premier element
    T_Produit* produit_precedent = NULL; // pointeur vers l'element precedent par rapport l'actuel (initailement à NULL)

    while (produit_actuel != NULL && strcmp(produit_actuel->marque, produit->marque) < 0)
    {
        /* on cherche la bonne position d'insertion ;
        parcours le rayon tant que la marque du produit actuel
        soit inferieur au nom du produit en parametre */

        produit_precedent = produit_actuel;
        produit_actuel = produit_actuel->suivant;
    }

    if (produit_actuel != NULL && strcmp(produit_actuel->marque, produit->marque) == 0)
    {
        /* dans ce cas, le produit est deja dans le rayon */
        return 0;
    }
    else // il n'est pas encore dans le rayon
    {
        if (produit_precedent == NULL) // ajout au debut du rayon
        {
            produit->suivant = rayon->premier; // le produit en parametre pointe vers le premier element
            rayon->premier = produit; // on pointe le debut du rayon vers le produit en parametre
            rayon->nombre_produits++; // on incremente le nombre de produits
            return 1; // le produit a ete bien ajoute
        }

        else if (produit_precedent != NULL) // ajout entre deux produits
        {
            produit->suivant = produit_precedent->suivant; // le produit en parametre pointe vers le suivant du precedent
            produit_precedent->suivant = produit; // le produit precedent pointe vers le produit qu'on ajoute
            rayon->nombre_produits++; // on incremente le nombre de produits
            return 1; // le produit a ete bien ajoute
        }

        else return 0; // le produit n'a pas ete bien ajoute
    }
}

//Fonction qui ajoute un rayon dans un magasin

int ajouterRayon(T_Magasin *magasin, T_Rayon *rayon){
    if(magasin == NULL || rayon == NULL) return 0; // erreur
    T_Rayon* rayon_actuel = magasin->premier; // pointeur vers le premier element
    T_Rayon* rayon_precedent = NULL; // pointeur vers l'element precedent par rapport l'actuel (initailement à NULL)

    while (rayon_actuel != NULL && strcmp(rayon_actuel->nom_rayon, rayon->nom_rayon) < 0)
    {
        /* on cherche la bonne position d'insertion ;
         parcours le magasin tant que le nom du rayon actuel
         soit inferieur au nom du rayon en parametre */

        rayon_precedent = rayon_actuel;
        rayon_actuel = rayon_actuel->suivant;
    }

    if (rayon_actuel != NULL && strcmp(rayon_actuel->nom_rayon, rayon->nom_rayon) == 0)
    {
        /* dans ce cas, le rayon est deja dans le magasin */
        printf("Le rayon existe deja dans le magasin\n");
        return 0;
    }
    else // il n'est pas encore dans le magasin
    {
        if (rayon_precedent == NULL) // ajout au debut du magasin
        {
            rayon->suivant = magasin->premier; // le rayon en parametre pointe vers le premier element
            magasin->premier = rayon; // on pointe le debut du magasin vers le rayon en parametre
            return 1; // le rayon a ete bien ajoute
        }

        else if (rayon_precedent != NULL) // ajout entre deux produits
        {
            rayon->suivant = rayon_precedent->suivant; // le rayon en parametre pointe vers le suivant du precedent (penser a faire l'actuel)
            rayon_precedent->suivant = rayon; // le rayon precedent pointe vers le rayon qu'on ajoute
            return 1; // le rayon a ete bien ajoute
        }

        else return 0; // le rayon n'a pas ete bien ajoute
    }
}

//Fonction qui affiche le rayons d'un magasin

void afficherMagasin(T_Magasin *magasin)
{
    int i;
    if (magasin == NULL) printf("Erreur : le magasin n'existe pas\n");
    printf("%s\n",magasin->nom);
    for (i = 0; i < NB+23; i++)
    {
        printf("-");
    }
    printf("\n");
    printf("|Nom");
    for (i = 0; i < NB - 3; i++)
    {
        printf(" ");
    }
    printf("| Nombre de produits |\n");
    for (i = 0; i < NB + 23; i++) {
        printf("-");
    }
    printf("\n");
    T_Rayon* iterateur_rayon = magasin->premier;
    while (iterateur_rayon != NULL)
    {
        printf("|%s",iterateur_rayon->nom_rayon);
        for (i = 0; i < (NB - strlen(iterateur_rayon->nom_rayon)); i++)
        {
            printf(" ");
        }
        printf("| %d",iterateur_rayon->nombre_produits);
        if (iterateur_rayon->nombre_produits >= 0 && iterateur_rayon->nombre_produits <= 9) {
            for (i = 0; i < 18; i++) {
                printf(" ");
            }
            printf("|");
        }
        else if (iterateur_rayon->nombre_produits >= 10 && iterateur_rayon->nombre_produits <= 99) {
            for (i = 0; i < 17; i++) {
                printf(" ");
            }
            printf("|");
        }
        else if (iterateur_rayon->nombre_produits >= 100 && iterateur_rayon->nombre_produits <= 999) {
            for (i = 0; i < 16; i++) {
                printf(" ");
            }
            printf("|");
        }
        else if (iterateur_rayon->nombre_produits >= 1000 && iterateur_rayon->nombre_produits <= 9999) {
            for (i = 0; i < 15; i++) {
                printf(" ");
            }
            printf("|");
        }
        printf("\n");
        for (i = 0; i < NB + 23; i++) {
            printf("-");
        }
        printf("\n");
        iterateur_rayon = iterateur_rayon->suivant;
    }
}

//Fonction qui affiche les produits d'un rayon

void afficherRayon(T_Rayon *rayon, T_Magasin* magasin)
{
    int i;
    if (rayon == NULL) printf("Erreur (affichage impossible) : le rayon n'existe pas\n");
    if (rayon != NULL && rayon->nombre_produits == 0) printf("Erreur (affichage impossible) : le rayon est vide\n");
    else if (rayon != NULL && rayon->nombre_produits != 0)
    {
        for (i = 0; i < 2*NB+42; i++)
        {
            printf("-");
        }
        printf("\n");
        printf("|Marque");
        for (i = 0; i < NB-6; i++)
        {
            printf(" ");
        }
        printf("| Prix  | Qualite  | Quantite en stock | Rayon");
        for (i = 0; i < NB-6; i++)
        {
            printf(" ");
        }
        printf("|\n");
        for (i = 0; i < 2*NB+42; i++)
        {
            printf("-");
        }
        printf("\n");
        T_Produit* iterateur_produit = rayon->premier;
        while (iterateur_produit != NULL)
        {
            printf("|%s",iterateur_produit->marque);
            for (i = 0; i < (NB - (strlen(iterateur_produit->marque))); i++)
            {
                printf(" ");
            }
            printf("| %.2f",iterateur_produit->prix);
            if (iterateur_produit->prix >= 0.01 && iterateur_produit->prix <= 9.99) {
                for (i = 0; i < 2; i++) printf(" ");
            }
            if (iterateur_produit->prix >= 10.00 && iterateur_produit->prix <= 99.99) {
                for (i = 0; i < 1; i++) printf(" ");
            }
            if (iterateur_produit->prix >= 100.00 && iterateur_produit->prix <= 999.99) {
                printf(" ");
            }
            printf("| %c        ",iterateur_produit->qualite);
            printf("| %d",iterateur_produit->quantite_en_stock);
            if (iterateur_produit->quantite_en_stock >= 0 && iterateur_produit->quantite_en_stock <= 9) {
                for (i = 0; i < 17; i++) {
                    printf(" ");
                }
            }
            else if (iterateur_produit->quantite_en_stock >= 10 && iterateur_produit->quantite_en_stock <= 99) {
                for (i = 0; i < 16; i++) {
                    printf(" ");
                }
            }
            else if (iterateur_produit->quantite_en_stock >= 100 && iterateur_produit->quantite_en_stock <= 999) {
                for (i = 0; i < 15; i++) {
                    printf(" ");
                }
            }
            printf("| %s",rayonProduit(magasin, iterateur_produit));
            for (i = 0; i < (NB - (strlen(rayonProduit(magasin, iterateur_produit))))-1; i++) {
                printf(" ");
            }
            printf("|");
            printf("\n");
            for (i = 0; i < 2*NB+42; i++)
            {
                printf("-");
            }
            printf("\n");
            iterateur_produit = iterateur_produit->suivant;
        }
    }

}

//Fonction qui retire un produit d'un rayon

int retirerProduit(T_Rayon *rayon, char* nom_produit)
{
    if (rayon == NULL) // verification de l'existence du rayon
    {
        printf("Erreur : aucun rayon ne contient ce produit\n");
        return 0;
    }
    if (rayon->nombre_produits == 0) // si le rayon est vide
    {
        printf("Erreur : le rayon est vide\n");
        return 0;
    }
    if (rayon->nombre_produits >= 1)
        // s'il y plus qu'un produit
    {
        T_Produit* produit_actuel = rayon->premier;
        T_Produit* produit_precedent = NULL;
        while (strcmp(produit_actuel->marque, nom_produit) != 0)
            // tant qu'on ne trouve pas le produit passe en parametre
        {
            produit_precedent = produit_actuel;
            produit_actuel = produit_actuel->suivant;
        }
        if (produit_actuel == NULL && produit_precedent != NULL)
            // on est a la fin de la liste
        {
            printf("Erreur : le produit n'est pas dans ce rayon\n");
            return 0;
        }
        if (produit_precedent == NULL)
            // le produit est le premier du rayon
        {
            rayon->premier = produit_actuel->suivant; // maintenant, le premier est le suivant de l'actuel
            rayon->nombre_produits--;
            free(produit_actuel);
            return 1;
        }
        else
            // on est entre deux produits
        {
            produit_precedent->suivant = produit_actuel->suivant; // le precedent pointe vers le suivant de l'actuel
            rayon->nombre_produits--;
            free(produit_actuel);
            return 1;
        }
    }
    return 1;
}

//Fonction qui supprime un rayon

void supprimerRayon(T_Magasin *magasin, char *nom_rayon)
{
    if (magasin == NULL) printf("Erreur : le magasin n'existe pas\n");
    T_Rayon* rayon_actuel = magasin->premier;
    T_Rayon* rayon_precedent = NULL;
    while (rayon_actuel != NULL && strcmp(rayon_actuel->nom_rayon, nom_rayon) != 0)
        // tant qu'on ne trouve pas le rayon passe en parametre
    {
        rayon_precedent = rayon_actuel;
        rayon_actuel = rayon_actuel->suivant;
    }
    if (rayon_actuel == NULL)
        // on n'a pas trouve le rayon
    {
        printf("Erreur : le rayon n'existe pas dans le magasin\n");
    }
    else
        // on a trouve le rayon
    {
        if (rayon_precedent == NULL) // on est au debut de la liste de rayons
        {
            magasin->premier = rayon_actuel->suivant;
        }
        else rayon_precedent->suivant = rayon_actuel->suivant; // le rayon precedent pointe vers le suivant de l'actuel

        T_Produit* iterateur_produit = rayon_actuel->premier;
        T_Produit* tmp = NULL;
        while (iterateur_produit != NULL)
            // on va jusqu'a la fin de la liste de produits
        {
            tmp = iterateur_produit->suivant; // on stocke la reference de l'element suivant
            retirerProduit(rayon_actuel, iterateur_produit->marque); // supprime l'element actuel
            iterateur_produit = tmp; // on continue avec le suivant
        }
        free(rayon_actuel); // on supprime l'actuel
    }
}

//Recherche des produits se situant dans une fourchette de prix entrée par l'utilisateur

void rechercheProduits(T_Magasin *magasin, float prix_min, float prix_max)
{
    if (magasin == NULL) printf("Erreur : le magasin n'existe pas\n");
    else if (prix_max < 0 || prix_min < 0) printf("Erreur : prix négatif\n");
    T_Rayon* rayon_prix = creerRayon("Rayon de la fourchette de prix"); // creation d'un rayon pour stocker les produit dans la foutchette de prix
    if (rayon_prix == NULL) printf("Erreur dans la creation du rayon\n");
    ajouterRayon(magasin, rayon_prix);
    T_Rayon* iterateur_rayon = magasin->premier; // on pointe un iterateur de rayons vers le debut du magasin
    while (iterateur_rayon != NULL)
        // tant qu'on n'arrive pas a la fin du magasin
    {
        T_Produit* iterateur_produit = iterateur_rayon->premier; // on pointe un iterateur de produits vers le debut du rayon
        while (iterateur_produit != NULL)
            // tant qu'on n'est pas a la fin du rayon
        {
            if (iterateur_produit->prix >= prix_min && iterateur_produit->prix <= prix_max)
                // si le prix est bien dans la fourchette
            {
                ajouterProduit(rayon_prix, copierProduit(iterateur_produit)); // on ajoute une copie du produit dans le rayon de prix
            }
            iterateur_produit = iterateur_produit->suivant;
        }
        iterateur_rayon = iterateur_rayon->suivant;
    }
    if (rayon_prix->nombre_produits == 0) printf("Aucun resultat trouve pour cette fourchette de prix...\n");
    else if (rayon_prix->nombre_produits != 0) afficherRayon(rayon_prix, magasin);
    supprimerRayon(magasin, rayon_prix->nom_rayon);
}

/*  L'utilisateur saisit une liste de produits à acheter (rayon, marque, quantité). Ces produits seront retirés des différents rayons en mettant à jour tous les champs nécessaires. On affichera à la fin le prix total des produits achetés et la liste des produits qui ne sont pas disponibles (nombre de produits demandés dépasse la quantité présente en stock).
*/

void traiterListeAchat(T_Magasin *magasin)
{
    T_Rayon* rayonDisponible = creerRayon("Produits disponibles"); // liste qui stocke les produits dispnibles
    T_Rayon* rayonIndisponible = creerRayon("Produits indisponibles"); // liste qui stocke les produits indisponibles
    int answer = 1, quantite = 0;
    char marque_produit[NB]; // variable qui recoit les noms des produits
    char nom_rayon[NB]; // variable qui recoit les noms des rayons
    printf("\nListe d'achat");
    do {
        // Saisie du rayon
        printf("\nRayon : ");
        viderBuffer();
        fgets(nom_rayon, NB, stdin);
        nom_rayon[strlen(nom_rayon)-1] = '\0';

        if (existeRayon(magasin, nom_rayon) != NULL)
            // si le rayon sisie existe dans le magasin
        {
            // Saisie du produit
            viderBuffer();
            printf("Marque du produit : ");
            fgets(marque_produit, NB, stdin);
            marque_produit[strlen(marque_produit)-1] = '\0';

            if (existeProduit(magasin, marque_produit) != NULL)
                // si le produit saisie est dans le rayon saisie
            {
                // Saisie de la quantite
                viderBuffer();
                printf("Quantite : ");
                scanf("%d",&quantite);

                if (quantite <= existeProduitDansRayon(existeRayon(magasin, nom_rayon), marque_produit)->quantite_en_stock)
                    // si la quantite saisie est inferieure ou egale a la quantite en stock
                {
                    // on cree un copie du produit
                    T_Produit* produit_copie = copierProduit(existeProduitDansRayon(existeRayon(magasin, nom_rayon), marque_produit));
                    // on stocke dans la variable 'quantite_en_stock' la quantite saisie afin de l'afficher a la fin
                    produit_copie->quantite_en_stock = quantite;
                    // on ajoute la copie dans le rayon de produits disponibles
                    ajouterProduit(rayonDisponible, produit_copie);
                    // on met a jour la quantite en stock du produit demande
                    existeProduitDansRayon(existeRayon(magasin, nom_rayon), marque_produit)->quantite_en_stock -= quantite;
                }
                else
                    //si la quantite saisie depasse la quantite en stock (on suppose que le client ne doit acheter que la quantite demande)
                {
                    printf("\nQuantite indisponible\n");
                    // on ajoute une copie du produit dans le rayon de produits insiponibles
                    ajouterProduit(rayonIndisponible, copierProduit(existeProduitDansRayon(existeRayon(magasin, nom_rayon), marque_produit)));
                }
            }
            else
            {
                printf("\nProduit indisponible\n");
                ajouterProduit(rayonIndisponible, creerProduit(marque_produit, 0, ' ', 0)); // on cree un element avec la marque saisie et on l'ajoute dans le rayon de produits indisponible
            }
        }
        else printf("\nCe rayon n'existe pas"); // si le rayon saisie n'est pas dans le magasin
        printf("\nVoulez-vous ajouter un autre produit dans votre liste ? 1 pour oui, 0 sinon ");
        scanf("%d",&answer);
    } while (answer != 0);
    afficherListeAchat(rayonDisponible, rayonIndisponible);
}

//Fonction qui vide le buffer

void viderBuffer()
{
    char c;
    while((c=getchar()) != '\n');
}

//Fonction qui recoit un produit et retourne un nouveau produit copie

T_Produit* copierProduit(T_Produit* p)
{
    if (p == NULL) return NULL;
    T_Produit* nv_produit = creerProduit(p->marque, p->prix, p->qualite, p->quantite_en_stock);
    return nv_produit;
}

//Fonction qui recoit un magasin et le nom d'un rayon et retour ce rayon s'il existe

T_Rayon* existeRayon (T_Magasin* magasin, char* nomRayon)
{
    if (magasin == NULL)
    {
        printf("Erreur : le magasin n'existe pas\n");
        return NULL;
    }
    T_Rayon* iterateur_rayon = magasin->premier;
    while (iterateur_rayon != NULL && strcmp(iterateur_rayon->nom_rayon, nomRayon) != 0)
    {
        iterateur_rayon = iterateur_rayon->suivant;
    }
    return iterateur_rayon;
}

//Fontion qui recoit un magasin et le nom d'un produit et retourne le rayon dans lequel ce derniere se trouve

T_Rayon* existeProduit (T_Magasin* magasin, char* nomProduit)
{
    if (magasin == NULL)
    {
        printf("Erreur : le magasin n'existe pas\n");
        return NULL;
    }
    int flag = 0;
    T_Rayon* iterateur_rayon = magasin->premier;
    while (iterateur_rayon != NULL && flag != 1)
    {
        if (existeProduitDansRayon(iterateur_rayon, nomProduit) != NULL) flag = 1;
        if (flag != 1) iterateur_rayon = iterateur_rayon->suivant;
    }
    return iterateur_rayon;
}

//Fonction qui recoit en parametre un magasin et un produit et retourne le nom du rayon du produit

char* rayonProduit (T_Magasin* magasin, T_Produit* produit)
{
    return existeProduit(magasin, produit->marque)->nom_rayon;
}

//Fonction qui recoit en parametre un magasin, un rayon et le nom d'un produit et retourne un produit s'il est dans le rayon indique

T_Produit* existeProduitDansRayon (T_Rayon* rayon, char* nomProduit)
{
    if (rayon == NULL)
    {
        printf("\nLe rayon n'existe pas");
        return NULL;
    }
    T_Produit* iterateur_produit = rayon->premier;
    while (iterateur_produit != NULL && strcmp(iterateur_produit->marque, nomProduit) != 0)
    {
        iterateur_produit = iterateur_produit->suivant;
    }
    return iterateur_produit;
}

void afficherListeAchat (T_Rayon* produits_dispo, T_Rayon* produits_indispo)
{
    int i;
    float prix_total = 0;
    printf("\nListe d'achats\n");
    for (i = 0; i < NB+38; i++) printf("*");
    if (produits_dispo == NULL || produits_dispo->nombre_produits == 0)
    {
        printf("\n\nIl n'y a pas de produits disponibles\n");
        for (i = 0; i < NB+38; i++) printf("*");
    }
    else if (produits_dispo != NULL && produits_indispo != NULL && produits_dispo->nombre_produits != 0)
    {
        T_Produit* iterateur_produit = produits_dispo->premier;
        printf("\nProduit");
        for (i = 0; i < NB-7; i++) printf(" ");
        printf("Quantite    Prix unitaire   Prix total    \n\n");
        while (iterateur_produit != NULL)
        {
            printf("%s",iterateur_produit->marque);
            for (i = 0; i < NB - (strlen(iterateur_produit->marque)); i++) printf(" ");

            if (iterateur_produit->quantite_en_stock >= 0 && iterateur_produit->quantite_en_stock <= 9)
                for (i = 0; i < 7; i++) printf(" ");
            else if (iterateur_produit->quantite_en_stock >= 10 && iterateur_produit->quantite_en_stock <= 99)
                for (i = 0; i < 6; i++) printf(" ");
            else if (iterateur_produit->quantite_en_stock >= 100 && iterateur_produit->quantite_en_stock <= 999)
                for (i = 0; i < 5; i++) printf(" ");
            printf("%d",iterateur_produit->quantite_en_stock);

            if (iterateur_produit->prix >= 0.01 && iterateur_produit->prix <= 9.99)
                for (i = 0; i < 13; i++) printf(" ");
            if (iterateur_produit->prix >= 10.00 && iterateur_produit->prix <= 99.99)
                for (i = 0; i < 12; i++) printf(" ");
            if (iterateur_produit->prix >= 100.00 && iterateur_produit->prix <= 999.99)
                for (i = 0; i < 11; i++) printf(" ");
            printf("%.2f",iterateur_produit->prix);

            float res = iterateur_produit->prix*iterateur_produit->quantite_en_stock;
            if (res >= 0.01 && res <= 9.99)
                for (i = 0; i < 9; i++) printf(" ");
            if (res >= 10.00 && res <= 99.99)
                for (i = 0; i < 8; i++) printf(" ");
            if (res >= 100.00 && res <= 999.99)
                for (i = 0; i < 7; i++) printf(" ");
            printf("%.2f\n",res);
            prix_total += iterateur_produit->prix*iterateur_produit->quantite_en_stock;
            iterateur_produit = iterateur_produit->suivant;
        }
        for (i = 0; i < NB+21; i++) printf(" ");
        printf("\nTOTAL");
        if (prix_total >= 0.01 && prix_total <= 9.99)
            for (i = 0; i < NB+29; i++) printf(" ");
        if (prix_total >= 10.00 && prix_total <= 99.99)
            for (i = 0; i < NB+28; i++) printf(" ");
        if (prix_total >= 100.00 && prix_total <= 999.99)
            for (i = 0; i < NB+27; i++) printf(" ");
        printf("%.2f\n\n",prix_total);
        for (i = 0; i < NB+38; i++) printf("*");
        if (produits_indispo->nombre_produits != 0)
        {
            printf("\nProduits indisponibles\n");
            iterateur_produit = produits_indispo->premier;
            while (iterateur_produit != NULL)
            {
                printf("\n%s",iterateur_produit->marque);
                iterateur_produit = iterateur_produit->suivant;
            }
            printf("\n");
            for (i = 0; i < NB+38; i++) printf("*");
        }
    }
}



