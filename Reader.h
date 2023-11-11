#ifndef READER_H
#define READER_H
#include <iostream>
#include <stdio.h>
#include "C:/Users/hrndr/Desktop/tubitak_calismalar/XML/pugixml-1.13/src/pugixml.hpp"
using namespace std;
/**
 * @brief XML dosyasını okuduğumuz sınıftır. PugiXML kütüphanesi ile bu işlemi gerçekleştiriyoruz.
 */
class Reader
{
private:
    /// @brief Okuduğumuz xml dosyasındaki ağaç(tree) yapısının kökü(root) pugi::xml_document ile tutulabiliyor.
    pugi::xml_document xmlFile;
    /// @brief Dosya okuma işlemi sırasında hata olup olmadığını kontrol etmek için pugi::xml_parse_result kullanılabilir.
    pugi::xml_parse_result xmlParseResult;
    /// @brief Okunacak xml dosyasının sadece adını tutar (ornek.xml)
    string xmlFileName;
    /// @brief Okunacak xml dosyasını Path ile beraber tutar (C:/ ... /ornek.xml)
    string xmlFileNameWithPath;
public:
    /// @brief Reader sınıfı için yapıcı fonksiyonu
    Reader();
    /// @brief Reader sınıfı için yıkıcı fonksiyon
    ~Reader();
    /// @brief Sadece dosya adı ile okuma işlemini başlatır
    void xmlRead(string);
    /// @brief Reader sınıfına ait olan xmlFile objesini döndürür
    pugi::xml_document &getXMLFile();
    /// @brief Dosya okuma işlemi hakkında bilgileri döndürür
    pugi::xml_parse_result& getXMLParseResult();
    /// @brief Masaüstünde sadece dosya adı alınmış xml dosyasını okur
    void setXMLFile();
    /// @brief Reader sıfındaki xmlFile objesini resetler
    void resetReader();
    /// @brief Okunan XML dosyasının adını xmlFileName değişkenine atar
    void setXMLFileName(string);
    /// @brief xmlFileName değerini döndürür
    string getXMLFileName();
    /// @brief Path bilgisini aldığımız xml dosyasını okumak için kullanılır.
    void ReadWithAllPath(string);
    /// \brief getXMLFileNameWithPath
    string getXMLFileNameWithPath();
};

#endif // READER_H
