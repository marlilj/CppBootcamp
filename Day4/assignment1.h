#include<time.h>
#include <iostream>
#include <vector>

enum Services_t {
    Repair, Wash, TireChange, Service
};
static const char *services_str[] = {"Repair", "Wash", "TireChange", "Service"};

enum Parts_t {
    Tire, Window, Lamp, Oil, None
};
static const char *parts_str[] = {"Tire", "Window", "Lamp", "Oil", "None"};

enum PaymentMethods_t {
    Swish, Card, Cash
};
static const char *payment_methods_str[] = {"Swish", "Card", "Cash"};

class Payment {
    public:
        int customer_number;
        int amount;
        PaymentMethods_t method;
        Services_t service;
        Parts_t parts;

        Payment() = delete;
        Payment(int _cn, int _a, PaymentMethods_t _method, Services_t _s, Parts_t _p):customer_number(_cn),amount(_a),method(_method),service(_s),parts(_p) {};
};

class Customer {

    private:

        std::string date;
        std::string name;
        int id;

    public:
        Customer() = delete;
        Customer(std::string _name, std::string _date, int _id):date(_date),name(_name), id(_id) {};
        int get_id();

};

class Shop {

    public:
        std::vector<Payment> payments;
        void print_payments();
        void add_payment(Payment _payment);
};