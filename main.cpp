#include <iostream>
#include <fstream>
#include <string>
#include <clocale>
#include <memory>
#include <vector>
#include <sstream>
#include <algorithm>

// base class
class Vehicle {
    protected:
        int power;
        std::string country;
    public:
        Vehicle(int powerVal, std::string countryVal) : power(powerVal), country(std::move(countryVal)) {}
        virtual ~Vehicle() = default;

        // виртуальный метод: каждый потомок обязан реализовать свою реализацию
        virtual void print(std::ostream& outputStream) const = 0;

        virtual bool matchesCondition(const std::string& field, const std::string& operation, const std::string& val) const {
            if (field == "power") {
                int target = std::stoi(val);
                if (operation == ">") {
                    return power > target;
                }
                if (operation == "<") {
                    return power < target;
                }
                if (operation == "==") {
                    return power == target;
                }
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

        bool matchesCondition(const std::string& field, const std::string& operation, const std::string& val) const override {
            if (Vehicle::matchesCondition(field, operation, val)) {
                return true;
            }
            if (field == "payload") {
                int target = std::stoi(val);
                if (operation == ">") {
                    return payload > target;
                }
                if (operation == "<") {
                    return payload < target;
                }
                if (operation == "==") {
                    return payload == target;
                }
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

        bool matchesCondition(const std::string& field, const std::string& operation, const std::string& val) const override {
            if (Vehicle::matchesCondition(field, operation, val)) {
                return true;
            }
            if (field == "capacity") {
                int target = std::stoi(val);
                if (operation == ">") {
                    return capacity > target;}
                if (operation == "<") {
                    return capacity < target;
                }
                if (operation == "==") {
                    return capacity == target;
                }
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

        bool matchesCondition(const std::string& field, const std::string& operation, const std::string& val) const override {
            if (Vehicle::matchesCondition(field, operation, val)) {
                return true;
            }
            if (field == "doors") {
                int target = std::stoi(val);
                if (operation == "==") {
                    return doors == target;
                }
            } else if (field == "speed") {
                int target = std::stoi(val);
                if (operation == ">") {
                    return maxSpeed > target;
                }
                if (operation == "<") {
                    return maxSpeed < target;
                }
                if (operation == "==") {
                    return maxSpeed == target;
                }
            }
            return false;
        }
};

int main() {
    std::setlocale(LC_ALL, ".UTF-8");

    std::vector<std::unique_ptr<Vehicle>> depot;

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
                depot.push_back(std::make_unique<Truck>(power, country, payload));
            }
            else if (type == "BUS") {
                short capacity;
                stream >> capacity;
                depot.push_back(std::make_unique<Bus>(power, country, capacity));
            }
            else if (type == "CAR") {
                int doors;
                int speed;
                stream >> doors >> speed;
                depot.push_back(std::make_unique<Car>(power, country, doors, speed));
            }
        }
        else if (command == "REM") {

            std::string field;
            std::string operation;
            std::string val;

            stream >> field >> operation >> val;

            depot.erase(
                std::remove_if(depot.begin(), depot.end(),
                    [&](const std::unique_ptr<Vehicle>& item) {
                        return item->matchesCondition(field, operation, val);
                    }),
                depot.end()
            );
        }
        else if (command == "PRINT") {
            std::cout << "\n=== Автопарк (" << depot.size() << ") ===" << "\n";

            for (const auto& item : depot) {
                item->print(std::cout);
                std::cout << "\n";
            }
        }
    }

    return 0;
}
