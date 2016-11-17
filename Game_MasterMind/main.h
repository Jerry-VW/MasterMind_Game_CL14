//
//  main.h
//  Game_MasterMind
//
//  Created by WANGWENQIAN on 2016/11/14.
//  Copyright © 2016 WANGWENQIAN. All rights reserved.
//

#ifndef main_h
#define main_h

#define VERSION_H 1.0

//stdbool.h (C99;VS2015) OR:
//ENUMARATORS
typedef enum {
    false, true
}bool;
//in C only; foundamental variable in C++

//CHARACTER SET
typedef enum {
    NUMBER0_3, NUMBER0_9, ALPHABET
} mode;

//struct element
//"element" after "struct" cannot be omitted!
typedef struct element{
    char cValue;
    char cAns;
    bool bIsHit;
    bool bIsBlow;
    struct element *eNext_pt;
} element;

bool setRules(int *, int *, mode *);
bool setList(int);
bool setAnswer(int);
bool listCheck(int, short *, short *);
bool showAnswer(int);

//foolproof; compatibility
bool isNumeric(char);
bool isAlphabet(char);

#endif /* main_h */
