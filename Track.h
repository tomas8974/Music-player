#ifndef TRACK_H
#define TRACK_H

#include <string>
#include <windows.h>

class Track {
public:

    Track(std::string song);

    std::string getTitle() const;
    void loadTrack();
    int getTrackLength();
    int getTrackPosition();

private:
    std::string title;
};

#endif // TRACK_H