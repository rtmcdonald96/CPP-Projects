#pragma once
#include <iostream>
#include <string>
#include <any>

#include "TechnicalServices/Payment/PaymentHandler.hpp"
#include "TechnicalServices/Payment/Payment.h"

namespace Domain::Sales
{
  class CreatePayment
  {
  public:
    //Operations
    CreatePayment( const std::string & paymentType, const TechnicalServices::Payment::PaymentInfo & payment );
    std::string executePayment( const std::string & paymentType, const TechnicalServices::Payment::PaymentInfo & payment );
    ~CreatePayment();

    TechnicalServices::Payment::PaymentInfo const _curPayment;
    std::string const                             _desc;
  private:
    std::string paymentVal;
  };
  //struct VisaPayment            : CreatePayment{ VisaPayment     ( const TechnicalServices::Payment::PaymentInfo & payment ); };
  //struct AmexPayment            : CreatePayment{ AmexPayment     ( const TechnicalServices::Payment::PaymentInfo & payment ); };
  //struct GenericPayment         : CreatePayment{ GenericPayment  ( const TechnicalServices::Payment::PaymentInfo & payment ); };
  
}    // namespace Domain::Sales