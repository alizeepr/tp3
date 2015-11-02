#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "tp3.h"

// O(1)
T_Livre *creerLivre (char *titre, char *auteur, char *edition) {
    T_Livre* livre = (T_Livre *) malloc(sizeof(T_Livre));

    if (livre == NULL) {
        return NULL;
    }

    livre->titre = titre;
    livre->auteur = auteur;
    livre->edition = edition;
    livre->disponible = 1;

    return livre;
}

// O(1)
T_Rayon *creerRayon (char *theme) {
    T_Rayon* rayon = (T_Rayon *) malloc(sizeof(T_Rayon));

    if (rayon == NULL) {
        return NULL;
    }

    rayon->theme_rayon = theme;
    rayon->nombre_livres = 0;

    return rayon;
}

// O(1)
T_Biblio *creerBiblio (char *nom) {
    T_Biblio* biblio = (T_Biblio *) malloc(sizeof(T_Biblio));

    if (biblio == NULL) {
        return NULL;
    }

    biblio->nom = nom;

    return biblio;
}

// Dans le meilleur des cas, soit on on ajoute le livre au début de la liste, soit on n'ajoute pas le livre => Omega(1)
// Dans le pire des cas, on ajoute le livre en dernière position => O(n)
int ajouterLivreListe(T_Livre *actuel, T_Livre *aAjouter) {
    // Si on est à la fin de la liste, on ajoute le livre en dernière positon
    if (actuel->suivant == NULL) {
        actuel->suivant = aAjouter;
        aAjouter->suivant = NULL;
        return 1;
    }

    int comparaison = strcmp(actuel->suivant->titre, aAjouter->titre);

    // Egaux => On ne peut pas ajouter ce livre
    if (comparaison == 0) {
        return 0;
    }

    // Le livre suivant doit être après le livre à ajouter
    if (comparaison > 0) {
        aAjouter->suivant = actuel->suivant;
        actuel->suivant = aAjouter;
        return 1;
    }

    return ajouterLivreListe(actuel->suivant, aAjouter);
}

// Dans le meilleur des cas, soit on on ajoute le livre au début de la liste, soit on n'ajoute pas le livre => Omega(1)
// Dans le pire des cas, on ajoute le livre en dernière position => O(n)
int ajouterLivre(T_Rayon *rayon, T_Livre *aAjouter) {
    int resultat = 0;

    if (rayon->premier == NULL) {
        rayon->premier = aAjouter;
        aAjouter->suivant = NULL;

        resultat = 1;
    }

    if (resultat == 0) {
        int comparaison = strcmp(rayon->premier->titre, aAjouter->titre);

        // Le livre suivant doit être après le livre à ajouter
        if (comparaison > 0) {
            aAjouter->suivant = rayon->premier;
            rayon->premier = aAjouter;

            rayon->nombre_livres++;

            resultat = 1;
        }
    }

    if (resultat == 0) {
        resultat = ajouterLivreListe(rayon->premier, aAjouter);
    }

    if (resultat == 1) {
        rayon->nombre_livres++;
    }

    return resultat;
}

// Dans le meilleur des cas, soit on on ajoute le rayon au début de la liste, soit on n'ajoute pas le rayon => Omega(1)
// Dans le pire des cas, on ajoute le rayon en dernière position => O(n)
int ajouterRayonListe(T_Rayon *actuel, T_Rayon *aAjouter) {
    // Si on est à la fin de la liste, on ajoute le rayon en dernière positon
    if (actuel->suivant == NULL) {
        actuel->suivant = aAjouter;
        aAjouter->suivant = NULL;
        return 1;
    }

    int comparaison = strcmp(actuel->suivant->theme_rayon, aAjouter->theme_rayon);

    // Egaux => On ne peut pas ajouter ce rayon
    if (comparaison == 0) {
        return 0;
    }

    // Le rayon suivant doit être après le rayon à ajouter
    if (comparaison > 0) {
        aAjouter->suivant = actuel->suivant;
        actuel->suivant = aAjouter;
        return 1;
    }

    return ajouterRayonListe(actuel->suivant, aAjouter);
}

