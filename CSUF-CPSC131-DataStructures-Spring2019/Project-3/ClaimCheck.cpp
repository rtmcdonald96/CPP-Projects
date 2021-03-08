#include <iostream>

#include "Automobile.hpp"
#include "ClaimCheck.hpp"



/*******************************************************************************
** Class attributes
*******************************************************************************/
size_t ClaimCheck::nextAvailableClaimNumber = 100;


/*******************************************************************************
** Member function definitions
*******************************************************************************/
ClaimCheck::ClaimCheck(const Automobile & vehicle)
	: vehicle_(vehicle), claimNumber_(nextAvailableClaimNumber) 


{
	nextAvailableClaimNumber++;
}


Automobile ClaimCheck::vehicle() const
{ return vehicle_; }



size_t ClaimCheck::claimNumber() const
{ return claimNumber_;  }



/*******************************************************************************
** Non-member function definitions
*******************************************************************************/
bool operator==( const ClaimCheck & lhs, const ClaimCheck & rhs )
{ 
	return (lhs.claimNumber_ == rhs.claimNumber_);
}

bool operator!=( const ClaimCheck & lhs, const ClaimCheck & rhs )
{ return ! (lhs == rhs); }



std::ostream & operator<<( std::ostream & stream, const ClaimCheck & ticket )
{

	stream << ticket.claimNumber_ << ticket.vehicle_;
	return stream;
}
