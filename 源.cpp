#include<iostream>
#include<fstream>
#include<iomanip>
using namespace std; 
char bin[1000];//��getline��ת����һ��ʹ��
template<typename type>
void swap(type** a, type** b) {//����ַ�Խ���ֵ���������ڼ�Ч����
	type* temp; temp = *a; *a = *b; *b = temp;}
char* clear(char* s) {//���ַ�����ÿ����Ϊ\0���Ա�strcmp
	for (int i = 0; i < strlen(s); i++) s[i] = '\0';
	return s;}
int max(int* t) { int max = 0;//���������ֵ�����ڴ����±��
	for (int i = 0; i <= 100; i++) {
		if (t[i] > max) max = t[i];} return max + 1;}
int pow(int u, int ex) { int temp = 1;//�˷����������ڱ�Ŵ�С�Ƚ�
	for (int i = 0; i < ex; i++) temp *= u;
	return temp;}
class coder; class manager;
class techmanager; class board;//��ǰ�����Ա�login��������
class staff {//������staff
protected:
	char id[7]; char name[10]; char intro[100];//���š�����������
	int age; int wage; char sex[3]; char password[20];//���䡢���ʡ��Ա�����
public:
	staff(char* n=(char*)".", char* i = (char*)".", char* it = (char*)"��ã�", 
		int a = 45, int w=5000,char*sx=(char*)"��", char* p = (char*)"123456") :
		age(a), wage(w) {
		clear(name); clear(id); clear(intro); clear(sex);
		clear(password); strcpy_s(name, n);
		strcpy_s(id, i); strcpy_s(intro, it);
		strcpy_s(password, p); strcpy_s(sex, sx); }
	void getpassword() { cout << "�����롿" << password << endl; }//������print()���չ˵��������˽��
	virtual void print() = 0; virtual void alt() = 0; virtual void show() = 0; //���崿�麯���Ա�������������
	friend int login(board*, techmanager*, coder*);//��login������Ϊ��Ԫ����������ʶ����id��password
	virtual ~staff() {}};
class coder :virtual public staff {//����Ա��
protected: double score;  int workage;//��Ч����ְ����
public:
	coder(char* n = (char*)".", char* i = (char*)".", char* it = (char*)"��ã�",
		int a = 45, int w = 5000, char* sx = (char*)"��", char* p = (char*)"123456", int c=0, double sc=60)
		:staff(n,i,it,a,w,sx,p),workage(c),score(sc) {}
	virtual void print() {
		cout << "��������" << name << endl << "�����š�" << id << endl
			<< "�����䡿" << age << endl << "���Ա�" << sex << endl
			<< "�����ʡ�" << wage << endl << "�����ܡ�" << intro << endl 
			<< "����ְ������" << workage << endl <<"����Ч��"<<score<<endl; }
	virtual void alt() {
		char n[100];  int i;  system("cls"); print(); getpassword();
		cout << "�����Ϣ���и��ģ����š����ʡ���Ч�֡���ְ�����޷����ģ��������Ա�����0�������ġ�" << endl;
		cout << "��������"<<endl; cin>>n; if((n[0]-48)||n[1]) { clear(name);  strcpy_s(name,n); }//�����������ж������Ƿ�Ϊ0����ͬ
		cout << "�����䡿"<<endl; cin >> i; while (cin.fail() || i<20&&i|| i>70)//�������䣬�������ַ��򲻷����������������룬��ͬ
		{	cin.clear(); cin.ignore(); cout << "����������!" << endl; cin >> i; } 
		if (i) { age = i; }//�ж������Ƿ�Ϊ0����ͬ
		cout << "���Ա�(0�� 1��)" << endl; cin >> i;  while (cin.fail() || i !=0 && i!=1) {
			cin.clear(); cin.ignore(); cout << "����������!" << endl; cin >> i; } clear(sex);
		switch (i) {
		case 0:strcpy_s(sex, "��"); break;
		case 1: strcpy_s(sex, "Ů"); }
		cout << "�����ܡ�" << endl; clear(n);  cin >> n; if ((n[0] - 48) || n[1]) { clear(intro);  strcpy_s(intro, n); }
		cout << "�����롿" << endl; clear(n);  cin >> n; if ((n[0] - 48) || n[1]) { clear(password);  strcpy_s(password, n); }
		system("cls"); print(); getpassword();
		fstream iof("as.txt", ios::in | ios::out); char ids[10] = { '\0' };//�����ĺ����Ϣ��д���ļ�
		try { int err = 1; if (!iof) throw err; }//����ļ��Ƿ�򿪳ɹ�����ͬ
		catch (int) { cerr << "�ļ��������顣" << endl; exit(0); }
		while(!iof.eof()) { iof >> ids;//ƥ�乤�����ļ��б���Ĺ���
			if (!strcmp(ids, id)) {
				iof.seekg(-6, ios::cur); iof << *this<<" "; iof.close(); break;}//��д���ر��ļ�
			else iof.getline(n, 2023); }system("pause");}
	virtual void show() {
		system("cls");
		cout << endl << endl << endl << endl << endl;
		cout.fill(' '); cout.setf(ios::right);
		cout << setw(50) << "++++++++++++++++++++++++" << endl
			<< setw(48) << "���İ���ҵ����ϵͳ" << endl << endl
			<< setw(50) << "++++++++++++++++++++++++" << endl << endl
			<< setw(51) << "##########################" << endl << endl
			<< setw(41) << "��ѡ��" << endl
			<< setw(43) << "1. ������Ϣ" << endl
			<< setw(43) << "2. ��Ϣ�޸�" << endl
			<< setw(43) << "3. ���µ�¼" << endl
			<< setw(39) << "4. �˳�" << endl
			<< setw(47) << "��ѡ����ţ�1-4��" << endl
			<< setw(51) << "##########################" << endl;
		cout << endl << endl << endl << endl << endl;
		cout << "��ã�����Ա"<<name<<"����ѡ���ܣ�" << endl; }
	friend void anew();
	friend board;  friend techmanager;
	friend istream& operator>>(istream&, coder&);//��������أ���ͬ
	friend fstream& operator<<(fstream&, coder&);
	friend fstream& operator>>(fstream&, coder&);
	virtual ~coder() {}};
