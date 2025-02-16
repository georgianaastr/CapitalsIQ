#include "country.h"

Country::Country(const std::string& n, const std::string& c, const std::string& d)
    : name(n), capital(c), difficulty(d) {}

const std::string& Country::getName() const { return name; }
const std::string& Country::getCapital() const { return capital; }
const std::string& Country::getDifficulty() const { return difficulty; }
