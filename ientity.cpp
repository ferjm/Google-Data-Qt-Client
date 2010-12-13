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

#include "ientity.h"
#include "qtgdata.h"

/*
    PropertyBasic implementation
*/
bool PropertyBasic::init(const unsigned int iname)
{
    QVector<QString>* properties = Qtgdata::getInstance()->getProperties();
    if(iname < properties->size())
    {
        iName = iname;
        sName = properties->at(iname);
        return true;
    }
    iName = -1;
    sName = "";
    return false;
}

bool PropertyBasic::init(const QString sname)
{
    QVector<QString>* properties = Qtgdata::getInstance()->getProperties();
    for(unsigned int i = 0; i < properties->size(); i++)
    {
        if(sname == properties->at(i))
        {
            iName = i;
            sName = sname;
            return true;
        }
    }
    iName = -1;
    sName = "";
    return false;
}

PropertyBasic::PropertyBasic(const unsigned int iname)
{
    init(iname);
}

PropertyBasic::PropertyBasic(const QString sname)
{
    init(sname);
}


/*
 IEntity implementation
*/
IEntity* IEntity::getPrivateProperty(const int iname, const bool recursive) const
{

    if(iName == iname)
        return(IEntity*) this;

    for(itConstEntities it = iEntityList.begin(); it != iEntityList.end(); it++)
    {
        IEntity *sit = dynamic_cast<IEntity*>(*it);
        if((sit != NULL) && (sit->iName == iname))
            return sit;
    }
    if(!recursive)
        return NULL;

    for(itConstEntities it = iEntityList.begin(); it != iEntityList.end(); it++)
    {
        IEntity *sit = dynamic_cast<IEntity*>(*it);
        if((sit != NULL))
        {
            IEntity *oFound = sit->getPrivateProperty(iname, recursive);
            if(oFound != NULL)
                return oFound;
        }
    }
    return NULL;
}

IEntity* IEntity::getPrivateProperty(const QString sname, const bool recursive) const
{
    if(sName == sname)
        return(IEntity*)this;

    for(itConstEntities it = iEntityList.begin(); it != iEntityList.end(); it++)
    {
        IEntity *sit = dynamic_cast<IEntity*>(*it);
        if((sit != NULL) && (sit->sName == sname))
            return sit;
    }
    if(!recursive)
        return NULL;

    for(itConstEntities it = iEntityList.begin(); it != iEntityList.end(); it++)
    {
        IEntity *sit = dynamic_cast<IEntity *>(*it);
        if((sit != NULL))
        {
            IEntity *oFound = sit->getPrivateProperty(sname, recursive);
            if(oFound != NULL)
                return oFound;
        }
    }
    return NULL;
}

void IEntity::clear()
{
    for(itEntities it = iEntityList.begin(); it != iEntityList.end(); it++)
    {
        IEntity *sit = dynamic_cast<IEntity*>(*it);
        if(sit != NULL)
            delete(sit);
    }
    iEntityList.clear();
    iName = -1;
    sName = "";
    basicValues.clear();
}

bool IEntity::initNamespace(const unsigned int iNamespace)
{
    QVector<QString> *namespaces = Qtgdata::getInstance()->getNamespaces();
    if(iNamespace < namespaces->size())
    {
        this->iNamespace = iNamespace;
        sNamespace = namespaces->at(iNamespace);
        return true;
    }
    this->iNamespace = -1;
    sNamespace = "";
    return false;
}

bool IEntity::initNamespace(const QString sNamespace)
{
    QVector<QString> *namespaces = Qtgdata::getInstance()->getNamespaces();
    for(unsigned int i = 0; i < namespaces->size(); i++)
    {   if(iNamespace < namespaces->size())
        {
            iNamespace = i;
            this->sNamespace = sNamespace;
            return true;
        }
    }
    iNamespace = -1;
    this->sNamespace = "";
    return false;
}

IEntity::IEntity(const unsigned int inamespace, const unsigned int iname)
{
    if(init(iname) && checkNamespaceId(inamespace) && initNamespace(inamespace))
        iNamespace = inamespace;
}

IEntity::IEntity(const unsigned int inamespace, const unsigned int iname, const IEntity *iEntity)
{
    if(init(iname) && checkNamespaceId(inamespace) && initNamespace(inamespace))
    {
        iNamespace = inamespace;
        iEntityList.push_back((IEntity*)iEntity);
    }
}

