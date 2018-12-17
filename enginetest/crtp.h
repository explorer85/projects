#ifndef CRTP_H
#define CRTP_H

#include <QDebug>

namespace crtp {


class Base {
public:
	virtual ~Base() = default;

};

template <typename T>
class BaseSystem {
public:

};

template <typename T>
class Inputable {
public:
	void input(int mouse) { static_cast<T *>(this)->inputableInput(mouse);	}
};



//class MapObject : public Base, public Renderable<MapObject>, public Inputable<MapObject> {
//public:
//	void renderableRender() { qDebug() << "MapObject::render";  }
//	void inputableInput(int mouse) { qDebug() << "MapObject::input";  }
//};

class GridObject : public BaseSystem<GridObject> {
public:
	void renderableRender() { qDebug() << "GridObject::render";  }
};



class Engine {
public:
	template <typename S>
	void addObject(S* obj) {

		objects.push_back(obj);

	}

	void update() {
		for (Base* obj : objects) {



			//mapinput->input(5);
		}
//			for (IRenderable* ptr : irobjects) {
//				ptr->render();
//			}

//			for (Inputable* ptr : iiobjects) {
//				ptr->input(5);
//			}
	}

	std::vector<Base*> objects;
//	std::vector<Inputable*> iiobjects;

};

}

#endif // CRTP_H
