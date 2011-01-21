#include <QtCore/QString>
#include <QtTest/QtTest>

class QtgdataTest : public QObject
{
    Q_OBJECT

public:
    QtgdataTest();

private Q_SLOTS:
    void createEntity();
};

QtgdataTest::QtgdataTest()
{
}

void QtgdataTest::createEntity()
{
    QVERIFY2(true, "Failure");
}

QTEST_APPLESS_MAIN(QtgdataTest);

#include "qtgdatatest.moc"
