#include <cstdlib>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include "Jeu.h"
#include <iostream>
using namespace std;

int main ( int argc, char** argv )
{
    SDL_Event evenement;
    SDL_Renderer *ecranTitre;
    //Création d'un objet de type jeu
    Jeu *afficheur= new Jeu();
    //On récupère le pointeur vers la fenêtre
    ecranTitre=afficheur->GetFen();
    int continuer=1;
    //Boucle infini permettant le fonctionnement du jeu
    while (continuer)
    {
        //Fonction permettant l'attente d'un evenement clavier, souris ou joystick
        SDL_WaitEvent(&evenement);
        //Boucle switch sur les types d'évenements
        switch(evenement.type)
        {
            case SDL_QUIT:
            continuer = 0;
            break;

            case SDL_KEYDOWN:
            switch (evenement.key.keysym.sym)
            {
                case SDLK_ESCAPE: /* Appui sur la touche Echap, on arrête le programme */
                continuer = 0;
                break;

                case SDLK_RETURN:
                //lancement du jeu
                afficheur->Jouer();
                break;
            }
            break;

        }
        //On met à jour la couleur de fond de l'écran titre
        SDL_SetRenderDrawColor(ecranTitre, 0, 0, 0, SDL_ALPHA_OPAQUE);
        SDL_RenderClear(ecranTitre);
        SDL_RenderPresent(ecranTitre);
        //SDL_FillRect(ecranTitre, NULL, SDL_MapRGB(ecranTitre->format, 0, 0, 0));
        // Mise à jour de l'écran avec sa nouvelle couleur
        //SDL_Flip(ecranTitre);
    }
    //On quitte la SDL
    SDL_Quit();
    return EXIT_SUCCESS;
}
