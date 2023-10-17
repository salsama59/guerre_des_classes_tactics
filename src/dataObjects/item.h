#ifndef DEF_OBJET
#define DEF_OBJET

#include <string>

class Item
{
protected:
    std::string name;
    float weight;
    int price;
    std::string type;
    std::string description;

public:
    Item();
    std::string getName();
};

#endif
