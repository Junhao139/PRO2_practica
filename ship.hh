#ifndef SHIP_HH
#define SHIP_HH

// The Ship class will hold the information for the River class
// to find the optimum route for transactions.

#ifndef NO_DIAGRAM
#include <string>
#include <vector>
#include <stdint.h>
#include <iostream>
#endif // NO_DIAGRAM

#include "product.hh"

using namespace std;

class Ship {
private:
    int32_t wanted;
    int32_t for_sell;
    int wanted_quantity;
    int for_sell_quantity;

    vector<string> visited_cities;
public:
    Ship();
    ~Ship();

    /** @brief  Returns the wanted product and value through referenced variables.
     *  \pre    TRUE.
     *  \post   Necessary information are returned. 
    */
    uint32_t wanted_product() const;
    int wanted_number() const;

    /** @brief  Returns the product for sell and its value through referenced variables.
     *  \pre    TRUE.
     *  \post   Necessary information are returned. 
    */
    uint32_t for_sell_product() const;
    int for_sell_number() const;

    /** @brief  Sets the wanted product and how many of it, and seemingly for the ones for_sell.
     *  \pre    Both products exist, the numbers are non-negative and one of them is strictly positive.
     *  \post   The information is updated to the class.
    */
    void set_all(int32_t wanted, int wanted_number, int32_t for_sell, int for_sell_number);

    /** @brief  Register a destination.
     *  \pre    The city ID is a valid one.
     *  \post   The destination is registered.
    */
    void add_destination(string const& city_id);

    /** @brief  Output using STL "cout" and in specific format as what is indicated in the Sample all the previous destinations.
     *  \pre    TRUE.
     *  \post   In console there will be a few lines of the City names.
    */
    void write_all_destinations() const;

    /** @brief  Clears all registered destinations.
     *  \pre    TRUE.
     *  \post   No destinations are registered in ship.
    */
    void clear_all_destinations();
};

#endif // SHIP_HH