/* A Bison parser, made by GNU Bison 3.0.4.  */

/* Bison implementation for Yacc-like parsers in C

   Copyright (C) 1984, 1989-1990, 2000-2015 Free Software Foundation, Inc.

   This program is free software: you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation, either version 3 of the License, or
   (at your option) any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program.  If not, see <http://www.gnu.org/licenses/>.  */

/* As a special exception, you may create a larger work that contains
   part or all of the Bison parser skeleton and distribute that work
   under terms of your choice, so long as that work isn't itself a
   parser generator using the skeleton or a modified version thereof
   as a parser skeleton.  Alternatively, if you modify or redistribute
   the parser skeleton itself, you may (at your option) remove this
   special exception, which will cause the skeleton and the resulting
   Bison output files to be licensed under the GNU General Public
   License without this special exception.

   This special exception was added by the Free Software Foundation in
   version 2.2 of Bison.  */

/* C LALR(1) parser skeleton written by Richard Stallman, by
   simplifying the original so-called "semantic" parser.  */

/* All symbols defined below should begin with yy or YY, to avoid
   infringing on user name space.  This should be done even for local
   variables, as they might otherwise be expanded by user macros.
   There are some unavoidable exceptions within include files to
   define necessary library symbols; they are noted "INFRINGES ON
   USER NAME SPACE" below.  */

/* Identify Bison output.  */
#define YYBISON 1

/* Bison version.  */
#define YYBISON_VERSION "3.0.4"

/* Skeleton name.  */
#define YYSKELETON_NAME "yacc.c"

/* Pure parsers.  */
#define YYPURE 1

/* Push parsers.  */
#define YYPUSH 0

/* Pull parsers.  */
#define YYPULL 1




/* Copy the first part of user declarations.  */



#include <stdio.h>
#include "../node/Node.h"
#include "parser.hpp"

#define LOC CLoc(parseFile->fullFileName, parseFile->shortFileName, yyloc.first_line, yyloc.first_column)
#define LLOC CLoc(parseFile->fullFileName, parseFile->shortFileName, yylloc.first_line, yylloc.first_column)

int yyerror(YYLTYPE *locp, void *scanner, Compiler* compiler, CParseFile* parseFile, const char *msg) {
  if (locp) {
  	compiler->addWarning(CLoc(parseFile->fullFileName, parseFile->shortFileName, locp->first_line, locp->first_column), CErrorCode::Parser, msg);
  } else {
  	compiler->addWarning(CLoc::undefined, CErrorCode::Parser, msg);
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




# ifndef YY_NULLPTR
#  if defined __cplusplus && 201103L <= __cplusplus
#   define YY_NULLPTR nullptr
#  else
#   define YY_NULLPTR 0
#  endif
# endif

/* Enabling verbose error messages.  */
#ifdef YYERROR_VERBOSE
# undef YYERROR_VERBOSE
# define YYERROR_VERBOSE 1
#else
# define YYERROR_VERBOSE 1
#endif

/* In a future release of Bison, this section will be replaced
   by #include "parser.hpp".  */
#ifndef YY_YY_PARSER_PARSER_HPP_INCLUDED
# define YY_YY_PARSER_PARSER_HPP_INCLUDED
/* Debug traces.  */
#ifndef YYDEBUG
# define YYDEBUG 0
#endif
#if YYDEBUG
extern int yydebug;
#endif
/* "%code requires" blocks.  */


struct OPTIONANDTYPELIST {
	bool isOption;
	CTypeNameList* templateTypeNames;	
};



/* Token type.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
  enum yytokentype
  {
    TIDENTIFIER = 258,
    TINTEGER = 259,
    TDOUBLE = 260,
    TSTRING = 261,
    TCHAR = 262,
    TCBLOCK = 263,
    TCFUNCTION = 264,
    TCDEFINE = 265,
    TCSTRUCT = 266,
    TCINCLUDE = 267,
    TCVAR = 268,
    TCTYPEDEF = 269,
    TQUOTEDIDENTIFIER = 270,
    TCEQ = 271,
    TCNE = 272,
    TCLT = 273,
    TCLE = 274,
    TCGT = 275,
    TCGE = 276,
    TEQUAL = 277,
    TEND = 278,
    TLPAREN = 279,
    TRPAREN = 280,
    TLBRACE = 281,
    TRBRACE = 282,
    TCOMMA = 283,
    TCOLON = 284,
    TQUOTE = 285,
    TPLUS = 286,
    TMINUS = 287,
    TMUL = 288,
    TDIV = 289,
    TTRUE = 290,
    TFALSE = 291,
    TAS = 292,
    TVOID = 293,
    TIF = 294,
    TELSE = 295,
    TTHROW = 296,
    TCATCH = 297,
    TFOR = 298,
    TTO = 299,
    TWHILE = 300,
    TPLUSPLUS = 301,
    TMINUSMINUS = 302,
    TPLUSEQUAL = 303,
    TMINUSEQUAL = 304,
    TLBRACKET = 305,
    TRBRACKET = 306,
    TEXCLAIM = 307,
    TDOT = 308,
    TTHIS = 309,
    TINCLUDE = 310,
    TAND = 311,
    TOR = 312,
    TCOPY = 313,
    TDESTROY = 314,
    TMOD = 315,
    THASH = 316,
    TCPEQ = 317,
    TCPNE = 318,
    TMULEQUAL = 319,
    TDIVEQUAL = 320,
    TISEMPTY = 321,
    TISVALID = 322,
    TGETVALUE = 323,
    TQUESTION = 324,
    TEMPTY = 325,
    TVALID = 326,
    TQUESTIONCOLON = 327,
    TQUESTIONDOT = 328,
    TPARENT = 329,
    TSTACK = 330,
    THEAP = 331,
    TWEAK = 332,
    TLOCAL = 333,
    TTYPEI32 = 334,
    TTYPEU32 = 335,
    TTYPEF32 = 336,
    TTYPEI64 = 337,
    TTYPEU64 = 338,
    TTYPEF64 = 339,
    TTYPECHAR = 340,
    TTYPEBOOL = 341,
    TTYPEPTR = 342,
    TINVALID = 343,
    TCOLONEQUAL = 344,
    THEAPPARENT = 345,
    THEAPTHIS = 346,
    TIFVALID = 347,
    TELSEEMPTY = 348,
    TTOREVERSE = 349,
    TENUM = 350,
    TSWITCH = 351,
    TDEFAULT = 352,
    TPACKAGE = 353,
    TIMPORT = 354,
    TUNDERSCORE = 355,
    TNULLPTR = 356
  };
#endif

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED

union YYSTYPE
{


	NBase* node;
	NBlock* block;
	NVariableBase* var;
	NodeList* exprvec;
	std::string* string;
	CTypeName* typeName;
	CTypeNameList* templateTypeNames;
	int token;
	AssignOp assignOp;
	OPTIONANDTYPELIST optionAndTypeList;
	NTupleAssignmentArgList* tupleAssignmentArgList;
	NTupleAssignmentArg* tupleAssignmentArg;
	CTypeMode typeMode;
	EnumArg* enumArg;
	EnumArgs* enumArgs;
	std::vector<std::string>* strings;
	std::vector<std::pair<std::string, std::vector<std::string>>>* import_namespaces;
	std::pair<std::string, std::vector<std::string>>* import_namespace;
	NCCode* ccode;
	CTypeNameParts* typeNameParts;
	vector<shared_ptr<NSwitchClause>>* switchClauses;
	NSwitchClause* switchClause;
	vector<pair<shared_ptr<NBase>, shared_ptr<NBase>>>* hashArgs;
	pair<shared_ptr<NBase>, shared_ptr<NBase>>* hashArg;


};

typedef union YYSTYPE YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif

/* Location type.  */
#if ! defined YYLTYPE && ! defined YYLTYPE_IS_DECLARED
typedef struct YYLTYPE YYLTYPE;
struct YYLTYPE
{
  int first_line;
  int first_column;
  int last_line;
  int last_column;
};
# define YYLTYPE_IS_DECLARED 1
# define YYLTYPE_IS_TRIVIAL 1
#endif



int yyparse (void *scanner, Compiler* compiler, CParseFile* parseFile);

#endif /* !YY_YY_PARSER_PARSER_HPP_INCLUDED  */

/* Copy the second part of user declarations.  */



#ifdef short
# undef short
#endif

#ifdef YYTYPE_UINT8
typedef YYTYPE_UINT8 yytype_uint8;
#else
typedef unsigned char yytype_uint8;
#endif

#ifdef YYTYPE_INT8
typedef YYTYPE_INT8 yytype_int8;
#else
typedef signed char yytype_int8;
#endif

#ifdef YYTYPE_UINT16
typedef YYTYPE_UINT16 yytype_uint16;
#else
typedef unsigned short int yytype_uint16;
#endif

#ifdef YYTYPE_INT16
typedef YYTYPE_INT16 yytype_int16;
#else
typedef short int yytype_int16;
#endif

#ifndef YYSIZE_T
# ifdef __SIZE_TYPE__
#  define YYSIZE_T __SIZE_TYPE__
# elif defined size_t
#  define YYSIZE_T size_t
# elif ! defined YYSIZE_T
#  include <stddef.h> /* INFRINGES ON USER NAME SPACE */
#  define YYSIZE_T size_t
# else
#  define YYSIZE_T unsigned int
# endif
#endif

#define YYSIZE_MAXIMUM ((YYSIZE_T) -1)

#ifndef YY_
# if defined YYENABLE_NLS && YYENABLE_NLS
#  if ENABLE_NLS
#   include <libintl.h> /* INFRINGES ON USER NAME SPACE */
#   define YY_(Msgid) dgettext ("bison-runtime", Msgid)
#  endif
# endif
# ifndef YY_
#  define YY_(Msgid) Msgid
# endif
#endif

#ifndef YY_ATTRIBUTE
# if (defined __GNUC__                                               \
      && (2 < __GNUC__ || (__GNUC__ == 2 && 96 <= __GNUC_MINOR__)))  \
     || defined __SUNPRO_C && 0x5110 <= __SUNPRO_C
#  define YY_ATTRIBUTE(Spec) __attribute__(Spec)
# else
#  define YY_ATTRIBUTE(Spec) /* empty */
# endif
#endif

#ifndef YY_ATTRIBUTE_PURE
# define YY_ATTRIBUTE_PURE   YY_ATTRIBUTE ((__pure__))
#endif

#ifndef YY_ATTRIBUTE_UNUSED
# define YY_ATTRIBUTE_UNUSED YY_ATTRIBUTE ((__unused__))
#endif

#if !defined _Noreturn \
     && (!defined __STDC_VERSION__ || __STDC_VERSION__ < 201112)
# if defined _MSC_VER && 1200 <= _MSC_VER
#  define _Noreturn __declspec (noreturn)
# else
#  define _Noreturn YY_ATTRIBUTE ((__noreturn__))
# endif
#endif

/* Suppress unused-variable warnings by "using" E.  */
#if ! defined lint || defined __GNUC__
# define YYUSE(E) ((void) (E))
#else
# define YYUSE(E) /* empty */
#endif

#if defined __GNUC__ && 407 <= __GNUC__ * 100 + __GNUC_MINOR__
/* Suppress an incorrect diagnostic about yylval being uninitialized.  */
# define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN \
    _Pragma ("GCC diagnostic push") \
    _Pragma ("GCC diagnostic ignored \"-Wuninitialized\"")\
    _Pragma ("GCC diagnostic ignored \"-Wmaybe-uninitialized\"")
# define YY_IGNORE_MAYBE_UNINITIALIZED_END \
    _Pragma ("GCC diagnostic pop")
#else
# define YY_INITIAL_VALUE(Value) Value
#endif
#ifndef YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
# define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
# define YY_IGNORE_MAYBE_UNINITIALIZED_END
#endif
#ifndef YY_INITIAL_VALUE
# define YY_INITIAL_VALUE(Value) /* Nothing. */
#endif


#if ! defined yyoverflow || YYERROR_VERBOSE

/* The parser invokes alloca or malloc; define the necessary symbols.  */

# ifdef YYSTACK_USE_ALLOCA
#  if YYSTACK_USE_ALLOCA
#   ifdef __GNUC__
#    define YYSTACK_ALLOC __builtin_alloca
#   elif defined __BUILTIN_VA_ARG_INCR
#    include <alloca.h> /* INFRINGES ON USER NAME SPACE */
#   elif defined _AIX
#    define YYSTACK_ALLOC __alloca
#   elif defined _MSC_VER
#    include <malloc.h> /* INFRINGES ON USER NAME SPACE */
#    define alloca _alloca
#   else
#    define YYSTACK_ALLOC alloca
#    if ! defined _ALLOCA_H && ! defined EXIT_SUCCESS
#     include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
      /* Use EXIT_SUCCESS as a witness for stdlib.h.  */
#     ifndef EXIT_SUCCESS
#      define EXIT_SUCCESS 0
#     endif
#    endif
#   endif
#  endif
# endif

# ifdef YYSTACK_ALLOC
   /* Pacify GCC's 'empty if-body' warning.  */
#  define YYSTACK_FREE(Ptr) do { /* empty */; } while (0)
#  ifndef YYSTACK_ALLOC_MAXIMUM
    /* The OS might guarantee only one guard page at the bottom of the stack,
       and a page size can be as small as 4096 bytes.  So we cannot safely
       invoke alloca (N) if N exceeds 4096.  Use a slightly smaller number
       to allow for a few compiler-allocated temporary stack slots.  */
#   define YYSTACK_ALLOC_MAXIMUM 4032 /* reasonable circa 2006 */
#  endif
# else
#  define YYSTACK_ALLOC YYMALLOC
#  define YYSTACK_FREE YYFREE
#  ifndef YYSTACK_ALLOC_MAXIMUM
#   define YYSTACK_ALLOC_MAXIMUM YYSIZE_MAXIMUM
#  endif
#  if (defined __cplusplus && ! defined EXIT_SUCCESS \
       && ! ((defined YYMALLOC || defined malloc) \
             && (defined YYFREE || defined free)))
#   include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
#   ifndef EXIT_SUCCESS
#    define EXIT_SUCCESS 0
#   endif
#  endif
#  ifndef YYMALLOC
#   define YYMALLOC malloc
#   if ! defined malloc && ! defined EXIT_SUCCESS
void *malloc (YYSIZE_T); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
#  ifndef YYFREE
#   define YYFREE free
#   if ! defined free && ! defined EXIT_SUCCESS
void free (void *); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
# endif
#endif /* ! defined yyoverflow || YYERROR_VERBOSE */


#if (! defined yyoverflow \
     && (! defined __cplusplus \
         || (defined YYLTYPE_IS_TRIVIAL && YYLTYPE_IS_TRIVIAL \
             && defined YYSTYPE_IS_TRIVIAL && YYSTYPE_IS_TRIVIAL)))

/* A type that is properly aligned for any stack member.  */
union yyalloc
{
  yytype_int16 yyss_alloc;
  YYSTYPE yyvs_alloc;
  YYLTYPE yyls_alloc;
};

/* The size of the maximum gap between one aligned stack and the next.  */
# define YYSTACK_GAP_MAXIMUM (sizeof (union yyalloc) - 1)

/* The size of an array large to enough to hold all stacks, each with
   N elements.  */
# define YYSTACK_BYTES(N) \
     ((N) * (sizeof (yytype_int16) + sizeof (YYSTYPE) + sizeof (YYLTYPE)) \
      + 2 * YYSTACK_GAP_MAXIMUM)

# define YYCOPY_NEEDED 1

/* Relocate STACK from its old location to the new one.  The
   local variables YYSIZE and YYSTACKSIZE give the old and new number of
   elements in the stack, and YYPTR gives the new location of the
   stack.  Advance YYPTR to a properly aligned location for the next
   stack.  */
# define YYSTACK_RELOCATE(Stack_alloc, Stack)                           \
    do                                                                  \
      {                                                                 \
        YYSIZE_T yynewbytes;                                            \
        YYCOPY (&yyptr->Stack_alloc, Stack, yysize);                    \
        Stack = &yyptr->Stack_alloc;                                    \
        yynewbytes = yystacksize * sizeof (*Stack) + YYSTACK_GAP_MAXIMUM; \
        yyptr += yynewbytes / sizeof (*yyptr);                          \
      }                                                                 \
    while (0)

#endif

#if defined YYCOPY_NEEDED && YYCOPY_NEEDED
/* Copy COUNT objects from SRC to DST.  The source and destination do
   not overlap.  */
# ifndef YYCOPY
#  if defined __GNUC__ && 1 < __GNUC__
#   define YYCOPY(Dst, Src, Count) \
      __builtin_memcpy (Dst, Src, (Count) * sizeof (*(Src)))
#  else
#   define YYCOPY(Dst, Src, Count)              \
      do                                        \
        {                                       \
          YYSIZE_T yyi;                         \
          for (yyi = 0; yyi < (Count); yyi++)   \
            (Dst)[yyi] = (Src)[yyi];            \
        }                                       \
      while (0)
#  endif
# endif
#endif /* !YYCOPY_NEEDED */

/* YYFINAL -- State number of the termination state.  */
#define YYFINAL  131
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   1800

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  102
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  80
/* YYNRULES -- Number of rules.  */
#define YYNRULES  254
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  453

/* YYTRANSLATE[YYX] -- Symbol number corresponding to YYX as returned
   by yylex, with out-of-bounds checking.  */
#define YYUNDEFTOK  2
#define YYMAXUTOK   356

#define YYTRANSLATE(YYX)                                                \
  ((unsigned int) (YYX) <= YYMAXUTOK ? yytranslate[YYX] : YYUNDEFTOK)

/* YYTRANSLATE[TOKEN-NUM] -- Symbol number corresponding to TOKEN-NUM
   as returned by yylex, without out-of-bounds checking.  */
