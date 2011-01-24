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

#ifndef QTGDATA_H
#define QTGDATA_H

//#include <QVector>
//#include <QString>
//
//
//#include "qtgdata_global.h"
//
//// Singleton class
//// pending client factory implementation
//class QTGDATASHARED_EXPORT Qtgdata {
//    static QVector<QString> properties;
//    static QVector<QString> attributes;
//    static QVector<QString> namespaces;
//
//    static Qtgdata qtgdata;
//    Qtgdata();
//public:
//     ~Qtgdata();
//     static Qtgdata* getInstance();
//     static QVector<QString>* getProperties();
//     static QVector<QString>* getAttributes();
//     static QVector<QString>* getNamespaces();
//};

// <lor>
#include <QStringList>
#include "defs.h"
class QTGDATASHARED_EXPORT Qtgdata {
    QStringList properties;
    QStringList attributes;
    QStringList namespaces;
    Qtgdata()
    {
    }
    ~Qtgdata();
public:
    QStringList& getProperties()
    {
      if (properties.isEmpty())
          properties = Id::sAux.split(QString(", "));
      return properties;
    }
    QStringList& getAttributes()
    {
        if (attributes.isEmpty())
            attributes = AttributeId::sAux.split(QString(", "));
        return attributes;
    }
    QStringList& getNamespaces()
    {
        if (namespaces.isEmpty())
            namespaces = NamespaceId::sAux.split(QString(", "));
        return namespaces;
    }
};
// </lor>

#endif // QTGDATA_H
