#pragma once
#include <QQuickView>

class Screenshot : public QObject {

    Q_OBJECT

public:

    Q_INVOKABLE QString makeBase64Screenshot(QRect rect) const;

};
