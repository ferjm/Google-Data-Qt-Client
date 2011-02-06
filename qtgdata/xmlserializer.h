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

#ifndef XMLSERIALIZER_H
#define XMLSERIALIZER_H

#include <exception>

#include "iserializer.h"

class XMLSerializerException : public std::exception
{
public:
    /**
     * Constructor "XMLSerializerException": Creates a new XMLSerializerException.
     * Default constructor.
     *
     * @param [in] what The reason or info/error clause informing about the error.
     *
     */
    XMLSerializerException(const QString& what);
    /**
     * Destructor "~XMLSerializerException": Virtual destructor
     *
     */
    virtual ~XMLSerializerException() throw () {
    }
    /**
     * Operation "What": It retrieves the reason or info/error clause informing
     * about the error.
     *
     * @return const char*. The reason or info/error clause informing about the error.
     *
     */
    virtual const char* what() const throw ();

protected:
    QString _what; /**< The reason or info/error clause informing about the error. */
};


class XMLSerializer : public ISerializer
{
public:
    struct NameSpace
    {
        QString technology;
        QString basename;
        QString shortname;
        QString vA;
    };
    struct XMLSchema {
        NameSpace nameSpace;
        QString xmlSchema;
    };
    /* List of NameSpaces */
    typedef QList<NameSpace> LNameSpaces;

private:
    LNameSpaces m_lNameSpaces;
    XMLSchema m_XMLSchema;
    /** NameSpaceToStr
     *
     *  @sNameSpace: The resulting namespace string
     *  @nameSpace: The namespace struct to convert
     *  Procedure to create xml schemas namespaces.
     *
     */
    void NameSpaceToStr(QString &sNameSpace,NameSpace nameSpace);

public:
    /** XMLSerializer
     *
     * @lNameSpaces: list of namespaces
     *
     * XMLSerializer constructor
     */
    XMLSerializer(LNameSpaces *lNameSpaces, XMLSchema schema);

    /**
     * Serialize:
     * @obj: IEntity object to serialize
     *
     * Recursive procedure to serialize a IEntity object
     *
     * Returns the QString containing the serialized entity
     *
     */
    QString Serialize(const IEntity *obj);
};

#endif // XMLSERIALIZER_H
