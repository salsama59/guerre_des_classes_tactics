#include <cstdlib>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include "Jeu.h"
#include "Menu.h"
#include "Moine.h"
#include "ChevalierDragon.h"
#include "Personnage.h"
#include "Equipement.h"
#include "Constantes.h"
#include <vector>
#include <iostream>
using namespace std;

Jeu::Jeu()
{
    if (SDL_Init(SDL_INIT_EVERYTHING) == -1) // Démarrage de la SDL. Si erreur :
    {
        fprintf(stderr, "Erreur d'initialisation de la SDL : %s\n", SDL_GetError()); // Écriture de l'erreur
        exit(EXIT_FAILURE); // On quitte le programme
    }

    // On s'assure de la fermeture de la SDL
    atexit(SDL_Quit);

     // Ouverture de la fenêtre
    fenetre = SDL_CreateWindow("Heroic fantasy version demo",
                          SDL_WINDOWPOS_CENTERED,
                          SDL_WINDOWPOS_CENTERED,
                          LARGEUR, HAUTEUR,
                          SDL_WINDOW_ALLOW_HIGHDPI | SDL_WINDOW_SHOWN);
    renderer = SDL_CreateRenderer(fenetre, -1, 0);

    //"Heroic fantasy version demo", 
    //fenetre=SDL_SetVideoMode(LARGEUR, HAUTEUR, NB_BITS_PAR_PIXEL, SDL_HWSURFACE | SDL_DOUBLEBUF);

    //Changer le titre de la fenêtre
    //SDL_WM_SetCaption("Heroic fantasy version demo", NULL);

    //En cas d'erreur
    if (!fenetre ||  !renderer)
    {
        fprintf(stderr, "Impossible d'ouvrir une fenetre : %s\n", SDL_GetError());// Écriture de l'erreur
        exit(EXIT_FAILURE); // On quitte le programme
    }

    SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "linear");  // make the scaled rendering look smoother.
    SDL_RenderSetLogicalSize(renderer, LARGEUR, HAUTEUR);

    // On s'assure de la fermeture de la SDL
    atexit(SDL_Quit);
}

void Jeu::Jouer()
{
    Menu *x=new Menu(*this);
    ChevalierDragon *sherao= new ChevalierDragon();
    Moine *sherifa= new Moine();
    //Personnage *X=new Personnage();
    //Personnage *X1=new Personnage("Jean", "Pierre");
    Lance *l1=new Lance("Partisant", 10);
    Lance *l2=new Lance("Javelo", 7);
    Gant *G1=new Gant("Gant en cuir", 15);
    Gant *G2=new Gant("Gant en tissu", 10);
    Casque *C1=new Casque("Barbut", "Lourd");
    Casque *C2=new Casque("Chapeau", "Leger");
    Cuirasse *CU1=new Cuirasse("Rengis", "Lourd");
    Cuirasse *CU2=new Cuirasse("Manteau", "Leger");
    Bouclier *BO1=new Bouclier("Targe", "Leger");
    Bouclier *BO2=new Bouclier("Bouclier or", "Lourd");
    Jambiere *JA1=new Jambiere("Botte de soie", "Leger");
    Jambiere *JA2=new Jambiere("Botte metal", "Lourd");
    sauvegardeCasqueInventaire.push_back(C1);
    sauvegardeCasqueInventaire.push_back(C2);
    sauvegardeCuirasseInventaire.push_back(CU1);
    sauvegardeCuirasseInventaire.push_back(CU2);
    sauvegardeBouclierInventaire.push_back(BO1);
    sauvegardeBouclierInventaire.push_back(BO2);
    sauvegardeJambiereInventaire.push_back(JA1);
    sauvegardeJambiereInventaire.push_back(JA2);
    sauvegardeArmeInventaire.push_back(l1);
    sauvegardeArmeInventaire.push_back(l2);
    sauvegardeArmeInventaire.push_back(G1);
    sauvegardeArmeInventaire.push_back(G2);
    sauvegardeGroupe.push_back(sherifa);
    sauvegardeGroupe.push_back(sherao);
    //sauvegardeGroupe.push_back(X);
    //sauvegardeGroupe.push_back(X1);
    sauvegardeEquipe.push_back(sherifa);
    sauvegardeEquipe.push_back(sherao);
    //sauvegardeEquipe.push_back(X);
    //sauvegardeEquipe.push_back(X1);
    //SDL_Surface *rectangle= NULL;
    SDL_Rect position;
    position.x = (LARGEUR / 2) - (220 / 2);
    position.y = (HAUTEUR / 2) - (180 / 2);
    position.w = 220;
    position.h = 180;

    SDL_Event event;
    int boucle = 1;
    //Création de la surface rectangulaire
    //rectangle = SDL_CreateRGBSurface(SDL_HWSURFACE, 220, 180, NB_BITS_PAR_PIXEL, 0, 0, 0, 0);
    /*SDL_Texture *sdlTexture = SDL_CreateTexture(renderer,
                               SDL_PIXELFORMAT_ARGB8888,
                               SDL_TEXTUREACCESS_STREAMING,
                               LARGEUR, HAUTEUR);*/
    // Remplissage de la surface avec du vert
    //Uint32 *myPixels = malloc(220 * 180  * sizeof (Uint32);
    //SDL_UpdateTexture(sdlTexture, NULL, myPixels, 220 * sizeof (Uint32));
    SDL_SetRenderDrawColor( renderer, 255, 255, 255, SDL_ALPHA_OPAQUE );
    SDL_RenderClear(renderer);
    //SDL_SetTextureBlendMode(sdlTexture, SDL_BLENDMODE_NONE);
    //SDL_SetTextureColorMod(sdlTexture, 255, 255, 255);
    //SDL_SetTextureAlphaMod(sdlTexture, 255);
    //SDL_RenderCopy(renderer, sdlTexture, NULL, NULL);
    SDL_SetRenderDrawColor( renderer, 0, 255, 0, SDL_ALPHA_OPAQUE );
    SDL_RenderFillRect(renderer, &position);
    SDL_RenderPresent(renderer);
    //SDL_RenderClear(renderer);
    //SDL_FillRect(rectangle, NULL, SDL_MapRGB(fenetre->format, 0, 255, 0));
    while (boucle)
    {
        SDL_WaitEvent(&event);
        switch(event.type)
        {
            case SDL_QUIT :
            boucle = 0;
            exit(EXIT_SUCCESS);
            atexit(SDL_Quit);

            case SDL_KEYDOWN:
            switch (event.key.keysym.sym)
            {
                case SDLK_ESCAPE: //Appui sur la touche Echap, on ouvre le menu
                x->EmissionSonMenu();
                x->AffichageMenu(sauvegardeEquipe, sauvegardeGroupe, renderer, sauvegardeArmeInventaire, sauvegardeCasqueInventaire, sauvegardeCuirasseInventaire, sauvegardeBouclierInventaire, sauvegardeJambiereInventaire, this->GetObjet());
                break;

                case SDLK_m: //Appui sur la touche Echap, on ouvre le menu
                x->EmissionSonMenu();
                x->AffichageMenu(sauvegardeEquipe, sauvegardeGroupe, renderer, sauvegardeArmeInventaire, sauvegardeCasqueInventaire, sauvegardeCuirasseInventaire, sauvegardeBouclierInventaire, sauvegardeJambiereInventaire, this->GetObjet());
                break;

                case SDLK_SPACE:
                boucle = 0;
                break;
            }
            break;
        }

        SDL_SetRenderDrawColor( renderer, 255, 255, 255, SDL_ALPHA_OPAQUE );
        SDL_RenderClear(renderer);
        //SDL_SetTextureBlendMode(sdlTexture, SDL_BLENDMODE_NONE);
        //SDL_SetTextureColorMod(sdlTexture, 255, 255, 255);
        //SDL_SetTextureAlphaMod(sdlTexture, 255);
        //SDL_RenderCopy(renderer, sdlTexture, NULL, NULL);
        SDL_SetRenderDrawColor( renderer, 0, 255, 0, SDL_ALPHA_OPAQUE );
        SDL_RenderFillRect(renderer, &position);
        SDL_RenderPresent(renderer);
        //Modification de la couleur du fond
       // SDL_FillRect(fenetre, NULL, SDL_MapRGB(fenetre->format, 255, 255, 255));
        // Collage de la surface sur l'écran
        //SDL_BlitSurface(rectangle, NULL, fenetre, &position);
        // Mise à jour de l'écran avec sa nouvelle couleur
        //SDL_Flip(fenetre);
    }
    // Libération de la surface
    //SDL_FreeSurface(rectangle);
}

