#ifndef GAME_H
#define GAME_H

#include <vector>
#include <string>
#include "country.h"
#include "gameElement.h"

class GameException : public std::exception {
private:
    std::string message;
public:
    GameException(const std::string& msg) : message(msg) {}
    const char* what() const noexcept override { return message.c_str(); }
};

class Game {
private:
    std::vector<Country> allCountries;
    std::vector<Question> activeQuestions;
    int score{0};
    size_t currentQuestionIndex{0};
    static int totalGames;

public:
    Game();
    void loadCountries();
    void startNewGame(const std::string& difficulty);
    bool answerQuestion(int index, const std::string& answer);
    const Question& getQuestion(int index) const;
    int getScore() const { return score; }
    size_t getQuestionCount() const { return activeQuestions.size(); }
    bool isGameFinished() const { return currentQuestionIndex >= activeQuestions.size(); }
    static int getTotalGames() { return totalGames; }
};

#endif
