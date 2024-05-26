/**
 * @file    main.cc
 * @author  Junhao Liu
 * @brief   The file that contains main function.
 */

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
    River&          river_structure,
    Ship&           ship
);

/** @brief  Runs a command given the datas of the params.
 *  \pre    "command" is valid; "types_of_products" is non-null; "river_structure" is valid; "ship" is valid.
 *  \post   The command is run. "types_of_products", "river_structure" and "ship" are modified.
 * 
 *  @param  command
 *  @param  product_types
 *  @param  river
 *  @param  ship
*/
void run_command(
    string const&   command,
    ProductData&    product_types,
    River&          river,
    Ship&           ship
);

/**
 *  @brief  All auxiliary functions for "run_command()" because they are long.
 *  @details
 *  All these functions' name start with "run_command_aux_", then
 *  it is the code of the requirement (see Practica's Instructions)
 *  to which corresponds the function's utility. All these functions
 *  will have the same four parameters as the original "run_command()",
 *  so the further descriptions are omitted for these functions.
 * 
 *  \addtogroup run_command_aux
 *  @{
 */
void run_command_aux_2( string const& command, ProductData& product_types, River& river, Ship& ship);
void run_command_aux_3( string const& command, ProductData& product_types, River& river, Ship& ship);
void run_command_aux_4( string const& command, ProductData& product_types, River& river, Ship& ship);
void run_command_aux_7( string const& command, ProductData& product_types, River& river, Ship& ship);
void run_command_aux_8( string const& command, ProductData& product_types, River& river, Ship& ship);
void run_command_aux_9( string const& command, ProductData& product_types, River& river, Ship& ship);
void run_command_aux_10(string const& command, ProductData& product_types, River& river, Ship& ship);
void run_command_aux_11(string const& command, ProductData& product_types, River& river, Ship& ship);
void run_command_aux_12(string const& command, ProductData& product_types, River& river, Ship& ship);
void run_command_aux_13(string const& command, ProductData& product_types, River& river, Ship& ship);
void run_command_aux_14(string const& command, ProductData& product_types, River& river, Ship& ship);
/** @} */


/** @brief
 *  \pre
 *  \post
*/
void error_log(string const& message);


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

    initial_data(types_of_products, river_structure, ship);

    string command;
    cin >> command;
    while (command != "fin") {
        /* Comment */
        if (command == "//") {
            // Absorb the whole line
            string comment;
            getline(cin, comment);
        }
        else {
            // note the input with "#" on the output
            cout << "#" << command;

            // run the command
            run_command(command, types_of_products, river_structure, ship);
        }

        cin >> command;
    }
}

void initial_data(
    ProductData&    types_of_products,
    River&          river_structure,
    Ship&           ship
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

    // Initial data for the ship
    uint32_t ship_wanted, ship_for_sell;
    int ship_wanted_qtty, ship_for_sell_qtty;
    cin >> ship_wanted >> ship_wanted_qtty >> ship_for_sell >> ship_for_sell_qtty;
    ship.set_all(ship_wanted, ship_wanted_qtty, ship_for_sell, ship_for_sell_qtty);
}

void run_command(
    string const&   command,
    ProductData&    product_types,
    River&          river,
    Ship&           ship
) {
    /* 1 */
    if (command == "leer_rio" or command == "lr") {
        ship.clear_all_destinations();
        river.input_river_structure();
        cout << endl;
    }
    /* 2 */
    else if (command == "leer_inventario" or command == "li") {
        run_command_aux_2(command, product_types, river, ship);
    }
    /* 3 */
    else if (command == "leer_inventarios" or command == "ls") {
        run_command_aux_3(command, product_types, river, ship);
    }
    /* 4 */
    else if (command == "modificar_barco" or command == "mb") {
        run_command_aux_4(command, product_types, river, ship);
    }
    /* 5 */
    else if (command == "escribir_barco" or command == "eb") {
        cout << endl;
        cout << ship.wanted_product()   << ' ' << ship.wanted_number()   << ' '
             << ship.for_sell_product() << ' ' << ship.for_sell_number() << endl;
        ship.write_all_destinations();
    }
    /* 6 */
    else if (command == "consultar_num" or command == "cn") {
        cout << endl;
        cout << product_types.database_size() << endl;
    }
    /* 7 */
    else if (command == "agregar_productos" or command == "ap") {
        run_command_aux_7(command, product_types, river, ship);
    }
    /* 8 */
    else if (command == "escribir_producto" or command == "ep") {
        run_command_aux_8(command, product_types, river, ship);
    }
    /* 9 */
    else if (command == "escribir_ciudad" or command == "ec") {
        run_command_aux_9(command, product_types, river, ship);
    }
    /* 10 */
    else if (command == "poner_prod" or command == "pp") {
        run_command_aux_10(command, product_types, river, ship);
    }
    /* 11 */
    else if (command == "modificar_prod" or command == "mp") {
        run_command_aux_11(command, product_types, river, ship);
    }
    /* 12 */
    else if (command == "quitar_prod" or command == "qp") {
        run_command_aux_12(command, product_types, river, ship);
    }
    /* 13 */
    else if (command == "consultar_prod" or command == "cp") {
        run_command_aux_13(command, product_types, river, ship);
    }
    /* 14 */
    else if (command == "comerciar" or command == "co") {
        run_command_aux_14(command, product_types, river, ship);
    }
    /* 15 */
    else if (command == "redistribuir" or command == "re") {
        cout << endl;
        river.redistribute(product_types);
    }
    /* 16 */
    else if (command == "hacer_viaje" or command == "hv") {
        cout << endl;
        int bought_units, sold_units;
        river.ship_travelling(ship, product_types, bought_units, sold_units);
        cout << bought_units + sold_units << endl; 
    }
}

