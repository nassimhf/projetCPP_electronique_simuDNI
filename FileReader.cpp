#include "pch.h"
#include "FileReader.h"
#include <fstream>
#include <sstream>
#include <iostream>
#include <cctype>

bool FileReader::readFile(const std::string& filePath)
{



    // Convertir std::string → CString
    CString path(filePath.c_str());


    std::ifstream file(path);
    if (!file.is_open()) {

        CString msg;
        msg.Format(_T("ERROR Reading file = %d"));  // %d convertit true → 1, false → 0

        AfxMessageBox(msg);
        std::cerr << "Erreur : impossible d'ouvrir le fichier " << filePath << std::endl;
        return false;
    }

    std::string line;
    InputDataVector currentPoint = { 0, 0, 0 };

    while (std::getline(file, line)) {
        // Supprimer les espaces superflus
        if (line.empty()) continue;

        // Enlever les espaces au début et à la fin
        line.erase(0, line.find_first_not_of(" \t\r\n"));
        line.erase(line.find_last_not_of(" \t\r\n") + 1);

        // Vérifier si la ligne contient une variable X, Y, Z
        std::stringstream ss(line);
        std::string var;
        char eq;
        int value;

        if (ss >> var >> eq >> value) {
            if (var == "X") currentPoint.X = value;
            else if (var == "Y") currentPoint.Y = value;
            else if (var == "Z") currentPoint.Z = value;
        }
        else {
            // Sinon, c’est probablement une ligne de délai (ex: "100ns")
            std::string numStr;
            for (char c : line) {
                if (std::isdigit(c)) numStr += c; // Ne garder que les chiffres
            }

            if (!numStr.empty()) {
                int delayValue = std::stoi(numStr);
                delays.push_back(delayValue);
                points.push_back(currentPoint);
            }
        }
    }

    file.close();
    return true;
}
