#ifndef PLAYLIST_H
#define PLAYLIST_H

#include <vector>
#include "Track.h"

class Playlist {
public:
    Playlist();
    ~Playlist();

    void setName(std::string name);
    std::string getName() const;
    void setTrackNumber(int trackNumber);
    int getTrackNumber() const;
    void setCurrentTrack(Track* currentTrack);
    Track* getCurrentTrack() const;
    int getNumberOfTracksInPlaylist() const;

    void addTrack(Track track);
    void removeTrack(Track* track);
    std::vector<Track*> getPlaylistTracks();
    void setPlaylistTracks(std::vector<Track*> tracks);
    void shufflePlaylist();

private:
    std::string name;
    int trackNumber;
    Track* currentTrack;

    std::vector<Track*> tracks;
};

#endif // PLAYLIST_H