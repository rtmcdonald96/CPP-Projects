#pragma once
#include <queue>

#include "ClaimCheck.hpp"
#include "Automobile.hpp"



struct ParkedCar {
public:
  Automobile  vehicle_;
  size_t      claimNumber_;


  ParkedCar(const Automobile& vehicle, const size_t claimNumber)
	  : vehicle_(vehicle), claimNumber_(claimNumber)

  {}
};



class ParkingLot {
  private:
    std::queue<ParkedCar> parkedCars_; // aisles closed on one end

  public:
    ClaimCheck dropOff( const Automobile& vehicle );
    Automobile pickUp ( const ClaimCheck& ticket  );

    size_t quantity();
  };
