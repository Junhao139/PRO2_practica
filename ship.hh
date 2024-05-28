/**
 * @file ship.hh
 * @brief The definition of the Ship class.
 */

#ifndef SHIP_HH
#define SHIP_HH

#ifndef NO_DIAGRAM
#include <string>
#include <list>
#include <stdint.h>
#include <iostream>
#endif // NO_DIAGRAM

#include "product.hh"

using namespace std;

/** @brief  Ship stores what it wants and what it is selling, as well as all destinations that it has been.
 *  @details
 *  The Ship class will hold the information for the River class
 *  to find the optimum route for transactions.
 */
class Ship {
private:
    /** @brief  The ID (tag) of the product that the ship wants to buy.
     */
    int32_t wanted;

    /** @brief  The ID (tag) of the product that the ship wants to sell.
     */
    int32_t for_sell;

    /** @brief  The quantity of the product that the ship wants to buy.
     */
    int wanted_quantity;

    /** @brief  The quantity of the product that the ship wants to sell.
     */
    int for_sell_quantity;

    /** @brief  The container of all visited cities.
     */
    list<string> visited_cities;

public:
    /** @brief  The constructor doesn't do anything. However, the ship need to be set_all in order to be used.
     */
    Ship();

    /** @brief  The destructor doesn't do anything.
     */
    ~Ship();

    /** @brief  Returns the wanted product's ID through referenced variables.
     *  \pre    TRUE.
     *  \post   Necessary information are returned. 
    */
    uint32_t wanted_product() const;

    /** @brief  Returns the wanted product's quantity through referenced variables.
     *  \pre    TRUE.
     *  \post   Necessary information are returned. 
    */
    int wanted_number() const;

    /** @brief  Returns the ID of the product for sell through referenced variables.
     *  \pre    TRUE.
     *  \post   Necessary information are returned. 
    */
    uint32_t for_sell_product() const;

    /** @brief  Returns the quantity of the product for sell and its value through referenced variables.
     *  \pre    TRUE.
     *  \post   Necessary information are returned. 
    */
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