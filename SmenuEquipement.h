#ifndef DEF_SMENUEQUIPEMENT
#define DEF_SMENUEQUIPEMENT
#include"Personnage.h"
#include"Jeu.h"
#include"Menu.h"
#include <freetype/freetype.h>
#include <ft2build.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_mixer.h>
#include <string>

class SmenuEquipement: public Menu
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
    char tableauDegat[TAILLE_TAB_CONV];
    char tableauInfoCasque[TAILLE_TAB_CONV];
    char tableauInfoCuirasse[TAILLE_TAB_CONV];
    char tableauInfoBouclier[TAILLE_TAB_CONV];
    char tableauInfoJambiere[TAILLE_TAB_CONV];
    SDL_Texture *optionEquipement[3];
    SDL_Texture *texteStatFr[4];
    SDL_Texture *texteStatDef[4];
    SDL_Texture *texteStatMag[4];
    SDL_Texture *texteStatVol[4];
    SDL_Texture *texteStatVit[4];
    SDL_Texture *texteStatPrc[4];
    SDL_Texture *texteStatEsq[4];
    SDL_Texture *texteStatCha[4];
    SDL_Texture *InfoArmeFr;
    SDL_Texture *InfoArmeDef;
    SDL_Texture *InfoArmeMag;
    SDL_Texture *InfoArmeVol;
    SDL_Texture *InfoArmeVit;
    SDL_Texture *InfoArmePrc;
    SDL_Texture *InfoArmeEsq;
    SDL_Texture *InfoArmeCha;
    SDL_Texture *InfoArmePv;
    SDL_Texture *InfoArmePm;
    SDL_Texture *texteStatNom[4];
    SDL_Texture *texteDegatArme[5];
    SDL_Texture *texteNomArme[5];
    SDL_Texture *texteNomArmure[5];
    SDL_Texture *texteNomCuirasse[5];
    SDL_Texture *texteNomBouclier[5];
    SDL_Texture *texteNomJambiere[5];
    SDL_Texture *texteStatNomArme[5];
    SDL_Texture *texteStatNomArmureM0[4];
    SDL_Texture *texteStatNomArmureM1[4];
    SDL_Texture *texteEquipement[5];
    SDL_Texture *ligneHorizontale[4];
    SDL_Rect positionOptionEquipement[3];
    SDL_Rect positionTexteStatFr[4];
    SDL_Rect positionTexteStatDef[4];
    SDL_Rect positionTexteStatMag[4];
    SDL_Rect positionTexteStatVol[4];
    SDL_Rect positionTexteStatVit[4];
    SDL_Rect positionTexteStatPrc[4];
    SDL_Rect positionTexteStatEsq[4];
    SDL_Rect positionTexteStatCha[4];
    SDL_Rect positionTexteStatPv[4];
    SDL_Rect positionTexteStatPm[4];
    SDL_Rect positionInfoArmeFr;
    SDL_Rect positionInfoArmeDef;
    SDL_Rect positionInfoArmeMag;
    SDL_Rect positionInfoArmeVol;
    SDL_Rect positionInfoArmeVit;
    SDL_Rect positionInfoArmePrc;
    SDL_Rect positionInfoArmeEsq;
    SDL_Rect positionInfoArmeCha;
    SDL_Rect positionInfoArmePv;
    SDL_Rect positionInfoArmePm;
    SDL_Rect positionLigneHorizontale[2];
    SDL_Rect positionTexteNomArme[5];
    SDL_Rect positionTexteNomArmure[5];
    SDL_Rect positionTexteNomCuirasse[5];
    SDL_Rect positionTexteNomJambiere[5];
    SDL_Rect positionTexteNomBouclier[5];
    SDL_Rect positionTexteDegatArme[4];
    SDL_Rect positionTexteStatNomArme[5];
    SDL_Rect positionTexteStatNomArmure[5];
    SDL_Rect positionTexteEquipement[5];
    SDL_Rect positionTof;

    public:

    SmenuEquipement(SDL_Renderer *ecran);
    ~SmenuEquipement();
    void AffichageEquipement(std::vector<Personnage*> equipe, SDL_Renderer *ecran, std::vector<Arme*> armeInventaire, std::vector<Casque*> casqueInventaire, std::vector<Cuirasse*> cuirasseInventaire, std::vector<Bouclier*> bouclierInventaire, std::vector<Jambiere*> jambiereInventaire, Jeu *obj);

    private:
    void DisplayMenuElements(std::vector<Personnage*> equipe, std::vector<Arme*> armeInventaire, std::vector<Casque*> casqueInventaire, std::vector<Cuirasse*> cuirasseInventaire, std::vector<Bouclier*> bouclierInventaire, std::vector<Jambiere*> jambiereInventaire, int memberId, SDL_Renderer *ecran, int cpt, int flag);

};

#endif
