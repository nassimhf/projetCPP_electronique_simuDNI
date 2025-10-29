// Chronogram.h
#ifndef CHRONOGRAM_H
#define CHRONOGRAM_H

#include <afxwin.h>
#include <vector>
using namespace std;

// Structure pour un �tat du chronogramme
struct ChronoState {
    bool state;        // �tat logique (1 ou 0)
    int timeMs;        // Dur�e en millisecondes

    ChronoState() : state(false), timeMs(0) {}
    ChronoState(bool s, int t) : state(s), timeMs(t) {}
};

// Classe pour dessiner un chronogramme logique
class Chronogram {
private:
    vector<ChronoState> states;     // Vecteur des �tats
    CString signalName;              // Nom du signal
    int startX;                      // Position X de d�part
    int startY;                      // Position Y de d�part
    int height;                      // Hauteur du signal (amplitude)
    float timeScale;                 // �chelle de temps (pixels par ms)

    // Couleurs
    COLORREF highColor;              // Rouge 207
    COLORREF lowColor;               // Bleu 207
    COLORREF gridColor;              // Couleur de la grille
    COLORREF textColor;              // Couleur du texte

public:
    Chronogram();
    Chronogram(CString name, int x, int y);

    // Ajouter un �tat
    void addState(bool state, int timeMs);
    void addState(ChronoState state);

    // D�finir tous les �tats d'un coup
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

    // Effacer tous les �tats
    void clear();

    // Obtenir la largeur totale du chronogramme
    int getTotalWidth() const;
    int getTotalTime() const;
};

#endif // CHRONOGRAM_H