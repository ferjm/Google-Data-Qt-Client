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
#include "qtgdatahttpconnector.h"

#include <QDebug>

OAuth::OAuth(QObject *parent)
{
    connector = new HttpConnector();
}

OAuth::~OAuth()
{
    delete connector;
}

void OAuth::getRequestToken(QString consumerKey, QString consumerSecret, QList<QUrl> scope, QUrl requestTokenUrl)
{
    request = new OAuthRequest(OAuthRequest::TemporaryCredentials,this);
    request->setRequestEndpoint(requestTokenUrl);
    request->setConsumerKey(consumerKey);
    request->setConsumerSecretKey(consumerSecret);
    request->setCallbackUrl(QUrl("oob"));
    request->setHttpMethod(HttpRequest::GET);
    QUrl scopeUrl;
    QString scopes;
    foreach(scopeUrl,scope)
        scopes += scopeUrl.toString();
    QMultiMap<QString,QString> additionalParams;
    additionalParams.insert("scope",scopes);
    request->setAdditionalParameters(additionalParams);
    QList<QByteArray> requestHeaders = request->getRequestParameters();
    QByteArray authHeader;
    bool first = true;
    foreach (const QByteArray header, requestHeaders) {
       if (!first) {
           authHeader.append(", ");
       } else {
           authHeader.append("OAuth ");
           first = false;
       }
       authHeader.append(header);
    }
    request->setHeader("Authorization",authHeader);
    request->prepareRequest();
    connect(connector, SIGNAL(requestFinished(QByteArray)), this, SLOT(onRequestFinished(QByteArray)));
    connector->httpRequest(request);
}

void OAuth::onRequestFinished(QByteArray response)
{
    QMultiMap<QString, QString> result;
    QString replyString(response);

    QStringList parameterPairs = replyString.split('&', QString::SkipEmptyParts);
    foreach (const QString &parameterPair, parameterPairs) {
        QStringList parameter = parameterPair.split('=');
#ifdef QTGDATA_DEBUG
        qDebug() << parameter.value(0) << " = " << parameter.value(1) << "\n";
#endif
        result.insert(parameter.value(0), parameter.value(1));
    }
    QString requestToken = QUrl::fromPercentEncoding( QString(result.value("oauth_token")).toLocal8Bit() );
    QString requestTokenSecret =  QUrl::fromPercentEncoding( QString(result.value("oauth_token_secret")).toLocal8Bit() );
    emit temporaryTokenReceived(requestToken,requestTokenSecret);

}
