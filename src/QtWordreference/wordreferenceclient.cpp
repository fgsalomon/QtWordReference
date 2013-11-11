#include "wordreferenceclient.h"
#include "translationentry.h"
#include <QJsonArray>
#include <QJsonDocument>
#include <QJsonObject>
#include <QDebug>

#ifdef DEBUG_MODE
#define WRCLIENT_DEBUG
#endif

WordReferenceClient::WordReferenceClient(const QString &APIKey, QObject *parent) :
    QObject(parent),
    mAPIKey(APIKey)
{
    mNetworkManager = new QNetworkAccessManager(this);
    connect(mNetworkManager, SIGNAL(finished(QNetworkReply*)), this, SLOT(onReplyFinished(QNetworkReply*)));
}

void WordReferenceClient::search(QString term, QString dictionary)
{
    //http://api.wordreference.com/{api_version}/{API_key}/json/{dictionary}/{term}
    QString url = "http://api.wordreference.com/0.8/"+mAPIKey+"/json/"+dictionary+"/"+term;
#ifdef WRCLIENT_DEBUG
    qDebug()<<"URL request:"<<url;
#endif
    mNetworkManager->get(QNetworkRequest(QUrl(url)));
}


void WordReferenceClient::onReplyFinished(QNetworkReply *reply)
{
    QByteArray response = reply->readAll();
    parseReply(response);
    reply->deleteLater();
}

void WordReferenceClient::parseReply(const QByteArray &reply)
{
    QJsonDocument document = QJsonDocument::fromJson(reply);
    QJsonObject object = document.object();
    QVariantMap variantMap = object.toVariantMap();
    QVariantMap principalMap = variantMap.value("term0").toMap().value("PrincipalTranslations").toMap();
    QVariantMap additionalMap = variantMap.value("term0").toMap().value("AdditionalTranslations").toMap();
    QVariantMap compoundsMap = variantMap.value("original").toMap().value("Compounds").toMap();
    QList<WordTranslation> principalTranslations;
    QList<WordTranslation> additionalTranslations;
    QList<WordTranslation> compoundTranslations;
    parseTranslationMap(principalMap, principalTranslations);
    parseTranslationMap(additionalMap, additionalTranslations);
    parseTranslationMap(compoundsMap, compoundTranslations);
    TranslationEntry entry;
    entry.setPrincipalTranslations(principalTranslations);
    entry.setAdditionalTranslations(additionalTranslations);
    entry.setCompoundForms(compoundTranslations);
    emit sendResponse(entry.getSerialized());
}

void WordReferenceClient::parseTranslationMap(const QVariantMap &translationMap, QList<WordTranslation> &translationList)
{
    for (int i=0; i<translationMap.size(); i++)
    {
        QVariantMap firstMap = translationMap[QString::number(i)].toMap();
        //qDebug()<<i<<endl<<firstMap;
        WordDefinition originalTerm;
        QList<WordDefinition> translations;
        QMapIterator<QString, QVariant> iterator(firstMap);
        while (iterator.hasNext())
        {
            iterator.next();
            //qDebug() << iterator.key() << ": " << iterator.value() << endl;

            if (iterator.key() == "OriginalTerm")
            {
#ifdef WRCLIENT_DEBUG
                qDebug()<<"OriginalTerm";
                qDebug()<<"Sense:"<<iterator.value().toMap().value("sense").toString();
#endif
                originalTerm.setSense(iterator.value().toMap().value("sense").toString());
                originalTerm.setTerm(iterator.value().toMap().value("term").toString());
                originalTerm.setPOS(iterator.value().toMap().value("POS").toString());
            }
            else
            {
                if (iterator.key() != "Note")
                {
                    WordDefinition translation;
                    translation.setSense(iterator.value().toMap().value("sense").toString());
                    translation.setTerm(iterator.value().toMap().value("term").toString());
                    translation.setPOS(iterator.value().toMap().value("POS").toString());
                    translations.push_back(translation);
                }
            }
        }
        WordTranslation translationEntry;
        translationEntry.setOriginalWord(originalTerm);
        translationEntry.setTranslations(translations);
        translationList.push_back(translationEntry);
    }
}
