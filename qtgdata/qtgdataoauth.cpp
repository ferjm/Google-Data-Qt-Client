/***************************************************************************
 *   Copyright (C) 2010 Fernando Jiménez Moreno <ferjmoreno@gmail.com>     *
 *                                                                         *
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 *   This program is distributed in the hope that it will be useful,       *
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of        *
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the         *
 *   GNU General Public License for more details.                          *
 *                                                                         *
 *   You should have received a copy of the GNU General Public License     *
 *   along with this program; if not, write to the                         *
 *   Free Software Foundation, Inc.,                                       *
 *   59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.             *
 ***************************************************************************/

#include "qtgdataoauth.h"

#include <QDebug>

OAuth::OAuth(QUrl requestTokenUrl,QUrl userAuthUrl,QUrl accessTokenUrl,QString consumerKey,QString consumerSecret) :
        _requestUrl(requestTokenUrl),
        _userAuthUrl(userAuthUrl),
        _accessUrl(accessTokenUrl),
        _consumerKey(consumerKey),
        _consumerSecret(consumerSecret)
{
    oauthRequest = new KQOAuthRequest;
    oauthManager = new KQOAuthManager(this);
    oauthRequest->setEnableDebugOutput(true);
}

OAuth::~OAuth()
{
    delete oauthRequest;
    delete oauthManager;
}

void OAuth::getAccessToken()
{
    connect(oauthManager, SIGNAL(temporaryTokenReceived(QString,QString)),
            this, SLOT(onTemporaryTokenReceived(QString, QString)));

    connect(oauthManager, SIGNAL(authorizationReceived(QString,QString)),
            this, SLOT( onAuthorizationReceived(QString, QString)));

    connect(oauthManager, SIGNAL(accessTokenReceived(QString,QString)),
            this, SLOT(onAccessTokenReceived(QString,QString)));

    connect(oauthManager, SIGNAL(requestReady(QByteArray)),
            this, SLOT(onRequestReady(QByteArray)));

    oauthRequest->initRequest(KQOAuthRequest::TemporaryCredentials, _requestUrl);
    oauthRequest->setConsumerKey(_consumerKey);
    oauthRequest->setConsumerSecretKey(_consumerSecret);

    oauthManager->setHandleUserAuthorization(true);

    oauthManager->executeRequest(oauthRequest);
}

void OAuth::onTemporaryTokenReceived(QString token,QString tokenSecret)
{
    qDebug() << "Temporary token received: " << token << tokenSecret;
    if( oauthManager->lastError() == KQOAuthManager::NoError) {
        qDebug() << "Asking for user's permission to access protected resources. Opening URL: " << _userAuthUrl;
        oauthManager->getUserAuthorization(_userAuthUrl);
    }
}

void OAuth::onAuthorizationReceived(QString token, QString verifier)
{
    qDebug() << "User authorization received: " << token << verifier;
    oauthManager->getUserAccessTokens(QUrl("https://api.twitter.com/oauth/access_token"));
    if( oauthManager->lastError() != KQOAuthManager::NoError) {
            //TODO: emit signal? exception?
    }
}

void OAuth::onAccessTokenReceived(QString token, QString tokenSecret)
{
    qDebug() << "Access token received: " << token << tokenSecret;
}

void OAuth::onRequestReady(QByteArray response)
{
    qDebug() << "Response from the service: " << response;
}
