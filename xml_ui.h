#ifndef XML_UI_H
#define XML_UI_H

#include <QMainWindow>
#include <QAbstractItemView>
#include <QTreeView>
#include <QTreeWidgetItem>
#include <QRect>
#include <QPainter>
#include <QColor>
#include "Parser.h"
#include "Edit_UI.h"
#include "FileSystem.h"
#include <stdexcept>
#include <stdio.h>
#include <QObject>
#include <QMenu>


QT_BEGIN_NAMESPACE
namespace Ui { class XML_ui; }
QT_END_NAMESPACE
using namespace std;
///
/// \brief Programın ana penceresi, işlemler bu pencerede yapılan işlemlere göre gerçekleşir
///
class XML_ui : public QMainWindow , protected Parser
{
    Q_OBJECT

public:
    /// @brief XML_ui yapıcı fonksiyonu
    XML_ui(QWidget *parent = nullptr);
    /// @brief XML_ui yıkıcı fonksiyonu
    ~XML_ui();
    /// @brief XML_ui penceresi üzerinde gerekli ayarlamaların yapılmasını sağlar
    void display();
    /// @brief XML_ui penceresinde QTreeWidget'da verilerin gösterilme sürecini başlatır
    void displayXML(QTreeWidgetItem*,int);
    /// @brief XML_ui penceresinde QListView'da ayarlanan konumdaki .xml uzantılı dosyaları bastırır
    void displayXMLs();
    /// @brief Parser sınıfından bir obje oluşturur
    void setXML_Parser();
    /// @brief Seçilen dosyanın okuma işlemini başlatır
    void setXML_Reader(string);
    /// @brief QTreeWidget üzerine verileri yazar
    void setTexts(QTreeWidgetItem*,int);
    /// @brief Parser sınıfından oluşturulan objeyi döndürür
    Parser& getXML_Parser();
    /// @brief XML_ui için pencere oluşturur
    Ui::XML_ui *ui;
    /// @brief Verilen hash değerine denk gelen QTreeWidget üzerinde gösterilen item'ı döndürür
    QTreeWidgetItem* getWidgetItem(int64_t);
    /// @brief QTreeWidget üzerinde seçilen item'ın hash değerini döndürür
    int64_t getHashItem(QTreeWidgetItem*);
    /// @brief QTreeWidget'ı temizler
    void freeQTWI();
    /// @brief QTreeWidget'a eklenen verilerin tutulduğu verctor QTWI'yı döndürür
    vector < pair < int64_t, QTreeWidgetItem* >> &getQTWI();
    /// @brief İlk okuma işlemi yapılana kadar etkin olmaması gerekn XML_ui penceresinin elemanlarını kapatır
    void widgetDisabled(bool);
    /// @brief Arama işlemi için gerekli işlemler yapılır
    void search(string, string, vector<pair<string,string>>&);
    /// @brief widgetDisabled için en son hangi bool değerin verildiğini döndürür
    bool getdisabledVar();
    /// @brief widgetDisabled için verilen bool değeri kaydeder
    void setdisabledVar(bool);
    /// @brief QTreeWidget'a eklenen header label'ları döndürür
    QStringList& getTreeWidgetHeaderLabels();
    /// @brief QTreeWidget'a eklenen header label'a yeni eleman ekler
    void addTreeWidgetHeaderLabels(QString label);
    /// @brief QTreeWidget header'larını ayarlar
    void setQTreeWidgetHeaders();

private slots:
    /// @brief QTreeWidget üzerinde tıklanan widget'ın bilgilerini kaydetmek için kullanılır
    void on_treeWidget_itemClicked(QTreeWidgetItem*, int);
    /// @brief XML_ui penceresinde add child butonu tıklandığı zaman çağrılır
    void on_addButton_clicked();
    /// @brief XML_ui penceresinde delete child butonu tıklandığı zaman çağrılır
    void on_deleteButton_clicked();
    /// @brief XML_ui penceresinde edit child butonu tıklandığı zaman çağrılır
    void on_editButton_clicked();
    /// @brief XML_ui penceresinde refresh butonu tıklandığı zaman çağrılır
    void on_refreshButton_clicked();
    /// @brief XML_ui penceresinde search butonu tıklandığı zaman çağrılır
    void on_searchButton_clicked();
    /// @brief XML_ui penceresinde save butonu tıklandığı zaman çağrılır
    void on_saveButton_clicked();
    /// @brief XML_ui penceresinde load butonu tıklandığı zaman çağrılır
    void on_okButton_2_clicked();
    /// @brief XML_ui penceresinde listWidget üzerinde seçim yapıldığında çağrılır
    void on_listWidget_currentTextChanged(const QString &currentText);
    /// @brief XML_ui penceresinde select butonu tıklandığı zaman çağrılır
    void on_okButton_clicked();
    /// @brief XML_ui penceresinde add attribute butonu tıklandığı zaman çağrılır
    void on_addAttButton_clicked();
    /// @brief QTreeWidget üzerinde sağ click yapıldığında menü açar
    void on_treeWidget_customContextMenuRequested(const QPoint &pos);
    /// @brief Delete Attribute için kullanılır
    void on_pushButton_2_clicked();

private:
    /// @brief Parser sınıfından bir obje oluşturulur
    Parser xml_parser;
    /// @brief QTreeWidget'a eklenen verileri tutar
    vector<pair<int64_t, QTreeWidgetItem* >> QTWI;
    /// @brief QTreeWidget'da eklenecek ilk eleman (diğerleri bunun için yazılır)
    QTreeWidgetItem* root;
    /// @brief QTreeWidget üzerinde seçilen item'ın verilerini tutar
    pair<int, QTreeWidgetItem*> tempSelectedWidgetItem;
    /// @brief Load file için seçilen dosyanın adını kaydeder
    string tempSelectedFileName;
    /// @brief widgetDisabled için verilen bool girdiyi tutar
    bool disabled;
    /// @brief QTreeWidget'ın header'ına yazılacak verileri tutar
    QStringList treeWidgetHeaderLabels;

};
#endif // XML_UI_H
