#include <iostream>
#include "Player.h"

using namespace std;


int main (){

    Player player;
    int choice;

    do {
        cout << "\nMenu:\n";
        cout << "1. Select a song to play\n";
        cout << "2. Display song list in the current folder\n";
        cout << "3. Play a song from the current folder\n";;
        cout << "4. Create a playlist\n";
        cout << "5. Delete a playlist\n";
        cout << "6. Rename a playlist\n";
        cout << "7. Display playlists\n";
        cout << "8. Display all tracks in the playlist\n";
        cout << "9. Play tracks in the playlist\n";
        cout << "10. Add song to playlist\n";
        cout << "11. Remove song from playlist\n";
        cout << "0. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1: {
                Track* song = player.selectTrack();
                if (song != NULL){
                    player.playTrack(*song, NULL);
                }
                break;
            }
            case 2: {
                // Display song list in the current folder

                vector<Track*> tracks = player.getTrackListFromCurrentFolder(); // gets tracks from current folder
                cout << "Song list:" << endl;
                if (tracks.size() == 0){
                    cout << "There are no songs." << endl;
                }
                else {
                    for (int i = 0; i < tracks.size(); i++)
                    {
                        cout << i << ". " << tracks[i]->getTitle() << endl;
                    }
                }
                break;
            }
            case 3: {
                // Play a song from the current folder
                vector<Track*> tracks = player.getTrackListFromCurrentFolder(); // gets tracks from current folder
                cout << "Choose a song to play: ";
                int trackNumber;
                cin >> trackNumber;
                if(trackNumber < 0 || trackNumber > tracks.size()){
                    cout << "Invalid song number!" << endl;
                }
                else {
                    player.currentPlaylist->setTrackNumber(trackNumber);
                    player.currentPlaylist->setCurrentTrack(tracks[trackNumber]);
                    player.playTrack(*player.currentPlaylist->getCurrentTrack(), player.currentPlaylist);

                    while (true) {
                        if(player.nextSongQueue == true){
                            player.nextSongQueue = false; // Reset the flag
                            player.playTrack(*player.currentPlaylist->getCurrentTrack(), player.currentPlaylist);
                        }
                        else if(player.previousSongQueue == true){
                            player.previousSongQueue = false; // Reset the flag
                            player.playTrack(*player.currentPlaylist->getCurrentTrack(), player.currentPlaylist);
                        }
                        else {
                            break;
                        }
                    }
                }
                break;
            }
            case 4: {
                // Create a playlist
                string name;
                cout << "Enter a name for a new playlist: ";
                cin >> name;
                player.createPlaylist(name);
                cout << "Playlist \" " << name <<  "\" was created successfully!" << endl;
                break;
            }
            case 5: {
                // Delete a playlist
                int number;
                if (player.getNumberOfPlaylists() == 0) {
                    cout << "There are no playlists to delete!" << endl;
                }
                else{
                    while (true){
                        player.displayAllPlaylists();
                        cout << "Choose a playlist to rename: " << endl;
                        cin >> number;
                        if (number < 0 or number >= player.getNumberOfPlaylists()){
                            cout << "There is no such playlist. Try again!" << endl;
                            while (getchar() != '\n')
                                                ;
                        }
                        else{
                            string name = player.playlists[number]->getName();
                            if (player.deletePlaylist(player.playlists[number]->getName()) == true){
                                cout << "Playlist \"" << name << "\" was successfully deleted!" << endl;
                                break;
                            }
                            else{
                                cout << "There was an error while trying to delete the playlist." << endl;
                            }
                        }
                    }
                }
                break;
            }
            case 6: {
                // Rename a playlist
                int number;
                string name;
                if (player.getNumberOfPlaylists() == 0) {
                    cout << "There are no playlists to rename!" << endl;
                }
                else{
                    while (true){
                        player.displayAllPlaylists();
                        cout << "Choose a playlist to rename: " << endl;
                        cin >> number;
                        if (number < 0 or number >= player.getNumberOfPlaylists()){
                            cout << "There is no such playlist. Try again!" << endl;
                            while (getchar() != '\n')
                                                ;
                        }
                        else{
                            cout << "Enter a new name for the playlist: ";
                            cin >> name;
                            if (player.renamePlaylist(player.playlists[number]->getName(), name) == true){
                                cout << "Playlist was successfully renamed to \"" << name << "\"!" << endl;
                                break;
                            }
                            else{
                                cout << "There was an error while trying to rename the playlist." << endl;
                            }
                        }
                    }
                }
                break;
            }
            case 7: {
                // Display all playlists
                player.displayAllPlaylists();
                break;
            }
            case 8: {
                // Display all tracks in the playlist
                int number;
                if (player.getNumberOfPlaylists() == 0) {
                    cout << "There are no playlists!" << endl;
                }
                else{
                    while (true){
                        player.displayAllPlaylists();
                        cout << "Choose a playlist to view tracks: " << endl;
                        cin >> number;
                        if (number < 0 or number >= player.getNumberOfPlaylists()){
                            cout << "There is no such playlist. Try again!" << endl;
                            while (getchar() != '\n')
                                                ;
                        }
                        else{
                            player.displayAllTracksInPlaylist(*player.playlists[number]);
                            break;
                        }
                    }
                }
                break;
            }
            case 9: {
                // Play tracks in the playlist
                int number;
                if (player.getNumberOfPlaylists() == 0) {
                    cout << "There are no playlists!" << endl;
                    break;
                } else {
                    while (true) {
                        player.displayAllPlaylists();
                        cout << "Choose a playlist to play tracks: ";
                        cin >> number;
                        if (number < 0 || number >= player.getNumberOfPlaylists()) {
                            cout << "There is no such playlist. Try again!" << endl;
                            while (getchar() != '\n');
                        } else {
                            player.currentPlaylist = player.playlists[number];
                            player.displayAllTracksInPlaylist(*player.playlists[number]);
                            if (player.currentPlaylist->getNumberOfTracksInPlaylist() > 0) {
                                vector<Track*> playlistTracks = player.currentPlaylist->getPlaylistTracks();
                                player.currentPlaylist->setCurrentTrack(playlistTracks[0]);
                                cout << "a. Play once\n";
                                cout << "b. Repeat album\n";
                                cout << "c. Shuffle\n";
                                cout << "Enter your choice: ";
                                char playChoice;
                                cin >> playChoice;
                                switch (playChoice) {
                                    case 'a':
                                        cout << player.currentPlaylist->getCurrentTrack()->getTitle() << endl;
                                        player.playTracksInThePlaylist(player.currentPlaylist, false, false);
                                        break;
                                    case 'b':
                                        player.playTracksInThePlaylist(player.currentPlaylist, true, false);
                                        break;
                                    case 'c':
                                        player.playTracksInThePlaylist(player.currentPlaylist, false, true);
                                        break;
                                    default:
                                        cout << "Invalid choice! Playing once by default.\n";
                                        player.playTracksInThePlaylist(player.currentPlaylist, false, false);
                                        break;
                                }
                            }
                            break;
                        }
                    }
                }
                break;
            }

            case 10: {
                // Add a song to the playlist
                int playlistNumber;
                while (true) {
                    player.displayAllPlaylists();
                    cout << "Choose a playlist to add a song: ";
                    cin >> playlistNumber;
                    if (playlistNumber < 0 || playlistNumber >= player.getNumberOfPlaylists()) {
                        cout << "Invalid playlist number. Try again!" << endl;
                    } else {
                        cout << "Choose a song to add: ";
                        Track* song = player.selectTrack();
                        if (song != NULL){
                            player.playlists[playlistNumber]->addTrack(*song);
                            cout << "Song \"" << song->getTitle() << "\" added succesfully!" << endl;
                            break;
                        }
                        else{
                            cout << "Something went wrong. Could not add a song to the playlist." << endl;
                            break;
                        }
                    }
                }
                break;
            }
            case 11: {
                // Remove a song from the playlist
                int playlistNumber;
                while (true) {
                    player.displayAllPlaylists();
                    cout << "Choose a playlist to remove a song: ";
                    cin >> playlistNumber;
                    if (playlistNumber < 0 || playlistNumber >= player.getNumberOfPlaylists()) {
                        cout << "Invalid playlist number. Try again!" << endl;
                    } else {
                        player.displayAllTracksInPlaylist(*player.playlists[playlistNumber]);
                        cout << "Choose a song to remove: ";
                        int trackNumber;
                        cin >> trackNumber;
                        if (trackNumber < 0 || trackNumber >= player.playlists[playlistNumber]->getNumberOfTracksInPlaylist()) {
                            cout << "Invalid song number!" << endl;
                        } else {
                            player.playlists[playlistNumber]->removeTrack(player.playlists[playlistNumber]->getPlaylistTracks()[trackNumber]);
                            cout << "Song removed from playlist successfully!" << endl;
                            break;
                        }
                    }
                }
                break;
            }
            case 0: {
                // Exit
                cout << "Exiting...\n";
                break;
            }
            default: {
                cout << "Invalid choice!\n";
                break;
            }
        }
    } while (choice != 0);

    return 0;
}
