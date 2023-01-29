#include "iostream"
#include "string"
#include "vector"
#include "Classes/Parts.h"
#include "Classes/Order.h"
#include "Classes/Database.h"

std::string userInput = "";

void menu()
{
    std::cout << "\n\nWitaj w programie!" << std::endl;
    std::cout << ">>> MENU <<<" << std::endl;
    std::cout << "1 Wypisz listę dostępnych części" << std::endl;
    std::cout << "2 Stwórz zamówienie" << std::endl;
    std::cout << "3 Zapisz i podsumuj zamówienie" << std::endl;
    std::cout << "4 Wyczyść zamówienie" << std::endl;
    std::cout << "5 Zaktualizuj bazę danych" << std::endl;
    std::cout << "\n9 Zamknij program" << std::endl;
    std::cout << "-----------------------------------" << std::endl;
    std::cout << "Wybierz co chcesz zrobić: ";
    std::cin >> userInput;
}

int main()
{
    std::vector<Parts> partDatabase;
    std::vector<Order> orderDatabase;
    Database partDatabase0;
    partDatabase0.databaseSizeCheck();
    partDatabase0.dataRead(partDatabase);

    while(true)
    {
        menu();

        if (userInput == "1")
        {
            partDatabase0.listParts(partDatabase);
        }
        else if (userInput == "2")
        {
            partDatabase0.makeOrder(partDatabase, orderDatabase);
        }
        else if (userInput == "3")
        {
            if (orderDatabase.size() == 0)
            {
                std::cout << "Zamówienie jest puste\nProszę wprowadzić zamówienie" << std::endl;
            } else
            {
                partDatabase0.saveOrder(orderDatabase, partDatabase);
            }
        }
        else if (userInput == "4")
        {
            partDatabase0.clearOrder(orderDatabase);
        }
        else if (userInput == "5")
        {
            partDatabase0.partDatabaseCreate();
        }
        else if (userInput == "9")
        {
            exit(0);
        } else
        {
            std::cout << "\n>>> BŁĄD. Wybierz jedną opcji dostępnych w menu" << std::endl;
        }
    }
    return 0;
}
