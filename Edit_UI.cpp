#include "Edit_UI.h"
#include "ui_Edit_UI.h"
///
/// \brief Edit_UI::Edit_UI
/// Edit_UI yapıcı fonksiyonu
/// \n Gerekli ayarlamalar bu fonksiyonda yapılır. Pointer olarak oluşturulan değişkenler burada tanımlanır.
/// \n close_event için timer burada başlatılır ve checkClose() slot'una bağlanır
/// \param parent
///
Edit_UI::Edit_UI(QWidget *parent) :
    QWidget(parent),
    ui_edit(new Ui::Edit_UI)
{
    ui_edit->setupUi(this);
    ui_edit->attributeNames->setHidden(true);
    timer = new QTimer(this);
    QObject::connect(timer, SIGNAL(timeout()), this, SLOT(on_Close()));
    timer->start(500);
}
///
/// \brief Edit_UI::~Edit_UI
/// Edit_UI yıkıcı fonksiyonu
///
Edit_UI::~Edit_UI()
{
    delete ui_edit;
}
///
/// \brief Edit_UI::setTemp
/// xml_ui penceresinde Add Attribute işlemi için gerekli olan attribute name ve value değerlerini tutar
/// \param an : attribute name
/// \param av : attribute value
///
void Edit_UI::setTemp(string an, string av){ temp.first = an ; temp.second = av;}
///
/// \brief Edit_UI::getTemp
/// \return xml_ui penceresinde Add Attribute işlemi için gerekli olan attribute name ve value değerlerini döndürür
///
pair<string,string>& Edit_UI::getTemp(){return temp; }

void Edit_UI::hideTagValueForParent()
{
    ui_edit->Tag_Value->setDisabled(true);
    ui_edit->label_2->setDisabled(true);
}

