#ifndef COMPONENTS_H
#define COMPONENTS_H

#include <QString>
#include <QMap>
#include <QDebug>
#include <QObject>

//namespace components {


class Component : public QObject {
	Q_OBJECT
 public:

	QString type_;
};
class Drawable : public Component {
	Q_OBJECT
public:
	void draw() { qDebug() << "Drawable::draw()"; }
};

class Pickable : public Component {
	Q_OBJECT
public:
	void picking() { qDebug() << "Pickable::picking()"; }
};




class Node {

public:
	template <class T>
	void addComponent(Component* comp) {
		components_.insert(T::staticMetaObject.className(), comp);
	}

	/// Return component by type. If there are several, returns the first.
	Component* GetComponent(QString type) const {
		return components_.value(type);

	}

	template <class T>
	T* GetComponent() const
	{
		qDebug() <<  T::staticMetaObject.className();
		return static_cast<T*>(GetComponent(T::staticMetaObject.className()));
	}

	QMap<QString, Component*> components_;

};

class Engine {
public:
	QMap<QString, Node*> nodes_;

};





//}

//Q_DECLARE_METATYPE(Component*)
//Q_DECLARE_METATYPE(Drawable*)


#endif // COMPONENTS_H
