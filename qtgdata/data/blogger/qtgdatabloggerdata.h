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

#ifndef QTGDATABLOGGERDATA_H
#define QTGDATABLOGGERDATA_H

#include <ostream>

/*atom*/
class Author
{
public:
    QString name;
    QString email;
    QUrl uri;
};

class Link
{
    QString rel;
    QString type;
    QUrl href;
};

/*blogger*/
class Blog
{
public:    
    QString id;
    QString title;
    Author author;
    QDateTime published;
    QDateTime updated;
    QString summary;
    QList<Link> links;

    friend std::ostream& operator<< (std::ostream &out,Blog &blog) {
        out << "Blog: \n" << "\t id: " << blog.id.toAscii().data() <<
               "\n\t title: " << blog.title.toAscii().data() <<
               "\n\t author: " << blog.author.name.toAscii().data() << " " << blog.author.email.toAscii().data() <<
               "\n\t QString summary: " << blog.summary.toAscii().data();
        return out;
    };
};

#endif // QTGDATABLOGGERDATA_H
