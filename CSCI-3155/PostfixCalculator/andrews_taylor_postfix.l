%{
#include "andrews_taylor_postfix.tab.hpp"
#include <iostream>
using namespace std;
%}

%option noyywrap

%%

[0-9]+   { yylval.val = atoi(yytext); return NUM; }
[\+|\-]  { yylval.sym = yytext[0]; return OPA; }
[\*|/]   { yylval.sym = yytext[0]; return OPM; }
";"      { return STOP; }
<<EOF>>  { return 0; }
[ \t\n]+ { }
.        { cerr << "Unrecognized token!" << endl; exit(1); }
%%