static const yytype_uint8 yytranslate[] =
{
       0,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     1,     2,     3,     4,
       5,     6,     7,     8,     9,    10,    11,    12,    13,    14,
      15,    16,    17,    18,    19,    20,    21,    22,    23,    24,
      25,    26,    27,    28,    29,    30,    31,    32,    33,    34,
      35,    36,    37,    38,    39,    40,    41,    42,    43,    44,
      45,    46,    47,    48,    49,    50,    51,    52,    53,    54,
      55,    56,    57,    58,    59,    60,    61,    62,    63,    64,
      65,    66,    67,    68,    69,    70,    71,    72,    73,    74,
      75,    76,    77,    78,    79,    80,    81,    82,    83,    84,
      85,    86,    87,    88,    89,    90,    91,    92,    93,    94,
      95,    96,    97,    98,    99,   100,   101
};

#if YYDEBUG
  /* YYRLINE[YYN] -- Source line where rule number YYN was defined.  */
static const yytype_uint16 yyrline[] =
{
       0,   121,   121,   124,   125,   128,   129,   130,   131,   132,
     133,   134,   135,   136,   137,   138,   139,   140,   141,   142,
     143,   146,   147,   150,   151,   154,   155,   158,   159,   162,
     163,   166,   167,   170,   171,   174,   175,   176,   179,   180,
     183,   184,   187,   190,   191,   192,   193,   194,   195,   196,
     197,   200,   203,   204,   205,   208,   209,   212,   218,   223,
     228,   235,   236,   237,   238,   241,   242,   245,   246,   249,
     250,   253,   254,   257,   258,   259,   260,   263,   264,   265,
     266,   267,   270,   273,   274,   277,   280,   283,   286,   287,
     288,   291,   292,   295,   296,   297,   298,   299,   300,   301,
     302,   303,   304,   307,   308,   309,   312,   313,   314,   315,
     316,   317,   318,   319,   320,   323,   324,   325,   326,   327,
     328,   329,   330,   331,   332,   333,   334,   337,   338,   339,
     340,   341,   342,   345,   346,   349,   352,   353,   356,   357,
     360,   361,   364,   365,   366,   367,   368,   371,   372,   375,
     376,   379,   380,   381,   382,   383,   384,   385,   386,   387,
     388,   389,   390,   391,   394,   395,   396,   397,   398,   399,
     400,   401,   402,   405,   406,   407,   408,   409,   410,   411,
     414,   415,   418,   419,   422,   423,   424,   425,   426,   427,
     430,   431,   432,   435,   438,   439,   442,   445,   448,   449,
     450,   451,   454,   457,   458,   461,   462,   465,   466,   467,
     468,   471,   474,   477,   478,   479,   482,   483,   484,   485,
     486,   489,   490,   493,   494,   495,   496,   497,   498,   499,
     500,   501,   504,   507,   508,   511,   512,   513,   516,   517,
     520,   521,   524,   525,   528,   531,   532,   535,   536,   537,
     538,   541,   542,   545,   546
};
#endif

#if YYDEBUG || YYERROR_VERBOSE || 1
/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "$end", "error", "$undefined", "TIDENTIFIER", "TINTEGER", "TDOUBLE",
  "TSTRING", "TCHAR", "TCBLOCK", "TCFUNCTION", "TCDEFINE", "TCSTRUCT",
  "TCINCLUDE", "TCVAR", "TCTYPEDEF", "TQUOTEDIDENTIFIER", "TCEQ", "TCNE",
  "TCLT", "TCLE", "TCGT", "TCGE", "TEQUAL", "TEND", "TLPAREN", "TRPAREN",
  "TLBRACE", "TRBRACE", "TCOMMA", "TCOLON", "TQUOTE", "TPLUS", "TMINUS",
  "TMUL", "TDIV", "TTRUE", "TFALSE", "TAS", "TVOID", "TIF", "TELSE",
  "TTHROW", "TCATCH", "TFOR", "TTO", "TWHILE", "TPLUSPLUS", "TMINUSMINUS",
  "TPLUSEQUAL", "TMINUSEQUAL", "TLBRACKET", "TRBRACKET", "TEXCLAIM",
  "TDOT", "TTHIS", "TINCLUDE", "TAND", "TOR", "TCOPY", "TDESTROY", "TMOD",
  "THASH", "TCPEQ", "TCPNE", "TMULEQUAL", "TDIVEQUAL", "TISEMPTY",
  "TISVALID", "TGETVALUE", "TQUESTION", "TEMPTY", "TVALID",
  "TQUESTIONCOLON", "TQUESTIONDOT", "TPARENT", "TSTACK", "THEAP", "TWEAK",
  "TLOCAL", "TTYPEI32", "TTYPEU32", "TTYPEF32", "TTYPEI64", "TTYPEU64",
  "TTYPEF64", "TTYPECHAR", "TTYPEBOOL", "TTYPEPTR", "TINVALID",
  "TCOLONEQUAL", "THEAPPARENT", "THEAPTHIS", "TIFVALID", "TELSEEMPTY",
  "TTOREVERSE", "TENUM", "TSWITCH", "TDEFAULT", "TPACKAGE", "TIMPORT",
  "TUNDERSCORE", "TNULLPTR", "$accept", "program", "stmts", "stmt",
  "cblock", "cdefine", "cstruct", "cfunction", "cinclude", "ctypedef",
  "cvar", "import_namespaces", "import_namespace", "namespace", "block",
  "var_decl", "enum_decl", "enum_args", "enum_arg", "func_decl",
  "func_type_name", "copy", "catch", "destroy", "func_block", "func_args",
  "func_arg", "implement", "implement_args", "implement_arg",
  "interface_decl", "interface_block", "interface_args", "interface_arg",
  "expr", "expr_and", "expr_comp", "expr_math", "expr_var", "for_expr",
  "while_expr", "switch_expr", "switch_clauses", "switch_clause",
  "if_expr", "ifValue_vars", "ifValue_var", "var_right", "const", "assign",
  "assign_tuple", "assign_tuple_arg", "assign_tuple_type", "assign_type",
  "tuple", "tuple_args", "array", "hash", "hash_args", "hash_arg",
  "end_optional", "end_star", "array_args", "return_type_quote",
  "arg_type_quote", "arg_type", "arg_mode", "return_type", "value_type",
  "func_type", "func_arg_type", "func_arg_type_list",
  "temp_block_optional", "namespace_hash", "namespace_dot",
  "namespace_ident", "namespace_last", "temp_option_optional",
  "temp_block", "temp_args", YY_NULLPTR
};
#endif

# ifdef YYPRINT
/* YYTOKNUM[NUM] -- (External) token number corresponding to the
   (internal) symbol number NUM (which must be that of a token).  */
static const yytype_uint16 yytoknum[] =
{
       0,   256,   257,   258,   259,   260,   261,   262,   263,   264,
     265,   266,   267,   268,   269,   270,   271,   272,   273,   274,
     275,   276,   277,   278,   279,   280,   281,   282,   283,   284,
     285,   286,   287,   288,   289,   290,   291,   292,   293,   294,
     295,   296,   297,   298,   299,   300,   301,   302,   303,   304,
     305,   306,   307,   308,   309,   310,   311,   312,   313,   314,
     315,   316,   317,   318,   319,   320,   321,   322,   323,   324,
     325,   326,   327,   328,   329,   330,   331,   332,   333,   334,
     335,   336,   337,   338,   339,   340,   341,   342,   343,   344,
     345,   346,   347,   348,   349,   350,   351,   352,   353,   354,
     355,   356
};
# endif

#define YYPACT_NINF -333

#define yypact_value_is_default(Yystate) \
  (!!((Yystate) == (-333)))

#define YYTABLE_NINF -195

#define yytable_value_is_error(Yytable_value) \
  0

  /* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
     STATE-NUM.  */
static const yytype_int16 yypact[] =
{
     732,  -333,    19,  -333,  -333,  -333,  -333,  -333,  -333,  -333,
    -333,  -333,  -333,   -26,  1247,    12,  1538,  -333,  -333,  -333,
    1325,    64,   101,  1325,    12,  1538,  -333,   106,  1538,   120,
     115,   129,   137,   151,   174,  -333,  1538,  1538,  1538,  1538,
    -333,  -333,    70,   167,  1403,   227,    12,  -333,  -333,   238,
     220,  -333,   241,   243,   249,   252,   250,   251,  -333,  -333,
    -333,     8,  -333,  -333,  -333,   148,   124,   278,  -333,  -333,
    -333,  -333,  -333,  -333,  -333,  -333,  -333,  -333,  -333,  -333,
    1700,  1674,  -333,   426,    25,  -333,  -333,    -2,  1325,   244,
     242,    42,    57,    50,  -333,   253,    12,  1325,  -333,   -26,
    1325,  -333,   246,   191,  1325,   240,   246,  1325,   191,  -333,
     191,   -26,  1325,  1325,  1325,  -333,  1325,   191,   191,   191,
     191,    39,  -333,   154,  -333,   254,    12,   257,  -333,    71,
     277,  -333,   630,  -333,  -333,  -333,  -333,  -333,  -333,   208,
     227,   141,   244,   226,  -333,  1481,  1481,  1481,  1481,  1481,
    1481,  1481,  1481,  1481,  1481,  1481,  1481,  1481,  1481,  1481,
    1700,  -333,  -333,  1481,  1481,  1325,  1583,  1481,  1481,  1538,
    1538,  -333,  -333,  -333,  -333,  -333,  -333,  -333,  -333,  -333,
    -333,  -333,  -333,  -333,  -333,    55,  -333,  -333,  1700,  -333,
    -333,  -333,   528,   231,   232,   233,  -333,  -333,  -333,  1325,
    1628,  1325,  1673,  1481,  -333,   263,    37,  -333,   833,   256,
    1538,   268,  1325,  -333,  -333,    44,   270,  -333,   272,   273,
     275,   280,  1325,    70,   210,    12,  1090,    12,   303,  -333,
     281,   146,  -333,   258,  -333,  -333,  1012,   169,  1444,   265,
     246,   141,  -333,  -333,  -333,   104,   104,   104,   104,   104,
     104,    88,    88,   269,   269,  -333,   104,   104,  -333,  -333,
    -333,   261,    19,  -333,  -333,  -333,  -333,  -333,   260,    28,
     311,    97,    59,   313,  -333,  -333,    23,  -333,  -333,  -333,
    -333,   266,    -2,  -333,    57,  -333,   293,  1325,  1169,   296,
    1325,   173,     3,  -333,   -13,  1169,   282,  1325,   116,  -333,
    -333,  -333,  -333,  -333,  -333,  -333,   246,   329,   246,   184,
      12,  -333,  1090,  -333,   227,   277,   246,   277,  -333,   321,
    -333,   150,  -333,  -333,  -333,   202,  -333,  -333,  -333,  -333,
    -333,   246,   288,   265,   265,   246,   314,   426,    25,  -333,
    1700,  1700,  -333,   195,  -333,   -26,  -333,  -333,  -333,  -333,
     260,  -333,  1700,  -333,  -333,  -333,  -333,  -333,  -333,  1325,
    -333,  -333,  -333,  -333,  -333,  1325,  1325,  -333,  1325,  -333,
    -333,   244,   140,  -333,  -333,   306,   171,  -333,  -333,  -333,
     320,  1090,   246,    12,   258,  -333,  -333,  -333,  -333,   932,
     324,  1012,  -333,   246,   294,   288,   288,   265,   528,  -333,
    -333,   528,  -333,  -333,  1444,    28,  -333,  -333,  -333,   246,
     246,  -333,   322,   116,  -333,   116,   352,   329,   333,   329,
    -333,  -333,   332,  -333,  1012,  -333,  -333,  -333,   246,  -333,
     294,   294,   288,  -333,  -333,  -333,  -333,  -333,  -333,  -333,
    -333,  -333,  -333,  -333,  -333,  -333,  -333,  -333,  -333,  -333,
    -333,   294,  -333
};

  /* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
     Performed when YYTABLE does not specify something else to do.  Zero
     means the default is an error.  */
