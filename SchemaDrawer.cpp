// SchemaDrawer.cpp
#include "pch.h"
#include "SchemaDrawer.h"
#include "ExpressionParser.h"





SchemaDrawer::SchemaDrawer(CClientDC* deviceContext)
    : dc(deviceContext), currentX(100), currentY(200),
    gateSpacing(200), verticalSpacing(150), gateLevel(0), maxLevel(0){
	
}

void SchemaDrawer::setSpacing(int horizontal, int vertical) {
    gateSpacing = horizontal;
    verticalSpacing = vertical;
}

int SchemaDrawer::calculateMaxDepth(LogicExpression* expr) {
    if (!expr) return 0;

    if (expr->type == "VAR") {
        return 1;
    }

    if (expr->type == "NOT") {
        return 1 + calculateMaxDepth(expr->left);
    }

    // Pour AND, OR, XOR
    int leftDepth = calculateMaxDepth(expr->left);
    int rightDepth = calculateMaxDepth(expr->right);
    return 1 + max(leftDepth, rightDepth);
}

void SchemaDrawer::drawSchema(string expression) {
    ExpressionParser parser(expression);
    LogicExpression* expr = parser.parse();

    // VÉRIFICATION D'ERREUR
    if (!parser.isValid() || !expr) {
        // Afficher un message d'erreur
        CString errorMsg(parser.getError().c_str());
        AfxMessageBox(errorMsg, MB_ICONERROR | MB_OK);
        return;
    }

    // Calculer la profondeur maximale
    maxLevel = calculateMaxDepth(expr);
    // Dessiner à partir du niveau 0 (dernière porte)
    CPoint output = drawExpression(expr, 0, 300, 0);
    dc->MoveTo(output);
    dc->LineTo(CPoint(output.x + 50, output.y));
}

