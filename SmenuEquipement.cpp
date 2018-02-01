#include <cstdlib>
#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include <ft2build.h>
#include <SDL/SDL_ttf.h>
#include <fmodex/fmod.h>
#include <freetype/freetype.h>
#include "SmenuEquipement.h"
#include "Jeu.h"
#include "Lance.h"
#include "Gant.h"
#include <string>
#include <iostream>
#include <vector>
using namespace std;

SmenuEquipement::SmenuEquipement(SDL_Surface *ecran)
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

SmenuEquipement:: ~SmenuEquipement()
{
    FMOD_System_Close(system);
    FMOD_System_Release(system);
    FMOD_Sound_Release(sonDeplacement);
    FMOD_Sound_Release(sonValidation);
}

void SmenuEquipement::AffichageEquipement(std::vector<Personnage*> equipe, SDL_Surface *ecran, std::vector<Arme*> armeInventaire, std::vector<Casque*> casqueInventaire, std::vector<Cuirasse*> cuirasseInventaire, std::vector<Bouclier*> bouclierInventaire, std::vector<Jambiere*> jambiereInventaire, Jeu *obj)
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
    //TTF_SetFontStyle(police, TTF_STYLE_BOLD | TTF_STYLE_UNDERLINE | TTF_STYLE_ITALIC);
    couleurCursseur= SDL_MapRGB(ecran->format, 255, 255, 36);
    positionCursseur.w=105;
    positionCursseur.h=35;
    positionCursseur.x=(largeur+5)/2;
    positionCursseur.y=0;
    cursseur= SDL_CreateRGBSurface(SDL_HWSURFACE, positionCursseur.w, positionCursseur.h, NB_BITS_PAR_PIXEL, 0, 0, 0, 0);
    SDL_FillRect(cursseur, NULL, couleurCursseur);
    SDL_SetAlpha(cursseur, SDL_SRCALPHA, 70);

    for(i=0; i<nb; i++)
    {
        if(i==0)
        {
            nomArmeInventaire[i]=armeInventaire[i]->GetNom();
            degat[i]=armeInventaire[i]->GetDegat();
            sprintf(tableauDegat, "%d", degat[i]);
            texteNomArme[i] = TTF_RenderText_Blended(police, nomArmeInventaire[i].c_str(), couleurCarac);
            positionTexteNomArme[i].x=0;
            positionTexteNomArme[i].y=265;
        }
        else
        {
            nomArmeInventaire[i]=armeInventaire[i]->GetNom();
            degat[i]=armeInventaire[i]->GetDegat();
            sprintf(tableauDegat, "%d", degat[i]);
            texteNomArme[i] = TTF_RenderText_Blended(police, nomArmeInventaire[i].c_str(), couleurCarac);
            positionTexteNomArme[i].x=0;
            positionTexteNomArme[i].y=positionTexteNomArme[i-1].y+30;
        }
    }

    for(i=0; i<arm; i++)
    {
        if(i==0)
        {
            nomArmureInventaire[i]=casqueInventaire[i]->GetNom();
            texteNomArmure[i] = TTF_RenderText_Blended(police, nomArmureInventaire[i].c_str(), couleurCarac);
            positionTexteNomArmure[i].x=0;
            positionTexteNomArmure[i].y=265;
        }
        else
        {
            nomArmureInventaire[i]=casqueInventaire[i]->GetNom();
            texteNomArmure[i] = TTF_RenderText_Blended(police, nomArmureInventaire[i].c_str(), couleurCarac);
            positionTexteNomArmure[i].x=0;
            positionTexteNomArmure[i].y=positionTexteNomArmure[i-1].y+30;
        }
    }

    for(i=0; i<cuir; i++)
    {
        if(i==0)
        {
            nomCuirasseInventaire[i]=cuirasseInventaire[i]->GetNom();
            texteNomCuirasse[i] = TTF_RenderText_Blended(police, nomCuirasseInventaire[i].c_str(), couleurCarac);
            positionTexteNomCuirasse[i].x=0;
            positionTexteNomCuirasse[i].y=265;
        }
        else
        {
            nomCuirasseInventaire[i]=cuirasseInventaire[i]->GetNom();
            texteNomCuirasse[i] = TTF_RenderText_Blended(police, nomCuirasseInventaire[i].c_str(), couleurCarac);
            positionTexteNomCuirasse[i].x=0;
            positionTexteNomCuirasse[i].y=positionTexteNomCuirasse[i-1].y+30;
        }
    }

    for(i=0; i<bouc; i++)
    {
        if(i==0)
        {
            nomBouclierInventaire[i]=bouclierInventaire[i]->GetNom();
            texteNomBouclier[i] = TTF_RenderText_Blended(police, nomBouclierInventaire[i].c_str(), couleurCarac);
            positionTexteNomBouclier[i].x=0;
            positionTexteNomBouclier[i].y=265;
        }
        else
        {
            nomBouclierInventaire[i]=bouclierInventaire[i]->GetNom();
            texteNomBouclier[i] = TTF_RenderText_Blended(police, nomBouclierInventaire[i].c_str(), couleurCarac);
            positionTexteNomBouclier[i].x=0;
            positionTexteNomBouclier[i].y=positionTexteNomBouclier[i-1].y+30;
        }
    }

    for(i=0; i<jamb; i++)
    {
        if(i==0)
        {
            nomJambiereInventaire[i]=jambiereInventaire[i]->GetNom();
            texteNomJambiere[i] = TTF_RenderText_Blended(police, nomJambiereInventaire[i].c_str(), couleurCarac);
            positionTexteNomJambiere[i].x=0;
            positionTexteNomJambiere[i].y=265;
        }
        else
        {
            nomJambiereInventaire[i]=jambiereInventaire[i]->GetNom();
            texteNomJambiere[i] = TTF_RenderText_Blended(police, nomJambiereInventaire[i].c_str(), couleurCarac);
            positionTexteNomJambiere[i].x=0;
            positionTexteNomJambiere[i].y=positionTexteNomJambiere[i-1].y+30;
        }
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
                    nomArmure[j]=e[j].GetNom();
                    texteStatNomArmureM0[j] = TTF_RenderText_Blended(police, nomArmure[j].c_str(), couleurCarac);
                    positionTexteStatNomArmure[j].x=150;
                    positionTexteStatNomArmure[j].y=130;

                }
                else if(j>0)
                {
                    nomArmure[j]=e[j].GetNom();
                    texteStatNomArmureM0[j] = TTF_RenderText_Blended(police, nomArmure[j].c_str(), couleurCarac);
                    positionTexteStatNomArmure[j].x=150;
                    positionTexteStatNomArmure[j].y=positionTexteStatNomArmure[j-1].y+30;

                }
            }
            if(i==1)
            {

                if(j==0)
                {
                    nomArmure[j]=e[j].GetNom();
                    texteStatNomArmureM1[j] = TTF_RenderText_Blended(police, nomArmure[j].c_str(), couleurCarac);
                    positionTexteStatNomArmure[j].x=150;
                    positionTexteStatNomArmure[j].y=130;

                }
                else if(j>0)
                {
                    nomArmure[j]=e[j].GetNom();
                    texteStatNomArmureM1[j] = TTF_RenderText_Blended(police, nomArmure[j].c_str(), couleurCarac);
                    positionTexteStatNomArmure[j].x=150;
                    positionTexteStatNomArmure[j].y=positionTexteStatNomArmure[j-1].y+30;

                }
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

        texteStatPv [i]= TTF_RenderText_Blended(police, tableauPv, couleurCarac);
        positionTexteStatPv[i].x=(largeur+10)/2;
        positionTexteStatPv[i].y=40;
        positionInfoArmePv.x=positionTexteStatPv[i].x+140;
        positionInfoArmePv.y=40;

        texteStatPm [i]= TTF_RenderText_Blended(police, tableauPm, couleurCarac);
        positionTexteStatPm[i].x=(largeur+10)/2;
        positionTexteStatPm[i].y=2*(hauteur-50)/11;
        positionInfoArmePm.x=positionTexteStatPm[i].x+140;
        positionInfoArmePm.y=2*(hauteur-50)/11;

        texteStatFr [i]= TTF_RenderText_Blended(police, tableauFr, couleurCarac);
        positionTexteStatFr[i].x=(largeur+10)/2;
        positionTexteStatFr[i].y=3*(hauteur-50)/11;
        positionInfoArmeFr.x=positionTexteStatFr[i].x+140;
        positionInfoArmeFr.y=3*(hauteur-50)/11;

        texteStatDef [i]= TTF_RenderText_Blended(police, tableauDef, couleurCarac);
        positionTexteStatDef[i].x=(largeur+10)/2;
        positionTexteStatDef[i].y=4*(hauteur-50)/11;
        positionInfoArmeDef.x=positionTexteStatDef[i].x+180;
        positionInfoArmeDef.y=4*(hauteur-50)/11;

        texteStatMag [i]= TTF_RenderText_Blended(police, tableauMag, couleurCarac);
        positionTexteStatMag[i].x=(largeur+10)/2;
        positionTexteStatMag[i].y=5*(hauteur-50)/11;
        positionInfoArmeMag.x=positionTexteStatMag[i].x+140;
        positionInfoArmeMag.y=5*(hauteur-50)/11;

        texteStatVol [i]= TTF_RenderText_Blended(police, tableauVol, couleurCarac);
        positionTexteStatVol[i].x=(largeur+10)/2;
        positionTexteStatVol[i].y=6*(hauteur-50)/11;
        positionInfoArmeVol.x=positionTexteStatVol[i].x+140;
        positionInfoArmeVol.y=6*(hauteur-50)/11;

        texteStatVit [i]= TTF_RenderText_Blended(police, tableauVit, couleurCarac);
        positionTexteStatVit[i].x=(largeur+10)/2;
        positionTexteStatVit[i].y=7*(hauteur-50)/11;
        positionInfoArmeVit.x=positionTexteStatVit[i].x+140;
        positionInfoArmeVit.y=7*(hauteur-50)/11;;

        texteStatPrc [i]= TTF_RenderText_Blended(police, tableauPrc, couleurCarac);
        positionTexteStatPrc[i].x=(largeur+10)/2;
        positionTexteStatPrc[i].y=8*(hauteur-50)/11;
        positionInfoArmePrc.x=positionTexteStatPrc[i].x+140;
        positionInfoArmePrc.y=8*(hauteur-50)/11;

        texteStatEsq [i]= TTF_RenderText_Blended(police, tableauEsq, couleurCarac);
        positionTexteStatEsq[i].x=(largeur+10)/2;
        positionTexteStatEsq[i].y=9*(hauteur-50)/11;
        positionInfoArmeEsq.x= positionTexteStatEsq[i].x+140;
        positionInfoArmeEsq.y=9*(hauteur-50)/11;

        texteStatCha [i]= TTF_RenderText_Blended(police, tableauCha, couleurCarac);
        positionTexteStatCha[i].x=(largeur+10)/2;
        positionTexteStatCha[i].y=10*(hauteur-50)/11;
        positionInfoArmeCha.x=positionTexteStatCha[i].x+140;
        positionInfoArmeCha.y=10*(hauteur-50)/11;;

        texteStatNomArme [i]= TTF_RenderText_Blended(police, nomArme[i].c_str(), couleurCarac);
        positionTexteStatNomArme[i].x=150;
        positionTexteStatNomArme[i].y=100;

        texteStatPrenom[i]= TTF_RenderText_Blended(police, prenom[i].c_str(), couleurCarac);
        positionTexteStatPrenom[i].x=100;
        positionTexteStatPrenom[i].y=45;
    }

    const char* tableauEquip[5]= {"Arme :", "Casque :", "Cuirasse :", "Bouclier :", "Jambiere :"};

    for(i=0; i<5; i++)
    {
        if(i==0)
        {
            texteEquipement[i] = TTF_RenderText_Blended(police, tableauEquip[i], couleurCarac);
            positionTexteEquipement[i].x=0;
            positionTexteEquipement[i].y=100;
        }
        else
        {
            texteEquipement[i] = TTF_RenderText_Blended(police, tableauEquip[i], couleurCarac);
            positionTexteEquipement[i].x=0;
            positionTexteEquipement[i].y=positionTexteEquipement[i-1].y+30;
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
            positionLigneHorizontale[i].x = 0;
            positionLigneHorizontale[i].y = 260;
            positionLigneHorizontale[i].w = largeur/2;
            positionLigneHorizontale[i].h = 2;
            ligneHorizontale [i]= SDL_CreateRGBSurface(SDL_HWSURFACE, positionLigneHorizontale[i].w, positionLigneHorizontale[i].h, 32, 0, 0, 0, 0);
            SDL_FillRect(ligneHorizontale[i], NULL, couleurLigne);
        }
    }

    titreMenu=TTF_RenderText_Blended(police, "Equipement", couleurCarac);
    positionTitreMenu.x=0;
    positionTitreMenu.y=0;

    const char*tableauOption[2]={"Equiper", "Enlever"};
    for(i=0; i<2; i++)
    {
            optionEquipement[i]=TTF_RenderText_Blended(police, tableauOption[i], couleurCarac);
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

    }

    positionTof.x =0;
    positionTof.y = 45;
    tof = IMG_Load("tof.png");
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
                    if(equipe[membre]->GetClasse()=="Chevalier dragon" && equipe[membre]->GetArmeEquipe().GetCategorie() != "aucun")
                    {
                        Lance *substitut=new Lance(equipe[membre]->GetArmeEquipe().GetNom(), equipe[membre]->GetArmeEquipe().GetDegat());
                        armeInventaire.push_back(substitut);
                        Arme *aucune=new Arme("aucun");
                        equipe[membre]->EquiperArme(*aucune);
                        texteStatNomArme[membre] = TTF_RenderText_Blended(police, aucune->GetNom().c_str(), couleurCarac);
                        nb=armeInventaire.size();
                        texteNomArme[nb-1]= TTF_RenderText_Blended(police, substitut->GetNom().c_str(), couleurCarac);
                        this->EmissionSonValidation();
                    }
                    else if(equipe[membre]->GetClasse()=="Moine" && equipe[membre]->GetArmeEquipe().GetCategorie() != "aucun")
                    {
                        Gant *substitut=new Gant(equipe[membre]->GetArmeEquipe().GetNom(), equipe[membre]->GetArmeEquipe().GetDegat());
                        armeInventaire.push_back(substitut);
                        Arme *aucune=new Arme("aucun");
                        equipe[membre]->EquiperArme(*aucune);
                        texteStatNomArme[membre] = TTF_RenderText_Blended(police, aucune->GetNom().c_str(), couleurCarac);
                        nb=armeInventaire.size();
                        texteNomArme[nb-1]= TTF_RenderText_Blended(police, substitut->GetNom().c_str(), couleurCarac);
                        this->EmissionSonValidation();
                    }
                    else
                    {

                    }
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
                                texteStatNomArme[membre] = TTF_RenderText_Blended(police, armeInventaire[i]->GetNom().c_str(), couleurCarac);
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
                                    if(j==i)
                                    {

                                    }
                                    else
                                    {
                                        armeInventaire.push_back(copy[j]);
                                        nomArmeInventaire[l]=armeInventaire[l]->GetNom();
                                        texteNomArme[l] = TTF_RenderText_Blended(police, nomArmeInventaire[l].c_str(), couleurCarac);
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
                                    texteStatNomArmureM0[CASQUE] = TTF_RenderText_Blended(police, casqueInventaire[i]->GetNom().c_str(), couleurCarac);
                                }
                                else if (membre==MEMBRE2)
                                {
                                    equipe[membre]->EquiperCasque(*casqueInventaire[i]);
                                    equipe[membre]->ModifierArmure(*casqueInventaire[i]);
                                    texteStatNomArmureM1[CASQUE] = TTF_RenderText_Blended(police, casqueInventaire[i]->GetNom().c_str(), couleurCarac);
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
                                        texteNomArmure[l] = TTF_RenderText_Blended(police, nomArmureInventaire[l].c_str(), couleurCarac);
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
                                    texteStatNomArmureM0[CUIRASSE] = TTF_RenderText_Blended(police, cuirasseInventaire[i]->GetNom().c_str(), couleurCarac);
                                }
                                else if (membre==MEMBRE2)
                                {
                                    equipe[membre]->EquiperCuirasse(*cuirasseInventaire[i]);
                                    equipe[membre]->ModifierArmure(*cuirasseInventaire[i]);
                                    texteStatNomArmureM1[CUIRASSE] = TTF_RenderText_Blended(police, cuirasseInventaire[i]->GetNom().c_str(), couleurCarac);
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
                                        texteNomCuirasse[l] = TTF_RenderText_Blended(police, nomCuirasseInventaire[l].c_str(), couleurCarac);
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
                                    texteStatNomArmureM0[BOUCLIER] = TTF_RenderText_Blended(police, bouclierInventaire[i]->GetNom().c_str(), couleurCarac);
                                }
                                else if (membre==MEMBRE2)
                                {
                                    equipe[membre]->EquiperBouclier(*bouclierInventaire[i]);
                                    equipe[membre]->ModifierArmure(*bouclierInventaire[i]);
                                    texteStatNomArmureM1[BOUCLIER] = TTF_RenderText_Blended(police, bouclierInventaire[i]->GetNom().c_str(), couleurCarac);
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
                                        texteNomBouclier[l] = TTF_RenderText_Blended(police, nomBouclierInventaire[l].c_str(), couleurCarac);
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
                                    texteStatNomArmureM0[JAMBIERE] = TTF_RenderText_Blended(police, jambiereInventaire[i]->GetNom().c_str(), couleurCarac);
                                }
                                else if (membre==MEMBRE2)
                                {
                                    equipe[membre]->EquiperJambiere(*jambiereInventaire[i]);
                                    equipe[membre]->ModifierArmure(*jambiereInventaire[i]);
                                    texteStatNomArmureM1[JAMBIERE] = TTF_RenderText_Blended(police, jambiereInventaire[i]->GetNom().c_str(), couleurCarac);
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
                                        texteNomJambiere[l] = TTF_RenderText_Blended(police, nomJambiereInventaire[l].c_str(), couleurCarac);
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

                case SDLK_KP6:
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

                case SDLK_KP4:
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
                    InfoArmeFr= TTF_RenderText_Blended(police, tableauDegat, couleurAjout);
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
                    InfoArmeDef= TTF_RenderText_Blended(police, tableauInfoCasque, couleurAjout);
                    sprintf(tableauInfoCasque, "+%d", casqueInventaire[m]->GetDefMag());
                    InfoArmeMag= TTF_RenderText_Blended(police, tableauInfoCasque, couleurAjout);
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
                    InfoArmeDef= TTF_RenderText_Blended(police, tableauInfoCuirasse, couleurAjout);
                    sprintf(tableauInfoCuirasse, "+%d", cuirasseInventaire[m]->GetDefMag());
                    InfoArmeMag= TTF_RenderText_Blended(police, tableauInfoCuirasse, couleurAjout);
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
                    InfoArmeDef= TTF_RenderText_Blended(police, tableauInfoBouclier, couleurAjout);
                    sprintf(tableauInfoBouclier, "+%d", bouclierInventaire[m]->GetDefMag());
                    InfoArmeMag= TTF_RenderText_Blended(police, tableauInfoBouclier, couleurAjout);
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
                    InfoArmeDef= TTF_RenderText_Blended(police, tableauInfoJambiere, couleurAjout);
                    sprintf(tableauInfoJambiere, "+%d", jambiereInventaire[m]->GetDefMag());
                    InfoArmeMag= TTF_RenderText_Blended(police, tableauInfoJambiere, couleurAjout);
                    flag=5;
                }
            }
            else
            {
                n++;
            }
        }
        // Collage de la surface de menu sur l'écran
        SDL_BlitSurface(fenMenu, NULL, ecran, &positionMenu);
        SDL_BlitSurface(ligne, NULL, ecran, &positionLigne);
        SDL_BlitSurface(texteStatPrenom[membre], NULL, ecran, &positionTexteStatPrenom[membre]);
        SDL_BlitSurface(texteStatNomArme[membre], NULL, ecran, &positionTexteStatNomArme[membre]);
        SDL_BlitSurface(texteStatPv[membre], NULL, ecran, &positionTexteStatPv[membre]);
        SDL_BlitSurface(texteStatPm[membre], NULL, ecran, &positionTexteStatPm[membre]);
        SDL_BlitSurface(texteStatFr[membre], NULL, ecran, &positionTexteStatFr[membre]);
        SDL_BlitSurface(texteStatDef[membre], NULL, ecran, &positionTexteStatDef[membre]);
        SDL_BlitSurface(texteStatMag[membre], NULL, ecran, &positionTexteStatMag[membre]);
        SDL_BlitSurface(texteStatVol[membre], NULL, ecran, &positionTexteStatVol[membre]);
        SDL_BlitSurface(texteStatVit[membre], NULL, ecran, &positionTexteStatVit[membre]);
        SDL_BlitSurface(texteStatPrc[membre], NULL, ecran, &positionTexteStatPrc[membre]);
        SDL_BlitSurface(texteStatEsq[membre], NULL, ecran, &positionTexteStatEsq[membre]);
        SDL_BlitSurface(texteStatCha[membre], NULL, ecran, &positionTexteStatCha[membre]);

        for(i=0; i<2; i++)
        {
            SDL_BlitSurface(ligneHorizontale[i], NULL, ecran, &positionLigneHorizontale[i]);
        }

        if(membre==MEMBRE1)
        {
            for(i=0; i<e.size(); i++)
            {
               SDL_BlitSurface(texteStatNomArmureM0[i], NULL, ecran, &positionTexteStatNomArmure[i]);
            }
        }
        if(membre==MEMBRE2)
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
        for(i=0; i<2; i++)
        {
            SDL_BlitSurface(optionEquipement[i], NULL, ecran, &positionOptionEquipement[i]);
        }

        if(cpt==1)
        {
            j=0;
            for(i=0; i<armeInventaire.size(); i++)
            {
                if(equipe[membre]->GetArmeEquipable() == armeInventaire[i]->GetCategorie())
                {
                    SDL_BlitSurface(texteNomArme[i], NULL, ecran, &positionTexteNomArme[abs(i-j)]);
                }
                else
                {
                    j++;
                }
            }
        }

        if(cpt==3)
        {
            j=0;
            for(i=0; i<casqueInventaire.size(); i++)
            {
                if(equipe[membre]->IsEquipable(casqueInventaire[i]->GetGenre()))
                {
                    SDL_BlitSurface(texteNomArmure[i], NULL, ecran, &positionTexteNomArmure[abs(i-j)]);
                }
                else
                {
                    j++;
                }
            }
        }

        if(cpt==4)
        {
            j=0;
            for(i=0; i<cuirasseInventaire.size(); i++)
            {
                if(equipe[membre]->IsEquipable(cuirasseInventaire[i]->GetGenre()))
                {
                    SDL_BlitSurface(texteNomCuirasse[i], NULL, ecran, &positionTexteNomArmure[abs(i-j)]);
                }
                else
                {
                    j++;
                }
            }
        }

        if(cpt==5)
        {
            j=0;
            for(i=0; i<bouclierInventaire.size(); i++)
            {
                if(equipe[membre]->IsEquipable(bouclierInventaire[i]->GetGenre()))
                {
                    SDL_BlitSurface(texteNomBouclier[i], NULL, ecran, &positionTexteNomBouclier[abs(i-j)]);
                }
                else
                {
                    j++;
                }
            }
        }

        if(cpt==6)
        {
            j=0;
            for(i=0; i<jambiereInventaire.size(); i++)
            {
                if(equipe[membre]->IsEquipable(jambiereInventaire[i]->GetGenre()))
                {
                    SDL_BlitSurface(texteNomJambiere[i], NULL, ecran, &positionTexteNomJambiere[abs(i-j)]);
                }
                else
                {
                    j++;
                }
            }
        }

        for(m=0; m<nb; m++)
        {
            if(positionCursseur.y==positionTexteNomArme[m].y && flag==1)
            {
                    SDL_BlitSurface(InfoArmeFr, NULL, ecran, &positionInfoArmeFr);
            }
        }

        for(m=0; m<arm; m++)
        {
            if(positionCursseur.y==positionTexteNomArmure[m].y && flag==2)
            {
                    SDL_BlitSurface(InfoArmeDef, NULL, ecran, &positionInfoArmeDef);
                    SDL_BlitSurface(InfoArmeMag, NULL, ecran, &positionInfoArmeMag);
            }
        }

        for(m=0; m<cuir; m++)
        {
            if(positionCursseur.y==positionTexteNomCuirasse[m].y && flag==3)
            {
                    SDL_BlitSurface(InfoArmeDef, NULL, ecran, &positionInfoArmeDef);
                    SDL_BlitSurface(InfoArmeMag, NULL, ecran, &positionInfoArmeMag);
            }
        }

        for(m=0; m<bouc; m++)
        {
            if(positionCursseur.y==positionTexteNomBouclier[m].y && flag==4)
            {
                    SDL_BlitSurface(InfoArmeDef, NULL, ecran, &positionInfoArmeDef);
                    SDL_BlitSurface(InfoArmeMag, NULL, ecran, &positionInfoArmeMag);
            }
        }

        for(m=0; m<jamb; m++)
        {
            if(positionCursseur.y==positionTexteNomJambiere[m].y && flag==5)
            {
                    SDL_BlitSurface(InfoArmeDef, NULL, ecran, &positionInfoArmeDef);
                    SDL_BlitSurface(InfoArmeMag, NULL, ecran, &positionInfoArmeMag);
            }
        }

        SDL_BlitSurface(tof, &clip[membre], ecran, &positionTof);
        SDL_BlitSurface(cursseur, NULL, ecran, &positionCursseur);
        SDL_BlitSurface(titreMenu, NULL, ecran, &positionTitreMenu);
        //Mise à jour de l'affichage
        SDL_Flip(ecran);
    }
    obj->SetArmeInventaire(armeInventaire);
    obj->SetCasqueInventaire(casqueInventaire);
    obj->SetCuirasseInventaire(cuirasseInventaire);
    obj->SetBouclierInventaire(bouclierInventaire);
    obj->SetJambiereInventaire(jambiereInventaire);
}

