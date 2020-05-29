//Delegating constructor
#include <iostream>
using namespace std;

class a
{
public:
a(int x){cout<<x<<" ctor1 "<<endl;}
a(int x,int y):a(x){cout<<y<<" ctor2 "<<endl;}
a(int x,int y,int z):a(x,y){cout<<z<<" ctor3 "<<endl;}	
	};
	
int main() {
	
	cout<<"3 var constructor:"<<endl;
	a var3(55,66,77);
	
	cout<<"2 var constructor:"<<endl;
	a var2(88,99);
	
	return 0;
}
