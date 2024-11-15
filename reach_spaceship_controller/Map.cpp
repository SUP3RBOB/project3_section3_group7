#include"Map.h"

Map::Map(){
    // list that has planet objects inside of it
    list = QList<Planet>({
        Planet("Mars", 15, 20),
        Planet("Mercury", 26, 29),
        Planet("Venus", 23,30),
        Planet("Jupiter", 26,35),
        Planet("Uranus",35,38),
        Planet("Neptune",45,46),
        Planet("Neptune",45,46),
        Planet("Naboo",100,250),
        Planet("Harrizz",420,69)
    });
}




