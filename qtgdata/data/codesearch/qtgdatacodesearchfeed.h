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

#ifndef QTGDATACODESEARCHFEED_H
#define QTGDATACODESEARCHFEED_H

#include "qtgdataatomentry.h"

class Match
{
public:
    QString type;
    QString lineNumber;
};

class Package
{
public:
    QString name;
    QUrl uri;
};

class CodeSearchEntry : public AtomEntry
{
public:
    QString file;
    Match match;
    Package package;

    virtual ~CodeSearchEntry(){};
};

class CodeSearchFeed : public AtomFeedBase
{
public:
    QList<CodeSearchEntry*> entries;

    virtual void clear() {
        this->id.clear();
        this->title.clear();
        this->authors.clear();
        this->categories.clear();
        this->links.clear();
        for(int i=0;i<this->entries.size();i++)
            if(entries.at(i) != NULL) delete entries.at(i);
        this->published = QDateTime();
    }
};

#endif // QTGDATACODESEARCHFEED_H
