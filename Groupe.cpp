#include <cstdlib>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_mixer.h>
#include <ft2build.h>
#include "Groupe.h"
#include "Jeu.h"
#include "Lance.h"
#include "Gant.h"
#include <string>
#include <iostream>
#include <vector>
using namespace std;

Groupe::Groupe(SDL_Renderer *ecran)
{
    largeur=LARGEUR;
    hauteur=HAUTEUR;
    
    positionMenu.x=0;
    positionMenu.y=0;
    fenMenu = SDL_CreateTexture(ecran,
                               SDL_PIXELFORMAT_ARGB8888,
                               SDL_TEXTUREACCESS_STREAMING,
                               largeur, hauteur);
    
    SDL_AudioSpec spec;
    spec.freq = MIX_DEFAULT_FREQUENCY;
    spec.format = MIX_DEFAULT_FORMAT;
    spec.channels = MIX_DEFAULT_CHANNELS;
    int channelNumber = 4;
    if (Mix_OpenAudio(MIX_DEFAULT_FREQUENCY, MIX_DEFAULT_FORMAT, MIX_DEFAULT_CHANNELS, 15) < 0) {
        SDL_Log("Couldn't open audio: %s\n", SDL_GetError());
        exit(2);
    } else {
        Mix_QuerySpec(&spec.freq, &spec.format, &channelNumber);
        SDL_Log("Opened audio at %d Hz %d bit%s %s audio buffer\n", spec.freq,
            (spec.format&0xFF),
            (SDL_AUDIO_ISFLOAT(spec.format) ? " (float)" : ""),
            (spec.channels > 2) ? "surround" : (spec.channels > 1) ? "stereo" : "mono");
    }

     /* Set the music volume */
    Mix_VolumeMusic(MIX_MAX_VOLUME);

    Mix_Music *music = NULL;
    sonDeplacement = Mix_LoadWAV("deplacement.mp3");
    sonValidation = Mix_LoadWAV("validation.wav");
    sonAnnulation = Mix_LoadWAV("annulation.wav");
}

Groupe:: ~Groupe()
{
    Mix_FreeChunk(sonDeplacement);
    Mix_FreeChunk(sonValidation);
    Mix_FreeChunk(sonAnnulation);
}

