/* main.cc */

#include <iostream>
#include <string>

#include "river.hh"
#include "product_data.hh"
#include "product.hh"
#include "ship.hh"

using namespace std;

/** @brief  The beginning input.
 *  \pre    TRUE.
 *  \post   It prepares the initial data according to the project description.
*/
void initial_data(
    ProductData&    types_of_products,
    River&          river_structure
);

/** @brief  Runs a command given the datas of the params.
 *  \pre    "command" is valid; "types_of_products" is non-null; "river_structure" is valid; "ship" is valid.
 *  \post   The command is run. "types_of_products", "river_structure" and "ship" are modified.
*/
void run_command(
    string const&   command,
    ProductData&    types_of_products,
    River&          river_structure,
    Ship&           ship
);

int main() {
    /** @brief  All types of products are registered by this object.
     */
    ProductData types_of_products;

    /** @brief  The river's structure is stored in this object. All the commerces are handled by it.
    */
    River river_structure;

    /** @brief  The ship.
    */
    Ship ship;

    initial_data(types_of_products, river_structure);

    string command;
    cin >> command;
    bool comment_output = true;
    while (command != "fin") {
        /* Comment */
        if (command[0] == '/' and command[1] == '/') {
            // Do nothing
        }
        else {
            // note the input with "#" on the output
            cout << "#" << command << endl;

            // run the command
            run_command(command, types_of_products, river_structure, ship);
        }

        cin >> command;
    }
}

void initial_data(
    ProductData&    types_of_products,
    River&          river_structure
) {
    // Add all the initially given products
    int product_count;
    cin >> product_count;
    for (int p = 0; p < product_count; ++p) {
        int mass, volume;
        cin >> mass >> volume;
        types_of_products.add_new_product(Product(mass, volume));
    }

    // Read the river structure
    river_structure.input_river_structure();
}

void run_command(
    string const&   command,
    ProductData&    types_of_products,
    River&          river_structure,
    Ship&           ship
) {
    /* 1 */
    if (command == "leer_rio" or command == "lr") {
        river_structure.input_river_structure();
    }
    /* 2 */
    else if (command == "leer_inventario" or command == "li") {
        string city_identifier;
        cin >> city_identifier;
        if (not river_structure.city_exists(city_identifier))
            cerr << "error: no existe la ciudad" << endl;
        else {
            int inventory_count;
            cin >> inventory_count;

            uint32_t product_identifier;
            int available, in_demand;
            // The in_demand number has to always be strictly positive,
            // but in specifications it defined no action for when this 
            // is not met.
            for (int i = 0; i < inventory_count; ++i) {
                cin >> product_identifier >> available >> in_demand;

            }
        }
    }
    /* 3 */
    else if (command == "leer_inventarios" or command == "ls") {

    }
    /* 4 */
    else if (command == "modificar_barco" or command == "mb") {

    }
    /* 5 */
    else if (command == "escribir_barco" or command == "eb") {

    }
    /* 6 */
    else if (command == "consultar_num" or command == "cn") {
        
    }
    /* 7 */
    else if (command == "agregar_productos" or command == "ap") {
        
    }
    /* 8 */
    else if (command == "escribir_producto" or command == "ep") {
        
    }
    /* 9 */
    else if (command == "escribir_ciudad" or command == "ec") {
        
    }
    /* 10 */
    else if (command == "poner_prod" or command == "pp") {
        
    }
    /* 11 */
    else if (command == "modificar_prod" or command == "mp") {
        
    }
    /* 12 */
    else if (command == "quitar_prod" or command == "qp") {
        
    }
    /* 13 */
    else if (command == "consultar_prod" or command == "cp") {
        
    }
    /* 14 */
    else if (command == "comerciar" or command == "co") {
        
    }
    /* 15 */
    else if (command == "redistribuir" or command == "re") {
        
    }
    /* 16 */
    else if (command == "hacer_viaje" or command == "hv") {
        
    }
}