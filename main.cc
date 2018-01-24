// TIE-02006 fall 2017
// Project 04
// Juha Suvanto 189427
// jsuvanto@iki.fi

#include "prioritylist.hh"
#include <iostream>
#include <string>
#include <regex>

void chorelistNotSet() {
    std::cout << "Error: chore list not set." << std::endl;
}


int main() {

    PriorityList* chorelist = nullptr;

    std::string input;
    std::regex parser("^([a-zA-Z]+) ?(-?[0-9]+)? ?(.*)?");
    std::smatch match;

    while(true) {
        std::cout << "chores> ";
        std::getline(std::cin, input);
        std::regex_search(input, match, parser);

        std::string command = match.str(1);
        std::string param1 = match.str(2);
        std::string param2 = match.str(3);

        //std::cout << command << "|" << param1 << "|" << param2 << std::endl; // for debug

        if (command == "quit") {
            delete chorelist;
            break;
        }

        else if (command == "next") {
            if (chorelist == nullptr) chorelistNotSet();
            else if (param1 != "" || param2 != "") std::cout << "Error: extra text after next command." << std::endl;
            else chorelist->nextChore();
        }

        else if (command == "print") {
            if (chorelist == nullptr) chorelistNotSet();
            else if (param1 != "" || param2 != "") std::cout << "Error: extra text after print command." << std::endl;
            else chorelist->printChores();
        }

        else if (command == "init") {
            try {
                int levels = std::stoi(param1);
                if (param2 != "") std::cout << "Error: extra text after init command." << std::endl;
                else if (levels < 1) std::cout << "Error: it is not possible to create a priority list with 0 or less levels." << std::endl; // Error for "init 0"
                else chorelist = new PriorityList(levels); // Successful initialization
            } catch (std::invalid_argument) {                
                if (param2 == "") std::cout << "Error: the number of priority levels is missing." << std::endl; // Error for "init" without arguments
                else if (param1 == "") std::cout << "Error: the number of priority levels must be an integer larger than 0." << std::endl; // Error for "init a"
            } catch (std::out_of_range) {
                std::cout << "Error: the number of priority levels is out of range." << std::endl;
            }
        }

        else if (command == "erase") {
            if (chorelist == nullptr) chorelistNotSet();            
            else try {
                int number = std::stoi(param1);
                if (param2 != "") std::cout << "Error: extra text after erase command." << std::endl;
                else chorelist->eraseChore(number);
            } catch (std::invalid_argument) {
                if (param2 =="") std::cout << "Error: the running number is missing." << std::endl; // Error for "erase" without arguments
                else std::cout << "Error: the running number must be an integer larger than 0." << std::endl; // Error for "erase a"
            } catch (std::out_of_range) {
                std::cout << "Error: the running number is out of range." << std::endl;
            }
        }

        else if (command == "add") {
            if (chorelist == nullptr) chorelistNotSet();
            else try {
                int number = std::stoi(param1);
                chorelist->addChore(number, param2);
            } catch (std::invalid_argument) {
                if (param1  == "" && param2 == "") std::cout << "Error: priority level and chore description are missing." << std::endl;
                else std::cout << "Error: priority level must be an integer between 1-3." << std::endl;
            } catch (std::out_of_range) {
                std::cout << "Error: the priority level is out of range."  << std::endl;
            }
        }

        else std::cout << "Error: unknown command" << std::endl;
    }
}