IEntity::IEntity(const unsigned int inamespace, const unsigned int iname, const QList<IEntity *> iEList)
{
    if(init(iname) && initNamespace(inamespace) && checkNamespaceId(inamespace))
    {
        iNamespace = inamespace;
        iEntityList = iEList;
    }
}

IEntity::IEntity(const unsigned int inamespace, const unsigned int iname, const QString basicValue)
{
    if(init(iname) && checkNamespaceId(inamespace && initNamespace(inamespace)))
    {
        iNamespace = inamespace;
        basicValues.push_back(basicValue);
    }
}

IEntity::IEntity(const unsigned int inamespace, const unsigned int iname, const QVector<QString> basicValues)
{
    if(init(iname) && checkNamespaceId(iNamespace) && initNamespace(inamespace))
    {
        iNamespace = inamespace;
        this->basicValues = basicValues;
    }
}

IEntity::~IEntity()
{
    clear();
}

void IEntity::addValues(QList<QString> values)
{
    QList<QString>::iterator it;
    for(it = values.begin(); it != values.end(); it++)
        basicValues.push_back((*it));
}

QString IEntity::getValue(const unsigned int index) const
{
    if(index >= basicValues.size())
        return NULL;
    return(basicValues[index]);
}

bool IEntity::checkNamespaceId(const int inamespace) const
{
    return((inamespace >= 0) && (inamespace < Qtgdata::getInstance()->getNamespaces()->size()));
}

void IEntity::addAttribute(const Attribute attribute)
{
    if(checkAttributeId(attribute.iName) == true)
        attributes.push_back(attribute);
}

void IEntity::addAttribute(const QString &attributeName, const QString &attributeValue)
{
    Attribute attr;
    if(checkAndGetAttributeId(attributeName,attr.iName) == true)
    {
        attr.sValue = attributeValue;
        attr.sName = attributeName;
        attributes.push_back(attr);
    }
}

bool IEntity::checkAttributeId(const int iAttributeName) const
{
    return((iAttributeName >= 0) && (iAttributeName < Qtgdata::getInstance()->getAttributes()->size()));
}

bool IEntity::checkAndGetAttributeId(const QString &attributeName, int &iname) const
{
    QVector<QString> *attributes = Qtgdata::getInstance()->getAttributes();
    for(unsigned int i = 0; i < attributes->size(); i++)
        if(attributeName == attributes->at(i))
            return true;
}

bool IEntity::checkAttributeId(const QString &attributeName) const
{
    QVector<QString> *attributes = Qtgdata::getInstance()->getAttributes();
    for(unsigned int i = 0; i < attributes->size(); i++)
        if(attributeName == attributes->at(i))
            return true;
    return false;
}

const Attribute* IEntity::getAttribute(const int iname)
{
    Attributes::const_iterator it = attributes.begin();
    unsigned int index = 0;
    while(it != attributes.end())
    {
        if((((Attribute)(*it)).iName) == iname)
            return &(attributes.at(index));
        it++;
        index++;
    }
    return NULL;
}

const Attribute* IEntity::getAttribute(const unsigned int index)
{
    if(index >= attributes.size())
        return NULL;
    return &(attributes.at(index));
}

Attributes* IEntity::getAttributes()
{
    return &attributes;
}

bool IEntity::deleteAttribute(const unsigned int index)
{
    if(index >= attributes.size())
        return false;
    Attributes::iterator it = attributes.begin() + index;
    attributes.erase(it);
    return true;
}

bool IEntity::setValues(const QString sname, const QVector<QString> basicValues, bool recursive)
{
    const IEntity *found = getPrivateProperty(sname, recursive);
    if(found != NULL)
    {
        this->basicValues = basicValues;
        return true;
    }
    return false;
}

bool IEntity::setValues(const unsigned int iname, const QVector<QString> basicValues, bool recursive)
{
    const IEntity *found = getPrivateProperty(iname, recursive);
    if(found != NULL)
    {
        this->basicValues = basicValues;
        return true;
    }
    return false;
}

bool IEntity::deleteValue(const unsigned int index)
{
    if(index != basicValues.size())
        return false;
    QVector<QString>::iterator it = basicValues.begin() + index;
    basicValues.erase(it);
    return true;
}

bool IEntity::addEntity(IEntity *iEntity)
{
    IEntity *sit = dynamic_cast<IEntity*>(iEntity);
    if(sit != NULL)
    {
        iEntityList.push_back(iEntity);
        return true;
    }
    return false;
}
