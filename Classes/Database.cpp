#include "iostream"
#include "vector"
#include "fstream"
#include "Parts.h"
#include "Order.h"
#include "Database.h"
 
    // Method creates new fictional car parts database
    void Database::partDatabaseCreate()
    {
        double weight = 0.0, producerPrice = 0.0;
        int cat, quantity = 0;
        std::string partDesc[4][4] {{"belt", "roller", "sensor", "sparkPlug"}, {"wire", "sensor", "battery", "device"}, {"oil", "filter", "brakePad", "bulb"}, {"bumper", "door", "mirror", "windshield"}};
        std::string category[4] {"engine", "electronics", "replaceable", "exterior"};

        std::fstream file;
        file.open("databaseNew.txt", std::ios::out);

        for (int i = 0; i < 51; ++i)
        {
            srand(rand());
            weight = double(rand() % 50000 + 10) / 100;
            producerPrice = rand() % 300 + 0;
            cat = rand() % 4;
            quantity = rand() % 100+1;

            if  (i < 10)
            {
                file << "00" << i << " " << partDesc[cat][rand()% 4] << " " << category[cat] << " " << weight << " " << producerPrice << " " << quantity <<std::endl;
            } else
            {
                file << "0" << i << " " << partDesc[cat][rand()% 4] << " " << category[cat] << " " << weight << " " << producerPrice << " " << quantity << std::endl;
            }
        }
        file.close();
        std::cout << ">>> Baza danych została zaktualizowana" << std::endl;
    }

    /*
     * Method reads "Available parts" database from specified ".txt" file
     * Method creates objects and appends them to "partDatabas" - a vector of available parts
     */
    void Database::dataRead(std::vector<Parts> &partDatabase){
        // Opening file
        std::fstream file;
        file.open("/home/adam/Documents/Learning/Programming/PPO 2 Sem Zaliczenie/databaseNew.txt", std::ios::in);
        int quantity;
        double weight, producerPrice;
        std::string id, line, data;
        std::string partDesc, category;

        std::cout << "### Utworzono zmienne funkcji partRead ###" << std::endl;

        std::cout << "### Sprawdzono rozmiar bazy danych ###" << "\n### Jej rozmiar to: " << dbSize <<  std::endl;

        // Loop that appends read data to corresponding variables
        for (int i = 0; i <= dbSize-1; ++i)
        {
            int j = 0;
            while(j != 6 and file >> data){
                switch (j) {
                    case 0:
                        id = data;
                        ++j;
                        break;
                    case 1:
                        partDesc = data;
                        ++j;
                        break;
                    case 2:
                        category = data;
                        ++j;
                        break;
                    case 3:
                        weight = std::stod(data);
                        ++j;
                        break;
                    case 4:
                        producerPrice = std::stod(data);
                        ++j;
                        break;
                    case 5:
                        quantity = std::stoi(data);
                        ++j;
                }
            }
            // Create objects with specified data and adding them to "partDatabase" vector
            Parts part(id,partDesc,category,weight,producerPrice,quantity);
            partDatabase.push_back(part);
        }

        std::cout << "### Utworzono obiekty bazy danych ###" << std::endl;

        file.close();
        std::cout << "### Plik został zamknięty poprawnie ###" << std::endl;
    }

    // Checking database size - number of lines in the textfile. Each new line corresponds to a new part 
    void Database::databaseSizeCheck()
    {
        dbSize = 0;
        std::string line;
        std::fstream file;
        file.open("databaseNew.txt", std::ios::in);
        while (getline(file,line))
        {
            ++dbSize;
        }
        file.close();
    }

    // Listing available parts to the user
    void Database::listParts(std::vector<Parts> &partDatabase)
    {
        std::cout << "### Rozpoczęto proces zamówienia ###" << std::endl;
        std::cout << "Produkty dostępne w bazie danych to: " << std::endl;
        for (int i = 0; i <= dbSize-1; ++i)
        {
            std::cout << i+1 << ". " <<partDatabase[i].partInfo() << std::endl;
        }
    }

    // Method creates objects in the "orderDatabase" which holds info on ordered parts
    void Database::makeOrder(std::vector<Parts> &partDatabase,std::vector<Order> &orderDatabase)
    {
        int i = 0, quantity = 0, partIndex = 0;
        int available = 0;
        std::string partID = "";
        bool isInPartDatabase = false;
        bool isInOrderDatabase = false;


        std::cout << "Wprowadź numery ID wszystkich części, które chcesz zamówić, jeśli chcesz zamknąć zamówienie wpisz N" << std::endl;

        /*
         * Input part Id's which the user wants to order
         * Programs stopps ONLY after entering the letter 'N'. There is no method that checks whether a given ID exists. 
        */

        do
        {
            std::cout << "Wprowadź ID produktu: ";
            std::cin >> partID;

            for (int x = 0; x <= partDatabase.size(); ++x)
            {
                if (partID == partDatabase[x].getPartId())
                {
                    isInPartDatabase = true;
                    partIndex = x;
                    available = partDatabase[partIndex].getQuantity();
                    std::cout << ">>> Znaleziono dany produkt w bazie części w ilości: " << available << " szt."<< std::endl;

                    if (orderDatabase.size() > 0)
                    {
                        isInOrderDatabase = false;
                        for (int k = 0; k < orderDatabase.size(); ++k)
                        {
                            while (!isInOrderDatabase)
                            {
                                if (searchIfOrdered(partDatabase, orderDatabase, partID, k, available, partIndex)) {
                                    isInOrderDatabase = true;
                                }
                                else
                                {
                                    break;
                                }
                            }
                        }
                    }
                }
            }

            if (!isInPartDatabase)
            {
                std::cout << ">>> Nie znaleziono części w bazie danych, spróbuj ponownie lub zakończ program" << std::endl;
            }

            if (addToOrderDatabase(partDatabase,orderDatabase,partID,isInPartDatabase,isInOrderDatabase,partIndex))
            {
                i++;
            }

        } while (partID != "N");

        std::cout << "\nTwoje zamówienie to" << std::endl;

        // Loops outputs list of ordered items and the overall cost of the order
        for (int j = 0; j < i; ++j) {
            std::cout << j+1 << ".    ID części: " << orderDatabase[j].getId() << "    Ilość: " << orderDatabase[j].getQuantity() <<"szt.    Koszt pozycji: " << orderDatabase[j].getCost() << " PLN" << std::endl;
        }
        std::cout << "\nZalecamy zapisanie zamówienia" << std::endl;
    }

    // Checking wheter a part is already in the order, if there is already one instance, the user is asked about adding quantity
    bool Database::searchIfOrdered(std::vector<Parts> &partDatabase, std::vector<Order> &orderDatabase, std::string partID, int k, int available, int partIndex)
    {
    bool isInOrderDatabase = false;
        if (partID == orderDatabase[k].getId() && orderDatabase[k].getQuantity() > 0)
        {
            std::string choice = "";
            isInOrderDatabase = true;
            std::cout << "W aktualnym zamówieniu dodano już " << orderDatabase[k].getQuantity()
                      << " sztuk tego produktu, czy dodać więcej? (T/N) ";
            std::cin >> choice;

            if (choice == "T")
            {
                int add = 0;
                std::cout << "Ile sztuk chcesz dodać? :";
                std::cin >> add;

                if (add <= available)
                {
                    available = available - add;
                    orderDatabase[k].addQuantity(add);
                    partDatabase[partIndex].updateQuantity(available);
                    std::cout << "\nTeraz w zamówieniu jest " << orderDatabase[k].getQuantity()
                              << " sztuk tego towaru, dostępnych jest jeszcze "
                              << partDatabase[partIndex].getQuantity() << " szt" << std::endl;
                }
                else
                {
                    std::cout
                            << "Podana ilość przekroczyła ilość dostępną w bazie danych.\nSpróbuj ponownie."
                            << std::endl;
                }
            }
            choice = "";
        }
        return isInOrderDatabase;
    }

    // Method adds new parts to the "ordered" vector
    int Database::addToOrderDatabase(std::vector<Parts> &partDatabase, std::vector<Order> &orderDatabase, std::string partID, bool isInPartDatabase, bool isInOrderDatabase, int partIndex)
    {
        int i = 0, quantity = 0, available = 0;

        if (partID != "N" && isInPartDatabase && !isInOrderDatabase) {
            isInOrderDatabase = false;
            isInPartDatabase = false;
            std::cout << "Ile sztuk: ";
            std::cin >> quantity;
            available = partDatabase[partIndex].getQuantity();

            if (quantity > 0 && quantity <= available)
            {
                available = available - quantity;
                partDatabase[partIndex].updateQuantity(available);

                Order part(partID, quantity);
                part.randomCost(partDatabase, dbSize);
                orderDatabase.push_back(part);
                i = 1;
                std::cout << ">>> Dodano pozycję" << std::endl;
            }
            else
            {
                std::cout << "Dostępne jest tylko: " << available << " szt tego produktu." << std::endl;
                std::cout << "Ilość musi być liczbą naturalną" << std::endl;
                std::cout << "Wprowadź tą pozycję jeszcze raz" << std::endl;
            }
        }
        return i;
    }

    // Method saves "ordered" vector's objects to "orders.txt"
    void Database::saveOrder(std::vector<Order> &orderDatabase, std::vector<Parts> &partDatabase)
    {
        int  maxAvailability = 1, daysUntilDelivered = 0;
        double sumCost = 0.0;

        std::fstream file;
        file.open("orders.txt", std::ios::app);

        time_t t = time(0);
        tm* now = localtime(&t);

        std::string dateTime = std::to_string((now->tm_mday))  + "." + std::to_string((now->tm_mon +1)) + "." + std::to_string((now->tm_year + 1900)) + " " + std::to_string((now->tm_hour)) + ":" + std::to_string((now->tm_min));

        // Adding a line break to split orders because of appending new orders to the same textfile
        file << "________________________________________" << std::endl;
        file << "### Date: " << dateTime;
        file << "\nID of ordered parts  |  Calculated part cost  |  Quantity" << std::endl;

        // Pętla zapisująca ID oraz cenę zamówionych części do pliku tekstowego
        // Loop for outputting part ID, quantity and the price of the order to the textfile
        for (int i = 0; i < orderDatabase.size(); ++i) {
            file << orderDatabase[i].getId() << "  |  " << orderDatabase[i].getCost() << "  |  "  << orderDatabase[i].getQuantity() << std::endl;
            sumCost += orderDatabase[i].getCost();

            // Checking the value of the "availability" variable for each part to calculate the estimated order completion time. 
            if (orderDatabase[i].getAvailability() > maxAvailability)
            {
                maxAvailability = orderDatabase[i].getAvailability();
            }
        }

        //Variable calculates the number of days needed for delivery.

        daysUntilDelivered = ((60*60)*48*maxAvailability);

        time_t tDelivery = t + daysUntilDelivered + 2;

        // Loop checks whether the day of delivery is not a weekend day, in such case 2 more days are added to the estimation
        if ((now->tm_wday+1)+daysUntilDelivered < 6)
        {
            tDelivery = t + daysUntilDelivered;
        } else
        {
            tDelivery = t + daysUntilDelivered + 2;
        }

        tm* delivery = localtime(&tDelivery);
        std::string deliveryDate = std::to_string((delivery->tm_mday)) + "." + std::to_string((delivery->tm_mon +1)) + "." +  std::to_string((delivery->tm_year + 1900));

        // Order ending lines which add the summary cost of the order, and the calculated estimated date of order.
        file << "\n### CAŁKOWITY KOSZT:" << sumCost << " PLN" << std::endl;
        file << "### ZAMÓWIENIE POWINNO BYĆ KOMPLETNE W DNIU: " << deliveryDate << std::endl;
        file << "### KONIEC ZAMÓWIENIA ###" << std::endl;
        file << "________________________________________\n\n" << std::endl;

        file.close();
        std::cout << "\n>>> Plik został zapisany pomyślnie" << std::endl;
        orderDatabase.clear();

        std::fstream databaseUpdate;
        databaseUpdate.open("/home/adam/Documents/Learning/Programming/PPO 2 Sem Zaliczenie/databaseNew.txt", std::ios::out);

        for (int i = 0; i < 51; ++i)
        {
            databaseUpdate << partDatabase[i].databaseUpdate();
        }
        databaseUpdate.close();
    }

    // Method clears order
    void Database::clearOrder(std::vector<Order> &orderDatabase)
    {
        orderDatabase.clear();
        std::cout << "\n>>> Baza danych została wyczyszczona pomyślnie" << std::endl;
    }
