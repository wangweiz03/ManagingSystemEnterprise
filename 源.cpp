#include<iostream>
#include<fstream>
#include<iomanip>
using namespace std; 
char bin[1000];//供getline跳转到下一行使用
template<typename type>
void swap(type** a, type** b) {//传地址以进行值交换，用于绩效排名
	type* temp; temp = *a; *a = *b; *b = temp;}
char* clear(char* s) {//将字符数组每项置为\0，以便strcmp
	for (int i = 0; i < strlen(s); i++) s[i] = '\0';
	return s;}
int max(int* t) { int max = 0;//求数组最大值，用于创建新编号
	for (int i = 0; i <= 100; i++) {
		if (t[i] > max) max = t[i];} return max + 1;}
int pow(int u, int ex) { int temp = 1;//乘方函数，用于编号大小比较
	for (int i = 0; i < ex; i++) temp *= u;
	return temp;}
class coder; class manager;
class techmanager; class board;//提前声明以便login函数调用
class staff {//抽象类staff
protected:
	char id[7]; char name[10]; char intro[100];//工号、姓名、介绍
	int age; int wage; char sex[3]; char password[20];//年龄、工资、性别、密码
public:
	staff(char* n=(char*)".", char* i = (char*)".", char* it = (char*)"你好！", 
		int a = 45, int w=5000,char*sx=(char*)"男", char* p = (char*)"123456") :
		age(a), wage(w) {
		clear(name); clear(id); clear(intro); clear(sex);
		clear(password); strcpy_s(name, n);
		strcpy_s(id, i); strcpy_s(intro, it);
		strcpy_s(password, p); strcpy_s(sex, sx); }
	void getpassword() { cout << "【密码】" << password << endl; }//独立于print()，照顾到密码的隐私性
	virtual void print() = 0; virtual void alt() = 0; virtual void show() = 0; //定义纯虚函数以便派生类内重载
	friend int login(board*, techmanager*, coder*);//将login函数设为友元，便于其访问对象的id和password
	virtual ~staff() {}};
class coder :virtual public staff {//程序员类
protected: double score;  int workage;//绩效、入职年数
public:
	coder(char* n = (char*)".", char* i = (char*)".", char* it = (char*)"你好！",
		int a = 45, int w = 5000, char* sx = (char*)"男", char* p = (char*)"123456", int c=0, double sc=60)
		:staff(n,i,it,a,w,sx,p),workage(c),score(sc) {}
	virtual void print() {
		cout << "【姓名】" << name << endl << "【工号】" << id << endl
			<< "【年龄】" << age << endl << "【性别】" << sex << endl
			<< "【工资】" << wage << endl << "【介绍】" << intro << endl 
			<< "【入职年数】" << workage << endl <<"【绩效】"<<score<<endl; }
	virtual void alt() {
		char n[100];  int i;  system("cls"); print(); getpassword();
		cout << "请对信息进行更改（工号、工资、绩效分、入职年数无法更改），除【性别】输入0代表不更改。" << endl;
		cout << "【姓名】"<<endl; cin>>n; if((n[0]-48)||n[1]) { clear(name);  strcpy_s(name,n); }//更改姓名，判断输入是否为0，下同
		cout << "【年龄】"<<endl; cin >> i; while (cin.fail() || i<20&&i|| i>70)//更改年龄，若输入字符或不符合区间则重新输入，下同
		{	cin.clear(); cin.ignore(); cout << "请重新输入!" << endl; cin >> i; } 
		if (i) { age = i; }//判断输入是否为0，下同
		cout << "【性别】(0♂ 1♀)" << endl; cin >> i;  while (cin.fail() || i !=0 && i!=1) {
			cin.clear(); cin.ignore(); cout << "请重新输入!" << endl; cin >> i; } clear(sex);
		switch (i) {
		case 0:strcpy_s(sex, "男"); break;
		case 1: strcpy_s(sex, "女"); }
		cout << "【介绍】" << endl; clear(n);  cin >> n; if ((n[0] - 48) || n[1]) { clear(intro);  strcpy_s(intro, n); }
		cout << "【密码】" << endl; clear(n);  cin >> n; if ((n[0] - 48) || n[1]) { clear(password);  strcpy_s(password, n); }
		system("cls"); print(); getpassword();
		fstream iof("as.txt", ios::in | ios::out); char ids[10] = { '\0' };//将更改后的信息覆写入文件
		try { int err = 1; if (!iof) throw err; }//检查文件是否打开成功，下同
		catch (int) { cerr << "文件出错，请检查。" << endl; exit(0); }
		while(!iof.eof()) { iof >> ids;//匹配工号与文件中保存的工号
			if (!strcmp(ids, id)) {
				iof.seekg(-6, ios::cur); iof << *this<<" "; iof.close(); break;}//覆写，关闭文件
			else iof.getline(n, 2023); }system("pause");}
	virtual void show() {
		system("cls");
		cout << endl << endl << endl << endl << endl;
		cout.fill(' '); cout.setf(ios::right);
		cout << setw(50) << "++++++++++++++++++++++++" << endl
			<< setw(48) << "中文版企业人事系统" << endl << endl
			<< setw(50) << "++++++++++++++++++++++++" << endl << endl
			<< setw(51) << "##########################" << endl << endl
			<< setw(41) << "主选单" << endl
			<< setw(43) << "1. 个人信息" << endl
			<< setw(43) << "2. 信息修改" << endl
			<< setw(43) << "3. 重新登录" << endl
			<< setw(39) << "4. 退出" << endl
			<< setw(47) << "请选择序号（1-4）" << endl
			<< setw(51) << "##########################" << endl;
		cout << endl << endl << endl << endl << endl;
		cout << "你好，程序员"<<name<<"！请选择功能：" << endl; }
	friend void anew();
	friend board;  friend techmanager;
	friend istream& operator>>(istream&, coder&);//运算符重载，下同
	friend fstream& operator<<(fstream&, coder&);
	friend fstream& operator>>(fstream&, coder&);
	virtual ~coder() {}};
