#ifndef XML_H
#define XML_H
#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;
/**
 * @brief XML dosyasından okunan verilerin her bir node'unun xml sınıfında tutulduğu yapıdır.\n
 * Tag name değeri string olarak tag_name değişkeninde tutulur.\n
 * Tag value değeri strin olarak tag_value değişkeninde tutulur.\n
 * Attributes name ve value değerleri vector<pair<string,string>> yapısında olan attributes değişkeninde tutulur.
 */
struct Node
{
    string tag_name;
    string tag_value;
    vector<pair<string,string>> attributes;
};

/// @brief Okunan XML dosyasından elde edile verilerin depolandığı sınıftır.
class xml
{
    /// @brief Arama işlemi gerçekleşirken girlen değerler ile tutulan verilerin küçük karakter olarak karşılaştırılması
    friend string stringToLower(string);
private:
    /// @brief Node yapısında bir P değişkeni oluşturulur ve veriler okunurken kullanılır.
    Node P;
    /// @brief Okunan veriler xmlMap değişkeni içerisinde tutulur.\n
    /// İlk pair Parent layer ve Node yapısı ile okunan verileri tutar.\n
    /// İkinci pair ise kendi hash değeri ile parent hash değerini tutar.
    vector<pair<pair<int, Node>,pair<int64_t,int64_t>>> xmlMap;
    /// @brief Dosyada okunan root hash değeridir.
    int64_t RootHashValue;
    /// @brief Eklenen node'ların kaçıncı katmanda oluduğunu görmek için kullanılır
    static int parent_layer;
    /// @brief Delete işlemi sırasında silinecek elemanların hash değerlerini tutan bir vector'dür.
    vector<int64_t> remove;
    /// @brief Okunan XML dosyasındaki attributeların isimlerini tutar.
    vector<string> attributes;

public:
    /// @brief xml sınıfı yapıcı fonksiyonu
    xml();
    /// @brief xml sınıfı yıkıcı fonksiyonu
    ~xml();
    /// @brief Static parent_layer değişkenini +1 arttırır
    static void upParentLayer();
    /// @brief Static parent_layer değişkenini -1 azaltır
    static void downParentLayer();
    /// @brief Static parent_layer değişkenini döndürür
    static int  getParentLayer();
    /// @brief Static parent_layer değişkenini sıfırlar
    static void setParentLayer();
    /// @brief Node yapısını set eder
    void setP(string, string, vector<pair<string,string>>&);
    /// @brief Okunan verilerin xmlMap vector'üne ekler
    void setXMLMap(int, Node, int64_t, int64_t);
    /// @brief Okunan verilerin xmlMap vector'üne ekler
    void setXMLMap(int, string, string, vector<pair<string,string>>&, int64_t, int64_t);
    /// @brief xmlMap vector'ü üzerinde belirli bir elemanın üzerinde değişim işlemi yapılır
    void editXMLMap(int ,int, string, string, vector<pair<string,string>>&, int64_t, int64_t);
    /// @brief xml sınıfındaki xmlMap vector'ünün referansını döndürür
    vector<pair<pair<int, Node>, pair<int64_t, int64_t>>>&					getXMLMap();
    /// @brief xml sınıfındaki xmlMap vector'ünün belirli bir elenanının referansını döndürür
    pair<pair<int, Node>, pair<int64_t, int64_t>>&							getXMLMapAtI(int);
    /// @brief xml sınıfındaki xmlMap vector'ünün ilk elemanının iteratorünü döndürür
    const vector<pair<pair<int, Node>, pair<int64_t, int64_t>>>::iterator&	getXMLFirstItr();
    /// @brief xml sınıfındaki xmlMap vector'ünün son elemanının iteratorünü döndürür
    const vector<pair<pair<int, Node>, pair<int64_t, int64_t>>>::iterator&	getXMLEndItr();
    /// @brief xml sınıfındaki xmlMap vector'ünün boyutunu döndürür
    int																		getXMLMapSize();
    /// @brief xml sınıfındaki xmlMap vector'ünün belirli bir elemanının parent_layer değerini döndürür
    int																		getXMLLayer(int);
    /// @brief xml sınıfındaki xmlMap vector'ünün belirli bir hash değerine sahip elemanının indexini döndürür
    int																		getXMLMapAtHash(int64_t);
    /// @brief xml sınıfındaki P yapısının referansını döndürür
    Node&																	getP();
    /// @brief xml sınıfındaki xmlMap vector'ünün belirli bir elemanının tag_name değerini döndürür
    string																	getTagAtI(int);
    /// @brief xml sınıfındaki xmlMap vector'ünün belirli bir elemanının tag_value değerini döndürür
    string																	getTagValueAtI(int);
    /// @brief xml sınıfındaki xmlMap vector'ünün belirli bir elemanının attributes vector'ünü döndürür
    vector<pair<string,string>>&                                            getAttributesAtI(int);
    /// @brief xml sınıfındaki xmlMap vector'ünün belirli bir elemanının hash değerini döndürür
    int64_t																	getCurrentHashValue(int);
    /// @brief xml sınıfındaki xmlMap vector'ünün belirli bir elemanının parrent hash değerini döndürür
    int64_t																	getParrentHashValue(int);
    /// @brief xml sınıfındaki RootHasHValue değerini döndürür
    int64_t																	getRootHashValue();
    /// @brief xml sınıfındaki xmlMap vector'ündeki belirli bir elemanı siler
    int64_t																	getRemoveAtI(int);
    /// @brief xml sınıfındaki xmlMap vector'ü üzerinde belirli bir tag_name için arama yapar
    vector<int64_t>															getHashesForTN(string);
    /// @brief xml sınıfındaki xmlMap vector'ü üzerinde belirli bir tag_value için arama yapar
    vector<int64_t>															getHashesForTV(string);
    /// @brief xml sınıfındaki xmlMap vector'ü üzerinde belirli bir tag_name ve tag_value için arama yapar
    vector<int64_t>															getHashesForTNTV(string,string);
    /// @brief xml sınıfındaki xmlMap vector'ü üzerinde belirli bir tag_name ve verilen attributes değerleri için arama yapar
    vector<int64_t>                                                         getHashesForAttsTN(string,vector<pair<string,string>>&);
    /// @brief xml sınıfındaki xmlMap vector'ü üzerinde belirli bir tag_value ve veirlen attributes değerleri için arama yapar
    vector<int64_t>                                                         getHashesForAttsTV(string,vector<pair<string,string>>&);
    /// @brief xml sınıfındaki xmlMap vector'ü üzerinde verilen attributes değerleri için arama yapar
    vector<int64_t>                                                         getHashesForAtts(vector<pair<string,string>>&);
    /// @brief xml sınıfındaki xmlMap vector'ü üzerinde belirli bir tag_name, tag_value ve verilen attributes değerleri için arama yapar
    vector<int64_t>                                                         getHashesForAttsTNTV(string,string,vector<pair<string,string>>&);
    /// @brief attributes vector'ünü ayarlar
    void                                                                    setAttributes();
    /// @brief attributes vector'ünün referansını döndürür
    vector<string>&                                                         getAttributes();
    /// @brief attributes vetor'üne eleman ekler
    void                                                                    addAttributes(string);
    /// @brief Kaldırılacak elemanları remove vector'üne ekler
    void																	setRemove(int64_t);
    /// @brief remove vector'ünün boyutunu döndürür
    int																		getRemoveSize();
    /// @brief
    void																	Remove();
    /// @brief remove vector'ünü boşaltır
    void																	resetRemove();
    /// @brief RootHashValue değerini verilen girdiye eşitler
    void																	setRootHashValue(int64_t);
    /// @brief xmlMap vector'ünü temizler
    void																	resetXMLMap();
    /// @brief Verilen girdideki hash değerine sahip child xmlMap'den kaldırılır
    void																	removeChild(int64_t);
    /// @brief Yeni attribute eklenmesi
    void                                                                    addAttributesToNodes(int64_t,string,string);
    /// \brief chechkHasChild
    bool                                                                    chechkHasChild(int64_t);
};

#endif // XML_H
