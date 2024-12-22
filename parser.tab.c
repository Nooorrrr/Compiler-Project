/* A Bison parser, made by GNU Bison 3.8.2.  */

/* Bison implementation for Yacc-like parsers in C

   Copyright (C) 1984, 1989-1990, 2000-2015, 2018-2021 Free Software Foundation,
   Inc.

   This program is free software: you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation, either version 3 of the License, or
   (at your option) any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program.  If not, see <https://www.gnu.org/licenses/>.  */

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

/* DO NOT RELY ON FEATURES THAT ARE NOT DOCUMENTED in the manual,
   especially those whose name start with YY_ or yy_.  They are
   private implementation details that can be changed or removed.  */

/* All symbols defined below should begin with yy or YY, to avoid
   infringing on user name space.  This should be done even for local
   variables, as they might otherwise be expanded by user macros.
   There are some unavoidable exceptions within include files to
   define necessary library symbols; they are noted "INFRINGES ON
   USER NAME SPACE" below.  */

/* Identify Bison output, and Bison version.  */
#define YYBISON 30802

/* Bison version string.  */
#define YYBISON_VERSION "3.8.2"

/* Skeleton name.  */
#define YYSKELETON_NAME "yacc.c"

/* Pure parsers.  */
#define YYPURE 0

/* Push parsers.  */
#define YYPUSH 0

/* Pull parsers.  */
#define YYPULL 1




/* First part of user prologue.  */
#line 1 "parser.y"

#include <stdio.h>
#include <stdlib.h>
#include "lex.yy.h"  // Inclure le fichier généré par Flex
#include "ts.h"      // Inclure le fichier d'en-tête de la table de symboles
#include "quadruplet.h"  // Le fichier où tu définis ta structure Quadruplet
extern int tempCount;
extern int scope;  // Déclaration de la variable scope
extern TableEntry Tab[1000];  // Table des identifiants et constantes
int scope = 0;  // Initialisation de scope
void yyerror(const char *s);  // Déclaration de la fonction d'erreur

#line 84 "parser.tab.c"

# ifndef YY_CAST
#  ifdef __cplusplus
#   define YY_CAST(Type, Val) static_cast<Type> (Val)
#   define YY_REINTERPRET_CAST(Type, Val) reinterpret_cast<Type> (Val)
#  else
#   define YY_CAST(Type, Val) ((Type) (Val))
#   define YY_REINTERPRET_CAST(Type, Val) ((Type) (Val))
#  endif
# endif
# ifndef YY_NULLPTR
#  if defined __cplusplus
#   if 201103L <= __cplusplus
#    define YY_NULLPTR nullptr
#   else
#    define YY_NULLPTR 0
#   endif
#  else
#   define YY_NULLPTR ((void*)0)
#  endif
# endif

#include "parser.tab.h"
/* Symbol kind.  */
enum yysymbol_kind_t
{
  YYSYMBOL_YYEMPTY = -2,
  YYSYMBOL_YYEOF = 0,                      /* "end of file"  */
  YYSYMBOL_YYerror = 1,                    /* error  */
  YYSYMBOL_YYUNDEF = 2,                    /* "invalid token"  */
  YYSYMBOL_NUMBERINTPOS = 3,               /* NUMBERINTPOS  */
  YYSYMBOL_NUMBERINTNEG = 4,               /* NUMBERINTNEG  */
  YYSYMBOL_NUMBERFLOATPOS = 5,             /* NUMBERFLOATPOS  */
  YYSYMBOL_NUMBERFLOATNEG = 6,             /* NUMBERFLOATNEG  */
  YYSYMBOL_IDENTIFIER = 7,                 /* IDENTIFIER  */
  YYSYMBOL_CARACTERE = 8,                  /* CARACTERE  */
  YYSYMBOL_VAR_GLOBAL = 9,                 /* VAR_GLOBAL  */
  YYSYMBOL_DECLARATION = 10,               /* DECLARATION  */
  YYSYMBOL_INSTRUCTION = 11,               /* INSTRUCTION  */
  YYSYMBOL_INTEGER = 12,                   /* INTEGER  */
  YYSYMBOL_FLOAT = 13,                     /* FLOAT  */
  YYSYMBOL_CHAR = 14,                      /* CHAR  */
  YYSYMBOL_CONST = 15,                     /* CONST  */
  YYSYMBOL_IF = 16,                        /* IF  */
  YYSYMBOL_ELSE = 17,                      /* ELSE  */
  YYSYMBOL_FOR = 18,                       /* FOR  */
  YYSYMBOL_READ = 19,                      /* READ  */
  YYSYMBOL_WRITE = 20,                     /* WRITE  */
  YYSYMBOL_AND = 21,                       /* AND  */
  YYSYMBOL_OR = 22,                        /* OR  */
  YYSYMBOL_NOT = 23,                       /* NOT  */
  YYSYMBOL_EQUAL = 24,                     /* EQUAL  */
  YYSYMBOL_NEQ = 25,                       /* NEQ  */
  YYSYMBOL_GTE = 26,                       /* GTE  */
  YYSYMBOL_LTE = 27,                       /* LTE  */
  YYSYMBOL_GT = 28,                        /* GT  */
  YYSYMBOL_LT = 29,                        /* LT  */
  YYSYMBOL_LBRACE = 30,                    /* LBRACE  */
  YYSYMBOL_RBRACE = 31,                    /* RBRACE  */
  YYSYMBOL_LPAREN = 32,                    /* LPAREN  */
  YYSYMBOL_RPAREN = 33,                    /* RPAREN  */
  YYSYMBOL_LBRACKET = 34,                  /* LBRACKET  */
  YYSYMBOL_RBRACKET = 35,                  /* RBRACKET  */
  YYSYMBOL_SEMICOLON = 36,                 /* SEMICOLON  */
  YYSYMBOL_COMMA = 37,                     /* COMMA  */
  YYSYMBOL_ASSIGN = 38,                    /* ASSIGN  */
  YYSYMBOL_BOUCLESEPARATOR = 39,           /* BOUCLESEPARATOR  */
  YYSYMBOL_PLUS = 40,                      /* PLUS  */
  YYSYMBOL_MINUS = 41,                     /* MINUS  */
  YYSYMBOL_MULT = 42,                      /* MULT  */
  YYSYMBOL_DIV = 43,                       /* DIV  */
  YYSYMBOL_TEXT = 44,                      /* TEXT  */
  YYSYMBOL_YYACCEPT = 45,                  /* $accept  */
  YYSYMBOL_program = 46,                   /* program  */
  YYSYMBOL_varGloballist = 47,             /* varGloballist  */
  YYSYMBOL_declaration = 48,               /* declaration  */
  YYSYMBOL_listevariable = 49,             /* listevariable  */
  YYSYMBOL_affectation = 50,               /* affectation  */
  YYSYMBOL_expression = 51,                /* expression  */
  YYSYMBOL_type = 52,                      /* type  */
  YYSYMBOL_statements = 53,                /* statements  */
  YYSYMBOL_expressionslogic = 54,          /* expressionslogic  */
  YYSYMBOL_statement = 55,                 /* statement  */
  YYSYMBOL_expressionlogic = 56,           /* expressionlogic  */
  YYSYMBOL_init_for = 57,                  /* init_for  */
  YYSYMBOL_expressionwrite = 58,           /* expressionwrite  */
  YYSYMBOL_NUMBERINT = 59,                 /* NUMBERINT  */
  YYSYMBOL_NUMBERFLOAT = 60                /* NUMBERFLOAT  */
};
typedef enum yysymbol_kind_t yysymbol_kind_t;




#ifdef short
# undef short
#endif

/* On compilers that do not define __PTRDIFF_MAX__ etc., make sure
   <limits.h> and (if available) <stdint.h> are included
   so that the code can choose integer types of a good width.  */

#ifndef __PTRDIFF_MAX__
# include <limits.h> /* INFRINGES ON USER NAME SPACE */
# if defined __STDC_VERSION__ && 199901 <= __STDC_VERSION__
#  include <stdint.h> /* INFRINGES ON USER NAME SPACE */
#  define YY_STDINT_H
# endif
#endif

/* Narrow types that promote to a signed type and that can represent a
   signed or unsigned integer of at least N bits.  In tables they can
   save space and decrease cache pressure.  Promoting to a signed type
   helps avoid bugs in integer arithmetic.  */

#ifdef __INT_LEAST8_MAX__
typedef __INT_LEAST8_TYPE__ yytype_int8;
#elif defined YY_STDINT_H
typedef int_least8_t yytype_int8;
#else
typedef signed char yytype_int8;
#endif

#ifdef __INT_LEAST16_MAX__
typedef __INT_LEAST16_TYPE__ yytype_int16;
#elif defined YY_STDINT_H
typedef int_least16_t yytype_int16;
#else
typedef short yytype_int16;
#endif

/* Work around bug in HP-UX 11.23, which defines these macros
   incorrectly for preprocessor constants.  This workaround can likely
   be removed in 2023, as HPE has promised support for HP-UX 11.23
   (aka HP-UX 11i v2) only through the end of 2022; see Table 2 of
   <https://h20195.www2.hpe.com/V2/getpdf.aspx/4AA4-7673ENW.pdf>.  */
#ifdef __hpux
# undef UINT_LEAST8_MAX
# undef UINT_LEAST16_MAX
# define UINT_LEAST8_MAX 255
# define UINT_LEAST16_MAX 65535
#endif

#if defined __UINT_LEAST8_MAX__ && __UINT_LEAST8_MAX__ <= __INT_MAX__
typedef __UINT_LEAST8_TYPE__ yytype_uint8;
#elif (!defined __UINT_LEAST8_MAX__ && defined YY_STDINT_H \
       && UINT_LEAST8_MAX <= INT_MAX)
typedef uint_least8_t yytype_uint8;
#elif !defined __UINT_LEAST8_MAX__ && UCHAR_MAX <= INT_MAX
typedef unsigned char yytype_uint8;
#else
typedef short yytype_uint8;
#endif

