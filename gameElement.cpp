#include "gameElement.h"
#include <iostream>
#include <random>
#include <algorithm>

Question::Question(const Country& c, const std::string& diff)
    : country(c), difficulty(diff) {
    points = (difficulty == "Usor" ? 5 :
             difficulty == "Mediu" ? 10 :
             difficulty == "Greu" ? 15 : 20);
}

void Question::displayImpl() const {
    std::cout << "Care este capitala " << country.getName() << "?\n\n";
    char option = 'A';
    for(const auto& opt : options) {
        std::cout << option << ") " << opt << "\n";
        ++option;
    }
    std::cout << std::endl;
}

bool Question::checkAnswer(const std::string& answer) const {
    return answer == country.getCapital();
}

void Question::generateOptions(const std::vector<Country>& countries) {
    options.clear();
    options.push_back(country.getCapital());

    std::vector<std::string> allCapitals;
    for(const auto& c : countries) {
        if(c.getCapital() != country.getCapital()) {
            allCapitals.push_back(c.getCapital());
        }
    }

    std::random_device rd;
    std::mt19937 gen(rd());
    std::shuffle(allCapitals.begin(), allCapitals.end(), gen);

    for(size_t i = 0; i < 3 && i < allCapitals.size(); ++i) {
        options.push_back(allCapitals[i]);
    }

    std::shuffle(options.begin(), options.end(), gen);
}