void run_command_aux_2( string const& command, ProductData& product_types, River& river, Ship& ship) {
    string city_id;
    cin >> city_id;
    cout << ' ' << city_id << endl;
    if (not river.city_exists_in_basin(city_id)) {
        error_log("no existe la ciudad");

        // Absorb inputs
        int inventary_size;
        cin >> inventary_size;

        for (int i = 0; i < inventary_size; ++i) {
            uint32_t product_id;
            int in_demand, available;
            cin >> product_id >> available >> in_demand;
        }
    } else {
        river.city_clear_inventory(city_id);

        int inventary_size;
        cin >> inventary_size;

        for (int i = 0; i < inventary_size; ++i) {
            uint32_t product_id;
            int in_demand, available;
            cin >> product_id >> available >> in_demand;

            river.city_add_product(city_id, product_types, product_id, in_demand, available);
        }
    }
}

void run_command_aux_3( string const& command, ProductData& product_types, River& river, Ship& ship) {
    string city_id;
    cin >> city_id;
    cout << endl;
    while (city_id != "#") {
        if (not river.city_exists_in_basin(city_id)) {
            error_log("no existe la ciudad");

            // Absorb inputs
            int inventary_size;
            cin >> inventary_size;

            for (int i = 0; i < inventary_size; ++i) {
                uint32_t product_id;
                int in_demand, available;
                cin >> product_id >> available >> in_demand;
            }
        } else {
            river.city_clear_inventory(city_id);

            int inventary_size;
            cin >> inventary_size;

            for (int i = 0; i < inventary_size; ++i) {
                uint32_t product_id;
                int in_demand, available;
                cin >> product_id >> available >> in_demand;

                river.city_add_product(city_id, product_types, product_id, in_demand, available);
            }
        }
        cin >> city_id;
    }
}

void run_command_aux_4( string const& command, ProductData& product_types, River& river, Ship& ship) {
    uint32_t ship_wanted, ship_for_sell;
    int ship_wanted_qtty, ship_for_sell_qtty;
    cin >> ship_wanted   >> ship_wanted_qtty
        >> ship_for_sell >> ship_for_sell_qtty;
    cout << endl;
    if (product_types.product_exists(ship_wanted) and product_types.product_exists(ship_for_sell)) {
        if (ship_wanted == ship_for_sell) {
            error_log("no se puede comprar y vender el mismo producto");
        } else {
            ship.set_all(ship_wanted, ship_wanted_qtty, ship_for_sell, ship_for_sell_qtty);
        }
    } else {
        error_log("no existe el producto");
    }
}

void run_command_aux_7( string const& command, ProductData& product_types, River& river, Ship& ship) {
    int input_quantity;
    cin >> input_quantity;
    cout << ' ' << input_quantity << endl;
    for (int i = 0; i < input_quantity; ++i) {
        int mass, volume;
        cin >> mass >> volume;
        product_types.add_new_product(Product(mass, volume));
    }
}

void run_command_aux_8( string const& command, ProductData& product_types, River& river, Ship& ship) {
    uint32_t product;
    cin >> product;
    cout << ' ' << product << endl;
    if (product_types.product_exists(product)) {
        Product prod(0, 0);
        product_types.consult_product(prod, product);
        cout << product << ' ' << prod.get_mass() << ' ' << prod.get_volume() << endl;
    } else {
        error_log("no existe el producto");
    }
}

