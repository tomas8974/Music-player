#include <iostream>
#include <windows.h>
#pragma comment(lib, "winmm.lib")
#include <iomanip>
#include <vector>
#include <algorithm>
#include <random>
#include "Playlist.h"

using namespace std;

Playlist::Playlist() {

}

Playlist::~Playlist() {
    // Clean up dynamically allocated Tracks
    for (Track* track : playlistTracks) {
        delete track;
    }
    playlistTracks.clear();
}

void Playlist::setName(string name) {
    this->name = name;
}

string Playlist::getName() const {
    return name;
}

void Playlist::setTrackNumber(int trackNumber) {
    this->trackNumber = trackNumber;
}

int Playlist::getTrackNumber() const {
    return this->trackNumber;
}

void Playlist::setCurrentTrack(Track* currentTrack) {
    this->currentTrack = currentTrack;
}

Track* Playlist::getCurrentTrack() const {
    return this->currentTrack;
}

int Playlist::getNumberOfTracksInPlaylist() const {
    return playlistTracks.size();
}

// Add a track to the playlist
void Playlist::addTrack(Track track) {
    playlistTracks.push_back(new Track(track));
}

void Playlist::removeTrack(int index) {
    // Check if index is valid
    if (index < 0 || index >= playlistTracks.size()) {
        return;
    }

    // Remove the track at the given index
    playlistTracks.erase(playlistTracks.begin() + index);
}

// Remove a track from the playlist
void Playlist::removeTrack(Track* track) {
    auto it = std::find(playlistTracks.begin(), playlistTracks.end(), track);
    if (it != playlistTracks.end()) {
        delete* it;
        playlistTracks.erase(it);
    }
}

// Shuffle the playlist and set currentTrack randomly
void Playlist::shufflePlaylist() {
    auto rng = std::default_random_engine{};
    std::shuffle(playlistTracks.begin(), playlistTracks.end(), rng);
}

vector<Track*> Playlist::getPlaylistTracks() {
    return playlistTracks;
}

void Playlist::setPlaylistTracks(vector<Track*> tracks) {
    this->playlistTracks = tracks;
}
