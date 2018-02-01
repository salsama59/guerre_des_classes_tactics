#include <cstdlib>
#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include <SDL/SDL_ttf.h>
#include <fmodex/fmod.h>
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
    //Modification de la couleur de fond
    couleur= SDL_MapRGB(ecran->format, 180, 180, 180);
    //On créé un fond qui fera office de menu
    fenMenu = SDL_CreateRGBSurface(SDL_HWSURFACE, largeur, hauteur, 32, 0, 0, 0, 0);
    //On définie les coordonnées du menu
    positionMenu.x=0;
    positionMenu.y=0;
    //Modification de la couleur du fond
    SDL_FillRect(fenMenu, NULL, couleur);
    //Initialisation de FMOD (création du système de son)
    FMOD_System_Create(&system);
    FMOD_System_Init(system, 3, FMOD_INIT_NORMAL, NULL);
    //on créé des sample de son afin de les utiliser plus tard
    FMOD_System_CreateSound(system, "deplacement.mp3", FMOD_CREATESAMPLE, 0, &sonDeplacement);
    FMOD_System_CreateSound(system, "validation.wav", FMOD_CREATESAMPLE, 0, &sonValidation);
    FMOD_System_CreateSound(system, "annulation.wav", FMOD_CREATESAMPLE, 0, &sonAnnulation);
    FMOD_System_CreateSound(system, "Menu.mp3", FMOD_CREATESAMPLE, 0, &sonMenu);
    //On récupère les informations liés au cannaux
    FMOD_System_GetChannel(system, 1, &channel);
}

Menu::Menu()
{

}
//Destructeur de la classe Menu
Menu:: ~Menu()
{
    FMOD_System_Close(system);
    FMOD_System_Release(system);
    FMOD_Sound_Release(sonDeplacement);
    FMOD_Sound_Release(sonValidation);
    FMOD_Sound_Release(sonAnnulation);
    FMOD_Sound_Release(sonMenu);
}

void Menu::ChangerCouleur(int r, int v, int b)
{
    couleur= SDL_MapRGB(ecran->format, r, v, b);
}

void Menu::EmissionSonDeplacement()
{
    FMOD_System_PlaySound(system, FMOD_CHANNEL_FREE, sonDeplacement, 0, NULL);
}

void Menu::EmissionSonValidation()
{
    FMOD_System_PlaySound(system, FMOD_CHANNEL_FREE, sonValidation, 0, NULL);
}

void Menu::EmissionSonAnnulation()
{
    FMOD_System_PlaySound(system, FMOD_CHANNEL_FREE, sonAnnulation, 0, NULL);
}

void Menu::EmissionSonMenu()
{
    FMOD_System_PlaySound(system, FMOD_CHANNEL_FREE, sonMenu, 0, NULL);
}

