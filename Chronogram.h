// Chronogram.h
#ifndef CHRONOGRAM_H
#define CHRONOGRAM_H

#include <afxwin.h>
#include <vector>
using namespace std;

// Structure pour un état du chronogramme
struct ChronoState {
    bool state;        // État logique (1 ou 0)
    int timeMs;        // Durée en millisecondes

    ChronoState() : state(false), timeMs(0) {}
    ChronoState(bool s, int t) : state(s), timeMs(t) {}
};

// Classe pour dessiner un chronogramme logique
class Chronogram {
private:
    vector<ChronoState> states;     // Vecteur des états
    CString signalName;              // Nom du signal
    int startX;                      // Position X de départ
    int startY;                      // Position Y de départ
    int height;                      // Hauteur du signal (amplitude)
    float timeScale;                 // Échelle de temps (pixels par ms)

    // Couleurs
    COLORREF highColor;              // Rouge 207
    COLORREF lowColor;               // Bleu 207
    COLORREF gridColor;              // Couleur de la grille
    COLORREF textColor;              // Couleur du texte

public:
    Chronogram();
    Chronogram(CString name, int x, int y);

    // Ajouter un état
    void addState(bool state, int timeMs);
    void addState(ChronoState state);

    // Définir tous les états d'un coup
    void setStates(vector<bool> states, vector<int> times);
    void setStates(vector<ChronoState> states);

    // Dessiner le chronogramme
    void draw(CDC* dc);

    // Accesseurs
    void setPosition(int x, int y);
    void setHeight(int h);
    void setTimeScale(float scale);
    void setSignalName(CString name);
    void setColors(COLORREF high, COLORREF low);

    // Effacer tous les états
    void clear();

    // Obtenir la largeur totale du chronogramme
    int getTotalWidth() const;
    int getTotalTime() const;
};

#endif // CHRONOGRAM_H