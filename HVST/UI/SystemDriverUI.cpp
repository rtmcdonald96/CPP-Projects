#include "UI/SystemDriverUI.hpp"

#include "Domain/Session/SessionHandler.hpp"

#include "TechnicalServices/Logging/LoggerHandler.hpp"




namespace UI
{
  // Default constructor
  SystemDriverUI::SystemDriverUI()
  : _loggerPtr( TechnicalServices::Logging::LoggerHandler::create() )
  {
    _logger << "Contracted UI being used and has been successfully initialized";
  }




  // Destructor
  SystemDriverUI::~SystemDriverUI() noexcept
  {
    _logger << "Contracted UI shutdown successfully";
  }




  // Operations
  void SystemDriverUI::launch()
  {
    {
      int userChoice;
      std::cout << "Which scenario would you like to run? (1, 2, or 3) 4 to Quit\n";
      std::cin >> userChoice;
      while( userChoice != 4 )
      {
        if( userChoice == 1 )
        {
          _logger << "Starting scenario 1: Make A Purchase";

          auto session  = Domain::Session::SessionHandler::createSession( { "Ryan", "123", { "Customer" } } );
          auto commands = session->getCommands();

          auto results = session->executeCommand( "Make A Purchase", { "1234567893", "1", "4444123456789082", "1024", "123" } );
          //session->singOff();

          _logger << "Completed scenario 1";
        }
        if( userChoice == 2 )
        {
          _logger << "Starting scenario 2: Add Customer";

          auto session  = Domain::Session::SessionHandler::createSession( { "Alex", "123", { "Sales Rep" } } );
          auto commands = session->getCommands();
          auto results  = session->executeCommand( "Add Customer", { "Tony", "1 North Way", "123-4567", "96587", "1" } );
          //session->singOff();
          
          _logger << "Completed scenario 2";
        }
        
        if( userChoice == 3 )
        {
          _logger << "Starting scenario 3: Edit Inventory";

          auto session  = Domain::Session::SessionHandler::createSession( { "Benny", "123", { "Manager" } } );
          auto commands = session->getCommands();
          auto results  = session->executeCommand( "Edit Inventory", { "1234567891", "50" } );
          //session->singOff();
        }
        std::cout << "Which scenario would you like to run? (1, 2, or 3) 4 to Quit\n";
        std::cin >> userChoice;
      }
    }
  }
}    // namespace UI
