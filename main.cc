/**
 * @file    main.cc
 * @author  Junhao Liu
 * @brief   The file that contains main function, and the first layer of command processing.
 */

#ifndef NO_DIAGRAM
#include <iostream>
#include <string>
#endif // NO_DIAGRAM

#include "river.hh"
#include "product_data.hh"
#include "product.hh"
#include "ship.hh"

using namespace std;

/** @brief  The beginning input.
 *  \pre    TRUE.
 *  \post   It prepares the initial data according to the project description.
 * 
 *  @param  types_of_products   It will be initialized with Practica's default initial data.
 *  @param  river_structure     It will be initialized with Practica's default initial data.
 *  @param  ship                It will be initialized with Practica's default initial data.
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
 *  @param  command         The command indicator of which function is to be done.
 *  @param  product_types   The products' database.
 *  @param  river           The basin's structure and city members.
 *  @param  ship            The ship containing info for travelling and trades.
*/
void run_command(
    string const&   command,
    ProductData&    product_types,
    River&          river,
    Ship&           ship
);

/**
 *  @brief  Auxiliary function for the "run_command()".
 *  \pre    "product_types" contains all intervened products. "river" is a valid one.
 *  \post   The requirement 2 is done. (See Practica's Enunciat and run_command()'s corresponding section)
 */
void run_command_aux_2(ProductData& product_types, River& river);
/**
 *  @brief  Auxiliary function for the "run_command()".
 *  \pre    "product_types" contains all intervened products. "river" is a valid one.
 *  \post   The requirement 3 is done. (See Practica's Enunciat and run_command()'s corresponding section)
 */
void run_command_aux_3(ProductData& product_types, River& river);
/**
 *  @brief  Auxiliary function for the "run_command()".
 *  \pre    "product_types" contains all intervened products. "ship" is a valid one.
 *  \post   The requirement 4 is done. (See Practica's Enunciat and run_command()'s corresponding section)
 */
void run_command_aux_4(ProductData& product_types, Ship& ship);
/**
 *  @brief  Auxiliary function for the "run_command()".
 *  \pre    "product_types" contains all intervened products.
 *  \post   The requirement 7 is done. (See Practica's Enunciat and run_command()'s corresponding section)
 */
void run_command_aux_7(ProductData& product_types);
/**
 *  @brief  Auxiliary function for the "run_command()".
 *  \pre    "product_types" contains all intervened products.
 *  \post   The requirement 8 is done. (See Practica's Enunciat and run_command()'s corresponding section)
 */
void run_command_aux_8(ProductData& product_types);
/**
 *  @brief  Auxiliary function for the "run_command()".
 *  \pre    "river" is a valid one.
 *  \post   The requirement 9 is done. (See Practica's Enunciat and run_command()'s corresponding section)
 */
void run_command_aux_9(River& river);
/**
 *  @brief  Auxiliary function for the "run_command()".
 *  \pre    "product_types" contains all intervened products. "river" is a valid one.
 *  \post   The requirement 10 is done. (See Practica's Enunciat and run_command()'s corresponding section)
 */
void run_command_aux_10(ProductData& product_types, River& river);
/**
 *  @brief  Auxiliary function for the "run_command()".
 *  \pre    "product_types" contains all intervened products. "river" is a valid one.
 *  \post   The requirement 11 is done. (See Practica's Enunciat and run_command()'s corresponding section)
 */
void run_command_aux_11(ProductData& product_types, River& river);
/**
 *  @brief  Auxiliary function for the "run_command()".
 *  \pre    "product_types" contains all intervened products. "river" is a valid one.
 *  \post   The requirement 12 is done. (See Practica's Enunciat and run_command()'s corresponding section)
 */
void run_command_aux_12(ProductData& product_types, River& river);
/**
 *  @brief  Auxiliary function for the "run_command()".
 *  \pre    "product_types" contains all intervened products. "river" is a valid one.
 *  \post   The requirement 13 is done. (See Practica's Enunciat and run_command()'s corresponding section)
 */
