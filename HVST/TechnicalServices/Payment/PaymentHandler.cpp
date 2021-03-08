#include "TechnicalServices/Payment/PaymentHandler.hpp"
#include "TechnicalServices/Payment/VisaPayment.h"
#include "TechnicalServices/Payment/GenericPayment.h"
#include "TechnicalServices/Persistence/PersistenceHandler.hpp"

#include <algorithm>    // std::any_of()
#include <memory>       // unique_ptr, make_unique<>()
#include <stdexcept>    // logic_error
#include <string>
#include <any>
namespace TechnicalServices::Payment
{
    PaymentHandler::~PaymentHandler() noexcept = default;

  std::unique_ptr<PaymentHandler> PaymentHandler::createPayment()
    {
      auto & persistantData   = TechnicalServices::Persistence::PersistenceHandler::instance();
      auto   requestedPayment = persistantData["Component.Payment"];

      if( requestedPayment == "Visa" ) return std::make_unique<TechnicalServices::Payment::VisaPayment>();
      else if( requestedPayment == "Generic" )
        return std::make_unique<TechnicalServices::Payment::GenericPayment>();
    }
    
}
    