void Groupe::AffichageGroupe(std::vector<Personnage*> groupe, std::vector<Personnage*> equipe, SDL_Renderer *ecran, Jeu *obj)
{
    int cycle=1, init=0, i=0, t=0, j=0, taille=0, membre=0, nb=0, cpt=0, k=0, l=0, m=0, n=0, flag=0, bas=0, haut=0, gauche=0, droite=0, arm=0, cuir=0, bouc=0, jamb=0;
    taille=equipe.size();
    int maxPv[taille], maxPm[taille], pv[taille], pm[taille], niv[taille];
    string prenom[taille];
    init=TTF_Init();
    if(init == -1)
    {
        fprintf(stderr, "Erreur d'initialisation de TTF_Init : %s\n", TTF_GetError());
        exit(EXIT_FAILURE);
        atexit(TTF_Quit);
    }
    police = TTF_OpenFont("arial.ttf", 30);
    police2 = TTF_OpenFont("arial.ttf", 20);
    couleurCarac = {255, 255, 255};
    couleurAjout={255, 255, 0};

    positionCursseur.w=largeur/2;
    positionCursseur.h=100;
    positionCursseur.x=0;
    positionCursseur.y=45;

    for(i=0; i<taille; i++)
    {
        int statTextWidth = 0;
        int statTextHeight = 0;
        positionTof[i].x =0;
        positionTof[i].w = 64;
        positionTof[i].h = 64;
        positionTofGroupe[i].x =largeur/2;
        positionTofGroupe[i].w = 64;
        positionTofGroupe[i].h = 64;
        prenom[i]=equipe[i]->GetPrenom();
        pv[i]=equipe[i]->GetPv();
        pm[i]=equipe[i]->GetPm();
        maxPv[i]=equipe[i]->GetMaxPv();
        maxPm[i]=equipe[i]->GetMaxPm();
        niv[i]=equipe[i]->GetNiv();
        sprintf(tableauPv, "PV : %d / %d", pv[i], maxPv[i]);
        sprintf(tableauPm, "PM : %d / %d", pm[i], maxPm[i]);
        sprintf(tableauNiv, "Niveau : %d", niv[i]);
        positionTexteStatPrenom[i].x=70;
        texteStatPrenom[i] = SDL_CreateTextureFromSurface(ecran, TTF_RenderText_Blended(police2, prenom[i].c_str(), couleurCarac));
        TTF_SizeText(police2, prenom[i].c_str(), &statTextWidth, &statTextHeight);
        positionTexteStatPrenom[i].w = statTextWidth;
        positionTexteStatPrenom[i].h = statTextHeight;
        positionTexteStatNiv[i].x=70;
        texteStatNiv[i] = SDL_CreateTextureFromSurface(ecran, TTF_RenderText_Blended(police2, tableauNiv, couleurCarac));
        TTF_SizeText(police2, tableauNiv, &statTextWidth, &statTextHeight);
        positionTexteStatNiv[i].w = statTextWidth;
        positionTexteStatNiv[i].h = statTextHeight;
        positionTexteStatPv[i].x=70;
        texteStatPv[i] = SDL_CreateTextureFromSurface(ecran, TTF_RenderText_Blended(police2, tableauPv, couleurCarac));
        TTF_SizeText(police2, tableauPv, &statTextWidth, &statTextHeight);
        positionTexteStatPv[i].w = statTextWidth;
        positionTexteStatPv[i].h = statTextHeight;
        positionTexteStatPm[i].x=70;
        texteStatPm[i] = SDL_CreateTextureFromSurface(ecran, TTF_RenderText_Blended(police2, tableauPm, couleurCarac));
        TTF_SizeText(police2, tableauPm, &statTextWidth, &statTextHeight);
        positionTexteStatPm[i].w = statTextWidth;
        positionTexteStatPm[i].h = statTextHeight;
        
        if(i==MEMBRE1)
        {
            positionTof[i].y = 45;
            positionTofGroupe[i].y = 195;
            positionTexteStatPrenom[i].y=45;
            positionTexteStatNiv[i].y=70;
            positionTexteStatPv[i].y=95;
            positionTexteStatPm[i].y=120;
        }
        else if(i==MEMBRE2)
        {
            positionTof[i].y = 150;
            positionTofGroupe[i].y = 245;
            positionTexteStatPrenom[i].y=150;
            positionTexteStatNiv[i].y=175;
            positionTexteStatPv[i].y=200;
            positionTexteStatPm[i].y=225;
        }
        else if(i==MEMBRE3)
        {
            positionTof[i].y = 255;
            positionTofGroupe[i].y = 300;
            positionTexteStatPrenom[i].y=255;
            positionTexteStatNiv[i].y=280;
            positionTexteStatPv[i].y=305;
            positionTexteStatPm[i].y=330;
        }
        else if(i==MEMBRE4)
        {
            positionTof[i].y = 360;
            positionTofGroupe[i].y = 350;
            positionTexteStatPrenom[i].y=360;
            positionTexteStatNiv[i].y=385;
            positionTexteStatPv[i].y=410;
            positionTexteStatPm[i].y=435;
        }
        
    }

    positionLigne.x = largeur/2;
    positionLigne.y = 0;
    positionLigne.w = 2;
    positionLigne.h = hauteur;

    for(i=0; i<2; i++)
    {
        if(i==0)
        {
            positionLigneHorizontale[i].x = 0;
            positionLigneHorizontale[i].y = 40;
            positionLigneHorizontale[i].w = largeur;
            positionLigneHorizontale[i].h = 2;
        }
        else
        {
            positionLigneHorizontale[i].x = largeur/2;
            positionLigneHorizontale[i].y = 143;
            positionLigneHorizontale[i].w = largeur/2;
            positionLigneHorizontale[i].h = 2;
        }
        
    }

    
    positionTitreMenu.x=0;
    positionTitreMenu.y=0;
    titreMenu = SDL_CreateTextureFromSurface(ecran, TTF_RenderText_Blended(police, "Groupe", couleurCarac));
    int titreMenuWidth = 0; 
    int titreMenuHeight = 0;
    TTF_SizeText(police, "Groupe", &titreMenuWidth, &titreMenuHeight);
    positionTitreMenu.w = titreMenuWidth;
    positionTitreMenu.h = titreMenuHeight;

    tof = SDL_CreateTextureFromSurface(ecran, IMG_Load("tof.png"));


    tofGroupe = SDL_CreateTextureFromSurface(ecran, IMG_Load("tofGroupe.png"));
    

    clipGroupe[MEMBRE1].x=0;
    clipGroupe[MEMBRE1].y=0;
    clipGroupe[MEMBRE1].w=192/4;
    clipGroupe[MEMBRE1].h=192/4;

    clipGroupe[MEMBRE2].x=3*192/4;
    clipGroupe[MEMBRE2].y=0;
    clipGroupe[MEMBRE2].w=192/4;
    clipGroupe[MEMBRE2].h=192/4;

    clipGroupe[MEMBRE3].x=2*192/4;
    clipGroupe[MEMBRE3].y=0;
    clipGroupe[MEMBRE3].w=192/4;
    clipGroupe[MEMBRE3].h=192/4;

    clipGroupe[MEMBRE4].x=1*192/4;
    clipGroupe[MEMBRE4].y=0;
    clipGroupe[MEMBRE4].w=192/4;
    clipGroupe[MEMBRE4].h=192/4;

    clip[MEMBRE1].x=0;
    clip[MEMBRE1].y=0;
    clip[MEMBRE1].w=192/4;
    clip[MEMBRE1].h=192/4;

    clip[MEMBRE2].x=3*192/4;
    clip[MEMBRE2].y=0;
    clip[MEMBRE2].w=192/4;
    clip[MEMBRE2].h=192/4;

    clip[MEMBRE3].x=2*192/4;
    clip[MEMBRE3].y=0;
    clip[MEMBRE3].w=192/4;
    clip[MEMBRE3].h=192/4;

    clip[MEMBRE4].x=1*192/4;
    clip[MEMBRE4].y=0;
    clip[MEMBRE4].w=192/4;
    clip[MEMBRE4].h=192/4;

    if(!tof)
    {
        fprintf(stderr, "Erreur de chargement de l'image tof.png : %s\n", SDL_GetError()); // Écriture de l'erreur
        exit(EXIT_FAILURE);
    }

    if(!tofGroupe)
    {
        fprintf(stderr, "Erreur de chargement de l'image tofGroupe.png : %s\n", SDL_GetError()); // Écriture de l'erreur
        exit(EXIT_FAILURE);
    }

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
                this->EmissionSonAnnulation();

                break;

                case SDLK_SPACE:
                break;

                case SDLK_RETURN:

                break;

                case SDLK_UP:

                if(positionCursseur.y==positionTof[taille-1].y)
                {
                    membre=taille-1;
                    positionCursseur.y=positionTof[--membre].y;
                    this->EmissionSonDeplacement();
                }
                else if(positionCursseur.y==positionTof[MEMBRE1].y)
                {
                    positionCursseur.y=positionTof[taille-1].y;
                    membre=taille-1;
                    this->EmissionSonDeplacement();
                }
                else
                {
                    positionCursseur.y=positionTof[--membre].y;
                    this->EmissionSonDeplacement();
                }
                break;

                case SDLK_DOWN:

                if(positionCursseur.y==positionTof[taille-1].y)
                {
                    membre=MEMBRE1;
                    positionCursseur.y=positionTof[membre].y;
                    this->EmissionSonDeplacement();
                }
                else if(positionCursseur.y==positionTof[MEMBRE1].y)
                {
                    positionCursseur.y=positionTof[++membre].y;
                    this->EmissionSonDeplacement();
                }
                else
                {
                    positionCursseur.y=positionTof[++membre].y;
                    this->EmissionSonDeplacement();
                }
                break;

                case SDLK_RIGHT:

                break;

                default:
                cout<<"ok"<<endl;
                break;
            }
            break;
        }

        DisplayMenuElements(equipe, ecran);
    }

}

