#ifndef PARSER_H
#define PARSER_H
#include "Reader.h"
#include "xml.h"

using namespace std;
/**
 * @brief Okunan XML dosyasının işlendiği sınıftır
 */
class Parser : protected Reader, protected xml
{
private:
    /// @brief Okunan XML dosyasının ağaç yapısındaki ilk elemanı tutmak için kullanılır
    pugi::xml_node node;
    /// @brief Verileri depolayacağımız xml sınıfından bir obje
    xml xmlp;
    /// @brief XML dosyasını okuyacağımız Reader sınıfından bir obje
    Reader reader;
    /// @brief Ağaç yapısındaki köke bağlı kaç tane child olduğunu sayıyor
    static int rootParents;
    /// @brief Kaydetme işlemi sırasında yazılmış olan child'ların hashlerini tutar
    vector<int64_t > writedHash;
    /// @brief Bulunulan node'un kardeşi olup olmadığını kontrol eder
    bool checkSiblings(pugi::xml_node&);
    /// @brief Bulunulan node'un çocuklarının olup olmadığını kontrol eder
    bool checkChild(pugi::xml_node&);
    /// @brief Gönderilen node ile beraber çocukları okuma işlemini başlatır ve revursive olarak çalışır
    void addSiblings(pugi::xml_node&);

public:
    Parser();
    ~Parser();
    /// @brief XML dosyasının işlenme sürecini başlatır
    void parse();
    /// @brief Tekrar okunma başlamadan önce gerekli değişkenleri sıfırlar
    void resetParser();
    /// @return 'node' değişkenini döndürür
    pugi::xml_node& getNode();
    /**
     * @brief Okuma işlemini başlatır
     * @param Okunacak dosyanın sadece adını alır ve ona göre okuma işlemini gerçekleştirir
     */
    void ReadXML(string);
    /**
     * @brief Okuma işlemini başlatır
     * @param Okunacak dosyayı 'PATH+DOSYA ADI' şeklinde alır ve ona göre okuma işlemini gerçekleştirir
     */
    void ReadXMLWithFullPath(string);
    /// @return Bu sınıfta oluşturulan 'xmlp' objesini döndürür
    xml& getXML();
    /// @brief rootParents değerini arttırır
    static void upRootParent();
    /// @return rootParents değerini döndürür
    static int	getRootParent();
    /// @brief Bu sınıfta oluşturulan 'reader' objesini döndürür
    Reader& getReader();
    /**
     * @brief Verilerin bir XML dosyasına yazdırılma işlemini başlatır, gerekli düzenlemeleri yapar
     * @param filePathAndName : XML dosyasının nereye ve hangi isimde kaydedileceğini gösterir
     */
    void saveXMLFile(string filePathAndName);
    /**
     * @brief Recursive olarak tutulan verileri pugi::xml_node objesine atar (Child ekler)
     * @param pHash : pugi::xml_node'da kayıtlı olan paretın hash değerini verir
     */
    void saveChilds(pugi::xml_node&, int64_t pHash);
    /// @brief Kaydetme işlemi sırasında kayıt edilmiş node'ları kontrol eder
    bool checkWritedHash(int64_t);
    /// @return writedHash vector'ünden istenilen elemanı döndürür
    int64_t getWritedHash(int );
    /// @brief pugi::xml_node'a yazılan child'ların hash değerlerini writedHash vector'üne yazar
    void setWritedHash(int64_t);
};

#endif // PARSER_H
