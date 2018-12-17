#include <QCoreApplication>

//#include "multiinterface.h"
//using namespace multiinterface;

//int main(int argc, char *argv[])
//{
//	QCoreApplication a(argc, argv);

//	MapObject *map = new MapObject();
//	Gridbject *grid = new Gridbject();

//	Engine e;
//	e.addObject(map);
//	e.addObject(grid);
//	e.update();


//	return a.exec();
//}



//#include "crtp.h"
//using namespace crtp;


//int main(int argc, char *argv[])
//{
//	QCoreApplication a(argc, argv);

//	//MapObject *map = new MapObject();
//	GridObject *grid = new GridObject();

//	//Inputable<MapObject> *mapinput = map;
//	//mapinput->input(6);


//	Engine e;
//	//e.addObject<MapObject>(map);
//	e.addObject(grid);
//	e.update();


//	return a.exec();
//}



#include "components.h"
//using namespace components;



int main(int argc, char *argv[])
{
	QCoreApplication a(argc, argv);
//	Drawable d;
//	qDebug() << d.metaObject()->className() << d.metaObject()->superClass()->className();
//	Component c;
//	qDebug() << c.metaObject()->className() << c.metaObject()->superClass()->className();



	Node n;
	Component *comp = new Drawable();
	n.addComponent<Drawable>(comp);
	comp = new Pickable();
	n.addComponent<Pickable>(comp);  //при создании компонента можно передавать в него контекст,
									 //из которого компонент  сможет инициализироваться общими штуками типа гиса, ввода итд


	{

	Component *cc =	n.GetComponent(Drawable::staticMetaObject.className());
	cc = new Component();
	Drawable *draw = static_cast<Drawable*>(cc);


	Drawable *drawable = n.GetComponent<Drawable>();
	drawable->draw();

	Pickable *pickable = n.GetComponent<Pickable>();
	pickable->picking();
	}


//	Engine e;
//	//e.addObject<MapObject>(map);
//	e.addObject(grid);
//	e.update();


	return a.exec();
}

