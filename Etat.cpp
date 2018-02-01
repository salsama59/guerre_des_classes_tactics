#include <cstdlib>
#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include <ft2build.h>
#include <SDL/SDL_ttf.h>
#include <fmodex/fmod.h>
#include "Etat.h"
#include "Arme.h"
#include "Jeu.h"
#include "Menu.h"
#include "Personnage.h"
#include "Equipement.h"
#include <string>
#include <iostream>
#include <vector>
using namespace std;

Etat::Etat(SDL_Surface *ecran) : Menu()
{
    largeur=640;
    hauteur=480;
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

/*
Etat:: ~Etat()
{

}

*/
void Etat::AffichageEtat(std::vector<Personnage*> equipe, SDL_Surface *ecran)
{
    int cycle=1, init=0, i=0, t=0, j=0, taille=0, membre=0;
    float esq[taille], prc[taille];
    int pv[taille], pm[taille], exp[taille], suivant[taille], maxPv[taille], maxPm[taille], niv[taille], fr[taille], def[taille], mag[taille], vol[taille], vit[taille], cha[taille];
    taille=equipe.size();
    string nom[taille], prenom[taille], nomArme[taille], nomArmure[4];
    std::vector<Equipement> e;
    std::vector<Arme> a;
    init=TTF_Init();
    if(init == -1)
    {
        fprintf(stderr, "Erreur d'initialisation de TTF_Init : %s\n", TTF_GetError());
        exit(EXIT_FAILURE);
        atexit(TTF_Quit);
    }
    police = TTF_OpenFont("arial.ttf", 25);
    couleurCarac = {255, 255, 255};
    //TTF_SetFontStyle(police, TTF_STYLE_BOLD);
    for(i=0; i <taille; i++)
    {
        niv[i]=equipe[i]->GetNiv();
        prenom[i]=equipe[i]->GetPrenom();
        pv[i]=equipe[i]->GetPv();
        pm[i]=equipe[i]->GetPm();
        maxPv[i]=equipe[i]->GetMaxPv();
        maxPm[i]=equipe[i]->GetMaxPm();
        exp[i]=equipe[i]->GetExp();
        suivant[i]=equipe[i]->GetSeuil();
        fr[i]=equipe[i]->GetFr();
        def[i]=equipe[i]->GetDef();
        mag[i]=equipe[i]->GetMag();
        vol[i]=equipe[i]->GetVol();
        vit[i]=equipe[i]->GetVit();
        esq[i]=equipe[i]->GetEsq();
        prc[i]=equipe[i]->GetPrc();
        cha[i]=equipe[i]->GetCha();
        nom[i]=equipe[i]->GetNom();
        a.push_back(equipe[i]->GetArmeEquipe());
        e=equipe[i]->GetArmureEquipe();
        for(j=0; j<e.size(); j++)
        {
            if(i==0)
            {
                if(j==0)
                {
                    nomArmure[j]=e[j].GetNom();
                    texteStatNomArmureM0[j] = TTF_RenderText_Blended(police, nomArmure[j].c_str(), couleurCarac);
                    positionTexteStatNomArmure[j].x=450;
                    positionTexteStatNomArmure[j].y=130;

                }
                else if(j>0)
                {
                    nomArmure[j]=e[j].GetNom();
                    texteStatNomArmureM0[j] = TTF_RenderText_Blended(police, nomArmure[j].c_str(), couleurCarac);
                    positionTexteStatNomArmure[j].x=450;
                    positionTexteStatNomArmure[j].y=positionTexteStatNomArmure[j-1].y+30;

                }
            }
            if(i==1)
            {

                if(j==0)
                {
                    nomArmure[j]=e[j].GetNom();
                    texteStatNomArmureM1[j] = TTF_RenderText_Blended(police, nomArmure[j].c_str(), couleurCarac);
                    positionTexteStatNomArmure[j].x=450;
                    positionTexteStatNomArmure[j].y=130;

                }
                else if(j>0)
                {
                    nomArmure[j]=e[j].GetNom();
                    texteStatNomArmureM1[j] = TTF_RenderText_Blended(police, nomArmure[j].c_str(), couleurCarac);
                    positionTexteStatNomArmure[j].x=450;
                    positionTexteStatNomArmure[j].y=positionTexteStatNomArmure[j-1].y+30;

                }
            }
        }
        nomArme[i]=a[i].GetNom();
        sprintf(tableauPv, "PV : %d / %d", pv[i], maxPv[i]);
        sprintf(tableauPm, "PM : %d / %d", pm[i], maxPm[i]);
        sprintf(tableauExp, "Experience %d / %d", exp[i], suivant[i]);
        sprintf(tableauNiv, "Niveau : %d", niv[i]);
        sprintf(tableauFr, "Force : %d", fr[i]);
        sprintf(tableauMag, "Magie : %d", mag[i]);
        sprintf(tableauDef, "Defense : %d", def[i]);
        sprintf(tableauVol, "Volonte : %d", vol[i]);
        sprintf(tableauVit, "Vitesse : %d", vit[i]);
        sprintf(tableauEsq, "Esquive : %.2f %", esq[i]);
        sprintf(tableauPrc, "Precision : %.2f %", prc[i]);
        sprintf(tableauCha, "Chance : %d", cha[i]);

        texteStatNom [i]= TTF_RenderText_Blended(police, nom[i].c_str(), couleurCarac);
        positionTexteStatNom[i].x=450;
        positionTexteStatNom[i].y=20;

        texteStatPrenom [i]= TTF_RenderText_Blended(police, prenom[i].c_str(), couleurCarac);
        positionTexteStatPrenom[i].x=450;
        positionTexteStatPrenom[i].y=40;

        texteStatNiv [i]= TTF_RenderText_Blended(police, tableauNiv, couleurCarac);
        positionTexteStatNiv[i].x=450;
        positionTexteStatNiv[i].y=60;

        texteStatPv [i]= TTF_RenderText_Blended(police, tableauPv, couleurCarac);
        positionTexteStatPv[i].x=0;
        positionTexteStatPv[i].y=0;

        texteStatPm [i]= TTF_RenderText_Blended(police, tableauPm, couleurCarac);
        positionTexteStatPm[i].x=0;
        positionTexteStatPm[i].y=hauteur/11;

        texteStatExp [i]= TTF_RenderText_Blended(police, tableauExp, couleurCarac);
        positionTexteStatExp[i].x=0;
        positionTexteStatExp[i].y=2*hauteur/11;

        texteStatFr [i]= TTF_RenderText_Blended(police, tableauFr, couleurCarac);
        positionTexteStatFr[i].x=0;
        positionTexteStatFr[i].y=3*hauteur/11;

        texteStatDef [i]= TTF_RenderText_Blended(police, tableauDef, couleurCarac);
        positionTexteStatDef[i].x=0;
        positionTexteStatDef[i].y=4*hauteur/11;

        texteStatMag [i]= TTF_RenderText_Blended(police, tableauMag, couleurCarac);
        positionTexteStatMag[i].x=0;
        positionTexteStatMag[i].y=5*hauteur/11;

        texteStatVol [i]= TTF_RenderText_Blended(police, tableauVol, couleurCarac);
        positionTexteStatVol[i].x=0;
        positionTexteStatVol[i].y=6*hauteur/11;

        texteStatVit [i]= TTF_RenderText_Blended(police, tableauVit, couleurCarac);
        positionTexteStatVit[i].x=0;
        positionTexteStatVit[i].y=7*hauteur/11;

        texteStatPrc [i]= TTF_RenderText_Blended(police, tableauPrc, couleurCarac);
        positionTexteStatPrc[i].x=0;
        positionTexteStatPrc[i].y=8*hauteur/11;

        texteStatEsq [i]= TTF_RenderText_Blended(police, tableauEsq, couleurCarac);
        positionTexteStatEsq[i].x=0;
        positionTexteStatEsq[i].y=9*hauteur/11;

        texteStatCha [i]= TTF_RenderText_Blended(police, tableauCha, couleurCarac);
        positionTexteStatCha[i].x=0;
        positionTexteStatCha[i].y=10*hauteur/11;

        texteStatNomArme [i]= TTF_RenderText_Blended(police, nomArme[i].c_str(), couleurCarac);
        positionTexteStatNomArme[i].x=420;
        positionTexteStatNomArme[i].y=100;
    }
    const char* tableauEquip[5]= {"Arme :", "Casque :", "Cuirasse :", "Bouclier :", "Jambiere :"};

    for(i=0; i<5; i++)
    {
        if(i==0)
        {
            texteEquipement[i] = TTF_RenderText_Blended(police, tableauEquip[i], couleurCarac);
            positionTexteEquipement[i].x=325;
            positionTexteEquipement[i].y=100;
        }
        else
        {
            texteEquipement[i] = TTF_RenderText_Blended(police, tableauEquip[i], couleurCarac);
            positionTexteEquipement[i].x=325;
            positionTexteEquipement[i].y=positionTexteEquipement[i-1].y+30;
        }
    }
    positionTof.x = (largeur/2);
    positionTof.y = 20;
    tof = IMG_Load("tof.png");
    clip[0].x=0;
    clip[0].y=0;
    clip[0].w=192/4;
    clip[0].h=192/4;

    clip[1].x=3*192/4;
    clip[1].y=0;
    clip[1].w=192/4;
    clip[1].h=192/4;

    if(!tof)
    {
        fprintf(stderr, "Erreur de chargement de l'image tof.png : %s\n", SDL_GetError()); // Écriture de l'erreur
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

                case SDLK_UP:
                break;

                case SDLK_DOWN:
                break;

                case SDLK_RIGHT:
                if(membre==(taille-1))
                {
                    membre=MEMBRE1;
                }
                else
                {
                     membre++;
                }
                this->EmissionSonDeplacement();
                break;

                case SDLK_LEFT:
                if(membre==MEMBRE1)
                {
                    membre=taille-1;
                }
                else
                {
                     membre--;
                }
                this->EmissionSonDeplacement();
                break;
            }
            break;
        }
        // Collage de la surface de menu sur l'écran
        SDL_BlitSurface(fenMenu, NULL, ecran, &positionMenu);
        SDL_BlitSurface(texteStatPv[membre], NULL, ecran, &positionTexteStatPv[membre]);
        SDL_BlitSurface(texteStatPm[membre], NULL, ecran, &positionTexteStatPm[membre]);
        SDL_BlitSurface(texteStatExp[membre], NULL, ecran, &positionTexteStatExp[membre]);
        SDL_BlitSurface(texteStatFr[membre], NULL, ecran, &positionTexteStatFr[membre]);
        SDL_BlitSurface(texteStatDef[membre], NULL, ecran, &positionTexteStatDef[membre]);
        SDL_BlitSurface(texteStatMag[membre], NULL, ecran, &positionTexteStatMag[membre]);
        SDL_BlitSurface(texteStatVol[membre], NULL, ecran, &positionTexteStatVol[membre]);
        SDL_BlitSurface(texteStatVit[membre], NULL, ecran, &positionTexteStatVit[membre]);
        SDL_BlitSurface(texteStatPrc[membre], NULL, ecran, &positionTexteStatPrc[membre]);
        SDL_BlitSurface(texteStatEsq[membre], NULL, ecran, &positionTexteStatEsq[membre]);
        SDL_BlitSurface(texteStatCha[membre], NULL, ecran, &positionTexteStatCha[membre]);
        SDL_BlitSurface(texteStatPrenom[membre], NULL, ecran, &positionTexteStatPrenom[membre]);
        SDL_BlitSurface(texteStatNom[membre], NULL, ecran, &positionTexteStatNom[membre]);
        SDL_BlitSurface(texteStatNiv[membre], NULL, ecran, &positionTexteStatNiv[membre]);
        SDL_BlitSurface(texteStatNomArme[membre], NULL, ecran, &positionTexteStatNomArme[membre]);

        if(membre==0)
        {
            for(i=0; i<e.size(); i++)
            {
               SDL_BlitSurface(texteStatNomArmureM0[i], NULL, ecran, &positionTexteStatNomArmure[i]);
            }
        }
        if(membre==1)
        {
            for(i=0; i<e.size(); i++)
            {
               SDL_BlitSurface(texteStatNomArmureM1[i], NULL, ecran, &positionTexteStatNomArmure[i]);
            }
        }

        for(i=0; i<5; i++)
        {
            SDL_BlitSurface(texteEquipement[i], NULL, ecran, &positionTexteEquipement[i]);
        }
        SDL_BlitSurface(tof, &clip[membre], ecran, &positionTof);
        //Mise à jour de l'affichage
        SDL_Flip(ecran);
    }
}
