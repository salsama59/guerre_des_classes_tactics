#ifndef DEF_SMENUEQUIPEMENT
#define DEF_SMENUEQUIPEMENT
#include"Personnage.h"
#include"Jeu.h"
#include"Menu.h"
#include <freetype/freetype.h>
#include <ft2build.h>
#include <SDL/SDL_ttf.h>
#include <fmodex/fmod.h>
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
    SDL_Surface *optionEquipement[3];
    SDL_Surface *texteStatFr[4];
    SDL_Surface *texteStatDef[4];
    SDL_Surface *texteStatMag[4];
    SDL_Surface *texteStatVol[4];
    SDL_Surface *texteStatVit[4];
    SDL_Surface *texteStatPrc[4];
    SDL_Surface *texteStatEsq[4];
    SDL_Surface *texteStatCha[4];
    SDL_Surface *InfoArmeFr;
    SDL_Surface *InfoArmeDef;
    SDL_Surface *InfoArmeMag;
    SDL_Surface *InfoArmeVol;
    SDL_Surface *InfoArmeVit;
    SDL_Surface *InfoArmePrc;
    SDL_Surface *InfoArmeEsq;
    SDL_Surface *InfoArmeCha;
    SDL_Surface *InfoArmePv;
    SDL_Surface *InfoArmePm;
    SDL_Surface *texteStatNom[4];
    SDL_Surface *texteDegatArme[5];
    SDL_Surface *texteNomArme[5];
    SDL_Surface *texteNomArmure[5];
    SDL_Surface *texteNomCuirasse[5];
    SDL_Surface *texteNomBouclier[5];
    SDL_Surface *texteNomJambiere[5];
    SDL_Surface *texteStatNomArme[5];
    SDL_Surface *texteStatNomArmureM0[4];
    SDL_Surface *texteStatNomArmureM1[4];
    SDL_Surface *texteEquipement[5];
    SDL_Surface *ligneHorizontale[4];
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

    SmenuEquipement(SDL_Surface *ecran);
    ~SmenuEquipement();
    void AffichageEquipement(std::vector<Personnage*> equipe, SDL_Surface *ecran, std::vector<Arme*> armeInventaire, std::vector<Casque*> casqueInventaire, std::vector<Cuirasse*> cuirasseInventaire, std::vector<Bouclier*> bouclierInventaire, std::vector<Jambiere*> jambiereInventaire, Jeu *obj);

};

#endif
