// SchemaDrawer.cpp
#include "pch.h"
#include "SchemaDrawer.h"
#include "ExpressionParser.h"
#include "Colors.h"
#include <format>
#include "DFlipFlop.h"
#include "JKFlipFlop.h"

SchemaDrawer::SchemaDrawer(CClientDC* deviceContext)
    : dc(deviceContext), currentX(100), currentY(100),
    gateSpacing(150), verticalSpacing(150), gateLevel(0), maxLevel(0), GateCounter(0), gateScale(0.7f), lastDFFstate(0), lastJKFstate(0) {

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

    // Pour DFF
    if (expr->type == "DFF") {
        int leftDepth = calculateMaxDepth(expr->left);
        int rightDepth = calculateMaxDepth(expr->right);
        return 1 + max(leftDepth, rightDepth);
    }

    // Pour JKF
    if (expr->type == "JKF") {
        int leftDepth = calculateMaxDepth(expr->left);
        // right contient le nœud JKF_KC avec K et CLK
        int rightDepth = 0;
        if (expr->right && expr->right->type == "JKF_KC") {
            int kDepth = calculateMaxDepth(expr->right->left);
            int clkDepth = calculateMaxDepth(expr->right->right);
            rightDepth = max(kDepth, clkDepth);
        }
        return 1 + max(leftDepth, rightDepth);
    }

    // Pour AND, OR, XOR
    int leftDepth = calculateMaxDepth(expr->left);
    int rightDepth = calculateMaxDepth(expr->right);
    return 1 + max(leftDepth, rightDepth);
}

int SchemaDrawer::calculateGateCount(LogicExpression* expr) {
    if (!expr) return 0;

    if (expr->type == "VAR") {
        return 0;
    }

    if (expr->type == "NOT") {
        return 1 + calculateGateCount(expr->left);
    }

    // Pour DFF
    if (expr->type == "DFF") {
        return 1 + calculateGateCount(expr->left) + calculateGateCount(expr->right);
    }

    // Pour JKF
    if (expr->type == "JKF") {
        int count = 1 + calculateGateCount(expr->left);
        if (expr->right && expr->right->type == "JKF_KC") {
            count += calculateGateCount(expr->right->left);
            count += calculateGateCount(expr->right->right);
        }
        return count;
    }

    // Pour AND, OR, XOR
    if (expr->type == "AND" || expr->type == "OR" || expr->type == "XOR") {
        return 1 + calculateGateCount(expr->left) + calculateGateCount(expr->right);
    }

    return GateCounter;
}

int SchemaDrawer::getGateCount() {
    return GateCounter;
}

float SchemaDrawer::calculateGateScale() {
    const int gateCount = getGateCount();// Recuperer le nombre de porte
    const float min_Scale = 0.3f; //scale minimum d une porte 
    const float max_Scale = 0.7f; //scale maximum d une porte

    const int minThreshold = 4;
    const int maxThreshold = 10;

    // ON RETURN min ou max si en dehors de l'interval
    if (gateCount <= minThreshold)
        return max_Scale;
    if (gateCount >= maxThreshold)
        return min_Scale;

    float ratio = float(gateCount - minThreshold) / float(maxThreshold - minThreshold);

    // Interpolation DÉCROISSANTE
    float scale = max_Scale - ratio * (max_Scale - min_Scale);
    return scale;
}

int SchemaDrawer::countLeaves(LogicExpression* expr) {
    if (!expr) return 0;

    if (expr->type == "VAR") {
        return 1;
    }

    if (expr->type == "NOT") {
        return countLeaves(expr->left);
    }

    // Pour JKF
    if (expr->type == "JKF") {
        int count = countLeaves(expr->left);
        if (expr->right && expr->right->type == "JKF_KC") {
            count += countLeaves(expr->right->left);
            count += countLeaves(expr->right->right);
        }
        return count;
    }

    // Pour DFF, AND, OR, XOR
    return countLeaves(expr->left) + countLeaves(expr->right);
}

void SchemaDrawer::Clear(CClientDC* dc) {
    CRect rect;
    dc->GetWindow()->GetClientRect(&rect);

    // Créer un brush blanc pour effacer tout
    CBrush whiteBrush(APP_COLOR_LIGHT);
    dc->FillRect(&rect, &whiteBrush);
}

InputDataVector SchemaDrawer::getInputData()
{
    return inputData;
}

void SchemaDrawer::setInputData(InputDataVector data)
{
    inputData = data;
}

void SchemaDrawer::setlastDFFstate(bool D)
{
    lastDFFstate = D;
}

