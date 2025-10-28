#include "pch.h"
#include "FileReader.h"



bool FileReader::readFile(const std::string& filePath)
{
    std::ifstream file(filePath);
    if (!file.is_open()) {
        std::cerr << "Erreur : impossible d'ouvrir le fichier " << filePath << std::endl;
        return false;
    }

    std::string line;
    InputDataVector currentPoint = { 0, 0, 0 };

    while (std::getline(file, line)) {
        // Supprimer les espaces et sauts de ligne inutiles
        if (line.empty()) continue;

        std::stringstream ss(line);
        std::string var;
        char eq;
        int value;

        // Exemple de ligne : "X = 1"
        if (ss >> var >> eq >> value) {
            if (var == "X") currentPoint.X = value;
            else if (var == "Y") currentPoint.Y = value;
            else if (var == "Z") currentPoint.Z = value;
        }
        else {
            // Si ce n’est pas une ligne de variable, c’est probablement un délai
            std::string delay = line;
            delays.push_back(delay);
            points.push_back(currentPoint);  // Sauvegarder l’état complet (X,Y,Z) avant le délai
        }
    }

    file.close();
    return true;
}
