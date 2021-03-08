#include <algorithm>    // std::any_of()
#include <iostream>
#include <memory>       // unique_ptr, make_unique<>()
#include <stdexcept>    // logic_error
#include <string>

#include "TechnicalServices/Payment/VisaPayment.h"
namespace TechnicalServices::Payment
{
  VisaPayment::VisaPayment( )
  {
  }
  VisaPayment::~VisaPayment() noexcept
  {
  }
  std::string VisaPayment::executePayment( const std::string & paymentType, const PaymentInfo & payment )
  {
    std::string result;
    result = "Visa Payment Approved\n";
    return result;
  }
}    // namespace TechnicalServices::Payment