class manager :virtual public staff {
protected: int bonus; char proj;//奖金、项目等级
public:
	manager(char* n = (char*)".", char* i = (char*)".", char* it = (char*)"你好！",
		int a = 45, int w = 5000, char* sx = (char*)"男", char* p = (char*)"123456", int b=1000,char pt='A') :
		staff(n, i, it, a, w, sx, p), bonus(b), proj(pt){}
	friend void anew(); virtual void rank() = 0; virtual ~manager() {};};
class techmanager : public coder, public manager {//技术负责人类
protected: char dept[100];//主管
public:
	techmanager(char* n = (char*)".", char* i = (char*)".", char* it = (char*)"你好！",
		int a = 45, int w = 5000, char* sx = (char*)"男", char* p = (char*)"123456", int c = 0, int b = 1000, char pt = 'A', char* d = (char*)".",double sc=60)
		:staff(n, i, it, a, w, sx, p), coder(n, i, it, a, w, sx, p, c, sc), manager(n, i, it, a, w, sx, p, b, pt) { clear(dept);  strcpy_s(dept, d); }
	virtual void print() {
		cout << "【姓名】" << name << endl << "【工号】" << id << endl
			<< "【年龄】" << age << endl << "【性别】" << sex << endl
			<< "【工资】" << wage << endl << "【介绍】" << intro << endl << "【入职年数】" << workage << endl
			<< "【奖金】" << bonus << endl << "【项目等级】" << proj << endl << "【主管】" << dept << endl<<"【绩效】"<<score<<endl ; }
	virtual void alt() {
	LT: coder C; char ID[100]; char IDc[100]; 
		cout << "请输入自己或程序员【工号】：" << endl; cin >> ID;
		fstream iof("as.txt", ios::in | ios::out); system("cls"); char n[1000];  int i;
		try { int err = 1; if (!iof) throw err; }
		catch (int) { cerr << "文件出错，请检查。" << endl; exit(0); }
		if (!strcmp(ID, id)) {//判断是否是自己的工号，对自己信息进行修改
			print(); getpassword();
			cout << "请对信息进行更改（工号、工资、绩效分无法更改），除【性别】输入0代表不更改。" << endl;
			cout << "【姓名】" << endl; cin >> n; if ((n[0] - 48) || n[1]) { clear(name);  strcpy_s(name, n); }
			cout << "【年龄】" << endl; cin >> i; while (cin.fail() || i < 20&&i || i>70){
				cin.clear(); cin.ignore(); cout << "请重新输入!" << endl; cin >> i;	}
			if (i) { age = i; }
			cout << "【性别】(0♂ 1♀)" << endl; cin >> i;  while (cin.fail() || i != 0 && i != 1) {
				cin.clear(); cin.ignore(); cout << "请重新输入!" << endl; cin >> i;
			} clear(sex);
			switch (i) {
			case 0:strcpy_s(sex, "男"); break; case 1: strcpy_s(sex, "女");}
			cout << "【介绍】" << endl; clear(n);  cin >> n; if ((n[0] - 48) || n[1]) { clear(intro);  strcpy_s(intro, n); }
			cout << "【入职年数】" << endl; cin >> i; while (cin.fail() || i < 0) {
				cin.clear(); cin.ignore(); cout << "请重新输入!" << endl; cin >> i;}
			if (i) { workage = i; }
			cout << "【项目等级】" << endl; clear(n);  cin >> n; if ((n[0] - 48) || n[1]) { proj = n[0]; cin.clear(); }
			cout << "【主管】" << endl; clear(n);  cin >> n; if ((n[0] - 48) || n[1]) { clear(dept); strcpy_s(dept, n); }
			cout << "【密码】" << endl; clear(n);  cin >> n; if ((n[0] - 48) || n[1]) { clear(password);  strcpy_s(password, n); }
			system("cls"); print(); getpassword();
			while (!iof.eof()) {
				iof >> ID; 
				if (!strcmp(ID, id)) {
					iof.seekg(-6, ios::cur); iof << *this <<" "; iof.close(); break; }
				else iof.getline(bin, 1000);}}
		else {bool flag = 0;//若不是自己的工号，则考虑是不是程序员工号
			while (!iof.eof()) {
				iof >> IDc;
				if (!strcmp(IDc, ID)&&ID[0]=='C') {
					iof.seekg(-6, ios::cur); 
					iof >> C; iof.close(); flag = 1;  break;}
				else iof.getline(bin, 1000); }
			if (flag) {//若有程序员工号成功匹配，则修改程序员信息
				system("cls"); C.print();
				cout << "请对信息进行更改（工号、工资、密码无法更改），输入0代表不更改。" << endl;
				cout << "【姓名】" << endl; cin >> n; if ((n[0] - 48) || n[1]) { clear(C.name);  strcpy_s(C.name, n); }
				cout << "【年龄】" << endl; cin >> i; while (cin.fail() || i < 0 || i>70)
				{cin.clear(); cin.ignore(); cout << "请重新输入!" << endl; cin >> i;	}
				if (i) { C.age = i; }
				cout << "【性别】(0♂ 1♀)" << endl; cin >> i;  while (cin.fail() || i != 0 && i != 1) {
					cin.clear(); cin.ignore(); cout << "请重新输入!" << endl; cin >> i; } clear(C.sex);
				switch (i) {case 0:strcpy_s(C.sex, "男"); break; case 1: strcpy_s(C.sex, "女");}
				cout << "【介绍】" << endl; clear(n);  cin >> n; if ((n[0] - 48) || n[1]) { clear(C.intro);  strcpy_s(C.intro, n); }
				cout << "【入职年数】" << endl; cin >> i; while (cin.fail() || i < 0) {
					cin.clear(); cin.ignore(); cout << "请重新输入!" << endl; cin >> i;} if (i) { C.workage = i; }
				cout << "【绩效分(1-100)】" << endl; cin >> i; while (cin.fail() || i < 0 || i>100) {
					cin.clear(); cin.ignore(); cout << "请重新输入!" << endl; cin >> i;} if (i) { C.score = i; }
					system("cls"); C.print(); iof.open("as.txt", ios::in | ios::out);
				while (!iof.eof()) {
					iof >> IDc;
					if (!strcmp(IDc, ID)) {
						iof.seekg(-6, ios::cur);
						iof << C<<" "; iof.close(); break; }
					else iof.getline(bin, 1000, '\n');}}
			else {cout << "查无此人或无权更改！" << endl; goto LT; }}
		iof.close(); }
	virtual void show() {
		system("cls");
		cout << endl << endl << endl << endl << endl;
		cout.fill(' '); cout.setf(ios::right);
		cout << setw(50) << "++++++++++++++++++++++++" << endl
			<< setw(48) << "中文版企业人事系统" << endl
			<< endl
			<< setw(50) << "++++++++++++++++++++++++" << endl
			<< endl
			<< setw(51) << "##########################" << endl
			<< endl
			<< setw(41) << "主选单" << endl
			<< setw(43) << "1.个人信息" << endl
			<< setw(43) << "2. 数据查询" << endl
			<< setw(43) << "3. 数据修改" << endl
			<< setw(43) << "4. 新增人员" << endl
			<< setw(43) << "5. 绩效排名" << endl
			<< setw(43) << "6. 重新登录" << endl
			<< setw(39) << "7. 退出" << endl
			<< setw(47) << "请选择序号（1-7）" << endl
			<< setw(51) << "##########################" << endl;
		cout << endl << endl << endl << endl << endl;
		cout << "您好，技术负责人" << name << "！请选择功能：" << endl; }
	virtual void rank() {
		fstream iof("as.txt", ios::in | ios::out); int n = 0;
		try { int err = 1; if (!iof) throw err; }
		catch (int) { cerr << "文件出错，请检查。" << endl; exit(0); }
		while (!iof.eof()) {
			if (iof.peek() == 'C') n++; //这一次打开文件是为了统计程序员个数
			iof.getline(bin, 1000);}
		if (!n) { cout << "暂无程序员！" << endl; return; }
		coder* C = new coder[n]; coder** pC = new coder * [n];
		for (int i = 0; i < n; i++) pC[i] = C + i;
		n = 0; iof.close(); iof.open("as.txt", ios::in | ios::out);//这一次打开文件是为了把程序员数据读到程序员数组里
		while (!iof.eof()) {
			if (iof.peek() == 'C') iof >> C[n++]; 
			iof.getline(bin, 1000);} iof.close();
		for (int i = 0; i < n-1 ; i++) {
			for (int j = 0; j < n - 1 - i; j++) {
				if (pC[j]->score < pC[j + 1]->score) {
					swap(pC+j, pC+j+1);}}}//冒泡排序
		cout << "=======程序员绩效排名=======" << endl;
		for (int i = 0; i < n; i++) cout << i+1 <<" 【工号】"<<pC[i]->id <<" 【姓名】" <<pC[i]->name <<" 【绩效】"<<pC[i]->score<< endl;
		delete[] C, pC;}
	friend board; virtual ~techmanager() {}
	friend istream & operator>>(istream&, techmanager&);
	friend fstream& operator<<(fstream&, techmanager&);
	friend fstream& operator>>(fstream&, techmanager&);
};
class board : public manager {//B
public:
	board(char* n = (char*)".", char* i = (char*)".", char* it = (char*)"你好！",
		int a = 45, int w = 5000, char* sx = (char*)"男", char* p = (char*)"123456", int b = 1000, char pt = 'A') :
		staff(n, i, it, a, w, sx, p), manager(n, i, it, a, w, sx, p, b, pt) {}
	virtual void print() {
		cout << "【姓名】" << name << endl << "【工号】" << id << endl
			<< "【年龄】" << age << endl << "【性别】" << sex << endl
			<< "【介绍】" << intro << endl << "【工资】" << wage << endl << "【奖金】" << bonus << endl << "【项目等级】" << proj << endl;}
	virtual void alt() {
		LB:coder C; techmanager T;  char ID[10]; char IDc[10];
		cout << "请输入自己/管理员/程序员【工号】：" << endl; cin >> ID;
		fstream iof("as.txt", ios::in | ios::out); 
		try { int err = 1; if (!iof) throw err; }
		catch (int) { cerr << "文件出错，请检查。" << endl; exit(0); }
		system("cls"); char n[100];  int i;
		if (!strcmp(ID, id)) {//是自己
			print(); getpassword();
			cout << "请对信息进行更改（工号无法更改），除【性别】输入0代表不更改。" << endl;
			cout << "【姓名】" << endl; cin >> n; if ((n[0] - 48) || n[1]) { clear(name);  strcpy_s(name, n); }
			cout << "【年龄】" << endl; cin >> i; while (cin.fail() || i < 20&&i || i>70){
				cin.clear(); cin.ignore(); cout << "请重新输入!" << endl; cin >> i;	} if (i) { age = i; }
			cout << "【性别】(0♂ 1♀)" << endl; cin >> i;  while (cin.fail() || i != 0 && i != 1) {
				cin.clear(); cin.ignore(); cout << "请重新输入!" << endl; cin >> i; } clear(sex);
			switch (i) {
			case 0:strcpy_s(sex, "男"); break; case 1: strcpy_s(sex, "女");}
			cout << "【介绍】" << endl; clear(n);  cin >> n; if ((n[0] - 48) || n[1]) { clear(intro);  strcpy_s(intro, n); }
			cout << "【工资】" << endl; cin >> i; while (cin.fail() || i < 0 ||i>1e8) {//只有董事会成员有修改工资、奖金的权限，下同
				cin.clear(); cin.ignore(); cout << "请重新输入!" << endl; cin >> i;} if (i) { wage = i; }
			cout << "【奖金】" << endl; cin >> i; while (cin.fail() || i < 0||i>1e8) {
				cin.clear(); cin.ignore(); cout << "请重新输入!" << endl; cin >> i;} if (i) { bonus = i; }
			cout << "【项目等级】" << endl; clear(n);  cin >> n; if ((n[0] - 48) || n[1]) { proj = n[0]; cin.clear(); }
			cout << "【密码】" << endl; clear(n);  cin >> n; if ((n[0] - 48) || n[1]) { clear(password);  strcpy_s(password, n); }
			system("cls"); print(); getpassword();
			while (!iof.eof()) {//定位、覆写
				iof >> ID; 
				if (!strcmp(ID, id)) {
					iof.seekg(-6, ios::cur); iof << *this <<" "; iof.close(); break; }
				else iof.getline(bin, 1000);}}
		else {bool flag = 0;
			if (ID[0] == 'C') {//可能是程序员类
				while (!iof.eof()) {
				iof >> IDc;
				if (!strcmp(IDc, ID)) {
					iof.seekg(-6, ios::cur); 
					iof >> C; iof.close(); flag = 1;  break;}
				else iof.getline(bin, 1000); }
			if (flag) {
				system("cls"); C.print();
				cout << "请对信息进行更改（工号、密码无法更改），除【性别】输入0代表不更改。" << endl;
				cout << "【姓名】" << endl; cin >> n; if ((n[0] - 48) || n[1]) { clear(C.name);  strcpy_s(C.name, n); }
				cout << "【年龄】" << endl; cin >> i; while (cin.fail() || i < 0 || i>70)
				{cin.clear(); cin.ignore(); cout << "请重新输入!" << endl; cin >> i;	}
				if (i) { C.age = i; }
				cout << "【性别】(0♂ 1♀)" << endl; cin >> i;  while (cin.fail() || i != 0 && i != 1) {
					cin.clear(); cin.ignore(); cout << "请重新输入!" << endl; cin >> i; } clear(C.sex);
				switch (i) {case 0:strcpy_s(C.sex, "男"); break; case 1: strcpy_s(C.sex, "女");}
				cout << "【介绍】" << endl; clear(n);  cin >> n; if ((n[0] - 48) || n[1]) { clear(C.intro);  strcpy_s(C.intro, n); }
				cout << "【入职年数】" << endl; cin >> i; while (cin.fail() || i < 0) {
					cin.clear(); cin.ignore(); cout << "请重新输入!" << endl; cin >> i;} if (i) { C.workage = i; }
					cout << "【工资】" << endl; cin >> i; while (cin.fail() || i < 0 ||i>1e6) {
						cin.clear(); cin.ignore(); cout << "请重新输入!" << endl; cin >> i;} if (i) { C.wage = i; }
				cout << "【绩效分(1-100)】" << endl; cin >> i; while (cin.fail() || i < 0 || i>100) {
					cin.clear(); cin.ignore(); cout << "请重新输入!" << endl; cin >> i;} if (i) { C.score = i; }
					system("cls"); C.print(); iof.open("as.txt", ios::in | ios::out);
				while (!iof.eof()) {//定位、覆写
					iof >> IDc;
					if (!strcmp(IDc, ID)) {
						iof.seekg(-6, ios::cur);
						iof << C<<" "; iof.close(); break; }
					else iof.getline(bin, 1000, '\n');}}
			}
			else if (ID[0] == 'T') {//可能是负责人类
				while (!iof.eof()) {
				iof >> IDc;
				if (!strcmp(IDc, ID)) {
					iof.seekg(-6, ios::cur); 
					iof >> T; iof.close(); flag = 1;  break;}
				else iof.getline(bin, 1000); }
			if (flag) {
				system("cls"); T.print();
				cout << "请对信息进行更改（工号、工资、密码无法更改），输入0代表不更改。" << endl;
				cout << "【姓名】" << endl; cin >> n; if ((n[0] - 48) || n[1]) { clear(T.name);  strcpy_s(T.name, n); }
				cout << "【年龄】" << endl; cin >> i; while (cin.fail() || i < 0 || i>70)
				{cin.clear(); cin.ignore(); cout << "请重新输入!" << endl; cin >> i;	}
				if (i) { T.age = i; }
				cout << "【性别】(0♂ 1♀)" << endl; cin >> i;  while (cin.fail() || i != 0 && i != 1) {
					cin.clear(); cin.ignore(); cout << "请重新输入!" << endl; cin >> i; } clear(T.sex);
				switch (i) {case 0:strcpy_s(T.sex, "男"); break; case 1: strcpy_s(T.sex, "女");}
				cout << "【介绍】" << endl; clear(n);  cin >> n; if ((n[0] - 48) || n[1]) { clear(T.intro);  strcpy_s(T.intro, n); }
				cout << "【入职年数】" << endl; cin >> i; while (cin.fail() || i < 0) {
					cin.clear(); cin.ignore(); cout << "请重新输入!" << endl; cin >> i;} if (i) { T.workage = i; }
				cout << "【工资】" << endl; cin >> i; while (cin.fail() || i < 0 ||i>1e7) {
					cin.clear(); cin.ignore(); cout << "请重新输入!" << endl; cin >> i;} if (i) { T.wage = i; }
				cout << "【奖金】" << endl; cin >> i; while (cin.fail() || i < 0 || i>1e7) {
					cin.clear(); cin.ignore(); cout << "请重新输入!" << endl; cin >> i;} if (i) { T.bonus = i; }
				cout << "【绩效分(1-100)】" << endl; cin >> i; while (cin.fail() || i < 0 || i>100) {
					cin.clear(); cin.ignore(); cout << "请重新输入!" << endl; cin >> i;} if (i) { T.score = i; }
					system("cls"); T.print(); iof.open("as.txt", ios::in | ios::out);
				while (!iof.eof()) {//定位、覆写
					iof >> IDc;
					if (!strcmp(IDc, ID)) {
						iof.seekg(-6, ios::cur);
						iof << T<<" "; iof.close(); break; }
					else iof.getline(bin, 1000, '\n');}}}
			else {cout << "查无此人或无权更改！" << endl;goto LB;}}
		iof.close();}
	virtual void show() {
		system("cls");
		cout << endl << endl << endl << endl << endl;
		cout.fill(' '); cout.setf(ios::right);
		cout << setw(50) << "++++++++++++++++++++++++" << endl
			<< setw(48) << "中文版企业人事系统" << endl << endl
			<< setw(50) << "++++++++++++++++++++++++" << endl << endl
			<< setw(51) << "##########################" << endl << endl
			<< setw(41) << "主选单" << endl
			<< setw(43) << "1.个人信息" << endl
			<< setw(43) << "2. 数据查询" << endl
			<< setw(43) << "3. 数据修改" << endl
			<< setw(43) << "4. 新增人员" << endl
			<< setw(43) << "5. 绩效排行" << endl
			<< setw(43) << "6. 重新登录" << endl
			<< setw(39) << "7. 退出" << endl
			<< setw(47) << "请选择序号（1-7）" << endl
			<< setw(51) << "##########################" << endl;
		cout << endl << endl << endl << endl << endl;
		cout << "您好，" << name << "董事长！请选择功能：" << endl; }
	virtual void rank() {
		fstream iof("as.txt", ios::in | ios::out); int n = 0;
		try { int err = 1; if (!iof) throw err; }
		catch (int) { cerr << "文件出错，请检查。" << endl; exit(0); }
		while (!iof.eof()) {
			if (iof.peek() == 'C') n++;
			iof.getline(bin, 1000);}
		if (!n) { cout << "暂无程序员！" << endl; iof.close(); return; }
		coder* C = new coder[n]; coder** pC = new coder * [n];
		for (int i = 0; i < n; i++) pC[i] = C + i;
		n = 0; iof.close(); iof.open("as.txt", ios::in | ios::out);
		while (!iof.eof()) {
			if (iof.peek() == 'C') iof >> C[n++];
			iof.getline(bin, 1000);} iof.close();
		for (int i = 0; i < n-1 ; i++) {
			for (int j = 0; j < n - 1 - i; j++) {
				if (pC[j]->score < pC[j + 1]->score) {
					swap(pC + j, pC + j + 1);}}}
		cout << "=======程序员绩效排名=======" << endl;
		for (int i = 0; i < n; i++) cout << i + 1 << " 【工号】" << pC[i]->id << " 【姓名】" << pC[i]->name << " 【绩效】" << pC[i]->score << endl;
		iof.close(); delete[] C, pC; iof.open("as.txt", ios::in | ios::out); n = 0;
		while (!iof.eof()) {
			if (iof.peek() == 'T') n++;
			iof.getline(bin, 1000);}
		if (!n) { cout << "暂无管理员！" << endl; iof.close(); return; }
		techmanager* T = new techmanager[n]; techmanager** pT = new techmanager * [n];
		for (int i = 0; i < n; i++) pT[i] = T + i;
		n = 0; iof.close(); iof.open("as.txt", ios::in | ios::out);
		while (!iof.eof()) {
			if (iof.peek() == 'T') iof >> T[n++];
			iof.getline(bin, 1000);} iof.close();
		for (int i = 0; i < n - 1; i++) {
			for (int j = 0; j < n - 1 - i; j++) {
				if (pT[j]->score < pT[j + 1]->score) {
					swap(pT + j, pT + j + 1);}}}
		cout << "=======管理员绩效排名=======" << endl;
		for (int i = 0; i < n; i++) cout << i + 1 << " 【工号】" << pT[i]->id << " 【姓名】" << pT[i]->name << " 【绩效】" << pT[i]->score << endl;
		delete[] T, pT;}
	friend istream& operator>>(istream&, board&);
	friend fstream& operator<<(fstream&, board&);
	friend fstream& operator>>(fstream&, board&);
	virtual ~board() {}};
