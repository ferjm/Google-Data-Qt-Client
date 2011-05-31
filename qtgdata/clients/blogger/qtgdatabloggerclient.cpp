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
#include "qtgdataxmlserializer.h"
#include "data/codesearch/qtgdatacodesearchfeed.h"

#include <QDebug>

#define BLOGGER_FEEDS "http://www.blogger.com/feeds/"


QtgdataBloggerClient::QtgdataBloggerClient(IAuthentication *auth, int version, QObject *parent) :
    QtgdataClient(version,parent)
{
    ID = BLOGGER;
    setAuthenticationData(auth);    
}

QtgdataBloggerClient::~QtgdataBloggerClient()
{

}

AtomFeedBase* QtgdataBloggerClient::createAtomFeed()
{
    if(atomFeed) delete atomFeed;
    atomFeed = new AtomFeed();
    return atomFeed;
}

AtomEntry* QtgdataBloggerClient::createAtomEntry()
{
    return new AtomEntry();
}

void QtgdataBloggerClient::emitAtomFeedRetrieved()
{
    if(atomFeed)
    {
        AtomFeed *feed = dynamic_cast<AtomFeed*>(atomFeed);
        if(feed) emit bloggerFeedRetrieved(feed);
    }
}

const int QtgdataBloggerClient::appendEntry(AtomEntry *entry)
{
    AtomFeed* feed = dynamic_cast<AtomFeed*>(atomFeed);
    if(feed) feed->entries.append(entry);
    else return QTGDATA_ERROR_FAILED;
    return QTGDATA_SUCCESS;
}

void QtgdataBloggerClient::parseEntry(int id,AtomEntry *atomEntry,IEntity *entry)
{

}

void QtgdataBloggerClient::parseFeed(IEntity *entity)
{

}

void QtgdataBloggerClient::retrieveListOfBlogs(QString profileID)
{
    QList<QPair<QByteArray,QByteArray> > headers;
    headers.append(qMakePair(QByteArray("GData-Version"),QByteArray::number(this->version)));
    sendClientRequest(HttpRequest::GET,
                      QUrl(QString(BLOGGER_FEEDS) + profileID +"/blogs"),
                      headers,
                      NULL);
}

void QtgdataBloggerClient::retrieveListOfPosts(QString blogID,                                               
                                               OrderBy orderby,
                                               QStringList categories,
                                               QDateTime publishedmin,
                                               QDateTime publishedmax,
                                               QDateTime updatedmin,
                                               QDateTime updatedmax,
                                               int maxresults,
                                               int startindex,
                                               QString etag)
{    
    QString endpoint = QString(BLOGGER_FEEDS) + blogID + "/posts/default";
    if(!categories.isEmpty())
    {
        endpoint += "/-";
        foreach(const QString& category,categories)
            endpoint += "/" + category;
    }
    switch(orderby)
    {
    case STARTTIME:
        endpoint += "?orderby=starttime";
        break;
    case UPDATED:
        endpoint += "?orderby=updated";
        break;
    }
    endpoint += "&max-results=" + QString::number(maxresults);
    endpoint += "&start-index=" + QString::number(startindex);
    if((!publishedmin.isNull()) && (!publishedmax.QDateTime::isNull()))
        endpoint += "&published-min=" + publishedmin.toString(Qt::ISODate) +
                    "&published-max=" + publishedmax.toString(Qt::ISODate);
    if((!updatedmin.isNull()) && (!updatedmax.QDateTime::isNull()))
    {
        if(orderby == UPDATED)
            endpoint += "&updated-min=" + updatedmin.toString(Qt::ISODate) +
                        "&updated-max=" + updatedmax.toString(Qt::ISODate);
        else
            qWarning("Updatedmin and updatedmax are ignored cause orderby parameter is not set to UPDATED");
    }
    QList<QPair<QByteArray,QByteArray> > headers;
    headers.append(qMakePair(QByteArray("GData-Version"),QByteArray::number(this->version)));
    if(!etag.isEmpty())
        headers.append(qMakePair(QByteArray("If-None-Match"),QByteArray(etag.toAscii())));
    sendClientRequest(HttpRequest::GET,
                      QUrl(endpoint),
                      headers,
                      NULL,
                      false);
}

