#include "xml_ui.h"
#include "./ui_xml_ui.h"
///
/// \brief XML_ui::XML_ui
/// XML_ui yapıcı fonksiyonu
/// \param parent
///
XML_ui::XML_ui(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::XML_ui)
    , root(new QTreeWidgetItem())
{
    ui->setupUi(this);
    widgetDisabled(true);
}
///
/// \brief XML_ui yıkıcı fonksiyonu
///
XML_ui::~XML_ui()
{
    delete ui;
}
///
/// \brief XML_ui::freeQTWI
/// QTreeWidgetItem'larının hash'lerle beraber tutulduğu QTWI vector'ünü temizler
/// \n (for_each fonksiyonu ile de yapılabilir)
///
void XML_ui::freeQTWI()
{
    for(int i = 0 ;i< getQTWI().size() ;i++)
    {
        QTreeWidgetItem* item = getQTWI().at(i).second;
        getQTWI().erase(getQTWI().begin() + i);
    }
    getQTWI().resize(0);
    getQTWI().shrink_to_fit();
    QTWI.clear();
}
///
/// \brief XML_ui::getQTWI
/// \return QTreeWidgetItem'larının hash'lerle beraber tutulduğu QTWI vector'ünü döndürür
///
vector<pair<int64_t, QTreeWidgetItem*>>& XML_ui::getQTWI() { return QTWI; }
///
/// \brief XML_ui::widgetDisabled
/// İlk dosya okuma işlemi yapılana kadar girdiye göre diğer elemanların açık veya kapalı olacağını ayarlar
/// \param x : bool girdi
///
void XML_ui::widgetDisabled(bool x)
{
    setdisabledVar(x);
    ui->addButton->setDisabled(x);
    ui->deleteButton->setDisabled(x);
    ui->editButton->setDisabled(x);
    ui->refreshButton->setDisabled(x);
    ui->saveButton->setDisabled(x);
    ui->treeWidget->setDisabled(x);
    ui->searchButton->setDisabled(x);
    ui->addAttButton->setDisabled(x);
    ui->pushButton_2->setDisabled(x);
}
///
/// \brief XML_ui::search
/// Arama işlemi yapılırken hangi verilere göre arama yapılacağı ilk olarak bu fonksiyon içinde belirlenir.
/// \n Sadece seçilen girdilere göre arama yapılır.
/// \n Son olarak bulunan item'lar seçili olarak QTreeWidet üzerinde görülebilir
/// \n Bu seçim işlemi MultipleSelection ile yapılır
/// \param tagName : Arama yapılması istenen tag name (var ise)
/// \param tagValue : Arama yapılması istenen tag value (var ise)
/// \param atts : Arama yapılması istenen attribute'lar (var ise)
///
void XML_ui::search(string tagName , string tagValue , vector<pair<string,string>>&atts)
{
    vector<int64_t> Searched;
    if      (tagName != "" && tagValue != "" && atts.size() == 0)
        Searched = getXML_Parser().getXML().getHashesForTNTV(tagName,tagValue);
    else if (tagName != "" && tagValue == "" && atts.size() == 0)
        Searched = getXML_Parser().getXML().getHashesForTN(tagName);
    else if (tagName == "" && tagValue != "" && atts.size() == 0)
        Searched = getXML_Parser().getXML().getHashesForTV(tagValue);
    else if (tagName == "" && tagValue == "" && atts.size() != 0)
        Searched = getXML_Parser().getXML().getHashesForAtts(atts);
    else if (tagName == "" && tagValue != "" && atts.size() != 0)
        Searched = getXML_Parser().getXML().getHashesForAttsTV(tagValue,atts);
    else if (tagName != "" && tagValue == "" && atts.size() != 0)
        Searched = getXML_Parser().getXML().getHashesForAttsTN(tagName,atts);
    else if (tagName != "" && tagValue != "" && atts.size() != 0)
        Searched = getXML_Parser().getXML().getHashesForAttsTNTV(tagName,tagValue,atts);

    ui->treeWidget->setSelectionMode(QAbstractItemView::MultiSelection);
    for (int i = 0; i < Searched.size(); i++)
    {
        getWidgetItem(Searched[i])->setSelected(true);
    }
    ui->treeWidget->setSelectionMode(QAbstractItemView::SingleSelection);
}
///
/// \brief XML_ui::getdisabledVar
/// \return widgetDisabled için en son verilmiş bool değeri döndürür
///
bool XML_ui::getdisabledVar()
{
    return disabled;
}
///
/// \brief XML_ui::setdisabledVar
/// \param x : widgetDisabled için en son verilmiş bool değeridir, disabled değişkenine atanır
///
void XML_ui::setdisabledVar(bool x)
{
    disabled = x;
}
///
/// \brief XML_ui::getWidgetItem
/// İstenen hash değeri için QTreeWidgetItem'ı arar ve döndürür
/// \param Hash : istenen item'ın hash değeri
/// \return İstenen hash değerine karşılık gelen QTreeWidgetItem'ı döndürür
///
QTreeWidgetItem* XML_ui::getWidgetItem(int64_t Hash)
{
    for(int i = 0 ; i < getQTWI().size(); i++)
    {
        if (getQTWI().at(i).first == Hash) return getQTWI().at(i).second;
    }
    return NULL;
}
///
/// \brief XML_ui::getHashItem
/// Seçilen widgetItem'a karşılık gelen hash değerini arar ve döndürür
/// \param widgetItem : seçilen widgetItem
/// \return İstenen widgetItem'a karşılık gelen hash değerini döndürür
///
int64_t XML_ui::getHashItem(QTreeWidgetItem* widgetItem)
{
    for (int i = 0; i < getQTWI().size(); i++)
    {
        if (getQTWI().at(i).second == widgetItem) return getQTWI().at(i).first;
    }
    return 0;
}
///
/// \brief XML_ui::setXML_Parser
/// Parse işlemini başlatır
///
void XML_ui::setXML_Parser() { getXML_Parser().parse(); }
///
/// \brief XML_ui::setXML_Reader
/// Seçilen dosya için okuma işlemini başlatır
/// \param fileName : Seçilen dosya
///
void XML_ui::setXML_Reader(string fileName) { getXML_Parser().ReadXML(fileName); }
///
/// \brief XML_ui::getXML_Parser
/// \return Parser sınıfının objesini döndürür
///
Parser& XML_ui::getXML_Parser() { return xml_parser; }
///
/// \brief XML_ui::getTreeWidgetHeaderLabels
/// \return QTreeWidget'da header olarak yazılı olan verileri döndürür
///
QStringList &XML_ui::getTreeWidgetHeaderLabels() {return treeWidgetHeaderLabels;}
///
/// \brief XML_ui::addTreeWidgetHeaderLabels
/// QTreeWidget'ın header kısmında yazılı olan verileri döndürür
/// \param label : eklenmek istenen attribute name
///
void XML_ui::addTreeWidgetHeaderLabels(QString label) { treeWidgetHeaderLabels.push_back(label);}
///
/// \brief XML_ui::setQTreeWidgetHeaders
/// QTreeWidget header'ı için gerekli olan verileri düzenler.
/// \n Default olarak Tag Name ve Tag Value yazılır.
/// \n Eğer varsa okunan dosyaya ait attribute  name'ler de yazılır
///
void XML_ui::setQTreeWidgetHeaders()
{
    getTreeWidgetHeaderLabels().clear();
    ui->treeWidget->setColumnCount(0);
    addTreeWidgetHeaderLabels("Tag Name");
    addTreeWidgetHeaderLabels("Tag Value");
    for(string an : getXML_Parser().getXML().getAttributes())
        addTreeWidgetHeaderLabels(QString::fromStdString(an));
    ui->treeWidget->setHeaderLabels(getTreeWidgetHeaderLabels());
}
///
/// \brief XML_ui::display
/// XML_ui penceresi üzerinde gerekli düzenlemeler yapılır
/// \n .xml uzantılı dosyalar listWidget'a yazılır
/// \n QTreeWidget'a header'lar eklenir
/// \n
///
void XML_ui::display()
{
    setQTreeWidgetHeaders();
    root = new QTreeWidgetItem();
    root->setText(0, "root");
    getQTWI().push_back(make_pair((int64_t)getXML_Parser().getXML().getRootHashValue(), root));
    ui->treeWidget->addTopLevelItem(root);
    for (int i = 0; i < getXML_Parser().getXML().getXMLMapSize(); i++) displayXML(root, i);
    ui->treeWidget->expandAll();
}
///
/// \brief XML_ui::displayXMLs
/// Belirlenen konumdaki .xml uzantılı dosyaların gösterimi yapılır
///
void XML_ui::displayXMLs()
{
    char buffer[128];
    //cd /Users/hrndr/Desktop/tubitak_calismalar  && ls | grep '\\.xml'
    FILE* pipe = _popen("dir /B %userprofile%\\Desktop\\*.xml", "r");
    if (!pipe) { return; }
    while (!feof(pipe)) { if (fgets(buffer, 128, pipe) != NULL) ui->listWidget->addItem(buffer); }
    _pclose(pipe);
}
///
/// \brief XML_ui::displayXML
/// \param current
/// \param currentInt
///
void XML_ui::displayXML(QTreeWidgetItem* current,int currentInt)
{
    QTreeWidgetItem* parent = getWidgetItem(getXML_Parser().getXML().getParrentHashValue(currentInt));
    QTreeWidgetItem* child = new QTreeWidgetItem();

    if(parent == NULL)
    {
        setTexts(child, currentInt);
        current->addChild(child);
    }
    else
    {
        setTexts(child, currentInt);
        parent->addChild(child);
    }
}
///
/// \brief XML_ui::setTexts
/// Belirli bir QTreeWidgetItem objesi için xml sınıfından depolanmış vector'den verilen index'deki XML bilgileri girilir.
/// \param item : Verilerin girileceği QTreeWidgetItem objesi referansı
/// \param i : xml sınıfında tutulan veri vector'ünden hangi elemana ait olan verilerin alınacağını belirtir
///
void XML_ui::setTexts(QTreeWidgetItem* item, int i)
{
    /**
            getXML_Parser()             => Return reference of xml_parser variable that beint64_ts to Parser class in XML_ui->h
            getXML()                    => Return reference of xmlp variable that beint64_ts to xml class in Parser.h
            getXMLMap()                 => Return reference of xmlMap vector that beint64_ts to vector class in xml.h
            getTagAtI(i)                => Return tag_name variable that beint64_ts to Node struct of xmlMap[i] in xml.h
            getTagValueAtI(i)           => Return tag_value variable that beint64_ts to Node struct of xmlMap[i] in xml.h
            getAttributeAtI(i)          => Return attribute_name variable that beint64_ts to Node struct of xmlMap[i] in xml.h
            getAttributeValueAtI(i)     => Return attribute_value variable that beint64_ts to Node struct of xmlMap[i] in xml.h
        */
    item->setText(0, QString::fromStdString(getXML_Parser().getXML().getTagAtI(i)));
    item->setText(1, QString::fromStdString(getXML_Parser().getXML().getTagValueAtI(i)));
    for(int j = 0 ; j < getXML_Parser().getXML().getAttributesAtI(i).size() ; j++)
    {
        for(int t=0;t<getXML_Parser().getXML().getAttributes().size();t++)
            if(getXML_Parser().getXML().getAttributes().at(t).compare(getXML_Parser().getXML().getAttributesAtI(i).at(j).first)==0)
                item->setText(2+t,QString::fromStdString(getXML_Parser().getXML().getAttributesAtI(i).at(j).second));
    }
    getQTWI().push_back(make_pair((int64_t)getXML_Parser().getXML().getCurrentHashValue(i), item));
}
///
/// \brief XML_ui::on_treeWidget_itemClicked
/// treeWidget üzerinde seçilen satırın QTreeWidgetItem pointer'ı ve kolonda tıklandığı tempSelectedWidgetItem'a kaydedilir
/// \param item : Seçilen QTreeWidgetItem
/// \param column : Seçilen kolon
///
void XML_ui::on_treeWidget_itemClicked(QTreeWidgetItem* item, int column)
{
    tempSelectedWidgetItem.first = column;
    tempSelectedWidgetItem.second = item;
}
///
/// \brief XML_ui::on_addButton_clicked
/// treeWidget üzerinde seçili satıra yeni child ekleme işlemini gerçekleştirir.
/// \n Edit_UI sınıfından bir obje oluşturur ve bu obje aracılığı ile bir pencere açılır.
/// \n Bu bencere Add işlemi için hazır hale getirilir (bütün değerler boştur sadece
/// xml sınıfından getAttributes fonksiyonu ile attribute name'leri parametre olarak veririr.)
/// İşlem tamamlandığında yine xml sınıfına ait olan setXMLMap fonksiyonu ile ekleme işlemi tetiklenir.
/// Bu fonksiyonun girdiler ise Edit_UI sınıfından oluşturduğumuz pencerede giriler verilerden gelir.
///
void XML_ui::on_addButton_clicked()
{
    Edit_UI *tempUI = new Edit_UI();
    tempUI->setUI("","",getXML_Parser().getXML().getAttributes());
    tempUI->show();
    setDisabled(true);
    QObject::connect(tempUI, &Edit_UI::ButtonClick, this,[=] ()
                     {
                         int index = getXML_Parser().getXML().getXMLMapAtHash(getHashItem(tempSelectedWidgetItem.second));
                         if (tempSelectedWidgetItem.second == root)
                         {

                         }
                         else
                         {
                            getXML_Parser().getXML().setXMLMap(getXML_Parser().getXML().getXMLLayer(index)+ 1
                                                                ,tempUI->getEditNodeTN()
                                                                ,tempUI->getEditNodeTV()
                                                                ,tempUI->getEditNodeAtts()
                                                                ,rand() % 100000
                                                                ,getHashItem(tempSelectedWidgetItem.second));
                         }
                         setDisabled(false);
                         getXML_Parser().saveXMLFile("");
                         on_refreshButton_clicked();
                     });
    QObject::connect(tempUI, &Edit_UI::closeEdit, this, [=]()
                     {
                         setDisabled(false);
                         if (getdisabledVar() == true) widgetDisabled(true);
                         on_refreshButton_clicked();
                     });

}
///
/// \brief XML_ui::on_deleteButton_clicked
/// treeWidget üzerinde seçili satırın silinme işlemini gerçekleştirir.
///
void XML_ui::on_deleteButton_clicked()
{
    int64_t hashItem = getHashItem(tempSelectedWidgetItem.second);
    getXML_Parser().getXML().removeChild(hashItem);
    getXML_Parser().getXML().Remove();
    getXML_Parser().saveXMLFile("");
    on_refreshButton_clicked();
}
///
/// \brief XML_ui::on_editButton_clicked
/// treeWidget üzerinde seçili olan satır için işlem gerçekleştirilir.
/// Edit_UI sınıfından bir obje oluşturulur ve bu obje aracılığı ile bir pencere açılır.
/// \n Seçilen satırın bilgilerinden xml sınıfında depolanmış olan hangi node'a denk geldiği bulunur.
/// \n Daha sonra seçilen satırın verileri Edit_UI ile beraner açılan yeni pencerede kullanılması için setUI() fonksiyonuna girdi olarak verilir.
/// \n İşlemin tamamlanmasının ardından xml sınıfına ait editXMLMap() fonksiyonuna geçici objede tutulan xml bilgileri parametre olarak verilir.
///
void XML_ui::on_editButton_clicked()
{
    Edit_UI* tempUI = new Edit_UI();
    int index = getXML_Parser().getXML().getXMLMapAtHash(getHashItem(tempSelectedWidgetItem.second));
    if(getXML_Parser().getXML().chechkHasChild(getHashItem(tempSelectedWidgetItem.second)))
    {
        tempUI->hideTagValueForParent();
    }
    tempUI->setUI(getXML_Parser().getXML().getTagAtI(index),
                  getXML_Parser().getXML().getTagValueAtI(index),
                  getXML_Parser().getXML().getAttributesAtI(index),
                  getXML_Parser().getXML().getAttributes());
    tempUI->show();
    setDisabled(true);
    QObject::connect(tempUI, &Edit_UI::ButtonClick, this, [=]()
                     {
                         if (tempSelectedWidgetItem.second == root)
                         {

                         }
                         else
                         {
                            getXML_Parser().getXML().editXMLMap( index
                                                                , getXML_Parser().getXML().getXMLLayer(index)
                                                                , tempUI->getEditNodeTN()
                                                                , tempUI->getEditNodeTV()
                                                                , tempUI->getEditNodeAtts()
                                                                , getXML_Parser().getXML().getCurrentHashValue(index)
                                                                , getXML_Parser().getXML().getParrentHashValue(index));
                         }
                         setDisabled(false);
                         getXML_Parser().saveXMLFile("");
                         on_refreshButton_clicked();
                     });

    QObject::connect(tempUI, &Edit_UI::closeEdit, this, [=]()
                     {
                         setDisabled(false);
                         if (getdisabledVar() == true) widgetDisabled(true);
                         on_refreshButton_clicked();
                     });
}
///
/// \brief XML_ui::on_refreshButton_clicked
/// QTreeWidget içeriğini yeniden yazmak için kullanılır. QTWI vector'ü ve treeWidget temizlenir. Ardından tekrar display() fonksiyonu çağrılır
///
void XML_ui::on_refreshButton_clicked()
{
    freeQTWI();
    ui->treeWidget->clear();
    display();
}
///
/// \brief XML_ui::on_searchButton_clicked
/// xml sınıfında depolanmış XML verileri içinde arama işlemi yapılır.
/// \n Edit_UI sınıfından geçici bir obje oluşturulur. Bu obje aracılığı ile açılan pencereden aranmak istenen tag name, tag value veya attribute name ve value ikilisi
/// alınır. Bu veriler alınarak xml_ui sınıfına ait olan search fonksiyonu ile arama işlemi yapılması için parametre olarak verilir.
///
void XML_ui::on_searchButton_clicked()
{

    Edit_UI* tempUI = new Edit_UI();
    tempUI->setUI("","",getXML_Parser().getXML().getAttributes());
    tempUI->show();
    setDisabled(true);
    QObject::connect(tempUI, &Edit_UI::ButtonClick, this, [=]()
                     {
                         search(tempUI->getEditNodeTN(),tempUI->getEditNodeTV(),tempUI->getEditNodeAtts());
                         setDisabled(false);
                         //on_refreshButton_clicked();
                     });
    QObject::connect(tempUI, &Edit_UI::closeEdit, this, [=]()
                     {
                         setDisabled(false);
                         if (getdisabledVar() == true) widgetDisabled(true);
                         //on_refreshButton_clicked();
                     });

}
///
/// \brief XML_ui::on_saveButton_clicked
/// Program üzerinde işlenen xml verilerinin istenilen konumda istenilen isimle tekrar kayıt edilmesini sağlar.
/// \n FileSystem sınıfından geçici bir obje oluşturulur. Bu obje aracılığı ile açılan pencere editYUforSave() fonksiyonu ile düzenlenir.
/// \n Seçilen dosya dizini ve dosya adı save işlemi için alınır ve Parser sınıfına ait saveXMLFile() fonksiyonu ile save işlemi gerçekleştirilir.
///
void XML_ui::on_saveButton_clicked()
{
    FileSystem* tempFileUI = new FileSystem();
    tempFileUI->editUIforSave();
    tempFileUI->show();
    setDisabled(true);
    QObject::connect(tempFileUI, &FileSystem::complete, this, [=]()
                     {
                         getXML_Parser().saveXMLFile(tempFileUI->getSFPN());
                         widgetDisabled(false);
                         setDisabled(false);
                         on_refreshButton_clicked();
                     });
    QObject::connect(tempFileUI, &FileSystem::exitClose, this, [=]()
                     {
                         setDisabled(false);
                         if (getdisabledVar() == true) widgetDisabled(true);
                         on_refreshButton_clicked();
                     });
}
///
/// @brief XML_ui::on_okButton_2_clicked
/// Farklı bir konumda bulunan .xml uzantılı dosyayı okuma işlemi gerçekleştirilir.
/// \n FileSystem sınıfından bir obje oluşturulur, bu obje aracılığı ile seçilen dosya dizinindeki .xml uzantılı dosya açılır.
///
void XML_ui::on_okButton_2_clicked()
{
    FileSystem* tempFileUI = new FileSystem();
    tempFileUI->editUIforLoad();
    tempFileUI->show();
    setDisabled(true);
    QObject::connect(tempFileUI, &FileSystem::complete, this, [=]()
                     {
                         getXML_Parser().resetParser();
                         getXML_Parser().ReadXMLWithFullPath(tempFileUI->getFullFilePath());
                         setXML_Parser();
                         widgetDisabled(false);
                         setDisabled(false);
                         on_refreshButton_clicked();
                     });
    QObject::connect(tempFileUI, &FileSystem::exitClose, this, [=]()
                     {
                         setDisabled(false);
                         if (getdisabledVar() == true) widgetDisabled(true);
                         on_refreshButton_clicked();
                     });

}
///
/// \brief XML_ui::on_listWidget_currentTextChanged
/// listWidget üzerinde gerçekleştirilen seçime göre dosya ismi seçilir ve tempSelectedFileName değişkenine atanır.
/// \param currentText : Seçilen dosya ismi
///
void XML_ui::on_listWidget_currentTextChanged(const QString &currentText)
{
    tempSelectedFileName = currentText.toStdString();
}
///
/// \brief XML_ui::on_okButton_clicked
/// Select butonu tetiklendiği zaman çalışır. tempSelectedFileName değişkeninde tutulan dosya ismini kullanarak dosya okuma işlemi tetiklenir.
///
void XML_ui::on_okButton_clicked()
{
    widgetDisabled(false);
    getXML_Parser().resetParser();
    setXML_Reader(tempSelectedFileName);
    setXML_Parser();
    on_refreshButton_clicked();
}
///
/// \brief XML_ui::on_addAttButton_clicked
/// Edit_UI sınıfından bir geçici bir obje yaratılır. Yeni açılan pencere setUiForAtts() fonksiyonu ile sadece attribute ekleme işlemi için pencere hazır hale gelir.
/// Edit_UI sınıfından ButtonClick() sinyali alındığı durumda seçilen QTreeWidgetItem'ın hash değeri alınır ve bu hash değerine göre eklenecek attribute name ve value
/// değerleri eklenmesi için xml sınıfına ait addAttributesToNodes() fonksiyonu çağrılır.
///
void XML_ui::on_addAttButton_clicked()
{
    Edit_UI* tempUI = new Edit_UI;
    tempUI->setUiForAtts();
    tempUI->show();

    QObject::connect(tempUI, &Edit_UI::ButtonClick, this, [=]()
                     {
                        getXML_Parser().getXML().addAttributesToNodes(getHashItem(tempSelectedWidgetItem.second)
                                                      ,tempUI->getTemp().first,tempUI->getTemp().second);
                        addTreeWidgetHeaderLabels(QString::fromStdString(tempUI->getTemp().first));
                        setDisabled(false);
                        ui->treeWidget->setHeaderLabels(getTreeWidgetHeaderLabels());
                        getXML_Parser().getXML().addAttributes(tempUI->getTemp().first);
                        getXML_Parser().saveXMLFile("");
                        on_refreshButton_clicked();

                     });
    QObject::connect(tempUI, &Edit_UI::closeEdit, this, [=]()
                     {
                        setDisabled(false);
                        if (getdisabledVar() == true) widgetDisabled(true);
                     });
}
///
/// \brief XML_ui::on_pushButton_2_clicked
///
void XML_ui::on_pushButton_2_clicked()
{

}

