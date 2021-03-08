#pragma once

#include <algorithm>    // std::any_of()
#include <memory>       // unique_ptr, make_unique<>()
#include <stdexcept>    // logic_error
#include <string>
#include <any>
namespace TechnicalServices::Payment
{
    struct PaymentInfo
    {
      std::string ccNum;
      std::string ccExp;
      std::string ccSec;
      double      ccCharge; 
    };
    class PaymentHandler
    {
        public:
            // Exceptions
            PaymentHandler() = default;
            struct  PaymentException    : std::runtime_error    {using runtime_error       ::runtime_error;};
            struct  InvalidCard         : PaymentException      {using PaymentException::PaymentException;};

            static std::unique_ptr<PaymentHandler> createPayment();
            virtual std::string                    executePayment( std::string const & paymentType, const PaymentInfo & payment ) = 0;

            virtual ~PaymentHandler() noexcept = 0;


        protected:
          // Copy assignment operators, protected to prevent mix derived-type assignments
          PaymentHandler & operator=( const PaymentHandler & rhs ) = default;    // copy assignment
          PaymentHandler & operator=( PaymentHandler && rhs ) = default;         // move assignment
    };

}