#if defined __UINT_LEAST16_MAX__ && __UINT_LEAST16_MAX__ <= __INT_MAX__
typedef __UINT_LEAST16_TYPE__ yytype_uint16;
#elif (!defined __UINT_LEAST16_MAX__ && defined YY_STDINT_H \
       && UINT_LEAST16_MAX <= INT_MAX)
typedef uint_least16_t yytype_uint16;
#elif !defined __UINT_LEAST16_MAX__ && USHRT_MAX <= INT_MAX
typedef unsigned short yytype_uint16;
#else
typedef int yytype_uint16;
#endif

#ifndef YYPTRDIFF_T
# if defined __PTRDIFF_TYPE__ && defined __PTRDIFF_MAX__
#  define YYPTRDIFF_T __PTRDIFF_TYPE__
#  define YYPTRDIFF_MAXIMUM __PTRDIFF_MAX__
# elif defined PTRDIFF_MAX
#  ifndef ptrdiff_t
#   include <stddef.h> /* INFRINGES ON USER NAME SPACE */
#  endif
#  define YYPTRDIFF_T ptrdiff_t
#  define YYPTRDIFF_MAXIMUM PTRDIFF_MAX
# else
#  define YYPTRDIFF_T long
#  define YYPTRDIFF_MAXIMUM LONG_MAX
# endif
#endif

#ifndef YYSIZE_T
# ifdef __SIZE_TYPE__
#  define YYSIZE_T __SIZE_TYPE__
# elif defined size_t
#  define YYSIZE_T size_t
# elif defined __STDC_VERSION__ && 199901 <= __STDC_VERSION__
#  include <stddef.h> /* INFRINGES ON USER NAME SPACE */
#  define YYSIZE_T size_t
# else
#  define YYSIZE_T unsigned
# endif
#endif

#define YYSIZE_MAXIMUM                                  \
  YY_CAST (YYPTRDIFF_T,                                 \
           (YYPTRDIFF_MAXIMUM < YY_CAST (YYSIZE_T, -1)  \
            ? YYPTRDIFF_MAXIMUM                         \
            : YY_CAST (YYSIZE_T, -1)))

#define YYSIZEOF(X) YY_CAST (YYPTRDIFF_T, sizeof (X))


/* Stored state numbers (used for stacks). */
typedef yytype_uint8 yy_state_t;

/* State numbers in computations.  */
typedef int yy_state_fast_t;

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


#ifndef YY_ATTRIBUTE_PURE
# if defined __GNUC__ && 2 < __GNUC__ + (96 <= __GNUC_MINOR__)
#  define YY_ATTRIBUTE_PURE __attribute__ ((__pure__))
# else
#  define YY_ATTRIBUTE_PURE
# endif
#endif

#ifndef YY_ATTRIBUTE_UNUSED
# if defined __GNUC__ && 2 < __GNUC__ + (7 <= __GNUC_MINOR__)
#  define YY_ATTRIBUTE_UNUSED __attribute__ ((__unused__))
# else
#  define YY_ATTRIBUTE_UNUSED
# endif
#endif

/* Suppress unused-variable warnings by "using" E.  */
#if ! defined lint || defined __GNUC__
# define YY_USE(E) ((void) (E))
#else
# define YY_USE(E) /* empty */
#endif

/* Suppress an incorrect diagnostic about yylval being uninitialized.  */
#if defined __GNUC__ && ! defined __ICC && 406 <= __GNUC__ * 100 + __GNUC_MINOR__
# if __GNUC__ * 100 + __GNUC_MINOR__ < 407
#  define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN                           \
    _Pragma ("GCC diagnostic push")                                     \
    _Pragma ("GCC diagnostic ignored \"-Wuninitialized\"")
# else
#  define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN                           \
    _Pragma ("GCC diagnostic push")                                     \
    _Pragma ("GCC diagnostic ignored \"-Wuninitialized\"")              \
    _Pragma ("GCC diagnostic ignored \"-Wmaybe-uninitialized\"")
# endif
# define YY_IGNORE_MAYBE_UNINITIALIZED_END      \
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

#if defined __cplusplus && defined __GNUC__ && ! defined __ICC && 6 <= __GNUC__
# define YY_IGNORE_USELESS_CAST_BEGIN                          \
    _Pragma ("GCC diagnostic push")                            \
    _Pragma ("GCC diagnostic ignored \"-Wuseless-cast\"")
# define YY_IGNORE_USELESS_CAST_END            \
    _Pragma ("GCC diagnostic pop")
#endif
#ifndef YY_IGNORE_USELESS_CAST_BEGIN
# define YY_IGNORE_USELESS_CAST_BEGIN
# define YY_IGNORE_USELESS_CAST_END
#endif


#define YY_ASSERT(E) ((void) (0 && (E)))

#if !defined yyoverflow

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
#endif /* !defined yyoverflow */

#if (! defined yyoverflow \
     && (! defined __cplusplus \
         || (defined YYSTYPE_IS_TRIVIAL && YYSTYPE_IS_TRIVIAL)))

/* A type that is properly aligned for any stack member.  */
union yyalloc
{
  yy_state_t yyss_alloc;
  YYSTYPE yyvs_alloc;
};

/* The size of the maximum gap between one aligned stack and the next.  */
# define YYSTACK_GAP_MAXIMUM (YYSIZEOF (union yyalloc) - 1)

/* The size of an array large to enough to hold all stacks, each with
   N elements.  */
# define YYSTACK_BYTES(N) \
     ((N) * (YYSIZEOF (yy_state_t) + YYSIZEOF (YYSTYPE)) \
      + YYSTACK_GAP_MAXIMUM)

# define YYCOPY_NEEDED 1

/* Relocate STACK from its old location to the new one.  The
   local variables YYSIZE and YYSTACKSIZE give the old and new number of
   elements in the stack, and YYPTR gives the new location of the
   stack.  Advance YYPTR to a properly aligned location for the next
   stack.  */
# define YYSTACK_RELOCATE(Stack_alloc, Stack)                           \
    do                                                                  \
      {                                                                 \
        YYPTRDIFF_T yynewbytes;                                         \
        YYCOPY (&yyptr->Stack_alloc, Stack, yysize);                    \
        Stack = &yyptr->Stack_alloc;                                    \
        yynewbytes = yystacksize * YYSIZEOF (*Stack) + YYSTACK_GAP_MAXIMUM; \
        yyptr += yynewbytes / YYSIZEOF (*yyptr);                        \
      }                                                                 \
    while (0)

#endif

#if defined YYCOPY_NEEDED && YYCOPY_NEEDED
/* Copy COUNT objects from SRC to DST.  The source and destination do
   not overlap.  */
# ifndef YYCOPY
#  if defined __GNUC__ && 1 < __GNUC__
#   define YYCOPY(Dst, Src, Count) \
      __builtin_memcpy (Dst, Src, YY_CAST (YYSIZE_T, (Count)) * sizeof (*(Src)))
#  else
#   define YYCOPY(Dst, Src, Count)              \
      do                                        \
        {                                       \
          YYPTRDIFF_T yyi;                      \
          for (yyi = 0; yyi < (Count); yyi++)   \
            (Dst)[yyi] = (Src)[yyi];            \
        }                                       \
      while (0)
#  endif
# endif
#endif /* !YYCOPY_NEEDED */

/* YYFINAL -- State number of the termination state.  */
#define YYFINAL  4
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   195

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  45
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  16
/* YYNRULES -- Number of rules.  */
#define YYNRULES  51
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  129

/* YYMAXUTOK -- Last valid token kind.  */
#define YYMAXUTOK   299


/* YYTRANSLATE(TOKEN-NUM) -- Symbol number corresponding to TOKEN-NUM
   as returned by yylex, with out-of-bounds checking.  */
#define YYTRANSLATE(YYX)                                \
  (0 <= (YYX) && (YYX) <= YYMAXUTOK                     \
   ? YY_CAST (yysymbol_kind_t, yytranslate[YYX])        \
   : YYSYMBOL_YYUNDEF)

/* YYTRANSLATE[TOKEN-NUM] -- Symbol number corresponding to TOKEN-NUM
   as returned by yylex.  */
static const yytype_int8 yytranslate[] =
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
      35,    36,    37,    38,    39,    40,    41,    42,    43,    44
};

#if YYDEBUG
/* YYRLINE[YYN] -- Source line where rule number YYN was defined.  */
static const yytype_int16 yyrline[] =
{
       0,    85,    85,    89,    90,    94,   110,   121,   133,   144,
     155,   161,   168,   227,   250,   261,   272,   281,   310,   340,
     371,   408,   415,   416,   417,   423,   424,   428,   429,   433,
     434,   467,   505,   511,   518,   570,   577,   605,   656,   684,
     713,   749,   785,   818,   830,   837,   838,   839,   849,   850,
     854,   855
};
#endif

/** Accessing symbol of state STATE.  */
#define YY_ACCESSING_SYMBOL(State) YY_CAST (yysymbol_kind_t, yystos[State])

#if YYDEBUG || 0
/* The user-facing name of the symbol whose (internal) number is
   YYSYMBOL.  No bounds checking.  */
static const char *yysymbol_name (yysymbol_kind_t yysymbol) YY_ATTRIBUTE_UNUSED;

/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "\"end of file\"", "error", "\"invalid token\"", "NUMBERINTPOS",
  "NUMBERINTNEG", "NUMBERFLOATPOS", "NUMBERFLOATNEG", "IDENTIFIER",
  "CARACTERE", "VAR_GLOBAL", "DECLARATION", "INSTRUCTION", "INTEGER",
  "FLOAT", "CHAR", "CONST", "IF", "ELSE", "FOR", "READ", "WRITE", "AND",
  "OR", "NOT", "EQUAL", "NEQ", "GTE", "LTE", "GT", "LT", "LBRACE",
  "RBRACE", "LPAREN", "RPAREN", "LBRACKET", "RBRACKET", "SEMICOLON",
  "COMMA", "ASSIGN", "BOUCLESEPARATOR", "PLUS", "MINUS", "MULT", "DIV",
  "TEXT", "$accept", "program", "varGloballist", "declaration",
  "listevariable", "affectation", "expression", "type", "statements",
  "expressionslogic", "statement", "expressionlogic", "init_for",
  "expressionwrite", "NUMBERINT", "NUMBERFLOAT", YY_NULLPTR
};

