#include "MainFrame.h"
#include <wx/notebook.h>
#include <wx/listctrl.h>
#include <wx/wfstream.h>
#include <wx/msgdlg.h>
#include <wx/filedlg.h>
#include <wx/tglbtn.h>

enum IDs {
    ID_SELECT = 2,
    ID_PLAY,
    ID_STOP,
    ID_PREVIOUS,
    ID_NEXT,
    ID_VOLUME_SLIDER,
    ID_TIME_DISPLAY,
    ID_ADD_TRACK,
    ID_REMOVE_TRACK,
    ID_NOTEBOOK,
    ID_REPEAT,
    ID_SHUFFLE
};

wxBEGIN_EVENT_TABLE(MainFrame, wxFrame)
EVT_BUTTON(ID_PLAY, MainFrame::OnPlay)
EVT_BUTTON(ID_STOP, MainFrame::OnStop)
EVT_BUTTON(ID_PREVIOUS, MainFrame::OnPrevious)
EVT_BUTTON(ID_NEXT, MainFrame::OnNext)
EVT_SLIDER(ID_VOLUME_SLIDER, MainFrame::OnVolumeSlider)
EVT_BUTTON(ID_ADD_TRACK, MainFrame::OnAddTrack)
EVT_BUTTON(ID_REMOVE_TRACK, MainFrame::OnRemoveTrack)
EVT_BUTTON(wxID_ANY, MainFrame::OnPlayPlaylist)
EVT_TOGGLEBUTTON(ID_REPEAT, MainFrame::OnRepeat)
EVT_TOGGLEBUTTON(ID_SHUFFLE, MainFrame::OnShuffle)
wxEND_EVENT_TABLE()

