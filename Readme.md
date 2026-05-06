# Music Player

**Team members:** Tomas Kazonas, Nojus Sandovas, Levon Airapetian

**Team name:** Špotify

This project was part of the C++ course in Vilnius University.

[Old Readme (in Lithuanian)](Readme.lt.md)

## Project Description

A desktop music player application built in C++ with a graphical user interface. The app allows users to manage and play their music library through a simple interface.

**Features:**

- **Playlist management** — add and remove tracks, repeat or shuffle songs in a playlist
- **Playback controls** — play, pause, resume, skip to next or previous track
- **Volume control** — adjust volume level at any time

[Proof of concept (YouTube)](https://www.youtube.com/watch?v=BZN2oEVn90A)

[Demo (Youtube)](https://youtu.be/enXnZIrW7xQ)

---

## Technologies & Libraries

- **wxWidgets** — GUI framework used to build the application interface
- **windows.h** — Windows API enabling audio file playback and control
- **winmm.lib** — Windows Multimedia library for audio track playback
- **filesystem** — iterates directory files by type for track loading
- **locale / codecvt** — character encoding conversion (wide string to string)
- Standard C++ libraries: `vector`, `algorithm`, `random`, `conio.h`

---

## Class Diagram

![Class diagram](image/Readme/1715329641293.png)

---

## How to Build & Run

### Prerequisites
- Visual Studio 2019 or later
- wxWidgets installed and configured

### Steps
1. Clone the repository
2. Open `MusicPlayer.sln` in Visual Studio
3. Build the solution — **Build → Build Solution** (or `Ctrl + Shift + B`)
4. Run the application — **Debug → Start Without Debugging** (or `Ctrl + F5`)

---

## Known Limitations & Possible Improvements

- Currently only one playlist is supported — multiple playlist support planned
- No seek/rewind functionality yet
- GUI visual polish could be improved

---

## Development Notes

The terminal version was completed smoothly with all planned features. The GUI phase presented challenges as none of the team members had prior experience with C++ GUI development. After researching available options, we chose **wxWidgets** over Qt (which requires a paid license). Working with wxWidgets required Visual Studio, which made sharing work between team members more complex due to reconfiguration overhead. Despite these challenges, the project was completed successfully.
