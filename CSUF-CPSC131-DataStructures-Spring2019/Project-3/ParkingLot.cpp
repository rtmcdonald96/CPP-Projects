#include <queue>
#include <stdexcept>
#include <string>


#include "ClaimCheck.hpp"
#include "ParkingLot.hpp"


/*******************************************************************************
** ParkingLot Member function definitions
*******************************************************************************/
ClaimCheck ParkingLot::dropOff( const Automobile& vehicle) {

	ClaimCheck ticket(vehicle);

	ParkedCar tempCar(ticket.vehicle(), ticket.claimNumber());

	parkedCars_.push(tempCar);


  return ticket;
  
}




Automobile ParkingLot::pickUp( const ClaimCheck& ticket ) {
	int numOfAttempts = 0;
	while (parkedCars_.front().claimNumber_ != ticket.claimNumber())
	{
		
		parkedCars_.push(parkedCars_.front());
		parkedCars_.pop();
		if (numOfAttempts == quantity()) {
			throw std::invalid_argument (" Car was not found in parking lot ");
		}
		numOfAttempts ++ ;
	}
	Automobile tempCar = ticket.vehicle();
	parkedCars_.pop();
	return tempCar;

}




size_t ParkingLot::quantity()
{
	return parkedCars_.size();

}

