#ifndef RIVER_HH
#define RIVER_HH

#include <iostream>
#include <map>

#include "city.hh"
#include "BinTree.hh"
#include "ship.hh"

using namespace std;

// River holds the BinTree structure and all the cities
// It also handles the input of a new basin structure, and
// therefore clears all the prior data.

class River {
private:
    // Access the inventory of a city using city's identifier
    map<City::CityID, City> inventory_database;

    // The structure of the basin
    BinTree<City::CityID> basin_cities;

public:
/* Methods */
    /** @brief  Constructor. It sets everything to its initial state. Basin is empty.
     *  \pre    TRUE.
     *  \post   TRUE.
    */
    River();

    /** @brief  Destructor. It calls the destructor of child elements.
     *  \pre    TRUE.
     *  \post   TRUE.
    */
    ~River();

    /** @brief  Read from input the new structure of the basin.
     *  \pre    There is a valid binary tree description in PreOrder on the input.
     *  \post   River's structure is updated according to the input.
    */
    void input_basin();

    /** @brief  Place the ship in the root node of the river.
     *  \pre    TRUE.
     *  \post   If basin's empty, BinTree() will be returned. Otherwise it returns a non-null BinTree.
    */
    void place_ship(Ship& ship);

    
};


#endif // RIVER_HH