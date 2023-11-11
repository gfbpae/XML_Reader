#include "xml.h"
/// @brief Yapıcı fonksiyon
xml::xml(){}
/// @brief Yıkıcı fonksiyon
xml::~xml()
{
}
/// @brief parent_layer'ı taınmlar
int		xml::parent_layer = 0;
/// @brief parent_layer'ı +1 arttırır
void	xml::upParentLayer()	{ parent_layer++; }
/// @brief parent_layer'ı -1 azaltır
void	xml::downParentLayer()	{ parent_layer--; }
/// @brief parent_layer'ı döndürür
int		xml::getParentLayer()	{ return parent_layer; }
/// @brief parent_layer'ı sıfırlar
void	xml::setParentLayer()	{ parent_layer = 0; }

///
/// \brief xml::getP
/// \return Node yapısındaki P değişkeninin refernasını döndürür
///
Node&                                                                       xml::getP()                             { return P; }
///
/// \brief xml::getXMLMap
/// \return xmlMap vector'ünün referansını döndürür
///
vector<pair<pair<int, Node>, pair<int64_t, int64_t>>>&                      xml::getXMLMap()                        { return xmlMap;}
///
/// \brief xml::getXMLMapAtI
/// \param i : istenilen index
/// \return xmlMap vector'ündei istenilen index de bulunan yapıyı döndürür
///
pair<pair<int, Node>, pair<int64_t, int64_t>>&                              xml::getXMLMapAtI(int i)                { return getXMLMap().at(i); }
///
/// \brief xml::getXMLMapSize
/// \return xmlMap boyutunu döndürür
///
int                                                                         xml::getXMLMapSize()                    { return (int)getXMLMap().size(); }
///
/// \brief xml::getXMLLayer
/// \param i : istenilen index
/// \return xmlMap vector'ündei istenilen index de bulunan ilk pair'ın ilk değişkeni döndürülür
///
int                                                                         xml::getXMLLayer(int i)                 { return getXMLMapAtI(i).first.first; }
///
/// \brief xml::getTagAtI
/// \param i : istenilen index
/// \return xmlMap vector'ündei istenilen index de bulunan ilk pair'ın ikinci elamanındaki Node yapısındaki tag_name değeri döndürülür
///
string                                                                      xml::getTagAtI(int i)                   { return getXMLMapAtI(i).first.second.tag_name; }
///
/// \brief xml::getTagValueAtI
/// \param i : istenilen index
/// \return xmlMap vector'ündei istenilen index de bulunan ilk pair'ın ikinci elamanındaki Node yapısındaki tag_value değeri döndürülür
///
string                                                                      xml::getTagValueAtI(int i)              { return getXMLMapAtI(i).first.second.tag_value; }
///
/// \brief xml::getAttributesAtI
/// \param i : istenilen index
/// \return xmlMap vector'ündei istenilen index de bulunan ilk pair'ın ikinci elamanındaki Node yapısındaki attributes vector'ünün referansı döndürülür
///
vector<pair<string, string> >&                                              xml::getAttributesAtI(int i)            { return getXMLMapAtI(i).first.second.attributes; }
///
/// \brief xml::getCurrentHashValue
/// \param i : istenilen index
/// \return xmlMap vector'ündei istenilen index de bulunan ikinci pair'ın ilk elemanında bulunan hash değeri döndürülür
///
int64_t                                                                     xml::getCurrentHashValue(int i)         { return getXMLMapAtI(i).second.first;}
///
/// \brief xml::getParrentHashValue
/// \param i : istenilen index
/// \return xmlMap vector'ündei istenilen index de bulunan ikinci pair'ın ikinci elemanında bulunan parent hash değeri döndürülür
///
int64_t                                                                     xml::getParrentHashValue(int i)         { return getXMLMapAtI(i).second.second;}
///
/// \brief xml::getRootHashValue
/// \return RootHashValue değerini döndürür
///
int64_t                                                                     xml::getRootHashValue()                 { return RootHashValue; }
///
/// \brief xml::getRemoveAtI
/// \param i : istenilen index
/// \return remove vector'ündeki istenilen index de bulunan hash değeri döndürlür
///
int64_t                                                                     xml::getRemoveAtI(int i)                { return remove[i]; }
///
/// \brief xml::getRemoveSize
/// \return remove vector'ünün boyutu döndürülür
///
int                                                                         xml::getRemoveSize()                    { return remove.size(); }
/// @brief remove vector'üne ekleme yapar
void                                                                        xml::setRemove(int64_t x)               { remove.push_back(x); }
/// @brief remove vector'ünü sıfırlar
void                                                                        xml::resetRemove()                      { remove = {}; }
///
/// \brief xml::setRootHashValue
/// \param x : RootHashValue
///
void                                                                        xml::setRootHashValue(int64_t x)        { RootHashValue = x; }
/// @brief xmlMap vector'ünü sıfırlar
void                                                                        xml::resetXMLMap()                      { getXMLMap().clear(); setParentLayer(); getAttributes().clear(); }
///
/// \brief xml::getXMLMapAtHash
/// \param hash : bulunmak istenilen hash değeri
/// \return Girdi olarak verilen hash değerinin hangi index de bulunduğu döndürülür
///
int                                                                         xml::getXMLMapAtHash(int64_t hash)      { for (int i = 0; i < getXMLMapSize(); i++) if (getCurrentHashValue(i) == hash) return i; }

