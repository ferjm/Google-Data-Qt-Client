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

#include <QtCore/QString>
#include <QtTest/QtTest>

#include <iostream>

#include "qtgdata/ientity.h"
#include "qtgdata/xmlserializer.h"

class QtgdataTest : public QObject
{
    Q_OBJECT

public:
    QtgdataTest();    

private Q_SLOTS:
    //IEntity tests
    void createEntity();
    void createEntityWithEntity();
    void createEntityWithList();
    void createEntityWithBasicValue();
    void createEntityWithBasicValues();
    void addValue();
    void addValues();
    void addAttribute();
    void addEntity();
    void deleteEntity();

    //XMLSerializer tests
    void serializeNULLEntity();
    void serializeSingleEntity();
    void serializeComplexEntities();
};

QtgdataTest::QtgdataTest()
{
}

void QtgdataTest::createEntity()
{
    IEntity *entity = new IEntity(NamespaceId::mockId, Id::mockId);
    QVERIFY(entity->getId() == Id::mockId);
    delete entity;
}

void QtgdataTest::createEntityWithEntity()
{
    IEntity *entity = new IEntity(NamespaceId::mockId, Id::mockId);
    IEntity *entity2 = new IEntity(NamespaceId::mockId, Id::mockId2, entity);
    IEntity *aux = entity2->getEntity(Id::mockId2);
    QVERIFY(aux->getId() == Id::mockId2);
    delete entity;
}

void QtgdataTest::createEntityWithList()
{
    QList<IEntity*> ielist;
    IEntity *entity = new IEntity(NamespaceId::mockId, Id::mockId);
    ielist.append(entity);
    IEntity *entity2 = new IEntity(NamespaceId::mockId, Id::mockId2);
    ielist.append(entity2);
    IEntity *entity3 = new IEntity(NamespaceId::mockId, Id::mockId3);
    ielist.append(entity3);
    IEntity *entity4 = new IEntity(NamespaceId::mockId, Id::mockId4,ielist);
    IEntity::itConstEntities begin, end;
    entity4->getEntityList(begin, end);
    IEntity::itConstEntities it = begin;
    QVERIFY((*it)->getId() == Id::mockId); // entity
    it++;
    QVERIFY((*it)->getId() == Id::mockId2); // entity2
    it++;
    QVERIFY((*it)->getId() == Id::mockId3); //entity3
    delete entity4;
}

void QtgdataTest::createEntityWithBasicValue()
{
    IEntity *entity = new IEntity(NamespaceId::mockId, Id::mockId, QString("basicvaluetest"));
    QVERIFY(entity->getValue() == QString("basicvaluetest"));
}

void QtgdataTest::createEntityWithBasicValues()
{
    QVector<QString> basicValues;
    basicValues.append(QString("1"));
    basicValues.append(QString("2"));
    IEntity *entity = new IEntity(NamespaceId::mockId, Id::mockId, basicValues);
    IEntity::itConstStrings begin, end, aux;
    entity->getValues(begin, end);
    aux = begin;
    QVERIFY((*aux) == QString("1"));
    aux++;
    QVERIFY((*aux) == QString("2"));
    delete entity;
}

void QtgdataTest::addValue()
{
    IEntity *entity = new IEntity(NamespaceId::mockId, Id::mockId);
    entity->addValue(QString("1"));
    entity->addValue(QString("2"));
    entity->addValue(QString("3"));
    IEntity::itConstStrings begin, end, aux;
    entity->getValues(begin, end);
    int i = 0;
    for(aux = begin; aux < end; aux++)
    {
        i++;
        QString value;
        value.setNum(i);
        QVERIFY((*aux) == value);
    }
    delete entity;
}

void QtgdataTest::addValues()
{
    IEntity *entity = new IEntity(NamespaceId::mockId, Id::mockId);
    QStringList basicValues;
    basicValues.append(QString("1"));
    basicValues.append(QString("2"));
    basicValues.append(QString("3"));
    IEntity::itConstStrings begin, end, aux;
    entity->getValues(begin, end);
    int i = 0;
    for(aux = begin; aux < end; aux++)
    {
        i++;
        QString value;
        value.setNum(i);
        QVERIFY((*aux) == value);
    }
    delete entity;
}

void QtgdataTest::addAttribute()
{
    IEntity *entity = new IEntity(NamespaceId::mockId, Id::mockId);
    entity->addAttribute(NamespaceId::mockId, AttributeId::mockId, QString("value"));
    const Attribute *attribute = entity->getAttribute(AttributeId::mockId);
    QVERIFY(attribute->iName == AttributeId::mockId);
    delete entity;
}