class manager :virtual public staff {
protected: int bonus; char proj;//������Ŀ�ȼ�
public:
	manager(char* n = (char*)".", char* i = (char*)".", char* it = (char*)"��ã�",
		int a = 45, int w = 5000, char* sx = (char*)"��", char* p = (char*)"123456", int b=1000,char pt='A') :
		staff(n, i, it, a, w, sx, p), bonus(b), proj(pt){}
	friend void anew(); virtual void rank() = 0; virtual ~manager() {};};
class techmanager : public coder, public manager {//������������
protected: char dept[100];//����
public:
	techmanager(char* n = (char*)".", char* i = (char*)".", char* it = (char*)"��ã�",
		int a = 45, int w = 5000, char* sx = (char*)"��", char* p = (char*)"123456", int c = 0, int b = 1000, char pt = 'A', char* d = (char*)".",double sc=60)
		:staff(n, i, it, a, w, sx, p), coder(n, i, it, a, w, sx, p, c, sc), manager(n, i, it, a, w, sx, p, b, pt) { clear(dept);  strcpy_s(dept, d); }
	virtual void print() {
		cout << "��������" << name << endl << "�����š�" << id << endl
			<< "�����䡿" << age << endl << "���Ա�" << sex << endl
			<< "�����ʡ�" << wage << endl << "�����ܡ�" << intro << endl << "����ְ������" << workage << endl
			<< "������" << bonus << endl << "����Ŀ�ȼ���" << proj << endl << "�����ܡ�" << dept << endl<<"����Ч��"<<score<<endl ; }
	virtual void alt() {
	LT: coder C; char ID[100]; char IDc[100]; 
		cout << "�������Լ������Ա�����š���" << endl; cin >> ID;
		fstream iof("as.txt", ios::in | ios::out); system("cls"); char n[1000];  int i;
		try { int err = 1; if (!iof) throw err; }
		catch (int) { cerr << "�ļ��������顣" << endl; exit(0); }
		if (!strcmp(ID, id)) {//�ж��Ƿ����Լ��Ĺ��ţ����Լ���Ϣ�����޸�
			print(); getpassword();
			cout << "�����Ϣ���и��ģ����š����ʡ���Ч���޷����ģ��������Ա�����0�������ġ�" << endl;
			cout << "��������" << endl; cin >> n; if ((n[0] - 48) || n[1]) { clear(name);  strcpy_s(name, n); }
			cout << "�����䡿" << endl; cin >> i; while (cin.fail() || i < 20&&i || i>70){
				cin.clear(); cin.ignore(); cout << "����������!" << endl; cin >> i;	}
			if (i) { age = i; }
			cout << "���Ա�(0�� 1��)" << endl; cin >> i;  while (cin.fail() || i != 0 && i != 1) {
				cin.clear(); cin.ignore(); cout << "����������!" << endl; cin >> i;
			} clear(sex);
			switch (i) {
			case 0:strcpy_s(sex, "��"); break; case 1: strcpy_s(sex, "Ů");}
			cout << "�����ܡ�" << endl; clear(n);  cin >> n; if ((n[0] - 48) || n[1]) { clear(intro);  strcpy_s(intro, n); }
			cout << "����ְ������" << endl; cin >> i; while (cin.fail() || i < 0) {
				cin.clear(); cin.ignore(); cout << "����������!" << endl; cin >> i;}
			if (i) { workage = i; }
			cout << "����Ŀ�ȼ���" << endl; clear(n);  cin >> n; if ((n[0] - 48) || n[1]) { proj = n[0]; cin.clear(); }
			cout << "�����ܡ�" << endl; clear(n);  cin >> n; if ((n[0] - 48) || n[1]) { clear(dept); strcpy_s(dept, n); }
			cout << "�����롿" << endl; clear(n);  cin >> n; if ((n[0] - 48) || n[1]) { clear(password);  strcpy_s(password, n); }
			system("cls"); print(); getpassword();
			while (!iof.eof()) {
				iof >> ID; 
				if (!strcmp(ID, id)) {
					iof.seekg(-6, ios::cur); iof << *this <<" "; iof.close(); break; }
				else iof.getline(bin, 1000);}}
		else {bool flag = 0;//�������Լ��Ĺ��ţ������ǲ��ǳ���Ա����
			while (!iof.eof()) {
				iof >> IDc;
				if (!strcmp(IDc, ID)&&ID[0]=='C') {
					iof.seekg(-6, ios::cur); 
					iof >> C; iof.close(); flag = 1;  break;}
				else iof.getline(bin, 1000); }
			if (flag) {//���г���Ա���ųɹ�ƥ�䣬���޸ĳ���Ա��Ϣ
				system("cls"); C.print();
				cout << "�����Ϣ���и��ģ����š����ʡ������޷����ģ�������0�������ġ�" << endl;
				cout << "��������" << endl; cin >> n; if ((n[0] - 48) || n[1]) { clear(C.name);  strcpy_s(C.name, n); }
				cout << "�����䡿" << endl; cin >> i; while (cin.fail() || i < 0 || i>70)
				{cin.clear(); cin.ignore(); cout << "����������!" << endl; cin >> i;	}
				if (i) { C.age = i; }
				cout << "���Ա�(0�� 1��)" << endl; cin >> i;  while (cin.fail() || i != 0 && i != 1) {
					cin.clear(); cin.ignore(); cout << "����������!" << endl; cin >> i; } clear(C.sex);
				switch (i) {case 0:strcpy_s(C.sex, "��"); break; case 1: strcpy_s(C.sex, "Ů");}
				cout << "�����ܡ�" << endl; clear(n);  cin >> n; if ((n[0] - 48) || n[1]) { clear(C.intro);  strcpy_s(C.intro, n); }
				cout << "����ְ������" << endl; cin >> i; while (cin.fail() || i < 0) {
					cin.clear(); cin.ignore(); cout << "����������!" << endl; cin >> i;} if (i) { C.workage = i; }
				cout << "����Ч��(1-100)��" << endl; cin >> i; while (cin.fail() || i < 0 || i>100) {
					cin.clear(); cin.ignore(); cout << "����������!" << endl; cin >> i;} if (i) { C.score = i; }
					system("cls"); C.print(); iof.open("as.txt", ios::in | ios::out);
				while (!iof.eof()) {
					iof >> IDc;
					if (!strcmp(IDc, ID)) {
						iof.seekg(-6, ios::cur);
						iof << C<<" "; iof.close(); break; }
					else iof.getline(bin, 1000, '\n');}}
			else {cout << "���޴��˻���Ȩ���ģ�" << endl; goto LT; }}
		iof.close(); }
	virtual void show() {
		system("cls");
		cout << endl << endl << endl << endl << endl;
		cout.fill(' '); cout.setf(ios::right);
		cout << setw(50) << "++++++++++++++++++++++++" << endl
			<< setw(48) << "���İ���ҵ����ϵͳ" << endl
			<< endl
			<< setw(50) << "++++++++++++++++++++++++" << endl
			<< endl
			<< setw(51) << "##########################" << endl
			<< endl
			<< setw(41) << "��ѡ��" << endl
			<< setw(43) << "1.������Ϣ" << endl
			<< setw(43) << "2. ���ݲ�ѯ" << endl
			<< setw(43) << "3. �����޸�" << endl
			<< setw(43) << "4. ������Ա" << endl
			<< setw(43) << "5. ��Ч����" << endl
			<< setw(43) << "6. ���µ�¼" << endl
			<< setw(39) << "7. �˳�" << endl
			<< setw(47) << "��ѡ����ţ�1-7��" << endl
			<< setw(51) << "##########################" << endl;
		cout << endl << endl << endl << endl << endl;
		cout << "���ã�����������" << name << "����ѡ���ܣ�" << endl; }
	virtual void rank() {
		fstream iof("as.txt", ios::in | ios::out); int n = 0;
		try { int err = 1; if (!iof) throw err; }
		catch (int) { cerr << "�ļ��������顣" << endl; exit(0); }
		while (!iof.eof()) {
			if (iof.peek() == 'C') n++; //��һ�δ��ļ���Ϊ��ͳ�Ƴ���Ա����
			iof.getline(bin, 1000);}
		if (!n) { cout << "���޳���Ա��" << endl; return; }
		coder* C = new coder[n]; coder** pC = new coder * [n];
		for (int i = 0; i < n; i++) pC[i] = C + i;
		n = 0; iof.close(); iof.open("as.txt", ios::in | ios::out);//��һ�δ��ļ���Ϊ�˰ѳ���Ա���ݶ�������Ա������
		while (!iof.eof()) {
			if (iof.peek() == 'C') iof >> C[n++]; 
			iof.getline(bin, 1000);} iof.close();
		for (int i = 0; i < n-1 ; i++) {
			for (int j = 0; j < n - 1 - i; j++) {
				if (pC[j]->score < pC[j + 1]->score) {
					swap(pC+j, pC+j+1);}}}//ð������
		cout << "=======����Ա��Ч����=======" << endl;
		for (int i = 0; i < n; i++) cout << i+1 <<" �����š�"<<pC[i]->id <<" ��������" <<pC[i]->name <<" ����Ч��"<<pC[i]->score<< endl;
		delete[] C, pC;}
	friend board; virtual ~techmanager() {}
	friend istream & operator>>(istream&, techmanager&);
	friend fstream& operator<<(fstream&, techmanager&);
	friend fstream& operator>>(fstream&, techmanager&);
};
class board : public manager {//B
public:
	board(char* n = (char*)".", char* i = (char*)".", char* it = (char*)"��ã�",
		int a = 45, int w = 5000, char* sx = (char*)"��", char* p = (char*)"123456", int b = 1000, char pt = 'A') :
		staff(n, i, it, a, w, sx, p), manager(n, i, it, a, w, sx, p, b, pt) {}
	virtual void print() {
		cout << "��������" << name << endl << "�����š�" << id << endl
			<< "�����䡿" << age << endl << "���Ա�" << sex << endl
			<< "�����ܡ�" << intro << endl << "�����ʡ�" << wage << endl << "������" << bonus << endl << "����Ŀ�ȼ���" << proj << endl;}
	virtual void alt() {
		LB:coder C; techmanager T;  char ID[10]; char IDc[10];
		cout << "�������Լ�/����Ա/����Ա�����š���" << endl; cin >> ID;
		fstream iof("as.txt", ios::in | ios::out); 
		try { int err = 1; if (!iof) throw err; }
		catch (int) { cerr << "�ļ��������顣" << endl; exit(0); }
		system("cls"); char n[100];  int i;
		if (!strcmp(ID, id)) {//���Լ�
			print(); getpassword();
			cout << "�����Ϣ���и��ģ������޷����ģ��������Ա�����0�������ġ�" << endl;
			cout << "��������" << endl; cin >> n; if ((n[0] - 48) || n[1]) { clear(name);  strcpy_s(name, n); }
			cout << "�����䡿" << endl; cin >> i; while (cin.fail() || i < 20&&i || i>70){
				cin.clear(); cin.ignore(); cout << "����������!" << endl; cin >> i;	} if (i) { age = i; }
			cout << "���Ա�(0�� 1��)" << endl; cin >> i;  while (cin.fail() || i != 0 && i != 1) {
				cin.clear(); cin.ignore(); cout << "����������!" << endl; cin >> i; } clear(sex);
			switch (i) {
			case 0:strcpy_s(sex, "��"); break; case 1: strcpy_s(sex, "Ů");}
			cout << "�����ܡ�" << endl; clear(n);  cin >> n; if ((n[0] - 48) || n[1]) { clear(intro);  strcpy_s(intro, n); }
			cout << "�����ʡ�" << endl; cin >> i; while (cin.fail() || i < 0 ||i>1e8) {//ֻ�ж��»��Ա���޸Ĺ��ʡ������Ȩ�ޣ���ͬ
				cin.clear(); cin.ignore(); cout << "����������!" << endl; cin >> i;} if (i) { wage = i; }
			cout << "������" << endl; cin >> i; while (cin.fail() || i < 0||i>1e8) {
				cin.clear(); cin.ignore(); cout << "����������!" << endl; cin >> i;} if (i) { bonus = i; }
			cout << "����Ŀ�ȼ���" << endl; clear(n);  cin >> n; if ((n[0] - 48) || n[1]) { proj = n[0]; cin.clear(); }
			cout << "�����롿" << endl; clear(n);  cin >> n; if ((n[0] - 48) || n[1]) { clear(password);  strcpy_s(password, n); }
			system("cls"); print(); getpassword();
			while (!iof.eof()) {//��λ����д
				iof >> ID; 
				if (!strcmp(ID, id)) {
					iof.seekg(-6, ios::cur); iof << *this <<" "; iof.close(); break; }
				else iof.getline(bin, 1000);}}
		else {bool flag = 0;
			if (ID[0] == 'C') {//�����ǳ���Ա��
				while (!iof.eof()) {
				iof >> IDc;
				if (!strcmp(IDc, ID)) {
					iof.seekg(-6, ios::cur); 
					iof >> C; iof.close(); flag = 1;  break;}
				else iof.getline(bin, 1000); }
			if (flag) {
				system("cls"); C.print();
				cout << "�����Ϣ���и��ģ����š������޷����ģ��������Ա�����0�������ġ�" << endl;
				cout << "��������" << endl; cin >> n; if ((n[0] - 48) || n[1]) { clear(C.name);  strcpy_s(C.name, n); }
				cout << "�����䡿" << endl; cin >> i; while (cin.fail() || i < 0 || i>70)
				{cin.clear(); cin.ignore(); cout << "����������!" << endl; cin >> i;	}
				if (i) { C.age = i; }
				cout << "���Ա�(0�� 1��)" << endl; cin >> i;  while (cin.fail() || i != 0 && i != 1) {
					cin.clear(); cin.ignore(); cout << "����������!" << endl; cin >> i; } clear(C.sex);
				switch (i) {case 0:strcpy_s(C.sex, "��"); break; case 1: strcpy_s(C.sex, "Ů");}
				cout << "�����ܡ�" << endl; clear(n);  cin >> n; if ((n[0] - 48) || n[1]) { clear(C.intro);  strcpy_s(C.intro, n); }
				cout << "����ְ������" << endl; cin >> i; while (cin.fail() || i < 0) {
					cin.clear(); cin.ignore(); cout << "����������!" << endl; cin >> i;} if (i) { C.workage = i; }
					cout << "�����ʡ�" << endl; cin >> i; while (cin.fail() || i < 0 ||i>1e6) {
						cin.clear(); cin.ignore(); cout << "����������!" << endl; cin >> i;} if (i) { C.wage = i; }
				cout << "����Ч��(1-100)��" << endl; cin >> i; while (cin.fail() || i < 0 || i>100) {
					cin.clear(); cin.ignore(); cout << "����������!" << endl; cin >> i;} if (i) { C.score = i; }
					system("cls"); C.print(); iof.open("as.txt", ios::in | ios::out);
				while (!iof.eof()) {//��λ����д
					iof >> IDc;
					if (!strcmp(IDc, ID)) {
						iof.seekg(-6, ios::cur);
						iof << C<<" "; iof.close(); break; }
					else iof.getline(bin, 1000, '\n');}}
			}
			else if (ID[0] == 'T') {//�����Ǹ�������
				while (!iof.eof()) {
				iof >> IDc;
				if (!strcmp(IDc, ID)) {
					iof.seekg(-6, ios::cur); 
					iof >> T; iof.close(); flag = 1;  break;}
				else iof.getline(bin, 1000); }
			if (flag) {
				system("cls"); T.print();
				cout << "�����Ϣ���и��ģ����š����ʡ������޷����ģ�������0�������ġ�" << endl;
				cout << "��������" << endl; cin >> n; if ((n[0] - 48) || n[1]) { clear(T.name);  strcpy_s(T.name, n); }
				cout << "�����䡿" << endl; cin >> i; while (cin.fail() || i < 0 || i>70)
				{cin.clear(); cin.ignore(); cout << "����������!" << endl; cin >> i;	}
				if (i) { T.age = i; }
				cout << "���Ա�(0�� 1��)" << endl; cin >> i;  while (cin.fail() || i != 0 && i != 1) {
					cin.clear(); cin.ignore(); cout << "����������!" << endl; cin >> i; } clear(T.sex);
				switch (i) {case 0:strcpy_s(T.sex, "��"); break; case 1: strcpy_s(T.sex, "Ů");}
				cout << "�����ܡ�" << endl; clear(n);  cin >> n; if ((n[0] - 48) || n[1]) { clear(T.intro);  strcpy_s(T.intro, n); }
				cout << "����ְ������" << endl; cin >> i; while (cin.fail() || i < 0) {
					cin.clear(); cin.ignore(); cout << "����������!" << endl; cin >> i;} if (i) { T.workage = i; }
				cout << "�����ʡ�" << endl; cin >> i; while (cin.fail() || i < 0 ||i>1e7) {
					cin.clear(); cin.ignore(); cout << "����������!" << endl; cin >> i;} if (i) { T.wage = i; }
				cout << "������" << endl; cin >> i; while (cin.fail() || i < 0 || i>1e7) {
					cin.clear(); cin.ignore(); cout << "����������!" << endl; cin >> i;} if (i) { T.bonus = i; }
				cout << "����Ч��(1-100)��" << endl; cin >> i; while (cin.fail() || i < 0 || i>100) {
					cin.clear(); cin.ignore(); cout << "����������!" << endl; cin >> i;} if (i) { T.score = i; }
					system("cls"); T.print(); iof.open("as.txt", ios::in | ios::out);
				while (!iof.eof()) {//��λ����д
					iof >> IDc;
					if (!strcmp(IDc, ID)) {
						iof.seekg(-6, ios::cur);
						iof << T<<" "; iof.close(); break; }
					else iof.getline(bin, 1000, '\n');}}}
			else {cout << "���޴��˻���Ȩ���ģ�" << endl;goto LB;}}
		iof.close();}
	virtual void show() {
		system("cls");
		cout << endl << endl << endl << endl << endl;
		cout.fill(' '); cout.setf(ios::right);
		cout << setw(50) << "++++++++++++++++++++++++" << endl
			<< setw(48) << "���İ���ҵ����ϵͳ" << endl << endl
			<< setw(50) << "++++++++++++++++++++++++" << endl << endl
			<< setw(51) << "##########################" << endl << endl
			<< setw(41) << "��ѡ��" << endl
			<< setw(43) << "1.������Ϣ" << endl
			<< setw(43) << "2. ���ݲ�ѯ" << endl
			<< setw(43) << "3. �����޸�" << endl
			<< setw(43) << "4. ������Ա" << endl
			<< setw(43) << "5. ��Ч����" << endl
			<< setw(43) << "6. ���µ�¼" << endl
			<< setw(39) << "7. �˳�" << endl
			<< setw(47) << "��ѡ����ţ�1-7��" << endl
			<< setw(51) << "##########################" << endl;
		cout << endl << endl << endl << endl << endl;
		cout << "���ã�" << name << "���³�����ѡ���ܣ�" << endl; }
	virtual void rank() {
		fstream iof("as.txt", ios::in | ios::out); int n = 0;
		try { int err = 1; if (!iof) throw err; }
		catch (int) { cerr << "�ļ��������顣" << endl; exit(0); }
		while (!iof.eof()) {
			if (iof.peek() == 'C') n++;
			iof.getline(bin, 1000);}
		if (!n) { cout << "���޳���Ա��" << endl; iof.close(); return; }
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
		cout << "=======����Ա��Ч����=======" << endl;
		for (int i = 0; i < n; i++) cout << i + 1 << " �����š�" << pC[i]->id << " ��������" << pC[i]->name << " ����Ч��" << pC[i]->score << endl;
		iof.close(); delete[] C, pC; iof.open("as.txt", ios::in | ios::out); n = 0;
		while (!iof.eof()) {
			if (iof.peek() == 'T') n++;
			iof.getline(bin, 1000);}
		if (!n) { cout << "���޹���Ա��" << endl; iof.close(); return; }
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
		cout << "=======����Ա��Ч����=======" << endl;
		for (int i = 0; i < n; i++) cout << i + 1 << " �����š�" << pT[i]->id << " ��������" << pT[i]->name << " ����Ч��" << pT[i]->score << endl;
		delete[] T, pT;}
	friend istream& operator>>(istream&, board&);
	friend fstream& operator<<(fstream&, board&);
	friend fstream& operator>>(fstream&, board&);
	virtual ~board() {}};
