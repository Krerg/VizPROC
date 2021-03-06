#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QWidget>
#include <QFileSystemModel>
#include <QMenuBar>
#include <QStringList>
#include <QTreeView>
#include <QListWidgetItem>
#include <QKeyEvent>
#include <QMap>

namespace Ui {
class MainWindow;
}

class MainWindow : public QWidget
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

protected:
    void keyPressEvent(QKeyEvent* event);


private:

    void updateDetailGallery(QString detailPath);

    void clearOutput();

    void updateAll();

    void updateGallery();

    void getDetailCategoriesList();

    Ui::MainWindow *ui;

    QString globalPath;

    QString galleryPath;

    QString modelPath;

    QString detailPath;

    QString detailArticlePath;

    QFileSystemModel *fileModelCarMake;

    QFileSystemModel *fileModelCarModel;

    QFileSystemModel *fileModelDetailCategory;

    QTreeView* details;

    QFileSystemModel *fileDetail;

    QFileSystemModel *fileDetailArticle;

    QMenu* service;

    QMenuBar* menuBar;

    QAction* settings;

    QAction* importFromExcel;

    QAction* exportToExcel;

    QMenu* requestCarMakeMenu;

    bool editDetail;

    QMenu* requestCarModelMenu;

    QMenu* requestDetailCategoryMenu;

    QMenu* requestDetailMenu;

    QMenu* requestDetailArticleMenu;

    QMenu* requestGalleryMenu;

    QMenu* requestDetailGalleryMenu;

    QAction* createCarMake;

    QAction* deleteCarMake;

    QAction* createCarModel;

    QAction* deleteCarModel;

    QAction* createDetailCategory;

    QAction* deleteDetailCategory;

    QWidget* createCarMakeWindow;

    QAction* createDetail;

    QAction* deleteDetail;

    QAction* createArticle;

    QAction* deleteArticle;

    QAction* changeArticle;

    QAction* deleteImage;

    QAction* add2ExistArticle;

    QAction* returnImage;

    QString sPath;

    QStringList* detailCategories;

    QMap<QString, QStringList*>* detailsMap;

    QString detailCategoryPath;

    QList<QListWidgetItem*>* images;

    QList<QListWidgetItem*>* articleImages;

    QString selectedDetailCategory;

    QString selectedDetail;

    /**
     * @brief settingsFile файл настроек, где лежат пути
     */
    QFile* settingsFile;


public slots:
    void carMakeChanged(QModelIndex);
    void carModelChanged(QModelIndex);
    void carDetailCategoryChanged(QModelIndex);
    void carDetailChanged(QModelIndex);
    void carDetailArticleChanged(QModelIndex);

    void openImage(QModelIndex);
    void openArticleImage(QModelIndex);

    void menuRequestCarMake(QPoint pos);
    void menuRequestCarModel(QPoint pos);
    void menuRequsetDetailCategory(QPoint pos);
    void menuRequestDetail(QPoint pos);
    void menuRequestDetailArticle(QPoint pos);
    void menuRequestGallery(QPoint pos);
    void menuRequsetDetailGallery(QPoint pos);

    void createCarMakeSlot();
    void deleteCarMakeSlot();

    void createCarModelSlot();
    void deleteCarModelSlot();

    void createDetailCategorySlot();
    void deleteDetailCategorySlot();

    void createDetailSlot();
    void deleteDetailSlot();

    void createArticleSlot();
    void deleteArticleSlot();
    void changeArticleSlot();

    void returnImageSlot();
    void deleteImageSlot();
    void add2ExistArticleSlot();

    void openSettingsWindow();
    void setSettings(QString path, QString galleryPath);

    void exportToExcelSlot();
    void importFromExcelSlot();
private slots:
    void on_pushButton_clicked();
};

#endif // MAINWINDOW_H
