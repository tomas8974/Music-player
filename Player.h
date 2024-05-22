#ifndef PLAYER_H
#define PLAYER_H

#include <string>
#include <vector>
#include <windows.h>
#include "Track.h"
#include "Playlist.h"


class Player {
public:

    std::vector<Playlist*> playlists;
    Playlist* currentPlaylist;
    bool nextSongQueue;
    bool previousSongQueue;
    int volume;
    bool isPlaying;
    bool isPaused;

    Player();

    Track* selectTrack();
    std::vector<Track*> getTrackListFromCurrentFolder();

    // Track management
    void playTrack(Track& track, Playlist* playlist);
    void pauseTrack();
    void resumeTrack();
    void stopTrack();
    void playPreviousTrack(Playlist* playlist);
    void playNextTrack(Playlist* playlist);

    // Playlist management
    int getNumberOfPlaylists() const;
    void createPlaylist(std::string name);
    bool deletePlaylist(std::string name);
    bool renamePlaylist(std::string oldName, std::string newName);
    void playTracksInThePlaylist(Playlist* playlist, bool repeat, bool shuffle);
    void displayAllTracksInPlaylist(Playlist playlist);
    void displayAllPlaylists();

    // Volume management
    void setVolume(int volume);
    void increaseVolume();
    void decreaseVolume();
};

#endif // PLAYER_H