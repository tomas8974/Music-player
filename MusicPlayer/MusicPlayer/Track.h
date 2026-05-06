#pragma once

#include <string>
#include <windows.h>

class Track {
public:
    Track(const std::string title, const std::string path);

    void loadTrack();
    std::string getTitle() const;
    std::string getPath() const;
    void setPath(const std::string path);
    int getTrackLength();
    int getTrackPosition();
    void reloadTrack();
    void closeTrack();

private:
    std::string title;
    std::string path;
};