// Dans le meilleur des cas, soit on on ajoute le rayon au début de la liste, soit on n'ajoute pas le rayon => Omega(1)
// Dans le pire des cas, on ajoute le rayon en dernière position => O(n)
int ajouterRayon(T_Biblio *biblio, T_Rayon *aAjouter) {
    if (biblio->premier == NULL) {
        biblio->premier = aAjouter;
        aAjouter->suivant = NULL;
        return 1;
    }

    int comparaison = strcmp(biblio->premier->theme_rayon, aAjouter->theme_rayon);

    // Egaux => On ne peut pas ajouter ce rayon
    if (comparaison == 0) {
        return 0;
    }

    // Le livre suivant doit être après le rayon à ajouter
    if (comparaison > 0) {
        aAjouter->suivant = biblio->premier;
        biblio->premier = aAjouter;
        return 1;
    }

    return ajouterRayonListe(biblio->premier, aAjouter);
}

// O(n)
void afficherLivres(T_Livre *livre) {
    printf(
            "| %-40s | %-20s | %-15s | %-5s |\n",
            livre->titre,
            livre->auteur,
            livre->edition,
            livre->disponible ? "Oui" : "Non"
    );

    if (livre->suivant) {
        afficherLivres(livre->suivant);
    }
}

// O(n)
void afficherRayon(T_Rayon *rayon) {
    printf(
            " Rayon %s\n -------------------------------------------------------------------------------------------\n",
            rayon->theme_rayon
    );

    printf("| %-40s | %-20s | %-15s | %-5s |\n", "Titre", "Auteur", "Edition", "Dispo");
    printf("|-------------------------------------------------------------------------------------------|\n");
    afficherLivres(rayon->premier);
    printf(" -------------------------------------------------------------------------------------------\n");
}

// O(n)
void afficherRayons(T_Rayon *rayon) {
    printf("| %-40s | %-20d |\n", rayon->theme_rayon, rayon->nombre_livres);

    if (rayon->suivant) {
        afficherRayons(rayon->suivant);
    }
}

// O(n)
void afficherBiblio(T_Biblio *biblio) {
    printf(
            " Bibliotèque %s\n -----------------------------------------------------------------\n",
            biblio->nom
    );

    printf("| %-40s | %-20s |\n", "Nom", "Nombre de livres");
    printf("|-----------------------------------------------------------------|\n");
    afficherRayons(biblio->premier);
    printf(" -----------------------------------------------------------------\n");
}

// Dans le meilleur des cas O(1)
// Dans le pire des cas O(n)
int trouverEtEmprunterLivre(T_Livre *actuel, char* titreAEmprunter) {
    int comparaison = strcmp(actuel->titre, titreAEmprunter);

    // On a trouvé le livre
    if (comparaison == 0) {
        if (actuel->disponible == 1) {
            actuel->disponible = 0;
            return 1;
        }

        return 0;
    }

    // Les livres sont triés, on peut donc s'arrêter avant si on atteint des
    // livres après le celuirecherché
    if (comparaison > 0) {
        return 0;
    }

    // On a pas trouvé le livre et on a fini la liste
    if (! actuel->suivant) {
        return 0;
    }

    return trouverEtEmprunterLivre(actuel->suivant, titreAEmprunter);
}

// Dans le meilleur des cas O(1)
// Dans le pire des cas O(n)
int emprunterLivre(T_Rayon *rayon, char* titre) {
    if (! rayon->premier) {
        return 0;
    }

    return trouverEtEmprunterLivre(rayon->premier, titre);
}

