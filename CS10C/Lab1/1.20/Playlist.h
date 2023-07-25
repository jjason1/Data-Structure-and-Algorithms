#pragma once

#include <iostream>
#include <string>
using namespace std;

class PlaylistNode
{
private:
    string uniqueId;
    string songName;
    string artistName;
    int songLength;
    PlaylistNode *nextNodePtr;

public:
    PlaylistNode();
    PlaylistNode(const string &, const string &, const string &, int);
    void InsertAfter(PlaylistNode *);
    void SetNext(PlaylistNode *);
    const string &GetID() const;
    const string &GetSongName() const;
    const string &GetArtistName() const;
    int GetSongLength() const;
    PlaylistNode *GetNext() const;
    void PrintPlaylistNode() const;
};

class Playlist
{
private:
    PlaylistNode *head;
    PlaylistNode *tail;

public:
    Playlist();
    ~Playlist();
    Playlist(const Playlist &);
    Playlist & operator=(const Playlist &);
    void print(string) const;
    void addSong(PlaylistNode *);
    PlaylistNode *removeSong(const string &);
    void changePos(int, int);
    void printByArtist(const string &) const;
    int totalTime() const;
};
