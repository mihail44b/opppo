#pragma once

#include <iostream>
#include <string>

class Vehicle {
protected:
    int power;
    std::string country;

    static bool compareNumbers(int actual, const std::string& operation, const std::string& val);

public:
    Vehicle(int powerVal, std::string countryVal);
    virtual ~Vehicle() = default;

    virtual void print(std::ostream& outputStream) const = 0;
    [[nodiscard]] virtual bool matchesCondition(const std::string& field, const std::string& operation, const std::string& val) const;
};

// Грузовик
class Truck : public Vehicle {
private:
    int payload;

public:
    Truck(int powerVal, std::string countryVal, int payloadVal);
    void print(std::ostream& outputStream) const override;
    [[nodiscard]] bool matchesCondition(const std::string& field, const std::string& operation, const std::string& val) const override;
};

// Автобус
class Bus : public Vehicle {
private:
    short capacity;

public:
    Bus(int powerVal, std::string countryVal, short capacityVal);
    void print(std::ostream& outputStream) const override;
    [[nodiscard]] bool matchesCondition(const std::string& field, const std::string& operation, const std::string& val) const override;
};

// Легковая
class Car : public Vehicle {
private:
    int doors;
    int maxSpeed;

public:
    Car(int powerVal, std::string countryVal, int doorsVal, int maxSpeedVal);
    void print(std::ostream& outputStream) const override;
    [[nodiscard]] bool matchesCondition(const std::string& field, const std::string& operation, const std::string& val) const override;
};
