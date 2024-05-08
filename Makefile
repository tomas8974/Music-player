all: MusicPlayer run


MusicPlayer: Player.o Track.o Main.o Playlist.o
	 g++ -o MusicPlayer Player.o Track.o Main.o Playlist.o -lwinmm
	 
Player.o: Player.cpp
	g++ -c Player.cpp

Track.o: Track.cpp
	g++ -c Track.cpp

Main.o: Main.cpp
	g++ -c Main.cpp

Playlist.o: Playlist.cpp
	g++ -c Playlist.cpp

run: MusicPlayer
	./MusicPlayer

clean:
	del /F /Q *.o MusicPlayer.exe

rebuild: clean all