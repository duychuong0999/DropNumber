#include<iostream>

using namespace std;

class Door
{
	class State* current;
public:
	Door();
	void setCurrent(State* state)
	{
		current = state;
	}
	void open();
	void close();
};

class State
{
public:
	virtual void open(Door* door) {
		cout << "Already open\n";
	}
	virtual void close(Door* door) {
		cout << "Already close\n";
	}
};

void Door::open() {
	current->open(this);
}
void Door::close() {
	current->close(this);
}

class Open: public State
{
public:
	Open()
	{
		cout << "Door current Opened\n";
	}
	void close(Door* door);
};

class Close : public State
{
public:
	Close()
	{
		cout << "Door current Closed\n";
	}
	void open(Door* door) {
		cout << "Opening the door\n";
		door->setCurrent(new Open());
		delete(this);
	}
};

void Open::close(Door* door) {
	cout << "Closinging the door\n";
	door->setCurrent(new Close());
	delete(this);
}

Door::Door()
{
	current = new Close();
	cout << "\n";
}

int main() {
	Door d1;
	d1.open();
	d1.close();
}