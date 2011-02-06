#include <QtCore/QString>
#include <QtTest/QtTest>

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
    XMLSerializer::NameSpace ns;
    XMLSerializer::XMLSchema sch;
    XMLSerializer::LNameSpaces namespaces;
    namespaces.append(ns);
    XMLSerializer serializer(&namespaces,sch);
    try
    {
        QString output = serializer.Serialize(NULL);
        QVERIFY(false);
    }
    catch(XMLSerializerException)
    {
        QVERIFY(true);
    }
}

QTEST_APPLESS_MAIN(QtgdataTest);

#include "qtgdatatest.moc"
