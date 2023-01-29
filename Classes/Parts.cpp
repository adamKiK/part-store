#include "iostream"
#include "Parts.h"

    Parts::Parts(std::string nid,std::string npartDesc,std::string ncategory,double nweight,double nproducerPrice,int nquantity)
    {
        id = nid;
        partDesc = npartDesc;
        category = ncategory;
        weight = nweight;
        producerPrice = nproducerPrice;
        quantity = nquantity;
    }

    std::string Parts::partInfo(){
        return "Id:" + id + " Category:" + category + " Part description:" + partDesc + " Quantity:" + (std::to_string(quantity));
    }

    std::string Parts::getPartId(){
        return id;
    }

    double Parts::getProducerPrice(){
        return producerPrice;
    }

    double Parts::getPartWeight(){
        return weight;
    }

    int Parts::getQuantity() {
        return quantity;
    }

    void Parts::updateQuantity(int nQuantity){
    quantity = nQuantity;
    }

    std::string Parts::databaseUpdate(){
        return id + " " + partDesc + " " + category + " " + std::to_string(weight) + " " + std::to_string(producerPrice) + " " + (std::to_string(quantity)) + "\n";
    }
