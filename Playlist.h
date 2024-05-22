#ifndef PLAYLIST_H
#define PLAYLIST_H

#include <string>
#include <vector>
#include "Track.h"

class Playlist {
public:
    Playlist();
    ~Playlist();

    void setName(const std::string name);
    std::string getName() const;
    void setTrackNumber(int trackNumber);
    int getTrackNumber() const;
    void setCurrentTrack(Track* track);
    Track* getCurrentTrack() const;
    int getNumberOfTracksInPlaylist() const;
    //void addTrack(Track& track);
    void removeTrack(int index);
    void shufflePlaylist();
    std::vector<Track*> getPlaylistTracks();
    void setPlaylistTracks(std::vector<Track*> tracks);
    void removeTrack(Track* track);
    void addTrack(Track track);

    bool repeat;

private:
    std::string name;
    int trackNumber;
    Track* currentTrack;
    std::vector<Track*> playlistTracks;
};

#endif // PLAYLIST_H
