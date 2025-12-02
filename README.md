<h1 align="center"> DNI Logic Simulator </h1>
<h1 align="center"> Système de Simulation de Circuits Logiques </h1>

<p align="center">
Un projet modulaire en C++/MFC permettant de simuler des circuits logiques, d’évaluer des expressions booléennes et de générer des chronogrammes de signaux.
</p>

<p align="center">
  <a href="#"><img alt="Langage Badge" src="https://img.shields.io/badge/Langage-C%2B%2B-blue?style=flat-square&logo=c%2B%2B"></a>
  <a href="#"><img alt="Framework Badge" src="https://img.shields.io/badge/Framework-MFC-green?style=flat-square"></a>
  <a href="#"><img alt="Simulation Badge" src="https://img.shields.io/badge/Simulation-Circuits%20Logiques-orange?style=flat-square"></a>
  <a href="#"><img alt="Parser Badge" src="https://img.shields.io/badge/Parser-Expressions%20Logiques-yellow?style=flat-square"></a>
  <a href="#"><img alt="Chronogramme Badge" src="https://img.shields.io/badge/Sortie-Chronogramme-lightgrey?style=flat-square"></a>
</p>

<br>



---

# 📌 Architecture du système

### Structure du projet
<pre><code>
  
├── Porte Logique/                 # Portes logiques
│   AndGate.h/.cpp
│   OrGate.h/.cpp
│   XorGate.h/.cpp
│   NotGate.h/.cpp
|   JKFlipFlop.h/.cpp
|   DFlipFlop.h/.cpp  
│
├── Parsing/
│   LogicExpression.h/.cpp   # Arbre d'expression logique
│   ExpressionParser.h/.cpp  # Analyse et validation
│
├── Drawing/
│   SchemaDrawer.h/.cpp      # Dessin du schéma logique
│   Chronogram.h/.cpp        # Affichage des signaux
│
├── Files/
│   FileReader.h/.cpp        # Lecture des fichiers d’entrée
│
├── UI/
│   MainScreen.cpp           # Interface utilisateur MFC
│
└── Projetcppsimu.cpp            # Point d'entrée du prorgramme


  </code></pre>






---

# ⚙️ Fonctionnalités actuelles

### ✔ Portes logiques  
- AND, OR, XOR, NOT
- Bascule D, JK
- Gestion dynamique des entrées  
- Propagation automatique des sorties  

### ✔ Analyseur d'expressions  
- Support d'expressions complexes :  
  `X AND (Y OR NOT Z)`
  `DFF(X,Y)` : X représente D et Y représente le signal d'horloge
  `JKF(X,Y,Z)` : X représente J et Y représente le signal d'horloge,Z représente K

- Construction d’un arbre syntaxique  
- Contrôle des erreurs de syntaxe

### ✔ Dessin du schéma  
- Affichage visuel des portes  
- Connexions automatiques  
- Représentation graphique claire

### ✔ Chronogramme  
- Tracé des signaux dans le temps  
- Délais configurables  
- Multiplicateur d’échelle temporelle

### ✔ Lecture de fichiers  
- Lecture des valeurs binaires 0/1  
- Lecture des durées/retards temporels  
- Génération de points temporels

---

# 🚀 Fonctionnalités principales

- Simulation visuelle des circuits logiques
- Évaluation d'expressions booléennes
- Chronogramme dynamique
- Lecture de signaux depuis fichiers externes
- Gestion des délais et des transitions
- Architecture propre et modulaire

---

# 🧭 Guide d’utilisation

1. **Saisir une fonction logique**  
   Exemple :  
   `A AND (B OR NOT C)`
   Pour la bascule D, la syntaxe a utiliser est DFF(X,Y) ici X pour D et Y pour CLK.
   Pour la bascule JK, la syntaxe a utiliser est JKF(X,Y,Z) ici X pour J, Y pour K et Z pour CLK.

3. **Choisir un fichier d’entrée**  
   Contenant les valeurs et les délais.

4. **Choisir un multiplicateur de temps**  
   Pour ajuster l’échelle du chronogramme.

5. **Lancer la simulation**  
   → Le schéma se dessine  
   → Le chronogramme s’affiche automatiquement

---

# 🔧 Instructions d’installation

1. Ouvrir le projet dans **Visual Studio**  
2. Vérifier que **MFC** est activé  
3. Compiler le projet  
4. Exécuter `Projetcppsimu.exe`  
5. Charger les fichiers et lancer la simulation  

---

# 🔮 Améliorations futures

- Interface utilisateur plus moderne et intuitive
- Ajout d’un timer interne pour les simulations longues sans blocage
- Ajout de nouvelles portes : NAND, NOR, XNOR…
- Zone de dessin interactive avec :
  - Zoom  
  - Panning  
  - Déplacement d’éléments  
  - Suppression / édition  
- Export du chronogramme (image, CSV…)
- Parser plus robuste avec gestion avancée des erreurs
- Système de sauvegarde et chargement de schémas

---

# 🎯 Objectifs pédagogiques

Ce projet permet d’apprendre :

- Programmation C++ en architecture modulaire  
- Manipulation et parsing d’expressions logiques  
- Implémentation d’un simulateur  
- Dessin et graphiques MFC  
- Construction d’un arbre syntaxique  
- Gestion des signaux dans le temps  

---

# 🧪 Simulation

Le projet inclut une simulation complète :  
- Lecture automatique des signaux d’entrée  
- Génération du chronogramme  
- Représentation graphique du circuit logique  

Tout fonctionne **sans matériel physique**, uniquement via l’interface graphique.

---