void QtgdataBloggerClient::createPost(QString blogID,
                                      QString title,
                                      QByteArray xhtmlContent,
                                      QList<Category> categories)
//FIXME: onAtomFeedRetrieved
//TODO: draft support
{
    IEntity *entry = new IEntity(NamespaceId::atom,Id::entry);
    IEntity *titleEntity = new IEntity(NamespaceId::atom,Id::title,title);
    entry->addEntity(titleEntity);
    IEntity *content = new IEntity(NamespaceId::atom,Id::content);
    content->addAttribute(NamespaceId::atom,AttributeId::type,QString("xhtml"));
    content->addValue(QString(xhtmlContent));
    entry->addEntity(content);
    for(int i= 0; i < categories.size(); i++)
    {
        IEntity *category = new IEntity(Id::category);
        category->addAttribute(NamespaceId::atom,AttributeId::scheme,categories.at(i).scheme.toString());
        category->addAttribute(NamespaceId::atom,AttributeId::term,categories.at(i).term);
        entry->addEntity(category);
    }
    QMultiMap<int,QString> namespaces;
    namespaces.insert(NamespaceId::atom,"http://www.w3.org/2005/Atom");
    XMLSerializer serializer(namespaces);
    QString serializedBody = serializer.serialize(entry);
    delete entry;
    QList<QPair<QByteArray,QByteArray> > headers;
    headers.append(qMakePair(QByteArray("GData-Version"),QByteArray::number(this->version)));
    sendClientRequest(HttpRequest::POST,
                      QUrl(QString(BLOGGER_FEEDS) + blogID + "/posts/default"),
                      headers,
                      &QByteArray(serializedBody.toAscii()));
}

void QtgdataBloggerClient::updatePost(AtomEntry entry)
{
    IEntity *entryEntity = new IEntity(NamespaceId::atom,Id::entry);
    bool relUrl = false;
    QUrl endpoint;
    for(int i=0; i < entry.links.size(); i++)
    {
        IEntity *link = new IEntity(Id::link);
        link->addAttribute(NamespaceId::atom,AttributeId::rel,entry.links.at(i).rel);
        link->addAttribute(NamespaceId::atom,AttributeId::type,entry.links.at(i).type);
        link->addAttribute(NamespaceId::atom,AttributeId::href,entry.links.at(i).href.toString());
        if(entry.links.at(i).rel == "edit")
        {
            endpoint = entry.links.at(i).href;
            relUrl = true;
        }
        entryEntity->addEntity(link);
    }
    if(!relUrl) return;
    IEntity *id = new IEntity(NamespaceId::atom,Id::id,entry.id);
    entryEntity->addEntity(id);
    IEntity *published = new IEntity(NamespaceId::atom,Id::published,entry.published.toString(Qt::ISODate));
    entryEntity->addEntity(published);
    IEntity *updated = new IEntity(NamespaceId::atom,Id::updated,entry.updated.toString(Qt::ISODate));
    entryEntity->addEntity(updated);
    for(int i=0; i<entry.categories.size(); i++)
    {
        IEntity *category = new IEntity(NamespaceId::atom,Id::category);
        category->addAttribute(NamespaceId::atom,AttributeId::scheme,entry.categories.at(i).scheme.toString());
        category->addAttribute(NamespaceId::atom,AttributeId::term,entry.categories.at(i).term);
        entryEntity->addEntity(category);
    }
    IEntity *content = new IEntity(NamespaceId::atom,Id::content,QString(entry.content.content));
    content->addAttribute(NamespaceId::atom,AttributeId::type,entry.content.type);
    entryEntity->addEntity(content);
    for(int i=0; i<entry.authors.size(); i++)
    {
        IEntity *author = new IEntity(NamespaceId::atom,Id::author);
        IEntity *name = new IEntity(NamespaceId::atom,Id::name,entry.authors.at(i).name);
        author->addEntity(name);
        IEntity *uri = new IEntity(NamespaceId::atom,Id::uri,entry.authors.at(i).uri.toString());
        author->addEntity(uri);
        IEntity *email = new IEntity(NamespaceId::atom,Id::email,entry.authors.at(i).email);
        author->addEntity(email);
        entryEntity->addEntity(author);
    }
    QMultiMap<int,QString> namespaces;
    namespaces.insert(NamespaceId::atom,"http://www.w3.org/2005/Atom");
    XMLSerializer serializer(namespaces);
    QString serializedBody = serializer.serialize(entryEntity);
    delete entryEntity;
    QList<QPair<QByteArray,QByteArray> > headers;
    headers.append(qMakePair(QByteArray("GData-Version"),QByteArray::number(this->version)));
    headers.append(qMakePair(QByteArray("X-HTTP-Method-Override"),QByteArray("PUT")));
    sendClientRequest(HttpRequest::PUT,
                      endpoint,
                      headers,
                      &QByteArray(serializedBody.toAscii()));
}

