#include <iostream>
#include <cstdlib>

using namespace std;

// promotion(to int, long) > standard conversion
void f2(int a) {
	cout<<"f2 (int)"<<endl;
}

void f2(char a) {
	cout<<"f2 (char)"<<endl;
}

void f2(unsigned short a) {
	cout<<"f2 (unsigned short)"<<endl;
}

// user-defined conversion < standard conversion
class Integer {
	private:
		int value;
	public:
		Integer(int i):value(i){}
		operator int() {return value;}
};

void f3(char i) {
	cout<<"f3 (char)"<<endl;
}

void f3(Integer i) {
	cout<<"f3 (Integer)"<<endl;
}

// conversion confusion
class BadString {
	private:
		char const* data;
	public:
		BadString(char const* str):data(str){
			cout<<"badstring::constructor"<<endl;
		}
		
		char const& operator[] (size_t idx) const {
			cout<<"char const& operator[](size_t)"<<endl;
			return data[idx];
		}
		
		operator char const* () { 
			cout<<"operator char const*"<<endl;
			return data;
		}
};

// const and non-const 
void f4(int& i) {
	cout<<"f4(int&)"<<endl;
	return;
}

void f4(int const& i) {
	cout<<"f4(int const&)"<<endl;
}

template<typename T>
int f5(T) {return 1;}

void f5(int) {}

// Functors and Surrogate Functions
void f6(int a, int b) {
	cout<<"f6(int, int)"<<endl;
}
typedef void FuncType(double, int);
class IndirectFunctor {
	public:
		operator() (double a, double b) {
			cout<<"operator()"<<endl;
		}
		operator FuncType*() const {
			return f6;
		}
};

int main() {
	short x = 1;
	f2(x);
	
	f3(2);
	
	f4(1);
	f4(x);
	int ix = 1;
	f4(ix);
		
	cout<<sizeof(ptrdiff_t)<<endl;
	
	BadString str("something");
	cout<<str[3]<<endl;
	
	//int ret = f5(4);
	
	IndirectFuncotr functor;
	functor(3,5);
	system("pause");
	return 0;
}

