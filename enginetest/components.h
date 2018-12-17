#ifndef COMPONENTS_H
#define COMPONENTS_H

#include <QString>
#include <QMap>
#include <QDebug>
#include <QObject>

//namespace components {

class Node;

class Component : public QObject {
	Q_OBJECT

	friend class Node;
 public:
	Node* getNode() { return node_; }
 protected:
	/// Set scene node. Called by Node when creating the component.
	void SetNode(Node* node) { node_ =  node;  }

 private:
	QString type_;
	/// Scene node.
	Node* node_;
};


class Pickable : public Component {
	Q_OBJECT
public:
	void picking() { qDebug() << "Pickable::picking()"; }
};

class Drawable : public Component {
	Q_OBJECT
public:
	virtual void draw() { qDebug() << "Drawable::draw()"; }
};






class Node {

public:
	template <class T>
	void addComponent(Component* comp) {
		comp->SetNode(this);
		components_.insert(T::staticMetaObject.className(), comp);
	}

	/// Return component by type. If there are several, returns the first.
	Component* GetComponent(QString type) const {
		 Component* comp =  components_.value(type);
		return comp;

	}

	template <class T>
	T* GetComponent() const
	{
		qDebug() <<  T::staticMetaObject.className();
		T* comp = static_cast<T*>(GetComponent(T::staticMetaObject.className()));
		if (comp == nullptr)
			Q_ASSERT(false);

		return comp;
	}
private:


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
