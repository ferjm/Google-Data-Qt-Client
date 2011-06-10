/***************************************************************************
 *   Copyright (C) 2010-2011 Fernando Jiménez Moreno <ferjmoreno@gmail.com>*
 *                                                                         *
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 3 of the License, or     *
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

#include "qtgdata.h"
#include "qtgdatadefs.h"

Qtgdata Qtgdata::qtgdata;

Qtgdata::Qtgdata()
{
}

Qtgdata::~Qtgdata()
{

}

Qtgdata* Qtgdata::getInstance()
{
    return &qtgdata;
}

QStringList& Qtgdata::getAttributes()
{
    if (attributes.isEmpty())
        attributes = AttributeId::sAux.split(QString(", "));
    return attributes;
}

QStringList& Qtgdata::getProperties()
{
    if (properties.isEmpty())
        properties = Id::sAux.split(QString(", "));
    return properties;
}

QStringList& Qtgdata::getNamespaces()
{
    if (namespaces.isEmpty())
        namespaces = NamespaceId::sAux.split(QString(", "));
    return namespaces;
}
