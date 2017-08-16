/**
 * @file   aufgabe2-pointer.c
 * @brief  Aufgabe2 - Pointermanipulationen
 */

#include <stdio.h>
#include <string.h>

/**
   @brief Aufgabe2a: Scannen durch einen String
   @param [in] char* input
   @return char*

Input ist ein String der aus alphanumerischen Zeichen besteht die
durch :: getrennt sein koennen. Als Beispiele betrachte man

<p>

<ul>
  <li> "Ha::ll::o"
  <li> "47::11"
</ul>

Ihre Aufgabe ist es eine Funktion zu schreiben die den
laengsten suffix (Endung) liefert der kein :: enthaelt.
Laengste Endungen fuer unsere Beispiele:
<ul>
  <li> "o"
  <li> "11"
</ul>

<p>

Input ist der String (char pointer), das Ergebnis soll als
return Wert geliefert werden, welcher ein Zeiger auf den
Anfang der laengsten Endung ohne :: ist.

 */

char* extract(char* input) {

    int index = 0;
    int wortAnfang = 0;

    while(input[index] != '\0'){

        if((input[index]==':') && (input[index+1]==':')){
            wortAnfang=index+2;
        }
        index++;
    }
    return (char*)input+wortAnfang;


}

/**
   @brief Aufgabe2b: Variation von 2a
   @param [in] char* input
   @param [out] char** output

Das Ergebnis soll hier nicht als return Wert geliefert werden.
Anstatt wird ein pointer auf einen pointer verwendet.
Wieso reicht ein pointer nicht aus?
*/

void extract2(char* input, char** output) {
  // Ihre Loesung

    *output = extract(input);


}


/**
 @brief Aufgabe2c: Weitere Variation von Scannen
 @param [in] char* input
 @return int

 Input ist ein String der aus einer Liste von alphanumerischen Woertern
 die durch Leerzeichen (white-space) getrennt sind.
 Ihre Aufgabe ist es eine Funktion zu schreiben, die die Anzahl der
 Woerter zaehlt.
 <p>
 Beispiel:  "Ha ll o 5"
 <p>
 Soll liefern 4
 */

int count(char* input) {
    unsigned short int i = 0;
    unsigned short int countWords = 0;

    while(i < strlen(input)) {
        if(input[i] != ' ') {
            while(input[i] != ' ' && input[i] != '\0') {
                i++;
            }
            countWords++;
        }
        i++;
    }
    return countWords;
}


/**
 @brief Aufgabe2d: Aufsammeln von Woertern. Erweiterung von Aufgabe2c.
 @param [in] char* line: erstes Zeichen der Zeile
 @param [in] int maxwords
 @param [out] char* words[]
 @return int Anzahl aufgesammelter Woerter

 Gegeben (als Input) ist ein String der aus einer Liste von alphanumerischen
 Woertern die durch Leerzeichen (white-space) getrennt sind.
 Ihre Aufgabe ist es die Woerter in einem Array von Strings aufzusammeln.
 Das Array von Strings words wird pre-allokiert mit fester Groesse (maxwords).
 Die Anzahl der aufgesammelten Woerter wird als return Wert zurueck
 geliefert.

 */

int breakIntoWords(char *line, int maxwords, char *words[]) {
    char *p = line;
    unsigned short int countwords = 0;
//bis zum 1. Wort bzw bis zum Ende
    while(*line != '/0' && countwords < maxwords) {
        while (*p == ' ' && *p != '\0') {
            p++;
        }
        if (*p == '\0') {
            return countwords;
        }
//Wort hat angefangen
        char *q = p;
        while(*q != ' ' && *q != '\0') {
            q++;
        }
        //q ist jetzt kein Wort mehr. q wird beendet und das Wort gezählt und im Array gespeichert.
        if(*q == '\0') {
            return countwords;
        }
        else {
            *q = '\0';
            p = q;
            p++;
        }
        words[countwords] = p;
        countwords++;
    }
    return countwords;
}


int main() {
  // Ihre Testroutinen

    char *test = "Hal::l::ooo";
    char *test1 = "";
    char *test2 = "Hal:::oo:o";
    char *test3 = "::ooo";
    char *test4 = "Hal::l::";
    char *test5 = "Hallo guten tag";
    char *test6 = "     Ein . Baum";
    char *test7 = "";
    char *test8 = "::";
    char *test9 = "Und  Tabs ?";
    char *output;
    char line[] = " hallo    guten Tag BAUM ";
    int i;
    int nwords;
    char* words[10];

    // Aufgabe 2a)

    printf("Aufgabe 2a : \n");
    printf("extract: %s \n\n", extract(test) );
    printf("extract: %s \n\n", extract(test1) );
    printf("extract: %s \n\n", extract(test2) );
    printf("extract: %s \n\n", extract(test3) );
    printf("extract: %s \n\n", extract(test4) );

    // Aufgabe 2b)

    printf("Aufgabe 2b : \n");
    extract2(test, &output);
    printf("extract2: %s\n\n", output);
    extract2(test1, &output);
    printf("extract2: %s\n\n", output);
    extract2(test2, &output);
    printf("extract2: %s\n\n", output);
    extract2(test3, &output);
    printf("extract2: %s\n\n", output);
    extract2(test4, &output);
    printf("extract2: %s\n\n", output);

      // Aufgabe 2c)

    printf("Aufgabe 2c : \n");
    printf("Anzahl gezaehlter Woerter: %i \n \n", count(test5));
    printf("Anzahl gezaehlter Woerter: %i \n \n", count(test6));
    printf("Anzahl gezaehlter Woerter: %i \n \n", count(test7));
    printf("Anzahl gezaehlter Woerter: %i \n \n", count(test8));
    printf("Anzahl gezaehlter Woerter: %i \n \n", count(test9));


    // Aufgabe 2d)

    printf("Aufgabe 2d :\n");
    nwords = breakIntoWords(line, 10, words);
    // for(i = 0; i < nwords; i++)
    //     printf("%s\n", words[i]);
    printf("Anzahl Woerter: %i\n", nwords);
    getchar();

}