MainFrame::MainFrame(const wxString& title)
    : wxFrame(nullptr, wxID_ANY, title), player(), selectedTrack(nullptr), playerThread(nullptr), isPlaying(false) {
    volume = 50;
    command = None;

    wxPanel* panel = new wxPanel(this);

    wxButton* play = new wxButton(panel, ID_PLAY, "Play", wxDefaultPosition, wxSize(50, 25));
    wxButton* stop = new wxButton(panel, ID_STOP, "Stop", wxDefaultPosition, wxSize(50, 25));
    wxButton* previous = new wxButton(panel, ID_PREVIOUS, "Previous", wxDefaultPosition, wxSize(50, 25));
    wxButton* next = new wxButton(panel, ID_NEXT, "Next", wxDefaultPosition, wxSize(50, 25));
    wxToggleButton* random = new wxToggleButton(panel, ID_SHUFFLE, "Shuffle", wxDefaultPosition, wxSize(50, 25));
    wxToggleButton* repeat = new wxToggleButton(panel, ID_REPEAT, "Repeat", wxDefaultPosition, wxSize(50, 25));
    wxSlider* volumeSlider = new wxSlider(panel, ID_VOLUME_SLIDER, 50, 0, 100, wxDefaultPosition, wxSize(100, 50), wxSL_VALUE_LABEL);
    wxButton* addTrack = new wxButton(panel, ID_ADD_TRACK, "Add Track", wxDefaultPosition, wxSize(100, 25));
    wxButton* removeTrack = new wxButton(panel, ID_REMOVE_TRACK, "Remove Track", wxDefaultPosition, wxSize(100, 25));

    wxBoxSizer* buttonSizer = new wxBoxSizer(wxHORIZONTAL);
    buttonSizer->Add(play, 0, wxALL | wxALIGN_CENTER, 5);
    buttonSizer->Add(stop, 0, wxALL | wxALIGN_CENTER, 5);
    buttonSizer->Add(previous, 0, wxALL | wxALIGN_CENTER, 5);
    buttonSizer->Add(next, 0, wxALL | wxALIGN_CENTER, 5);
    buttonSizer->Add(random, 0, wxALL | wxALIGN_CENTER, 5);
    buttonSizer->Add(repeat, 0, wxALL | wxALIGN_CENTER, 5);
    buttonSizer->Add(volumeSlider, 0, wxALL | wxALIGN_CENTER, 5);
    buttonSizer->Add(addTrack, 0, wxALL | wxALIGN_CENTER, 5);
    buttonSizer->Add(removeTrack, 0, wxALL | wxALIGN_CENTER, 5);

    wxBoxSizer* trackInfoSizer = new wxBoxSizer(wxHORIZONTAL);

    wxBoxSizer* panelSizer = new wxBoxSizer(wxVERTICAL);
    panelSizer->AddStretchSpacer(1);
    panelSizer->Add(trackInfoSizer, 0, wxALIGN_LEFT);
    panelSizer->Add(buttonSizer, 0, wxALIGN_CENTER);

    CreateStatusBar();
    SetStatusText("Ready");

    wxStaticText* timeDisplay = new wxStaticText(panel, ID_TIME_DISPLAY, "00:00 / 00:00", wxDefaultPosition, wxDefaultSize, wxALIGN_LEFT);
    trackInfoSizer->Add(timeDisplay, 1, wxALL | wxALIGN_LEFT, 5);

    wxButton* playPlaylist = new wxButton(panel, wxID_ANY, "Play Playlist", wxDefaultPosition, wxSize(100, 25));
    buttonSizer->Add(playPlaylist, 0, wxALL | wxALIGN_CENTER, 5);
    playPlaylist->Bind(wxEVT_BUTTON, &MainFrame::OnPlayPlaylist, this);

    wxNotebook* notebook = new wxNotebook(panel, ID_NOTEBOOK, wxDefaultPosition, wxDefaultSize, wxNB_LEFT);

    for (int i = 0; i < player.getNumberOfPlaylists(); i++) {
        wxPanel* playlistPanel = new wxPanel(notebook, wxID_ANY);
        playlistBox = new wxListCtrl(playlistPanel, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxLC_REPORT | wxLC_SINGLE_SEL | wxLC_HRULES);

        playlistBox->InsertColumn(0, "Title", wxLIST_FORMAT_LEFT, 250);
        playlistBox->InsertColumn(1, "Duration", wxLIST_FORMAT_LEFT, 150);

        wxBoxSizer* playlistSizer = new wxBoxSizer(wxVERTICAL);
        playlistSizer->Add(playlistBox, 1, wxEXPAND | wxALL, 5);

        playlistPanel->SetSizer(playlistSizer);
        notebook->AddPage(playlistPanel, player.playlists[i]->getName(), true);

        for (int j = 0; j < player.playlists[i]->getPlaylistTracks().size(); j++) {
            wxListItem item;
            item.SetId(j);
            item.SetText(player.playlists[i]->getPlaylistTracks()[j]->getTitle());
            playlistBox->InsertItem(item);

            // Set the duration in the second column
            player.playlists[0]->getPlaylistTracks()[j]->reloadTrack();
            int durationInMinutes = player.playlists[i]->getPlaylistTracks()[j]->getTrackLength() / 60;
            int durationInSeconds = player.playlists[i]->getPlaylistTracks()[j]->getTrackLength() % 60;
            wxString duration = wxString::Format("%02d:%02d", durationInMinutes, durationInSeconds);
            playlistBox->SetItem(j, 1, duration);
            player.playlists[0]->getPlaylistTracks()[j]->closeTrack();
        }
    }

    panelSizer->Add(notebook, 1, wxEXPAND | wxALL, 5);
    panel->SetSizer(panelSizer);
    SetMinClientSize(panel->GetBestSize());


    Bind(wxEVT_COMMAND_TEXT_UPDATED, [&](wxCommandEvent& event) {
        wxButton* playButton = wxDynamicCast(FindWindowById(ID_PLAY, this), wxButton);
        if (playButton && event.GetString() == "Play") {
            playButton->SetLabel("Play");
        }

        wxStaticText* timeDisplay = wxDynamicCast(FindWindowById(ID_TIME_DISPLAY, this), wxStaticText);
        if (timeDisplay && event.GetString() == "00:00 / 00:00") {
            timeDisplay->SetLabel("00:00 / 00:00");
        }
        SetStatusText(event.GetString());
        });

    // Bind the close event to a lambda function that stops the player and joins the thread
    Bind(wxEVT_CLOSE_WINDOW, [&](wxCloseEvent& event) {
        command = Stop;
        if (playerThread) {
            if (playerThread->joinable()) {
                playerThread->join();
            }
            delete playerThread;
            playerThread = nullptr;
        }
        Destroy();
        });

}

