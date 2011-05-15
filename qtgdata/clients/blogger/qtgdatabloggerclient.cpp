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
    QList<QPair<QByteArray,QByteArray> > headers;
    headers.append(qMakePair(QByteArray("GData-Version"),QByteArray::number(this->version)));
    sendClientRequest(HttpRequest::GET,
                      QUrl(QString(BLOGGER_FEEDS) + profileID +"/blogs"),
                      headers,
                      &(this->httpConnector),
                      SIGNAL(requestFinished(QByteArray)),
                      this,
                      SLOT(onAtomFeedRetrieved(QByteArray))
                      );

}

void QtgdataBloggerClient::retrieveListOfPosts(QString blogID,
                                               Alt alt,
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
        if(orderby == UPDATED)
            endpoint += "&updated-min=" + updatedmin.toString(Qt::ISODate) +
                        "&updated-max=" + updatedmax.toString(Qt::ISODate);
        else
            qWarning("Updatedmin and updatedmax are ignored cause orderby parameter is not set to UPDATED");
    QList<QPair<QByteArray,QByteArray> > headers;
    headers.append(qMakePair(QByteArray("GData-Version"),QByteArray::number(this->version)));
    if(!etag.isEmpty())
        headers.append(qMakePair(QByteArray("If-None-Match"),QByteArray(etag.toAscii())));
    sendClientRequest(HttpRequest::GET,
                      QUrl(endpoint),
                      headers,
                      &(this->httpConnector),
                      SIGNAL(requestFinished(QByteArray)),
                      this,
                      SLOT(onAtomFeedRetrieved(QByteArray)),
                      false);
}
