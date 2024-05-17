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
    River&          river_structure,
    Ship&           ship
);

/** @brief  Runs a command given the datas of the params.
 *  \pre    "command" is valid; "types_of_products" is non-null; "river_structure" is valid; "ship" is valid.
 *  \post   The command is run. "types_of_products", "river_structure" and "ship" are modified.
*/
void run_command(
    string const&   command,
    ProductData&    product_types,
    River&          river,
    Ship&           ship
);

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
            cout << "#" << command << endl;

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
    }
    /* 2 */
    else if (command == "leer_inventario" or command == "li") {
        string city_id;
        cin >> city_id;
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
    /* 3 */
    else if (command == "leer_inventarios" or command == "ls") {
        string city_id;
        cin >> city_id;
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
    /* 4 */
    else if (command == "modificar_barco" or command == "mb") {
        uint32_t ship_wanted, ship_for_sell;
        int ship_wanted_qtty, ship_for_sell_qtty;
        cin >> ship_wanted   >> ship_wanted_qtty
            >> ship_for_sell >> ship_for_sell_qtty;
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
    /* 5 */
    else if (command == "escribir_barco" or command == "eb") {
        cout << ship.wanted_product()   << ' ' << ship.wanted_number()   << ' '
             << ship.for_sell_product() << ' ' << ship.for_sell_number() << endl;
        ship.write_all_destinations();
    }
    /* 6 */
    else if (command == "consultar_num" or command == "cn") {
        cout << product_types.database_size() << endl;
    }
    /* 7 */
    else if (command == "agregar_productos" or command == "ap") {
        int input_quantity;
        cin >> input_quantity;
        for (int i = 0; i < input_quantity; ++i) {
            int mass, volume;
            cin >> mass >> volume;
            product_types.add_new_product(Product(mass, volume));
        }
    }
    /* 8 */
    else if (command == "escribir_producto" or command == "ep") {
        uint32_t product;
        cin >> product;
        if (product_types.product_exists(product)) {
            Product prod(0, 0);
            product_types.consult_product(prod, product);
            cout << prod.get_mass() << ' ' << prod.get_volume() << endl;
        } else {
            error_log("no existe el producto");
        }
    }
    /* 9 */
    else if (command == "escribir_ciudad" or command == "ec") {
        string city_id;
        cin >> city_id;
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
    /* 10 */
    else if (command == "poner_prod" or command == "pp") {
        string city_id;
        uint32_t product;
        int available, in_demand;
        cin >> city_id >> product >> available >> in_demand;
        if (product_types.product_exists(product)) {
            if (river.city_exists_in_basin(city_id)) {
                if (not river.city_has_product(city_id, product)) {
                    river.city_add_product(city_id, product_types, product, available, in_demand);
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
    /* 11 */
    else if (command == "modificar_prod" or command == "mp") {
        string city_id;
        uint32_t product;
        int available, in_demand;
        cin >> city_id >> product >> available >> in_demand;
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
    /* 12 */
    else if (command == "quitar_prod" or command == "qp") {
        string city_id;
        uint32_t product;
        cin >> city_id >> product;
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
    /* 13 */
    else if (command == "consultar_prod" or command == "cp") {
        string city_id;
        uint32_t product;
        cin >> city_id >> product;
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
    /* 14 */
    else if (command == "comerciar" or command == "co") {
        string city_1, city_2;
        cin >> city_1 >> city_2;
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
    /* 15 */
    else if (command == "redistribuir" or command == "re") {
        river.redistribute(product_types);
    }
    /* 16 */
    else if (command == "hacer_viaje" or command == "hv") {
        int bought_units, sold_units;
        river.ship_travelling(ship, product_types, bought_units, sold_units);
        cout << bought_units + sold_units << endl; 
    }
}

void error_log(string const& message) {
    cout << "error: " << message << endl;
}