MainFrame::~MainFrame() {
    if (playerThread && playerThread->joinable()) {
        {
            std::lock_guard<std::mutex> lock(mtx);
            command = Stop;
        }
        cv.notify_one();
        playerThread->join();
        delete playerThread;
    }
}

void MainFrame::PlayerPlay() {
    if (selectedTrack != nullptr && !player.isPlaying) {
        isThreadRunning = true;
        playerThread = new std::thread([this]() {
            do {
                wxButton* playButton = wxDynamicCast(FindWindowById(ID_PLAY, this), wxButton);
                if (playButton && selectedTrack != nullptr) {
                    if (playButton->GetLabel() == "Play") {
                        playButton->SetLabel("Pause");
                    }
                    else if (playButton->GetLabel() == "Pause") {
                        playButton->SetLabel("Pause");
                    }
                }
                player.playTrack(*selectedTrack, player.currentPlaylist);
                int minutes = 0;
                int seconds = 0;

                // Gets track length
                int durationMin = selectedTrack->getTrackLength() / 60;
                int durationSec = selectedTrack->getTrackLength() % 60;
                while ((durationMin * 60 + durationSec) > (minutes * 60 + seconds)) { // while playing

                    //  Pause/resume, move to prev/next track, exit program or go to menu
                    //  change volume
                    if (command == Pause) {
                        player.pauseTrack();
                        command = None;
                    }
                    else if (command == Resume) {
                        player.resumeTrack();
                        command = None;
                    }
                    else if (command == Stop) {
                        break;
                    }
                    else if (command == Next && player.currentPlaylist != NULL) {
                        break;
                    }
                    else if (command == Previous && player.currentPlaylist != NULL) {
                        break;
                    }
                    else if (command == ChangeVolume) {
                        player.setVolume(volume);
                        command = None;
                    }

                    UpdateTimeDisplay(minutes, seconds, durationMin, durationSec);

                    // update the track position

                    seconds = selectedTrack->getTrackPosition() % 60; // Gets track position in seconds
                    minutes = selectedTrack->getTrackPosition() / 60; // Gets track position in minutes
                }
                player.stopTrack();
                UpdateButtonDisplayWhenStopped();
                // Check if there is a next track in the playlist
                if (player.currentPlaylist != NULL && isThreadRunning && command == Previous) {
                    player.playPreviousTrack(player.currentPlaylist);
                    selectedTrack = player.currentPlaylist->getCurrentTrack();
                    command = None;
                }
                else if (player.currentPlaylist != NULL && isThreadRunning && (command == Next || command == None)) {
                    player.playNextTrack(player.currentPlaylist);
                    if (player.currentPlaylist->getCurrentTrack() == nullptr) {
						break;
					}
                    selectedTrack = player.currentPlaylist->getCurrentTrack();
                    command = None;
                }
                else {
                    selectedTrack = nullptr;
                    command = None;
                }
            }
            while (selectedTrack != nullptr && isThreadRunning && command != Stop);
            });

    }
    else if (selectedTrack == nullptr) {
        wxMessageBox("No track selected");
    }
}

void MainFrame::OnPlay(wxCommandEvent& event) {
    // Song selection
    player.setVolume(volume);
    if (!player.isPlaying) {
        Track* newTrack = player.selectTrack();
        if (newTrack != nullptr) {
            selectedTrack = newTrack;
            player.currentPlaylist = nullptr;
        }
    }

    // button play/pause
    wxButton* playButton = dynamic_cast<wxButton*>(event.GetEventObject());
    if (playButton && selectedTrack != nullptr) {
        if (playButton->GetLabel() == "Play") {
            playButton->SetLabel("Pause");
            command = Resume;
        }
        else if (playButton->GetLabel() == "Pause") {
            playButton->SetLabel("Play");
            command = Pause;
        }
    }
    // Play track
    PlayerPlay();
}

