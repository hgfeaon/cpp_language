/*
	Name: Class Template Practice Codes
	Copyright: No
	Author: He Goafeng
	Date: 19/04/14 23:05
	Description: 
*/

#include <iostream>
#include <cstdlib>
#include <vector>
#include <stdexcept>
#include <queue>

template<typename T>
class Stack {
	private:
		std::vector<T> elems;
	public:
		Stack(){};
		void push(T const&);
		void pop();
		T top() const;
		bool isAscendent();
		void showPushTimes() { std::cout<<push_times<<std::endl;}
	public:
		static int push_times;
};

// static member has copied to every different types of template instants
template<typename T> int Stack<T>::push_times = 0;

template<typename T>
void Stack<T>::push (T const& elem) {
	push_times++;
	elems.push_back(elem);
}

template<typename T>
T Stack<T>::top() const {
	return elems.back();
}

template<typename T>
void Stack<T>::pop() {
	if (elems.empty()) {
		throw std::out_of_range("Stack<>::top: empty stack.");
	}
	elems.pop_back();
}

// some type many not support operator <
template<typename T>
bool Stack<T>::isAscendent() {
	int i;
	for (i=0; i<elems.size() - 1; i++) {
		if (elems[i+1] < elems[i]) {
			break;
		}
	}
	return i == elems.size() - 1;
}

class DummyInteger {
	private:
		int value;
	public:
		DummyInteger(int i): value(i){}
		int asInt(){return value;}
};


template<typename T, typename P = long>
class MyPair {
	private:
		T va;
		P vb;
	public:
		MyPair(T const& a, P const& b) : va(a), vb(b){
			std::cout<<"General MyPair<T, P> Template Constructor"<<std::endl;
		}
		T first() {return va;}
		P second() {return vb;}
};

// template specialization(all the type arguments have been determined)
template<>
class MyPair<bool, bool> {
	private:
		unsigned char vab;
	public:
		MyPair(bool const& a, bool const& b) {
			std::cout<<"Specialized<bool, bool> MyPair Template Constructor"<<std::endl;
			vab = 0;
			vab |= a;
			vab |= (b<<1);
		}
		bool first() {return vab&0x1;}
		bool second() {return vab&0x2;}
};

// template partial specializations(partial type arguments have been determined)
template<typename T>
class MyPair<T, T> {
	private:
		T v[2];
	public:
		MyPair(T const& a, T const& b) {
			std::cout<<"Partial Specialized<T, T> MyPair Template Constructor"<<std::endl;
			v[0] = a, v[1] = b;
		}
		T first() { return v[0];}
		T second() { return v[1];}
};
template<typename T>
class MyPair<T, int> {
	private:
		T va;
		int vb;
	public:
		MyPair(T const& a, int const& b): va(a), vb(b){
			std::cout<<"Partial Specialized<T, int> MyPair Template Constructor"<<std::endl;
		}
		T first() {return va;}
		int second() {return vb;}
};

// default template arguments & back-forward refer
template <typename T, typename CONT = std::deque<T> >
class MyQueue {
	private:
		CONT que;
	public:
		MyQueue() {
			std::cout<<"MyQueue constructor"<<std::endl;
		}
		void push(T const& e);
		void pop();
		T front() const;
		T back() const;
};

template <typename T, typename CONT>
void MyQueue<T, CONT>::push(T const& e) {
	que.push_back(e);
}

template <typename T, typename CONT>
T MyQueue<T, CONT>::back() const {
	return que.back();
}

// some member function of template class MyQueue not implemented 
// but it's ok if we don't invoke them

int main() {
	Stack<int> stack;
	Stack<DummyInteger> dummyIntStack;
	dummyIntStack.push(1);
	// uncomment line below will cause complier error : isAscendent will use the operator < of type T(here is DummyInterger which has not one)
	// dummyIntStack.isAscendent();
	dummyIntStack.showPushTimes();
	try {
		stack.push(1);
		// static template class member variable
		stack.showPushTimes();
		stack.push(2);
		std::cout<<stack.top()<<std::endl;
		stack.pop();
		stack.pop();
	} catch (std::exception const& ex) {
		std::cerr<<"Exception:"<<ex.what()<<std::endl;
		return 0;
	}
	
	std::cout<<"========MyPair template test=========="<<std::endl;
	// will use general template<T, P>
	MyPair<int, char> apair(1, 'a');
	std::cout<<"pair(int, char): ("<<apair.first()<<","<<apair.second()<<")"<<std::endl;
	
	// will use specialized template<> class<bool, bool>
	MyPair<bool, bool> boolpair(false, true);
	std::cout<<"pair(bool, bool): ("<<boolpair.first()<<","<<boolpair.second()<<")"<<std::endl;
	
	// will use partial specialized template<T> class<T, T>
	MyPair<long, long> longpair(1L, 3L);
	std::cout<<"pair(long, long): ("<<longpair.first()<<","<<longpair.second()<<")"<<std::endl;
	
	// will use partial specialized template<T> class<T, int>
	MyPair<char, int> bpair('c', 20140419);
	std::cout<<"pair(char, int): ("<<bpair.first()<<","<<bpair.second()<<")"<<std::endl;
	
	// will use general template but with a default type arguemnt 
	MyPair<int> cpair(2, 8);
	std::cout<<"pair(int, long): ("<<cpair.first()<<","<<cpair.second()<<")"<<std::endl;
	
	// use default type argument (container type=std::deque<int>)
	MyQueue<int> aque;
	aque.push(3721);
	std::cout<<aque.back()<<std::endl;
	
	// explicitly use a container type = std::vector<int>
	MyQueue<int, std::vector<int> > bque;
	bque.push(419419);
	std::cout<<bque.back()<<std::endl;
	
	system("pause");
	return 0;
}
