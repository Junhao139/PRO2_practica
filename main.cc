/* main.cc */

#include <iostream>

/* INPUT MANAGERS */

/* OPERATIONS */
void operations_manager();

int main() {

}

void operations_manager() {
    std::string command;
    std::cin >> command;
    while (command != "fin") {
        /* Comment */
        if (command[0] == '\\' and command[1] == '\\') {
            
        }
        /* 1 */
        else if (command == "leer_rio" or command == "lr") {

        }
        /* 2 */
        else if (command == "leer_inventario" or command == "li") {

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

        std::cin >> command;
    }
}