void MainFrame::OnStop(wxCommandEvent& event) {
    command = Stop;
    if (playerThread) {
        playerThread->join();
        delete playerThread;
        playerThread = nullptr;
        isThreadRunning = false;
    }
    UpdateButtonDisplayWhenStopped();
    command = None;
}

void MainFrame::OnPrevious(wxCommandEvent& event) {
    if (player.currentPlaylist != NULL) {
        command = Previous;
    }
    else {
		wxMessageBox("No playlist selected");
	}   
}

void MainFrame::OnNext(wxCommandEvent& event) {
    if (player.currentPlaylist != NULL) {
        command = Next;
    }
    else {
        wxMessageBox("No playlist selected");
    }
}

void MainFrame::OnVolumeSlider(wxCommandEvent& event) {
    wxSlider* slider = dynamic_cast<wxSlider*>(event.GetEventObject());
    if (slider) {
        volume = slider->GetValue();
        command = ChangeVolume;
    }
}

void MainFrame::OnAddTrack(wxCommandEvent& event) {
    Track* track = player.selectTrack();
    if (track == NULL) return;
    track->loadTrack();
    player.playlists[0]->addTrack(*track);

    if (!playlistBox) return;
    UpdatePlaylistDisplay();
}

void MainFrame::OnRemoveTrack(wxCommandEvent& event) {
    if (playlistBox->GetSelectedItemCount() == 0) {
        wxMessageBox("No track selected to remove.", "Error", wxOK | wxICON_ERROR);
        return;
    }

    long selectedItem = playlistBox->GetNextItem(-1, wxLIST_NEXT_ALL, wxLIST_STATE_SELECTED);

    // Get the currently selected playlist
    wxNotebook* notebook = static_cast<wxNotebook*>(FindWindowById(ID_NOTEBOOK, this));

    // Check if the notebook exists
    if (!notebook) {
        wxMessageBox("No notebook found.", "Error", wxOK | wxICON_ERROR);
        return;
    }

    int selectedPlaylistIndex = notebook->GetSelection();

    // Remove the track from the currently selected playlist
    player.playlists[selectedPlaylistIndex]->removeTrack(selectedItem);
    UpdatePlaylistDisplay();
}

void MainFrame::OnPlayPlaylist(wxCommandEvent& event) {
    if (player.isPlaying) {
        wxMessageBox("Player is already playing");
    }
    else {
        player.setVolume(volume);
        
        player.currentPlaylist = player.playlists[0];
        
        if (player.playlists[0]->getPlaylistTracks().size() != 0) {
            if (shuffle && player.currentPlaylist != NULL) {
                player.currentPlaylist->shufflePlaylist();

            }

            std::vector<Track*> playlistTracks = player.playlists[0]->getPlaylistTracks();

            player.currentPlaylist->setTrackNumber(0);
            player.currentPlaylist->setCurrentTrack(playlistTracks[0]);
            selectedTrack = playlistTracks[0];
            // button play/pause
            wxButton* playButton = wxDynamicCast(FindWindowById(ID_PLAY, this), wxButton);
            if (playButton && selectedTrack != nullptr) {
                if (playButton->GetLabel() == "Play") {
                    playButton->SetLabel("Pause");
                    command = Resume;
                }
                else if (playButton->GetLabel() == "Pause") {
                    playButton->SetLabel("Play");
                    command = Pause;
                }
            }
            // Play track
            PlayerPlay();
        }
        else {
            wxMessageBox("No tracks in the playlist");
        }
    }
}


void MainFrame::OnRepeat(wxCommandEvent& event) {
    wxToggleButton* repeatButton = dynamic_cast<wxToggleButton*>(event.GetEventObject());
    if (repeatButton) {
        if (repeatButton->GetValue()) {
            repeat = true;
            player.currentPlaylist->repeat = true;
        }
        else {
            repeat = false;
            player.currentPlaylist->repeat = false;
        }
    }
}