istream& operator>>(istream& i, coder& c) {//���š���顢���롢��Ч����ְ������Ĭ��
	cout << "�����롾��������" << endl;  i >> c.name;
	cout << "�����롾���䡿��" << endl;  i >> c.age; while (i.fail() || c.age < 20 || c.age>70){
		cin.clear(); cin.ignore(); cout << "����������!" << endl; i >> c.age;}
	cout << "�����롾�Ա𡿣�" << endl;  i >> c.sex; 
	cout << "�����롾���ʡ���" << endl;  i >> c.wage; while (i.fail() || c.wage < 0 || c.wage>1e6) {//���ù��ʣ��������ޣ���ͬ
		i.clear(); i.ignore(); cout << "����������!" << endl; i >> c.age; }
	return i; }
fstream& operator<<(fstream& f, coder& c) {
	f << c.id << " " << c.name << " " << c.intro << " " << c.age << " " << c.wage << " " << c.sex << " " << c.password << " " <<c.score<<" " << c.workage;
	return f; }//���ÿո������ֲ�ͬ���ԣ���ͬ
fstream& operator>>(fstream& f, coder& c) {
	f >> c.id; f.ignore(); f >> c.name; f.ignore();
	f >> c.intro; f.ignore(); f >> c.age; f.ignore();
	f >> c.wage; f.ignore(); f >> c.sex; f.ignore();
	f >> c.password; f.ignore(); f >> c.score; f.ignore(); //���Կո���ͬ
	f >> c.workage; return f; }
