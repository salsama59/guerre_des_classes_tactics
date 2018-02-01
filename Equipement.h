#ifndef DEF_EQUIPEMENT
#define DEF_EQUIPEMENT

#include <string>

class Equipement
{
    protected:

    std::string nom;
    std::string genre;
    std::string categorie;
    float poids;
    int prix;

    public:

    Equipement();
    std::string GetNom();
    std::string GetGenre();
    std::string GetCategorie();
};

#endif
