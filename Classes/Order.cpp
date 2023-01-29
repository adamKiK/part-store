#include "iostream"
#include "vector"
#include "Parts.h"
#include "Order.h"

// Class creates an objects vector storing information on ordered parts
    Order::Order(std::string npartID, int nquantity) {
        partId = npartID;
        quantity = nquantity;
    }

    /*
     * Funkcja sprawdzająca "dostępność" części.
     * Method checks availability of a part.
     * The output value is used to calculate end cost of a part based on the simulated "complexity of delivery". 
    */
    double Order::checkAvailability() {
        srand(time(NULL));
        availability = rand() % 5 + 1;
        return availability;
    }

    // Calculate the delivery costs based on the availability cost and the weight of the part.
    double Order::randomCost(std::vector<Parts> &partDatabase, int dbSize) {
        int index = 0;
        int avail = checkAvailability();

        while (index <= dbSize and partId != partDatabase[index].getPartId()) {
            index++;
        }


        cost = partDatabase[index].getProducerPrice();
        if (avail <= 2)
        {
            cost += cost * (avail / 10.0);
        }
        else
        {
            cost += cost * (((avail - 1) / 10.0) * partDatabase[index].getPartWeight() / 10.0);
        }

        return cost;
    }

    double Order::getCost()
    {
        double nCost = cost * double(quantity);
        return nCost;
    }

    std::string Order::getId()
    {
        return partId;
    }

    int Order::getAvailability()
    {
        return availability;
    }

    int Order::getQuantity()
    {
        return quantity;
    }

    void Order::addQuantity(int add)
    {
        quantity += add;
    }

