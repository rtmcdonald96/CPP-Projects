#pragma once
#include <string>
#include <iostream>

#include "Domain/Sales/PurchaseHandler.h"
#include "Domain/Sales/CreatePayment.h"
#include "TechnicalServices/Payment/Payment.h"
#include "TechnicalServices/Payment/PaymentHandler.hpp"

namespace Domain::Sales
{
  class Purchase : public PurchaseHandler
  {
  public:
    //Operations
    Purchase();
    std::string makePurchase( std::string iNum, std::string qty, double cost ) override;                          // get item#, validate exists, show current cost, get cc info, call makePayment, do makeReciept
    std::string makeReciept(std::string pList) override;                                              // return item purchased + itemcost * qty * tax (tax = 5% default)
    std::string makePayment( std::string ccInfo, int ccExpire, int ccSecurity, double cost ) override;    // takes CC info and exports to external system

    ~Purchase();

  private:
    std::string buyer;
  };
}    // namespace Domain::Sales