#include <iostream>
#include<stdexcept>
#include<vector>
#include<algorithm>
#include<ctime>

#include  "play.h"
#include "render.h"

using namespace std;

int main(){
    srand((int)time(0));
    string mainPath = "data/libraryPaths.txt";
    vector <string> libCategory;
    try {
        libCategory = accessLib(mainPath);
    } catch (domain_error) {
        cout << endl << "Error: in reading vocabulary file: " << mainPath << endl;
        return 1;
    }
    string categoryPath = summonFromFile(libCategory);

    vector <string> wordLib;
    try {
        wordLib = accessLib(categoryPath);
    } catch (domain_error) {
        cout << endl << "Error: in reading vocabulary file: " << categoryPath << endl;
        return 1;
    }

    state game;
    hint help;
    char guess;
    do{
        help.topic = wordLib[0];
        game.hidden = summonFromFile(wordLib);
        newState (game, help);
        printScreen (game, help);
        while (game.missGuesses < MAX_MISTAKES - 1 && game.mask != game.hidden){
            guess = getInputCharacter();
            process (guess, game, help);
            printScreen (game, help);

        }
        playAnimation (game);
        MAX_MISTAKES = 8;
        TOPIC = "";
        cout << endl << endl
        << "Type '1' to coninue "<< endl
        <<"Type '0' to exit ";
        guess = getInputCharacter();
    } while (guess == '1');
}
