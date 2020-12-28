#ifndef __CPP2C_ENCAPSULATION_DEFS_H__
#define __CPP2C_ENCAPSULATION_DEFS_H__
#define NUM_BOXES 3
#include <stdbool.h>
/* Box */

typedef struct Box
{    
    double length;
    double width;
    double height;
}Box;


/* Box Defs*/

void Box_ctord(Box* const box,double dim);
void Box_ctorddd(Box* const box,double l, double w, double h);
void Box_dtordef(Box* const box);
Box* Box_operator_muld(Box* const box,double mult);
void Box_print(Box* const box);
/*Shelf */

typedef struct Shelf
{
    Box boxes[NUM_BOXES];
}Shelf;

/*Shelf Defs*/
void Shelf_setBoxiB(Shelf* const s,int index, const Box* const dims);
double Shelf_getVolume(Shelf* const s);
void Shelf_print(Shelf* const s);
#endif /* __CPP2C_ENCAPSULATION_DEFS_H__*/

