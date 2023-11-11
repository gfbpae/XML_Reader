#include "Parser.h"

Parser::Parser(){}
Parser::~Parser() {}

/**
 * @brief Sadece dosya ismi alınmış masaüstünde bulunan xml dosyasını okumak için kullanılır.
 * @brief Reader sınıfındaki xmlRead fonksiyonunu çağırarak bunu gerçekleştirir.
 * @brief Son olarakta okunan dosyanın ilk child'ını pugi::xml_node türündeki node değişkenine atar.
 * @param xmlName : Reader sınıfındaki xmlRead fonksyionu için  gerekli olan dosya adını verir.
 */
void Parser::ReadXML(string xmlName)
{
    getReader().xmlRead(xmlName);
    node = getReader().getXMLFile().first_child();
    string root = "root";
    string nRoot = node.name();
    while(nRoot.compare(root) == 0)
    {
        node = node.first_child();
        nRoot = node.name();
    }
}
/**
 * @brief Dosya adı ve PATH'i seçilmiş xml dosyasını okumak için kullanılır.
 * @brief Reader sınıfındaki ReadWithAllPath fonksiyonunu çağırarak bunu gerçekleştirir.
 * @brief Son olarakta okunan dosyanın ilk child'ını pugi::xml_node türündeki node değişkenine atar.
 * @param xmlName : Reader sınıfındaki ReadWithAllPath fonksyionu için  gerekli olan dosya adını ve PATH'i verir.
 */
void Parser::ReadXMLWithFullPath(string Path)
{
    getReader().ReadWithAllPath(Path);
    node = getReader().getXMLFile().first_child();
    string root = "root";
    string nRoot = node.name();
    while(nRoot.compare(root) == 0)
    {
        node = node.first_child();
        nRoot = node.name();
    }
}
/**
 * @brief Parse işlemi başlatılmadan önce daha öncesinde Parser sınıfındaki node değişkenine atanmış
 * \n XML ağaç yapısının ilk child'ının parent hash değeri (yani root'un hash değeri) xml sınıfındaki RootHashValue değişkenine atanır.
 * @brief Bunun ardından recursive olarak çalışan addSiblings() fonksiyonu parametre olarak Parser sınıfındaki node değişkenini alır ve fonksiyon çalışır.
 * @brief Son olarkta Okunan XML dosyasındaki attribute isimleri xml sınıfındaki attributes vector'üne atanır
 */
void Parser::parse()
{
    getXML().setRootHashValue(getNode().parent().hash_value());
    addSiblings(getNode());
    getXML().setAttributes();
}
/**
 * @brief Tekrar okuma işlemi için Parser sınıfında oluşturulan xmlp ve reader objeleri sıfırlanır.
 */
void Parser::resetParser()
{
    xmlp.resetXMLMap();
    reader.resetReader();
}
/// @return Parser sınıfındaki okunan XML dosyasının ilk child'ını döndürür.
pugi::xml_node& Parser::getNode() { return node; }
/// @brief Statik bir değişken olan rootParents'ı tanımlar
int Parser::rootParents = 0;
/// @brief Statik bir değişken olan rootParents'ı +1 arttırır
void Parser::upRootParent() { rootParents++; }
/// @return Statik bir değişken olan rootParents'ı döndürür
int Parser::getRootParent() { return rootParents; }
/// @brief Parser sınıfındaki reader objesini döndürür
Reader& Parser::getReader() { return reader; }
/// @brief Parser sınıfındaki xmlp objesini döndürür
xml& Parser::getXML() { return xmlp; }
/**
 * @brief Girdi olarak verilen pugi::xml_node objesinin okunma sırasında başka çocuklaroı var mı diye kontrol eder.
 * @param x : kontrol edilecek pugi::xml_node objesidir.
 * @return Kontrol sonucunda eğer girdi olarak verilen pugi::xml_node objesinin çocukları varsa true, yoksa false değeri döndürülür
 */
bool Parser::checkSiblings(pugi::xml_node &x)
{
    string a = x.name();
    if (a== "") { if (getXML().getParentLayer() != 0) getXML().downParentLayer(); return false; }
    else { getXML().upParentLayer(); return true; }
}
/**
 * @brief Girdi olarak verilen pugi::xml_node objesinin okunma sırasında tag_value değeri var mı diye kontrol eder.
 * @param x : kontrol edilecek pugi::xml_node objesidir.
 * @return Kontrol sonucunda eğer girdi olarak verilen pugi::xml_node objesinin tag_value değeri varsa true, yoksa false değeri döndürülür
 */
bool Parser::checkChild(pugi::xml_node& x)
{
    string a= x.child_value();
    if (a == "") { return false; }
    else { return true; }
}
/**
 * @brief Recursive olarak çalışan ve okunan XML dosyasının her node'unu kontrol eden fonksiyonumuzdur.
 * \n Girdi olarak alınan pugi::xml_node objesinin önce kendi Tag Name, Tag Value ve Attributes özellikleri alınır.
 * \n İlk başta girdi olarak verilen objede herhangi bir yapı olup olmadığı kontrol edilir. \n
 * \n Daha sonrasında bu girdi olarak verilen node'un tag_value değeri var mı diye kontrol edilir. Eğer tag_value değeri varsa okunur.
 * \n Bulunduğumuz node'da okuduğumuz değerler xml sınıfı fonksiyonu olans setXMLMap() fonksiyonu ile kayıt edilir.
 * \n Son işlemde öncelikle elimizdeki node objesinden bir tempChild objesi oluşturulur ve tekrar addSiblins fonksiyonu çağrılır.
 * \n Eğer tempChild objesi bir node içeriyor ise yukarıda anlatılan işlemler bu tempChild objesi içinde gerçekleştirilir.
 * \n Eğer tempChild objesinde bir node yoksa tekrardan geri döner ve node objesinden bir tempNode oluştururuz. Bunu tekrardan addSiblings fonksiyonuna
 * parametre olarak veririz ve yukarıdaki işlemler bu tempNode içinde gerçekleşmiş olur.
 * @param x : İşlem yapılacak pugi::xml_node objesini alır.
 */
