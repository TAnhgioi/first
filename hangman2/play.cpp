#include "play.h"
#include "render.h"

#include<vector>
#include<iostream>
#include<cstdlib>
#include<ctime>
#include <thread>         // std::this_thread::sleep_for
#include <chrono>
#include<set>
using namespace std;


//lay mot tu ngau nhien trong kho tu

vector<string> accessLib(const string& libPath){
    vector<string> wordList;
    string word;
    ifstream wordFile (libPath);
    if (!wordFile.is_open()) {
        throw domain_error("Unable to open file");
    }
    //while ( getline (wordFile, word) ){  // Thong thuong doc tung line.
                                           // Chuong trinh nay cung chay.
    while (wordFile >> word) {  // Nhung voi chuong trinh nay, doc tung word cung duoc
                                // Tuc ca 2 cach doc deu chay.
        wordList.push_back(word);
        //cout << word << '\n';
    }
    wordFile.close();
    return wordList;
}

string summonFromFile(const vector <string>& summon){
    // Khởi tạo hạt giống ngẫu nhiên bằng thời gian hiện tại
    int quantity = summon.size();
    int gacha = rand() % (quantity - 1) + 1;
    string hidden = summon[gacha];
    return hidden;
}

/*for (int i = 0; i < hidden.size(); i++){
    maskedWord = "-";
}*/

//
char getInputCharacter() {
    char ch;
    cin >> ch;
    return tolower(ch);
}

/**void initalize (state& game){
    game.mask = createMask(game.hidden);
    //game.hidden = summonWord(wordLib);

}**/

// tao mat na cho tu bi mat
string createMask(const string& hidden){
    string mask = "";
    for (int i = 0; i < hidden.size(); i++){
        mask += "-";
    }
    return mask;
}

void updateSetGuessed (set <char>& guessed, const char& guess){
    if (guess >= 'a' && guess <= 'z'){
        guessed.insert(guess);
    }
}

bool isGuessHit (const char& guess, const string& hidden){
    for (int i = 0; i < hidden.size(); i++){
        if (guess == hidden[i]){
            return true;
        }
    }
    return false;
}

void updateMask (const char& guess, const string& hidden, string& mask){
    for (int i = 0; i < hidden.size(); i++){
        if (hidden[i] == guess){
            mask[i] = guess;
        }
    }
}

void updateMissedLetters (const char& guess, string& missed){
    missed = missed + " " +guess;
}

void process ( char& guess, state& game, hint& help){
    if (guess == '?'){
        useHint (game, help, guess);
    }
    else if ( isGuessHit(guess, game.hidden) ){
        updateMask(guess, game.hidden, game.mask);
        updateHitChain(game.hitChain);
        game.missChain = 0;
    }
    else {
        updateMissedLetters (guess, game.missed);
        updateMissGuesses(game.missGuesses);
        updateMissChain(game.missChain);
        game.hitChain = 0;
    }
}

void updateMissGuesses (int& missGuesses){
    missGuesses++;
}

void updateMissChain (int& missChain){
    missChain++;
}

void updateHitChain (int& hitChain){
    hitChain++;
}

// hint liet ke mot so chu cai khong co trong tu
set <char> newOutedChars (const string& hidden){
    set <char> outed;
    for (char c = 'a'; c <= 'z'; c++){
        outed.insert(c);
    }
    for (auto c : hidden){
        outed.erase(c);
    }
    return outed;
}

void updateSetOutedChars (const string& missed, set <char>& getOuted){
    for (auto c : missed){
        if (c >= 'a' && c <= 'z'){
            getOuted.erase(c);
        }
    }
}

void updateOutedChars (set <char>& getOuted, string& outed){
    if ( !getOuted.empty() ){
        int gacha = rand() % getOuted.size();
        auto it = getOuted.begin();
        advance(it, gacha);
        outed = outed + " " + *it;
        getOuted.erase(*it);
    }
    //else neu ma het cac chu khong co trong tu thi co can lam gi khong
}

void getTopic (const string& topic){
    TOPIC = topic;
}

void revealLetter(const string& hidden, string& mask, string& inChars){
    int len = hidden.size();
    while (len){
        int gacha = rand() % len;
        if (mask[gacha] == '-'){
            mask[gacha] = hidden[gacha];
            inChars = inChars + " " + mask[gacha];
            len = 0;
        }
    }

}

void useHint (state& game, hint& help, char& guess){
    if (help.turn){
        cout << endl << "Choose one option, type: "
        << endl << " '1' to reveal the word's topic (only one)"
        << endl << " '2' to reveal a random letter"
        << endl << " '3' to reveal a random letter not in word "
        << endl << " '4' to gain +1 chance (available only when chances left < 7)"
        << endl << " '5' to randomly choose an option "
        << endl << "Turns left: " << help.turn << endl;
        guess = getInputCharacter();
        if (guess == '5'){
            int g = rand() % 4 + 1;
            while (g == 1 &&  help.topic == "" || g == 4 && !game.missGuesses){
                g = rand() % 4 + 1;
            }
            guess = g + '0';
            cout << endl << "Picked: " << g;
            this_thread::sleep_for (chrono::milliseconds(2000));
        }
        if (guess == '1'){
            if (help.topic == ""){
                cout << endl << "1 word - 1 Topic only !";
                this_thread::sleep_for (chrono::milliseconds(2000));
                help.turn ++;
            }
            getTopic(help.topic);
            help.topic = "";
        }
        else if (guess == '2'){
            revealLetter(game.hidden, game.mask, help.inChars);
        }
        else if (guess == '3'){
            updateOutedChars (help.getOutedChar, help.outedChars);
        }
        else if (guess == '4'){
            if (game.missGuesses){
                game.missGuesses--;
            }
            else {
                cout << endl << "Unable to gain +1 chance";
                help.turn ++;
                this_thread::sleep_for (chrono::milliseconds(2000));
            }
        }
        else {
            cout << endl << "Unvalid option !";
            this_thread::sleep_for (chrono::milliseconds(1500));
            help.turn++;
        }
        help.turn --;
    }
    else {
        cout << endl << "Out of turns !";
        this_thread::sleep_for (chrono::milliseconds(2000));
    }

}

void newState(state& game, hint& help){
    game.missed = "";
    game.missChain = 0;
    game.hitChain = 0;
    game.mask = createMask(game.hidden);
    game.missGuesses = 0;
    help.outedChars = "";
    help.inChars = "";
    help.turn = game.hidden.size()/2;
    help.getOutedChar.clear();
    help.getOutedChar = newOutedChars (game.hidden);
}
// moi lan doan cho chon 1eff, chon dung dc nhieu diem hon, diem dung de doi lay goi y

