#include "polymorphism_defs.h"

#include <stdio.h>
void printFunc(const char* fname)
{
    printf("%-60s | ", fname); 
}
v_table TF[]={(v_table)TextFormatter_dtor,NULL};
v_table DTF[] ={(v_table)DefaultTextFormatter_dtor,(v_table)DefaultTextFormatter_printcc};
v_table PPF[]={(v_table)PrePostFixer_dtor,(v_table)PrePostFixer_printcc,(v_table)PrePostFixer_printlc,(v_table)PrePostFixer_getDefaultSymbol};
v_table PPDF[]={(v_table)PrePostDollarFixer_dtor,(v_table)PrePostFixer_printcc,(v_table)PrePostDollarFixer_printlc,(v_table)PrePostDollarFixer_getDefaultSymbolPPDF};
v_table PPHF[]={(v_table)PrePostHashFixer_dtor,(v_table)PrePostFixer_printcc,(v_table)PrePostHashFixer_printlc,(v_table)PrePostHashFixer_getDefaultSymbol};
v_table PPFDF[]={(v_table)PrePostFloatDollarFixer_dtor,(v_table)PrePostFixer_printcc,(v_table)PrePostDollarFixer_printlc,(v_table)PrePostFloatDollarFixer_getDefaultSymbol};
v_table PPC[]={(v_table)PrePostChecker_dtor,(v_table)PrePostFixer_printcc,(v_table)PrePostDollarFixer_printlc,(v_table)PrePostFloatDollarFixer_getDefaultSymbol};
//v_table M[]={Multiplier_dtor,Multiplier_printcc};

void TextFormatter_dtor()
{}
//// DefaultTextFormatter Defs ////////////
int next_id=0;
int getId() { return next_id++; }
void DefaultTextFormatter_ctor(DefaultTextFormatter* this)
{
    this->tf.vptr=DTF;
	this->id=next_id++;
    printf("--- DefaultTextFormatter Default CTOR\n########## C %d ##########\n", this->id);
}
void DefaultTextFormatter_dtor(DefaultTextFormatter* this)
{
    printf("--- DefaultTextFormatter DTOR\n########## D %d ##########\n", this->id);
	this->tf.vptr=TF;
}
void DefaultTextFormatter_cctor(DefaultTextFormatter* this,const DefaultTextFormatter* const other)
{
    this->tf.vptr=DTF;
    this->id=next_id++;
    printf("--- DefaultTextFormatter Copy CTOR, from id: %d\n########## C %d ##########\n", other->id, this->id);
}
DefaultTextFormatter* DefaultTextFormatter_eq(DefaultTextFormatter* const this,const DefaultTextFormatter* const other)
{
	printf("--- DefaultTextFormatter operator=(), from id: %d to id: %d\n", other->id,this->id);
    return this;
}
void DefaultTextFormatter_printcc(DefaultTextFormatter* const this,const char* text)
{
    printFunc("[DefaultTextFormatter::print(const char*)]");    
    printf("%s\n", text);
}
DefaultTextFormatter* generateFormatterArray()
{
    DefaultTextFormatter* arr=malloc(sizeof(DefaultTextFormatter)*3);
    DefaultTextFormatter d1;
    DefaultTextFormatter_ctor(&d1);
    DefaultTextFormatter d2;
    DefaultTextFormatter_ctor(&d2);
    DefaultTextFormatter d3;
    DefaultTextFormatter_ctor(&d3);
    arr[0]=d1;
    arr[1]=d2;
    arr[2]=d3;
    return arr;

}
/*
//// PrePostFixer Defs ////////////
*/


void PrePostFixer_ctorcc(PrePostFixer  *this,const char* prefix, const char* postfix)
{
	DefaultTextFormatter_ctor((DefaultTextFormatter*)this);
	this->dtf.tf.vptr=PPF;
	this->pre=prefix;
    this->post=postfix;
//    printf("sss%S",this->post);
    printf("--- PrePostFixer CTOR: \"%s\"...\"%s\"\n", this->pre, this->post);
}

