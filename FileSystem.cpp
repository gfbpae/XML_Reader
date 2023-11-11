#include "FileSystem.h"
#include "ui_FileSystem.h"
///
/// \brief FileSystem::FileSystem
/// FileSystem sınıfı yapıcı fonksiyonu
/// \n Gerekli ayarlamalar bu fonksiyonda yapılır. Pointer olarak oluşturulan değişkenler burada tanımlanır.
/// \n close_event için timer burada başlatılır ve checkClose() slot'una bağlanır
/// \param parent
///
FileSystem::FileSystem(QWidget *parent) :
    QWidget(parent),
    uiFile(new Ui::FileSystem)
    , dmodel (new QFileSystemModel(this))
    , fmodel (new QFileSystemModel(this))
{
    uiFile->setupUi(this);
    QString fpath = "C:/";
    dmodel->setFilter(QDir::NoDotAndDotDot | QDir::AllDirs);
    dmodel->setRootPath(fpath);
    uiFile->treeView->setModel(dmodel);
    fmodel->setFilter(QDir::NoDotAndDotDot | QDir::Files);
    uiFile->listView->setModel(fmodel);

    timer = new QTimer(this);
    QObject::connect(timer, SIGNAL(timeout()), this, SLOT(checkClose()));
    timer->start(500);
}
///
/// \brief FileSystem::~FileSystem
/// FileSystem sınıfı yıkıcı fonksiyonu
///
FileSystem::~FileSystem()
{
    delete uiFile;
}
///
/// \brief FileSystem::editUIforSave
/// xml_ui penceresinde save butonu basıldığında listView ve label_2 (Load işlemi için kullanılan araçlar) gizlenir.
///
void FileSystem::editUIforSave()
{
    uiFile->listView->setHidden(true);
    uiFile->label_2->setHidden(true);
}
///
/// \brief FileSystem::editUIforLoad
/// xml_ui penceresinde load butonu basıldığında fileName, fileLabel ve fileButon (Save işlemi için kullanılan araçlar) gizlenir.
///
void FileSystem::editUIforLoad()
{
    uiFile->fileName->setHidden(true);
    uiFile->fileLabel->setHidden(true);
    uiFile->fileButton->setHidden(true);
}
///
/// \brief FileSystem::setFilePath
/// Seçilen dosya dizinini filePath değişkenine atar
/// \param x : Seçilen dosya dizini
///
void FileSystem::setFilePath(string x)
{
    filePath = x;
}
///
/// \brief FileSystem::getFilePath
/// \return : Seçilen dosya dizinini döndürür
///
string FileSystem::getFilePath()
{
    return filePath;
}
///
/// \brief FileSystem::setFileName
/// Seçilen dosyanın adını fileName değişkenine atar
/// \param x : Seçilen Dosyanın adı
///
void FileSystem::setFileName(string x)
{
    fileName = x;
}
///
/// \brief FileSystem::getFileName
/// \return Dosya adını döndürür.
///
string FileSystem::getFileName()
{
    return fileName;
}
///
/// \brief FileSystem::getFullFilePath
/// Seçilen Path ve dosya adını döndürür. Döndürmeden önce '\\' olarak gelen ayraçları '/' ile düzeltir
/// \return Düzenlenmiş Dizin ve dosya adını döndürür
///
string FileSystem::getFullFilePath()
{
    string processedPath = getFilePath() + "/" + getFileName();
    size_t found = processedPath.find('/');
    while (found != std::string::npos)
    {
        processedPath[found] = '\\';
        found = processedPath.find('/', found + 1);
    }
    return processedPath;

}
///
/// \brief FileSystem::on_treeView_doubleClicked
/// Seçilen dizini kaydeder ve bu dizindeki '.xml' uzantılı dosyaları listView'de bastırır
/// \param index : Seçilen dizin
///
void FileSystem::on_treeView_doubleClicked(const QModelIndex & index)
{
    fmodel->setNameFilterDisables(false);
    fmodel->setNameFilters(QStringList() << "*.xml");
    QString fpath = dmodel->fileInfo(index).absoluteFilePath();
    uiFile->listView->setRootIndex(fmodel->setRootPath(fpath));
    setFilePath(fpath.toStdString());
}
///
/// \brief FileSystem::on_listView_doubleClicked
/// Seçilen dosyanın adını kaydeder ve on_Complete() fonksiyonunu çağırır
/// \param index : listView üzerinde seçilen dosya
///
void FileSystem::on_listView_doubleClicked(const QModelIndex& index)
{
    setFileName(index.data().toString().toStdString());
    on_Complete();
}
///
/// \brief FileSystem::on_Complete
/// Dosya seçme işlemi tamalandığı zaman pencereyi kapatır ve complete() sinyalini tetkler
///
void FileSystem::on_Complete()
{
    FileSystem::close();
    timer->stop();
    emit(complete());
}
///
/// \brief FileSystem::on_Close
/// Penvere kapatıldığı zaman manuel olarak exitClose() sinyali tetiklenir.
///
void FileSystem::on_Close()
{
    timer->stop();
    emit(exitClose());
}
///
/// \brief FileSystem::checkClose
/// Pencere üzerindeki kapatma tuşu basıldı mı kontrolü yapar ve basıldığı zaman on_Close() fonksiyonunu çağırır
///
void FileSystem::checkClose()
{
    if (this->isHidden()) { on_Close(); }
}
///
/// \brief FileSystem::on_treeView_clicked
/// \param index
///
void FileSystem::on_treeView_clicked(const QModelIndex& index)
{
}
///
/// \brief FileSystem::getSFPN
/// \return Save işlemi için seçilen dizin ve girilen dosya adını döndürür (C:/... .ornek.xml şeklinde)
///
string FileSystem::getSFPN()
{
    return saveFilePathAndName;
}
///
/// \brief FileSystem::on_fileButton_clicked
/// Save işlemi seçilen dosya dizinini ve girilen dosya adını kaydeder
///
void FileSystem::on_fileButton_clicked()
{
    QString extension = ".xml";
    saveFilePathAndName = filePath.append("/") + uiFile->fileName->text().toStdString() +extension.toStdString();
    on_Complete();
}

