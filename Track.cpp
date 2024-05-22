#include "Track.h"
#include <iostream>
#include <iomanip>
#include <vector>

#pragma comment(lib, "winmm.lib")

using namespace std;

Track::Track(string title, string path) : title(title), path(path) {

}

string Track::getTitle() const{

    return this->title;
}

string Track::getPath() const{
    return this->path;
}
void Track::setPath(string path){
    this->path = path;
}

void Track::loadTrack() {
    // Open the selected song
    string command = "open \"" + path + "\" type mpegvideo alias mp3";
    mciSendStringA(command.c_str(), NULL, 0, NULL);
}

void Track::closeTrack() {
    mciSendStringA("close mp3", NULL, 0, NULL);
}

void Track::reloadTrack() {
    mciSendStringA("close mp3", NULL, 0, NULL);
    loadTrack();
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