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
        Vehicle(int p, std::string c) : power(p), country(std::move(c)) {}
        virtual ~Vehicle() = default;

        // виртуальный метод: каждый потомок обязан реализовать свою реализацию
        virtual void print(std::ostream& os) const = 0;

        virtual bool matchesCondition(const std::string& field, const std::string& op, const std::string& val) const {
            if (field == "power") {
                int target = std::stoi(val);
                if (op == ">") return power > target;
                if (op == "<") return power < target;
                if (op == "==") return power == target;
            } else if (field == "country") {
                if (op == "==") return country == val;
                if (op == "!=") return country != val;
            }
            return false;
        }
};

// Грузовик
class Truck : public Vehicle {
    private:
        int payload; // грузоподъемность
    public:
        Truck(int p, std::string c, int load)
            : Vehicle(p, std::move(c)), payload(load) {}

        void print(std::ostream& os) const override {
            os << "[Грузовик] Страна: " << country
               << ", Мощность: " << power << " л.с."
               << ", Грузоподъемность: " << payload << " кг";
        }

        bool matchesCondition(const std::string& field, const std::string& op, const std::string& val) const override {
            if (Vehicle::matchesCondition(field, op, val)) return true;
            if (field == "payload") {
                int target = std::stoi(val);
                if (op == ">") return payload > target;
                if (op == "<") return payload < target;
                if (op == "==") return payload == target;
            }
            return false;
        }
};

// Автобус
class Bus : public Vehicle {
    private:
        short capacity;
    public:
        Bus(int p, std::string c, short cap)
            : Vehicle(p, std::move(c)), capacity(cap) {}

        void print(std::ostream& os) const override {
            os << "[Автобус]  Страна: " << country
               << ", Мощность: " << power << " л.с."
               << ", Вместимость: " << capacity << " пасс.";
        }

        bool matchesCondition(const std::string& field, const std::string& op, const std::string& val) const override {
            if (Vehicle::matchesCondition(field, op, val)) return true;
            if (field == "capacity") {
                int target = std::stoi(val);
                if (op == ">") return capacity > target;
                if (op == "<") return capacity < target;
                if (op == "==") return capacity == target;
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
        Car(int p, std::string c, int d, int s)
            : Vehicle(p, std::move(c)), doors(d), maxSpeed(s) {}

        void print(std::ostream& os) const override {
            os << "[Легковой] Страна: " << country
               << ", Мощность: " << power << " л.с."
               << ", Дверей: " << doors
               << ", Макс. скорость: " << maxSpeed << " км/ч";
        }

        bool matchesCondition(const std::string& field, const std::string& op, const std::string& val) const override {
            if (Vehicle::matchesCondition(field, op, val)) return true;
            if (field == "doors") {
                int target = std::stoi(val);
                if (op == "==") return doors == target;
            } else if (field == "speed") {
                int target = std::stoi(val);
                if (op == ">") return maxSpeed > target;
                if (op == "<") return maxSpeed < target;
                if (op == "==") return maxSpeed == target;
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
        if (line.empty()) continue;

        std::stringstream ss(line);
        std::string command;
        ss >> command;

        if (command == "ADD") {
            std::string type;
            int power;
            std::string country;

            ss >> type >> power >> country;

            if (type == "TRUCK") {
                int payload;
                ss >> payload;
                depot.push_back(std::make_unique<Truck>(power, country, payload));
            }
            else if (type == "BUS") {
                short capacity;
                ss >> capacity;
                depot.push_back(std::make_unique<Bus>(power, country, capacity));
            }
            else if (type == "CAR") {
                int doors;
                int speed;
                ss >> doors >> speed;
                depot.push_back(std::make_unique<Car>(power, country, doors, speed));
            }
        }
        else if (command == "REM") {
            std::string field, op, val;
            ss >> field >> op >> val;

            depot.erase(
                std::remove_if(depot.begin(), depot.end(),
                    [&](const std::unique_ptr<Vehicle>& v) {
                        return v->matchesCondition(field, op, val);
                    }),
                depot.end()
            );
        }
        else if (command == "PRINT") {
            std::cout << "\n=== Автопарк (" << depot.size() << ") ===" << "\n";

            for (const auto& v : depot) {
                v->print(std::cout);
                std::cout << "\n";
            }
        }
    }

    return 0;
}
