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

#ifndef IENTITY_H
#define IENTITY_H

#include <QString>
#include <QVector>
#include <QList>

#include "qtgdata_global.h"

class Attribute
{
public:
    int iName;
    QString sName;
    QString sValue;
    QString nSpace;
};

typedef QVector<Attribute> Attributes;

class PropertyBasic
{
public:
    enum PropertyType {
        BlankProperty,
        SimpleProperty,
        ComplexProperty
    };

protected:
    int iName;
    QString sName;
    QVector<QString> basicValues;
    Attributes attributes;

    bool init(const int iname);
    bool init(const QString sname);

    PropertyBasic() :
            iName(-1),
            sName("") { attributes.clear(); }

    PropertyBasic(const unsigned int iname);
    PropertyBasic(const QString sname);
};


class QTGDATASHARED_EXPORT IEntity : public PropertyBasic
{
private:
    IEntity& operator=(const IEntity& old) { return *this; }
    IEntity& operator&(const IEntity& old) { return *this; }
    IEntity* getPrivateProperty(const int iname, const bool recursive = false) const;
    IEntity* getPrivateProperty(const QString sname, const bool recursive = false) const;
    void clear();
    bool initNamespace(const int iNamespace);
    bool initNamespace(const QString sNamespace);

protected:
    QList<IEntity*> iEntityList;
    QString sNamespace;
    int iNamespace;

public:
    typedef QList<IEntity*> *pEntity;
    typedef QList<IEntity*>::const_iterator itConstEntities;
    typedef QList<IEntity*>::iterator itEntities;
    typedef QVector<QString>::const_iterator itConstStrings;

    IEntity(const unsigned int inamespace, const unsigned int iname);
    IEntity(const unsigned int inamespace, const unsigned int iname, const QList<IEntity*> iEList);
    IEntity(const unsigned int inamespace, const unsigned int iname, const IEntity* iEntity);
    IEntity(const unsigned int inamespace, const unsigned int iname, const QVector<QString> basicValues);
    IEntity(const unsigned int inamespace, const unsigned int iname, const QString basicValue);

    virtual ~IEntity();

    virtual void addValue(QString value) { basicValues.push_back(value); }
    virtual void addValues(QList<QString> values);
    virtual void getValues(itConstStrings &begin, itConstStrings &end) const
    {
        begin = basicValues.begin();
        end = basicValues.end();
    }
    virtual QString getValue(const int index = 0) const;
    bool checkNamespaceId(const int iNamespace) const;

    virtual void addAttribute(const Attribute attribute);
    virtual void addAttribute(const QString &attributeName, const QString &attributeValue);
    virtual void addAttribute(const int iNamespace, const QString &attributeName, const QString &attributeValue);
    virtual bool checkAttributeId(const QString &attributeName) const;
    virtual bool checkAndGetAttributeId(const QString &attributeName, int &iname) const;
    virtual bool checkAttributeId(const int iAttributeName) const;
    virtual const Attribute* getAttribute(const unsigned int index);
    virtual const Attribute* getAttribute(const int iname);
    virtual Attributes* getAttributes();
    virtual bool deleteAttribute(const int index);

    virtual bool setValues(const QString sname, const QVector<QString> basicValues, bool recursive = false);
    virtual bool setValues(const unsigned int iname, const QVector<QString> basicValues, bool recursive = false);
    virtual unsigned int getValueSize(void) const { return basicValues.size(); }

    virtual bool deleteValue(const int index);

    virtual bool addEntity(IEntity *iEntity);
    virtual bool deleteEntity(const QString sname, bool erase = true);
    virtual void getEntityList(itConstEntities &begin, itConstEntities &end) const
    {
        begin = iEntityList.begin();
        end = iEntityList.end();
    }
    virtual IEntity *getEntity(const unsigned int iname, const bool recursive = false) const;    

    virtual bool isValid() const;
    PropertyType getType() const;
    const QString getName() const { return sName; }
    int getId() const { return iName; }
    int getNamespace() const { return iNamespace; }

#ifdef QTGDATA_DEBUG
    const QString toString(const unsigned int tab = 0) const;
#endif

};

#endif // IENTITY_H
