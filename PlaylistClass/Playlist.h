#pragma once // #ifndef equivalent

#include <string>

class PlaylistNode {
 private:
  std::string uniqueID; 
  std::string songName;
  std::string artistName;
  int songLength;
  PlaylistNode* nextNodePtr;

  // Node data members represent the attributes of a song. The song's attributes are then placed in a Linkedlist, with each individual node representing a song in a playlist.

  
 public:
  PlaylistNode(); // Default values handled in .cpp file
  // Constructor for Playlist with title, destructor, more
  PlaylistNode(std::string uniqueID, std::string songName, std::string artistName, int songLength) 
  : uniqueID(uniqueID), songName(songName), artistName(artistName), songLength(songLength), 
  nextNodePtr(nullptr) {}
  void InsertAfter(PlaylistNode*); // Insert given parameter node after implicit parameter
  void SetNext(PlaylistNode*); // Set implicit parameter's next to parameter given
  std::string GetID(); // Getters for Node private data members
  std::string GetSongName(); 
  std::string GetArtistName();
  int GetSongLength();
  PlaylistNode* GetNext();
  void PrintPlaylistNode(); // Print all unique data members for Node

  
};

class Playlist {
 private:
    PlaylistNode* head = nullptr;
    PlaylistNode* tail = nullptr; // Empty list should have head and tail be nullptr
 public: // Constructor for playlist with title, more
    void PrintMenu(std::string title);
    Playlist(const Playlist&) = delete; // RULE OF 3: We do not need copy constructor and copy assignment, deleting C++ default functions to avoid shallow copy
    Playlist& operator=(const Playlist&) = delete;
    Playlist() : head(nullptr), tail(nullptr) {} // No value constructor
    ~Playlist(); // Destructor
    Playlist(std::string); // Constructor given title
    void add(std::string, std::string, std::string, int); // Add and remove nodes
    void remove(std::string);
    void outputByName(std::string); // Output all songs by a specific artist given their name
    void outputTotalPlaytime(); // Output total playtime of playlist in seconds
    void outputFullPlaylist(std::string); // Use PrintPlaylistNode() to print the whole playlist cleanly
    void changePositionSong(int, int); // Change the position of a Node from first parameter to second parameter
   



};