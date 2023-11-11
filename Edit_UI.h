#ifndef EDIT_UI_H
#define EDIT_UI_H

#include <QWidget>
#include <QTimer>
#include <QObject>
#include <QThread>
#include <algorithm>
#include <QKeyEvent>
#include <QEvent>
#include <QMessageBox>


namespace Ui {

class Edit_UI;
}
using namespace std;
/**
 * @brief XML classında tutulduğu gibi XML dosyasındaki node'lar için gerekli olan veriler tutulmaktadır
 * @param tag_name : tag name
 * @param tag_value : tag value
 * @param atts : attribute name ve value'leri
 */
struct node
{
    string tag_name;
    string tag_value;
    vector<pair<string,string>> atts;
};
///
/// \brief xml_ui üzerinde seçilen item'ların düzenleme işlemlerini, yeni child ekleme işlemlerini yapmak için kullanılan sınıf
///
class Edit_UI : public QWidget
{
    Q_OBJECT

public:
    /// \brief EDIT_UI yapıcı fonksiyonu
    explicit Edit_UI(QWidget *parent = nullptr);
    /// \brief EDIT_UI yıkıcı fonksiyonu
    ~Edit_UI();
    /// \brief Gerçekleştirilen işlem sonrası değişiklikleri node yapısına kaydeder
    void setEditNode(string, string, vector<pair<string,string>>&);
    /// \brief node yapısındaki tag_name değerini döndürür
    string getEditNodeTN();
    /// \brief node yapısındaki tag_value değerini döndürür
    string getEditNodeTV();
    /// \brief node yapısındaki atts vector'ünü döndürür
    vector<pair<string,string>>& getEditNodeAtts();
    /// \brief xml_ui penceresinden Edit işlemi çağrıldığında seçilen item'ın verileri bu fonksiyon ile EDIT_UI penceresi için ayarlanır
    void setUI(string, string, vector<pair<string,string>>&,vector<string>&);
    /// \brief xml_ui penceresinden Add işlemi çağrıldığında EDIT_UI penceresi ayarlanır
    void setUI(string, string, vector<string>&);
    /// \brief ComboBox içinde gösterilmesi gereken attribute name'leri ekler
    void setAttsCombo(vector<string>&);
    /// \brief ComboBox içindeki attribute name'leri döndürür
    vector<string>& getAttsCombo();
    /// \brief ComboBox'da seçilen attribute name, seçilen node'da varmı kontrolünü yapar
    bool checkAttsContain(string);
    /// \brief xml_ui penceresinden Add Attribute işlemi için EDIT_UI penceresi ayarlanır
    void setUiForAtts();
    /// \brief Enter tuşu basıldımı kontrolü yapar
    void keyPressEvent(QKeyEvent* event);
    /// \brief Add Attribute işlemi sırasındaki verileri kaydeder
    void setTemp(string,string);
    /// \brief Add Attribute işlemi için olan girdileri döndürür
    pair<string,string>& getTemp();
    /// \brief
    void hideTagValueForParent();

private:
    /// \brief Edit_UI için pencere oluşturur
    Ui::Edit_UI *ui_edit;
    /// \brief node yapısı için bir örnek oluşturur
    node n;
    /// \brief ComboBox üzerinde seçilen değeri tutar
    string selectedItem;
    /// \brief Close event için timer
    QTimer* timer;
    /// \brief ComboBox'daki attribute name'ler
    vector<string> attsCombo;
    /// \brief Add Attribute işlemi için girilen string'ler
    pair<string,string> temp;

public slots:
    /// \brief Yapılan işlemi tamamlamak için kullanılır
    void on_pushButton_clicked();
    /// \brief Pencere üzerinde kapatma işlmei uygulandığında kullanılır
    void on_Close();

signals:
    /// \brief Tamamlandı sinyali
    void ButtonClick();
    /// \brief Pencere kapatıldı sinyali
    void closeEdit();

private slots:
    /// \brief ComboBox üzerindeki seçili item değiştiğinde gerekli işlemleri yapar
    void on_attributeCombo_currentIndexChanged(int index);
    /// \brief Tag name değeri girildiğinde kaydeder
    void on_Tag_Name_textChanged(const QString &arg1);
    /// \brief Tag value değeri girildiğinde kaydeder
    void on_Tag_Value_textChanged(const QString &arg1);
    /// \brief Attribute value değeri girildiğinde kaydeder
    void on_Att_Value_textChanged(const QString &arg1);
};

#endif // EDIT_UI_H
