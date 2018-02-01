#ifndef DEF_JEU
#define DEF_JEU
#include <SDL/SDL.h>
#include "Arme.h"
#include "Casque.h"
#include "Cuirasse.h"
#include "Bouclier.h"
#include "Jambiere.h"
#include "Lance.h"
#include "Gant.h"
#include "Personnage.h"
#include <vector>


class Jeu
{
    private:

    SDL_Surface *fenetre;
    std::vector <Arme*> sauvegardeArmeInventaire;
    std::vector <Casque*> sauvegardeCasqueInventaire;
    std::vector <Cuirasse*> sauvegardeCuirasseInventaire;
    std::vector <Bouclier*> sauvegardeBouclierInventaire;
    std::vector <Jambiere*> sauvegardeJambiereInventaire;
    std::vector <Personnage*> sauvegardeGroupe;
    std::vector <Personnage*> sauvegardeEquipe;


    public:

    Jeu();
    void Jouer();
    SDL_Surface *GetFen();
    void SetArmeInventaire(std::vector<Arme*> nouvelInventaire);
    void SetCasqueInventaire(std::vector<Casque*> nouvelInventaire);
    void SetCuirasseInventaire(std::vector<Cuirasse*> nouvelInventaire);
    void SetBouclierInventaire(std::vector<Bouclier*> nouvelInventaire);
    void SetJambiereInventaire(std::vector<Jambiere*> nouvelInventaire);
    void SetGroupe(std::vector <Personnage*> nouveauGroupe);
    void SetEquipe(std::vector <Personnage*> nouvelleEquipe);
    Jeu *GetObjet();
    std::vector <Arme*> GetArmeInventaire();
    std::vector <Casque*> GetCasqueInventaire();
    std::vector <Cuirasse*> GetCuirasseInventaire();
    std::vector <Bouclier*> GetBouclierInventaire();
    std::vector <Jambiere*> GetJambiereInventaire();
    std::vector <Personnage*> GetGroupe();
    std::vector <Personnage*> GetEquipe();
};

#endif
