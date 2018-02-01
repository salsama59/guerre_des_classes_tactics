#include <cstdlib>
#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include <SDL/SDL_ttf.h>
#include <fmodex/fmod.h>
#include <ft2build.h>
#include <freetype/freetype.h>
#include "Inventaire.h"
#include "Jeu.h"
#include <string>
#include <iostream>
#include <vector>
using namespace std;

Inventaire::Inventaire(Jeu &j)
{
    largeur=640;
    hauteur=480;
    ecran=j.GetFen();
    couleur= SDL_MapRGB(ecran->format, 180, 180, 180);
    fenMenu = SDL_CreateRGBSurface(SDL_HWSURFACE, largeur, hauteur, 32, 0, 0, 0, 0);
    positionMenu.x=0;
    positionMenu.y=0;
    //Modification de la couleur du fond
    SDL_FillRect(fenMenu, NULL, couleur);
    FMOD_System_Create(&system);
    FMOD_System_Init(system, 3, FMOD_INIT_NORMAL, NULL);
    FMOD_System_CreateSound(system, "deplacement.mp3", FMOD_CREATESAMPLE, 0, &sonDeplacement);
    FMOD_System_CreateSound(system, "validation.wav", FMOD_CREATESAMPLE, 0, &sonValidation);
    FMOD_System_CreateSound(system, "annulation.wav", FMOD_CREATESAMPLE, 0, &sonAnnulation);
    FMOD_System_GetChannel(system, 1, &channel);
}

Inventaire:: ~Inventaire()
{
    FMOD_System_Close(system);
    FMOD_System_Release(system);
    FMOD_Sound_Release(sonDeplacement);
    FMOD_Sound_Release(sonAnnulation);
    FMOD_Sound_Release(sonValidation);
}

void Inventaire::AffichageInventaire()
{
    int cycle=1, init=0, i=0, t=0, j=0;
    init=TTF_Init();
    if(init == -1)
    {
        fprintf(stderr, "Erreur d'initialisation de TTF_Init : %s\n", TTF_GetError());
        exit(EXIT_FAILURE);
        atexit(TTF_Quit);
    }

    police = TTF_OpenFont("arial.ttf", 30);
    couleurCarac = {255, 255, 255};
    //TTF_SetFontStyle(police, TTF_STYLE_BOLD | TTF_STYLE_UNDERLINE | TTF_STYLE_ITALIC);

    couleurCursseur= SDL_MapRGB(ecran->format, 255, 255, 36);
    positionCursseur.w=185;
    positionCursseur.h=35;
    positionCursseur.x=0;
    positionCursseur.y=0;
    cursseur= SDL_CreateRGBSurface(SDL_HWSURFACE, positionCursseur.w, positionCursseur.h, 32, 0, 0, 0, 0);
    SDL_FillRect(cursseur, NULL, couleurCursseur);
    SDL_SetAlpha(cursseur, SDL_SRCALPHA, 70);
    while (cycle)
    {
        SDL_WaitEvent(&action);
        switch(action.type)
        {
            case SDL_QUIT :
            cycle = 0;
            exit(EXIT_SUCCESS);
            atexit(SDL_Quit);

            case SDL_KEYDOWN:
            switch (action.key.keysym.sym)
            {
                case SDLK_ESCAPE: //Appui sur la touche Echap, on sort du menu pour revenir au jeu
                cycle = 0;
                break;

                case SDLK_SPACE:
                break;

                case SDLK_UP:

                break;

                case SDLK_DOWN:

                break;
            }
            break;
        }

        // Collage de la surface de menu sur l'écran
        SDL_BlitSurface(fenMenu, NULL, ecran, &positionMenu);

        SDL_BlitSurface(cursseur, NULL, ecran, &positionCursseur);
        //Mise à jour de l'affichage
        SDL_Flip(ecran);
    }
}
