#include <cstdlib>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_mixer.h>
#include <ft2build.h>
#include "Menu.h"
#include "Jeu.h"
#include "Personnage.h"
#include "Etat.h"
#include "Groupe.h"
#include "SmenuEquipement.h"
#include <string>
#include <iostream>
#include <vector>
using namespace std;

Menu::Menu(Jeu &j)
{
    largeur=LARGEUR;
    hauteur=HAUTEUR;
    //Récupération du pointeur vers la fenêtre utilisé
    ecran=j.GetFen();
    //On définie les coordonnées du menu
    positionMenu.x=0;
    positionMenu.y=0;
    fenMenu = SDL_CreateTexture(ecran,
                               SDL_PIXELFORMAT_ARGB8888,
                               SDL_TEXTUREACCESS_STREAMING,
                               largeur, hauteur);
    //Initialisation de FMOD (création du système de son)
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

    sonDeplacement = Mix_LoadWAV("deplacement.mp3");

    if(sonDeplacement == NULL){
        SDL_Log("Couldn't open audio file %s : %s\n","deplacement.mp3", SDL_GetError());
        exit(2);
    }

    sonValidation = Mix_LoadWAV("validation.wav");

    if(sonValidation == NULL){
        SDL_Log("Couldn't open audio file %s : %s\n","validation.wav", SDL_GetError());
        exit(2);
    }

    sonAnnulation = Mix_LoadWAV("annulation.wav");

    if(sonAnnulation == NULL){
        SDL_Log("Couldn't open audio file %s : %s\n","annulation.wav", SDL_GetError());
        exit(2);
    }

    sonMenu = Mix_LoadWAV("Menu.mp3");

    if(sonMenu == NULL){
        SDL_Log("Couldn't open audio file %s : %s\n","Menu.mp3", SDL_GetError());
        exit(2);
    }
}

Menu::Menu()
{

}
//Destructeur de la classe Menu
Menu:: ~Menu()
{
    Mix_CloseAudio();
    Mix_FreeChunk(sonDeplacement);
    Mix_FreeChunk(sonValidation);
    Mix_FreeChunk(sonAnnulation);
    Mix_FreeChunk(sonMenu);
}

void Menu::EmissionSonDeplacement()
{
    SDL_Log("Playing %s\n", "deplacement.mp3");
    Mix_PlayChannel(0, sonDeplacement, 0);
}

void Menu::EmissionSonValidation()
{
    SDL_Log("Playing %s\n", "validation.wav");
    Mix_PlayChannel(0, sonValidation, 0);
}

void Menu::EmissionSonAnnulation()
{
    SDL_Log("Playing %s\n", "annulation.wav");
    Mix_PlayChannel(0, sonAnnulation, 0);
}

void Menu::EmissionSonMenu()
{
    SDL_Log("Playing %s\n", "Menu.mp3");
    Mix_PlayChannel(0, sonMenu, 0);
}