istream& operator>>(istream& i, coder& c) {//工号、简介、密码、绩效、入职年数均默认
	cout << "请输入【姓名】：" << endl;  i >> c.name;
	cout << "请输入【年龄】：" << endl;  i >> c.age; while (i.fail() || c.age < 20 || c.age>70){
		cin.clear(); cin.ignore(); cout << "请重新输入!" << endl; i >> c.age;}
	cout << "请输入【性别】：" << endl;  i >> c.sex; 
	cout << "请输入【工资】：" << endl;  i >> c.wage; while (i.fail() || c.wage < 0 || c.wage>1e6) {//设置工资（奖金）上限，下同
		i.clear(); i.ignore(); cout << "请重新输入!" << endl; i >> c.age; }
	return i; }
fstream& operator<<(fstream& f, coder& c) {
	f << c.id << " " << c.name << " " << c.intro << " " << c.age << " " << c.wage << " " << c.sex << " " << c.password << " " <<c.score<<" " << c.workage;
	return f; }//设置空格以区分不同属性，下同
fstream& operator>>(fstream& f, coder& c) {
	f >> c.id; f.ignore(); f >> c.name; f.ignore();
	f >> c.intro; f.ignore(); f >> c.age; f.ignore();
	f >> c.wage; f.ignore(); f >> c.sex; f.ignore();
	f >> c.password; f.ignore(); f >> c.score; f.ignore(); //忽略空格，下同
	f >> c.workage; return f; }
