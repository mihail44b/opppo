#include <iostream>
#include <fstream>
#include <string>
#include <clocale>
#include <memory>
#include <vector>
#include <sstream>

// base class
class Vehicle {
    protected:
        int power;
        std::string country;

        static bool compareNumbers(int actual, const std::string& operation, const std::string& val) {
            try {
                int target = std::stoi(val);
                if (operation == ">") {
                    return actual > target;
                }
                else if (operation == "<") {
                    return actual < target;
                }
                else if (operation == "==") {
                    return actual == target;
                }
            } catch (...) {
                return false;
            }
            return false;
        }
    public:
        Vehicle(int powerVal, std::string countryVal) : power(powerVal), country(std::move(countryVal)) {}
        virtual ~Vehicle() = default;

        // виртуальный метод: каждый потомок обязан реализовать свою реализацию
        virtual void print(std::ostream& outputStream) const = 0;

        [[nodiscard]] virtual bool matchesCondition(const std::string& field, const std::string& operation, const std::string& val) const {
            if (field == "power") {
                return compareNumbers(power, operation, val);
            } else if (field == "country") {
                if (operation == "==") {
                    return country == val;
                }
                if (operation == "!=") {
                    return country != val;
                }
            }
            return false;
        }
};

// Грузовик
class Truck : public Vehicle {
    private:
        int payload; // грузоподъемность
    public:
        Truck(int powerVal, std::string countryVal, int payloadVal)
            : Vehicle(powerVal, std::move(countryVal)), payload(payloadVal) {}

        void print(std::ostream& outputStream) const override {
            outputStream << "[Грузовик] Страна: " << country
               << ", Мощность: " << power << " л.с."
               << ", Грузоподъемность: " << payload << " кг";
        }

        [[nodiscard]] bool matchesCondition(const std::string& field, const std::string& operation, const std::string& val) const override {
            if (Vehicle::matchesCondition(field, operation, val)) {
                return true;
            }
            if (field == "payload") {
                return compareNumbers(payload, operation, val);
            }
            return false;
        }
};

// Автобус
class Bus : public Vehicle {
    private:
        short capacity;
    public:
        Bus(int powerVal, std::string countryVal, short capacityVal)
            : Vehicle(powerVal, std::move(countryVal)), capacity(capacityVal) {}

        void print(std::ostream& outputStream) const override {
            outputStream << "[Автобус]  Страна: " << country
               << ", Мощность: " << power << " л.с."
               << ", Вместимость: " << capacity << " пасс.";
        }

        [[nodiscard]] bool matchesCondition(const std::string& field, const std::string& operation, const std::string& val) const override {
            if (Vehicle::matchesCondition(field, operation, val)) {
                return true;
            }
            if (field == "capacity") {
                return compareNumbers(capacity, operation, val);
            }
            return false;
        }
};

// Легковая
class Car : public Vehicle {
    private:
        int doors;
        int maxSpeed;
    public:
        Car(int powerVal, std::string countryVal, int doorsVal, int maxSpeedVal)
            : Vehicle(powerVal, std::move(countryVal)), doors(doorsVal), maxSpeed(maxSpeedVal) {}

        void print(std::ostream& outputStream) const override {
            outputStream << "[Легковой] Страна: " << country
               << ", Мощность: " << power << " л.с."
               << ", Дверей: " << doors
               << ", Макс. скорость: " << maxSpeed << " км/ч";
        }

        [[nodiscard]] bool matchesCondition(const std::string& field, const std::string& operation, const std::string& val) const override {
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
};

class Depot {
    private:
        std::vector<std::unique_ptr<Vehicle>> vehicles;
    public:
        void add(std::unique_ptr<Vehicle> vehicle) {
            vehicles.push_back(std::move(vehicle));
        }

        void removeByCondition(const std::string& field, const std::string& operation, const std::string& val) {
            // по стандарту c++20 используем erase_if вместо erase + remove_if
            std::erase_if(vehicles, [&](const auto& item) {
                return item->matchesCondition(field, operation, val);
            });
        }

        void printAll(std::ostream& outputStream) const {
            outputStream << "\n=== Автопарк (" << vehicles.size() << ") ===\n";
            for (const auto& item : vehicles) {
                item->print(outputStream);
                outputStream << "\n";
            }
        }
};

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
                }
                else if (type == "BUS") {
                    short capacity;
                    stream >> capacity;
                    depot.add(std::make_unique<Bus>(power, country, capacity));
                }
                else if (type == "CAR") {
                    int doors;
                    int speed;
                    stream >> doors >> speed;
                    depot.add(std::make_unique<Car>(power, country, doors, speed));
                }
            }
            else if (command == "REM") {
                std::string field;
                std::string operation;
                std::string val;

                stream >> field >> operation >> val;

                depot.removeByCondition(field, operation, val);
            }
            else if (command == "PRINT") {
                depot.printAll(std::cout);
            }
        }

        return 0;
}
