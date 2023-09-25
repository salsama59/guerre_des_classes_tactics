#include <cstdlib>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <ft2build.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_mixer.h>
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

Etat::Etat(SDL_Renderer *ecran) : Menu()
{
    largeur=640;
    hauteur=480;
    fenMenu = SDL_CreateTexture(ecran,
                               SDL_PIXELFORMAT_ARGB8888,
                               SDL_TEXTUREACCESS_STREAMING,
                               largeur, hauteur);
    positionMenu.x=0;
    positionMenu.y=0;

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

/*
Etat:: ~Etat()
{

}

*/
void Etat::AffichageEtat(std::vector<Personnage*> equipe, SDL_Renderer *ecran)
{
    int cycle=1, init=0, i=0, t=0, j=0, taille=0, membre=0;
    taille=equipe.size();
    float esq[taille], prc[taille];
    int pv[taille], pm[taille], exp[taille], suivant[taille], maxPv[taille], maxPm[taille], niv[taille], fr[taille], def[taille], mag[taille], vol[taille], vit[taille], cha[taille];
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
            nomArmure[j]=e[j].GetNom();
            positionTexteStatNomArmure[j].x=450;
            if(j==0)
            {
                positionTexteStatNomArmure[j].y=130;
            }
            else if(j>0)
            {
                positionTexteStatNomArmure[j].y=positionTexteStatNomArmure[j-1].y+30;
            }

            int texteStatNomArmureWidth = 0; 
            int texteStatNomArmureHeight = 0;
            TTF_SizeText(police, nomArmure[j].c_str(), &texteStatNomArmureWidth, &texteStatNomArmureHeight);
            positionTexteStatNomArmure[j].w = texteStatNomArmureWidth;
            positionTexteStatNomArmure[j].h = texteStatNomArmureHeight;

            if(i==MEMBRE1)
            {
                texteStatNomArmureM0[j] = SDL_CreateTextureFromSurface(ecran, TTF_RenderText_Blended(police, nomArmure[j].c_str(), couleurCarac));
            }

            if(i==MEMBRE2)
            {
                texteStatNomArmureM1[j] = SDL_CreateTextureFromSurface(ecran, TTF_RenderText_Blended(police, nomArmure[j].c_str(), couleurCarac));
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

        /*texte[i] = SDL_CreateTextureFromSurface(ecran, TTF_RenderText_Blended(police, nom[i].c_str(), couleurCarac));
        int texteWidth = 0; 
        int texteHeight = 0;
        TTF_SizeText(police, nom[i].c_str(), &texteWidth, &texteHeight);
        positionTexte[i].w = texteWidth;
        positionTexte[i].h = texteHeight;
        positionTexte[i].x=0;
        positionTexte[i].y=i*50;*/
        
        texteStatNom[i] = SDL_CreateTextureFromSurface(ecran, TTF_RenderText_Blended(police, nom[i].c_str(), couleurCarac));
        int texteStatNomWidth = 0; 
        int texteStatNomHeight = 0;
        TTF_SizeText(police, nom[i].c_str(), &texteStatNomWidth, &texteStatNomHeight);
        positionTexteStatNom[i].w = texteStatNomWidth;
        positionTexteStatNom[i].h = texteStatNomHeight;
        positionTexteStatNom[i].x=450;
        positionTexteStatNom[i].y=20;

        texteStatPrenom[i] = SDL_CreateTextureFromSurface(ecran, TTF_RenderText_Blended(police, prenom[i].c_str(), couleurCarac));
        int texteStatPrenomWidth = 0; 
        int texteStatPrenomHeight = 0;
        TTF_SizeText(police, prenom[i].c_str(), &texteStatPrenomWidth, &texteStatPrenomHeight);
        positionTexteStatPrenom[i].w = texteStatPrenomWidth;
        positionTexteStatPrenom[i].h = texteStatPrenomHeight;
        positionTexteStatPrenom[i].x=450;
        positionTexteStatPrenom[i].y=40;

        texteStatNiv[i] = SDL_CreateTextureFromSurface(ecran, TTF_RenderText_Blended(police, tableauNiv, couleurCarac));
        int texteStatNivWidth = 0; 
        int texteStatNivHeight = 0;
        TTF_SizeText(police, tableauNiv, &texteStatNivWidth, &texteStatNivHeight);
        positionTexteStatNiv[i].w = texteStatNivWidth;
        positionTexteStatNiv[i].h = texteStatNivHeight;
        positionTexteStatNiv[i].x=450;
        positionTexteStatNiv[i].y=60;

        texteStatPv[i] = SDL_CreateTextureFromSurface(ecran, TTF_RenderText_Blended(police, tableauPv, couleurCarac));
        int texteStatPvWidth = 0; 
        int texteStatPvHeight = 0;
        TTF_SizeText(police, tableauPv, &texteStatPvWidth, &texteStatPvHeight);
        positionTexteStatPv[i].w = texteStatPvWidth;
        positionTexteStatPv[i].h = texteStatPvHeight;
        positionTexteStatPv[i].x=0;
        positionTexteStatPv[i].y=0;
        
        texteStatPm[i] = SDL_CreateTextureFromSurface(ecran, TTF_RenderText_Blended(police, tableauPm, couleurCarac));
        int texteStatPmWidth = 0; 
        int texteStatPmHeight = 0;
        TTF_SizeText(police, tableauPm, &texteStatPmWidth, &texteStatPmHeight);
        positionTexteStatPm[i].w = texteStatPmWidth;
        positionTexteStatPm[i].h = texteStatPmHeight;
        positionTexteStatPm[i].x=0;
        positionTexteStatPm[i].y=hauteur/11;

        texteStatExp[i] = SDL_CreateTextureFromSurface(ecran, TTF_RenderText_Blended(police, tableauExp, couleurCarac));
        int texteStatExpWidth = 0; 
        int texteStatExpHeight = 0;
        TTF_SizeText(police, tableauExp, &texteStatExpWidth, &texteStatExpHeight);
        positionTexteStatExp[i].w = texteStatExpWidth;
        positionTexteStatExp[i].h = texteStatExpHeight;
        positionTexteStatExp[i].x=0;
        positionTexteStatExp[i].y=2*hauteur/11;

        texteStatFr[i] = SDL_CreateTextureFromSurface(ecran, TTF_RenderText_Blended(police, tableauFr, couleurCarac));
        int texteStatFrWidth = 0; 
        int texteStatFrHeight = 0;
        TTF_SizeText(police, tableauFr, &texteStatFrWidth, &texteStatFrHeight);
        positionTexteStatFr[i].w = texteStatFrWidth;
        positionTexteStatFr[i].h = texteStatFrHeight;
        positionTexteStatFr[i].x=0;
        positionTexteStatFr[i].y=3*hauteur/11;

        texteStatDef[i] = SDL_CreateTextureFromSurface(ecran, TTF_RenderText_Blended(police, tableauDef, couleurCarac));
        int texteStatDefWidth = 0; 
        int texteStatDefHeight = 0;
        TTF_SizeText(police, tableauDef, &texteStatDefWidth, &texteStatDefHeight);
        positionTexteStatDef[i].w = texteStatDefWidth;
        positionTexteStatDef[i].h = texteStatDefHeight;
        positionTexteStatDef[i].x=0;
        positionTexteStatDef[i].y=4*hauteur/11;
        
        texteStatMag[i] = SDL_CreateTextureFromSurface(ecran, TTF_RenderText_Blended(police, tableauMag, couleurCarac));
        int texteStatMagWidth = 0; 
        int texteStatMagHeight = 0;
        TTF_SizeText(police, tableauMag, &texteStatMagWidth, &texteStatMagHeight);
        positionTexteStatMag[i].w = texteStatMagWidth;
        positionTexteStatMag[i].h = texteStatMagHeight;
        positionTexteStatMag[i].x=0;
        positionTexteStatMag[i].y=5*hauteur/11;
        
        texteStatVol[i] = SDL_CreateTextureFromSurface(ecran, TTF_RenderText_Blended(police, tableauVol, couleurCarac));
        int texteStatVolWidth = 0; 
        int texteStatVolHeight = 0;
        TTF_SizeText(police, tableauVol, &texteStatVolWidth, &texteStatVolHeight);
        positionTexteStatVol[i].w = texteStatVolWidth;
        positionTexteStatVol[i].h = texteStatVolHeight;
        positionTexteStatVol[i].x=0;
        positionTexteStatVol[i].y=6*hauteur/11;
        
        texteStatVit[i] = SDL_CreateTextureFromSurface(ecran, TTF_RenderText_Blended(police, tableauVit, couleurCarac));
        int texteStatVitWidth = 0;
        int texteStatVitHeight = 0;
        TTF_SizeText(police, tableauVit, &texteStatVitWidth, &texteStatVitHeight);
        positionTexteStatVit[i].w = texteStatVitWidth;
        positionTexteStatVit[i].h = texteStatVitHeight;
        positionTexteStatVit[i].x=0;
        positionTexteStatVit[i].y=7*hauteur/11;

        texteStatPrc[i] = SDL_CreateTextureFromSurface(ecran, TTF_RenderText_Blended(police, tableauPrc, couleurCarac));
        int texteStatPrcWidth = 0;
        int texteStatPrcHeight = 0;
        TTF_SizeText(police, tableauPrc, &texteStatPrcWidth, &texteStatPrcHeight);
        positionTexteStatPrc[i].w = texteStatPrcWidth;
        positionTexteStatPrc[i].h = texteStatPrcHeight;
        positionTexteStatPrc[i].x=0;
        positionTexteStatPrc[i].y=8*hauteur/11;
    
        texteStatEsq[i] = SDL_CreateTextureFromSurface(ecran, TTF_RenderText_Blended(police, tableauEsq, couleurCarac));
        int texteStatEsqWidth = 0;
        int texteStatEsqHeight = 0;
        TTF_SizeText(police, tableauEsq, &texteStatEsqWidth, &texteStatEsqHeight);
        positionTexteStatEsq[i].w = texteStatEsqWidth;
        positionTexteStatEsq[i].h = texteStatEsqHeight;
        positionTexteStatEsq[i].x=0;
        positionTexteStatEsq[i].y=9*hauteur/11;

        texteStatCha[i] = SDL_CreateTextureFromSurface(ecran, TTF_RenderText_Blended(police, tableauCha, couleurCarac));
        int texteStatChaWidth = 0;
        int texteStatChaHeight = 0;
        TTF_SizeText(police, tableauCha, &texteStatChaWidth, &texteStatChaHeight);
        positionTexteStatCha[i].w = texteStatChaWidth;
        positionTexteStatCha[i].h = texteStatChaHeight;
        positionTexteStatCha[i].x=0;
        positionTexteStatCha[i].y=10*hauteur/11;

        texteStatNomArme[i] = SDL_CreateTextureFromSurface(ecran, TTF_RenderText_Blended(police, nomArme[i].c_str(), couleurCarac));
        int texteStatNomArmeWidth = 0;
        int texteStatNomArmeHeight = 0;
        TTF_SizeText(police, nomArme[i].c_str(), &texteStatNomArmeWidth, &texteStatNomArmeHeight);
        positionTexteStatNomArme[i].w = texteStatNomArmeWidth;
        positionTexteStatNomArme[i].h = texteStatNomArmeHeight;
        positionTexteStatNomArme[i].x=450;
        positionTexteStatNomArme[i].y=100;
        
    }
    const char* tableauEquip[5]= {"Arme :", "Casque :", "Cuirasse :", "Bouclier :", "Jambiere :"};

    for(i=0; i<5; i++)
    {
        if(i==0)
        {
            positionTexteEquipement[i].y=100;
        }
        else
        {
            positionTexteEquipement[i].y=positionTexteEquipement[i-1].y+30;
        }

        texteEquipement[i] = SDL_CreateTextureFromSurface(ecran,  TTF_RenderText_Blended(police, tableauEquip[i], couleurCarac));
        int texteEquipementWidth = 0;
        int texteEquipementHeight = 0;
        TTF_SizeText(police,  tableauEquip[i], &texteEquipementWidth, &texteEquipementHeight);
        positionTexteEquipement[i].w = texteEquipementWidth;
        positionTexteEquipement[i].h = texteEquipementHeight;
        positionTexteEquipement[i].x=325;
        
    }
    positionTof.x = (largeur/2);
    positionTof.y = 20;
    positionTof.w = 64;
    positionTof.h = 64;
    tof = SDL_CreateTextureFromSurface(ecran, IMG_Load("tof.png"));
    
    
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
        
        DisplayMenuElements(equipe, membre, ecran);
    }
}

