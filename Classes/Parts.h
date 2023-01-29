#ifndef INC_2__MY_FIRST_PARTS_H
#define INC_2__MY_FIRST_PARTS_H


class Parts{
public:
    Parts(std::string nid,std::string npartDesc,std::string ncategory,double nweight,double nproducerPrice, int nquantity);

    std::string partInfo();

    std::string getPartId();

    double getProducerPrice();

    double getPartWeight();

    int getQuantity();

    void updateQuantity(int nQuantity);

    std::string databaseUpdate();

private:
    std::string id;
    std::string partDesc;
    std::string category;
    double weight;
    double producerPrice;
    int quantity;
};

#endif //INC_2__MY_FIRST_PARTS_H
