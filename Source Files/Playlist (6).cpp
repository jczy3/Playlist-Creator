#include "Playlist.h"
#include <iostream>
using namespace std;

//default constructor
PlaylistNode::PlaylistNode(){
  this->uniqueID = "none";
  this->songName = "none";
  this->artistName = "none";
  this->songLength = 0;
  this->nextNodePtr = nullptr;
}

//parameterized constructor, sets all private variables to the parameters
PlaylistNode::PlaylistNode(const string& ID, const string& song, const string& artist, const int& length){
  this->uniqueID = ID;
  this->songName = song;
  this->artistName = artist;
  this->songLength = length;
}

//inserts a new node after a nodes location
void PlaylistNode::InsertAfter(PlaylistNode* nodeLoc){
  PlaylistNode* tmpNext = this->nextNodePtr;
  this->nextNodePtr = nodeLoc;
  nodeLoc->nextNodePtr = tmpNext; 
}

//sets the next node pointer to the parameter
void PlaylistNode::SetNext(PlaylistNode* nextLoc){
  this->nextNodePtr = nextLoc;
}

//accesses uniqueID
string PlaylistNode::GetID() const{
  return this->uniqueID;
}

//accesses songName
string PlaylistNode::GetSongName() const{
  return this->songName;
}

//accesses aritistName
string PlaylistNode::GetArtistName() const{
  return this->artistName;
}

//accesses songLength
int PlaylistNode::GetSongLength() const{
  return this->songLength;
}

//accesses next node in the list
PlaylistNode* PlaylistNode::GetNext() const{
  return this->nextNodePtr;
}

//prints a node from the playlist 
void PlaylistNode::printPlaylistNode() const{
  cout << "Unique ID: " << GetID() << endl;
  cout << "Song Name: " << GetSongName() << endl;
  cout << "Artist Name: " << GetArtistName() << endl;
  cout << "Song Length (in seconds): " << GetSongLength() << endl << endl;
}

//default constructor for Playlist class
Playlist::Playlist(){
  this->head = nullptr;
  this->tail = nullptr;
}

//destructor for Playlist class
Playlist::~Playlist(){
  PlaylistNode* currNode = this->head->GetNext();
  PlaylistNode* victim;
  while(currNode != tail){    //run loop until curr node is at the tail
    victim = currNode;
    currNode = currNode->GetNext();
    delete victim;
  }
  this->head = nullptr;      //head and tail are part of playlist class, both are not dynamically allocated, so they don't need to be deleted
  this->tail = nullptr;
}

//paramaterized constructor for Playlist class
Playlist::Playlist(PlaylistNode* headptr, PlaylistNode* tailptr){
  this->head = headptr;
  this->tail = tailptr;
}

//function to output the full playlist
void Playlist::outputFullPlaylist() const{
  int nodeNum = 1;
  if (head == nullptr){        //playlist is empty if head is nullptr
    cout << "Playlist is empty" << endl << endl;
    return;
  }
  else{
    PlaylistNode* cur = head;
    while (cur != nullptr){    //iterate until current node reaches tail, prints each playlist node until cur reaches tail
      cout << nodeNum << "." << endl;
      cur->printPlaylistNode();
      cur = cur->GetNext();
      nodeNum++;
    }
  }
}

//function to add songs to the end of the playlist
void Playlist::addSong(const string& ID, const string& song, const string& artist, const int& length){
  PlaylistNode* newPlaylistNode = new PlaylistNode(ID, song, artist, length);      //allocating memory for new node
  if(head == nullptr){                      //create new head and tail if list is initially empty
    head = newPlaylistNode;
    tail = newPlaylistNode;
  }
  else{
    tail->InsertAfter(newPlaylistNode);    //insert new node (song node) after tail
    tail = newPlaylistNode;                //set tail as the new node
  }
  nodeAmt++;
}

//function to remove songs from playlist
void Playlist::removeSong(const string& ID){
  if(this->head == nullptr){               //cannot remove if playlist is empty
    cout << "Cannot remove a song, the playlist is empty." << endl;
    return;
  }
  PlaylistNode* cur = head;
  PlaylistNode* prev = head;
  while (cur != nullptr){
    if (cur->GetID() == ID){    //cur node finds ID from parameter, break out of while 
      cout << "\"" << cur->GetSongName() << "\" removed." << endl << endl;
      break;
    }
    prev = cur;                 //prev node is cur node
    cur = cur->GetNext();       //cur node is moved to the next node
  }
  if (cur != nullptr && cur == head){          //if head is removed, set head to node after head
    head = head->GetNext();
    delete cur;
  }
  else if (cur != nullptr && cur == tail){    //if tail is removed, set tail equal to previous node to tail
    tail = prev;
    prev->SetNext(nullptr);
    delete cur;
  }
  else if (cur != nullptr){                   //points previous node to node after cur node that is deleted
    prev->SetNext(cur->GetNext());
    delete cur;
  }
  nodeAmt--;
}

