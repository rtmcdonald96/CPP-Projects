#include <iostream>
#include <string>

#include "Song.hpp"
#include "RadList.hpp"

using std::string;
using std::cout;
using std::endl;

// Helper Functions
template <typename T>
void assertEquals(string, T, T);

int main(int argc, char const *argv[]) {
    RadList jukebox;
    jukebox.loadPlaylist("Downtempo.csv");
    assertEquals("RadList.name()", static_cast<string>("All In Forms"), jukebox.nowPlaying().name());
    jukebox.next();
    assertEquals("RadList.artist()", static_cast<string>("Bonobo"), jukebox.nowPlaying().artist());
    jukebox.prev();
    assertEquals("RadList.minutes()", static_cast<unsigned int>(4), jukebox.nowPlaying().minutes());
    assertEquals("RadList.seconds()", static_cast<unsigned int>(51), jukebox.nowPlaying().seconds());
    jukebox.next();
    jukebox.addToQueue(Song("Black Canyon", "Ana Caravelle", "Basic Climb", 457, false));
    jukebox.next();
    jukebox.playNext(Song("Tumbleweed", "9 Lazy 9", "Sweet Jones", 192, false));
    assertEquals("RadList.name()/album()", jukebox.nowPlaying().name(), jukebox.nowPlaying().album());
    jukebox.addToQueue(Song("Building Steam With A Grain Of Salt", "DJ Shadow", "Endtroducing...", 399, true));
    jukebox.next();
    assertEquals("RadList.playNext())", static_cast<string>("9 Lazy 9"), jukebox.nowPlaying().artist());
    jukebox.next();
    assertEquals("RadList.album()", static_cast<string>("Silver Wilkinson"), jukebox.nowPlaying().album());
    jukebox.next();
    assertEquals("RadList.addToQueue()", static_cast<string>("Ana Caravelle"), jukebox.nowPlaying().artist());
    jukebox.next();
    assertEquals("RadList.explicit_lyrics()", true, jukebox.nowPlaying().explicit_lyrics());

    return 0;
}

template <typename T>
void assertEquals(string test_name, T expected, T actual) {
    if (actual == expected) {
        cout << "[PASSED] " << test_name << endl;
    } else {
        cout << "[FAILED] " << test_name
             << " - Expected: " << expected
             << ", Actual: " << actual
             << endl;
    }
}
