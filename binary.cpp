#include <iostream>

using namespace std;

template<class T>
class node
{
public:
	//CT,DT
	node(node *X){_data=X->_data;
		         _left=X->_left;
		         _right=X->_right;}
		
	node(T data){_data=new T(data);
		         _left=nullptr;
		         _right=nullptr;}
		         
	node(){      _data=nullptr;
		         _left=nullptr;
		         _right=nullptr;}	          
		     
	~node(){delete _data;}
				    	

	T    *_data;
	node *_left,
	     *_right;
};

template <class T>
class binary_tree

{  
public:
	
binary_tree(T data)
{
_root=new node<T>(data);
}

void print()
{
	print(_root);
};

void print(node<T>* nd)
{
  cout<<*nd->_data<<endl;
  if(nd->_left!=nullptr)print(nd->_left);
  if(nd->_right!=nullptr)print(nd->_right);
  
	   };

void add(T data)
{
node<T> *current(_root);
	
while(1)
	{
		
if(data>=*(current->_data))//go right
	{
   if(current->_right==nullptr)//if node not exist
		{
			node<T> *nd = new node(data);
			current->_right=nd;
			break;
		}
	else
		{	
			current=current->_right;
		}
		}//end right
else{ //go left
	
		if(current->_left==nullptr)//if node not exist
		{
			node<T> *nd = new node(data);
			current->_left=nd;
			break;
		}
	else
		{	
			current=current->_left;
		}
		

	};//end left

};//while()
};//add

private:
	node<T> *_root;			
};

int main(){

	binary_tree a(44);
	a.add(123);
	a.add(44);
	a.add(43);
	a.add(77);
	a.add(99);
	a.add(55);
	a.print();	
	
return 0;	
	}
