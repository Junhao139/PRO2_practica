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
    map<string, City> inventory_database;

    // The structure of the basin
    BinTree<string> basin_cities;

public:
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
    void input_river_structure();

    /** @brief  Let the ship select route and commercialize.
     *  \pre    TRUE.
     *  \post   The ship's data will be modified. The number of bought and sold units are returned via references.
    */
    void ship_travelling(Ship& ship, int& bought_units, int& sold_units);

    /** @brief  Tells if a city exists.
     *  \pre    TRUE.
     *  \post   Return TRUE only if the "identifier"'s city exists in River.
    */
    bool city_exists(string const& identifier) const;

    /** @brief  Commercialize between 2 cities.
     *  \pre    Both cities exist.
     *  \post   Two cities will commercialize between them, modifying their inventory.
    */
    void commercialize(string const& city_1, string const& city2);

    /** @brief  Redistribute according to the requirement 17 of the documentation.
     *  \pre    TRUE.
     *  \post   All inventory of the invervened cities will be modified.
    */
    void redistribute();
};


#endif // RIVER_HH