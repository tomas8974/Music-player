#include "Track.h"
#include <iostream>
#include <iomanip>
#include <vector>

#pragma comment(lib, "winmm.lib")

using namespace std;

Track::Track(string song) : title(song) {

}

string Track::getTitle() const{

    return title;
}

void Track::loadTrack() {
    // Open the selected song
    string command = "open \"" + title + ".mp3" + "\" type mpegvideo alias mp3";
    mciSendStringA(command.c_str(), NULL, 0, NULL);
}

int Track::getTrackLength() {
    char length[128];
    mciSendStringA("status mp3 length", length, sizeof(length), NULL);
    int lengthInSeconds = atoi(length) / 1000;

    return lengthInSeconds;
}

int Track::getTrackPosition(){
    char position[128];
    mciSendStringA("status mp3 position", position, sizeof(position), NULL);
    int positionInSeconds = atoi(position) / 1000;

    return positionInSeconds;
}