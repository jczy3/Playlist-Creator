#ifndef PLAYLIST_H
#define PLAYLIST_H

#include <iostream>
#include <string>
using namespace std;

class PlaylistNode{    //class for playlist nodes
private:               //private data members for a playlist node
string uniqueID;       
string songName;       
string artistName;     
int songLength;        
PlaylistNode* nextNodePtr;

public:
PlaylistNode();    //default constructor
PlaylistNode(const string&, const string&, const string&, const int&);    //paramaterized constructor
void InsertAfter(PlaylistNode*);              //playlist node functions
void SetNext(PlaylistNode*);
string GetID() const;
string GetSongName() const;
string GetArtistName() const;
int GetSongLength() const;
PlaylistNode* GetNext() const;
void printPlaylistNode() const;
};

class Playlist{      //class playlist object, used to create playlist functions and to store the head and tail of the playlist
private:
PlaylistNode* head;
PlaylistNode* tail;
int nodeAmt = 0;     //counts amount of nodes in linked list, utilized in changePos function

public:
Playlist();          
~Playlist();         
Playlist(PlaylistNode*,PlaylistNode*);                      //paramaterized constructor
Playlist (const Playlist&) = delete;                        //copy constructor
Playlist& operator = (const Playlist& other) = delete;      //assignment operator
void outputFullPlaylist() const;                            //playlist functions
void addSong(const string&, const string&, const string&, const int&);
void removeSong(const string&);
void changePos(const int&, const int&);
void outputSongs(const string&);
void printTime() const;
};

#endif