void run_command_aux_9( string const& command, ProductData& product_types, River& river, Ship& ship) {
    string city_id;
    cin >> city_id;
    cout << ' ' << city_id << endl;
    if (river.city_exists_in_basin(city_id)) {
        river.city_write_inventory(city_id);
        int total_mass, total_volume;
        bool has_inventory; // this is not needed though
        river.city_information(city_id, total_mass, total_volume, has_inventory);
        cout << total_mass << ' ' << total_volume << endl;
    } else {
        error_log("no existe la ciudad");
    }
}

void run_command_aux_10(string const& command, ProductData& product_types, River& river, Ship& ship) {
    string city_id;
    uint32_t product;
    int available, in_demand;
    cin >> city_id >> product >> available >> in_demand;
    cout << ' ' << city_id << ' ' << product << endl;
    if (product_types.product_exists(product)) {
        if (river.city_exists_in_basin(city_id)) {
            if (not river.city_has_product(city_id, product)) {
                river.city_add_product(city_id, product_types, product, in_demand, available);
                int total_mass, total_volume;
                bool has_inventory;
                river.city_information(city_id, total_mass, total_volume, has_inventory);
                cout << total_mass << ' ' << total_volume << endl;
            } else {
                error_log("la ciudad ya tiene el producto");
            }
        } else {
            error_log("no existe la ciudad");
        }
    } else {
        error_log("no existe el producto");
    }
}

void run_command_aux_11(string const& command, ProductData& product_types, River& river, Ship& ship) {
    string city_id;
    uint32_t product;
    int available, in_demand;
    cin >> city_id >> product >> available >> in_demand;
    cout << ' ' << city_id << ' ' << product << endl;
    if (product_types.product_exists(product)) {
        if (river.city_exists_in_basin(city_id)) {
            if (river.city_has_product(city_id, product)) {
                river.city_modify_product(city_id, product_types, product, in_demand, available);
                int total_mass, total_volume;
                bool has_inventory;
                river.city_information(city_id, total_mass, total_volume, has_inventory);
                cout << total_mass << ' ' << total_volume << endl;
            } else {
                error_log("la ciudad no tiene el producto");
            }
        } else {
            error_log("no existe la ciudad");
        }
    } else {
        error_log("no existe el producto");
    }
}

void run_command_aux_12(string const& command, ProductData& product_types, River& river, Ship& ship) {
    string city_id;
    uint32_t product;
    cin >> city_id >> product;
    cout << ' ' << city_id << ' ' << product << endl;
    if (product_types.product_exists(product)) {
        if (river.city_exists_in_basin(city_id)) {
            if (river.city_has_product(city_id, product)) {
                river.city_delete_product(city_id, product_types, product);
                int total_mass, total_volume;
                bool has_inventory;
                river.city_information(city_id, total_mass, total_volume, has_inventory);
                cout << total_mass << ' ' << total_volume << endl;
            } else {
                error_log("la ciudad no tiene el producto");
            }
        } else {
            error_log("no existe la ciudad");
        }
    } else {
        error_log("no existe el producto");
    }
}

void run_command_aux_13(string const& command, ProductData& product_types, River& river, Ship& ship) {
    string city_id;
    uint32_t product;
    cin >> city_id >> product;
    cout << ' ' << city_id << ' ' << product << endl;
    if (product_types.product_exists(product)) {
        if (river.city_exists_in_basin(city_id)) {
            if (river.city_has_product(city_id, product)) {
                int in_demand, available;
                river.city_consult_product(city_id, product, in_demand, available);
                cout << available << ' ' << in_demand << endl;
            } else {
                error_log("la ciudad no tiene el producto");
            }
        } else {
            error_log("no existe la ciudad");
        }
    } else {
        error_log("no existe el producto");
    }
}

void run_command_aux_14(string const& command, ProductData& product_types, River& river, Ship& ship) {
    string city_1, city_2;
    cin >> city_1 >> city_2;
    cout << ' ' << city_1 << ' ' << city_2 << endl;
    if (river.city_exists_in_basin(city_1) and river.city_exists_in_basin(city_2)) {
        if (city_1 != city_2) {
            river.commercialize(city_1, city_2, product_types);
        } else {
            error_log("ciudad repetida");
        }
    } else {
        error_log("no existe la ciudad");
    }
}


void error_log(string const& message) {
    cout << "error: " << message << endl;
}