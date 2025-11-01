// SchemaDrawer.h - MISE � JOUR
#ifndef SCHEMA_DRAWER_H
#define SCHEMA_DRAWER_H

#include <afxwin.h>
#include <string>
#include <map>
#include "LogicExpression.h"
#include "InputData.h"
#include "AndGate.h"
#include "OrGate.h"
#include "XorGate.h"
#include "NotGate.h"

using namespace std;



struct InputDataVector {
    bool X;
    bool Y;
    bool Z;
};
struct DrawResult {
    CPoint point;
    int value;
};
class SchemaDrawer {
private:
    CClientDC* dc;
    int currentX;
    int currentY;
    int gateSpacing;
    int verticalSpacing;
    int gateLevel;
    int maxLevel;
     // Donn�es d'entr�e pour les variables

    // Variables d'entr�e actuelles
    map<string, int> currentInputValues;  // A->x, B->y, C->z

    int calculateMaxDepth(LogicExpression* expr);
    
    // CHANGEMENT: Ajout du param�tre yOffset
    CPoint SchemaDrawer::drawExpression(LogicExpression* expr, int level, int baseY, int yOffset);

    void drawConnection(CPoint from, CPoint to);


  
public: 

    InputDataVector inputData;
       // �valuer l'expression avec les valeurs d'entr�e
 
    bool evaluateExpression(LogicExpression* expr);
    SchemaDrawer(CClientDC* deviceContext);
    void drawSchema(string expression);
    void drawSchemaWithInputs(string expression, InputData& inputs);
    void setSpacing(int horizontal, int vertical); 
    int evaluateSchema(string expression, InputDataVector& inputs);
    void Clear(CClientDC* dc);
};


#endif // SCHEMA_DRAWER_H