#ifndef DEF_MENU
#define DEF_MENU
#include"Personnage.h"
#include"Jeu.h"
#include <ft2build.h>
#include <SDL/SDL_ttf.h>
#include <fmodex/fmod.h>
#include "Constantes.h"
#include <string>
#include <vector>
class Menu
{
    protected:

    char tableauPv[TAILLE_TAB_CONV];
    char tableauPm[TAILLE_TAB_CONV];
    char tableauExp[TAILLE_TAB_CONV];
    char tableauNiv[TAILLE_TAB_CONV];
    int largeur;//Largeur du menu
    int hauteur;//hauteur du menu
    int largeurCur;//Largeur du cursseur
    int hauteurCur;//hauteur du cursseur
    Uint32 couleur;//Couleur du menu
    Uint32 couleurCursseur;
    Uint32 couleurLigne;
    SDL_Color couleurCarac;
    SDL_Color couleurAjout;
    SDL_Surface *tof;
    SDL_Surface *tofGroupe;
    SDL_Surface *titreMenu;
    SDL_Surface *cursseur;//Cursseur permettant la navigation dans le menu
    SDL_Surface *fenMenu;//Fenetre du menu
    SDL_Surface *ecran;//Pointeur vers la fenetre principale
    SDL_Surface *texteStatPv[4];
    SDL_Surface *texteStatPm[4];
    SDL_Surface *texteStatExp[4];
    SDL_Surface *texteStatPrenom[4];
    SDL_Surface *texteStatNiv[4];
    SDL_Surface *texte[9];
    SDL_Surface *ligne;
    SDL_Surface *ligneHorizontale[4];
    SDL_Rect positionCursseur;//Position du cursseur dans le menu
    SDL_Rect positionTitreMenu;
    SDL_Rect positionMenu;//Position de la fenêtre du menu
    SDL_Rect positionTexte[9];
    SDL_Rect positionTexteStatPv[4];
    SDL_Rect positionTexteStatPm[4];
    SDL_Rect positionTexteStatExp[4];
    SDL_Rect positionTexteStatPrenom[4];
    SDL_Rect positionTexteStatNiv[4];
    SDL_Rect positionTof[4];
    SDL_Rect positionTofGroupe[4];
    SDL_Rect positionLigne;
    SDL_Rect positionLigneHorizontale[4];
    SDL_Rect clip[4];
    SDL_Rect clipGroupe[4];
    SDL_Event action;//Variable permettant la gestion des évènements dans le menu
    FMOD_SYSTEM *system;
    FMOD_CHANNEL *channel;
    FMOD_SOUND *sonDeplacement;//Son lors du déplacement du cursseur dans le  menu
    FMOD_SOUND *sonValidation;//Son lors de la validation
    FMOD_SOUND *sonAnnulation;//Son lors de l'annulation
    FMOD_SOUND *sonMenu;//Son lors de l'entrée dans le menu
    TTF_Font *police;//Police de caractère utilisé dans le menu
    TTF_Font *police2;//Police de caractère utilisé dans le menu
    int vitesseCursseur;//Vitesse de déplacement du cursseur

    public:

    Menu(Jeu &j);
    Menu();
    ~Menu();
    void ChangerCouleur(int r, int v, int b);
    void EmissionSonDeplacement();
    void EmissionSonValidation();
    void EmissionSonAnnulation();
    void EmissionSonMenu();
    void AffichageMenu(std::vector<Personnage*> equipe, std::vector<Personnage*> groupe, SDL_Surface *ecran, std::vector<Arme*> armeInventaire, std::vector<Casque*> casqueInventaire, std::vector<Cuirasse*> cuirasseInventaire, std::vector<Bouclier*> bouclierInventaire, std::vector<Jambiere*> jambiereInventaire, Jeu *obj);

};

#endif
