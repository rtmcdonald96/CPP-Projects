#pragma once

#include <fstream>
#include <iostream>
#include <list>
#include <stdexcept>
#include <string>

#include "Song.hpp"

class RadList {
private:
    std::list<Song> queue_;
    std::list<Song>::iterator nowPlaying_;
public:
    void loadPlaylist(const std::string&);
	void next();
    void prev();
    Song nowPlaying();
    void addToQueue(const Song& newSong);
    void playNext(const Song& nextSong);
};

void RadList::loadPlaylist(const std::string& filename) {
    std::ifstream playlist(filename);

    if (playlist.is_open()) {
        std::string name, artist, album, duration, explicit_lyrics, toss;

        // Read in everything from comma seperated values file
        while (std::getline(playlist, name, ',')) {
            std::getline(playlist, toss, ' ');           // ignore leading space
            std::getline(playlist, artist, ',');
            std::getline(playlist, toss, ' ');           // ignore leading space
            std::getline(playlist, album, ',');
            std::getline(playlist, toss, ' ');           // ignore leading space
            std::getline(playlist, duration, ',');
            std::getline(playlist, toss, ' ');           // ignore leading space
            std::getline(playlist, explicit_lyrics);

            // Construct Song and add to queue
            queue_.push_back(Song(name, artist, album, stoi(duration), explicit_lyrics == "true"));
        }

        playlist.close();
        nowPlaying_ = queue_.begin();
    } else {
        throw std::invalid_argument("Could not open " + filename);
    }
}

void RadList::next() {
	if (nowPlaying_	!= queue_.end()) //Check to make sure nowPlaying_ isn't at end of queue, so there's no illegal memory access
	{
	nowPlaying_++;
	}
	else { 
	throw 	std::out_of_range( "Iterator at end of List" );
	}
}

void RadList::prev() {
	if (nowPlaying_ != queue_.begin()) //Check to make sure nowPlaying_ isn't at beginning of queue, so there's no illegal memory access
	{ 
	nowPlaying_--;
	}
	else {
	throw std::out_of_range( "Iterator at beginning of List" );
	}
}

Song RadList::nowPlaying() {
	return *nowPlaying_;
}

void RadList::addToQueue(const Song& newSong) {
	queue_.push_back(newSong);
}

void RadList::playNext(const Song& nextSong) {
	if (nowPlaying_ == queue_.end()) //if nowPlaying is at the end of the queue call pushback function
	{
	queue_.push_back(nextSong);
	}	
	else{
	std::list<Song>::iterator ptr;	//create a iterator named ptr to place nextSong into queue
	ptr = nowPlaying_;
	ptr++;
	queue_.emplace(ptr, nextSong);
	}

}
