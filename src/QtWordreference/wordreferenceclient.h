#ifndef WORDREFERENCECLIENT_H
#define WORDREFERENCECLIENT_H

#include <QObject>
#include <QtNetwork/QNetworkAccessManager>
#include <QtNetwork/QNetworkReply>
#include "wordtranslation.h"

class WordReferenceClient : public QObject
{
    Q_OBJECT
public:
    explicit WordReferenceClient(const QString &APIKey, QObject *parent = 0);
    void setAPIKey(const QString &APIKey) {mAPIKey = APIKey;}
    
signals:
    void sendResponse(QByteArray response);
    
public slots:
    void search(QString term, QString dictionary);

private slots:
    void onReplyFinished(QNetworkReply*reply);

private:
    QString mAPIKey;
    QNetworkAccessManager* mNetworkManager;

    void parseReply(const QByteArray &reply);
    void parseTranslationMap(const QVariantMap &translationMap, QList<WordTranslation> &translationList);
};

#endif // WORDREFERENCECLIENT_H
