#ifndef DEF_RESOURCE
#define DEF_RESOURCE
#include <string>
#include "../enums/resourceTypeEnum.h"
using namespace std;

class Resource
{
private:
    string name;
    string path;
    ResourceTypeEnum type;

public:
    Resource(string name, string path, ResourceTypeEnum type);
    ~Resource();
    string getName();
    void setName(string name);
    string getPath();
    void setPath(string path);
    ResourceTypeEnum getType();
    void setType(ResourceTypeEnum type);
};
#endif