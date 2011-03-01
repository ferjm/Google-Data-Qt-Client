/***************************************************************************
 *   Copyright (C) 2010 Fernando Jiménez Moreno <ferjmoreno@gmail.com>     *
 *                                                                         *
 *   This class is based on KQOAuthRequest from KQOAuth Library            *
 *   by Johan Paul (johan.paul@d-pointer.com)                              *
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

#include "qtgdataoauthrequest.h"
#include "qtgdatadefs.h"

OAuthRequest::OAuthRequest(QObject *parent) : HttpRequest(parent)
{
}

void OAuthRequest::prepareRequest()
{
    if( !requestParameters.isEmpty() ) {
        return;
    }

    switch(requestType) {
    case OAuthRequest::TemporaryCredentials:
        requestParameters.append( qMakePair( OAUTH_KEY_CALLBACK, oauthCallbackUrl.toString()) );
        requestParameters.append( qMakePair( OAUTH_KEY_SIGNATURE_METHOD, oauthSignatureMethod) );
        requestParameters.append( qMakePair( OAUTH_KEY_CONSUMER_KEY, oauthConsumerKey ));
        requestParameters.append( qMakePair( OAUTH_KEY_VERSION, oauthVersion ));
        requestParameters.append( qMakePair( OAUTH_KEY_TIMESTAMP, this->oauthTimestamp() ));
        requestParameters.append( qMakePair( OAUTH_KEY_NONCE, this->oauthNonce() ));
        insertAdditionalParams(requestParameters);
        break;

    case OAuthRequest::AccessToken:
        requestParameters.append( qMakePair( OAUTH_KEY_SIGNATURE_METHOD, oauthSignatureMethod ));
        requestParameters.append( qMakePair( OAUTH_KEY_CONSUMER_KEY, oauthConsumerKey ));
        requestParameters.append( qMakePair( OAUTH_KEY_VERSION, oauthVersion ));
        requestParameters.append( qMakePair( OAUTH_KEY_TIMESTAMP, this->oauthTimestamp() ));
        requestParameters.append( qMakePair( OAUTH_KEY_NONCE, this->oauthNonce() ));
        requestParameters.append( qMakePair( OAUTH_KEY_VERIFIER, oauthVerifier ));
        requestParameters.append( qMakePair( OAUTH_KEY_TOKEN, oauthToken ));
        insertAdditionalParams(requestParameters);
        break;

    case OAuthRequest::AuthorizedRequest:
        requestParameters.append( qMakePair( OAUTH_KEY_SIGNATURE_METHOD, oauthSignatureMethod ));
        requestParameters.append( qMakePair( OAUTH_KEY_CONSUMER_KEY, oauthConsumerKey ));
        requestParameters.append( qMakePair( OAUTH_KEY_VERSION, oauthVersion ));
        requestParameters.append( qMakePair( OAUTH_KEY_TIMESTAMP, this->oauthTimestamp() ));
        requestParameters.append( qMakePair( OAUTH_KEY_NONCE, this->oauthNonce() ));
        requestParameters.append( qMakePair( OAUTH_KEY_TOKEN, oauthToken ));
        insertAdditionalParams(requestParameters);
        break;

    default:
        break;
    }
}

void OAuthRequest::insertAdditionalParams(QList<QPair<QString, QString> > &requestParams)
{
    QList<QString> additionalKeys = this->additionalParams.keys();
    QList<QString> additionalValues = this->additionalParams.values();
    for(int i=0; i<additionalKeys.size(); i++)
        requestParameters.append( qMakePair(QString(additionalKeys.at(i)),
                                            QString(additionalValues.at(i))));
    if(this->httpMethod == HttpRequest::POST) {
        insertPostBody();
    }
}

void OAuthRequest::insertPostBody()
{
//TODO: ...
}
