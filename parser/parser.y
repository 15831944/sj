%define parse.error verbose
%define api.pure true
%locations
%token-table
%lex-param {void *scanner}
%parse-param {void *scanner} {CResult* result}

%{

#include <stdio.h>
#include "../node/Node.h"
#include "parser.hpp"

#pragma clang diagnostic ignored "-Wunreachable-code"
#pragma clang diagnostic ignored "-Wunused-variable"

#define LOC CLoc(yyloc.first_line, yyloc.first_column)

int yyerror(YYLTYPE *locp, void *scanner, CResult* result, const char *msg) {
  if (locp) {
  	result->warnings.push_back(CError(CLoc(locp->first_line, locp->first_column), CErrorCode::Parser, msg));
  } else {
  	result->warnings.push_back(CError(CLoc::undefined, CErrorCode::Parser, msg));
  }
  return (0);
}

extern int yylex(YYSTYPE * yylval_param,YYLTYPE * yylloc_param , void *scanner);

#define YYPRINT yyprint

void yyprint(FILE* file, unsigned short int v1, const YYSTYPE type) {
	switch (v1) {
		case TIDENTIFIER:
        case TINTEGER:
        case TDOUBLE:
			fprintf(file, "%s", type.string->c_str());
	}				
}

%}

/* Represents the different ways to access our code being compiled*/

%union {
	NBase* node;
	NBlock* block;
	NIf* nif;
	NAssignment* var_decl;
	std::vector<shared_ptr<NBase>>* exprvec;
	std::string* string;
	std::vector<std::string>* strList;
	int token;
	bool isMutable;
}

/* Terminal symbols. They need to match tokens in tokens.l file */
%token <string> TIDENTIFIER TINTEGER TDOUBLE TINVALID 
%token <token> TCEQ TCNE TCLT TCLE TCGT TCGE TEQUAL TEND error
%token <token> TLPAREN TRPAREN TLBRACE TRBRACE TCOMMA TDOT TCOLON TQUOTE
%token <token> TPLUS TMINUS TMUL TDIV TTRUE TFALSE TCAST TVOID TIF TELSE

/* Non Terminal symbols. Types refer to union decl above */
%type <node> program expr var stmt var_decl func_decl func_call func_arg
%type <block> stmts block
%type <nif> if_expr
%type <exprvec> func_args
%type <isMutable> assign

/* Operator precedence */
%left TPLUS TMINUS
%left TMUL TDIV

/* Starting rule in the grammar*/

%start program

/* Grammar rules */

%%

program 			: stmts 										{ result->block = std::shared_ptr<NBlock>($1); }
					;

stmts 				: stmt											{ $$ = new NBlock(LOC); if ($1) $$->statements->push_back(shared_ptr<NBase>($1)); }
					| stmts TEND stmt								{ if ($3) $1->statements->push_back(shared_ptr<NBase>($3)); }
					;
					
stmt 				: /* Blank! */									{ $$ = nullptr; }
					| var_decl
					| func_decl 
					| expr
					| error	 										{ $$ = nullptr; /* yyclearin; */ result->errors.push_back(CError(LOC, CErrorCode::InvalidCharacter)); }
					;

block 				: TLBRACE stmts TRBRACE 						{ $$ = $2; }
					;

var_decl 			: TIDENTIFIER assign expr						{ /* x = 1 */ 		$$ = new NAssignment(LOC, "", $1->c_str(), shared_ptr<NBase>($3), $2); }
					| TIDENTIFIER TQUOTE TIDENTIFIER assign expr	{ /* x'int = 2 */ 	$$ = new NAssignment(LOC, $3->c_str(), $1->c_str(), shared_ptr<NBase>($5), $4); }
					;

func_decl 			: TIDENTIFIER TLPAREN func_args TRPAREN block 						{ /* f()'int */ $$ = new NFunctionDeclaration(LOC, "", $1->c_str(), shared_ptr<NodeList>($3), shared_ptr<NBlock>($5)); }
					| TIDENTIFIER TLPAREN func_args TRPAREN TQUOTE TIDENTIFIER block 	{ /* f() */     $$ = new NFunctionDeclaration(LOC, $6->c_str(), $1->c_str(), shared_ptr<NodeList>($3), shared_ptr<NBlock>($7)); }
					;