void QtgdataTest::addEntity()
{
    IEntity *entity = new IEntity(NamespaceId::mockId, Id::mockId);
    entity->addEntity(new IEntity(NamespaceId::mockId, Id::mockId2));
    QVERIFY(entity->getEntity(Id::mockId2)->getId() == Id::mockId2);
}

void QtgdataTest::deleteEntity()
{
    IEntity *entity = new IEntity(NamespaceId::mockId, Id::mockId);
    entity->addEntity(new IEntity(NamespaceId::mockId, Id::mockId2));
    QVERIFY(entity->getEntitySize() == 1);
    entity->deleteEntity(Id::mockId);
    QVERIFY(entity->getEntitySize() == 1);
    entity->deleteEntity(Id::mockId2);
    QVERIFY(entity->getEntitySize() == 0);
}

/* XMLSerializer tests*/
void QtgdataTest::serializeNULLEntity()
{
    XMLSerializer::XMLSchema sch;
    QStringList namespaces;
    namespaces.append("");
    XMLSerializer serializer(&namespaces,sch);
    try
    {
        QString output = serializer.serialize(NULL);
        QVERIFY(false);
    }
    catch(XMLSerializerException)
    {
        QVERIFY(true);
    }
}

void QtgdataTest::serializeSingleEntity()
{
    XMLSerializer::XMLSchema sch;
    sch.nameSpace = "http://schema.namespace";
    sch.xmlSchema = "schema";
    QStringList namespaces;
    namespaces.append("http://testnamespace");
    XMLSerializer serializer(&namespaces,sch);
    IEntity *entity = new IEntity(NamespaceId::mockId,Id::mockId,"test");
    try
    {
        QString output = serializer.serialize(entity);
        QVERIFY(true);
        delete entity;
    }
    catch(XMLSerializerException)
    {
        QVERIFY(false);
        delete entity;
    }
}

void QtgdataTest::serializeComplexEntities()
{
    XMLSerializer::XMLSchema sch;
    sch.nameSpace = "http://schema.namespace";
    sch.xmlSchema = "schema";
    QStringList namespaces;
    namespaces.append("http://testnamespace");
    XMLSerializer serializer(&namespaces,sch);
    IEntity *entity = new IEntity(NamespaceId::mockId,Id::mockId);
    entity->addEntity(new IEntity(NamespaceId::mockId,Id::mockId2,"test"));
    entity->addEntity(new IEntity(NamespaceId::mockId,Id::mockId3,"test2"));
    try
    {
        QString output = serializer.serialize(entity);
        QString expected = "<?xml version=\"1.0\"?>"
                          "<n1:mockId xmlns:n1=\"mockId\" xmlns:n2=\"http://testnamespace\">"
                              "<n1:mockId2>test</n1:mockId2>"
                              "<n1:mockId3>test2</n1:mockId3>"
                           "</n1:mockId>\n";
        QVERIFY2(expected.compare(output) == 0, "FAILED: first case");

        IEntity *entity2 = new IEntity(NamespaceId::mockId, Id::mockId4);
        entity2->addAttribute(NamespaceId::mockId,AttributeId::mockId,"attributeValue");
        entity2->addAttribute(NamespaceId::mockId,AttributeId::mockId,"attributeValue2");
        entity2->addEntity(new IEntity(NamespaceId::mockId,Id::mockId,"test3"));
        entity->addEntity(entity2);
        output = serializer.serialize(entity);
        expected = "<?xml version=\"1.0\"?>"
                   "<n1:mockId xmlns:n1=\"mockId\" xmlns:n2=\"http://testnamespace\">"
                        "<n1:mockId2>test</n1:mockId2>"
                        "<n1:mockId3>test2</n1:mockId3>"
                        "<n1:mockId4 n1:mockId=\"attributeValue\" n1:mockId=\"attributeValue2\">"
                            "<n1:mockId>test3</n1:mockId>"
                        "</n1:mockId4>"
                   "</n1:mockId>\n";
        QVERIFY2(expected.compare(output) == 0, "FAILED: second case");        
        delete entity;
    }
    catch(XMLSerializerException)
    {
        QVERIFY(false);
        delete entity;
    }
}

QTEST_APPLESS_MAIN(QtgdataTest);

#include "qtgdatatest.moc"
