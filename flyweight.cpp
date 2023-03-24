#include <iostream>
#include <vector>
#include <map>
using namespace std;

// Базовый класс для всех графических примитивов
class Primitive {
public:
    virtual void draw(int x, int y) = 0;
};

// Круг - один из видов графических примитивов
class Circle : public Primitive {
    int radius;
public:
    Circle(int radius) : radius(radius) {}
    void draw(int x, int y) override {
        cout << "Drawing a circle with radius " << radius << " at (" << x << ", " << y << ")\n";
    }
};

// Квадрат - один из видов графических примитивов
class Square : public Primitive {
    int size;
public:
    Square(int size) : size(size) {}
    void draw(int x, int y) override {
        cout << "Drawing a square with size " << size << " at (" << x << ", " << y << ")\n";
    }
};

// Точка - один из видов графических примитивов
class Point : public Primitive {
public:
    void draw(int x, int y) override {
        cout << "Drawing a point at (" << x << ", " << y << ")\n";
    }
};

// Класс Picture представляет собой композицию графических примитивов
class Picture {
    vector<pair<Primitive*, pair<int, int>>> shapes;
public:
    void addShape(Primitive* shape, int x, int y) {
        shapes.emplace_back(shape, make_pair(x, y));
    }
    void draw() {
        for (auto& shape : shapes) {
            shape.first->draw(shape.second.first, shape.second.second);
        }
    }
};

// Класс, реализующий паттерн Flyweight, который представляет собой фабрику графических примитивов.
// Он хранит уже созданные объекты и при запросе на создание нового объекта, возвращает существующий объект, если такой уже был создан.
class FlyweightFactory {
    map<string, Primitive*> cache;
public:
    Primitive* getShape(string type) {
        if (cache.count(type) == 0) {
            if (type == "circle") {
                cache[type] = new Circle(10);
            }
            else if (type == "square") {
                cache[type] = new Square(15);
            }
            else if (type == "point") {
                cache[type] = new Point();
            }
        }
        return cache[type];
    }
};

int main() {
    FlyweightFactory factory;
    Picture picture;

    picture.addShape(factory.getShape("circle"), 10, 10);
    picture.addShape(factory.getShape("square"), 20, 20);
    picture.addShape(factory.getShape("circle"), 30, 30);
    picture.addShape(factory.getShape("point"), 40, 40);
    picture.addShape(factory.getShape("circle"), 50, 50);

    picture.draw();

    return 0;
}

/*
В этом примере создаётся фабрика FlyweightFactory,
которая создает и кеширует объекты типов Primitive:
Circle, Square и Point. Затем мы создаем Picture
и добавляем на нее различные объекты с помощью метода
addShape(). Этот метод принимает тип объекта и координаты,
и запрашивает соответствующий объект из фабрики.
Если такой объект уже есть в кеше, он будет возвращен
из него, иначе будет создан новый объект
и добавлен в кеш.

В конце выводятся все объекты на экран с помощью метода
draw(). Таким образом, достигается экономия памяти,
так как каждый объект создается только один раз,
и затем используется многократно.
*/

// https://refactoring.guru/ru/design-patterns/flyweight

/*
Легковес — это структурный паттерн проектирования,
который позволяет вместить бóльшее количество объектов
в отведённую оперативную память. Легковес экономит память,
разделяя общее состояние объектов между собой, вместо
хранения одинаковых данных в каждом объекте.
*/