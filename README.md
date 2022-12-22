# Projet noté de Théorie des Langages
Réalisé par : **Tom CHEDMAIL**
## Prérequis
### Debian Bullseye
- `flex`
- `libfl-dev`
- `bison`
- `qt5-qmake`
- `qtbase5-dev`

Vous pouvez installer ces paquets avec la commande suivante :
```bash
sudo apt install -y flex libfl-dev bison qt5-qmake qtbase5-dev
```

### Arch Linux
- `base-devel`
- `qt5-base`

Vous pouvez installer ce groupe et paquet avec la commande suivante :
```bash
sudo pacman -S base-devel qt5-base
```

## Compilation
```bash
mkdir build
cd build
qmake ../projet.pro
make
```

Vous trouverez l'exécutable dans `./build/tortue`.

> **Avertissement:** Ne passez pas d'argument `-j` à `make` pour spécifier le nombre de jobs utilisés pour compiler en parallèle le projet, ceci provoque des erreurs. Faites également attention à la variable d'environnement `MAKEFLAGS` si vous l'avez définie sur votre système.

## Structure des dossiers
- *Racine* : Fichiers de configuration (QMake, Doxygen, Git) et en-tête d'alias [`Utils.hh`](./Utils.hh).
- `.vscode` : Fichiers de Visual Studio Code.
- `expressions` : Fourni dans le cadre du projet. Contient les structures de données pour les formules arithmétiques. Les modifications suivantes ont été apportées :
  - Retrait du nom de l'argument dans `Constante::calculer(Contexte const &)` pour supprimer un avertissement du compilateur (variable non utilisée).
- `fields` : Fourni dans le cadre du projet. Contient des exemples de jardins. [`jardin3.txt`](fields/jardin3.txt) contient un exemple malformé.
- `GUI` : Fourni dans le cadre du projet. Contient l'interface graphique. Les modifications suivantes ont été apportées :
  - Correction de comparaisons entre entiers signés et non signés.
  - Utilisation de `std::size_t` comme identifiant de tortue (comme il s'agit d'un index dans un tableau).
  - Réimplémentation de `JardinRendering::estVide(int, int)` pour corriger un bug (espace non retourné comme vide alors qu'il n'y a pas de mur).
- `instructions` : Contient l'implémentation des différentes instructions du langage.
- `instructions/conditionals` : Contient l'implémentation des différentes instructions de branchement et de comparaison du langage.
- `parser` : Contient le lexeur et le parser du langage ainsi que la fonction `main`.

## Configuration de Visual Studio Code
J'ai personnellement utilisé Visual Studio Code pour réaliser ce projet, et normalement si ce projet est ouvert dans VSCode deux extensions vous seront proposées :
- [C/C++](https://marketplace.visualstudio.com/items?itemName=ms-vscode.cpptools)
- [Yash](https://marketplace.visualstudio.com/items?itemName=daohong-emilio.yash)

Vous pouvez les installer automatiquement depuis la zone de notifications de votre éditeur.