#ifndef CITY_HH
#define CITY_HH

#include <string>
#include <map>
#include <stdint.h>
#include <iostream>

#include "product_data.hh"

using namespace std;

/** @details 
 *  City corresponds with a node in the River's BinTree structure
 *  It serves mainly for a container to manage city's inventory.
*/
class City {
private:
    struct ProductDemand {
        int in_demand;
        int available;
    };
    map<uint32_t, ProductDemand> inventory;
    bool inventory_disposition;

    int total_mass;
    int total_volume;
public:
    /** @brief  Initializes all values. The city is ready to be operated with.
     *  \pre    TRUE.
     *  \post   All values are initialized.
    */
    City();

    /** @brief  Frees all possible dynamic memory.
     *  \pre    TRUE.
     *  \post   All possible dynamic memory are freed.
    */
    ~City();

    /** @brief  Clear the inventory.
     *  \pre    The city actually has an inventory.
     *  \post   Inventory is cleared.
    */
    void clear_inventory();

    /** @brief  Add one type of product to inventory.
     *  \pre    The product does not existe before in the inventory.
     *  \post   The product is added.
    */
    void add_product_to_inventory(uint32_t identifier, ProductData const& pd, int in_demand, int available);

    /** @brief  Modify the product in the inventory.
     *  \pre    The product already exists in the inventory.
     *  \post   The product is modified.
    */
    void set_product_in_inventory(uint32_t identifier, ProductData const& pd, int in_demand, int available);

    /** @brief  Tells if the product is in the inventory.
     *  \pre    TRUE.
     *  \post   Return TRUE only if the product is in the inventory. FALSE otherwise.
    */
    bool exist_in_inventory(uint32_t product) const;

    /** @brief  Consult the information of a specific product.
     *  \pre    The product is in the inventory.
     *  \post   The information is returned via the references.
    */
    void consult_product(uint32_t identifier, int& in_demand, int& available) const;

    /** @brief  The product is deleted from the inventory.
     *  \pre    The product exists.
    */
    void delete_product(uint32_t identifier, ProductData const& pd);

    /** @brief  Returns the total mass and volume of the inventory.
     *  \pre    TRUE.
     *  \post   The "mass" and "volume" are returned via reference.
    */
    void total_mass_and_volume(int& mass, int& volume) const;

    /** @brief  Tells if this city has an inventory.
     *  \pre    TRUE.
     *  \post   Returns TRUE only if the city has an inventory.
    */
    bool has_inventory() const;

    /** @brief  Trade between this city and the given one.
     *  \pre    The fireign city exist.
     *  \post   The inventory of the two cities are modified.
    */
    void trade_with(City& foreign, ProductData const& pd);

    /** @brief  Write on the output using STL "cout" in the requiered format the whole inventory in numerical order of the product.
     *  \pre    TRUE.
     *  \post   The inventory, if exist and has elements, will be written on the output.
    */
    void write_inventory() const;
};

#endif // CITY_HH