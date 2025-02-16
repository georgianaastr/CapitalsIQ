#include "game.h"
#include <fstream>
#include <algorithm>
#include <random>
#include <iostream>
#include <set>

int Game::totalGames = 0;

Game::Game() {
    ++totalGames;
}

void Game::loadCountries() {
    std::ifstream file("countries.txt");
    if(!file) {
        throw GameException("Could not open countries file");
    }

    std::string difficulty, name, capital;
    std::set<std::string> uniqueCountries;

    while(std::getline(file, difficulty, '|')) {
        std::getline(file, name, '|');
        std::getline(file, capital);

        capital = capital.substr(0, capital.find_last_not_of("\r\n") + 1);

        if(uniqueCountries.insert(name).second) {
            allCountries.emplace_back(name, capital, difficulty);
        }
    }
}

void Game::startNewGame(const std::string& difficulty) {
    if(difficulty != "Usor" && difficulty != "Mediu" &&
       difficulty != "Greu" && difficulty != "Expert") {
        throw GameException("Invalid difficulty level");
    }

    activeQuestions.clear();
    score = 0;
    currentQuestionIndex = 0;

    std::vector<Country> difficultyCountries;
    for(const auto& country : allCountries) {
        if(country.getDifficulty() == difficulty) {
            difficultyCountries.push_back(country);
        }
    }

    std::random_device rd;
    std::mt19937 gen(rd());
    std::shuffle(difficultyCountries.begin(), difficultyCountries.end(), gen);

    int numQuestions = std::min(10, static_cast<int>(difficultyCountries.size()));
    for(int i = 0; i < numQuestions; ++i) {
        Question q(difficultyCountries[i], difficulty);
        q.generateOptions(allCountries);
        activeQuestions.push_back(q);
    }
}

bool Game::answerQuestion(int index, const std::string& answer) {
    if(index < 0 || static_cast<size_t>(index) >= activeQuestions.size()) {
        throw GameException("Invalid question index");
    }

    if(activeQuestions[index].checkAnswer(answer)) {
        score += activeQuestions[index].getPoints();
        return true;
    }
    return false;
}

const Question& Game::getQuestion(int index) const {
    if(index < 0 || static_cast<size_t>(index) >= activeQuestions.size()) {
        throw GameException("Invalid question index");
    }
    return activeQuestions[index];
}
