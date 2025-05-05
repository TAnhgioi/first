#ifndef PLAY_H
#define PLAY_H

#include<iostream>
#include<fstream>
#include<vector>
#include<set>
using namespace std;

struct state{
    string mask;
    string missed;
    string hidden;
    int hitChain;
    int missChain;
    int missGuesses;
};

struct hint {
    set <char> getOutedChar;
    string outedChars;
    string topic;
    string inChars;
    int turn;
};

//Initialize
vector <string> accessLib (const string& libPath);
string summonFromFile(const vector <string>& summon); // sinh tu
string createMask(const string& hidden);

// Operate
char getInputCharacter();

bool isGuessHit (const char& guess, const string& hidden);

void newState(state& game, hint& help);
void updateMask(const char& guess, const string& hidden, string& mask);
void updateMissedLetters(const char& guess, string& missed);
void updateMissGuesses (int &missGuesses);
void updateMissChain (int& missChain);
void updateHitChain (int& hitChain);
void process ( char& guess, state& game, hint& help);

// Hint
void useHint(state& game, hint& help, char& guess);
void getTopic (const string& topic);
void updateOutedChars (set <char>& getOuted, string& outed);
void revealLetter(const string& hidden, string& mask, string& inChars);

set <char> newOutedChars (const string& hidden);
void updateSetOutedChars (const string& missed, set <char>& outed);
#endif // PLAY_H