///
/// \brief Edit_UI::keyPressEvent
/// xml_ui penceresinde Add Attribute işlemi için açılan penverede Enter tuşu basıldı mı kontrolü yapar ve basıldığında girilen değerler kaydedilir.
/// \param event
///
void Edit_UI::keyPressEvent(QKeyEvent *event)
{
    if( event->key() == Qt::Key_Return )
    {
        setTemp(ui_edit->attributeNames->text().toStdString(),ui_edit->Att_Value->text().toStdString());
        Edit_UI::close();
        emit(ButtonClick());
    }
}
///
/// \brief Edit_UI::setEditNode
/// xml_ui penceresinde Edit işlemi için seçilen node'un verileri gönderilir. Gönderilen bu veriler Edit_UI penceresi için ayarlanır.
/// \param tn : tag name
/// \param tv : tag value
/// \param an : attribute name ve value'leri tutan vector
///
void Edit_UI::setEditNode(string tn, string tv, vector<pair<string,string>>& an)
{
    n.tag_name = tn;
    n.tag_value = tv;
    for(int i = 0 ; i < an.size();i++)
        n.atts.push_back(make_pair(an.at(i).first,an.at(i).second));
}
///
/// \brief Edit_UI::getEditNodeTN
/// \return node yapısındaki tag name değerini döndürür
///
string Edit_UI::getEditNodeTN() { return n.tag_name; }
///
/// \brief Edit_UI::getEditNodeTV
/// \return node yapısındaki tag value değerini döndürür
///
string Edit_UI::getEditNodeTV() { return n.tag_value; }
///
/// \brief Edit_UI::getEditNodeAtts
/// \return node yapısındaki atts vector'ünü döndürür
///
vector<pair<string,string>>& Edit_UI::getEditNodeAtts() { return n.atts; }
///
/// \brief Edit_UI::setAttsCombo
/// Girdi olarak alınan attribute name'leri ComboBox'a ait olan attsCombo vector'üne atar
/// \param atts : Attribute name'ler
///
void Edit_UI::setAttsCombo(vector<string>& atts)
{
    attsCombo=atts;
}
///
/// \brief Edit_UI::getAttsCombo
/// \return ComboBox'da tutulan attribute name'leri tutan attsCombo vector'ü döndürülür
///
vector<string>& Edit_UI::getAttsCombo(){return attsCombo;}
///
/// \brief Edit_UI::setUI
/// xml_ui penceresinde Edit işlemi için seçilen item'ın verileri ayarlanır
/// \param tn : tag name
/// \param tv : tag value
/// \param atts : attribute name ve value'ler
/// \param attname : attribute name'ler (atts içindeki attribute name'lerden farklı)
///
void Edit_UI::setUI(string tn, string tv, vector<pair<string,string>>& atts,vector<string>& attname)
{
    n.atts = atts;
    setUI(tn,tv,attname);
}
///
/// \brief Edit_UI::setUI
/// xml_ui penceresinde Add işlemi için attribute name'leri ComboBox'a atar
/// \param tn : tag name (boş)
/// \param tv : tag value (boş
/// \param an : attribute name'ler
///
void Edit_UI::setUI(string tn, string tv, vector<string>& an)
{
    n.tag_name = tn;
    n.tag_value = tv;
    ui_edit->Tag_Name->setText(QString::fromStdString(tn));
    ui_edit->Tag_Value->setText(QString::fromStdString(tv));
    ui_edit->attributeCombo->blockSignals(true);
    for(int i = 0 ; i < an.size() ; i ++)
    {
        ui_edit->attributeCombo->addItem(QString::fromStdString(an.at(i)));        
    }
    setAttsCombo(an);
    selectedItem =  ui_edit->attributeCombo->itemText(0).toStdString();
    on_attributeCombo_currentIndexChanged(0);
    ui_edit->attributeCombo->blockSignals(false);
}
///
/// \brief Edit_UI::on_Close
/// Edit_UI penceresindeki kapatma işlemi gerçekleşti mi kontrolü yapar, gerçekleştiyse closeEdit() sinyali tetiklenir
///
void Edit_UI::on_Close()
{
    if (this->isHidden()) { timer->stop() ; emit(closeEdit()); }
}
///
/// \brief Edit_UI::on_pushButton_clicked
/// Add Attribute işlemi için açılan Edit_UI penceresinde yapılan işlemler tamamlandı anlamına gelir ve girilen verileri kaydeder.
/// \n Daha sonra tamamlandı anlamına gelen ButtonClick() sinyali tetiklenir
///
void Edit_UI::on_pushButton_clicked()
{
    setTemp(ui_edit->attributeNames->text().toStdString(),ui_edit->Att_Value->text().toStdString());
    Edit_UI::close();
    timer->stop();
    emit(ButtonClick());
}
///
/// \brief Edit_UI::on_attributeCombo_currentIndexChanged
/// ComboBox'da seçili indexi değiştirir. Yeni index de yazılı olan attribute name seçilir.
/// \n Sol olarakta attribute value üzerinde değişim yapıldıysa eski seçili attribute name'e ait olan attribute value değiştirilir.
/// \param index : Yeni seçilen index
///
void Edit_UI::on_attributeCombo_currentIndexChanged(int index)
{
    selectedItem =  ui_edit->attributeCombo->itemText(index).toStdString();
    int flag = 0 ;
    ui_edit->Att_Value->blockSignals(true);
    for(int i = 0 ; i < n.atts.size() ; i ++)
        if(selectedItem.compare(n.atts.at(i).first) == 0)
        {
            ui_edit->Att_Value->setText(QString::fromStdString(getEditNodeAtts().at(i).second));
            flag++;
        }
    if(flag==0) ui_edit->Att_Value->setText("");
    ui_edit->Att_Value->blockSignals(false);
}
///
/// \brief Edit_UI::on_Tag_Name_textChanged
/// Tag name için girilen yeni değeri alır. Eğer geçersiz karakterler varsa onları kontrol eder.
/// \param arg1 : tag name için girdi
///
void Edit_UI::on_Tag_Name_textChanged(const QString &arg1)
{
    string result;
    for (QChar ch : arg1)
    {
        if (ch.isLetterOrNumber() || ch.isSpace() || ch == '-')
        {
            result.push_back(ch.toLatin1());
        }
        else
        {
            QString errorMessage = QString("Geçersiz karakter: %1").arg(ch);
            QMessageBox::information(this, "Hata", errorMessage);
        }
    }
    n.tag_name = result;
}
///
/// \brief Edit_UI::on_Tag_Value_textChanged
/// Tag vale için girilen yeni değeri alır. Eğer geçersiz karakterler varsa onları kontrol eder.
/// \param arg1 : tag value için girdi
///
void Edit_UI::on_Tag_Value_textChanged(const QString &arg1)
{
    string result;
    for (QChar ch : arg1) {
        if (ch.isLetterOrNumber() || ch.isSpace() || ch == '-') {
            result.push_back(ch.toLatin1());
        }
    }

    n.tag_value = result;
}
///
/// \brief Edit_UI::checkAttsContain
/// Seçilen attribute name, seçilen item'ın attribute'ları içinde var mı diye kontrol eder.
/// \param an : ComboBox üzerinde seçilen attribute name
/// \return Kontrol sonucuna göre attribute name varsa true yoksa false döndürülür.
///
bool Edit_UI::checkAttsContain(string an)
{
    for( pair<string,string> x : getEditNodeAtts())
        if( x.first == an) return true;

    return false;
}
///
/// \brief Edit_UI::on_Att_Value_textChanged
/// Attribute value değeri için girilen değer node yapısındaki atts vector'üne eklenir.
/// \n Eğer seçili attribute name, seçili item attribute'ları içinde varsa ona karşılık gelen attribute value ile değiştirilir.
/// \n Eğer seçili attrinute name, seçili item attribute'ları içinde yoksa node yapısındaki atts vector'üne attribute name ve value eklenir.
/// \param arg1 : Girilen attribute value
///
void Edit_UI::on_Att_Value_textChanged(const QString &arg1)
{
    if(checkAttsContain(selectedItem))
    {
        for(int i = 0; i < n.atts.size() ; i++)
        {
            if(selectedItem.compare(n.atts.at(i).first) == 0)
            {
                string result;
                for (QChar ch : arg1) {
                    if (ch.isLetterOrNumber() || ch.isSpace() || ch == '-') {
                        result.push_back(ch.toLatin1());
                    }
                }
                n.atts.at(i).second = result;
            }
        }
    }
    else
    {
        string result;
        for (QChar ch : arg1) {
            if (ch.isLetterOrNumber() || ch.isSpace() || ch == '-') {
                result.push_back(ch.toLatin1());
            }
        }
        n.atts.push_back(make_pair(selectedItem,result));
    }

}
///
/// \brief Edit_UI::setUiForAtts
/// xml_ui penceresinde Add Attribute işlemi için açılan penverede attribute name ve value için girdi alınacak kutucuklar haricinde kalan elemanlar kaldırılır.
///
void Edit_UI::setUiForAtts()
{
    ui_edit->attributeCombo->setHidden(true);
    ui_edit->label->setHidden(true);
    ui_edit->label_2->setHidden(true);
    ui_edit->Tag_Name->setHidden(true);
    ui_edit->Tag_Value->setHidden(true);
    ui_edit->attributeNames->setHidden(false);
    selectedItem = "attribute name";
}
