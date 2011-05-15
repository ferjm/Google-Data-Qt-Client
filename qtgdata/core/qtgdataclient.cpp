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

#include "qtgdataclient.h"
#include "qtgdataoauthdata.h"
#include "qtgdataoauthrequest.h"
#include "qtgdataxmlparser.h"

QtgdataClient::QtgdataClient(int version, QObject *parent) : version(version)
{
}

QtgdataClient::~QtgdataClient()
{
    if(authenticationData) delete authenticationData;
}

void QtgdataClient::setAuthenticationData(IAuthentication *authenticationData)
{
    this->authenticationData = authenticationData;
    if(dynamic_cast<OAuthData*>(authenticationData) != NULL)
        authenticationMode = OAUTH_1_0;
}

HttpRequest* QtgdataClient::authenticatedRequest()
{
    switch(authenticationMode)
    {
    case OAUTH_1_0: {
            OAuthRequest *request = new OAuthRequest();
            OAuthData *oAuthData = dynamic_cast<OAuthData*>(authenticationData);
            request->setConsumerKey(oAuthData->getConsumerKey());
            request->setConsumerSecretKey(oAuthData->getConsumerSecret());
            request->setToken(oAuthData->getToken());
            request->setTokenSecret(oAuthData->getTokenSecret());
            return dynamic_cast<HttpRequest*>(request);
            break;
        }
    default:
        return NULL;
    }
}

void QtgdataClient::sendClientRequest(HttpRequest::RequestHttpMethod method,
                                      QUrl endpoint,
                                      QList<QPair<QByteArray,QByteArray> > &headers,
                                      const QObject *sender,
                                      const char* signal,
                                      const QObject *receiver,
                                      const char* slot,
                                      bool oauth)
{
    HttpRequest *request = authenticatedRequest();
    request->setRequestEndpoint(endpoint);
    request->setHttpMethod(method);
    for(int i=0; i < headers.size(); i++)
        request->setHeader(headers.at(i).first,headers.at(i).second);
    if(oauth)
        request->setAuthHeader();
    connect(&this->httpConnector,
            SIGNAL(requestFinished(QByteArray)),
            this,
            SLOT(onAtomFeedRetrieved(QByteArray)));
    this->httpConnector.httpRequest(request);
    delete request;
}

void QtgdataClient::onAtomFeedRetrieved(QByteArray reply)
{
#ifdef QTGDATA_DEBUG
    qDebug() << "onAtomFeedRetrieved";
#endif
    XMLParser parser;
    try {
        IEntity *entity = parser.parse(reply,reply.size());
        if((entity != NULL)&&(entity->getId() != Id::NULLID))
        {
            IEntity::itConstEntities begin,end;
            entity->getEntityList(begin,end);
            QList<AtomEntry> entries;
            if(begin != end)
            {
                for(IEntity::itConstEntities it = begin; it != end; it++ )
                {
                    IEntity *sit = dynamic_cast<IEntity *>(*it);
                    if(sit->getId() == Id::entry)
                    {
                        AtomEntry atomEntry;
                        IEntity::itConstEntities entryBegin,entryEnd;
                        sit->getEntityList(entryBegin,entryEnd);
                        for(IEntity::itConstEntities itEntry = entryBegin;
                            itEntry != entryEnd;
                            itEntry++)
                        {
                            IEntity *entry = dynamic_cast<IEntity *>(*itEntry);
                            int id = entry->getId();
                            switch(id)
                            {
                            case Id::author: {
                                IEntity *author = entry->getEntity(Id::author);
                                if((author)&&(author->getId()!=NULL))
                                {
                                    IEntity *aux = NULL;
                                    if((aux=author->getEntity(Id::name)));
                                        atomEntry.author.name = aux->getValue();
                                }
                                break;
                            }
                            case Id::id:
                                atomEntry.id = entry->getValue();
                                break;
                            case Id::published:
                                atomEntry.published.fromString(entry->getValue(),Qt::ISODate);
                                break;
                            case Id::updated:
                                atomEntry.updated.fromString(entry->getValue(),Qt::ISODate);
                                break;
                            case Id::summary:
                                atomEntry.summary = entry->getValue();
                                break;
                            case Id::title:
                                atomEntry.title = entry->getValue();
                                break;
                            case Id::link:
                            {
                                Link link;
                                link.href = QUrl(entry->getAttribute(AttributeId::href)->sValue);
                                link.rel = entry->getAttribute(AttributeId::rel)->sValue;
                                link.type = entry->getAttribute(AttributeId::type)->sValue;
                                atomEntry.links.append(link);
                                break;
                            }
                            default: break;
                            }
                        }
                        entries.append(atomEntry);
                    }
                 }
            }
            if(!entries.isEmpty())
                emit atomFeedRetrievedFinished(entries);
        }
        delete entity;
    } catch(XMLParserException e) {
        qDebug() << e.what();
    }
}


