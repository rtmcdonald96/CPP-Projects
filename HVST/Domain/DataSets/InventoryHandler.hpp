#pragma once

#include <memory>
#include <iostream>
#include <string>
#include <stdexcept>

#include "TechnicalServices/Persistence/PersistenceHandler.hpp"

namespace Domain::DataSets
{
  // Library Package within the Domain Layer Abstract class
  class InventoryHandler
  {
    public:
    // Operations
      virtual std::vector<TechnicalServices::Persistence::itemLine> getInventory() = 0;                                                     //Returns a vector of item lines
      virtual std::vector<TechnicalServices::Persistence::itemLine>         updateInventory() = 0;                                          //Updates local inventory vector
      virtual void                                                          editQuantity( TechnicalServices::Persistence::itemLine ) = 0;   //Edits values in local inventory vector
    //static std::unique_ptr<InventoryHandler> createInventory();
    //InventoryHandler() = default;
    // Destructor
    // Pure virtual destructor helps force the class to be abstract, but must still be implemented
      virtual ~InventoryHandler() = 0;

  protected:
    // Copy assignment operators, protected to prevent mix derived-type assignments
    InventoryHandler & operator=( const InventoryHandler & rhs ) = default;    // copy assignment
    InventoryHandler & operator=( InventoryHandler && rhs ) = default;         // move assignment

  };    // class MaintainBooksHandler
  inline InventoryHandler::~InventoryHandler() {}
}    // namespace Domain::DataSets
