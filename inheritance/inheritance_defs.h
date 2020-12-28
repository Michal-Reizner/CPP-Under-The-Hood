#ifndef __CPP2C_INHERITANCE_DEFS_H__
#define __CPP2C_INHERITANCE_DEFS_H__

#include <stdio.h>
#include "encapsulation_defs.h" 
//// Materials ////////////

typedef struct Materials
{
    /*enum Types
    {
        PLASTIC,
        METAL,
        WOOD,
        PAPER,
        OTHER
    };

    static const char* getName(Types type)
    {
        const char* const names[] = { "Plastic", "Metal", "Wood", "Paper", "Other" };
        return names[type];
    }*/
	char nothing;
}Materials;
typedef enum Types
{
        PLASTIC,
        METAL,
        WOOD,
        PAPER,
        OTHER
}Types;
typedef struct Material_t
{
    /*Material_t(Types mat = OTHER): material(mat) { printf("Material created, set to %s\n", name()); }
    const char* name() const { return getName(material); }*/

    Types material;
}Material_t;


//// PhysicalBox ////////////

typedef struct PhysicalBox
{
/*public:
    PhysicalBox(double l, double w, double h);
    PhysicalBox(double l, double w, double h, Materials::Types t);
    PhysicalBox(Materials::Types t);
    ~PhysicalBox();

    Materials::Types getMaterial() const;
    void printp() const;

private:*/
	Box box;
    Material_t material;
}PhysicalBox;
void PhysicalBox_ctorddd(PhysicalBox* const this,double l, double w, double h);
void PhysicalBox_ctordddM(PhysicalBox* const this,double l, double w, double h, Types t);
void PhysicalBox_ctorM(PhysicalBox* const this,Types t);
void PhysicalBox_dtor(PhysicalBox* const this);
void PhysicalBox_printp(PhysicalBox* const this);
/*bool operator==(const PhysicalBox&, const PhysicalBox&);
bool operator!=(const PhysicalBox&, const PhysicalBox&);*/

//// PhysicalBox Defs ////////////

/*inline Materials::Types PhysicalBox::getMaterial() const
{
    return material.material;
}

inline bool operator==(const PhysicalBox& lhs, const PhysicalBox& rhs)
{
    return (const Box&)lhs == (const Box&)rhs && lhs.getMaterial() == rhs.getMaterial();
}

inline bool operator!=(const PhysicalBox& lhs, const PhysicalBox& rhs)
{
    return !(lhs == rhs);
}*/

//// WeightBox ////////////

typedef struct WeightBox
{
/*public:
    WeightBox(double l, double w, double h, double wgt = 0.0);
    WeightBox(const WeightBox& other);
    ~WeightBox();

    WeightBox& operator=(const WeightBox& other);

    double getWeight() const;
    void printw() const;

private:*/
	Box box;
    double weight;
}WeightBox;

/*bool operator==(const WeightBox&, const WeightBox&);
bool operator!=(const WeightBox&, const WeightBox&);

//// WeightBox Defs ////////////

inline double WeightBox::getWeight() const
{
    return weight;
}

inline bool operator==(const WeightBox& lhs, const WeightBox& rhs)
{
    return (const Box&)lhs == (const Box&)rhs && lhs.getWeight() == rhs.getWeight();
}

inline bool operator!=(const WeightBox& lhs, const WeightBox& rhs)
{
    return !(lhs == rhs);
}*/
void WeightBox_ctordddd(WeightBox* const this,double l, double w, double h, double wgt);
void WeightBox_cctor(WeightBox* const this,const WeightBox* const other);
void WeightBox_dtor();
WeightBox* WeightBox_operatoreq(WeightBox* const this,const WeightBox* const other);
void WeightBox_printw(WeightBox* const this);




#endif // __CPP2C_INHERITANCE_DEFS_H__


