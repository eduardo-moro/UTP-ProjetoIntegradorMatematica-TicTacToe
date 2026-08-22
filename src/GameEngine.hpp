#pragma once

#include <QObject>
#include <QVariant>

class GameEngine : public QObject {
    Q_OBJECT

    public: 
        explicit GameEngine(QObject* parent = nullptr);
    
};