istream& operator>>(istream& i, techmanager& t) {
	cout << "请输入【姓名】：" << endl;  i >> t.name; 
	cout << "请输入【年龄】：" << endl;  i >> t.age; while (i.fail() || t.age < 20 || t.age>70) {
		i.clear(); i.ignore(); cout << "请重新输入!" << endl; i >> t.age; }
	cout << "请输入【性别】：" << endl;  i >> t.sex; 
	cout << "请输入【工资】：" << endl;  i >> t.wage; while (i.fail() || t.wage < 0 || t.wage>1e7) {
		i.clear(); i.ignore(); cout << "请重新输入!" << endl; i >> t.wage; }
	cout << "请输入【奖金】：" << endl;  i >> t.bonus; while (i.fail() || t.bonus < 0 || t.bonus>1e7) {
		i.clear(); i.ignore(); cout << "请重新输入!" << endl; i >> t.bonus;}
	cout << "请输入【项目等级】：" << endl;  i >> t.proj; cout << "请输入【主管】：" << endl;  i >> t.dept; return i;}
fstream& operator<<(fstream& f, techmanager& t) {
	f << t.id << " " << t.name << " " << t.intro << " " << t.age << " " << t.wage << " " << t.sex << " " << t.password << " " <<t.score<<" " << t.bonus << " " << t.proj<<" "<<t.dept;
	return f; }
