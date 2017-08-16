

#include "RE.h"
#include "FSA.h"

#include "TestOrakel.h"

#include <iostream>
#include <string>

using namespace std;

int main() {


	//Testorakel
	cout << "Testorakel:" << endl;

	//r1 + r2 ==> r2 falls L(r1)={} (Test Regel 6)
	RE* r3 = new Alt(new Phi(), new Ch('c'));

	//r1 + r2 ==> r1 falls L(r2)={}
	RE* r4 = new Alt(new Ch('c'), new Phi());

	//(r*)* ==> r* (Test Regel 4)
	RE* r5 = new Star(new Star(new Ch('c')));

    // phi*
	RE* r6 = new Star(new Phi());

	// (phi + c) + c**
	RE* r7 = new Alt(r3, r5);

	//eps r (Test Regel 1)
	RE* r8 = new Conc(new Eps(), new Ch('b'));

	//phi b (Test Regel 2)
	RE* r9 = new Conc(new Phi(), new Ch('b'));

	//r1 r2 ==> phi falls L(r2)={} (Test Regel 2)
	RE* r10 = new Conc(new Ch('b'), new Phi());

	//r + r ==> r (Test Regel 5)
	RE* r11 = new Alt(new Ch('b'), new Ch('b'));

	//Kombination verschiedener Regeln
	RE* r12 = new Conc(new Alt(new Phi(), new Conc(new Star(new Ch('b')), new Eps())), new Ch('a'));

	//r* ==> eps falls L(r)={} (Test Regel 3)
	RE* r13 = new Star(new Phi);

	//r1 r2 ==> phi falls L(r1)={} (Test Regel 2)
	RE* r14 = new Conc(new Phi(), new Ch('b'));



	TestCase tests[] = {
						 { r3, r3->simp(), "ccc" },
						 { r4, r4->simp(), "ccc" },
						 { r5, r5->simp(), "ccccccccc" },
						 { r6, r6->simp(), "leer" },
						 { r7, r7->simp(), "ccc" },
						 { r8, r8->simp(), "bb" },
						 { r9, r9->simp(), "b" },
                         { r10, r10->simp(), "abc" },
						 { r11, r11->simp(), "r" },
						 { r12, r12->simp(), "bbbbbbba" },
						 { r13, r13->simp(), "acd" },
						 { r14, r14->simp(), "b" }
						};
	runTests(8, tests);
	cout << endl;

    string result = " result: ";
	// phi + c
	cout << r3->pretty() << result << r3->simp()->pretty() << endl;

	//c + phi
	cout << r4->pretty() << result << r4->simp()->pretty() << endl;

	// c**
	cout << r5->pretty() << result << r5->simp()->pretty() << endl;

	// phi*
	cout << r6->pretty() << result << r6->simp()->pretty() << endl;

	// (phi + c) + c**
	cout << r7->pretty() << result << simpFix(r7)->pretty() << endl;

	//eps r (Test Regel 1)
	cout << r8->pretty() << result << r8->simp()->pretty() << endl;

    //phi b (Test Regel 2)
	cout << r9->pretty() << result << r9->simp()->pretty() << endl;

	//b phi (Test Regel 2)
	cout << r10->pretty() << result << r10->simp()->pretty() << endl;

	//b + b (Test Regel 5)
	cout << r11->pretty() << result << r11->simp()->pretty() << endl;

	//(phi |(b* + eps )+a
	cout << r12->pretty() << result << r12->simp()->pretty() << endl;

	//phi*
	cout << r13->pretty() << result << r13->simp()->pretty() << endl;

    //phi b
	cout << r14->pretty() << result << r14->simp()->pretty() << endl;

	cout << endl;



}
