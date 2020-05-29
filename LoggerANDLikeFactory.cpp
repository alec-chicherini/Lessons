//logger and like factory but not factory block creation
#include <iostream>
#include <string>
#include <vector>
#include <cmath>
#include <cfloat>

//logger
//////////////////////////////////
#define LOG(str)\
do{logger l(str);}while(false)
#define LOG_PRINT()\
do{logger ll; ll.print();}while(false)

using namespace std;

class logger
{
public:
	logger() {}

	logger(string str)
	{
		logger* l = logger::getInstance();
		l->log(str);
	}

private:
	static logger* instance;
	static vector<string> data;
	static int num;

public:
	void log(string str) {
		num++;
		data.push_back(to_string(num) +
			": " + str);
	}

	void print() {
		for (auto s : data)cout << s << endl;
	};

	static logger* getInstance()
	{
		if (instance == NULL)
		{
			instance = new logger();
			instance->num = 0;
			instance->data.push_back(to_string(num) +
				": start log");
		}
		return instance;
	}
};

vector<string> logger::data;
int logger::num(0);
logger* logger::instance = NULL;
//end of logger
//////////////////////////////////////
typedef struct {
	unsigned int r,
		g,
		b,
		a;
}Fcolor;

typedef struct {
	float x,
		y,
		z;
}FVector;

enum block_type { cube, sphere };

#define DEFAULT_COLOR {0, 0, 0, 0}
#define DEFAULT_POSITION { 0,0,0 }
#define DEFAULT_CUBE_EDGE 1.0
#define DEFAULT_SPHERE_RADIUS 1.0
#define DEFAULT_CUBE_SAFETY_DISTANCE 0.707 //sqrt(1/2) from center of cube

class block
{
public:
	virtual float distance(block *second) = 0;
	virtual FVector getPosition()=0;
	virtual float getSafety_distance()=0;

private:
	Fcolor clr = DEFAULT_COLOR;
	FVector position = DEFAULT_POSITION;
	unsigned int id=0;
};

struct ID
{
	static unsigned int _id;
};
unsigned int ID::_id = 0;

class cube_block :public block, public ID
{
public:
	 float distance(block* second) {

		 return(  
			 hypot(
					 (this->position.x) - ((second->getPosition()).x),
					 (this->position.y) - ((second->getPosition()).y),
					 (this->position.z) - ((second->getPosition()).z)
				  ) - this->safety_dist - second->getSafety_distance()
			 );
			 
									 }

	 FVector getPosition() { return position; }
	 float getSafety_distance() { return safety_dist; }

	cube_block():
		id((ID::_id)++),
		clr(DEFAULT_COLOR),
		position(DEFAULT_POSITION),
		edge(DEFAULT_CUBE_EDGE),
		safety_dist(sqrt(edge*edge/2)),
		type(block_type::cube)
	{
		
		LOG("block created, id: "
			+ to_string(id)
			+ " type: "
			+ to_string(type));
	};

cube_block(Fcolor c,FVector pos,float _edge):
		id((ID::_id)++),
		clr(c),
		position(pos),
		edge(_edge),
		safety_dist(sqrt(_edge*_edge/2)),
		type(block_type::cube)
	         {
		LOG("block created, id: "
			+ to_string(id)
			+ " type: "
			+ to_string(type));
           	};

private:
	int type;

private:
	Fcolor clr;
	FVector position;
	unsigned int id;
	float edge,
		   safety_dist;	
};

class sphere_block :public block, public ID
{
public:
	float distance(block* second) {return 0;}
	FVector getPosition() {return position;}
	float getSafety_distance() {return safety_dist;}

	sphere_block():
		id((ID::_id)++),
		clr(DEFAULT_COLOR),
		position(DEFAULT_POSITION),
		radius(DEFAULT_SPHERE_RADIUS),
		safety_dist(0),
		type(block_type::sphere)
	{
		
		LOG("block created, id: "
			+ to_string(id)
			+ " type: "
			+ to_string(type));
	};

	sphere_block(Fcolor c, FVector pos,float _radius) :
		id((ID::_id)++),
		clr(c),
		position(pos),
		radius(_radius),
		safety_dist(0),
		type(block_type::sphere)
	{
		LOG("block created, id: "
			+ to_string(id)
			+ " type: "
			+ to_string(type));
	};

private:
	int type;

private:
	Fcolor clr;
	FVector position;
	unsigned int id;
	float radius, safety_dist;
};

int main()
{
	LOG("first");
	LOG("second");
//cube_block c1(DEFAULT_COLOR,DEFAULT_POSITION,DEFAULT_CUBE_EDGE);
	
//sphere_block c1(DEFAULT_COLOR,DEFAULT_POSITION,DEFAULT_SPHERE_RADIUS);
		
	cube_block c2, c3, c4;
	sphere_block c5, c6, c7;

	block* b = new sphere_block;
	block* bb = new cube_block;

	LOG_PRINT();

	return 0;
};
