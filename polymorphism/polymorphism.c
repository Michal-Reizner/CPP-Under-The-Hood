#include "polymorphism_defs.h"
extern v_table PPDF[4];
v_table M[]={Multiplier_dtor,Multiplier_printcc};
void doPrePostFixer()
{
    printf("\n--- start doPrePostFixer() ---\n\n");

    PrePostFixer angleBrackets;
    PrePostFixer_ctorcc(&angleBrackets,"<<< ", " >>>");
    PrePostFixer_printcc(&angleBrackets,"Hello World!");
    PrePostFixer_printlc(&angleBrackets,-777,'\0');
    PrePostFixer_printlc(&angleBrackets,350, '#');
    PrePostFixer_printlc(&angleBrackets,(long int)(3.14),'\0');

    printf("\n--- end doPrePostFixer() ---\n\n");
	PrePostFixer_dtor(&angleBrackets);
}

void doPrePostDollarFixer()
{
    printf("\n--- start doPrePostDollarFixer() ---\n\n");

    PrePostDollarFixer asterisks;
	PrePostDollarFixer_ctorcc(&asterisks,"***** ", " *****");
    PrePostDollarFixer_printic(&asterisks,-777,'$');
    PrePostDollarFixer_printic(&asterisks,350, '#');
    PrePostDollarFixer_printdc(&asterisks,3.14,'$');

    printf("\n--- end doPrePostDollarFixer() ---\n\n");
	PrePostDollarFixer_dtor(&asterisks);
}

void doPrePostChecker()
{
    printf("\n--- start doPrePostChecker() ---\n\n");

    PrePostChecker check;
    PrePostChecker_ctor(&check);

    PrePostChecker_printThisSymbolUsingFunc(&check);
    PrePostChecker_printThisSymbolDirectly(&check);
    PrePostChecker_printDollarSymbolByCastDirectly(&check);
    PrePostChecker_printDollarSymbolByScopeDirectly(&check);
    PrePostChecker_printDollarSymbolByCastUsingFunc(&check);
    PrePostChecker_printDollarSymbolByScopeUsingFunc(&check);

    printf("\n--- end doPrePostChecker() ---\n\n");

    PrePostChecker_dtor(&check);
}

void doPrePostFloatDollarFixer()
{
    printf("\n--- start doPrePostFloatDollarFixer() ---\n\n");

    PrePostFloatDollarFixer hashes;
    PrePostFloatDollarFixer_ctorcc(&hashes,"### ", " ###");
    PrePostFloatDollarFixer_printf(&hashes,-777);
    PrePostFloatDollarFixer_printfc(&hashes,350, '#');
    PrePostFloatDollarFixer_printf(&hashes,3.14);

    PrePostDollarFixer hashes2;
    PrePostDollarFixer_ctorPPDF(&hashes2,&hashes.ppdf);
    PrePostDollarFixer_printdc(&hashes2,7.5,'$');
    PrePostDollarFixer_printic(&hashes2,100,'$');

    printf("\n--- start doPrePostFloatDollarFixer() ---\n\n");
    PrePostDollarFixer_dtor(&hashes2);
    PrePostFloatDollarFixer_dtor(&hashes);
}

void runAsPrePostFixerRef(const PrePostFixer* pp)
{
    printf("\n--- start runAsPrePostFixerRef() ---\n\n");

    pp->dtf.tf.vptr[2](pp,123,'\0');

    printf("\n--- end runAsPrePostFixerRef() ---\n\n");
}

void runAsPrePostDollarFixerRef(const PrePostDollarFixer* pp)
{
    printf("\n--- start runAsPrePostDollarFixerRef() ---\n\n");

    PrePostDollarFixer_printic(pp,123,'$');

    printf("\n--- end runAsPrePostDollarFixerRef() ---\n\n");
}

void runAsPrePostDollarFixerObj(const PrePostDollarFixer pp)
{
    PrePostDollarFixer p;
    PrePostDollarFixer_ctorPPDF(&p,&pp);
    printf("\n--- start runAsPrePostDollarFixerObj() ---\n\n");
    p.ppf.dtf.tf.vptr=PPDF;
    PrePostDollarFixer_printic(&p,123,'$');

    printf("\n--- end runAsPrePostDollarFixerObj() ---\n\n");
    PrePostDollarFixer_dtor(&p);
}

