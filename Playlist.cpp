#include "Playlist.h"


#include <iostream>
#include <string>


Playlist::Playlist(std::string title) {
  head = nullptr;  // Initalize an empty list.
  tail = nullptr;
}
/* The destructor iterates through all Nodes in the list, create a new pointer to the data, 
and delete that new pointer until the list is empty. */
Playlist::~Playlist() {
  PlaylistNode *curr = head;
  while(curr != nullptr) {
    PlaylistNode* toDelete = curr;
    curr = curr->GetNext();
    delete toDelete;
  }
}


void Playlist::PrintMenu(std::string title) {  // PrintMenu() is called everytime the user is prompted for input.
  std::cout << title << " PLAYLIST MENU" << std::endl;

  std::cout << "a - Add song" << std::endl;
  std::cout << "d - Remove song" << std::endl;
  std::cout << "c - Change position of song" << std::endl;
  std::cout << "s - Output songs by specific artist" << std::endl;
  std::cout << "t - Output total time of playlist (in seconds)" << std::endl;
  std::cout << "o - Output full playlist" << std::endl;
  std::cout << "q - Quit" << std::endl << std::endl;


  std::cout << "Choose an option:" << std::endl;
}

/* remove() removes a Node given a song's ID.
If there are multiple Nodes with that ID, all are removed.*/
void Playlist::remove(std::string uniqueID) {
  if(head == nullptr) {  // Edge case, empty list returns without execution as there is nothing to remove
    return;
  }
  if(head == tail) {  // Edge case, if one Node in list, checks the one Node before returning
    if(head->GetID() == uniqueID) {
      std::cout << "\"" << head->GetSongName() << "\"" << " removed" << std::endl;
      delete head;
      head = nullptr;
    }
  } else {  // Curr and prev are used to iterate through Linkedlist until removal spot is found.
    PlaylistNode* curr = head->GetNext();
    PlaylistNode* prev = head;
    while(curr != nullptr) {
      if(curr->GetID() == uniqueID) {  // As long as curr is valid, check parameter ID against iteration ID
        std::string removedSong = curr->GetSongName();  // Save curr's song name before we delete it, to print the statement later
        PlaylistNode* toDelete = curr;
        curr = curr->GetNext();  // Follow same logic as in destructor
        delete toDelete;

        std::cout << "\"" << removedSong << "\"" << " removed." << std::endl << std::endl;
        prev->SetNext(curr);
      } else {
        curr = curr->GetNext();  // If ID does not match keep going
        prev = prev->GetNext();
      }
    }
  }
}

/* outputByName() takes an artist name as input and outputs all songs with that artist's name */
void Playlist::outputByName(std::string artistName) {
  PlaylistNode* curr = head;
  int count = 1;  // This variable is updated each time a song is found
  while(curr != nullptr) {
    // If artist name matches, count is incremented and printed, and the Node's data is printed.
    if(curr->GetArtistName() == artistName) {
      std::cout << count << "." << std::endl;
      curr->PrintPlaylistNode();
      std::cout << std::endl;
    }
    count++;
    curr = curr->GetNext();
  }
}

// add() takes all Node data as input and creates a new Node at the back of the list.
void Playlist::add(std::string uniqueID, std::string songName, std::string artistName, int songLength) {
  PlaylistNode* newSong = new PlaylistNode(uniqueID, songName, artistName, songLength);

  if(head == nullptr) {  // Edge case, if list is empty, add one element and update head and tail accordingly
    head = tail = newSong;
  } else {
    tail->SetNext(newSong);
    tail = newSong;
  }
}

// outputFullPlaylist() takes a title as parameter and prints Node data through the whole list.
void Playlist::outputFullPlaylist(std::string title) {
  std::cout << title << " - OUTPUT FULL PLAYLIST" << std::endl;
  if(head == nullptr) {  // Edge case, if playlist is empty output to user and return
    std::cout << "Playlist is empty" << std::endl << std::endl;
    return;
  }

  int count = 1;  // Starts at 1 incremented for every song in playlist
  PlaylistNode *curr = head;
  while(curr != nullptr) {  // PrintPlaylistNode() is called for every Node until nullptr (end)
    std::cout << count << "." << std::endl;
    curr->PrintPlaylistNode();
    std::cout << std::endl;
    count++;
    curr = curr->GetNext();
  }
}

