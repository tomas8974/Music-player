#include <iostream>
#include <windows.h>
#pragma comment(lib, "winmm.lib")
#include <conio.h>
#include <iomanip>
#include <vector>
#include <filesystem>

#include <locale>
#include <codecvt>

#include "Track.h"
#include "Playlist.h"
#include "Player.h"

using namespace std;
namespace fs = filesystem;


Player::Player() {
    volume = 500;
    string command = "setaudio mp3 volume to " + to_string(volume);
    mciSendStringA(command.c_str(), NULL, 0, NULL);
    createPlaylist("Default playlist");
    currentPlaylist = playlists[0];
    nextSongQueue = false;
    previousSongQueue = false;
}

Track* Player::selectTrack(){
    OPENFILENAMEW ofn;
    wchar_t fileName[MAX_PATH] = L"";
    ZeroMemory(&ofn, sizeof(ofn));

    ofn.lStructSize = sizeof(OPENFILENAME);
    ofn.hwndOwner = NULL;
    ofn.lpstrFilter = L"MP3 Files (*.mp3)\0*.mp3\0";
    ofn.lpstrFile = fileName;
    ofn.nMaxFile = MAX_PATH;
    ofn.Flags = OFN_EXPLORER | OFN_FILEMUSTEXIST | OFN_HIDEREADONLY;
    ofn.lpstrDefExt = L"";

    if (GetOpenFileNameW(&ofn)) {

        // gets filename without path and extension
        wstring fullPath(fileName);
        size_t lastSlash = fullPath.find_last_of(L"\\/");
        wstring filenameWithExtension = fullPath.substr(lastSlash + 1);
        size_t lastDot = filenameWithExtension.find_last_of(L".");
        wstring filenameOnly = filenameWithExtension.substr(0, lastDot);
        wcout << L"You chose the file \"" << filenameOnly << L"\"\n";

        // converts wstring to string
        wstring_convert<codecvt_utf8<wchar_t>, wchar_t> converter;
        string path = converter.to_bytes(fullPath);
        string title = converter.to_bytes(filenameOnly); 

        // creates new track and returns
        Track* newTrack = new Track(title, path);
        return newTrack;

    } else {
        cout << "You cancelled.\n";
        return NULL;
    }
}

vector<Track*> Player::getTrackListFromCurrentFolder()
{
    vector<Track*> newTrackList;
    string path = "./";
    for (const auto &entry : fs::directory_iterator(path))
    {
        if (entry.path().extension() == ".mp3")
        {
            Track* newTrack = new Track(entry.path().stem().string(), entry.path().string());
            newTrackList.push_back(newTrack);
        }
    }
    return newTrackList;
}

void Player::playTrack(Track track, Playlist* playlist) {
    track.loadTrack();
    string command = "setaudio mp3 volume to " + to_string(volume);
    mciSendStringA(command.c_str(), NULL, 0, NULL);
    mciSendStringA("play mp3", NULL, 0, NULL);
    cout << "Now playing: " << track.getTitle() << endl;
    followTrackPosition(track, playlist);
    stopTrack();
}

void Player::pauseTrack() {
    mciSendStringA("pause mp3", NULL, 0, NULL);
    cout << "\nMusic paused. Press P again to resume." << endl;
    while (_getch() != 'p' && _getch() != 'P') {
        // Wait for 'P' key to resume
    }
    mciSendStringA("resume mp3", NULL, 0, NULL);
    cout << "\nMusic resumed." << endl;
}

void Player::stopTrack() {
    mciSendStringA("stop mp3", NULL, 0, NULL);
    mciSendStringA("close mp3", NULL, 0, NULL);
    if (nextSongQueue == true){
        previousSongQueue = false;
    }
    else if (previousSongQueue == true){
        nextSongQueue = false;
    }
    cout << "\rMusic stopped\n" << flush;
}

void Player::playNextTrack(Playlist* playlist) {
    cout << "\nPlaying next song from the library." << endl;
    stopTrack();
    int trackNumber = playlist->getTrackNumber();
    trackNumber = (trackNumber + 1) % playlist->getNumberOfTracksInPlaylist(); // Update currentSong to next song index
    playlist->setTrackNumber(trackNumber);
    vector<Track*> tracks = playlist->getPlaylistTracks();
    playlist->setCurrentTrack(tracks[trackNumber]);
    nextSongQueue = true;
    previousSongQueue = false;
    
    return;
}

void Player::playPreviousTrack(Playlist* playlist) {
    cout << "\nPlaying previous song from the library." << endl;
    stopTrack();
    int trackNumber = playlist->getTrackNumber();
    trackNumber = (trackNumber - 1 + playlist->getNumberOfTracksInPlaylist()) % playlist->getNumberOfTracksInPlaylist(); // Update currentSong to previous song index
    playlist->setTrackNumber(trackNumber);
    vector<Track*> tracks = playlist->getPlaylistTracks();
    playlist->setCurrentTrack(tracks[trackNumber]);
    nextSongQueue = false;
    previousSongQueue = true;

    return;
}