bool SchemaDrawer::getlastDFFstate()
{
    return lastDFFstate;
}

void SchemaDrawer::setlastJKFstate(bool Q)
{
    lastJKFstate = Q;
}

bool SchemaDrawer::getlastJKFstate()
{
    return lastJKFstate;
}

void SchemaDrawer::drawSchema(string expression) {
    ExpressionParser parser(expression);
    LogicExpression* expr = parser.parse();
    GateCounter = calculateGateCount(expr);

    gateScale = calculateGateScale();
    gateSpacing = int(200 * gateScale);
    verticalSpacing = int(150 * gateScale);
    // Calculer la profondeur maximale
    maxLevel = calculateMaxDepth(expr);
    // Dessiner à partir du niveau 0 (dernière porte)

    CPoint output = drawExpression(expr, 0, 200, 0);
    dc->MoveTo(output);
    dc->LineTo(CPoint(output.x + 50, output.y));
    CFont font;
    font.CreatePointFont(90, _T("Arial"));
    CFont* oldFont = dc->SelectObject(&font);
    dc->SetBkMode(TRANSPARENT);

    CString text("S");
    dc->TextOut(output.x + 25, output.y - 28, text);
}

int SchemaDrawer::calculateSubtreeHeight(LogicExpression* expr) {
    if (!expr) return 0;

    if (expr->type == "VAR") {
        return 1;  // Une variable = 1 unité de hauteur
    }

    if (expr->type == "NOT") {
        return calculateSubtreeHeight(expr->left);  // NOT ne change pas la hauteur
    }

    // Pour JKF
    if (expr->type == "JKF") {
        int leftHeight = calculateSubtreeHeight(expr->left);
        int rightHeight = 0;
        if (expr->right && expr->right->type == "JKF_KC") {
            int kHeight = calculateSubtreeHeight(expr->right->left);
            int clkHeight = calculateSubtreeHeight(expr->right->right);
            rightHeight = kHeight + clkHeight;
        }
        return leftHeight + rightHeight;
    }

    // Pour DFF, AND, OR, XOR : la hauteur = somme des hauteurs des deux branches
    int leftHeight = calculateSubtreeHeight(expr->left);
    int rightHeight = calculateSubtreeHeight(expr->right);

    return leftHeight + rightHeight;
}

