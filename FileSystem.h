#ifndef FILESYSTEM_H
#define FILESYSTEM_H

#include <QWidget>
#include <QMessageBox>
#include <QFileSystemModel>
#include <QSortFilterProxyModel>
#include <QTimer>
#include <QCloseEvent>
#include <QObject>

namespace Ui {
class FileSystem;
}
using namespace std;
///
/// \brief Bir dosya okunacağı zaman yada bir dosya kaydedileceği zaman kullanılan sınıf
///
class FileSystem : public QWidget
{
    Q_OBJECT

public:
    /// @brief FileSystem sınıfının yapıcı fonksiyonu
    explicit FileSystem(QWidget *parent = nullptr);
    /// @brief FileSystem sınıfının yıkıcı fonksiyonu
    ~FileSystem();
    /// @brief Pencere üzerinde seçilen dosya yolunu filePath değişkenine atar
    void setFilePath(string);
    /// @brief filePath değişkenini döndürür
    string getFilePath();
    /// @brief Pencere üzerinde seçilen dosya adını fileName değişkenine atar
    void setFileName(string);
    /// @brief fileName değişkenini döndürür
    string getFileName();
    /// @brief filePath ve fileName değişkenlerini birleştirir ve döndürür
    string getFullFilePath();
    /// @brief xml_ui penceresinde save butonu tıklandığı zaman açılacak pencere için ayarlama yapar
    void editUIforSave();
    /// @brief xml_ui penceresinde load butonu tıklandığı zaman açılacak pencere için ayarlama yapar
    void editUIforLoad();
    /// @brief save butonu için filePath + dosya adını döndürür
    string getSFPN();

private slots:
    /// @brief Boş
    void on_treeView_clicked(const QModelIndex& index);
    /// @brief Path seçerken seçilen itemı ayarlar
    void on_treeView_doubleClicked(const QModelIndex& index);
    /// @brief Dosya seçerken seçilen itemı ayarlar
    void on_listView_doubleClicked(const QModelIndex& index);
    /// @brief Dosya seçildiğinde tamamlandı sinyalini tetikler
    void on_Complete();
    /// @brief Pencere üzerinde kapatma tuşu basıldığında kapatma sinyalini tetikler
    void on_Close();
    /// @brief Kapatma tuşu basıldı mı kontrolü yapar
    void checkClose();
    /// @brief Save işlemi için tamamlama işlemini yapar
    void on_fileButton_clicked();

signals:
    /// @brief Tamamlandı sinyali
    void complete();
    /// @brief Kapatma sinyali
    void exitClose();
private:
    /// @brief FileSystem için pencere oluşturur
    Ui::FileSystem *uiFile;
    /// @brief Dosya sistemi üzerinde işlem yapabilmemiz için (dizin seçimi)
    QFileSystemModel* dmodel;
    /// @brief Dosya sistemi üzerinde işlem yapabilmemiz için (dosya seçimi)
    QFileSystemModel* fmodel;
    /// @brief Seçilen dizini tutar
    string filePath;
    /// @brief Seçilen dosyanın adını tutar
    string fileName;
    /// @brief Close event için timer
    QTimer* timer;
    /// @brief Save işlemi için seçilen PATH ve verilen dosya ismini tutar
    string saveFilePathAndName;
};

#endif // FILESYSTEM_H
