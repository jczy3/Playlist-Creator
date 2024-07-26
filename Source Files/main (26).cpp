#include <iostream>
#include <vector>
#include "Playlist.h"
using namespace std;

Playlist* plist = new Playlist();                     //playlist object 
void printMenu(string);             //print menu function

int main() {
  string title;
  cout << "Enter playlist's title:" << endl << endl;
  getline(cin,title);
  if(cin.fail()) throw runtime_error("Input failed.");
  printMenu(title);
  return 0;
}

void printMenu(string title){
  char c = ' ';
  cout << endl << title << " PLAYLIST MENU" << endl;
  cout << "a - Add song" << endl;
  cout << "d - Remove song" << endl;
  cout << "c - Change position of song" << endl;
  cout << "s - Output songs by specific artist" << endl;
  cout << "t - Output total time of playlist (in seconds)" << endl;
  cout << "o - Output full playlist" << endl;
  cout << "q - Quit" << endl;
  cout << endl << "Choose an option:" << endl;
  cin >> c;
  cout << endl;
  if(cin.fail()) throw runtime_error("Input failed.");
  while (tolower(c) != 'a' && tolower(c) != 'd' && tolower(c) != 'c' && tolower(c) != 's' && tolower(c) != 't' && tolower(c) != 'o' && tolower(c) != 'q'){                //input validation
    printMenu(title);
    cin >> c;
    if(cin.fail()) throw runtime_error("Input failed.");
  }  
  if (tolower(c) == 'a'){             //using addSong function    
    string ID, song, artist;
    int length;
    cout << "ADD SONG" << endl;
    cout << "Enter song's unique ID:" << endl;
    cin >> ID;
    if(cin.fail()) throw runtime_error("Input failed.");
    cout << "Enter song's name:" << endl;
    cin.ignore();
    getline(cin, song);
    if(cin.fail()) throw runtime_error("Input failed.");
    cout << "Enter artist's name:" << endl;
    getline(cin,artist);
    if(cin.fail()) throw runtime_error("Input failed.");
    cout << "Enter song's length (in seconds):" << endl;
    cin >> length;
    if(cin.fail()) throw runtime_error("Input failed.");
    plist->addSong(ID, song, artist, length);
    printMenu(title);
  }
  if (tolower(c) == 'd'){            //using removeSong function
    string ID;
    cout << "REMOVE SONG" << endl;
    cout << "Enter song's unique ID:" << endl;
    cin.ignore();
    getline(cin,ID);
    if(cin.fail()) throw runtime_error("Input failed.");
    plist->removeSong(ID);
    printMenu(title);
  }
  if (tolower(c) == 'c'){            //using changePos function
    int curPos, newPos;
    cout << "CHANGE POSITION OF SONG" << endl;
    cout << "Enter song's current position:" << endl;
    cin >> curPos;
    if(cin.fail()) throw runtime_error("Input failed.");
    cout << "Enter new position for song:" << endl;
    cin >> newPos;
    if(cin.fail()) throw runtime_error("Input failed.");
    plist->changePos(curPos, newPos);
    printMenu(title);
  }
  if (tolower(c) == 's'){             //using outputSongs function
    string artist;
    cout << "OUTPUT SONGS BY SPECIFIC ARTIST" << endl;
    cout << "Enter artist's name:" << endl;
    cin.ignore();
    getline(cin,artist);
    if(cin.fail()) throw runtime_error("Input failed.");
    cout << endl;
    plist->outputSongs(artist);
    printMenu(title);
  }
  if (tolower(c) == 't'){             //using printTime function
    cout << "OUTPUT TOTAL TIME OF PLAYLIST (IN SECONDS)" << endl;
    plist->printTime();
    printMenu(title);
  }
  if (tolower(c) == 'o'){              //using outputFullPlaylist function
    cout << title << " - OUTPUT FULL PLAYLIST" << endl;
    plist->outputFullPlaylist();
    printMenu(title);
  }
  if (tolower(c) == 'q'){                         //condition to quit out of recursive function printMenu 
    delete plist;                                 //deletes all allocated nodes in playlist destructor
    return;
  }
}