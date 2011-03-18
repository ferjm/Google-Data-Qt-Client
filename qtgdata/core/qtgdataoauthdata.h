#ifndef QTGDATAOAUTHDATA_H
#define QTGDATAOAUTHDATA_H

#include "qtgdataiauthentication.h"

class OAuthData : public IAuthentication
{
    QHash<QString, QString> data;
public:
    OAuthData();
    void setConsumerKey(QString consumerKey);
    void setConsumerSecret(QString consumerSecret);
    void setToken(QString token);
    void setTokenSecret(QString tokenSecret);
    QString getConsumerKey();
    QString getConsumerSecret();
    QString getToken();
    QString getTokenSecret();
};

#endif // QTGDATAOAUTHDATA_H
