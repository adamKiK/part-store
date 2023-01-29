#ifndef INC_2__MY_FIRST_DATABASE_H
#define INC_2__MY_FIRST_DATABASE_H


// Class responsible for working on files and creating orders
class Database
{
public:

    // Method creates new fictional car parts database
    void partDatabaseCreate();

    /*
     * Method reads "Available parts" database from specified ".txt" file
     * Method creates objects and appends them to "partDatabas" - a vector of available parts
     */
    void dataRead(std::vector<Parts> &partDatabase);

    // Checking database size - number of lines in the textfile. Each new line corresponds to a new part
    void databaseSizeCheck();

    // Listing available parts to the user
    void listParts(std::vector<Parts> &partDatabase);

    // Method creates objects in the "orderDatabase" which holds info on ordered parts
    void makeOrder(std::vector<Parts> &partDatabase,std::vector<Order> &orderDatabase);

    // Checking wheter a part is already in the order, if there is already one instance, the user is asked about adding quantity
    bool searchIfOrdered(std::vector<Parts> &partDatabase, std::vector<Order> &orderDatabase, std::string partID, int k, int available, int partIndex);
    
    // Method adds new parts to the "ordered" vector
    int addToOrderDatabase(std::vector<Parts> &partDatabase, std::vector<Order> &orderDatabase, std::string partID, bool isInPartDatabase, bool isInOrderDatabase, int partIndex);

    // Method saves "ordered" vector's objects to "orders.txt"
    void saveOrder(std::vector<Order> &orderDatabase, std::vector<Parts> &partDatabase);

    // Method clears order
    void clearOrder(std::vector<Order> &orderDatabase);

private:
    int dbSize;
};


#endif //INC_2__MY_FIRST_DATABASE_H
