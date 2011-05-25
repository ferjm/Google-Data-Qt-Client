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

#ifndef QTGDATACODESEARCHCLIENT_H
#define QTGDATACODESEARCHCLIENT_H

#include "qtgdataclient.h"
#include "qtgdatacodesearchfeed.h"

class QtgdataCodeSearchClient : public QtgdataClient
{
    Q_OBJECT
public:
    explicit QtgdataCodeSearchClient(IAuthentication *auth, int version = 2, QObject *parent = 0);
    virtual ~QtgdataCodeSearchClient();

    virtual AtomFeedBase* createAtomFeed();
    virtual AtomEntry* createAtomEntry();
    virtual const int appendEntry(AtomEntry *entry);
    virtual void emitAtomFeedRetrieved();
    virtual void parseEntry(int id,AtomEntry *atomEntry,IEntity *entry);
    virtual void parseFeed(IEntity *entity);

    void query(QStringList keywords);

signals:    
    void codeSearchFeedRetrieved(CodeSearchFeed*);
};

#endif // QTGDATACODESEARCHCLIENT_H
