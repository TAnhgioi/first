#include <iostream>
#include <thread>         // std::this_thread::sleep_for
#include <chrono>         // std::chrono::seconds
#include "render.h"
#include "play.h"

using std::string;
using std::endl;
using std::cout;

int MAX_MISTAKES = 8;
string TOPIC = "";

string getDrawing(const int i)
{
    static int LEN = 8;
    static string FIGURES[] = {
                "   -------------    \n"
                "   |                \n"
                "   |                \n"
                "   |                \n"
                "   |                \n"
                "   |     \n"
                " -----   \n",
                "   -------------    \n"
                "   |           |    \n"
                "   |                \n"
                "   |                \n"
                "   |                \n"
                "   |     \n"
                " -----   \n",
                "   -------------    \n"
                "   |           |    \n"
                "   |           O    \n"
                "   |                \n"
                "   |                \n"
                "   |     \n"
                " -----   \n",
                "   -------------    \n"
                "   |           |    \n"
                "   |           O    \n"
                "   |           |    \n"
                "   |                \n"
                "   |     \n"
                " -----   \n",
                "   -------------    \n"
                "   |           |    \n"
                "   |           O    \n"
                "   |          /|    \n"
                "   |                \n"
                "   |     \n"
                " -----   \n",
                "   -------------    \n"
                "   |           |    \n"
                "   |           O    \n"
                "   |          /|\\  \n"
                "   |                \n"
                "   |     \n"
                " -----   \n",
                "   -------------    \n"
                "   |           |    \n"
                "   |           O    \n"
                "   |          /|\\  \n"
                "   |          /     \n"
                "   |     \n"
                " -----   \n",
                "   -------------    \n"
                "   |           |    \n"
                "   |           O    \n"
                "   |          /|\\  \n"
                "   |          / \\  \n"
                "   |     \n"
                " -----   \n",
    };
    return FIGURES[i % LEN];
}

string getNextHangman()
{
    static int LEN = 4;
    static string FIGURES[] = {
          "   ------------+    \n"
          "   |          /     \n"
          "   |         O      \n"
          "   |        /|\\    \n"
          "   |        / \\    \n"
          "   |        \n"
          " -----      \n" ,
          "   ------------+     \n"
          "   |           |     \n"
          "   |           O     \n"
          "   |          /|\\   \n"
          "   |          / \\   \n"
          "   |        \n"
          " -----      \n",
          "   ------------+      \n"
          "   |            \\    \n"
          "   |            O     \n"
          "   |           /|\\   \n"
          "   |           / \\   \n"
          "   |      \n"
          " -----    \n",
          "   ------------+     \n"
          "   |           |     \n"
          "   |           O     \n"
          "   |          /|\\   \n"
          "   |          / \\   \n"
          "   |        \n"
          " -----      \n",
          };
    static int i = 0;
    i = (i + 1) % LEN;

    return FIGURES[i];
}

string getNextStandingman()
{
    static int LEN = 8;
    static string FIGURES[] = {
          "     O     \n"
          "    /|\\   \n"
          "    | |    \n",
          "     O     \n"
          "    /|\\   \n"
          "    / \\   \n",
          "   __O__   \n"
          "     |     \n"
          "    / \\   \n",
          "    \\O/   \n"
          "     |     \n"
          "    / \\   \n",
          "   __O__   \n"
          "     |     \n"
          "    / \\   \n",
          "     O     \n"
          "    /|\\   \n"
          "    / \\   \n" ,
          "    O     \n"
          "    /|\\   \n"
          "    / \\   \n" ,
          "     O     \n"
          "    /|\\   \n"
          "    / \\   \n" ,
          "      O     \n"
          "    /|\\   \n"
          "    / \\   \n" ,
          "     O     \n"
          "    /|\\   \n"
          "    / \\   \n" ,
          };
    static int i = 0;
    i = (i + 1) % LEN;

    return FIGURES[i];
}

string getGoodAchieve (){
    static vector <string> good = {"Dominating !", "Immortal !", "Legendary !", "Godlike !", "Onslaught !"};
    int g = rand() % good.size();
    return good[g];
}

string getBadAchieve (){
    static vector <string> bad = {"Dominated !", "Defenseless !", "Crushed !", "Demolished !", "Destroyed !"};
    //static int g = rand() % sizeof(bad);
    int g = rand()% bad.size();
    return bad[g];
}

void showOutedChars (const string& outed){
    cout << endl << " 3 - Hint (Not in word letters): " << outed
    << endl << endl;
}

void showInChars (const string& inChars){
    cout << endl << " 2 - Hint (Revealed letters in word): " << inChars;
}

void showTopic (const string& topic){
    cout << endl << " 1 - Hint, This word is related to " << topic;
}

void showAchieve (const int& missChain, const int& hitChain){
    if (missChain >= 2){
        cout << endl << getBadAchieve() << endl;
    }
    else if (hitChain >= 2){
        cout << endl << getGoodAchieve() << endl;
    }

}

//void showHint

void printStats(const state& game){
        string secret = game.hidden;

        cout << endl << "Current word:  " << game.mask;
       // cout << endl << "Correct guesses: " << correctChars;
        cout << "                          Wrong guesses: " << game.missed;

        cout << endl << "Chances left:  " << MAX_MISTAKES - 1 - game.missGuesses;
        if (game.mask == secret) {
            cout << endl << "Well done :D   The word is: " << secret << endl;
        } else if (game.missGuesses == MAX_MISTAKES-1) {
            cout << endl << "You lose :(   The word is: " << secret << endl;
        } else {
            cout << endl << "Choose a character (type '?' to get help): ";
        }
}

void printScreen(//const string& hiddenWord, const string& maskedWord,
                 //const int incorrectGuess, const string& guessed
                 const state& game, const hint& help)
{
    system("cls");
    cout << getDrawing(game.missGuesses);
    showTopic(TOPIC);
    showInChars (help.inChars);
    showOutedChars (help.outedChars);
    showAchieve(game.missChain, game.hitChain);
    printStats(game);

}

void playAnimation(const state& game)
{
    std::this_thread::sleep_for (std::chrono::milliseconds(3000));
    for (int i = 0; i < 10; ++i) {
        for (int i = 0; i < 30; ++i) cout << endl;

        if (game.hidden == game.mask) {
            cout << getNextStandingman();
        } else if (game.missGuesses == MAX_MISTAKES-1) {
            cout << getNextHangman();
        }
        //printStats(game);

        std::this_thread::sleep_for (std::chrono::milliseconds(1000/2));
    }
}