void Menu::AffichageMenu(std::vector<Personnage*> equipe, std::vector<Personnage*> groupe, SDL_Surface *ecran, std::vector<Arme*> armeInventaire, std::vector<Casque*> casqueInventaire, std::vector<Cuirasse*> cuirasseInventaire, std::vector<Bouclier*> bouclierInventaire, std::vector<Jambiere*> jambiereInventaire, Jeu *obj)
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
        texte[i] = TTF_RenderText_Blended(police, elements[i].c_str(), couleurCarac);
        positionTexte[i].x=0;
        positionTexte[i].y=i*50;
    }

    for(i=0; i <taille; i++)
    {
        if(i==MEMBRE1)
        {
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
            texteStatPrenom[i] = TTF_RenderText_Blended(police2, prenom[i].c_str(), couleurCarac);
            positionTexteStatPrenom[i].x=(largeur/2)+90;
            positionTexteStatPrenom[i].y=10;
            texteStatNiv[i] = TTF_RenderText_Blended(police2, tableauNiv, couleurCarac);
            positionTexteStatNiv[i].x=(largeur/2)+90;
            positionTexteStatNiv[i].y=30;
            texteStatPv[i] = TTF_RenderText_Blended(police2, tableauPv, couleurCarac);
            positionTexteStatPv[i].x=(largeur/2)+90;
            positionTexteStatPv[i].y=50;
            texteStatPm[i] = TTF_RenderText_Blended(police2, tableauPm, couleurCarac);
            positionTexteStatPm[i].x=(largeur/2)+90;
            positionTexteStatPm[i].y=70;
            texteStatExp[i] = TTF_RenderText_Blended(police2, tableauExp, couleurCarac);
            positionTexteStatExp[i].x=(largeur/2)+90;
            positionTexteStatExp[i].y=90;
        }
        else if(i==MEMBRE2)
        {
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
            texteStatPrenom[i] = TTF_RenderText_Blended(police2, prenom[i].c_str(), couleurCarac);
            positionTexteStatPrenom[i].x=(largeur/2)+90;
            positionTexteStatPrenom[i].y=130;
            texteStatNiv[i] = TTF_RenderText_Blended(police2, tableauNiv, couleurCarac);
            positionTexteStatNiv[i].x=(largeur/2)+90;
            positionTexteStatNiv[i].y=150;
            texteStatPv[i] = TTF_RenderText_Blended(police2, tableauPv, couleurCarac);
            positionTexteStatPv[i].x=(largeur/2)+90;
            positionTexteStatPv[i].y=170;
            texteStatPm[i] = TTF_RenderText_Blended(police2, tableauPm, couleurCarac);
            positionTexteStatPm[i].x=(largeur/2)+90;
            positionTexteStatPm[i].y=190;
            texteStatExp[i] = TTF_RenderText_Blended(police2, tableauExp, couleurCarac);
            positionTexteStatExp[i].x=(largeur/2)+90;
            positionTexteStatExp[i].y=210;
        }
        else if(i==MEMBRE3)
        {
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
            texteStatPrenom[i] = TTF_RenderText_Blended(police2, prenom[i].c_str(), couleurCarac);
            positionTexteStatPrenom[i].x=(largeur/2)+90;
            positionTexteStatPrenom[i].y=250;
            texteStatNiv[i] = TTF_RenderText_Blended(police2, tableauNiv, couleurCarac);
            positionTexteStatNiv[i].x=(largeur/2)+90;
            positionTexteStatNiv[i].y=270;
            texteStatPv[i] = TTF_RenderText_Blended(police2, tableauPv, couleurCarac);
            positionTexteStatPv[i].x=(largeur/2)+90;
            positionTexteStatPv[i].y=290;
            texteStatPm[i] = TTF_RenderText_Blended(police2, tableauPm, couleurCarac);
            positionTexteStatPm[i].x=(largeur/2)+90;
            positionTexteStatPm[i].y=310;
            texteStatExp[i] = TTF_RenderText_Blended(police2, tableauExp, couleurCarac);
            positionTexteStatExp[i].x=(largeur/2)+90;
            positionTexteStatExp[i].y=330;
        }
        else if(i==MEMBRE4)
        {
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
            texteStatPrenom[i] = TTF_RenderText_Blended(police2, prenom[i].c_str(), couleurCarac);
            positionTexteStatPrenom[i].x=(largeur/2)+90;
            positionTexteStatPrenom[i].y=370;
            texteStatNiv[i] = TTF_RenderText_Blended(police2, tableauNiv, couleurCarac);
            positionTexteStatNiv[i].x=(largeur/2)+90;
            positionTexteStatNiv[i].y=390;
            texteStatPv[i] = TTF_RenderText_Blended(police2, tableauPv, couleurCarac);
            positionTexteStatPv[i].x=(largeur/2)+90;
            positionTexteStatPv[i].y=410;
            texteStatPm[i] = TTF_RenderText_Blended(police2, tableauPm, couleurCarac);
            positionTexteStatPm[i].x=(largeur/2)+90;
            positionTexteStatPm[i].y=430;
            texteStatExp[i] = TTF_RenderText_Blended(police2, tableauExp, couleurCarac);
            positionTexteStatExp[i].x=(largeur/2)+90;
            positionTexteStatExp[i].y=450;
        }

    }

    couleurCursseur= SDL_MapRGB(ecran->format, 255, 255, 36);
    positionCursseur.w=185;
    positionCursseur.h=35;
    positionCursseur.x=0;
    positionCursseur.y=0;
    cursseur= SDL_CreateRGBSurface(SDL_HWSURFACE, positionCursseur.w, positionCursseur.h, 32, 0, 0, 0, 0);
    SDL_FillRect(cursseur, NULL, couleurCursseur);
    SDL_SetAlpha(cursseur, SDL_SRCALPHA, 70);
    positionLigne.x = largeur/2;
    positionLigne.y = 0;
    positionLigne.w = 2;
    positionLigne.h = hauteur;
    ligne= SDL_CreateRGBSurface(SDL_HWSURFACE, positionLigne.w, positionLigne.h, NB_BITS_PAR_PIXEL, 0, 0, 0, 0);
    couleurLigne= SDL_MapRGB(ecran->format, 255, 255, 255);
    SDL_FillRect(ligne, NULL, couleurLigne);

    for(i=0; i<4; i++)
    {
        if(i==0)
        {
            positionLigneHorizontale[i].x = largeur/2;
            positionLigneHorizontale[i].y = hauteur/4;
            positionLigneHorizontale[i].w = largeur/2;
            positionLigneHorizontale[i].h = 2;
            ligneHorizontale[i]= SDL_CreateRGBSurface(SDL_HWSURFACE, positionLigneHorizontale[i].w, positionLigneHorizontale[i].h, NB_BITS_PAR_PIXEL, 0, 0, 0, 0);
            SDL_FillRect(ligneHorizontale[i], NULL, couleurLigne);
        }
        else
        {
            positionLigneHorizontale[i].x = largeur/2;
            positionLigneHorizontale[i].y = i*(hauteur/4);
            positionLigneHorizontale[i].w = largeur/2;
            positionLigneHorizontale[i].h = 2;
            ligneHorizontale [i]= SDL_CreateRGBSurface(SDL_HWSURFACE, positionLigneHorizontale[i].w, positionLigneHorizontale[i].h, NB_BITS_PAR_PIXEL, 0, 0, 0, 0);
            SDL_FillRect(ligneHorizontale[i], NULL, couleurLigne);
        }
    }

    positionTof[MEMBRE1].x = (largeur/2)+12;
    positionTof[MEMBRE1].y = 30;
    positionTof[MEMBRE2].x = (largeur/2)+12;
    positionTof[MEMBRE2].y = 150;
    positionTof[MEMBRE3].x = (largeur/2)+12;
    positionTof[MEMBRE3].y = 270;
    positionTof[MEMBRE4].x = (largeur/2)+12;
    positionTof[MEMBRE4].y = 390;
    tof = IMG_Load("tof.png");
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

        // Collage de la surface de menu sur l'écran
        SDL_BlitSurface(fenMenu, NULL, ecran, &positionMenu);
        SDL_BlitSurface(ligne, NULL, ecran, &positionLigne);
        for(i=0; i<4; i++)
        {
            SDL_BlitSurface(ligneHorizontale[i], NULL, ecran, &positionLigneHorizontale[i]);
        }
        for(i=0; i<t; i++)
        {
            SDL_BlitSurface(texte[i], NULL, ecran, &positionTexte[i]); /* Blit du texte */
        }
        for(i=0; i<taille; i++)
        {
            SDL_BlitSurface(texteStatPrenom[i], NULL, ecran, &positionTexteStatPrenom[i]);
            SDL_BlitSurface(texteStatNiv[i], NULL, ecran, &positionTexteStatNiv[i]);
            SDL_BlitSurface(texteStatPv[i], NULL, ecran, &positionTexteStatPv[i]);
            SDL_BlitSurface(texteStatPm[i], NULL, ecran, &positionTexteStatPm[i]);
            SDL_BlitSurface(texteStatExp[i], NULL, ecran, &positionTexteStatExp[i]);
            SDL_BlitSurface(tof, &clip[i], ecran, &positionTof[i]);
        }
        SDL_BlitSurface(cursseur, NULL, ecran, &positionCursseur);
        //Mise à jour de l'affichage
        SDL_Flip(ecran);
    }
}
