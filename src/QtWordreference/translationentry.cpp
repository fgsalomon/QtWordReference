#include "translationentry.h"
#include <QDebug>
#include <QTextStream>

TranslationEntry::TranslationEntry()
{
}

QByteArray TranslationEntry::getSerialized()
{
    QByteArray serialization;
    QTextStream textStream(&serialization);
    textStream<<"<html><head>"
                "<link rel='stylesheet' type='text/css' href='format.css'>"
                "</head><body>";
    textStream << "<h3>Principal translations</h3>";
    qDebug()<<"Principal translations";
    for (int i=0; i<mPrincipalTranslations.size(); i++)
    {
        printTranslation(mPrincipalTranslations[i], textStream);

    }
    if (!mAdditionalTranslations.isEmpty())
    {
        textStream << "<h3>Additional translations</h3>";
        qDebug()<<"Additional translations";
        for (int i=0; i<mAdditionalTranslations.size(); i++)
        {
            printTranslation(mAdditionalTranslations[i], textStream);
        }
    }
    if (!mCompoundForms.isEmpty())
    {
        textStream << "<h3>Compound forms</h3>";
        qDebug()<<"Compound forms";
        for (int i=0; i<mCompoundForms.size(); i++)
        {
            printTranslation(mCompoundForms[i], textStream);
        }
    }
    textStream << "</body></html>";
    return serialization;
}


void TranslationEntry::printTranslation(const WordTranslation &translation, QTextStream &textStream)
{
    qDebug()<<"Original word:" << translation.getOriginalWord().toString();
    WordDefinition originalWord = translation.getOriginalWord();
    textStream << "<p> <span class='origterm'>" << originalWord.getTerm() << " </span><span class='pos'>"+ originalWord.getPOS()+" </span>"
               << " <span class='sense'>" + originalWord.getSense()+" </span>";
    if (!translation.getTranslations().isEmpty())
    {
    for (int j=0; j<translation.getTranslations().size()-1; j++)
    {
        WordDefinition translatedWord = translation.getTranslations()[j];
        textStream << " <span class='transterm'>" << translatedWord.getTerm() << " </span><span class='pos'>"+ translatedWord.getPOS()+" </span>"
                   << " <span class='sense'>" + translatedWord.getSense()+" </span>, ";
        qDebug()<<"Translation "<<j+1<<":"<<translation.getTranslations()[j].toString();
    }
    WordDefinition translatedWord = (translation.getTranslations().back());
    qDebug()<<"Translation "<<translation.getTranslations().size()<<":"<<translatedWord.toString();

    textStream << " <span class='transterm'>" << translatedWord.getTerm() << " </span><span class='pos'>"+ translatedWord.getPOS()+" </span>"
               << " <span class='sense'>" + translatedWord.getSense()+" </span></p>";
    }
    else
        textStream << "</p>";
}
