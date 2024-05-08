/* main.cc */

#include <iostream>
#include <string>

#include "basin.hh"

using namespace std;

int main() {
    Basin basin;
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
            basin.run_command(command);
        }

        cin >> command;
    }
}