void Menu::AffichageMenu(std::vector<Personnage*> equipe, std::vector<Personnage*> groupe, SDL_Renderer *ecran, std::vector<Arme*> armeInventaire, std::vector<Casque*> casqueInventaire, std::vector<Cuirasse*> cuirasseInventaire, std::vector<Bouclier*> bouclierInventaire, std::vector<Jambiere*> jambiereInventaire, Jeu *obj)
{
    //On instancie un objet de type Etat
    Etat *e=new Etat(ecran);
    //On instancie un objet de type SmenuEquipement
    SmenuEquipement *sme=new SmenuEquipement(ecran);
    //On instancie un objet de type Groupe
    Groupe *g=new Groupe(ecran);

    int cycle=1, init=0, i=0, t=0, j=0, taille=0;
    //On définie la taille des tableaux
    taille=equipe.size();
    int pv[taille], pm[taille], exp[taille], suivant[taille], maxPv[taille], maxPm[taille], niv[taille];
    std::string prenom[taille];
    //Initialisation de la bibliothèque SDL_TTF
    init=TTF_Init();
    //En cas d'erreur
    if(init == -1)
    {
        //On récupère le descriptif de l'érreur et on l'affiche sur la sortie standard
        fprintf(stderr, "Erreur d'initialisation de TTF_Init : %s\n", TTF_GetError());
        exit(EXIT_FAILURE);
        atexit(TTF_Quit);
    }
    //Tableau contenant les intitulés de chaque sous menu
    const char* tab[9]= {"Inventaire", "Equipement", "Etat", "Groupe", "Competences", "Sauvegarder", "Charger", "Options", "Sortie"};
    vector<string> elements(9);
    t=elements.size();
    //on charge la police
    police = TTF_OpenFont("arial.ttf", 30);
    police2 = TTF_OpenFont("arial.ttf", 15);
    //On définie la couleur de la police
    couleurCarac = {255, 255, 255};
    //On défini les effets sur la police
    TTF_SetFontStyle(police2, TTF_STYLE_BOLD);

    for(i=0; i < t; i++)
    {
        elements[i]=tab[i];
        texte[i] = SDL_CreateTextureFromSurface(ecran, TTF_RenderText_Blended(police, elements[i].c_str(), couleurCarac));
        int mainMenuItemWidth = 0; 
        int mainMenuItemHeight = 0;
        TTF_SizeText(police, elements[i].c_str(), &mainMenuItemWidth, &mainMenuItemHeight);
        positionTexte[i].x=0;
        positionTexte[i].y=i*50;
        positionTexte[i].w = mainMenuItemWidth;
        positionTexte[i].h = mainMenuItemHeight;
    }

    for(i=0; i <taille; i++)
    {
        int partyStatisticTextWidth = 0; 
        int partyStatisticTextHeight = 0;

        niv[i]=equipe[i]->GetNiv();
        prenom[i]=equipe[i]->GetPrenom();
        pv[i]=equipe[i]->GetPv();
        pm[i]=equipe[i]->GetPm();
        maxPv[i]=equipe[i]->GetMaxPv();
        maxPm[i]=equipe[i]->GetMaxPm();
        exp[i]=equipe[i]->GetExp();
        suivant[i]=equipe[i]->GetSeuil();
        sprintf(tableauPv, "PV : %d / %d", pv[i], maxPv[i]);
        sprintf(tableauPm, "PM : %d / %d", pm[i], maxPm[i]);
        sprintf(tableauExp, "Experience %d / %d", exp[i], suivant[i]);
        sprintf(tableauNiv, "Niveau : %d", niv[i]);
        texteStatPrenom[i] = SDL_CreateTextureFromSurface(ecran, TTF_RenderText_Blended(police2, prenom[i].c_str(), couleurCarac));
        TTF_SizeText(police2, prenom[i].c_str(), &partyStatisticTextWidth, &partyStatisticTextHeight);
        positionTexteStatPrenom[i].x=(largeur/2)+90;
        positionTexteStatPrenom[i].h=partyStatisticTextHeight;
        positionTexteStatPrenom[i].w=partyStatisticTextWidth;
        texteStatNiv[i] = SDL_CreateTextureFromSurface(ecran, TTF_RenderText_Blended(police2, tableauNiv, couleurCarac));
        TTF_SizeText(police2, tableauNiv, &partyStatisticTextWidth, &partyStatisticTextHeight);
        positionTexteStatNiv[i].x=(largeur/2)+90;
        positionTexteStatNiv[i].h=partyStatisticTextHeight;
        positionTexteStatNiv[i].w=partyStatisticTextWidth;
        texteStatPv[i] = SDL_CreateTextureFromSurface(ecran, TTF_RenderText_Blended(police2, tableauPv, couleurCarac));
        TTF_SizeText(police2, tableauPv, &partyStatisticTextWidth, &partyStatisticTextHeight);
        positionTexteStatPv[i].x=(largeur/2)+90;
        positionTexteStatPv[i].h=partyStatisticTextHeight;
        positionTexteStatPv[i].w=partyStatisticTextWidth;
        texteStatPm[i] = SDL_CreateTextureFromSurface(ecran, TTF_RenderText_Blended(police2, tableauPm, couleurCarac));
        TTF_SizeText(police2, tableauPm, &partyStatisticTextWidth, &partyStatisticTextHeight);
        positionTexteStatPm[i].x=(largeur/2)+90;
        positionTexteStatPm[i].h=partyStatisticTextHeight;
        positionTexteStatPm[i].w=partyStatisticTextWidth;
        texteStatExp[i] = SDL_CreateTextureFromSurface(ecran, TTF_RenderText_Blended(police2, tableauExp, couleurCarac));
        TTF_SizeText(police2, tableauExp, &partyStatisticTextWidth, &partyStatisticTextHeight);
        positionTexteStatExp[i].x=(largeur/2)+90;
        positionTexteStatExp[i].h=partyStatisticTextHeight;
        positionTexteStatExp[i].w=partyStatisticTextWidth;
        
        if(i==MEMBRE1)
        {
            positionTexteStatPrenom[i].y=10;
            positionTexteStatNiv[i].y=30;
            positionTexteStatPv[i].y=50;
            positionTexteStatPm[i].y=70;
            positionTexteStatExp[i].y=90;
        }
        else if(i==MEMBRE2)
        {
            positionTexteStatPrenom[i].y=130;
            positionTexteStatNiv[i].y=150;
            positionTexteStatPv[i].y=170;
            positionTexteStatPm[i].y=190;
            positionTexteStatExp[i].y=210;
        }
        else if(i==MEMBRE3)
        {
            positionTexteStatPrenom[i].y=250;
            positionTexteStatNiv[i].y=270;
            positionTexteStatPv[i].y=290;
            positionTexteStatPm[i].y=310;
            positionTexteStatExp[i].y=330;
        }
        else if(i==MEMBRE4)
        {
            positionTexteStatPrenom[i].y=370;
            positionTexteStatNiv[i].y=390;
            positionTexteStatPv[i].y=410;
            positionTexteStatPm[i].y=430;
            positionTexteStatExp[i].y=450;
        }
    }

    positionCursseur.w=185;
    positionCursseur.h=35;
    positionCursseur.x=0;
    positionCursseur.y=0;
    
    positionLigne.x = largeur/2;
    positionLigne.y = 0;
    positionLigne.w = 2;
    positionLigne.h = hauteur;

    for(i=0; i<4; i++)
    {
        if(i==0)
        {
            positionLigneHorizontale[i].x = largeur/2;
            positionLigneHorizontale[i].y = hauteur/4;
            positionLigneHorizontale[i].w = largeur/2;
            positionLigneHorizontale[i].h = 2;
        }
        else
        {
            positionLigneHorizontale[i].x = largeur/2;
            positionLigneHorizontale[i].y = i*(hauteur/4);
            positionLigneHorizontale[i].w = largeur/2;
            positionLigneHorizontale[i].h = 2;
        }
    }

    positionTof[MEMBRE1].x = (largeur/2)+12;
    positionTof[MEMBRE1].y = 30;
    positionTof[MEMBRE1].w = 64;
    positionTof[MEMBRE1].h = 64;
    positionTof[MEMBRE2].x = (largeur/2)+12;
    positionTof[MEMBRE2].y = 150;
    positionTof[MEMBRE2].w = 64;
    positionTof[MEMBRE2].h = 64;
    positionTof[MEMBRE3].x = (largeur/2)+12;
    positionTof[MEMBRE3].y = 270;
    positionTof[MEMBRE3].w = 64;
    positionTof[MEMBRE3].h = 64;
    positionTof[MEMBRE4].x = (largeur/2)+12;
    positionTof[MEMBRE4].y = 390;
    positionTof[MEMBRE4].w = 64;
    positionTof[MEMBRE4].h = 64;
    tof = SDL_CreateTextureFromSurface(ecran, IMG_Load("tof.png"));
    
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
    SDL_RenderPresent(ecran);
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

                case SDLK_RETURN:

                if(positionCursseur.y==positionTexte[INVENTAIRE].y)
                {
                    //this->EmissionSonValidation();
                }
                else if(positionCursseur.y==positionTexte[EQUIPEMENT].y)
                {
                    this->EmissionSonValidation();
                    sme->AffichageEquipement(equipe, ecran, armeInventaire, casqueInventaire, cuirasseInventaire, bouclierInventaire, jambiereInventaire, obj);
                    armeInventaire=obj->GetArmeInventaire();
                    casqueInventaire=obj->GetCasqueInventaire();
                    cuirasseInventaire=obj->GetCuirasseInventaire();
                    bouclierInventaire=obj->GetBouclierInventaire();
                    jambiereInventaire=obj->GetJambiereInventaire();
                }
                else if(positionCursseur.y==positionTexte[ETAT].y)
                {
                    this->EmissionSonValidation();
                    e->AffichageEtat(equipe, ecran);
                }
                else if(positionCursseur.y==positionTexte[GROUPE].y)
                {
                    this->EmissionSonValidation();
                    g->AffichageGroupe(groupe, equipe, ecran, obj);
                }
                else if(positionCursseur.y==positionTexte[COMPETENCES].y)
                {
                    this->EmissionSonValidation();

                }
                else if(positionCursseur.y==positionTexte[SAUVEGARDER].y)
                {
                    this->EmissionSonValidation();

                }
                else if(positionCursseur.y==positionTexte[CHARGER].y)
                {
                    this->EmissionSonValidation();

                }
                else if(positionCursseur.y==positionTexte[OPTIONS].y)
                {
                    this->EmissionSonValidation();

                }
                else if(positionCursseur.y==positionTexte[SORTIE].y)
                {
                    this->EmissionSonValidation();
                    cycle=0;
                }
                break;

                case SDLK_UP:
                if(positionCursseur.y==positionTexte[INVENTAIRE].y)
                {
                    positionCursseur.y=positionTexte[SORTIE].y;
                    j=SORTIE;
                }
                else
                {
                    positionCursseur.y=positionTexte[--j].y;
                }
                this->EmissionSonDeplacement();
                break;

                case SDLK_DOWN:
                if(positionCursseur.y==positionTexte[SORTIE].y)
                {
                    positionCursseur.y=positionTexte[INVENTAIRE].y;
                    j=INVENTAIRE;
                }
                else
                {
                    positionCursseur.y=positionTexte[++j].y;
                }
                this->EmissionSonDeplacement();
                break;
            }
            break;
        }

        this->DisplayMenuElements(elements, equipe);
    }
}

