
struct Livre {
    char* titre;
    char* auteur;
    char* edition;
    int disponible;
    struct Livre* suivant;
};

struct Rayon {
    char* theme_rayon;
    int nombre_livres;
    struct Livre* premier;
    struct Rayon* suivant;
};

struct Biblio {
    char* nom;
    struct Rayon* premier;
};

typedef struct Livre T_Livre;
typedef struct Rayon T_Rayon;
typedef struct Biblio T_Biblio;
