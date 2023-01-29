#ifndef INC_2__MY_FIRST_ORDER_H
#define INC_2__MY_FIRST_ORDER_H


// Class creates an objects vector storing information on ordered parts
class Order {
public:
    Order(std::string npartID, int nquantity);

    /*
     * Funkcja sprawdzająca "dostępność" części.
     * Method checks availability of a part.
     * The output value is used to calculate end cost of a part based on the simulated "complexity of delivery". 
    */
    double checkAvailability();

    // Calculate the delivery costs based on the availability cost and the weight of the part.
    double randomCost(std::vector<Parts> &partDatabase, int dbSize);

    double getCost();

    std::string getId();

    int getAvailability();

    int getQuantity();

    void addQuantity(int add);

private:
    int quantity;
    double availability;
    double cost;
    std::string partId;
};

#endif //INC_2__MY_FIRST_ORDER_H