void PrePostFixer_dtor(PrePostFixer *this)
{
	printf("--- PrePostFixer DTOR: \"%s\"...\"%s\"\n", this->pre, this->post);
	this->dtf.tf.vptr=DTF;
	DefaultTextFormatter_dtor((DefaultTextFormatter*)this);
}

void PrePostFixer_printcc(const PrePostFixer const *this,const char* text)
{
	printf("%-60s | ", "[PrePostFixer::print(const char*)]");
	printf("%s%s%s\n", this->pre,text,this->post);
}

void PrePostFixer_printlc(const PrePostFixer const *this,long num, char symbol)
{
	printf("%-60s | ", "[PrePostFixer::print(long, char)]");
	printf("-->\n");
   
    if (symbol)
	{    
        printf("%-60s | ", "[PrePostFixer::print_num(long, char)]");  
    	printf("%s%c%ld%s\n", this->pre, symbol, num, this->post);
	}
    else
	{
        printf("%-60s | ", "[PrePostFixer::print_num(long)]");
    	printf("%s%ld%s\n", this->pre, num, this->post);
	}
}

char PrePostFixer_getDefaultSymbol(const PrePostFixer const *this)
{
	return '\0';
}

//// PrePostDollarFixer Defs ////////////


void PrePostDollarFixer_ctorcc(PrePostDollarFixer * const this ,const char* prefix, const char* postfix)
{
	PrePostFixer_ctorcc(&this->ppf,prefix,postfix);
	this->ppf.dtf.tf.vptr=PPDF;
	printf("--- PrePostDollarFixer CTOR: \"%s\"...\"%s\"\n", this->ppf.pre, this->ppf.post);
}
void PrePostDollarFixer_ctorPPDF(PrePostDollarFixer * const this,const PrePostDollarFixer* other)
{
    DefaultTextFormatter_cctor(&this->ppf.dtf,&other->ppf.dtf);
    this->ppf.dtf.tf.vptr=other->ppf.dtf.tf.vptr;
	this->ppf.pre=other->ppf.pre;
	this->ppf.post=other->ppf.post;
	this->ppf.dtf.tf.vptr=other->ppf.dtf.tf.vptr;
    printf("--- PrePostDollarFixer Copy CTOR: \"%s\"...\"%s\"\n", this->ppf.pre, this->ppf.post);
}

void PrePostDollarFixer_dtor(PrePostDollarFixer *this)
{
	printf("--- PrePostDollarFixer DTOR: \"%s\"...\"%s\"\n", this->ppf.pre, this->ppf.post);
	this->ppf.dtf.tf.vptr=PPF;
	PrePostFixer_dtor((PrePostFixer*)this);
}

void PrePostDollarFixer_printic(const PrePostDollarFixer const *this,int num, char symbol)
{
	printf("%-60s | ", "[PrePostDollarFixer::print(int, char)]");
    printf("-->\n");
	this->ppf.dtf.tf.vptr[2](this,(long)num,symbol);
    //PrePostDollarFixer_printlc(this,(long)num,symbol);
}
void PrePostDollarFixer_printlc(const PrePostDollarFixer const *this,long num, char symbol)
{
	printf("%-60s | ", "[PrePostDollarFixer::print(long, char)]");
    printf("-->\n");
	PrePostFixer_printlc((PrePostFixer*)this,num,symbol);
}

void PrePostDollarFixer_printdc(const PrePostDollarFixer const *this,double num, char symbol)
{
	printf("%-60s | ", "[PrePostDollarFixer::print(double, char)]");
    printf("%s%c%f%s\n", this->ppf.pre,symbol, num, this->ppf.post);
}

char PrePostDollarFixer_getDefaultSymbolPPDF(const PrePostDollarFixer const *this)
{
	return '$';
}