///
/// \brief XML_ui::on_treeWidget_customContextMenuRequested
/// Seçilen treeWidgetItem'a ait bir menu açılır ve bu menu üzerinde add,delete ve edit işlemleri için seçenekler çıkar.
/// \n Seçilen seçeneğe göre işlemler tetiklenir.
/// \param pos : Seçilen treeWidgetItem'ın konumu
///
void XML_ui::on_treeWidget_customContextMenuRequested(const QPoint &pos)
{
    QModelIndex index = ui->treeWidget->indexAt(pos);
    QTreeWidgetItem* item = ui->treeWidget->currentItem();

    QMenu *menu = new QMenu(this);

    QAction *addChildAction = new QAction("Add Child to Selected Item", this);
    connect(addChildAction, SIGNAL(triggered()), this, SLOT(on_addButton_clicked()));
    menu->addAction(addChildAction);

    QAction *editAction = new QAction("Edit Selected Item", this);
    connect(editAction, SIGNAL(triggered()), this, SLOT(on_editButton_clicked()));
    menu->addAction(editAction);

    QAction *deleteAction = new QAction("Delete Selected Item", this);
    connect(deleteAction, SIGNAL(triggered()), this, SLOT(on_deleteButton_clicked()));
    menu->addAction(deleteAction);

    menu->popup(ui->treeWidget->viewport()->mapToGlobal(pos));
}