void Etat::DisplayMenuElements(std::vector<Personnage*> equipe, int memberId, SDL_Renderer *ecran)
{
    SDL_SetRenderDrawColor(ecran, 180, 180, 180, SDL_ALPHA_OPAQUE );
    SDL_RenderClear(ecran);

    SDL_RenderCopy(ecran, fenMenu, NULL, &positionMenu);

    std::vector<Equipement> equipements = equipe[memberId]->GetArmureEquipe();

    for(int i = 0; i < equipements.size(); i++)
    {
        if(memberId == MEMBRE1)
        {
            SDL_RenderCopy(ecran, texteStatNomArmureM0[i], NULL, &positionTexteStatNomArmure[i]);
        }
        if(memberId == MEMBRE2)
        {
            SDL_RenderCopy(ecran, texteStatNomArmureM1[i], NULL, &positionTexteStatNomArmure[i]);
        }
 
    }

    
    SDL_RenderCopy(ecran, texteStatNom[memberId], NULL, &positionTexteStatNom[memberId]);
    SDL_RenderCopy(ecran, texteStatPrenom[memberId], NULL, &positionTexteStatPrenom[memberId]);
    SDL_RenderCopy(ecran, texteStatNiv[memberId], NULL, &positionTexteStatNiv[memberId]);
    SDL_RenderCopy(ecran, texteStatPv[memberId], NULL, &positionTexteStatPv[memberId]);
    SDL_RenderCopy(ecran, texteStatPm[memberId], NULL, &positionTexteStatPm[memberId]);
    SDL_RenderCopy(ecran, texteStatExp[memberId], NULL, &positionTexteStatExp[memberId]);
    SDL_RenderCopy(ecran, texteStatFr[memberId], NULL, &positionTexteStatFr[memberId]);
    SDL_RenderCopy(ecran, texteStatDef[memberId], NULL, &positionTexteStatDef[memberId]);
    SDL_RenderCopy(ecran, texteStatMag[memberId], NULL, &positionTexteStatMag[memberId]);
    SDL_RenderCopy(ecran, texteStatVol[memberId], NULL, &positionTexteStatVol[memberId]);
    SDL_RenderCopy(ecran, texteStatVit[memberId], NULL, &positionTexteStatVit[memberId]);
    SDL_RenderCopy(ecran, texteStatPrc[memberId], NULL, &positionTexteStatPrc[memberId]);
    SDL_RenderCopy(ecran, texteStatEsq[memberId], NULL, &positionTexteStatEsq[memberId]);
    SDL_RenderCopy(ecran, texteStatCha[memberId], NULL, &positionTexteStatCha[memberId]);
    SDL_RenderCopy(ecran, texteStatNomArme[memberId], NULL, &positionTexteStatNomArme[memberId]);
    

    for(int i = 0; i < 5; i++)
    {
        SDL_RenderCopy(ecran, texteEquipement[i], NULL, &positionTexteEquipement[i]);
    }

    SDL_RenderCopy(ecran, tof, &clip[memberId], &positionTof);

    SDL_RenderPresent(ecran);
}
