//****************************************************************************************
//
//	INCLUDE FILES
//
//****************************************************************************************
#include	<iostream>
#include 	<string>
#include	"GateControl.hpp"

using namespace std;

//****************************************************************************************
//
//	CONSTANT DEFINITIONS
//
//****************************************************************************************

//****************************************************************************************
//
//	CLASSES, TYPEDEFS AND STRUCTURES
//
//****************************************************************************************

//****************************************************************************************
//
//	PUBLIC DATA
//
//****************************************************************************************
extern	string	gCurrentDate;

extern	string	gCurrentTime;

//****************************************************************************************
//
//	PRIVATE DATA
//
//****************************************************************************************

//****************************************************************************************
//
//	FUNCTION PROTOTYPES
//
//****************************************************************************************

//****************************************************************************************
//
//	GateControl::AccessAllowed
//
//****************************************************************************************
bool	GateControl::AccessAllowed(CardNumber number)
{

	//************************************************************************************
	//
	//	LOCAL DATA
	//
	//************************************************************************************
	Transaction myTrans; //Creates Transaction to be pushed onto transactionVector_
	Authorization myAuth; //Creates Authorization to pull information from authorizationMap_
	
	//************************************************************************************
	//
	//	EXECUTABLE STATEMENTS
	//
	//************************************************************************************
		
	myTrans.date_ = gCurrentDate; //Sets transaction date to match current date 
	myTrans.time_ = gCurrentTime; //Sets transaction time to match current time 
	
	//Runs check to see if the number given is in the map, if it is not in the map replaces name with "***"
	//Sets accessAllowed_ to false because it has not been given authorization
	AuthorizationIterator it = authorizationMap_.find(number);
	if (it == authorizationMap_.end()){
	myTrans.number_= number;
	myTrans.name_ = "***";
	myTrans.accessAllowed_ = false;
	transactionVector_.push_back(myTrans);
	return false;	
	}
	//If the number is in the map sets transaction name and number to match name and number from map
	myAuth = authorizationMap_[number];
	myTrans.name_ = myAuth.name_;
	myTrans.number_ = number;
	//If time is outside of start or end time access is not allowed so set to false
		if (myAuth.startTime_ > gCurrentTime || myAuth.endTime_ < gCurrentTime) {
			myTrans.accessAllowed_ = false;
			transactionVector_.push_back(myTrans);
			return false;
		}
		else { //If time is inside of start and end time access is allowed so set to true
			myTrans.accessAllowed_ = true;
			transactionVector_.push_back(myTrans);
			return true;
		}
	}

//****************************************************************************************
//
//	GateControl::AddAuthorization
//
//****************************************************************************************
bool	GateControl::AddAuthorization(CardNumber number, const string& name,
									  const string& startTime, const string& endTime)
{

	//************************************************************************************
	//
	//	LOCAL DATA
	//
	//************************************************************************************
	
	AuthorizationIterator authMapIt;
	
	//************************************************************************************
	//
	//	EXECUTABLE STATEMENTS
	//
	//************************************************************************************
	
	//Sets iterator equal to the location of number in the authorizationMap
	authMapIt = authorizationMap_.find(number);
	
	//If iterator equals authorizationMap_.end() the number was not found in the authorization map
	//so it is added to the authorization map
	if (authMapIt == authorizationMap_.end()) {
		Authorization tempAuth(number, name, startTime, endTime);
		authorizationMap_[number] = tempAuth;
		return true;
	}
	else //If the iterator is not equal to the end, the number is somewhere in the authorization map already
		//so return false
	{
		return false;
	}

	

}

//****************************************************************************************
//
//	GateControl::ChangeAuthorization
//
//****************************************************************************************
bool	GateControl::ChangeAuthorization(CardNumber number, const string& name,
										 const string& startTime, const string& endTime)
{

	//************************************************************************************
	//
	//	LOCAL DATA
	//
	//************************************************************************************
	
		AuthorizationIterator it = authorizationMap_.find(number);
		
	//************************************************************************************
	//
	//	EXECUTABLE STATEMENTS
	//
	//************************************************************************************
	
	//if the iterator is at the end of the map the number was not found so return false
	if (it == authorizationMap_.end()) { return false; }
	else { //if the iterator was found, replace authorization in the map with the
		   // replacementAuth which is constructed with the information given
		Authorization replacementAuth(number, name, startTime, endTime);
		it->second = replacementAuth;
	}
	return true;
}

