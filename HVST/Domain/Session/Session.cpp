#include "Domain/Session/Session.hpp"

#include <string>
#include <any>
#include <vector>

namespace  // anonymous (private) working area
{
  // 1)  First define all system events (commands, actions, requests, etc.)
  #define STUB(functionName)  std::any functionName( Domain::Session::SessionBase & /*session*/, const std::vector<std::string> & /*args*/ ) \
                              { return {}; }  // Stubbed for now

  STUB( help         )
  STUB( shutdown     )
  STUB( viewCustomers )


  std::any addCustomer(Domain::Session::SessionBase& session, const std::vector<std::string> & args) 
  {
    Customer    newCust = { args[0], args[1], args[2], args[3], args[4] };
    session._currentCustomers.getCustomers();
    session._currentCustomers.addCustomer( newCust );
    std::string results = "You Added: \nCustomer Name: " + args[0] + 
                          "\nCustomer Address: " + args[1] + 
                          "\nCustomer Phone Number: " + args[2] + 
                          "\nCustomer Zipcode: " + args[3] + 
                          "\nCustomer Level: " + args[4] + "\n";
    //session._logger << "Add Customer:  " + results;
    return results;
  }

  std::any makeAPurchase(Domain::Session::SessionBase& session, const std::vector<std::string> & args) 
  {
    
    //std::string results = "You Selected: \n Item Number: " + args[0] + "\nItem Quantity: " + args[1] + "\n";
    //                     "Paid with: CC Number: " + args[2] + " Expiration: " + args[3] + " Security Code: " + args[4] + "\n";
    long          ccExpire, ccSec;
    std::string ccInfo;
    std::string pItem;
    std::string   pQty;
    ccInfo   =  args[2];
    ccExpire = std::stoi( args[3] );
    ccSec    = std::stoi( args[4] );
    double                                                cost;
    Domain::DataSets::Inventory _currentInventory;
    std::vector<TechnicalServices::Persistence::itemLine> tempInv = _currentInventory.getInventory();
    std::cout << "Item Name | Item Description | Item Number | Item Cost | Item Quantity\n";
    for( auto it = tempInv.begin(); it != tempInv.end(); it++ )
    {
      TechnicalServices::Persistence::itemLine temp;
      temp = *it;
      std::cout << temp.itemName << " | " << temp.itemDescription << " | " << temp.itemNumber << " | " << temp.itemCost << " | " << temp.itemQuantity << "\n";
    }
    for( auto it = tempInv.begin(); it != tempInv.end(); it++ )
    {
      TechnicalServices::Persistence::itemLine temp;
      temp = *it;
      if( args[0] == std::to_string( temp.itemNumber ) )
      {
        pItem = temp.itemName;
        pQty  = args[1];
        cost =  temp.itemCost;
      }
    }
    Domain::Sales::Purchase                  _newPurchase;
    std::string      totals = _newPurchase.makePurchase( args[0], args[1], cost);
    std::cout << "You selected: " << pItem << " Qty: " << pQty; 
    std::cout << "\nTotal cost of purchase: " << totals; 
    std::cout << "\nEnter Credit Card Number: ";
    std::cout << ccInfo;
    //std::cin >> ccInfo;
    std::cout << "\nEnter Credit Card Number: ";
    std::cout << ccExpire;
    //std::cin >> ccExpire;
    std::cout << "\nEnter Credit Card Security Number: ";
    std::cout << ccSec;
    //std::cin >> ccSec;
    std::string paymentMade = _newPurchase.makePayment( ccInfo, ccExpire, ccSec, cost );
    std::cout << "\nPayment status: " << paymentMade;
    std::string recTotal = "Item Number: " + args[0] + "\nItem Quantity: " + args[1] + "\nTotal Cost: " + totals;
    std::string reciept = _newPurchase.makeReciept(recTotal) + "\n";
    std::cout << reciept;
    
    return reciept;
  }
  std::any editInventory( Domain::Session::SessionBase & session, const std::vector<std::string> & args )
  {
    int                                                   tempQuantity = 0;
    Domain::DataSets::Inventory                           _currentInventory;
    std::vector<TechnicalServices::Persistence::itemLine> tempInv = _currentInventory.getInventory();

    for( auto it = tempInv.begin(); it != tempInv.end(); it++ )
    {
      TechnicalServices::Persistence::itemLine temp;
      temp = *it;
      if( args[0] == std::to_string( temp.itemNumber ) )
      {
        tempQuantity      = std::stoi( args[1] );
        temp.itemQuantity = tempQuantity;
        _currentInventory.editQuantity( temp );
        break;
      }
    }

    tempInv             = _currentInventory.updateInventory();
    std::string results = "\nEdited Item Number: " + args[0] + "\nNew Item Quantity: " + args[1] + "\n";
    //std::cout << "Item Name | Item Description | Item Number | Item Cost | Item Quantity\n";
    /*for( auto it = tempInv.begin(); it != tempInv.end(); it++ )
    {
      TechnicalServices::Persistence::itemLine temp;
      temp = *it;
      std::cout << temp.itemName << " | " << temp.itemDescription << " | " << temp.itemNumber << " | " << temp.itemCost << " | " << temp.itemQuantity << "\n";
    }*/

    session._logger << "Edit Inventory:  " + results;
    return results;
  }
}    // anonymous (private) working area



