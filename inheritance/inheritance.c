#include <stdio.h>
#include "inheritance_defs.h"
void g_doMaterials()
{
	const char* const names[] = { "Plastic", "Metal", "Wood", "Paper", "Other" };
    printf("\n--- Start doMaterials() ---\n\n");
    
    Materials mat;
	
    printf("Size of Materials: %lu\n", sizeof(Materials));
    printf("Size of mat: %lu\n", sizeof(mat));
    printf("Size of Materials::Types: %lu\n",sizeof(Types));
    printf("Size of Material_t: %lu\n", sizeof(Material_t));

    struct MatTest { Materials mat; Material_t mat_t; };
    printf("Size of Materials + Material_t: %lu\n",sizeof(struct MatTest) );
    
    Material_t mat1;
	mat1.material=OTHER;
	printf("Material created, set to %s\n",names[mat1.material]);
	Material_t mat2;
	mat2.material=METAL;
	printf("Material created, set to %s\n",names[mat2.material]);

    printf("\n--- End doMaterials() ---\n\n");
}

void g_doPhysicalBox()
{
    printf("\n--- Start doPhysicalBox() ---\n\n");

    PhysicalBox pb1;
	PhysicalBox_ctordddM(&pb1,8, 6, 4,PLASTIC);
    PhysicalBox pb2;
	PhysicalBox_ctorM(&pb2,WOOD);
    PhysicalBox pb3;
	PhysicalBox_ctorddd(&pb3,7, 7, 7);
    
    printf("\npb4 is copy-constructed from pb1\n");
    PhysicalBox pb4 = pb1;
    PhysicalBox_printp(&pb4);
	PhysicalBox_printp(&pb1);
    printf("pb4 %s pb1\n", ((pb1.box.length==pb4.box.length)&(pb1.box.width==pb4.box.width)&(pb1.box.height==pb4.box.height)& (pb1.material.material==pb4.material.material)) ? "equals" : "does not equal");

    printf("\npb4 is copy-assigned from pb3\n");
    pb4 = pb3;
    PhysicalBox_printp(&pb4);
    PhysicalBox_printp(&pb3);
    printf("pb4 %s pb3\n", ((pb3.box.length==pb4.box.length)&(pb3.box.width==pb4.box.width)&(pb3.box.height==pb3.box.height)& (pb3.material.material==pb4.material.material)) ? "equals" : "does not equal");

    printf("\n--- End doPhysicalBox() ---\n\n");
	PhysicalBox_dtor(&pb4);
	PhysicalBox_dtor(&pb3);
	PhysicalBox_dtor(&pb2);
	PhysicalBox_dtor(&pb1);
}

void g_doWeightBox()
{
    printf("\n--- Start doWeightBox() ---\n\n");

    WeightBox pw1;
	WeightBox_ctordddd(&pw1,8, 6, 4, 25);
    WeightBox pw2;
	WeightBox_ctordddd(&pw2,1, 2, 3,0.0);
    WeightBox pw3;
	WeightBox_ctordddd(&pw3,10, 20, 30, 15);
    
    printf("\npw4 is copy-constructed from pw1\n");
    WeightBox pw4;
	WeightBox_cctor(&pw4,&pw1);
    WeightBox_printw(&pw4);
    WeightBox_printw(&pw1);
    printf("pw4 %s pw1\n",((pw1.box.length==pw4.box.length)&&(pw1.box.width==pw4.box.width)&&(pw1.box.height==pw1.box.height)&& (pw1.weight==pw4.weight))? "equals" : "does not equal");

    printf("\npw4 is copy-assigned from pw3\n");
    WeightBox_operatoreq(&pw4,&pw3);
    WeightBox_printw(&pw4);
    WeightBox_printw(&pw3);
    printf("pw4 %s pw3\n",((pw3.box.length==pw4.box.length)&&(pw3.box.width==pw4.box.width)&&(pw3.box.height==pw3.box.height)&& (pw1.weight==pw4.weight))? "equals" : "does not equal");

    printf("\n--- End doWeightBox() ---\n\n");
	WeightBox_dtor(&pw4);
	WeightBox_dtor(&pw3);
	WeightBox_dtor(&pw2);
	WeightBox_dtor(&pw1);
}





int main()
{
    printf("\n--- Start main() ---\n\n");

    g_doMaterials();

    g_doPhysicalBox();

    g_doWeightBox();

    printf("\n--- End main() ---\n\n");

}
