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

#include "xmlserializer.h"

#include <QtXml/QXmlStreamWriter>

XMLSerializerException::XMLSerializerException(const QString &what) : _what(what)
{
}

const char* XMLSerializerException::what() const throw()
{
    QString retval = "XMLSerializerException: " + _what;
    return retval.toAscii();
}

XMLSerializer::XMLSerializer( LNameSpaces *lNameSpaces,XMLSchema schema )
{
    m_lNameSpaces = *lNameSpaces;
    m_XMLSchema.nameSpace = schema.nameSpace;
    m_XMLSchema.xmlSchema = schema.xmlSchema;
}

QString XMLSerializer::Serialize( const IEntity *obj )
{
    if((obj == NULL) || (!obj->isValid())) throw XMLSerializerException("Invalid entity\n");
    QString output;
    QXmlStreamWriter stream(&output);
    stream.setAutoFormatting(true);
    stream.writeStartDocument();
/*  stream.writeStartElement("bookmark");
    stream.writeAttribute("href", "http://qt.nokia.com/");
    stream.writeTextElement("title", "Qt Home");
    stream.writeEndElement(); // bookmark
*/
    stream.writeEndDocument();
    return output;
}
