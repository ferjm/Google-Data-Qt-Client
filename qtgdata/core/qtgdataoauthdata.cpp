#include "qtgdataoauthdata.h"

#define CONSUMER_KEY "consumerkey"
#define CONSUMER_SECRET "consumersecret"
#define TOKEN "token"
#define TOKEN_SECRET "tokensecret"

OAuthData::OAuthData()
{
}

void OAuthData::setConsumerKey(QString consumerKey)
{
    data.insert(CONSUMER_KEY,consumerKey);
}

void OAuthData::setConsumerSecret(QString consumerSecret)
{
    data.insert(CONSUMER_SECRET,consumerSecret);
}

void OAuthData::setToken(QString token)
{
    data.insert(TOKEN,token);
}

void OAuthData::setTokenSecret(QString tokenSecret)
{
    data.insert(TOKEN_SECRET,tokenSecret);
}

QString OAuthData::getConsumerKey()
{
    return data.value(CONSUMER_KEY).toString();
}

QString OAuthData::getConsumerSecret()
{
    return data.value(CONSUMER_SECRET).toString();
}

QString OAuthData::getToken()
{
    return data.value(TOKEN).toString();
}

QString OAuthData::getTokenSecret()
{
    return data.value(TOKEN_SECRET).toString();
}

QVariant OAuthData::getAuthentication()
{
    return data;
}
