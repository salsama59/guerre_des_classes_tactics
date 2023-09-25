#ifndef DEF_GROUPE
#define DEF_GROUPE
#include"Personnage.h"
#include"Jeu.h"
#include"Menu.h"
#include <freetype/freetype.h>
#include <ft2build.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_mixer.h>
#include <string>

class Groupe: public Menu
{
    private:

    SDL_Texture *ligneHorizontale[4];
    SDL_Rect positionTexteStatPv[4];
    SDL_Rect positionTexteStatPm[4];
    void DisplayMenuElements(std::vector<Personnage*> equipe, SDL_Renderer *ecran);

    public:

    Groupe(SDL_Renderer *ecran);
    ~Groupe();
    void AffichageGroupe(std::vector<Personnage*> groupe, std::vector<Personnage*> equipe, SDL_Renderer *ecran, Jeu *obj);

};

#endif
