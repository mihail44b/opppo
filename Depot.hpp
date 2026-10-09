#pragma once

#include "Vehicle.hpp"
#include <vector>
#include <memory>
#include <iostream>

class Depot {
private:
    std::vector<std::unique_ptr<Vehicle>> vehicles;

public:
    void add(std::unique_ptr<Vehicle> vehicle);
    void removeByCondition(const std::string& field, const std::string& operation, const std::string& val);
    void printAll(std::ostream& outputStream) const;
};