static const yytype_uint8 yydefact[] =
{
       0,    20,    61,   164,   165,   168,   169,    22,    28,    24,
      26,    30,    32,    63,     0,   203,     0,   166,   167,   102,
       0,     0,     0,     0,   203,     0,   159,     0,     0,     0,
       0,     0,     0,     0,     0,   158,     0,     0,     0,     0,
     160,   161,     0,     0,     0,     0,   203,   171,   170,     0,
       2,     3,    11,    12,    13,    14,    15,    16,     6,     9,
       7,   157,     8,    10,    97,   105,   114,   126,    94,    96,
      95,    93,   132,   163,    43,    98,    99,   100,   190,   192,
     216,   216,   191,     0,     0,    62,    64,    61,     0,   157,
       0,   105,   126,     0,   180,     0,   205,     0,   204,    61,
       0,   162,     0,   126,     0,     0,     0,     0,   120,    17,
     125,   238,     0,     0,     0,   172,     0,   121,   123,   124,
     122,    61,   150,     0,   148,     0,   203,     0,    41,     0,
       0,     1,     0,    21,    23,    25,    27,    29,    31,   203,
       0,   152,     0,    82,    83,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     216,    44,    45,     0,     0,     0,     0,     0,     0,     0,
       0,   218,   219,   220,   217,   223,   224,   225,   226,   227,
     228,   229,   230,   231,   212,     0,   213,   215,   216,   251,
     173,   174,     0,   184,   186,   185,   182,   152,   151,     0,
       0,     0,     0,     0,   206,     0,   203,   198,     0,   142,
       0,     0,     0,   135,   207,   203,     0,   239,     0,     0,
       0,     0,     0,     0,   145,   203,     0,   203,     0,    18,
      41,   203,    37,    39,     4,    72,     0,   238,   216,    67,
       0,     0,    84,   103,   104,   106,   107,   110,   111,   112,
     113,   115,   116,   117,   118,   119,   108,   109,   127,    46,
      47,     0,    61,   128,    48,    49,   129,   130,   246,   235,
       0,   247,     0,   242,   241,   253,     0,   175,   187,   189,
     188,     0,    61,   179,     0,   181,   195,     0,     0,     0,
     204,     0,     0,   101,     0,     0,     0,   204,    91,    86,
     153,   154,   155,   156,   149,   147,     0,     0,     0,     0,
     203,   138,     0,    40,     0,     0,     0,   204,    34,    80,
      79,   203,    73,    77,    81,   126,    78,    85,   222,   221,
     211,     0,    65,    67,    67,     0,   131,     0,     0,   244,
     216,   216,   236,     0,   245,   248,   214,   249,   246,   240,
       0,   243,   216,   252,   131,   183,   193,   202,   201,     0,
     197,   199,    42,   143,   144,     0,     0,   210,     0,   196,
     208,     0,     0,    88,   146,    55,   203,    54,   141,   140,
       0,   204,     0,   203,    38,    36,    19,    35,    33,     0,
       0,   204,    68,     0,    69,    65,    65,    67,     0,   176,
     177,     0,   234,   233,   216,     0,   250,   254,   200,     0,
       0,   209,     0,    91,    87,    91,     0,     0,     0,   204,
     137,   139,     0,    76,     0,    71,    74,    66,     0,    57,
      69,    69,    65,    50,   178,   232,   237,   133,   134,    92,
      89,    90,    56,    53,    51,    52,   136,    75,    70,    59,
      58,    69,    60
};

  /* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
    -333,  -333,   152,   -79,  -333,  -333,  -333,  -333,  -333,  -333,
    -333,  -333,   -67,   -29,   -89,  -333,  -333,  -333,  -163,  -229,
       1,  -332,  -288,  -304,   -83,  -333,  -309,  -333,  -333,   218,
    -212,  -333,  -333,  -156,   -11,   199,   -12,  1641,     0,  -333,
    -333,  -333,    52,   -16,    76,  -333,   149,     6,  -333,  -206,
    -333,   172,    87,   -65,  -333,  -333,  -333,  -333,  -333,  -267,
      20,   -81,  -333,  -223,   -28,   -70,  -333,   -33,  -333,  -333,
     -32,  -333,   138,  -333,   103,  -333,   105,  -333,    -5,  -333
};

  /* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int16 yydefgoto[] =
{
      -1,    49,    50,    51,    52,    53,    54,    55,    56,    57,
     319,   231,   232,   233,   379,    58,    59,   376,   377,    60,
      89,   394,   332,   429,   141,   321,   322,   142,   143,   144,
      62,   299,   372,   373,    63,    64,    65,    66,   103,    68,
      69,    70,   310,   311,    71,   123,   124,    72,    73,    74,
      93,    94,   196,    83,    75,    95,    76,    77,   206,   207,
      97,    98,   215,   240,    84,   329,   185,   330,   186,   187,
     342,   343,   216,   271,   272,   273,   274,   346,    85,   276
};

  /* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
     positive, shift that token.  If negative, reduce the rule whose
     number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_int16 yytable[] =
{
      67,    61,    91,    90,   190,   115,   197,   320,    86,   102,
     184,   189,   106,   209,    92,   204,   129,   213,   335,   192,
     193,   358,   101,   361,   323,   108,    81,   194,   110,   208,
     326,   365,   139,   127,   224,    96,   117,   118,   119,   120,
     229,    78,    20,   122,   107,   395,   396,    78,    79,    80,
      81,   352,   239,   234,    79,   191,   222,   340,   268,   241,
      96,    78,   348,   430,   431,   288,   130,    96,    79,   140,
    -194,    81,   295,   121,   353,   201,    91,    90,   202,   269,
     423,   366,   426,    67,    61,    13,   205,   195,   104,    90,
     258,    81,   408,   211,   160,    42,   214,   208,   145,   146,
     451,   218,   219,   220,   105,   221,   217,   199,    82,   432,
     200,   237,   109,   277,    82,   447,   270,   341,   275,    99,
     270,   155,   156,   111,   228,   290,   449,   450,    82,   169,
     170,    13,    67,    61,   297,   153,   154,   155,   156,   112,
     147,   148,   149,   150,   151,   152,   226,   452,   157,    81,
     317,   333,   334,   113,   261,   153,   154,   155,   156,   236,
     320,   114,   320,   413,   157,   414,   345,   208,   415,    96,
     125,   238,   263,    96,   315,   266,   267,   323,   389,   323,
     208,    80,   223,   326,   157,   326,   158,   159,   281,   439,
     283,   286,    67,    61,    96,   320,   132,   337,   116,   417,
     362,   294,   284,   363,   145,   146,   263,   359,    67,    61,
     208,   304,   323,   287,   368,   309,   263,   374,   326,   378,
     404,    81,   228,   405,   122,   324,   289,   386,   160,   381,
     128,    96,   217,   235,   338,   296,   325,    61,   131,   160,
     391,   199,   392,   132,   210,   307,   397,   312,   385,   133,
     387,   316,   199,   134,   443,   166,   445,   440,   399,   441,
     135,   136,   137,   169,   170,   138,   347,   198,   139,   212,
     402,   403,   208,   401,   169,   170,   357,   205,   225,   205,
     230,   203,   407,   227,   367,   384,   370,   140,   412,   278,
     279,   280,   287,   293,   298,   419,   292,   300,   301,   371,
     302,   382,   381,   306,   427,   303,   313,   331,   424,   400,
     314,   228,   336,   339,   344,   160,   350,   354,   356,   433,
     437,   438,   434,   360,   161,   162,   163,   164,   165,   157,
     380,   166,   375,   369,   388,   416,   398,    67,    61,   448,
     406,   390,   167,   168,   243,   244,   393,   420,   205,   425,
     169,   170,   238,   428,   409,   410,   442,   411,   444,   446,
     291,   242,   259,   260,   383,   421,   264,   265,   364,   355,
     382,   435,   305,   436,   285,   327,   351,   349,   324,     0,
     324,     0,     0,     0,     0,     0,     0,     0,     0,   325,
      61,   325,    61,     0,     0,     0,   418,     0,    67,    61,
       0,    67,    61,   422,     0,     0,     0,     0,     0,     0,
       0,     0,     0,   324,   371,     0,   371,     0,     0,     0,
       0,     0,     0,     0,   325,    61,    -5,     1,     0,     2,
       3,     4,     5,     6,     7,     8,     9,    10,    11,     0,
      12,    13,     0,     0,     0,     0,     0,     0,     0,    -5,
      14,    -5,    15,    -5,    -5,     0,    80,     0,    16,     0,
       0,    17,    18,     0,    19,    20,     0,    21,     0,    22,
       0,    23,     0,     0,     0,     0,    24,     0,    25,     0,
      26,    27,     0,     0,    28,     0,     0,    29,     0,     0,
       0,     0,    30,    31,    32,     0,    33,    34,     0,     0,
      35,    36,    37,    38,    39,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,    40,    41,    42,     0,
       0,    43,    44,     0,    45,    46,    47,    48,    -5,     1,
       0,     2,     3,     4,     5,     6,     7,     8,     9,    10,
      11,     0,    12,    13,     0,     0,     0,     0,     0,     0,
       0,    -5,    14,    -5,    15,    -5,    -5,     0,     0,     0,
      16,     0,     0,    17,    18,     0,    19,    20,     0,    21,
       0,    22,     0,    23,     0,     0,     0,     0,    24,     0,
      25,     0,    26,    27,     0,     0,    28,     0,     0,    29,
       0,     0,     0,     0,    30,    31,    32,     0,    33,    34,
       0,     0,    35,    36,    37,    38,    39,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,    40,    41,
      42,     0,     0,    43,    44,     0,    45,    46,    47,    48,
      -5,     1,     0,     2,     3,     4,     5,     6,     7,     8,
       9,    10,    11,     0,    12,    13,     0,     0,     0,     0,
       0,     0,     0,    -5,    14,     0,    15,    -5,     0,     0,
       0,     0,    16,     0,     0,    17,    18,     0,    19,    20,
       0,    21,     0,    22,     0,    23,     0,     0,     0,     0,
      24,     0,    25,     0,    26,    27,     0,     0,    28,     0,
       0,    29,     0,     0,     0,     0,    30,    31,    32,     0,
      33,    34,     0,     0,    35,    36,    37,    38,    39,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
      40,    41,    42,     0,     0,    43,    44,     0,    45,    46,
      47,    48,    -5,     1,     0,     2,     3,     4,     5,     6,
       7,     8,     9,    10,    11,     0,    12,    13,     0,     0,
       0,     0,     0,     0,     0,    -5,    14,     0,    15,     0,
       0,     0,     0,     0,    16,     0,     0,    17,    18,     0,
      19,    20,     0,    21,     0,    22,     0,    23,     0,     0,
       0,     0,    24,     0,    25,     0,    26,    27,     0,     0,
      28,     0,     0,    29,     0,     0,     0,     0,    30,    31,
      32,     0,    33,    34,     0,     0,    35,    36,    37,    38,
      39,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,    40,    41,    42,     0,     0,    43,    44,     0,
      45,    46,    47,    48,     1,     0,     2,     3,     4,     5,
       6,     7,     8,     9,    10,    11,     0,    12,    13,     0,
       0,     0,     0,     0,     0,     0,    -5,    14,     0,    15,
      -5,     0,     0,     0,     0,    16,     0,     0,    17,    18,
       0,    19,    20,     0,    21,     0,    22,     0,    23,     0,
       0,     0,     0,    24,     0,    25,     0,    26,    27,     0,
       0,    28,     0,     0,    29,     0,     0,     0,     0,    30,
      31,    32,     0,    33,    34,     0,     0,    35,    36,    37,
      38,    39,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,    40,    41,    42,     0,     0,    43,    44,
       0,    45,    46,    47,    48,     2,     3,     4,     5,     6,
       0,     0,     0,     0,     0,   318,     0,    13,     0,     0,
       0,     0,     0,     0,     0,    96,    14,     0,    15,     0,
       0,     0,     0,     0,    16,     0,     0,    17,    18,     0,
      19,    20,     0,    21,     0,    22,     0,    23,     0,     0,
       0,     0,    24,     0,    25,     0,    26,     0,     0,     0,
      28,     0,     0,    29,     0,     0,     0,     0,    30,    31,
      32,     0,    33,    34,     0,     0,    35,    36,    37,    38,
      39,     0,     0,     0,     0,     2,     3,     4,     5,     6,
       0,     0,    40,    41,    42,   318,     0,    13,    44,     0,
       0,     0,    47,    48,     0,     0,    14,     0,    15,     0,
       0,     0,     0,     0,    16,     0,     0,    17,    18,     0,
      19,    20,     0,    21,     0,    22,     0,    23,     0,     0,
       0,     0,    24,     0,    25,     0,    26,     0,     0,     0,
      28,     0,     0,    29,     0,     0,     0,     0,    30,    31,
      32,     0,    33,    34,     0,     0,    35,    36,    37,    38,
      39,     0,     0,    99,     3,     4,     5,     6,     0,     0,
       0,     0,    40,    41,    42,    13,     0,     0,    44,     0,
       0,     0,    47,    48,    88,     0,    15,     0,     0,     0,
       0,     0,    16,     0,     0,    17,    18,     0,    19,    20,
       0,    21,     0,    22,     0,    23,     0,     0,     0,     0,
      24,     0,    25,     0,    26,     0,     0,     0,    28,     0,
       0,     0,     0,     0,     0,     0,    30,    31,    32,     0,
      33,    34,     0,     0,    35,    36,    37,    38,    39,     0,
       0,     0,    99,     3,     4,     5,     6,     0,     0,     0,
      40,    41,    42,     0,    13,     0,    44,   308,     0,     0,
      47,    48,    96,    88,     0,    15,     0,     0,     0,     0,
       0,    16,     0,     0,    17,    18,     0,    19,    20,     0,
      21,     0,    22,     0,    23,     0,     0,     0,     0,    24,
       0,    25,     0,    26,     0,     0,     0,    28,     0,     0,
       0,     0,     0,     0,     0,    30,    31,    32,     0,    33,
      34,     0,     0,    35,    36,    37,    38,    39,     0,     0,
      87,     3,     4,     5,     6,     0,     0,     0,     0,    40,
      41,    42,    13,     0,     0,    44,     0,     0,     0,    47,
      48,    88,     0,    15,     0,     0,     0,     0,     0,    16,
       0,     0,    17,    18,     0,    19,    20,     0,    21,     0,
      22,     0,    23,     0,     0,     0,     0,    24,     0,    25,
       0,    26,     0,     0,     0,    28,     0,     0,     0,     0,
       0,     0,     0,    30,    31,    32,     0,    33,    34,     0,
       0,    35,    36,    37,    38,    39,     0,     0,    99,     3,
       4,     5,     6,     0,     0,     0,     0,    40,    41,    42,
      13,     0,     0,    44,     0,     0,     0,    47,    48,    88,
       0,    15,     0,     0,     0,     0,     0,    16,     0,     0,
      17,    18,     0,    19,    20,     0,    21,     0,    22,     0,
      23,     0,     0,     0,     0,    24,     0,    25,     0,    26,
       0,     0,     0,    28,     0,     0,     0,     0,     0,     0,
       0,    30,    31,    32,     0,    33,    34,     0,     0,    35,
      36,    37,    38,    39,     0,     0,    99,     3,     4,     5,
       6,     0,     0,     0,     0,    40,    41,    42,    13,     0,
       0,    44,     0,     0,     0,    47,    48,    88,     0,   126,
       0,     0,     0,     0,     0,    16,     0,     0,    17,    18,
       0,    19,    20,     0,    21,     0,    22,     0,    23,     0,
       0,     0,     0,    24,     0,    25,     0,    26,     0,     0,
       0,    28,     0,     0,     0,     0,     0,     0,     0,    30,
      31,    32,     0,    33,    34,     0,     0,    35,    36,    37,
      38,    39,   328,     0,    99,     3,     4,     5,     6,     0,
       0,     0,     0,    40,    41,    42,    13,     0,     0,    44,
       0,     0,     0,    47,    48,   100,     0,     0,     0,     0,
       0,     0,     0,    16,     0,     0,    17,    18,     0,   171,
     172,   173,   174,   175,   176,   177,   178,   179,   180,   181,
     182,   183,     0,    25,     0,    26,     0,     0,     0,    28,
       0,    99,     3,     4,     5,     6,     0,    30,    31,    32,
       0,    33,    34,    13,     0,    35,    36,    37,    38,    39,
       0,     0,   100,     0,     0,     0,     0,     0,     0,     0,
      16,    40,    41,    17,    18,     0,     0,     0,     0,     0,
       0,    47,    48,     0,     0,     0,   262,     3,     4,     5,
       6,     0,    26,     0,     0,     0,     0,     0,    13,     0,
       0,     0,     0,     0,    30,    31,    32,   100,    33,    34,
       0,     0,    35,     0,     0,    16,     0,     0,    17,    18,
       0,     0,     0,     0,     0,     0,     0,     0,    40,    41,
       0,   282,     3,     4,     5,     6,     0,    26,    47,    48,
       0,     0,     0,    13,     0,     0,     0,     0,     0,    30,
      31,    32,   100,    33,    34,     0,     0,    35,     0,     0,
      16,     0,     0,    17,    18,     0,     0,     0,     0,     0,
       0,     0,     0,    40,    41,     0,    87,     3,     4,     5,
       6,     0,    26,    47,    48,     0,     0,     0,    13,     0,
       0,     0,     0,     0,    30,    31,    32,   100,    33,    34,
       0,     0,    35,     0,     0,    16,     0,     0,    17,    18,
       0,     0,     0,     0,     0,     0,     0,     0,    40,    41,
       0,     0,     0,     0,   188,     0,     0,    26,    47,    48,
       0,     0,     0,     0,     0,     0,     0,     0,     0,    30,
      31,    32,     0,    33,    34,     0,     0,    35,     0,   171,
     172,   173,   174,   175,   176,   177,   178,   179,   180,   181,
     182,   183,     0,    40,    41,     0,     0,     0,     0,     0,
       0,     0,     0,    47,    48,   171,   172,   173,   174,   175,
     176,   177,   178,   179,   180,   181,   182,   183,   245,   246,
     247,   248,   249,   250,   251,   252,   253,   254,   255,   256,
     257
};

static const yytype_int16 yycheck[] =
{
       0,     0,    14,    14,    83,    33,    89,   236,    13,    20,
      80,    81,    23,   102,    14,    96,    45,   106,   241,    84,
      22,   288,    16,   290,   236,    25,    52,    29,    28,    26,
     236,    44,    24,    44,   123,    23,    36,    37,    38,    39,
     129,    22,    39,    42,    24,   333,   334,    22,    29,    30,
      52,    28,   141,   132,    29,    83,   121,    29,     3,   142,
      23,    22,     3,   395,   396,    28,    46,    23,    29,    61,
      28,    52,    28,     3,    51,    25,    88,    88,    28,    24,
     389,    94,   391,    83,    83,    15,    97,    89,    24,   100,
     160,    52,   359,   104,    37,    92,   107,    26,    56,    57,
     432,   112,   113,   114,     3,   116,   111,    50,    89,   397,
      53,   140,     6,   192,    89,   424,    61,    89,   188,     3,
      61,    33,    34,     3,    53,   206,   430,   431,    89,    72,
      73,    15,   132,   132,   215,    31,    32,    33,    34,    24,
      16,    17,    18,    19,    20,    21,   126,   451,    60,    52,
     231,   240,   241,    24,   165,    31,    32,    33,    34,   139,
     389,    24,   391,    23,    60,    25,    69,    26,    28,    23,
       3,    30,   166,    23,    28,   169,   170,   389,    28,   391,
      26,    30,    28,   389,    60,   391,    62,    63,   199,   412,
     201,   203,   192,   192,    23,   424,    23,   262,    24,    28,
      27,   212,   202,   292,    56,    57,   200,   288,   208,   208,
      26,   222,   424,    29,   295,   226,   210,   306,   424,   308,
      25,    52,    53,    28,   223,   236,   206,   316,    37,   310,
       3,    23,   237,    25,   262,   215,   236,   236,     0,    37,
     321,    50,   331,    23,    53,   225,   335,   227,   315,     8,
     317,   231,    50,    10,   417,    53,   419,   413,   337,   415,
      11,     9,    12,    72,    73,    14,   271,    25,    24,    29,
     340,   341,    26,   338,    72,    73,   287,   288,    24,   290,
       3,    28,   352,    26,   295,   314,   297,    61,   371,    58,
      58,    58,    29,    25,    24,   376,    40,    25,    25,   298,
      25,   312,   383,    93,   393,    25,     3,    42,   389,   337,
      29,    53,    51,    53,     3,    37,     3,    51,    25,   398,
     409,   410,   401,    27,    46,    47,    48,    49,    50,    60,
     310,    53,     3,    51,    13,    29,    22,   337,   337,   428,
     345,   321,    64,    65,   145,   146,    58,    27,   359,    25,
      72,    73,    30,    59,   365,   366,     4,   368,    25,    27,
     208,   143,   163,   164,   312,   381,   167,   168,   292,   282,
     381,   404,   223,   405,   202,   237,   273,   272,   389,    -1,
     391,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   389,
     389,   391,   391,    -1,    -1,    -1,   376,    -1,   398,   398,
      -1,   401,   401,   383,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,   424,   413,    -1,   415,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,   424,   424,     0,     1,    -1,     3,
       4,     5,     6,     7,     8,     9,    10,    11,    12,    -1,
      14,    15,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    23,
      24,    25,    26,    27,    28,    -1,    30,    -1,    32,    -1,
      -1,    35,    36,    -1,    38,    39,    -1,    41,    -1,    43,
      -1,    45,    -1,    -1,    -1,    -1,    50,    -1,    52,    -1,
      54,    55,    -1,    -1,    58,    -1,    -1,    61,    -1,    -1,
      -1,    -1,    66,    67,    68,    -1,    70,    71,    -1,    -1,
      74,    75,    76,    77,    78,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    90,    91,    92,    -1,
      -1,    95,    96,    -1,    98,    99,   100,   101,     0,     1,
      -1,     3,     4,     5,     6,     7,     8,     9,    10,    11,
      12,    -1,    14,    15,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    23,    24,    25,    26,    27,    28,    -1,    -1,    -1,
      32,    -1,    -1,    35,    36,    -1,    38,    39,    -1,    41,
      -1,    43,    -1,    45,    -1,    -1,    -1,    -1,    50,    -1,
      52,    -1,    54,    55,    -1,    -1,    58,    -1,    -1,    61,
      -1,    -1,    -1,    -1,    66,    67,    68,    -1,    70,    71,
      -1,    -1,    74,    75,    76,    77,    78,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    90,    91,
      92,    -1,    -1,    95,    96,    -1,    98,    99,   100,   101,
       0,     1,    -1,     3,     4,     5,     6,     7,     8,     9,
      10,    11,    12,    -1,    14,    15,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    23,    24,    -1,    26,    27,    -1,    -1,
      -1,    -1,    32,    -1,    -1,    35,    36,    -1,    38,    39,
      -1,    41,    -1,    43,    -1,    45,    -1,    -1,    -1,    -1,
      50,    -1,    52,    -1,    54,    55,    -1,    -1,    58,    -1,
      -1,    61,    -1,    -1,    -1,    -1,    66,    67,    68,    -1,
      70,    71,    -1,    -1,    74,    75,    76,    77,    78,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      90,    91,    92,    -1,    -1,    95,    96,    -1,    98,    99,
     100,   101,     0,     1,    -1,     3,     4,     5,     6,     7,
       8,     9,    10,    11,    12,    -1,    14,    15,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    23,    24,    -1,    26,    -1,
      -1,    -1,    -1,    -1,    32,    -1,    -1,    35,    36,    -1,
      38,    39,    -1,    41,    -1,    43,    -1,    45,    -1,    -1,
      -1,    -1,    50,    -1,    52,    -1,    54,    55,    -1,    -1,
      58,    -1,    -1,    61,    -1,    -1,    -1,    -1,    66,    67,
      68,    -1,    70,    71,    -1,    -1,    74,    75,    76,    77,
      78,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    90,    91,    92,    -1,    -1,    95,    96,    -1,
      98,    99,   100,   101,     1,    -1,     3,     4,     5,     6,
       7,     8,     9,    10,    11,    12,    -1,    14,    15,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    23,    24,    -1,    26,
      27,    -1,    -1,    -1,    -1,    32,    -1,    -1,    35,    36,
      -1,    38,    39,    -1,    41,    -1,    43,    -1,    45,    -1,
      -1,    -1,    -1,    50,    -1,    52,    -1,    54,    55,    -1,
      -1,    58,    -1,    -1,    61,    -1,    -1,    -1,    -1,    66,
      67,    68,    -1,    70,    71,    -1,    -1,    74,    75,    76,
      77,    78,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    90,    91,    92,    -1,    -1,    95,    96,
      -1,    98,    99,   100,   101,     3,     4,     5,     6,     7,
      -1,    -1,    -1,    -1,    -1,    13,    -1,    15,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    23,    24,    -1,    26,    -1,
      -1,    -1,    -1,    -1,    32,    -1,    -1,    35,    36,    -1,
      38,    39,    -1,    41,    -1,    43,    -1,    45,    -1,    -1,
      -1,    -1,    50,    -1,    52,    -1,    54,    -1,    -1,    -1,
      58,    -1,    -1,    61,    -1,    -1,    -1,    -1,    66,    67,
      68,    -1,    70,    71,    -1,    -1,    74,    75,    76,    77,
      78,    -1,    -1,    -1,    -1,     3,     4,     5,     6,     7,
      -1,    -1,    90,    91,    92,    13,    -1,    15,    96,    -1,
      -1,    -1,   100,   101,    -1,    -1,    24,    -1,    26,    -1,
      -1,    -1,    -1,    -1,    32,    -1,    -1,    35,    36,    -1,
      38,    39,    -1,    41,    -1,    43,    -1,    45,    -1,    -1,
      -1,    -1,    50,    -1,    52,    -1,    54,    -1,    -1,    -1,
      58,    -1,    -1,    61,    -1,    -1,    -1,    -1,    66,    67,
      68,    -1,    70,    71,    -1,    -1,    74,    75,    76,    77,
      78,    -1,    -1,     3,     4,     5,     6,     7,    -1,    -1,
      -1,    -1,    90,    91,    92,    15,    -1,    -1,    96,    -1,
      -1,    -1,   100,   101,    24,    -1,    26,    -1,    -1,    -1,
      -1,    -1,    32,    -1,    -1,    35,    36,    -1,    38,    39,
      -1,    41,    -1,    43,    -1,    45,    -1,    -1,    -1,    -1,
      50,    -1,    52,    -1,    54,    -1,    -1,    -1,    58,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    66,    67,    68,    -1,
      70,    71,    -1,    -1,    74,    75,    76,    77,    78,    -1,
      -1,    -1,     3,     4,     5,     6,     7,    -1,    -1,    -1,
      90,    91,    92,    -1,    15,    -1,    96,    97,    -1,    -1,
     100,   101,    23,    24,    -1,    26,    -1,    -1,    -1,    -1,
      -1,    32,    -1,    -1,    35,    36,    -1,    38,    39,    -1,
      41,    -1,    43,    -1,    45,    -1,    -1,    -1,    -1,    50,
      -1,    52,    -1,    54,    -1,    -1,    -1,    58,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    66,    67,    68,    -1,    70,
      71,    -1,    -1,    74,    75,    76,    77,    78,    -1,    -1,
       3,     4,     5,     6,     7,    -1,    -1,    -1,    -1,    90,
      91,    92,    15,    -1,    -1,    96,    -1,    -1,    -1,   100,
     101,    24,    -1,    26,    -1,    -1,    -1,    -1,    -1,    32,
      -1,    -1,    35,    36,    -1,    38,    39,    -1,    41,    -1,
      43,    -1,    45,    -1,    -1,    -1,    -1,    50,    -1,    52,
      -1,    54,    -1,    -1,    -1,    58,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    66,    67,    68,    -1,    70,    71,    -1,
      -1,    74,    75,    76,    77,    78,    -1,    -1,     3,     4,
       5,     6,     7,    -1,    -1,    -1,    -1,    90,    91,    92,
      15,    -1,    -1,    96,    -1,    -1,    -1,   100,   101,    24,
      -1,    26,    -1,    -1,    -1,    -1,    -1,    32,    -1,    -1,
      35,    36,    -1,    38,    39,    -1,    41,    -1,    43,    -1,
      45,    -1,    -1,    -1,    -1,    50,    -1,    52,    -1,    54,
      -1,    -1,    -1,    58,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    66,    67,    68,    -1,    70,    71,    -1,    -1,    74,
      75,    76,    77,    78,    -1,    -1,     3,     4,     5,     6,
       7,    -1,    -1,    -1,    -1,    90,    91,    92,    15,    -1,
      -1,    96,    -1,    -1,    -1,   100,   101,    24,    -1,    26,
      -1,    -1,    -1,    -1,    -1,    32,    -1,    -1,    35,    36,
      -1,    38,    39,    -1,    41,    -1,    43,    -1,    45,    -1,
      -1,    -1,    -1,    50,    -1,    52,    -1,    54,    -1,    -1,
      -1,    58,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    66,
      67,    68,    -1,    70,    71,    -1,    -1,    74,    75,    76,
      77,    78,    38,    -1,     3,     4,     5,     6,     7,    -1,
      -1,    -1,    -1,    90,    91,    92,    15,    -1,    -1,    96,
      -1,    -1,    -1,   100,   101,    24,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    32,    -1,    -1,    35,    36,    -1,    75,
      76,    77,    78,    79,    80,    81,    82,    83,    84,    85,
      86,    87,    -1,    52,    -1,    54,    -1,    -1,    -1,    58,
      -1,     3,     4,     5,     6,     7,    -1,    66,    67,    68,
      -1,    70,    71,    15,    -1,    74,    75,    76,    77,    78,
      -1,    -1,    24,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      32,    90,    91,    35,    36,    -1,    -1,    -1,    -1,    -1,
      -1,   100,   101,    -1,    -1,    -1,     3,     4,     5,     6,
       7,    -1,    54,    -1,    -1,    -1,    -1,    -1,    15,    -1,
      -1,    -1,    -1,    -1,    66,    67,    68,    24,    70,    71,
      -1,    -1,    74,    -1,    -1,    32,    -1,    -1,    35,    36,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    90,    91,
      -1,     3,     4,     5,     6,     7,    -1,    54,   100,   101,
      -1,    -1,    -1,    15,    -1,    -1,    -1,    -1,    -1,    66,
      67,    68,    24,    70,    71,    -1,    -1,    74,    -1,    -1,
      32,    -1,    -1,    35,    36,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    90,    91,    -1,     3,     4,     5,     6,
       7,    -1,    54,   100,   101,    -1,    -1,    -1,    15,    -1,
      -1,    -1,    -1,    -1,    66,    67,    68,    24,    70,    71,
      -1,    -1,    74,    -1,    -1,    32,    -1,    -1,    35,    36,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    90,    91,
      -1,    -1,    -1,    -1,    50,    -1,    -1,    54,   100,   101,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    66,
      67,    68,    -1,    70,    71,    -1,    -1,    74,    -1,    75,
      76,    77,    78,    79,    80,    81,    82,    83,    84,    85,
      86,    87,    -1,    90,    91,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,   100,   101,    75,    76,    77,    78,    79,
      80,    81,    82,    83,    84,    85,    86,    87,   147,   148,
     149,   150,   151,   152,   153,   154,   155,   156,   157,   158,
     159
};

  /* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
     symbol of state STATE-NUM.  */
