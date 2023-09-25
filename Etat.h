#ifndef DEF_ETAT
#define DEF_ETAT
#include"Personnage.h"
#include"Jeu.h"
#include"Menu.h"
#include"Constantes.h"
#include <ft2build.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_mixer.h>
#include <string>
#include <vector>

class Etat : public Menu
{
    private:

    char tableauFr[TAILLE_TAB_CONV];
    char tableauDef[TAILLE_TAB_CONV];
    char tableauVol[TAILLE_TAB_CONV];
    char tableauPrc[TAILLE_TAB_CONV];
    char tableauEsq[TAILLE_TAB_CONV];
    char tableauCha[TAILLE_TAB_CONV];
    char tableauVit[TAILLE_TAB_CONV];
    char tableauMag[TAILLE_TAB_CONV];
    SDL_Texture *texteStatFr[4];
    SDL_Texture *texteStatDef[4];
    SDL_Texture *texteStatMag[4];
    SDL_Texture *texteStatVol[4];
    SDL_Texture *texteStatVit[4];
    SDL_Texture *texteStatPrc[4];
    SDL_Texture *texteStatEsq[4];
    SDL_Texture *texteStatCha[4];
    SDL_Texture *texteStatNom[4];
    SDL_Texture *texteStatNomArme[4];
    SDL_Texture *texteStatNomArmureM0[4];
    SDL_Texture *texteStatNomArmureM1[4];
    SDL_Texture *texteStatNomArmureM2[4];
    SDL_Texture *texteStatNomArmureM3[4];
    SDL_Texture *texteEquipement[5];
    SDL_Texture *texte[9];
    SDL_Surface *ligne;
    SDL_Surface *ligneHorizontale[4];
    const char *tableauEquip[5];
    SDL_Rect positionTexteStatFr[4];
    SDL_Rect positionTexteStatDef[4];
    SDL_Rect positionTexteStatMag[4];
    SDL_Rect positionTexteStatVol[4];
    SDL_Rect positionTexteStatVit[4];
    SDL_Rect positionTexteStatPrc[4];
    SDL_Rect positionTexteStatEsq[4];
    SDL_Rect positionTexteStatCha[4];
    SDL_Rect positionTexteStatNom[4];
    SDL_Rect positionTexteStatPv[4];
    SDL_Rect positionTexteStatPm[4];
    SDL_Rect positionTexteStatExp[4];
    SDL_Rect positionTexteStatPrenom[4];
    SDL_Rect positionTexteStatNiv[4];
    SDL_Rect positionTexteStatNomArme[4];
    SDL_Rect positionTexteStatNomArmure[4];
    SDL_Rect positionTexteEquipement[5];
    SDL_Rect positionTof;

    public:

    Etat(SDL_Renderer *ecran);
    //~Etat();
    void AffichageEtat(std::vector<Personnage*> equipe, SDL_Renderer *ecran);

    void DisplayMenuElements(std::vector<Personnage *> equipe, int memberId, SDL_Renderer *ecran);
};

#endif