///
/// \brief xmlMap vector'ündeki ilk pair'ın ikinci elemanı olan Node yapısı içinde tutulan attributes vector'ündeki ilk elemanları tekrarsız bir şekilde yazar
///
void xml::setAttributes()
{
    getAttributes().clear();
    for(int i =0 ; i < getXMLMapSize();i++)
    {
        for(int j =0 ; j < getAttributesAtI(i).size();j++)
        {
            if(find(getAttributes().begin(),getAttributes().end(),getAttributesAtI(i).at(j).first) != getAttributes().end())
                continue;
            else
                getAttributes().push_back(getAttributesAtI(i).at(j).first);
        }
    }
}
///
/// \brief xml::addAttributes
/// attributes vector'üne girdi olarak verilen stringi yazar
/// \param attName : eklenmek istenen isim
///
void xml::addAttributes(string attName) {attributes.push_back(attName);}
///
/// \brief xml::getAttributes
/// \return attributes vector'ünü döndürür
///
vector<string> &xml::getAttributes() {return attributes;}
///
/// \brief xml::setXMLMap
/// xmlMap vector'üne eleman ekler
/// \param layer : eklenecek eleman için layer değeri
/// \param node : eklenecek eleman için tag name, tag value ve attribute'ların tutulduğu Node yapısı
/// \param hashCurrent : eklenecek eleman için hash değeri
/// \param hashParrent : eklenecek elemanın parent hash değeri
///
void xml::setXMLMap 	(int layer, Node node, int64_t hashCurrent, int64_t hashParrent)
{ getXMLMap().push_back(make_pair(make_pair(layer, node), make_pair(hashCurrent, hashParrent))); }
///
/// \brief xml::setXMLMap
/// xmlMap vector'üne eleman ekler. string türünde alınan elemanları Node'a yerleştirir ve tekrar setXMLMap fonksiyonu çağrılır
/// \param layer : eklenecek eleman için layer değeri
/// \param tn : tag name
/// \param tv : tag value
/// \param att : attributes
/// \param hc : eklenecek eleman için hash değeri
/// \param hp : eklenecek elemanın parent hash değeri
///
void xml::setXMLMap 	(int layer, string tn, string tv, vector<pair<string,string>>& att, int64_t hc, int64_t hp)
{ setP(tn,tv,att); setXMLMap(layer,getP(),hc,hp); }

