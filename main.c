#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#define MAX_SOMMETS 4

struct Noeud {
    int valeur;
    struct Noeud* gauche;
    struct Noeud* droite;
};

struct Noeud* creerNoeud(int val) {
    struct Noeud* nouveau = (struct Noeud*)malloc(sizeof(struct Noeud));
    nouveau->valeur = val;
    nouveau->gauche = NULL;
    nouveau->droite = NULL;
    return nouveau;
}

void initialiserMatrice(int matrice[MAX_SOMMETS][MAX_SOMMETS]) {
    for (int i = 0; i < MAX_SOMMETS; i++) {
        for (int j = 0; j < MAX_SOMMETS; j++) {
            matrice[i][j] = 0;
        }
    }
}

void ajouterArrete(int matrice[MAX_SOMMETS][MAX_SOMMETS], int i, int j) {
    matrice[i][j] = 1;
    matrice[j][i] = 1;
}

void afficherMatrice(int matrice[MAX_SOMMETS][MAX_SOMMETS]) {
    printf("Matrice d'adjacence :\n");
    for (int i = 0; i < MAX_SOMMETS; i++) {
        for (int j = 0; j < MAX_SOMMETS; j++) {
            printf("%d ", matrice[i][j]);
        }
        printf("\n");
    }
}

void prefixe(struct Noeud* racine) {
    if (racine != NULL) {
        printf("%d ", racine->valeur);
        prefixe(racine->gauche);
        prefixe(racine->droite);
    }
}

void infixe(struct Noeud* racine) {
    if (racine != NULL) {
        infixe(racine->gauche);
        printf("%d ", racine->valeur);
        infixe(racine->droite);
    }
}

void postfixe(struct Noeud* racine) {
    if (racine != NULL) {
        postfixe(racine->gauche);
        postfixe(racine->droite);
        printf("%d ", racine->valeur);
    }
}

void BFS(int matrice[MAX_SOMMETS][MAX_SOMMETS], int sommetDepart) {
    int visite[MAX_SOMMETS] = { 0 };
    int file[MAX_SOMMETS];
    int tete = 0, queue = 0;

    visite[sommetDepart] = 1;
    file[queue++] = sommetDepart;
    printf("Parcours BFS a partir du sommet %d : ", sommetDepart);
    while (tete < queue) {
        int sommetActuel = file[tete++];
        printf("%d ", sommetActuel);

        for (int i = 0; i < MAX_SOMMETS; i++) {
            if (matrice[sommetActuel][i] == 1 && !visite[i]) {
                file[queue++] = i;
                visite[i] = 1;
            }
        }
    }
    printf("\n");
}

void DFS(int matrice[MAX_SOMMETS][MAX_SOMMETS], int sommet, int visite[MAX_SOMMETS]) {
    printf("%d ", sommet);
    visite[sommet] = 1;

    for (int i = 0; i < MAX_SOMMETS; i++) {
        if (matrice[sommet][i] == 1 && !visite[i]) {
            DFS(matrice, i, visite);
        }
    }
}

int main() {
    int Graphe[MAX_SOMMETS][MAX_SOMMETS];
    int visiteDFS[MAX_SOMMETS] = { 0 };

    initialiserMatrice(Graphe);
    ajouterArrete(Graphe, 0, 1);
    ajouterArrete(Graphe, 0, 3);
    ajouterArrete(Graphe, 1, 2);
    ajouterArrete(Graphe, 1, 3);

    afficherMatrice(Graphe);
    BFS(Graphe, 0);

    printf("Parcours DFS a partir du sommet 0 : ");
    DFS(Graphe, 0, visiteDFS);
    printf("\n\n-----------------------------\n\n");

    struct Noeud* racine = creerNoeud(1);
    racine->gauche = creerNoeud(2);
    racine->droite = creerNoeud(3);
    racine->gauche->gauche = creerNoeud(4);
    racine->gauche->droite = creerNoeud(5);

    printf("Parcours ARBRE :\n");
    printf("Prefixe : "); prefixe(racine); printf("\n");
    printf("Infixe  : "); infixe(racine);  printf("\n");
    printf("Postfixe: "); postfixe(racine); printf("\n");

    return 0;
}