// Dans le meilleur des cas O(1)
// Dans le pire des cas O(n)
int trouverEtSupprimerLivre(T_Livre *actuel, char* titreASupprimer) {
    if (! actuel->suivant) {
        return 0;
    }

    int comparaison = strcmp(actuel->suivant->titre, titreASupprimer);

    // On a trouvé le livre
    if (comparaison == 0) {
        struct Livre* aSupprimer = actuel->suivant;
        actuel->suivant = aSupprimer->suivant;
        free(aSupprimer);

        return 1;
    }

    // Les livres sont triés, on peut donc s'arrêter si on atteint un livre
    // après celui recherché
    if (comparaison > 0) {
        return 0;
    }

    return trouverEtSupprimerLivre(actuel->suivant, titreASupprimer);
}

// Dans le meilleur des cas O(1)
// Dans le pire des cas O(n)
int supprimerLivre(T_Rayon *rayon, char* titre) {
    if (! rayon->premier) {
        return 0;
    }

    int comparaison = strcmp(rayon->premier->titre, titre);

    // On a trouvé le livre
    if (comparaison == 0) {
        struct Livre* aSupprimer = rayon->premier;
        rayon->premier = aSupprimer->suivant;
        free(aSupprimer);

        return 1;
    }

    // Les livres sont triés, on peut donc s'arrêter si on atteint un livre
    // après celui recherché
    if (comparaison > 0) {
        return 0;
    }

    return trouverEtSupprimerLivre(rayon->premier, titre);
}

// O(n)
int supprimerLivresListe(T_Livre* actuel)
{
    if (actuel->suivant) {
        supprimerLivresListe(actuel->suivant);
    }

    free(actuel);
}

// Dans le meilleur des cas O(1)
// Dans le pire des cas O(n)
int trouverEtSupprimerRayon(T_Rayon *actuel, char* themeASupprimer) {
    if (! actuel->suivant) {
        return 0;
    }

    int comparaison = strcmp(actuel->suivant->theme_rayon, themeASupprimer);

    // On a trouvé le livre
    if (comparaison == 0) {
        struct Rayon* aSupprimer = actuel->suivant;
        actuel->suivant = aSupprimer->suivant;

        supprimerLivresListe(aSupprimer->premier);
        free(aSupprimer);

        return 1;
    }

    // Les livres sont triés, on peut donc s'arrêter si on atteint un livre
    // après celui recherché
    if (comparaison > 0) {
        return 0;
    }

    return trouverEtSupprimerRayon(actuel->suivant, themeASupprimer);
}

// Dans le meilleur des cas O(n)
// Dans le pire des cas O(n^2)
int supprimerRayon(T_Biblio *biblio, char* themeASupprimer) {
    if (! biblio->premier) {
        return 0;
    }

    int comparaison = strcmp(biblio->premier->theme_rayon, themeASupprimer);

    // On a trouvé le rayon
    if (comparaison == 0) {
        struct Rayon* aSupprimer = biblio->premier;
        biblio->premier = aSupprimer->suivant;

        supprimerLivresListe(aSupprimer->premier);
        free(aSupprimer);

        return 1;
    }

    // Les rayons sont triés, on peut donc s'arrêter si on atteint un livre
    // après celui recherché
    if (comparaison > 0) {
        return 0;
    }

    return trouverEtSupprimerRayon(biblio->premier, themeASupprimer);
}

// O(n)
void rechercherLivreListe(T_Livre *actuel, char* critereTitre, char* themeRayon) {
    if (strstr(actuel->titre, critereTitre) != NULL) {
        printf(
                "| %-35s | %-20s | %-15s | %-5s | %-20s |\n",
                actuel->titre,
                actuel->auteur,
                actuel->edition,
                actuel->disponible ? "Oui" : "Non",
                themeRayon
        );
    }

    if (actuel->suivant) {
        rechercherLivreListe(actuel->suivant, critereTitre, themeRayon);
    }
}

