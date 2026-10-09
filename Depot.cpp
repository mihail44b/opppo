#include "Depot.hpp"

void Depot::add(std::unique_ptr<Vehicle> vehicle) {
    vehicles.push_back(std::move(vehicle));
}

void Depot::removeByCondition(const std::string& field, const std::string& operation, const std::string& val) {
    std::erase_if(vehicles, [&](const auto& item) {
        return item->matchesCondition(field, operation, val);
    });
}

void Depot::printAll(std::ostream& outputStream) const {
    outputStream << "\n=== Автопарк (" << vehicles.size() << ") ===\n";
    for (const auto& item : vehicles) {
        item->print(outputStream);
        outputStream << "\n";
    }
}
