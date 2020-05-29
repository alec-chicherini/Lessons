#include <iostream>
#include <thread>
//#include <mutex>
#include <chrono>

using namespace std;

//some function to spent processor time. using isnstead of sleep_for to see that parallel code execute faster.
 int calc(int z)
{
 int x(0);

		 if (z == 0) return x;
		 for(int i=0;i<z;i++)
		 {x = 987654321123456789 / 1234512312678990;}
		 calc(--z);
	
return x;
}

//function without arguments and return
void f_simple()
{
	cout << "start f_simple() " << endl;
	//this_thread::sleep_for(chrono::seconds(3));
	calc(1000);
	cout << "end f_simple() " << endl;
}

//function with arguments
void f_args_set(int& a)
{
	cout << "start f_args_set() input = " << a << endl;
	//this_thread::sleep_for(chrono::seconds(3));
	calc(1000);
	a++;
	cout << "f_args_set::a = " << a << endl;
	cout << "end f_args_set() " << endl;
}

//function with arguments and return
int f_return(int b)
{
	cout << "start f_return()  input = " << b << endl;
	//this_thread::sleep_for(chrono::seconds(3));
	calc(1000);
	b++;
	cout << "f_return::b = " << b << endl;
	cout << "end f_return() " << endl;
	return b;
}

int main()
{

	cout << "threads availible = "
		<< thread::hardware_concurrency()
		<< endl;

	int a = 5,
		b = 7,
		c;


	cout << endl << "executing continuous:" << endl;

	//start of functions execution in one - main thread
	auto start = chrono::high_resolution_clock::now(); cout << "timer start: " << endl;
	
	f_simple();
	f_args_set(a);
	c = f_return(b);

	//end of functions execution
	auto end = chrono::high_resolution_clock::now();

	cout << "main thread->f_return: call = " << c << endl;

	int elapsed_time = std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count();

	cout << "continuous executing time = "
		<< elapsed_time << " ms" << endl;

	cout << endl << "using threads:" << endl;

	int d = 5,
		output;

	//start of function execution different threads
   start = chrono::high_resolution_clock::now();

	//simple using thread
	thread t1(f_simple);
   cout<<"after t1"<<endl;
	//to send value by reference must use std::ref() or thread reate own example of variable
	thread t2(f_args_set, ref(d));
 cout<<"after t2"<<endl;
	//to return value from thread shoud using lambda or pass by arguments reference
thread t3([&output](){output = f_return(9);});
cout<<"after t3"<<endl;
	//waiting threads while they are finish execution
	t1.join();
	t2.join();
	t3.join();

	//end of functions execution
	end = chrono::high_resolution_clock::now();

	elapsed_time = std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count();

	cout << "paralell executing time = "
		<< elapsed_time << " ms" << endl;

	return 1;
}