static const char *
yysymbol_name (yysymbol_kind_t yysymbol)
{
  return yytname[yysymbol];
}
#endif

#define YYPACT_NINF (-82)

#define yypact_value_is_default(Yyn) \
  ((Yyn) == YYPACT_NINF)

#define YYTABLE_NINF (-1)

#define yytable_value_is_error(Yyn) \
  0

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
static const yytype_int16 yypact[] =
{
      -8,   -14,    28,   -82,   -82,   111,   -82,   -82,   -82,     6,
      34,   -82,    52,    70,    36,    47,   -13,    72,   -82,   114,
     -82,    83,   133,   119,   105,   -82,   -82,   -82,   -82,   -82,
      82,   107,   115,   158,   134,   -82,   -82,   -82,   141,   -82,
     128,   135,   140,   142,   143,   144,   -82,    -5,   -82,    50,
      44,   170,   171,    -3,   -82,   -82,   -82,   -82,    50,    59,
     -82,   -82,    44,    44,    87,     2,    43,   145,   146,   147,
     149,   150,   148,   112,   -82,    50,    50,    50,    50,   -82,
      79,     0,    50,    50,    50,    50,    50,   152,    43,    44,
      44,    50,    50,   153,    -3,    -3,   154,   -82,    26,    26,
     -82,   -82,   -82,   125,   125,   125,   125,   125,   128,   -82,
     -82,   125,   121,   -82,   -82,   -82,   -82,    55,    50,   162,
     116,   161,   163,   128,   128,    73,    78,   -82,   -82
};

/* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
   Performed when YYTABLE does not specify something else to do.  Zero
   means the default is an error.  */
static const yytype_int8 yydefact[] =
{
       0,     0,     0,     4,     1,     0,    22,    23,    24,     0,
       0,     3,     0,     0,     0,    11,     0,     0,     4,     0,
       5,     0,     0,     0,     0,    10,    48,    49,    51,    50,
       0,     0,     0,     0,     0,     8,     6,     7,     0,     9,
       0,     0,     0,     0,     0,     0,    29,     0,    25,     0,
       0,     0,     0,     0,     2,    26,    13,    16,     0,     0,
      14,    15,     0,     0,     0,     0,    27,     0,     0,     0,
      44,    45,     0,     0,    12,     0,     0,     0,     0,    42,
       0,     0,     0,     0,     0,     0,     0,     0,    28,     0,
       0,     0,     0,     0,     0,     0,     0,    21,    17,    18,
      19,    20,    35,    34,    39,    37,    38,    36,     0,    40,
      41,    43,     0,    32,    47,    46,    33,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,    30,    31
};

/* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
     -82,   -82,   166,   -82,   -82,   -82,   -46,   179,   -81,   -82,
     -47,    -2,   -82,   -11,   172,   173
};

/* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int8 yydefgoto[] =
{
       0,     2,     5,    11,    16,    46,    64,    12,    47,    65,
      48,    66,    68,    72,    60,    61
};

/* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule whose
   number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_uint8 yytable[] =
{
      55,     1,    41,    59,    70,    26,    27,    28,    29,    56,
      57,    42,    73,    43,    44,    45,     3,    80,     6,     7,
       8,    89,    90,    20,    21,    62,    54,   117,     4,    98,
      99,   100,   101,   102,    63,    87,   103,   104,   105,   106,
     107,    71,   125,   126,    14,   111,   112,    26,    27,    28,
      29,    56,    57,    26,    27,    28,    29,    56,    57,    15,
      79,    81,    41,    88,    89,    90,    18,    62,    77,    78,
      55,    42,   120,    43,    44,    45,    63,    17,    55,    55,
      41,    19,    58,   114,   115,    41,   119,   109,   110,    42,
      25,    43,    44,    45,    42,    74,    43,    44,    45,    75,
      76,    77,    78,    82,   127,    83,    84,    85,    86,   128,
      22,    82,    97,    83,    84,    85,    86,    24,    35,    75,
      76,    77,    78,     6,     7,     8,     9,    75,    76,    77,
      78,     6,     7,     8,     9,    41,    26,    27,    28,    29,
      34,    30,    10,    36,    42,    97,    43,    44,    45,   122,
      33,    37,    75,    76,    77,    78,    75,    76,    77,    78,
     118,    75,    76,    77,    78,    75,    76,    77,    78,    38,
      39,    40,    50,    49,    51,    52,    53,    67,    69,   121,
      93,    96,   108,    91,    23,    92,    94,    95,    13,   113,
     116,   123,     0,   124,    31,    32
};

static const yytype_int8 yycheck[] =
{
      47,     9,     7,    49,     7,     3,     4,     5,     6,     7,
       8,    16,    58,    18,    19,    20,    30,    63,    12,    13,
      14,    21,    22,    36,    37,    23,    31,   108,     0,    75,
      76,    77,    78,    33,    32,    33,    82,    83,    84,    85,
      86,    44,   123,   124,    10,    91,    92,     3,     4,     5,
       6,     7,     8,     3,     4,     5,     6,     7,     8,     7,
      62,    63,     7,    65,    21,    22,    30,    23,    42,    43,
     117,    16,   118,    18,    19,    20,    32,     7,   125,   126,
       7,    34,    32,    94,    95,     7,    31,    89,    90,    16,
       7,    18,    19,    20,    16,    36,    18,    19,    20,    40,
      41,    42,    43,    24,    31,    26,    27,    28,    29,    31,
      38,    24,    33,    26,    27,    28,    29,     3,    36,    40,
      41,    42,    43,    12,    13,    14,    15,    40,    41,    42,
      43,    12,    13,    14,    15,     7,     3,     4,     5,     6,
      35,     8,    31,    36,    16,    33,    18,    19,    20,    33,
      31,    36,    40,    41,    42,    43,    40,    41,    42,    43,
      39,    40,    41,    42,    43,    40,    41,    42,    43,    11,
      36,    30,    32,    38,    32,    32,    32,     7,     7,    17,
      33,    33,    30,    38,    18,    39,    37,    37,     9,    36,
      36,    30,    -1,    30,    22,    22
};

/* YYSTOS[STATE-NUM] -- The symbol kind of the accessing symbol of
   state STATE-NUM.  */
static const yytype_int8 yystos[] =
{
       0,     9,    46,    30,     0,    47,    12,    13,    14,    15,
      31,    48,    52,    52,    10,     7,    49,     7,    30,    34,
      36,    37,    38,    47,     3,     7,     3,     4,     5,     6,
       8,    59,    60,    31,    35,    36,    36,    36,    11,    36,
      30,     7,    16,    18,    19,    20,    50,    53,    55,    38,
      32,    32,    32,    32,    31,    55,     7,     8,    32,    51,
      59,    60,    23,    32,    51,    54,    56,     7,    57,     7,
       7,    44,    58,    51,    36,    40,    41,    42,    43,    56,
      51,    56,    24,    26,    27,    28,    29,    33,    56,    21,
      22,    38,    39,    33,    37,    37,    33,    33,    51,    51,
      51,    51,    33,    51,    51,    51,    51,    51,    30,    56,
      56,    51,    51,    36,    58,    58,    36,    53,    39,    31,
      51,    17,    33,    30,    30,    53,    53,    31,    31
};

/* YYR1[RULE-NUM] -- Symbol kind of the left-hand side of rule RULE-NUM.  */
static const yytype_int8 yyr1[] =
{
       0,    45,    46,    47,    47,    48,    48,    48,    48,    48,
      49,    49,    50,    51,    51,    51,    51,    51,    51,    51,
      51,    51,    52,    52,    52,    53,    53,    54,    54,    55,
      55,    55,    55,    55,    56,    56,    56,    56,    56,    56,
      56,    56,    56,    57,    58,    58,    58,    58,    59,    59,
      60,    60
};

/* YYR2[RULE-NUM] -- Number of symbols on the right-hand side of rule RULE-NUM.  */
static const yytype_int8 yyr2[] =
{
       0,     2,    12,     2,     0,     3,     6,     6,     6,     6,
       3,     1,     4,     1,     1,     1,     1,     3,     3,     3,
       3,     3,     1,     1,     1,     1,     2,     1,     2,     1,
      11,    11,     5,     5,     3,     3,     3,     3,     3,     3,
       3,     3,     2,     3,     1,     1,     3,     3,     1,     1,
       1,     1
};


enum { YYENOMEM = -2 };

#define yyerrok         (yyerrstatus = 0)
#define yyclearin       (yychar = YYEMPTY)

#define YYACCEPT        goto yyacceptlab
#define YYABORT         goto yyabortlab
#define YYERROR         goto yyerrorlab
#define YYNOMEM         goto yyexhaustedlab


#define YYRECOVERING()  (!!yyerrstatus)

#define YYBACKUP(Token, Value)                                    \
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
        yyerror (YY_("syntax error: cannot back up")); \
        YYERROR;                                                  \
      }                                                           \
  while (0)

/* Backward compatibility with an undocumented macro.
   Use YYerror or YYUNDEF. */
#define YYERRCODE YYUNDEF


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




# define YY_SYMBOL_PRINT(Title, Kind, Value, Location)                    \
do {                                                                      \
  if (yydebug)                                                            \
    {                                                                     \
      YYFPRINTF (stderr, "%s ", Title);                                   \
      yy_symbol_print (stderr,                                            \
                  Kind, Value); \
      YYFPRINTF (stderr, "\n");                                           \
    }                                                                     \
} while (0)


/*-----------------------------------.
| Print this symbol's value on YYO.  |
`-----------------------------------*/

static void
yy_symbol_value_print (FILE *yyo,
                       yysymbol_kind_t yykind, YYSTYPE const * const yyvaluep)
{
  FILE *yyoutput = yyo;
  YY_USE (yyoutput);
  if (!yyvaluep)
    return;
  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  YY_USE (yykind);
  YY_IGNORE_MAYBE_UNINITIALIZED_END
}