void run_command_aux_13(ProductData& product_types, River& river);
/**
 *  @brief  Auxiliary function for the "run_command()".
 *  \pre    "product_types" contains all intervened products. "river" is a valid one.
 *  \post   The requirement 14 is done. (See Practica's Enunciat and run_command()'s corresponding section)
 */
void run_command_aux_14(ProductData& product_types, River& river);


/** @brief  Outputs in "error: $message$" format the indicated message.
 *  \pre    TRUE.
 *  \post   The message will appear in output stream.
 * 
 *  @param  message The message to be logged.
*/
void error_log(string const& message);


int main()
{
    /** @brief  All types of products are registered by this object.
     */
    ProductData types_of_products;

    /** @brief  The river's structure is stored in this object. All the commerces are handled by it.
    */
    River river_structure;

    /** @brief  The ship.
    */
    Ship ship;

    // Initial data inputs
    initial_data(types_of_products, river_structure, ship);

    // Command execution
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
    )
{
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
    )
{
    /* 1 */
    if (command == "leer_rio" or command == "lr") {
        ship.clear_all_destinations();
        river.input_river_structure();
        cout << endl;
    }
    /* 2 */
    else if (command == "leer_inventario" or command == "li") {
        run_command_aux_2(product_types, river);
    }
    /* 3 */
    else if (command == "leer_inventarios" or command == "ls") {
        run_command_aux_3(product_types, river);
    }
    /* 4 */
    else if (command == "modificar_barco" or command == "mb") {
        run_command_aux_4(product_types, ship);
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
        run_command_aux_7(product_types);
    }
    /* 8 */
    else if (command == "escribir_producto" or command == "ep") {
        run_command_aux_8(product_types);
    }
    /* 9 */
    else if (command == "escribir_ciudad" or command == "ec") {
        run_command_aux_9(river);
    }
    /* 10 */
    else if (command == "poner_prod" or command == "pp") {
        run_command_aux_10(product_types, river);
    }
    /* 11 */
    else if (command == "modificar_prod" or command == "mp") {
        run_command_aux_11(product_types, river);
    }
    /* 12 */
    else if (command == "quitar_prod" or command == "qp") {
        run_command_aux_12(product_types, river);
    }
    /* 13 */
    else if (command == "consultar_prod" or command == "cp") {
        run_command_aux_13(product_types, river);
    }
    /* 14 */
    else if (command == "comerciar" or command == "co") {
        run_command_aux_14(product_types, river);
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

void run_command_aux_2(ProductData& product_types, River& river)
{
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

void run_command_aux_3(ProductData& product_types, River& river)
{
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

void run_command_aux_4(ProductData& product_types, Ship& ship)
{
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

void run_command_aux_7(ProductData& product_types)
{
    int input_quantity;
    cin >> input_quantity;
    cout << ' ' << input_quantity << endl;
    for (int i = 0; i < input_quantity; ++i) {
        int mass, volume;
        cin >> mass >> volume;
        product_types.add_new_product(Product(mass, volume));
    }
}

void run_command_aux_8(ProductData& product_types)
{
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

void run_command_aux_9(River& river)
{
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

void run_command_aux_10(ProductData& product_types, River& river)
{
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

void run_command_aux_11(ProductData& product_types, River& river)
{
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

void run_command_aux_12(ProductData& product_types, River& river)
{
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

void run_command_aux_13(ProductData& product_types, River& river)
{
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

void run_command_aux_14(ProductData& product_types, River& river)
{
    string city_1, city_2;
    cin >> city_1 >> city_2;
    cout << ' ' << city_1 << ' ' << city_2 << endl;
    if (river.city_exists_in_basin(city_1) and river.city_exists_in_basin(city_2)) {
        if (city_1 != city_2) {
            river.trade(city_1, city_2, product_types);
        } else {
            error_log("ciudad repetida");
        }
    } else {
        error_log("no existe la ciudad");
    }
}


void error_log(string const& message)
{
    cout << "error: " << message << endl;
}