void Player::followTrackPosition(Track track, Playlist* playlist) {

    int minutes = 0;
    int seconds = 0;
    int oldSeconds = -1;

    // Gets track length
    int durationMin = track.getTrackLength() / 60;
    int durationSec = track.getTrackLength() % 60;

    if (playlist != NULL){
        cout << "Press P to pause or unpause music" << endl;
        cout << "Press X key to exit the player..." << endl;
        cout << "Press > to play new song" << endl;
        cout << "Press < to play previous song" << endl;
        cout << "Press Q to go to menu" << endl;
        cout << "Press + to increase volume" << endl;
        cout << "Press - to decrease volume" << endl;
    }
    else{
        cout << "Press P to pause or unpause music" << endl;
        cout << "Press X key to exit the player..." << endl;
        cout << "Press Q to go to menu" << endl;
        cout << "Press + to increase volume" << endl;
        cout << "Press - to decrease volume" << endl;
    }
    
    cout <<"----------------------------------------" << endl;
    while ((durationMin * 60 + durationSec) > (minutes * 60 + seconds)) {

        //  Pause/resume, move to prev/next track, exit program or go to menu
        //  change volume
        if (_kbhit()) {
            char key = _getch();
            if (key == 'p' || key == 'P') {
                pauseTrack();
            }
            else if(key == 'x' || key == 'X') {
                exit(0);
            }
            else if(key == '>' && playlist != NULL) {
                playNextTrack(playlist);
                return;
            }
            else if(key == '<' && playlist != NULL) {
                playPreviousTrack(playlist);
                return;
            }
            else if (key == 'q' || key == 'Q'){
                return;
            }
            else if (key == '+'){
                increaseVolume();
            }
            else if (key == '-'){
                decreaseVolume();
            }
        }

        seconds = track.getTrackPosition() % 60; // Gets track position in seconds
        minutes = track.getTrackPosition() / 60; // Gets track position in minutes
        if (seconds != oldSeconds) {
            cout << "\r" << setw(2) << setfill('0') << minutes << ":" << setw(2) << setfill('0') << seconds <<
                " / " << setw(2) << setfill('0') << durationMin << ":" << setw(2) << setfill('0') << durationSec <<
                "     "<< flush;
            oldSeconds = seconds;
        }
    }
}

// Playlist management

int Player::getNumberOfPlaylists() const{
    return playlists.size();
}

void Player::createPlaylist(string name) {
    Playlist* newPlaylist = new Playlist();
    newPlaylist->setName(name);
    playlists.push_back(newPlaylist);
}

bool Player::deletePlaylist(string name) {
    for (auto it = playlists.begin(); it != playlists.end(); ++it) {
        if ((*it)->getName() == name) {
            delete *it;
            playlists.erase(it);
            return true;
        }
    }
    return false;
}

bool Player::renamePlaylist(string oldName, string newName) {
    for (auto it = playlists.begin(); it != playlists.end(); ++it) {
        if ((*it)->getName() == oldName) {
            (*it)->setName(newName);
            return true;
        }
    }
    return false;
}

void Player::displayAllTracksInPlaylist(Playlist playlist){
    if (playlist.getNumberOfTracksInPlaylist() == 0){
        cout << "There are no tracks in the playlist." << endl;
    }
    else {
        cout << "Tracks in \"" << playlist.getName() << "\"." << endl;
        vector<Track*> playlistTracks = playlist.getPlaylistTracks();
        for (int i = 0; i < playlist.getNumberOfTracksInPlaylist(); i++){
            cout << i << ". " << playlistTracks[i]->getTitle() << endl;
        }
    }
}

void Player::playTracksInThePlaylist(Playlist* playlist, bool repeat, bool shuffle) {
    do {
        playTrack(*(playlist->getCurrentTrack()), playlist);
        while (true) {
            // If song was skipped
            if (nextSongQueue == true) {
                nextSongQueue = false; // Reset the flag
                playTrack(*(playlist->getCurrentTrack()), playlist);
            }
            // If went to previous song
            else if (previousSongQueue == true) {
                previousSongQueue = false; // Reset the flag
                playTrack(*(playlist->getCurrentTrack()), playlist);
            }
            // Going to the next track by default
            else {
                if (playlist->getNumberOfTracksInPlaylist() == (playlist->getTrackNumber() + 1)) {
                    break;
                }   
                else {
                    playNextTrack(playlist);
                }
            }
        }
        if (!repeat) {
            cout << "\nPress 'R' to repeat playlist or any other key to exit: ";
            char key;
            cin >> key;
            if (key != 'R' && key != 'r') {
                break;
            }
        }
        else {
            if (shuffle) {
                playlist->shufflePlaylist();
            }
            playlist->setTrackNumber(0);
        }
    } while (repeat);
}

void Player::displayAllPlaylists(){
    int size = playlists.size();
    if (size == 0){
        cout << "There are no created playlists." << endl;
    }
    else{
        cout << "Playlist list." << endl;
        for (int i = 0; i < size; i++){
            cout << i << ". " << playlists[i]->getName() << endl;
        }
    }
}


// Volume management

void Player::increaseVolume(){
    volume += 20;
    if (volume >= 1000){
        volume = 1000;
    }
    string command = "setaudio mp3 volume to " + to_string(volume);
    mciSendStringA(command.c_str(), NULL, 0, NULL); 
    cout << "\rVolume: " << volume/10 << "/100" << flush;
}

void Player::decreaseVolume(){
    volume -= 20;
    if (volume <= 0){
        volume = 0;
    }
    string command = "setaudio mp3 volume to " + to_string(volume);
    mciSendStringA(command.c_str(), NULL, 0, NULL);
    cout << "\rVolume: " << volume/10 << "/100" << flush;
}