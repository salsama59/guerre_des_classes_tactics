#ifndef DEF_PERSONNAGE
#define DEF_PERSONNAGE
#include"Arme.h"
#include"Casque.h"
#include"Cuirasse.h"
#include"Bouclier.h"
#include"Jambiere.h"
#include"Potion.h"
#include <string>
#include <vector>

class Personnage
{
    protected :
    std::string nom;//Nom du personnage
    std::string prenom;//Prénom du personnage
    std::string classe;//Classe du personnage
    std::string armeEquipable;//Arme que peut equiper un personnage
    std::string armureEquipable[2];//Types d'arrmure que peut equiper un personnage
    int pv;//Points de santé du personnage
    int pm;//Points de magie du personnage
    int fr;//Force
    int def;//Défense
    int mag;//Magie
    int vol;//Volonté
    int vit;//Vitesse
    int cha;//Chance
    float esq;//Esquive
    float prc;//Précision
    int niv;//Niveau du personnage
    int maxPv;//Maximum de points de santé du personnage
    int maxPm;//Maximun de points de magie du personnage
    int exp;//Expérience actuelle du personnage
    int seuil;//Seuil d'expérience donnant lieu à une augmentation du niveau du personnage
    Arme armeEquipe;//Arme équipée
    Casque casqueEquipe;//Casque équipé
    Bouclier bouclierEquipe;//Bouclier équipé
    Cuirasse cuirasseEquipe;//Cuirasse équipée
    Jambiere jambiereEquipe;//Jambiere équipée
    std::vector<Equipement> armureEquipe;//Armure entière équipée

    public :

    Personnage();
    Personnage(std::string n, std::string p);
    void Attaquer(Personnage &cible, Personnage &attaquant, Arme &armUtilise);
    int RecevoirDegat(int degatArme, int forceAdversaire);
    int RecevoirDegatSpecial(int degatArme, int caractAdversaire, int base, std::string nature);
    void AffichageEtat();
    virtual int GainFr(int bonus);
    virtual int GainPv(int bonus);
    virtual int GainPm(int bonus);
    virtual int GainDef(int bonus);
    virtual int GainCha(int bonus);
    virtual int GainMag(int bonus);
    virtual int GainVol(int bonus);
    virtual int GainVit(int bonus);
    virtual int GainEsq(int bonus);
    virtual int GainPrc(int bonus);
    virtual int GainNiv(int bonus);
    virtual int GainExp(int gain);
    virtual int ChangementSeuil(int nouvelleValeur);
    void EquiperArme(Arme &nouvelleArme);
    void EquiperCasque(Casque &nouveauCasque);
    void EquiperCuirasse(Cuirasse &nouvelleCuirasse);
    void EquiperBouclier(Bouclier &nouveauBouclier);
    void EquiperJambiere(Jambiere &nouvelleJambiere);
    void ModifierArmure(Armure &pieceArmure);
    int UtiliserObjet(Personnage &cible, Potion &objet);
    void NiveauAcquis();
    int GetNiv();
    std::string GetNom();
    std::string GetPrenom();
    std::string GetClasse();
    int GetPv();
    int GetPm();
    int GetMaxPv();
    int GetMaxPm();
    int GetExp();
    int GetSeuil();
    int GetFr();
    int GetDef();
    int GetMag();
    int GetVol();
    int GetVit();
    float GetEsq();
    float GetPrc();
    int GetCha();
    Arme GetArmeEquipe();
    Casque GetCasqueEquipe();
    Cuirasse GetCuirasseEquipe();
    Bouclier GetBouclierEquipe();
    Jambiere GetJambiereEquipe();
    std::vector<Equipement> GetArmureEquipe();
    std::string GetArmeEquipable();
    std::string *GetArmureEquipable();
    bool IsEquipable(std::string type);
};

#endif
