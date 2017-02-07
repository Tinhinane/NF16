#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "tp3.h"

int main()
{

    T_Magasin* mag_base = creerMagasin("Marche Marchons");

    T_Rayon* r1 = creerRayon("Fruits");
    T_Rayon* r2 = creerRayon("Hygiene");
    T_Rayon* r3 = creerRayon("Boissons");
    T_Rayon* r4 = creerRayon("Boucherie");
    T_Rayon* r5 = creerRayon("Laitiers");

    ajouterRayon(mag_base, r1);
    ajouterRayon(mag_base, r2);
    ajouterRayon(mag_base, r3);
    ajouterRayon(mag_base, r4);
    ajouterRayon(mag_base, r5);

    T_Produit* p1 = creerProduit("Papaye", 2.43, 'A', 13);
    T_Produit* p2 = creerProduit("Bannane", 3.56, 'B', 150);
    T_Produit* p3 = creerProduit("Orange", 0.90, 'B', 300);
    T_Produit* p4 = creerProduit("Avocat", 1.45, 'C', 20);
    T_Produit* p5 = creerProduit("Savon Auchan", 1.34, 'C', 100);
    T_Produit* p6 = creerProduit("Listerine", 3.45, 'A', 40);
    T_Produit* p7 = creerProduit("Williams", 2.67, 'B', 18);
    T_Produit* p8 = creerProduit("Teraxyl", 2.13, 'C', 20);
    T_Produit* p9 = creerProduit("Pure Life", 3.87, 'A', 34);
    T_Produit* p10 = creerProduit("Sprite", 1.09, 'B', 43);
    T_Produit* p11 = creerProduit("Sirop Auchan", 0.67, 'A', 23);
    T_Produit* p12 = creerProduit("Coca-Cola", 1.87, 'A', 79);
    T_Produit* p13 = creerProduit("Boeuf", 3.54, 'A', 10);
    T_Produit* p14 = creerProduit("Boudin blanc", 4.65, 'C', 3);
    T_Produit* p15 = creerProduit("Saucisses", 5.34, 'A', 16);
    T_Produit* p16 = creerProduit("Rillettes", 2.87, 'B', 76);
    T_Produit* p17 = creerProduit("Beurre", 2.73, 'A', 56);
    T_Produit* p18 = creerProduit("Danio", 1.25, 'B', 47);
    T_Produit* p19 = creerProduit("Gouda Auchan", 1.41, 'C', 3);
    T_Produit* p20 = creerProduit("Lait Nestle", 0.76, 'A', 65);

    ajouterProduit(r1, p1);
    ajouterProduit(r1, p2);
    ajouterProduit(r1, p3);
    ajouterProduit(r1, p4);
    ajouterProduit(r2, p5);
    ajouterProduit(r2, p6);
    ajouterProduit(r2, p7);
    ajouterProduit(r2, p8);
    ajouterProduit(r3, p9);
    ajouterProduit(r3, p10);
    ajouterProduit(r3, p11);
    ajouterProduit(r3, p12);
    ajouterProduit(r4, p13);
    ajouterProduit(r4, p14);
    ajouterProduit(r4, p15);
    ajouterProduit(r4, p16);
    ajouterProduit(r5, p17);
    ajouterProduit(r5, p18);
    ajouterProduit(r5, p19);
    ajouterProduit(r5, p20);


    int option;
    printf("Menu\n1. Creer un magasin\n2. Ajouter un rayon au magasin\n3. Ajouter un produit dans un rayon\n4. Afficher les rayons du magasin\n5. Afficher les produits d'un rayon\n6. Retirer un produit\n7. Supprimer un rayon\n8. Rechercher un produit par prix\n9. Liste d'achat\n10. Quitter");
    do {
        float minimum, maximum, prix_produit;
        char nom_mag[NB], qualite_produit;
        int quantite_produit;
        printf("\nOption : ");
        scanf("%d",&option);
        switch (option) {

            case 1:

                printf("\nDonnez un nom pour le magasin (%d lettres): ",NB);
                viderBuffer();
                fgets(nom_mag, NB, stdin); // Permet d'ajouter un jeu dont le nom comporte des espaces
                nom_mag[strlen(nom_mag)-1] = '\0'; // …crase le '\n' capture par fgets() avec le caractere de fin de chaine
                T_Magasin* mag = creerMagasin(nom_mag);
                if (mag != NULL) printf("\nCreation du magasin %s reussie !\n",nom_mag);
                else printf("\nErreur !\n");
                break;

            case 2:

                printf("\nDonnez un nom pour le rayon (%d lettres): ",NB);
                char* nom_rayon = (char*)malloc(NB*sizeof(char));
                viderBuffer();
                fgets(nom_rayon, NB, stdin);
                nom_rayon[strlen(nom_rayon)-1] = '\0';
                T_Rayon* ray = creerRayon(nom_rayon);
                if (ajouterRayon(mag_base, ray) == 1) printf("Rayon bien ajoute\n");
                else printf("Erreur\n");
                break;

            case 3:

                printf("\nMarque du produit (%d lettres): ",NB);
                viderBuffer();
                char* marque_produit = (char*)malloc(NB*sizeof(char));
                fgets(marque_produit, NB, stdin);
                marque_produit[strlen(marque_produit)-1] = '\0';
                do {
                    printf("\nPrix : ");
                    scanf("%f", &prix_produit);
                } while (prix_produit < 0);
                //do {
                    printf("\nQualite (A, B ou C) : ");
                    viderBuffer();
                    qualite_produit = getchar();
                //} while (qualite_produit < 'A' && qualite_produit > 'C');
                do {
                    printf("\nQuantite : ");
                    scanf("%d", &quantite_produit);
                } while (quantite_produit < 0);
                T_Produit* pro = creerProduit(marque_produit, prix_produit, qualite_produit, quantite_produit);
                if (pro != NULL) {
                    printf("\nDans quel rayon voulez-vous ajouter ce produit ? ");
                    viderBuffer();
                    char* rayon_ajoute = (char*)malloc(NB*sizeof(char));
                    fgets(rayon_ajoute, NB, stdin);
                    rayon_ajoute[strlen(rayon_ajoute)-1] = '\0';
                    if (ajouterProduit(existeRayon(mag_base, rayon_ajoute), pro) == 1) printf("\nProduit bien ajoute");
                    else printf("\nLe produit n'a pas ete ajoute");
                }
                break;

            case 4:
                afficherMagasin(mag_base);
                break;

            case 5:

                printf("\nQuel rayon voulez-vous afficher ? ");
                viderBuffer();
                char* rayon_affiche = (char*)malloc(NB*sizeof(char));
                fgets(rayon_affiche, NB, stdin);
                rayon_affiche[strlen(rayon_affiche)-1] = '\0';
                afficherRayon(existeRayon(mag_base, rayon_affiche),mag_base);
                free(rayon_affiche);
                break;

            case 6:

                printf("\nQuel produit voulez-vous supprimer ? ");
                viderBuffer();
                char* produit_suppression = (char*)malloc(NB*sizeof(char));
                fgets(produit_suppression, NB, stdin);
                produit_suppression[strlen(produit_suppression)-1] = '\0';
                if (retirerProduit(existeProduit(mag_base, produit_suppression), produit_suppression) == 1) printf("Produit bien supprime\n");
                free(produit_suppression);
                break;

            case 7:

                printf("\nQuel rayon voulez-vous supprimer ? ");
                viderBuffer();
                char* rayon_suppression = (char*)malloc(NB*sizeof(char));
                fgets(rayon_suppression, NB, stdin);
                rayon_suppression[strlen(rayon_suppression)-1] = '\0';
                if (existeRayon(mag_base, rayon_suppression))
                {
                    supprimerRayon(mag_base, rayon_suppression);
                    printf("Rayon bien supprime\n");
                }
                else printf("Le rayon n'existe pas\n");
                free(rayon_suppression);
                break;

            case 8:

                printf("\nPrix minimum : ");
                viderBuffer();
                scanf("%f", &minimum);
                printf("\nPrix maximum : ");
                viderBuffer();
                scanf("%f", &maximum);
                rechercheProduits(mag_base, minimum, maximum);
                break;

            case 9:

                traiterListeAchat(mag_base);

            case 10:

                printf("\nAu revoir !\n");
                break;

            default:

                printf("\nCette option n'existe pas !\n");
                viderBuffer();
                break;
        }
    } while (option != 10);
    return 0;
}