///
/// \brief xml::editXMLMap
/// xmlMap'in istenen index'ini düzenler
/// \param index : düzenlenmel istenen index
/// \param layer : yeni layer değeri
/// \param tn : yeni tag name
/// \param tv : yeni tag value
/// \param att : yeni attributes
/// \param hc : yeni hash değeri
/// \param hp : yeni parent hash değeri
///
void xml::editXMLMap    (int index,int layer, string tn, string tv, vector<pair<string,string>>& att, int64_t hc, int64_t hp)
{
    getXMLMapAtI(index).first.first = layer;
    getXMLMapAtI(index).first.second.attributes.clear();
    getXMLMapAtI(index).first.second.attributes = att ;
    getXMLMapAtI(index).first.second.tag_name = tn ;
    getXMLMapAtI(index).first.second.tag_value = tv;
    getXMLMapAtI(index).second.first = hc ;
    getXMLMapAtI(index).second.second = hp;
}
///
/// \brief xml::setP
/// Node yapısını düzenler
/// \param tag_n : tag name
/// \param tag_v : tag value
/// \param atts : attribute name ve value'leri
///
void xml::setP          (string tag_n, string tag_v, vector<pair<string,string>>& atts)
{ P.tag_name = tag_n; P.tag_value = tag_v; P.attributes = atts; }
///
/// \brief xml::removeChild
/// Bir parent silinirken içindeki child'ların da silinmesini sağlar
/// \param hash : parent hash değeri
///
void xml::removeChild   (int64_t hash)
{
    for(int i=0;i<getXMLMapSize();i++)
    {
        if(hash == getCurrentHashValue(i))
        {
            setRemove(getCurrentHashValue(i));
        }
        else if(hash==getParrentHashValue(i))
        {
            removeChild(getCurrentHashValue(i));
        }
    }
}
/// @brief Silme işlemi gerçekleştirilir
void xml::Remove()
{
    for (int i = 0; i < getRemoveSize(); i++)
    {
        int temp = getXMLMapAtHash(getRemoveAtI(i));
        getXMLMap().erase(getXMLMap().begin() + temp, getXMLMap().begin() + temp + 1);
    }
    resetRemove();
    getXMLMap().shrink_to_fit();
}
///
/// \brief stringToLower
/// \param in : girdi
/// \return girdi olarak verilen string'i küçük karakterlerden oluşan bir string olarak döndürür
///
string stringToLower(string in)
{
    transform(in.begin(), in.end(), in.begin(), ::tolower);
    return in;
}
///
/// \brief xml::getHashesForTN
/// İstenen tag name değerine göre arama işlemi yapılır
/// \param tagName : istenen tag name
/// \return İstenen tag name değerine sahip node'ların hashlerini döndürür
///
vector<int64_t> xml::getHashesForTN(string tagName)
{
    vector<int64_t> Searched;
    for(int i =0 ;i < getXMLMapSize();i++)
    {
        if (stringToLower( getXMLMapAtI(i).first.second.tag_name )== stringToLower(tagName)) Searched.push_back(getCurrentHashValue(i));
    }
    return Searched;
}
///
/// \brief xml::getHashesForTV
/// İstenen tag value değerine göre arama işlemi yapılır
/// \param tagValue : istenen tag value
/// \return İstenen tag value değerine sahip node'ların hashlerini döndürür
///
vector<int64_t> xml::getHashesForTV(string tagValue)
{
    vector<int64_t> Searched;
    for(int i =0 ;i < getXMLMapSize();i++)
    {
        if (stringToLower(getXMLMapAtI(i).first.second.tag_value) == stringToLower(tagValue)) Searched.push_back(getCurrentHashValue(i));
    }
    return Searched;
}
///
/// \brief xml::getHashesForTNTV
/// İstenen tag name ve tag value değerine göre arama işlemi yapılır
/// \param tagName : İstenen tag name
/// \param tagValue : İstenen tag value
/// \return  İstenen tag name ve tag value değerine sahip node'ların hashlerini döndürür
///
vector<int64_t> xml::getHashesForTNTV(string tagName,string tagValue)
{
    vector<int64_t> Searched;
    for(int i =0 ;i < getXMLMapSize();i++)
    {
        if (stringToLower(getXMLMapAtI(i).first.second.tag_name) == stringToLower(tagName) &&
            stringToLower(getXMLMapAtI(i).first.second.tag_value) == stringToLower(tagValue))
            Searched.push_back(getCurrentHashValue(i));
    }
    return Searched;
}
///
/// \brief xml::getHashesForAttsTNTV
/// İstenen tag name, tag value ve attributes value'lerine göre arama işlemi yapılır
/// \param tagName : İstenen tag name
/// \param tagValue : İstenen tag value
/// \param atts : İstenen attributes value'leri
/// \return İstenen tag name, tag value ve attributes value'lere sahip node'ların hashlerini döndürür
///
vector<int64_t> xml::getHashesForAttsTNTV(string tagName, string tagValue, vector<pair<string, string> > & atts)
{
    vector<int64_t> SearchedTemp,Searched;
    SearchedTemp = getHashesForTNTV(tagName,tagValue);
    for(int64_t temp : SearchedTemp)
    {
        int attsFlag = 0 ;
        int index = getXMLMapAtHash(temp);
        for(pair<string,string> tempAtts : atts)
        {
            vector<pair<string,string>>::iterator it = find(getAttributesAtI(index).begin(),getAttributesAtI(index).end(),tempAtts);
            if(stringToLower(it->second) == stringToLower(tempAtts.second))
                    attsFlag++;
        }
        if(attsFlag == atts.size()) Searched.push_back(getCurrentHashValue(index));
    }
    return Searched;
}
///
/// \brief xml::getHashesForAttsTNTV
/// İstenen tag name ve attributes value'lerine göre arama işlemi yapılır
/// \param tagName : İstenen tag name
/// \param atts : İstenen attributes value'leri
/// \return İstenen tag name ve attributes value'lere sahip node'ların hashlerini döndürür
///
vector<int64_t> xml::getHashesForAttsTN(string tagName, vector<pair<string, string> > & atts)
{
    vector<int64_t> SearchedTemp,Searched;
    SearchedTemp = getHashesForTN(tagName);
    for(int64_t temp : SearchedTemp)
    {
        int attsFlag = 0 ;
        int index = getXMLMapAtHash(temp);
        for(pair<string,string> tempAtts : atts)
        {
                auto it = find_if(getAttributesAtI(index).begin(),getAttributesAtI(index).end(),[&tempAtts](const pair<string,string>&p){return p.first == tempAtts.first;});
                if(it != getAttributesAtI(index).end() && stringToLower(it->second) == stringToLower(tempAtts.second))
                    attsFlag++;
        }
        if(attsFlag == atts.size()) Searched.push_back(getCurrentHashValue(index));
    }
    return Searched;
}
///
/// \brief xml::getHashesForAttsTNTV
/// İstenen tag value ve attributes value'lerine göre arama işlemi yapılır
/// \param tagValue : İstenen tag value
/// \param atts : İstenen attributes value'leri
/// \return İstenen tag value ve attributes value'lere sahip node'ların hashlerini döndürür
///
vector<int64_t> xml::getHashesForAttsTV( string tagValue, vector<pair<string, string> > & atts)
{
    vector<int64_t> SearchedTemp,Searched;
    SearchedTemp = getHashesForTV(tagValue);
    for(int64_t temp : SearchedTemp)
    {
        int attsFlag = 0 ;
        int index = getXMLMapAtHash(temp);
        for(pair<string,string> tempAtts : atts)
        {
                auto it = find_if(getAttributesAtI(index).begin(),getAttributesAtI(index).end(),[&tempAtts](const pair<string,string>&p){return p.first == tempAtts.first;});
                if(it != getAttributesAtI(index).end() && stringToLower(it->second) == stringToLower(tempAtts.second))
                    attsFlag++;
        }
        if(attsFlag == atts.size()) Searched.push_back(getCurrentHashValue(index));
    }
    return Searched;
}
///
/// \brief xml::getHashesForAttsTNTV
/// İstenen tag name, tag value ve attributes value'lerine göre arama işlemi yapılır
/// \param atts : İstenen attributes value'leri
/// \return İstenen attributes value'lere sahip node'ların hashlerini döndürür
///
vector<int64_t> xml::getHashesForAtts(vector<pair<string, string> > & atts)
{
    vector<int64_t> Searched;
    for(int i = 0 ; i < getXMLMapSize() ; i++)
    {
        int attsFlag = 0 ;
        for(pair<string,string> tempAtts : atts)
        {
                auto it = find_if(getAttributesAtI(i).begin(),getAttributesAtI(i).end(),[&tempAtts](const pair<string,string>&p){return p.first == tempAtts.first;});
                if(it != getXMLMapAtI(i).first.second.attributes.end() && stringToLower(it->second) == stringToLower(tempAtts.second))
                    attsFlag++;
        }
        if(attsFlag == atts.size())
                Searched.push_back(getCurrentHashValue(i));
    }
    return Searched;
}
///
/// \brief xml::addAttributesToNodes
/// Yeni attribute name ve value değerini istenen node'a ekliyor, ayrıca aynı tag name'i olan node'lara tag name = "" ekliyor
/// \param nodeHash : Ekleme yapılmak istenen node
/// \param attName : Eklenmek istenen attribute name
/// \param attValue : Ekelnemek istenen attribute value
///
void xml::addAttributesToNodes(int64_t nodeHash, string attName, string attValue)
{
    int index = getXMLMapAtHash(nodeHash);
    vector<int64_t> Searched = getHashesForTN(getXMLMapAtI(index).first.second.tag_name);
    for(int64_t temp : Searched)
    {
        int index = getXMLMapAtHash(temp);
        if(temp == nodeHash) getXMLMapAtI(index).first.second.attributes.push_back(make_pair(attName,attValue));
        else getXMLMapAtI(index).first.second.attributes.push_back(make_pair(attName,""));
    }
}
///
/// \brief xml::chechkHasChild
/// \param hash
/// \return Gönderilen hash değerinde parent'ı olan bir child var mı kontrol edilir ve bool değer döndürür (varsa true döner)
///
bool xml::chechkHasChild(int64_t hash)
{
    for(int i = 0 ; i < getXMLMapSize() ; i++)
    {
        if(getParrentHashValue(i) == hash)
        {
            return true;
        }
    }
    return false;
}
