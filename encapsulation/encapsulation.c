#include <stdio.h>
#include "encapsulation_defs.h"
extern const char *g_message;
static bool flag1=1,flag2=1;
static Box largeBox;
static Box box99;
static Box box88;
void g_thisFunc()
{
	
	printf("\n--- thisFunc() ---\n\n"); 
	
	if(flag1)
	{
		flag1=0;
		Box_ctorddd(&box99,99, 99, 99);
	}
	Box_operator_muld(&box99,10);
}

void g_thatFunc()
{
	static bool flag=1;
	printf("\n--- thatFunc() ---\n\n"); 
	if(flag2)
	{
		flag2=0;
		Box_ctorddd(&box88,88, 88, 88);
	}
	Box_operator_muld(&box88,10);
}

void g_doBoxes()
{
	Box b1;
	Box b2;
	Box b3;
	Box b4;
	printf("\n--- Start doBoxes() ---\n\n");

	
	Box_ctord(&b1,3);
	
	Box_ctorddd(&b2,4, 5, 6);
    	b3 = b2;
    	b4 =b2;
	printf("b1 volume: %f\n", b1.width * b1.length * b1.height);
    	printf("b2 volume: %f\n", b2.width * b2.length * b2.height);
	Box_operator_muld(&b1,1.5);
	Box_operator_muld(&b2,0.5);
	printf("b1 volume: %f\n", b1.width * b1.length * b1.height);
    	printf("b2 volume: %f\n", b2.width * b2.length * b2.height);

    	
	Box_operator_muld(&b4,3);
    	printf("b3 %s b4\n", ((b3.length==b4.length)&&(b3.width==b4.width)&&(b3.height==b4.height)) ? "equals" : "does not equal");
	Box_operator_muld(&b3,1.5);
	Box_operator_muld(&b4,0.5);
    	printf("Now, b3 %s b4\n",((b3.length==b4.length)&&(b3.width==b4.width)&&(b3.height==b4.height))? "equals" : "does not equal");

    	printf("\n--- End doBoxes() ---\n\n");
	Box_dtordef(&b4);
	Box_dtordef(&b3);
	Box_dtordef(&b2);
	Box_dtordef(&b1);
}


void g_doShelves()
{
	int i=0;
	Box aBox;
	Box b;
	Box b1;
	Shelf aShelf;
	printf("\n--- start doShelves() ---\n\n");

	
	Box_ctord(&aBox,5);
	
	for(i=0;i<NUM_BOXES;i++)
	{
		Box_ctord(&aShelf.boxes[i],1);
	}
	Shelf_print(&aShelf);
	Shelf_setBoxiB(&aShelf,1,&largeBox);
	Shelf_setBoxiB(&aShelf,0,&aBox);
	Shelf_print(&aShelf);
	g_message="This is the total volume on the shelf:";
	Shelf_print(&aShelf);
	g_message="Shelf's volume:";
   	Shelf_print(&aShelf);
	
	Box_ctorddd(&b,2, 4, 6);
	Shelf_setBoxiB(&aShelf,1,&b);
	Box_dtordef(&b);
	
	Box_ctord(&b1,2);
	Box_dtordef(&b1);
	Shelf_setBoxiB(&aShelf,2,&b1);
  	Shelf_print(&aShelf);

    	printf("\n--- end doShelves() ---\n\n");
	
	for(i=NUM_BOXES-1;i>=0;i--)
	{
		Box_dtordef(&aShelf.boxes[i]);
	}
	Box_dtordef(&aBox);
}
void __attribute__((constructor)) init_largeBox();
void __attribute__((destructor)) destroy_staticBox();
int main()
{
	Box_ctorddd(&largeBox,10, 20, 30);
 	printf("\n--- Start main() ---\n\n");
	g_doBoxes();
    g_thisFunc();
	g_thisFunc();
	g_thisFunc();
	g_thatFunc();
	g_thatFunc();

	g_doShelves();
        
	printf("\n--- End main() ---\n\n");
	Box_dtordef(&largeBox);
	if(!flag1)
		Box_dtordef(&box99);
	if(!flag2)
		Box_dtordef(&box88);
	return 0;

}