CPoint SchemaDrawer::drawExpression(LogicExpression* expr, int level, int baseY, int yOffset) {
    if (!expr) return CPoint(0, 0);

    // POSITIONS FIXES basées sur le niveau
    int fixedX =  (maxLevel - level) * gateSpacing;

    // DÉCALAGE EN Y POUR CHAQUE PORTE - AMÉLIORATION
    int adjustedY = baseY + yOffset;

    if (expr->type == "VAR") {
        // Variable - position fixe à l'extrême gauche
  
      
        if (!expr->isNegated)
        {
          fixedX = currentX;
        }
	
        CFont font;
        font.CreatePointFont(120, _T("Arial"));
        CFont* oldFont = dc->SelectObject(&font);
        dc->SetBkMode(TRANSPARENT);

        CString text(expr->varName.c_str());
        dc->TextOut(fixedX, adjustedY, text);
       
        dc->SelectObject(oldFont);
        return CPoint(fixedX + 20, adjustedY + 10);
       
    }

    if (expr->type == "NOT") {
      

        if (expr->left != nullptr && (expr->left->type == "VAR" || expr->left->type == "NOT")) {
		//	fixedX = fixedX-100;
        }

        // PORTE NOT - COMPORTEMENT SPÉCIAL
        NotGate notGate;
		notGate.setStartPoint(CPoint(fixedX, adjustedY));
        notGate.draw(*dc);
        
        
        // Pour NOT, on garde le même décalage Y pour l'entrée
        CPoint inputPoint = drawExpression(expr->left, level + 1, baseY, yOffset);

		CPoint gateInput = CPoint(notGate.getInputPoint().x, notGate.getInputPoint().y);
        // ✅ Tracé avec virage à 90° pour éviter les diagonales
        int midX = (inputPoint.x + notGate.getInputPoint().x) / 2;  // position intermédiaire horizontale

        dc->MoveTo(inputPoint);
        dc->LineTo(midX, inputPoint.y);      // ligne horizontale
        dc->LineTo(midX, gateInput.y);       // ligne verticale
        dc->LineTo(gateInput);


        return notGate.getOutputPoint();
    }

    if (expr->type == "AND") {
       
        if (expr->right!= nullptr && (expr->right->type =="VAR"|| expr->right->type == "NOT"))
        {
            
        }
        // PORTE AND - DÉCALAGE SPÉCIFIQUE
        AndGate andGate;
        
        andGate.setStartPoint(CPoint(fixedX, adjustedY));
        andGate.draw(*dc);
		andGate.computeSortie();
		andGate.setEntre1(false);
		andGate.setEntre2(false);
        
        // Points d'entrée de la porte AND
       

        // DÉCALAGES DIFFÉRENTS POUR CHAQUE BRANCHE
        int leftYOffset = yOffset - verticalSpacing / 2;  // Branche gauche plus haute
        int rightYOffset = yOffset + verticalSpacing / 2; // Branche droite plus basse

        // Dessiner les entrées avec décalages différents
        CPoint leftInput = drawExpression(expr->left, level + 1, baseY, leftYOffset);
        CPoint rightInput = drawExpression(expr->right, level + 1, baseY, rightYOffset);

        // Lignes horizontales alignées
       // Lignes horizontales + verticales pour un alignement propre
        int midX = (leftInput.x + andGate.getInputPoint1().x) / 2; // point intermédiaire
        // ligne horizontale depuis la sortie gauche
        dc->MoveTo(leftInput);
        dc->LineTo(midX, leftInput.y);
        // ligne verticale pour rejoindre la porte
        dc->LineTo(midX, andGate.getInputPoint1().y);
        // puis ligne horizontale finale
        dc->LineTo(andGate.getInputPoint1());

 


        // Lignes horizontales alignées
        // Lignes horizontales + verticales pour un alignement propre
        int midY = (rightInput.x + andGate.getInputPoint2().x) / 2; // point intermédiaire
        // ligne horizontale depuis la sortie gauche
        dc->MoveTo(rightInput);
        dc->LineTo(midY, rightInput.y);
        // ligne verticale pour rejoindre la porte
        dc->LineTo(midY, andGate.getInputPoint2().y);
        // puis ligne horizontale finale
        dc->LineTo(andGate.getInputPoint2());
        

        return andGate.getOutputPoint();
    }

    if (expr->type == "OR") {
        

        if (expr->right != nullptr  && expr->right->type == "NOT")
        {
          
            
        }
        
        // PORTE OR - DÉCALAGE SPÉCIFIQUE
        OrGate orGate;
        orGate.setStartPoint( CPoint(fixedX, adjustedY));
        orGate.draw(*dc);
		


        // Points d'entrée de la porte OR
        CPoint topInputGate(orGate.startPoint.x, orGate.startPoint.y + 22);
        CPoint bottomInputGate(orGate.startPoint.x, orGate.startPoint.y + 66);

        // DÉCALAGES DIFFÉRENTS POUR CHAQUE BRANCHE
        int leftYOffset = yOffset - verticalSpacing / 2;  // Branche gauche plus haute
        int rightYOffset = yOffset + verticalSpacing / 2; // Branche droite plus basse

        // Dessiner les entrées avec décalages différents
        CPoint leftInput = drawExpression(expr->left, level + 1, baseY, leftYOffset);
        CPoint rightInput = drawExpression(expr->right, level + 1, baseY, rightYOffset);

        // Lignes horizontales alignées
        // Lignes horizontales alignées
       // Lignes horizontales + verticales pour un alignement propre
        int midX = (leftInput.x + topInputGate.x) / 2; // point intermédiaire
        // ligne horizontale depuis la sortie gauche
        dc->MoveTo(leftInput);
        dc->LineTo(midX, leftInput.y);
        // ligne verticale pour rejoindre la porte
        dc->LineTo(midX, topInputGate.y);
        // puis ligne horizontale finale
        dc->LineTo(topInputGate);




        // Lignes horizontales alignées
        // Lignes horizontales + verticales pour un alignement propre
        int midY = (rightInput.x + bottomInputGate.x) / 2; // point intermédiaire
        // ligne horizontale depuis la sortie gauche
        dc->MoveTo(rightInput);
        dc->LineTo(midY, rightInput.y);
        // ligne verticale pour rejoindre la porte
        dc->LineTo(midY, bottomInputGate.y);
        // puis ligne horizontale finale
        dc->LineTo(bottomInputGate);
        
      
        return orGate.outputPoint;
    }

    if (expr->type == "XOR") {
        


        // PORTE XOR - DÉCALAGE SPÉCIFIQUE
        XorGate xorGate;
		xorGate.computeSortie();

        xorGate.setStartPoint( CPoint(fixedX, adjustedY));
        xorGate.draw(*dc);

        // Points d'entrée de la porte XOR
        CPoint topInputGate(xorGate.startPoint.x, xorGate.startPoint.y + 22);
        CPoint bottomInputGate(xorGate.startPoint.x, xorGate.startPoint.y + 66);

        // DÉCALAGES DIFFÉRENTS POUR CHAQUE BRANCHE
        int leftYOffset = yOffset - verticalSpacing / 2;  // Branche gauche plus haute
        int rightYOffset = yOffset + verticalSpacing / 2; // Branche droite plus basse

        // Dessiner les entrées avec décalages différents
        CPoint leftInput = drawExpression(expr->left, level + 1, baseY, leftYOffset);
        CPoint rightInput = drawExpression(expr->right, level + 1, baseY, rightYOffset);

        // Lignes horizontales alignées
       // Lignes horizontales + verticales pour un alignement propre
        int midX = (leftInput.x + topInputGate.x) / 2; // point intermédiaire
        // ligne horizontale depuis la sortie gauche
        dc->MoveTo(leftInput);
        dc->LineTo(midX, leftInput.y);
        // ligne verticale pour rejoindre la porte
        dc->LineTo(midX, topInputGate.y);
        // puis ligne horizontale finale
        topInputGate.x -= 5; // Ajustement pour le cercle de sortie
        dc->LineTo(topInputGate);


        // Lignes horizontales alignées
        // Lignes horizontales + verticales pour un alignement propre
        int midY = (rightInput.x + bottomInputGate.x) / 2; // point intermédiaire
        // ligne horizontale depuis la sortie gauche
        dc->MoveTo(rightInput);
        dc->LineTo(midY, rightInput.y);
        // ligne verticale pour rejoindre la porte
        dc->LineTo(midY, bottomInputGate.y);
        // puis ligne horizontale finale
        bottomInputGate.x -= 5; // Ajustement pour le cercle de sortie
        dc->LineTo(bottomInputGate);

       

        return xorGate.outputPoint;
    }
		
    return CPoint(0, 0);
}

