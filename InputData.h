// InputData.h
#ifndef INPUT_DATA_H
#define INPUT_DATA_H

#include <vector>
using namespace std;

// Structure pour repr�senter un point d'entr�e
struct InputPoint {
    int x;
    int y;
    int z;

    InputPoint() : x(0), y(0), z(0) {}
    InputPoint(int _x, int _y, int _z) : x(_x), y(_y), z(_z) {}
};

// Classe pour g�rer les entr�es et calculer les sorties
class InputData {
private:
    vector<InputPoint> inputs;  // Vecteur des points d'entr�e

public:
    InputData();

    // Ajouter un point d'entr�e
    void addInput(int x, int y, int z);
    void addInput(InputPoint point);

    // R�cup�rer tous les points
    vector<InputPoint> getInputs() const;

    // R�cup�rer un point sp�cifique
    InputPoint getInput(int index) const;

    // Nombre de points
    int size() const;

    // Vider les entr�es
    void clear();
};

#endif // INPUT_DATA_H