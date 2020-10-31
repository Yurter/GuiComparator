#include "Screenshot.hpp"

#include <QGuiApplication>
#include <QScreen>
#include <QBuffer>
#include <QPainter>

QString Screenshot::makeBase64Screenshot(QRect rect) const {
   QByteArray byteArray;
   QBuffer buffer { &byteArray };
   buffer.open(QIODevice::WriteOnly);

   const auto screen { QGuiApplication::screenAt(rect.center()) };
   const auto geometry { screen->geometry() };
   const auto pixmap = screen->grabWindow(
          0 // grab screen
        , rect.x() - geometry.x()
        , rect.y() - geometry.y()
        , rect.width()
        , rect.height()
   );
   QImage image { pixmap.size(), QImage::Format_ARGB32_Premultiplied };
   image.fill(Qt::transparent);
   QPainter painter { &image };
   painter.setOpacity(0.5);
   painter.drawPixmap(0, 0, pixmap);
   painter.end();
   image.save(&buffer, "PNG");
   buffer.close();

   const auto base64data {
       QString::fromLatin1(byteArray.toBase64().data())
   };
   const auto base64image {
       QString { "data:image/png;base64," }.append(base64data)
   };

   return base64image;
}
