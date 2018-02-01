#ifndef DEF_ETAT
#define DEF_ETAT
#include"Personnage.h"
#include"Jeu.h"
#include"Menu.h"
#include"Constantes.h"
#include <ft2build.h>
#include <SDL/SDL_ttf.h>
#include <fmodex/fmod.h>
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
    SDL_Surface *texteStatFr[4];
    SDL_Surface *texteStatDef[4];
    SDL_Surface *texteStatMag[4];
    SDL_Surface *texteStatVol[4];
    SDL_Surface *texteStatVit[4];
    SDL_Surface *texteStatPrc[4];
    SDL_Surface *texteStatEsq[4];
    SDL_Surface *texteStatCha[4];
    SDL_Surface *texteStatNom[4];
    SDL_Surface *texteStatNomArme[4];
    SDL_Surface *texteStatNomArmureM0[4];
    SDL_Surface *texteStatNomArmureM1[4];
    SDL_Surface *texteStatNomArmureM2[4];
    SDL_Surface *texteStatNomArmureM3[4];
    SDL_Surface *texteEquipement[5];
    SDL_Surface *texte[9];
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

    Etat(SDL_Surface *ecran);
    //~Etat();
    void AffichageEtat(std::vector<Personnage*> equipe, SDL_Surface *ecran);

};

#endif
