#include "game.h"
#include <iostream>
#include <limits>

void clearInputBuffer() {
    std::cin.clear();
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
}

int main() {
    try {
        Game game;
        game.loadCountries();

        std::string difficulty;
        std::cout << "Alege dificultatea (Usor/Mediu/Greu/Expert): ";
        std::getline(std::cin, difficulty);

        game.startNewGame(difficulty);

        for(size_t i = 0; i < game.getQuestionCount(); ++i) {
            const Question& question = game.getQuestion(i);
            question.display();

            std::string answer;
            std::cout << "Raspunsul tau (A/B/C/D): ";
            std::getline(std::cin, answer);

            if(game.answerQuestion(i, answer)) {
                std::cout << "Corect! Scor: " << game.getScore() << "\n\n";
            } else {
                std::cout << "Gresit! Scor: " << game.getScore() << "\n\n";
            }
        }

        std::cout << "Joc terminat! Scor final: " << game.getScore() << "\n";
        std::cout << "Numar total de jocuri jucate: " << Game::getTotalGames() << "\n";

    } catch(const GameException& e) {
        std::cerr << "Eroare: " << e.what() << std::endl;
        return 1;
    } catch(const std::exception& e) {
        std::cerr << "Eroare neasteptata: " << e.what() << std::endl;
        return 1;
    }

    return 0;
}
