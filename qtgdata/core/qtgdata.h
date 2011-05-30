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

#include <QStringList>

#include "qtgdatadefs.h"
#include "qtgdata_global.h"

/**
  * \class Qtgdata
  * Singleton class containing the core data of the elements
  * to be shared between clients and server.
  */
class QTGDATASHARED_EXPORT Qtgdata {
    /**
     * String list containing the id of the entity tags
     */
    QStringList properties;
    /**
     * String list containing the id of the entity attributes
     */
    QStringList attributes;
    /**
     * String list containing the entity namespaces ids.
     */
    QStringList namespaces;
    /**
     * Single instance
     */
    static Qtgdata qtgdata;
    /**
     * Constructor
     */
    Qtgdata();

public:
    /**
     * Destructor
     */
    ~Qtgdata();
    /**
     * Gets a reference of the single instance
     */
    static Qtgdata* getInstance();
    /**
     * Gets the list of entity tags ids
     */
    QStringList& getProperties();
    /**
     * Gets the list of attributes ids
     */
    QStringList& getAttributes();
    /**
     * Gets the list of namespaces
     */
    QStringList& getNamespaces();
};

#endif // QTGDATA_H
