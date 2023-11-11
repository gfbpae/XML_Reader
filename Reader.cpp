#include "Reader.h"
#include <QStandardPaths>

Reader::Reader()
{
}
Reader::~Reader()
{
}

///
/// \brief Reader::xmlRead
/// Dosya isimini verilen girdiye eşitler ve okuma işlemini başlatır
/// \param x : girdi olarak erilen dosya ismi
///
void Reader::xmlRead(string x) { setXMLFileName(x); setXMLFile(); }
///
/// \brief Reader::resetReader
/// Okunan belgeyi serbest bırakır (pugixml kütüphanesinde gerçekleşiyor)
///
void Reader::resetReader() { xmlFile.reset(); }

/// @brief  Okunacak dosyanın adının sonunda yer alan "\\n" ifadesini çıkartan fonksiyon
/// @brief  TreeView'da seçilen item otomatik olarak "\\n" ifadesini eklediği için böyle bir fonksiyona ihtiyaç duyulmuştur
void Reader::setXMLFileName(string x)
{
    size_t found = x.find_last_not_of("\n");
    if (found != string::npos) {
        x.erase(found + 1);
    }
    xmlFileName = x;
}
///
/// \brief Reader::getXMLFileNameWithPath
/// \return Okunmuş olan XML dosyasının PATH'ini ve ismini döndürür
///
string Reader::getXMLFileNameWithPath() {return xmlFileNameWithPath;}
///
/// \brief Reader::getXMLFileName
/// \return Okunmuş olan XML dosyasının adını döndürür
///
string Reader::getXMLFileName() { return xmlFileName; }
///
/// \brief Reader::ReadWithAllPath
/// Girdi olarak verilen Path ve dosya ismi ile beraber okuma işlemi gerçekleştirilir.
/// \param filePath : Okunmak istenen dosyanın PATH'i ve dosya adı
///
void Reader::ReadWithAllPath(string filePath){xmlParseResult = xmlFile.load_file(filePath.c_str());xmlFileNameWithPath = filePath;}
///
/// \brief Reader::getXMLFile
/// \return Okunan ve hafızada tutulan XML dosyasının pugi::xml_document objesinin referansını döndürür
///
pugi::xml_document& Reader::getXMLFile() { return xmlFile; }
///
/// \brief Reader::getXMLParseResult
/// \return Okunma işlemi hakkında bilgileri tutan pugi::xml_parese_result objesinin referansını döndürür
///
pugi::xml_parse_result& Reader::getXMLParseResult() { return xmlParseResult; }
///
/// \brief Reader::setXMLFile
/// Dosya ismi ile okuma işlemini gerçekleştirir.
///
void Reader::setXMLFile()
{
    QString desktopPath = QStandardPaths::writableLocation(QStandardPaths::DesktopLocation);
    QString fullFilePath = desktopPath + "/" + QString::fromStdString(getXMLFileName());
    xmlFileNameWithPath = fullFilePath.toStdString();
    xmlParseResult = xmlFile.load_file(xmlFileNameWithPath.c_str());
}
