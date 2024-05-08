#ifndef BASIN_HH
#define BASIN_HH

/** @brief Basin: the class for the whole basin, the management and processing.
*/

#include <iostream>

#include "river.hh"
#include "product_data.hh"

class Basin {
private:
    /** @brief  All types of products are registered by this object.
     */
    ProductData types_of_products;

    /** @brief  The river's structure is stored in this object. All the commerces are handled by it.
    */
    River river_structure;

public:
    Basin();
    ~Basin();

    /** @brief  Runs a valid command, executes the command modifying internal data or outputing onto console.
     *  \pre    The command is valid.
     *  \post   The corresponding action is taken.
    */
    void run_command(string const& command);
};

#endif // BASIN_HH