CPoint SchemaDrawer::drawExpression(LogicExpression* expr, int level, int baseY, int yOffset) {
    if (!expr) return CPoint(0, 0);

    int fixedX = (maxLevel - level) * gateSpacing;
    int adjustedY = baseY + yOffset;

    if (expr->type == "VAR") {
        CFont font;
        font.CreatePointFont(80, _T("Arial"));
        CFont* oldFont = dc->SelectObject(&font);
        dc->SetBkMode(TRANSPARENT);

        CString text(expr->varName.c_str());
        dc->SetTextColor(RGB(0, 0, 0));
        dc->TextOut(fixedX, adjustedY, text);

        dc->SelectObject(oldFont);
        return CPoint(fixedX + 20, adjustedY);
    }

    if (expr->type == "NOT") {
        NotGate notGate;
        notGate.setStartPoint(CPoint(fixedX, adjustedY));
        notGate.setEntree(evaluateExpression(expr->left) ? 1 : 0);
        notGate.draw(*dc);

        CPoint inputPoint = drawExpression(expr->left, level + 1, baseY, yOffset);
        CPoint gateInput = CPoint(notGate.getInputPoint().x, notGate.getInputPoint().y);

        int midX = (inputPoint.x + notGate.getInputPoint().x) / 2;
        dc->MoveTo(inputPoint);
        dc->LineTo(midX, inputPoint.y);
        dc->LineTo(midX, gateInput.y);
        dc->LineTo(gateInput);

        return notGate.getOutputPoint();
    }

    // NOUVEAU : Gestion de la bascule JK (JKF)
    if (expr->type == "JKF") {
        // Extraire les 3 entrées
        LogicExpression* inputJ = expr->left;
        LogicExpression* inputK = nullptr;
        LogicExpression* inputCLK = nullptr;

        if (expr->right && expr->right->type == "JKF_KC") {
            inputK = expr->right->left;
            inputCLK = expr->right->right;
        }

        // Détecter si les trois branches sont simples
        bool jIsSimple = (inputJ && (inputJ->type == "VAR" ||
            (inputJ->type == "NOT" && inputJ->left && inputJ->left->type == "VAR")));
        bool kIsSimple = (inputK && (inputK->type == "VAR" ||
            (inputK->type == "NOT" && inputK->left && inputK->left->type == "VAR")));
        bool clkIsSimple = (inputCLK && (inputCLK->type == "VAR" ||
            (inputCLK->type == "NOT" && inputCLK->left && inputCLK->left->type == "VAR")));

        int jCenterY, kCenterY, clkCenterY;

        if (jIsSimple && kIsSimple && clkIsSimple) {
            // Utiliser l'espacement minimal standard pour 3 entrées
            int simpleSpacing = int(50 * gateScale);
            if (simpleSpacing < 25) simpleSpacing = 25;

            jCenterY = adjustedY - simpleSpacing;        // J en haut
            clkCenterY = adjustedY;                       // CLK au milieu
            kCenterY = adjustedY + simpleSpacing;         // K en bas
        }
        else {
            // Cas complexe
            int jHeight = calculateSubtreeHeight(inputJ);
            int kHeight = calculateSubtreeHeight(inputK);
            int clkHeight = calculateSubtreeHeight(inputCLK);
            int totalHeight = jHeight + kHeight + clkHeight;

            const int baseUnitSpacing = 60;
            int unitSpacing = int(baseUnitSpacing * gateScale);
            if (unitSpacing < 30) unitSpacing = 30;

            int totalSpace = totalHeight * unitSpacing;
            int startY = adjustedY - totalSpace / 2;

            int jSpace = jHeight * unitSpacing;
            int clkSpace = clkHeight * unitSpacing;
            int kSpace = kHeight * unitSpacing;

            jCenterY = startY + jSpace / 2;
            clkCenterY = startY + jSpace + clkSpace / 2;
            kCenterY = startY + jSpace + clkSpace + kSpace / 2;
        }

        JKFlipFlop jkf;
        jkf.setStartPoint(CPoint(fixedX, adjustedY));
        jkf.setJ(evaluateExpression(inputJ) ? 1 : 0);
        jkf.setK(evaluateExpression(inputK) ? 1 : 0);
        jkf.setCLK(evaluateExpression(inputCLK) ? 1 : 0);
        jkf.computeQ();
        jkf.draw(*dc, calculateGateScale());

        // Dessiner les connexions pour l'entrée J
        CPoint jInput = drawExpression(inputJ, level + 1, jCenterY, 0);
        CPoint jInputPoint = jkf.getInputPointJ();

        int midXJ = (jInput.x + jInputPoint.x) / 2;
        dc->MoveTo(jInput);
        dc->LineTo(midXJ, jInput.y);
        dc->LineTo(midXJ, jInputPoint.y);
        dc->LineTo(jInputPoint);

        // Dessiner les connexions pour l'entrée K
        CPoint kInput = drawExpression(inputK, level + 1, kCenterY, 0);
        CPoint kInputPoint = jkf.getInputPointK();

        int midXK = (kInput.x + kInputPoint.x) / 2;
        dc->MoveTo(kInput);
        dc->LineTo(midXK, kInput.y);
        dc->LineTo(midXK, kInputPoint.y);
        dc->LineTo(kInputPoint);

        // Dessiner les connexions pour l'entrée CLK
        CPoint clkInput = drawExpression(inputCLK, level + 1, clkCenterY, 0);
        CPoint clkInputPoint = jkf.getInputPointCLK();

        int midXCLK = (clkInput.x + clkInputPoint.x) / 2;
        dc->MoveTo(clkInput);
        dc->LineTo(midXCLK, clkInput.y);
        dc->LineTo(midXCLK, clkInputPoint.y);
        dc->LineTo(clkInputPoint);

        return jkf.getOutputPointQ();
    }

    // Gestion de la bascule D (DFF)
    if (expr->type == "DFF") {
        // Détecter si les deux branches sont simples
        bool leftIsSimple = (expr->left->type == "VAR" ||
            (expr->left->type == "NOT" && expr->left->left && expr->left->left->type == "VAR"));
        bool rightIsSimple = (expr->right->type == "VAR" ||
            (expr->right->type == "NOT" && expr->right->left && expr->right->left->type == "VAR"));

        int leftCenterY, rightCenterY;

        if (leftIsSimple && rightIsSimple) {
            // Utiliser l'espacement minimal standard
            int simpleSpacing = int(50 * gateScale);  // Espacement pour D et CLK
            if (simpleSpacing < 25) simpleSpacing = 25;

            leftCenterY = adjustedY - simpleSpacing;   // Position pour D
            rightCenterY = adjustedY + simpleSpacing;  // Position pour CLK
        }
        else {
            // Cas complexe : Au moins une branche a des sous-arbres
            int leftHeight = calculateSubtreeHeight(expr->left);
            int rightHeight = calculateSubtreeHeight(expr->right);
            int totalHeight = leftHeight + rightHeight;

            const int baseUnitSpacing = 80;
            int unitSpacing = int(baseUnitSpacing * gateScale);
            if (unitSpacing < 40) unitSpacing = 40;

            int totalSpace = totalHeight * unitSpacing;
            int startY = adjustedY - totalSpace / 2;

            int leftSpace = leftHeight * unitSpacing;
            int rightSpace = rightHeight * unitSpacing;

            leftCenterY = startY + leftSpace / 2;
            rightCenterY = startY + leftSpace + rightSpace / 2;
        }

        DFlipFlop dff;
        dff.setStartPoint(CPoint(fixedX, adjustedY));
        dff.setD(evaluateExpression(expr->left) ? 1 : 0);
        dff.setCLK(evaluateExpression(expr->right) ? 1 : 0);
     
        dff.draw(*dc, calculateGateScale());

        // Dessiner les connexions pour l'entrée D
        CPoint leftInput = drawExpression(expr->left, level + 1, leftCenterY, 0);
        CPoint dInputPoint = dff.getInputPointD();

        int midXD = (leftInput.x + dInputPoint.x) / 2;
        dc->MoveTo(leftInput);
        dc->LineTo(midXD, leftInput.y);
        dc->LineTo(midXD, dInputPoint.y);
        dc->LineTo(dInputPoint);

        // Dessiner les connexions pour l'entrée CLK
        CPoint rightInput = drawExpression(expr->right, level + 1, rightCenterY, 0);
        CPoint clkInputPoint = dff.getInputPointCLK();

        int midXCLK = (rightInput.x + clkInputPoint.x) / 2;
        dc->MoveTo(rightInput);
        dc->LineTo(midXCLK, rightInput.y);
        dc->LineTo(midXCLK, clkInputPoint.y);
        dc->LineTo(clkInputPoint);

        return dff.getOutputPointQ();
    }

    if (expr->type == "AND" || expr->type == "OR" || expr->type == "XOR") {

        // DÉTECTER SI LES DEUX BRANCHES SONT SIMPLES (VAR ou NOT VAR)
        bool leftIsSimple = (expr->left->type == "VAR" ||
            (expr->left->type == "NOT" && expr->left->left && expr->left->left->type == "VAR"));
        bool rightIsSimple = (expr->right->type == "VAR" ||
            (expr->right->type == "NOT" && expr->right->left && expr->right->left->type == "VAR"));

        int leftCenterY, rightCenterY;

        if (leftIsSimple && rightIsSimple) {

            // Utiliser l'espacement minimal standard de la porte
            int simpleSpacing = int(40 * gateScale);  // Espacement minimal
            if (simpleSpacing < 20) simpleSpacing = 20;

            leftCenterY = adjustedY - simpleSpacing;
            rightCenterY = adjustedY + simpleSpacing;
        }
        else {
            // CAS COMPLEXE : Au moins une branche a des sous-arbres
            int leftHeight = calculateSubtreeHeight(expr->left);
            int rightHeight = calculateSubtreeHeight(expr->right);
            int totalHeight = leftHeight + rightHeight;

            const int baseUnitSpacing = 80;
            int unitSpacing = int(baseUnitSpacing * gateScale);
            if (unitSpacing < 40) unitSpacing = 40;

            int totalSpace = totalHeight * unitSpacing;
            int startY = adjustedY - totalSpace / 2;

            int leftSpace = leftHeight * unitSpacing;
            int rightSpace = rightHeight * unitSpacing;

            leftCenterY = startY + leftSpace / 2;
            rightCenterY = startY + leftSpace + rightSpace / 2;
        }

        if (expr->type == "AND") {
            AndGate andGate;
            andGate.setStartPoint(CPoint(fixedX, adjustedY));
            andGate.setEntre1(evaluateExpression(expr->left) ? 1 : 0);
            andGate.setEntre2(evaluateExpression(expr->right) ? 1 : 0);
            andGate.draw(*dc, calculateGateScale());

            CPoint leftInput = drawExpression(expr->left, level + 1, leftCenterY, 0);
            CPoint rightInput = drawExpression(expr->right, level + 1, rightCenterY, 0);

            int midX = (leftInput.x + andGate.getInputPoint1().x) / 2;
            dc->MoveTo(leftInput);
            dc->LineTo(midX, leftInput.y);
            dc->LineTo(midX, andGate.getInputPoint1().y);
            dc->LineTo(andGate.getInputPoint1());

            int midY = (rightInput.x + andGate.getInputPoint2().x) / 2;
            dc->MoveTo(rightInput);
            dc->LineTo(midY, rightInput.y);
            dc->LineTo(midY, andGate.getInputPoint2().y);
            dc->LineTo(andGate.getInputPoint2());

            return andGate.getOutputPoint();
        }

        if (expr->type == "OR") {
            OrGate orGate;
            orGate.setStartPoint(CPoint(fixedX, adjustedY));
            orGate.entre1 = evaluateExpression(expr->left) ? 1 : 0;
            orGate.entre2 = evaluateExpression(expr->right) ? 1 : 0;
            orGate.draw(*dc, calculateGateScale());

            CPoint leftInput = drawExpression(expr->left, level + 1, leftCenterY, 0);
            CPoint rightInput = drawExpression(expr->right, level + 1, rightCenterY, 0);

            CPoint topInputGate(orGate.getInputPoint1());
            CPoint bottomInputGate(orGate.getInputPoint2());

            int midX = (leftInput.x + topInputGate.x) / 2;
            dc->MoveTo(leftInput);
            dc->LineTo(midX, leftInput.y);
            dc->LineTo(midX, topInputGate.y);
            dc->LineTo(topInputGate);

            int midY = (rightInput.x + bottomInputGate.x) / 2;
            dc->MoveTo(rightInput);
            dc->LineTo(midY, rightInput.y);
            dc->LineTo(midY, bottomInputGate.y);
            dc->LineTo(bottomInputGate);

            return orGate.outputPoint;
        }

        if (expr->type == "XOR") {
            XorGate xorGate;
            xorGate.setStartPoint(CPoint(fixedX, adjustedY));
            xorGate.entre1 = evaluateExpression(expr->left) ? 1 : 0;
            xorGate.entre2 = evaluateExpression(expr->right) ? 1 : 0;
            xorGate.draw(*dc, calculateGateScale());

            CPoint leftInput = drawExpression(expr->left, level + 1, leftCenterY, 0);
            CPoint rightInput = drawExpression(expr->right, level + 1, rightCenterY, 0);

            CPoint topInputGate(xorGate.getInputPoint1());
            CPoint bottomInputGate(xorGate.getInputPoint2());

            int midX = (leftInput.x + topInputGate.x) / 2;
            dc->MoveTo(leftInput);
            dc->LineTo(midX, leftInput.y);
            dc->LineTo(midX, topInputGate.y);
            topInputGate.x -= 5;
            dc->LineTo(topInputGate);

            int midY = (rightInput.x + bottomInputGate.x) / 2;
            dc->MoveTo(rightInput);
            dc->LineTo(midY, rightInput.y);
            dc->LineTo(midY, bottomInputGate.y);
            bottomInputGate.x -= 5;
            dc->LineTo(bottomInputGate);

            return xorGate.outputPoint;
        }
    }
    return CPoint(0, 0);
}

