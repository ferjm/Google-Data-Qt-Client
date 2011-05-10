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

#include "qtgdatabloggerclient.h"
#include "qtgdataoauthrequest.h"
#include "qtgdataxmlparser.h"

#include <QDebug>

#define BLOGGER_FEEDS "http://www.blogger.com/feeds/"

QtgdataBloggerClient::QtgdataBloggerClient(IAuthentication *auth, int version, QObject *parent) :
    QtgdataClient(version,parent)
{
    setAuthenticationData(auth);
}

void QtgdataBloggerClient::retrieveListOfBlogs(QString profileID)
{
    HttpRequest *request = authenticatedRequest();
    request->setRequestEndpoint(QUrl(QString(BLOGGER_FEEDS) + profileID +"/blogs"));    
    request->setHttpMethod(HttpRequest::GET);
    request->setHeader(QByteArray("GData-Version"),QByteArray::number(this->version));
    request->setAuthHeader();
    connect(&(this->httpConnector), SIGNAL(requestFinished(QByteArray)), this, SLOT(onRetrieveListOfBlogsFinished(QByteArray)));
    this->httpConnector.httpRequest(request);
    delete request;
}

void QtgdataBloggerClient::onListOfBlogsRetrieved(QByteArray reply)
{
#ifdef QTGDATA_DEBUG
    qDebug() << "onRetrieveListOfBlogsFinished";
#endif
    XMLParser parser;
    try {
        IEntity *entity = parser.parse(reply,reply.size());
        if((entity != NULL)&&(entity->getId() != Id::NULLID))
        {
            IEntity::itConstEntities begin,end;
            entity->getEntityList(begin,end);
            QList<Blog> blogs;
            if(begin != end)
            {
                for(IEntity::itConstEntities it = begin; it != end; it++ )
                {
                    IEntity *sit = dynamic_cast<IEntity *>(*it);
                    if(sit->getId() == Id::entry)
                    {
                        Blog blog;                        
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
                                        blog.author.name = aux->getValue();
                                }
                                break; }
                            case Id::id:
                                blog.id = entry->getValue();
                                break;
                            case Id::published:
                                blog.published.fromString(entry->getValue(),Qt::ISODate);
                                break;
                            case Id::updated:
                                blog.updated.fromString(entry->getValue(),Qt::ISODate);
                                break;
                            case Id::summary:
                                blog.summary = entry->getValue();
                                break;
                            case Id::title:
                                blog.title = entry->getValue();
                                break;
                            default: break;
                            }
                        }                        
                        blogs.append(blog);
                    }
                 }
            }
            if(!blogs.isEmpty())
                emit onRetrieveListOfBlogsFinished(blogs);
        }
        delete entity;
    } catch(XMLParserException e) {
        qDebug() << e.what();
    }
}
