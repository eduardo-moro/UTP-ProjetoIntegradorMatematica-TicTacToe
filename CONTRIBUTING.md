# Contribuindo

## Requisitos (Ubuntu)

O projeto é C++ com Qt (Quick/QML + Multimedia), buildado via qmake.

Instale as dependências:

```bash
sudo apt update
sudo apt install build-essential qt6-base-dev qt6-declarative-dev qt6-multimedia-dev qmake6
```

Se o Ubuntu for mais antigo (20.04/22.04) e não tiver Qt6 nos repositórios padrão, use Qt5 no lugar:

```bash
sudo apt install build-essential qtbase5-dev qtdeclarative5-dev qtmultimedia5-dev qt5-qmake qml-module-qtquick2
```

## Build

```bash
qmake6 tic-tac-toe.pro   # ou "qmake", dependendo da versão instalada
make
```

## Rodar

Execute o binário gerado (`tic-tac-toe`, na raiz do projeto ou em `build/`).
