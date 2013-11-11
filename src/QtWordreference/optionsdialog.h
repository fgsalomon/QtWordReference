#ifndef OPTIONSDIALOG_H
#define OPTIONSDIALOG_H

#include <QDialog>

namespace Ui {
class OptionsDialog;
}

class OptionsDialog : public QDialog
{
    Q_OBJECT
    
public:
    explicit OptionsDialog(const QStringList &dictionaries, const QStringList &styles, const QString &APIKey,
                           const int defaultDictionaryIndex, const int defaultStyleIndex, QWidget *parent = 0);
    bool optionsChanged();
    QString getAPIKey();
    int getDefaultDictionaryIndex();
    int getDefaultStyleIndex();
    ~OptionsDialog();
    
private:
    Ui::OptionsDialog *ui;
    QStringList mDictionaries;
    QStringList mStyles;
    QString mAPIKey;
    int mDefaultDictionaryIndex;
    int mDefaultStyleIndex;
};

#endif // OPTIONSDIALOG_H
