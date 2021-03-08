#pragma once
#include <string>
#include <vector>
#include <memory>
#include "Domain/DataSets/Inventory.hpp"
#include "Domain/DataSets/InventoryHandler.hpp"
#include "TechnicalServices/Logging/LoggerHandler.hpp"
#include "TechnicalServices/Persistence/PersistenceHandler.hpp"

#include "UI/UserInterfaceHandler.hpp"

namespace Domain::DataSets
{
  
  class Inventory : public InventoryHandler
  {
    public:
        // Constructors
        //using InventoryHandler::InventoryHandler;
        Inventory();

        std::vector<TechnicalServices::Persistence::itemLine> getInventory();
        std::vector<TechnicalServices::Persistence::itemLine> updateInventory();
        void                                                  editQuantity( TechnicalServices::Persistence::itemLine );
        ~Inventory();

    private:
        std::vector<TechnicalServices::Persistence::itemLine> itemList;
  }; // class Inventory

}    // namespace Domain::DataSets
