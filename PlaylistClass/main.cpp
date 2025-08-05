#include <iostream>
#include <limits>
#include <string>

#include "Playlist.h"

// Using std instead of namespace to avoid invalid variable names by accident
using std::cin;
using std::cout;
using std::endl;
using std::getline;
using std::numeric_limits;
using std::string;
using std::streamsize;

/* void PrintMenu(const string& title) {
  cout << title << endl;
} */
// PrintMenu() function handled in Playlist.cpp

int main() {
  string title;
  string command;

  // Prompt for and read the title for the playlist (may contain spaces)
  cout << "Enter playlist's title:" << endl;
  cout << endl;
  getline(cin, title);
  if(!cin.good()) {
    throw std::runtime_error("Title input error");
  }

  // Build a playlist object with this title
  Playlist playlist(title);
  playlist.PrintMenu(title);  // Print intial menu

  // Read the next "token".  Will stop on EOF or a q
  while (cin >> command and command != "q") {
    // ignore characters until we get to a newline or end-of-file
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    if(!cin.good()) {
      throw std::runtime_error("Print Menu command input error");
    }
    if (command == "a") {
        string uniqueID;  // Define ID, name, artist Name, length, prompt for input and add to class object
        string songName;
        string artistName;
        int songLength;
        cout << "ADD SONG" << endl;
        cout << "Enter song's unique ID:" << endl;
        getline(cin, uniqueID);
        if(!cin.good()) {
          throw std::runtime_error("ID input error");
        }
        cout << "Enter song's name:" << endl;
        getline(cin, songName);
        if(!cin.good()) {
          throw std::runtime_error("Song name input error");
        }
        cout << "Enter artist's name:" << endl;
        getline(cin, artistName);
        if(!cin.good()) {
          throw std::runtime_error("Artist name input error");
        }
        cout << "Enter song's length (in seconds):" << endl;
        cin >> songLength;
        if(!cin.good()) {
          throw std::runtime_error("Song length input error");
        }
        cout << endl;
        playlist.add(uniqueID, songName, artistName, songLength);
    } else if (command == "d") {
      std::cout << "REMOVE SONG" << std::endl;  // Prompt for ID of song to remove and call function
      std::cout << "Enter song's unique ID:" << std::endl;
      std::string uniqueID;
      cin >> uniqueID;
      if(!cin.good()) {
        throw std::runtime_error("Removal ID input error");
      }
      playlist.remove(uniqueID);
    } else if (command == "c") {
      int currPos;
      int newPos;  // Change Position takes two user-defined parameters
      std::cout << "CHANGE POSITION OF SONG" << std::endl;
      std::cout << "Enter song's current position:" << std::endl;
      cin >> currPos;
      if(!cin.good()) {
        throw std::runtime_error("Current Position input error");
      }
      std::cout << "Enter new position for song:" << std::endl;
      cin >> newPos;
      if(!cin.good()) {
        throw std::runtime_error("New Position input error");
      }
      playlist.changePositionSong(currPos, newPos);
    } else if (command == "s") {
      std::cout << "OUTPUT SONGS BY SPECIFIC ARTIST" << std::endl;  // Take user input string and output songs by that artist
      std::string artistName;
      std::cout << "Enter artist's name:" << std::endl << std::endl;
      getline(cin, artistName);
      if(cin.fail()) {
        throw std::runtime_error("Artist Name input error");
      }
      playlist.outputByName(artistName);
    } else if (command == "t") {
      playlist.outputTotalPlaytime();  // outputTotalPlaytime() needs no parameters
    } else if (command == "o") {
      playlist.outputFullPlaylist(title);  // outputFullPlaylist() needs a title parameter to print the name of the playlist
    }
    // Repeat the menu and wait for another command
    playlist.PrintMenu(title);
  }


  return 0;  // return 0 -> no problem exit
}
