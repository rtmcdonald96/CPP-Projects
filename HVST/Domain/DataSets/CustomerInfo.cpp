#include "Domain/DataSets/CustomerInfo.h"

namespace Domain::DataSets
{
	CustomerInfo::CustomerInfo()
	{
		
	}
	CustomerInfo::~CustomerInfo() {

	}
	std::vector<Customer> CustomerInfo::getCustomers() {

		TechnicalServices::Persistence::PersistenceHandler & data( TechnicalServices::Persistence::PersistenceHandler::instance() );
          std::vector<TechnicalServices::Persistence::Customer>             temp = data.findCustomers();
                Customer                                              tempCust;
		  for (auto it = temp.begin(); it != temp.end(); it++) {
                    tempCust.custName = it->custName;
                    tempCust.custAddress = it->custAddress;
                    tempCust.custPhone   = it->custPhone;
                    tempCust.custZip     = it->custZip;
                    currentCustomers.push_back( tempCust );
				}
		return currentCustomers;
	}
	Customer CustomerInfo::addCustomer( Customer custIn) {
          currentCustomers.push_back( custIn );
          std::cout << "Customer Added!\n";
          return currentCustomers.back();
	}
}