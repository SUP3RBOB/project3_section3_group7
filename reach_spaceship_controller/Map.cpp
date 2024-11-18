#include"Map.h"

Map::Map(){
    // list that has planet objects inside of it
    list = QList<Planet>({
        Planet("Moon", 384400.f, 384400.f),
        Planet("Mercury", 77000000.f, 77000000.f),
        Planet("Venus", 38000000.f, 38000000.f),
        Planet("Mars", 225000000.f, 225000000.f),
        Planet("Jupiter", 714000000.f, 714000000.f),
        Planet("Saturn", 1200000000.f, 1200000000.f),
        Planet("Uranus", 2600000000.f, 2600000000.f),
        Planet("Neptune", 4500000000.f, 4500000000.f),
        Planet("Pluto", 7500000000.f, 7500000000.f),
        Planet("Naboo", 5.6764e+16f, 5.6764e+16f)
    });
}




