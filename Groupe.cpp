#include <cstdlib>
#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include <SDL/SDL_ttf.h>
#include <fmodex/fmod.h>
#include <ft2build.h>
#include "Groupe.h"
#include "Jeu.h"
#include "Lance.h"
#include "Gant.h"
#include <string>
#include <iostream>
#include <vector>
using namespace std;

Groupe::Groupe(SDL_Surface *ecran)
{
    largeur=LARGEUR;
    hauteur=HAUTEUR;
    couleur= SDL_MapRGB(ecran->format, 180, 180, 180);
    fenMenu = SDL_CreateRGBSurface(SDL_HWSURFACE, largeur, hauteur, NB_BITS_PAR_PIXEL, 0, 0, 0, 0);
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

Groupe:: ~Groupe()
{
    FMOD_System_Close(system);
    FMOD_System_Release(system);
    FMOD_Sound_Release(sonDeplacement);
    FMOD_Sound_Release(sonValidation);
}

void Groupe::AffichageGroupe(std::vector<Personnage*> groupe, std::vector<Personnage*> equipe, SDL_Surface *ecran, Jeu *obj)
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
    //TTF_SetFontStyle(police, TTF_STYLE_BOLD | TTF_STYLE_UNDERLINE | TTF_STYLE_ITALIC);
    couleurCursseur= SDL_MapRGB(ecran->format, 255, 255, 36);
    positionCursseur.w=largeur/2;
    positionCursseur.h=100;
    positionCursseur.x=0;
    positionCursseur.y=45;
    cursseur= SDL_CreateRGBSurface(SDL_HWSURFACE, positionCursseur.w, positionCursseur.h, NB_BITS_PAR_PIXEL, 0, 0, 0, 0);
    SDL_FillRect(cursseur, NULL, couleurCursseur);
    SDL_SetAlpha(cursseur, SDL_SRCALPHA, 70);



    for(i=0; i<taille; i++)
    {
        if(i==MEMBRE1)
        {
            positionTof[i].x =0;
            positionTof[i].y = 45;
            positionTofGroupe[i].x =largeur/2;
            positionTofGroupe[i].y = 195;
            prenom[i]=equipe[i]->GetPrenom();
            pv[i]=equipe[i]->GetPv();
            pm[i]=equipe[i]->GetPm();
            maxPv[i]=equipe[i]->GetMaxPv();
            maxPm[i]=equipe[i]->GetMaxPm();
            niv[i]=equipe[i]->GetNiv();
            sprintf(tableauPv, "PV : %d / %d", pv[i], maxPv[i]);
            sprintf(tableauPm, "PM : %d / %d", pm[i], maxPm[i]);
            sprintf(tableauNiv, "Niveau : %d", niv[i]);
            texteStatPrenom[i] = TTF_RenderText_Blended(police2, prenom[i].c_str(), couleurCarac);
            positionTexteStatPrenom[i].x=70;
            positionTexteStatPrenom[i].y=45;
            texteStatNiv[i] = TTF_RenderText_Blended(police2, tableauNiv, couleurCarac);
            positionTexteStatNiv[i].x=70;
            positionTexteStatNiv[i].y=70;
            texteStatPv[i] = TTF_RenderText_Blended(police2, tableauPv, couleurCarac);
            positionTexteStatPv[i].x=70;
            positionTexteStatPv[i].y=95;
            texteStatPm[i] = TTF_RenderText_Blended(police2, tableauPm, couleurCarac);
            positionTexteStatPm[i].x=70;
            positionTexteStatPm[i].y=120;
        }
        else if(i==MEMBRE2)
        {
            positionTof[i].x =0;
            positionTof[i].y = 150;
            positionTofGroupe[i].x =largeur/2;
            positionTofGroupe[i].y = 245;
            prenom[i]=equipe[i]->GetPrenom();
            pv[i]=equipe[i]->GetPv();
            pm[i]=equipe[i]->GetPm();
            maxPv[i]=equipe[i]->GetMaxPv();
            maxPm[i]=equipe[i]->GetMaxPm();
            niv[i]=equipe[i]->GetNiv();
            sprintf(tableauPv, "PV : %d / %d", pv[i], maxPv[i]);
            sprintf(tableauPm, "PM : %d / %d", pm[i], maxPm[i]);
            sprintf(tableauNiv, "Niveau : %d", niv[i]);
            texteStatPrenom[i] = TTF_RenderText_Blended(police2, prenom[i].c_str(), couleurCarac);
            positionTexteStatPrenom[i].x=70;
            positionTexteStatPrenom[i].y=150;
            texteStatNiv[i] = TTF_RenderText_Blended(police2, tableauNiv, couleurCarac);
            positionTexteStatNiv[i].x=70;
            positionTexteStatNiv[i].y=175;
            texteStatPv[i] = TTF_RenderText_Blended(police2, tableauPv, couleurCarac);
            positionTexteStatPv[i].x=70;
            positionTexteStatPv[i].y=200;
            texteStatPm[i] = TTF_RenderText_Blended(police2, tableauPm, couleurCarac);
            positionTexteStatPm[i].x=70;
            positionTexteStatPm[i].y=225;
        }
        else if(i==MEMBRE3)
        {
            positionTof[i].x =0;
            positionTof[i].y = 255;
            positionTofGroupe[i].x =largeur/2;
            positionTofGroupe[i].y = 300;
            prenom[i]=equipe[i]->GetPrenom();
            pv[i]=equipe[i]->GetPv();
            pm[i]=equipe[i]->GetPm();
            maxPv[i]=equipe[i]->GetMaxPv();
            maxPm[i]=equipe[i]->GetMaxPm();
            niv[i]=equipe[i]->GetNiv();
            sprintf(tableauPv, "PV : %d / %d", pv[i], maxPv[i]);
            sprintf(tableauPm, "PM : %d / %d", pm[i], maxPm[i]);
            sprintf(tableauNiv, "Niveau : %d", niv[i]);
            texteStatPrenom[i] = TTF_RenderText_Blended(police2, prenom[i].c_str(), couleurCarac);
            positionTexteStatPrenom[i].x=70;
            positionTexteStatPrenom[i].y=255;
            texteStatNiv[i] = TTF_RenderText_Blended(police2, tableauNiv, couleurCarac);
            positionTexteStatNiv[i].x=70;
            positionTexteStatNiv[i].y=280;
            texteStatPv[i] = TTF_RenderText_Blended(police2, tableauPv, couleurCarac);
            positionTexteStatPv[i].x=70;
            positionTexteStatPv[i].y=305;
            texteStatPm[i] = TTF_RenderText_Blended(police2, tableauPm, couleurCarac);
            positionTexteStatPm[i].x=70;
            positionTexteStatPm[i].y=330;
        }
        else if(i==MEMBRE4)
        {
            positionTof[i].x =0;
            positionTof[i].y = 360;
            positionTofGroupe[i].x =largeur/2;
            positionTofGroupe[i].y = 350;
            prenom[i]=equipe[i]->GetPrenom();
            pv[i]=equipe[i]->GetPv();
            pm[i]=equipe[i]->GetPm();
            maxPv[i]=equipe[i]->GetMaxPv();
            maxPm[i]=equipe[i]->GetMaxPm();
            niv[i]=equipe[i]->GetNiv();
            sprintf(tableauPv, "PV : %d / %d", pv[i], maxPv[i]);
            sprintf(tableauPm, "PM : %d / %d", pm[i], maxPm[i]);
            sprintf(tableauNiv, "Niveau : %d", niv[i]);
            texteStatPrenom[i] = TTF_RenderText_Blended(police2, prenom[i].c_str(), couleurCarac);
            positionTexteStatPrenom[i].x=70;
            positionTexteStatPrenom[i].y=360;
            texteStatNiv[i] = TTF_RenderText_Blended(police2, tableauNiv, couleurCarac);
            positionTexteStatNiv[i].x=70;
            positionTexteStatNiv[i].y=385;
            texteStatPv[i] = TTF_RenderText_Blended(police2, tableauPv, couleurCarac);
            positionTexteStatPv[i].x=70;
            positionTexteStatPv[i].y=410;
            texteStatPm[i] = TTF_RenderText_Blended(police2, tableauPm, couleurCarac);
            positionTexteStatPm[i].x=70;
            positionTexteStatPm[i].y=435;
        }
        else
        {

        }
    }


    positionLigne.x = largeur/2;
    positionLigne.y = 0;
    positionLigne.w = 2;
    positionLigne.h = hauteur;
    ligne= SDL_CreateRGBSurface(SDL_HWSURFACE, positionLigne.w, positionLigne.h, 32, 0, 0, 0, 0);
    couleurLigne= SDL_MapRGB(ecran->format, 255, 255, 255);
    SDL_FillRect(ligne, NULL, couleurLigne);

    for(i=0; i<2; i++)
    {
        if(i==0)
        {
            positionLigneHorizontale[i].x = 0;
            positionLigneHorizontale[i].y = 40;
            positionLigneHorizontale[i].w = largeur;
            positionLigneHorizontale[i].h = 2;
            ligneHorizontale[i]= SDL_CreateRGBSurface(SDL_HWSURFACE, positionLigneHorizontale[i].w, positionLigneHorizontale[i].h, 32, 0, 0, 0, 0);
            SDL_FillRect(ligneHorizontale[i], NULL, couleurLigne);
        }
        else
        {
            positionLigneHorizontale[i].x = largeur/2;
            positionLigneHorizontale[i].y = 143;
            positionLigneHorizontale[i].w = largeur/2;
            positionLigneHorizontale[i].h = 2;
            ligneHorizontale [i]= SDL_CreateRGBSurface(SDL_HWSURFACE, positionLigneHorizontale[i].w, positionLigneHorizontale[i].h, 32, 0, 0, 0, 0);
            SDL_FillRect(ligneHorizontale[i], NULL, couleurLigne);
        }
    }

    titreMenu=TTF_RenderText_Blended(police, "Groupe", couleurCarac);
    positionTitreMenu.x=0;
    positionTitreMenu.y=0;


    tof = IMG_Load("tof.png");
    tofGroupe = IMG_Load("tofGroupe.png");

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

        // Collage de la surface de menu sur l'écran
        SDL_BlitSurface(fenMenu, NULL, ecran, &positionMenu);
        SDL_BlitSurface(ligne, NULL, ecran, &positionLigne);
        for(i=0; i<taille; i++)
        {
            SDL_BlitSurface(texteStatPrenom[i], NULL, ecran, &positionTexteStatPrenom[i]);
            SDL_BlitSurface(texteStatPv[i], NULL, ecran, &positionTexteStatPv[i]);
            SDL_BlitSurface(texteStatPm[i], NULL, ecran, &positionTexteStatPm[i]);
            SDL_BlitSurface(texteStatNiv[i], NULL, ecran, &positionTexteStatNiv[i]);
            SDL_BlitSurface(tof, &clip[i], ecran, &positionTof[i]);
            SDL_BlitSurface(tofGroupe, &clipGroupe[i], ecran, &positionTofGroupe[i]);
        }


        for(i=0; i<2; i++)
        {
            SDL_BlitSurface(ligneHorizontale[i], NULL, ecran, &positionLigneHorizontale[i]);
        }



        SDL_BlitSurface(cursseur, NULL, ecran, &positionCursseur);
        SDL_BlitSurface(titreMenu, NULL, ecran, &positionTitreMenu);
        //Mise à jour de l'affichage
        SDL_Flip(ecran);
    }

}

