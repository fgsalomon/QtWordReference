#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "wordreferenceclient.h"
#include <QSystemTrayIcon>
#include <QCloseEvent>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT
    
public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    
protected:
    void closeEvent(QCloseEvent *event);

private slots:
    void on_searchPushButton_clicked();
    void on_actionOptions_triggered();
    void on_actionExit_triggered();
    void on_actionAbout_Qt_triggered();
    void on_actionAbout_WordReference_triggered();

public slots:
    void onReceivedResponse(QByteArray response);

private:
    Ui::MainWindow *ui;
    WordReferenceClient *mWRClient;
    QSystemTrayIcon *mTrayIcon;
    QMenu *mTrayIconMenu;
    QAction *minimizeAction;
    QAction *maximizeAction;
    QAction *restoreAction;
    QAction *quitAction;
    int mDefaultDictionaryIndex;
    int mDefaultStyleIndex;
    QString mAPIKey;
    static QStringList dictionaryList;
    static QStringList longDictionaryList;
    static QStringList styleList;

    ///     METHODS    ///
    void createTrayIcon();
    void createActions();
    QString getDictionary();
    void writeSettings();
    void readSettings();
    QString getCSS();
    void APIKeyChanged();
};

#endif // MAINWINDOW_H
