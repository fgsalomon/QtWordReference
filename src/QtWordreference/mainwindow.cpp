#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "optionsdialog.h"
#include <QMessageBox>
#include <QDebug>
#include <QIcon>
#include <QSettings>
#include <QStyleFactory>

#ifdef DEBUG_MODE
#define MAINWINDOW_DEBUG
#endif

QStringList MainWindow::dictionaryList = QStringList() << "enes" << "enfr" << "enpt" << "esen" << "fren" << "pten";
QStringList MainWindow::longDictionaryList = QStringList()  << "English-Spanish" << "English-French" << "English-Portuguese" << "Spanish-English" << "French-English" << "Portuguese-English";
QStringList MainWindow::styleList = QStringList() << "Default" << "Solarized";

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    QApplication::setStyle(QStyleFactory::create("Fusion"));
    setWindowTitle("QtWordReference");
    ui->dictionariesComboBox->addItems(longDictionaryList);
    connect(ui->searchTermLineEdit, SIGNAL(returnPressed()), this, SLOT(on_searchPushButton_clicked()));
    createActions();
    createTrayIcon();
    readSettings();
    ui->dictionariesComboBox->setCurrentIndex(mDefaultDictionaryIndex);
    mWRClient = new WordReferenceClient(mAPIKey, this);
    connect(mWRClient, SIGNAL(sendResponse(QByteArray)), this, SLOT(onReceivedResponse(QByteArray)));
    QTextDocument *doc = new QTextDocument(ui->textBrowser);
    ui->textBrowser->setDocument(doc);
    APIKeyChanged();
}

void MainWindow::closeEvent(QCloseEvent *event)
{
#ifdef MAINWINDOW_DEBUG
    qDebug()<<"closeEvent";
#endif
    writeSettings();
    event->accept();
}

MainWindow::~MainWindow()
{
    delete ui;
    delete mWRClient;
    delete mTrayIcon;
    delete mTrayIconMenu;
    delete minimizeAction;
    delete maximizeAction;
    delete restoreAction;
    delete quitAction;
}

void MainWindow::on_searchPushButton_clicked()
{
    if (ui->searchTermLineEdit->text().isEmpty())
    {
        QMessageBox::information(this, tr("Information"), tr("You must type a search term"));
        return;
    }
    mWRClient->search(ui->searchTermLineEdit->text(), getDictionary());
}


void MainWindow::onReceivedResponse(QByteArray response)
{
    QString text(response);
    QTextDocument *doc = ui->textBrowser->document();
    doc->clear();
    doc->addResource(QTextDocument::StyleSheetResource, QUrl("format.css"), getCSS());
    doc->setHtml(text);
    ui->textBrowser->setDocument(doc);
}

void MainWindow::on_actionOptions_triggered()
{
    OptionsDialog optionsDialog(longDictionaryList, styleList, mAPIKey, mDefaultDictionaryIndex, mDefaultStyleIndex);
    optionsDialog.exec();
    if (optionsDialog.optionsChanged())
    {
#ifdef MAINWINDOW_DEBUG
        qDebug() << "Options changed";
#endif
        mDefaultDictionaryIndex = optionsDialog.getDefaultDictionaryIndex();
        mDefaultStyleIndex = optionsDialog.getDefaultStyleIndex();
        mAPIKey = optionsDialog.getAPIKey();
        mWRClient->setAPIKey(mAPIKey);
        APIKeyChanged();
    }
}

void MainWindow::on_actionExit_triggered()
{
    close();
    qApp->exit(0);
}

void MainWindow::on_actionAbout_Qt_triggered()
{
    QMessageBox::aboutQt(this, tr("About Qt"));
}

void MainWindow::on_actionAbout_WordReference_triggered()
{
    QMessageBox::about(this, tr("About QtWordReference"), tr("QtWordReference is a desktop client for the WordReference.com API made with Qt"));
}