// O(n)
void rechercherLivreRayons(T_Rayon *rayon, char* critereTitre) {
    rechercherLivreListe(rayon->premier, critereTitre, rayon->theme_rayon);

    if (rayon->suivant) {
        rechercherLivreRayons(rayon->suivant, critereTitre);
    }
}

// O(n^2)
void rechercherLivres(T_Biblio *biblio, char* critereTitre) {
    printf(
            " Recherche: %s\n"
                    " -------------------------------------------------------------------------------------------------------------\n",
            critereTitre
    );

    printf("| %-35s | %-20s | %-15s | %-5s | %-20s |\n", "Titre", "Auteur", "Edition", "Dispo", "Rayon");
    printf("|-------------------------------------------------------------------------------------------------------------|\n");
    rechercherLivreRayons(biblio->premier, critereTitre);
    printf(" -------------------------------------------------------------------------------------------------------------\n");
}

int main() {
    T_Biblio *biblio = creerBiblio("NF16");

    T_Rayon *rayonJulesVerne = creerRayon("Jules Verne");
    ajouterLivre(rayonJulesVerne, creerLivre("Cinq semaines en ballon", "Jules Verne", "Hetzel"));
    ajouterLivre(rayonJulesVerne, creerLivre("Les Aventures du capitaine Hatteras", "Jules Verne", "Hetzel"));
    ajouterLivre(rayonJulesVerne, creerLivre("Voyage au centre de la Terre", "Jules Verne", "Hetzel"));
    ajouterLivre(rayonJulesVerne, creerLivre("De la Terre a la Lune", "Jules Verne", "Hetzel"));
    ajouterLivre(rayonJulesVerne, creerLivre("Le Compte de Chanteleine", "Jules Verne", "Hetzel"));

    T_Rayon *rayonVictorHugo = creerRayon("Victor Hugo");
    ajouterLivre(rayonVictorHugo, creerLivre("Ruy Blas", "Victor Hugo", "Gallica"));
    ajouterLivre(rayonVictorHugo, creerLivre("Cromwell", "Victor Hugo", "Gallica"));
    ajouterLivre(rayonVictorHugo, creerLivre("Hernani", "Victor Hugo", "Gallica"));
    ajouterLivre(rayonVictorHugo, creerLivre("Cinq semaines Victor Hugo 2", "Victor Hugo", "Hetzel"));
    ajouterLivre(rayonVictorHugo, creerLivre("Marion de Lorme", "Victor Hugo", "Gallica"));
    ajouterLivre(rayonVictorHugo, creerLivre("Marie Tudor", "Victor Hugo", "Gallica"));
    ajouterLivre(rayonVictorHugo, creerLivre("Cinq semaines Victor Hugo", "Victor Hugo", "Hetzel"));

    ajouterRayon(biblio, rayonJulesVerne);
    ajouterRayon(biblio, rayonVictorHugo);

    /*
    afficherRayon(rayonJulesVerne);

    printf("%d", emprunterLivre(rayonJulesVerne, "Cinq semaines en ballon"));
    printf("%d", emprunterLivre(rayonJulesVerne, "Le Compte de Chanteleine"));
    printf("%d", emprunterLivre(rayonJulesVerne, "Voyage au centre de la Terre"));

    afficherRayon(rayonJulesVerne);

    printf("%d", supprimerLivre(rayonJulesVerne, "Cinq semaines en ballon"));
    printf("%d", supprimerLivre(rayonJulesVerne, "Le Compte de Chanteleine"));
    printf("%d", supprimerLivre(rayonJulesVerne, "Voyage au centre de la Terre"));

    afficherRayon(rayonJulesVerne);

    afficherBiblio(biblio);

    printf("%d", supprimerRayon(biblio, "Victor Hugo"));

    afficherBiblio(biblio);

    printf("%d", supprimerRayon(biblio, "Jules Verne"));

    afficherBiblio(biblio);
    */

    rechercherLivres(biblio, "semaines");

    return 0;
}
