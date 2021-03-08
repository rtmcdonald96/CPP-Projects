#include "Domain/DataSets/CustomerInfoHandler.h"
#include <vector>
namespace Domain::DataSets
{
  
  class CustomerInfo : public CustomerInfoHandler
  {
  public:
    CustomerInfo();
    std::vector<Customer> getCustomers() override;      //Returns a vector of customer objects
    Customer addCustomer( Customer custIn ) override;   //Returns a customer object

    ~CustomerInfo();

  private:
    std::vector<Customer> currentCustomers;
  };
}    // namespace Domain::DataSets