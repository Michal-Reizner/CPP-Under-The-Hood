#include <stdio.h>
#include "encapsulation_defs.h"
const char DEF_MSG[]="The total volume held on the shelf is";
const char* g_message = DEF_MSG;
/* Box*/
void Box_ctord(Box* const box,double dim)
{
 	box->length=dim;
	box->width=dim;
  	box->height=dim; 
 	Box_print(box);
}

void Box_ctorddd(Box* const box,double l, double w, double h)
{
	box->length=l;
	box->width=w;
	box->height=h; 
    	Box_print(box); 
}
void Box_dtordef(Box* const box)
{
	printf("Box destructor, %f x %f x %f\n", box->width, box->height, box->length);
} 
Box* Box_operator_muld(Box* const box,double mult)
{
    box->width *= mult;
    box->height *= mult;
    box->length *= mult;

    return box;
}
void Box_print(Box* const box)
{
    printf("Box: %f x %f x %f\n", box->length, box->width, box->height); 
}
/*Shelf*/		
void Shelf_setBoxiB(Shelf* const s,int index, const Box* const dims)
{
	s->boxes[index] = *dims;
}
double Shelf_getVolume(Shelf* const s)
{
	double vol = 0;
	size_t i = 0;
    	for (; i < NUM_BOXES; ++i)
        	vol += (s->boxes[i]).length*(s->boxes[i]).width*(s->boxes[i]).height;

    	return vol;
}
void Shelf_print(Shelf* const s)
{
	printf("%s %f\n", g_message, Shelf_getVolume(s));
}