int SchemaDrawer::evaluateExpression(LogicExpression* expr) {
    if (!expr) return 0;

    // --- Cas d'une variable ---
    if (expr->type == "VAR") {
        if (expr->varName == "X") return inputData.X;
        if (expr->varName == "Y") return inputData.Y;
        if (expr->varName == "Z") return inputData.Z;
        return 0;
    }

    // --- Cas d'une porte NOT ---
    if (expr->type == "NOT") {
        return !evaluateExpression(expr->left);
    }

    // --- Cas d'une porte AND ---
    if (expr->type == "AND") {
        int left = evaluateExpression(expr->left);
        int right = evaluateExpression(expr->right);
        return left && right;
    }

    // --- Cas d'une porte OR ---
    if (expr->type == "OR") {
        int left = evaluateExpression(expr->left);
        int right = evaluateExpression(expr->right);
        return left || right;
    }

    // --- Cas d'une porte XOR ---
    if (expr->type == "XOR") {
        int left = evaluateExpression(expr->left);
        int right = evaluateExpression(expr->right);
        return left ^ right;
    }

    return 0;
}
int SchemaDrawer::evaluateSchema(string expression, InputDataVector& inputs) {
    ExpressionParser parser(expression);
    LogicExpression* expr = parser.parse();

    if (!expr) return 0;

    // Stocker les valeurs d'entrée dans l'objet
    inputData = inputs;

    // Évaluer récursivement
    int result = evaluateExpression(expr);

    return result;
}


void SchemaDrawer::drawConnection(CPoint from, CPoint to) {
    dc->MoveTo(from);
    dc->LineTo(to);
}