istream& operator>>(istream& i, techmanager& t) {
	cout << "�����롾��������" << endl;  i >> t.name; 
	cout << "�����롾���䡿��" << endl;  i >> t.age; while (i.fail() || t.age < 20 || t.age>70) {
		i.clear(); i.ignore(); cout << "����������!" << endl; i >> t.age; }
	cout << "�����롾�Ա𡿣�" << endl;  i >> t.sex; 
	cout << "�����롾���ʡ���" << endl;  i >> t.wage; while (i.fail() || t.wage < 0 || t.wage>1e7) {
		i.clear(); i.ignore(); cout << "����������!" << endl; i >> t.wage; }
	cout << "�����롾���𡿣�" << endl;  i >> t.bonus; while (i.fail() || t.bonus < 0 || t.bonus>1e7) {
		i.clear(); i.ignore(); cout << "����������!" << endl; i >> t.bonus;}
	cout << "�����롾��Ŀ�ȼ�����" << endl;  i >> t.proj; cout << "�����롾���ܡ���" << endl;  i >> t.dept; return i;}
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
	cout << "�����롾��������" << endl;  i >> b.name; 
	cout << "�����롾���䡿��" << endl;  i >> b.age; while (i.fail() || b.age < 0 || b.age>70) {
		i.clear(); i.ignore(); cout << "����������!" << endl; i >> b.age; }
	cout << "�����롾�Ա𡿣�" << endl;  i >> b.sex; 
	cout << "�����롾���ʡ���" << endl;  i >> b.wage; while (i.fail() || b.wage < 0 || b.wage>1e8) {
		i.clear(); i.ignore(); cout << "����������!" << endl; i >> b.wage; }
	cout << "�����롾���𡿣�" << endl;  i >> b.bonus; while (i.fail() || b.bonus < 0 || b.bonus >1e8) {
		i.clear(); i.ignore(); cout << "����������!" << endl; i >> b.bonus; }
	 cout << "�����롾��Ŀ�ȼ�����" << endl;  i >> b.proj;
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
int login(board* b,techmanager* t,coder* c) {//��¼����
	fstream lfile("as.txt");
	try {int err = 1; if (!lfile) throw err;}
	catch (int) { cerr << "�ļ��������顣" << endl; exit(0);}
	cout << endl << endl << endl << endl << endl;
	cout.fill(' '); cout.setf(ios::right);
	cout << setw(50) << "++++++++++++++++++++++++" << endl
		<< setw(48) << "���İ���ҵ����ϵͳ" << endl << endl
		<< setw(50) << "++++++++++++++++++++++++" << endl << endl
		<< setw(51) << "##########################" << endl << endl
		<< setw(43) << "��ӭʹ�ã�" << endl << setw(47) << "�����빤�š����룺" << endl
		<< setw(51) << "##########################" << endl;
	cout << endl << endl << endl << endl << endl;
	char identity[10] = { '\0' }; char code[10] = { '\0' };
	cin >> identity; cin >> code;
	while (!lfile.eof()) {
		switch (lfile.peek()) {//����ÿ������ĸ�ж���Ա����
		case 66: lfile >> (*b); //����ַ���õ�¼�߶�Ӧ��Ϣ��ֵ����ͬ
			if (!strcmp(identity,(*b).id)){//�ȽϹ��ţ���ͬ
				if (!strcmp(code, (*b).password)) {//�Ƚ����룬��ͬ
					lfile.close();return 1;}}break;
		case 84: lfile >>(*t);
			if (!strcmp(identity, (*t).id)) {
				if (!strcmp(code, (*t).password)) {
					lfile.close();return 2;}}break;
		case 67: lfile >>(*c);
			if (!strcmp(identity, (*c).id)) {
				if (!strcmp(code, (*c).password)) {
					lfile.close();return 3;}} }
		lfile.getline(bin, 1000);}//��ת����һ��
	cout << "�˺Ż��������" << endl; system("cls");
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
	cout << "��ѡ��Ҫ��������Ա���ͣ�" << endl << "��1�����»��Ա" << endl << "��2������������" << endl << "��3������Ա" << endl;
	cin >> choose; while (cin.fail() || (choose !=1 && choose != 2 && choose !=3))
	{cin.clear();cin.ignore();cout << "����������!" << endl;cin >> choose;}
	fstream iof("as.txt", ios::in|ios::out);  try { int err = 1; if (!iof) throw err;}
	catch (int) { cerr << "�ļ��������顣" << endl; exit(0); }
	int n[100] = { 0 };  char IDc[10] = { 'C' }; char IDt[10] = { 'T' }; char IDb[10] = { 'B' };  int mx; char t[10] = { '\0' };
	switch (choose) {
	case 3: cin >> C; for (int j = 0; !iof.eof(); j++) {
		if (iof.peek() == 67) {
			for (int k = 4; k >= 0; k--) { iof.seekg(1, ios::cur); n[j] += pow(10, k) * (iof.peek() - 48); }}
		iof.getline(bin, 1000);} iof.close(); mx = max(n); 
		for (int j = 4; j >= 0; j--) {t[ j] = mx % 10 + 48; mx/=10; } 
		strcat_s(IDc, t); strcpy_s(C.id, IDc); 
		system("cls"); C.print(); C.getpassword(); iof.open("as.txt", ios::app); iof << C
			<< "																																								"<< endl; iof.close(); break;//Ԥ���޸Ŀռ䣬��ͬ
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
	system("color 1F");//���ñ�����ɫ������
L:switch (login(&B, &T, &C)) {
case 0: goto L;//���Ż��������
case 1://B��
L1: B.show(); cin >> choose;
	while (cin.fail() || choose > 7 || choose < 1)
	{cin.clear();cin.ignore();cout << "����������!" << endl;cin >> choose;}
	system("cls"); switch (choose) {
	case 1: B.print(); B.getpassword(); system("pause"); goto L1;
	case 2: showall(); system("pause");  goto L1;
	case 3: B.alt(); system("pause"); goto L1;
	case 4: anew(); system("pause"); goto L1;
	case 5: B.rank(); system("pause"); goto L1;
	case 6: goto L;
	case 7: cout << "��ӭ���ٴ�ʹ�ã��ټ���" << endl;  exit(0); }
case 2://T��
L2: T.show(); cin >> choose;
	while (cin.fail() || choose > 7 || choose < 1){
		cin.clear(); cin.ignore();
		cout << "����������!" << endl; cin >> choose; }
	system("cls"); switch (choose) {
	case 1: T.print(); T.getpassword(); system("pause"); goto L2;
	case 2: showall(); system("pause");  goto L2;
	case 3: T.alt(); system("pause"); goto L2;
	case 4: anew(); system("pause"); goto L2;
	case 5: T.rank(); system("pause"); goto L2;
	case 6: goto L;
	case 7: cout << "��ӭ���ٴ�ʹ�ã��ټ���" << endl;  exit(0);}
case 3://C��
L3: C.show(); cin >> choose;
	while (cin.fail() || choose > 4 || choose < 1)
	{ cin.clear(); cin.ignore();
	cout << "����������!" << endl; cin >> choose; }
	system("cls"); switch (choose) {
	case 1: C.print(); C.getpassword(); system("pause"); goto L3;
	case 2: C.alt(); goto L3;
	case 3: goto L;
	case 4: cout << "��ӭ���ٴ�ʹ�ã��ټ���" << endl;  exit(0);}}}