/*---------------------------.
| Print this symbol on YYO.  |
`---------------------------*/

static void
yy_symbol_print (FILE *yyo,
                 yysymbol_kind_t yykind, YYSTYPE const * const yyvaluep)
{
  YYFPRINTF (yyo, "%s %s (",
             yykind < YYNTOKENS ? "token" : "nterm", yysymbol_name (yykind));

  yy_symbol_value_print (yyo, yykind, yyvaluep);
  YYFPRINTF (yyo, ")");
}

/*------------------------------------------------------------------.
| yy_stack_print -- Print the state stack from its BOTTOM up to its |
| TOP (included).                                                   |
`------------------------------------------------------------------*/

static void
yy_stack_print (yy_state_t *yybottom, yy_state_t *yytop)
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
yy_reduce_print (yy_state_t *yyssp, YYSTYPE *yyvsp,
                 int yyrule)
{
  int yylno = yyrline[yyrule];
  int yynrhs = yyr2[yyrule];
  int yyi;
  YYFPRINTF (stderr, "Reducing stack by rule %d (line %d):\n",
             yyrule - 1, yylno);
  /* The symbols being reduced.  */
  for (yyi = 0; yyi < yynrhs; yyi++)
    {
      YYFPRINTF (stderr, "   $%d = ", yyi + 1);
      yy_symbol_print (stderr,
                       YY_ACCESSING_SYMBOL (+yyssp[yyi + 1 - yynrhs]),
                       &yyvsp[(yyi + 1) - (yynrhs)]);
      YYFPRINTF (stderr, "\n");
    }
}

# define YY_REDUCE_PRINT(Rule)          \
do {                                    \
  if (yydebug)                          \
    yy_reduce_print (yyssp, yyvsp, Rule); \
} while (0)

/* Nonzero means print parse trace.  It is left uninitialized so that
   multiple parsers can coexist.  */
int yydebug;
#else /* !YYDEBUG */
# define YYDPRINTF(Args) ((void) 0)
# define YY_SYMBOL_PRINT(Title, Kind, Value, Location)
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






/*-----------------------------------------------.
| Release the memory associated to this symbol.  |
`-----------------------------------------------*/

static void
yydestruct (const char *yymsg,
            yysymbol_kind_t yykind, YYSTYPE *yyvaluep)
{
  YY_USE (yyvaluep);
  if (!yymsg)
    yymsg = "Deleting";
  YY_SYMBOL_PRINT (yymsg, yykind, yyvaluep, yylocationp);

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  YY_USE (yykind);
  YY_IGNORE_MAYBE_UNINITIALIZED_END
}


/* Lookahead token kind.  */
int yychar;

/* The semantic value of the lookahead symbol.  */
YYSTYPE yylval;
/* Number of syntax errors so far.  */
int yynerrs;




/*----------.
| yyparse.  |
`----------*/

