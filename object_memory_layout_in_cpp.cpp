#include <iostream>
#include <string>

using namespace std;

typedef void (*Fun) (void);

class A
{
	public :
		int iA;
		char cA;
		
		A() : iA(1), cA('A') {}
		
		virtual void f() {cout << "A::f()" << endl;}
		virtual void Af() {cout << "A::Af()" << endl;}
};

class B : public A
{
	public :
		int iB;
		char cB;
		
		B() : iB(2), cB('B') {}
		
		virtual void f() {cout << "B::f()" << endl;}
		virtual void Af() {cout << "B::Af()" << endl;}
		virtual void Bf() {cout << "B::Bf()" << endl;}
};

class C : public A
{
	public :
		int iC;
		
		C() : iC(3) {}
		
		virtual void f() {cout << "C::f()" << endl;}
		virtual void Cf() {cout << "C::Cf()" << endl;}
};

class D : public B, public C
{
	public :
		int iD;
		char cD;
		
		D() : iD(4), cD('D') {}
		
		virtual void f() {cout << "D::f()" << endl;}
		virtual void Bf() {cout << "D::Bf()" << endl;}
		virtual void Cf() {cout << "D::Cf()" << endl;}
		virtual void Df() {cout << "D:Df()" << endl;}
};

int main(void)
{	
	D d;
	
	Fun pFun = NULL;
	
	int* pData = (int*) &d;
	
	/*if A size is 16, means that the virtual table is align of 8 bytes,
	 *so 16 is
	 *	8(virtual function table)
	 *	4(int)
	 *	4(char(add 3 bytes for align))
	 *
	 *if A size is 8, means that the virtual table is align of 4 bytes,
	 *so 12 is
	 *	4(virtual function table)
	 *	4(int)
	 *	4(char(add 3 bytes for align))
	 */
	cout << "A class size is " << sizeof(A) << endl;
	
	/*if B size is 24, means that the virtual table is align of 8 bytes,
	 *so 24 is
	 *	8(virtual function table)
	 *	4(int)
	 *	4(char(add 3 bytes for align))
	 *	4(int)
	 *	4(char(add 3 bytes for align))
	 *
	 *if B size is 20, means that the virtual table is align of 4 bytes,
	 *so 20 is
	 *	4(virtual function table)
	 *	4(int)
	 *	4(char(add 3 bytes for align))
	 *	4(int)
	 *	4(char(add 3 bytes for align))
	 */
	cout << "B class size is " << sizeof(B) << endl;
	
	/*if C size is 24, means that the virtual table is align of 8 bytes,
	 *so 24 is
	 *	8(virtual function table)
	 *	4(int)
	 *	4(char(add 3 bytes for align))
	 *	4(int)
	 *	4(add 4 bytes for align)
	 *
	 *if C size is 16, means that the virtual table is align of 4 bytes,
	 *so 16 is
	 *	4(virtual function table);
	 *	4(int)
	 *	4(char(add 3 bytes for align))
	 *	4(int)
	 */
	cout << "C class size is " << sizeof(C) << endl;
	
	/*if D size is 56, means that the virtual table is align of 8 bytes,
	 *so 56 is
	 *	8(virtual function table)
	 *	4(int)
	 *	4(char(add 3 bytes for align))
	 *	4(int)
	 *	4(char(add 3 bytes for align))
	 *
	 *	8(virtual function table)
	 *	4(int)
	 *	4(char(add 3 bytes for align))
	 *	4(int)
	 *	4(add 4 bytes for align)
	 *
	 *	4(int)
	 *	4(char(add 3 bytes for align))
	 *
	 *if D size is 44, means that the virtual table is align of 4 bytes,
	 *so 44 is
	 *	4(virtual function table)
	 *	4(int)
	 *	4(char(add 3 bytes for align))
	 *	4(int)
	 *	4(char(add 3 bytes for align))
	 *
	 *	4(virtual function table);
	 *	4(int)
	 *	4(char(add 3 bytes for align))
	 *	4(int)
	 *
	 *	4(int)
	 *	4(char(add 3 bytes for align))
	 */
	cout << "D class size is " << sizeof(D) << endl;
	
	
	//Fun* bVtable = (Fun *)(*pData); //this will cause error in C++ , because of safty type detection
	Fun* bVtable = reinterpret_cast<Fun *>(*pData); //get the B virtual function table addr
	
	cout << "[0]  B virtual function table" << endl;
	
	pFun = bVtable[0];
	cout << "    [0]";
	pFun();
	
	pFun = bVtable[1];
	cout << "    [1]";
	pFun();
	
	pFun = bVtable[2];
	cout << "    [2]";
	pFun();
	
	pFun = bVtable[3];
	cout << "    [3]";
	pFun();
	
	pFun = bVtable[4];
	cout << "    [4]";
	pFun();
	
	pFun = bVtable[5];
	cout << "    [5] 0x" << pFun << endl;
	
	//if the virtual table is align of 8 bytes,pData[1] is the high address of B virtual function table
	cout << "[1]  A:iA = " << pData[2] << endl;
	cout << "[2]  A:cA = " << *reinterpret_cast<char*>(&pData[3]) << endl;
	cout << "[3]  B:iB = " << pData[4] << endl;
	cout << "[4]  B:cB = " << *reinterpret_cast<char*>(&pData[5]) << endl;
	
	Fun* cVtable = reinterpret_cast<Fun *>(pData[6]); //get the C virtual function table addr
	
	cout << "[5]  C virtual function table" << endl;
	
	pFun = cVtable[0];
	cout << "    [0]";
	pFun();
	
	pFun = cVtable[1];
	cout << "    [1]";
	pFun();
	
	pFun = cVtable[2];
	cout << "    [2]";
	pFun();
	
	pFun = cVtable[3];
	cout << "    [3] 0x" << pFun << endl;
	
	//if the virtual table is align of 8 bytes,pData[7] is the high address of C virtual function table
	cout << "[6]  A:iA = " << pData[8] << endl;
	cout << "[7]  A:cA = " << *reinterpret_cast<char*>(&pData[9]) << endl;
	cout << "[8]  C:iC = " << pData[10] << endl;
	cout << "[9]  D:iD = " << pData[11] << endl;
	cout << "[10] D:cD = " << *reinterpret_cast<char*>(&pData[12]) << endl;
	
	return 0;
}