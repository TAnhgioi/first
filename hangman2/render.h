#ifndef RENDER_H
#define RENDER_H
#include "play.h"
#pragma once
using namespace std;

extern int MAX_MISTAKES;
extern string TOPIC;

void printStats(const state& game);
void printScreen(const state& game, const hint& help);
void playAnimation (const state& game);
void showOutedChars (const string& outed);
void showInChars (const string& inChars);
void showTopic (const string& topic);
void showAchieve (const int& missChain, const int& hitChain);
string getBadAchieve ();
string getGoodAchieve();

#endif // RENDER_H
