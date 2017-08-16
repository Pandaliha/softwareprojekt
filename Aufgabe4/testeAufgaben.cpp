
// Testrahmen fuer 1. Teilaufgabe

#include <iostream>

using namespace std;

#include "FSA.h"
#include "RE.h"

#include "Transform.h"
#include "TestOrakel.h"

#include <string>



//--------------------------- TEIL 1 ---------------------------
// Systematischer Test

// Ein Testfall besteht aus einem regulaeren Ausdruck (RE)
// und einem Eingabestring.
// 
// Testorakel match ueberprueft ob string s enthalten in regex r.
// 
// Simplifizierer korrekt fuer Testfall, falls Testorakel gleiches
// Ergebnis liefert fuer Original regex r und simplifizierten regex r->simp()

bool testSimp(RE* r, string s)
{
    bool b = (match(r,s) == match(r->simp(),s));
    
    cout << "Test case: " << r->pretty() << "   " << s << "\n";
    cout << "Test result: " << b << endl;

    return b;
}

//--------------------------- TEIL 2 UND 3 ---------------------------
// Systematischer Test

// Ein Testfall besteht aus einem regulaeren Ausdruck (RE)
// und einem Eingabestring.
//
// Testorakel match ueberprueft ob string s enthalten in regex r.
//
// closure und Tranformater RE -> NFA korrekt, falls Testorakel gleiches
// Ergebnis liefert wie Ausfuehrung des resultierenden NFA.

bool testClosureTransform(RE* r, string s) {
    NFA nfa = transform(r);
    FSA fsa(nfa);
    bool b1 = fsa.run(s);
    bool b2 = match(r,s);
    bool b = b1 == b2;
    
    cout << "Test case: " << r->pretty() << "   " << s << "\n";
    cout << "Test result: " << b << endl;
    
    return b;
}



int main()
{
    RE* r;
    string s;
    
    //TESTE TEIL 1
    cout << "---------- TEIL 1 ----------" << endl;
    cout << "Ein paar Testfaelle. Ueberpruefung per Auge" << endl;
    
    r = new Alt (new Phi(), new Ch('c'));
    cout << "original:    " << r->pretty() << endl;
    cout << "vereinfacht: " << r->simp()->pretty() << endl;
    cout << "-----" << endl;
    
    r = new Alt (new Ch('c'), new Phi());
    cout << "original:    " << r->pretty() << endl;
    cout << "vereinfacht: " << r->simp()->pretty() << endl;
    cout << "-----" << endl;
    
    r = new Star(new Star (new Ch('c')));
    cout << "original:    " << r->pretty() << endl;
    cout << "vereinfacht: "  << r->simp()->pretty() << endl;
    cout << "-----" << endl;
    
    r = new Star(new Phi());
    cout << "original:    " << r->pretty() << endl;
    cout << "vereinfacht: " << r->simp()->pretty() << endl;
    cout << "-----" << endl;

    r = new Alt(new Ch('c'), new Ch('c'));
    cout << "original:    " << r->pretty() << endl;
    cout << "vereinfacht: " << r->simp()->pretty() << endl;
    cout << "-----" << endl;
    
    r = new Alt(new Alt(new Ch('c'), new Ch('c')), new Phi());
    cout << "original:    " << r->pretty() << endl;
    cout << "vereinfacht: " << r->simp()->pretty() << endl;
    cout << "-----" << endl;
    
    r = new Conc(new Eps(), new Ch('c'));
    cout << "original:    " << r->pretty() << endl;
    cout << "vereinfacht: " << r->simp()->pretty() << endl;
    cout << "-----" << endl;
    
    r = new Conc(new Ch('c'), new Eps());
    cout << "original:    " << r->pretty() << endl;
    cout << "vereinfacht: " << r->simp()->pretty() << endl;
    cout << "-----" << endl;
    
    r = new Conc(new Phi(), new Ch('c'));
    cout << "original:    " << r->pretty() << endl;
    cout << "vereinfacht: " << r->simp()->pretty() << endl;
    cout << "-----" << endl;
    
    r = new Conc(new Ch('a'), new Star(new Alt(new Ch('c'), new Eps())));
    cout << "original:    " << r->pretty() << endl;
    cout << "vereinfacht: " << r->simp()->pretty() << endl;
    cout << "-----" << endl;
    
    
    r = new Conc(new Eps(), new Conc(new Star(new Star(new Ch('a'))), new Alt(new Phi(), new Ch('b')))); //eps ((a*)* (phi + b))
    cout << "original:    " << r->pretty() << endl;
    cout << "vereinfacht: " << r->simp()->pretty() << endl;
    cout << endl;
    
    //TESTE TEIL 2 UND 3
    cout << "---------- TEIL 2 UND 3 ----------" << endl;
    
    //(a|b)c
    r = new Conc(new Alt(new Ch('a'), new Ch('b')), new Ch('c'));
    s = "ac";
    testClosureTransform(r, s);
    s = "bc";
    testClosureTransform(r, s);
    s = "aaaa";
    testClosureTransform(r, s);
    
    cout << "......" << endl;
    
    //(ab)*
    r = new Star(new Conc(new Ch('a'), new Ch('b')));
    s = "abab";
    testClosureTransform(r,s);
    s = "ababa";
    testClosureTransform(r,s);
    s = "";
    testClosureTransform(r,s);
    
    cout << "......" << endl;
    
    //(a)**(a|b)
    r = new Conc(new Star(new Star(new Ch('a'))), new Alt(new Ch('a'), new Ch('b')));
    s = "a";
    testClosureTransform(r,s);
    s = "aaab";
    testClosureTransform(r,s);
    s = "ab";
    testClosureTransform(r,s);
    s = "b";
    testClosureTransform(r,s);
    
    cout << "......" << endl;
    
    //Phi|a
    r = new Alt(new Phi(), new Ch('a'));
    s = "a";
    testClosureTransform(r,s);
    s = "phi";
    testClosureTransform(r,s);
    
    cout << "......" << endl;
    
    //Eps(a*|b)
    r = new Conc(new Eps(), new Alt(new Star(new Ch('a')), new Ch('b')));
    s = "aaaa";
    testClosureTransform(r,s);
    s = "";
    testClosureTransform(r,s);
    s = "b";
    testClosureTransform(r,s);
    
}
