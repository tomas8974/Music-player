#include <iostream>
#include <windows.h>
#pragma comment(lib, "winmm.lib")
#include <iomanip>
#include <vector>
#include <filesystem>
#include <algorithm>
#include <random>
#include "Playlist.h"

using namespace std;
namespace fs = filesystem;

Playlist::Playlist() {

}

Playlist::~Playlist() {

}

void Playlist::setName(string name){
    this->name = name;
}

string Playlist::getName() const{
    return name;
}

void Playlist::setTrackNumber(int trackNumber){
    this->trackNumber = trackNumber;
}

int Playlist::getTrackNumber() const{
    return this->trackNumber;
}

void Playlist::setCurrentTrack(Track* currentTrack){
    this->currentTrack = currentTrack;
}

Track* Playlist::getCurrentTrack() const{
    return this->currentTrack;
}

int Playlist::getNumberOfTracksInPlaylist() const {
    return tracks.size();
}

// Gets song list in the current folder

vector<Track*> Playlist::getTrackListFromCurrentFolder()
{
    vector<Track*> newTrackList;
    string path = "./";
    for (const auto &entry : fs::directory_iterator(path))
    {
        if (entry.path().extension() == ".mp3")
        {
            Track* newTrack = new Track(entry.path().stem().string());
            newTrackList.push_back(newTrack);
        }
    }
    return newTrackList;
}

// add a track to the playlist
void Playlist::addTrack(Track track) {
    tracks.push_back(new Track(track));
}

// remove a track from the playlist
void Playlist::removeTrack(Track* track) {
    auto it = std::find(tracks.begin(), tracks.end(), track);
    if (it != tracks.end()) {
        tracks.erase(it);
    }
}

// Shuffle the playlist
void Playlist::shufflePlaylist() {
    std::random_shuffle(tracks.begin(), tracks.end());
}

vector<Track*> Playlist::getPlaylistTracks(){
    return tracks;
}
void Playlist::setPlaylistTracks(vector<Track*> tracks){
    this->tracks = tracks;
}
