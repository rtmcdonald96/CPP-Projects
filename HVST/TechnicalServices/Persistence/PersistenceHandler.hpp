#pragma once

#include <map>
#include <stdexcept>    // domain_error, runtime_error
#include <string>
#include <vector>




namespace TechnicalServices::Persistence
{
  // Function argument type definitions
  struct UserCredentials
  {
    std::string               userName;
    std::string               passPhrase;
    std::vector<std::string>  roles;
  };
  struct itemLine
  {
    std::string itemName;
    std::string itemDescription;
    int         itemNumber;
    int         itemQuantity;
    double      itemCost;
  };
  struct Customer
  {
    std::string custName;
    std::string custAddress;
    std::string custPhone;
    std::string custZip;
    std::string custLevel;
  };



  // Persistence Package within the Technical Services Layer Abstract class
  // Singleton Class - only one instance of the DB exists for the entire system
  class PersistenceHandler
  {
    public:
      // Exceptions
      struct PersistenceException : std::runtime_error   {using runtime_error       ::runtime_error;};
      struct   NoSuchUser         : PersistenceException {using PersistenceException::PersistenceException;};
      struct   NoSuchProperty     : PersistenceException {using PersistenceException::PersistenceException;};

      // Creation (Singleton)
      PersistenceHandler            (                            ) = default;
      PersistenceHandler            ( const PersistenceHandler & ) = delete;
      PersistenceHandler & operator=( const PersistenceHandler & ) = delete;
      static  PersistenceHandler & instance();


      // Operations
      virtual std::vector<std::string> findRoles()                                       = 0;   // Returns list of all legal roles
      virtual UserCredentials          findCredentialsByName( const std::string & name ) = 0;   // Returns credentials for specified user, throws NoSuchUser if user not found
      virtual std::vector<itemLine>    findInventory()                                   = 0;    // Returns the inventory currently in the database
      virtual std::vector<Customer>    findCustomers()                                   = 0;

      // Adaptation Data read only access.  Adaptation data is a Key/Value pair
      // Throws NoSuchProperty
      virtual const std::string & operator[]( const std::string & key ) const = 0;


      // Destructor
      // Pure virtual destructor helps force the class to be abstract, but must still be implemented
      virtual ~PersistenceHandler() noexcept = 0;
  };
} // namespace TechnicalServices::Persistence
