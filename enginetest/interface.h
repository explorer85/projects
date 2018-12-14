#ifndef INTERFACE_H
#define INTERFACE_H

#include <QDebug>

class Base /*:*/ /*public QObject*/ {
public:
	virtual ~Base() = default;
	void test() {}
};

class IRenderable : virtual public Base {
public:
	virtual void render() = 0;
};

class Inputable : virtual public Base {
	public:
	virtual void input(int mouse) = 0;
};

class MapObject : public QObject, public IRenderable, public Inputable {
	Q_OBJECT
public:
	void render() {  qDebug() << "MapObject::render"; }
	void input(int /*mouse*/) { qDebug() << "MapObject::input";  }
public slots:
	void onReceive() {}
};

class Gridbject : public QObject, public IRenderable {
	Q_OBJECT
public:
	void render() { qDebug() << "Gridbject::render";  }
};

#endif // INTERFACE_H
