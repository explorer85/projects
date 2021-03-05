#include <iostream>
#include <vector>
#include "geopoint.h"
#include "geotransform.h"
#include "point.h"
#include "transform.h"
using namespace std;

//Решаемая проблема:
//Класс Node это абстракция инкапсулирующая в себе обьект для отрисовки на
//экране Задача: Обеспечить классу Node возможность задания его координат в
//декартовой или географической системах координат и возможность полиморфной
//обработки этих координат
//Если пойти по простому пути то нужно создать 2 класса OrthoNode и GeoNode
//OrthoNode будет содержать Transform, GeoNodeбудет содержать GeoTransform
//Мы же хотим сделать универсальный Node которому в конструкторе будет
//передаваться тип его позиционирования. Однако в этом случае
//мы сталкиваемся с проблемой: Transform и GeoTransform используют для своей
//работы функцию accept которая принимает разные аргументы
//Нам нужно чтобы  в зависмости от подаваемого на вход типа аргумента
//вызывалась функция заполнения нужной трансформации
//например:
//vector<AbstractPoint*> points
//for (Node n : nodes)
//   n.transform()->accept(points[i]);

//Решение: Для этого воспользуемся паттерном Visitor
//где наследниками от Visitor будут классы описывающие декартову точку и
//геодезическую точку а наследниками Element будут классы описывающие
//трансформацию.
//В результате создавая Node мы можем выбрать тип трансформации GeoTransform
//или Transform.
//Создав std::vector<Node> nodes мы можем полиморфно осушествить трасформацию
// каждого Node, в зависимоти от выбранного типа трансформации, с помощью
// transform_->update();
//А вот координаты точки в класс трансформации в зависимости от ее типа мы
//передадим с помощь паттерна Visitor. При передаче любой точки  в класс
//трансформации через абстракцию AbstractPoint в методе accept  конкретная точка
//вызовом v.visit(*this) запустит через базовый класс AbstractPoint,
//с помощью механизма выбора перегрузки функции, функцию производного
//класса соответсвующую входному производному от Element


//узел с типом позиционирования на плоскости иили в геокоординатах
class Node {
 public:
  Node(bool isGeo = false) {
    if (isGeo)
      transform_ = new GeoTransform();
    else
      transform_ = new Transform();
  }
  Element *transform() { return transform_; }
  void update() { transform_->update(); }
  Element *transform_;
};

int main()
{
  Node n;
  Node ngeo(true);
  vector<Node> nodes = {n, ngeo};

  Point p(10, 10);
  //устанавливаем координаты в XY
  n.transform()->accept(p);

  AbstractPoint *pg = new GeoPoint(45.0, 37.0);
  //устанавливаем координаты в ШД
  ngeo.transform()->accept(*pg);

  for (auto &n : nodes) {
    n.update();
  }
  return 0;
}
