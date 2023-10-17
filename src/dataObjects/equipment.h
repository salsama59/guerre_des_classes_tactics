#ifndef DEF_EQUIPEMENT
#define DEF_EQUIPEMENT

#include <string>

class Equipment
{
protected:
    std::string name;
    std::string type;
    std::string category;
    float weight;
    int price;

public:
    Equipment();
    std::string GetName();
    std::string GetType();
    std::string GetCategory();
};

#endif
