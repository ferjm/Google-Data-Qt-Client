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

#include "qtgdataxmlserializer.h"

XMLSerializerException::XMLSerializerException(const QString &what) : _what(what)
{
}

const char* XMLSerializerException::what() const throw()
{
    QString retval = "XMLSerializerException: " + _what;
    return retval.toAscii();
}

XMLSerializer::XMLSerializer(QStringList *lNameSpaces,XMLSchema schema)
{
    m_lNameSpaces = *lNameSpaces;
    m_XMLSchema.nameSpace = schema.nameSpace;
    m_XMLSchema.xmlSchema = schema.xmlSchema;
}

void XMLSerializer::serialize(const IEntity *obj, QXmlStreamWriter *stream)
{
    IEntity::itConstEntities it,ite;
    obj->getEntityList(it,ite);
    for(;it != ite; it++)
    {
        IEntity *it_ent = (*it);
        if(it_ent->getType() == PropertyBasic::ComplexProperty)
        {
            stream->writeStartElement(it_ent->getNamespace(), it_ent->getName());
            Attributes *attributes = it_ent->getAttributes();
            if((attributes) && (!attributes->empty()))
            {
                Attributes::const_iterator it = attributes->begin();
                while(it != attributes->end())
                {
                    stream->writeAttribute(((Attribute)(*it)).nSpace,
                                           ((Attribute)(*it)).sName,
                                           ((Attribute)(*it)).sValue);
                    it++;
                }
            }
            serialize(it_ent,stream);
            stream->writeEndElement();
        }
        else
        {
            if(it_ent->getType() == PropertyBasic::SimpleProperty)
            {
                IEntity::itConstStrings its,itse;
                it_ent->getValues(its,itse);
                for(;its != itse; its++)
                {
                    stream->writeTextElement(it_ent->getNamespace(),
                                             it_ent->getName(),
                                             (QString)(*its));
                    Attributes *attributes = it_ent->getAttributes();
                    if((attributes) && (!attributes->empty()))
                    {
                        Attributes::const_iterator it = attributes->begin();
                        while(it != attributes->end())
                        {
                            stream->writeAttribute(((Attribute)(*it)).nSpace,
                                                   ((Attribute)(*it)).sName,
                                                   ((Attribute)(*it)).sValue);
                            it++;
                        }
                    }
                }
            }
        }
    }
}

QString XMLSerializer::serialize(const IEntity *obj)
{
    if((obj == NULL) || (!obj->isValid())) throw XMLSerializerException("Invalid entity\n");
    QString output;
    QXmlStreamWriter stream(&output);    
    stream.writeStartDocument();
    stream.writeStartElement(obj->getNamespace(),obj->getName());
    QStringList::iterator it;
    for (QStringList::iterator it = m_lNameSpaces.begin();it
            != m_lNameSpaces.end();it++)
        stream.writeNamespace((QString)(*it));
    serialize(obj,&stream);
    stream.writeEndElement();
    stream.writeEndDocument();
    return output;
}
