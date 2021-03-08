#pragma once
#include <string>
#include <vector>

#include "TechnicalServices/Persistence/PersistenceHandler.hpp"
namespace Domain::Sales
{
  class PurchaseHandler
  {
  public:
    //Returns a vector of current customers from TS layer
    virtual std::string makePurchase( std::string iNum, std::string qty, double cost ) = 0;
    //Inserts customer into vector, returns the customer added if needed for output
    virtual std::string makeReciept( std::string pList )                        = 0;
    virtual std::string makePayment( std::string ccInfo, int ccExpire, int ccSecurity, double cost ) = 0;
    virtual ~PurchaseHandler() = 0;
  };
  inline PurchaseHandler::~PurchaseHandler() {}
}    // namespace Domain::DataSets