bool SchemaDrawer::evaluateExpression(LogicExpression* expr) {
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

    // --- NOUVEAU : Cas d'une bascule JK (JKF) ---
    if (expr->type == "JKF") {
        bool J = evaluateExpression(expr->left);
        bool K = false;
        bool CLK = false;

        if (expr->right && expr->right->type == "JKF_KC") {
            K = evaluateExpression(expr->right->left);
            CLK = evaluateExpression(expr->right->right);
        }

        // Simulation de la bascule JK sur front montant
        if (CLK) {
            bool currentQ = getlastJKFstate();
            bool newQ = currentQ;

            if (!J && !K) {
                // Maintien : Q garde sa valeur
                newQ = currentQ;
            }
            else if (!J && K) {
                // Reset
                newQ = false;
            }
            else if (J && !K) {
                // Set
                newQ = true;
            }
            else if (J && K) {
                // Toggle
                newQ = !currentQ;
            }

            setlastJKFstate(newQ);
            return newQ;
        }

        return getlastJKFstate();
    }

    // --- Cas d'une bascule D (DFF) ---
    if (expr->type == "DFF") {
        bool D = evaluateExpression(expr->left);
        bool CLK = evaluateExpression(expr->right);

        if (CLK) {
            setlastDFFstate(D);
            return D;
        }
        return getlastDFFstate();
    }

    // --- Cas d'une porte AND ---
    if (expr->type == "AND") {
        int left = evaluateExpression(expr->left);
        int right = evaluateExpression(expr->right);
        return left & right;
    }

    // --- Cas d'une porte OR ---
    if (expr->type == "OR") {
        int left = evaluateExpression(expr->left);
        int right = evaluateExpression(expr->right);
        return left | right;
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