void PrePostHashFixer_ctori(PrePostHashFixer* const this ,int prc)
{
	PrePostDollarFixer_ctorcc(&this->ppdf,"===> ", " <===");
	this->ppdf.ppf.dtf.tf.vptr=PPHF;
	this->precision=prc;
	printf("--- PrePostHashFixer CTOR: \"%s\"...\"%s\", precision: %d\n",this->ppdf.ppf.pre, this->ppdf.ppf.post, this->precision);

	printf("%-60s | ", "[PrePostHashFixer::print(double, char)]");
    printf("%s[%c%.*f]%s\n", this->ppdf.ppf.pre, '#', this->precision, 9999.9999, this->ppdf.ppf.post);

}
void PrePostHashFixer_dtor(PrePostHashFixer* this)
{
    printf("--- PrePostHashFixer DTOR: \"%s\"...\"%s\"\n", this->ppdf.ppf.pre, this->ppdf.ppf.post);
    this->ppdf.ppf.dtf.tf.vptr=PPDF;
    PrePostDollarFixer_dtor((PrePostDollarFixer*)this);
}
void PrePostHashFixer_printic(const PrePostHashFixer* const this,int num, char symbol)
{
    printf("%-60s | ", "[PrePostHashFixer::print(int, char)]");
    printf("-->\n");
    printf("%-60s | ", "[PrePostHashFixer::print(double, char)]");
    printf("%s[%c%.*f]%s\n", this->ppdf.ppf.pre,symbol, this->precision,(double)(num), this->ppdf.ppf.post);

}
void PrePostHashFixer_printlc(const PrePostHashFixer* const this,long num, char symbol)
{
    printf("%-60s | ", "[PrePostHashFixer::print(long, char)]");
    printf("-->\n");

    printf("%-60s | ", "[PrePostHashFixer::print(double, char)]");

    printf("%s[%c%.*f]%s\n", this->ppdf.ppf.pre, symbol, this->precision,(double)(num), this->ppdf.ppf.post);
   
}
char PrePostHashFixer_getDefaultSymbol(const PrePostHashFixer* const this)
{
    return '#';
}


//// PrePostHashFixer Defs ////////////

//// PrePostFloatDollarFixer Defs ////////////
void PrePostFloatDollarFixer_ctorcc(PrePostFloatDollarFixer* const this,const char* prefix, const char* postfix)
{
    PrePostDollarFixer_ctorcc(&this->ppdf, prefix, postfix);
    this->ppdf.ppf.dtf.tf.vptr = PPFDF;
    printf("--- PrePostFloatDollarFixer CTOR: \"%s\"...\"%s\"\n", this->ppdf.ppf.pre, this->ppdf.ppf.post);
}

void PrePostFloatDollarFixer_dtor(PrePostFloatDollarFixer* const this)
{
    printf("--- PrePostFloatDollarFixer DTOR: \"%s\"...\"%s\"\n",this->ppdf.ppf.pre, this->ppdf.ppf.post);
    this->ppdf.ppf.dtf.tf.vptr = PPDF;
    PrePostDollarFixer_dtor(&this->ppdf);
}
void PrePostFloatDollarFixer_printf(PrePostFloatDollarFixer* const this,float num)
{
    printFunc("[PrePostFloatDollarFixer::print(float)]");
    printf("-->\n");
    PrePostFloatDollarFixer_printfc(this,num, '@');
}
void PrePostFloatDollarFixer_printfc(PrePostFloatDollarFixer* const this,float num,char symbol)
{
    printFunc("[PrePostFloatDollarFixer::print(float, char)]");
    printf("%s%c%.2f%s\n", this->ppdf.ppf.pre, symbol, num,this->ppdf.ppf.post);
}
char PrePostFloatDollarFixer_getDefaultSymbol()
{
    return '@';
}



