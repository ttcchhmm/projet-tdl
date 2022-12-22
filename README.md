# Projet noté de Théorie des Langages
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

## Configuration de Visual Studio Code
J'ai personnellement utilisé Visual Studio Code pour réaliser ce projet, et normalement si ce projet est ouvert dans VSCode deux extensions vous seront proposées :
- [C/C++](https://marketplace.visualstudio.com/items?itemName=ms-vscode.cpptools)
- [Yash](https://marketplace.visualstudio.com/items?itemName=daohong-emilio.yash)

Vous pouvez les installer automatiquement depuis la zone de notification de votre éditeur.