void Playlist::changePos(const int& curPos, const int& newPos){
  int nodeNum = 1;               //used to find position of curNode and swapNode
  PlaylistNode* curNode = head;
  PlaylistNode* prevCurNode;     //node before curNode
  PlaylistNode* afterCurNode;    //node after curNode
  PlaylistNode* swapNode = head;
  PlaylistNode* prevSwapNode;    //node before swapNode
  PlaylistNode* afterSwapNode;   //node after swapNode
  if(curPos == newPos) return;
  while (curNode != nullptr){    //while loop to get correct node for cur node
    if(nodeNum == curPos) break;
    else{
      prevCurNode = curNode;
      curNode = curNode->GetNext();
      nodeNum++;
    }
  }
  afterCurNode = curNode->GetNext();
  nodeNum = 1;
    while (swapNode != nullptr){    //while loop to get correct node for swap node
    if(nodeNum == newPos) break;
    else{
      prevSwapNode = swapNode;
      swapNode = swapNode->GetNext();
      nodeNum++;
    }
  }
  afterSwapNode = swapNode->GetNext();
  cout << '\"' << curNode->GetSongName() << '\"' << " moved to position " << newPos << endl << endl;
  int n = newPos - curPos;     //n is used to determine whether curNode is either greater or less than swapNode in terms of position
  if(newPos > 1 && newPos < nodeAmt && n > 1 && curNode != head){        //curNode is on the left, swap node on the right, curNode is not the head and newPos is within the bounds of the playlist
    prevCurNode->SetNext(afterCurNode);
    curNode->SetNext(afterSwapNode);
    swapNode->SetNext(curNode);
    return;
  }
  if(newPos > 1 && newPos < nodeAmt && n < 1 && curNode != tail){  //curNode is on the right, swap node on the left, curNode is not the head and newPos is within the bounds of the playlist
    prevSwapNode->SetNext(afterSwapNode);
    swapNode->SetNext(afterCurNode);
    curNode->SetNext(swapNode);
    return;
  }
  if(newPos > 1 && newPos < nodeAmt && n == 1){      //swapping curNode and swapNode directly 1 position from each other, not including head and/or tail
    prevCurNode->SetNext(swapNode);
    swapNode->SetNext(curNode);
    curNode->SetNext(afterSwapNode);
    return;
  }
  if (newPos > 1 && newPos < nodeAmt && n == -1){    //swapping swapNode and curNode directly 1 position from each other, not including head and/or tail
    prevSwapNode->SetNext(curNode);
    curNode->SetNext(swapNode);
    swapNode->SetNext(afterCurNode);
    return;
  }
  if(curNode == head && swapNode != tail && n > 1){       //setting curNode to swapNode's position with curNode being the head, curNode is on the left and swapNode is on the right
    curNode->SetNext(afterSwapNode);
    swapNode->SetNext(curNode);
    head = afterCurNode;
    return;
  }
  if(curNode != tail && swapNode == head && n < 1){       //setting curNode to swapNode's position with swapNode being the head, curNode is on the right and swapNode is on the left
    curNode->SetNext(swapNode);
    prevCurNode->SetNext(afterCurNode);
    head = curNode;
    return;
  }
  if(curNode != head && swapNode == tail && n > 1){       //setting curNode to swapNode's position with swapNode being the tail, curNode is on the left and swapNode is on the right
    prevCurNode->SetNext(afterCurNode);
    swapNode->SetNext(curNode);
    curNode->SetNext(nullptr);
    tail = curNode;
    return;
  }
  if(curNode == tail && swapNode != head && n < 1){       //setting curNode to swapNode's position with curNode being the tail, curNode is on the right and swapNode is on the left
    prevSwapNode->SetNext(curNode);
    curNode->SetNext(swapNode);
    prevCurNode->SetNext(nullptr);
    tail = prevCurNode;
    return;
  }
}

//function used to output songs by specific artist
void Playlist::outputSongs(const string& artist){
  int nodeNum = 1;
  PlaylistNode* curNode = head;
  while (curNode != nullptr){                  //iterate from head to tail
    if(curNode->GetArtistName() == artist){    //print playlist node if curNode's artist is equal to artist received by parameter
      cout << nodeNum << "." << endl;
      curNode->printPlaylistNode();
    }
    curNode = curNode->GetNext();
    nodeNum++;                                 //getting node positions
  }
}

//function used to get total time of playlist
void Playlist::printTime() const{
  PlaylistNode* curNode = head;
  int time = 0;
  while (curNode != nullptr){                  //iterate from head to tail
    time += curNode->GetSongLength();          //add each song's length to time
    curNode = curNode->GetNext();
  }
  cout << "Total time: " << time << " seconds" << endl << endl; 
}