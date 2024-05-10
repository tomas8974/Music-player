#ifndef TRACK_H
#define TRACK_H

#include <string>
#include <windows.h>

class Track {
public:

    Track(std::string title, std::string path);

    std::string getTitle() const;
    std::string getPath() const;
    void setPath(std::string path);
    void loadTrack();
    int getTrackLength();
    int getTrackPosition();

private:
    std::string title;
    std::string path;
};

#endif // TRACK_H