#include"assignment1.h"

void Shop::add_payment(Payment _payment) {
    this->payments.push_back(_payment);
}

int Customer::get_id() {
    return this->id;
}

void Shop::print_payments() {
    for (const Payment &p : this->payments) {
        std::cout << "Customer id: " << p.customer_number << std::endl;
        std::cout << "\tAmount: " << p.amount << std::endl;
        std::cout << "\tService: " << services_str[p.service] << std::endl;
        std::cout << "\tParts: " << p.parts <<std::endl;
        std::cout << "\tPayment method: " << p.method <<std::endl;
    }
}

int main() {
    Customer c1("Marie", "2021-10-07", 1);
    Payment p1(c1.get_id(), 100, PaymentMethods_t::Card, Services_t::TireChange, Parts_t::Tire);
    Payment p2(c1.get_id(), 1000, PaymentMethods_t::Cash, Services_t::Service, Parts_t::None);
    Shop shop;
    shop.add_payment(p1);
    shop.add_payment(p2);
    shop.print_payments();
}