void QtgdataBloggerClient::deletePost(QString blogID,QString postID)
{
    QUrl endpoint(QString(BLOGGER_FEEDS) + blogID + "/posts/default/" + postID);
    QList<QPair<QByteArray,QByteArray> > headers;
    headers.append(qMakePair(QByteArray("GData-Version"),QByteArray::number(this->version)));
    headers.append(qMakePair(QByteArray("X-HTTP-Method-Override"),QByteArray("DELETE")));
    sendClientRequest(HttpRequest::DELETE,
                      endpoint,
                      headers,
                      NULL);
}

void QtgdataBloggerClient::createComment(QString blogID,QString postID,AtomEntry entry)
{
    IEntity *entryEntity = new IEntity(NamespaceId::atom,Id::entry);
    IEntity *title = new IEntity(NamespaceId::atom,Id::title,entry.title);
    entryEntity->addEntity(title);
    IEntity *content = new IEntity(NamespaceId::atom,Id::content,QString(entry.content.content));
    entryEntity->addEntity(content);

    /*QStringList namespaces;
    namespaces.append("http://www.w3.org/2005/Atom");*/
    QMultiMap<int,QString> namespaces;
    namespaces.insert(NamespaceId::atom,"http://www.w3.org/2005/Atom");
    XMLSerializer serializer(namespaces);
    QString serializedBody = serializer.serialize(entryEntity);
    delete entryEntity;
    QList<QPair<QByteArray,QByteArray> > headers;
    headers.append(qMakePair(QByteArray("GData-Version"),QByteArray::number(this->version)));
    sendClientRequest(HttpRequest::POST,
                      QUrl(QString(BLOGGER_FEEDS) + blogID + "/" + postID +"/comments/default"),
                      headers,
                      &QByteArray(serializedBody.toAscii()));
}

void QtgdataBloggerClient::deleteComment(QString blogID, QString postID, QString commentID)
{
    //http://www.blogger.com/feeds/blogID/postID/comments/default/commentID
    QList<QPair<QByteArray,QByteArray> > headers;
    headers.append(qMakePair(QByteArray("GData-Version"),QByteArray::number(this->version)));
    sendClientRequest(HttpRequest::DELETE,
                      QUrl(QString(BLOGGER_FEEDS) + blogID + "/" + postID + "/comments/default/" + commentID),
                      headers,
                      NULL);
}

void QtgdataBloggerClient::retrieveListOfComments(QString blogID, QString postID)
{
    QList<QPair<QByteArray,QByteArray> > headers;
    headers.append(qMakePair(QByteArray("GData-Version"),QByteArray::number(this->version)));
    QString endpoint = QString(BLOGGER_FEEDS) + blogID;
    if(!postID.isEmpty())
        endpoint += "/" + postID;
    endpoint += "/comments/default";
    sendClientRequest(HttpRequest::GET,
                      QUrl(endpoint),
                      headers,
                      NULL);
}