fstream& operator>>(fstream& f, techmanager& t) {
	f >> t.id; f.ignore(); f >> t.name; f.ignore();
	f >> t.intro; f.ignore(); f >> t.age; f.ignore();
	f >> t.wage; f.ignore(); f >> t.sex; f.ignore();
	f >> t.password; f.ignore(); f >> t.score; f.ignore();
	f >> t.bonus; f.ignore(); f >> t.proj; f.ignore(); f >> t.dept;  return f;}
istream& operator>>(istream& i, board& b) {
	cout << "请输入【姓名】：" << endl;  i >> b.name; 
	cout << "请输入【年龄】：" << endl;  i >> b.age; while (i.fail() || b.age < 0 || b.age>70) {
		i.clear(); i.ignore(); cout << "请重新输入!" << endl; i >> b.age; }
	cout << "请输入【性别】：" << endl;  i >> b.sex; 
	cout << "请输入【工资】：" << endl;  i >> b.wage; while (i.fail() || b.wage < 0 || b.wage>1e8) {
		i.clear(); i.ignore(); cout << "请重新输入!" << endl; i >> b.wage; }
	cout << "请输入【奖金】：" << endl;  i >> b.bonus; while (i.fail() || b.bonus < 0 || b.bonus >1e8) {
		i.clear(); i.ignore(); cout << "请重新输入!" << endl; i >> b.bonus; }
	 cout << "请输入【项目等级】：" << endl;  i >> b.proj;
	return i; }
