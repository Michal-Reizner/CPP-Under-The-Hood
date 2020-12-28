#include <stdio.h>
#include "inheritance_defs.h"


//// PhysicalBox Defs ////////////

void PhysicalBox_ctorddd(PhysicalBox* const this,double l, double w, double h)
{
	const char* const names[] = { "Plastic", "Metal", "Wood", "Paper", "Other" };
	Box_ctorddd(&this->box,l,w,h);
	this->material.material=OTHER;
	printf("Material created, set to %s\n", names[this->material.material]);
    PhysicalBox_printp(this);
}

void PhysicalBox_ctordddM(PhysicalBox* const this,double l, double w, double h, Types t)
{
	const char* const names[] = { "Plastic", "Metal", "Wood", "Paper", "Other" };
	Box_ctorddd(&this->box,l,w,h);
	this->material.material=t;
	printf("Material created, set to %s\n", names[this->material.material]);
    PhysicalBox_printp(this);
}

void PhysicalBox_ctorM(PhysicalBox* const this,Types t)
{
	const char* const names[] = { "Plastic", "Metal", "Wood", "Paper", "Other" };
	Box_ctord(&this->box,1);
	this->material.material=t;
	printf("Material created, set to %s\n", names[this->material.material]);
	
    PhysicalBox_printp(this);
}

void PhysicalBox_dtor(PhysicalBox* const this)
{
	const char* const names[] = { "Plastic", "Metal", "Wood", "Paper", "Other" };
    printf("PhysicalBox dtor, %f x %f x %f, %s; ",this->box.length,this->box.width, this->box.width, names[this->material.material]);
	Box_dtordef(&this->box);
}

void PhysicalBox_printp(PhysicalBox* const this)
{
	const char* const names[] = { "Plastic", "Metal", "Wood", "Paper", "Other" };
    printf("PhysicalBox, made of %s; ", names[this->material.material]);
    Box_print(&this->box);
}


/// WeightBox Defs ////////////
void WeightBox_ctordddd(WeightBox* const this,double l, double w, double h, double wgt)
{
	Box_ctorddd(&this->box,l,w,h);
	this->weight=wgt;
    WeightBox_printw(this);
}

void WeightBox_cctor(WeightBox* const this,const WeightBox* const other)
{
	Box_ctord(&this->box,1);
	this->weight=other->weight;
	WeightBox_printw(this);
	
    
}

void WeightBox_dtor(WeightBox* const this)
{
	
   	printf("Destructing WeightBox; ");
	WeightBox_printw(this);
	Box_dtordef(&this->box);
	
  	
}

void WeightBox_printw(WeightBox* const this)
{
    printf("WeightBox, weight: %f; ", this->weight);
    Box_print(&this->box);
}
WeightBox* WeightBox_operatoreq(WeightBox* const this,const WeightBox* const other)
{
	this->weight=other->weight;
	return this;
}