void MainFrame::OnShuffle(wxCommandEvent& event) {
    wxToggleButton* shuffleButton = dynamic_cast<wxToggleButton*>(event.GetEventObject());
    if (shuffleButton) {
        if (shuffleButton->GetValue()) {
            shuffle = true;
        }
        else {
            shuffle = false;
        }
    }
}

void MainFrame::UpdateTimeDisplay(int minutes, int seconds, int durationMin, int durationSec) {
    wxString statusText;
    statusText.Printf("Now playing: %s - %02d:%02d / %02d:%02d", selectedTrack->getTitle(), minutes, seconds, durationMin, durationSec);

    wxString currentSong;
    currentSong.Printf("%s - %02d:%02d / %02d:%02d", selectedTrack->getTitle(), minutes, seconds, durationMin, durationSec);

    // Create a new wxThreadEvent and set the string data to the status text
    wxThreadEvent* evt = new wxThreadEvent(wxEVT_COMMAND_TEXT_UPDATED, wxID_ANY);
    evt->SetString(statusText);
    wxQueueEvent(this, evt);

    wxStaticText* timeDisplay = wxDynamicCast(FindWindowById(ID_TIME_DISPLAY, this), wxStaticText);
    if (timeDisplay) {
        wxString timeText;
        timeText.Printf("%s - %02d:%02d / %02d:%02d", selectedTrack->getTitle(), minutes, seconds, durationMin, durationSec);
        timeDisplay->SetLabel(timeText);
    }
}

void MainFrame::UpdateButtonDisplayWhenStopped() {
    // Create a new wxThreadEvent and set the string data to an empty string
    wxThreadEvent* evt = new wxThreadEvent(wxEVT_COMMAND_TEXT_UPDATED, wxID_ANY);
    evt->SetString("Ready");

    wxQueueEvent(this, evt);

    // Create a new wxThreadEvent and set the string data to the status text
    wxThreadEvent* evt2 = new wxThreadEvent(wxEVT_COMMAND_TEXT_UPDATED, wxID_ANY);
    evt->SetString("Play");
    wxQueueEvent(this, evt2);

    // Similarly for time display
    wxThreadEvent* evt3 = new wxThreadEvent(wxEVT_COMMAND_TEXT_UPDATED, wxID_ANY);
    evt2->SetString("00:00 / 00:00");
    wxQueueEvent(this, evt3);
}

void MainFrame::UpdateStatus(const wxString& status) {
    SetStatusText(status);
}

wxListCtrl* MainFrame::GetCurrentPlaylistBox() {
    wxNotebook* notebook = static_cast<wxNotebook*>(FindWindowById(wxID_ANY, this));
    if (!notebook) return nullptr;

    wxPanel* currentPlaylistPanel = static_cast<wxPanel*>(notebook->GetCurrentPage());
    if (!currentPlaylistPanel) return nullptr;

    return static_cast<wxListCtrl*>(currentPlaylistPanel->FindWindowById(wxID_ANY, currentPlaylistPanel));
}

void MainFrame::UpdatePlaylistDisplay() {
    if (!playlistBox) return;

    playlistBox->DeleteAllItems();

    for (int j = 0; j < player.playlists[0]->getPlaylistTracks().size(); j++) {
        wxListItem item;
        item.SetId(j);
        item.SetText(player.playlists[0]->getPlaylistTracks()[j]->getTitle());
        playlistBox->InsertItem(item);

        // Set the duration in the second column
        player.playlists[0]->getPlaylistTracks()[j]->reloadTrack();
        int durationInMinutes = player.playlists[0]->getPlaylistTracks()[j]->getTrackLength() / 60;
        int durationInSeconds = player.playlists[0]->getPlaylistTracks()[j]->getTrackLength() % 60;
        wxString duration = wxString::Format("%02d:%02d", durationInMinutes, durationInSeconds);
        playlistBox->SetItem(j, 1, duration);
        player.playlists[0]->getPlaylistTracks()[j]->closeTrack();
    }
}
