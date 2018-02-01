#ifndef DEF_GROUPE
#define DEF_GROUPE
#include"Personnage.h"
#include"Jeu.h"
#include"Menu.h"
#include <freetype/freetype.h>
#include <ft2build.h>
#include <SDL/SDL_ttf.h>
#include <fmodex/fmod.h>
#include <string>

class Groupe: public Menu
{
    private:

    SDL_Surface *ligneHorizontale[4];
    SDL_Rect positionTexteStatPv[4];
    SDL_Rect positionTexteStatPm[4];

    public:

    Groupe(SDL_Surface *ecran);
    ~Groupe();
    void AffichageGroupe(std::vector<Personnage*> groupe, std::vector<Personnage*> equipe, SDL_Surface *ecran, Jeu *obj);

};

#endif
