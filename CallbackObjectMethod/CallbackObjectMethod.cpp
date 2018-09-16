// CallbackObjectMethod.cpp : 定義主控台應用程式的進入點。
//

#include "stdafx.h"
#include <iostream>
#include <functional>
#include <set>
#include <list>

using namespace std;
using namespace std::placeholders;
//using std::cout;
//using std::endl;

class EventHandler;
typedef std::function<void(EventHandler*)> callBackFunc;

class EventHandler
{
private:
	list<callBackFunc> callbackFuncs;
    public:
		int x;
        void addHandler(callBackFunc callback)
        {
            cout << "Handler added..." << endl;
            // Let's pretend an event just occured
			callbackFuncs.push_back(callback);
			//callbackFuncs.emplace(callback);
            //callback(7);
        }
		void doEventCallback(int z)
		{
			x = z;
			for(callBackFunc Func : callbackFuncs)
				Func(this);
		}
};

EventHandler* handler;

class MyClass
{
    public:
        MyClass();

        // Note: No longer marked `static`, and only takes the actual argument
        void Callback(EventHandler* x);
    private:
        int private_x;
};

MyClass::MyClass()
{
    //using namespace std::placeholders; // for `_1`

    private_x = 5;
    //handler->addHandler(std::bind(&MyClass::Callback, this, _1));
}

void MyClass::Callback(EventHandler* x)
{
    // No longer needs an explicit `instance` argument,
    // as `this` is set up properly
    cout << x->x + private_x << endl;
}

class YourClass
{
    public:
        YourClass();

        // Note: No longer marked `static`, and only takes the actual argument
        void Callback(EventHandler* x);
    private:
        int private_x;
};
YourClass::YourClass()
{
    //using namespace std::placeholders; // for `_1`

    private_x = 5;
    //handler->addHandler(std::bind(&MyClass::Callback, this, _1));
}

void YourClass::Callback(EventHandler* x)
{
    // No longer needs an explicit `instance` argument,
    // as `this` is set up properly
    cout << x->x - private_x << endl;
}


int _tmain(int argc, _TCHAR* argv[])
{
	handler = new EventHandler();
    MyClass* myClass = new MyClass();
	handler->addHandler(std::bind(&MyClass::Callback, myClass, _1)); 

	YourClass* yourClass = new YourClass();
	handler->addHandler(std::bind(&YourClass::Callback, yourClass, _1)); 

	handler->doEventCallback(3);

	system("pause");
	return 0;
}