static const yytype_uint8 yystos[] =
{
       0,     1,     3,     4,     5,     6,     7,     8,     9,    10,
      11,    12,    14,    15,    24,    26,    32,    35,    36,    38,
      39,    41,    43,    45,    50,    52,    54,    55,    58,    61,
      66,    67,    68,    70,    71,    74,    75,    76,    77,    78,
      90,    91,    92,    95,    96,    98,    99,   100,   101,   103,
     104,   105,   106,   107,   108,   109,   110,   111,   117,   118,
     121,   122,   132,   136,   137,   138,   139,   140,   141,   142,
     143,   146,   149,   150,   151,   156,   158,   159,    22,    29,
      30,    52,    89,   155,   166,   180,   180,     3,    24,   122,
     136,   138,   140,   152,   153,   157,    23,   162,   163,     3,
      24,   149,   136,   140,    24,     3,   136,   162,   140,     6,
     140,     3,    24,    24,    24,   166,    24,   140,   140,   140,
     140,     3,   122,   147,   148,     3,    26,   136,     3,   115,
     162,     0,    23,     8,    10,    11,     9,    12,    14,    24,
      61,   126,   129,   130,   131,    56,    57,    16,    17,    18,
      19,    20,    21,    31,    32,    33,    34,    60,    62,    63,
      37,    46,    47,    48,    49,    50,    53,    64,    65,    72,
      73,    75,    76,    77,    78,    79,    80,    81,    82,    83,
      84,    85,    86,    87,   167,   168,   170,   171,    50,   167,
     105,   166,   155,    22,    29,    89,   154,   126,    25,    50,
      53,    25,    28,    28,   163,   136,   160,   161,    26,   116,
      53,   136,    29,   116,   136,   164,   174,   180,   136,   136,
     136,   136,   155,    28,   116,    24,   162,    26,    53,   116,
       3,   113,   114,   115,   105,    25,   162,   115,    30,   116,
     165,   126,   131,   137,   137,   139,   139,   139,   139,   139,
     139,   139,   139,   139,   139,   139,   139,   139,   167,   137,
     137,   136,     3,   149,   137,   137,   149,   149,     3,    24,
      61,   175,   176,   177,   178,   167,   181,   105,    58,    58,
      58,   136,     3,   136,   140,   153,   138,    29,    28,   162,
     163,   104,    40,    25,   136,    28,   162,   163,    24,   133,
      25,    25,    25,    25,   136,   148,    93,   162,    97,   136,
     144,   145,   162,     3,    29,    28,   162,   163,    13,   112,
     121,   127,   128,   132,   136,   140,   151,   174,    38,   167,
     169,    42,   124,   116,   116,   165,    51,   155,   166,    53,
      29,    89,   172,   173,     3,    69,   179,   180,     3,   178,
       3,   176,    28,    51,    51,   154,    25,   136,   161,   163,
      27,   161,    27,   116,   146,    44,    94,   136,   163,    51,
     136,   122,   134,   135,   116,     3,   119,   120,   116,   116,
     162,   163,   136,   144,   115,   114,   116,   114,    13,    28,
     162,   163,   116,    58,   123,   124,   124,   116,    22,   105,
     166,   155,   167,   167,    25,    28,   180,   167,   161,   136,
     136,   136,   126,    23,    25,    28,    29,    28,   162,   163,
      27,   145,   162,   128,   163,    25,   128,   116,    59,   125,
     123,   123,   124,   105,   105,   169,   172,   116,   116,   165,
     135,   135,     4,   120,    25,   120,    27,   128,   116,   125,
     125,   123,   125
};

  /* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const yytype_uint8 yyr1[] =
{
       0,   102,   103,   104,   104,   105,   105,   105,   105,   105,
     105,   105,   105,   105,   105,   105,   105,   105,   105,   105,
     105,   106,   106,   107,   107,   108,   108,   109,   109,   110,
     110,   111,   111,   112,   112,   113,   113,   113,   114,   114,
     115,   115,   116,   117,   117,   117,   117,   117,   117,   117,
     117,   118,   119,   119,   119,   120,   120,   121,   121,   121,
     121,   122,   122,   122,   122,   123,   123,   124,   124,   125,
     125,   126,   126,   127,   127,   127,   127,   128,   128,   128,
     128,   128,   129,   130,   130,   131,   132,   133,   134,   134,
     134,   135,   135,   136,   136,   136,   136,   136,   136,   136,
     136,   136,   136,   137,   137,   137,   138,   138,   138,   138,
     138,   138,   138,   138,   138,   139,   139,   139,   139,   139,
     139,   139,   139,   139,   139,   139,   139,   140,   140,   140,
     140,   140,   140,   141,   141,   142,   143,   143,   144,   144,
     145,   145,   146,   146,   146,   146,   146,   147,   147,   148,
     148,   149,   149,   149,   149,   149,   149,   149,   149,   149,
     149,   149,   149,   149,   150,   150,   150,   150,   150,   150,
     150,   150,   150,   151,   151,   151,   151,   151,   151,   151,
     152,   152,   153,   153,   154,   154,   154,   154,   154,   154,
     155,   155,   155,   156,   157,   157,   158,   159,   160,   160,
     160,   160,   161,   162,   162,   163,   163,   164,   164,   164,
     164,   165,   166,   167,   167,   167,   168,   168,   168,   168,
     168,   169,   169,   170,   170,   170,   170,   170,   170,   170,
     170,   170,   171,   172,   172,   173,   173,   173,   174,   174,
     175,   175,   176,   176,   177,   178,   178,   179,   179,   179,
     179,   180,   180,   181,   181
};

  /* YYR2[YYN] -- Number of symbols on the right hand side of rule YYN.  */
static const yytype_uint8 yyr2[] =
{
       0,     2,     1,     1,     3,     0,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     2,     3,     5,
       1,     2,     1,     2,     1,     2,     1,     2,     1,     2,
       1,     2,     1,     2,     1,     3,     3,     1,     3,     1,
       3,     1,     3,     1,     2,     2,     3,     3,     3,     3,
       6,     7,     3,     3,     1,     1,     3,     6,     7,     7,
       8,     1,     2,     1,     2,     0,     2,     0,     2,     0,
       2,     5,     2,     1,     3,     4,     3,     1,     1,     1,
       1,     1,     1,     1,     2,     3,     4,     3,     1,     3,
       3,     0,     3,     1,     1,     1,     1,     1,     1,     1,
       1,     4,     1,     3,     3,     1,     3,     3,     3,     3,
       3,     3,     3,     3,     1,     3,     3,     3,     3,     3,
       2,     2,     2,     2,     2,     2,     1,     3,     3,     3,
       3,     4,     1,     7,     7,     3,     7,     6,     1,     3,
       2,     2,     3,     5,     5,     3,     5,     3,     1,     3,
       1,     3,     2,     4,     4,     4,     4,     1,     1,     1,
       1,     1,     2,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     2,     3,     3,     4,     5,     5,     6,     4,
       1,     3,     2,     4,     1,     1,     1,     2,     2,     2,
       1,     1,     1,     5,     1,     3,     5,     5,     1,     3,
       4,     3,     3,     0,     1,     1,     2,     1,     3,     4,
       3,     2,     2,     1,     3,     1,     0,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     5,     2,     2,     0,     1,     3,     0,     1,
       2,     1,     1,     2,     2,     2,     1,     0,     1,     1,
       2,     2,     4,     1,     3
};


#define yyerrok         (yyerrstatus = 0)
#define yyclearin       (yychar = YYEMPTY)
#define YYEMPTY         (-2)
#define YYEOF           0

#define YYACCEPT        goto yyacceptlab
#define YYABORT         goto yyabortlab
#define YYERROR         goto yyerrorlab


#define YYRECOVERING()  (!!yyerrstatus)

#define YYBACKUP(Token, Value)                                  \
do                                                              \
  if (yychar == YYEMPTY)                                        \
    {                                                           \
      yychar = (Token);                                         \
      yylval = (Value);                                         \
      YYPOPSTACK (yylen);                                       \
      yystate = *yyssp;                                         \
      goto yybackup;                                            \
    }                                                           \
  else                                                          \
    {                                                           \
      yyerror (&yylloc, scanner, compiler, parseFile, YY_("syntax error: cannot back up")); \
      YYERROR;                                                  \
    }                                                           \
while (0)

/* Error token number */
#define YYTERROR        1
#define YYERRCODE       256


/* YYLLOC_DEFAULT -- Set CURRENT to span from RHS[1] to RHS[N].
   If N is 0, then set CURRENT to the empty location which ends
   the previous symbol: RHS[0] (always defined).  */

#ifndef YYLLOC_DEFAULT
# define YYLLOC_DEFAULT(Current, Rhs, N)                                \
    do                                                                  \
      if (N)                                                            \
        {                                                               \
          (Current).first_line   = YYRHSLOC (Rhs, 1).first_line;        \
          (Current).first_column = YYRHSLOC (Rhs, 1).first_column;      \
          (Current).last_line    = YYRHSLOC (Rhs, N).last_line;         \
          (Current).last_column  = YYRHSLOC (Rhs, N).last_column;       \
        }                                                               \
      else                                                              \
        {                                                               \
          (Current).first_line   = (Current).last_line   =              \
            YYRHSLOC (Rhs, 0).last_line;                                \
          (Current).first_column = (Current).last_column =              \
            YYRHSLOC (Rhs, 0).last_column;                              \
        }                                                               \
    while (0)
#endif

#define YYRHSLOC(Rhs, K) ((Rhs)[K])


/* Enable debugging if requested.  */
#if YYDEBUG

# ifndef YYFPRINTF
#  include <stdio.h> /* INFRINGES ON USER NAME SPACE */
#  define YYFPRINTF fprintf
# endif

# define YYDPRINTF(Args)                        \
do {                                            \
  if (yydebug)                                  \
    YYFPRINTF Args;                             \
} while (0)


/* YY_LOCATION_PRINT -- Print the location on the stream.
   This macro was not mandated originally: define only if we know
   we won't break user code: when these are the locations we know.  */

#ifndef YY_LOCATION_PRINT
# if defined YYLTYPE_IS_TRIVIAL && YYLTYPE_IS_TRIVIAL

/* Print *YYLOCP on YYO.  Private, do not rely on its existence. */

YY_ATTRIBUTE_UNUSED
static unsigned
yy_location_print_ (FILE *yyo, YYLTYPE const * const yylocp)
{
  unsigned res = 0;
  int end_col = 0 != yylocp->last_column ? yylocp->last_column - 1 : 0;
  if (0 <= yylocp->first_line)
    {
      res += YYFPRINTF (yyo, "%d", yylocp->first_line);
      if (0 <= yylocp->first_column)
        res += YYFPRINTF (yyo, ".%d", yylocp->first_column);
    }
  if (0 <= yylocp->last_line)
    {
      if (yylocp->first_line < yylocp->last_line)
        {
          res += YYFPRINTF (yyo, "-%d", yylocp->last_line);
          if (0 <= end_col)
            res += YYFPRINTF (yyo, ".%d", end_col);
        }
      else if (0 <= end_col && yylocp->first_column < end_col)
        res += YYFPRINTF (yyo, "-%d", end_col);
    }
  return res;
 }

#  define YY_LOCATION_PRINT(File, Loc)          \
  yy_location_print_ (File, &(Loc))

