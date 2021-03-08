#include <iostream>
#include <string>

#include "Automobile.hpp"



/*******************************************************************************
** Member function definitions
*******************************************************************************/
Automobile::Automobile( const std::string & color,
                        const std::string & brand,
                        const std::string & model,
                        const std::string & plateNumber )
  : color_(color), brand_(brand), model_(model), plateNumber_(plateNumber)
{}






/*******************************************************************************
** Non-member function definitions
*******************************************************************************/
bool operator==( const Automobile& lhs, const Automobile& rhs ) {
	if ( (lhs.color_.compare(rhs.color_) == 0) && (lhs.brand_.compare(rhs.brand_) == 0) && (lhs.model_.compare(rhs.model_) == 0) && (lhs.plateNumber_.compare(rhs.plateNumber_) == 0) ) {
		return true; 
	}
	else {
		return false;
	}
}



bool operator!=( const Automobile& lhs, const Automobile& rhs )
{ return !( lhs == rhs ); }



std::ostream & operator<<( std::ostream& stream, const Automobile& vehicle )
{

	stream << vehicle.color_ << vehicle.brand_ << vehicle.model_ << vehicle.plateNumber_; 
	return stream;

}
