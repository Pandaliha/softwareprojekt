#include "RE.h"
#include <iostream>
#include "Oracle.h"

using namespace std;

int main() {

	
	
	
	//Testorakel
	cout << "Testorakel:" << endl;

	// ((phi+(b*eps))a)
	

	// eps r => r (Test Regel 1)
	RE* r13 = new Conc(new Eps(), new Ch('r'));

	//r1 r2 ==> phi falls L(r2)={} (Test Regel 2)
	RE* r10 = new Conc(new Ch('b'), new Phi());

	//r1 r2 ==> phi falls L(r1)={} (Test Regel 2)
	RE* r17 = new Conc(new Phi(), new Ch('b'));

	//r* ==> eps falls L(r)={} (Test Regel 3)
	RE* r14 = new Star(new Phi);

	//(r*)* ==> r* (Test Regel 4)
	RE* r5 = new Star(new Star(new Ch('c')));

	//r + r ==> r (Test Regel 5)
	RE* r11 = new Alt(new Ch('b'), new Ch('b'));

	//r1 + r2 ==> r2 falls L(r1)={} (Test Regel 6)
	RE* r3 = new Alt(new Phi(), new Ch('c'));

	//r1 + r2 ==> r1 falls L(r2)={}
	RE* r4 = new Alt(new Ch('c'), new Phi());

	//Kombination verschiedener Regeln
	RE* r12 = new Conc(new Alt(new Phi(), new Conc(new Star(new Ch('b')), new Eps())), new Ch('a'));


	



	

	TestCase tests[] = { { r13, r13->simp(), "r" },
						 { r10, r10->simp(), "abc" },
						 { r10, r10->simp(), "abc" },
						 { r14, r14->simp(), "acd" },
						 { r5, r5->simp(), "ccccccccc" },
						 { r11, r11->simp(), "r" },
						 { r3, r3->simp(), "ccc" },
						 { r4, r4->simp(), "ccc" },
						 { r12, r12->simp(), "bbbbbbba" },
						};
	runTests(9, tests);
	cout << endl;


	// phi + c
	cout << r3->pretty() << endl;
	cout << r3->simp()->pretty() << endl;

	// c**
	cout << r5->pretty() << endl;
	cout << r5->simp()->pretty() << endl;

	// phi*
	RE* r6 = new Star(new Phi());
	cout << r6->pretty() << endl;
	cout << r6->simp()->pretty() << endl;

	// (phi + c) + c**
	RE* r7 = new Alt(r3, r5);

	cout << r7->pretty() << endl;
	// exhaustively apply simplifications
	cout << simpFix(r7)->pretty() << endl;

	//eps r (Test Regel 1)
	RE* r8 = new Conc(new Eps(), new Ch('b'));
	cout << r8->pretty() << endl;
	cout << r8->simp()->pretty() << endl;

	//phi b (Test Regel 2)
	RE* r9 = new Conc(new Phi(), new Ch('b'));

	cout << r9->pretty() << endl;
	cout << r9->simp()->pretty() << endl;

	//b phi (Test Regel 2)
	cout << r10->pretty() << endl;
	cout << r10->simp()->pretty() << endl;

	//b + b (Test Regel 5)
	cout << r11->pretty() << endl;
	cout << r11->simp()->pretty() << endl;

	cout << endl;
	

}