# else
#  define YY_LOCATION_PRINT(File, Loc) ((void) 0)
# endif
#endif


# define YY_SYMBOL_PRINT(Title, Type, Value, Location)                    \
do {                                                                      \
  if (yydebug)                                                            \
    {                                                                     \
      YYFPRINTF (stderr, "%s ", Title);                                   \
      yy_symbol_print (stderr,                                            \
                  Type, Value, Location, scanner, compiler, parseFile); \
      YYFPRINTF (stderr, "\n");                                           \
    }                                                                     \
} while (0)


/*----------------------------------------.
| Print this symbol's value on YYOUTPUT.  |
`----------------------------------------*/

static void
yy_symbol_value_print (FILE *yyoutput, int yytype, YYSTYPE const * const yyvaluep, YYLTYPE const * const yylocationp, void *scanner, Compiler* compiler, CParseFile* parseFile)
{
  FILE *yyo = yyoutput;
  YYUSE (yyo);
  YYUSE (yylocationp);
  YYUSE (scanner);
  YYUSE (compiler);
  YYUSE (parseFile);
  if (!yyvaluep)
    return;
# ifdef YYPRINT
  if (yytype < YYNTOKENS)
    YYPRINT (yyoutput, yytoknum[yytype], *yyvaluep);
# endif
  YYUSE (yytype);
}


/*--------------------------------.
| Print this symbol on YYOUTPUT.  |
`--------------------------------*/

static void
yy_symbol_print (FILE *yyoutput, int yytype, YYSTYPE const * const yyvaluep, YYLTYPE const * const yylocationp, void *scanner, Compiler* compiler, CParseFile* parseFile)
{
  YYFPRINTF (yyoutput, "%s %s (",
             yytype < YYNTOKENS ? "token" : "nterm", yytname[yytype]);

  YY_LOCATION_PRINT (yyoutput, *yylocationp);
  YYFPRINTF (yyoutput, ": ");
  yy_symbol_value_print (yyoutput, yytype, yyvaluep, yylocationp, scanner, compiler, parseFile);
  YYFPRINTF (yyoutput, ")");
}

/*------------------------------------------------------------------.
| yy_stack_print -- Print the state stack from its BOTTOM up to its |
| TOP (included).                                                   |
`------------------------------------------------------------------*/

static void
yy_stack_print (yytype_int16 *yybottom, yytype_int16 *yytop)
{
  YYFPRINTF (stderr, "Stack now");
  for (; yybottom <= yytop; yybottom++)
    {
      int yybot = *yybottom;
      YYFPRINTF (stderr, " %d", yybot);
    }
  YYFPRINTF (stderr, "\n");
}

# define YY_STACK_PRINT(Bottom, Top)                            \
do {                                                            \
  if (yydebug)                                                  \
    yy_stack_print ((Bottom), (Top));                           \
} while (0)


/*------------------------------------------------.
| Report that the YYRULE is going to be reduced.  |
`------------------------------------------------*/

static void
yy_reduce_print (yytype_int16 *yyssp, YYSTYPE *yyvsp, YYLTYPE *yylsp, int yyrule, void *scanner, Compiler* compiler, CParseFile* parseFile)
{
  unsigned long int yylno = yyrline[yyrule];
  int yynrhs = yyr2[yyrule];
  int yyi;
  YYFPRINTF (stderr, "Reducing stack by rule %d (line %lu):\n",
             yyrule - 1, yylno);
  /* The symbols being reduced.  */
  for (yyi = 0; yyi < yynrhs; yyi++)
    {
      YYFPRINTF (stderr, "   $%d = ", yyi + 1);
      yy_symbol_print (stderr,
                       yystos[yyssp[yyi + 1 - yynrhs]],
                       &(yyvsp[(yyi + 1) - (yynrhs)])
                       , &(yylsp[(yyi + 1) - (yynrhs)])                       , scanner, compiler, parseFile);
      YYFPRINTF (stderr, "\n");
    }
}

# define YY_REDUCE_PRINT(Rule)          \
do {                                    \
  if (yydebug)                          \
    yy_reduce_print (yyssp, yyvsp, yylsp, Rule, scanner, compiler, parseFile); \
} while (0)

/* Nonzero means print parse trace.  It is left uninitialized so that
   multiple parsers can coexist.  */
int yydebug;
#else /* !YYDEBUG */
# define YYDPRINTF(Args)
# define YY_SYMBOL_PRINT(Title, Type, Value, Location)
# define YY_STACK_PRINT(Bottom, Top)
# define YY_REDUCE_PRINT(Rule)
#endif /* !YYDEBUG */


/* YYINITDEPTH -- initial size of the parser's stacks.  */
#ifndef YYINITDEPTH
# define YYINITDEPTH 200
#endif

/* YYMAXDEPTH -- maximum size the stacks can grow to (effective only
   if the built-in stack extension method is used).

   Do not make this value too large; the results are undefined if
   YYSTACK_ALLOC_MAXIMUM < YYSTACK_BYTES (YYMAXDEPTH)
   evaluated with infinite-precision integer arithmetic.  */

#ifndef YYMAXDEPTH
# define YYMAXDEPTH 10000
#endif


#if YYERROR_VERBOSE

# ifndef yystrlen
#  if defined __GLIBC__ && defined _STRING_H
#   define yystrlen strlen
#  else
/* Return the length of YYSTR.  */
static YYSIZE_T
yystrlen (const char *yystr)
{
  YYSIZE_T yylen;
  for (yylen = 0; yystr[yylen]; yylen++)
    continue;
  return yylen;
}
#  endif
# endif

# ifndef yystpcpy
#  if defined __GLIBC__ && defined _STRING_H && defined _GNU_SOURCE
#   define yystpcpy stpcpy
#  else
/* Copy YYSRC to YYDEST, returning the address of the terminating '\0' in
   YYDEST.  */
static char *
yystpcpy (char *yydest, const char *yysrc)
{
  char *yyd = yydest;
  const char *yys = yysrc;

  while ((*yyd++ = *yys++) != '\0')
    continue;

  return yyd - 1;
}
#  endif
# endif

# ifndef yytnamerr
/* Copy to YYRES the contents of YYSTR after stripping away unnecessary
   quotes and backslashes, so that it's suitable for yyerror.  The
   heuristic is that double-quoting is unnecessary unless the string
   contains an apostrophe, a comma, or backslash (other than
   backslash-backslash).  YYSTR is taken from yytname.  If YYRES is
   null, do not copy; instead, return the length of what the result
   would have been.  */
static YYSIZE_T
yytnamerr (char *yyres, const char *yystr)
{
  if (*yystr == '"')
    {
      YYSIZE_T yyn = 0;
      char const *yyp = yystr;

      for (;;)
        switch (*++yyp)
          {
          case '\'':
          case ',':
            goto do_not_strip_quotes;

          case '\\':
            if (*++yyp != '\\')
              goto do_not_strip_quotes;
            /* Fall through.  */
          default:
            if (yyres)
              yyres[yyn] = *yyp;
            yyn++;
            break;

          case '"':
            if (yyres)
              yyres[yyn] = '\0';
            return yyn;
          }
    do_not_strip_quotes: ;
    }

  if (! yyres)
    return yystrlen (yystr);

  return yystpcpy (yyres, yystr) - yyres;
}
# endif

/* Copy into *YYMSG, which is of size *YYMSG_ALLOC, an error message
   about the unexpected token YYTOKEN for the state stack whose top is
   YYSSP.

   Return 0 if *YYMSG was successfully written.  Return 1 if *YYMSG is
   not large enough to hold the message.  In that case, also set
   *YYMSG_ALLOC to the required number of bytes.  Return 2 if the
   required number of bytes is too large to store.  */
static int
yysyntax_error (YYSIZE_T *yymsg_alloc, char **yymsg,
                yytype_int16 *yyssp, int yytoken)
{
  YYSIZE_T yysize0 = yytnamerr (YY_NULLPTR, yytname[yytoken]);
  YYSIZE_T yysize = yysize0;
  enum { YYERROR_VERBOSE_ARGS_MAXIMUM = 5 };
  /* Internationalized format string. */
  const char *yyformat = YY_NULLPTR;
  /* Arguments of yyformat. */
  char const *yyarg[YYERROR_VERBOSE_ARGS_MAXIMUM];
  /* Number of reported tokens (one for the "unexpected", one per
     "expected"). */
  int yycount = 0;

  /* There are many possibilities here to consider:
     - If this state is a consistent state with a default action, then
       the only way this function was invoked is if the default action
       is an error action.  In that case, don't check for expected
       tokens because there are none.
     - The only way there can be no lookahead present (in yychar) is if
       this state is a consistent state with a default action.  Thus,
       detecting the absence of a lookahead is sufficient to determine
       that there is no unexpected or expected token to report.  In that
       case, just report a simple "syntax error".
     - Don't assume there isn't a lookahead just because this state is a
       consistent state with a default action.  There might have been a
       previous inconsistent state, consistent state with a non-default
       action, or user semantic action that manipulated yychar.
     - Of course, the expected token list depends on states to have
       correct lookahead information, and it depends on the parser not
       to perform extra reductions after fetching a lookahead from the
       scanner and before detecting a syntax error.  Thus, state merging
       (from LALR or IELR) and default reductions corrupt the expected
       token list.  However, the list is correct for canonical LR with
       one exception: it will still contain any token that will not be
       accepted due to an error action in a later state.
  */
  if (yytoken != YYEMPTY)
    {
      int yyn = yypact[*yyssp];
      yyarg[yycount++] = yytname[yytoken];
      if (!yypact_value_is_default (yyn))
        {
          /* Start YYX at -YYN if negative to avoid negative indexes in
             YYCHECK.  In other words, skip the first -YYN actions for
             this state because they are default actions.  */
          int yyxbegin = yyn < 0 ? -yyn : 0;
          /* Stay within bounds of both yycheck and yytname.  */
          int yychecklim = YYLAST - yyn + 1;
          int yyxend = yychecklim < YYNTOKENS ? yychecklim : YYNTOKENS;
          int yyx;

          for (yyx = yyxbegin; yyx < yyxend; ++yyx)
            if (yycheck[yyx + yyn] == yyx && yyx != YYTERROR
                && !yytable_value_is_error (yytable[yyx + yyn]))
              {
                if (yycount == YYERROR_VERBOSE_ARGS_MAXIMUM)
                  {
                    yycount = 1;
                    yysize = yysize0;
                    break;
                  }
                yyarg[yycount++] = yytname[yyx];
                {
                  YYSIZE_T yysize1 = yysize + yytnamerr (YY_NULLPTR, yytname[yyx]);
                  if (! (yysize <= yysize1
                         && yysize1 <= YYSTACK_ALLOC_MAXIMUM))
                    return 2;
                  yysize = yysize1;
                }
              }
        }
    }

  switch (yycount)
    {
# define YYCASE_(N, S)                      \
      case N:                               \
        yyformat = S;                       \
      break
      YYCASE_(0, YY_("syntax error"));
      YYCASE_(1, YY_("syntax error, unexpected %s"));
      YYCASE_(2, YY_("syntax error, unexpected %s, expecting %s"));
      YYCASE_(3, YY_("syntax error, unexpected %s, expecting %s or %s"));
      YYCASE_(4, YY_("syntax error, unexpected %s, expecting %s or %s or %s"));
      YYCASE_(5, YY_("syntax error, unexpected %s, expecting %s or %s or %s or %s"));
# undef YYCASE_
    }

  {
    YYSIZE_T yysize1 = yysize + yystrlen (yyformat);
    if (! (yysize <= yysize1 && yysize1 <= YYSTACK_ALLOC_MAXIMUM))
      return 2;
    yysize = yysize1;
  }

  if (*yymsg_alloc < yysize)
    {
      *yymsg_alloc = 2 * yysize;
      if (! (yysize <= *yymsg_alloc
             && *yymsg_alloc <= YYSTACK_ALLOC_MAXIMUM))
        *yymsg_alloc = YYSTACK_ALLOC_MAXIMUM;
      return 1;
    }

  /* Avoid sprintf, as that infringes on the user's name space.
     Don't have undefined behavior even if the translation
     produced a string with the wrong number of "%s"s.  */
  {
    char *yyp = *yymsg;
    int yyi = 0;
    while ((*yyp = *yyformat) != '\0')
      if (*yyp == '%' && yyformat[1] == 's' && yyi < yycount)
        {
          yyp += yytnamerr (yyp, yyarg[yyi++]);
          yyformat += 2;
        }
      else
        {
          yyp++;
          yyformat++;
        }
  }
  return 0;
}
#endif /* YYERROR_VERBOSE */

/*-----------------------------------------------.
| Release the memory associated to this symbol.  |
`-----------------------------------------------*/

static void
yydestruct (const char *yymsg, int yytype, YYSTYPE *yyvaluep, YYLTYPE *yylocationp, void *scanner, Compiler* compiler, CParseFile* parseFile)
{
  YYUSE (yyvaluep);
  YYUSE (yylocationp);
  YYUSE (scanner);
  YYUSE (compiler);
  YYUSE (parseFile);
  if (!yymsg)
    yymsg = "Deleting";
  YY_SYMBOL_PRINT (yymsg, yytype, yyvaluep, yylocationp);

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  YYUSE (yytype);
  YY_IGNORE_MAYBE_UNINITIALIZED_END
}




/*----------.
| yyparse.  |
`----------*/

