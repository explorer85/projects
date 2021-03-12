#include <QtTest>
#include "../../jsonparser.h"

class JsonParserTest : public QObject {
    Q_OBJECT
private slots:
    void testReadJson();



};

void JsonParserTest::testReadJson() {
    JsonParser jp;
    //empty
    QString excpectedString = "{\n}\n";
    QString outString = jp.formatFromFile("empty.json");
    QCOMPARE(outString, excpectedString);

    //keyvalue
    excpectedString = "{\n       \"key1\": \"value1\",\n       \"key2\": \"value2\"\n}\n";
    outString = jp.formatFromFile("keyvalue.json");
    QCOMPARE(outString, excpectedString);

    //array of key value
    excpectedString = "{\n       \"key1\": [\n              {\n                     \"obj1key1\": \"obj1value1\",\n"
                      "                     \"obj1key2\": \"obj1value2\"\n              },\n              {\n"
                      "                     \"obj2key1\": \"obj2value1\",\n                     \"obj2key2\": \"obj2value2\"\n              }\n       ]\n}\n";
    outString = jp.formatFromFile("arrayofvalue.json");
    QCOMPARE(outString, excpectedString);

}

QTEST_MAIN(JsonParserTest)
#include "jsonparsertest.moc"
