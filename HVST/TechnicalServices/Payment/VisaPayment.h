#pragma once

#include <algorithm>    // std::any_of()
#include <any>
#include <memory>       // unique_ptr, make_unique<>()
#include <stdexcept>    // logic_error
#include <string>

#include "TechnicalServices/Payment/PaymentHandler.hpp"

namespace TechnicalServices::Payment
{
  class VisaPayment : public TechnicalServices::Payment::PaymentHandler
  {
  public:
    using PaymentHandler::PaymentHandler;
    VisaPayment( );

    std::string executePayment( std::string const & paymentType, const PaymentInfo & payment ) override;

    ~VisaPayment() noexcept override;
  };

}    // namespace TechnicalServices::Payment