int
yyparse (void *scanner, Compiler* compiler, CParseFile* parseFile)
{
/* The lookahead symbol.  */
int yychar;


/* The semantic value of the lookahead symbol.  */
/* Default value used for initialization, for pacifying older GCCs
   or non-GCC compilers.  */
YY_INITIAL_VALUE (static YYSTYPE yyval_default;)
YYSTYPE yylval YY_INITIAL_VALUE (= yyval_default);

/* Location data for the lookahead symbol.  */
static YYLTYPE yyloc_default
# if defined YYLTYPE_IS_TRIVIAL && YYLTYPE_IS_TRIVIAL
  = { 1, 1, 1, 1 }
# endif
;
YYLTYPE yylloc = yyloc_default;

    /* Number of syntax errors so far.  */
    int yynerrs;

    int yystate;
    /* Number of tokens to shift before error messages enabled.  */
    int yyerrstatus;

    /* The stacks and their tools:
       'yyss': related to states.
       'yyvs': related to semantic values.
       'yyls': related to locations.

       Refer to the stacks through separate pointers, to allow yyoverflow
       to reallocate them elsewhere.  */

    /* The state stack.  */
    yytype_int16 yyssa[YYINITDEPTH];
    yytype_int16 *yyss;
    yytype_int16 *yyssp;

    /* The semantic value stack.  */
    YYSTYPE yyvsa[YYINITDEPTH];
    YYSTYPE *yyvs;
    YYSTYPE *yyvsp;

    /* The location stack.  */
    YYLTYPE yylsa[YYINITDEPTH];
    YYLTYPE *yyls;
    YYLTYPE *yylsp;

    /* The locations where the error started and ended.  */
    YYLTYPE yyerror_range[3];

    YYSIZE_T yystacksize;

  int yyn;
  int yyresult;
  /* Lookahead token as an internal (translated) token number.  */
  int yytoken = 0;
  /* The variables used to return semantic value and location from the
     action routines.  */
  YYSTYPE yyval;
  YYLTYPE yyloc;

#if YYERROR_VERBOSE
  /* Buffer for error messages, and its allocated size.  */
  char yymsgbuf[128];
  char *yymsg = yymsgbuf;
  YYSIZE_T yymsg_alloc = sizeof yymsgbuf;
#endif

#define YYPOPSTACK(N)   (yyvsp -= (N), yyssp -= (N), yylsp -= (N))

  /* The number of symbols on the RHS of the reduced rule.
     Keep to zero when no symbol should be popped.  */
  int yylen = 0;

  yyssp = yyss = yyssa;
  yyvsp = yyvs = yyvsa;
  yylsp = yyls = yylsa;
  yystacksize = YYINITDEPTH;

  YYDPRINTF ((stderr, "Starting parse\n"));

  yystate = 0;
  yyerrstatus = 0;
  yynerrs = 0;
  yychar = YYEMPTY; /* Cause a token to be read.  */
  yylsp[0] = yylloc;
  goto yysetstate;

/*------------------------------------------------------------.
| yynewstate -- Push a new state, which is found in yystate.  |
`------------------------------------------------------------*/
 yynewstate:
  /* In all cases, when you get here, the value and location stacks
     have just been pushed.  So pushing a state here evens the stacks.  */
  yyssp++;

 yysetstate:
  *yyssp = yystate;

  if (yyss + yystacksize - 1 <= yyssp)
    {
      /* Get the current used size of the three stacks, in elements.  */
      YYSIZE_T yysize = yyssp - yyss + 1;

#ifdef yyoverflow
      {
        /* Give user a chance to reallocate the stack.  Use copies of
           these so that the &'s don't force the real ones into
           memory.  */
        YYSTYPE *yyvs1 = yyvs;
        yytype_int16 *yyss1 = yyss;
        YYLTYPE *yyls1 = yyls;

        /* Each stack pointer address is followed by the size of the
           data in use in that stack, in bytes.  This used to be a
           conditional around just the two extra args, but that might
           be undefined if yyoverflow is a macro.  */
        yyoverflow (YY_("memory exhausted"),
                    &yyss1, yysize * sizeof (*yyssp),
                    &yyvs1, yysize * sizeof (*yyvsp),
                    &yyls1, yysize * sizeof (*yylsp),
                    &yystacksize);

        yyls = yyls1;
        yyss = yyss1;
        yyvs = yyvs1;
      }
#else /* no yyoverflow */
# ifndef YYSTACK_RELOCATE
      goto yyexhaustedlab;
# else
      /* Extend the stack our own way.  */
      if (YYMAXDEPTH <= yystacksize)
        goto yyexhaustedlab;
      yystacksize *= 2;
      if (YYMAXDEPTH < yystacksize)
        yystacksize = YYMAXDEPTH;

      {
        yytype_int16 *yyss1 = yyss;
        union yyalloc *yyptr =
          (union yyalloc *) YYSTACK_ALLOC (YYSTACK_BYTES (yystacksize));
        if (! yyptr)
          goto yyexhaustedlab;
        YYSTACK_RELOCATE (yyss_alloc, yyss);
        YYSTACK_RELOCATE (yyvs_alloc, yyvs);
        YYSTACK_RELOCATE (yyls_alloc, yyls);
#  undef YYSTACK_RELOCATE
        if (yyss1 != yyssa)
          YYSTACK_FREE (yyss1);
      }
# endif
#endif /* no yyoverflow */

      yyssp = yyss + yysize - 1;
      yyvsp = yyvs + yysize - 1;
      yylsp = yyls + yysize - 1;

      YYDPRINTF ((stderr, "Stack size increased to %lu\n",
                  (unsigned long int) yystacksize));

      if (yyss + yystacksize - 1 <= yyssp)
        YYABORT;
    }

  YYDPRINTF ((stderr, "Entering state %d\n", yystate));

  if (yystate == YYFINAL)
    YYACCEPT;

  goto yybackup;

/*-----------.
| yybackup.  |
`-----------*/
yybackup:

  /* Do appropriate processing given the current state.  Read a
     lookahead token if we need one and don't already have one.  */

  /* First try to decide what to do without reference to lookahead token.  */
  yyn = yypact[yystate];
  if (yypact_value_is_default (yyn))
    goto yydefault;

  /* Not known => get a lookahead token if don't already have one.  */

  /* YYCHAR is either YYEMPTY or YYEOF or a valid lookahead symbol.  */
  if (yychar == YYEMPTY)
    {
      YYDPRINTF ((stderr, "Reading a token: "));
      yychar = yylex (&yylval, &yylloc, scanner);
    }

  if (yychar <= YYEOF)
    {
      yychar = yytoken = YYEOF;
      YYDPRINTF ((stderr, "Now at end of input.\n"));
    }
  else
    {
      yytoken = YYTRANSLATE (yychar);
      YY_SYMBOL_PRINT ("Next token is", yytoken, &yylval, &yylloc);
    }

  /* If the proper action on seeing token YYTOKEN is to reduce or to
     detect an error, take that action.  */
  yyn += yytoken;
  if (yyn < 0 || YYLAST < yyn || yycheck[yyn] != yytoken)
    goto yydefault;
  yyn = yytable[yyn];
  if (yyn <= 0)
    {
      if (yytable_value_is_error (yyn))
        goto yyerrlab;
      yyn = -yyn;
      goto yyreduce;
    }

  /* Count tokens shifted since error; after three, turn off error
     status.  */
  if (yyerrstatus)
    yyerrstatus--;

  /* Shift the lookahead token.  */
  YY_SYMBOL_PRINT ("Shifting", yytoken, &yylval, &yylloc);

  /* Discard the shifted token.  */
  yychar = YYEMPTY;

  yystate = yyn;
  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END
  *++yylsp = yylloc;
  goto yynewstate;


/*-----------------------------------------------------------.
| yydefault -- do the default action for the current state.  |
`-----------------------------------------------------------*/
yydefault:
  yyn = yydefact[yystate];
  if (yyn == 0)
    goto yyerrlab;
  goto yyreduce;


/*-----------------------------.
| yyreduce -- Do a reduction.  |
`-----------------------------*/
yyreduce:
  /* yyn is the number of a rule to reduce with.  */
  yylen = yyr2[yyn];

  /* If YYLEN is nonzero, implement the default value of the action:
     '$$ = $1'.

     Otherwise, the following line sets YYVAL to garbage.
     This behavior is undocumented and Bison
     users should not rely upon it.  Assigning to YYVAL
     unconditionally makes the parser a bit smaller, and it avoids a
     GCC warning that YYVAL may be used uninitialized.  */
  yyval = yyvsp[1-yylen];

  /* Default location.  */
  YYLLOC_DEFAULT (yyloc, (yylsp - yylen), yylen);
  YY_REDUCE_PRINT (yyn);
  switch (yyn)
    {
        case 2:

    { parseFile->block = std::shared_ptr<NBlock>((yyvsp[0].block)); }

    break;

  case 3:

    { (yyval.block) = new NBlock(LOC); if ((yyvsp[0].node)) (yyval.block)->statements.push_back(shared_ptr<NBase>((yyvsp[0].node))); }

    break;

  case 4:

    { if ((yyvsp[0].node)) (yyvsp[-2].block)->statements.push_back(shared_ptr<NBase>((yyvsp[0].node))); }

    break;

  case 5:

    { (yyval.node) = nullptr; }

    break;

  case 10:

    { (yyval.node) = (yyvsp[0].node); }

    break;

  case 11:

    { (yyval.node) = (yyvsp[0].ccode); }

    break;

  case 12:

    { (yyval.node) = (yyvsp[0].ccode); }

    break;

  case 13:

    { (yyval.node) = (yyvsp[0].ccode); }

    break;

  case 14:

    { (yyval.node) = (yyvsp[0].ccode); }

    break;

  case 15:

    { (yyval.node) = (yyvsp[0].ccode); }

    break;

  case 16:

    { (yyval.node) = (yyvsp[0].ccode); }

    break;

  case 17:

    { (yyval.node) = new NInclude(LOC, (yyvsp[0].string)->c_str()); delete (yyvsp[0].string); }

    break;

  case 18:

    { (yyval.node) = new NPackage(LOC, *(yyvsp[-1].strings), shared_ptr<NBase>((yyvsp[0].node))); delete (yyvsp[-1].strings); }

    break;

  case 19:

    { (yyval.node) = new NImport(LOC, *(yyvsp[-2].import_namespaces), shared_ptr<NBase>((yyvsp[0].node))); delete (yyvsp[-2].import_namespaces); }

    break;

  case 20:

    { (yyval.node) = nullptr; /* yyclearin; */ compiler->addError(LLOC, CErrorCode::InvalidCharacter, "Something failed to parse"); }

    break;

  case 21:

    { (yyval.ccode)->lines.push_back(*(yyvsp[0].string)); delete (yyvsp[0].string); }

    break;

  case 22:

    { (yyval.ccode) = new NCCode(LOC, NCC_BLOCK, (yyvsp[0].string)->c_str()); delete (yyvsp[0].string); }

    break;

  case 23:

    { (yyval.ccode)->lines.push_back(*(yyvsp[0].string)); delete (yyvsp[0].string); }

    break;

  case 24:

    { (yyval.ccode) = new NCCode(LOC, NCC_DEFINE, (yyvsp[0].string)->c_str()); delete (yyvsp[0].string); }

    break;

  case 25:

    { (yyval.ccode)->lines.push_back(*(yyvsp[0].string)); delete (yyvsp[0].string); }

    break;

  case 26:

    { (yyval.ccode) = new NCCode(LOC, NCC_STRUCT, (yyvsp[0].string)->c_str()); delete (yyvsp[0].string); }

    break;

  case 27:

    { (yyval.ccode)->lines.push_back(*(yyvsp[0].string)); delete (yyvsp[0].string); }

    break;

  case 28:

    { (yyval.ccode) = new NCCode(LOC, NCC_FUNCTION, (yyvsp[0].string)->c_str()); delete (yyvsp[0].string); }

    break;

  case 29:

    { (yyval.ccode)->lines.push_back(*(yyvsp[0].string)); delete (yyvsp[0].string); }

    break;

  case 30:

    { (yyval.ccode) = new NCCode(LOC, NCC_INCLUDE, (yyvsp[0].string)->c_str()); delete (yyvsp[0].string); }

    break;

  case 31:

    { (yyval.ccode)->lines.push_back(*(yyvsp[0].string)); delete (yyvsp[0].string); }

    break;

  case 32:

    { (yyval.ccode) = new NCCode(LOC, NCC_TYPEDEF, (yyvsp[0].string)->c_str()); delete (yyvsp[0].string); }

    break;

  case 33:

    { (yyval.ccode)->lines.push_back(*(yyvsp[0].string)); delete (yyvsp[0].string); }

    break;

  case 34:

    { (yyval.ccode) = new NCCode(LOC, NCC_VAR, (yyvsp[0].string)->c_str()); delete (yyvsp[0].string); }

    break;

  case 35:

    { (yyvsp[-2].import_namespaces)->push_back(*(yyvsp[0].import_namespace)); delete (yyvsp[0].import_namespace); }

    break;

  case 36:

    { (yyvsp[-2].import_namespaces)->push_back(*(yyvsp[0].import_namespace)); delete (yyvsp[0].import_namespace); }

    break;

  case 37:

    { (yyval.import_namespaces) = new vector<pair<string, vector<string>>>(); (yyval.import_namespaces)->push_back(*(yyvsp[0].import_namespace)); delete (yyvsp[0].import_namespace); }

    break;

  case 38:

    { (yyval.import_namespace) = new pair<string, vector<string>>(*(yyvsp[-2].string), *(yyvsp[0].strings)); delete (yyvsp[-2].string); delete (yyvsp[0].strings); }

    break;

  case 39:

    { (yyval.import_namespace) = new pair<string, vector<string>>("", *(yyvsp[0].strings)); delete (yyvsp[0].strings); }

    break;

  case 40:

    { (yyval.strings)->push_back(*(yyvsp[0].string)); delete (yyvsp[0].string); }

    break;

  case 41:

    { (yyval.strings) = new vector<string>(); (yyval.strings)->push_back(*(yyvsp[0].string)); delete (yyvsp[0].string); }

    break;

  case 42:

    { (yyval.node) = (yyvsp[-1].block); }

    break;

  case 44:

    { (yyval.node) = new NMathAssignment(LOC, shared_ptr<NVariableBase>((yyvsp[-1].var)), NMAO_Inc, nullptr); }

    break;

  case 45:

    { (yyval.node) = new NMathAssignment(LOC, shared_ptr<NVariableBase>((yyvsp[-1].var)), NMAO_Dec, nullptr); }

    break;

  case 46:

    { (yyval.node) = new NMathAssignment(LOC, shared_ptr<NVariableBase>((yyvsp[-2].var)), NMAO_Add, shared_ptr<NVariableBase>((yyvsp[0].var))); }

    break;

  case 47:

    { (yyval.node) = new NMathAssignment(LOC, shared_ptr<NVariableBase>((yyvsp[-2].var)), NMAO_Sub, shared_ptr<NVariableBase>((yyvsp[0].var))); }

    break;

  case 48:

    { (yyval.node) = new NMathAssignment(LOC, shared_ptr<NVariableBase>((yyvsp[-2].var)), NMAO_Mul, shared_ptr<NVariableBase>((yyvsp[0].var))); }

    break;

  case 49:

    { (yyval.node) = new NMathAssignment(LOC, shared_ptr<NVariableBase>((yyvsp[-2].var)), NMAO_Div, shared_ptr<NVariableBase>((yyvsp[0].var))); }

    break;

  case 50:

    { (yyval.node) = new NDot(LOC, shared_ptr<NVariableBase>((yyvsp[-5].var)), make_shared<NCall>(LOC, "setAt", nullptr, make_shared<NodeList>(shared_ptr<NBase>((yyvsp[-3].node)), shared_ptr<NBase>((yyvsp[0].node))))); }

    break;

  case 51:

    { (yyval.node) = new NEnum(LOC, *(yyvsp[-5].string), shared_ptr<EnumArgs>((yyvsp[-2].enumArgs))); delete (yyvsp[-5].string); }

    break;

  case 52:

    { (yyvsp[-2].enumArgs)->push_back(shared_ptr<EnumArg>((yyvsp[0].enumArg))); }

    break;

  case 53:

    { (yyvsp[-2].enumArgs)->push_back(shared_ptr<EnumArg>((yyvsp[0].enumArg))); }

    break;

  case 54:

    { (yyval.enumArgs) = new EnumArgs(shared_ptr<EnumArg>((yyvsp[0].enumArg))); }

    break;

  case 55:

    { (yyval.enumArg) = new EnumArg(*(yyvsp[0].string)); delete (yyvsp[0].string); }

    break;

  case 56:

    { (yyval.enumArg) = new EnumArg(*(yyvsp[-2].string), *(yyvsp[0].string)); delete (yyvsp[-2].string); delete (yyvsp[0].string); }

    break;

  case 57:

    { 
						(yyval.node) = new NFunction(LOC, FT_Private, nullptr, (yyvsp[-5].typeName)->valueName.c_str(), (yyvsp[-5].typeName)->templateTypeNames, 
							nullptr, shared_ptr<NodeList>((yyvsp[-4].exprvec)), 
							shared_ptr<NBase>((yyvsp[-3].node)), shared_ptr<NBase>((yyvsp[-2].node)), shared_ptr<NBase>((yyvsp[-1].node)), shared_ptr<NBase>((yyvsp[0].node)));
						delete (yyvsp[-5].typeName); 
					}

    break;

  case 58:

    { 
						(yyval.node) = new NFunction(LOC, FT_Private, nullptr, (yyvsp[-6].typeName)->valueName.c_str(), (yyvsp[-6].typeName)->templateTypeNames, 
							shared_ptr<CTypeNameList>((yyvsp[-5].templateTypeNames)), shared_ptr<NodeList>((yyvsp[-4].exprvec)), 
							shared_ptr<NBase>((yyvsp[-3].node)), shared_ptr<NBase>((yyvsp[-2].node)), shared_ptr<NBase>((yyvsp[-1].node)), shared_ptr<NBase>((yyvsp[0].node))); 
					}

    break;

  case 59:

    { 
						(yyval.node) = new NFunction(LOC, FT_Private, shared_ptr<CTypeName>((yyvsp[-4].typeName)), (yyvsp[-6].typeName)->valueName.c_str(), (yyvsp[-6].typeName)->templateTypeNames, 
							nullptr, shared_ptr<NodeList>((yyvsp[-5].exprvec)), 
							shared_ptr<NBase>((yyvsp[-3].node)), shared_ptr<NBase>((yyvsp[-2].node)), shared_ptr<NBase>((yyvsp[-1].node)), shared_ptr<NBase>((yyvsp[0].node))); 
					}

    break;

  case 60:

    { 
						(yyval.node) = new NFunction(LOC, FT_Private, shared_ptr<CTypeName>((yyvsp[-4].typeName)), (yyvsp[-7].typeName)->valueName.c_str(), (yyvsp[-7].typeName)->templateTypeNames, 
							shared_ptr<CTypeNameList>((yyvsp[-6].templateTypeNames)), shared_ptr<NodeList>((yyvsp[-5].exprvec)), 
							shared_ptr<NBase>((yyvsp[-3].node)), shared_ptr<NBase>((yyvsp[-2].node)), shared_ptr<NBase>((yyvsp[-1].node)), shared_ptr<NBase>((yyvsp[0].node))); 
					}

    break;

  case 61:

    { (yyval.typeName) = new CTypeName(CTC_Value, CTM_Stack, emptyNamespace, (yyvsp[0].string)->c_str(), false); delete (yyvsp[0].string); }

    break;

  case 62:

    { (yyval.typeName) = new CTypeName(CTC_Value, CTM_Stack, emptyNamespace, (yyvsp[-1].string)->c_str(), shared_ptr<CTypeNameList>((yyvsp[0].templateTypeNames)), false); delete (yyvsp[-1].string); }

    break;

  case 63:

    { (yyval.typeName) = new CTypeName(CTC_Value, CTM_Stack, emptyNamespace, (yyvsp[0].string)->c_str(), false); delete (yyvsp[0].string); }

    break;

  case 64:

    { (yyval.typeName) = new CTypeName(CTC_Value, CTM_Stack, emptyNamespace, (yyvsp[-1].string)->c_str(), shared_ptr<CTypeNameList>((yyvsp[0].templateTypeNames)), false); delete (yyvsp[-1].string); }

    break;

  case 65:

    { (yyval.node) = nullptr; }

    break;

  case 66:

    { (yyval.node) = (yyvsp[0].node); }

    break;

  case 67:

    { (yyval.node) = nullptr; }

    break;

  case 68:

    { (yyval.node) = (yyvsp[0].node); }

    break;

  case 69:

    { (yyval.node) = nullptr; }

    break;

  case 70:

    { (yyval.node) = (yyvsp[0].node); }

    break;

  case 71:

    { (yyval.exprvec) = (yyvsp[-2].exprvec); }

    break;

  case 72:

    { (yyval.exprvec) = new NodeList(); }

    break;

  case 73:

    { (yyval.exprvec) = new NodeList(); if ((yyvsp[0].node)) { (yyval.exprvec)->push_back(shared_ptr<NBase>((yyvsp[0].node))); } }

    break;

  case 74:

    { if ((yyvsp[0].node)) { (yyvsp[-2].exprvec)->push_back(shared_ptr<NBase>((yyvsp[0].node))); } }

    break;

  case 75:

    { if ((yyvsp[0].node)) { (yyvsp[-3].exprvec)->push_back(shared_ptr<NBase>((yyvsp[0].node))); } }

    break;

  case 76:

    { if ((yyvsp[0].node)) { (yyvsp[-2].exprvec)->push_back(shared_ptr<NBase>((yyvsp[0].node))); } }

    break;

  case 80:

    { (yyval.node) = (yyvsp[0].ccode); }

    break;

  case 81:

    { (yyval.node) = (yyvsp[0].node); }

    break;

  case 82:

    { (yyval.templateTypeNames) = (yyvsp[0].templateTypeNames); }

    break;

  case 83:

    { (yyval.templateTypeNames) = new CTypeNameList(); (yyval.templateTypeNames)->push_back(shared_ptr<CTypeName>((yyvsp[0].typeName))); }

    break;

  case 84:

    { (yyval.templateTypeNames) = (yyvsp[-1].templateTypeNames); (yyval.templateTypeNames)->push_back(shared_ptr<CTypeName>((yyvsp[0].typeName))); }

    break;

  case 85:

    { string t = (yyvsp[-1].strings)->back(); (yyvsp[-1].strings)->pop_back(); (yyval.typeName) = new CTypeName(CTC_Interface, CTM_Stack, *(yyvsp[-1].strings), t, shared_ptr<CTypeNameList>((yyvsp[0].templateTypeNames)), false); delete (yyvsp[-1].strings); }

    break;

  case 86:

    { (yyval.node) = new NInterface(LOC, *(yyvsp[-2].string), shared_ptr<CTypeNameList>((yyvsp[-1].templateTypeNames)), shared_ptr<NodeList>((yyvsp[0].exprvec))); delete (yyvsp[-2].string); }

    break;

  case 87:

    { (yyval.exprvec) = (yyvsp[-1].exprvec); }

    break;

  case 88:

    { (yyval.exprvec) = new NodeList(); if ((yyvsp[0].node)) { (yyval.exprvec)->push_back(shared_ptr<NBase>((yyvsp[0].node))); } }

    break;

  case 89:

    { if ((yyvsp[0].node)) { (yyvsp[-2].exprvec)->push_back(shared_ptr<NBase>((yyvsp[0].node))); } }

    break;

  case 90:

    { if ((yyvsp[0].node)) { (yyvsp[-2].exprvec)->push_back(shared_ptr<NBase>((yyvsp[0].node))); } }

    break;

  case 91:

    { (yyval.node) = nullptr; }

    break;

  case 92:

    { (yyval.node) = new NInterfaceMethod(LOC, (yyvsp[-2].typeName)->valueName.c_str(), (yyvsp[-2].typeName)->templateTypeNames, shared_ptr<NodeList>((yyvsp[-1].exprvec)), shared_ptr<CTypeName>((yyvsp[0].typeName))); }

    break;

  case 93:

    { (yyval.node) = (yyvsp[0].node); }

    break;

  case 95:

    { (yyval.node) = (yyvsp[0].node); }

    break;

  case 97:

    { (yyval.node) = (yyvsp[0].var); }

    break;

  case 98:

    { (yyval.node) = (yyvsp[0].var); }

    break;

  case 101:

    { (yyval.node) = new NThrow(LOC, shared_ptr<NBase>((yyvsp[-1].node))); }

    break;

  case 102:

    { (yyval.node) = new NVoid(LOC); }

    break;

  case 103:

    { (yyval.var) = new NAnd(LOC, shared_ptr<NVariableBase>((yyvsp[-2].var)), shared_ptr<NVariableBase>((yyvsp[0].var))); }

    break;

  case 104:

    { (yyval.var) = new NOr(LOC, shared_ptr<NVariableBase>((yyvsp[-2].var)), shared_ptr<NVariableBase>((yyvsp[0].var))); }

    break;

  case 106:

    { (yyval.var) = new NCompare(LOC, shared_ptr<NVariableBase>((yyvsp[-2].var)), NCompareOp::EQ, shared_ptr<NVariableBase>((yyvsp[0].var))); }

    break;

  case 107:

    { (yyval.var) = new NCompare(LOC, shared_ptr<NVariableBase>((yyvsp[-2].var)), NCompareOp::NE, shared_ptr<NVariableBase>((yyvsp[0].var))); }

    break;

  case 108:

    { (yyval.var) = new NCompare(LOC, shared_ptr<NVariableBase>((yyvsp[-2].var)), NCompareOp::PEQ, shared_ptr<NVariableBase>((yyvsp[0].var))); }

    break;

  case 109:

    { (yyval.var) = new NCompare(LOC, shared_ptr<NVariableBase>((yyvsp[-2].var)), NCompareOp::PNE, shared_ptr<NVariableBase>((yyvsp[0].var))); }

    break;

  case 110:

    { (yyval.var) = new NCompare(LOC, shared_ptr<NVariableBase>((yyvsp[-2].var)), NCompareOp::LT, shared_ptr<NVariableBase>((yyvsp[0].var))); }

    break;

  case 111:

    { (yyval.var) = new NCompare(LOC, shared_ptr<NVariableBase>((yyvsp[-2].var)), NCompareOp::LE, shared_ptr<NVariableBase>((yyvsp[0].var))); }

    break;

  case 112:

    { (yyval.var) = new NCompare(LOC, shared_ptr<NVariableBase>((yyvsp[-2].var)), NCompareOp::GT, shared_ptr<NVariableBase>((yyvsp[0].var))); }

    break;

  case 113:

    { (yyval.var) = new NCompare(LOC, shared_ptr<NVariableBase>((yyvsp[-2].var)), NCompareOp::GE, shared_ptr<NVariableBase>((yyvsp[0].var))); }

    break;

  case 114:

    { (yyval.var) = (yyvsp[0].var); }

    break;

  case 115:

    { (yyval.var) = new NMath(LOC, shared_ptr<NVariableBase>((yyvsp[-2].var)), NMathOp::Add, shared_ptr<NVariableBase>((yyvsp[0].var))); }

    break;

  case 116:

    { (yyval.var) = new NMath(LOC, shared_ptr<NVariableBase>((yyvsp[-2].var)), NMathOp::Sub, shared_ptr<NVariableBase>((yyvsp[0].var))); }

    break;

  case 117:

    { (yyval.var) = new NMath(LOC, shared_ptr<NVariableBase>((yyvsp[-2].var)), NMathOp::Mul, shared_ptr<NVariableBase>((yyvsp[0].var))); }

    break;

  case 118:

    { (yyval.var) = new NMath(LOC, shared_ptr<NVariableBase>((yyvsp[-2].var)), NMathOp::Div, shared_ptr<NVariableBase>((yyvsp[0].var))); }

    break;

  case 119:

    { (yyval.var) = new NMath(LOC, shared_ptr<NVariableBase>((yyvsp[-2].var)), NMathOp::Mod, shared_ptr<NVariableBase>((yyvsp[0].var))); }

    break;

  case 120:

    { (yyval.var) = new NNot(LOC, shared_ptr<NVariableBase>((yyvsp[0].var))); }

    break;

  case 121:

    { (yyval.var) = new NChangeMode(LOC, CTM_Stack, shared_ptr<NBase>((yyvsp[0].var))); }

    break;

  case 122:

    { (yyval.var) = new NChangeMode(LOC, CTM_Local, shared_ptr<NBase>((yyvsp[0].var))); }

    break;

  case 123:

    { (yyval.var) = new NChangeMode(LOC, CTM_Heap, shared_ptr<NBase>((yyvsp[0].var))); }

    break;

  case 124:

    { (yyval.var) = new NChangeMode(LOC, CTM_Weak, shared_ptr<NBase>((yyvsp[0].var))); }

    break;

  case 125:

    { (yyval.var) = new NCopy(LOC, shared_ptr<NBase>((yyvsp[0].var))); }

    break;

  case 126:

    { (yyval.var) = (yyvsp[0].var); }

    break;

  case 127:

    { (yyval.var) = new NCast(LOC, shared_ptr<CTypeName>((yyvsp[0].typeName)), shared_ptr<NVariableBase>((yyvsp[-2].var))); }

    break;

  case 128:

    { (yyval.var) = new NDot(LOC, shared_ptr<NVariableBase>((yyvsp[-2].var)), shared_ptr<NVariableBase>((yyvsp[0].var))); }

    break;

  case 129:

    { (yyval.var) = new NGetOrElse(LOC, shared_ptr<NVariableBase>((yyvsp[-2].var)), shared_ptr<NBase>((yyvsp[0].var))); }

    break;

  case 130:

    { (yyval.var) = new NOptionDot(LOC, shared_ptr<NVariableBase>((yyvsp[-2].var)), shared_ptr<NVariableBase>((yyvsp[0].var))); }

    break;

  case 131:

    { (yyval.var) = new NDot(LOC, shared_ptr<NVariableBase>((yyvsp[-3].var)), make_shared<NCall>(LOC, "getAt", nullptr, make_shared<NodeList>(shared_ptr<NBase>((yyvsp[-1].node))))); }

    break;

  case 132:

    { (yyval.var) = (yyvsp[0].var); }

    break;

  case 133:

    { (yyval.node) = new NFor(LOC, (yyvsp[-5].string)->c_str(), shared_ptr<NBase>((yyvsp[-3].node)), shared_ptr<NBase>((yyvsp[-1].node)), shared_ptr<NBase>((yyvsp[0].node)), true); delete (yyvsp[-5].string); }

    break;

  case 134:

    { (yyval.node) = new NFor(LOC, (yyvsp[-5].string)->c_str(), shared_ptr<NBase>((yyvsp[-3].node)), shared_ptr<NBase>((yyvsp[-1].node)), shared_ptr<NBase>((yyvsp[0].node)), false); delete (yyvsp[-5].string); }

    break;

  case 135:

    { (yyval.node) = new NWhile(LOC, shared_ptr<NBase>((yyvsp[-1].node)), shared_ptr<NBase>((yyvsp[0].node))); }

    break;

  case 136:

    { (yyval.node) = new NSwitch(LOC, shared_ptr<NBase>((yyvsp[-5].node)), *(yyvsp[-2].switchClauses)); delete (yyvsp[-2].switchClauses); }

    break;

  case 137:

    { (yyval.node) = new NSwitch(LOC, nullptr, *(yyvsp[-2].switchClauses)); delete (yyvsp[-2].switchClauses); }

    break;

  case 138:

    { (yyval.switchClauses) = new vector<shared_ptr<NSwitchClause>>(); (yyval.switchClauses)->push_back(shared_ptr<NSwitchClause>((yyvsp[0].switchClause))); }

    break;

  case 139:

    { (yyval.switchClauses) = (yyvsp[-2].switchClauses); (yyval.switchClauses)->push_back(shared_ptr<NSwitchClause>((yyvsp[0].switchClause))); }

    break;

  case 140:

    { (yyval.switchClause) = new NSwitchClause(LOC, shared_ptr<NBase>((yyvsp[-1].node)), shared_ptr<NBase>((yyvsp[0].node))); }

    break;

  case 141:

    { (yyval.switchClause) = new NSwitchClause(LOC, nullptr, shared_ptr<NBase>((yyvsp[0].node))); }

    break;

  case 142:

    { (yyval.node) = new NIf(LOC, shared_ptr<NBase>((yyvsp[-1].node)), shared_ptr<NBase>((yyvsp[0].node)), nullptr); }

    break;

  case 143:

    { (yyval.node) = new NIf(LOC, shared_ptr<NBase>((yyvsp[-3].node)), shared_ptr<NBase>((yyvsp[-2].node)), shared_ptr<NBase>((yyvsp[0].node))); }

    break;

  case 144:

    { (yyval.node) = new NIf(LOC, shared_ptr<NBase>((yyvsp[-3].node)), shared_ptr<NBase>((yyvsp[-2].node)), shared_ptr<NBase>((yyvsp[0].node))); }

    break;

  case 145:

    { (yyval.node) = new NIfValid(LOC, shared_ptr<NodeList>((yyvsp[-1].exprvec)), shared_ptr<NBase>((yyvsp[0].node)), nullptr); }

    break;

  case 146:

    { (yyval.node) = new NIfValid(LOC, shared_ptr<NodeList>((yyvsp[-3].exprvec)), shared_ptr<NBase>((yyvsp[-2].node)), shared_ptr<NBase>((yyvsp[0].node))); }

    break;

  case 147:

    { (yyvsp[-2].exprvec)->push_back(shared_ptr<NBase>((yyvsp[0].node))); (yyval.exprvec) = (yyvsp[-2].exprvec); }

    break;

  case 148:

    { (yyval.exprvec) = new NodeList(); (yyval.exprvec)->push_back(shared_ptr<NBase>((yyvsp[0].node))); }

    break;

  case 149:

    { (yyval.node) = new NAssignment(LOC, nullptr, nullptr, (yyvsp[-2].string)->c_str(), shared_ptr<NBase>((yyvsp[0].node)), (yyvsp[-1].assignOp)); }

    break;

  case 150:

    { (yyval.node) = new NVariable(LOC, (yyvsp[0].typeName)->valueName.c_str(), (yyvsp[0].typeName)->templateTypeNames); delete (yyvsp[0].typeName); }

    break;

  case 151:

    { (yyval.var) = new NVariableStub(shared_ptr<NBase>((yyvsp[-1].node))); }

    break;

  case 152:

    { (yyval.var) = new NCall(LOC, (yyvsp[-1].typeName)->valueName.c_str(), (yyvsp[-1].typeName)->templateTypeNames, shared_ptr<NodeList>((yyvsp[0].exprvec))); delete (yyvsp[-1].typeName); }

    break;

  case 153:

    { (yyval.var) = new NIsEmptyOrValid(LOC, shared_ptr<NBase>((yyvsp[-1].node)), true); }

    break;

  case 154:

    { (yyval.var) = new NIsEmptyOrValid(LOC, shared_ptr<NBase>((yyvsp[-1].node)), false); }

    break;

  case 155:

    { (yyval.var) = new NGetValue(LOC, shared_ptr<NBase>((yyvsp[-1].node)), false); }

    break;

  case 156:

    { (yyval.var) = new NValue(LOC, shared_ptr<NBase>((yyvsp[-1].node))); }

    break;

  case 157:

    { (yyval.var) = new NVariable(LOC, (yyvsp[0].typeName)->valueName.c_str(), (yyvsp[0].typeName)->templateTypeNames); delete (yyvsp[0].typeName); }

    break;

  case 158:

    { (yyval.var) = new NParent(LOC, false); }

    break;

  case 159:

    { (yyval.var) = new NThis(LOC, false); }

    break;

  case 160:

    { (yyval.var) = new NParent(LOC, true); }

    break;

  case 161:

    { (yyval.var) = new NThis(LOC, true); }

    break;

  case 162:

    { (yyval.var) = new NNegate(LOC, shared_ptr<NVariableBase>((yyvsp[0].var))); }

    break;

  case 163:

    { (yyval.var) = (yyvsp[0].var); }

    break;

  case 164:

    { (yyval.var) = new NInteger(LOC, (yyvsp[0].string)->c_str()); delete (yyvsp[0].string); }

    break;

  case 165:

    { (yyval.var) = new NDouble(LOC, (yyvsp[0].string)->c_str()); delete (yyvsp[0].string); }

    break;

  case 166:

    { (yyval.var) = new NBool(LOC, true); }

    break;

  case 167:

    { (yyval.var) = new NBool(LOC, false); }

    break;

  case 168:

    { (yyval.var) = new NString(LOC, (yyvsp[0].string)->c_str()); delete (yyvsp[0].string); }

    break;

  case 169:

    { (yyval.var) = new NChar(LOC, (yyvsp[0].string)->c_str()); delete (yyvsp[0].string); }

    break;

  case 170:

    { (yyval.var) = new NNullPtr(LOC); }

    break;

  case 171:

    { (yyval.var) = new NUnderscore(LOC); }

    break;

  case 172:

    { (yyval.var) = new NEmpty(LOC, shared_ptr<CTypeName>((yyvsp[0].typeName))); }

    break;

  case 173:

    { (yyval.node) = new NAssignment(LOC, nullptr, nullptr, (yyvsp[-2].string)->c_str(), shared_ptr<NBase>((yyvsp[0].node)), (yyvsp[-1].assignOp)); }

    break;

  case 174:

    { (yyval.node) = new NAssignment(LOC, nullptr, shared_ptr<CTypeName>((yyvsp[0].typeName)), (yyvsp[-2].string)->c_str(), nullptr, (yyvsp[-1].assignOp)); }

    break;

  case 175:

    { (yyval.node) = new NAssignment(LOC, nullptr, shared_ptr<CTypeName>((yyvsp[-2].typeName)), (yyvsp[-3].string)->c_str(), shared_ptr<NBase>((yyvsp[0].node)), (yyvsp[-1].assignOp)); }

    break;

  case 176:

    { (yyval.node) = new NAssignment(LOC, shared_ptr<NVariableBase>((yyvsp[-4].var)), nullptr, (yyvsp[-2].string)->c_str(), shared_ptr<NBase>((yyvsp[0].node)), (yyvsp[-1].assignOp)); }

    break;

  case 177:

    { (yyval.node) = new NAssignment(LOC, shared_ptr<NVariableBase>((yyvsp[-4].var)), shared_ptr<CTypeName>((yyvsp[0].typeName)), (yyvsp[-2].string)->c_str(), nullptr, (yyvsp[-1].assignOp)); }

    break;

  case 178:

    { (yyval.node) = new NAssignment(LOC, shared_ptr<NVariableBase>((yyvsp[-5].var)), shared_ptr<CTypeName>((yyvsp[-2].typeName)), (yyvsp[-3].string)->c_str(), shared_ptr<NBase>((yyvsp[0].node)), (yyvsp[-1].assignOp)); }

    break;

  case 179:

    { (yyval.node) = new NTupleAssignment(LOC, shared_ptr<NTupleAssignmentArgList>((yyvsp[-2].tupleAssignmentArgList)), shared_ptr<NBase>((yyvsp[0].node))); }

    break;

  case 180:

    { (yyval.tupleAssignmentArgList) = new NTupleAssignmentArgList(); (yyval.tupleAssignmentArgList)->push_back(shared_ptr<NTupleAssignmentArg>((yyvsp[0].tupleAssignmentArg))); }

    break;

  case 181:

    { (yyvsp[-2].tupleAssignmentArgList)->push_back(shared_ptr<NTupleAssignmentArg>((yyvsp[0].tupleAssignmentArg))); }

    break;

  case 182:

    { (yyval.tupleAssignmentArg) = new NTupleAssignmentArg(LOC, nullptr, nullptr, (yyvsp[-1].string)->c_str(), (yyvsp[0].assignOp)); }

    break;

  case 183:

    { (yyval.tupleAssignmentArg) = new NTupleAssignmentArg(LOC, shared_ptr<NVariableBase>((yyvsp[-3].var)), nullptr, (yyvsp[-1].string)->c_str(), (yyvsp[0].assignOp)); }

    break;

  case 184:

    { (yyval.assignOp).isCopy = false; (yyval.assignOp).typeMode = CTM_Undefined; (yyval.assignOp).isMutable = true;  (yyval.assignOp).isFirstAssignment = false; }

    break;

  case 185:

    { (yyval.assignOp).isCopy = false; (yyval.assignOp).typeMode = CTM_Undefined; (yyval.assignOp).isMutable = true;  (yyval.assignOp).isFirstAssignment = true; }

    break;

  case 186:

    { (yyval.assignOp).isCopy = false; (yyval.assignOp).typeMode = CTM_Undefined; (yyval.assignOp).isMutable = false; (yyval.assignOp).isFirstAssignment = true; }

    break;

  case 187:

    { (yyval.assignOp).isCopy = true; (yyval.assignOp).typeMode = CTM_Undefined; (yyval.assignOp).isMutable = true;  (yyval.assignOp).isFirstAssignment = false; }

    break;

  case 188:

    { (yyval.assignOp).isCopy = true; (yyval.assignOp).typeMode = CTM_Undefined; (yyval.assignOp).isMutable = true;  (yyval.assignOp).isFirstAssignment = true; }

    break;

  case 189:

    { (yyval.assignOp).isCopy = true; (yyval.assignOp).typeMode = CTM_Undefined; (yyval.assignOp).isMutable = false; (yyval.assignOp).isFirstAssignment = true; }

    break;

  case 190:

    { (yyval.assignOp).isCopy = false; (yyval.assignOp).typeMode = CTM_Undefined; (yyval.assignOp).isMutable = true;  (yyval.assignOp).isFirstAssignment = false; }

    break;

  case 191:

    { (yyval.assignOp).isCopy = false; (yyval.assignOp).typeMode = CTM_Undefined; (yyval.assignOp).isMutable = true;  (yyval.assignOp).isFirstAssignment = true; }

    break;

  case 192:

    { (yyval.assignOp).isCopy = false; (yyval.assignOp).typeMode = CTM_Undefined; (yyval.assignOp).isMutable = false; (yyval.assignOp).isFirstAssignment = true; }

    break;

  case 193:

    { (yyvsp[-3].exprvec)->push_back(shared_ptr<NBase>((yyvsp[-1].var))); (yyval.var) = new NTuple(LOC, shared_ptr<NodeList>((yyvsp[-3].exprvec))); }

    break;

  case 194:

    { (yyval.exprvec) = new NodeList(); (yyval.exprvec)->push_back(shared_ptr<NBase>((yyvsp[0].var))); }

    break;

  case 195:

    { (yyvsp[-2].exprvec)->push_back(shared_ptr<NBase>((yyvsp[0].var))); }

    break;

  case 196:

    { (yyval.node) = new NArray(LOC, shared_ptr<NodeList>((yyvsp[-2].exprvec))); }

    break;

  case 197:

    { (yyval.node) = new NHash(LOC, *(yyvsp[-2].hashArgs)); delete (yyvsp[-2].hashArgs); }

    break;

  case 198:

    { (yyval.hashArgs) = new vector<pair<shared_ptr<NBase>, shared_ptr<NBase>>>(); (yyval.hashArgs)->push_back(*(yyvsp[0].hashArg)); delete (yyvsp[0].hashArg); }

    break;

  case 199:

    { (yyvsp[-2].hashArgs)->push_back(*(yyvsp[0].hashArg)); delete (yyvsp[0].hashArg); }

    break;

  case 200:

    { (yyvsp[-3].hashArgs)->push_back(*(yyvsp[0].hashArg)); delete (yyvsp[0].hashArg); }

    break;

  case 201:

    { (yyvsp[-2].hashArgs)->push_back(*(yyvsp[0].hashArg)); delete (yyvsp[0].hashArg); }

    break;

  case 202:

    { (yyval.hashArg) = new pair<shared_ptr<NBase>, shared_ptr<NBase>>(shared_ptr<NBase>((yyvsp[-2].node)), shared_ptr<NBase>((yyvsp[0].node))); }

    break;

  case 203:

    { (yyval.node) = nullptr; }

    break;

  case 204:

    { (yyval.node) = nullptr; }

    break;

  case 205:

    { (yyval.node) = nullptr; }

    break;

  case 206:

    { (yyval.node) = nullptr; }

    break;

  case 207:

    { (yyval.exprvec) = new NodeList(); (yyval.exprvec)->push_back(shared_ptr<NBase>((yyvsp[0].node))); }

    break;

  case 208:

    { (yyvsp[-2].exprvec)->push_back(shared_ptr<NBase>((yyvsp[0].node))); }

    break;

  case 209:

    { (yyvsp[-3].exprvec)->push_back(shared_ptr<NBase>((yyvsp[0].node))); }

    break;

  case 210:

    { (yyvsp[-2].exprvec)->push_back(shared_ptr<NBase>((yyvsp[0].node))); }

    break;

  case 211:

    { (yyval.typeName) = (yyvsp[0].typeName); }

    break;

  case 212:

    { (yyval.typeName) = (yyvsp[0].typeName); }

    break;

  case 213:

    { (yyval.typeName) = (yyvsp[0].typeName); }

    break;

  case 214:

    { (yyval.typeName) = new CTypeName((yyvsp[-1].typeNameParts)->isHash ? CTC_Interface : CTC_Value, (yyvsp[-2].typeMode), (yyvsp[-1].typeNameParts)->packageNamespace, (yyvsp[-1].typeNameParts)->name, shared_ptr<CTypeNameList>((yyvsp[0].optionAndTypeList).templateTypeNames), (yyvsp[0].optionAndTypeList).isOption); delete (yyvsp[-1].typeNameParts); }

    break;

  case 215:

    { (yyval.typeName) = (yyvsp[0].typeName); }

    break;

  case 216:

    { (yyval.typeMode) = CTM_Undefined; }

    break;

  case 217:

    { (yyval.typeMode) = CTM_Local; }

    break;

  case 218:

    { (yyval.typeMode) = CTM_Stack; }

    break;

  case 219:

    { (yyval.typeMode) = CTM_Heap; }

    break;

  case 220:

    { (yyval.typeMode) = CTM_Weak; }

    break;

  case 221:

    { (yyval.typeName) = (yyvsp[0].typeName); }

    break;

  case 222:

    { (yyval.typeName) = new CTypeName(CTC_Value, CTM_Stack, emptyNamespace, "void", false); }

    break;

  case 223:

    { (yyval.typeName) = new CTypeName(CTC_Value, CTM_Value, emptyNamespace, "i32", false); }

    break;

  case 224:

    { (yyval.typeName) = new CTypeName(CTC_Value, CTM_Value, emptyNamespace, "u32", false); }

    break;

  case 225:

    { (yyval.typeName) = new CTypeName(CTC_Value, CTM_Value, emptyNamespace, "f32", false); }

    break;

  case 226:

    { (yyval.typeName) = new CTypeName(CTC_Value, CTM_Value, emptyNamespace, "i64", false); }

    break;

  case 227:

    { (yyval.typeName) = new CTypeName(CTC_Value, CTM_Value, emptyNamespace, "u64", false); }

    break;

  case 228:

    { (yyval.typeName) = new CTypeName(CTC_Value, CTM_Value, emptyNamespace, "f64", false); }

    break;

  case 229:

    { (yyval.typeName) = new CTypeName(CTC_Value, CTM_Value, emptyNamespace, "char", false); }

    break;

  case 230:

    { (yyval.typeName) = new CTypeName(CTC_Value, CTM_Value, emptyNamespace, "bool", false); }

    break;

  case 231:

    { (yyval.typeName) = new CTypeName(CTC_Value, CTM_Value, emptyNamespace, "ptr", false); }

    break;

  case 232:

    { (yyval.typeName) = new CTypeName((yyvsp[-4].typeMode), shared_ptr<CTypeNameList>((yyvsp[-2].templateTypeNames)), shared_ptr<CTypeName>((yyvsp[0].typeName))); }

    break;

  case 233:

    { (yyval.typeName) = (yyvsp[0].typeName); (yyval.typeName)->mutability = CTI_Mutable; }

    break;

  case 234:

    { (yyval.typeName) = (yyvsp[0].typeName); (yyval.typeName)->mutability = CTI_Immutable; }

    break;

  case 235:

    { (yyval.templateTypeNames) = new CTypeNameList(); }

    break;

  case 236:

    { (yyval.templateTypeNames) = new CTypeNameList(); (yyval.templateTypeNames)->push_back(shared_ptr<CTypeName>((yyvsp[0].typeName))); }

    break;

  case 237:

    { (yyvsp[-2].templateTypeNames)->push_back(shared_ptr<CTypeName>((yyvsp[0].typeName))); }

    break;

  case 238:

    { (yyval.templateTypeNames) = nullptr; }

    break;

  case 239:

    { (yyval.templateTypeNames) = (yyvsp[0].templateTypeNames); }

    break;

  case 240:

    { (yyval.typeNameParts) = (yyvsp[0].typeNameParts); (yyval.typeNameParts)->packageNamespace = *(yyvsp[-1].strings); delete (yyvsp[-1].strings); }

    break;

  case 241:

    { (yyval.typeNameParts) = (yyvsp[0].typeNameParts); }

    break;

  case 242:

    { (yyval.strings) = new vector<string>(); (yyval.strings)->push_back(*(yyvsp[0].string)); delete (yyvsp[0].string); }

    break;

  case 243:

    { (yyval.strings) = (yyvsp[0].strings); (yyval.strings)->push_back(*(yyvsp[-1].string)); delete (yyvsp[-1].string); }

    break;

  case 244:

    { (yyval.string) = (yyvsp[-1].string); }

    break;

  case 245:

    { (yyval.typeNameParts) = new CTypeNameParts(); (yyval.typeNameParts)->isHash = true;  (yyval.typeNameParts)->name = *(yyvsp[0].string); delete (yyvsp[0].string); }

    break;

  case 246:

    { (yyval.typeNameParts) = new CTypeNameParts(); (yyval.typeNameParts)->isHash = false; (yyval.typeNameParts)->name = *(yyvsp[0].string); delete (yyvsp[0].string); }

    break;

  case 247:

    { (yyval.optionAndTypeList).isOption = false;  (yyval.optionAndTypeList).templateTypeNames = nullptr; }

    break;

  case 248:

    { (yyval.optionAndTypeList).isOption = true;   (yyval.optionAndTypeList).templateTypeNames = nullptr; }

    break;

  case 249:

    { (yyval.optionAndTypeList).isOption = false;  (yyval.optionAndTypeList).templateTypeNames = (yyvsp[0].templateTypeNames); }

    break;

  case 250:

    { (yyval.optionAndTypeList).isOption = true;   (yyval.optionAndTypeList).templateTypeNames = (yyvsp[0].templateTypeNames); }

    break;

  case 251:

    { (yyval.templateTypeNames) = new CTypeNameList(); (yyval.templateTypeNames)->push_back(shared_ptr<CTypeName>((yyvsp[0].typeName))); }

    break;

  case 252:

    { (yyval.templateTypeNames) = (yyvsp[-1].templateTypeNames); }

    break;

  case 253:

    { (yyval.templateTypeNames) = new CTypeNameList(); (yyval.templateTypeNames)->push_back(shared_ptr<CTypeName>((yyvsp[0].typeName))); }

    break;

  case 254:

    { (yyvsp[-2].templateTypeNames)->push_back(shared_ptr<CTypeName>((yyvsp[0].typeName))); }

    break;



      default: break;
    }
  /* User semantic actions sometimes alter yychar, and that requires
     that yytoken be updated with the new translation.  We take the
     approach of translating immediately before every use of yytoken.
     One alternative is translating here after every semantic action,
     but that translation would be missed if the semantic action invokes
     YYABORT, YYACCEPT, or YYERROR immediately after altering yychar or
     if it invokes YYBACKUP.  In the case of YYABORT or YYACCEPT, an
     incorrect destructor might then be invoked immediately.  In the
     case of YYERROR or YYBACKUP, subsequent parser actions might lead
     to an incorrect destructor call or verbose syntax error message
     before the lookahead is translated.  */
  YY_SYMBOL_PRINT ("-> $$ =", yyr1[yyn], &yyval, &yyloc);

  YYPOPSTACK (yylen);
  yylen = 0;
  YY_STACK_PRINT (yyss, yyssp);

  *++yyvsp = yyval;
  *++yylsp = yyloc;

  /* Now 'shift' the result of the reduction.  Determine what state
     that goes to, based on the state we popped back to and the rule
     number reduced by.  */

  yyn = yyr1[yyn];

  yystate = yypgoto[yyn - YYNTOKENS] + *yyssp;
  if (0 <= yystate && yystate <= YYLAST && yycheck[yystate] == *yyssp)
    yystate = yytable[yystate];
  else
    yystate = yydefgoto[yyn - YYNTOKENS];

  goto yynewstate;


/*--------------------------------------.
| yyerrlab -- here on detecting error.  |
`--------------------------------------*/
yyerrlab:
  /* Make sure we have latest lookahead translation.  See comments at
     user semantic actions for why this is necessary.  */
  yytoken = yychar == YYEMPTY ? YYEMPTY : YYTRANSLATE (yychar);

  /* If not already recovering from an error, report this error.  */
  if (!yyerrstatus)
    {
      ++yynerrs;
#if ! YYERROR_VERBOSE
      yyerror (&yylloc, scanner, compiler, parseFile, YY_("syntax error"));
#else
# define YYSYNTAX_ERROR yysyntax_error (&yymsg_alloc, &yymsg, \
                                        yyssp, yytoken)
      {
        char const *yymsgp = YY_("syntax error");
        int yysyntax_error_status;
        yysyntax_error_status = YYSYNTAX_ERROR;
        if (yysyntax_error_status == 0)
          yymsgp = yymsg;
        else if (yysyntax_error_status == 1)
          {
            if (yymsg != yymsgbuf)
              YYSTACK_FREE (yymsg);
            yymsg = (char *) YYSTACK_ALLOC (yymsg_alloc);
            if (!yymsg)
              {
                yymsg = yymsgbuf;
                yymsg_alloc = sizeof yymsgbuf;
                yysyntax_error_status = 2;
              }
            else
              {
                yysyntax_error_status = YYSYNTAX_ERROR;
                yymsgp = yymsg;
              }
          }
        yyerror (&yylloc, scanner, compiler, parseFile, yymsgp);
        if (yysyntax_error_status == 2)
          goto yyexhaustedlab;
      }
# undef YYSYNTAX_ERROR
#endif
    }

  yyerror_range[1] = yylloc;

  if (yyerrstatus == 3)
    {
      /* If just tried and failed to reuse lookahead token after an
         error, discard it.  */

      if (yychar <= YYEOF)
        {
          /* Return failure if at end of input.  */
          if (yychar == YYEOF)
            YYABORT;
        }
      else
        {
          yydestruct ("Error: discarding",
                      yytoken, &yylval, &yylloc, scanner, compiler, parseFile);
          yychar = YYEMPTY;
        }
    }

  /* Else will try to reuse lookahead token after shifting the error
     token.  */
  goto yyerrlab1;


