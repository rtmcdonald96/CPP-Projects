#pragma once

#include <string>

class Song {
private:
    std::string name_;
    std::string artist_;
    std::string album_;
    unsigned int duration_;
    bool explicit_lyrics_;

public:
    Song(std::string, std::string, std::string, unsigned int, bool);

    std::string name();
    std::string artist();
    std::string album();
    unsigned int minutes();
    unsigned int seconds();
    bool explicit_lyrics();
};


Song::Song(std::string new_name, std::string new_artist, std::string new_album, unsigned int new_duration, bool new_explicit_lyrics)
	: name_(new_name), artist_(new_artist), album_(new_album), duration_(new_duration), explicit_lyrics_(new_explicit_lyrics)  {
}
std::string Song::name() {
	return name_;
}
std::string Song::artist() {
	return artist_;
}
std::string Song::album() {
	return album_;
}
unsigned int Song::minutes() {
	return (unsigned int)(duration_ / 60);
}
unsigned int Song::seconds() {
	return (unsigned int)(duration_ % 60);
}
bool Song::explicit_lyrics() {
	return explicit_lyrics_;
}