void Groupe::DisplayMenuElements(std::vector<Personnage*> equipe, SDL_Renderer *ecran)
{
    SDL_SetRenderDrawColor(ecran, 180, 180, 180, SDL_ALPHA_OPAQUE );
    SDL_RenderClear(ecran);
    SDL_RenderCopy(ecran, fenMenu, NULL, &positionMenu);

    SDL_SetRenderDrawBlendMode(ecran, SDL_BLENDMODE_BLEND);
    SDL_SetRenderDrawColor(ecran, 255, 255, 36, 70 );
    SDL_RenderFillRect(ecran, &positionCursseur);

    for(int i = 0; i < equipe.size(); i++)
    {
        SDL_RenderCopy(ecran, tof, &clip[i], &positionTof[i]);
        SDL_RenderCopy(ecran, tofGroupe, &clipGroupe[i], &positionTofGroupe[i]);
        SDL_RenderCopy(ecran, texteStatPrenom[i], NULL, &positionTexteStatPrenom[i]);
        SDL_RenderCopy(ecran, texteStatNiv[i], NULL, &positionTexteStatNiv[i]);
        SDL_RenderCopy(ecran, texteStatPv[i], NULL, &positionTexteStatPv[i]);
        SDL_RenderCopy(ecran, texteStatPm[i], NULL, &positionTexteStatPm[i]);
        
    }

    SDL_SetRenderDrawColor(ecran, 255, 255, 255, SDL_ALPHA_OPAQUE);
    SDL_RenderFillRect(ecran, &positionLigne);

    for(int i = 0; i < 2; i++)
    {
        SDL_SetRenderDrawColor(ecran, 255, 255, 255, SDL_ALPHA_OPAQUE);
        SDL_RenderFillRect(ecran, &positionLigneHorizontale[i]);  
    }

    SDL_RenderCopy(ecran, titreMenu, NULL, &positionTitreMenu);

    SDL_RenderPresent(ecran);
}