/*---------------------------------------------------.
| yyerrorlab -- error raised explicitly by YYERROR.  |
`---------------------------------------------------*/
yyerrorlab:

  /* Pacify compilers like GCC when the user code never invokes
     YYERROR and the label yyerrorlab therefore never appears in user
     code.  */
  if (/*CONSTCOND*/ 0)
     goto yyerrorlab;

  yyerror_range[1] = yylsp[1-yylen];
  /* Do not reclaim the symbols of the rule whose action triggered
     this YYERROR.  */
  YYPOPSTACK (yylen);
  yylen = 0;
  YY_STACK_PRINT (yyss, yyssp);
  yystate = *yyssp;
  goto yyerrlab1;


/*-------------------------------------------------------------.
| yyerrlab1 -- common code for both syntax error and YYERROR.  |
`-------------------------------------------------------------*/
yyerrlab1:
  yyerrstatus = 3;      /* Each real token shifted decrements this.  */

  for (;;)
    {
      yyn = yypact[yystate];
      if (!yypact_value_is_default (yyn))
        {
          yyn += YYTERROR;
          if (0 <= yyn && yyn <= YYLAST && yycheck[yyn] == YYTERROR)
            {
              yyn = yytable[yyn];
              if (0 < yyn)
                break;
            }
        }

      /* Pop the current state because it cannot handle the error token.  */
      if (yyssp == yyss)
        YYABORT;

      yyerror_range[1] = *yylsp;
      yydestruct ("Error: popping",
                  yystos[yystate], yyvsp, yylsp, scanner, compiler, parseFile);
      YYPOPSTACK (1);
      yystate = *yyssp;
      YY_STACK_PRINT (yyss, yyssp);
    }

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END

  yyerror_range[2] = yylloc;
  /* Using YYLLOC is tempting, but would change the location of
     the lookahead.  YYLOC is available though.  */
  YYLLOC_DEFAULT (yyloc, yyerror_range, 2);
  *++yylsp = yyloc;

  /* Shift the error token.  */
  YY_SYMBOL_PRINT ("Shifting", yystos[yyn], yyvsp, yylsp);

  yystate = yyn;
  goto yynewstate;


