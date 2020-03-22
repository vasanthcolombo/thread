#include <iostream>
#include <algorithm>

enum Dice {
    paper = 0,
    rock  = 1,
    scissors = 2
};

enum Winner {
    player,
    computer,
    draw
};
// rows are the outcome of player
// columns are the outcome of computer
Winner theWinner[3][3] = {
        {draw, player, computer},
        {computer, draw, player},
        {player, computer, draw}
};

bool is_number(std::string& sRounds) {
    return !sRounds.empty() && std::all_of(sRounds.begin(), sRounds.end(), [](char c) {return std::isdigit(c);});
}

void getUserInput(std::string& user, int& rounds) {
    std::string sRounds;
    std::cout << "What's your name?" << std::endl;
    getline(std::cin, user);

    std::cout << "How many rounds would you like to play?? " << std::endl;
    getline(std::cin, sRounds);
    if (!is_number(sRounds)) {
        std::cout << "Invalid number" << std::endl;
        exit(EXIT_FAILURE);
    }
    rounds = stoi(sRounds);
}

int main() {

    std::string sName;
    int iRounds;
    std::cout << "****** Welcome to Paper Scissors Rock ********" << std::endl;

    getUserInput(sName, iRounds);

    //DEBUG
    std::cout << "user input : " << iRounds << std::endl;
    //
    for (int i = 0; i < iRounds; ++i) {

    }

}