func_call			: TIDENTIFIER TLPAREN func_args TRPAREN			{ $$ = new NMethodCall(LOC, $1->c_str(), shared_ptr<NodeList>($3)); delete $1; }
					;

func_args  			: /* Blank! */ 									{ $$ = new NodeList(); }
					| func_arg										{ $$ = new NodeList(); $$->push_back(shared_ptr<NBase>($1)); }
					| func_args TCOMMA func_arg 					{ $1->push_back(shared_ptr<NBase>($3)); }
					;

func_arg			: var_decl 										
					| expr 											
					; 

expr				: func_call 	
					| expr TPLUS var 								{ $$ = new NMath(LOC, shared_ptr<NBase>($1), NMathOp::Add, shared_ptr<NBase>($3)); }
					| expr TMINUS var 								{ $$ = new NMath(LOC, shared_ptr<NBase>($1), NMathOp::Sub, shared_ptr<NBase>($3)); }
					| expr TMUL var 								{ $$ = new NMath(LOC, shared_ptr<NBase>($1), NMathOp::Mul, shared_ptr<NBase>($3)); }
					| expr TDIV var 								{ $$ = new NMath(LOC, shared_ptr<NBase>($1), NMathOp::Div, shared_ptr<NBase>($3)); }
					| expr TCEQ var 								{ $$ = new NCompare(LOC, shared_ptr<NBase>($1), NCompareOp::EQ, shared_ptr<NBase>($3)); }
					| expr TCNE var 								{ $$ = new NCompare(LOC, shared_ptr<NBase>($1), NCompareOp::NE, shared_ptr<NBase>($3)); }
					| expr TCLT var 								{ $$ = new NCompare(LOC, shared_ptr<NBase>($1), NCompareOp::LT, shared_ptr<NBase>($3)); }
					| expr TCLE var 								{ $$ = new NCompare(LOC, shared_ptr<NBase>($1), NCompareOp::LE, shared_ptr<NBase>($3)); }
					| expr TCGT var 								{ $$ = new NCompare(LOC, shared_ptr<NBase>($1), NCompareOp::GT, shared_ptr<NBase>($3)); }
					| expr TCGE var 								{ $$ = new NCompare(LOC, shared_ptr<NBase>($1), NCompareOp::GE, shared_ptr<NBase>($3)); }
					| TLPAREN expr TRPAREN 							{ $$ = $2; }
					| expr TCAST TIDENTIFIER   						{ $$ = new NCast(LOC, $3->c_str(), shared_ptr<NBase>($1)); }
					| if_expr										{ $$ = (NBase*)$1; }
					| var
					;
					
if_expr		 		: TIF expr block								{ $$ = new NIf(LOC, shared_ptr<NBase>($2), shared_ptr<NBase>($3), nullptr); }
					| TIF expr block TELSE block					{ $$ = new NIf(LOC, shared_ptr<NBase>($2), shared_ptr<NBase>($3), shared_ptr<NBase>($5)); }
					| TIF expr block TELSE if_expr					{ $$ = new NIf(LOC, shared_ptr<NBase>($2), shared_ptr<NBase>($3), shared_ptr<NBase>($5)); }
					;

var 				: TMINUS TINTEGER 								{ $2->insert(0, "-"); $$ = new NInteger(LOC, $2->c_str()); delete $2; }
					| TINTEGER 										{ $$ = new NInteger(LOC, $1->c_str()); delete $1; }
					| TMINUS TDOUBLE 								{ $2->insert(0, "-"); $$ = new NDouble(LOC, $2->c_str()); delete $2; }
					| TDOUBLE 										{ $$ = new NDouble(LOC, $1->c_str()); delete $1; }
					| TTRUE											{ $$ = new NBool(LOC, true); }
					| TFALSE										{ $$ = new NBool(LOC, false); }
					| TVOID											{ $$ = new NVoid(LOC); }
					| TIDENTIFIER									{ $$ = new NVariable(LOC, $1->c_str()); delete $1; }
					;
										
assign				: TEQUAL										{ $$ = true; }
					| TCOLON										{ $$ = false; }
					;

%%