void runAsPrePostHashFixerRef(const PrePostHashFixer* pp)
{
    printf("\n--- start runAsPrePostHashFixerRef() ---\n\n");
    PrePostHashFixer_printic(pp,123,'#');


    printf("\n--- end runAsPrePostHashFixerRef() ---\n\n");
}
void doMultiplier()
{
    printf("\n--- start doMultiplier() ---\n\n");
    Multiplier m1;
    DefaultTextFormatter_ctor(&m1.dtf);
    m1.dtf.tf.vptr=M;
    m1.times=3;
    printf("--- Multiplier CTOR: times = %d\n", m1.times);
    Multiplier m2;
    DefaultTextFormatter_ctor(&m2.dtf);
    m2.dtf.tf.vptr=M;
    m2.times = 5;
    printf("--- Multiplier CTOR: times = %d\n", m2.times);
    Multiplier m3;
    DefaultTextFormatter_cctor(&m3.dtf,&m1.dtf);
    m3.dtf.tf.vptr=M;
    m3.times = m1.times;
    Multiplier m4;
    DefaultTextFormatter_cctor(&m4.dtf,&m1.dtf);
    m4.dtf.tf.vptr=M;
    m4.times = m2.times;

    Multiplier_printcc(&m1,"abc ");
    Multiplier_printcc(&m2,"abc ");
    Multiplier_printcc(&m3,"abc ");
    Multiplier_printcc(&m4,"abc ");

    printf("\n--- start doMultiplier() ---\n\n");
    Multiplier_dtor(&m4);
    Multiplier_dtor(&m3);
    Multiplier_dtor(&m2);
    Multiplier_dtor(&m1);

}

void doFormatterArray()
{
    printf("\n--- start doFormatterArray() ---\n\n");
    DefaultTextFormatter d1;
    DefaultTextFormatter d2;
    DefaultTextFormatter d3;

    PrePostDollarFixer p1;
    PrePostDollarFixer_ctorcc(&p1,"!!! ", " !!!");
    DefaultTextFormatter_cctor(&d1,&p1.ppf.dtf);
    PrePostDollarFixer_dtor(&p1);
    Multiplier m1;
    DefaultTextFormatter_ctor(&m1.dtf);
    m1.dtf.tf.vptr=M;
    m1.times=4;
    printf("--- Multiplier CTOR: times = %d\n", m1.times);
    DefaultTextFormatter_cctor(&d2,&m1.dtf);
    Multiplier_dtor(&m1);
    PrePostChecker p2;
    PrePostChecker_ctor(&p2);
    DefaultTextFormatter_cctor(&d3,&p2.ppfdf.ppdf.ppf.dtf);
    PrePostChecker_dtor(&p2);
    DefaultTextFormatter formatters[] =
    {
        d1,
        d2,
        d3
    };

    for (int i = 0; i < 3; ++i)
        DefaultTextFormatter_printcc(&formatters[i],"Hello World!");

    printf("\n--- end doFormatterArray() ---\n\n");
    DefaultTextFormatter_dtor(&d3);
    DefaultTextFormatter_dtor(&d2);
    DefaultTextFormatter_dtor(&d1);

}

void doFormatterPtrs()
{
    printf("\n--- start doFormatterPtrs() ---\n\n");
    PrePostDollarFixer p1;
    PrePostDollarFixer_ctorcc(&p1,"!!! ", " !!!");
    Multiplier m1;
    DefaultTextFormatter_ctor(&m1.dtf);
    m1.dtf.tf.vptr=M;
    m1.times=4;
    printf("--- Multiplier CTOR: times = %d\n", m1.times);
    PrePostChecker p2;
    PrePostChecker_ctor(&p2);
    DefaultTextFormatter* pfmt[]={
        &p1.ppf.dtf,
        &m1.dtf,
        &p2.ppfdf.ppdf.ppf.dtf
    };
    for (int i = 0; i < 3; ++i)
        pfmt[i]->tf.vptr[1](pfmt[i],"Hello World");
    for (int i = 2; i >= 0; --i)
        pfmt[i]->tf.vptr[0](pfmt[i]);

    printf("\n--- end doFormatterPtrs() ---\n\n");
}

void doFormatterDynamicArray() {
    printf("\n--- start doFormatterDynamicArray() ---\n\n");

    DefaultTextFormatter *formatters = generateFormatterArray();

    for (int i = 0; i < 3; ++i)
        formatters[i].tf.vptr[1](&formatters[i], "Hello World!");

    for (int i = 2; i>=0; i--)
        formatters[i].tf.vptr[0](&formatters[i]);

    free(formatters);

    printf("\n--- start doFormatterDynamicArray() ---\n\n");
}

int main()
{
    printf("\n--- Start main() ---\n\n");

   /* doPrePostFixer();
    doPrePostDollarFixer();
    doPrePostFloatDollarFixer();
    doPrePostChecker();*/

    PrePostHashFixer hfix;
    PrePostHashFixer_ctori(&hfix,4);
    runAsPrePostFixerRef(&hfix.ppdf.ppf);
    runAsPrePostDollarFixerRef(&hfix.ppdf);
   runAsPrePostDollarFixerObj(hfix.ppdf);
    runAsPrePostHashFixerRef(&hfix);

    doMultiplier();

    doFormatterArray();
    doFormatterPtrs();
    doFormatterDynamicArray();

    printf("\n--- End main() ---\n\n");
    PrePostHashFixer_dtor(&hfix);
    return 0;
}