/*std::any editInventory( Domain::Session::SessionBase & session, const std::vector<std::string> & args )
{
  std::string results = "You Selected: \nItem Number: " + args[0] + "\nNew Item Quantity: " + args[1] + "\n";

  session._logger << "Edit Inventory:  " + results;
  return results;
}*/






namespace Domain::Session
{
  SessionBase::SessionBase( const std::string & description, const UserCredentials & credentials ) : _credentials( credentials ), _name( description )
  {
    _logger << "Session \"" + _name + "\" being used and has been successfully initialized";

  }




  SessionBase::~SessionBase() noexcept
  {
    _logger << "Session \"" + _name + "\" shutdown successfully";
  }




  std::vector<std::string> SessionBase::getCommands()
  {
    std::vector<std::string> availableCommands;
    availableCommands.reserve( _commandDispatch.size() );

    for( const auto & [command, function] : _commandDispatch ) availableCommands.emplace_back( command );

    return availableCommands;
  }

  void SessionBase::getInventory() {
   
  }



  std::any SessionBase::executeCommand( const std::string & command, const std::vector<std::string> & args )
  {
    std::string parameters;
    for( const auto & arg : args )  parameters += '"' + arg + "\"  ";
    _logger << "Responding to \"" + command + "\" request with parameters: " + parameters;

    auto it = _commandDispatch.find( command );
    if( it == _commandDispatch.end() )
    {
      std::string message = __func__;
      message += " attempt to execute \"" + command + "\" failed, no such command";

      _logger << message;
      throw BadCommand( message );
    }

    auto results = it->second( *this, args);

    if( results.has_value() )
    {
      // The type of result depends on function called.  Let's assume strings for now ...
      //_logger << "Responding with: \"" + std::any_cast<const std::string &>( results ) + '"';
    }

    return results;
  }








  // 2) Now map the above system events to roles authorized to make such a request.  Many roles can request the same event, and many
  //    events can be requested by a single role.
  SystemAdminSession::SystemAdminSession( const UserCredentials & credentials ) : SessionBase( "System Admin", credentials )
  {
    _commandDispatch = { {"Help",            help        },
                         {"Shutdown System", shutdown    } };
  }




  CustomerSession::CustomerSession( const UserCredentials & credentials ) : SessionBase( "Customer", credentials )
  {
    _commandDispatch = { {"Make A Purchase", makeAPurchase  },
                                                            };
  }




  ManagerSession::ManagerSession( const UserCredentials & credentials ) : SessionBase( "Manager", credentials )
  {
    _commandDispatch = { { "Edit Inventory", editInventory } };
  }




  SalesRepSession::SalesRepSession( const UserCredentials & credentials ) : SessionBase( "Sales Rep", credentials )
  {
    _commandDispatch = { {"Add Customer",   addCustomer},
                         {"View Customers", viewCustomers},
                         {"Help",           help} };
  }
}    // namespace Domain::Session
