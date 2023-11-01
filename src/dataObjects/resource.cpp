#include <string>
#include "resource.h"
using namespace std;

Resource::Resource(string name, string path, ResourceTypeEnum type)
{
    this->name = name;
    this->path = path;
    this->type = type;
}

string Resource::getName()
{
    return this->name;
}

void Resource::setName(string name)
{
    this->name = name;
}

string Resource::getPath()
{
    return this->path;
}

void Resource::setPath(string path)
{
    this->path = path;
}

ResourceTypeEnum Resource::getType()
{
    return this->type;
}

void Resource::setType(ResourceTypeEnum type)
{
    this->type = type;
}