#include<iostream>
#include<list>

using namespace std;

struct Vector2
{
	float x;
	float y;
};

class BaseObject
{
private: 
	int id;
	string name;
	Vector2 position;
public:
	BaseObject() {
		id = 0;
		name = "";
		position.x = 0;
		position.y = 0;
	}
	BaseObject(int _id, string _name, Vector2 _position) {
		id = _id;
		name = _name;
		position = _position;
	}

	int getId() {
		return id;
	}
	string getName() {
		return name;
	}
	void move(float xDistance, float yDistance) {
		position.x += xDistance;
		position.y += yDistance;
	}
	void printPosition() {
		cout <<name<< " position: " << position.x << " " << position.y << endl;
	}
};

class StaticObject : public BaseObject 
{
public: StaticObject(int _id, string _name, Vector2 _position) :BaseObject(_id, _name, _position) {}
};

class DynamicObject : public BaseObject
{
public: DynamicObject(int _id, string _name, Vector2 _position) :BaseObject(_id, _name, _position) {}
};

class Tree : public StaticObject
{
public: Tree(int _id, string _name, Vector2 _position) :StaticObject(_id, _name, _position) {}
};

class House : public StaticObject
{
public: House(int _id, string _name, Vector2 _position) :StaticObject(_id, _name, _position) {}
};

class Motorbike : public DynamicObject
{
public: Motorbike(int _id, string _name, Vector2 _position) :DynamicObject(_id, _name, _position) {}
};

class Car : public DynamicObject
{
public: Car(int _id, string _name, Vector2 _position) :DynamicObject(_id, _name, _position) {}
};

void createListObjects()
{
	list<BaseObject*> listObj;
	Vector2 pos1,pos2,pos3,pos4;
	pos1.x = 0; pos1.y = 0;
	pos2.x = 1; pos2.y = 1;
	pos3.x = 2; pos3.y = 2;
	pos4.x = 3; pos4.y = 3;
	BaseObject obj1 = Tree(0,"Tree",pos1);
	BaseObject obj2 = House(1, "House", pos2);
	BaseObject obj3 = Motorbike(2, "Motorbike", pos3);
	BaseObject obj4 = Car(3, "Car", pos4);
	listObj.push_back(&obj1);
	listObj.push_back(&obj2);
	listObj.push_back(&obj3);
	listObj.push_back(&obj4);

	for (auto obj : listObj) {
		cout << obj->getName() << endl;
	}
	for (auto obj : listObj) {
		obj->move(2, 2);
	}
	for (auto obj : listObj) {
		obj->printPosition();
	}
	listObj.clear();
}

int main() {
	/*Vector2 pos;
	pos.x = 1;
	pos.y = 2;
	BaseObject a = BaseObject(0, "meo", pos);
	cout << a.getName() << " " << a.getId()<<endl;
	a.printPosition();
	a.move(1, 1);
	a.printPosition();*/

	createListObjects();
}