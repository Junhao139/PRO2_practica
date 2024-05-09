#ifndef CITY_HH
#define CITY_HH

#include <string>
#include <map>
#include <stdint.h>

#include "product.hh"

using namespace std;

// City corresponds with a node in the River's BinTree structure
// It serves mainly for a container to manage city's inventory.

class City {
private:
    struct ProductDemand {
        int in_demand;
        int available;
    };
    map<uint32_t, ProductDemand> inventory;
    bool has_inventory;

    int total_mass;
    int total_volume;
public:
    City();

    /** @brief  Clear the inventory.
     *  \pre    The city actually has an inventory.
     *  \post   Inventory is cleared.
    */
    void clear_inventory();

    /** @brief  Add one type of product to inventory.
     *  \pre    The product does not existe before in the inventory.
     *  \post   The product is added.
    */
    void add_product_to_inventory(uint32_t identifier, int in_demand, int available);

    /** @brief  Modify the product in the inventory.
     *  \pre    The product already exists in the inventory.
     *  \post   The product is modified.
    */
    void set_product_in_inventory(uint32_t identifier, int in_demand, int available);

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
    void delete_product(uint32_t identifier);

    /** @brief  Returns the total mass and volume of the inventory.
     *  \pre    TRUE.
     *  \post   The "mass" and "volume" are returned via reference.
    */
    void total_mass_and_volume(int& mass, int& volume) const;
};

#endif // CITY_HH