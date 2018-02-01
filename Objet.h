#ifndef DEF_OBJET
#define DEF_OBJET

#include <string>

class Objet
{
    protected:

    std::string nom;
    float poids;
    int prix;
    std::string type;
    std::string description;

    public:

    Objet();
    std::string GetNom();
};

#endif