fstream& operator<<(fstream& f, board& b) {
	f << b.id << " " << b.name << " " << b.intro << " " << b.age << " " << b.wage << " " << b.sex << " " << b.password<< " " << b.bonus<< " " << b.proj;
	return f; }
fstream& operator>>(fstream& f, board& b) {
	f >> b.id; f.ignore(); f >> b.name; f.ignore();
	f >> b.intro; f.ignore(); f >> b.age; f.ignore();
	f >> b.wage; f.ignore(); f >> b.sex; f.ignore();
	f >> b.password; f.ignore(); f >> b.bonus; f.ignore();
	f >> b.proj; return f; }
int login(board* b,techmanager* t,coder* c) {//登录函数
	fstream lfile("as.txt");
	try {int err = 1; if (!lfile) throw err;}
	catch (int) { cerr << "文件出错，请检查。" << endl; exit(0);}
	cout << endl << endl << endl << endl << endl;
	cout.fill(' '); cout.setf(ios::right);
	cout << setw(50) << "++++++++++++++++++++++++" << endl
		<< setw(48) << "中文版企业人事系统" << endl << endl
		<< setw(50) << "++++++++++++++++++++++++" << endl << endl
		<< setw(51) << "##########################" << endl << endl
		<< setw(43) << "欢迎使用！" << endl << setw(47) << "请输入工号、密码：" << endl
		<< setw(51) << "##########################" << endl;
	cout << endl << endl << endl << endl << endl;
	char identity[10] = { '\0' }; char code[10] = { '\0' };
	cin >> identity; cin >> code;
	while (!lfile.eof()) {
		switch (lfile.peek()) {//根据每行首字母判断人员类型
		case 66: lfile >> (*b); //传地址，用登录者对应信息赋值，下同
			if (!strcmp(identity,(*b).id)){//比较工号，下同
				if (!strcmp(code, (*b).password)) {//比较密码，下同
					lfile.close();return 1;}}break;
		case 84: lfile >>(*t);
			if (!strcmp(identity, (*t).id)) {
				if (!strcmp(code, (*t).password)) {
					lfile.close();return 2;}}break;
		case 67: lfile >>(*c);
			if (!strcmp(identity, (*c).id)) {
				if (!strcmp(code, (*c).password)) {
					lfile.close();return 3;}} }
		lfile.getline(bin, 1000);}//跳转到下一行
	cout << "账号或密码错误！" << endl; system("cls");
	lfile.close(); return 0;}
