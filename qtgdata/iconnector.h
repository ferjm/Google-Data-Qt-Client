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

#ifndef ICONNECTOR_H
#define ICONNECTOR_H

#include "ientity.h"

class IConnector
{
public:
    /**
      \enum CONNECTION_MODE
      Indicates the client working mode.
     */
    enum CONNECTION_MODE
    {
        HTTP_REST,
        TEST_OK
    };
private:
    CONNECTION_MODE connectionMode;

public:
    IConnector(CONNECTION_MODE connMode) : connectionMode(connMode) {};
    CONNECTION_MODE getConnectionMode() { return connectionMode; };
    virtual IEntity* createEntity(const IEntity *in) = 0;
    virtual IEntity* retrieveEntity(const IEntity *in) = 0;
    virtual IEntity* updateEntity(const IEntity *in) = 0;
    virtual IEntity* deleteEntity(const IEntity *in) = 0;
};

#endif // ICONNECTOR_H
