%{
%}
%%
[6-9][0-9]{9} {printf("\n mobile number valid");}
.+ {printf("\n mobile number invalid");}
%%
int yywrap(void){}
int main()
{
printf("\n enter number");
yylex();
printf("\n");
return 0;
}