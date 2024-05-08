#ifndef CITY_HH
#define CITY_HH

#include <string>
#include <map>

#include "product.hh"

using namespace std;

// City corresponds with a node in the River's BinTree structure
// It serves mainly for a container to manage city's inventory.

class City {
public:
/* TYPES */
    typedef string CityID;

private:
    CityID identifier;
    struct ProductDemand {
        int in_demand;
        int available;
    };
    map<Product::ProdID, ProductDemand> inventory;
    bool has_inventory;

public:
/* METHODS */
    City(CityID const& identifier);

    /**
     * 
    */
    void clear_inventory();
};

#endif // CITY_HH