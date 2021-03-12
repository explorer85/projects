#include <QtTest>
#include "../../jsonparser.h"

class JsonParserTest : public QObject {
    Q_OBJECT
private slots:
    void testReadJson();

};

void JsonParserTest::testReadJson() {
    JsonParser jp;
    jp.formatFromString("{}");

    //QCOMPARE()

}

QTEST_MAIN(JsonParserTest)
#include "jsonparsertest.moc"
