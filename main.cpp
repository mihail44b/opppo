#include "Depot.hpp"
#include <iostream>
#include <fstream>
#include <sstream>
#include <clocale>

int main() {
    std::setlocale(LC_ALL, ".UTF-8");

    Depot depot;

    std::ifstream file("commands.txt");
    if (!file.is_open()) {
        std::cerr << "Не удалось открыть файл" << "\n";
        return 1;
    }

    std::string line;

    while (std::getline(file, line)) {
        if (line.empty()) {
            continue;
        }

        std::stringstream stream(line);
        std::string command;
        stream >> command;

        if (command == "ADD") {
            std::string type;
            int power;
            std::string country;

            stream >> type >> power >> country;

            if (type == "TRUCK") {
                int payload;
                stream >> payload;
                depot.add(std::make_unique<Truck>(power, country, payload));
            } else if (type == "BUS") {
                short capacity;
                stream >> capacity;
                depot.add(std::make_unique<Bus>(power, country, capacity));
            } else if (type == "CAR") {
                int doors;
                int speed;
                stream >> doors >> speed;
                depot.add(std::make_unique<Car>(power, country, doors, speed));
            }
        } else if (command == "REM") {
            std::string field;
            std::string operation;
            std::string val;

            stream >> field >> operation >> val;

            depot.removeByCondition(field, operation, val);
        } else if (command == "PRINT") {
            depot.printAll(std::cout);
        }
    }

    return 0;
}
