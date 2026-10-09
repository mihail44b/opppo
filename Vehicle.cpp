#include "Vehicle.hpp"

// Vehicle
bool Vehicle::compareNumbers(int actual, const std::string& operation, const std::string& val) {
    try {
        int target = std::stoi(val);
        if (operation == ">") {
            return actual > target;
        }
        if (operation == "<") {
            return actual < target;
        }
        if (operation == "==") {
            return actual == target;
        }
    } catch (...) {
        return false;
    }
    return false;
}

Vehicle::Vehicle(int powerVal, std::string countryVal)
    : power(powerVal), country(std::move(countryVal)) {}

bool Vehicle::matchesCondition(const std::string& field, const std::string& operation, const std::string& val) const {
    if (field == "power") {
        return compareNumbers(power, operation, val);
    }
    if (field == "country") {
        if (operation == "==") {
            return country == val;
        }
        if (operation == "!=") {
            return country != val;
        }
    }
    return false;
}

// Truck
Truck::Truck(int powerVal, std::string countryVal, int payloadVal)
    : Vehicle(powerVal, std::move(countryVal)), payload(payloadVal) {}

void Truck::print(std::ostream& outputStream) const {
    outputStream << "[Грузовик] Страна: " << country
                 << ", Мощность: " << power << " л.с."
                 << ", Грузоподъемность: " << payload << " кг";
}

bool Truck::matchesCondition(const std::string& field, const std::string& operation, const std::string& val) const {
    if (Vehicle::matchesCondition(field, operation, val)) {
        return true;
    }
    if (field == "payload") {
        return compareNumbers(payload, operation, val);
    }
    return false;
}

// Bus
Bus::Bus(int powerVal, std::string countryVal, short capacityVal)
    : Vehicle(powerVal, std::move(countryVal)), capacity(capacityVal) {}

void Bus::print(std::ostream& outputStream) const {
    outputStream << "[Автобус]  Страна: " << country
                 << ", Мощность: " << power << " л.с."
                 << ", Вместимость: " << capacity << " пасс.";
}

bool Bus::matchesCondition(const std::string& field, const std::string& operation, const std::string& val) const {
    if (Vehicle::matchesCondition(field, operation, val)) {
        return true;
    }
    if (field == "capacity") {
        return compareNumbers(capacity, operation, val);
    }
    return false;
}

// Car
Car::Car(int powerVal, std::string countryVal, int doorsVal, int maxSpeedVal)
    : Vehicle(powerVal, std::move(countryVal)), doors(doorsVal), maxSpeed(maxSpeedVal) {}

void Car::print(std::ostream& outputStream) const {
    outputStream << "[Легковой] Страна: " << country
                 << ", Мощность: " << power << " л.с."
                 << ", Дверей: " << doors
                 << ", Макс. скорость: " << maxSpeed << " км/ч";
}

bool Car::matchesCondition(const std::string& field, const std::string& operation, const std::string& val) const {
    if (Vehicle::matchesCondition(field, operation, val)) {
        return true;
    }
    if (field == "doors") {
        return compareNumbers(doors, operation, val);
    }
    if (field == "speed") {
        return compareNumbers(maxSpeed, operation, val);
    }
    return false;
}
