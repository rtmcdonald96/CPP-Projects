#pragma once

#include <string>
#include <vector>
using std::string;
using std::vector;

// This is already done for you...
class Item {
public:
    string name;
    int sellIn;
    int quality;
    Item(string, int, int);
};

Item::Item(string new_name, int new_sellIn, int new_quality)
: name(new_name), sellIn(new_sellIn), quality(new_quality) {
}



class GildedRose {
private:

	vector<Item> inventory; //vector of items to hold all my items
public:
//Constructor and destructor do not have anything in them as the vector is created when the item of class GildedRose is created
	GildedRose() {}  
	~GildedRose() {} 
//Returns the number of the elements in the vector inventory. Inventory starts with zero elements and increases everytime an Item is push_back via the add function
	size_t size() const {

		return inventory.size();
	
	}
//Returns the item of the specified location
	Item& get(size_t location) {

		return inventory[location];
	
	}
//Adds a new Item to the inventory vector and places it at the end of the vector
	void add(const Item& newItem) {

		inventory.push_back(newItem);
	
	}
//Returns the number of the elements in the vector inventory. Inventory starts with zero elements and increases everytime an Item is push_back via the add function
	Item& operator[](size_t location) {
	
		return inventory[location];
	
	
	
	}
};
