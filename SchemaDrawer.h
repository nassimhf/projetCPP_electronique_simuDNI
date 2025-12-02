    // SchemaDrawer.h 


// La classe SchemaDrawer permet de dessiner graphiquement un schéma logique 
// dans un contexte MFC. Elle gère la position et l'espacement des portes logiques, 
// le comptage et l'échelle des portes, ainsi que les connexions entre elles. 
// Elle fournit des méthodes pour dessiner une expression logique, évaluer ses valeurs 
// avec des entrées spécifiques, accéder et modifier les états des bascules, 
// et effacer le schéma affiché. Les structures InputDataVector et DrawResult 
// facilitent le stockage des données d'entrée et des points dessinés.

    #ifndef SCHEMA_DRAWER_H
    #define SCHEMA_DRAWER_H

    #include <afxwin.h>
    #include <string>
    #include <map>
    #include "LogicExpression.h"
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
        int GateCounter;
        float gateScale;
        InputDataVector inputData;
        bool lastDFFstate;
    
 
        int countLeaves(LogicExpression* expr);
        int calculateSubtreeHeight(LogicExpression* expr);
        int calculateMaxDepth(LogicExpression* expr);
    
        // CHANGEMENT: Ajout du paramètre yOffset
        CPoint SchemaDrawer::drawExpression(LogicExpression* expr, int level, int baseY, int yOffset);

        void drawConnection(CPoint from, CPoint to);


  
    public: 
        SchemaDrawer(CClientDC* deviceContext);
        bool lastJKFstate;
           // Évaluer l'expression avec les valeurs d'entrée
        float calculateGateScale();
        int calculateGateCount(LogicExpression* expr);
        int getGateCount();
  
        bool evaluateExpression(LogicExpression* expr);
        bool getlastDFFstate();
        void setlastJKFstate(bool Q);
        bool getlastJKFstate();
        void setlastDFFstate(bool D);
        void drawSchema(string expression);
    
        void setSpacing(int horizontal, int vertical); 
        int evaluateSchema(string expression, InputDataVector& inputs);
        void Clear(CClientDC* dc);

        InputDataVector getInputData();
        void setInputData(InputDataVector data);
    };


    #endif // SCHEMA_DRAWER_H