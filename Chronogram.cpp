// Chronogram.cpp
#include "pch.h"
#include "Chronogram.h"
#include "Colors.h"

Chronogram::Chronogram()
    : signalName(_T("Signal")), startX(50), startY(100),
    height(60), timeScale(1.0f) {

    // Couleurs par défaut
    highColor = APP_COLOR_HIGH;     // Vert pour état haut
    lowColor = APP_COLOR_LOW;       // Gris foncé pour état bas
    gridColor = RGB(189, 195, 199); // Gris clair
    textColor = APP_COLOR_TEXT_PRIMARY;
}

Chronogram::Chronogram(CString name, int x, int y)
    : signalName(name), startX(x), startY(y),
    height(60), timeScale(1.0f) {

    highColor = APP_COLOR_HIGH;     // Vert pour état haut
    lowColor = APP_COLOR_LOW;       // Gris foncé pour état bas
    gridColor = RGB(189, 195, 199); // Gris clair
    textColor = APP_COLOR_TEXT_PRIMARY;
}

void Chronogram::addState(bool state, int timeMs) {
    states.push_back(ChronoState(state, timeMs));
}

void Chronogram::addState(ChronoState state) {
    states.push_back(state);
}

void Chronogram::setStates(vector<bool> stateVec, vector<int> timeVec) {
    states.clear();

    // S'assurer que les deux vecteurs ont la même taille
    int size = min(stateVec.size(), timeVec.size());

    for (int i = 0; i < size; i++) {
        states.push_back(ChronoState(stateVec[i], timeVec[i]));
    }
}

void Chronogram::setStates(vector<ChronoState> newStates) {
    states = newStates;
}

void Chronogram::draw(CDC* dc) {
    if (states.empty()) return;

    // Sauvegarder le contexte graphique
    int savedDC = dc->SaveDC();

    // --- 1. Dessiner le nom du signal ---
    CFont nameFont;
    nameFont.CreatePointFont(100, _T("Arial Bold"));
    CFont* oldFont = dc->SelectObject(&nameFont);
    dc->SetTextColor(textColor);
    dc->SetBkMode(TRANSPARENT);
    dc->TextOut(startX - 80, startY + height / 2 - 10, signalName);

    // --- 2. Dessiner les axes ---
    CPen axisPen(PS_SOLID, 2, RGB(0, 0, 0));
    CPen* oldPen = dc->SelectObject(&axisPen);

    // Ligne de base (état bas)
    dc->MoveTo(startX, startY + height);
    dc->LineTo(startX + getTotalWidth(), startY + height);

    // Ligne haute (état haut)
    CPen gridPen(PS_DOT, 1, gridColor);
    dc->SelectObject(&gridPen);
    dc->MoveTo(startX, startY);
    dc->LineTo(startX + getTotalWidth(), startY);

    // --- 3. Dessiner le chronogramme ---
    int currentX = startX;
    bool previousState = states[0].state;
    int currentY = states[0].state ? startY : (startY + height);

    for (int i = 0; i < states.size(); i++) {
        ChronoState& st = states[i];

        // Calculer la largeur de ce segment
        int segmentWidth = (int)(st.timeMs * timeScale);

        // Déterminer la couleur selon l'état
        COLORREF segmentColor = st.state ? highColor : lowColor;
        CPen signalPen(PS_SOLID, 3, segmentColor);
        dc->SelectObject(&signalPen);

        // Si changement d'état, dessiner la transition verticale
        if (i > 0 && st.state != previousState) {
            int newY = st.state ? startY : (startY + height);

            // Ligne verticale de transition
            dc->MoveTo(currentX, currentY);
            dc->LineTo(currentX, newY);

            currentY = newY;
        }

        // Dessiner la ligne horizontale pour cet état
        dc->MoveTo(currentX, currentY);
        dc->LineTo(currentX + segmentWidth, currentY);

        // --- 4. Dessiner les annotations de temps ---
        dc->SelectObject(oldFont);
        CFont timeFont;
        timeFont.CreatePointFont(80, _T("Arial"));
        dc->SelectObject(&timeFont);
        dc->SetTextColor(RGB(100, 100, 100));

        CString timeStr;
        timeStr.Format(_T("%dms"), st.timeMs);
        dc->TextOut(currentX + 5, startY + height + 10, timeStr);

        // Ligne verticale de séparation (grille)
        dc->SelectObject(&gridPen);
        dc->MoveTo(currentX + segmentWidth, startY - 5);
        dc->LineTo(currentX + segmentWidth, startY + height + 5);

        // Mettre à jour la position
        currentX += segmentWidth;
        previousState = st.state;
    }

    // --- 5. Dessiner les marqueurs d'état ---
    dc->SelectObject(oldFont);
    CFont stateFont;
    stateFont.CreatePointFont(90, _T("Arial Bold"));
    dc->SelectObject(&stateFont);

    currentX = startX;
    for (int i = 0; i < states.size(); i++) {
        ChronoState& st = states[i];
        int segmentWidth = (int)(st.timeMs * timeScale);

        // Afficher "1" ou "0" au milieu du segment
        CString stateStr = st.state ? _T("1") : _T("0");
        COLORREF stateTextColor = st.state ? highColor : lowColor;
        dc->SetTextColor(stateTextColor);

        int textY = st.state ? (startY - 20) : (startY + height + 30);
        dc->TextOut(currentX + segmentWidth / 2 - 5, textY, stateStr);

        currentX += segmentWidth;
    }

    // Restaurer le contexte
    dc->RestoreDC(savedDC);
}

void Chronogram::setPosition(int x, int y) {
    startX = x;
    startY = y;
}

void Chronogram::setHeight(int h) {
    height = h;
}

void Chronogram::setTimeScale(float scale) {
    timeScale = scale;
}

void Chronogram::setSignalName(CString name) {
    signalName = name;
}

void Chronogram::setColors(COLORREF high, COLORREF low) {
    highColor = high;
    lowColor = low;
}

void Chronogram::clear() {
    states.clear();
}

int Chronogram::getTotalWidth() const {
    int totalWidth = 0;
    for (const ChronoState& st : states) {
        totalWidth += (int)(st.timeMs * timeScale);
    }
    return totalWidth;
}

int Chronogram::getTotalTime() const {
    int totalTime = 0;
    for (const ChronoState& st : states) {
        totalTime += st.timeMs;
    }
    return totalTime;
}