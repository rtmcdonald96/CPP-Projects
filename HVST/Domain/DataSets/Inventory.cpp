#pragma once
#include <iostream>
#include "Domain/DataSets/Inventory.hpp"

#include "TechnicalServices/Persistence/PersistenceHandler.hpp"

namespace Domain::DataSets
{
  Inventory::Inventory() 
  {
    
    itemList = this->getInventory();
      for( auto it = itemList.begin(); it != itemList.end(); it++ )
        {
          TechnicalServices::Persistence::itemLine temp;
          temp = *it;
          //std::cout << temp.itemName << " " << temp.itemDescription << " " << temp.itemNumber << " " << temp.itemCost << " " << temp.itemQuantity << "\n";
        }
  }
  std::vector<TechnicalServices::Persistence::itemLine> Inventory::updateInventory()
  {
    return itemList;
  }

  std::vector<TechnicalServices::Persistence::itemLine> Inventory::getInventory()
  {
    TechnicalServices::Persistence::PersistenceHandler & data( TechnicalServices::Persistence::PersistenceHandler::instance() );
    itemList = data.findInventory();
    return itemList;
  }
  void Inventory::editQuantity( TechnicalServices::Persistence::itemLine temp )
  {
    int count = 0;
    itemList  = this->getInventory();
    for( auto it = itemList.begin(); it != itemList.end(); it++ )
    {
      TechnicalServices::Persistence::itemLine t;
      t = *it;
      if( t.itemNumber == temp.itemNumber )
      {
        itemList[count].itemQuantity = temp.itemQuantity;
        break;
      }
      count++;
    }
  }
    Inventory::~Inventory() {}
}    // namespace Domain::Datasets