board B; techmanager T; coder C; int choose;
void showall() {
	fstream iof("as.txt", ios::in | ios::out); coder C; techmanager T; board B;
	while (!iof.eof()) {
		switch (iof.peek()) {
		case 67: iof >> C; C.print(); cout << "===================" << endl; break;
		case 84: iof >> T; T.print(); cout << "===================" << endl; break;
		case 66: iof >> B; B.print(); cout << "===================" << endl;} 
		iof.getline(bin, 1000);} iof.close(); }
void anew() {
	 coder C; techmanager T; board B;
	cout << "请选择要新增的人员类型：" << endl << "【1】董事会成员" << endl << "【2】技术负责人" << endl << "【3】程序员" << endl;
	cin >> choose; while (cin.fail() || (choose !=1 && choose != 2 && choose !=3))
	{cin.clear();cin.ignore();cout << "请重新输入!" << endl;cin >> choose;}
	fstream iof("as.txt", ios::in|ios::out);  try { int err = 1; if (!iof) throw err;}
	catch (int) { cerr << "文件出错，请检查。" << endl; exit(0); }
	int n[100] = { 0 };  char IDc[10] = { 'C' }; char IDt[10] = { 'T' }; char IDb[10] = { 'B' };  int mx; char t[10] = { '\0' };
	switch (choose) {
	case 3: cin >> C; for (int j = 0; !iof.eof(); j++) {
		if (iof.peek() == 67) {
			for (int k = 4; k >= 0; k--) { iof.seekg(1, ios::cur); n[j] += pow(10, k) * (iof.peek() - 48); }}
		iof.getline(bin, 1000);} iof.close(); mx = max(n); 
		for (int j = 4; j >= 0; j--) {t[ j] = mx % 10 + 48; mx/=10; } 
		strcat_s(IDc, t); strcpy_s(C.id, IDc); 
		system("cls"); C.print(); C.getpassword(); iof.open("as.txt", ios::app); iof << C
			<< "																																								"<< endl; iof.close(); break;//预留修改空间，下同
	case 2:  cin >> T; for (int j = 0; !iof.eof(); j++) {
		if (iof.peek() == 84) {
			for (int k = 4; k >= 0; k--) { iof.seekg(1, ios::cur); n[j] += pow(10, k) * (iof.peek() - 48); }}
		iof.getline(bin, 1000);} iof.close(); mx = max(n);
		for (int j = 4; j >= 0; j--) { t[j] = mx % 10 + 48; mx /= 10; }
		strcat_s(IDt, t); strcpy_s(T.id, IDt);
		system("cls"); T.print(); T.getpassword(); iof.open("as.txt", ios::app); iof << T 
			<< "																																								"<< endl; iof.close(); break;
	case 1: cin >> B; for (int j = 0; !iof.eof(); j++) {
		if (iof.peek() == 66) {
			for (int k = 4; k >= 0; k--) { iof.seekg(1, ios::cur); n[j] += pow(10, k) * (iof.peek() - 48); }}
		iof.getline(bin, 1000); } iof.close(); mx = max(n);
		for (int j = 4; j >= 0; j--) { t[j] = mx % 10 + 48; mx /= 10; }
		strcat_s(IDb, t); strcpy_s(B.id, IDb);
		system("cls"); B.print(); B.getpassword(); iof.open("as.txt", ios::app); iof << B 
			<< "																																								" << endl; iof.close(); }}
