#pragma once
#include <iostream>
#include <string>
#include <vector>

#include "TechnicalServices/Persistence/PersistenceHandler.hpp"
struct Customer
{
  std::string custName;
  std::string custAddress;
  std::string custPhone;
  std::string custZip;
  std::string custLevel;
};
namespace Domain::DataSets
{
  class CustomerInfoHandler
  {
  public:
      //Returns a vector of current customers from TS layer
    virtual std::vector<Customer> getCustomers() = 0;
     //Inserts customer into vector, returns the customer added if needed for output
    virtual Customer addCustomer( Customer )  = 0;

    virtual ~CustomerInfoHandler() = 0;
  };
  inline CustomerInfoHandler::~CustomerInfoHandler() {}
}    // namespace Domain::DataSets