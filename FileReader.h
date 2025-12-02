// La classe FileReader permet de lire des fichiers contenant des données de signaux
// et des délais associés. Elle stocke les points d'entrée dans un vecteur de structures
// InputDataVector et les délais dans un vecteur d'entiers. 
// La méthode readFile() lit le fichier et remplit ces vecteurs, tandis que
// getPoints() et getDelays() permettent d'accéder aux données lues.


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
