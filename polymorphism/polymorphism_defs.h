#ifndef __CPP2C_POLYMORPHISM_H__
#define __CPP2C_POLYMORPHISM_H__
#include <malloc.h>
#include <string.h>
#include <stdio.h>
typedef void (*v_table)();


//// TextFormatter ////////////
typedef struct TextFormatter
{
	v_table* vptr;
}TextFormatter;
void TextFormatter_dtor();
//// DefaultTextFormatter ////////////


typedef struct DefaultTextFormatter
{
	TextFormatter tf;
	int id;
}DefaultTextFormatter;
void DefaultTextFormatter_ctor(DefaultTextFormatter* this);
void DefaultTextFormatter_dtor(DefaultTextFormatter* this);
void DefaultTextFormatter_cctor(DefaultTextFormatter* this,const DefaultTextFormatter* const other);
DefaultTextFormatter* DefaultTextFormatter_eq(DefaultTextFormatter* const this,const DefaultTextFormatter* const other);
void DefaultTextFormatter_printcc(DefaultTextFormatter* const this,const char* text);
DefaultTextFormatter* generateFormatterArray();
/*

//// PrePostFixer ////////////
*/
typedef struct PrePostFixer
{	
	DefaultTextFormatter dtf;
	const char* pre;
    const char* post;
}PrePostFixer;
//// PrePostFixer Defs ////////////

void PrePostFixer_ctorcc(PrePostFixer  *this,const char* prefix, const char* postfix);
void PrePostFixer_dtor(PrePostFixer *this);
void PrePostFixer_printcc(const PrePostFixer const *this,const char* text);
void PrePostFixer_printlc(const PrePostFixer const *this,long num, char symbol);
char PrePostFixer_getDefaultSymbol(const PrePostFixer const *this);

//// PrePostDollarFixer ////////////
typedef struct PrePostDollarFixer
{
	PrePostFixer ppf;
}PrePostDollarFixer;
//// PrePostDollarFixer Defs ////////////
void PrePostDollarFixer_ctorcc(PrePostDollarFixer * const this ,const char* prefix, const char* postfix);
void PrePostDollarFixer_ctorPPDF(PrePostDollarFixer * const this,const PrePostDollarFixer* other);
void PrePostDollarFixer_dtor(PrePostDollarFixer *this);
void PrePostDollarFixer_printic(const PrePostDollarFixer const *this,int num, char symbol);
void PrePostDollarFixer_printlc(const PrePostDollarFixer const *this,long num, char symbol);
void PrePostDollarFixer_printdc(const PrePostDollarFixer const *this,double num, char symbol);
char PrePostDollarFixer_getDefaultSymbolPPDF(const PrePostDollarFixer const *this);
//// PrePostHashFixer ////////////
typedef struct PrePostHashFixer
{
    PrePostDollarFixer ppdf;
	int precision;
}PrePostHashFixer;

//// PrePostHashFixer Defs ////////////
void PrePostHashFixer_ctori(PrePostHashFixer* const this ,int prc);
void PrePostHashFixer_dtor(PrePostHashFixer* this);
void PrePostHashFixer_printic(const PrePostHashFixer* const this,int num, char symbol);
void PrePostHashFixer_printlc(const PrePostHashFixer* const this,long num, char symbol);
char PrePostHashFixer_getDefaultSymbol(const PrePostHashFixer* const this);
//// PrePostFloatDollarFixer ////////////
/*
class PrePostFloatDollarFixer: public PrePostDollarFixer
{
protected:
    static const char DEFAULT_SYMBOL = '@';

public:
    PrePostFloatDollarFixer(const char* prefix, const char* postfix);
    ~PrePostFloatDollarFixer();
    void print(float num) const;
    void print(float num, char symbol) const;
    char getDefaultSymbol() const;
};*/
typedef struct PrePostFloatDollarFixer
{
	PrePostDollarFixer ppdf;
}PrePostFloatDollarFixer;
void PrePostFloatDollarFixer_ctorcc(PrePostFloatDollarFixer* const this,const char* prefix, const char* postfix);
void PrePostFloatDollarFixer_dtor(PrePostFloatDollarFixer* const this);
void PrePostFloatDollarFixer_printf(PrePostFloatDollarFixer* const this,float num);
void PrePostFloatDollarFixer_printfc(PrePostFloatDollarFixer* const this,float num,char symbol);
char PrePostFloatDollarFixer_getDefaultSymbol();

//// PrePostChecker ////////////
typedef struct PrePostChecker
{
    PrePostFloatDollarFixer ppfdf;
}PrePostChecker;
/*class PrePostChecker: public PrePostFloatDollarFixer
{
public:
    PrePostChecker();
    ~PrePostChecker();
    
    void printThisSymbolUsingFunc() const;
    void printThisSymbolDirectly() const;    
    void printDollarSymbolByCastUsingFunc() const;
    void printDollarSymbolByScopeUsingFunc() const;
    void printDollarSymbolByCastDirectly() const;
    void printDollarSymbolByScopeDirectly() const;
};*/
void PrePostChecker_ctor(PrePostChecker* const this);
void PrePostChecker_dtor(PrePostChecker* const this);
void PrePostChecker_printThisSymbolUsingFunc(PrePostChecker* const this);
void PrePostChecker_printThisSymbolDirectly(const PrePostChecker* const this);
void PrePostChecker_printDollarSymbolByCastUsingFunc(PrePostChecker* this);
void PrePostChecker_printDollarSymbolByScopeUsingFunc(const PrePostChecker* const this);
void PrePostChecker_printDollarSymbolByCastDirectly(const PrePostChecker* const this);
void PrePostChecker_printDollarSymbolByScopeDirectly(const PrePostChecker* const this);
/*
//// Multiplier ////////////

class Multiplier: public DefaultTextFormatter
{
public:
    Multiplier(int t = 2);
    ~Multiplier();

    void print(const char*) const;
    int getTimes() const;
    void setTimes(int);
private:
    int times;
}; 
*/
typedef struct Multiplier
{
    DefaultTextFormatter dtf;
    int times;
}Multiplier;
void Multiplier_dtor(Multiplier* const this);
void Multiplier_printcc(Multiplier* const this,const char* text);
/*
//// Multiplier Defs ////////////

inline Multiplier::Multiplier(int t)
:   times(t)
{
    printf("--- Multiplier CTOR: times = %d\n", times);
}

inline Multiplier::~Multiplier()
{
    printf("--- Multiplier DTOR: times = %d\n", times);
}
    
inline int Multiplier::getTimes() const
{
    return times;
}

inline void Multiplier::setTimes(int t)
{
    times = t;
}
*/


#endif // __CPP2C_POLYMORPHISM_H__

