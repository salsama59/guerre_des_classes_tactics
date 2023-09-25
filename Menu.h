#ifndef DEF_MENU
#define DEF_MENU
#include"Personnage.h"
#include"Jeu.h"
#include <ft2build.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_mixer.h>
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
    SDL_Texture *tof;
    SDL_Texture *tofGroupe;
    SDL_Texture *titreMenu;
    SDL_Texture *cursseur;//Cursseur permettant la navigation dans le menu
    SDL_Texture *fenMenu;//Fenetre du menu
    SDL_Renderer *ecran;//Pointeur vers la fenetre principale
    SDL_Texture *texteStatPv[4];
    SDL_Texture *texteStatPm[4];
    SDL_Texture *texteStatExp[4];
    SDL_Texture *texteStatPrenom[4];
    SDL_Texture *texteStatNiv[4];
    SDL_Texture *texte[9];
    SDL_Texture *ligne;
    SDL_Texture *ligneHorizontale[4];
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
    Mix_Chunk  *sonDeplacement;//Son lors du déplacement du cursseur dans le  menu
    Mix_Chunk  *sonValidation;//Son lors de la validation
    Mix_Chunk  *sonAnnulation;//Son lors de l'annulation
    Mix_Chunk  *sonMenu;//Son lors de l'entrée dans le menu
    TTF_Font *police;//Police de caractère utilisé dans le menu
    TTF_Font *police2;//Police de caractère utilisé dans le menu
    int vitesseCursseur;//Vitesse de déplacement du cursseur

    public:

    Menu(Jeu &j);
    Menu();
    ~Menu();
    void EmissionSonDeplacement();
    void EmissionSonValidation();
    void EmissionSonAnnulation();
    void EmissionSonMenu();
    void AffichageMenu(std::vector<Personnage*> equipe, std::vector<Personnage*> groupe, SDL_Renderer *ecran, std::vector<Arme*> armeInventaire, std::vector<Casque*> casqueInventaire, std::vector<Cuirasse*> cuirasseInventaire, std::vector<Bouclier*> bouclierInventaire, std::vector<Jambiere*> jambiereInventaire, Jeu *obj);

    private:
    void DisplayMenuElements(std::vector<std::string> elements, std::vector<Personnage*> equipe);

};

#endif