void Menu::DisplayMenuElements(std::vector<std::string> elements, std::vector<Personnage*> equipe)
{
    int menuElementsSize = elements.size();
    SDL_SetRenderDrawColor(ecran, 180, 180, 180, SDL_ALPHA_OPAQUE );
    SDL_RenderClear(ecran);

    SDL_RenderCopy(ecran, fenMenu, NULL, &positionMenu);

    for(int i = 0; i < menuElementsSize; i++)
    {
        SDL_RenderCopy(ecran, texte[i], NULL, &positionTexte[i]);
    }

    for(int i = 0; i <equipe.size(); i++)
    {
        SDL_RenderCopy(ecran, tof, &clip[i], &positionTof[i]);
        SDL_RenderCopy(ecran, texteStatPrenom[i], NULL, &positionTexteStatPrenom[i]);
        SDL_RenderCopy(ecran, texteStatNiv[i], NULL, &positionTexteStatNiv[i]);
        SDL_RenderCopy(ecran, texteStatPv[i], NULL, &positionTexteStatPv[i]);
        SDL_RenderCopy(ecran, texteStatPm[i], NULL, &positionTexteStatPm[i]);
        SDL_RenderCopy(ecran, texteStatExp[i], NULL, &positionTexteStatExp[i]);
    }

    SDL_SetRenderDrawBlendMode(ecran, SDL_BLENDMODE_BLEND);
    SDL_SetRenderDrawColor(ecran, 255, 255, 36, 70);
    SDL_RenderFillRect(ecran, &positionCursseur);

    SDL_SetRenderDrawColor(ecran, 255, 255, 255, 178);
    SDL_RenderFillRect(ecran, &positionLigne);

    for(int i = 0; i < 4; i++)
    {
        SDL_SetRenderDrawColor(ecran, 255, 255, 255, 178);
        SDL_RenderFillRect(ecran, &positionLigneHorizontale[i]);  
    }

    SDL_RenderPresent(ecran);
}
