#include<iostream>
#include<fstream>
using namespace std;
class a {
public:
	virtual void s() const= 0;
};
class b :virtual public a {
	virtual void s() {}
};
class c :virtual public a {
	virtual void s() {}
};
class d :public b, public c {

};
int main() {
	int a[10];
	cout << sizeof(a) / sizeof(int);
}