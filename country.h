#ifndef COUNTRY_H
#define COUNTRY_H

#include <string>

class Country {
private:
    std::string name;
    std::string capital;
    std::string difficulty;

public:
    Country(const std::string& n, const std::string& c, const std::string& d);

    const std::string& getName() const;
    const std::string& getCapital() const;
    const std::string& getDifficulty() const;
};

#endif