void MainWindow::createActions()
{
    minimizeAction = new QAction(tr("Mi&nimize"), this);
    connect(minimizeAction, SIGNAL(triggered()), this, SLOT(hide()));

    maximizeAction = new QAction(tr("Ma&ximize"), this);
    connect(maximizeAction, SIGNAL(triggered()), this, SLOT(showMaximized()));

    restoreAction = new QAction(tr("&Restore"), this);
    connect(restoreAction, SIGNAL(triggered()), this, SLOT(showNormal()));

    quitAction = new QAction(tr("&Quit"), this);
    connect(quitAction, SIGNAL(triggered()), this, SLOT(on_actionExit_triggered()));
}

void MainWindow::createTrayIcon()
{
    mTrayIconMenu = new QMenu(this);
    mTrayIconMenu->addAction(minimizeAction);
    mTrayIconMenu->addAction(maximizeAction);
    mTrayIconMenu->addAction(restoreAction);
    mTrayIconMenu->addSeparator();
    mTrayIconMenu->addAction(quitAction);

    mTrayIcon = new QSystemTrayIcon(this);
    mTrayIcon->setContextMenu(mTrayIconMenu);
    mTrayIcon->setIcon(QIcon(":/icons/logoQtWordReference22x22.png"));
    mTrayIcon->setVisible(true);
}


QString MainWindow::getDictionary()
{
    return dictionaryList[ui->dictionariesComboBox->currentIndex()];
}

void MainWindow::writeSettings()
{
    QSettings settings("Moose Soft", "QtWordReference");
    settings.setValue("APIKey", mAPIKey);
    settings.setValue("DefaultDictionary", mDefaultDictionaryIndex);
    settings.setValue("DefaultStyle", mDefaultStyleIndex);
    #ifdef MAINWINDOW_DEBUG
    qDebug() << "Write settings. mAPIKey:" << mAPIKey;
#endif
}

void MainWindow::readSettings()
{
    QSettings settings("Moose Soft", "QtWordReference");
    mAPIKey = settings.value("APIKey", "").toString();
    mDefaultDictionaryIndex = settings.value("DefaultDictionary", 0).toInt();
    mDefaultStyleIndex = settings.value("DefaultStyle", 0).toInt();
}

QString MainWindow::getCSS()
{
    QString css;
    switch(mDefaultStyleIndex)
    {
    case 0:
        #ifdef MAINWINDOW_DEBUG
        qDebug() << "CSS 0";
#endif
        css  = "span.sense { color:#DE0000; } "
                "span.origterm {font-weight:bold}"
                "span.transterm {}"
                "span.pos {color:#0000DE;}";
        break;
    case 1:
#ifdef MAINWINDOW_DEBUG
        qDebug() << "CSS 1";
#endif
        css  = "body {background-color: #002b36;"
                        "color: #b58900;}"
                "span.sense { color:#859900; } "
                "span.origterm {font-weight:bold}"
                "span.transterm {}"
                "span.pos {color:#268bd2;}";
        break;
    default:
        #ifdef MAINWINDOW_DEBUG
        qDebug() << "CSS default";
#endif
        css  = "span.sense { color:#DE0000; } "
                "span.origterm {font-weight:italic}"
                "span.transterm {}"
                "span.pos {color:#0000DE;}";
        break;
    }
    return css;
}

void MainWindow::APIKeyChanged()
{
    if (!mAPIKey.isEmpty()) // If the API key is valid
    {
        ui->textBrowser->setHidden(false);
        ui->searchPushButton->setEnabled(true);
        ui->searchTermLineEdit->setEnabled(true);
        ui->dictionariesComboBox->setEnabled(true);
        ui->NoAPIKeyWidget->setHidden(true);
    }
    else
    {
        ui->textBrowser->setHidden(true);
        ui->searchPushButton->setEnabled(false);
        ui->searchTermLineEdit->setEnabled(false);
        ui->dictionariesComboBox->setEnabled(false);
        ui->NoAPIKeyWidget->setHidden(false);
    }
}