SDL_Renderer *Jeu::GetFen()
{
    return renderer;
}

void Jeu::SetArmeInventaire(std::vector<Arme*> nouvelInventaire)
{
    this->sauvegardeArmeInventaire=nouvelInventaire;
}

void Jeu::SetCasqueInventaire(std::vector<Casque*> nouvelInventaire)
{
    this->sauvegardeCasqueInventaire=nouvelInventaire;
}

void Jeu::SetCuirasseInventaire(std::vector<Cuirasse*> nouvelInventaire)
{
    this->sauvegardeCuirasseInventaire=nouvelInventaire;
}

void Jeu::SetBouclierInventaire(std::vector<Bouclier*> nouvelInventaire)
{
    this->sauvegardeBouclierInventaire=nouvelInventaire;
}

void Jeu::SetJambiereInventaire(std::vector<Jambiere*> nouvelInventaire)
{
    this->sauvegardeJambiereInventaire=nouvelInventaire;
}

void Jeu::SetGroupe(std::vector <Personnage*> nouveauGroupe)
{
    this->sauvegardeGroupe=nouveauGroupe;
}

void Jeu::SetEquipe(std::vector <Personnage*> nouvelleEquipe)
{
    this->sauvegardeEquipe=nouvelleEquipe;
}

std::vector <Arme*> Jeu::GetArmeInventaire()
{
    return sauvegardeArmeInventaire;
}

std::vector <Casque*> Jeu::GetCasqueInventaire()
{
    return sauvegardeCasqueInventaire;
}

std::vector <Cuirasse*> Jeu::GetCuirasseInventaire()
{
    return sauvegardeCuirasseInventaire;
}

std::vector <Bouclier*> Jeu::GetBouclierInventaire()
{
    return sauvegardeBouclierInventaire;
}

std::vector <Jambiere*> Jeu::GetJambiereInventaire()
{
    return sauvegardeJambiereInventaire;
}

std::vector <Personnage*> Jeu::GetGroupe()
{
    return sauvegardeGroupe;
}

std::vector <Personnage*> Jeu::GetEquipe()
{
    return sauvegardeEquipe;
}

Jeu *Jeu::GetObjet()
{
    return this;
}