void Playlist::outputTotalPlaytime() {  // outputTotalPlayTime() takes no parameter and outputs total time in seconds.
  PlaylistNode* curr = head;
  int totalSeconds = 0;
  while(curr != nullptr) {
    totalSeconds += curr->GetSongLength();  // Node data is accessed and incremented
    curr = curr->GetNext();
  }
  std::cout << "OUTPUT TOTAL TIME OF PLAYLIST (IN SECONDS)" << std::endl;
  std::cout << "Total time: " << totalSeconds << " seconds" << std::endl << std::endl;
}


PlaylistNode::PlaylistNode()  // No parameter constructor makes an empty Node
  : uniqueID("none"), songName("none"), artistName("none"), songLength(0), nextNodePtr(nullptr) {
}

// changePositionSong() takes two parameters, current and new position, and moves the song at current position to new position.
void Playlist::changePositionSong(int currentPosition, int newPosition) {
  if(head == nullptr || head == tail || currentPosition == newPosition) {
    return;  // Edge case(s), if the list is empty or has one element, or if both parameters are the same, do nothing
  }
  if(newPosition < 1) {
    newPosition = 1;  // The new position cannot be negative. The first place it can be is the head. Set user input accordingly
  }
  int count = 1;  // Count is set to 1 so we can track the positions of nodes by integers, necessary because parameters are integers
  PlaylistNode* curr = head;
  PlaylistNode* prev = nullptr;

  while(curr != nullptr && count < currentPosition) {
    count++;
    prev = curr;
    curr = curr->GetNext();
  }

  if(curr == nullptr) {
    return;  // Defensive case to avoid memory leaks
  }

  if(prev != nullptr) {
    /* The function has stopped iterating and has found the Node at currentPosition.
    Unlink the node by unlinking its next pointer */
    prev->SetNext(curr->GetNext());
  } else {
    head = curr->GetNext();  // If prev is nullptr then the curr is the head. Unlink the Node.
  }
  if(curr == tail) {  // If curr is tail then after insertion we need to update tail
    tail = prev;
  }
  // Node is removed, pointer is stored in curr.


  count = 1;  // Reset count to iterate to newPosition
  PlaylistNode* newPrev = nullptr;
  PlaylistNode* newCurr = head;
  while(newCurr != nullptr && count < newPosition) {
    count++;
    newPrev = newCurr;
    newCurr = newCurr->GetNext();
  }

  if(count == 1) {  // If newPosition is 1 stick curr at the head
    curr->SetNext(head);
    head = curr;
  } else {  // our new "previous" location will be just behind newPosition
    newPrev->InsertAfter(curr);
  }
  // update tail if at end
  if(curr->GetNext() == nullptr) {
    tail = curr;
  }


  std::cout << "\"" << curr->GetSongName() << "\"" << " moved to position " << newPosition << std::endl << std::endl;
}

void PlaylistNode::SetNext(PlaylistNode* afterNode) {
  nextNodePtr = afterNode;  // updates the next pointer for any given Node
}

void PlaylistNode::InsertAfter(PlaylistNode* nodeAfter) {
  nodeAfter->SetNext(this->nextNodePtr);  // The inserted node's next pointer is updated
  this->SetNext(nodeAfter);
  // insert nodeAfter between the implicit parameter and implicit parameter's nextNodePtr
}

int PlaylistNode::GetSongLength() {  // Getters for Node data
  return songLength;
}

std::string PlaylistNode::GetArtistName() {
  return artistName;
}

std::string PlaylistNode::GetID() {
  return uniqueID;
}

PlaylistNode* PlaylistNode::GetNext() {
    return nextNodePtr;
}

std::string PlaylistNode::GetSongName() {
  return songName;
}

void PlaylistNode::PrintPlaylistNode() {  // Prints a Node's data
  std::cout << "Unique ID: " << uniqueID << std::endl;
  std::cout << "Song Name: " << songName << std::endl;
  std::cout << "Artist Name: " << artistName << std::endl;
  std::cout << "Song Length (in seconds): " << songLength << std::endl;
}
