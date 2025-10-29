#pragma once
#include <string>
#include <vector>
#include <fstream>
#include <sstream>
#include <iostream>
#include "SchemaDrawer.h"


class FileReader {
public:
    bool readFile(const std::string& filePath);

    const std::vector<InputDataVector>& getPoints() const { return points; }
    const std::vector<int>& getDelays() const { return delays; }

private:
    std::vector<InputDataVector> points;
    std::vector<int> delays;
};
