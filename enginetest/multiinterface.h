#ifndef INTERFACE_H
#define INTERFACE_H

#include <QDebug>

namespace multiinterface {



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



class Engine {
public:
	void addObject(Base* obj) {

		objects.push_back(obj);
		//obj->input(5);
		if (IRenderable* ir = dynamic_cast<IRenderable*>(obj)) {
			irobjects.push_back(ir);
		}
		if (Inputable* ii = dynamic_cast<Inputable*>(obj)) {
			iiobjects.push_back(ii);
		}
	}

	void update() {
			for (IRenderable* ptr : irobjects) {
				ptr->render();
			}

			for (Inputable* ptr : iiobjects) {
				ptr->input(5);
			}
	}

	std::vector<IRenderable*> irobjects;
	std::vector<Inputable*> iiobjects;
	std::vector<Base*> objects;

};

}

#endif // INTERFACE_H
