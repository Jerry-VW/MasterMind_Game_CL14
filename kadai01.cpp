//
//  main.c
//  20161107_kdadai01_training_MasterMind
//  optional マス数iKoma4　記号種類0123　繰返す回数iChance
//
//  Copyright © 2016 WANGWENQIAN. All rights reserved.
//

#include <stdio.h>
#include <stdlib.h>
//#include <stdbool.h>

#define Debug

//stdbool.h OR:
//enumerators
//typedef enum { false, true, } bool;

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
    //struct element *eNext_pt;
} element;

//struct pointer
element eList[4];

bool setRules(int *, int *, mode *);
bool setList(int);
bool setAnswer(int);
bool listCheck(int, short *, short *);
bool showAnswer(int);

//foolproof; compatibility
bool isNumeric(char);
bool isAlphabet(char);

bool setRules(int *iKoma_pt, int *iChance_pt, mode *pMode){
    int iChoose;
    //user setting
    *iKoma_pt = 4;
    
    printf("Set chance[FREE]: ");
    scanf("%d", iChance_pt);
    
    iChoose = 0;
    switch (iChoose) {
        case 0:
            *pMode = NUMBER0_3;
            break;
        case 1:
            *pMode = NUMBER0_9;
            break;
        case 2:
            *pMode = ALPHABET;
            break;
        default:
            break;
    }
    return true;
}

bool setList(int iKoma){
    element *eWork_pt;
    
    eWork_pt = eList;
    for (int i = 0; i < iKoma; i++) {
        printf("Set value for Koma %d: ", (i + 1));
        getchar();
        scanf("%c", &(eWork_pt -> cValue));
        eWork_pt -> cAns = '\0';
        eWork_pt -> bIsHit = false;
        eWork_pt -> bIsBlow = false;
        eWork_pt++;
    }
    return true;
}

bool setAnswer(int iKoma){
    char cInput[30];
    scanf("%s", cInput);
    for (int i = 0; i < iKoma; i++) {
        eList[i].cAns = cInput[i];
    }
    return true;
}

bool listCheck(int iKoma, short *sHit, short *sBlow){
    //element *eWork_pt, *eCheck_pt;
    
    //main judgement process
    //step 0 : reset properties, flags
    *sHit = 0;
    *sBlow = 0;
    //eWork_pt = eList;
    for (int i = 0; i < iKoma; i++) {
        eList[i].bIsHit = false;
        eList[i].bIsBlow = false;
    }
    
    //step 1 : check hits
    //eWork_pt = eList;
    for (int i = 0; i < iKoma; i++) {
        if ((eList[i].cValue) == (eList[i].cAns)) {
            eList[i].bIsHit = true;
            *sHit += 1;
        }
    }
    
    //step 2 : check blows
    //eWork_pt = eList;
    for (int i = 0; i < iKoma; i++) {
        //reference
        if (eList[i].bIsHit) {
            continue;
        }
        //eCheck_pt = eList;
        for (int j = 0; j < iKoma; j++) {
            //check from head to tail
            if (!(eList[j].bIsHit) && !(eList[j].bIsBlow) &&
                (eList[i].cAns == eList[j].cValue)) {
                eList[j].bIsBlow = true;
                *sBlow += 1;
                //break;
            }
        }
    }
    
    return true;
}

bool showAnswer(int iKoma){
    printf("Answer: ");
    for (int i = 0; i < iKoma; i++) {
        printf("%c", eList[i].cValue);
    }
    printf("\n");
    return true;
}

int main(int argc, const char * argv[]) {
    //default properties
    int iKoma = 4;
    int iChance = 10;
    mode mMode = NUMBER0_3;
    short sHit = 0;
    short sBlow = 0;
    
    //settings
    printf("Welcome to MasterMind Game\n");
    setRules(&iKoma, &iChance, &mMode);
    setList(iKoma);
#ifdef Debug
    //trace eList by lldb
    element *eList_debug;
    eList_debug = eList;
#endif
    
    printf("************************\nReady.\tStandby.\t[Press Enter to start]\n>");
    getchar();
    getchar();
    system("cls");
    
    //play
    //show rules
    printf("Koma(s): %d\nChances: %d\nCandidate set: ", iKoma, iChance);
    switch (mMode) {
        case NUMBER0_3:
            printf("Numbers 0 - 3\n");
            break;
        case NUMBER0_9:
            printf("Numbers 0 - 9\n");
            break;
        case ALPHABET:
            printf("Alphabet\n");
            break;
        default:
            printf("Error\n");
            break;
    }
    
    for (; iChance > 0;) {
        printf("Enter your answer:\n>");
        //set answer
        setAnswer(iKoma);
        //check
        listCheck(iKoma, &sHit, &sBlow);
        //show result of this turn
        if (sHit == iKoma) {
            break;
        }
        printf("\tHit: %d\tBlow: %d\tChances remaining: %d\n", sHit, sBlow, --iChance);
        
    }
    
    //show result
    if (iChance) {
        printf("Correct. Congrats!\n");
    } else {
        printf("What a pity!\n");;
        showAnswer(iKoma);
        printf("Try again!\n");
    }
    
    return 0;
}