//// PrePostChecker Defs ////////////
void PrePostChecker_ctor(PrePostChecker* const this)
{
    this->ppfdf.ppdf.ppf.dtf.tf.vptr=PPC;
    PrePostFloatDollarFixer_ctorcc(&this->ppfdf,"[[[[ ", " ]]]]");
    printf("--- PrePostChecker CTOR: \"%s\"...\"%s\"\n", this->ppfdf.ppdf.ppf.pre,this->ppfdf.ppdf.ppf.post);
}
void PrePostChecker_dtor(PrePostChecker* const this)
{
    printf("--- PrePostChecker CTOR: \"%s\"...\"%s\"\n",this->ppfdf.ppdf.ppf.pre,this->ppfdf.ppdf.ppf.post);
    this->ppfdf.ppdf.ppf.dtf.tf.vptr=PPFDF;
    PrePostFloatDollarFixer_dtor(&this->ppfdf);
}
void PrePostChecker_printThisSymbolUsingFunc(PrePostChecker* const this)
{
    printFunc("[PrePostChecker::printThisSymbolUsingFunc()]");
    printf("Default symbol is %c\n", ((char(*)())this->ppfdf.ppdf.ppf.dtf.tf.vptr[3])());
}
void PrePostChecker_printThisSymbolDirectly(const PrePostChecker* const this)
{
    printf("%-60s | ","[PrePostChecker::printThisSymbolDirectly()]");
    printf("Default symbol is %c\n", '@');

}

void PrePostChecker_printDollarSymbolByCastUsingFunc(PrePostChecker* this)
{
    printf("%-60s | ","[PrePostChecker::printDollarSymbolByCastUsingFunc()]");
    this->ppfdf.ppdf.ppf.dtf.tf.vptr=PPFDF;
    printf("Default symbol is %c\n", ((char(*)(const void * const))(this->ppfdf.ppdf.ppf.dtf.tf.vptr[3]))((PrePostFloatDollarFixer*)this));
    this->ppfdf.ppdf.ppf.dtf.tf.vptr=PPC;
}

void PrePostChecker_printDollarSymbolByScopeUsingFunc(const PrePostChecker* const this)
{
    printf("%-60s | ","[PrePostChecker::printDollarSymbolByScopeUsingFunc()]");
    printf("Default symbol is %c\n", PrePostDollarFixer_getDefaultSymbolPPDF(&this->ppfdf.ppdf));
}
void PrePostChecker_printDollarSymbolByCastDirectly(const PrePostChecker* const this)
{
    printf("%-60s | ","[PrePostChecker::printDollarSymbolByCastDirectly()]");
    printf("Default symbol is %c\n",'$');
}
void PrePostChecker_printDollarSymbolByScopeDirectly(const PrePostChecker* const this)
{
    printf("%-60s | ","[PrePostChecker::printDollarSymbolByScopeDirectly()]");
    printf("Default symbol is %c\n",'$');
}
/*
void PrePostChecker::printThisSymbolDirectly() const
{
    printFunc("[PrePostChecker::printThisSymbolDirectly()]");

    printf("Default symbol is %c\n", this->DEFAULT_SYMBOL);
}

void PrePostChecker::printDollarSymbolByCastUsingFunc() const
{
    printFunc("[PrePostChecker::printDollarSymbolByCastUsingFunc()]");

    printf("Default symbol is %c\n", ((PrePostDollarFixer*)(this))->getDefaultSymbol());
}

void PrePostChecker::printDollarSymbolByScopeUsingFunc() const
{
    printFunc("[PrePostChecker::printDollarSymbolByScopeUsingFunc()]");

    printf("Default symbol is %c\n", this->PrePostDollarFixer::getDefaultSymbol());
}

void PrePostChecker::printDollarSymbolByCastDirectly() const
{
    printFunc("[PrePostChecker::printDollarSymbolByCastDirectly()]");

    printf("Default symbol is %c\n", ((PrePostDollarFixer*)(this))->DEFAULT_SYMBOL);
}

void PrePostChecker::printDollarSymbolByScopeDirectly() const
{
    printFunc("[PrePostChecker::printDollarSymbolByScopeDirectly()]");

    printf("Default symbol is %c\n", this->PrePostDollarFixer::DEFAULT_SYMBOL);
}


//// Multiplier Defs ////////////
    */
void Multiplier_dtor(Multiplier* const this)
{
    printf("--- Multiplier DTOR: times = %d\n", this->times);
    DefaultTextFormatter_dtor(&this->dtf);
}
void Multiplier_printcc(Multiplier* const this,const char* text)
{
    printFunc("[Multiplier::print(const char*)]");

    for (int i = 0; i < this->times; ++i)
        printf("%s", text);
    printf("\n");
}


