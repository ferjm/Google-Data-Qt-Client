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

#ifndef DEFS_H
#define DEFS_H

#define Ids(...) typedef enum {__VA_ARGS__} tipo;             \
  const QString sAux(#__VA_ARGS__);

namespace Id
{
    Ids
    (
        NULLID,
        mockId,
        mockId2,
        mockId3,
        mockId4
    )
}

namespace AttributeId
{
    Ids
    (
        NULLID,
        mockId
    )
}

namespace NamespaceId {
    Ids
    (
        NULLID,
        mockId
    )
}


#endif // DEFS_H
