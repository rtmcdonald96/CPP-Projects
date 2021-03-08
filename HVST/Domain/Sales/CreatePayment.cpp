#include "Domain/Sales/CreatePayment.h"
#include "TechnicalServices/Payment/PaymentHandler.hpp"
#include "TechnicalServices/Payment/Payment.h"
#include <string>
#include <any>
#include <vector>

namespace Domain::Sales
{
  CreatePayment::CreatePayment( const std::string & paymentType, const TechnicalServices::Payment::PaymentInfo & payment ) : _desc( paymentType ), _curPayment(payment)
  {
    //_logger << "Session \"" + _name + "\" shutdown successfully";
  }




  CreatePayment::~CreatePayment() noexcept
  {
    //_logger << "Session \"" + _name + "\" shutdown successfully";
  }

  std::string CreatePayment::executePayment( const std::string & paymentType, const TechnicalServices::Payment::PaymentInfo & payment )
  {
    auto newPayment = TechnicalServices::Payment::PaymentHandler::createPayment();
    
    //TechnicalServices::Payment::PaymentHandler * testPay();
    //TechnicalServices::Payment::Payment newP( paymentType, payment );
    return newPayment->executePayment( paymentType, payment );
   
  }
  /*
  VisaPayment::VisaPayment(const TechnicalServices::Payment::PaymentInfo & payment) : CreatePayment("Visa Payment", payment) {
    TechnicalServices::Payment::Payment newP( _desc, _curPayment );
    this->executePayment( _desc, _curPayment );
    std::cout << " VISA PAYMENT CONSTRUCTION ";
  }
  AmexPayment::AmexPayment( const TechnicalServices::Payment::PaymentInfo & payment ) : CreatePayment( "Amex Payment", payment )
  {
    TechnicalServices::Payment::Payment newP( _desc, _curPayment );
    this->executePayment( _desc, _curPayment );
    std::cout << " AMEX PAYMENT CONSTRUCTION ";
  }
  */
}