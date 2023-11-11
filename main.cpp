/**
 * @brief Harun Dursun
 * @brief 11 Eylül 2023 - 20 Ekim 2023 Staj Dönemi
 * @brief XML Okuyucu, Düzenleyici Programı
*/
#include "xml_ui.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    XML_ui w;
    w.show();
    w.displayXMLs();
    return a.exec();
}
