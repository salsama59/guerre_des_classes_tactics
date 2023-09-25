#ifndef DEF_INVENTAIRE
#define DEF_INVENTAIRE
#include"Personnage.h"
#include"Jeu.h"
#include"Menu.h"
#include <freetype/freetype.h>
#include <ft2build.h>
#include <SDL2/SDL_ttf.h>
#include <string>

class Inventaire: public Menu
{
    private:


    public:

    Inventaire(Jeu &j);
    ~Inventaire();
    void AffichageInventaire();

};

#endif
