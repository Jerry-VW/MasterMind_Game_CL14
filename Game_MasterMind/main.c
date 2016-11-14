//
//  main.c
//  Game_MasterMind
//
//  Created by WANGWENQIAN on 2016/11/12.
//  Copyright © 2016 WANGWENQIAN. All rights reserved.
//
//  optional マス数iKoma　記号種類123　繰返す回数iChance

#include <stdio.h>
#include <stdlib.h>
#define Debug

//stdbool.h (C99;VS2015) OR:
//enumerators
typedef enum {
    false, true
}bool;

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

//struct pointer
element *eList;

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
    fflush(stdin);
    printf("Set koma[FREE]:>");
    scanf("%d", iKoma_pt);
    
    printf("Set chance[FREE]:>");
    scanf("%d", iChance_pt);
    
    printf("Set mode[0: NUMBER0_3, 1: NUMBER0_9, 2: ALPHABET]:>");
    scanf("%d",&iChoose);
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
    //ABANDONED!
    //   malloc() 要注意ある
    
    //consider using list
    element *eWork_pt;
    
    eList = (element *)malloc(sizeof(element) * 2);
    eWork_pt = eList;
    for (int i = 0; i < iKoma; i++) {
        printf("Set value for Koma %d:>", (i + 1));
        getchar();
        scanf("%c", &(eWork_pt -> cValue));
        eWork_pt -> cAns = '\0';
        eWork_pt -> bIsHit = false;
        eWork_pt -> bIsBlow = false;
        if (i == (iKoma - 1)) {
            //no need for next element at last loop
            eWork_pt -> eNext_pt = NULL; //番兵
        }else{
            eWork_pt -> eNext_pt = (element *)malloc(sizeof(element) * 2);
            eWork_pt = eWork_pt -> eNext_pt;
        }
    }
    //fflush(stdin);
    return true;
}

bool setAnswer(int iKoma){
    char cInput[10];
    
    fflush(stdin);
    element *eWork_pt = eList;
    
//    for (int i = 0; i < iKoma; i++) {
//        scanf("%c", &(eWork_pt -> cAns));
//        eWork_pt = eWork_pt -> eNext_pt;
//    }
    
    scanf("%s", cInput);
    for (int i = 0; i < iKoma; i++) {
        eWork_pt -> cAns = cInput[i];
        eWork_pt = eWork_pt -> eNext_pt;
    }
    return true;
}

bool listCheck(int iKoma, short *sHit, short *sBlow){
    element *eWork_pt, *eCheck_pt;
    
    //main judgement process
    //step 0 : reset properties, flags
    *sHit = 0;
    *sBlow = 0;
    eWork_pt = eList;
    for (int i = 0; i < iKoma; i++) {
        eWork_pt -> bIsHit = false;
        eWork_pt -> bIsBlow = false;
        eWork_pt = eWork_pt -> eNext_pt;
    }
    
    //step 1 : check hits
    eWork_pt = eList;
    for (int i = 0; i < iKoma; i++) {
        if ((eWork_pt -> cValue) == (eWork_pt -> cAns)) {
            eWork_pt -> bIsHit = true;
            *sHit += 1;
        }
        eWork_pt = eWork_pt -> eNext_pt;
    }
//    for (; eWork_pt -> eNext_pt != NULL; eWork_pt = eWork_pt -> eNext_pt) {
//        if ((eWork_pt -> cValue) == (eWork_pt -> cAns)) {
//            eWork_pt -> bIsHit = true;
//            *sHit += 1;
//        }
//    }
    
    //step 2 : check blows
    eWork_pt = eList;
    for (int i = 0; i < iKoma; i++) {
        //reference
        if (eWork_pt -> bIsHit) {
            continue;
        }
        eCheck_pt = eList;
        for (int j = 0; j < iKoma; j++) {
            //check from head to tail
            if (!(eCheck_pt -> bIsHit) && !(eCheck_pt -> bIsBlow)
                && (eWork_pt -> cAns == eCheck_pt -> cValue)) {
                eCheck_pt -> bIsBlow = true;
                *sBlow += 1;
                //break;
            }
            eCheck_pt = eCheck_pt -> eNext_pt;
        }
        eWork_pt = eWork_pt -> eNext_pt;
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
    printf("%d", sizeof(element));
#endif
    
    printf("************************:\nReady.\tStandby.\t[Press Enter to start]\n>");
    getchar();
    getchar();
    system("clear");
    
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
        printf("\tHit: %d\tBlow: %d\tChances remaing: %d\n", sHit, sBlow, --iChance);
        if (sHit == iKoma) {
            break;
        }
    }
    
    //show result
    if (iChance) {
        printf("Correct. Congrats!\n");
    } else {
        printf("What a pity!\n");
        showAnswer(iKoma);
        printf("Try again!\n");
    }
    
    return 0;
}
