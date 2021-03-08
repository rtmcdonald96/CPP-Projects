// This file tests your class and makes sure you created the GildedRose correctly
#include <iostream>
#include <string>
#include "GildedRose.h"
using std::cout;
using std::endl;
using std::string;

const size_t NUM_TESTS = 9;
size_t NUM_PASSED = 0;

// Helper Functions
template <typename T>
void assertEquals(string, T, T);

// Main Testing
int main(int argc, char const *argv[]) {
    GildedRose store;
    store.add(Item("+5 Dexterity Vest", 10, 20));
    store.add(Item("Aged Brie", 2, 0));
    store.add(Item("Elixir of the Mongoose", 5, 7));
    store.add(Item("Sulfuras, Hand of Ragnaros", 0, 80));

    assertEquals("GildedRose.size()", static_cast<size_t>(4), store.size());
    assertEquals("GildedRose[0].sellIn", 10, store[0].sellIn);
    assertEquals("GildedRose.get(3).quality", 80, store.get(3).quality);

    store.add(Item("Backstage passes to a TAFKAL80ETC concert", 15, 20));
    store.add(Item("Backstage passes to a TAFKAL80ETC concert", 10, 49));
    store.add(Item("Backstage passes to a TAFKAL80ETC concert", 5, 49));

    assertEquals("GildedRose.size()", static_cast<size_t>(7), store.size());
    assertEquals("GildedRose[6].quality", 49, store[6].quality);
    assertEquals("GildedRose.get(4).sellIn", 15, store.get(4).sellIn);

    store.add(Item("Conjured Mana Cake", 3, 6));

    assertEquals("GildedRose.size()", static_cast<size_t>(8), store.size());
    assertEquals("GildedRose[8].name", static_cast<string>("Conjured Mana Cake"), store[7].name);
    assertEquals("GildedRose.get(8).name", static_cast<string>("Conjured Mana Cake"), store.get(7).name);

    cout << endl << "Tests passed: " << NUM_PASSED << "/" << NUM_TESTS << endl;

    return 0;
}

template <typename T>
void assertEquals(string test_name, T expected, T actual) {
    if (actual == expected) {
        cout << "[PASSED] " << test_name << endl;
        NUM_PASSED++;
    } else {
        cout << "[FAILED] " << test_name
             << " - Expected: " << expected
             << ", Actual: " << actual
             << endl;
    }
}
