/**
 * @file   aufgabe1-bit.c
 * @brief  Aufgabe1 - Bit Manipulationen
 */

#include <stdio.h>

/**
 1a
*/

unsigned short int switchLowHighByte(unsigned short int input) {
    return (input << 8) | ((unsigned short int) input >> 8);
}

typedef enum {
  Stop = 0,
  Start = 1,
  Finish = 5,
  Fail = 255
} Status;


typedef enum {
  One = 1,
  Fifteen = 15,
  Last = 255
} Numbers;

/**
  1b
*/

void serialize(Status s, Numbers n, short int* data) {
    *data = (short int) (((unsigned short int) n << 8) | s);
}

/**
 1c
*/

void deserialize(short int data, Status* s, Numbers* n) {
    *s = data & 0x00FF;
    *n = ((unsigned short int) data >> 8);
}


enum TestEnum {
  OK = 1,
  FAIL = 0
};

typedef enum TestEnum Test;

Test testLowHigh(short int i) {
  Test t;
  if(i == switchLowHighByte(switchLowHighByte(i)))
    t = OK;
  else
    t = FAIL;

  return t;
}

Test testSD(Status s, Numbers n) {
    Test t;
    short int data;
    Status s2;
    Numbers n2;

    // Test execution
    serialize(s, n, &data);
    deserialize(data, &s2, &n2);
    if(s2 == s && n2 == n) {
        t = OK;
    }
    else {
        t = FAIL; }
    return t;
}



int main() {
    // Ihre Testroutinen
    short int zahl = 0x2040;
    printf("Aufgabe 1 a:\n");
    while (zahl < 0x5040) {
    printf("%x \n", zahl);
    printf("%x \n\n", switchLowHighByte(zahl));
    zahl = zahl + 0x0156;
    }

    printf("Aufgabe 1 b :\n");
    printf("%u \n\n", testSD(Finish, One));
    printf("%u \n\n", testSD(Fail, Fifteen));
    printf("%u \n\n", testSD(Stop, One));
    printf("%u \n\n", testSD(Start, Last));

    return 0;
}
