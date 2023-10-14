#include <cstdlib>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include "game.h"
#include <iostream>
using namespace std;

int main(int argc, char **argv)
{
    SDL_Event inputEvent;
    SDL_Renderer *screenRenderer;
    // Création d'un objet de type jeu
    Game *game = new Game();
    // On récupère le pointeur vers la fenêtre
    screenRenderer = game->getRenderer();
    bool isWaitingInputs = true;
    // Boucle infini permettant le fonctionnement du jeu
    while (isWaitingInputs)
    {
        // Fonction permettant l'attente d'un inputEvent clavier, souris ou joystick
        SDL_WaitEvent(&inputEvent);
        // Boucle switch sur les types d'évenements
        switch (inputEvent.type)
        {
        case SDL_QUIT:
            isWaitingInputs = false;
            break;

        case SDL_KEYDOWN:
            switch (inputEvent.key.keysym.sym)
            {
            case SDLK_ESCAPE: /* Appui sur la touche Echap, on arrête le programme */
                isWaitingInputs = false;
                break;

            case SDLK_RETURN:
                // lancement du jeu
                game->Jouer();
                break;
            }
            break;
        }
        SDL_SetRenderDrawColor(screenRenderer, 0, 0, 0, SDL_ALPHA_OPAQUE);
        SDL_RenderClear(screenRenderer);
        SDL_RenderPresent(screenRenderer);
    }
    // On quitte la SDL
    SDL_Quit();
    return EXIT_SUCCESS;
}
