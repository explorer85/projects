#include <QCoreApplication>


#include "interface.h"




class Engine {
public:
//	template <class T>
//	void addObject(T obj) {

//		objects.push_back(obj);
//		//obj->input(5);
//		if (static_cast<IRenderable*>(obj)) {
//			irobjects.push_back(obj);
//		}
//		if (static_cast<Inputable*>(obj)) {
//			//Inputable* i = obj;
//			iiobjects.push_back(obj);
//		}
//	}



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

int main(int argc, char *argv[])
{
	QCoreApplication a(argc, argv);



	MapObject *map = new MapObject();
	Gridbject *grid = new Gridbject();

 //  Inputable* res = (Inputable*)(grid);

	Engine e;
//	e.addObject<MapObject*>(map);
//	e.addObject<Gridbject*>(grid);

	e.addObject(map);
	e.addObject(grid);


	e.update();


	return a.exec();
}