//****************************************************************************************
//
//	GateControl::DeleteAuthorization
//
//****************************************************************************************
bool	GateControl::DeleteAuthorization(CardNumber number)
{

	//************************************************************************************
	//
	//	LOCAL DATA
	//
	//************************************************************************************
	AuthorizationIterator it = authorizationMap_.find(number);

	//************************************************************************************
	//
	//	EXECUTABLE STATEMENTS
	//
	//************************************************************************************
	
	// If the iterator is at the end that means the number was not found and there is nothing
	// to delete so return false
	if (it == authorizationMap_.end())
	{
		return false;
	}
	//If the iterator is not at the end we erase the entry from the authorizationMap_ and 
	//return true.
	else {
		authorizationMap_.erase(it);
		return true;
	}
}

//****************************************************************************************
//
//	GateControl::GetAllAuthorizations
//
//****************************************************************************************
void	GateControl::GetAllAuthorizations(AuthorizationVector& authorizationVector)
{

	//************************************************************************************
	//
	//	LOCAL DATA
	//
	//************************************************************************************
	
	
	//************************************************************************************
	//
	//	EXECUTABLE STATEMENTS
	//
	//************************************************************************************
	
	//Clear authorization vector so no duplicate entries are added from previous calls of
	//GetAllAuthorizations
	authorizationVector.clear();
	
	//Iterate through authorizationMap_ and pushback all entries to authorizationVector
	for (AuthorizationIterator iterator = authorizationMap_.begin(); iterator != authorizationMap_.end(); ++iterator)
	{
		authorizationVector.push_back(iterator->second);
	}
	return;
}

//****************************************************************************************
//
//	GateControl::GetAllTransactions
//
//****************************************************************************************
void	GateControl::GetAllTransactions(TransactionVector& transactionVector)
{

	//************************************************************************************
	//
	//	LOCAL DATA
	//
	//************************************************************************************
	

	//************************************************************************************
	//
	//	EXECUTABLE STATEMENTS
	//
	//************************************************************************************
	
	//Clear transaction vector so no duplicates remain from previous calls of GetAllTransactions
	//Also remains clear if there are no transactions to be found
	transactionVector.clear();
	
	//For loop through transactionVector_ to pushback entries onto transactionVector
	for (int i = 0; i < transactionVector_.size(); i++)
	{
		transactionVector.push_back(transactionVector_[i]);
	}
	return;
}

//****************************************************************************************
//
//	GateControl::GetCardAuthorization
//
//****************************************************************************************
bool	GateControl::GetCardAuthorization(CardNumber number, Authorization& authorization)
{

	//************************************************************************************
	//
	//	LOCAL DATA
	//
	//************************************************************************************
	AuthorizationIterator authMapIt = authorizationMap_.find(number);
	
	//************************************************************************************
	//
	//	EXECUTABLE STATEMENTS
	//
	//************************************************************************************
	
	//If the iterator is at the end the authorization it means the cardnumber was not found
	//so return false
	if (authMapIt == authorizationMap_.end()) { 
		return false;
	}
	//If the card was found set all of the information from the map to the authorization
	//output argument from the function
	else {
		Authorization tempAuth;
		tempAuth = authorizationMap_[number];
		authorization.name_ = tempAuth.name_;
		authorization.number_ = tempAuth.number_;
		authorization.endTime_ = tempAuth.endTime_;
		authorization.startTime_ = tempAuth.startTime_;
		return true;
	}

}

//****************************************************************************************
//
//	GateControl::GetCardTransactions
//
//****************************************************************************************
bool	GateControl::GetCardTransactions(CardNumber number,
										 TransactionVector& transactionVector)
{

	//************************************************************************************
	//
	//	LOCAL DATA
	//
	//************************************************************************************

	//************************************************************************************
	//
	//	EXECUTABLE STATEMENTS
	//
	//************************************************************************************
	
	//Clears transaction vector from previous calls of GetCardTransactions
	//Remains clear if no transactions are provided for this card
	transactionVector.clear();
	
	//For loop through transactionVector to find any transactions where the number given
	//matches the number in the transaction vector. Push back any matching entries. 
	for (int i = 0; i < transactionVector_.size(); i++)
	{
		if (number == transactionVector_[i].number_) {
			transactionVector.push_back(transactionVector_[i]);
		}
		
	}
	//If the transactionVector is empty return false as no entries were found.
	if (transactionVector.empty() == true)
	{
		return false;
	}
	//Returns true if entries are present in the transactionVector
	return true;
}