int main() {
	system("color 1F");//设置背景颜色，美观
L:switch (login(&B, &T, &C)) {
case 0: goto L;//工号或密码错误
case 1://B类
L1: B.show(); cin >> choose;
	while (cin.fail() || choose > 7 || choose < 1)
	{cin.clear();cin.ignore();cout << "请重新输入!" << endl;cin >> choose;}
	system("cls"); switch (choose) {
	case 1: B.print(); B.getpassword(); system("pause"); goto L1;
	case 2: showall(); system("pause");  goto L1;
	case 3: B.alt(); system("pause"); goto L1;
	case 4: anew(); system("pause"); goto L1;
	case 5: B.rank(); system("pause"); goto L1;
	case 6: goto L;
	case 7: cout << "欢迎您再次使用，再见！" << endl;  exit(0); }
case 2://T类
L2: T.show(); cin >> choose;
	while (cin.fail() || choose > 7 || choose < 1){
		cin.clear(); cin.ignore();
		cout << "请重新输入!" << endl; cin >> choose; }
	system("cls"); switch (choose) {
	case 1: T.print(); T.getpassword(); system("pause"); goto L2;
	case 2: showall(); system("pause");  goto L2;
	case 3: T.alt(); system("pause"); goto L2;
	case 4: anew(); system("pause"); goto L2;
	case 5: T.rank(); system("pause"); goto L2;
	case 6: goto L;
	case 7: cout << "欢迎您再次使用，再见！" << endl;  exit(0);}
case 3://C类
L3: C.show(); cin >> choose;
	while (cin.fail() || choose > 4 || choose < 1)
	{ cin.clear(); cin.ignore();
	cout << "请重新输入!" << endl; cin >> choose; }
	system("cls"); switch (choose) {
	case 1: C.print(); C.getpassword(); system("pause"); goto L3;
	case 2: C.alt(); goto L3;
	case 3: goto L;
	case 4: cout << "欢迎您再次使用，再见！" << endl;  exit(0);}}}