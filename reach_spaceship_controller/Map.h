#ifndef MAP_H
#define MAP_H
#include "planet.h"
#include <qlist.h>

class Map{
public:
    //List that will hold the planet objects
    QList<Planet> list;
    //constructor for map class
    Map();
};
#endif // MAP_H
