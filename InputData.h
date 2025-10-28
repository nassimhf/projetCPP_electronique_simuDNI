// InputData.h
#ifndef INPUT_DATA_H
#define INPUT_DATA_H

#include <vector>
using namespace std;

// Structure pour représenter un point d'entrée
struct InputPoint {
    int x;
    int y;
    int z;

    InputPoint() : x(0), y(0), z(0) {}
    InputPoint(int _x, int _y, int _z) : x(_x), y(_y), z(_z) {}
};

// Classe pour gérer les entrées et calculer les sorties
class InputData {
private:
    vector<InputPoint> inputs;  // Vecteur des points d'entrée

public:
    InputData();

    // Ajouter un point d'entrée
    void addInput(int x, int y, int z);
    void addInput(InputPoint point);

    // Récupérer tous les points
    vector<InputPoint> getInputs() const;

    // Récupérer un point spécifique
    InputPoint getInput(int index) const;

    // Nombre de points
    int size() const;

    // Vider les entrées
    void clear();
};

#endif // INPUT_DATA_H