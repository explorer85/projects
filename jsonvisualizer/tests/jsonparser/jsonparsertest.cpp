#include <QtTest>
#include "../../jsonparser.h"

class JsonParserTest : public QObject {
  Q_OBJECT
 private slots:
  void testReadJson();
};

void JsonParserTest::testReadJson() {
  // empty
  {
    JsonParser jp;
    jp.openFile("empty.json");
    QString excpectedString = "{\n}\n";
    QString outString = jp.format();
    QCOMPARE(outString, excpectedString);

    QJsonObject jo = jp.writeObject(outString);
    QJsonDocument saveDoc(jo);
    QString resOrigString = saveDoc.toJson(QJsonDocument::Compact);
    QCOMPARE(resOrigString, jp.source());
  }

  // keyvalue
  {
    JsonParser jp;
    jp.openFile("keyvalue.json");
    QString excpectedString =
        "{\n       \"key1\": \"value1\",\n       \"key2\": \"value2\"\n}\n";
    QString outString = jp.format();
    QCOMPARE(outString, excpectedString);

    QJsonObject jo = jp.writeObject(outString);
    QJsonDocument saveDoc(jo);
    QString resOrigString = saveDoc.toJson(QJsonDocument::Compact);
    QCOMPARE(resOrigString, jp.source());
  }

  // array of key value
  {
    JsonParser jp;
    jp.openFile("arrayofvalue.json");
    QString excpectedString =
        "{\n       \"key1\": [\n              {\n                     "
        "\"obj1key1\": \"obj1value1\",\n"
        "                     \"obj1key2\": \"obj1value2\"\n              },\n "
        "             {\n"
        "                     \"obj2key1\": \"obj2value1\",\n                  "
        "   \"obj2key2\": \"obj2value2\"\n              }\n       ]\n}\n";
    QString outString = jp.format();
    QCOMPARE(outString, excpectedString);

    QJsonObject jo = jp.writeObject(outString);
    QJsonDocument saveDoc(jo);
    QString resOrigString = saveDoc.toJson(QJsonDocument::Compact);
    QCOMPARE(resOrigString, jp.source());
  }
}

QTEST_MAIN(JsonParserTest)
#include "jsonparsertest.moc"