void Parser::addSiblings(pugi::xml_node& x)
{
    pugi::xml_node tempNode = x;
    pugi::xml_node tempChild = x.first_child();
    pugi::xml_object_range<pugi::xml_attribute_iterator> tempAttributes = x.attributes();
    string tag_n="", tag_v="";
    vector<pair<string,string>>att={};

    if (checkSiblings(tempNode))
    {
        tag_n = tempNode.name();
        if (checkChild(tempNode))
        {
            tag_v = tempNode.child_value();
        }
        for(pugi::xml_attribute x : tempAttributes) { att.push_back(make_pair(x.name(),x.value()));}
        getXML().setP(tag_n, tag_v, att);
        if (getXML().getParentLayer() == 1) {
                        upRootParent(); getXML().setXMLMap(getXML().getParentLayer(),
                        getXML().getP(), tempNode.hash_value(), tempNode.parent().hash_value()); }
        else getXML().setXMLMap(getXML().getParentLayer(),
                        getXML().getP(), tempNode.hash_value(), tempNode.parent().hash_value());
        int i = getParentLayer();
        addSiblings(tempChild);
        tempNode = tempNode.next_sibling();
        addSiblings(tempNode);
        //ROBOT FRAMEWORK
    }
}
/**
 * @brief Dosyayı kayıt etme işlemini gerçekleştirir.
 * @param filePathAndName : Kullanıcının seçtiği dosyanın kayıt edileceği adrestir.\n
 *        Kod içinde mevcut dosya üzerine işlemi de yapılmaktadır ve bu durumda parametre boş string olarak gelmektedir.
 *
 */
void Parser::saveXMLFile(string filePathAndName)
{

    pugi::xml_document saveDoc;
    auto declarationNode = saveDoc.append_child(pugi::node_declaration);
    declarationNode.append_attribute("version")    = "1.0";
    pugi::xml_node rootNode = saveDoc.append_child("root");
    saveChilds(rootNode,getXML().getParrentHashValue(0));
    if(filePathAndName == "") saveDoc.save_file(getReader().getXMLFileNameWithPath().c_str());
    else saveDoc.save_file(filePathAndName.c_str());

    writedHash.clear();
}
/**
 * @brief Recursive olarak çalışan bir fonksiyondur. Verileri XML dosyasına yazmak için kullanılır.\n
 * current objesinin eğer child'ı/child'ları olması gerekiyorsa bir tempNode oluşturulur ve bu node'a tag name, tag value ve attributes gibi
 * özellikler eklenir.\n
 * For döngüsü ile tutulan bütün node'lar gezilir ve parent hash değeri fonksiyon parametresi olan pHash değerine eşit olanları kontrol edip
 * yazılmasına yardımcı olur.
 * @param current : Verilerin yazılacağı node'dur.
 * @param pHash : node olarak gönderilen current'a en son eklenen verinin hash değeridir. Parent hash değeri bu hash değerine eşit olan child'lar current noduna
 * child olarak eklenir.
 */
void Parser::saveChilds(pugi::xml_node& current,int64_t pHash)
{
    for(int i = 0 ; i < getXML().getXMLMapSize();i++)
    {
        if(checkWritedHash(getXML().getCurrentHashValue(i))) continue;
        else if(getXML().getParrentHashValue(i) == pHash)
        {
            pugi::xml_node tempNode;
            tempNode = current.append_child(getXML().getTagAtI(i).c_str());
            tempNode.append_child(pugi::node_pcdata).set_value(getXML().getTagValueAtI(i).c_str());
            for(int j=0 ;j<getXML().getXMLMapAtI(i).first.second.attributes.size();j++)
            {
                tempNode.append_attribute(getXML().getAttributesAtI(i).at(j).first.c_str()) = getXML().getAttributesAtI(i).at(j).second.c_str();
            }
            setWritedHash(getXML().getCurrentHashValue(i));
            for(int s=0+i ;s<getXML().getXMLMapSize();s++)
            {
                if(getXML().getCurrentHashValue(i)== getXML().getParrentHashValue(s))
                {
                    saveChilds(tempNode,getXML().getCurrentHashValue(i));
                }
            }
        }
    }
}
/**
 * @brief Dosyaya yazma işlemi sırasında dosyaya yazılan node'ların hashlerinin ekli olduğu writedHash vector'u içinde kontrol işlemi yapılır.
 * @param x : Kontrol edilecek hash değeri.
 * @return Eğer hash değeri döndürülen node daha önce XML dosyasına eklenmişse true değeri döndürür, eklenmemişse false değeri döndürür
 */
bool Parser::checkWritedHash(int64_t x)
{
    for (int i = 0; i < writedHash.size(); i++) if (x == getWritedHash(i)) return true;
    return false;
}
/**
 * @brief writedHash vector'ünün belirli bir elemanını döndürür.
 * @param i : istenilen elemanın indexi.
 * @return istenilen hash değeri döndürülür.
 */
int64_t Parser::getWritedHash(int i)
{
    return writedHash[i];
}
/**
 * @brief Kayıt edilen node'ların hash değerlerini writedHash vector'üne eklenir.
 * @param hash : eklenecek hash değeridir.
 */
void Parser::setWritedHash(int64_t hash)
{
    writedHash.push_back(hash);
}

