#include <algorithm>    // std::any_of()
#include <iostream>
#include <memory>       // unique_ptr, make_unique<>()
#include <stdexcept>    // logic_error
#include <string>

#include "TechnicalServices/Payment/GenericPayment.h"
namespace TechnicalServices::Payment
{
  GenericPayment::GenericPayment()
  {
  }
  GenericPayment::~GenericPayment() noexcept
  {
  }
  std::string GenericPayment::executePayment( const std::string & paymentType, const PaymentInfo & payment )
  {
    std::string result;
    result = "Generic Payment Approved\n";
    return result;
  }
}    // namespace TechnicalServices::Payment