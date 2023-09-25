#include <cstdlib>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <ft2build.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_mixer.h>
#include <freetype/freetype.h>
#include "SmenuEquipement.h"
#include "Jeu.h"
#include "Lance.h"
#include "Gant.h"
#include <string>
#include <iostream>
#include <vector>
using namespace std;

SmenuEquipement::SmenuEquipement(SDL_Renderer *ecran)
{
    largeur=LARGEUR;
    hauteur=HAUTEUR;
    //couleur= SDL_MapRGB(ecran->format, 180, 180, 180);
    //fenMenu = SDL_CreateRGBSurface(SDL_HWSURFACE, largeur, hauteur, NB_BITS_PAR_PIXEL, 0, 0, 0, 0);
    positionMenu.x=0;
    positionMenu.y=0;
    fenMenu = SDL_CreateTexture(ecran,
                               SDL_PIXELFORMAT_ARGB8888,
                               SDL_TEXTUREACCESS_STREAMING,
                               largeur, hauteur);
    
    //Modification de la couleur du fond
    //SDL_FillRect(fenMenu, NULL, couleur);

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

SmenuEquipement:: ~SmenuEquipement()
{
    Mix_FreeChunk(sonDeplacement);
    Mix_FreeChunk(sonValidation);
    Mix_FreeChunk(sonAnnulation);
}

void SmenuEquipement::AffichageEquipement(std::vector<Personnage*> equipe, SDL_Renderer *ecran, std::vector<Arme*> armeInventaire, std::vector<Casque*> casqueInventaire, std::vector<Cuirasse*> cuirasseInventaire, std::vector<Bouclier*> bouclierInventaire, std::vector<Jambiere*> jambiereInventaire, Jeu *obj)
{
    int cycle=1, init=0, i=0, t=0, j=0, taille=0, membre=0, nb=0, cpt=0, k=0, l=0, m=0, n=0, flag=0, bas=0, haut=0, gauche=0, droite=0, arm=0, cuir=0, bouc=0, jamb=0;
    taille=equipe.size();
    nb=armeInventaire.size();
    arm=casqueInventaire.size();
    cuir=cuirasseInventaire.size();
    bouc=bouclierInventaire.size();
    jamb=jambiereInventaire.size();
    float esq[taille], prc[taille];
    int maxPv[taille], maxPm[taille], fr[taille], def[taille], mag[taille], vol[taille], vit[taille], cha[taille], degat[nb];
    string nomArme[taille], nomArmure[4], prenom[taille], nomArmeInventaire[nb], nomArmureInventaire[arm], nomCuirasseInventaire[cuir], nomBouclierInventaire[bouc], nomJambiereInventaire[jamb];
    std::vector<Equipement> e;
    std::vector<Arme> a;
    init=TTF_Init();
    if(init == -1)
    {
        fprintf(stderr, "Erreur d'initialisation de TTF_Init : %s\n", TTF_GetError());
        exit(EXIT_FAILURE);
        atexit(TTF_Quit);
    }

    police = TTF_OpenFont("arial.ttf", 30);
    couleurCarac = {255, 255, 255};
    couleurAjout={255, 255, 0};

    positionCursseur.w=105;
    positionCursseur.h=35;
    positionCursseur.x=(largeur+5)/2;
    positionCursseur.y=0;

    for(i=0; i<nb; i++)
    {
        if(i==0)
        {
            
            positionTexteNomArme[i].x=0;
            positionTexteNomArme[i].y=265;
        }
        else
        {
            positionTexteNomArme[i].x=0;
            positionTexteNomArme[i].y=positionTexteNomArme[i-1].y+30;
        }

        nomArmeInventaire[i]=armeInventaire[i]->GetNom();
        degat[i]=armeInventaire[i]->GetDegat();
        sprintf(tableauDegat, "%d", degat[i]);
        texteNomArme[i] = SDL_CreateTextureFromSurface(ecran, TTF_RenderText_Blended(police, nomArmeInventaire[i].c_str(), couleurCarac));
        int texteNomArmeWidth = 0; 
        int texteNomArmeHeight = 0;
        TTF_SizeText(police, nomArmeInventaire[i].c_str(), &texteNomArmeWidth, &texteNomArmeHeight);
        positionTexteNomArme[i].w = texteNomArmeWidth;
        positionTexteNomArme[i].h = texteNomArmeHeight;
    }

    for(i=0; i<arm; i++)
    {
        if(i==0)
        {
            positionTexteNomArmure[i].x=0;
            positionTexteNomArmure[i].y=265;
        }
        else
        {
            positionTexteNomArmure[i].x=0;
            positionTexteNomArmure[i].y=positionTexteNomArmure[i-1].y+30;
        }

        nomArmureInventaire[i]=casqueInventaire[i]->GetNom();
        texteNomArmure[i] = SDL_CreateTextureFromSurface(ecran, TTF_RenderText_Blended(police, nomArmureInventaire[i].c_str(), couleurCarac));
        int texteNomArmureWidth = 0; 
        int texteNomArmureHeight = 0;
        TTF_SizeText(police, nomArmureInventaire[i].c_str(), &texteNomArmureWidth, &texteNomArmureHeight);
        positionTexteNomArmure[i].w = texteNomArmureWidth;
        positionTexteNomArmure[i].h = texteNomArmureHeight;
    }

    for(i=0; i<cuir; i++)
    {
        if(i==0)
        {
            positionTexteNomCuirasse[i].x=0;
            positionTexteNomCuirasse[i].y=265;
        }
        else
        {
            positionTexteNomCuirasse[i].x=0;
            positionTexteNomCuirasse[i].y=positionTexteNomCuirasse[i-1].y+30;
        }

        nomCuirasseInventaire[i]=cuirasseInventaire[i]->GetNom();
        texteNomCuirasse[i] = SDL_CreateTextureFromSurface(ecran, TTF_RenderText_Blended(police, nomCuirasseInventaire[i].c_str(), couleurCarac));
        int texteNomCuirasseWidth = 0; 
        int texteNomCuirasseHeight = 0;
        TTF_SizeText(police, nomCuirasseInventaire[i].c_str(), &texteNomCuirasseWidth, &texteNomCuirasseHeight);
        positionTexteNomCuirasse[i].w = texteNomCuirasseWidth;
        positionTexteNomCuirasse[i].h = texteNomCuirasseHeight;
    }

    for(i=0; i<bouc; i++)
    {
        if(i==0)
        {
            positionTexteNomBouclier[i].x=0;
            positionTexteNomBouclier[i].y=265;
        }
        else
        {
            positionTexteNomBouclier[i].x=0;
            positionTexteNomBouclier[i].y=positionTexteNomBouclier[i-1].y+30;
        }

        nomBouclierInventaire[i]=bouclierInventaire[i]->GetNom();
        texteNomBouclier[i] = SDL_CreateTextureFromSurface(ecran, TTF_RenderText_Blended(police, nomBouclierInventaire[i].c_str(), couleurCarac));
        int texteNomBouclierWidth = 0; 
        int texteNomBouclierHeight = 0;
        TTF_SizeText(police, nomBouclierInventaire[i].c_str(), &texteNomBouclierWidth, &texteNomBouclierHeight);
        positionTexteNomBouclier[i].w = texteNomBouclierWidth;
        positionTexteNomBouclier[i].h = texteNomBouclierHeight;
    }

    for(i=0; i<jamb; i++)
    {
        if(i==0)
        {
            positionTexteNomJambiere[i].x=0;
            positionTexteNomJambiere[i].y=265;
        }
        else
        {
            
            positionTexteNomJambiere[i].x=0;
            positionTexteNomJambiere[i].y=positionTexteNomJambiere[i-1].y+30;
        }

        nomJambiereInventaire[i]=jambiereInventaire[i]->GetNom();
        texteNomJambiere[i] = SDL_CreateTextureFromSurface(ecran, TTF_RenderText_Blended(police, nomJambiereInventaire[i].c_str(), couleurCarac));
        int texteNomJambiereWidth = 0; 
        int texteNomJambiereHeight = 0;
        TTF_SizeText(police, nomJambiereInventaire[i].c_str(), &texteNomJambiereWidth, &texteNomJambiereHeight);
        positionTexteNomJambiere[i].w = texteNomJambiereWidth;
        positionTexteNomJambiere[i].h = texteNomJambiereHeight;
    }

    for(i=0; i<taille; i++)
    {
        a.push_back(equipe[i]->GetArmeEquipe());
        prenom[i]=equipe[i]->GetPrenom();
        e=equipe[i]->GetArmureEquipe();
        nomArme[i]=a[i].GetNom();
        maxPv[i]=equipe[i]->GetMaxPv();
        maxPm[i]=equipe[i]->GetMaxPm();
        fr[i]=equipe[i]->GetFr();
        def[i]=equipe[i]->GetDef();
        mag[i]=equipe[i]->GetMag();
        vol[i]=equipe[i]->GetVol();
        vit[i]=equipe[i]->GetVit();
        esq[i]=equipe[i]->GetEsq();
        prc[i]=equipe[i]->GetPrc();
        cha[i]=equipe[i]->GetCha();

        for(j=0; j<e.size(); j++)
        {
            if(i==0)
            {
                if(j==0)
                {
                    positionTexteStatNomArmure[j].x=150;
                    positionTexteStatNomArmure[j].y=130;

                }
                else if(j>0)
                {
                    
                    positionTexteStatNomArmure[j].x=150;
                    positionTexteStatNomArmure[j].y=positionTexteStatNomArmure[j-1].y+30;

                }
                nomArmure[j]=e[j].GetNom();
                texteStatNomArmureM0[j] = SDL_CreateTextureFromSurface(ecran, TTF_RenderText_Blended(police, nomArmure[j].c_str(), couleurCarac));
                int texteStatNomArmureM0Width = 0; 
                int texteStatNomArmureM0Height = 0;
                TTF_SizeText(police, nomArmure[j].c_str(), &texteStatNomArmureM0Width, &texteStatNomArmureM0Height);
                positionTexteStatNomArmure[j].w = texteStatNomArmureM0Width;
                positionTexteStatNomArmure[j].h = texteStatNomArmureM0Height;
            }
            if(i==1)
            {

                if(j==0)
                {
                    positionTexteStatNomArmure[j].x=150;
                    positionTexteStatNomArmure[j].y=130;

                }
                else if(j>0)
                {
                    positionTexteStatNomArmure[j].x=150;
                    positionTexteStatNomArmure[j].y=positionTexteStatNomArmure[j-1].y+30;

                }

                nomArmure[j]=e[j].GetNom();
                texteStatNomArmureM1[j] = SDL_CreateTextureFromSurface(ecran, TTF_RenderText_Blended(police, nomArmure[j].c_str(), couleurCarac));
                int texteStatNomArmureM1Width = 0; 
                int texteStatNomArmureM1Height = 0;
                TTF_SizeText(police, nomArmure[j].c_str(), &texteStatNomArmureM1Width, &texteStatNomArmureM1Height);
                positionTexteStatNomArmure[j].w = texteStatNomArmureM1Width;
                positionTexteStatNomArmure[j].h = texteStatNomArmureM1Height;
            }
        }

        sprintf(tableauPv, "MAX PV : %d", maxPv[i]);
        sprintf(tableauPm, "MAX PM : %d", maxPm[i]);
        sprintf(tableauFr, "Force : %d", fr[i]);
        sprintf(tableauMag, "Magie : %d", mag[i]);
        sprintf(tableauDef, "Defense : %d", def[i]);
        sprintf(tableauVol, "Volonte : %d", vol[i]);
        sprintf(tableauVit, "Vitesse : %d", vit[i]);
        sprintf(tableauEsq, "Esquive : %.2f %", esq[i]);
        sprintf(tableauPrc, "Precision : %.2f %", prc[i]);
        sprintf(tableauCha, "Chance : %d", cha[i]);

        int texteStatCharacterWidth = 0; 
        int texteStatCharacterHeight = 0;

        texteStatPv[i] = SDL_CreateTextureFromSurface(ecran, TTF_RenderText_Blended(police, tableauPv, couleurCarac));
        TTF_SizeText(police, tableauPv, &texteStatCharacterWidth, &texteStatCharacterHeight);
        positionTexteStatPv[i].x=(largeur+10)/2;
        positionTexteStatPv[i].y=40;
        positionInfoArmePv.x=positionTexteStatPv[i].x+140;
        positionInfoArmePv.y=40;
        positionTexteStatPv[i].w = texteStatCharacterWidth;
        positionTexteStatPv[i].h = texteStatCharacterHeight;

        texteStatPm[i] = SDL_CreateTextureFromSurface(ecran, TTF_RenderText_Blended(police, tableauPm, couleurCarac));
        TTF_SizeText(police, tableauPm, &texteStatCharacterWidth, &texteStatCharacterHeight);
        positionTexteStatPm[i].x=(largeur+10)/2;
        positionTexteStatPm[i].y=2*(hauteur-50)/11;
        positionInfoArmePm.x=positionTexteStatPm[i].x+140;
        positionInfoArmePm.y=2*(hauteur-50)/11;
        positionTexteStatPm[i].w = texteStatCharacterWidth;
        positionTexteStatPm[i].h = texteStatCharacterHeight;

        texteStatFr[i] = SDL_CreateTextureFromSurface(ecran, TTF_RenderText_Blended(police, tableauFr, couleurCarac));
        TTF_SizeText(police, tableauFr, &texteStatCharacterWidth, &texteStatCharacterHeight);
        positionTexteStatFr[i].x=(largeur+10)/2;
        positionTexteStatFr[i].y=3*(hauteur-50)/11;
        positionInfoArmeFr.x=positionTexteStatFr[i].x+140;
        positionInfoArmeFr.y=3*(hauteur-50)/11;
        positionTexteStatFr[i].w = texteStatCharacterWidth;
        positionTexteStatFr[i].h = texteStatCharacterHeight;

        texteStatDef[i] = SDL_CreateTextureFromSurface(ecran, TTF_RenderText_Blended(police, tableauDef, couleurCarac));
        TTF_SizeText(police, tableauDef, &texteStatCharacterWidth, &texteStatCharacterHeight);
        positionTexteStatDef[i].x=(largeur+10)/2;
        positionTexteStatDef[i].y=4*(hauteur-50)/11;
        positionInfoArmeDef.x=positionTexteStatDef[i].x+180;
        positionInfoArmeDef.y=4*(hauteur-50)/11;
        positionTexteStatDef[i].w = texteStatCharacterWidth;
        positionTexteStatDef[i].h = texteStatCharacterHeight;

        texteStatMag[i] = SDL_CreateTextureFromSurface(ecran, TTF_RenderText_Blended(police, tableauMag, couleurCarac));
        TTF_SizeText(police, tableauMag, &texteStatCharacterWidth, &texteStatCharacterHeight);
        positionTexteStatMag[i].x=(largeur+10)/2;
        positionTexteStatMag[i].y=5*(hauteur-50)/11;
        positionInfoArmeMag.x=positionTexteStatMag[i].x+140;
        positionInfoArmeMag.y=5*(hauteur-50)/11;
        positionTexteStatMag[i].w = texteStatCharacterWidth;
        positionTexteStatMag[i].h = texteStatCharacterHeight;

        texteStatVol[i] = SDL_CreateTextureFromSurface(ecran, TTF_RenderText_Blended(police, tableauVol, couleurCarac));
        TTF_SizeText(police, tableauVol, &texteStatCharacterWidth, &texteStatCharacterHeight);
        positionTexteStatVol[i].x=(largeur+10)/2;
        positionTexteStatVol[i].y=6*(hauteur-50)/11;
        positionInfoArmeVol.x=positionTexteStatVol[i].x+140;
        positionInfoArmeVol.y=6*(hauteur-50)/11;
        positionTexteStatVol[i].w = texteStatCharacterWidth;
        positionTexteStatVol[i].h = texteStatCharacterHeight;

        texteStatVit[i] = SDL_CreateTextureFromSurface(ecran, TTF_RenderText_Blended(police, tableauVit, couleurCarac));
        TTF_SizeText(police, tableauVit, &texteStatCharacterWidth, &texteStatCharacterHeight);
        positionTexteStatVit[i].x=(largeur+10)/2;
        positionTexteStatVit[i].y=7*(hauteur-50)/11;
        positionInfoArmeVit.x=positionTexteStatVit[i].x+140;
        positionInfoArmeVit.y=7*(hauteur-50)/11;
        positionTexteStatVit[i].w = texteStatCharacterWidth;
        positionTexteStatVit[i].h = texteStatCharacterHeight;

        texteStatPrc[i] = SDL_CreateTextureFromSurface(ecran, TTF_RenderText_Blended(police, tableauPrc, couleurCarac));
        TTF_SizeText(police, tableauPrc, &texteStatCharacterWidth, &texteStatCharacterHeight);
        positionTexteStatPrc[i].x=(largeur+10)/2;
        positionTexteStatPrc[i].y=8*(hauteur-50)/11;
        positionInfoArmePrc.x=positionTexteStatPrc[i].x+140;
        positionInfoArmePrc.y=8*(hauteur-50)/11;
        positionTexteStatPrc[i].w = texteStatCharacterWidth;
        positionTexteStatPrc[i].h = texteStatCharacterHeight;

        texteStatEsq[i] = SDL_CreateTextureFromSurface(ecran, TTF_RenderText_Blended(police, tableauEsq, couleurCarac));
        TTF_SizeText(police, tableauEsq, &texteStatCharacterWidth, &texteStatCharacterHeight);
        positionTexteStatEsq[i].x=(largeur+10)/2;
        positionTexteStatEsq[i].y=9*(hauteur-50)/11;
        positionInfoArmeEsq.x= positionTexteStatEsq[i].x+140;
        positionInfoArmeEsq.y=9*(hauteur-50)/11;
        positionTexteStatEsq[i].w = texteStatCharacterWidth;
        positionTexteStatEsq[i].h = texteStatCharacterHeight;

        texteStatCha[i] = SDL_CreateTextureFromSurface(ecran, TTF_RenderText_Blended(police, tableauCha, couleurCarac));
        TTF_SizeText(police, tableauCha, &texteStatCharacterWidth, &texteStatCharacterHeight);
        positionTexteStatCha[i].x=(largeur+10)/2;
        positionTexteStatCha[i].y=10*(hauteur-50)/11;
        positionInfoArmeCha.x=positionTexteStatCha[i].x+140;
        positionInfoArmeCha.y=10*(hauteur-50)/11;
        positionTexteStatCha[i].w = texteStatCharacterWidth;
        positionTexteStatCha[i].h = texteStatCharacterHeight;

        texteStatNomArme[i] = SDL_CreateTextureFromSurface(ecran, TTF_RenderText_Blended(police, nomArme[i].c_str(), couleurCarac));
        TTF_SizeText(police, nomArme[i].c_str(), &texteStatCharacterWidth, &texteStatCharacterHeight);
        positionTexteStatNomArme[i].x=150;
        positionTexteStatNomArme[i].y=100;
        positionTexteStatNomArme[i].w = texteStatCharacterWidth;
        positionTexteStatNomArme[i].h = texteStatCharacterHeight;

        texteStatPrenom[i] = SDL_CreateTextureFromSurface(ecran, TTF_RenderText_Blended(police, prenom[i].c_str(), couleurCarac));
        TTF_SizeText(police, prenom[i].c_str(), &texteStatCharacterWidth, &texteStatCharacterHeight);
        positionTexteStatPrenom[i].x=100;
        positionTexteStatPrenom[i].y=45;
        positionTexteStatPrenom[i].w = texteStatCharacterWidth;
        positionTexteStatPrenom[i].h = texteStatCharacterHeight;
    }

    const char* tableauEquip[5]= {"Arme :", "Casque :", "Cuirasse :", "Bouclier :", "Jambiere :"};

    for(i=0; i<5; i++)
    {
        if(i==0)
        {
            positionTexteEquipement[i].x=0;
            positionTexteEquipement[i].y=100;
        }
        else
        {
            positionTexteEquipement[i].x=0;
            positionTexteEquipement[i].y=positionTexteEquipement[i-1].y+30;
        }

        texteEquipement[i] = SDL_CreateTextureFromSurface(ecran, TTF_RenderText_Blended(police, tableauEquip[i], couleurCarac));
        int texteEquipementWidth = 0; 
        int texteEquipementHeight = 0;
        TTF_SizeText(police, tableauEquip[i], &texteEquipementWidth, &texteEquipementHeight);
        positionTexteEquipement[i].w = texteEquipementWidth;
        positionTexteEquipement[i].h = texteEquipementHeight;
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
            positionLigneHorizontale[i].x = 0;
            positionLigneHorizontale[i].y = 260;
            positionLigneHorizontale[i].w = largeur/2;
            positionLigneHorizontale[i].h = 2;
        }
    }

    titreMenu = SDL_CreateTextureFromSurface(ecran, TTF_RenderText_Blended(police, "Equipement", couleurCarac));
    int titreMenuWidth = 0; 
    int titreMenuHeight = 0;
    TTF_SizeText(police, "Equipement", &titreMenuWidth, &titreMenuHeight);
    positionTitreMenu.x=0;
    positionTitreMenu.y=0;
    positionTitreMenu.w = titreMenuWidth;
    positionTitreMenu.h = titreMenuHeight;

    const char*tableauOption[2]={"Equiper", "Enlever"};

    for(i=0; i<2; i++)
    {
        if(i==0)
        {
            positionOptionEquipement[i].x=(largeur+5)/2;
            positionOptionEquipement[i].y=0;
        }
        else
        {
            positionOptionEquipement[i].x=positionOptionEquipement[i-1].x+150;
            positionOptionEquipement[i].y=0;
        }

        optionEquipement[i] = SDL_CreateTextureFromSurface(ecran, TTF_RenderText_Blended(police, tableauOption[i], couleurCarac));
        int optionEquipementWidth = 0; 
        int optionEquipementHeight = 0;
        TTF_SizeText(police, tableauOption[i], &optionEquipementWidth, &optionEquipementHeight);
        positionOptionEquipement[i].w = optionEquipementWidth;
        positionOptionEquipement[i].h = optionEquipementHeight;
    }

    positionTof.x =0;
    positionTof.y = 45;
    positionTof.w = 50;
    positionTof.h = 50;
    tof = SDL_CreateTextureFromSurface(ecran, IMG_Load("tof.png"));
    
    clip[MEMBRE1].x=0;
    clip[MEMBRE1].y=0;
    clip[MEMBRE1].w=192/4;
    clip[MEMBRE1].h=192/4;

    clip[MEMBRE2].x=3*192/4;
    clip[MEMBRE2].y=0;
    clip[MEMBRE2].w=192/4;
    clip[MEMBRE2].h=192/4;

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
                if(positionCursseur.x>=positionTexteStatNomArme[membre].x && positionCursseur.x<=positionLigne.x && positionCursseur.y>=positionTexteStatNomArme[membre].y && positionCursseur.y<=positionLigneHorizontale[1].y && cpt==0)
                {
                    positionCursseur.x=positionOptionEquipement[EQUIPER].x;
                    positionCursseur.y=positionOptionEquipement[EQUIPER].y;
                    cpt=0;
                    this->EmissionSonAnnulation();
                }
                else if(positionCursseur.x>=0 && positionCursseur.x<=positionLigne.x && positionCursseur.y<=HAUTEUR && positionCursseur.y>=positionLigneHorizontale[1].y && cpt==1)
                {
                    positionCursseur.x=positionTexteStatNomArme[membre].x;
                    positionCursseur.y=positionTexteStatNomArme[membre].y;
                    cpt=0;
                    flag=0;
                    this->EmissionSonAnnulation();
                }
                else if(positionCursseur.x>=positionTexteStatNomArme[membre].x && positionCursseur.x<=positionLigne.x && positionCursseur.y>=positionTexteStatNomArme[membre].y && positionCursseur.y<=positionLigneHorizontale[1].y &&cpt==2)
                {

                    positionCursseur.x=positionOptionEquipement[EQUIPER].x;
                    positionCursseur.y=positionOptionEquipement[EQUIPER].y;
                    cpt=0;
                    this->EmissionSonAnnulation();
                }
                else if(positionCursseur.x>=0 && positionCursseur.x<=positionLigne.x && positionCursseur.y<=HAUTEUR && positionCursseur.y>=positionLigneHorizontale[1].y && cpt==3)
                {
                    positionCursseur.x=positionTexteStatNomArmure[CASQUE].x;
                    positionCursseur.y=positionTexteStatNomArmure[CASQUE].y;
                    cpt=0;
                    flag=0;
                    this->EmissionSonAnnulation();
                }
                else if(positionCursseur.x>=0 && positionCursseur.x<=positionLigne.x && positionCursseur.y<=HAUTEUR && positionCursseur.y>=positionLigneHorizontale[1].y && cpt==4)
                {
                    positionCursseur.x=positionTexteStatNomArmure[CUIRASSE].x;
                    positionCursseur.y=positionTexteStatNomArmure[CUIRASSE].y;
                    cpt=0;
                    flag=0;
                    this->EmissionSonAnnulation();
                }
                else if(positionCursseur.x>=0 && positionCursseur.x<=positionLigne.x && positionCursseur.y<=HAUTEUR && positionCursseur.y>=positionLigneHorizontale[1].y && cpt==5)
                {
                    positionCursseur.x=positionTexteStatNomArmure[BOUCLIER].x;
                    positionCursseur.y=positionTexteStatNomArmure[BOUCLIER].y;
                    cpt=0;
                    flag=0;
                    this->EmissionSonAnnulation();
                }
                else if(positionCursseur.x>=0 && positionCursseur.x<=positionLigne.x && positionCursseur.y<=HAUTEUR && positionCursseur.y>=positionLigneHorizontale[1].y && cpt==6)
                {
                    positionCursseur.x=positionTexteStatNomArmure[JAMBIERE].x;
                    positionCursseur.y=positionTexteStatNomArmure[JAMBIERE].y;
                    cpt=0;
                    flag=0;
                    this->EmissionSonAnnulation();
                }
                else
                {
                    cycle = 0;
                    this->EmissionSonAnnulation();
                }
                break;

                case SDLK_SPACE:
                break;

                case SDLK_RETURN:
                if(positionCursseur.x==positionOptionEquipement[EQUIPER].x && positionCursseur.y==positionOptionEquipement[EQUIPER].y)
                {
                    positionCursseur.x=positionTexteStatNomArme[membre].x;
                    positionCursseur.y=positionTexteStatNomArme[membre].y;
                    cpt=0;
                    this->EmissionSonValidation();
                }
                else if(positionCursseur.x==positionOptionEquipement[ENLEVER].x && positionCursseur.y==positionOptionEquipement[ENLEVER].y)
                {
                    positionCursseur.x=positionTexteStatNomArme[membre].x;
                    positionCursseur.y=positionTexteStatNomArme[membre].y;
                    cpt=2;
                    this->EmissionSonValidation();
                }
                else if(positionCursseur.x==positionTexteStatNomArme[membre].x && positionCursseur.y==positionTexteStatNomArme[membre].y && cpt==0)
                {
                    nb=0;
                    for(i=0; i<armeInventaire.size(); i++)
                    {
                        if(equipe[membre]->GetArmeEquipable() == armeInventaire[i]->GetCategorie())
                        {
                            nb++;
                        }
                    }
                    if(nb!=0)
                    {
                        cpt=1;
                        k=0;
                        positionCursseur.x=positionTexteNomArme[0].x;
                        positionCursseur.y=positionTexteNomArme[0].y;
                        this->EmissionSonValidation();
                    }
                    else
                    {
                        break;
                    }
                }
                else if(positionCursseur.x==positionTexteStatNomArme[membre].x && positionCursseur.y==positionTexteStatNomArme[membre].y && cpt==2)
                {
                    string weaponName = NULL;
                    if(equipe[membre]->GetClasse()=="Chevalier dragon" && equipe[membre]->GetArmeEquipe().GetCategorie() != "aucun")
                    {
                        Lance *substitut=new Lance(equipe[membre]->GetArmeEquipe().GetNom(), equipe[membre]->GetArmeEquipe().GetDegat());
                        armeInventaire.push_back(substitut);
                        weaponName = substitut->GetNom().c_str();
                    }
                    else if(equipe[membre]->GetClasse()=="Moine" && equipe[membre]->GetArmeEquipe().GetCategorie() != "aucun")
                    {
                        Gant *substitut=new Gant(equipe[membre]->GetArmeEquipe().GetNom(), equipe[membre]->GetArmeEquipe().GetDegat());
                        armeInventaire.push_back(substitut);
                        weaponName = substitut->GetNom().c_str();
                    }

                    Arme *aucune=new Arme("aucun");
                    equipe[membre]->EquiperArme(*aucune);
                    texteStatNomArme[membre] = SDL_CreateTextureFromSurface(ecran, TTF_RenderText_Blended(police, aucune->GetNom().c_str(), couleurCarac));
                    int texteStatNomArmeWidth = 0; 
                    int texteStatNomArmeHeight = 0;
                    TTF_SizeText(police, aucune->GetNom().c_str(), &texteStatNomArmeWidth, &texteStatNomArmeHeight);
                    positionTexteStatNomArme[membre].w = texteStatNomArmeWidth;
                    positionTexteStatNomArme[membre].h = texteStatNomArmeHeight;
                    nb=armeInventaire.size();
                    texteNomArme[nb-1] = SDL_CreateTextureFromSurface(ecran, TTF_RenderText_Blended(police, weaponName.c_str(), couleurCarac));
                    int texteNomArmeWidth = 0; 
                    int texteNomArmeHeight = 0;
                    TTF_SizeText(police, weaponName.c_str(), &texteNomArmeWidth, &texteNomArmeHeight);
                    positionTexteNomArme[membre].w = texteNomArmeWidth;
                    positionTexteNomArme[membre].h = texteNomArmeHeight;
                    this->EmissionSonValidation();
                }
                else if(positionCursseur.x==positionTexteStatNomArmure[CASQUE].x && positionCursseur.y==positionTexteStatNomArmure[CASQUE].y && cpt==0)
                {
                    arm=0;
                    for(i=0; i<casqueInventaire.size(); i++)
                    {
                        if(equipe[membre]->IsEquipable(casqueInventaire[i]->GetGenre()))
                        {
                            arm++;
                        }
                    }

                    if(arm!=0)
                    {
                        cpt=3;
                        k=0;
                        positionCursseur.x=positionTexteNomArmure[0].x;
                        positionCursseur.y=positionTexteNomArmure[0].y;
                        this->EmissionSonValidation();
                    }
                    else
                    {
                        break;
                    }

                }
                else if(positionCursseur.x==positionTexteStatNomArmure[CUIRASSE].x && positionCursseur.y==positionTexteStatNomArmure[CUIRASSE].y)
                {
                    cuir=0;
                    for(i=0; i<cuirasseInventaire.size(); i++)
                    {
                        if(equipe[membre]->IsEquipable(cuirasseInventaire[i]->GetGenre()))
                        {
                            cuir++;
                        }
                    }

                    if(cuir!=0)
                    {
                        cpt=4;
                        k=0;
                        positionCursseur.x=positionTexteNomCuirasse[0].x;
                        positionCursseur.y=positionTexteNomCuirasse[0].y;
                        this->EmissionSonValidation();
                    }
                    else
                    {
                        break;
                    }
                }
                else if(positionCursseur.x==positionTexteStatNomArmure[BOUCLIER].x && positionCursseur.y==positionTexteStatNomArmure[BOUCLIER].y)
                {
                    bouc=0;
                    for(i=0; i<bouclierInventaire.size(); i++)
                    {
                        if(equipe[membre]->IsEquipable(bouclierInventaire[i]->GetGenre()))
                        {
                            bouc++;
                        }
                    }

                    if(bouc!=0)
                    {
                        cpt=5;
                        k=0;
                        positionCursseur.x=positionTexteNomBouclier[0].x;
                        positionCursseur.y=positionTexteNomBouclier[0].y;
                        this->EmissionSonValidation();
                    }
                    else
                    {
                        break;
                    }
                }
                else if(positionCursseur.x==positionTexteStatNomArmure[JAMBIERE].x && positionCursseur.y==positionTexteStatNomArmure[JAMBIERE].y)
                {
                    jamb=0;
                    for(i=0; i<jambiereInventaire.size(); i++)
                    {
                        if(equipe[membre]->IsEquipable(jambiereInventaire[i]->GetGenre()))
                        {
                            jamb++;
                        }
                    }

                    if(jamb!=0)
                    {
                        cpt=6;
                        k=0;
                        positionCursseur.x=positionTexteNomJambiere[0].x;
                        positionCursseur.y=positionTexteNomJambiere[0].y;
                        this->EmissionSonValidation();
                    }
                    else
                    {
                        break;
                    }
                }
                else if(positionCursseur.x>=0 && positionCursseur.x<largeur/2 && positionCursseur.y>=positionTexteNomArme[0].y && positionCursseur.x<=hauteur && cpt==1)
                {
                    n=0;
                    for(i=0; i<armeInventaire.size(); i++)
                    {
                        if(equipe[membre]->GetArmeEquipable() == armeInventaire[i]->GetCategorie())
                        {
                            if(positionCursseur.x==positionTexteNomArme[abs(i-n)].x && positionCursseur.y==positionTexteNomArme[abs(i-n)].y && cpt==1)
                            {
                                vector<Arme*> copy;
                                copy=armeInventaire;
                                if(equipe[membre]->GetClasse()=="Chevalier dragon" && equipe[membre]->GetArmeEquipe().GetCategorie()!= "aucun")
                                {
                                    Lance *substitut=new Lance(equipe[membre]->GetArmeEquipe().GetNom(), equipe[membre]->GetArmeEquipe().GetDegat());
                                    copy.push_back(substitut);
                                }
                                else if(equipe[membre]->GetClasse()=="Moine" && equipe[membre]->GetArmeEquipe().GetCategorie()!= "aucun")
                                {
                                    Gant *substitut=new Gant(equipe[membre]->GetArmeEquipe().GetNom(), equipe[membre]->GetArmeEquipe().GetDegat());
                                    copy.push_back(substitut);
                                }

                                equipe[membre]->EquiperArme(*armeInventaire[i]);
                                texteStatNomArme[membre] = SDL_CreateTextureFromSurface(ecran, TTF_RenderText_Blended(police, armeInventaire[i]->GetNom().c_str(), couleurCarac));
                                int texteStatNomArmeWidth = 0; 
                                int texteStatNomArmeHeight = 0;
                                TTF_SizeText(police, armeInventaire[i]->GetNom().c_str(), &texteStatNomArmeWidth, &texteStatNomArmeHeight);
                                positionTexteStatNomArme[membre].w = texteStatNomArmeWidth;
                                positionTexteStatNomArme[membre].h = texteStatNomArmeHeight;
                                j=0;
                                l=0;

                                while(0!=armeInventaire.size())
                                {
                                    armeInventaire[j]=NULL;
                                    armeInventaire.pop_back();
                                    j++;
                                }
                                for(j=0; j<copy.size(); j++)
                                {
                                    if(j != i)
                                    {
                                        armeInventaire.push_back(copy[j]);
                                        nomArmeInventaire[l]=armeInventaire[l]->GetNom();
                                        texteNomArme[l] = SDL_CreateTextureFromSurface(ecran, TTF_RenderText_Blended(police, nomArmeInventaire[l].c_str(), couleurCarac));
                                        int texteNomArmeWidth = 0; 
                                        int texteNomArmeHeight = 0;
                                        TTF_SizeText(police, nomArmeInventaire[l].c_str(), &texteNomArmeWidth, &texteNomArmeHeight);
                                        positionTexteNomArme[membre].w = texteNomArmeWidth;
                                        positionTexteNomArme[membre].h = texteNomArmeHeight;
                                        l++;
                                    }
                                    
                                }
                                positionCursseur.x=positionTexteStatNomArme[membre].x;
                                positionCursseur.y=positionTexteStatNomArme[membre].y;
                                cpt=0;
                                k=0;
                            }
                        }
                        else
                        {
                            n++;
                        }
                    }
                    this->EmissionSonValidation();
                }
                else if(positionCursseur.x>=0 && positionCursseur.x<largeur/2 && positionCursseur.y>=positionTexteNomArmure[0].y && positionCursseur.x<=hauteur && cpt==3)
                {
                    n=0;
                    for(i=0; i<casqueInventaire.size(); i++)
                    {
                        if(equipe[membre]->IsEquipable(casqueInventaire[i]->GetGenre()))
                        {
                            if(positionCursseur.x==positionTexteNomArmure[abs(i-n)].x && positionCursseur.y==positionTexteNomArmure[abs(i-n)].y && cpt==3)
                            {
                                vector<Casque*> copy;
                                copy=casqueInventaire;
                                if(equipe[membre]->GetCasqueEquipe().GetGenre()!= "aucun")
                                {
                                    Casque *substitut=new Casque(equipe[membre]->GetCasqueEquipe().GetNom(), equipe[membre]->GetCasqueEquipe().GetGenre());
                                    copy.push_back(substitut);
                                }

                                if (membre==MEMBRE1)
                                {
                                    equipe[membre]->EquiperCasque(*casqueInventaire[i]);
                                    equipe[membre]->ModifierArmure(*casqueInventaire[i]);
                                    texteStatNomArmureM0[CASQUE] = SDL_CreateTextureFromSurface(ecran, TTF_RenderText_Blended(police, casqueInventaire[i]->GetNom().c_str(), couleurCarac)); 
                                }
                                else if (membre==MEMBRE2)
                                {
                                    equipe[membre]->EquiperCasque(*casqueInventaire[i]);
                                    equipe[membre]->ModifierArmure(*casqueInventaire[i]);
                                    texteStatNomArmureM1[CASQUE] = SDL_CreateTextureFromSurface(ecran, TTF_RenderText_Blended(police, casqueInventaire[i]->GetNom().c_str(), couleurCarac));
                                }
                                j=0;
                                l=0;

                                while(0!=casqueInventaire.size())
                                {
                                    casqueInventaire[j]=NULL;
                                    casqueInventaire.pop_back();
                                    j++;
                                }
                                for(j=0; j<copy.size(); j++)
                                {
                                    if(j==i)
                                    {

                                    }
                                    else
                                    {
                                        casqueInventaire.push_back(copy[j]);
                                        nomArmureInventaire[l]=casqueInventaire[l]->GetNom();
                                        texteNomArmure[l] = SDL_CreateTextureFromSurface(ecran, TTF_RenderText_Blended(police, nomArmureInventaire[l].c_str(), couleurCarac));
                                        l++;
                                    }
                                }
                                positionCursseur.x=positionTexteStatNomArmure[0].x;
                                positionCursseur.y=positionTexteStatNomArmure[0].y;
                                cpt=0;
                                k=0;
                            }
                        }
                        else
                        {
                            n++;
                        }
                    }
                    flag=0;
                    this->EmissionSonValidation();
                }
                else if(positionCursseur.x>=0 && positionCursseur.x<largeur/2 && positionCursseur.y>=positionTexteNomCuirasse[0].y && positionCursseur.x<=hauteur && cpt==4)
                {
                    n=0;
                    for(i=0; i<cuirasseInventaire.size(); i++)
                    {
                        if(equipe[membre]->IsEquipable(cuirasseInventaire[i]->GetGenre()))
                        {
                            if(positionCursseur.x==positionTexteNomCuirasse[abs(i-n)].x && positionCursseur.y==positionTexteNomCuirasse[abs(i-n)].y && cpt==4)
                            {
                                vector<Cuirasse*> copy;
                                copy=cuirasseInventaire;
                                if(equipe[membre]->GetCuirasseEquipe().GetGenre()!= "aucun")
                                {
                                    Cuirasse *substitut=new Cuirasse(equipe[membre]->GetCuirasseEquipe().GetNom(), equipe[membre]->GetCuirasseEquipe().GetGenre());
                                    copy.push_back(substitut);
                                }

                                if (membre==MEMBRE1)
                                {
                                    equipe[membre]->EquiperCuirasse(*cuirasseInventaire[i]);
                                    equipe[membre]->ModifierArmure(*cuirasseInventaire[i]);
                                    texteStatNomArmureM0[CUIRASSE] = SDL_CreateTextureFromSurface(ecran, TTF_RenderText_Blended(police, cuirasseInventaire[i]->GetNom().c_str(), couleurCarac));
                                }
                                else if (membre==MEMBRE2)
                                {
                                    equipe[membre]->EquiperCuirasse(*cuirasseInventaire[i]);
                                    equipe[membre]->ModifierArmure(*cuirasseInventaire[i]);
                                    texteStatNomArmureM1[CUIRASSE] = SDL_CreateTextureFromSurface(ecran, TTF_RenderText_Blended(police, cuirasseInventaire[i]->GetNom().c_str(), couleurCarac));
                                }
                                j=0;
                                l=0;

                                while(0!=cuirasseInventaire.size())
                                {
                                    cuirasseInventaire[j]=NULL;
                                    cuirasseInventaire.pop_back();
                                    j++;
                                }
                                for(j=0; j<copy.size(); j++)
                                {
                                    if(j==i)
                                    {

                                    }
                                    else
                                    {
                                        cuirasseInventaire.push_back(copy[j]);
                                        nomCuirasseInventaire[l]=cuirasseInventaire[l]->GetNom();
                                        texteNomCuirasse[l] = SDL_CreateTextureFromSurface(ecran, TTF_RenderText_Blended(police, nomCuirasseInventaire[l].c_str(), couleurCarac));
                                        l++;
                                    }
                                }
                                positionCursseur.x=positionTexteStatNomArmure[1].x;
                                positionCursseur.y=positionTexteStatNomArmure[1].y;
                                cpt=0;
                                k=0;
                            }
                        }
                        else
                        {
                            n++;
                        }
                    }
                    flag=0;
                    this->EmissionSonValidation();
                }
                else if(positionCursseur.x>=0 && positionCursseur.x<largeur/2 && positionCursseur.y>=positionTexteNomBouclier[0].y && positionCursseur.x<=hauteur && cpt==5)
                {
                    n=0;
                    for(i=0; i<bouclierInventaire.size(); i++)
                    {
                        if(equipe[membre]->IsEquipable(bouclierInventaire[i]->GetGenre()))
                        {
                            if(positionCursseur.x==positionTexteNomBouclier[abs(i-n)].x && positionCursseur.y==positionTexteNomBouclier[abs(i-n)].y && cpt==5)
                            {
                                vector<Bouclier*> copy;
                                copy=bouclierInventaire;
                                if(equipe[membre]->GetBouclierEquipe().GetGenre()!= "aucun")
                                {
                                    Bouclier *substitut=new Bouclier(equipe[membre]->GetBouclierEquipe().GetNom(), equipe[membre]->GetBouclierEquipe().GetGenre());
                                    copy.push_back(substitut);
                                }

                                if (membre==MEMBRE1)
                                {
                                    equipe[membre]->EquiperBouclier(*bouclierInventaire[i]);
                                    equipe[membre]->ModifierArmure(*bouclierInventaire[i]);
                                    texteStatNomArmureM0[BOUCLIER] = SDL_CreateTextureFromSurface(ecran, TTF_RenderText_Blended(police, bouclierInventaire[i]->GetNom().c_str(), couleurCarac));
                                }
                                else if (membre==MEMBRE2)
                                {
                                    equipe[membre]->EquiperBouclier(*bouclierInventaire[i]);
                                    equipe[membre]->ModifierArmure(*bouclierInventaire[i]);
                                    texteStatNomArmureM1[BOUCLIER] = SDL_CreateTextureFromSurface(ecran, TTF_RenderText_Blended(police, bouclierInventaire[i]->GetNom().c_str(), couleurCarac));
                                }
                                j=0;
                                l=0;

                                while(0!=bouclierInventaire.size())
                                {
                                    bouclierInventaire[j]=NULL;
                                    bouclierInventaire.pop_back();
                                    j++;
                                }
                                for(j=0; j<copy.size(); j++)
                                {
                                    if(j==i)
                                    {

                                    }
                                    else
                                    {
                                        bouclierInventaire.push_back(copy[j]);
                                        nomBouclierInventaire[l]=bouclierInventaire[l]->GetNom();
                                        texteNomBouclier[l] = SDL_CreateTextureFromSurface(ecran, TTF_RenderText_Blended(police, nomBouclierInventaire[l].c_str(), couleurCarac));
                                        l++;
                                    }
                                }
                                positionCursseur.x=positionTexteStatNomArmure[2].x;
                                positionCursseur.y=positionTexteStatNomArmure[2].y;
                                cpt=0;
                                k=0;
                            }
                        }
                        else
                        {
                            n++;
                        }
                    }
                    flag=0;
                    this->EmissionSonValidation();
                }

                else if(positionCursseur.x>=0 && positionCursseur.x<largeur/2 && positionCursseur.y>=positionTexteNomJambiere[0].y && positionCursseur.x<=hauteur && cpt==6)
                {
                    n=0;
                    for(i=0; i<jambiereInventaire.size(); i++)
                    {
                        if(equipe[membre]->IsEquipable(jambiereInventaire[i]->GetGenre()))
                        {
                            if(positionCursseur.x==positionTexteNomJambiere[abs(i-n)].x && positionCursseur.y==positionTexteNomJambiere[abs(i-n)].y && cpt==6)
                            {
                                vector<Jambiere*> copy;
                                copy=jambiereInventaire;
                                if(equipe[membre]->GetJambiereEquipe().GetGenre()!= "aucun")
                                {
                                    Jambiere *substitut=new Jambiere(equipe[membre]->GetJambiereEquipe().GetNom(), equipe[membre]->GetJambiereEquipe().GetGenre());
                                    copy.push_back(substitut);
                                }

                                if (membre==MEMBRE1)
                                {
                                    equipe[membre]->EquiperJambiere(*jambiereInventaire[i]);
                                    equipe[membre]->ModifierArmure(*jambiereInventaire[i]);
                                    texteStatNomArmureM0[JAMBIERE] = SDL_CreateTextureFromSurface(ecran, TTF_RenderText_Blended(police, jambiereInventaire[i]->GetNom().c_str(), couleurCarac));
                                }
                                else if (membre==MEMBRE2)
                                {
                                    equipe[membre]->EquiperJambiere(*jambiereInventaire[i]);
                                    equipe[membre]->ModifierArmure(*jambiereInventaire[i]);
                                    texteStatNomArmureM1[JAMBIERE] = SDL_CreateTextureFromSurface(ecran, TTF_RenderText_Blended(police, jambiereInventaire[i]->GetNom().c_str(), couleurCarac));
                                }
                                j=0;
                                l=0;

                                while(0!=jambiereInventaire.size())
                                {
                                    jambiereInventaire[j]=NULL;
                                    jambiereInventaire.pop_back();
                                    j++;
                                }
                                for(j=0; j<copy.size(); j++)
                                {
                                    if(j==i)
                                    {

                                    }
                                    else
                                    {
                                        jambiereInventaire.push_back(copy[j]);
                                        nomJambiereInventaire[l]=jambiereInventaire[l]->GetNom();
                                        texteNomJambiere[l] = SDL_CreateTextureFromSurface(ecran, TTF_RenderText_Blended(police, nomJambiereInventaire[l].c_str(), couleurCarac));
                                        l++;
                                    }
                                }
                                positionCursseur.x=positionTexteStatNomArmure[3].x;
                                positionCursseur.y=positionTexteStatNomArmure[3].y;
                                cpt=0;
                                k=0;
                            }
                        }
                        else
                        {
                            n++;
                        }
                    }
                    flag=0;
                    this->EmissionSonValidation();
                }
                break;

                case SDLK_UP:
                if(positionCursseur.x==positionTexteStatNomArme[membre].x && positionCursseur.y==positionTexteStatNomArme[membre].y && (cpt==0 || cpt==2))
                {
                    positionCursseur.y=positionTexteStatNomArmure[JAMBIERE].y;
                    haut=JAMBIERE;
                    this->EmissionSonDeplacement();
                }
                else if(positionCursseur.x==positionTexteStatNomArmure[CASQUE].x && positionCursseur.y==positionTexteStatNomArmure[CASQUE].y && (cpt==0 || cpt==2))
                {
                    positionCursseur.y=positionTexteStatNomArme[membre].y;
                    this->EmissionSonDeplacement();
                }
                else if(positionCursseur.y>=positionTexteStatNomArmure[CASQUE].y && (cpt==0 || cpt==2))
                {
                    positionCursseur.y=positionTexteStatNomArmure[--haut].y;
                    this->EmissionSonDeplacement();
                }
                else if(positionCursseur.y==positionTexteNomArme[0].y && cpt==1)
                {
                    positionCursseur.y=positionTexteNomArme[nb-1].y;
                    k=nb-1;
                    this->EmissionSonDeplacement();
                }
                else if(positionCursseur.y!=positionTexteNomArme[0].y && cpt==1)
                {
                    positionCursseur.y=positionTexteNomArme[--k].y;
                    this->EmissionSonDeplacement();
                }
                else if(positionCursseur.y==positionTexteNomArmure[0].y && cpt==3)
                {
                    positionCursseur.y=positionTexteNomArmure[arm-1].y;
                    k=arm-1;
                    this->EmissionSonDeplacement();
                }
                else if(positionCursseur.y!=positionTexteNomArmure[0].y && cpt==3)
                {
                    positionCursseur.y=positionTexteNomArmure[--k].y;
                    this->EmissionSonDeplacement();
                }
                else if(positionCursseur.y==positionTexteNomCuirasse[0].y && cpt==4)
                {
                    positionCursseur.y=positionTexteNomCuirasse[cuir-1].y;
                    k=cuir-1;
                    this->EmissionSonDeplacement();
                }
                else if(positionCursseur.y!=positionTexteNomCuirasse[0].y && cpt==4)
                {
                    positionCursseur.y=positionTexteNomCuirasse[--k].y;
                    this->EmissionSonDeplacement();
                }
                else if(positionCursseur.y==positionTexteNomBouclier[0].y && cpt==5)
                {
                    positionCursseur.y=positionTexteNomBouclier[bouc-1].y;
                    k=bouc-1;
                    this->EmissionSonDeplacement();
                }
                else if(positionCursseur.y!=positionTexteNomBouclier[0].y && cpt==5)
                {
                    positionCursseur.y=positionTexteNomBouclier[--k].y;
                    this->EmissionSonDeplacement();
                }
                else if(positionCursseur.y==positionTexteNomJambiere[0].y && cpt==6)
                {
                    positionCursseur.y=positionTexteNomJambiere[jamb-1].y;
                    k=jamb-1;
                    this->EmissionSonDeplacement();
                }
                else if(positionCursseur.y!=positionTexteNomJambiere[0].y && cpt==6)
                {
                    positionCursseur.y=positionTexteNomJambiere[--k].y;
                    this->EmissionSonDeplacement();
                }
                else if(positionCursseur.x==positionOptionEquipement[ENLEVER].x && positionCursseur.y==positionOptionEquipement[ENLEVER].y)
                {
                    break;
                }
                else if(positionCursseur.x==positionOptionEquipement[EQUIPER].x && positionCursseur.y==positionOptionEquipement[EQUIPER].y)
                {
                    break;
                }
                break;

                case SDLK_DOWN:
                if(positionCursseur.x==positionTexteStatNomArmure[JAMBIERE].x && positionCursseur.y==positionTexteStatNomArmure[JAMBIERE].y && (cpt==0 || cpt==2))
                {
                    positionCursseur.y=positionTexteStatNomArme[membre].y;
                    haut=0;
                    this->EmissionSonDeplacement();
                }
                else if(positionCursseur.x==positionTexteStatNomArme[membre].x && positionCursseur.y==positionTexteStatNomArme[membre].y && (cpt==0 || cpt==2))
                {
                    positionCursseur.y=positionTexteStatNomArmure[CASQUE].y;
                    haut=CASQUE;
                    this->EmissionSonDeplacement();
                }
                else if(positionCursseur.y>=positionTexteStatNomArmure[CASQUE].y && (cpt==0 || cpt==2))
                {
                    positionCursseur.y=positionTexteStatNomArmure[++haut].y;
                    this->EmissionSonDeplacement();
                }
                else if(positionCursseur.y==positionTexteNomArme[nb-1].y && cpt==1)
                {
                    positionCursseur.y=positionTexteNomArme[0].y;
                    k=0;
                    this->EmissionSonDeplacement();
                }
                else if(positionCursseur.y!=positionTexteNomArme[nb-1].y && cpt==1)
                {
                    positionCursseur.y=positionTexteNomArme[++k].y;
                    this->EmissionSonDeplacement();
                }
                else if(positionCursseur.y==positionTexteNomArmure[arm-1].y && cpt==3)
                {
                    positionCursseur.y=positionTexteNomArmure[0].y;
                    k=0;
                    this->EmissionSonDeplacement();
                }
                else if(positionCursseur.y!=positionTexteNomArmure[arm-1].y && cpt==3)
                {
                    positionCursseur.y=positionTexteNomArmure[++k].y;
                    this->EmissionSonDeplacement();
                }
                else if(positionCursseur.y==positionTexteNomCuirasse[cuir-1].y && cpt==4)
                {
                    positionCursseur.y=positionTexteNomCuirasse[0].y;
                    k=0;
                    this->EmissionSonDeplacement();
                }
                else if(positionCursseur.y!=positionTexteNomCuirasse[cuir-1].y && cpt==4)
                {
                    positionCursseur.y=positionTexteNomCuirasse[++k].y;
                    this->EmissionSonDeplacement();
                }
                else if(positionCursseur.y==positionTexteNomBouclier[bouc-1].y && cpt==5)
                {
                    positionCursseur.y=positionTexteNomBouclier[0].y;
                    k=0;
                    this->EmissionSonDeplacement();
                }
                else if(positionCursseur.y!=positionTexteNomBouclier[bouc-1].y && cpt==5)
                {
                    positionCursseur.y=positionTexteNomBouclier[++k].y;
                    this->EmissionSonDeplacement();
                }
                else if(positionCursseur.y==positionTexteNomJambiere[jamb-1].y && cpt==6)
                {
                    positionCursseur.y=positionTexteNomJambiere[0].y;
                    k=0;
                    this->EmissionSonDeplacement();
                }
                else if(positionCursseur.y!=positionTexteNomJambiere[jamb-1].y && cpt==6)
                {
                    positionCursseur.y=positionTexteNomJambiere[++k].y;
                    this->EmissionSonDeplacement();
                }
                else if(positionCursseur.x==positionOptionEquipement[ENLEVER].x && positionCursseur.y==positionOptionEquipement[ENLEVER].y)
                {
                    break;
                }
                else if(positionCursseur.x==positionOptionEquipement[EQUIPER].x && positionCursseur.y==positionOptionEquipement[EQUIPER].y)
                {
                    break;
                }
                else
                {
                    positionCursseur.y=positionTexteNomArme[++k].y;
                    this->EmissionSonDeplacement();
                }
                break;

                case SDLK_RIGHT:
                if(positionCursseur.x==positionOptionEquipement[ENLEVER].x)
                {
                    positionCursseur.x=positionOptionEquipement[EQUIPER].x;
                    this->EmissionSonDeplacement();
                }
                else if(positionCursseur.x==positionOptionEquipement[EQUIPER].x)
                {
                    positionCursseur.x=positionOptionEquipement[ENLEVER].x;
                    this->EmissionSonDeplacement();
                }
                break;

                case SDLK_LEFT:
                if(positionCursseur.x==positionOptionEquipement[EQUIPER].x && cpt==0)
                {
                    positionCursseur.x=positionOptionEquipement[ENLEVER].x;
                    this->EmissionSonDeplacement();
                }
                else if(positionCursseur.x==positionOptionEquipement[ENLEVER].x && cpt==0)
                {
                    positionCursseur.x=positionOptionEquipement[EQUIPER].x;
                    this->EmissionSonDeplacement();
                }
                break;

                case SDLK_KP_6:
                if(membre==(taille-1) && (cpt==0 || cpt==2))
                {
                    membre=MEMBRE1;
                    this->EmissionSonDeplacement();
                }
                else if(membre!=(taille-1) && (cpt==0 || cpt==2))
                {
                    membre++;
                    this->EmissionSonDeplacement();
                }
                else if(cpt==1)
                {
                    break;
                }
                break;

                case SDLK_KP_4:
                if(membre==MEMBRE1 && (cpt==0 || cpt==2))
                {
                    membre=taille-1;
                    this->EmissionSonDeplacement();
                }
                else if(cpt==1)
                {
                    break;
                }
                else if(membre!=MEMBRE1 && (cpt==0 || cpt==2))
                {
                    membre--;
                    this->EmissionSonDeplacement();
                }
                break;

                default:
                cout<<"ok"<<endl;
                break;
            }
            break;
        }
        n=0;
        for(m=0; m<armeInventaire.size(); m++)
        {
            if(equipe[membre]->GetArmeEquipable()== armeInventaire[m]->GetCategorie())
            {
                if(positionCursseur.y==positionTexteNomArme[abs(m-n)].y && cpt==1)
                {
                    sprintf(tableauDegat, "+%d", armeInventaire[m]->GetDegat());
                    InfoArmeFr = SDL_CreateTextureFromSurface(ecran, TTF_RenderText_Blended(police, tableauDegat, couleurAjout));
                    int InfoArmeFrWidth = 0;
                    int InfoArmeFrHeight = 0;
                    TTF_SizeText(police, tableauDegat, &InfoArmeFrWidth, &InfoArmeFrHeight);
                    positionInfoArmeFr.w = InfoArmeFrWidth;
                    positionInfoArmeFr.h = InfoArmeFrHeight;
                    flag=1;
                }
            }
            else
            {
                n++;
            }
        }
        n=0;
        for(m=0; m<casqueInventaire.size(); m++)
        {
            if(equipe[membre]->IsEquipable(casqueInventaire[m]->GetGenre()))
            {
                if(positionCursseur.y==positionTexteNomArmure[abs(m-n)].y && cpt==3)
                {
                    sprintf(tableauInfoCasque, "+%d", casqueInventaire[m]->GetDefPhy());
                    InfoArmeDef = SDL_CreateTextureFromSurface(ecran, TTF_RenderText_Blended(police, tableauInfoCasque, couleurAjout));
                    int InfoArmeDefWidth = 0;
                    int InfoArmeDefHeight = 0;
                    TTF_SizeText(police, tableauInfoCasque, &InfoArmeDefWidth, &InfoArmeDefHeight);
                    positionInfoArmeDef.w = InfoArmeDefWidth;
                    positionInfoArmeDef.h = InfoArmeDefHeight;
                    sprintf(tableauInfoCasque, "+%d", casqueInventaire[m]->GetDefMag());
                    InfoArmeMag = SDL_CreateTextureFromSurface(ecran, TTF_RenderText_Blended(police, tableauInfoCasque, couleurAjout));
                    int InfoArmeMagWidth = 0;
                    int InfoArmeMagHeight = 0;
                    TTF_SizeText(police, tableauInfoCasque, &InfoArmeMagWidth, &InfoArmeMagHeight);
                    positionInfoArmeMag.w = InfoArmeMagWidth;
                    positionInfoArmeMag.h = InfoArmeMagHeight;
                    flag=2;
                }
            }
            else
            {
                n++;
            }
        }
        n=0;
        for(m=0; m<cuirasseInventaire.size(); m++)
        {
            if(equipe[membre]->IsEquipable(cuirasseInventaire[m]->GetGenre()))
            {
                if(positionCursseur.y==positionTexteNomCuirasse[abs(m-n)].y && cpt==4)
                {
                    sprintf(tableauInfoCuirasse, "+%d", cuirasseInventaire[m]->GetDefPhy());
                    InfoArmeDef = SDL_CreateTextureFromSurface(ecran, TTF_RenderText_Blended(police, tableauInfoCuirasse, couleurAjout));
                    int InfoArmeDefWidth = 0;
                    int InfoArmeDefHeight = 0;
                    TTF_SizeText(police, tableauInfoCuirasse, &InfoArmeDefWidth, &InfoArmeDefHeight);
                    positionInfoArmeDef.w = InfoArmeDefWidth;
                    positionInfoArmeDef.h = InfoArmeDefHeight;
                    sprintf(tableauInfoCuirasse, "+%d", cuirasseInventaire[m]->GetDefMag());
                    InfoArmeMag = SDL_CreateTextureFromSurface(ecran, TTF_RenderText_Blended(police, tableauInfoCuirasse, couleurAjout));
                    int InfoArmeMagWidth = 0;
                    int InfoArmeMagHeight = 0;
                    TTF_SizeText(police, tableauInfoCuirasse, &InfoArmeMagWidth, &InfoArmeMagHeight);
                    positionInfoArmeMag.w = InfoArmeMagWidth;
                    positionInfoArmeMag.h = InfoArmeMagHeight;
                    flag=3;
                }
            }
            else
            {
                n++;
            }
        }
        n=0;
        for(m=0; m<bouclierInventaire.size(); m++)
        {
            if(equipe[membre]->IsEquipable(bouclierInventaire[m]->GetGenre()))
            {
                if(positionCursseur.y==positionTexteNomBouclier[abs(m-n)].y && cpt==5)
                {
                    sprintf(tableauInfoBouclier, "+%d", bouclierInventaire[m]->GetDefPhy());
                    InfoArmeDef = SDL_CreateTextureFromSurface(ecran, TTF_RenderText_Blended(police, tableauInfoBouclier, couleurAjout));
                    int InfoArmeDefWidth = 0;
                    int InfoArmeDefHeight = 0;
                    TTF_SizeText(police, tableauInfoBouclier, &InfoArmeDefWidth, &InfoArmeDefHeight);
                    positionInfoArmeDef.w = InfoArmeDefWidth;
                    positionInfoArmeDef.h = InfoArmeDefHeight;
                    sprintf(tableauInfoBouclier, "+%d", bouclierInventaire[m]->GetDefMag());
                    InfoArmeMag = SDL_CreateTextureFromSurface(ecran, TTF_RenderText_Blended(police, tableauInfoBouclier, couleurAjout));
                    int InfoArmeMagWidth = 0;
                    int InfoArmeMagHeight = 0;
                    TTF_SizeText(police, tableauInfoBouclier, &InfoArmeMagWidth, &InfoArmeMagHeight);
                    positionInfoArmeMag.w = InfoArmeMagWidth;
                    positionInfoArmeMag.h = InfoArmeMagHeight;
                    flag=4;
                }
            }
            else
            {
                n++;
            }
        }
        n=0;
        for(m=0; m<jambiereInventaire.size(); m++)
        {
            if(equipe[membre]->IsEquipable(jambiereInventaire[m]->GetGenre()))
            {
                if(positionCursseur.y==positionTexteNomJambiere[abs(m-n)].y && cpt==6)
                {
                    sprintf(tableauInfoJambiere, "+%d", jambiereInventaire[m]->GetDefPhy());
                    InfoArmeDef = SDL_CreateTextureFromSurface(ecran, TTF_RenderText_Blended(police, tableauInfoJambiere, couleurAjout));
                    int InfoArmeDefWidth = 0;
                    int InfoArmeDefHeight = 0;
                    TTF_SizeText(police, tableauInfoJambiere, &InfoArmeDefWidth, &InfoArmeDefHeight);
                    positionInfoArmeDef.w = InfoArmeDefWidth;
                    positionInfoArmeDef.h = InfoArmeDefHeight;
                    sprintf(tableauInfoJambiere, "+%d", jambiereInventaire[m]->GetDefMag());
                    InfoArmeMag = SDL_CreateTextureFromSurface(ecran, TTF_RenderText_Blended(police, tableauInfoJambiere, couleurAjout));
                    int InfoArmeMagWidth = 0;
                    int InfoArmeMagHeight = 0;
                    TTF_SizeText(police, tableauInfoJambiere, &InfoArmeMagWidth, &InfoArmeMagHeight);
                    positionInfoArmeMag.w = InfoArmeMagWidth;
                    positionInfoArmeMag.h = InfoArmeMagHeight;
                    flag=5;
                }
            }
            else
            {
                n++;
            }
        }
        
        DisplayMenuElements(equipe, armeInventaire, casqueInventaire, cuirasseInventaire, bouclierInventaire, jambiereInventaire, membre, ecran, cpt, flag);
    }
    obj->SetArmeInventaire(armeInventaire);
    obj->SetCasqueInventaire(casqueInventaire);
    obj->SetCuirasseInventaire(cuirasseInventaire);
    obj->SetBouclierInventaire(bouclierInventaire);
    obj->SetJambiereInventaire(jambiereInventaire);
}

