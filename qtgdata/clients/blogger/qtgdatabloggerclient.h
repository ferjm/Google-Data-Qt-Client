/***************************************************************************
 *   Copyright (C) 2010-2011 Fernando Jiménez Moreno <ferjmoreno@gmail.com>*
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

#ifndef QTGDATABLOGGERCLIENT_H
#define QTGDATABLOGGERCLIENT_H

#include "qtgdataclient.h"
#include "qtgdataatomentry.h"

class QtgdataBloggerClient : public QtgdataClient
{
    Q_OBJECT
public:
    enum OrderBy { STARTTIME, UPDATED };
    enum Alt { ATOM, RSS };

    QtgdataBloggerClient(IAuthentication *auth, int version = 2, QObject *parent = 0);
    virtual ~QtgdataBloggerClient();

    virtual AtomFeedBase* createAtomFeed();
    virtual AtomEntry* createAtomEntry();
    virtual const int appendEntry(AtomEntry *entry);
    virtual void emitAtomFeedRetrieved();
    virtual void parseEntry(int id,AtomEntry *atomEntry,IEntity *entry);
    virtual void parseFeed(IEntity *entity);

    void retrieveListOfBlogs(QString profileID = "default");
    void retrieveListOfPosts(QString blogID,                             
                             OrderBy orderby = UPDATED,
                             QStringList categories = QStringList(),
                             QDateTime publishedmin = QDateTime(),
                             QDateTime publishedmax = QDateTime(),
                             QDateTime updatedmin = QDateTime(),
                             QDateTime updatedmax = QDateTime(),
                             int maxresults = 10,
                             int startindex = 1,
                             QString etag = "");    
    void createPost(QString blogID,
                    QString title,
                    QByteArray xhtmlContent,
                    QList<Category> categories = QList<Category>());
    void updatePost(AtomEntry entry);
    void deletePost(QString blogID,QString postID);
    void createComment(QString blogID,QString postID,AtomEntry entry);
    void retrieveListOfComments(QString blogID,QString postID = QString());
    void deleteComment(QString blogID,QString postID,QString commentID);    

signals:    
    void bloggerFeedRetrieved(AtomFeed*);
};

#endif // QTGDATABLOGGERCLIENT_H