/*-------------------------------------.
| yyacceptlab -- YYACCEPT comes here.  |
`-------------------------------------*/
yyacceptlab:
  yyresult = 0;
  goto yyreturn;

/*-----------------------------------.
| yyabortlab -- YYABORT comes here.  |
`-----------------------------------*/
yyabortlab:
  yyresult = 1;
  goto yyreturn;

#if !defined yyoverflow || YYERROR_VERBOSE
/*-------------------------------------------------.
| yyexhaustedlab -- memory exhaustion comes here.  |
`-------------------------------------------------*/
yyexhaustedlab:
  yyerror (&yylloc, scanner, compiler, parseFile, YY_("memory exhausted"));
  yyresult = 2;
  /* Fall through.  */
#endif

yyreturn:
  if (yychar != YYEMPTY)
    {
      /* Make sure we have latest lookahead translation.  See comments at
         user semantic actions for why this is necessary.  */
      yytoken = YYTRANSLATE (yychar);
      yydestruct ("Cleanup: discarding lookahead",
                  yytoken, &yylval, &yylloc, scanner, compiler, parseFile);
    }
  /* Do not reclaim the symbols of the rule whose action triggered
     this YYABORT or YYACCEPT.  */
  YYPOPSTACK (yylen);
  YY_STACK_PRINT (yyss, yyssp);
  while (yyssp != yyss)
    {
      yydestruct ("Cleanup: popping",
                  yystos[*yyssp], yyvsp, yylsp, scanner, compiler, parseFile);
      YYPOPSTACK (1);
    }
#ifndef yyoverflow
  if (yyss != yyssa)
    YYSTACK_FREE (yyss);
#endif
#if YYERROR_VERBOSE
  if (yymsg != yymsgbuf)
    YYSTACK_FREE (yymsg);
#endif
  return yyresult;
}