void SmenuEquipement::DisplayMenuElements(std::vector<Personnage*> equipe, std::vector<Arme*> armeInventaire, std::vector<Casque*> casqueInventaire, std::vector<Cuirasse*> cuirasseInventaire, std::vector<Bouclier*> bouclierInventaire, std::vector<Jambiere*> jambiereInventaire, int memberId, SDL_Renderer *ecran, int cpt, int flag)
{
    //cpt = 0 => EQUIPER
    //cpt = 2 => ENELVER
    //cpt = 1 => ARME
    //cpt = 3 => CASQUE
    //cpt = 4 => CUIRASSE
    //cpt = 5 => BOUCLIER
    //cpt = 6 => JAMBIERE
    SDL_SetRenderDrawColor(ecran, 180, 180, 180, SDL_ALPHA_OPAQUE );
    SDL_RenderClear(ecran);
    SDL_RenderCopy(ecran, fenMenu, NULL, &positionMenu);

    SDL_SetRenderDrawBlendMode(ecran, SDL_BLENDMODE_BLEND);
    SDL_SetRenderDrawColor(ecran, 255, 255, 36, 70 );
    SDL_RenderFillRect(ecran, &positionCursseur);


    std::vector<SDL_Texture*> equipement_name_textures;
    std::vector<SDL_Rect> equipement_name_rectangles;
    
    for(int i = 0; i < armeInventaire.size(); i++)
    {
        if(equipe[memberId]->GetArmeEquipable() == armeInventaire[i]->GetCategorie() && (cpt == 0 || cpt == 2 || cpt == 1))
        {
            equipement_name_textures.push_back(texteNomArme[i]);
            equipement_name_rectangles.push_back(positionTexteNomArme[i]);
            printf("memberId => %d can equip %s\n", memberId, texteNomArme[i]);
        }
    }

    for(int i = 0; i < casqueInventaire.size(); i++)
    {
        if(equipe[memberId]->IsEquipable(casqueInventaire[i]->GetGenre()) && (cpt == 0 || cpt == 2 || cpt == 3))
        {
            equipement_name_textures.push_back(texteNomArmure[i]);
            equipement_name_rectangles.push_back(positionTexteNomArmure[i]);
        }
    }

    for(int i = 0; i < cuirasseInventaire.size(); i++)
    {
        if(equipe[memberId]->IsEquipable(cuirasseInventaire[i]->GetGenre()) && (cpt == 0 || cpt == 2 || cpt == 4))
        {
            equipement_name_textures.push_back(texteNomCuirasse[i]);
            equipement_name_rectangles.push_back(positionTexteNomCuirasse[i]);
        }
    }

    for(int i = 0; i < bouclierInventaire.size(); i++)
    {
        if(equipe[memberId]->IsEquipable(bouclierInventaire[i]->GetGenre()) && (cpt == 0 || cpt == 2) || cpt == 5)
        {
            equipement_name_textures.push_back(texteNomBouclier[i]);
            equipement_name_rectangles.push_back(positionTexteNomBouclier[i]);
        }
    }

    for(int i = 0; i < jambiereInventaire.size(); i++)
    {
        if(equipe[memberId]->IsEquipable(jambiereInventaire[i]->GetGenre()) && (cpt == 0 || cpt == 2) || cpt == 6)
        {
            equipement_name_textures.push_back(texteNomJambiere[i]);
            equipement_name_rectangles.push_back(positionTexteNomJambiere[i]);
        }
    }

    for(int i = 0; i < equipement_name_textures.size(); i++)
    {
        SDL_Rect customRectangle;
        customRectangle.x = 0;
        customRectangle.h = equipement_name_rectangles[i].h;
        customRectangle.w = equipement_name_rectangles[i].w;

        if(i==0)
        {
            customRectangle.y = (i + 1) *  265;
        }
        else
        {
            customRectangle.y = (i + 1) *  265 + 30;
        }

        //printf("pos x = %d | pos y = %d\n", customRectangle.x, customRectangle.y);
        SDL_RenderCopy(ecran, equipement_name_textures[i], NULL, &customRectangle);
    }


    std::vector<Equipement> equipements = equipe[memberId]->GetArmureEquipe();

    for(int j = 0; j < equipements.size(); j++)
    {
        if(memberId == MEMBRE1)
        {
            SDL_RenderCopy(ecran, texteStatNomArmureM0[j], NULL, &positionTexteStatNomArmure[j]);
        }
        if(memberId == MEMBRE2)
        {
            SDL_RenderCopy(ecran, texteStatNomArmureM1[j], NULL, &positionTexteStatNomArmure[j]);
        }
    }

    SDL_RenderCopy(ecran, texteStatPv[memberId], NULL, &positionTexteStatPv[memberId]);
    SDL_RenderCopy(ecran, texteStatPm[memberId], NULL, &positionTexteStatPm[memberId]);
    SDL_RenderCopy(ecran, texteStatFr[memberId], NULL, &positionTexteStatFr[memberId]);
    SDL_RenderCopy(ecran, texteStatDef[memberId], NULL, &positionTexteStatDef[memberId]);
    SDL_RenderCopy(ecran, texteStatMag[memberId], NULL, &positionTexteStatMag[memberId]);
    SDL_RenderCopy(ecran, texteStatVol[memberId], NULL, &positionTexteStatVol[memberId]);
    SDL_RenderCopy(ecran, texteStatVit[memberId], NULL, &positionTexteStatVit[memberId]);
    SDL_RenderCopy(ecran, texteStatPrc[memberId], NULL, &positionTexteStatPrc[memberId]);
    SDL_RenderCopy(ecran, texteStatEsq[memberId], NULL, &positionTexteStatEsq[memberId]);
    SDL_RenderCopy(ecran, texteStatCha[memberId], NULL, &positionTexteStatCha[memberId]);
    SDL_RenderCopy(ecran, texteStatNomArme[memberId], NULL, &positionTexteStatNomArme[memberId]);
    SDL_RenderCopy(ecran, texteStatPrenom[memberId], NULL, &positionTexteStatPrenom[memberId]);


    for(int i = 0; i < 5; i++)
    {
        SDL_RenderCopy(ecran, texteEquipement[i], NULL, &positionTexteEquipement[i]);
    }

    SDL_SetRenderDrawColor(ecran, 255, 255, 255, SDL_ALPHA_OPAQUE);
    SDL_RenderFillRect(ecran, &positionLigne);

    for(int i = 0; i < 2; i++)
    {
        SDL_SetRenderDrawColor(ecran, 255, 255, 255, SDL_ALPHA_OPAQUE);
        SDL_RenderFillRect(ecran, &positionLigneHorizontale[i]);  
    }

    SDL_RenderCopy(ecran, titreMenu, NULL, &positionTitreMenu);

    for(int i = 0; i < 2; i++)
    {
        SDL_RenderCopy(ecran, optionEquipement[i], NULL, &positionOptionEquipement[i]);
    }
    
    SDL_RenderCopy(ecran, tof, &clip[memberId], &positionTof);

    if(flag == 1)
    {
        SDL_RenderCopy(ecran, InfoArmeFr, NULL, &positionInfoArmeFr);
    }

    if(flag == 2 || flag == 3 || flag == 4 || flag == 5 || flag == 6)
    {
        SDL_RenderCopy(ecran, InfoArmeDef, NULL, &positionInfoArmeDef);
        SDL_RenderCopy(ecran, InfoArmeMag, NULL, &positionInfoArmeMag);
    }
   
    SDL_RenderPresent(ecran);
}

