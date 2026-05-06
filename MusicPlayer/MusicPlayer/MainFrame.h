#pragma once

#include <wx/wx.h>
#include <wx/listctrl.h>
#include "Player.h"
#include <thread>
#include <condition_variable>
#include <windows.h>
#include "Track.h"

class MainFrame : public wxFrame
{
public:
    MainFrame(const wxString& title);
    ~MainFrame();

private:
    Player player;
    Track* selectedTrack;
    std::thread* playerThread;
    wxListCtrl* playlistBox;
    std::condition_variable cv;
    std::mutex mtx;
    enum PlayerCommand { None, Play, Pause, Resume, Stop, Next, Previous, ChangeVolume};
    PlayerCommand command;
    int volume;
    bool isPlaying;
    bool isThreadRunning;
    bool repeat;
    bool shuffle;

    void PlayerPlay();

    void OnPlay(wxCommandEvent& event);
    void OnStop(wxCommandEvent& event);
    void OnPrevious(wxCommandEvent& event);
    void OnNext(wxCommandEvent& event);
    void OnVolumeSlider(wxCommandEvent& event);
    void OnAddTrack(wxCommandEvent& event);
    void OnRemoveTrack(wxCommandEvent& event);
    void OnPlayPlaylist(wxCommandEvent& event);
    void OnRepeat(wxCommandEvent& event);
    void OnShuffle(wxCommandEvent& event);

    void UpdateTimeDisplay(int minutes, int seconds, int durationMin, int durationSec);
    void UpdateButtonDisplayWhenStopped();
    void UpdateStatus(const wxString& status);

    wxListCtrl* GetCurrentPlaylistBox();
    void UpdatePlaylistDisplay();

    wxDECLARE_EVENT_TABLE();
};