int
yyparse (void)
{
    yy_state_fast_t yystate = 0;
    /* Number of tokens to shift before error messages enabled.  */
    int yyerrstatus = 0;

    /* Refer to the stacks through separate pointers, to allow yyoverflow
       to reallocate them elsewhere.  */

    /* Their size.  */
    YYPTRDIFF_T yystacksize = YYINITDEPTH;

    /* The state stack: array, bottom, top.  */
    yy_state_t yyssa[YYINITDEPTH];
    yy_state_t *yyss = yyssa;
    yy_state_t *yyssp = yyss;

    /* The semantic value stack: array, bottom, top.  */
    YYSTYPE yyvsa[YYINITDEPTH];
    YYSTYPE *yyvs = yyvsa;
    YYSTYPE *yyvsp = yyvs;

  int yyn;
  /* The return value of yyparse.  */
  int yyresult;
  /* Lookahead symbol kind.  */
  yysymbol_kind_t yytoken = YYSYMBOL_YYEMPTY;
  /* The variables used to return semantic value and location from the
     action routines.  */
  YYSTYPE yyval;



#define YYPOPSTACK(N)   (yyvsp -= (N), yyssp -= (N))

  /* The number of symbols on the RHS of the reduced rule.
     Keep to zero when no symbol should be popped.  */
  int yylen = 0;

  YYDPRINTF ((stderr, "Starting parse\n"));

  yychar = YYEMPTY; /* Cause a token to be read.  */

  goto yysetstate;


/*------------------------------------------------------------.
| yynewstate -- push a new state, which is found in yystate.  |
`------------------------------------------------------------*/
yynewstate:
  /* In all cases, when you get here, the value and location stacks
     have just been pushed.  So pushing a state here evens the stacks.  */
  yyssp++;


/*--------------------------------------------------------------------.
| yysetstate -- set current state (the top of the stack) to yystate.  |
`--------------------------------------------------------------------*/
yysetstate:
  YYDPRINTF ((stderr, "Entering state %d\n", yystate));
  YY_ASSERT (0 <= yystate && yystate < YYNSTATES);
  YY_IGNORE_USELESS_CAST_BEGIN
  *yyssp = YY_CAST (yy_state_t, yystate);
  YY_IGNORE_USELESS_CAST_END
  YY_STACK_PRINT (yyss, yyssp);

  if (yyss + yystacksize - 1 <= yyssp)
#if !defined yyoverflow && !defined YYSTACK_RELOCATE
    YYNOMEM;
#else
    {
      /* Get the current used size of the three stacks, in elements.  */
      YYPTRDIFF_T yysize = yyssp - yyss + 1;

# if defined yyoverflow
      {
        /* Give user a chance to reallocate the stack.  Use copies of
           these so that the &'s don't force the real ones into
           memory.  */
        yy_state_t *yyss1 = yyss;
        YYSTYPE *yyvs1 = yyvs;

        /* Each stack pointer address is followed by the size of the
           data in use in that stack, in bytes.  This used to be a
           conditional around just the two extra args, but that might
           be undefined if yyoverflow is a macro.  */
        yyoverflow (YY_("memory exhausted"),
                    &yyss1, yysize * YYSIZEOF (*yyssp),
                    &yyvs1, yysize * YYSIZEOF (*yyvsp),
                    &yystacksize);
        yyss = yyss1;
        yyvs = yyvs1;
      }
# else /* defined YYSTACK_RELOCATE */
      /* Extend the stack our own way.  */
      if (YYMAXDEPTH <= yystacksize)
        YYNOMEM;
      yystacksize *= 2;
      if (YYMAXDEPTH < yystacksize)
        yystacksize = YYMAXDEPTH;

      {
        yy_state_t *yyss1 = yyss;
        union yyalloc *yyptr =
          YY_CAST (union yyalloc *,
                   YYSTACK_ALLOC (YY_CAST (YYSIZE_T, YYSTACK_BYTES (yystacksize))));
        if (! yyptr)
          YYNOMEM;
        YYSTACK_RELOCATE (yyss_alloc, yyss);
        YYSTACK_RELOCATE (yyvs_alloc, yyvs);
#  undef YYSTACK_RELOCATE
        if (yyss1 != yyssa)
          YYSTACK_FREE (yyss1);
      }
# endif

      yyssp = yyss + yysize - 1;
      yyvsp = yyvs + yysize - 1;

      YY_IGNORE_USELESS_CAST_BEGIN
      YYDPRINTF ((stderr, "Stack size increased to %ld\n",
                  YY_CAST (long, yystacksize)));
      YY_IGNORE_USELESS_CAST_END

      if (yyss + yystacksize - 1 <= yyssp)
        YYABORT;
    }
#endif /* !defined yyoverflow && !defined YYSTACK_RELOCATE */


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

  /* YYCHAR is either empty, or end-of-input, or a valid lookahead.  */
  if (yychar == YYEMPTY)
    {
      YYDPRINTF ((stderr, "Reading a token\n"));
      yychar = yylex ();
    }

  if (yychar <= YYEOF)
    {
      yychar = YYEOF;
      yytoken = YYSYMBOL_YYEOF;
      YYDPRINTF ((stderr, "Now at end of input.\n"));
    }
  else if (yychar == YYerror)
    {
      /* The scanner already issued an error message, process directly
         to error recovery.  But do not keep the error token as
         lookahead, it is too special and may lead us to an endless
         loop in error recovery. */
      yychar = YYUNDEF;
      yytoken = YYSYMBOL_YYerror;
      goto yyerrlab1;
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
  yystate = yyn;
  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END

  /* Discard the shifted token.  */
  yychar = YYEMPTY;
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
| yyreduce -- do a reduction.  |
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


  YY_REDUCE_PRINT (yyn);
  switch (yyn)
    {
  case 5: /* declaration: type listevariable SEMICOLON  */
#line 94 "parser.y"
                                 {
        for (int i = 0; i < (yyvsp[-1].varList).count; i++) {
            if (rechercher((yyvsp[-1].varList).variables[i]) != NULL) {
                yyerror("Variable déjà déclarée.");
                return 0;
            } else {
                if (strcmp((yyvsp[-2].chaine), "INTEGER") == 0) {
                    inserer((yyvsp[-1].varList).variables[i], (yyvsp[-2].chaine), 0, scope, 0, 0, 0);  // Insérer sans valeur initiale pour une variable
                } else if (strcmp((yyvsp[-2].chaine), "FLOAT") == 0) {
                    inserer((yyvsp[-1].varList).variables[i], (yyvsp[-2].chaine), 0.0f, scope, 0, 0, 0);  // Insérer un flottant
                } else if (strcmp((yyvsp[-2].chaine), "CHAR") == 0) {
                    inserer((yyvsp[-1].varList).variables[i], (yyvsp[-2].chaine), '\0', scope, 0, 0, 0);  // Insérer un caractère (valeur nulle par défaut)
                }
            }
        }
    }
#line 1236 "parser.tab.c"
    break;

  case 6: /* declaration: CONST type IDENTIFIER ASSIGN NUMBERINT SEMICOLON  */
#line 110 "parser.y"
                                                       {
        if (rechercher((yyvsp[-3].id).name) != NULL) {
            yyerror("Variable déjà déclarée.");
            return 0;
        } else {
            inserer((yyvsp[-3].id).name, (yyvsp[-4].chaine), (yyvsp[-1].entier), scope, 0, 0, 1);  // Insérer la constante entière
        }
         char var2[20];
        sprintf(var2,"%d",  (yyvsp[-1].entier));
        generer("=",var2, "", (yyvsp[-3].id).name);
    }
#line 1252 "parser.tab.c"
    break;

  case 7: /* declaration: CONST type IDENTIFIER ASSIGN NUMBERFLOAT SEMICOLON  */
#line 121 "parser.y"
                                                         {
        if (rechercher((yyvsp[-3].id).name) != NULL) {
            yyerror("Variable déjà déclarée.");
            return 0;
        } else {
            inserer((yyvsp[-3].id).name, (yyvsp[-4].chaine), (yyvsp[-1].flottant), scope, 0, 0, 1);  // Insérer la constante flottante
        }
         char var2[20];
        sprintf(var2,"%f",  (yyvsp[-1].flottant));
        generer("=",var2, "", (yyvsp[-3].id).name);
        
    }
#line 1269 "parser.tab.c"
    break;

  case 8: /* declaration: CONST type IDENTIFIER ASSIGN CARACTERE SEMICOLON  */
#line 133 "parser.y"
                                                       {
        if (rechercher((yyvsp[-3].id).name) != NULL) {
            yyerror("Variable déjà déclarée.");
            return 0;
        } else {
            inserer((yyvsp[-3].id).name, (yyvsp[-4].chaine), (yyvsp[-1].car), scope, 0, 0, 1);  // Insérer la constante flottante
        }
             char var2[20];
        sprintf(var2,"%c",  (yyvsp[-1].car));
        generer("=",var2, "", (yyvsp[-3].id).name);
    }
#line 1285 "parser.tab.c"
    break;

  case 9: /* declaration: type IDENTIFIER LBRACKET NUMBERINTPOS RBRACKET SEMICOLON  */
#line 144 "parser.y"
                                                               {
        if (rechercher((yyvsp[-4].id).name) != NULL) {
            yyerror("Variable déjà déclarée.");
            return 0;
        } else {
            inserer((yyvsp[-4].id).name, (yyvsp[-5].chaine), 0, scope, 0, (yyvsp[-2].entier), 1);
        }
    }
#line 1298 "parser.tab.c"
    break;

  case 10: /* listevariable: listevariable COMMA IDENTIFIER  */
#line 155 "parser.y"
                                   {
        (yyval.varList) = (yyvsp[-2].varList);  // Copier la liste précédente
        (yyval.varList).count++;  // Incrémenter le namebre d'éléments
        (yyval.varList).variables = realloc((yyval.varList).variables, sizeof(char*) * (yyval.varList).count);
        (yyval.varList).variables[(yyval.varList).count - 1] = (yyvsp[0].id).name;  // Ajouter la nouvelle variable
    }
#line 1309 "parser.tab.c"
    break;

  case 11: /* listevariable: IDENTIFIER  */
#line 161 "parser.y"
                 {
        (yyval.varList).count = 1;  // Une seule variable
        (yyval.varList).variables = malloc(sizeof(char*));
        (yyval.varList).variables[0] = (yyvsp[0].id).name;
    }
#line 1319 "parser.tab.c"
    break;

  case 12: /* affectation: IDENTIFIER ASSIGN expression SEMICOLON  */
#line 168 "parser.y"
                                           {
        // Vérification si la variable est déclarée
        TableEntry *varEntry = rechercher((yyvsp[-3].id).name);
        if (varEntry == NULL) {
            yyerror("Variable non déclarée.");
            return 0;
        }

        // Vérification si la variable est une constante et ne peut pas être modifiée
        if (varEntry->isConst == 1) {
            yyerror("Vous essayez de modifier une constante.");
            return 0;
        }

        // Vérification de la compatibilité des types entre la variable et l'expression
        if(strcmp(varEntry->type,"INTEGER")== 0||strcmp(varEntry->type,"CHAR")== 0){
        if (strcmp(varEntry->type, (yyvsp[-1].exprari).type) != 0) {
            yyerror("Type incompatible dans l'affectation.test1");
            return 0;
        }
        }
        if(strcmp(varEntry->type,"FLOAT")== 0){
            if (strcmp((yyvsp[-1].exprari).type, "CHAR") == 0) {
            yyerror("Type incompatible dans l'affectation.2");
            return 0;
        }
        }
         if(strcmp(varEntry->type,"CHAR")== 0){
            if (strcmp((yyvsp[-1].exprari).type, "CHAR") != 0) {
            yyerror("Type incompatible dans l'affectation.3");
            return 0;
        }
        }

        // Modification de la valeur en fonction du type
        if (strcmp(varEntry->type, "INTEGER") == 0) {
            varEntry->val.ival = (yyvsp[-1].exprari).value.ival;  // Affecter un entier
            generer("=",(yyvsp[-1].exprari).name, "", varEntry->name);
        } else if (strcmp(varEntry->type, "FLOAT") == 0) {
            varEntry->val.fval = (yyvsp[-1].exprari).value.fval;  // Affecter un flottant
            if(strcmp((yyvsp[-1].exprari).type,"INTEGER") == 0){
            
               
                generer("=",(yyvsp[-1].exprari).name, "", varEntry->name);
                varEntry->val.fval = (float) (yyvsp[-1].exprari).value.fval;
            }
        } else if (strcmp(varEntry->type, "CHAR") == 0) {
       
            generer("=",(yyvsp[-1].exprari).name, "", varEntry->name);
            varEntry->val.cval = (yyvsp[-1].exprari).value.cval;  // Affecter un caractère
        } else {
            yyerror("Type inconnu pour l'affectation.4");
            return 0;
        } 
    
    }
#line 1380 "parser.tab.c"
    break;

  case 13: /* expression: IDENTIFIER  */
#line 227 "parser.y"
               {  // Cas où l'expression est une variable
        TableEntry *entry = rechercher((yyvsp[0].id).name);
        if (entry == NULL) {
            yyerror("Variable non déclarée.");
            return 0;
        }

        (yyval.exprari).type = entry->type;

        // Affectation de la valeur en fonction du type de la variable
        if (strcmp(entry->type, "INTEGER") == 0) {
            (yyval.exprari).value.ival = entry->val.ival;
        } else if (strcmp(entry->type, "FLOAT") == 0) {
            (yyval.exprari).value.fval = entry->val.fval;
        } else if (strcmp(entry->type, "CHAR") == 0) {
            (yyval.exprari).value.cval = entry->val.cval;
        } else {
            yyerror("Type inconnu pour l'expression.");
            return 0;
        }
        (yyval.exprari).name=(yyvsp[0].id).name;
      
    }
#line 1408 "parser.tab.c"
    break;

  case 14: /* expression: NUMBERINT  */
#line 250 "parser.y"
                {  // Cas où l'expression est un entier
        (yyval.exprari).type = "INTEGER";
        (yyval.exprari).value.ival = (yyvsp[0].entier);  // La valeur entière
        // Générer un quadruplet pour l'entier
        char val[20];
        sprintf(val, "%d", (yyvsp[0].entier));
         (yyval.exprari).name=val;
          
      
         
    }
#line 1424 "parser.tab.c"
    break;

  case 15: /* expression: NUMBERFLOAT  */
#line 261 "parser.y"
                  {  // Cas où l'expression est un flottant
        (yyval.exprari).type = "FLOAT";
        (yyval.exprari).value.fval = (yyvsp[0].flottant);  // La valeur flottante


        // Générer un quadruplet pour le flottant
       char val[20];
        sprintf(val, "%f", (yyvsp[0].flottant));  // Corrected format specifier
         (yyval.exprari).name=val;
         printf("%s",val);
    }
#line 1440 "parser.tab.c"
    break;

  case 16: /* expression: CARACTERE  */
#line 272 "parser.y"
                {  // Cas où l'expression est un caractère
        (yyval.exprari).type = "CHAR";
        (yyval.exprari).value.cval = (yyvsp[0].car);  // La valeur caractère
        // Générer un quadruplet pour le caractère
       char val[20];
        sprintf(val, "%c", (yyvsp[0].car));
         (yyval.exprari).name=val;

    }
#line 1454 "parser.tab.c"
    break;

  case 17: /* expression: expression PLUS expression  */
#line 281 "parser.y"
                                 {  // Addition
        if (strcmp((yyvsp[-2].exprari).type, (yyvsp[0].exprari).type) != 0) {
            yyerror("Opérandes incompatibles pour l'addition.");
            return 0;
        }
        if (strcmp((yyvsp[-2].exprari).type, "INTEGER") == 0) {
            (yyval.exprari).type = "INTEGER";
            (yyval.exprari).value.ival = (yyvsp[-2].exprari).value.ival + (yyvsp[0].exprari).value.ival;

            // Générer un quadruplet pour l'addition
            char tempVar[20];
            sprintf(tempVar, "t%d", tempCount++);
            generer("+", (yyvsp[-2].exprari).name,(yyvsp[0].exprari).name, tempVar);
                (yyval.exprari).name=tempVar;
        } else if (strcmp((yyvsp[-2].exprari).type, "FLOAT") == 0) {
            (yyval.exprari).type = "FLOAT";
            (yyval.exprari).value.fval = (yyvsp[-2].exprari).value.fval + (yyvsp[0].exprari).value.fval;

            // Générer un quadruplet pour l'addition flottante
            char tempVar[20];
            sprintf(tempVar, "t%d", tempCount++);
            generer("+",(yyvsp[-2].exprari).name,(yyvsp[0].exprari).name, tempVar);
            (yyval.exprari).name=tempVar;
        } else {
            yyerror("Addition non supportée pour ce type.");
            return 0;
        }
      
    }
#line 1488 "parser.tab.c"
    break;

  case 18: /* expression: expression MINUS expression  */
#line 310 "parser.y"
                                  {  // Soustraction
        if (strcmp((yyvsp[-2].exprari).type, (yyvsp[0].exprari).type) != 0) {
            yyerror("Opérandes incompatibles pour la soustraction.");
            return 0;
        }
        if (strcmp((yyvsp[-2].exprari).type, "INTEGER") == 0) {
            (yyval.exprari).type = "INTEGER";
            (yyval.exprari).value.ival = (yyvsp[-2].exprari).value.ival - (yyvsp[0].exprari).value.ival;

            // Générer un quadruplet pour la soustraction
            char tempVar[20];
            sprintf(tempVar, "t%d", tempCount++);
             
            generer("-",(yyvsp[-2].exprari).name,(yyvsp[0].exprari).name, tempVar);
            (yyval.exprari).name=tempVar;
        } else if (strcmp((yyvsp[-2].exprari).type, "FLOAT") == 0) {
            (yyval.exprari).type = "FLOAT";
            (yyval.exprari).value.fval = (yyvsp[-2].exprari).value.fval - (yyvsp[0].exprari).value.fval;

            // Générer un quadruplet pour la soustraction flottante
            char tempVar[20];
            sprintf(tempVar, "t%d", tempCount++);
            generer("-",(yyvsp[-2].exprari).name,(yyvsp[0].exprari).name, tempVar);
                (yyval.exprari).name=tempVar;
            
        } else {
            yyerror("Soustraction non supportée pour ce type.");
            return 0;
        }
    }
#line 1523 "parser.tab.c"
    break;

  case 19: /* expression: expression MULT expression  */
#line 340 "parser.y"
                                 {  // Multiplication
        if (strcmp((yyvsp[-2].exprari).type, (yyvsp[0].exprari).type) != 0) {
            yyerror("Opérandes incompatibles pour la multiplication.");
            return 0;
        }
        if (strcmp((yyvsp[-2].exprari).type, "INTEGER") == 0) {
            (yyval.exprari).type = "INTEGER";
            (yyval.exprari).value.ival = (yyvsp[-2].exprari).value.ival * (yyvsp[0].exprari).value.ival;

            // Générer un quadruplet pour la multiplication
            char tempVar[20];
                
            sprintf(tempVar, "t%d", tempCount++);
            generer("*", (yyvsp[-2].exprari).name,(yyvsp[0].exprari).name, tempVar);
            (yyval.exprari).name=tempVar;
        } else if (strcmp((yyvsp[-2].exprari).type, "FLOAT") == 0) {
            (yyval.exprari).type = "FLOAT";
            (yyval.exprari).value.fval = (yyvsp[-2].exprari).value.fval * (yyvsp[0].exprari).value.fval;

            // Générer un quadruplet pour la multiplication flottante
            char tempVar[20];
            sprintf(tempVar, "t%d", tempCount++);
               printf("\n\n\n\n%s\n\n\n\n", (yyvsp[-2].exprari).name);
                     printf("\n\n\n\n%s\n\n\n\n", (yyvsp[0].exprari).name);
            generer("*", (yyvsp[-2].exprari).name,(yyvsp[0].exprari).name, tempVar);
            (yyval.exprari).name=tempVar;
        } else {
            yyerror("Multiplication non supportée pour ce type.");
            return 0;
        }
    }
#line 1559 "parser.tab.c"
    break;

  case 20: /* expression: expression DIV expression  */
#line 371 "parser.y"
                                {  // Division
        if (strcmp((yyvsp[-2].exprari).type, (yyvsp[0].exprari).type) != 0) {
            yyerror("Opérandes incompatibles pour la division.");
            return 0;
        }
        if (strcmp((yyvsp[-2].exprari).type, "INTEGER") == 0) {
            if ((yyvsp[0].exprari).value.ival == 0) {
                yyerror("Division par zéro.");
                return 0;
            }
            (yyval.exprari).type = "INTEGER";
            (yyval.exprari).value.ival = (yyvsp[-2].exprari).value.ival / (yyvsp[0].exprari).value.ival;

            // Générer un quadruplet pour la division
            char tempVar[20];
            sprintf(tempVar, "t%d", tempCount++);
            generer("/",(yyvsp[-2].exprari).name,(yyvsp[0].exprari).name, tempVar);
            (yyval.exprari).name=tempVar;
        } else if (strcmp((yyvsp[-2].exprari).type, "FLOAT") == 0) {
            if ((yyvsp[0].exprari).value.fval == 0.0f) {
                yyerror("Division par zéro.");
                return 0;
            }
            (yyval.exprari).type = "FLOAT";
            (yyval.exprari).value.fval = (yyvsp[-2].exprari).value.fval / (yyvsp[0].exprari).value.fval;

            // Générer un quadruplet pour la division flottante
            char tempVar[20];
               sprintf(tempVar, "t%d", tempCount++);
    
            generer("/", (yyvsp[-2].exprari).name,(yyvsp[0].exprari).name, tempVar);
                (yyval.exprari).name=tempVar;
        } else {
            yyerror("Division non supportée pour ce type.");
            return 0;
        }
    }
#line 1601 "parser.tab.c"
    break;

  case 21: /* expression: LPAREN expression RPAREN  */
#line 408 "parser.y"
                               {  // Parenthèses pour prioriser les opérations
        (yyval.exprari).type = (yyvsp[-1].exprari).type;
        (yyval.exprari).value = (yyvsp[-1].exprari).value;
        (yyval.exprari).name=(yyvsp[-1].exprari).name;
    }
#line 1611 "parser.tab.c"
    break;

  case 22: /* type: INTEGER  */
#line 415 "parser.y"
            { (yyval.chaine) = "INTEGER"; }
#line 1617 "parser.tab.c"
    break;

  case 23: /* type: FLOAT  */
#line 416 "parser.y"
            { (yyval.chaine) = "FLOAT"; }
#line 1623 "parser.tab.c"
    break;

  case 24: /* type: CHAR  */
#line 417 "parser.y"
           { (yyval.chaine) = "CHAR"; }
#line 1629 "parser.tab.c"
    break;

  case 30: /* statement: IF LPAREN expressionslogic RPAREN LBRACE statements RBRACE ELSE LBRACE statements RBRACE  */
#line 434 "parser.y"
                                                                                               {
        // Vérifier que la condition dans IF est de type booléen

        if (strcmp((yyvsp[-8].exprlog).type, "BOOLEAN") != 0) {
            yyerror("La condition de l'instruction IF doit être de type BOOLEAN.");
            return 0;
        }
    // Generate unique labels for jumps
    char* else_label = malloc(20);
    char* end_label = malloc(20);
    sprintf(else_label, "L%d", tempCount++);
    sprintf(end_label, "L%d", tempCount++);
    
    // If expression is false (0), jump to else
    generer("BZ", (yyvsp[-8].exprlog).name, "", else_label);
    
    // If-block code was already generated in statements
    
    // Jump to end after if block
    generer("BR", end_label, "", "");
    
    // Place else label
    generer("LABEL", else_label, "", "");
    
    // Else-block code was already generated in statements
    
    // Place end label
    generer("LABEL", end_label, "", "");
    
    free(else_label);
    free(end_label);

    }
#line 1667 "parser.tab.c"
    break;

  case 31: /* statement: FOR LPAREN init_for BOUCLESEPARATOR expression BOUCLESEPARATOR expression RPAREN LBRACE statements RBRACE  */
#line 467 "parser.y"
                                                                                                                {
      if (strcmp((yyvsp[-6].exprari).type, "INTEGER") != 0||strcmp((yyvsp[-4].exprari).type, "INTEGER") != 0) {
        yyerror("Le pas de la boucle doit être un entier.");
        return 0;
    }

    // Generate unique labels
    char* start_label = malloc(20);
    char* end_label = malloc(20);
    sprintf(start_label, "L%d", tempCount++);
    sprintf(end_label, "L%d", tempCount++);
    
    // Place start label
    generer("LABEL", start_label, "", "");
    
    // Generate comparison result
    char* temp = malloc(20);
    sprintf(temp, "t%d", tempCount++);
    generer("-", (yyvsp[-8].exprari).name, (yyvsp[-6].exprari).name, temp);  // temp = counter - limit
    
    // If temp >= 0 (counter >= limit), exit loop
    generer("BGE", temp, "", end_label);
    
    // Loop body code was already generated in statements
    
    // Increment counter
    generer("+", (yyvsp[-8].exprari).name, (yyvsp[-4].exprari).name, (yyvsp[-8].exprari).name);
    
    // Jump back to start
    generer("BR", start_label, "", "");
    
    // Place end label
    generer("LABEL", end_label, "", "");
    
    free(start_label);
    free(end_label);
    free(temp);
    }
#line 1710 "parser.tab.c"
    break;

  case 32: /* statement: READ LPAREN IDENTIFIER RPAREN SEMICOLON  */
#line 505 "parser.y"
                                              {
        if (rechercher((yyvsp[-2].id).name) == NULL) {
            yyerror("Variable non déclarée.");
            return 0;
        }
    }
#line 1721 "parser.tab.c"
    break;

  case 33: /* statement: WRITE LPAREN expressionwrite RPAREN SEMICOLON  */
#line 511 "parser.y"
                                                    {
        // Vérification que l'expression à écrire est valide
    }
#line 1729 "parser.tab.c"
    break;

  case 34: /* expressionlogic: expression EQUAL expression  */
#line 518 "parser.y"
                           {
        if (strcmp((yyvsp[-2].exprari).type, (yyvsp[0].exprari).type) != 0) {
            yyerror("Opérandes de types incompatibles pour l'opération de comparaison.");
            return 0;
        }
        (yyval.exprlog).type = "BOOLEAN";  // Le résultat de la comparaison est de type booléen
         char* temp = malloc(20);
        sprintf(temp, "t%d", tempCount++);
        char* true_label = malloc(20);
        char* end_label = malloc(20);
        sprintf(true_label, "L%d", tempCount++);
        sprintf(end_label, "L%d", tempCount++);
        
        // Compare values
        generer("-", (yyvsp[-2].exprari).name, (yyvsp[0].exprari).name, temp);
        
        // If difference is 0, values are equal
        generer("BZ", temp, "", true_label);
        generer("=", "0", "", temp);  // Set result to false
        generer("BR", end_label, "", "");
        generer("LABEL", true_label, "", "");
        generer("=", "1", "", temp);  // Set result to true
        generer("LABEL", end_label, "", "");
        
        (yyval.exprlog).name = temp;
        free(true_label);
        free(end_label);

        if(strcmp((yyvsp[-2].exprari).type,"INTEGER")==0){
             if((yyvsp[-2].exprari).value.ival==(yyvsp[0].exprari).value.ival){
              (yyval.exprlog).value=1;
        }else{
            (yyval.exprlog).value=0;
        }
        }
          if(strcmp((yyvsp[-2].exprari).type,"FLOAT")==0){
             if((yyvsp[-2].exprari).value.fval==(yyvsp[0].exprari).value.fval){
              (yyval.exprlog).value=1;
        }else{
            (yyval.exprlog).value=0;
        }
        }
          if(strcmp((yyvsp[-2].exprari).type,"CHAR")==0){
             if((yyvsp[-2].exprari).value.cval==(yyvsp[0].exprari).value.cval){
              (yyval.exprlog).value=1;
        }else{
            (yyval.exprlog).value=0;
        }
        }
    
    }
#line 1785 "parser.tab.c"
    break;

  case 35: /* expressionlogic: LPAREN expressionlogic RPAREN  */
#line 570 "parser.y"
                                  {
        // Copier le contenu de la sous-expression dans l'expression actuelle
        (yyval.exprlog).type = (yyvsp[-1].exprlog).type;
        (yyval.exprlog).variables = (yyvsp[-1].exprlog).variables;
        (yyval.exprlog).count = (yyvsp[-1].exprlog).count;
        (yyval.exprlog).value=(yyvsp[-1].exprlog).value;
    }
#line 1797 "parser.tab.c"
    break;

  case 36: /* expressionlogic: expression LT expression  */
#line 577 "parser.y"
                               {
        if (strcmp((yyvsp[-2].exprari).type, (yyvsp[0].exprari).type) != 0) {
            yyerror("Opérandes de types incompatibles pour l'opération de comparaison.");
            return 0;
        }
        (yyval.exprlog).type = "BOOLEAN";  // Le résultat de la comparaison est de type booléen
        if(strcmp((yyvsp[-2].exprari).type,"INTEGER")==0){
             if((yyvsp[-2].exprari).value.ival<(yyvsp[0].exprari).value.ival){
              (yyval.exprlog).value=1;
        }else{
            (yyval.exprlog).value=0;
        }
        }
          if(strcmp((yyvsp[-2].exprari).type,"FLOAT")==0){
             if((yyvsp[-2].exprari).value.fval<(yyvsp[0].exprari).value.fval){
              (yyval.exprlog).value=1;
        }else{
            (yyval.exprlog).value=0;
        }
        }
          if(strcmp((yyvsp[-2].exprari).type,"CHAR")==0){
             if((yyvsp[-2].exprari).value.cval<(yyvsp[0].exprari).value.cval){
              (yyval.exprlog).value=1;
        }else{
            (yyval.exprlog).value=0;
        }
        }}
#line 1829 "parser.tab.c"
    break;

  case 37: /* expressionlogic: expression LTE expression  */
#line 605 "parser.y"
                                {
        if (strcmp((yyvsp[-2].exprari).type, (yyvsp[0].exprari).type) != 0) {
            yyerror("Opérandes de types incompatibles pour l'opération de comparaison.");
            return 0;
        }
        (yyval.exprlog).type = "BOOLEAN";  // Le résultat de la comparaison est de type booléen
         char* temp = malloc(20);
        sprintf(temp, "t%d", tempCount++);
        char* true_label = malloc(20);
        char* end_label = malloc(20);
        sprintf(true_label, "L%d", tempCount++);
        sprintf(end_label, "L%d", tempCount++);
        
        // Compare values
        generer("-", (yyvsp[-2].exprari).name, (yyvsp[0].exprari).name, temp);
        
        // If difference is negative, first value is less
        generer("BL", temp, "", true_label);
        generer("=", "0", "", temp);  // Set result to false
        generer("BR", end_label, "", "");
        generer("LABEL", true_label, "", "");
        generer("=", "1", "", temp);  // Set result to true
        generer("LABEL", end_label, "", "");
        
        (yyval.exprlog).name = temp;
        free(true_label);
        free(end_label);

        if(strcmp((yyvsp[-2].exprari).type,"INTEGER")==0){
             if((yyvsp[-2].exprari).value.ival<=(yyvsp[0].exprari).value.ival){
              (yyval.exprlog).value=1;
        }else{
            (yyval.exprlog).value=0;
        }
        }
          if(strcmp((yyvsp[-2].exprari).type,"FLOAT")==0){
             if((yyvsp[-2].exprari).value.fval<=(yyvsp[0].exprari).value.fval){
              (yyval.exprlog).value=1;
        }else{
            (yyval.exprlog).value=0;
        }
        }
          if(strcmp((yyvsp[-2].exprari).type,"CHAR")==0){
             if((yyvsp[-2].exprari).value.cval<=(yyvsp[0].exprari).value.cval){
              (yyval.exprlog).value=1;
        }else{
            (yyval.exprlog).value=0;
        }
        }
    }
#line 1884 "parser.tab.c"
    break;

  case 38: /* expressionlogic: expression GT expression  */
#line 657 "parser.y"
    {  if (strcmp((yyvsp[-2].exprari).type, (yyvsp[0].exprari).type) != 0) {
            yyerror("Opérandes de types incompatibles pour l'opération de comparaison.");
            return 0;
        }
        (yyval.exprlog).type = "BOOLEAN";  // Le résultat de la comparaison est de type booléen
        if(strcmp((yyvsp[-2].exprari).type,"INTEGER")==0){
             if((yyvsp[-2].exprari).value.ival>(yyvsp[0].exprari).value.ival){
              (yyval.exprlog).value=1;
        }else{
            (yyval.exprlog).value=0;
        }
        }
          if(strcmp((yyvsp[-2].exprari).type,"FLOAT")==0){
             if((yyvsp[-2].exprari).value.fval>(yyvsp[0].exprari).value.fval){
              (yyval.exprlog).value=1;
        }else{
            (yyval.exprlog).value=0;
        }
        }
          if(strcmp((yyvsp[-2].exprari).type,"CHAR")==0){
             if((yyvsp[-2].exprari).value.cval>(yyvsp[0].exprari).value.cval){
              (yyval.exprlog).value=1;
        }else{
            (yyval.exprlog).value=0;
        }
          }
    }
#line 1916 "parser.tab.c"
    break;

  case 39: /* expressionlogic: expression GTE expression  */
#line 684 "parser.y"
                                {
        if (strcmp((yyvsp[-2].exprari).type, (yyvsp[0].exprari).type) != 0) {
            yyerror("Opérandes de types incompatibles pour l'opération de comparaison.");
            return 0;
        }
        (yyval.exprlog).type = "BOOLEAN";  // Le résultat de la comparaison est de type booléen
        if(strcmp((yyvsp[-2].exprari).type,"INTEGER")==0){
             if((yyvsp[-2].exprari).value.ival>=(yyvsp[0].exprari).value.ival){
              (yyval.exprlog).value=1;
        }else{
            (yyval.exprlog).value=0;
        }
        }
          if(strcmp((yyvsp[-2].exprari).type,"FLOAT")==0){
             if((yyvsp[-2].exprari).value.fval>=(yyvsp[0].exprari).value.fval){
              (yyval.exprlog).value=1;
        }else{
            (yyval.exprlog).value=0;
        }
        }
          if(strcmp((yyvsp[-2].exprari).type,"CHAR")==0){
             if((yyvsp[-2].exprari).value.cval>=(yyvsp[0].exprari).value.cval){
              (yyval.exprlog).value=1;
        }else{
            (yyval.exprlog).value=0;
        }
        }
    }
#line 1949 "parser.tab.c"
    break;

  case 40: /* expressionlogic: expressionlogic AND expressionlogic  */
#line 713 "parser.y"
                                         {
        // Vérification que les deux opérandes sont booléens
        if (strcmp((yyvsp[-2].exprlog).type, "BOOLEAN") != 0 || strcmp((yyvsp[0].exprlog).type, "BOOLEAN") != 0) {
            yyerror("Opérandes incompatibles pour l'opérateur logique AND.");
            return 0;
        }
        (yyval.exprlog).type = "BOOLEAN";
        char* temp = malloc(20);
        sprintf(temp, "t%d", tempCount++);
        char* false_label = malloc(20);
        char* end_label = malloc(20);
        sprintf(false_label, "L%d", tempCount++);
        sprintf(end_label, "L%d", tempCount++);
        
        // If first expression is false, result is false
        generer("BZ", (yyvsp[-2].exprlog).name, "", false_label);
        // If second expression is false, result is false
        generer("BZ", (yyvsp[0].exprlog).name, "", false_label);
        // Both true, set result to true
        generer("=", "1", "", temp);
        generer("BR", end_label, "", "");
        // False case
        generer("LABEL", false_label, "", "");
        generer("=", "0", "", temp);
        generer("LABEL", end_label, "", "");
        
        (yyval.exprlog).name = temp;
        free(false_label);
        free(end_label);

            if((yyvsp[-2].exprlog).value&&(yyvsp[0].exprlog).value){
              (yyval.exprlog).value=1;
        }else{
            (yyval.exprlog).value=0;
        }
    }
#line 1990 "parser.tab.c"
    break;

  case 41: /* expressionlogic: expressionlogic OR expressionlogic  */
#line 749 "parser.y"
                                         {
        if (strcmp((yyvsp[-2].exprlog).type, "BOOLEAN") != 0 || strcmp((yyvsp[0].exprlog).type, "BOOLEAN") != 0) {
            yyerror("Opérandes incompatibles pour l'opérateur logique OR.");
            return 0;
        }
        (yyval.exprlog).type = "BOOLEAN";

         char* temp = malloc(20);
        sprintf(temp, "t%d", tempCount++);
        char* true_label = malloc(20);
        char* end_label = malloc(20);
        sprintf(true_label, "L%d", tempCount++);
        sprintf(end_label, "L%d", tempCount++);
        
        // If first expression is true, result is true
        generer("BNZ", (yyvsp[-2].exprlog).name, "", true_label);
        // If second expression is true, result is true
        generer("BNZ", (yyvsp[0].exprlog).name, "", true_label);
        // Both false, set result to false
        generer("=", "0", "", temp);
        generer("BR", end_label, "", "");
        // True case
        generer("LABEL", true_label, "", "");
        generer("=", "1", "", temp);
        generer("LABEL", end_label, "", "");
        
        (yyval.exprlog).name = temp;
        free(true_label);
        free(end_label);

          if((yyvsp[-2].exprlog).value||(yyvsp[0].exprlog).value){
              (yyval.exprlog).value=1;
        }else{
            (yyval.exprlog).value=0;
        }
    }
#line 2031 "parser.tab.c"
    break;

  case 42: /* expressionlogic: NOT expressionlogic  */
#line 785 "parser.y"
                          {
        if (strcmp((yyvsp[0].exprlog).type, "BOOLEAN") != 0) {
            yyerror("L'opérande de NOT doit être de type BOOLEAN.");
            return 0;
        }
        (yyval.exprlog).type = "BOOLEAN";
        char* temp = malloc(20);
        sprintf(temp, "t%d", tempCount++);
        char* true_label = malloc(20);
        char* end_label = malloc(20);
        sprintf(true_label, "L%d", tempCount++);
        sprintf(end_label, "L%d", tempCount++);
        
        // If expression is false, result is true
        generer("BZ", (yyvsp[0].exprlog).name, "", true_label);
        generer("=", "0", "", temp);
        generer("BR", end_label, "", "");
        generer("LABEL", true_label, "", "");
        generer("=", "1", "", temp);
        generer("LABEL", end_label, "", "");
        
        (yyval.exprlog).name = temp;
        free(true_label);
        free(end_label);
          if(!(yyvsp[0].exprlog).value){
              (yyval.exprlog).value=1;
        }else{
            (yyval.exprlog).value=0;
        }
    }
#line 2066 "parser.tab.c"
    break;

  case 43: /* init_for: IDENTIFIER ASSIGN expression  */
#line 818 "parser.y"
                                 {
        TableEntry *varEntry = rechercher((yyvsp[-2].id).name);
        if (varEntry == NULL) {
            yyerror("Variable non déclarée.");
            return 0;
        }
        (yyval.exprari) = (yyvsp[0].exprari);  // Pass the expression value up
    }
#line 2079 "parser.tab.c"
    break;

  case 44: /* expressionwrite: IDENTIFIER  */
#line 830 "parser.y"
               {
        TableEntry *varEntry = rechercher((yyvsp[0].id).name);
        if (varEntry == NULL) {
            yyerror("Variable non déclarée.");
            return 0;
        }
    }
#line 2091 "parser.tab.c"
    break;

  case 47: /* expressionwrite: IDENTIFIER COMMA expressionwrite  */
#line 839 "parser.y"
                                       {
        TableEntry *varEntry = rechercher((yyvsp[-2].id).name);
        if (varEntry == NULL) {
            yyerror("Variable non déclarée.");
            return 0;
        }
    }
#line 2103 "parser.tab.c"
    break;


#line 2107 "parser.tab.c"

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
  YY_SYMBOL_PRINT ("-> $$ =", YY_CAST (yysymbol_kind_t, yyr1[yyn]), &yyval, &yyloc);

  YYPOPSTACK (yylen);
  yylen = 0;

  *++yyvsp = yyval;

  /* Now 'shift' the result of the reduction.  Determine what state
     that goes to, based on the state we popped back to and the rule
     number reduced by.  */
  {
    const int yylhs = yyr1[yyn] - YYNTOKENS;
    const int yyi = yypgoto[yylhs] + *yyssp;
    yystate = (0 <= yyi && yyi <= YYLAST && yycheck[yyi] == *yyssp
               ? yytable[yyi]
               : yydefgoto[yylhs]);
  }

  goto yynewstate;


/*--------------------------------------.
| yyerrlab -- here on detecting error.  |
`--------------------------------------*/
yyerrlab:
  /* Make sure we have latest lookahead translation.  See comments at
     user semantic actions for why this is necessary.  */
  yytoken = yychar == YYEMPTY ? YYSYMBOL_YYEMPTY : YYTRANSLATE (yychar);
  /* If not already recovering from an error, report this error.  */
  if (!yyerrstatus)
    {
      ++yynerrs;
      yyerror (YY_("syntax error"));
    }

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
                      yytoken, &yylval);
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
  /* Pacify compilers when the user code never invokes YYERROR and the
     label yyerrorlab therefore never appears in user code.  */
  if (0)
    YYERROR;
  ++yynerrs;

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

  /* Pop stack until we find a state that shifts the error token.  */
  for (;;)
    {
      yyn = yypact[yystate];
      if (!yypact_value_is_default (yyn))
        {
          yyn += YYSYMBOL_YYerror;
          if (0 <= yyn && yyn <= YYLAST && yycheck[yyn] == YYSYMBOL_YYerror)
            {
              yyn = yytable[yyn];
              if (0 < yyn)
                break;
            }
        }

      /* Pop the current state because it cannot handle the error token.  */
      if (yyssp == yyss)
        YYABORT;


      yydestruct ("Error: popping",
                  YY_ACCESSING_SYMBOL (yystate), yyvsp);
      YYPOPSTACK (1);
      yystate = *yyssp;
      YY_STACK_PRINT (yyss, yyssp);
    }

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END


  /* Shift the error token.  */
  YY_SYMBOL_PRINT ("Shifting", YY_ACCESSING_SYMBOL (yyn), yyvsp, yylsp);

  yystate = yyn;
  goto yynewstate;


/*-------------------------------------.
| yyacceptlab -- YYACCEPT comes here.  |
`-------------------------------------*/
yyacceptlab:
  yyresult = 0;
  goto yyreturnlab;


/*-----------------------------------.
| yyabortlab -- YYABORT comes here.  |
`-----------------------------------*/
yyabortlab:
  yyresult = 1;
  goto yyreturnlab;


/*-----------------------------------------------------------.
| yyexhaustedlab -- YYNOMEM (memory exhaustion) comes here.  |
`-----------------------------------------------------------*/
yyexhaustedlab:
  yyerror (YY_("memory exhausted"));
  yyresult = 2;
  goto yyreturnlab;


/*----------------------------------------------------------.
| yyreturnlab -- parsing is finished, clean up and return.  |
`----------------------------------------------------------*/
yyreturnlab:
  if (yychar != YYEMPTY)
    {
      /* Make sure we have latest lookahead translation.  See comments at
         user semantic actions for why this is necessary.  */
      yytoken = YYTRANSLATE (yychar);
      yydestruct ("Cleanup: discarding lookahead",
                  yytoken, &yylval);
    }
  /* Do not reclaim the symbols of the rule whose action triggered
     this YYABORT or YYACCEPT.  */
  YYPOPSTACK (yylen);
  YY_STACK_PRINT (yyss, yyssp);
  while (yyssp != yyss)
    {
      yydestruct ("Cleanup: popping",
                  YY_ACCESSING_SYMBOL (+*yyssp), yyvsp);
      YYPOPSTACK (1);
    }
#ifndef yyoverflow
  if (yyss != yyssa)
    YYSTACK_FREE (yyss);
#endif

  return yyresult;
}

#line 858 "parser.y"


void yyerror(const char *s) {
    extern int yylineno;
    fprintf(stderr, "Erreur à la ligne %d: %s\n", yylineno, s);
}/*
expressionlogic:

expression EQUAL expression{
        if (strcmp($1.type, $3.type) != 0) {
            yyerror("Opérandes de types incompatibles pour l'opération de comparaison.");
            return 0;
        }
        $$.type = "BOOLEAN";  // Le résultat de la comparaison est de type booléen
    }
    |
    LPAREN expressionlogic RPAREN {
        // Copier le contenu de la sous-expression dans l'expression actuelle
        $$.type = $2.type;
        $$.variables = $2.variables;
        $$.count = $2.count;
    }
    | expression LT expression {
        if (strcmp($1.type, $3.type) != 0) {
            yyerror("Opérandes de types incompatibles pour l'opération de comparaison.");
            return 0;
        }
        $$.type = "BOOLEAN";  // Le résultat de la comparaison est de type booléen
    }
    | expression LTE expression {
        if (strcmp($1.type, $3.type) != 0) {
            yyerror("Opérandes de types incompatibles pour l'opération de comparaison.");
            return 0;
        }
        $$.type = "BOOLEAN";
    }
    | expression GT expression {
        if (strcmp($1.type, $3.type) != 0) {
            yyerror("Opérandes de types incompatibles pour l'opération de comparaison.");
            return 0;
        }
        $$.type = "BOOLEAN";
    }
    | expression GTE expression {
        if (strcmp($1.type, $3.type) != 0) {
            yyerror("Opérandes de types incompatibles pour l'opération de comparaison.");
            return 0;
        }
        $$.type = "BOOLEAN";
    }
    
    | expressionlogic AND expressionlogic {
        // Vérification que les deux opérandes sont booléens
        if (strcmp($1.type, "BOOLEAN") != 0 || strcmp($3.type, "BOOLEAN") != 0) {
            yyerror("Opérandes incompatibles pour l'opérateur logique AND.");
            return 0;
        }
        $$.type = "BOOLEAN";
    }
    | expressionlogic OPERA expressionlogic {
        if (strcmp($1.type, "BOOLEAN") != 0 || strcmp($3.type, "BOOLEAN") != 0) {
            yyerror("Opérandes incompatibles pour l'opérateur logique OR.");
            return 0;
        }
        $$.type = "BOOLEAN";
    }
    | NOT expressionlogic {
        if (strcmp($2.type, "BOOLEAN") != 0) {
            yyerror("L'opérande de NOT doit être de type BOOLEAN.");
            return 0;
        }
        $$.type = "BOOLEAN";
    }
;*/
