#include <iostream>
#include <string>
#include "Playlist.h"
using namespace std;

/*Global Playlist pointer so it can be used in main and the PrintMenu function*/
Playlist *playlist;
void PrintMenu(string);

int main()
{
    string playlistTitle;

    cout << "Enter playlist's title:" << endl;
    getline(cin, playlistTitle);
    cout << endl;

    // cout << playlistTitle << endl;
    playlist = new Playlist();

    PrintMenu(playlistTitle);

    return 0;
}

/*The print menu function will print a menu with a list of commands they can do to the playlist. This function that will call itslef mutliple times until q is inputted.
* The user will first be prompted the menu and asked to choose a selection they want to do. Then, with an if-else statement, the function will decide which code to call.
*/
void PrintMenu(string playlistTitle)
{
    char userInput;

    cout << playlistTitle << " PLAYLIST MENU" << endl;
    cout << "a - Add song" << endl;
    cout << "d - Remove song" << endl;
    cout << "c - Change position of song" << endl;
    cout << "s - Output songs by specific artist" << endl;
    cout << "t - Output total time of playlist (in seconds)" << endl;
    cout << "o - Output full playlist" << endl;
    cout << "q - Quit" << endl;
    cout << endl;
    cout << "Choose an option:" << endl;

    cin >> userInput;

    if (userInput == 'a')
    {

        string uniqueID, songName, artistName;
        int songLength;

        cout << "ADD SONG" << endl;

        cout << "Enter song's unique ID:" << endl;
        cin.ignore();
        getline(cin, uniqueID);

        cout << "Enter song's name:" << endl;
        getline(cin, songName);

        cout << "Enter artist's name:" << endl;
        getline(cin, artistName);

        cout << "Enter song's length (in seconds):" << endl;
        cin >> songLength;

        PlaylistNode *newNode = new PlaylistNode(uniqueID, songName, artistName, songLength);
        playlist->addSong(newNode);
        cout << endl;
        PrintMenu(playlistTitle);
    }
    else if (userInput == 'd')
    {
        string id;

        cout << "REMOVE SONG" << endl;
        cout << "Enter song's unique ID:";
        cin.ignore();
        getline(cin, id);
        cout << endl;

        playlist->removeSong(id);
        cout << endl;
        PrintMenu(playlistTitle);
    }
    else if (userInput == 'o')
    {
        cout << playlistTitle << " - OUTPUT FULL PLAYLIST" << endl;
        playlist->print(playlistTitle);
        PrintMenu(playlistTitle);
    }
    else if (userInput == 'c')
    {
        int currentPostition, newPostition;

        cout << "CHANGE POSITION OF SONG" << endl;
        cout << "Enter song's current position:" << endl;
        cin >> currentPostition;
        cout << "Enter new position for song:" << endl;
        cin >> newPostition;

        playlist->changePos(currentPostition, newPostition);
        cout << endl;
        PrintMenu(playlistTitle);
    }
    else if (userInput == 's')
    {
        string artistName;

        cout << "OUTPUT SONGS BY SPECIFIC ARTIST" << endl;
        cout << "Enter artist's name:" << endl;
        cin.ignore();
        getline(cin, artistName);

        cout << endl;

        playlist->printByArtist(artistName);
        PrintMenu(playlistTitle);
    }
    else if (userInput == 't')
    {
        cout << "OUTPUT TOTAL TIME OF PLAYLIST (IN SECONDS)" << endl;
        cout << "Total time: " << playlist->totalTime() << " seconds" << endl;
        cout << endl;
        PrintMenu(playlistTitle);
    }
    else if (userInput == 'q')
    {
    }
    else
    {
        PrintMenu(playlistTitle);
    }
}