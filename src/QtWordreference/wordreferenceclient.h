#ifndef WORDREFERENCECLIENT_H
#define WORDREFERENCECLIENT_H

#include <QObject>
#include <QtNetwork/QNetworkAccessManager>
#include <QtNetwork/QNetworkReply>
#include "wordtranslation.h"


/*!
 * \brief The WordReferenceClient class encapsulates the interaction with the WordReference API.
 */
class WordReferenceClient : public QObject
{
    Q_OBJECT
public:
    /*!
     * \brief WordReferenceClient constructor
     * \param APIKey WordReference API key
     * \param parent Pointer to the parent QObject
     */
    explicit WordReferenceClient(const QString &APIKey, QObject *parent = 0);
    /*!
     * \brief setAPIKey changes the WordReference API key for the passed one
     * \param APIKey WordReference API key
     */
    void setAPIKey(const QString &APIKey) {mAPIKey = APIKey;}
    
signals:
    /*!
     * \brief sendResponse sends parsed and formatted WordReference responses
     * \param response Parsed and formatted WordReference response
     */
    void sendResponse(QByteArray response);
    
public slots:
    /*!
     * \brief search sends a search request to the WordReference service
     * \param term Search term
     * \param dictionary A four letter string representing the dictionary as specified by the WordReference API (enes, fren, etc.)
     */
    void search(QString term, QString dictionary);

private slots:
    /*!
     * \brief onReplyFinished is a slot called when a request reply is received
     * \param reply Request reply
     */
    void onReplyFinished(QNetworkReply*reply);

private:
    QString mAPIKey; /*!< WordReference API key */
    QNetworkAccessManager* mNetworkManager; /*!< Manager to handle the http requests */

    /*!
     * \brief parseReply parses a request reply
     * \param reply Request reply
     */
    void parseReply(const QByteArray &reply);
    /*!
     * \brief parseTranslationMap parses a translation map into a translation list
     * \param translationMap Translation map to be parsed
     * \param translationList Translation list
     */
    void parseTranslationMap(const QVariantMap &translationMap, QList<WordTranslation> &translationList);
};

#endif // WORDREFERENCECLIENT_H
