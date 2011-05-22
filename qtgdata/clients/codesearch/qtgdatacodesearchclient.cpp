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

#include "qtgdatacodesearchclient.h"
#include "data/codesearch/qtgdatacodesearchfeed.h"

QtgdataCodeSearchClient::QtgdataCodeSearchClient(IAuthentication *auth, int version, QObject *parent) :
    QtgdataClient(version,parent)
{
    ID = CODESEARCH;
    setAuthenticationData(auth);
}

QtgdataCodeSearchClient::~QtgdataCodeSearchClient()
{

}

AtomFeedBase* QtgdataCodeSearchClient::createAtomFeed()
{
    if(atomFeed) delete atomFeed;
    atomFeed = new CodeSearchFeed();
    return atomFeed;
}

const int QtgdataCodeSearchClient::appendEntry(AtomEntry *entry)
{
    CodeSearchFeed* csfeed = dynamic_cast<CodeSearchFeed*>(atomFeed);
    CodeSearchEntry* csentry = dynamic_cast<CodeSearchEntry*>(entry);
    if(csfeed) csfeed->entries.append(csentry);
    else return -1;
    return 0;
}

AtomEntry* QtgdataCodeSearchClient::createAtomEntry()
{
    return new CodeSearchEntry();
}

void QtgdataCodeSearchClient::emitAtomFeedRetrieved()
{
    if(atomFeed)
    {
        CodeSearchFeed *feed = dynamic_cast<CodeSearchFeed*>(atomFeed);
        if(feed) emit codeSearchFeedRetrieved(feed);
    }
}

void QtgdataCodeSearchClient::parseEntry(int id,AtomEntry *atomEntry,IEntity *entry)
{
    CodeSearchEntry *codeSearchEntry = dynamic_cast<CodeSearchEntry*>(atomEntry);
    if(codeSearchEntry)
    {
        switch(id)
        {
        case Id::file:
            codeSearchEntry->file = entry->getAttribute(AttributeId::name)->sValue;
            break;
        case Id::match:
            codeSearchEntry->match.type = entry->getAttribute(AttributeId::type)->sValue;
            codeSearchEntry->match.lineNumber = entry->getAttribute(AttributeId::lineNumber)->sValue;
            break;
        case Id::package:
            codeSearchEntry->package.name = entry->getAttribute(AttributeId::name)->sValue;
            codeSearchEntry->package.uri = entry->getAttribute(AttributeId::uri)->sValue;
            break;
        }
    }
}

void QtgdataCodeSearchClient::query(QStringList keywords)
{
    QList<QPair<QByteArray,QByteArray> > headers;
    headers.append(qMakePair(QByteArray("GData-Version"),QByteArray::number(this->version)));
    QString url("https://www.google.com/codesearch/feeds/search?q=");
    for(int i=0; i<keywords.size(); i++)
        url += keywords.at(i) + "+";
    sendClientRequest(HttpRequest::GET,
                      QUrl(url),
                      headers,
                      NULL);
}
