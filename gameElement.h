#ifndef GAME_ELEMENT_H
#define GAME_ELEMENT_H

#include <string>
#include <vector>
#include "country.h"

class GameElement {
public:
    virtual ~GameElement() = default;
    virtual bool checkAnswer(const std::string& answer) const = 0;
    virtual void displayImpl() const = 0;
    virtual int getPoints() const = 0;

    void display() const { displayImpl(); }
};

class Question : public GameElement {
private:
    Country country;
    std::string difficulty;
    std::vector<std::string> options;
    int points;

public:
    Question(const Country& c, const std::string& diff);
    bool checkAnswer(const std::string& answer) const override;
    void displayImpl() const override;
    int getPoints() const override { return points; }
    void generateOptions(const std::vector<Country>& countries);
};

#endif
