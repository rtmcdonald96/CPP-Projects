#include "UI/SimpleUI.hpp"

#include <any>         // any_cast()
#include <iomanip>     // setw()
#include <iostream>    // streamsize
#include <limits>      // numeric_limits
#include <memory>      // unique_ptr, make_unique<>()
#include <string>      // string, getline()
#include <vector>


#include "Domain/Session/SessionHandler.hpp"

#include "TechnicalServices/Logging/LoggerHandler.hpp"
#include "TechnicalServices/Persistence/PersistenceHandler.hpp"



namespace UI
{
  // Default constructor
  SimpleUI::SimpleUI()
  : _loggerPtr     ( TechnicalServices::Logging::LoggerHandler::create()            ),
    _persistentData( TechnicalServices::Persistence::PersistenceHandler::instance() )
  {
    _inventory = testINV.getInventory();
    //_inventory = _persistentData.findInventory();
    _logger << "Simple UI being used and has been successfully initialized";
  }




  // Destructor
  SimpleUI::~SimpleUI() noexcept
  {
    _logger << "Simple UI shutdown successfully";
  }




  // Operations
  void SimpleUI::launch()
  {
    // 1) Fetch Role legal value list
    std::vector<std::string> roleLegalValues = _persistentData.findRoles();
    


    // 2) Present login screen to user and get username, password, and valid role
    Domain::Session::UserCredentials credentials  = {"", "", {""}};           // ensures roles[0] exists
    auto &                           selectedRole = credentials.roles[0];     // convenience alias

    std::unique_ptr<Domain::Session::SessionHandler> sessionControl;

    do
    {
      std::cin.ignore(  std::numeric_limits<std::streamsize>::max(), '\n' );

      std::cout << "  name: ";
      std::getline( std::cin, credentials.userName );

      std::cout << "  pass phrase: ";
      std::getline( std::cin, credentials.passPhrase );

      unsigned menuSelection;
      do
      {
        for( unsigned i = 0; i != roleLegalValues.size(); ++i )   std::cout << std::setw( 2 ) << i << " - " << roleLegalValues[i] << '\n';
        std::cout << "  role (0-" << roleLegalValues.size()-1 << "): ";
        std::cin  >> menuSelection;
      } while( menuSelection >= roleLegalValues.size() );

      selectedRole = roleLegalValues[menuSelection];


      // 3) Validate user is authorized for this role, and if so create session
      sessionControl = Domain::Session::SessionHandler::createSession( credentials );
      if( sessionControl != nullptr )
      {
        _logger << "Login Successful for \"" + credentials.userName + "\" as role \"" + selectedRole + "\"";
        break;
      }

      std::cout << "** Login failed\n";
      _logger << "Login failure for \"" + credentials.userName + "\" as role \"" + selectedRole + "\"";

    } while( true );


    // 4) Fetch functionality options for this role
    do
    {
      auto        commands = sessionControl->getCommands();
      std::string selectedCommand;
      unsigned    menuSelection;

      do
      {
        for( unsigned i = 0; i != commands.size(); ++i ) std::cout << std::setw( 2 ) << i << " - " << commands[i] << '\n';
        std::cout << std::setw( 2 ) << commands.size() << " - " << "Quit\n";

        std::cout << "  action (0-" << commands.size() << "): ";
        std::cin >> menuSelection;
      } while( menuSelection > commands.size() );

      if( menuSelection == commands.size() ) break;

      selectedCommand = commands[menuSelection];
      _logger << "Command selected \"" + selectedCommand + '"';


      /******************************************************************************************************************************
      **  5) The user interface will collect relevant information to execute the chosen command.  This section requires the UI to
      **     know what information to collect, and hence what the available commands are.  Our goal is loose (minimal) coupling, not
      **     no coupling. This can be achieved in a variety of ways, but one common way is to pass strings instead of strong typed
      **     parameters.
      ******************************************************************************************************************************/

      if( selectedCommand == "Add Customer" ) /* Prompts the user for the information required to enter a customer into the technical services database, returns success prompt on valid entry */ {
      std::vector<std::string> parameters( 5 );

        std::cout << " Customer Name: ";  std::cin >> std::ws;  std::getline( std::cin, parameters[0] );
        std::cout << " Customer Address: ";  std::cin >> std::ws;  std::getline( std::cin, parameters[1] );
        std::cout << " Customer Phone Number:   ";  std::cin >> std::ws;  std::getline( std::cin, parameters[2] );
        std::cout << " Customer Zipcode:   ";  std::cin >> std::ws;  std::getline( std::cin, parameters[3] );
        std::cout << " Customer Level:   ";  std::cin >> std::ws;  std::getline( std::cin, parameters[4] );
        auto results = sessionControl->executeCommand( selectedCommand, parameters );
        if( results.has_value() ) _logger << "Received reply: \"" + std::any_cast<const std::string &>( results ) + '"';
      }

      else if( selectedCommand == "Make A Purchase" ) /* Prompts the user for an item number, quantity, and credit card information, returns a reciept of purchase with tax included and a successful payment prompt */ {
      std::vector<std::string> parameters( 7 );
        std::cout << "Item Name | Item Description | Item Number | Item Cost | Item Quantity\n";
        for( auto it = _inventory.begin(); it != _inventory.end(); it++ )
        {
          TechnicalServices::Persistence::itemLine temp;
          temp = *it;
          std::cout << temp.itemName << " | " << temp.itemDescription << " | " << temp.itemNumber << " | " << temp.itemCost << " | " << temp.itemQuantity << "\n";
        }
        std::cout << "Select an item by item number: "; std::cin >> std::ws;  std::getline( std::cin, parameters[0] );
        std::cout << "Quantity requested: "; std::cin >> std::ws;  std::getline( std::cin, parameters[1] );
        std::cout << "Enter Credit Card Num: "; std::cin >> std::ws;  std::getline( std::cin, parameters[2] );
        std::cout << "Expiration date: "; std::cin >> std::ws;  std::getline( std::cin, parameters[3] );
        std::cout << "Security code: "; std::cin >> std::ws;  std::getline( std::cin, parameters[4] );

        
        auto results = sessionControl->executeCommand( selectedCommand, parameters );
        if( results.has_value() ) _logger << "Received reply: \"" + std::any_cast<const std::string &>( results ) + '"';
        
      }

      else if( selectedCommand == "Edit Inventory" ) /*Prompts the user for an item number and new quantity, returns the item number and quantity that was adjusted */ {
        std::vector<std::string> parameters( 2 );

            std::cout << "Select an item by item number: "; std::cin >> std::ws;  std::getline( std::cin, parameters[0] );
            std::cout << "Quantity Changed To: "; std::cin >> std::ws;  std::getline( std::cin, parameters[1] );
          auto results = sessionControl->executeCommand( selectedCommand, parameters );
          if( results.has_value() ) _logger << "Received reply: \"" + std::any_cast<const std::string &>( results ) + '"';
        }
      else sessionControl->executeCommand( selectedCommand, {} );
    } while( true );

    _logger << "Ending session and terminating";
  }
}    // namespace UI