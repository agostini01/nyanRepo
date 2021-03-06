/* A Bison parser, made by GNU Bison 3.0.2.  */

/* Bison implementation for Yacc-like parsers in C

   Copyright (C) 1984, 1989-1990, 2000-2013 Free Software Foundation, Inc.

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
#define YYBISON_VERSION "3.0.2"

/* Skeleton name.  */
#define YYSKELETON_NAME "yacc.c"

/* Pure parsers.  */
#define YYPURE 0

/* Push parsers.  */
#define YYPUSH 0

/* Pull parsers.  */
#define YYPULL 1


/* Substitute the variable and function names.  */
#define yyparse         cl2llvm_yyparse
#define yylex           cl2llvm_yylex
#define yyerror         cl2llvm_yyerror
#define yydebug         cl2llvm_yydebug
#define yynerrs         cl2llvm_yynerrs

#define yylval          cl2llvm_yylval
#define yychar          cl2llvm_yychar

/* Copy the first part of user declarations.  */
#line 1 "parser.y" /* yacc.c:339  */


#define YYDEBUG 1

#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <lib/util/debug.h>
#include <lib/util/hash-table.h>
#include <lib/util/list.h>
#include <llvm-c/Core.h>
#include <llvm-c/Analysis.h>
#include <llvm-c/ExecutionEngine.h>
#include <llvm-c/Target.h>
#include <llvm-c/Transforms/Scalar.h>
#include <llvm-c/BitWriter.h>

#include "vector-ops.h"
#include "for-blocks.h"
#include "while-blocks.h"
#include "arg.h"
#include "declarator-list.h"
#include "function.h"
#include "val.h"
#include "type.h"
#include "init.h"
#include "symbol.h"
#include "built-in-funcs.h"
#include "parser.h"
#include "cl2llvm.h"
#include "array.h"

#define CL2LLVM_MAX_FUNC_ARGS 64
#define CL2LLVM_MAX_ARG_NAME_LEN 200
#define CL2LLVM_MAX_NUM_ARRAY_INDEX_DIM 100

extern LLVMBuilderRef cl2llvm_builder;
extern LLVMModuleRef cl2llvm_module;
extern LLVMValueRef cl2llvm_function;
extern LLVMBasicBlockRef cl2llvm_basic_block;

extern int temp_var_count;
extern char temp_var_name[50];

int block_count;
char block_name[50];

int  func_count;
char func_name[50];

extern struct hash_table_t *cl2llvm_built_in_func_table;
struct hash_table_t *cl2llvm_symbol_table;
extern struct hash_table_t *cl2llvm_built_in_const_table;

struct cl2llvm_function_t *cl2llvm_current_function;
LLVMBasicBlockRef current_basic_block;


#line 135 "parser.c" /* yacc.c:339  */

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
# define YYERROR_VERBOSE 0
#endif

/* In a future release of Bison, this section will be replaced
   by #include "y.tab.h".  */
#ifndef YY_CL2LLVM_YY_PARSER_H_INCLUDED
# define YY_CL2LLVM_YY_PARSER_H_INCLUDED
/* Debug traces.  */
#ifndef YYDEBUG
# define YYDEBUG 0
#endif
#if YYDEBUG
extern int cl2llvm_yydebug;
#endif

/* Token type.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
  enum yytokentype
  {
    TOK_ID = 258,
    TOK_CONST_INT = 259,
    TOK_CONST_INT_U = 260,
    TOK_CONST_INT_L = 261,
    TOK_CONST_INT_UL = 262,
    TOK_CONST_INT_LL = 263,
    TOK_CONST_INT_ULL = 264,
    TOK_CONST_DEC = 265,
    TOK_CONST_DEC_H = 266,
    TOK_CONST_DEC_F = 267,
    TOK_CONST_DEC_L = 268,
    TOK_CONST_VAL = 269,
    TOK_STRING = 270,
    TOK_COMMA = 271,
    TOK_SEMICOLON = 272,
    TOK_ELLIPSIS = 273,
    TOK_EQUAL = 274,
    TOK_ADD_EQUAL = 275,
    TOK_MINUS_EQUAL = 276,
    TOK_MULT_EQUAL = 277,
    TOK_DIV_EQUAL = 278,
    TOK_MOD_EQUAL = 279,
    TOK_AND_EQUAL = 280,
    TOK_OR_EQUAL = 281,
    TOK_EXCLUSIVE_EQUAL = 282,
    TOK_SHIFT_RIGHT_EQUAL = 283,
    TOK_SHIFT_LEFT_EQUAL = 284,
    TOK_CONDITIONAL = 285,
    TOK_COLON = 286,
    TOK_LOGICAL_OR = 287,
    TOK_LOGICAL_AND = 288,
    TOK_BITWISE_OR = 289,
    TOK_BITWISE_EXCLUSIVE = 290,
    TOK_BITWISE_AND = 291,
    TOK_EQUALITY = 292,
    TOK_INEQUALITY = 293,
    TOK_GREATER = 294,
    TOK_LESS = 295,
    TOK_GREATER_EQUAL = 296,
    TOK_LESS_EQUAL = 297,
    TOK_SHIFT_RIGHT = 298,
    TOK_SHIFT_LEFT = 299,
    TOK_PLUS = 300,
    TOK_MINUS = 301,
    TOK_MULT = 302,
    TOK_DIV = 303,
    TOK_MOD = 304,
    TOK_PREFIX = 305,
    TOK_LOGICAL_NEGATE = 306,
    TOK_BITWISE_NOT = 307,
    TOK_CURLY_BRACE_CLOSE = 308,
    TOK_CURLY_BRACE_OPEN = 309,
    TOK_PAR_OPEN = 310,
    TOK_PAR_CLOSE = 311,
    TOK_BRACKET_OPEN = 312,
    TOK_BRACKET_CLOSE = 313,
    TOK_POSTFIX = 314,
    TOK_STRUCT_REF = 315,
    TOK_STRUCT_DEREF = 316,
    TOK_DECREMENT = 317,
    TOK_INCREMENT = 318,
    TOK_AUTO = 319,
    TOK_BOOL = 320,
    TOK_BREAK = 321,
    TOK_CASE = 322,
    TOK_CHAR = 323,
    TOK_CHARN = 324,
    TOK_CONSTANT = 325,
    TOK_CONST = 326,
    TOK_CONTINUE = 327,
    TOK_DEFAULT = 328,
    TOK_DO = 329,
    TOK_DOUBLE = 330,
    TOK_DOUBLE_LONG = 331,
    TOK_DOUBLEN = 332,
    TOK_ENUM = 333,
    TOK_EVENT_T = 334,
    TOK_EXTERN = 335,
    TOK_FLOAT = 336,
    TOK_FLOATN = 337,
    TOK_FOR = 338,
    TOK_GLOBAL = 339,
    TOK_GOTO = 340,
    TOK_HALF = 341,
    TOK_IF = 342,
    TOK_ELSE = 343,
    TOK_IMAGE2D_T = 344,
    TOK_IMAGE3D_T = 345,
    TOK_IMAGE2D_ARRAY_T = 346,
    TOK_IMAGE1D_T = 347,
    TOK_IMAGE1D_BUFFER_T = 348,
    TOK_IMAGE1D_ARRAY_T = 349,
    TOK_INLINE = 350,
    TOK_INT = 351,
    TOK_INT_LONG = 352,
    TOK_LONG_LONG = 353,
    TOK_INTN = 354,
    TOK_INTPTR_T = 355,
    TOK_KERNEL = 356,
    TOK_LOCAL = 357,
    TOK_LONG = 358,
    TOK_LONGN = 359,
    TOK_PRIVATE = 360,
    TOK_PTRDIFF_T = 361,
    TOK_READ_ONLY = 362,
    TOK_READ_WRITE = 363,
    TOK_REGISTER = 364,
    TOK_RETURN = 365,
    TOK_SAMPLER_T = 366,
    TOK_SHORT = 367,
    TOK_SHORTN = 368,
    TOK_SIGNED = 369,
    TOK_SIZEOF = 370,
    TOK_SIZE_T = 371,
    TOK_STATIC = 372,
    TOK_STRUCT = 373,
    TOK_SWITCH = 374,
    TOK_TYPEDEF = 375,
    TOK_TYPENAME = 376,
    TOK_UCHARN = 377,
    TOK_UCHAR = 378,
    TOK_ULONG = 379,
    TOK_USHORT = 380,
    TOK_UINT = 381,
    TOK_UINT_LONG = 382,
    TOK_UINT_LONG_LONG = 383,
    TOK_UINTN = 384,
    TOK_ULONGN = 385,
    TOK_UINTPTR_T = 386,
    TOK_UNION = 387,
    TOK_UNSIGNED = 388,
    TOK_USHORTN = 389,
    TOK_VOID = 390,
    TOK_VOLATILE = 391,
    TOK_WHILE = 392,
    TOK_WRITE_ONLY = 393
  };
#endif
/* Tokens.  */
#define TOK_ID 258
#define TOK_CONST_INT 259
#define TOK_CONST_INT_U 260
#define TOK_CONST_INT_L 261
#define TOK_CONST_INT_UL 262
#define TOK_CONST_INT_LL 263
#define TOK_CONST_INT_ULL 264
#define TOK_CONST_DEC 265
#define TOK_CONST_DEC_H 266
#define TOK_CONST_DEC_F 267
#define TOK_CONST_DEC_L 268
#define TOK_CONST_VAL 269
#define TOK_STRING 270
#define TOK_COMMA 271
#define TOK_SEMICOLON 272
#define TOK_ELLIPSIS 273
#define TOK_EQUAL 274
#define TOK_ADD_EQUAL 275
#define TOK_MINUS_EQUAL 276
#define TOK_MULT_EQUAL 277
#define TOK_DIV_EQUAL 278
#define TOK_MOD_EQUAL 279
#define TOK_AND_EQUAL 280
#define TOK_OR_EQUAL 281
#define TOK_EXCLUSIVE_EQUAL 282
#define TOK_SHIFT_RIGHT_EQUAL 283
#define TOK_SHIFT_LEFT_EQUAL 284
#define TOK_CONDITIONAL 285
#define TOK_COLON 286
#define TOK_LOGICAL_OR 287
#define TOK_LOGICAL_AND 288
#define TOK_BITWISE_OR 289
#define TOK_BITWISE_EXCLUSIVE 290
#define TOK_BITWISE_AND 291
#define TOK_EQUALITY 292
#define TOK_INEQUALITY 293
#define TOK_GREATER 294
#define TOK_LESS 295
#define TOK_GREATER_EQUAL 296
#define TOK_LESS_EQUAL 297
#define TOK_SHIFT_RIGHT 298
#define TOK_SHIFT_LEFT 299
#define TOK_PLUS 300
#define TOK_MINUS 301
#define TOK_MULT 302
#define TOK_DIV 303
#define TOK_MOD 304
#define TOK_PREFIX 305
#define TOK_LOGICAL_NEGATE 306
#define TOK_BITWISE_NOT 307
#define TOK_CURLY_BRACE_CLOSE 308
#define TOK_CURLY_BRACE_OPEN 309
#define TOK_PAR_OPEN 310
#define TOK_PAR_CLOSE 311
#define TOK_BRACKET_OPEN 312
#define TOK_BRACKET_CLOSE 313
#define TOK_POSTFIX 314
#define TOK_STRUCT_REF 315
#define TOK_STRUCT_DEREF 316
#define TOK_DECREMENT 317
#define TOK_INCREMENT 318
#define TOK_AUTO 319
#define TOK_BOOL 320
#define TOK_BREAK 321
#define TOK_CASE 322
#define TOK_CHAR 323
#define TOK_CHARN 324
#define TOK_CONSTANT 325
#define TOK_CONST 326
#define TOK_CONTINUE 327
#define TOK_DEFAULT 328
#define TOK_DO 329
#define TOK_DOUBLE 330
#define TOK_DOUBLE_LONG 331
#define TOK_DOUBLEN 332
#define TOK_ENUM 333
#define TOK_EVENT_T 334
#define TOK_EXTERN 335
#define TOK_FLOAT 336
#define TOK_FLOATN 337
#define TOK_FOR 338
#define TOK_GLOBAL 339
#define TOK_GOTO 340
#define TOK_HALF 341
#define TOK_IF 342
#define TOK_ELSE 343
#define TOK_IMAGE2D_T 344
#define TOK_IMAGE3D_T 345
#define TOK_IMAGE2D_ARRAY_T 346
#define TOK_IMAGE1D_T 347
#define TOK_IMAGE1D_BUFFER_T 348
#define TOK_IMAGE1D_ARRAY_T 349
#define TOK_INLINE 350
#define TOK_INT 351
#define TOK_INT_LONG 352
#define TOK_LONG_LONG 353
#define TOK_INTN 354
#define TOK_INTPTR_T 355
#define TOK_KERNEL 356
#define TOK_LOCAL 357
#define TOK_LONG 358
#define TOK_LONGN 359
#define TOK_PRIVATE 360
#define TOK_PTRDIFF_T 361
#define TOK_READ_ONLY 362
#define TOK_READ_WRITE 363
#define TOK_REGISTER 364
#define TOK_RETURN 365
#define TOK_SAMPLER_T 366
#define TOK_SHORT 367
#define TOK_SHORTN 368
#define TOK_SIGNED 369
#define TOK_SIZEOF 370
#define TOK_SIZE_T 371
#define TOK_STATIC 372
#define TOK_STRUCT 373
#define TOK_SWITCH 374
#define TOK_TYPEDEF 375
#define TOK_TYPENAME 376
#define TOK_UCHARN 377
#define TOK_UCHAR 378
#define TOK_ULONG 379
#define TOK_USHORT 380
#define TOK_UINT 381
#define TOK_UINT_LONG 382
#define TOK_UINT_LONG_LONG 383
#define TOK_UINTN 384
#define TOK_ULONGN 385
#define TOK_UINTPTR_T 386
#define TOK_UNION 387
#define TOK_UNSIGNED 388
#define TOK_USHORTN 389
#define TOK_VOID 390
#define TOK_VOLATILE 391
#define TOK_WHILE 392
#define TOK_WRITE_ONLY 393

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
typedef union YYSTYPE YYSTYPE;
union YYSTYPE
{
#line 62 "parser.y" /* yacc.c:355  */

	long int const_int_val;
	unsigned long long const_int_val_ull;
	double  const_float_val;
	char * identifier;
	struct cl2llvm_type_t *llvm_type_ref;
	struct cl2llvm_val_t *llvm_value_ref;
	struct list_t * init_list;
	struct list_t * list_val_t;
	struct cl2llvm_arg_t *arg_t;
	struct list_t *arg_list;
	LLVMBasicBlockRef basic_block_ref;
	struct cl2llvm_while_blocks_t *llvm_while_blocks;
	struct cl2llvm_for_blocks_t *llvm_for_blocks;
	struct cl2llvm_decl_list_t *decl_list;

#line 468 "parser.c" /* yacc.c:355  */
};
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif


extern YYSTYPE cl2llvm_yylval;

int cl2llvm_yyparse (void);

#endif /* !YY_CL2LLVM_YY_PARSER_H_INCLUDED  */

/* Copy the second part of user declarations.  */

#line 483 "parser.c" /* yacc.c:358  */

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
         || (defined YYSTYPE_IS_TRIVIAL && YYSTYPE_IS_TRIVIAL)))

/* A type that is properly aligned for any stack member.  */
union yyalloc
{
  yytype_int16 yyss_alloc;
  YYSTYPE yyvs_alloc;
};

/* The size of the maximum gap between one aligned stack and the next.  */
# define YYSTACK_GAP_MAXIMUM (sizeof (union yyalloc) - 1)

/* The size of an array large to enough to hold all stacks, each with
   N elements.  */
# define YYSTACK_BYTES(N) \
     ((N) * (sizeof (yytype_int16) + sizeof (YYSTYPE)) \
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
#define YYFINAL  63
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   1751

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  139
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  56
/* YYNRULES -- Number of rules.  */
#define YYNRULES  204
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  337

/* YYTRANSLATE[YYX] -- Symbol number corresponding to YYX as returned
   by yylex, with out-of-bounds checking.  */
#define YYUNDEFTOK  2
#define YYMAXUTOK   393

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
      95,    96,    97,    98,    99,   100,   101,   102,   103,   104,
     105,   106,   107,   108,   109,   110,   111,   112,   113,   114,
     115,   116,   117,   118,   119,   120,   121,   122,   123,   124,
     125,   126,   127,   128,   129,   130,   131,   132,   133,   134,
     135,   136,   137,   138
};

#if YYDEBUG
  /* YYRLINE[YYN] -- Source line where rule number YYN was defined.  */
static const yytype_uint16 yyrline[] =
{
       0,   222,   222,   223,   227,   228,   232,   241,   240,   387,
     393,   399,   407,   413,   424,   428,   473,   477,   481,   486,
     494,   500,   506,   512,   518,   525,   531,   540,   541,   545,
     546,   547,   552,   556,   562,   564,   568,   572,   650,   701,
     718,   739,   748,   758,   763,   764,   765,   766,   767,   768,
     769,   770,   784,   788,   792,   796,   800,   807,   894,   902,
     908,   913,   918,   923,   928,   936,   941,   944,   948,   956,
     967,   977,   990,  1005,  1173,  1174,  1178,  1182,  1186,  1190,
    1191,  1192,  1193,  1197,  1201,  1205,  1213,  1212,  1239,  1238,
    1276,  1293,  1328,  1292,  1375,  1411,  1374,  1458,  1483,  1457,
    1506,  1505,  1534,  1561,  1564,  1570,  1572,  1576,  1649,  1718,
    1796,  1875,  1933,  1997,  2060,  2139,  2218,  2308,  2397,  2486,
    2575,  2681,  2782,  2808,  2899,  2990,  3086,  3179,  3267,  3349,
    3431,  3513,  3596,  3678,  3682,  3687,  3692,  3709,  3773,  3837,
    3905,  3976,  4046,  4117,  4188,  4236,  4240,  4251,  4256,  4305,
    4316,  4436,  4450,  4454,  4464,  4470,  4476,  4482,  4488,  4494,
    4500,  4506,  4512,  4518,  4524,  4619,  4627,  4631,  4649,  4654,
    4659,  4664,  4669,  4674,  4679,  4684,  4689,  4694,  4699,  4704,
    4710,  4716,  4722,  4728,  4734,  4740,  4747,  4754,  4761,  4768,
    4775,  4781,  4787,  4793,  4799,  4805,  4811,  4817,  4823,  4829,
    4835,  4841,  4847,  4853,  4860
};
#endif

#if YYDEBUG || YYERROR_VERBOSE || 0
/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "$end", "error", "$undefined", "TOK_ID", "TOK_CONST_INT",
  "TOK_CONST_INT_U", "TOK_CONST_INT_L", "TOK_CONST_INT_UL",
  "TOK_CONST_INT_LL", "TOK_CONST_INT_ULL", "TOK_CONST_DEC",
  "TOK_CONST_DEC_H", "TOK_CONST_DEC_F", "TOK_CONST_DEC_L", "TOK_CONST_VAL",
  "TOK_STRING", "TOK_COMMA", "TOK_SEMICOLON", "TOK_ELLIPSIS", "TOK_EQUAL",
  "TOK_ADD_EQUAL", "TOK_MINUS_EQUAL", "TOK_MULT_EQUAL", "TOK_DIV_EQUAL",
  "TOK_MOD_EQUAL", "TOK_AND_EQUAL", "TOK_OR_EQUAL", "TOK_EXCLUSIVE_EQUAL",
  "TOK_SHIFT_RIGHT_EQUAL", "TOK_SHIFT_LEFT_EQUAL", "TOK_CONDITIONAL",
  "TOK_COLON", "TOK_LOGICAL_OR", "TOK_LOGICAL_AND", "TOK_BITWISE_OR",
  "TOK_BITWISE_EXCLUSIVE", "TOK_BITWISE_AND", "TOK_EQUALITY",
  "TOK_INEQUALITY", "TOK_GREATER", "TOK_LESS", "TOK_GREATER_EQUAL",
  "TOK_LESS_EQUAL", "TOK_SHIFT_RIGHT", "TOK_SHIFT_LEFT", "TOK_PLUS",
  "TOK_MINUS", "TOK_MULT", "TOK_DIV", "TOK_MOD", "TOK_PREFIX",
  "TOK_LOGICAL_NEGATE", "TOK_BITWISE_NOT", "TOK_CURLY_BRACE_CLOSE",
  "TOK_CURLY_BRACE_OPEN", "TOK_PAR_OPEN", "TOK_PAR_CLOSE",
  "TOK_BRACKET_OPEN", "TOK_BRACKET_CLOSE", "TOK_POSTFIX", "TOK_STRUCT_REF",
  "TOK_STRUCT_DEREF", "TOK_DECREMENT", "TOK_INCREMENT", "TOK_AUTO",
  "TOK_BOOL", "TOK_BREAK", "TOK_CASE", "TOK_CHAR", "TOK_CHARN",
  "TOK_CONSTANT", "TOK_CONST", "TOK_CONTINUE", "TOK_DEFAULT", "TOK_DO",
  "TOK_DOUBLE", "TOK_DOUBLE_LONG", "TOK_DOUBLEN", "TOK_ENUM",
  "TOK_EVENT_T", "TOK_EXTERN", "TOK_FLOAT", "TOK_FLOATN", "TOK_FOR",
  "TOK_GLOBAL", "TOK_GOTO", "TOK_HALF", "TOK_IF", "TOK_ELSE",
  "TOK_IMAGE2D_T", "TOK_IMAGE3D_T", "TOK_IMAGE2D_ARRAY_T", "TOK_IMAGE1D_T",
  "TOK_IMAGE1D_BUFFER_T", "TOK_IMAGE1D_ARRAY_T", "TOK_INLINE", "TOK_INT",
  "TOK_INT_LONG", "TOK_LONG_LONG", "TOK_INTN", "TOK_INTPTR_T",
  "TOK_KERNEL", "TOK_LOCAL", "TOK_LONG", "TOK_LONGN", "TOK_PRIVATE",
  "TOK_PTRDIFF_T", "TOK_READ_ONLY", "TOK_READ_WRITE", "TOK_REGISTER",
  "TOK_RETURN", "TOK_SAMPLER_T", "TOK_SHORT", "TOK_SHORTN", "TOK_SIGNED",
  "TOK_SIZEOF", "TOK_SIZE_T", "TOK_STATIC", "TOK_STRUCT", "TOK_SWITCH",
  "TOK_TYPEDEF", "TOK_TYPENAME", "TOK_UCHARN", "TOK_UCHAR", "TOK_ULONG",
  "TOK_USHORT", "TOK_UINT", "TOK_UINT_LONG", "TOK_UINT_LONG_LONG",
  "TOK_UINTN", "TOK_ULONGN", "TOK_UINTPTR_T", "TOK_UNION", "TOK_UNSIGNED",
  "TOK_USHORTN", "TOK_VOID", "TOK_VOLATILE", "TOK_WHILE", "TOK_WRITE_ONLY",
  "$accept", "program", "external_def", "func_decl", "func_def", "$@1",
  "arg_list", "arg", "declarator_list", "addr_qual", "declarator",
  "type_qual", "access_qual", "sc_spec", "stmt_list", "lvalue",
  "array_deref_list", "stmt", "func_call", "param_list", "array_init",
  "init", "init_list", "declaration", "stmt_or_stmt_list", "label_stmt",
  "goto_stmt", "switch_stmt", "switch_body", "default_clause",
  "case_clause", "if_stmt", "@2", "if", "@3", "for_loop",
  "for_loop_header", "@4", "$@5", "@6", "$@7", "do_while_loop", "@8",
  "$@9", "while_loop", "$@10", "while_block_init", "maybe_expr", "expr",
  "unary_expr", "vec_literal", "vec_literal_param_two_elem",
  "vec_literal_param_list", "primary", "type_spec", "type_name", YY_NULLPTR
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
     355,   356,   357,   358,   359,   360,   361,   362,   363,   364,
     365,   366,   367,   368,   369,   370,   371,   372,   373,   374,
     375,   376,   377,   378,   379,   380,   381,   382,   383,   384,
     385,   386,   387,   388,   389,   390,   391,   392,   393
};
# endif

#define YYPACT_NINF -196

#define yypact_value_is_default(Yystate) \
  (!!((Yystate) == (-196)))

#define YYTABLE_NINF -104

#define yytable_value_is_error(Yytable_value) \
  0

  /* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
     STATE-NUM.  */
static const yytype_int16 yypact[] =
{
    1279,  -196,  -196,  -196,  -196,  -196,  -196,  -196,  -196,  -196,
    -196,  -196,  -196,  -196,  -196,  -196,  -196,  -196,  -196,  -196,
    -196,  -196,  -196,  -196,  -196,  -196,  -196,  -196,  -196,  -196,
    -196,  -196,  -196,  -196,  -196,  -196,  -196,  -196,  -196,  -196,
    -196,  -196,  -196,  -196,  -196,  -196,  -196,  -196,  -196,  -196,
    -196,   157,  -196,  -196,  -196,   640,  -196,  -196,  -196,  -196,
    -196,    -8,  -196,  -196,  -196,   -26,  -196,  -196,  1279,    -3,
    -196,   715,  1279,    95,  -196,  -196,  -196,  -196,   293,    -5,
    -196,  -196,  -196,  -196,  -196,  -196,  -196,  -196,  -196,  -196,
       7,  1222,  1222,     7,  1222,  1222,   293,  1001,     7,     7,
      24,    31,  -196,     1,    56,    62,  1222,    64,  1222,    65,
    -196,  -196,   790,    18,   425,  -196,  -196,  -196,   293,  -196,
    -196,  -196,  -196,    42,  -196,   429,  -196,  -196,   106,  1643,
    -196,  -196,  -196,  -196,  1134,  -196,     7,   -20,   110,  -196,
    -196,   -20,  -196,  -196,   101,   562,  1478,   -14,   -20,   -20,
    -196,  -196,   429,   565,   138,  1222,  1458,  1351,  1578,  -196,
       3,    35,  -196,  1222,  1222,  1222,  1222,  1222,  1222,  1222,
    1222,  1222,  1222,  1222,  1222,   163,  -196,  -196,   114,  -196,
    -196,  -196,  -196,  1222,  1222,  1222,  1222,  1222,  1222,  1222,
    1222,  1222,  1222,  1222,  1222,  1222,  1222,  1222,  1222,  1222,
    1222,  1222,  1147,  -196,     4,    14,  -196,  1643,    58,  -196,
    -196,  -196,  1283,    37,   865,  -196,   150,  -196,  1503,  -196,
     -11,   -29,  1222,  1209,     8,  -196,   173,  -196,  1643,  1643,
    1643,  1643,  1643,  1643,  1643,  1643,  1643,  1643,  1643,   279,
    -196,  1222,   429,  1603,  1660,    99,  1675,  1689,  1702,   169,
     169,   115,   115,   115,   115,   143,   143,    79,    79,  -196,
    -196,  -196,   100,  1222,  1147,  -196,  1001,  -196,   123,    68,
    1222,  -196,  -196,  -196,  1222,   151,   -18,  -196,  -196,  1528,
    -196,  1643,  -196,    68,  -196,  1267,  -196,  1222,  -196,  1643,
      72,  -196,  1643,   986,  -196,    30,  -196,   164,  1222,   429,
    1623,   293,  -196,  -196,  -196,  -196,     8,  -196,  -196,  1643,
    1222,  1222,  1222,  -196,  1222,  -196,   167,  -196,   293,  -196,
     429,  -196,  1643,  1643,  1643,  1553,  1222,  -196,  -196,  -196,
     168,   137,  1222,  -196,  -196,   139,  -196
};

  /* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
     Performed when YYTABLE does not specify something else to do.  Zero
     means the default is an error.  */
static const yytype_uint8 yydefact[] =
{
       0,   200,   198,   192,    19,    27,   201,   202,   194,   172,
      32,   199,   193,    16,   204,   173,   174,   175,   176,   177,
     178,    23,   195,   196,   197,   190,   168,    22,    17,   191,
      18,   169,    29,    31,   171,   183,   189,    33,   186,   182,
     184,   179,   180,   181,   185,   187,   170,   188,   203,    28,
      30,     0,     2,     5,     4,     0,    25,    14,    26,    21,
      24,    20,   166,     1,     3,     0,    15,   167,     9,     0,
      10,    13,     0,     0,    12,    11,     6,     7,    34,    39,
     154,   156,   155,   157,   158,   159,   160,   161,   162,   163,
       0,     0,     0,     0,     0,     0,    34,     0,     0,     0,
       0,     0,    97,     0,     0,     0,     0,     0,     0,     0,
      46,    45,     0,     0,   164,    74,   135,    44,    34,    55,
      56,    54,    50,    85,    47,   103,    49,    48,     0,   104,
     134,   165,   105,    76,     0,    39,     0,   149,    39,   145,
     144,    38,   136,   148,     0,   164,     0,     0,   142,   141,
      53,    52,   103,   103,     0,     0,     0,     0,     0,   102,
      66,     0,     8,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,   143,   140,    37,    35,
      86,    90,    43,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,    58,     0,     0,    61,    59,     0,    75,
      36,   106,     0,     0,     0,    94,     0,    77,     0,    51,
       0,     0,     0,     0,    66,    69,     0,    73,   122,   123,
     124,   126,   125,   127,   128,   129,   130,   131,   132,     0,
      40,     0,   103,     0,   121,   120,   138,   139,   137,   114,
     115,   117,   116,   119,   118,   113,   112,   107,   108,   109,
     110,   111,     0,     0,     0,    57,     0,   146,     0,    66,
     103,    91,    88,   147,     0,     0,     0,    79,    80,     0,
      68,    67,    71,    66,    41,     0,    87,     0,    65,    60,
       0,    63,    62,     0,   152,     0,    98,     0,   103,   103,
       0,    34,    78,    81,    82,   100,    66,    70,    42,   133,
       0,     0,     0,   150,     0,    95,     0,    89,    34,    83,
     103,    72,    64,   151,   153,     0,   103,    92,    84,   101,
       0,     0,   103,    99,    96,     0,    93
};

  /* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
    -196,  -196,   146,    12,    34,  -196,  -196,   122,    16,  -196,
     -46,  -196,  -196,  -196,   -94,   -79,  -113,  -196,  -196,    -4,
    -195,  -193,  -196,    46,  -120,  -196,  -196,  -196,  -196,   -75,
     -74,  -196,  -196,  -196,  -196,  -196,  -196,  -196,  -196,  -196,
    -196,  -196,  -196,  -196,  -196,  -196,  -196,  -146,   -91,  -196,
    -196,  -196,  -196,  -196,   -89,  -196
};

  /* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int16 yydefgoto[] =
{
      -1,    51,    52,   110,   111,    78,    69,    70,   112,    56,
      57,    58,    59,    60,   113,   114,   178,   115,   116,   205,
     206,   225,   161,   117,   118,   119,   120,   121,   276,   277,
     278,   122,   242,   123,   299,   124,   125,   298,   332,   270,
     326,   126,   152,   314,   127,   320,   222,   128,   129,   130,
     131,   294,   295,   132,    61,    62
};

  /* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
     positive, shift that token.  If negative, reduce the rule whose
     number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_int16 yytable[] =
{
     139,   140,   144,   142,   143,   181,   146,   216,   147,    66,
     135,   137,    53,    72,   141,   156,    55,   158,   145,   148,
     149,   204,   223,   263,   179,    66,   133,   223,   280,    68,
     264,   282,   213,    67,    54,   302,    67,   174,   274,    67,
     175,   150,   212,   207,   275,   273,   312,   224,   151,   274,
     134,   226,   227,    73,    93,   275,   153,   208,    68,   154,
     174,   241,   136,    53,   218,   241,    66,    55,   220,   291,
     265,   162,   228,   229,   230,   231,   232,   233,   234,   235,
     236,   237,   238,   239,    71,    54,   313,   223,    71,   204,
     307,   310,   243,   244,   245,   246,   247,   248,   249,   250,
     251,   252,   253,   254,   255,   256,   257,   258,   259,   260,
     261,   207,    76,   321,   210,   174,   264,   155,   175,   157,
     159,   267,   286,   182,   297,   174,   199,   200,   201,   241,
     180,   279,   281,   186,   187,   188,   189,   190,   191,   192,
     193,   194,   195,   196,   197,   198,   199,   200,   201,    77,
     285,   290,   316,   288,   209,   217,   224,    63,   195,   196,
     197,   198,   199,   200,   201,   134,   240,   271,    66,   214,
     306,   241,   289,   292,   268,   293,   283,   147,   296,   317,
     331,   315,   301,   300,   327,   333,   335,   145,   197,   198,
     199,   200,   201,   334,    75,   336,   309,    64,   262,   215,
     329,   303,   304,     0,     0,     0,     0,   319,   191,   192,
     193,   194,   195,   196,   197,   198,   199,   200,   201,   322,
     323,   324,     1,   325,   328,     2,     3,     4,     5,     0,
       0,     0,     6,     7,     8,     0,     9,    10,    11,    12,
       0,    13,     0,    14,     0,     0,    15,    16,    17,    18,
      19,    20,    21,    22,    23,    24,    25,    26,    27,    28,
       0,    29,    30,    31,    32,    33,     0,     0,    34,    35,
      36,     0,     0,     0,    37,     0,     0,     0,     0,    38,
      39,     0,    40,    41,    42,    43,    44,    45,    46,     0,
       0,    47,    48,    49,     0,    50,    79,    80,    81,    82,
      83,    84,    85,    86,    87,    88,    89,     0,     0,   183,
    -103,   184,   185,   186,   187,   188,   189,   190,   191,   192,
     193,   194,   195,   196,   197,   198,   199,   200,   201,    90,
       0,     0,     0,     0,     0,     0,     0,   284,    91,    92,
      93,     0,     0,     0,    94,    95,     0,    96,    97,     0,
       0,     0,     0,     0,     0,    98,    99,     0,     1,   100,
       0,     2,     3,     4,     5,   101,     0,   102,     6,     7,
       8,     0,     9,    10,    11,    12,   103,    13,   104,    14,
     105,     0,    15,    16,    17,    18,    19,    20,    21,    22,
      23,    24,    25,    26,    27,    28,     0,    29,    30,    31,
      32,    33,     0,   106,    34,    35,    36,     0,   107,     0,
      37,     0,   108,     0,     0,    38,    39,     0,    40,    41,
      42,    43,    44,    45,    46,     0,     0,    47,    48,    49,
     109,    50,    79,    80,    81,    82,    83,    84,    85,    86,
      87,    88,    89,     0,   163,   164,   165,   166,   167,   168,
     169,   170,   171,   172,   173,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,    90,     0,     0,     0,     0,
       0,     0,     0,     0,    91,    92,    93,     0,     0,     0,
      94,    95,   174,    96,    97,   175,     0,   176,   177,     0,
       0,    98,    99,     0,     1,   100,     0,     2,     3,     4,
       5,   101,     0,   102,     6,     7,     8,     0,     9,    10,
      11,    12,   103,    13,   104,    14,   105,     0,    15,    16,
      17,    18,    19,    20,    21,    22,    23,    24,    25,    26,
      27,    28,     0,    29,    30,    31,    32,    33,     0,   106,
      34,    35,    36,     0,   107,     0,    37,     0,   108,     0,
       0,    38,    39,     0,    40,    41,    42,    43,    44,    45,
      46,     0,     0,    47,    48,    49,   109,    50,   138,    80,
      81,    82,    83,    84,    85,    86,    87,    88,    89,     0,
       0,   163,   164,   165,   166,   167,   168,   169,   170,   171,
     172,   173,     0,     0,     0,     0,     0,     0,     0,     0,
       0,    90,     0,     0,     0,     0,     0,     0,     0,     0,
      91,    92,    93,     0,     0,     0,    94,    95,   210,   174,
      97,     0,   175,     0,   176,   177,     0,    98,    99,     0,
       1,     0,     0,     2,     3,     4,     5,     0,     0,     0,
       6,     7,     8,    65,     9,    10,    11,    12,     0,    13,
       0,    14,     0,     0,    15,    16,    17,    18,    19,    20,
      21,    22,    23,    24,    25,    26,    27,    28,     0,    29,
      30,    31,    32,    33,     0,     0,    34,    35,    36,     0,
     107,     0,    37,     0,     0,     0,     0,    38,    39,     0,
      40,    41,    42,    43,    44,    45,    46,     0,     0,    47,
      48,    49,     0,    50,     0,     1,     0,     0,     2,     3,
       4,     5,     0,     0,     0,     6,     7,     8,    74,     9,
      10,    11,    12,     0,    13,     0,    14,     0,     0,    15,
      16,    17,    18,    19,    20,    21,    22,    23,    24,    25,
      26,    27,    28,     0,    29,    30,    31,    32,    33,     0,
       0,    34,    35,    36,     0,     0,     0,    37,     0,     0,
       0,     0,    38,    39,     0,    40,    41,    42,    43,    44,
      45,    46,     0,     0,    47,    48,    49,     0,    50,     0,
       1,     0,     0,     2,     3,     4,     5,     0,     0,     0,
       6,     7,     8,   160,     9,    10,    11,    12,     0,    13,
       0,    14,     0,     0,    15,    16,    17,    18,    19,    20,
      21,    22,    23,    24,    25,    26,    27,    28,     0,    29,
      30,    31,    32,    33,     0,     0,    34,    35,    36,     0,
       0,     0,    37,     0,     0,     0,     0,    38,    39,     0,
      40,    41,    42,    43,    44,    45,    46,     0,     0,    47,
      48,    49,     0,    50,     0,     1,     0,     0,     2,     3,
       4,     5,     0,     0,     0,     6,     7,     8,   269,     9,
      10,    11,    12,     0,    13,     0,    14,     0,     0,    15,
      16,    17,    18,    19,    20,    21,    22,    23,    24,    25,
      26,    27,    28,     0,    29,    30,    31,    32,    33,     0,
       0,    34,    35,    36,     0,     0,     0,    37,     0,     0,
       0,     0,    38,    39,     0,    40,    41,    42,    43,    44,
      45,    46,     0,     0,    47,    48,    49,     0,    50,     0,
       1,     0,     0,     2,     3,     4,     5,     0,     0,     0,
       6,     7,     8,     0,     9,    10,    11,    12,     0,    13,
       0,    14,     0,     0,    15,    16,    17,    18,    19,    20,
      21,    22,    23,    24,    25,    26,    27,    28,     0,    29,
      30,    31,    32,    33,     0,     0,    34,    35,    36,     0,
       0,     0,    37,     0,     0,     0,     0,    38,    39,     0,
      40,    41,    42,    43,    44,    45,    46,     0,     0,    47,
      48,    49,   311,    50,   138,    80,    81,    82,    83,    84,
      85,    86,    87,    88,    89,     0,   183,     0,   184,   185,
     186,   187,   188,   189,   190,   191,   192,   193,   194,   195,
     196,   197,   198,   199,   200,   201,     0,    90,     0,     0,
       0,     0,   211,     0,     0,     0,    91,    92,    93,     0,
       0,     0,    94,    95,     0,     0,    97,     0,     0,     0,
       0,     0,     0,    98,    99,     0,     1,     0,     0,     2,
       3,     0,     0,     0,     0,     0,     6,     7,     8,     0,
       9,     0,    11,    12,     0,     0,     0,    14,     0,     0,
      15,    16,    17,    18,    19,    20,     0,    22,    23,    24,
      25,    26,     0,     0,     0,    29,     0,    31,     0,     0,
       0,     0,    34,    35,    36,     0,   107,     0,     0,     0,
       0,     0,     0,    38,    39,     0,    40,    41,    42,    43,
      44,    45,    46,     0,     0,    47,    48,   138,    80,    81,
      82,    83,    84,    85,    86,    87,    88,    89,     0,     0,
     138,    80,    81,    82,    83,    84,    85,    86,    87,    88,
      89,     0,     0,     0,     0,     0,     0,     0,     0,     0,
      90,     0,     0,     0,     0,     0,     0,     0,     0,    91,
      92,    93,     0,    90,     0,    94,    95,     0,   202,    97,
     203,   174,    91,    92,    93,     0,    98,    99,    94,    95,
       0,   202,    97,     0,   174,     0,     0,     0,     0,    98,
      99,     0,   138,    80,    81,    82,    83,    84,    85,    86,
      87,    88,    89,     0,     0,   138,    80,    81,    82,    83,
      84,    85,    86,    87,    88,    89,     0,     0,     0,     0,
       0,     0,     0,     0,     0,    90,     0,     0,     0,   107,
       0,     0,     0,     0,    91,    92,    93,     0,    90,     0,
      94,    95,   107,   202,    97,     0,     0,    91,    92,    93,
       0,    98,    99,    94,    95,     0,     0,    97,     0,     0,
       0,     0,     0,     0,    98,    99,   138,    80,    81,    82,
      83,    84,    85,    86,    87,    88,    89,   183,     0,   184,
     185,   186,   187,   188,   189,   190,   191,   192,   193,   194,
     195,   196,   197,   198,   199,   200,   201,     0,     0,    90,
       0,     0,     0,     0,   107,   308,     0,     0,    91,    92,
      93,     0,     0,     0,    94,    95,     0,   107,   266,     0,
       0,     0,     0,     0,     1,    98,    99,     2,     3,     4,
       5,     0,     0,     0,     6,     7,     8,     0,     9,    10,
      11,    12,     0,    13,     0,    14,     0,     0,    15,    16,
      17,    18,    19,    20,    21,    22,    23,    24,    25,    26,
      27,    28,     0,    29,    30,    31,    32,    33,     0,     0,
      34,    35,    36,     0,     0,     0,    37,     0,   107,     0,
       0,    38,    39,     0,    40,    41,    42,    43,    44,    45,
      46,     0,     0,    47,    48,    49,     1,    50,     0,     2,
       3,     0,     0,     0,     0,     0,     6,     7,     8,     0,
       9,     0,    11,    12,     0,     0,     0,    14,     0,     0,
      15,    16,    17,    18,    19,    20,     0,    22,    23,    24,
      25,    26,     0,     0,     0,    29,     0,    31,     0,     0,
       0,     0,    34,    35,    36,     0,     0,     0,     0,     0,
       0,     0,     0,    38,    39,   219,    40,    41,    42,    43,
      44,    45,    46,     0,     0,    47,    48,     0,   183,     0,
     184,   185,   186,   187,   188,   189,   190,   191,   192,   193,
     194,   195,   196,   197,   198,   199,   200,   201,   183,     0,
     184,   185,   186,   187,   188,   189,   190,   191,   192,   193,
     194,   195,   196,   197,   198,   199,   200,   201,     0,     0,
       0,     0,     0,   183,   211,   184,   185,   186,   187,   188,
     189,   190,   191,   192,   193,   194,   195,   196,   197,   198,
     199,   200,   201,     0,     0,     0,     0,     0,   183,   272,
     184,   185,   186,   187,   188,   189,   190,   191,   192,   193,
     194,   195,   196,   197,   198,   199,   200,   201,     0,     0,
       0,     0,     0,   183,   305,   184,   185,   186,   187,   188,
     189,   190,   191,   192,   193,   194,   195,   196,   197,   198,
     199,   200,   201,     0,     0,     0,     0,     0,   183,   330,
     184,   185,   186,   187,   188,   189,   190,   191,   192,   193,
     194,   195,   196,   197,   198,   199,   200,   201,     0,     0,
       0,     0,   221,   183,   287,   184,   185,   186,   187,   188,
     189,   190,   191,   192,   193,   194,   195,   196,   197,   198,
     199,   200,   201,   183,   318,   184,   185,   186,   187,   188,
     189,   190,   191,   192,   193,   194,   195,   196,   197,   198,
     199,   200,   201,   183,     0,   184,   185,   186,   187,   188,
     189,   190,   191,   192,   193,   194,   195,   196,   197,   198,
     199,   200,   201,   185,   186,   187,   188,   189,   190,   191,
     192,   193,   194,   195,   196,   197,   198,   199,   200,   201,
     187,   188,   189,   190,   191,   192,   193,   194,   195,   196,
     197,   198,   199,   200,   201,   188,   189,   190,   191,   192,
     193,   194,   195,   196,   197,   198,   199,   200,   201,   189,
     190,   191,   192,   193,   194,   195,   196,   197,   198,   199,
     200,   201
};

static const yytype_int16 yycheck[] =
{
      91,    92,    96,    94,    95,   125,    97,   153,    97,    55,
       3,    90,     0,    16,    93,   106,     0,   108,    97,    98,
      99,   134,    19,    19,   118,    71,    31,    19,   223,    55,
      16,   224,   152,    47,     0,    53,    47,    57,    67,    47,
      60,    17,    56,   134,    73,    56,    16,   160,    17,    67,
      55,    16,    17,    56,    47,    73,    55,   136,    55,     3,
      57,    57,    55,    51,   155,    57,   112,    51,   157,   264,
      56,    53,   163,   164,   165,   166,   167,   168,   169,   170,
     171,   172,   173,   174,    68,    51,    56,    19,    72,   202,
     283,    19,   183,   184,   185,   186,   187,   188,   189,   190,
     191,   192,   193,   194,   195,   196,   197,   198,   199,   200,
     201,   202,    17,   306,    56,    57,    16,    55,    60,    55,
      55,   212,   242,    17,   270,    57,    47,    48,    49,    57,
      88,   222,   223,    34,    35,    36,    37,    38,    39,    40,
      41,    42,    43,    44,    45,    46,    47,    48,    49,    54,
     241,   264,   298,    53,    53,    17,   269,     0,    43,    44,
      45,    46,    47,    48,    49,    55,     3,    17,   214,   153,
     283,    57,   263,   264,   137,   266,     3,   266,    55,   299,
     326,    17,    31,   274,    17,    17,   332,   266,    45,    46,
      47,    48,    49,    56,    72,    56,   287,    51,   202,   153,
     320,   276,   276,    -1,    -1,    -1,    -1,   301,    39,    40,
      41,    42,    43,    44,    45,    46,    47,    48,    49,   310,
     311,   312,    65,   314,   318,    68,    69,    70,    71,    -1,
      -1,    -1,    75,    76,    77,    -1,    79,    80,    81,    82,
      -1,    84,    -1,    86,    -1,    -1,    89,    90,    91,    92,
      93,    94,    95,    96,    97,    98,    99,   100,   101,   102,
      -1,   104,   105,   106,   107,   108,    -1,    -1,   111,   112,
     113,    -1,    -1,    -1,   117,    -1,    -1,    -1,    -1,   122,
     123,    -1,   125,   126,   127,   128,   129,   130,   131,    -1,
      -1,   134,   135,   136,    -1,   138,     3,     4,     5,     6,
       7,     8,     9,    10,    11,    12,    13,    -1,    -1,    30,
      17,    32,    33,    34,    35,    36,    37,    38,    39,    40,
      41,    42,    43,    44,    45,    46,    47,    48,    49,    36,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    58,    45,    46,
      47,    -1,    -1,    -1,    51,    52,    -1,    54,    55,    -1,
      -1,    -1,    -1,    -1,    -1,    62,    63,    -1,    65,    66,
      -1,    68,    69,    70,    71,    72,    -1,    74,    75,    76,
      77,    -1,    79,    80,    81,    82,    83,    84,    85,    86,
      87,    -1,    89,    90,    91,    92,    93,    94,    95,    96,
      97,    98,    99,   100,   101,   102,    -1,   104,   105,   106,
     107,   108,    -1,   110,   111,   112,   113,    -1,   115,    -1,
     117,    -1,   119,    -1,    -1,   122,   123,    -1,   125,   126,
     127,   128,   129,   130,   131,    -1,    -1,   134,   135,   136,
     137,   138,     3,     4,     5,     6,     7,     8,     9,    10,
      11,    12,    13,    -1,    19,    20,    21,    22,    23,    24,
      25,    26,    27,    28,    29,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    36,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    45,    46,    47,    -1,    -1,    -1,
      51,    52,    57,    54,    55,    60,    -1,    62,    63,    -1,
      -1,    62,    63,    -1,    65,    66,    -1,    68,    69,    70,
      71,    72,    -1,    74,    75,    76,    77,    -1,    79,    80,
      81,    82,    83,    84,    85,    86,    87,    -1,    89,    90,
      91,    92,    93,    94,    95,    96,    97,    98,    99,   100,
     101,   102,    -1,   104,   105,   106,   107,   108,    -1,   110,
     111,   112,   113,    -1,   115,    -1,   117,    -1,   119,    -1,
      -1,   122,   123,    -1,   125,   126,   127,   128,   129,   130,
     131,    -1,    -1,   134,   135,   136,   137,   138,     3,     4,
       5,     6,     7,     8,     9,    10,    11,    12,    13,    -1,
      -1,    19,    20,    21,    22,    23,    24,    25,    26,    27,
      28,    29,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    36,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      45,    46,    47,    -1,    -1,    -1,    51,    52,    56,    57,
      55,    -1,    60,    -1,    62,    63,    -1,    62,    63,    -1,
      65,    -1,    -1,    68,    69,    70,    71,    -1,    -1,    -1,
      75,    76,    77,     3,    79,    80,    81,    82,    -1,    84,
      -1,    86,    -1,    -1,    89,    90,    91,    92,    93,    94,
      95,    96,    97,    98,    99,   100,   101,   102,    -1,   104,
     105,   106,   107,   108,    -1,    -1,   111,   112,   113,    -1,
     115,    -1,   117,    -1,    -1,    -1,    -1,   122,   123,    -1,
     125,   126,   127,   128,   129,   130,   131,    -1,    -1,   134,
     135,   136,    -1,   138,    -1,    65,    -1,    -1,    68,    69,
      70,    71,    -1,    -1,    -1,    75,    76,    77,     3,    79,
      80,    81,    82,    -1,    84,    -1,    86,    -1,    -1,    89,
      90,    91,    92,    93,    94,    95,    96,    97,    98,    99,
     100,   101,   102,    -1,   104,   105,   106,   107,   108,    -1,
      -1,   111,   112,   113,    -1,    -1,    -1,   117,    -1,    -1,
      -1,    -1,   122,   123,    -1,   125,   126,   127,   128,   129,
     130,   131,    -1,    -1,   134,   135,   136,    -1,   138,    -1,
      65,    -1,    -1,    68,    69,    70,    71,    -1,    -1,    -1,
      75,    76,    77,     3,    79,    80,    81,    82,    -1,    84,
      -1,    86,    -1,    -1,    89,    90,    91,    92,    93,    94,
      95,    96,    97,    98,    99,   100,   101,   102,    -1,   104,
     105,   106,   107,   108,    -1,    -1,   111,   112,   113,    -1,
      -1,    -1,   117,    -1,    -1,    -1,    -1,   122,   123,    -1,
     125,   126,   127,   128,   129,   130,   131,    -1,    -1,   134,
     135,   136,    -1,   138,    -1,    65,    -1,    -1,    68,    69,
      70,    71,    -1,    -1,    -1,    75,    76,    77,     3,    79,
      80,    81,    82,    -1,    84,    -1,    86,    -1,    -1,    89,
      90,    91,    92,    93,    94,    95,    96,    97,    98,    99,
     100,   101,   102,    -1,   104,   105,   106,   107,   108,    -1,
      -1,   111,   112,   113,    -1,    -1,    -1,   117,    -1,    -1,
      -1,    -1,   122,   123,    -1,   125,   126,   127,   128,   129,
     130,   131,    -1,    -1,   134,   135,   136,    -1,   138,    -1,
      65,    -1,    -1,    68,    69,    70,    71,    -1,    -1,    -1,
      75,    76,    77,    -1,    79,    80,    81,    82,    -1,    84,
      -1,    86,    -1,    -1,    89,    90,    91,    92,    93,    94,
      95,    96,    97,    98,    99,   100,   101,   102,    -1,   104,
     105,   106,   107,   108,    -1,    -1,   111,   112,   113,    -1,
      -1,    -1,   117,    -1,    -1,    -1,    -1,   122,   123,    -1,
     125,   126,   127,   128,   129,   130,   131,    -1,    -1,   134,
     135,   136,    16,   138,     3,     4,     5,     6,     7,     8,
       9,    10,    11,    12,    13,    -1,    30,    -1,    32,    33,
      34,    35,    36,    37,    38,    39,    40,    41,    42,    43,
      44,    45,    46,    47,    48,    49,    -1,    36,    -1,    -1,
      -1,    -1,    56,    -1,    -1,    -1,    45,    46,    47,    -1,
      -1,    -1,    51,    52,    -1,    -1,    55,    -1,    -1,    -1,
      -1,    -1,    -1,    62,    63,    -1,    65,    -1,    -1,    68,
      69,    -1,    -1,    -1,    -1,    -1,    75,    76,    77,    -1,
      79,    -1,    81,    82,    -1,    -1,    -1,    86,    -1,    -1,
      89,    90,    91,    92,    93,    94,    -1,    96,    97,    98,
      99,   100,    -1,    -1,    -1,   104,    -1,   106,    -1,    -1,
      -1,    -1,   111,   112,   113,    -1,   115,    -1,    -1,    -1,
      -1,    -1,    -1,   122,   123,    -1,   125,   126,   127,   128,
     129,   130,   131,    -1,    -1,   134,   135,     3,     4,     5,
       6,     7,     8,     9,    10,    11,    12,    13,    -1,    -1,
       3,     4,     5,     6,     7,     8,     9,    10,    11,    12,
      13,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      36,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    45,
      46,    47,    -1,    36,    -1,    51,    52,    -1,    54,    55,
      56,    57,    45,    46,    47,    -1,    62,    63,    51,    52,
      -1,    54,    55,    -1,    57,    -1,    -1,    -1,    -1,    62,
      63,    -1,     3,     4,     5,     6,     7,     8,     9,    10,
      11,    12,    13,    -1,    -1,     3,     4,     5,     6,     7,
       8,     9,    10,    11,    12,    13,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    36,    -1,    -1,    -1,   115,
      -1,    -1,    -1,    -1,    45,    46,    47,    -1,    36,    -1,
      51,    52,   115,    54,    55,    -1,    -1,    45,    46,    47,
      -1,    62,    63,    51,    52,    -1,    -1,    55,    -1,    -1,
      -1,    -1,    -1,    -1,    62,    63,     3,     4,     5,     6,
       7,     8,     9,    10,    11,    12,    13,    30,    -1,    32,
      33,    34,    35,    36,    37,    38,    39,    40,    41,    42,
      43,    44,    45,    46,    47,    48,    49,    -1,    -1,    36,
      -1,    -1,    -1,    -1,   115,    58,    -1,    -1,    45,    46,
      47,    -1,    -1,    -1,    51,    52,    -1,   115,    55,    -1,
      -1,    -1,    -1,    -1,    65,    62,    63,    68,    69,    70,
      71,    -1,    -1,    -1,    75,    76,    77,    -1,    79,    80,
      81,    82,    -1,    84,    -1,    86,    -1,    -1,    89,    90,
      91,    92,    93,    94,    95,    96,    97,    98,    99,   100,
     101,   102,    -1,   104,   105,   106,   107,   108,    -1,    -1,
     111,   112,   113,    -1,    -1,    -1,   117,    -1,   115,    -1,
      -1,   122,   123,    -1,   125,   126,   127,   128,   129,   130,
     131,    -1,    -1,   134,   135,   136,    65,   138,    -1,    68,
      69,    -1,    -1,    -1,    -1,    -1,    75,    76,    77,    -1,
      79,    -1,    81,    82,    -1,    -1,    -1,    86,    -1,    -1,
      89,    90,    91,    92,    93,    94,    -1,    96,    97,    98,
      99,   100,    -1,    -1,    -1,   104,    -1,   106,    -1,    -1,
      -1,    -1,   111,   112,   113,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,   122,   123,    17,   125,   126,   127,   128,
     129,   130,   131,    -1,    -1,   134,   135,    -1,    30,    -1,
      32,    33,    34,    35,    36,    37,    38,    39,    40,    41,
      42,    43,    44,    45,    46,    47,    48,    49,    30,    -1,
      32,    33,    34,    35,    36,    37,    38,    39,    40,    41,
      42,    43,    44,    45,    46,    47,    48,    49,    -1,    -1,
      -1,    -1,    -1,    30,    56,    32,    33,    34,    35,    36,
      37,    38,    39,    40,    41,    42,    43,    44,    45,    46,
      47,    48,    49,    -1,    -1,    -1,    -1,    -1,    30,    56,
      32,    33,    34,    35,    36,    37,    38,    39,    40,    41,
      42,    43,    44,    45,    46,    47,    48,    49,    -1,    -1,
      -1,    -1,    -1,    30,    56,    32,    33,    34,    35,    36,
      37,    38,    39,    40,    41,    42,    43,    44,    45,    46,
      47,    48,    49,    -1,    -1,    -1,    -1,    -1,    30,    56,
      32,    33,    34,    35,    36,    37,    38,    39,    40,    41,
      42,    43,    44,    45,    46,    47,    48,    49,    -1,    -1,
      -1,    -1,    54,    30,    31,    32,    33,    34,    35,    36,
      37,    38,    39,    40,    41,    42,    43,    44,    45,    46,
      47,    48,    49,    30,    31,    32,    33,    34,    35,    36,
      37,    38,    39,    40,    41,    42,    43,    44,    45,    46,
      47,    48,    49,    30,    -1,    32,    33,    34,    35,    36,
      37,    38,    39,    40,    41,    42,    43,    44,    45,    46,
      47,    48,    49,    33,    34,    35,    36,    37,    38,    39,
      40,    41,    42,    43,    44,    45,    46,    47,    48,    49,
      35,    36,    37,    38,    39,    40,    41,    42,    43,    44,
      45,    46,    47,    48,    49,    36,    37,    38,    39,    40,
      41,    42,    43,    44,    45,    46,    47,    48,    49,    37,
      38,    39,    40,    41,    42,    43,    44,    45,    46,    47,
      48,    49
};

  /* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
     symbol of state STATE-NUM.  */
static const yytype_uint8 yystos[] =
{
       0,    65,    68,    69,    70,    71,    75,    76,    77,    79,
      80,    81,    82,    84,    86,    89,    90,    91,    92,    93,
      94,    95,    96,    97,    98,    99,   100,   101,   102,   104,
     105,   106,   107,   108,   111,   112,   113,   117,   122,   123,
     125,   126,   127,   128,   129,   130,   131,   134,   135,   136,
     138,   140,   141,   142,   143,   147,   148,   149,   150,   151,
     152,   193,   194,     0,   141,     3,   149,    47,    55,   145,
     146,   147,    16,    56,     3,   146,    17,    54,   144,     3,
       4,     5,     6,     7,     8,     9,    10,    11,    12,    13,
      36,    45,    46,    47,    51,    52,    54,    55,    62,    63,
      66,    72,    74,    83,    85,    87,   110,   115,   119,   137,
     142,   143,   147,   153,   154,   156,   157,   162,   163,   164,
     165,   166,   170,   172,   174,   175,   180,   183,   186,   187,
     188,   189,   192,    31,    55,     3,    55,   154,     3,   187,
     187,   154,   187,   187,   153,   154,   187,   193,   154,   154,
      17,    17,   181,    55,     3,    55,   187,    55,   187,    55,
       3,   161,    53,    19,    20,    21,    22,    23,    24,    25,
      26,    27,    28,    29,    57,    60,    62,    63,   155,   153,
      88,   163,    17,    30,    32,    33,    34,    35,    36,    37,
      38,    39,    40,    41,    42,    43,    44,    45,    46,    47,
      48,    49,    54,    56,   155,   158,   159,   187,   154,    53,
      56,    56,    56,   163,   147,   162,   186,    17,   187,    17,
     193,    54,   185,    19,   155,   160,    16,    17,   187,   187,
     187,   187,   187,   187,   187,   187,   187,   187,   187,   187,
       3,    57,   171,   187,   187,   187,   187,   187,   187,   187,
     187,   187,   187,   187,   187,   187,   187,   187,   187,   187,
     187,   187,   158,    19,    16,    56,    55,   187,   137,     3,
     178,    17,    56,    56,    67,    73,   167,   168,   169,   187,
     159,   187,   160,     3,    58,   187,   163,    31,    53,   187,
     155,   159,   187,   187,   190,   191,    55,   186,   176,   173,
     187,    31,    53,   168,   169,    56,   155,   160,    58,   187,
      19,    16,    16,    56,   182,    17,   186,   163,    31,   153,
     184,   160,   187,   187,   187,   187,   179,    17,   153,   163,
      56,   186,   177,    17,    56,   186,    56
};

  /* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const yytype_uint8 yyr1[] =
{
       0,   139,   140,   140,   141,   141,   142,   144,   143,   145,
     145,   145,   146,   146,   147,   147,   148,   148,   148,   148,
     149,   149,   149,   149,   149,   149,   149,   150,   150,   151,
     151,   151,   152,   152,   153,   153,   154,   154,   154,   154,
     154,   155,   155,   156,   156,   156,   156,   156,   156,   156,
     156,   156,   156,   156,   156,   156,   156,   157,   157,   158,
     158,   158,   158,   158,   158,   159,   160,   160,   160,   161,
     161,   161,   161,   162,   163,   163,   164,   165,   166,   167,
     167,   167,   167,   168,   169,   170,   171,   170,   173,   172,
     174,   176,   177,   175,   178,   179,   175,   181,   182,   180,
     184,   183,   185,   186,   186,   187,   187,   187,   187,   187,
     187,   187,   187,   187,   187,   187,   187,   187,   187,   187,
     187,   187,   187,   187,   187,   187,   187,   187,   187,   187,
     187,   187,   187,   187,   187,   187,   187,   187,   187,   187,
     188,   188,   188,   188,   188,   188,   188,   188,   188,   188,
     189,   190,   191,   191,   192,   192,   192,   192,   192,   192,
     192,   192,   192,   192,   192,   192,   193,   193,   194,   194,
     194,   194,   194,   194,   194,   194,   194,   194,   194,   194,
     194,   194,   194,   194,   194,   194,   194,   194,   194,   194,
     194,   194,   194,   194,   194,   194,   194,   194,   194,   194,
     194,   194,   194,   194,   194
};

  /* YYR2[YYN] -- Number of symbols on the right hand side of rule YYN.  */
static const yytype_uint8 yyr2[] =
{
       0,     2,     1,     2,     1,     1,     6,     0,     9,     0,
       1,     3,     2,     1,     1,     2,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     0,     2,     3,     2,     2,     1,
       3,     3,     4,     2,     1,     1,     1,     1,     1,     1,
       1,     3,     2,     2,     1,     1,     1,     4,     3,     1,
       3,     1,     3,     3,     5,     3,     0,     2,     2,     2,
       4,     3,     5,     3,     1,     3,     2,     3,     5,     1,
       1,     2,     2,     3,     4,     1,     0,     4,     0,     6,
       2,     0,     0,    10,     0,     0,     9,     0,     0,     9,
       0,     7,     0,     0,     1,     1,     3,     3,     3,     3,
       3,     3,     3,     3,     3,     3,     3,     3,     3,     3,
       3,     3,     3,     3,     3,     3,     3,     3,     3,     3,
       3,     3,     3,     5,     1,     1,     2,     3,     3,     3,
       2,     2,     2,     2,     2,     2,     4,     4,     2,     2,
       6,     3,     1,     3,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     2,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1
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
      yyerror (YY_("syntax error: cannot back up")); \
      YYERROR;                                                  \
    }                                                           \
while (0)

/* Error token number */
#define YYTERROR        1
#define YYERRCODE       256



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

/* This macro is provided for backward compatibility. */
#ifndef YY_LOCATION_PRINT
# define YY_LOCATION_PRINT(File, Loc) ((void) 0)
#endif


# define YY_SYMBOL_PRINT(Title, Type, Value, Location)                    \
do {                                                                      \
  if (yydebug)                                                            \
    {                                                                     \
      YYFPRINTF (stderr, "%s ", Title);                                   \
      yy_symbol_print (stderr,                                            \
                  Type, Value); \
      YYFPRINTF (stderr, "\n");                                           \
    }                                                                     \
} while (0)


/*----------------------------------------.
| Print this symbol's value on YYOUTPUT.  |
`----------------------------------------*/

static void
yy_symbol_value_print (FILE *yyoutput, int yytype, YYSTYPE const * const yyvaluep)
{
  FILE *yyo = yyoutput;
  YYUSE (yyo);
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
yy_symbol_print (FILE *yyoutput, int yytype, YYSTYPE const * const yyvaluep)
{
  YYFPRINTF (yyoutput, "%s %s (",
             yytype < YYNTOKENS ? "token" : "nterm", yytname[yytype]);

  yy_symbol_value_print (yyoutput, yytype, yyvaluep);
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
yy_reduce_print (yytype_int16 *yyssp, YYSTYPE *yyvsp, int yyrule)
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
                                              );
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
yydestruct (const char *yymsg, int yytype, YYSTYPE *yyvaluep)
{
  YYUSE (yyvaluep);
  if (!yymsg)
    yymsg = "Deleting";
  YY_SYMBOL_PRINT (yymsg, yytype, yyvaluep, yylocationp);

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  YYUSE (yytype);
  YY_IGNORE_MAYBE_UNINITIALIZED_END
}




/* The lookahead symbol.  */
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
    int yystate;
    /* Number of tokens to shift before error messages enabled.  */
    int yyerrstatus;

    /* The stacks and their tools:
       'yyss': related to states.
       'yyvs': related to semantic values.

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

    YYSIZE_T yystacksize;

  int yyn;
  int yyresult;
  /* Lookahead token as an internal (translated) token number.  */
  int yytoken = 0;
  /* The variables used to return semantic value and location from the
     action routines.  */
  YYSTYPE yyval;

#if YYERROR_VERBOSE
  /* Buffer for error messages, and its allocated size.  */
  char yymsgbuf[128];
  char *yymsg = yymsgbuf;
  YYSIZE_T yymsg_alloc = sizeof yymsgbuf;
#endif

#define YYPOPSTACK(N)   (yyvsp -= (N), yyssp -= (N))

  /* The number of symbols on the RHS of the reduced rule.
     Keep to zero when no symbol should be popped.  */
  int yylen = 0;

  yyssp = yyss = yyssa;
  yyvsp = yyvs = yyvsa;
  yystacksize = YYINITDEPTH;

  YYDPRINTF ((stderr, "Starting parse\n"));

  yystate = 0;
  yyerrstatus = 0;
  yynerrs = 0;
  yychar = YYEMPTY; /* Cause a token to be read.  */
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

        /* Each stack pointer address is followed by the size of the
           data in use in that stack, in bytes.  This used to be a
           conditional around just the two extra args, but that might
           be undefined if yyoverflow is a macro.  */
        yyoverflow (YY_("memory exhausted"),
                    &yyss1, yysize * sizeof (*yyssp),
                    &yyvs1, yysize * sizeof (*yyvsp),
                    &yystacksize);

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
#  undef YYSTACK_RELOCATE
        if (yyss1 != yyssa)
          YYSTACK_FREE (yyss1);
      }
# endif
#endif /* no yyoverflow */

      yyssp = yyss + yysize - 1;
      yyvsp = yyvs + yysize - 1;

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
      yychar = yylex ();
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


  YY_REDUCE_PRINT (yyn);
  switch (yyn)
    {
        case 6:
#line 233 "parser.y" /* yacc.c:1646  */
    {
		
		cl2llvm_yyerror("function declarations not supported");
	}
#line 2139 "parser.c" /* yacc.c:1646  */
    break;

  case 7:
#line 241 "parser.y" /* yacc.c:1646  */
    {
		int err;
		struct cl2llvm_function_t *new_function;	
		char arg_name[CL2LLVM_MAX_ARG_NAME_LEN];
		LLVMTypeRef func_args[CL2LLVM_MAX_FUNC_ARGS];
		LLVMTypeRef function_type;
		LLVMValueRef function;
		int arg_count;
		int i;

		/* Create name for function entry block */
		snprintf(block_name, sizeof block_name,
			"block_%d", block_count++);
		
		arg_count = list_count((yyvsp[-2].arg_list));

		/* Check that first argument is not empty.  This step is 
		necessary because of the grammar definition which allows 
		for the first argument of a multi-argument function to be empty. */
		if (list_get((yyvsp[-2].arg_list), (yyvsp[-2].arg_list)->head) == NULL && arg_count > 1)
				yyerror("expected declaration specifiers or" 
					"'...' before ',' token");
		
		/* Read function arguments and create an array of argument types */
		else if(list_get((yyvsp[-2].arg_list), (yyvsp[-2].arg_list)->head))
		{
			for (i = 0; i < arg_count; i++)
			{
				
				struct cl2llvm_arg_t *current_arg = list_get(
					(yyvsp[-2].arg_list), i);
				if (!current_arg->name)
					yyerror("parameter name omitted");
				func_args[i] = current_arg->type_spec->llvm_type;
			}
		}
		else 
			arg_count = 0;

		/* Define function */
		function_type = LLVMFunctionType(
			(yyvsp[-5].decl_list)->type_spec->llvm_type, func_args, arg_count, 0);
		function = LLVMAddFunction(cl2llvm_module, (yyvsp[-4].identifier),
			function_type);
		LLVMSetFunctionCallConv(function, LLVMCCallConv);

		/* Create function's variable declaration block */
		LLVMBasicBlockRef basic_block = LLVMAppendBasicBlock( 
			function, block_name);
		
		/* Position builder at start of function */
		LLVMPositionBuilderAtEnd(cl2llvm_builder, basic_block);
			current_basic_block = basic_block;

		/* Create and initialize function object */
		new_function = cl2llvm_function_create((yyvsp[-4].identifier), (yyvsp[-2].arg_list));

		new_function->func = function;
		new_function->func_type = function_type;
		new_function->sign = (yyvsp[-5].decl_list)->type_spec->sign;
		new_function->entry_block = basic_block;

		/* Set current function to newly created function */
		cl2llvm_current_function = new_function;

		/* Insert function into global symbol table */
		err = hash_table_insert(cl2llvm_symbol_table, 
			(yyvsp[-4].identifier), new_function);
		if (!err)
			yyerror("function already defined");
	
		/* Declare parameters if the argument list is not empty*/
		if (list_get((yyvsp[-2].arg_list), (yyvsp[-2].arg_list)->head))
		{
			for (i = 0; i < arg_count; i++)
			{
				struct cl2llvm_arg_t *current_arg = list_get(
					(yyvsp[-2].arg_list), i);

				snprintf(arg_name, sizeof arg_name,
					"%s_addr", current_arg->name);

				struct cl2llvm_val_t *arg_pointer = 
					cl2llvm_val_create_w_init( 
					LLVMBuildAlloca(cl2llvm_builder, 
					current_arg->type_spec->llvm_type, 
					arg_name),
					current_arg->type_spec->sign);

				struct cl2llvm_symbol_t *symbol = 
					cl2llvm_symbol_create_w_init(
					arg_pointer->val, 
					current_arg->type_spec->sign, 
					current_arg->name);

				symbol->cl2llvm_val->type->llvm_type = 
					current_arg->type_spec->llvm_type;

				/* Name and store arguments */
				LLVMValueRef arg_val = LLVMGetParam(
					new_function->func, i);
				LLVMSetValueName(arg_val, current_arg->name);

				LLVMBuildStore(cl2llvm_builder, arg_val,
					arg_pointer->val);
				hash_table_insert(new_function->symbol_table,
					current_arg->name, symbol);

				/* Free argument */
				cl2llvm_val_free(arg_pointer);
			}
		}
		/* End declaration block and create first instruction block. */
		snprintf(block_name, sizeof block_name,
			"block_%d", block_count++);

		LLVMBasicBlockRef first_block = LLVMAppendBasicBlock( 
			new_function->func, block_name);
		LLVMValueRef branch = LLVMBuildBr(cl2llvm_builder, 
			first_block);
		LLVMPositionBuilderAtEnd(cl2llvm_builder, first_block);

		/* Set current basic block */
		current_basic_block = first_block;

		/* initialize function branch instruction for building 
		declarations off of */
		new_function->branch_instr = branch;

		/* Free declarator list */
		cl2llvm_decl_list_free((yyvsp[-5].decl_list));	
	}
#line 2276 "parser.c" /* yacc.c:1646  */
    break;

  case 8:
#line 374 "parser.y" /* yacc.c:1646  */
    {
		/* If function is of type void, create return instruction 
		by default*/
		if (LLVMGetReturnType(cl2llvm_current_function->func_type)
			== LLVMVoidType())
			LLVMBuildRetVoid(cl2llvm_builder);
	}
#line 2288 "parser.c" /* yacc.c:1646  */
    break;

  case 9:
#line 387 "parser.y" /* yacc.c:1646  */
    {
		struct cl2llvm_arg_t *empty_arg = NULL;
		struct list_t *arg_list = list_create();
		list_add(arg_list, empty_arg);
		(yyval.arg_list) = arg_list;
	}
#line 2299 "parser.c" /* yacc.c:1646  */
    break;

  case 10:
#line 394 "parser.y" /* yacc.c:1646  */
    {
		struct list_t *arg_list = list_create();
		list_add(arg_list, (yyvsp[0].arg_t));
		(yyval.arg_list) = arg_list;
	}
#line 2309 "parser.c" /* yacc.c:1646  */
    break;

  case 11:
#line 400 "parser.y" /* yacc.c:1646  */
    {
		list_add((yyvsp[-2].arg_list), (yyvsp[0].arg_t));
		(yyval.arg_list) = (yyvsp[-2].arg_list);
	}
#line 2318 "parser.c" /* yacc.c:1646  */
    break;

  case 12:
#line 408 "parser.y" /* yacc.c:1646  */
    {
		struct cl2llvm_arg_t *arg = cl2llvm_arg_create((yyvsp[-1].decl_list), (yyvsp[0].identifier));
		cl2llvm_decl_list_struct_free((yyvsp[-1].decl_list));
		(yyval.arg_t) = arg;
	}
#line 2328 "parser.c" /* yacc.c:1646  */
    break;

  case 13:
#line 414 "parser.y" /* yacc.c:1646  */
    {
		struct cl2llvm_arg_t *arg = cl2llvm_arg_create((yyvsp[0].decl_list), NULL);
		cl2llvm_decl_list_struct_free((yyvsp[0].decl_list));
		(yyval.arg_t) = arg;
	}
#line 2338 "parser.c" /* yacc.c:1646  */
    break;

  case 14:
#line 425 "parser.y" /* yacc.c:1646  */
    {
		(yyval.decl_list) = (yyvsp[0].decl_list);
	}
#line 2346 "parser.c" /* yacc.c:1646  */
    break;

  case 15:
#line 429 "parser.y" /* yacc.c:1646  */
    {
		cl2llvm_attach_decl_to_list((yyvsp[0].decl_list), (yyvsp[-1].decl_list));
		if ((yyvsp[-1].decl_list)->type_spec != NULL && (yyvsp[0].decl_list)->addr_qual != 0)
		{
			switch ((yyvsp[0].decl_list)->addr_qual)
			{
				case 1:
					(yyvsp[-1].decl_list)->type_spec->llvm_type = LLVMPointerType( 
						LLVMGetElementType((yyvsp[-1].decl_list)->type_spec->llvm_type), 1);
					break;
					
				case 2:
					(yyvsp[-1].decl_list)->type_spec->llvm_type = LLVMPointerType(  
						LLVMGetElementType((yyvsp[-1].decl_list)->type_spec->llvm_type), 2);
						break;

				default:
					break;
			}
		}
		if ((yyvsp[-1].decl_list)->addr_qual != 0 && (yyvsp[0].decl_list)->type_spec != NULL)
		{
			switch ((yyvsp[-1].decl_list)->addr_qual)
			{
				case 1:
					(yyvsp[-1].decl_list)->type_spec->llvm_type = LLVMPointerType( 
						LLVMGetElementType((yyvsp[0].decl_list)->type_spec->llvm_type), 1);
						break;
					
				case 2:
					(yyvsp[-1].decl_list)->type_spec->llvm_type = LLVMPointerType( 	
						LLVMGetElementType((yyvsp[0].decl_list)->type_spec->llvm_type), 2);
						break;

				default:
					break;
			}
		}
		cl2llvm_decl_list_struct_free((yyvsp[0].decl_list));
		(yyval.decl_list) = (yyvsp[-1].decl_list);
	}
#line 2392 "parser.c" /* yacc.c:1646  */
    break;

  case 16:
#line 474 "parser.y" /* yacc.c:1646  */
    {
		(yyval.const_int_val) = 1;
	}
#line 2400 "parser.c" /* yacc.c:1646  */
    break;

  case 17:
#line 478 "parser.y" /* yacc.c:1646  */
    {
		(yyval.const_int_val) = 2;
	}
#line 2408 "parser.c" /* yacc.c:1646  */
    break;

  case 18:
#line 482 "parser.y" /* yacc.c:1646  */
    {
		cl2llvm_yyerror("'private' not supported");
		(yyval.const_int_val) = 0;
	}
#line 2417 "parser.c" /* yacc.c:1646  */
    break;

  case 19:
#line 487 "parser.y" /* yacc.c:1646  */
    {
		cl2llvm_yyerror("'constant' not supported");
		(yyval.const_int_val) = 0;
	}
#line 2426 "parser.c" /* yacc.c:1646  */
    break;

  case 20:
#line 495 "parser.y" /* yacc.c:1646  */
    {
		struct cl2llvm_decl_list_t *decl_list = cl2llvm_decl_list_create();
		decl_list->type_spec = (yyvsp[0].llvm_type_ref);
		(yyval.decl_list) = decl_list;
	}
#line 2436 "parser.c" /* yacc.c:1646  */
    break;

  case 21:
#line 501 "parser.y" /* yacc.c:1646  */
    {
		struct cl2llvm_decl_list_t *decl_list = cl2llvm_decl_list_create();
		decl_list->access_qual = NULL;
		(yyval.decl_list) = decl_list;
	}
#line 2446 "parser.c" /* yacc.c:1646  */
    break;

  case 22:
#line 507 "parser.y" /* yacc.c:1646  */
    {
		struct cl2llvm_decl_list_t *decl_list = cl2llvm_decl_list_create();
		decl_list->kernel_t = 	"kernel";
		(yyval.decl_list) = decl_list;
	}
#line 2456 "parser.c" /* yacc.c:1646  */
    break;

  case 23:
#line 513 "parser.y" /* yacc.c:1646  */
    {
		struct cl2llvm_decl_list_t *decl_list = cl2llvm_decl_list_create();
		decl_list->inline_t = NULL;
		(yyval.decl_list) = decl_list;
	}
#line 2466 "parser.c" /* yacc.c:1646  */
    break;

  case 24:
#line 519 "parser.y" /* yacc.c:1646  */
    {
		struct cl2llvm_decl_list_t *decl_list = cl2llvm_decl_list_create();
		decl_list->sc_spec = NULL;
		(yyval.decl_list) = decl_list;

	}
#line 2477 "parser.c" /* yacc.c:1646  */
    break;

  case 25:
#line 526 "parser.y" /* yacc.c:1646  */
    {
		struct cl2llvm_decl_list_t *decl_list = cl2llvm_decl_list_create();
		decl_list->addr_qual = (yyvsp[0].const_int_val);
		(yyval.decl_list) = decl_list;
	}
#line 2487 "parser.c" /* yacc.c:1646  */
    break;

  case 26:
#line 532 "parser.y" /* yacc.c:1646  */
    {
		struct cl2llvm_decl_list_t *decl_list = cl2llvm_decl_list_create();
		decl_list->type_qual = NULL;
		(yyval.decl_list) = decl_list;
	}
#line 2497 "parser.c" /* yacc.c:1646  */
    break;

  case 32:
#line 553 "parser.y" /* yacc.c:1646  */
    {
		cl2llvm_yyerror("'extern' not supported");
	}
#line 2505 "parser.c" /* yacc.c:1646  */
    break;

  case 33:
#line 557 "parser.y" /* yacc.c:1646  */
    {
		cl2llvm_yyerror("'static' not supported");
	}
#line 2513 "parser.c" /* yacc.c:1646  */
    break;

  case 36:
#line 569 "parser.y" /* yacc.c:1646  */
    {
		(yyval.llvm_value_ref) = (yyvsp[-1].llvm_value_ref);
	}
#line 2521 "parser.c" /* yacc.c:1646  */
    break;

  case 37:
#line 573 "parser.y" /* yacc.c:1646  */
    {
		struct cl2llvm_val_t *ptr;
		int i;
		struct cl2llvm_val_t *current_index;
		LLVMValueRef deref_ptr;
		LLVMValueRef indices[CL2LLVM_MAX_NUM_ARRAY_INDEX_DIM];

		/*Retrieve symbol from table*/
	 	/*symbol = hash_table_get(cl2llvm_current_function->symbol_table, $1);
		if (symbol == NULL)	
			yyerror("symbol undeclared first use in this program");*/
		
		deref_ptr = (yyvsp[-1].llvm_value_ref)->val;

		/* Loop through all dereference operators */	
		for (i = 0; i < list_count((yyvsp[0].list_val_t)); i++)
		{
			if  (LLVMGetTypeKind(LLVMGetElementType(LLVMTypeOf(
				deref_ptr))) == LLVMPointerTypeKind)
			{
				snprintf(temp_var_name, sizeof temp_var_name,
					"tmp_%d", temp_var_count++);
			
				deref_ptr = LLVMBuildLoad(cl2llvm_builder, 
					deref_ptr, temp_var_name);

				current_index = list_get((yyvsp[0].list_val_t), i);
				indices[0] = current_index->val;

				snprintf(temp_var_name, sizeof temp_var_name,
					"tmp_%d", temp_var_count++);
				deref_ptr = LLVMBuildGEP(cl2llvm_builder, 
					deref_ptr, indices, 1, 
					temp_var_name);
				
			}
			else if (LLVMGetTypeKind(LLVMGetElementType(LLVMTypeOf(
				deref_ptr))) == LLVMArrayTypeKind)

			{
				indices[0] = LLVMConstInt(LLVMInt32Type(), 0, 0);
				indices[1] = LLVMConstInt(LLVMInt32Type(), 0, 0);
				
				snprintf(temp_var_name, sizeof temp_var_name,
					"tmp_%d", temp_var_count++);
				
				deref_ptr = LLVMBuildGEP(cl2llvm_builder, 
					deref_ptr, indices, 2, temp_var_name); 

				current_index = list_get((yyvsp[0].list_val_t), i);
				indices[0] = current_index->val;
				

				/* Get element pointer */
				snprintf(temp_var_name, sizeof temp_var_name,
					"tmp_%d", temp_var_count++);

				deref_ptr = LLVMBuildGEP(cl2llvm_builder, 
					deref_ptr, indices, 1, temp_var_name);
			}
			else
				cl2llvm_yyerror("Subscripted value is neither array nor pointer");
		}

		ptr = cl2llvm_val_create_w_init(deref_ptr, 
			(yyvsp[-1].llvm_value_ref)->type->sign);

		/*Free pointers*/
		LIST_FOR_EACH((yyvsp[0].list_val_t), i)
		{
			cl2llvm_val_free(list_get((yyvsp[0].list_val_t), i));
		}
		list_free((yyvsp[0].list_val_t));
		cl2llvm_val_free((yyvsp[-1].llvm_value_ref));

		(yyval.llvm_value_ref) = ptr;
	}
#line 2603 "parser.c" /* yacc.c:1646  */
    break;

  case 38:
#line 651 "parser.y" /* yacc.c:1646  */
    {
		struct cl2llvm_val_t *ptr;
		LLVMValueRef deref_ptr;
		LLVMValueRef indices[CL2LLVM_MAX_NUM_ARRAY_INDEX_DIM];

		deref_ptr = (yyvsp[0].llvm_value_ref)->val;

		if  (LLVMGetTypeKind(LLVMGetElementType(LLVMTypeOf(
			deref_ptr))) == LLVMPointerTypeKind)
		{
			snprintf(temp_var_name, sizeof temp_var_name,
				"tmp_%d", temp_var_count++);
			
			deref_ptr = LLVMBuildLoad(cl2llvm_builder, 
				deref_ptr, temp_var_name);

		}
		else if (LLVMGetTypeKind(LLVMGetElementType(LLVMTypeOf(
			deref_ptr))) == LLVMArrayTypeKind)

		{
			indices[0] = LLVMConstInt(LLVMInt32Type(), 0, 0);
			indices[1] = LLVMConstInt(LLVMInt32Type(), 0, 0);
				
			snprintf(temp_var_name, sizeof temp_var_name,
				"tmp_%d", temp_var_count++);
				
			deref_ptr = LLVMBuildGEP(cl2llvm_builder, 
				deref_ptr, indices, 2, temp_var_name); 

			indices[0] = LLVMConstInt(LLVMInt32Type(), 0, 0);
				
			/* Get element pointer */
			snprintf(temp_var_name, sizeof temp_var_name,
				"tmp_%d", temp_var_count++);

			deref_ptr = LLVMBuildGEP(cl2llvm_builder, 
				deref_ptr, indices, 1, temp_var_name);
		}
		else
			cl2llvm_yyerror("Invalid type argument of unary '*'.");
		

		ptr = cl2llvm_val_create_w_init(deref_ptr, 
			(yyvsp[0].llvm_value_ref)->type->sign);

		cl2llvm_val_free((yyvsp[0].llvm_value_ref));

		(yyval.llvm_value_ref) = ptr;
	}
#line 2658 "parser.c" /* yacc.c:1646  */
    break;

  case 39:
#line 702 "parser.y" /* yacc.c:1646  */
    {
		struct cl2llvm_symbol_t *symbol;
		struct cl2llvm_val_t *symbol_val_dup;

		/* Access symbol from symbol table */
		symbol = hash_table_get(cl2llvm_current_function->symbol_table, (yyvsp[0].identifier));
		if (!symbol)
			yyerror("undefined identifier");

		/*Duplicate symbol*/
		symbol_val_dup = cl2llvm_val_create_w_init(symbol->cl2llvm_val->val, 
			symbol->cl2llvm_val->type->sign);


		(yyval.llvm_value_ref) = symbol_val_dup;
	}
#line 2679 "parser.c" /* yacc.c:1646  */
    break;

  case 40:
#line 719 "parser.y" /* yacc.c:1646  */
    {

		
		/* Get symbol from hash table */
	/*	symbol = hash_table_get(cl2llvm_current_function->symbol_table, $1);
		if (!symbol)	
			yyerror("symbol undeclared first use in this program");
*/

		/* If symbol is a vector retrieve the specified indices */
		if (LLVMGetTypeKind(LLVMGetElementType((yyvsp[-2].llvm_value_ref)->type->llvm_type))
			== LLVMVectorTypeKind)
		{	
			cl2llvm_get_vector_indices((yyvsp[-2].llvm_value_ref), (yyvsp[0].identifier));
		}
		(yyval.llvm_value_ref) = (yyvsp[-2].llvm_value_ref);
	}
#line 2701 "parser.c" /* yacc.c:1646  */
    break;

  case 41:
#line 740 "parser.y" /* yacc.c:1646  */
    {
		struct list_t *array_deref_list = list_create();
		
		if (LLVMGetTypeKind((yyvsp[-1].llvm_value_ref)->type->llvm_type) != LLVMIntegerTypeKind)
			yyerror("array index is not an integer");
		list_add(array_deref_list, (yyvsp[-1].llvm_value_ref));
		(yyval.list_val_t) = array_deref_list;
	}
#line 2714 "parser.c" /* yacc.c:1646  */
    break;

  case 42:
#line 749 "parser.y" /* yacc.c:1646  */
    {
		if (LLVMGetTypeKind((yyvsp[-1].llvm_value_ref)->type->llvm_type) != LLVMIntegerTypeKind)
			yyerror("array index is not an integer");
		list_add((yyvsp[-3].list_val_t), (yyvsp[-1].llvm_value_ref));
		(yyval.list_val_t) = (yyvsp[-3].list_val_t);
	}
#line 2725 "parser.c" /* yacc.c:1646  */
    break;

  case 43:
#line 759 "parser.y" /* yacc.c:1646  */
    {
		if ((yyvsp[-1].llvm_value_ref) != NULL)
			cl2llvm_val_free((yyvsp[-1].llvm_value_ref));
	}
#line 2734 "parser.c" /* yacc.c:1646  */
    break;

  case 51:
#line 771 "parser.y" /* yacc.c:1646  */
    {
		struct cl2llvm_val_t *ret_val;
		struct cl2llvm_type_t *type = cl2llvm_type_create_w_init( LLVMGetReturnType(cl2llvm_current_function->func_type), cl2llvm_current_function->sign);
		if (type->llvm_type != (yyvsp[-1].llvm_value_ref)->type->llvm_type || type->sign != (yyvsp[-1].llvm_value_ref)->type->sign)
			ret_val = llvm_type_cast((yyvsp[-1].llvm_value_ref), type);
		else
			ret_val = (yyvsp[-1].llvm_value_ref);
		LLVMBuildRet(cl2llvm_builder, ret_val->val);
		cl2llvm_type_free(type);
		if (ret_val != (yyvsp[-1].llvm_value_ref))
			cl2llvm_val_free(ret_val);
		cl2llvm_val_free((yyvsp[-1].llvm_value_ref));
	}
#line 2752 "parser.c" /* yacc.c:1646  */
    break;

  case 52:
#line 785 "parser.y" /* yacc.c:1646  */
    {
		cl2llvm_yyerror("'continue' not supported");
	}
#line 2760 "parser.c" /* yacc.c:1646  */
    break;

  case 53:
#line 789 "parser.y" /* yacc.c:1646  */
    {
		cl2llvm_yyerror("'break' not supported");
	}
#line 2768 "parser.c" /* yacc.c:1646  */
    break;

  case 54:
#line 793 "parser.y" /* yacc.c:1646  */
    {
		cl2llvm_yyerror("'switch' not supported");
	}
#line 2776 "parser.c" /* yacc.c:1646  */
    break;

  case 55:
#line 797 "parser.y" /* yacc.c:1646  */
    {
		cl2llvm_yyerror("'label statements not supported");
	}
#line 2784 "parser.c" /* yacc.c:1646  */
    break;

  case 56:
#line 801 "parser.y" /* yacc.c:1646  */
    {
		cl2llvm_yyerror("'goto' not supported");
	}
#line 2792 "parser.c" /* yacc.c:1646  */
    break;

  case 57:
#line 808 "parser.y" /* yacc.c:1646  */
    {
		int *func_id;
		int i;
		LLVMValueRef cast_param_array[100];
		struct cl2llvm_arg_t *current_func_arg;
		struct cl2llvm_val_t *current_param;
		struct cl2llvm_function_t *function;
		struct cl2llvm_type_t *type;
		struct cl2llvm_val_t *cast_param;
		LLVMValueRef llvm_val_func_ret;
		struct cl2llvm_val_t *ret_val;
		LLVMTypeRef llvm_param_types[100];
		int offset = 0;

		/* If function is found in the built-in function table but not the
		   global symbol table, declare it and insert it into the  global
		   symbol table. */
		func_id = hash_table_get(cl2llvm_built_in_func_table, (yyvsp[-3].identifier));
		if (func_id && !hash_table_get(cl2llvm_symbol_table, (yyvsp[-3].identifier)))
			func_declare(func_id);
	
		/* Retrieve function specs from sybmol table */
		function = hash_table_get(cl2llvm_symbol_table, (yyvsp[-3].identifier));
		if (!function)
			yyerror("implicit declaration of function");
		
		/* If specified function arg count differs from the arg count of
		   the generated function, get offset */
		if (function->arg_count != LLVMCountParamTypes(function->func_type))
		{
			LLVMGetParamTypes(function->func_type, llvm_param_types);

			offset = LLVMCountParamTypes(function->func_type) -
				function->arg_count;
			for (i = 0; i < offset; i++)
			{
				cast_param_array[i] = LLVMConstInt(llvm_param_types[i], 0, 0);
			}		
		}

		/* check that parameter types match */
		for (i = 0; i < function->arg_count; i++)
		{
			current_func_arg = list_get(function->arg_list, i);
			current_param = list_get((yyvsp[-1].list_val_t), i);
			if (current_func_arg->type_spec->llvm_type != current_param->type->llvm_type)
			{
				type = cl2llvm_type_create_w_init( 
					current_func_arg->type_spec->llvm_type,
					current_func_arg->type_spec->sign);
				cast_param = llvm_type_cast(current_param, type);
				cl2llvm_type_free(type);
				cast_param_array[i + offset] = cast_param->val;
				cl2llvm_val_free(current_param);
				cl2llvm_val_free(cast_param);
			}
			else
			{
				cast_param_array[i + offset] = current_param->val;
				cl2llvm_val_free(current_param);
			}
		}
		list_free((yyvsp[-1].list_val_t));


		/* Build function call */
		if (LLVMGetReturnType(function->func_type) == LLVMVoidType())
		{
			llvm_val_func_ret = LLVMBuildCall(cl2llvm_builder, function->func,
				cast_param_array, function->arg_count + offset, "");
		}
		else
		{
			snprintf(temp_var_name, sizeof temp_var_name,
				"tmp_%d", temp_var_count++);

			llvm_val_func_ret = LLVMBuildCall(cl2llvm_builder, function->func,
				cast_param_array, function->arg_count + offset, temp_var_name);
		}

		/* Create return value */
		ret_val = cl2llvm_val_create_w_init(llvm_val_func_ret, 	
			function->sign);
		
		(yyval.llvm_value_ref) = ret_val;
	}
#line 2883 "parser.c" /* yacc.c:1646  */
    break;

  case 58:
#line 895 "parser.y" /* yacc.c:1646  */
    {
		cl2llvm_yyerror("function calls with no parameters not supported");
		(yyval.llvm_value_ref) = NULL;
	}
#line 2892 "parser.c" /* yacc.c:1646  */
    break;

  case 59:
#line 903 "parser.y" /* yacc.c:1646  */
    {
		struct list_t *param_list = list_create();
		list_add(param_list, (yyvsp[0].llvm_value_ref));
		(yyval.list_val_t) = param_list;
	}
#line 2902 "parser.c" /* yacc.c:1646  */
    break;

  case 60:
#line 909 "parser.y" /* yacc.c:1646  */
    {
		cl2llvm_yyerror("array initializers not supported");
		(yyval.list_val_t) = NULL;
	}
#line 2911 "parser.c" /* yacc.c:1646  */
    break;

  case 61:
#line 914 "parser.y" /* yacc.c:1646  */
    {
		cl2llvm_yyerror("array initializers not supported");
		(yyval.list_val_t) = NULL;
	}
#line 2920 "parser.c" /* yacc.c:1646  */
    break;

  case 62:
#line 919 "parser.y" /* yacc.c:1646  */
    {
		list_add((yyvsp[-2].list_val_t), (yyvsp[0].llvm_value_ref));
		(yyval.list_val_t) = (yyvsp[-2].list_val_t);
	}
#line 2929 "parser.c" /* yacc.c:1646  */
    break;

  case 63:
#line 924 "parser.y" /* yacc.c:1646  */
    {
		cl2llvm_yyerror("array initializers not supported");
		(yyval.list_val_t) = NULL;
	}
#line 2938 "parser.c" /* yacc.c:1646  */
    break;

  case 64:
#line 929 "parser.y" /* yacc.c:1646  */
    {
		cl2llvm_yyerror("array initializers not supported");
		(yyval.list_val_t) = NULL;
	}
#line 2947 "parser.c" /* yacc.c:1646  */
    break;

  case 66:
#line 941 "parser.y" /* yacc.c:1646  */
    {
		(yyval.llvm_value_ref) = NULL;
	}
#line 2955 "parser.c" /* yacc.c:1646  */
    break;

  case 67:
#line 945 "parser.y" /* yacc.c:1646  */
    {
		(yyval.llvm_value_ref) = (yyvsp[0].llvm_value_ref);
	}
#line 2963 "parser.c" /* yacc.c:1646  */
    break;

  case 68:
#line 949 "parser.y" /* yacc.c:1646  */
    {
		cl2llvm_yyerror("array initializers not supported");
		(yyval.llvm_value_ref) = NULL;
	}
#line 2972 "parser.c" /* yacc.c:1646  */
    break;

  case 69:
#line 957 "parser.y" /* yacc.c:1646  */
    {
		struct list_t *init_list = list_create();
		struct cl2llvm_init_t *init = cl2llvm_init_create((yyvsp[-1].identifier));

		cl2llvm_val_free(init->cl2llvm_val);
		init->cl2llvm_val = (yyvsp[0].llvm_value_ref);

		list_add(init_list, init);
		(yyval.init_list) = init_list;
	}
#line 2987 "parser.c" /* yacc.c:1646  */
    break;

  case 70:
#line 968 "parser.y" /* yacc.c:1646  */
    {
		struct cl2llvm_init_t *init = cl2llvm_init_create((yyvsp[-1].identifier));

		cl2llvm_val_free(init->cl2llvm_val);
		init->cl2llvm_val = (yyvsp[0].llvm_value_ref);

		list_add((yyvsp[-3].init_list), init);
		(yyval.init_list) = (yyvsp[-3].init_list);
	}
#line 3001 "parser.c" /* yacc.c:1646  */
    break;

  case 71:
#line 978 "parser.y" /* yacc.c:1646  */
    {
		struct list_t *init_list = list_create();
		struct cl2llvm_init_t *init = cl2llvm_init_create((yyvsp[-2].identifier));

		cl2llvm_val_free(init->cl2llvm_val);
		init->cl2llvm_val = (yyvsp[0].llvm_value_ref);
		init->array_deref_list = (yyvsp[-1].list_val_t);

		list_add(init_list, init);
		(yyval.init_list) = init_list;

	}
#line 3018 "parser.c" /* yacc.c:1646  */
    break;

  case 72:
#line 991 "parser.y" /* yacc.c:1646  */
    {
		struct cl2llvm_init_t *init = cl2llvm_init_create((yyvsp[-2].identifier));

		cl2llvm_val_free(init->cl2llvm_val);
		init->cl2llvm_val = (yyvsp[0].llvm_value_ref);
		init->array_deref_list = (yyvsp[-1].list_val_t);

		list_add((yyvsp[-4].init_list), init);
		(yyval.init_list) = (yyvsp[-4].init_list);
	}
#line 3033 "parser.c" /* yacc.c:1646  */
    break;

  case 73:
#line 1006 "parser.y" /* yacc.c:1646  */
    {
		struct cl2llvm_val_t *cl2llvm_index;
		LLVMTypeRef type;
		struct cl2llvm_val_t *ptr;
		struct cl2llvm_val_t *value;
		int i;
		struct cl2llvm_symbol_t *symbol;
		struct cl2llvm_val_t *cast_to_val;
		int init_count = list_count((yyvsp[-1].init_list));
		struct cl2llvm_init_t *current_list_elem;
		struct cl2llvm_symbol_t *err_symbol;
		char error_message[50];
		LLVMValueRef var_addr;

		/*Create each sybmol in the init_list*/
		for(i = 0; i < init_count; i++)
		{	
			int err;			
			current_list_elem = list_get((yyvsp[-1].init_list), i);
			
			/*if variable type is a vector*/
			if (LLVMGetTypeKind((yyvsp[-2].decl_list)->type_spec->llvm_type) == LLVMVectorTypeKind)
			{	
				/*Go to entry block and declare variable*/
				LLVMPositionBuilder(cl2llvm_builder, cl2llvm_current_function->entry_block, cl2llvm_current_function->branch_instr);
				var_addr = LLVMBuildAlloca(cl2llvm_builder, 
					(yyvsp[-2].decl_list)->type_spec->llvm_type, current_list_elem->name);
				LLVMPositionBuilderAtEnd(cl2llvm_builder, current_basic_block);

				/*Create symbol*/
				symbol = cl2llvm_symbol_create_w_init( var_addr, 
					(yyvsp[-2].decl_list)->type_spec->sign, current_list_elem->name);
				
				/* If initializer is present, store it. */
				if (current_list_elem->cl2llvm_val != NULL)
				{

					if (LLVMTypeOf(current_list_elem->cl2llvm_val->val) == (yyvsp[-2].decl_list)->type_spec->llvm_type 
						&& current_list_elem->cl2llvm_val->type->sign == (yyvsp[-2].decl_list)->type_spec->sign)
					{
						LLVMBuildStore(cl2llvm_builder, 
							current_list_elem->cl2llvm_val->val, var_addr);
					}
					else 
					{
						yyerror("type of vector initializer does not match type of declarator");
					}
				}
			}
			/*If data type is not an array*/
			else if (current_list_elem->array_deref_list == NULL)
			{
				/*Go to entry block and declare variable*/
				LLVMPositionBuilder(cl2llvm_builder, cl2llvm_current_function->entry_block, cl2llvm_current_function->branch_instr);
				var_addr = LLVMBuildAlloca(cl2llvm_builder, 
					(yyvsp[-2].decl_list)->type_spec->llvm_type, current_list_elem->name);
				LLVMPositionBuilderAtEnd(cl2llvm_builder, current_basic_block);

				/*Create symbol*/
				symbol = cl2llvm_symbol_create_w_init( var_addr, 
					(yyvsp[-2].decl_list)->type_spec->sign, current_list_elem->name);
				symbol->cl2llvm_val->type->llvm_type = (yyvsp[-2].decl_list)->type_spec->llvm_type;

				
				/*If initializer is present, cast initializer to declarator 
				  type and store*/
				if (current_list_elem->cl2llvm_val != NULL)
				{
					cast_to_val = llvm_type_cast( 
						current_list_elem->cl2llvm_val, 
						(yyvsp[-2].decl_list)->type_spec);
					LLVMBuildStore(cl2llvm_builder, cast_to_val->val, 
						symbol->cl2llvm_val->val);
					cl2llvm_val_free(cast_to_val);
				}
			}
			/*If init is an array*/
			else
			{		
				int i;
				int j;
				
				/* Check that array sizes are constants */
				for (i = 0; i < list_count(
					current_list_elem->array_deref_list); i++)
				{	
					value = list_get(current_list_elem->array_deref_list, i);
					if (!LLVMIsConstant(value->val))
						cl2llvm_yyerror("Array size must be a constant.");
				}

				/* Create type for pointer to array. */
				type = (yyvsp[-2].decl_list)->type_spec->llvm_type;

				for (i = 0; i < list_count(
					current_list_elem->array_deref_list); i++)
				{
					cl2llvm_index = list_get(current_list_elem->array_deref_list, i);
					j = 0;
					while(LLVMConstInt(LLVMInt1Type() ,1 ,0) 
						== LLVMConstICmp(LLVMIntSLT, 
						LLVMConstInt(LLVMInt32Type(), j,
						0), cl2llvm_index->val))
					{
						j++;
					}

					type = LLVMArrayType(type, j);
				}

				/* Go to entry block and allocate array pointer */
				LLVMPositionBuilder(cl2llvm_builder,
					cl2llvm_current_function->entry_block,
					cl2llvm_current_function->branch_instr);

				ptr = cl2llvm_val_create_w_init( LLVMBuildAlloca( 
					cl2llvm_builder, type,
					current_list_elem->name), 
					(yyvsp[-2].decl_list)->type_spec->sign);
	
				LLVMPositionBuilderAtEnd(cl2llvm_builder,
					current_basic_block);


				
				/* Create symbol */
				symbol = cl2llvm_symbol_create_w_init( 
					ptr->val , (yyvsp[-2].decl_list)->type_spec->sign, 
					current_list_elem->name);

				
				cl2llvm_val_free(ptr);

			}
			/* Insert symbol into symbol table */
			err = hash_table_insert(cl2llvm_current_function->symbol_table, 
				current_list_elem->name, symbol);
			if (!err)
			{
				snprintf(error_message, sizeof error_message,
					"Symbol '%s' previously declared.", current_list_elem->name);

				cl2llvm_yyerror(error_message);
			}
			/* Check that symbol is not a reserved constant */
			err_symbol = hash_table_get(cl2llvm_built_in_const_table, 
				current_list_elem->name);
			if (err_symbol)
			{
				snprintf(error_message, sizeof error_message,
					"'%s' expected an identifier.", current_list_elem->name);
				cl2llvm_yyerror(error_message);
			}

		}

		/* Free pointers */
		cl2llvm_decl_list_free((yyvsp[-2].decl_list));
		LIST_FOR_EACH((yyvsp[-1].init_list), i)
		{
			cl2llvm_init_free(list_get((yyvsp[-1].init_list), i));
		}
		list_free((yyvsp[-1].init_list));
	}
#line 3202 "parser.c" /* yacc.c:1646  */
    break;

  case 85:
#line 1206 "parser.y" /* yacc.c:1646  */
    {
		/* goto endif block*/
		LLVMBuildBr(cl2llvm_builder, (yyvsp[0].basic_block_ref));
		LLVMPositionBuilderAtEnd(cl2llvm_builder, (yyvsp[0].basic_block_ref));
		current_basic_block = (yyvsp[0].basic_block_ref);
	}
#line 3213 "parser.c" /* yacc.c:1646  */
    break;

  case 86:
#line 1213 "parser.y" /* yacc.c:1646  */
    { 
		/*create endif block. $1 now becomes the if false block*/
		snprintf(block_name, sizeof block_name,
			"block_%d", block_count++);
		LLVMBasicBlockRef endif = LLVMAppendBasicBlock(cl2llvm_current_function->func, block_name);
		
		/*Branch to endif*/
		LLVMBuildBr(cl2llvm_builder, endif);
		/*position builder at if false block*/
		LLVMPositionBuilderAtEnd(cl2llvm_builder, (yyvsp[-1].basic_block_ref));
		current_basic_block = (yyvsp[-1].basic_block_ref);

		(yyval.basic_block_ref) = endif;
	}
#line 3232 "parser.c" /* yacc.c:1646  */
    break;

  case 87:
#line 1228 "parser.y" /* yacc.c:1646  */
    {
		/*branch to endif block and prepare to write code for endif block*/
		LLVMBuildBr(cl2llvm_builder, (yyvsp[-1].basic_block_ref));
		LLVMPositionBuilderAtEnd(cl2llvm_builder, (yyvsp[-1].basic_block_ref));
		current_basic_block = (yyvsp[-1].basic_block_ref);

	}
#line 3244 "parser.c" /* yacc.c:1646  */
    break;

  case 88:
#line 1239 "parser.y" /* yacc.c:1646  */
    {
		struct cl2llvm_type_t *i1 = cl2llvm_type_create_w_init(LLVMInt1Type(), 1);
		
		/*Create endif block*/
		snprintf(block_name, sizeof block_name,
			"block_%d", block_count++);
		LLVMBasicBlockRef endif = LLVMAppendBasicBlock(cl2llvm_current_function->func, block_name);
		
		/*Create if true block*/
		snprintf(block_name, sizeof block_name,
			"block_%d", block_count++);
		LLVMBasicBlockRef if_true = LLVMAppendBasicBlock(
			cl2llvm_current_function->func, block_name);
		
		/*evaluate expression*/
		if (LLVMGetTypeKind((yyvsp[-1].llvm_value_ref)->type->llvm_type) == LLVMVectorTypeKind)
			cl2llvm_yyerror("expression must have arithmetic, enum "
				"or pointer type");
		struct cl2llvm_val_t *bool_val =  cl2llvm_to_bool_ne_0((yyvsp[-1].llvm_value_ref));
		LLVMBuildCondBr(cl2llvm_builder, bool_val->val, if_true, endif);
		(yyval.basic_block_ref) = endif;
		
		/*prepare to write if_true block*/
		LLVMPositionBuilderAtEnd(cl2llvm_builder, if_true);
		current_basic_block = if_true;
	
		cl2llvm_val_free(bool_val);
		cl2llvm_val_free((yyvsp[-1].llvm_value_ref));
		cl2llvm_type_free(i1);
	}
#line 3279 "parser.c" /* yacc.c:1646  */
    break;

  case 89:
#line 1270 "parser.y" /* yacc.c:1646  */
    {
		(yyval.basic_block_ref) = (yyvsp[-1].basic_block_ref);
	}
#line 3287 "parser.c" /* yacc.c:1646  */
    break;

  case 90:
#line 1277 "parser.y" /* yacc.c:1646  */
    {
		/*Finish for loop statement*/
		LLVMBuildBr(cl2llvm_builder, (yyvsp[-1].llvm_for_blocks)->for_incr);

		/*Prepare to build for end*/
		LLVMPositionBuilderAtEnd(cl2llvm_builder, (yyvsp[-1].llvm_for_blocks)->for_end);
		current_basic_block = (yyvsp[-1].llvm_for_blocks)->for_end;

		/*Free for_blocks*/
		cl2llvm_for_blocks_free((yyvsp[-1].llvm_for_blocks));

	}
#line 3304 "parser.c" /* yacc.c:1646  */
    break;

  case 91:
#line 1293 "parser.y" /* yacc.c:1646  */
    {
		struct cl2llvm_for_blocks_t *for_blocks;
		
		/*Initialize "for" blocks*/
		for_blocks = cl2llvm_for_blocks_create();
		
		snprintf(block_name, sizeof block_name,
			"block_%d", block_count++);
		LLVMBasicBlockRef for_cond = LLVMAppendBasicBlock(cl2llvm_current_function->func,
			block_name);
		snprintf(block_name, sizeof block_name,
			"block_%d", block_count++);
		LLVMBasicBlockRef for_stmt = LLVMAppendBasicBlock(cl2llvm_current_function->func,
			block_name);
		snprintf(block_name, sizeof block_name,
			"block_%d", block_count++);
		LLVMBasicBlockRef for_incr = LLVMAppendBasicBlock(cl2llvm_current_function->func,
			block_name);
		snprintf(block_name, sizeof block_name,
			"block_%d", block_count++);
		LLVMBasicBlockRef for_end = LLVMAppendBasicBlock(cl2llvm_current_function->func, 
			block_name);

		for_blocks->for_cond = for_cond;
		for_blocks->for_stmt = for_stmt;
		for_blocks->for_incr = for_incr;
		for_blocks->for_end = for_end;

		/*Prepare to build for loop conditional*/
		LLVMBuildBr(cl2llvm_builder, for_blocks->for_cond);
		LLVMPositionBuilderAtEnd(cl2llvm_builder, for_blocks->for_cond);

		(yyval.llvm_for_blocks) = for_blocks;
	}
#line 3343 "parser.c" /* yacc.c:1646  */
    break;

  case 92:
#line 1328 "parser.y" /* yacc.c:1646  */
    {
		struct cl2llvm_val_t *bool_val = NULL;

		/*Build for loop conditional*/
		if ((yyvsp[-1].llvm_value_ref) != NULL)
		{
			if (LLVMGetTypeKind((yyvsp[-1].llvm_value_ref)->type->llvm_type)
				== LLVMVectorTypeKind)
				cl2llvm_yyerror("expression must have "
					"arithmetic, enum or pointer type");
			bool_val = cl2llvm_to_bool_ne_0((yyvsp[-1].llvm_value_ref));
			LLVMBuildCondBr(cl2llvm_builder, bool_val->val, 
				(yyvsp[-2].llvm_for_blocks)->for_stmt, (yyvsp[-2].llvm_for_blocks)->for_end);	
		}
		else
		{
			LLVMBuildBr(cl2llvm_builder, (yyvsp[-2].llvm_for_blocks)->for_stmt);
		}
		
		/*Prepare to build for loop increment*/
		LLVMPositionBuilderAtEnd(cl2llvm_builder, (yyvsp[-2].llvm_for_blocks)->for_incr);

			
		/*Free pointers*/
		if (bool_val != NULL)
			cl2llvm_val_free(bool_val);
		if ((yyvsp[-4].llvm_value_ref) != NULL)
			cl2llvm_val_free((yyvsp[-4].llvm_value_ref));
		if ((yyvsp[-1].llvm_value_ref) != NULL)
			cl2llvm_val_free((yyvsp[-1].llvm_value_ref));
	}
#line 3379 "parser.c" /* yacc.c:1646  */
    break;

  case 93:
#line 1360 "parser.y" /* yacc.c:1646  */
    {
		/*Finish for loop increment*/
		LLVMBuildBr(cl2llvm_builder, (yyvsp[-5].llvm_for_blocks)->for_cond);
			
		/*Prepare to build for loop statements*/
		LLVMPositionBuilderAtEnd(cl2llvm_builder, (yyvsp[-5].llvm_for_blocks)->for_stmt);
		current_basic_block = (yyvsp[-5].llvm_for_blocks)->for_stmt;

		/*Free pointers*/
		if ((yyvsp[-1].llvm_value_ref) != NULL)
			cl2llvm_val_free((yyvsp[-1].llvm_value_ref));

		(yyval.llvm_for_blocks) = (yyvsp[-5].llvm_for_blocks);
	}
#line 3398 "parser.c" /* yacc.c:1646  */
    break;

  case 94:
#line 1375 "parser.y" /* yacc.c:1646  */
    {
		struct cl2llvm_for_blocks_t *for_blocks;
		
		/*Initialize "for" blocks*/
		for_blocks = cl2llvm_for_blocks_create();
		
		snprintf(block_name, sizeof block_name,
			"block_%d", block_count++);
		LLVMBasicBlockRef for_cond = LLVMAppendBasicBlock(cl2llvm_current_function->func,
			block_name);
		snprintf(block_name, sizeof block_name,
			"block_%d", block_count++);
		LLVMBasicBlockRef for_stmt = LLVMAppendBasicBlock(cl2llvm_current_function->func,
			block_name);
		snprintf(block_name, sizeof block_name,
			"block_%d", block_count++);
		LLVMBasicBlockRef for_incr = LLVMAppendBasicBlock(cl2llvm_current_function->func,
			block_name);
		snprintf(block_name, sizeof block_name,
			"block_%d", block_count++);
		LLVMBasicBlockRef for_end = LLVMAppendBasicBlock(cl2llvm_current_function->func, 
			block_name);

		for_blocks->for_cond = for_cond;
		for_blocks->for_stmt = for_stmt;
		for_blocks->for_incr = for_incr;
		for_blocks->for_end = for_end;

		/*Prepare to build for loop conditional*/
		LLVMBuildBr(cl2llvm_builder, for_blocks->for_cond);
		LLVMPositionBuilderAtEnd(cl2llvm_builder, for_blocks->for_cond);

		(yyval.llvm_for_blocks) = for_blocks;
		
	}
#line 3438 "parser.c" /* yacc.c:1646  */
    break;

  case 95:
#line 1411 "parser.y" /* yacc.c:1646  */
    {
		struct cl2llvm_val_t *bool_val = NULL;

		/*Build for loop conditional*/
		if ((yyvsp[-1].llvm_value_ref) != NULL)
		{
			if (LLVMGetTypeKind((yyvsp[-1].llvm_value_ref)->type->llvm_type)
				== LLVMVectorTypeKind)
				cl2llvm_yyerror("expression must have "
					"arithmetic, enum or pointer type");
			bool_val = cl2llvm_to_bool_ne_0((yyvsp[-1].llvm_value_ref));
			LLVMBuildCondBr(cl2llvm_builder, bool_val->val, 
				(yyvsp[-2].llvm_for_blocks)->for_stmt, (yyvsp[-2].llvm_for_blocks)->for_end);
		}
		else
		{
			LLVMBuildBr(cl2llvm_builder, (yyvsp[-2].llvm_for_blocks)->for_stmt);
		}

		/*Prepare to build for loop increment*/
		LLVMPositionBuilderAtEnd(cl2llvm_builder, (yyvsp[-2].llvm_for_blocks)->for_incr);
		
		/*Free pointers*/
		if (bool_val != NULL)
			cl2llvm_val_free(bool_val);
		if ((yyvsp[-1].llvm_value_ref) != NULL)
			cl2llvm_val_free((yyvsp[-1].llvm_value_ref));
		
	}
#line 3472 "parser.c" /* yacc.c:1646  */
    break;

  case 96:
#line 1441 "parser.y" /* yacc.c:1646  */
    {
		LLVMBuildBr(cl2llvm_builder, (yyvsp[-5].llvm_for_blocks)->for_cond);

		/*Prepare to build for loop statements*/
		LLVMPositionBuilderAtEnd(cl2llvm_builder, (yyvsp[-5].llvm_for_blocks)->for_stmt);
		current_basic_block = (yyvsp[-5].llvm_for_blocks)->for_stmt;
		/*Free pointers*/
		if ((yyvsp[-1].llvm_value_ref) != NULL)
			cl2llvm_val_free((yyvsp[-1].llvm_value_ref));

		(yyval.llvm_for_blocks) = (yyvsp[-5].llvm_for_blocks);

	}
#line 3490 "parser.c" /* yacc.c:1646  */
    break;

  case 97:
#line 1458 "parser.y" /* yacc.c:1646  */
    {
		struct cl2llvm_while_blocks_t *while_blocks = cl2llvm_while_blocks_create();

		snprintf(block_name, sizeof block_name,
			"block_%d", block_count++);
		LLVMBasicBlockRef while_stmt = LLVMAppendBasicBlock(cl2llvm_current_function->func, block_name);

		snprintf(block_name, sizeof block_name,
			"block_%d", block_count++);
		LLVMBasicBlockRef while_cond = LLVMAppendBasicBlock(cl2llvm_current_function->func, block_name);
		snprintf(block_name, sizeof block_name,
			"block_%d", block_count++);
		LLVMBasicBlockRef while_end = LLVMAppendBasicBlock(cl2llvm_current_function->func, block_name);
		
		LLVMBuildBr(cl2llvm_builder, while_stmt);
		LLVMPositionBuilderAtEnd(cl2llvm_builder, while_stmt);
		current_basic_block = while_stmt;

		while_blocks->while_stmt = while_stmt;
		while_blocks->while_cond = while_cond;
		while_blocks->while_end = while_end;

		(yyval.llvm_while_blocks) = while_blocks;
	}
#line 3519 "parser.c" /* yacc.c:1646  */
    break;

  case 98:
#line 1483 "parser.y" /* yacc.c:1646  */
    {
		LLVMBuildBr(cl2llvm_builder, (yyvsp[-3].llvm_while_blocks)->while_cond);
		LLVMPositionBuilderAtEnd(cl2llvm_builder, (yyvsp[-3].llvm_while_blocks)->while_cond);
		current_basic_block = (yyvsp[-3].llvm_while_blocks)->while_cond;
	}
#line 3529 "parser.c" /* yacc.c:1646  */
    break;

  case 99:
#line 1489 "parser.y" /* yacc.c:1646  */
    {
		struct cl2llvm_val_t *bool_val;
	
		if (LLVMGetTypeKind((yyvsp[-2].llvm_value_ref)->type->llvm_type)
			== LLVMVectorTypeKind)
			cl2llvm_yyerror("expression must have "
				"arithmetic, enum or pointer type");
		bool_val = cl2llvm_to_bool_ne_0((yyvsp[-2].llvm_value_ref));
		LLVMBuildCondBr(cl2llvm_builder, bool_val->val, (yyvsp[-7].llvm_while_blocks)->while_stmt,
			(yyvsp[-7].llvm_while_blocks)->while_end);
		LLVMPositionBuilderAtEnd(cl2llvm_builder, (yyvsp[-7].llvm_while_blocks)->while_end);
		current_basic_block = (yyvsp[-7].llvm_while_blocks)->while_end;
	}
#line 3547 "parser.c" /* yacc.c:1646  */
    break;

  case 100:
#line 1506 "parser.y" /* yacc.c:1646  */
    {
		struct cl2llvm_val_t *bool_val;
		
		if (LLVMGetTypeKind((yyvsp[-1].llvm_value_ref)->type->llvm_type)
			== LLVMVectorTypeKind)
			cl2llvm_yyerror("expression must have "
				"arithmetic, enum or pointer type");
		bool_val = cl2llvm_to_bool_ne_0((yyvsp[-1].llvm_value_ref));
		LLVMBuildCondBr(cl2llvm_builder, bool_val->val, (yyvsp[-2].llvm_while_blocks)->while_stmt, (yyvsp[-2].llvm_while_blocks)->while_end);

		LLVMPositionBuilderAtEnd(cl2llvm_builder, (yyvsp[-2].llvm_while_blocks)->while_stmt);
	
		current_basic_block = (yyvsp[-2].llvm_while_blocks)->while_stmt;
	
		cl2llvm_val_free(bool_val);
		cl2llvm_val_free((yyvsp[-1].llvm_value_ref));
	}
#line 3569 "parser.c" /* yacc.c:1646  */
    break;

  case 101:
#line 1524 "parser.y" /* yacc.c:1646  */
    {
		LLVMBuildBr(cl2llvm_builder, (yyvsp[-4].llvm_while_blocks)->while_cond);
		LLVMPositionBuilderAtEnd(cl2llvm_builder, (yyvsp[-4].llvm_while_blocks)->while_end);
		current_basic_block = (yyvsp[-4].llvm_while_blocks)->while_end;
		cl2llvm_while_blocks_free((yyvsp[-4].llvm_while_blocks));
	}
#line 3580 "parser.c" /* yacc.c:1646  */
    break;

  case 102:
#line 1534 "parser.y" /* yacc.c:1646  */
    {
		struct cl2llvm_while_blocks_t *while_blocks = cl2llvm_while_blocks_create();

		snprintf(block_name, sizeof block_name,
			"block_%d", block_count++);
		LLVMBasicBlockRef while_stmt = LLVMAppendBasicBlock(cl2llvm_current_function->func, block_name);

		snprintf(block_name, sizeof block_name,
			"block_%d", block_count++);
		LLVMBasicBlockRef while_cond = LLVMAppendBasicBlock(cl2llvm_current_function->func, block_name);
		snprintf(block_name, sizeof block_name,
			"block_%d", block_count++);
		LLVMBasicBlockRef while_end = LLVMAppendBasicBlock(cl2llvm_current_function->func, block_name);
		
		LLVMBuildBr(cl2llvm_builder, while_cond);
		LLVMPositionBuilderAtEnd(cl2llvm_builder, while_cond);

		while_blocks->while_stmt = while_stmt;
		while_blocks->while_cond = while_cond;
		while_blocks->while_end = while_end;

		(yyval.llvm_while_blocks) = while_blocks;
	}
#line 3608 "parser.c" /* yacc.c:1646  */
    break;

  case 103:
#line 1561 "parser.y" /* yacc.c:1646  */
    {
		(yyval.llvm_value_ref) = NULL;
	}
#line 3616 "parser.c" /* yacc.c:1646  */
    break;

  case 104:
#line 1565 "parser.y" /* yacc.c:1646  */
    {
		(yyval.llvm_value_ref) = (yyvsp[0].llvm_value_ref);
	}
#line 3624 "parser.c" /* yacc.c:1646  */
    break;

  case 106:
#line 1573 "parser.y" /* yacc.c:1646  */
    {
		(yyval.llvm_value_ref) = (yyvsp[-1].llvm_value_ref);
	}
#line 3632 "parser.c" /* yacc.c:1646  */
    break;

  case 107:
#line 1577 "parser.y" /* yacc.c:1646  */
    {
		struct cl2llvm_type_t *switch_type;
		struct cl2llvm_val_t *value;
		struct cl2llvm_type_t *type = cl2llvm_type_create();
		struct cl2llvm_val_t *op1, *op2;
		
		/* Find out which value differs from the original and set the
		   dominant type equal to the type of that value. */
		type_unify((yyvsp[-2].llvm_value_ref), (yyvsp[0].llvm_value_ref), &op1, &op2);
		if(op1 == (yyvsp[-2].llvm_value_ref))
		{
			type->llvm_type = op1->type->llvm_type;
			type->sign = op1->type->sign;
		}
		else
		{
			type->llvm_type = op2->type->llvm_type;
			type->sign = op2->type->sign;
		}

		/* Create an object that will hold the type of the operands.
		   This extra object is necessary since in the case of a vector 
		   type, we are concerned with the type of its components, but the
		   resultant type of the operation is a vector. */
		switch_type = cl2llvm_type_create_w_init(type->llvm_type, type->sign);
		if (LLVMGetTypeKind(type->llvm_type) == LLVMVectorTypeKind)
		{
			switch_type->llvm_type = LLVMGetElementType(type->llvm_type);
		}

		snprintf(temp_var_name, sizeof temp_var_name,
				"tmp_%d", temp_var_count++);
		
		value = cl2llvm_val_create();

		/* Determine which type of addition to use based on type of
		   operators. */
		switch (LLVMGetTypeKind(switch_type->llvm_type))
		{
		case LLVMIntegerTypeKind:

			value->val = LLVMBuildAdd(cl2llvm_builder, op1->val, op2->val, temp_var_name);
			value->type->sign = type->sign;
			value->type->llvm_type = type->llvm_type;
			break;

		case LLVMHalfTypeKind:
		case LLVMFloatTypeKind:
		case LLVMDoubleTypeKind:

			value->val = LLVMBuildFAdd(cl2llvm_builder, op1->val, op2->val, temp_var_name);
			value->type->sign = type->sign;
			value->type->llvm_type = type->llvm_type;
			break;

		default:

			yyerror("invalid type of operands for addition");
		}
		
		/* Free pointers */
		if ((yyvsp[-2].llvm_value_ref) != op1)
			cl2llvm_val_free(op1);
		else if ((yyvsp[0].llvm_value_ref) != op2)
			cl2llvm_val_free( op2);
		cl2llvm_val_free((yyvsp[0].llvm_value_ref));
		cl2llvm_val_free((yyvsp[-2].llvm_value_ref));
		cl2llvm_type_free(type);
		cl2llvm_type_free(switch_type);

		(yyval.llvm_value_ref) = value;
	}
#line 3709 "parser.c" /* yacc.c:1646  */
    break;

  case 108:
#line 1650 "parser.y" /* yacc.c:1646  */
    {
		struct cl2llvm_val_t *value;
		struct cl2llvm_type_t *switch_type;
		struct cl2llvm_type_t *type = cl2llvm_type_create();
		struct cl2llvm_val_t *op1, *op2;

		/* Find out which value differs from the original and set the
		   dominant type equal to the type of that value. */	
		type_unify((yyvsp[-2].llvm_value_ref), (yyvsp[0].llvm_value_ref), &op1, & op2);
		if(op1 == (yyvsp[-2].llvm_value_ref))
		{
			type->llvm_type = LLVMTypeOf(op1->val);
			type->sign = op1->type->sign;
		}
		else
		{
			type->llvm_type = LLVMTypeOf(op1->val);
			type->sign = op1->type->sign;
		}
		
		/* Create an object that will hold the type of the operands.
		   This extra object is necessary since in the case of a vector 
		   type, we are concerned with the type of its components, but the
		   resultant type of the operation is a vector. */
		switch_type = cl2llvm_type_create_w_init(type->llvm_type, type->sign);
		if (LLVMGetTypeKind(type->llvm_type) == LLVMVectorTypeKind)
		{
			switch_type->llvm_type = LLVMGetElementType(type->llvm_type);
		}

		snprintf(temp_var_name, sizeof temp_var_name,
				"tmp_%d", temp_var_count++);

		value = cl2llvm_val_create();
		switch (LLVMGetTypeKind(switch_type->llvm_type))
		{
		case LLVMIntegerTypeKind:

			value->val = LLVMBuildSub(cl2llvm_builder, op1->val, op2->val, temp_var_name);
			value->type->sign = type->sign;
			value->type->llvm_type = type->llvm_type;
			break;

		case LLVMHalfTypeKind:
		case LLVMFloatTypeKind:
		case LLVMDoubleTypeKind:

			value->val = LLVMBuildFSub(cl2llvm_builder, op1->val, op2->val, temp_var_name);
			value->type->sign = type->sign;
			value->type->llvm_type = type->llvm_type;
			break;

		default:

			yyerror("invalid type of operands for subtraction");
		}
		if ((yyvsp[-2].llvm_value_ref) != op1)
			cl2llvm_val_free(op1);
		else if ((yyvsp[0].llvm_value_ref) != op2)
			cl2llvm_val_free(op2);

		cl2llvm_val_free((yyvsp[-2].llvm_value_ref));
		cl2llvm_val_free((yyvsp[0].llvm_value_ref));
		cl2llvm_type_free(type);
		cl2llvm_type_free(switch_type);

		(yyval.llvm_value_ref) = value;
	}
#line 3782 "parser.c" /* yacc.c:1646  */
    break;

  case 109:
#line 1719 "parser.y" /* yacc.c:1646  */
    {
		struct cl2llvm_type_t *switch_type;
		struct cl2llvm_type_t *type;
		struct cl2llvm_val_t *value;

		type = cl2llvm_type_create();
		value = cl2llvm_val_create();

		snprintf(temp_var_name, sizeof temp_var_name,
			"tmp_%d", temp_var_count++);

		struct cl2llvm_val_t *op1, *op2;
		
		type_unify((yyvsp[-2].llvm_value_ref), (yyvsp[0].llvm_value_ref), &op1, &op2);
		if(op1 == (yyvsp[-2].llvm_value_ref))
		{
			type->llvm_type = LLVMTypeOf(op1->val);
			type->sign = op1->type->sign;
		}
		else
		{
			type->llvm_type = LLVMTypeOf(op1->val);
			type->sign = op1->type->sign;
		}
		
		/* Create an object that will hold the type of the operands.
		   This extra object is necessary since in the case of a vector 
		   type, we are concerned with the type of its components, but the
		   resultant type of the operation is a vector. */
		switch_type = cl2llvm_type_create_w_init(type->llvm_type, type->sign);
		if (LLVMGetTypeKind(type->llvm_type) == LLVMVectorTypeKind)
		{
			switch_type->llvm_type = LLVMGetElementType(type->llvm_type);
		}

		switch (LLVMGetTypeKind(switch_type->llvm_type))
		{
		case LLVMIntegerTypeKind:

			value->val = LLVMBuildMul(cl2llvm_builder, op1->val,
				op2->val, temp_var_name);

			value->type->sign = type->sign;
			value->type->llvm_type = type->llvm_type;

			break;

		case LLVMHalfTypeKind:
		case LLVMFloatTypeKind:
		case LLVMDoubleTypeKind:

			value->val = LLVMBuildFMul(cl2llvm_builder, op1->val,
				op2->val, temp_var_name);

			value->type->sign = type->sign;
			value->type->llvm_type = type->llvm_type;

			break;

		default:

			yyerror("invalid type of operands for addition");
		}

		/* Free pointers */
		if ((yyvsp[-2].llvm_value_ref) != op1)
			cl2llvm_val_free(op1);
		else if ((yyvsp[0].llvm_value_ref) != op2)
			cl2llvm_val_free(op2);
		cl2llvm_val_free((yyvsp[-2].llvm_value_ref));
		cl2llvm_val_free((yyvsp[0].llvm_value_ref));
		cl2llvm_type_free(type);
		cl2llvm_type_free(switch_type);

		(yyval.llvm_value_ref) = value;

	}
#line 3864 "parser.c" /* yacc.c:1646  */
    break;

  case 110:
#line 1797 "parser.y" /* yacc.c:1646  */
    {
		struct cl2llvm_type_t *switch_type;
		struct cl2llvm_type_t *type;
		struct cl2llvm_val_t *value;
		
		type = cl2llvm_type_create();
		value = cl2llvm_val_create();

		snprintf(temp_var_name, sizeof temp_var_name,
			"tmp_%d", temp_var_count++);

		struct cl2llvm_val_t *op1, *op2;
		
		type_unify((yyvsp[-2].llvm_value_ref), (yyvsp[0].llvm_value_ref), &op1, & op2);
		if(op1 == (yyvsp[-2].llvm_value_ref))
		{
			type->llvm_type = LLVMTypeOf(op1->val);
			type->sign = op1->type->sign;
		}
		else
		{
			type->llvm_type = LLVMTypeOf(op1->val);
			type->sign = op1->type->sign;
		}

		/* Create an object that will hold the type of the operands.
		   This extra object is necessary since in the case of a vector 
		   type, we are concerned with the type of its components, but the
		   resultant type of the operation is a vector. */
		switch_type = cl2llvm_type_create_w_init(type->llvm_type, type->sign);
		if (LLVMGetTypeKind(type->llvm_type) == LLVMVectorTypeKind)
		{
			switch_type->llvm_type = LLVMGetElementType(type->llvm_type);
		}

		switch (LLVMGetTypeKind(switch_type->llvm_type))
		{
		case LLVMIntegerTypeKind:
			if (type->sign)
			{
				value->val = LLVMBuildSDiv(cl2llvm_builder, 
					op1->val, op2->val, temp_var_name);
			}
			else
			{
				value->val = LLVMBuildUDiv(cl2llvm_builder, 
					op1->val, op2->val, temp_var_name);
			}
			value->type->sign = type->sign;
			value->type->llvm_type = type->llvm_type;
			break;

		case LLVMHalfTypeKind:
		case LLVMFloatTypeKind:
		case LLVMDoubleTypeKind:
			value->val = LLVMBuildFDiv(cl2llvm_builder, 
					op1->val, op2->val, temp_var_name);
			value->type->sign = type->sign;
			value->type->llvm_type = type->llvm_type;
			break;

		default:
			
			yyerror("invalid type of operands for '/'");
		}

		/* Free pointers */
		if ((yyvsp[-2].llvm_value_ref) != op1)
			cl2llvm_val_free(op1);
		else if ((yyvsp[0].llvm_value_ref) != op2)
			cl2llvm_val_free(op2);
		cl2llvm_val_free((yyvsp[-2].llvm_value_ref));
		cl2llvm_val_free((yyvsp[0].llvm_value_ref));
		cl2llvm_type_free(type);
		cl2llvm_type_free(switch_type);

		(yyval.llvm_value_ref) = value;
	}
#line 3947 "parser.c" /* yacc.c:1646  */
    break;

  case 111:
#line 1876 "parser.y" /* yacc.c:1646  */
    {
		struct cl2llvm_type_t *type;
		struct cl2llvm_val_t *value;
		
		snprintf(temp_var_name, sizeof temp_var_name,
			"tmp_%d", temp_var_count++);
	
		type = cl2llvm_type_create();
		value = cl2llvm_val_create();

		struct cl2llvm_val_t *op1, *op2;
		
		type_unify((yyvsp[-2].llvm_value_ref), (yyvsp[0].llvm_value_ref), &op1, & op2);
		if(op1 == (yyvsp[-2].llvm_value_ref))
		{
			type->llvm_type = LLVMTypeOf(op1->val);
			type->sign = op1->type->sign;
		}
		else
		{
			type->llvm_type = LLVMTypeOf(op1->val);
			type->sign = op1->type->sign;
		}

		switch (type->sign)
		{
		case 1:
			value->val = LLVMBuildSRem(cl2llvm_builder, 
				op1->val, op2->val, temp_var_name);
			value->type->sign = type->sign;
			value->type->llvm_type = type->llvm_type;
			break;

		case 0:
			value->val = LLVMBuildURem(cl2llvm_builder, 
				op1->val, op2->val, temp_var_name);
			value->type->sign = type->sign;
			value->type->llvm_type = type->llvm_type;
			break;

		default:
			
			yyerror("invalid type of operands for addition");
		}
		
		/* Free pointers */
		if ((yyvsp[-2].llvm_value_ref) != op1)
			cl2llvm_val_free(op1);
		else if ((yyvsp[0].llvm_value_ref) != op2)
			cl2llvm_val_free(op2);
		cl2llvm_val_free((yyvsp[-2].llvm_value_ref));
		cl2llvm_val_free((yyvsp[0].llvm_value_ref));
		cl2llvm_type_free(type);

		(yyval.llvm_value_ref) = value;

	}
#line 4009 "parser.c" /* yacc.c:1646  */
    break;

  case 112:
#line 1934 "parser.y" /* yacc.c:1646  */
    {
		struct cl2llvm_type_t *switch_type;
		struct cl2llvm_type_t *type;
		struct cl2llvm_val_t *value;
		
		type = cl2llvm_type_create();
		value = cl2llvm_val_create();

		snprintf(temp_var_name, sizeof temp_var_name,
			"tmp_%d", temp_var_count++);

		struct cl2llvm_val_t *op1, *op2;
		
		type_unify((yyvsp[-2].llvm_value_ref), (yyvsp[0].llvm_value_ref), &op1, & op2);
		if(op1 == (yyvsp[-2].llvm_value_ref))
		{
			type->llvm_type = LLVMTypeOf(op1->val);
			type->sign = op1->type->sign;
		}
		else
		{
			type->llvm_type = LLVMTypeOf(op1->val);
			type->sign = op1->type->sign;
		}

		/* Create an object that will hold the type of the operands.
		   This extra object is necessary since in the case of a vector 
		   type, we are concerned with the type of its components, but the
		   resultant type of the operation is a vector. */
		switch_type = cl2llvm_type_create_w_init(type->llvm_type, type->sign);
		if (LLVMGetTypeKind(type->llvm_type) == LLVMVectorTypeKind)
		{
			switch_type->llvm_type = LLVMGetElementType(type->llvm_type);
		}

		switch (LLVMGetTypeKind(switch_type->llvm_type))
		{
		case LLVMIntegerTypeKind:
			value->val = LLVMBuildShl(cl2llvm_builder, 
				op1->val, op2->val, temp_var_name);
			value->type->sign = type->sign;
			value->type->llvm_type = type->llvm_type;
			break;


		default:
			
			yyerror("Invalid type of operands for '<<'.");
		}

		/* Free pointers */
		if ((yyvsp[-2].llvm_value_ref) != op1)
			cl2llvm_val_free(op1);
		else if ((yyvsp[0].llvm_value_ref) != op2)
			cl2llvm_val_free(op2);
		cl2llvm_val_free((yyvsp[-2].llvm_value_ref));
		cl2llvm_val_free((yyvsp[0].llvm_value_ref));
		cl2llvm_type_free(type);
		cl2llvm_type_free(switch_type);

		(yyval.llvm_value_ref) = value;

	}
#line 4077 "parser.c" /* yacc.c:1646  */
    break;

  case 113:
#line 1998 "parser.y" /* yacc.c:1646  */
    {
		struct cl2llvm_type_t *switch_type;
		struct cl2llvm_type_t *type;
		struct cl2llvm_val_t *value;
		
		type = cl2llvm_type_create();
		value = cl2llvm_val_create();

		snprintf(temp_var_name, sizeof temp_var_name,
			"tmp_%d", temp_var_count++);

		struct cl2llvm_val_t *op1, *op2;
		
		type_unify((yyvsp[-2].llvm_value_ref), (yyvsp[0].llvm_value_ref), &op1, & op2);
		if(op1 == (yyvsp[-2].llvm_value_ref))
		{
			type->llvm_type = LLVMTypeOf(op1->val);
			type->sign = op1->type->sign;
		}
		else
		{
			type->llvm_type = LLVMTypeOf(op1->val);
			type->sign = op1->type->sign;
		}

		/* Create an object that will hold the type of the operands.
		   This extra object is necessary since in the case of a vector 
		   type, we are concerned with the type of its components, but the
		   resultant type of the operation is a vector. */
		switch_type = cl2llvm_type_create_w_init(type->llvm_type, type->sign);
		if (LLVMGetTypeKind(type->llvm_type) == LLVMVectorTypeKind)
		{
			switch_type->llvm_type = LLVMGetElementType(type->llvm_type);
		}

		switch (LLVMGetTypeKind(switch_type->llvm_type))
		{
		case LLVMIntegerTypeKind:
			value->val = LLVMBuildAShr(cl2llvm_builder, 
				op1->val, op2->val, temp_var_name);
			value->type->sign = type->sign;
			value->type->llvm_type = type->llvm_type;
			break;


		default:
			
			yyerror("Invalid type of operands for '>>'.");
		}

		/* Free pointers */
		if ((yyvsp[-2].llvm_value_ref) != op1)
			cl2llvm_val_free(op1);
		else if ((yyvsp[0].llvm_value_ref) != op2)
			cl2llvm_val_free(op2);
		cl2llvm_val_free((yyvsp[-2].llvm_value_ref));
		cl2llvm_val_free((yyvsp[0].llvm_value_ref));
		cl2llvm_type_free(type);
		cl2llvm_type_free(switch_type);

		(yyval.llvm_value_ref) = value;
	}
#line 4144 "parser.c" /* yacc.c:1646  */
    break;

  case 114:
#line 2061 "parser.y" /* yacc.c:1646  */
    {
		struct cl2llvm_type_t *switch_type;
		struct cl2llvm_type_t *type;
		struct cl2llvm_val_t *value;
		struct cl2llvm_val_t *bool_val;
		

		type = cl2llvm_type_create();
		bool_val = cl2llvm_val_create();

		struct cl2llvm_val_t *op1, *op2;
		
		type_unify((yyvsp[-2].llvm_value_ref), (yyvsp[0].llvm_value_ref), &op1, & op2);
		if(op1 == (yyvsp[-2].llvm_value_ref))
		{
			type->llvm_type = LLVMTypeOf(op1->val);
			type->sign = op1->type->sign;
		}
		else
		{
			type->llvm_type = LLVMTypeOf(op1->val);
			type->sign = op1->type->sign;
		}

		/* Create an object that will hold the type of the operands.
		   This extra object is necessary since in the case of a vector 
		   type, we are concerned with the type of its components, but the
		   resultant type of the operation is a vector. */
		switch_type = cl2llvm_type_create_w_init(type->llvm_type, type->sign);
		if (LLVMGetTypeKind(switch_type->llvm_type) == LLVMVectorTypeKind)
		{
			switch_type->llvm_type = LLVMGetElementType(type->llvm_type);
		}
		
		snprintf(temp_var_name, sizeof temp_var_name,
			"tmp_%d", temp_var_count++);
		
		switch (LLVMGetTypeKind(switch_type->llvm_type))
		{
		case LLVMIntegerTypeKind:

			bool_val->val = LLVMBuildICmp(cl2llvm_builder, LLVMIntEQ,
				op1->val, op2->val, temp_var_name);
			bool_val->type->sign = 1;
			bool_val->type->llvm_type = LLVMInt1Type();
			break;

		case LLVMHalfTypeKind:
		case LLVMFloatTypeKind:
		case LLVMDoubleTypeKind:

			bool_val->val = LLVMBuildFCmp(cl2llvm_builder,
				LLVMRealOEQ, op1->val, op2->val, temp_var_name);
			bool_val->type->sign = 1;
			bool_val->type->llvm_type = LLVMInt1Type();
			break;

		default:

			yyerror("invalid type of operands for equality");
		}

		/* Extend bits */
		value = cl2llvm_bool_ext(bool_val, (yyvsp[-2].llvm_value_ref)->type);

		/* Free pointers */
		if ((yyvsp[-2].llvm_value_ref) != op1)
			cl2llvm_val_free(op1);
		else if ((yyvsp[0].llvm_value_ref) != op2)
			cl2llvm_val_free(op2);
		cl2llvm_val_free((yyvsp[-2].llvm_value_ref));
		cl2llvm_val_free((yyvsp[0].llvm_value_ref));
		cl2llvm_val_free(bool_val);
		cl2llvm_type_free(type);
		cl2llvm_type_free(switch_type);

		(yyval.llvm_value_ref) = value;
	}
#line 4227 "parser.c" /* yacc.c:1646  */
    break;

  case 115:
#line 2140 "parser.y" /* yacc.c:1646  */
    {
		struct cl2llvm_type_t *switch_type;
		struct cl2llvm_type_t *type;
		struct cl2llvm_val_t *value;
		struct cl2llvm_val_t *bool_val;
		
		type = cl2llvm_type_create();
		bool_val = cl2llvm_val_create();

		struct cl2llvm_val_t *op1, *op2;
		
		type_unify((yyvsp[-2].llvm_value_ref), (yyvsp[0].llvm_value_ref), &op1, & op2);
		if(op1 == (yyvsp[-2].llvm_value_ref))
		{
			type->llvm_type = LLVMTypeOf(op1->val);
			type->sign = op1->type->sign;
		}
		else
		{
			type->llvm_type = LLVMTypeOf(op1->val);
			type->sign = op1->type->sign;
		}

		/* Create an object that will hold the type of the operands.
		   This extra object is necessary since in the case of a vector 
		   type, we are concerned with the type of its components, but the
		   resultant type of the operation is a vector. */
		switch_type = cl2llvm_type_create_w_init(type->llvm_type, type->sign);
		if (LLVMGetTypeKind(switch_type->llvm_type) == LLVMVectorTypeKind)
		{
			switch_type->llvm_type = LLVMGetElementType(type->llvm_type);
		}
		
		snprintf(temp_var_name, sizeof temp_var_name,
			"tmp_%d", temp_var_count++);

		switch (LLVMGetTypeKind(switch_type->llvm_type))
		{
		case LLVMIntegerTypeKind:

			bool_val->val = LLVMBuildICmp(cl2llvm_builder, LLVMIntNE,
				op1->val, op2->val, temp_var_name);
			bool_val->type->sign = 1;
			bool_val->type->llvm_type = LLVMInt1Type();
			break;

		case LLVMHalfTypeKind:
		case LLVMFloatTypeKind:
		case LLVMDoubleTypeKind:

			bool_val->val = LLVMBuildFCmp(cl2llvm_builder, 
				LLVMRealONE, op1->val, op2->val, temp_var_name);
			bool_val->type->sign = 1;
			bool_val->type->llvm_type = LLVMInt1Type();
			break;

		default:

			yyerror("invalid type of operands for addition");
		}
	
		/* Extend bits */
		value = cl2llvm_bool_ext(bool_val, (yyvsp[-2].llvm_value_ref)->type);

		/* Free pointers */
		if ((yyvsp[-2].llvm_value_ref) != op1)
			cl2llvm_val_free(op1);
		else if ((yyvsp[0].llvm_value_ref) != op2)
			cl2llvm_val_free(op2);
		cl2llvm_val_free((yyvsp[-2].llvm_value_ref));
		cl2llvm_val_free((yyvsp[0].llvm_value_ref));
		cl2llvm_val_free(bool_val);
		cl2llvm_type_free(type);
		cl2llvm_type_free(switch_type);

		(yyval.llvm_value_ref) = value;

	}
#line 4310 "parser.c" /* yacc.c:1646  */
    break;

  case 116:
#line 2219 "parser.y" /* yacc.c:1646  */
    {
		struct cl2llvm_type_t *switch_type;
		struct cl2llvm_type_t *type;
		struct cl2llvm_val_t *value;
		struct cl2llvm_val_t *bool_val;
		
	
		type = cl2llvm_type_create();
		bool_val = cl2llvm_val_create();

		struct cl2llvm_val_t *op1, *op2;
		
		type_unify((yyvsp[-2].llvm_value_ref), (yyvsp[0].llvm_value_ref), &op1, & op2);
		if(op1 == (yyvsp[-2].llvm_value_ref))
		{
			type->llvm_type = LLVMTypeOf(op1->val);
			type->sign = op1->type->sign;
		}
		else
		{
			type->llvm_type = LLVMTypeOf(op1->val);
			type->sign = op1->type->sign;
		}

		/* Create an object that will hold the type of the operands.
		   This extra object is necessary since in the case of a vector 
		   type, we are concerned with the type of its components, but the
		   resultant type of the operation is a vector. */
		switch_type = cl2llvm_type_create_w_init(type->llvm_type, type->sign);
		if (LLVMGetTypeKind(switch_type->llvm_type) == LLVMVectorTypeKind)
		{
			switch_type->llvm_type = LLVMGetElementType(type->llvm_type);
		}
	
		snprintf(temp_var_name, sizeof temp_var_name,
			"tmp_%d", temp_var_count++);

		switch (LLVMGetTypeKind(switch_type->llvm_type))
		{
		case LLVMIntegerTypeKind:

			if (type->sign)
			{
				bool_val->val = LLVMBuildICmp(cl2llvm_builder, 
					LLVMIntSLT, op1->val, op2->val, 
					temp_var_name);
			}
			else
			{
				bool_val->val = LLVMBuildICmp(cl2llvm_builder, 
					LLVMIntULT, op1->val, op2->val, 
					temp_var_name);
			}
			bool_val->type->sign = 1;
			bool_val->type->llvm_type = LLVMInt1Type();
			break;

		case LLVMHalfTypeKind:
		case LLVMFloatTypeKind:
		case LLVMDoubleTypeKind:

			bool_val->val = LLVMBuildFCmp(cl2llvm_builder, 
				LLVMRealOLT, op1->val, op2->val, temp_var_name);
			bool_val->type->sign = 1;
			bool_val->type->llvm_type = LLVMInt1Type();
			break;

		default:

			yyerror("invalid type of operands for comparison");
		}

		/* Extend bits */
		value = cl2llvm_bool_ext(bool_val, (yyvsp[-2].llvm_value_ref)->type);

		/* Free pointers */
		if ((yyvsp[-2].llvm_value_ref) != op1)
			cl2llvm_val_free(op1);
		else if ((yyvsp[0].llvm_value_ref) != op2)
			cl2llvm_val_free(op2);
		cl2llvm_val_free((yyvsp[-2].llvm_value_ref));
		cl2llvm_val_free((yyvsp[0].llvm_value_ref));
		cl2llvm_val_free(bool_val);
		cl2llvm_type_free(type);
		cl2llvm_type_free(switch_type);

		(yyval.llvm_value_ref) = value;

	}
#line 4404 "parser.c" /* yacc.c:1646  */
    break;

  case 117:
#line 2309 "parser.y" /* yacc.c:1646  */
    {
		struct cl2llvm_type_t *switch_type;
		struct cl2llvm_type_t *type;
		struct cl2llvm_val_t *value;
		struct cl2llvm_val_t *bool_val;
		
	
		type = cl2llvm_type_create();
		bool_val = cl2llvm_val_create();

		struct cl2llvm_val_t *op1, *op2;
		
		type_unify((yyvsp[-2].llvm_value_ref), (yyvsp[0].llvm_value_ref), &op1, & op2);
		if(op1 == (yyvsp[-2].llvm_value_ref))
		{
			type->llvm_type = LLVMTypeOf(op1->val);
			type->sign = op1->type->sign;
		}
		else
		{
			type->llvm_type = LLVMTypeOf(op1->val);
			type->sign = op1->type->sign;
		}

		/* Create an object that will hold the type of the operands.
		   This extra object is necessary since in the case of a vector 
		   type, we are concerned with the type of its components, but the
		   resultant type of the operation is a vector. */
		switch_type = cl2llvm_type_create_w_init(type->llvm_type, type->sign);
		if (LLVMGetTypeKind(switch_type->llvm_type) == LLVMVectorTypeKind)
		{
			switch_type->llvm_type = LLVMGetElementType(type->llvm_type);
		}
	
		snprintf(temp_var_name, sizeof temp_var_name,
			"tmp_%d", temp_var_count++);

		switch (LLVMGetTypeKind(switch_type->llvm_type))
		{
		case LLVMIntegerTypeKind:

			if (type->sign)
			{
				bool_val->val = LLVMBuildICmp(cl2llvm_builder, 
					LLVMIntSGT, op1->val, op2->val, 
					temp_var_name);
			}
			else
			{
				bool_val->val = LLVMBuildICmp(cl2llvm_builder, 
					LLVMIntUGT, op1->val, op2->val, 
					temp_var_name);
			}
			bool_val->type->sign = 1;
			bool_val->type->llvm_type = LLVMInt1Type();
			break;

		case LLVMHalfTypeKind:
		case LLVMFloatTypeKind:
		case LLVMDoubleTypeKind:

			bool_val->val = LLVMBuildFCmp(cl2llvm_builder, 
				LLVMRealOGT, op1->val, op2->val, temp_var_name);
			bool_val->type->sign = 1;
			bool_val->type->llvm_type = LLVMInt1Type();
			break;

		default:

			yyerror("invalid type of operands for comparison");
		}

		/* Extend bits */
		value = cl2llvm_bool_ext(bool_val, (yyvsp[-2].llvm_value_ref)->type);

		/* Free pointers */
		if ((yyvsp[-2].llvm_value_ref) != op1)
			cl2llvm_val_free(op1);
		else if ((yyvsp[0].llvm_value_ref) != op2)
			cl2llvm_val_free(op2);
		cl2llvm_val_free((yyvsp[-2].llvm_value_ref));
		cl2llvm_val_free((yyvsp[0].llvm_value_ref));
		cl2llvm_val_free(bool_val);
		cl2llvm_type_free(type);
		cl2llvm_type_free(switch_type);

		(yyval.llvm_value_ref) = value;
	}
#line 4497 "parser.c" /* yacc.c:1646  */
    break;

  case 118:
#line 2398 "parser.y" /* yacc.c:1646  */
    {
		struct cl2llvm_type_t *switch_type;
		struct cl2llvm_type_t *type;
		struct cl2llvm_val_t *value;
		struct cl2llvm_val_t *bool_val;
		
	
		type = cl2llvm_type_create();
		bool_val = cl2llvm_val_create();

		struct cl2llvm_val_t *op1, *op2;
		
		type_unify((yyvsp[-2].llvm_value_ref), (yyvsp[0].llvm_value_ref), &op1, & op2);
		if(op1 == (yyvsp[-2].llvm_value_ref))
		{
			type->llvm_type = LLVMTypeOf(op1->val);
			type->sign = op1->type->sign;
		}
		else
		{
			type->llvm_type = LLVMTypeOf(op1->val);
			type->sign = op1->type->sign;
		}

		/* Create an object that will hold the type of the operands.
		   This extra object is necessary since in the case of a vector 
		   type, we are concerned with the type of its components, but the
		   resultant type of the operation is a vector. */
		switch_type = cl2llvm_type_create_w_init(type->llvm_type, type->sign);
		if (LLVMGetTypeKind(switch_type->llvm_type) == LLVMVectorTypeKind)
		{
			switch_type->llvm_type = LLVMGetElementType(type->llvm_type);
		}
	
		snprintf(temp_var_name, sizeof temp_var_name,
			"tmp_%d", temp_var_count++);

		switch (LLVMGetTypeKind(switch_type->llvm_type))
		{
		case LLVMIntegerTypeKind:

			if (type->sign)
			{
				bool_val->val = LLVMBuildICmp(cl2llvm_builder, 
					LLVMIntSLE, op1->val, op2->val, 
					temp_var_name);
			}
			else
			{
				bool_val->val = LLVMBuildICmp(cl2llvm_builder, 
					LLVMIntULE, op1->val, op2->val, 
					temp_var_name);
			}
			bool_val->type->sign = 1;
			bool_val->type->llvm_type = LLVMInt1Type();
			break;

		case LLVMHalfTypeKind:
		case LLVMFloatTypeKind:
		case LLVMDoubleTypeKind:

			bool_val->val = LLVMBuildFCmp(cl2llvm_builder, 
				LLVMRealOLE, op1->val, op2->val, temp_var_name);
			bool_val->type->sign = 1;
			bool_val->type->llvm_type = LLVMInt1Type();
			break;

		default:

			yyerror("invalid type of operands for comparison");
		}
	
		/* Extend bits */
		value = cl2llvm_bool_ext(bool_val, (yyvsp[-2].llvm_value_ref)->type);

		/* Free pointers */
		if ((yyvsp[-2].llvm_value_ref) != op1)
			cl2llvm_val_free(op1);
		else if ((yyvsp[0].llvm_value_ref) != op2)
			cl2llvm_val_free(op2);
		cl2llvm_val_free((yyvsp[-2].llvm_value_ref));
		cl2llvm_val_free((yyvsp[0].llvm_value_ref));
		cl2llvm_val_free(bool_val);
		cl2llvm_type_free(type);
		cl2llvm_type_free(switch_type);

		(yyval.llvm_value_ref) = value;
	}
#line 4590 "parser.c" /* yacc.c:1646  */
    break;

  case 119:
#line 2487 "parser.y" /* yacc.c:1646  */
    {
		struct cl2llvm_type_t *switch_type;
		struct cl2llvm_type_t *type;
		struct cl2llvm_val_t *value;
		struct cl2llvm_val_t *bool_val;
		
	
		type = cl2llvm_type_create();
		bool_val = cl2llvm_val_create();

		struct cl2llvm_val_t *op1, *op2;
		
		type_unify((yyvsp[-2].llvm_value_ref), (yyvsp[0].llvm_value_ref), &op1, & op2);
		if(op1 == (yyvsp[-2].llvm_value_ref))
		{
			type->llvm_type = LLVMTypeOf(op1->val);
			type->sign = op1->type->sign;
		}
		else
		{
			type->llvm_type = LLVMTypeOf(op1->val);
			type->sign = op1->type->sign;
		}

		/* Create an object that will hold the type of the operands.
		   This extra object is necessary since in the case of a vector 
		   type, we are concerned with the type of its components, but the
		   resultant type of the operation is a vector. */
		switch_type = cl2llvm_type_create_w_init(type->llvm_type, type->sign);
		if (LLVMGetTypeKind(switch_type->llvm_type) == LLVMVectorTypeKind)
		{
			switch_type->llvm_type = LLVMGetElementType(type->llvm_type);
		}

		snprintf(temp_var_name, sizeof temp_var_name,
			"tmp_%d", temp_var_count++);

		switch (LLVMGetTypeKind(switch_type->llvm_type))
		{
		case LLVMIntegerTypeKind:

			if (type->sign)
			{
				bool_val->val = LLVMBuildICmp(cl2llvm_builder, 
					LLVMIntSGE, op1->val, op2->val, 
					temp_var_name);
			}
			else
			{
				bool_val->val = LLVMBuildICmp(cl2llvm_builder, 
					LLVMIntUGE, op1->val, op2->val, 
					temp_var_name);
			}
			bool_val->type->sign = 1;
			bool_val->type->llvm_type = LLVMInt1Type();
			break;

		case LLVMHalfTypeKind:
		case LLVMFloatTypeKind:
		case LLVMDoubleTypeKind:

			bool_val->val = LLVMBuildFCmp(cl2llvm_builder, 
				LLVMRealOGE, op1->val, op2->val, temp_var_name);
			bool_val->type->sign = 1;
			bool_val->type->llvm_type = LLVMInt1Type();
			break;

		default:

			yyerror("invalid type of operands for comparison");
		}
	
		/* Extend bits */
		value = cl2llvm_bool_ext(bool_val, (yyvsp[-2].llvm_value_ref)->type);

		/* Free pointers */
		if ((yyvsp[-2].llvm_value_ref) != op1)
			cl2llvm_val_free(op1);
		else if ((yyvsp[0].llvm_value_ref) != op2)
			cl2llvm_val_free(op2);
		cl2llvm_val_free((yyvsp[-2].llvm_value_ref));
		cl2llvm_val_free((yyvsp[0].llvm_value_ref));
		cl2llvm_val_free(bool_val);
		cl2llvm_type_free(type);
		cl2llvm_type_free(switch_type);

		(yyval.llvm_value_ref) = value;
	}
#line 4683 "parser.c" /* yacc.c:1646  */
    break;

  case 120:
#line 2576 "parser.y" /* yacc.c:1646  */
    {
		struct cl2llvm_val_t *bool1;
		struct cl2llvm_val_t *bool2;
		struct cl2llvm_val_t *value;
		struct cl2llvm_val_t *land_cond;
		struct cl2llvm_type_t *type;
		LLVMBasicBlockRef land_rhs;
		LLVMBasicBlockRef land_end;
		struct cl2llvm_val_t *op1, *op2;
		
		/* If one value is a vector */
		if (LLVMGetTypeKind((yyvsp[-2].llvm_value_ref)->type->llvm_type) == LLVMVectorTypeKind
			|| LLVMGetTypeKind((yyvsp[0].llvm_value_ref)->type->llvm_type) == LLVMVectorTypeKind)
		{
			type = cl2llvm_type_create();
			
			type_unify((yyvsp[-2].llvm_value_ref), (yyvsp[0].llvm_value_ref), &op1, &op2);
			
			if(op1 == (yyvsp[-2].llvm_value_ref))
			{
				type->llvm_type = op1->type->llvm_type;
				type->sign = op1->type->sign;
			}
			else
			{
				type->llvm_type = op2->type->llvm_type;
				type->sign = op2->type->sign;
			}

			/* Convert to bool */
			bool1 = cl2llvm_to_bool_ne_0(op1);
			bool2 = cl2llvm_to_bool_ne_0(op2);

			snprintf(temp_var_name, sizeof temp_var_name,
				"tmp_%d", temp_var_count++);
			
			/* Compare vectors */
			land_cond = cl2llvm_val_create_w_init(LLVMBuildAnd(
				cl2llvm_builder, bool1->val, bool2->val, temp_var_name), 0);
			
			/* Sign extend vector */
			value = cl2llvm_bool_ext(land_cond, type);
		
			/* Free pointers */
			cl2llvm_type_free(type);
			if ((yyvsp[-2].llvm_value_ref) != op1)
				cl2llvm_val_free(op1);
		else if ((yyvsp[0].llvm_value_ref) != op2)
				cl2llvm_val_free(op2);

		}
		/* If neither value is a vector */
		else
		{
			/* Create basic blocks */
			land_rhs = LLVMAppendBasicBlock(
				cl2llvm_current_function->func, "land_rhs");
			land_end = LLVMAppendBasicBlock(
				cl2llvm_current_function->func, "land_end");

			/* Convert LHS to boolean value */
			bool1 = cl2llvm_to_bool_ne_0((yyvsp[-2].llvm_value_ref));

			/* Create conditional branch. Branch will skip to end block if LHS
			   is false */
			LLVMBuildCondBr(cl2llvm_builder, bool1->val, land_rhs, land_end);
		
			/* Move builder to RHS block */
			LLVMPositionBuilderAtEnd(cl2llvm_builder, land_rhs);

			/* Convert RHS to Bool */
			bool2 = cl2llvm_to_bool_ne_0((yyvsp[0].llvm_value_ref));

			/* Build branch to end block */
			LLVMBuildBr(cl2llvm_builder, land_end);
			LLVMPositionBuilderAtEnd(cl2llvm_builder, land_end);

			/* Position builder at end block */
		
			/* Build Phi node */
			LLVMValueRef phi_vals[] = {LLVMConstInt(
				LLVMInt1Type(), 0, 0), bool2->val};
			LLVMBasicBlockRef phi_blocks[] = 
				{current_basic_block, land_rhs};
			land_cond = cl2llvm_val_create_w_init(
				LLVMBuildPhi(cl2llvm_builder, 
				LLVMInt1Type(), "land_cond"), 0);
			LLVMAddIncoming(land_cond->val, phi_vals, phi_blocks, 2);
			
			/* sign extend */
			value = cl2llvm_bool_ext(land_cond, (yyvsp[-2].llvm_value_ref)->type);

			/* Set current current basic block */
			current_basic_block = land_end;

		}
		/* Free pointers */
		cl2llvm_val_free((yyvsp[-2].llvm_value_ref));
		cl2llvm_val_free((yyvsp[0].llvm_value_ref));
		cl2llvm_val_free(bool1);
		cl2llvm_val_free(bool2);
		cl2llvm_val_free(land_cond);
	
		(yyval.llvm_value_ref) = value;
	}
#line 4793 "parser.c" /* yacc.c:1646  */
    break;

  case 121:
#line 2682 "parser.y" /* yacc.c:1646  */
    {
		struct cl2llvm_val_t *bool1;
		struct cl2llvm_val_t *bool2;
		struct cl2llvm_val_t *value;
		LLVMBasicBlockRef land_rhs;
		LLVMBasicBlockRef land_end;
		struct cl2llvm_val_t *land_cond;
		struct cl2llvm_type_t *type;
		struct cl2llvm_val_t *op1, *op2;


		
		/* If one value is a vector */
		if (LLVMGetTypeKind((yyvsp[-2].llvm_value_ref)->type->llvm_type) == LLVMVectorTypeKind
			|| LLVMGetTypeKind((yyvsp[0].llvm_value_ref)->type->llvm_type) == LLVMVectorTypeKind)
		{
			type = cl2llvm_type_create();
			
			type_unify((yyvsp[-2].llvm_value_ref), (yyvsp[0].llvm_value_ref), &op1, &op2);
			
			if(op1 == (yyvsp[-2].llvm_value_ref))
			{
				type->llvm_type = op1->type->llvm_type;
				type->sign = op1->type->sign;
			}
			else
			{
				type->llvm_type = op2->type->llvm_type;
				type->sign = op2->type->sign;
			}

			/* Convert to bool */
			bool1 = cl2llvm_to_bool_ne_0(op1);
			bool2 = cl2llvm_to_bool_ne_0(op2);

			snprintf(temp_var_name, sizeof temp_var_name,
				"tmp_%d", temp_var_count++);
			
			/* Compare vectors */
			land_cond = cl2llvm_val_create_w_init(LLVMBuildOr(
				cl2llvm_builder, bool1->val, bool2->val, temp_var_name), 0);
			
			/* Sign extend vector */
			value = cl2llvm_bool_ext(land_cond, type);
		
			/* Free pointers */
			cl2llvm_type_free(type);
			if ((yyvsp[-2].llvm_value_ref) != op1)
				cl2llvm_val_free(op1);
		else if ((yyvsp[0].llvm_value_ref) != op2)
				cl2llvm_val_free(op2);

		}
		/* If neither value is a vector */
		else
		{
			/* Create basic blocks */
			land_rhs = LLVMAppendBasicBlock(cl2llvm_current_function->func, "land_rhs");
			land_end = LLVMAppendBasicBlock(cl2llvm_current_function->func, "land_end");

			/* Convert LHS to boolean value */
			bool1 = cl2llvm_to_bool_ne_0((yyvsp[-2].llvm_value_ref));

			/* Create conditional branch. Branch will skip to end block if LHS
			   is true */
			LLVMBuildCondBr(cl2llvm_builder, bool1->val, land_end, land_rhs);
		
			/* Move builder to RHS block */
			LLVMPositionBuilderAtEnd(cl2llvm_builder, land_rhs);

			/* Convert RHS to Bool */
			bool2 = cl2llvm_to_bool_ne_0((yyvsp[0].llvm_value_ref));

			/* Build branch to end block */
			LLVMBuildBr(cl2llvm_builder, land_end);
	
			/* Position builder at end block */
			LLVMPositionBuilderAtEnd(cl2llvm_builder, land_end);
		
			/* Build Phi node */
			LLVMValueRef phi_vals[] = {LLVMConstInt(LLVMInt1Type(), 1, 0), bool2->val};
			LLVMBasicBlockRef phi_blocks[] = {current_basic_block, land_rhs};
			land_cond = cl2llvm_val_create_w_init(LLVMBuildPhi(
				cl2llvm_builder, LLVMInt1Type(), "land_cond"), 0);
			LLVMAddIncoming(land_cond->val, phi_vals, phi_blocks, 2);

			/* Set current current basic block */
			current_basic_block = land_end;

			value = cl2llvm_val_create_w_init(land_cond->val, 1);
		}
		/* Free pointers */
		cl2llvm_val_free((yyvsp[-2].llvm_value_ref));
		cl2llvm_val_free((yyvsp[0].llvm_value_ref));
		cl2llvm_val_free(bool1);
		cl2llvm_val_free(bool2);
		cl2llvm_val_free(land_cond);

		(yyval.llvm_value_ref) = value;
	}
#line 4898 "parser.c" /* yacc.c:1646  */
    break;

  case 122:
#line 2783 "parser.y" /* yacc.c:1646  */
    {
		struct cl2llvm_val_t *value;
		struct cl2llvm_type_t *type; 
		
		type = cl2llvm_type_create_w_init(LLVMGetElementType((yyvsp[-2].llvm_value_ref)->type->llvm_type) , (yyvsp[-2].llvm_value_ref)->type->sign);

		/* If lvalue is a component referenced vector. */
		if ((yyvsp[-2].llvm_value_ref)->vector_indices[0])
		{
			value = cl2llvm_build_component_wise_assignment((yyvsp[-2].llvm_value_ref), (yyvsp[0].llvm_value_ref));
		}
		else
		{
			/*Cast rvalue to type of lvalue and store*/
			value = llvm_type_cast((yyvsp[0].llvm_value_ref), type);
			LLVMBuildStore(cl2llvm_builder, value->val, (yyvsp[-2].llvm_value_ref)->val);
		}

		/*Free pointers*/
		cl2llvm_type_free(type);
		cl2llvm_val_free((yyvsp[-2].llvm_value_ref));
		cl2llvm_val_free((yyvsp[0].llvm_value_ref));

		(yyval.llvm_value_ref) = value;
	}
#line 4928 "parser.c" /* yacc.c:1646  */
    break;

  case 123:
#line 2809 "parser.y" /* yacc.c:1646  */
    {
		struct cl2llvm_type_t *switch_type;
		struct cl2llvm_val_t *value;
		struct cl2llvm_type_t *type = cl2llvm_type_create();
		struct cl2llvm_val_t *op1, *op2;
		struct cl2llvm_val_t *lval;
		struct cl2llvm_val_t *rval;

		/* Load lval */
		snprintf(temp_var_name, sizeof temp_var_name,
			"tmp_%d", temp_var_count++);
		lval = cl2llvm_val_create_w_init(
			LLVMBuildLoad(cl2llvm_builder, (yyvsp[-2].llvm_value_ref)->val, temp_var_name),
			(yyvsp[-2].llvm_value_ref)->type->sign);

		/* Find out which value differs from the original and set the
		   dominant type equal to the type of that value. */
		type_unify(lval, (yyvsp[0].llvm_value_ref), &op1, &op2);
		
		if(op1 == lval)
		{
			type->llvm_type = op1->type->llvm_type;
			type->sign = op1->type->sign;
		}
		else
		{
			type->llvm_type = op2->type->llvm_type;
			type->sign = op2->type->sign;
		}

		/* Create an object that will hold the type of the operands.
		   This extra object is necessary since in the case of a vector 
		   type, we are concerned with the type of its components, but the
		   resultant type of the operation is a vector. */
		switch_type = cl2llvm_type_create_w_init(type->llvm_type, type->sign);
		if (LLVMGetTypeKind(type->llvm_type) == LLVMVectorTypeKind)
		{
			switch_type->llvm_type = LLVMGetElementType(type->llvm_type);
		}

		snprintf(temp_var_name, sizeof temp_var_name,
				"tmp_%d", temp_var_count++);
		
		rval = cl2llvm_val_create();

		/* Determine which type of addition to use based on type of
		   operators. */
		switch (LLVMGetTypeKind(switch_type->llvm_type))
		{
		case LLVMIntegerTypeKind:

			rval->val = LLVMBuildAdd(cl2llvm_builder, op1->val, op2->val, temp_var_name);
			rval->type->sign = type->sign;
			rval->type->llvm_type = type->llvm_type;
			break;

		case LLVMHalfTypeKind:
		case LLVMFloatTypeKind:
		case LLVMDoubleTypeKind:

			rval->val = LLVMBuildFAdd(cl2llvm_builder, op1->val, op2->val, temp_var_name);
			rval->type->sign = type->sign;
			rval->type->llvm_type = type->llvm_type;
			break;

		default:

			yyerror("invalid type of operands for addition");
		}

		/* Cast result to type of lvalue and store */
		value = llvm_type_cast(rval, lval->type);
		
		LLVMBuildStore(cl2llvm_builder, value->val, (yyvsp[-2].llvm_value_ref)->val);

		/* Free pointers */
		if (lval != op1)
			cl2llvm_val_free(op1);
		else if ((yyvsp[0].llvm_value_ref) != op2)
			cl2llvm_val_free( op2);
		cl2llvm_val_free((yyvsp[0].llvm_value_ref));
		cl2llvm_val_free((yyvsp[-2].llvm_value_ref));
		cl2llvm_val_free(lval);
		cl2llvm_val_free(rval);
		cl2llvm_type_free(type);
		cl2llvm_type_free(switch_type);

		(yyval.llvm_value_ref) = value;

	}
#line 5023 "parser.c" /* yacc.c:1646  */
    break;

  case 124:
#line 2900 "parser.y" /* yacc.c:1646  */
    {
		struct cl2llvm_type_t *switch_type;
		struct cl2llvm_val_t *value;
		struct cl2llvm_type_t *type = cl2llvm_type_create();
		struct cl2llvm_val_t *op1, *op2;
		struct cl2llvm_val_t *lval;
		struct cl2llvm_val_t *rval;

		/* Load lval */
		snprintf(temp_var_name, sizeof temp_var_name,
			"tmp_%d", temp_var_count++);
		lval = cl2llvm_val_create_w_init(
			LLVMBuildLoad(cl2llvm_builder, (yyvsp[-2].llvm_value_ref)->val, temp_var_name),
			(yyvsp[-2].llvm_value_ref)->type->sign);

		/* Find out which value differs from the original and set the
		   dominant type equal to the type of that value. */
		type_unify(lval, (yyvsp[0].llvm_value_ref), &op1, &op2);
		
		if(op1 == lval)
		{
			type->llvm_type = op1->type->llvm_type;
			type->sign = op1->type->sign;
		}
		else
		{
			type->llvm_type = op2->type->llvm_type;
			type->sign = op2->type->sign;
		}

		/* Create an object that will hold the type of the operands.
		   This extra object is necessary since in the case of a vector 
		   type, we are concerned with the type of its components, but the
		   resultant type of the operation is a vector. */
		switch_type = cl2llvm_type_create_w_init(type->llvm_type, type->sign);
		if (LLVMGetTypeKind(type->llvm_type) == LLVMVectorTypeKind)
		{
			switch_type->llvm_type = LLVMGetElementType(type->llvm_type);
		}

		snprintf(temp_var_name, sizeof temp_var_name,
				"tmp_%d", temp_var_count++);
		
		rval = cl2llvm_val_create();

		/* Determine which type of addition to use based on type of
		   operators. */
		switch (LLVMGetTypeKind(switch_type->llvm_type))
		{
		case LLVMIntegerTypeKind:

			rval->val = LLVMBuildSub(cl2llvm_builder, op1->val, op2->val, temp_var_name);
			rval->type->sign = type->sign;
			rval->type->llvm_type = type->llvm_type;
			break;

		case LLVMHalfTypeKind:
		case LLVMFloatTypeKind:
		case LLVMDoubleTypeKind:

			rval->val = LLVMBuildFSub(cl2llvm_builder, op1->val, op2->val, temp_var_name);
			rval->type->sign = type->sign;
			rval->type->llvm_type = type->llvm_type;
			break;

		default:

			yyerror("invalid type of operands for addition");
		}

		/* Cast result to type of lvalue and store */
		value = llvm_type_cast(rval, lval->type);
		
		LLVMBuildStore(cl2llvm_builder, value->val, (yyvsp[-2].llvm_value_ref)->val);

		/* Free pointers */
		if (lval != op1)
			cl2llvm_val_free(op1);
		else if ((yyvsp[0].llvm_value_ref) != op2)
			cl2llvm_val_free( op2);
		cl2llvm_val_free((yyvsp[0].llvm_value_ref));
		cl2llvm_val_free((yyvsp[-2].llvm_value_ref));
		cl2llvm_val_free(lval);
		cl2llvm_val_free(rval);
		cl2llvm_type_free(type);
		cl2llvm_type_free(switch_type);

		(yyval.llvm_value_ref) = value;

	}
#line 5118 "parser.c" /* yacc.c:1646  */
    break;

  case 125:
#line 2991 "parser.y" /* yacc.c:1646  */
    {
		struct cl2llvm_type_t *switch_type;
		struct cl2llvm_val_t *value;
		struct cl2llvm_type_t *type = cl2llvm_type_create();
		struct cl2llvm_val_t *op1, *op2;
		struct cl2llvm_val_t *lval;
		struct cl2llvm_val_t *rval;

		/* Load lval */
		snprintf(temp_var_name, sizeof temp_var_name,
			"tmp_%d", temp_var_count++);
		lval = cl2llvm_val_create_w_init(
			LLVMBuildLoad(cl2llvm_builder, (yyvsp[-2].llvm_value_ref)->val, temp_var_name),
			(yyvsp[-2].llvm_value_ref)->type->sign);

		/* Find out which value differs from the original and set the
		   dominant type equal to the type of that value. */
		type_unify(lval, (yyvsp[0].llvm_value_ref), &op1, &op2);
		
		if(op1 == lval)
		{
			type->llvm_type = op1->type->llvm_type;
			type->sign = op1->type->sign;
		}
		else
		{
			type->llvm_type = op2->type->llvm_type;
			type->sign = op2->type->sign;
		}

		/* Create an object that will hold the type of the operands.
		   This extra object is necessary since in the case of a vector 
		   type, we are concerned with the type of its components, but the
		   resultant type of the operation is a vector. */
		switch_type = cl2llvm_type_create_w_init(type->llvm_type, type->sign);
		if (LLVMGetTypeKind(type->llvm_type) == LLVMVectorTypeKind)
		{
			switch_type->llvm_type = LLVMGetElementType(type->llvm_type);
		}

		snprintf(temp_var_name, sizeof temp_var_name,
				"tmp_%d", temp_var_count++);
		
		rval = cl2llvm_val_create();

		switch (LLVMGetTypeKind(switch_type->llvm_type))
		{
		case LLVMIntegerTypeKind:
			if (type->sign)
			{
				rval->val = LLVMBuildSDiv(cl2llvm_builder, 
					op1->val, op2->val, temp_var_name);
			}
			else
			{
				rval->val = LLVMBuildUDiv(cl2llvm_builder, 
					op1->val, op2->val, temp_var_name);
			}
			rval->type->sign = type->sign;
			rval->type->llvm_type = type->llvm_type;
			break;

		case LLVMHalfTypeKind:
		case LLVMFloatTypeKind:
		case LLVMDoubleTypeKind:
			rval->val = LLVMBuildFDiv(cl2llvm_builder, 
					op1->val, op2->val, temp_var_name);
			rval->type->sign = type->sign;
			rval->type->llvm_type = type->llvm_type;
			break;

		default:
			
			yyerror("invalid type of operands for '/='");
		}
	
		/* Cast result to type of lvalue and store */
		value = llvm_type_cast(rval, lval->type);
		
		LLVMBuildStore(cl2llvm_builder, value->val, (yyvsp[-2].llvm_value_ref)->val);

		/* Free pointers */
		if (lval != op1)
			cl2llvm_val_free(op1);
		else if ((yyvsp[0].llvm_value_ref) != op2)
			cl2llvm_val_free( op2);
		cl2llvm_val_free((yyvsp[0].llvm_value_ref));
		cl2llvm_val_free((yyvsp[-2].llvm_value_ref));
		cl2llvm_val_free(lval);
		cl2llvm_val_free(rval);
		cl2llvm_type_free(type);
		cl2llvm_type_free(switch_type);

		(yyval.llvm_value_ref) = value;
	}
#line 5218 "parser.c" /* yacc.c:1646  */
    break;

  case 126:
#line 3087 "parser.y" /* yacc.c:1646  */
    {
		struct cl2llvm_type_t *switch_type;
		struct cl2llvm_val_t *value;
		struct cl2llvm_type_t *type = cl2llvm_type_create();
		struct cl2llvm_val_t *op1, *op2;
		struct cl2llvm_val_t *lval;
		struct cl2llvm_val_t *rval;

		/* Load lval */
		snprintf(temp_var_name, sizeof temp_var_name,
			"tmp_%d", temp_var_count++);
		lval = cl2llvm_val_create_w_init(
			LLVMBuildLoad(cl2llvm_builder, (yyvsp[-2].llvm_value_ref)->val, temp_var_name),
			(yyvsp[-2].llvm_value_ref)->type->sign);

		/* Find out which value differs from the original and set the
		   dominant type equal to the type of that value. */
		type_unify(lval, (yyvsp[0].llvm_value_ref), &op1, &op2);
		
		if(op1 == lval)
		{
			type->llvm_type = op1->type->llvm_type;
			type->sign = op1->type->sign;
		}
		else
		{
			type->llvm_type = op2->type->llvm_type;
			type->sign = op2->type->sign;
		}

		/* Create an object that will hold the type of the operands.
		   This extra object is necessary since in the case of a vector 
		   type, we are concerned with the type of its components, but the
		   resultant type of the operation is a vector. */
		switch_type = cl2llvm_type_create_w_init(type->llvm_type, type->sign);
		if (LLVMGetTypeKind(type->llvm_type) == LLVMVectorTypeKind)
		{
			switch_type->llvm_type = LLVMGetElementType(type->llvm_type);
		}

		snprintf(temp_var_name, sizeof temp_var_name,
				"tmp_%d", temp_var_count++);
		
		rval = cl2llvm_val_create();

		switch (LLVMGetTypeKind(switch_type->llvm_type))
		{
		case LLVMIntegerTypeKind:
			rval->val = LLVMBuildMul(cl2llvm_builder, 
				op1->val, op2->val, temp_var_name);
			rval->type->sign = type->sign;
			rval->type->llvm_type = type->llvm_type;
			break;

		case LLVMHalfTypeKind:
		case LLVMFloatTypeKind:
		case LLVMDoubleTypeKind:
			rval->val = LLVMBuildFMul(cl2llvm_builder, 
					op1->val, op2->val, temp_var_name);
			rval->type->sign = type->sign;
			rval->type->llvm_type = type->llvm_type;
			break;

		default:
			
			yyerror("invalid type of operands for '/='");
		}


		/* Cast result to type of lvalue and store */
		value = llvm_type_cast(rval, lval->type);
		
		LLVMBuildStore(cl2llvm_builder, value->val, (yyvsp[-2].llvm_value_ref)->val);

		/* Free pointers */
		if (lval != op1)
			cl2llvm_val_free(op1);
		else if ((yyvsp[0].llvm_value_ref) != op2)
			cl2llvm_val_free( op2);
		cl2llvm_val_free((yyvsp[0].llvm_value_ref));
		cl2llvm_val_free((yyvsp[-2].llvm_value_ref));
		cl2llvm_val_free(lval);
		cl2llvm_val_free(rval);
		cl2llvm_type_free(type);
		cl2llvm_type_free(switch_type);

		(yyval.llvm_value_ref) = value;




	}
#line 5315 "parser.c" /* yacc.c:1646  */
    break;

  case 127:
#line 3180 "parser.y" /* yacc.c:1646  */
    {
		struct cl2llvm_type_t *switch_type;
		struct cl2llvm_val_t *value;
		struct cl2llvm_type_t *type = cl2llvm_type_create();
		struct cl2llvm_val_t *op1, *op2;
		struct cl2llvm_val_t *lval;
		struct cl2llvm_val_t *rval;

		/* Load lval */
		snprintf(temp_var_name, sizeof temp_var_name,
			"tmp_%d", temp_var_count++);
		lval = cl2llvm_val_create_w_init(
			LLVMBuildLoad(cl2llvm_builder, (yyvsp[-2].llvm_value_ref)->val, temp_var_name),
			(yyvsp[-2].llvm_value_ref)->type->sign);

		/* Find out which value differs from the original and set the
		   dominant type equal to the type of that value. */
		type_unify(lval, (yyvsp[0].llvm_value_ref), &op1, &op2);
		
		if(op1 == lval)
		{
			type->llvm_type = op1->type->llvm_type;
			type->sign = op1->type->sign;
		}
		else
		{
			type->llvm_type = op2->type->llvm_type;
			type->sign = op2->type->sign;
		}

		/* Create an object that will hold the type of the operands.
		   This extra object is necessary since in the case of a vector 
		   type, we are concerned with the type of its components, but the
		   resultant type of the operation is a vector. */
		switch_type = cl2llvm_type_create_w_init(type->llvm_type, type->sign);
		if (LLVMGetTypeKind(type->llvm_type) == LLVMVectorTypeKind)
		{
			switch_type->llvm_type = LLVMGetElementType(type->llvm_type);
		}

		snprintf(temp_var_name, sizeof temp_var_name,
				"tmp_%d", temp_var_count++);
		
		rval = cl2llvm_val_create();

		switch (LLVMGetTypeKind(switch_type->llvm_type))
		{
		case LLVMIntegerTypeKind:

			if (type->sign)
			{
				rval->val = LLVMBuildSRem(cl2llvm_builder, 
					op1->val, op2->val, temp_var_name);
			}
			else
			{
				rval->val = LLVMBuildURem(cl2llvm_builder, 
					op1->val, op2->val, temp_var_name);
			}
			rval->type->sign = type->sign;
			rval->type->llvm_type = type->llvm_type;
			break;
		
		default:
			
			yyerror("invalid type of operands for '%='");
		}

		/* Cast result to type of lvalue and store */
		value = llvm_type_cast(rval, lval->type);
		
		LLVMBuildStore(cl2llvm_builder, value->val, (yyvsp[-2].llvm_value_ref)->val);

		/* Free pointers */
		if (lval != op1)
			cl2llvm_val_free(op1);
		else if ((yyvsp[0].llvm_value_ref) != op2)
			cl2llvm_val_free( op2);
		cl2llvm_val_free((yyvsp[0].llvm_value_ref));
		cl2llvm_val_free((yyvsp[-2].llvm_value_ref));
		cl2llvm_val_free(lval);
		cl2llvm_val_free(rval);
		cl2llvm_type_free(type);
		cl2llvm_type_free(switch_type);

		(yyval.llvm_value_ref) = value;
	}
#line 5407 "parser.c" /* yacc.c:1646  */
    break;

  case 128:
#line 3268 "parser.y" /* yacc.c:1646  */
    {
		struct cl2llvm_type_t *switch_type;
		struct cl2llvm_val_t *value;
		struct cl2llvm_type_t *type = cl2llvm_type_create();
		struct cl2llvm_val_t *op1, *op2;
		struct cl2llvm_val_t *lval;
		struct cl2llvm_val_t *rval;

		/* Load lval */
		snprintf(temp_var_name, sizeof temp_var_name,
			"tmp_%d", temp_var_count++);
		lval = cl2llvm_val_create_w_init(
			LLVMBuildLoad(cl2llvm_builder, (yyvsp[-2].llvm_value_ref)->val, temp_var_name),
			(yyvsp[-2].llvm_value_ref)->type->sign);
 
		/* Find out which value differs from the original and set the
		   dominant type equal to the type of that value. */
		type_unify(lval, (yyvsp[0].llvm_value_ref), &op1, &op2);
		if(op1 == lval)
		{
			type->llvm_type = op1->type->llvm_type;
			type->sign = op1->type->sign;
		}
		else
		{
			type->llvm_type = op2->type->llvm_type;
			type->sign = op2->type->sign;
		}

		/* Create an object that will hold the type of the operands.
		   This extra object is necessary since in the case of a vector 
		   type, we are concerned with the type of its components, but the
		   resultant type of the operation is a vector. */
		switch_type = cl2llvm_type_create_w_init(type->llvm_type, type->sign);
		if (LLVMGetTypeKind(type->llvm_type) == LLVMVectorTypeKind)
		{
			switch_type->llvm_type = LLVMGetElementType(type->llvm_type);
		}

		snprintf(temp_var_name, sizeof temp_var_name,
				"tmp_%d", temp_var_count++);
		
		rval = cl2llvm_val_create();

		/* Determine which type of addition to use based on type of
		   operators. */
		switch (LLVMGetTypeKind(switch_type->llvm_type))
		{
		case LLVMIntegerTypeKind:

			rval->val = LLVMBuildAnd(cl2llvm_builder, op1->val, op2->val, temp_var_name);
			rval->type->sign = type->sign;
			rval->type->llvm_type = type->llvm_type;
			break;


		default:

			yyerror("invalid type of operands for binary '&'.");
		}

		/* Cast result to type of lvalue and store */
		value = llvm_type_cast(rval, lval->type);
		
		LLVMBuildStore(cl2llvm_builder, value->val, (yyvsp[-2].llvm_value_ref)->val);

		/* Free pointers */
		if (lval != op1)
			cl2llvm_val_free(op1);
		else if ((yyvsp[0].llvm_value_ref) != op2)
			cl2llvm_val_free( op2);
		cl2llvm_val_free((yyvsp[0].llvm_value_ref));
		cl2llvm_val_free((yyvsp[-2].llvm_value_ref));
		cl2llvm_val_free(lval);
		cl2llvm_val_free(rval);
		cl2llvm_type_free(type);
		cl2llvm_type_free(switch_type);

		(yyval.llvm_value_ref) = value;

	}
#line 5493 "parser.c" /* yacc.c:1646  */
    break;

  case 129:
#line 3350 "parser.y" /* yacc.c:1646  */
    {
		struct cl2llvm_type_t *switch_type;
		struct cl2llvm_val_t *value;
		struct cl2llvm_type_t *type = cl2llvm_type_create();
		struct cl2llvm_val_t *op1, *op2;
		struct cl2llvm_val_t *lval;
		struct cl2llvm_val_t *rval;

		/* Load lval */
		snprintf(temp_var_name, sizeof temp_var_name,
			"tmp_%d", temp_var_count++);
		lval = cl2llvm_val_create_w_init(
			LLVMBuildLoad(cl2llvm_builder, (yyvsp[-2].llvm_value_ref)->val, temp_var_name),
			(yyvsp[-2].llvm_value_ref)->type->sign);
 
		/* Find out which value differs from the original and set the
		   dominant type equal to the type of that value. */
		type_unify(lval, (yyvsp[0].llvm_value_ref), &op1, &op2);
		if(op1 == lval)
		{
			type->llvm_type = op1->type->llvm_type;
			type->sign = op1->type->sign;
		}
		else
		{
			type->llvm_type = op2->type->llvm_type;
			type->sign = op2->type->sign;
		}

		/* Create an object that will hold the type of the operands.
		   This extra object is necessary since in the case of a vector 
		   type, we are concerned with the type of its components, but the
		   resultant type of the operation is a vector. */
		switch_type = cl2llvm_type_create_w_init(type->llvm_type, type->sign);
		if (LLVMGetTypeKind(type->llvm_type) == LLVMVectorTypeKind)
		{
			switch_type->llvm_type = LLVMGetElementType(type->llvm_type);
		}

		snprintf(temp_var_name, sizeof temp_var_name,
				"tmp_%d", temp_var_count++);
		
		rval = cl2llvm_val_create();

		/* Determine which type of addition to use based on type of
		   operators. */
		switch (LLVMGetTypeKind(switch_type->llvm_type))
		{
		case LLVMIntegerTypeKind:

			rval->val = LLVMBuildOr(cl2llvm_builder, op1->val, op2->val, temp_var_name);
			rval->type->sign = type->sign;
			rval->type->llvm_type = type->llvm_type;
			break;


		default:

			yyerror("invalid type of operands for '|='.");
		}

		/* Cast result to type of lvalue and store */
		value = llvm_type_cast(rval, lval->type);
		
		LLVMBuildStore(cl2llvm_builder, value->val, (yyvsp[-2].llvm_value_ref)->val);

		/* Free pointers */
		if (lval != op1)
			cl2llvm_val_free(op1);
		else if ((yyvsp[0].llvm_value_ref) != op2)
			cl2llvm_val_free( op2);
		cl2llvm_val_free((yyvsp[0].llvm_value_ref));
		cl2llvm_val_free((yyvsp[-2].llvm_value_ref));
		cl2llvm_val_free(lval);
		cl2llvm_val_free(rval);
		cl2llvm_type_free(type);
		cl2llvm_type_free(switch_type);

		(yyval.llvm_value_ref) = value;

	}
#line 5579 "parser.c" /* yacc.c:1646  */
    break;

  case 130:
#line 3432 "parser.y" /* yacc.c:1646  */
    {
		struct cl2llvm_type_t *switch_type;
		struct cl2llvm_val_t *value;
		struct cl2llvm_type_t *type = cl2llvm_type_create();
		struct cl2llvm_val_t *op1, *op2;
		struct cl2llvm_val_t *lval;
		struct cl2llvm_val_t *rval;

		/* Load lval */
		snprintf(temp_var_name, sizeof temp_var_name,
			"tmp_%d", temp_var_count++);
		lval = cl2llvm_val_create_w_init(
			LLVMBuildLoad(cl2llvm_builder, (yyvsp[-2].llvm_value_ref)->val, temp_var_name),
			(yyvsp[-2].llvm_value_ref)->type->sign);
 
		/* Find out which value differs from the original and set the
		   dominant type equal to the type of that value. */
		type_unify(lval, (yyvsp[0].llvm_value_ref), &op1, &op2);
		if(op1 == lval)
		{
			type->llvm_type = op1->type->llvm_type;
			type->sign = op1->type->sign;
		}
		else
		{
			type->llvm_type = op2->type->llvm_type;
			type->sign = op2->type->sign;
		}

		/* Create an object that will hold the type of the operands.
		   This extra object is necessary since in the case of a vector 
		   type, we are concerned with the type of its components, but the
		   resultant type of the operation is a vector. */
		switch_type = cl2llvm_type_create_w_init(type->llvm_type, type->sign);
		if (LLVMGetTypeKind(type->llvm_type) == LLVMVectorTypeKind)
		{
			switch_type->llvm_type = LLVMGetElementType(type->llvm_type);
		}

		snprintf(temp_var_name, sizeof temp_var_name,
				"tmp_%d", temp_var_count++);
		
		rval = cl2llvm_val_create();

		/* Determine which type of addition to use based on type of
		   operators. */
		switch (LLVMGetTypeKind(switch_type->llvm_type))
		{
		case LLVMIntegerTypeKind:

			rval->val = LLVMBuildXor(cl2llvm_builder, op1->val, op2->val, temp_var_name);
			rval->type->sign = type->sign;
			rval->type->llvm_type = type->llvm_type;
			break;


		default:

			yyerror("invalid type of operands for binary '^='.");
		}

		/* Cast result to type of lvalue and store */
		value = llvm_type_cast(rval, lval->type);
		
		LLVMBuildStore(cl2llvm_builder, value->val, (yyvsp[-2].llvm_value_ref)->val);

		/* Free pointers */
		if (lval != op1)
			cl2llvm_val_free(op1);
		else if ((yyvsp[0].llvm_value_ref) != op2)
			cl2llvm_val_free( op2);
		cl2llvm_val_free((yyvsp[0].llvm_value_ref));
		cl2llvm_val_free((yyvsp[-2].llvm_value_ref));
		cl2llvm_val_free(lval);
		cl2llvm_val_free(rval);
		cl2llvm_type_free(type);
		cl2llvm_type_free(switch_type);

		(yyval.llvm_value_ref) = value;

	}
#line 5665 "parser.c" /* yacc.c:1646  */
    break;

  case 131:
#line 3514 "parser.y" /* yacc.c:1646  */
    {
		struct cl2llvm_type_t *switch_type;
		struct cl2llvm_val_t *value;
		struct cl2llvm_type_t *type = cl2llvm_type_create();
		struct cl2llvm_val_t *op1, *op2;
		struct cl2llvm_val_t *lval;
		struct cl2llvm_val_t *rval;

		/* Load lval */
		snprintf(temp_var_name, sizeof temp_var_name,
			"tmp_%d", temp_var_count++);
		lval = cl2llvm_val_create_w_init(
			LLVMBuildLoad(cl2llvm_builder, (yyvsp[-2].llvm_value_ref)->val, temp_var_name),
			(yyvsp[-2].llvm_value_ref)->type->sign);
 
		/* Find out which value differs from the original and set the
		   dominant type equal to the type of that value. */
		type_unify(lval, (yyvsp[0].llvm_value_ref), &op1, &op2);
		if(op1 == lval)
		{
			type->llvm_type = op1->type->llvm_type;
			type->sign = op1->type->sign;
		}
		else
		{
			type->llvm_type = op2->type->llvm_type;
			type->sign = op2->type->sign;
		}

		/* Create an object that will hold the type of the operands.
		   This extra object is necessary since in the case of a vector 
		   type, we are concerned with the type of its components, but the
		   resultant type of the operation is a vector. */
		switch_type = cl2llvm_type_create_w_init(type->llvm_type, type->sign);
		if (LLVMGetTypeKind(type->llvm_type) == LLVMVectorTypeKind)
		{
			switch_type->llvm_type = LLVMGetElementType(type->llvm_type);
		}

		snprintf(temp_var_name, sizeof temp_var_name,
				"tmp_%d", temp_var_count++);
		
		rval = cl2llvm_val_create();

		/* Determine which type of addition to use based on type of
		   operators. */
		switch (LLVMGetTypeKind(switch_type->llvm_type))
		{
		case LLVMIntegerTypeKind:

			rval->val = LLVMBuildAShr(cl2llvm_builder, op1->val, op2->val, temp_var_name);
			rval->type->sign = type->sign;
			rval->type->llvm_type = type->llvm_type;
			break;


		default:

			yyerror("invalid type of operands for '>>='.");
		}

		/* Cast result to type of lvalue and store */
		value = llvm_type_cast(rval, lval->type);
		
		LLVMBuildStore(cl2llvm_builder, value->val, (yyvsp[-2].llvm_value_ref)->val);

		/* Free pointers */
		if (lval != op1)
			cl2llvm_val_free(op1);
		else if ((yyvsp[0].llvm_value_ref) != op2)
			cl2llvm_val_free( op2);
		cl2llvm_val_free((yyvsp[0].llvm_value_ref));
		cl2llvm_val_free((yyvsp[-2].llvm_value_ref));
		cl2llvm_val_free(lval);
		cl2llvm_val_free(rval);
		cl2llvm_type_free(type);
		cl2llvm_type_free(switch_type);

		(yyval.llvm_value_ref) = value;


	}
#line 5752 "parser.c" /* yacc.c:1646  */
    break;

  case 132:
#line 3597 "parser.y" /* yacc.c:1646  */
    {
		struct cl2llvm_type_t *switch_type;
		struct cl2llvm_val_t *value;
		struct cl2llvm_type_t *type = cl2llvm_type_create();
		struct cl2llvm_val_t *op1, *op2;
		struct cl2llvm_val_t *lval;
		struct cl2llvm_val_t *rval;

		/* Load lval */
		snprintf(temp_var_name, sizeof temp_var_name,
			"tmp_%d", temp_var_count++);
		lval = cl2llvm_val_create_w_init(
			LLVMBuildLoad(cl2llvm_builder, (yyvsp[-2].llvm_value_ref)->val, temp_var_name),
			(yyvsp[-2].llvm_value_ref)->type->sign);
 
		/* Find out which value differs from the original and set the
		   dominant type equal to the type of that value. */
		type_unify(lval, (yyvsp[0].llvm_value_ref), &op1, &op2);
		if(op1 == lval)
		{
			type->llvm_type = op1->type->llvm_type;
			type->sign = op1->type->sign;
		}
		else
		{
			type->llvm_type = op2->type->llvm_type;
			type->sign = op2->type->sign;
		}

		/* Create an object that will hold the type of the operands.
		   This extra object is necessary since in the case of a vector 
		   type, we are concerned with the type of its components, but the
		   resultant type of the operation is a vector. */
		switch_type = cl2llvm_type_create_w_init(type->llvm_type, type->sign);
		if (LLVMGetTypeKind(type->llvm_type) == LLVMVectorTypeKind)
		{
			switch_type->llvm_type = LLVMGetElementType(type->llvm_type);
		}

		snprintf(temp_var_name, sizeof temp_var_name,
				"tmp_%d", temp_var_count++);
		
		rval = cl2llvm_val_create();

		/* Determine which type of addition to use based on type of
		   operators. */
		switch (LLVMGetTypeKind(switch_type->llvm_type))
		{
		case LLVMIntegerTypeKind:

			rval->val = LLVMBuildShl(cl2llvm_builder, op1->val, op2->val, temp_var_name);
			rval->type->sign = type->sign;
			rval->type->llvm_type = type->llvm_type;
			break;


		default:

			yyerror("invalid type of operands for '<<='.");
		}

		/* Cast result to type of lvalue and store */
		value = llvm_type_cast(rval, lval->type);
		
		LLVMBuildStore(cl2llvm_builder, value->val, (yyvsp[-2].llvm_value_ref)->val);

		/* Free pointers */
		if (lval != op1)
			cl2llvm_val_free(op1);
		else if ((yyvsp[0].llvm_value_ref) != op2)
			cl2llvm_val_free( op2);
		cl2llvm_val_free((yyvsp[0].llvm_value_ref));
		cl2llvm_val_free((yyvsp[-2].llvm_value_ref));
		cl2llvm_val_free(lval);
		cl2llvm_val_free(rval);
		cl2llvm_type_free(type);
		cl2llvm_type_free(switch_type);

		(yyval.llvm_value_ref) = value;

	}
#line 5838 "parser.c" /* yacc.c:1646  */
    break;

  case 133:
#line 3679 "parser.y" /* yacc.c:1646  */
    {
		cl2llvm_yyerror("a'?'b':'c not supported");
	}
#line 5846 "parser.c" /* yacc.c:1646  */
    break;

  case 134:
#line 3683 "parser.y" /* yacc.c:1646  */
    {
		(yyval.llvm_value_ref) = (yyvsp[0].llvm_value_ref);
	}
#line 5854 "parser.c" /* yacc.c:1646  */
    break;

  case 135:
#line 3688 "parser.y" /* yacc.c:1646  */
    {
		(yyval.llvm_value_ref) = (yyvsp[0].llvm_value_ref);
	}
#line 5862 "parser.c" /* yacc.c:1646  */
    break;

  case 136:
#line 3693 "parser.y" /* yacc.c:1646  */
    {
		struct cl2llvm_val_t *value;
		struct cl2llvm_val_t *bool_val;
		
		/* Convert $2 to bool */
		bool_val = cl2llvm_to_bool_eq_0((yyvsp[0].llvm_value_ref));

		/* Convert bool back to type of $2 */
		value = cl2llvm_bool_ext(bool_val, (yyvsp[0].llvm_value_ref)->type);

		/* Free pointers */
		cl2llvm_val_free((yyvsp[0].llvm_value_ref));
		cl2llvm_val_free(bool_val);

		(yyval.llvm_value_ref) = value;
	}
#line 5883 "parser.c" /* yacc.c:1646  */
    break;

  case 137:
#line 3710 "parser.y" /* yacc.c:1646  */
    {
		struct cl2llvm_type_t *switch_type;
		struct cl2llvm_type_t *type;
		struct cl2llvm_val_t *value;
		
		type = cl2llvm_type_create();
		value = cl2llvm_val_create();

		snprintf(temp_var_name, sizeof temp_var_name,
			"tmp_%d", temp_var_count++);

		struct cl2llvm_val_t *op1, *op2;
		
		type_unify((yyvsp[-2].llvm_value_ref), (yyvsp[0].llvm_value_ref), &op1, & op2);
		if(op1 == (yyvsp[-2].llvm_value_ref))
		{
			type->llvm_type = LLVMTypeOf(op1->val);
			type->sign = op1->type->sign;
		}
		else
		{
			type->llvm_type = LLVMTypeOf(op1->val);
			type->sign = op1->type->sign;
		}

		/* Create an object that will hold the type of the operands.
		   This extra object is necessary since in the case of a vector 
		   type, we are concerned with the type of its components, but the
		   resultant type of the operation is a vector. */
		switch_type = cl2llvm_type_create_w_init(type->llvm_type, type->sign);
		if (LLVMGetTypeKind(type->llvm_type) == LLVMVectorTypeKind)
		{
			switch_type->llvm_type = LLVMGetElementType(type->llvm_type);
		}

		switch (LLVMGetTypeKind(switch_type->llvm_type))
		{
		case LLVMIntegerTypeKind:
			value->val = LLVMBuildAnd(cl2llvm_builder, 
				op1->val, op2->val, temp_var_name);
			value->type->sign = type->sign;
			value->type->llvm_type = type->llvm_type;
			break;


		default:
			
			yyerror("Invalid type of operands for binary '&'.");
		}

		/* Free pointers */
		if ((yyvsp[-2].llvm_value_ref) != op1)
			cl2llvm_val_free(op1);
		else if ((yyvsp[0].llvm_value_ref) != op2)
			cl2llvm_val_free(op2);
		cl2llvm_val_free((yyvsp[-2].llvm_value_ref));
		cl2llvm_val_free((yyvsp[0].llvm_value_ref));
		cl2llvm_type_free(type);
		cl2llvm_type_free(switch_type);

		(yyval.llvm_value_ref) = value;
		
	}
#line 5951 "parser.c" /* yacc.c:1646  */
    break;

  case 138:
#line 3774 "parser.y" /* yacc.c:1646  */
    {
		struct cl2llvm_type_t *switch_type;
		struct cl2llvm_type_t *type;
		struct cl2llvm_val_t *value;
		
		type = cl2llvm_type_create();
		value = cl2llvm_val_create();

		snprintf(temp_var_name, sizeof temp_var_name,
			"tmp_%d", temp_var_count++);

		struct cl2llvm_val_t *op1, *op2;
		
		type_unify((yyvsp[-2].llvm_value_ref), (yyvsp[0].llvm_value_ref), &op1, & op2);
		if(op1 == (yyvsp[-2].llvm_value_ref))
		{
			type->llvm_type = LLVMTypeOf(op1->val);
			type->sign = op1->type->sign;
		}
		else
		{
			type->llvm_type = LLVMTypeOf(op1->val);
			type->sign = op1->type->sign;
		}

		/* Create an object that will hold the type of the operands.
		   This extra object is necessary since in the case of a vector 
		   type, we are concerned with the type of its components, but the
		   resultant type of the operation is a vector. */
		switch_type = cl2llvm_type_create_w_init(type->llvm_type, type->sign);
		if (LLVMGetTypeKind(type->llvm_type) == LLVMVectorTypeKind)
		{
			switch_type->llvm_type = LLVMGetElementType(type->llvm_type);
		}

		switch (LLVMGetTypeKind(switch_type->llvm_type))
		{
		case LLVMIntegerTypeKind:
			value->val = LLVMBuildOr(cl2llvm_builder, 
				op1->val, op2->val, temp_var_name);
			value->type->sign = type->sign;
			value->type->llvm_type = type->llvm_type;
			break;


		default:
			
			yyerror("Invalid type of operands for '|'.");
		}

		/* Free pointers */
		if ((yyvsp[-2].llvm_value_ref) != op1)
			cl2llvm_val_free(op1);
		else if ((yyvsp[0].llvm_value_ref) != op2)
			cl2llvm_val_free(op2);
		cl2llvm_val_free((yyvsp[-2].llvm_value_ref));
		cl2llvm_val_free((yyvsp[0].llvm_value_ref));
		cl2llvm_type_free(type);
		cl2llvm_type_free(switch_type);

		(yyval.llvm_value_ref) = value;

	}
#line 6019 "parser.c" /* yacc.c:1646  */
    break;

  case 139:
#line 3838 "parser.y" /* yacc.c:1646  */
    {
		struct cl2llvm_type_t *switch_type;
		struct cl2llvm_type_t *type;
		struct cl2llvm_val_t *value;
		
		type = cl2llvm_type_create();
		value = cl2llvm_val_create();

		snprintf(temp_var_name, sizeof temp_var_name,
			"tmp_%d", temp_var_count++);

		struct cl2llvm_val_t *op1, *op2;
		
		type_unify((yyvsp[-2].llvm_value_ref), (yyvsp[0].llvm_value_ref), &op1, & op2);
		if(op1 == (yyvsp[-2].llvm_value_ref))
		{
			type->llvm_type = LLVMTypeOf(op1->val);
			type->sign = op1->type->sign;
		}
		else
		{
			type->llvm_type = LLVMTypeOf(op1->val);
			type->sign = op1->type->sign;
		}

		/* Create an object that will hold the type of the operands.
		   This extra object is necessary since in the case of a vector 
		   type, we are concerned with the type of its components, but the
		   resultant type of the operation is a vector. */
		switch_type = cl2llvm_type_create_w_init(type->llvm_type, type->sign);
		if (LLVMGetTypeKind(type->llvm_type) == LLVMVectorTypeKind)
		{
			switch_type->llvm_type = LLVMGetElementType(type->llvm_type);
		}

		switch (LLVMGetTypeKind(switch_type->llvm_type))
		{
		case LLVMIntegerTypeKind:
			value->val = LLVMBuildXor(cl2llvm_builder, 
				op1->val, op2->val, temp_var_name);
			value->type->sign = type->sign;
			value->type->llvm_type = type->llvm_type;
			break;


		default:
			
			yyerror("Invalid type of operands for '^'.");
		}

		/* Free pointers */
		if ((yyvsp[-2].llvm_value_ref) != op1)
			cl2llvm_val_free(op1);
		else if ((yyvsp[0].llvm_value_ref) != op2)
			cl2llvm_val_free(op2);
		cl2llvm_val_free((yyvsp[-2].llvm_value_ref));
		cl2llvm_val_free((yyvsp[0].llvm_value_ref));
		cl2llvm_type_free(type);
		cl2llvm_type_free(switch_type);

		(yyval.llvm_value_ref) = value;

	}
#line 6087 "parser.c" /* yacc.c:1646  */
    break;

  case 140:
#line 3906 "parser.y" /* yacc.c:1646  */
    {
		struct cl2llvm_type_t *switch_type;
		struct cl2llvm_type_t *type;
		struct cl2llvm_val_t *value_plus_one;
		struct cl2llvm_val_t *one;

		/* Create constant one to add to variable */
		one = cl2llvm_val_create_w_init(LLVMConstInt(LLVMInt32Type(), 1, 0), 1);

		type = cl2llvm_type_create_w_init(LLVMGetElementType(
			(yyvsp[-1].llvm_value_ref)->type->llvm_type), (yyvsp[-1].llvm_value_ref)->type->sign);

		snprintf(temp_var_name, sizeof temp_var_name,
			"tmp_%d", temp_var_count++);
		struct cl2llvm_val_t *lval = cl2llvm_val_create_w_init(
			LLVMBuildLoad(cl2llvm_builder, (yyvsp[-1].llvm_value_ref)->val, temp_var_name),
			(yyvsp[-1].llvm_value_ref)->type->sign);

		/* Cast constant one to type of variable */
		struct cl2llvm_val_t *cast_one = llvm_type_cast(one, type);
	
		snprintf(temp_var_name, sizeof temp_var_name,
			"tmp_%d", temp_var_count++);
		
		/* Create an object that will hold the type of the operands.
		   This extra object is necessary since in the case of a vector 
		   type, we are concerned with the type of its components, but the
		   resultant type of the operation is a vector. */
		switch_type = cl2llvm_type_create_w_init(type->llvm_type, type->sign);
		if (LLVMGetTypeKind(switch_type->llvm_type) == LLVMVectorTypeKind)
		{
			switch_type->llvm_type = LLVMGetElementType(type->llvm_type);
		}

		switch (LLVMGetTypeKind(switch_type->llvm_type))
		{
		case LLVMIntegerTypeKind:

			value_plus_one = cl2llvm_val_create_w_init(
				LLVMBuildAdd(cl2llvm_builder, lval->val, 
				cast_one->val, temp_var_name), type->sign);
			break;

		case LLVMHalfTypeKind:
		case LLVMFloatTypeKind:
		case LLVMDoubleTypeKind:

			value_plus_one = cl2llvm_val_create_w_init(
				LLVMBuildFAdd(cl2llvm_builder, lval->val, 
				cast_one->val, temp_var_name), type->sign);
			break;

		default:

			yyerror("invalid type of operand for post '++'");
			value_plus_one = cl2llvm_val_create();
		}
		
		LLVMBuildStore(cl2llvm_builder, value_plus_one->val, (yyvsp[-1].llvm_value_ref)->val);
		
		cl2llvm_val_free(one);
		cl2llvm_val_free(value_plus_one);
		cl2llvm_val_free(cast_one);
		cl2llvm_val_free((yyvsp[-1].llvm_value_ref));
		cl2llvm_type_free(type);
		cl2llvm_type_free(switch_type);

		(yyval.llvm_value_ref) = lval;

	}
#line 6162 "parser.c" /* yacc.c:1646  */
    break;

  case 141:
#line 3977 "parser.y" /* yacc.c:1646  */
    {	
		struct cl2llvm_type_t *switch_type;
		struct cl2llvm_type_t *type;
		struct cl2llvm_val_t *value_plus_one;
		struct cl2llvm_val_t *one;

		/* Create constant one to add to variable */
		one = cl2llvm_val_create_w_init(LLVMConstInt(LLVMInt32Type(), 1, 0), 1);

		type = cl2llvm_type_create_w_init(LLVMGetElementType(
			(yyvsp[0].llvm_value_ref)->type->llvm_type), (yyvsp[0].llvm_value_ref)->type->sign);

		snprintf(temp_var_name, sizeof temp_var_name,
			"tmp_%d", temp_var_count++);
		struct cl2llvm_val_t *lval = cl2llvm_val_create_w_init(
			LLVMBuildLoad(cl2llvm_builder, (yyvsp[0].llvm_value_ref)->val, temp_var_name),
			(yyvsp[0].llvm_value_ref)->type->sign);

		/* Cast constant one to type of variable */
		struct cl2llvm_val_t *cast_one = llvm_type_cast(one, type);
	
		snprintf(temp_var_name, sizeof temp_var_name,
			"tmp_%d", temp_var_count++);
		
		/* Create an object that will hold the type of the operands.
		   This extra object is necessary since in the case of a vector 
		   type, we are concerned with the type of its components, but the
		   resultant type of the operation is a vector. */
		switch_type = cl2llvm_type_create_w_init(type->llvm_type, type->sign);
		if (LLVMGetTypeKind(switch_type->llvm_type) == LLVMVectorTypeKind)
		{
			switch_type->llvm_type = LLVMGetElementType(type->llvm_type);
		}

		switch (LLVMGetTypeKind(switch_type->llvm_type))
		{
		case LLVMIntegerTypeKind:

			value_plus_one = cl2llvm_val_create_w_init(
				LLVMBuildAdd(cl2llvm_builder, lval->val, 
				cast_one->val, temp_var_name), type->sign);
			break;

		case LLVMHalfTypeKind:
		case LLVMFloatTypeKind:
		case LLVMDoubleTypeKind:

			value_plus_one = cl2llvm_val_create_w_init(
				LLVMBuildFAdd(cl2llvm_builder, lval->val, 
				cast_one->val, temp_var_name), type->sign);
			break;

		default:

			yyerror("invalid type of operand for pre '++'");
			value_plus_one = cl2llvm_val_create();
		}
		
		LLVMBuildStore(cl2llvm_builder, value_plus_one->val, (yyvsp[0].llvm_value_ref)->val);
		
		cl2llvm_val_free(one);
		cl2llvm_val_free((yyvsp[0].llvm_value_ref));
		cl2llvm_val_free(cast_one);
		cl2llvm_val_free(lval);
		cl2llvm_type_free(type);
		cl2llvm_type_free(switch_type);

		(yyval.llvm_value_ref) = value_plus_one;
	}
#line 6236 "parser.c" /* yacc.c:1646  */
    break;

  case 142:
#line 4047 "parser.y" /* yacc.c:1646  */
    {
		struct cl2llvm_type_t *switch_type;
		struct cl2llvm_type_t *type;
		struct cl2llvm_val_t *value_minus_one;
		struct cl2llvm_val_t *one;

		/* Create constant one to add to variable */
		one = cl2llvm_val_create_w_init(LLVMConstInt(LLVMInt32Type(), 1, 0), 1);

		type = cl2llvm_type_create_w_init(LLVMGetElementType(
			(yyvsp[0].llvm_value_ref)->type->llvm_type), (yyvsp[0].llvm_value_ref)->type->sign);

		snprintf(temp_var_name, sizeof temp_var_name,
			"tmp_%d", temp_var_count++);
		struct cl2llvm_val_t *lval = cl2llvm_val_create_w_init(
			LLVMBuildLoad(cl2llvm_builder, (yyvsp[0].llvm_value_ref)->val, temp_var_name),
			(yyvsp[0].llvm_value_ref)->type->sign);

		/* Cast constant one to type of variable */
		struct cl2llvm_val_t *cast_one = llvm_type_cast(one, type);
	
		snprintf(temp_var_name, sizeof temp_var_name,
			"tmp_%d", temp_var_count++);
		
		/* Create an object that will hold the type of the operands.
		   This extra object is necessary since in the case of a vector 
		   type, we are concerned with the type of its components, but the
		   resultant type of the operation is a vector. */
		switch_type = cl2llvm_type_create_w_init(type->llvm_type, type->sign);
		if (LLVMGetTypeKind(switch_type->llvm_type) == LLVMVectorTypeKind)
		{
			switch_type->llvm_type = LLVMGetElementType(type->llvm_type);
		}

		switch (LLVMGetTypeKind(switch_type->llvm_type))
		{
		case LLVMIntegerTypeKind:

			value_minus_one = cl2llvm_val_create_w_init(
				LLVMBuildSub(cl2llvm_builder, lval->val, 
				cast_one->val, temp_var_name), type->sign);
			break;

		case LLVMHalfTypeKind:
		case LLVMFloatTypeKind:
		case LLVMDoubleTypeKind:

			value_minus_one = cl2llvm_val_create_w_init(
				LLVMBuildFSub(cl2llvm_builder, lval->val, 
				cast_one->val, temp_var_name), type->sign);
			break;

		default:

			yyerror("invalid type of operand for pre '--'");
			value_minus_one = cl2llvm_val_create();
		}
		
		LLVMBuildStore(cl2llvm_builder, value_minus_one->val, (yyvsp[0].llvm_value_ref)->val);
		
		cl2llvm_val_free(one);
		cl2llvm_val_free((yyvsp[0].llvm_value_ref));
		cl2llvm_val_free(cast_one);
		cl2llvm_val_free(lval);
		cl2llvm_type_free(type);
		cl2llvm_type_free(switch_type);

		(yyval.llvm_value_ref) = value_minus_one;

	}
#line 6311 "parser.c" /* yacc.c:1646  */
    break;

  case 143:
#line 4118 "parser.y" /* yacc.c:1646  */
    {
		struct cl2llvm_type_t *switch_type;
		struct cl2llvm_type_t *type;
		struct cl2llvm_val_t *value_minus_one;
		struct cl2llvm_val_t *one;

		/* Create constant one to add to variable */
		one = cl2llvm_val_create_w_init(LLVMConstInt(LLVMInt32Type(), 1, 0), 1);

		type = cl2llvm_type_create_w_init(LLVMGetElementType(
			(yyvsp[-1].llvm_value_ref)->type->llvm_type), (yyvsp[-1].llvm_value_ref)->type->sign);

		snprintf(temp_var_name, sizeof temp_var_name,
			"tmp_%d", temp_var_count++);
		struct cl2llvm_val_t *lval = cl2llvm_val_create_w_init(
			LLVMBuildLoad(cl2llvm_builder, (yyvsp[-1].llvm_value_ref)->val, temp_var_name),
			(yyvsp[-1].llvm_value_ref)->type->sign);

		/* Cast constant one to type of variable */
		struct cl2llvm_val_t *cast_one = llvm_type_cast(one, type);
	
		snprintf(temp_var_name, sizeof temp_var_name,
			"tmp_%d", temp_var_count++);
		
		/* Create an object that will hold the type of the operands.
		   This extra object is necessary since in the case of a vector 
		   type, we are concerned with the type of its components, but the
		   resultant type of the operation is a vector. */
		switch_type = cl2llvm_type_create_w_init(type->llvm_type, type->sign);
		if (LLVMGetTypeKind(switch_type->llvm_type) == LLVMVectorTypeKind)
		{
			switch_type->llvm_type = LLVMGetElementType(type->llvm_type);
		}

		switch (LLVMGetTypeKind(switch_type->llvm_type))
		{
		case LLVMIntegerTypeKind:

			value_minus_one = cl2llvm_val_create_w_init(
				LLVMBuildSub(cl2llvm_builder, lval->val, 
				cast_one->val, temp_var_name), type->sign);
			break;

		case LLVMHalfTypeKind:
		case LLVMFloatTypeKind:
		case LLVMDoubleTypeKind:

			value_minus_one = cl2llvm_val_create_w_init(
				LLVMBuildFSub(cl2llvm_builder, lval->val, 
				cast_one->val, temp_var_name), type->sign);
			break;

		default:

			yyerror("invalid type of operand for post '--'");
			value_minus_one = cl2llvm_val_create();
		}
		
		LLVMBuildStore(cl2llvm_builder, value_minus_one->val, (yyvsp[-1].llvm_value_ref)->val);
		
		cl2llvm_val_free(one);
		cl2llvm_val_free(value_minus_one);
		cl2llvm_val_free(cast_one);
		cl2llvm_val_free((yyvsp[-1].llvm_value_ref));
		cl2llvm_type_free(type);
		cl2llvm_type_free(switch_type);

		(yyval.llvm_value_ref) = lval;

	}
#line 6386 "parser.c" /* yacc.c:1646  */
    break;

  case 144:
#line 4189 "parser.y" /* yacc.c:1646  */
    {
		struct cl2llvm_val_t *value;
		struct cl2llvm_type_t *switch_type;
		
		snprintf(temp_var_name, sizeof temp_var_name,
			"tmp_%d", temp_var_count++);
		
		/* Create an object that will hold the type of the operands.
		   This extra object is necessary since in the case of a vector 
		   type, we are concerned with the type of its components, but the
		   resultant type of the operation is a vector. */
		switch_type = cl2llvm_type_create_w_init((yyvsp[0].llvm_value_ref)->type->llvm_type, (yyvsp[0].llvm_value_ref)->type->sign);
		if (LLVMGetTypeKind(switch_type->llvm_type) == LLVMVectorTypeKind)
		{
			switch_type->llvm_type = LLVMGetElementType((yyvsp[0].llvm_value_ref)->type->llvm_type);
		}

		switch (LLVMGetTypeKind(switch_type->llvm_type))
		{
		case LLVMIntegerTypeKind:

			value = cl2llvm_val_create_w_init(
				LLVMBuildNeg(cl2llvm_builder, (yyvsp[0].llvm_value_ref)->val, 
				temp_var_name), (yyvsp[0].llvm_value_ref)->type->sign);
			break;

		case LLVMHalfTypeKind:
		case LLVMFloatTypeKind:
		case LLVMDoubleTypeKind:

			value = cl2llvm_val_create_w_init(
				LLVMBuildFNeg(cl2llvm_builder, (yyvsp[0].llvm_value_ref)->val, 
				temp_var_name), (yyvsp[0].llvm_value_ref)->type->sign);
			break;

		default:

			yyerror("invalid type of operand for unary '-'");
			value = cl2llvm_val_create();
		}
		
		/* Free pointers */
		cl2llvm_val_free((yyvsp[0].llvm_value_ref));
		cl2llvm_type_free(switch_type);

		(yyval.llvm_value_ref) = value;
	}
#line 6438 "parser.c" /* yacc.c:1646  */
    break;

  case 145:
#line 4237 "parser.y" /* yacc.c:1646  */
    {
		(yyval.llvm_value_ref) = (yyvsp[0].llvm_value_ref);
	}
#line 6446 "parser.c" /* yacc.c:1646  */
    break;

  case 146:
#line 4241 "parser.y" /* yacc.c:1646  */
    {
		struct cl2llvm_val_t *value;

		value = llvm_type_cast((yyvsp[0].llvm_value_ref), (yyvsp[-2].llvm_type_ref));
	
		/* Free pointers */
		cl2llvm_val_free((yyvsp[0].llvm_value_ref));
		cl2llvm_type_free((yyvsp[-2].llvm_type_ref));
		(yyval.llvm_value_ref) = value;
	}
#line 6461 "parser.c" /* yacc.c:1646  */
    break;

  case 147:
#line 4252 "parser.y" /* yacc.c:1646  */
    {
		cl2llvm_yyerror("'sizeof' not supported");
		(yyval.llvm_value_ref) = NULL;
	}
#line 6470 "parser.c" /* yacc.c:1646  */
    break;

  case 148:
#line 4257 "parser.y" /* yacc.c:1646  */
    {
		struct cl2llvm_type_t *switch_type;
		struct cl2llvm_val_t *value;
		struct cl2llvm_val_t *neg_one;
		struct cl2llvm_val_t *cast_neg_one;

		value = cl2llvm_val_create();

		/* Create a negative one value to use in the xor operation */
		neg_one = cl2llvm_val_create_w_init(LLVMConstInt(
			LLVMInt32Type(), -1, 0), 1);

		/* Cast negative one to type of $2 */
		cast_neg_one = llvm_type_cast(neg_one, (yyvsp[0].llvm_value_ref)->type);		

		/* Create an object that will hold the type of the operands.
		   This extra object is necessary since in the case of a vector 
		   type, we are concerned with the type of its components, but the
		   resultant type of the operation is a vector. */
		switch_type = cl2llvm_type_create_w_init((yyvsp[0].llvm_value_ref)->type->llvm_type, (yyvsp[0].llvm_value_ref)->type->sign);
		if (LLVMGetTypeKind((yyvsp[0].llvm_value_ref)->type->llvm_type) == LLVMVectorTypeKind)
		{
			switch_type->llvm_type = LLVMGetElementType((yyvsp[0].llvm_value_ref)->type->llvm_type);
		}

		switch (LLVMGetTypeKind(switch_type->llvm_type))
		{
		case LLVMIntegerTypeKind:
			value->val = LLVMBuildXor(cl2llvm_builder, 
				(yyvsp[0].llvm_value_ref)->val, cast_neg_one->val, temp_var_name);
			value->type->sign = (yyvsp[0].llvm_value_ref)->type->sign;
			value->type->llvm_type = (yyvsp[0].llvm_value_ref)->type->llvm_type;
			break;


		default:
			
			yyerror("Invalid type of operands for '~'.");
		}

		/* Free pointers */
		cl2llvm_val_free((yyvsp[0].llvm_value_ref));
		cl2llvm_val_free(neg_one);
		cl2llvm_val_free(cast_neg_one);
		cl2llvm_type_free(switch_type);

		(yyval.llvm_value_ref) = value;
	}
#line 6523 "parser.c" /* yacc.c:1646  */
    break;

  case 149:
#line 4306 "parser.y" /* yacc.c:1646  */
    {
		(yyval.llvm_value_ref) = (yyvsp[0].llvm_value_ref);
	}
#line 6531 "parser.c" /* yacc.c:1646  */
    break;

  case 150:
#line 4317 "parser.y" /* yacc.c:1646  */
    {
		int index;
		struct cl2llvm_val_t *current_vec_elem;
		struct cl2llvm_type_t *elem_type;
		struct cl2llvm_val_t *cast_val;
		struct cl2llvm_val_t *value;
		struct cl2llvm_val_t *blank_elem = cl2llvm_val_create_w_init( LLVMConstInt(LLVMInt32Type(), 0, 0), 1);
		struct cl2llvm_val_t *cast_index;
		struct cl2llvm_val_t *cl2llvm_index;
		LLVMValueRef vec_const_elems[16];
		int vec_nonconst_elems[16];
		int elem_count = 0;
		int non_const_elem_count = 0;

		cast_index = NULL;
		cast_val = NULL;
		current_vec_elem = NULL;

		snprintf(temp_var_name, sizeof(temp_var_name),
			"tmp_%d", temp_var_count++);
		/* Create type object to represent element type */
		elem_type = cl2llvm_type_create_w_init(LLVMGetElementType((yyvsp[-4].llvm_type_ref)->llvm_type), (yyvsp[-4].llvm_type_ref)->sign);
		/*Go to entry block and declare vector*/
		LLVMPositionBuilder(cl2llvm_builder, cl2llvm_current_function->entry_block, cl2llvm_current_function->branch_instr);
		LLVMValueRef vec_addr = LLVMBuildAlloca(cl2llvm_builder, 
			(yyvsp[-4].llvm_type_ref)->llvm_type, temp_var_name);
		LLVMPositionBuilderAtEnd(cl2llvm_builder, current_basic_block);

		/*Expand any vectors present in list*/
		expand_vectors((yyvsp[-1].list_val_t));

		/*Iterate over list and build a vector of all constant entries*/
		for (index = 0; index < list_count((yyvsp[-1].list_val_t)); ++index)
		{
			current_vec_elem = list_get((yyvsp[-1].list_val_t), index);
			if(LLVMIsConstant(current_vec_elem->val) == 1)
			{
				
				cast_val = llvm_type_cast(current_vec_elem, elem_type);
				vec_const_elems[index] = cast_val->val;
				vec_nonconst_elems[index] = 0;
				elem_count++;
			}
			else
			{
				cast_val = llvm_type_cast(blank_elem, elem_type);
				vec_const_elems[index] = cast_val->val;
				vec_nonconst_elems[index] = 1;
				elem_count++;
				non_const_elem_count++;
			}
			if (elem_count > LLVMGetVectorSize((yyvsp[-4].llvm_type_ref)->llvm_type))
				yyerror("Too many elements in vector literal");
			cl2llvm_val_free(cast_val);
		}
		if (elem_count < LLVMGetVectorSize((yyvsp[-4].llvm_type_ref)->llvm_type))
			yyerror("Too few elements in vector literal");
		
		LLVMValueRef new_vector = LLVMConstVector(vec_const_elems, elem_count);

		/*Store constant vector*/
		if(non_const_elem_count < elem_count)
			LLVMBuildStore(cl2llvm_builder, new_vector, vec_addr);

		
		/*If there are non-constant entries in vector, insert them*/
		if (non_const_elem_count)
		{
			for (index = 0; index < elem_count; index++)
			{	
				cl2llvm_index = cl2llvm_val_create_w_init( LLVMConstInt(LLVMInt32Type(), index, 0), 1);
				cast_val = NULL;
				cast_index = NULL;

				current_vec_elem = list_get((yyvsp[-1].list_val_t), index);
				if (vec_nonconst_elems[index])
				{
					cast_val = llvm_type_cast(current_vec_elem, elem_type);
					
					snprintf(temp_var_name, sizeof(temp_var_name),
						"tmp_%d", temp_var_count++);

					LLVMValueRef vector_load = LLVMBuildLoad( cl2llvm_builder, vec_addr, temp_var_name);

					snprintf(temp_var_name, sizeof(temp_var_name),
						"tmp_%d", temp_var_count++);
					cast_index = llvm_type_cast(cl2llvm_index, elem_type);

					new_vector = LLVMBuildInsertElement( cl2llvm_builder, vector_load, cast_val->val, cl2llvm_index->val, temp_var_name);

					LLVMBuildStore(cl2llvm_builder, new_vector, vec_addr);

				}
				if (cast_val != NULL)
					cl2llvm_val_free(cast_val);
				if (cast_index != NULL)
					cl2llvm_val_free(cast_index);
				cl2llvm_val_free(cl2llvm_index);
			}

		}
		cl2llvm_val_free(blank_elem);
		cl2llvm_type_free(elem_type);

		LIST_FOR_EACH((yyvsp[-1].list_val_t), index)
		{
			cl2llvm_val_free(list_get((yyvsp[-1].list_val_t), index));
		}
		list_free((yyvsp[-1].list_val_t));

		value = cl2llvm_val_create_w_init(new_vector, (yyvsp[-4].llvm_type_ref)->sign);
		
		(yyval.llvm_value_ref) = value;

		cl2llvm_type_free((yyvsp[-4].llvm_type_ref));
	}
#line 6652 "parser.c" /* yacc.c:1646  */
    break;

  case 151:
#line 4437 "parser.y" /* yacc.c:1646  */
    {
		struct list_t *vec_elem_list;

		vec_elem_list = list_create();
		list_add(vec_elem_list, (yyvsp[-2].llvm_value_ref));
		list_add(vec_elem_list, (yyvsp[0].llvm_value_ref));

		(yyval.list_val_t) = vec_elem_list;

	}
#line 6667 "parser.c" /* yacc.c:1646  */
    break;

  case 152:
#line 4451 "parser.y" /* yacc.c:1646  */
    {
		(yyval.list_val_t) = (yyvsp[0].list_val_t);
	}
#line 6675 "parser.c" /* yacc.c:1646  */
    break;

  case 153:
#line 4455 "parser.y" /* yacc.c:1646  */
    {
		list_add((yyvsp[-2].list_val_t), (yyvsp[0].llvm_value_ref));

		(yyval.list_val_t) = (yyvsp[-2].list_val_t);
	}
#line 6685 "parser.c" /* yacc.c:1646  */
    break;

  case 154:
#line 4465 "parser.y" /* yacc.c:1646  */
    {
		struct cl2llvm_val_t *value = cl2llvm_val_create_w_init(
			LLVMConstInt(LLVMInt32Type(), (yyvsp[0].const_int_val), 0), 1);
		(yyval.llvm_value_ref) = value;
	}
#line 6695 "parser.c" /* yacc.c:1646  */
    break;

  case 155:
#line 4471 "parser.y" /* yacc.c:1646  */
    {
		struct cl2llvm_val_t *value = cl2llvm_val_create_w_init(
			LLVMConstInt(LLVMInt32Type(), (yyvsp[0].const_int_val), 0), 1);
		(yyval.llvm_value_ref) = value;
	}
#line 6705 "parser.c" /* yacc.c:1646  */
    break;

  case 156:
#line 4477 "parser.y" /* yacc.c:1646  */
    {
		struct cl2llvm_val_t *value = cl2llvm_val_create_w_init(
			LLVMConstInt(LLVMInt32Type(), (yyvsp[0].const_int_val), 0), 0);
		(yyval.llvm_value_ref) = value;
	}
#line 6715 "parser.c" /* yacc.c:1646  */
    break;

  case 157:
#line 4483 "parser.y" /* yacc.c:1646  */
    {
		struct cl2llvm_val_t *value =  cl2llvm_val_create_w_init(
			LLVMConstInt(LLVMInt32Type(), (yyvsp[0].const_int_val), 0), 0);
		(yyval.llvm_value_ref) = value;
	}
#line 6725 "parser.c" /* yacc.c:1646  */
    break;

  case 158:
#line 4489 "parser.y" /* yacc.c:1646  */
    {
		struct cl2llvm_val_t *value = cl2llvm_val_create_w_init(
			LLVMConstInt(LLVMInt64Type(), (yyvsp[0].const_int_val_ull), 0), 1);
		(yyval.llvm_value_ref) = value;
	}
#line 6735 "parser.c" /* yacc.c:1646  */
    break;

  case 159:
#line 4495 "parser.y" /* yacc.c:1646  */
    {
		struct cl2llvm_val_t *value = cl2llvm_val_create_w_init(
			LLVMConstInt(LLVMInt64Type(), (yyvsp[0].const_int_val_ull), 0), 0);
		(yyval.llvm_value_ref) = value;
	}
#line 6745 "parser.c" /* yacc.c:1646  */
    break;

  case 160:
#line 4501 "parser.y" /* yacc.c:1646  */
    {
		struct cl2llvm_val_t *value = cl2llvm_val_create_w_init( 
			LLVMConstReal(LLVMDoubleType(), (yyvsp[0].const_float_val)), 1);
		(yyval.llvm_value_ref) = value;
	}
#line 6755 "parser.c" /* yacc.c:1646  */
    break;

  case 161:
#line 4507 "parser.y" /* yacc.c:1646  */
    {
		struct cl2llvm_val_t *value = cl2llvm_val_create_w_init(
			LLVMConstReal(LLVMHalfType(), (yyvsp[0].const_float_val)), 1);
		(yyval.llvm_value_ref) = value;
	}
#line 6765 "parser.c" /* yacc.c:1646  */
    break;

  case 162:
#line 4513 "parser.y" /* yacc.c:1646  */
    {
		struct cl2llvm_val_t *value = cl2llvm_val_create_w_init(
			LLVMConstReal(LLVMFloatType(), (yyvsp[0].const_float_val)), 1);
		(yyval.llvm_value_ref) = value;
	}
#line 6775 "parser.c" /* yacc.c:1646  */
    break;

  case 163:
#line 4519 "parser.y" /* yacc.c:1646  */
    {
		struct cl2llvm_val_t *value = cl2llvm_val_create_w_init(
			LLVMConstReal(LLVMDoubleType(), (yyvsp[0].const_float_val)), 1);
		(yyval.llvm_value_ref) = value;
	}
#line 6785 "parser.c" /* yacc.c:1646  */
    break;

  case 164:
#line 4525 "parser.y" /* yacc.c:1646  */
    {
		int i;
		int component_count = 0;
		LLVMValueRef new_vector_addr;
		LLVMValueRef new_vector;
		LLVMValueRef component;
		
		snprintf(temp_var_name, sizeof(temp_var_name),
			"tmp_%d", temp_var_count++);
		struct cl2llvm_val_t *value = cl2llvm_val_create_w_init(
			LLVMBuildLoad(cl2llvm_builder, (yyvsp[0].llvm_value_ref)->val, temp_var_name),
			(yyvsp[0].llvm_value_ref)->type->sign);

		/* If value is an array element, retrieve element type */
		if (LLVMGetTypeKind(value->type->llvm_type) == LLVMArrayTypeKind
			|| LLVMGetTypeKind(value->type->llvm_type) == LLVMPointerTypeKind
			|| LLVMGetTypeKind(value->type->llvm_type) == LLVMStructTypeKind)
		{
			value->type->llvm_type = LLVMGetElementType(value->type->llvm_type);
		}

		/* If element is of vector type, check for component indices. */
		if (LLVMGetTypeKind(LLVMGetElementType((yyvsp[0].llvm_value_ref)->type->llvm_type))
			== LLVMVectorTypeKind && (yyvsp[0].llvm_value_ref)->vector_indices[i])
		{
			/* Get vector component count */
			while((yyvsp[0].llvm_value_ref)->vector_indices[component_count])
				component_count++;
			/* If there are multiple components */
			if (component_count == 2 || component_count == 3
				|| component_count == 4 || component_count == 8
				|| component_count == 16)
			{

				snprintf(temp_var_name, sizeof temp_var_name,
					"tmp_%d", temp_var_count++);

				/* Go to entry block and allocate new vector */
				LLVMPositionBuilder(cl2llvm_builder, 
					cl2llvm_current_function->entry_block,
					cl2llvm_current_function->branch_instr);
			
				new_vector_addr = LLVMBuildAlloca(cl2llvm_builder,
					LLVMVectorType(LLVMGetElementType(value->type->llvm_type),
					component_count), temp_var_name);

				LLVMPositionBuilderAtEnd(cl2llvm_builder, current_basic_block);


				/* Load new vector */
				snprintf(temp_var_name, sizeof temp_var_name,
					"tmp_%d", temp_var_count++);
				new_vector = LLVMBuildLoad(cl2llvm_builder, new_vector_addr,
					temp_var_name);

				while ((yyvsp[0].llvm_value_ref)->vector_indices[i])
				{
					snprintf(temp_var_name, sizeof temp_var_name,
						"tmp_%d", temp_var_count++);
					component = LLVMBuildExtractElement(cl2llvm_builder, 
						value->val, (yyvsp[0].llvm_value_ref)->vector_indices[i]->val,
						temp_var_name);

					snprintf(temp_var_name, sizeof temp_var_name,
						"tmp_%d", temp_var_count++);
					new_vector = LLVMBuildInsertElement(cl2llvm_builder, 
						new_vector, component, (yyvsp[0].llvm_value_ref)->vector_indices[i]->val,
						temp_var_name);
					i++;
				}
				value->val = new_vector;
				value->type->llvm_type = LLVMTypeOf(new_vector);
			}
			else if (component_count == 1)
			{
				snprintf(temp_var_name, sizeof temp_var_name,
					"tmp_%d", temp_var_count++);
				
				component = LLVMBuildExtractElement(cl2llvm_builder, 
					value->val, (yyvsp[0].llvm_value_ref)->vector_indices[0]->val,
					temp_var_name);
				value->val = component;
				value->type->llvm_type = LLVMTypeOf(component);
			}
			else
				cl2llvm_yyerror("Invalid vector type.");
		}
			

		cl2llvm_val_free((yyvsp[0].llvm_value_ref));

		(yyval.llvm_value_ref) = value;
	}
#line 6883 "parser.c" /* yacc.c:1646  */
    break;

  case 165:
#line 4620 "parser.y" /* yacc.c:1646  */
    {
		(yyval.llvm_value_ref) = (yyvsp[0].llvm_value_ref);
	}
#line 6891 "parser.c" /* yacc.c:1646  */
    break;

  case 166:
#line 4628 "parser.y" /* yacc.c:1646  */
    {
		(yyval.llvm_type_ref) = (yyvsp[0].llvm_type_ref);
	}
#line 6899 "parser.c" /* yacc.c:1646  */
    break;

  case 167:
#line 4632 "parser.y" /* yacc.c:1646  */
    {
		LLVMTypeRef ptr_type;
		struct cl2llvm_type_t *type;
		
		/* Create pointer type */
		ptr_type = LLVMPointerType((yyvsp[-1].llvm_type_ref)->llvm_type, 0);
		
		type = cl2llvm_type_create_w_init(ptr_type, (yyvsp[-1].llvm_type_ref)->sign);
	
		/* Free pointers */
		cl2llvm_type_free((yyvsp[-1].llvm_type_ref));
		
		(yyval.llvm_type_ref) = type;
	}
#line 6918 "parser.c" /* yacc.c:1646  */
    break;

  case 168:
#line 4650 "parser.y" /* yacc.c:1646  */
    {
		cl2llvm_yyerror("'intptr_t' not supported");
		(yyval.llvm_type_ref) = NULL;
	}
#line 6927 "parser.c" /* yacc.c:1646  */
    break;

  case 169:
#line 4655 "parser.y" /* yacc.c:1646  */
    {
		cl2llvm_yyerror("'ptrdiff_t' not supported");
		(yyval.llvm_type_ref) = NULL;
	}
#line 6936 "parser.c" /* yacc.c:1646  */
    break;

  case 170:
#line 4660 "parser.y" /* yacc.c:1646  */
    {
		cl2llvm_yyerror("'uintptr_t' not supported");
		(yyval.llvm_type_ref) = NULL;
	}
#line 6945 "parser.c" /* yacc.c:1646  */
    break;

  case 171:
#line 4665 "parser.y" /* yacc.c:1646  */
    {
		cl2llvm_yyerror("'sampler_t' not supported");
		(yyval.llvm_type_ref) = NULL;
	}
#line 6954 "parser.c" /* yacc.c:1646  */
    break;

  case 172:
#line 4670 "parser.y" /* yacc.c:1646  */
    {
		cl2llvm_yyerror("'event_t' not supported");
		(yyval.llvm_type_ref) = NULL;
	}
#line 6963 "parser.c" /* yacc.c:1646  */
    break;

  case 173:
#line 4675 "parser.y" /* yacc.c:1646  */
    {
		cl2llvm_yyerror("'image2d_t' not supported");
		(yyval.llvm_type_ref) = NULL;
	}
#line 6972 "parser.c" /* yacc.c:1646  */
    break;

  case 174:
#line 4680 "parser.y" /* yacc.c:1646  */
    {
		cl2llvm_yyerror("'image3d_t' not supported");
		(yyval.llvm_type_ref) = NULL;
	}
#line 6981 "parser.c" /* yacc.c:1646  */
    break;

  case 175:
#line 4685 "parser.y" /* yacc.c:1646  */
    {
		cl2llvm_yyerror("'image2d_array_t' not supported");
		(yyval.llvm_type_ref) = NULL;
	}
#line 6990 "parser.c" /* yacc.c:1646  */
    break;

  case 176:
#line 4690 "parser.y" /* yacc.c:1646  */
    {
		cl2llvm_yyerror("'image1d_t' not supported");
		(yyval.llvm_type_ref) = NULL;
	}
#line 6999 "parser.c" /* yacc.c:1646  */
    break;

  case 177:
#line 4695 "parser.y" /* yacc.c:1646  */
    {
		cl2llvm_yyerror("'image1d_buffer_t' not supported");
		(yyval.llvm_type_ref) = NULL;
	}
#line 7008 "parser.c" /* yacc.c:1646  */
    break;

  case 178:
#line 4700 "parser.y" /* yacc.c:1646  */
    {
		cl2llvm_yyerror("'image1d_array_t' not supported");
		(yyval.llvm_type_ref) = NULL;
	}
#line 7017 "parser.c" /* yacc.c:1646  */
    break;

  case 179:
#line 4705 "parser.y" /* yacc.c:1646  */
    {
		struct cl2llvm_type_t *type = cl2llvm_type_create_w_init(
			LLVMInt32Type(), 0);
		(yyval.llvm_type_ref) = type;
	}
#line 7027 "parser.c" /* yacc.c:1646  */
    break;

  case 180:
#line 4711 "parser.y" /* yacc.c:1646  */
    {
		struct cl2llvm_type_t *type = cl2llvm_type_create_w_init(
			LLVMInt32Type(), 0);
		(yyval.llvm_type_ref) = type;
	}
#line 7037 "parser.c" /* yacc.c:1646  */
    break;

  case 181:
#line 4717 "parser.y" /* yacc.c:1646  */
    {
		struct cl2llvm_type_t *type = cl2llvm_type_create_w_init(
			LLVMInt64Type(), 0);
		(yyval.llvm_type_ref) = type;
	}
#line 7047 "parser.c" /* yacc.c:1646  */
    break;

  case 182:
#line 4723 "parser.y" /* yacc.c:1646  */
    {
		struct cl2llvm_type_t *type = cl2llvm_type_create_w_init(
			LLVMInt8Type(), 0);
		(yyval.llvm_type_ref) = type;
	}
#line 7057 "parser.c" /* yacc.c:1646  */
    break;

  case 183:
#line 4729 "parser.y" /* yacc.c:1646  */
    {
		struct cl2llvm_type_t *type = cl2llvm_type_create_w_init(
			LLVMInt16Type(), 1);
		(yyval.llvm_type_ref) = type;
	}
#line 7067 "parser.c" /* yacc.c:1646  */
    break;

  case 184:
#line 4735 "parser.y" /* yacc.c:1646  */
    {
		struct cl2llvm_type_t *type = cl2llvm_type_create_w_init(
			LLVMInt16Type(), 0);
		(yyval.llvm_type_ref) = type;
	}
#line 7077 "parser.c" /* yacc.c:1646  */
    break;

  case 185:
#line 4741 "parser.y" /* yacc.c:1646  */
    {
		struct cl2llvm_type_t *type;
		type = cl2llvm_type_create_w_init(LLVMVectorType(LLVMInt32Type(), (yyvsp[0].const_int_val)), 0);
		(yyval.llvm_type_ref) = type;

	}
#line 7088 "parser.c" /* yacc.c:1646  */
    break;

  case 186:
#line 4748 "parser.y" /* yacc.c:1646  */
    {
		struct cl2llvm_type_t *type;
		type = cl2llvm_type_create_w_init(LLVMVectorType(LLVMInt8Type(), (yyvsp[0].const_int_val)), 0);
		(yyval.llvm_type_ref) = type;

	}
#line 7099 "parser.c" /* yacc.c:1646  */
    break;

  case 187:
#line 4755 "parser.y" /* yacc.c:1646  */
    {
		struct cl2llvm_type_t *type;
		type = cl2llvm_type_create_w_init(LLVMVectorType(LLVMInt32Type(), (yyvsp[0].const_int_val)), 0);
		(yyval.llvm_type_ref) = type;

	}
#line 7110 "parser.c" /* yacc.c:1646  */
    break;

  case 188:
#line 4762 "parser.y" /* yacc.c:1646  */
    {
		struct cl2llvm_type_t *type;
		type = cl2llvm_type_create_w_init(LLVMVectorType(LLVMInt16Type(), (yyvsp[0].const_int_val)), 0);
		(yyval.llvm_type_ref) = type;

	}
#line 7121 "parser.c" /* yacc.c:1646  */
    break;

  case 189:
#line 4769 "parser.y" /* yacc.c:1646  */
    {
		struct cl2llvm_type_t *type;
		type = cl2llvm_type_create_w_init(LLVMVectorType(LLVMInt16Type(), (yyvsp[0].const_int_val)), 1);
		(yyval.llvm_type_ref) = type;

	}
#line 7132 "parser.c" /* yacc.c:1646  */
    break;

  case 190:
#line 4776 "parser.y" /* yacc.c:1646  */
    {
		struct cl2llvm_type_t *type;
		type = cl2llvm_type_create_w_init(LLVMVectorType(LLVMInt32Type(), (yyvsp[0].const_int_val)), 1);
		(yyval.llvm_type_ref) = type;
	}
#line 7142 "parser.c" /* yacc.c:1646  */
    break;

  case 191:
#line 4782 "parser.y" /* yacc.c:1646  */
    {
		struct cl2llvm_type_t *type;
		type = cl2llvm_type_create_w_init(LLVMVectorType(LLVMInt32Type(), (yyvsp[0].const_int_val)), 1);
		(yyval.llvm_type_ref) = type;
	}
#line 7152 "parser.c" /* yacc.c:1646  */
    break;

  case 192:
#line 4788 "parser.y" /* yacc.c:1646  */
    {
		struct cl2llvm_type_t *type;
		type = cl2llvm_type_create_w_init(LLVMVectorType(LLVMInt8Type(), (yyvsp[0].const_int_val)), 1);
		(yyval.llvm_type_ref) = type;
	}
#line 7162 "parser.c" /* yacc.c:1646  */
    break;

  case 193:
#line 4794 "parser.y" /* yacc.c:1646  */
    {
		struct cl2llvm_type_t *type;
		type = cl2llvm_type_create_w_init(LLVMVectorType(LLVMFloatType(), (yyvsp[0].const_int_val)), 0);
		(yyval.llvm_type_ref) = type;
	}
#line 7172 "parser.c" /* yacc.c:1646  */
    break;

  case 194:
#line 4800 "parser.y" /* yacc.c:1646  */
    {
		struct cl2llvm_type_t *type;
		type = cl2llvm_type_create_w_init(LLVMVectorType(LLVMDoubleType(), (yyvsp[0].const_int_val)), 0);
		(yyval.llvm_type_ref) = type;
	}
#line 7182 "parser.c" /* yacc.c:1646  */
    break;

  case 195:
#line 4806 "parser.y" /* yacc.c:1646  */
    {
		struct cl2llvm_type_t *type = cl2llvm_type_create_w_init(
			LLVMInt32Type(), 1);
		(yyval.llvm_type_ref) = type;
	}
#line 7192 "parser.c" /* yacc.c:1646  */
    break;

  case 196:
#line 4812 "parser.y" /* yacc.c:1646  */
    {
		struct cl2llvm_type_t *type = cl2llvm_type_create_w_init(
			LLVMInt32Type(), 1);
		(yyval.llvm_type_ref) = type;
	}
#line 7202 "parser.c" /* yacc.c:1646  */
    break;

  case 197:
#line 4818 "parser.y" /* yacc.c:1646  */
    {
		struct cl2llvm_type_t *type = cl2llvm_type_create_w_init(
			LLVMInt64Type(), 1);
		(yyval.llvm_type_ref) = type;
	}
#line 7212 "parser.c" /* yacc.c:1646  */
    break;

  case 198:
#line 4824 "parser.y" /* yacc.c:1646  */
    {
		struct cl2llvm_type_t *type = cl2llvm_type_create_w_init(
			LLVMInt8Type(), 1);
		(yyval.llvm_type_ref) = type;
	}
#line 7222 "parser.c" /* yacc.c:1646  */
    break;

  case 199:
#line 4830 "parser.y" /* yacc.c:1646  */
    {
		struct cl2llvm_type_t *type = cl2llvm_type_create_w_init(
			LLVMFloatType(), 1);
		(yyval.llvm_type_ref) = type;
	}
#line 7232 "parser.c" /* yacc.c:1646  */
    break;

  case 200:
#line 4836 "parser.y" /* yacc.c:1646  */
    {
		struct cl2llvm_type_t *type = cl2llvm_type_create_w_init(
			LLVMInt1Type(), 1);
		(yyval.llvm_type_ref) = type;
	}
#line 7242 "parser.c" /* yacc.c:1646  */
    break;

  case 201:
#line 4842 "parser.y" /* yacc.c:1646  */
    {
		struct cl2llvm_type_t *type = cl2llvm_type_create_w_init(
			LLVMDoubleType(), 1);
		(yyval.llvm_type_ref) = type;
	}
#line 7252 "parser.c" /* yacc.c:1646  */
    break;

  case 202:
#line 4848 "parser.y" /* yacc.c:1646  */
    {
		struct cl2llvm_type_t *type = cl2llvm_type_create_w_init(
			LLVMInt64Type(), 1);
		(yyval.llvm_type_ref) = type;
	}
#line 7262 "parser.c" /* yacc.c:1646  */
    break;

  case 203:
#line 4854 "parser.y" /* yacc.c:1646  */
    {
		struct cl2llvm_type_t *type = cl2llvm_type_create_w_init(
			LLVMVoidType(), 1);
		(yyval.llvm_type_ref) = type;

	}
#line 7273 "parser.c" /* yacc.c:1646  */
    break;

  case 204:
#line 4861 "parser.y" /* yacc.c:1646  */
    {
		struct cl2llvm_type_t *type = cl2llvm_type_create_w_init(
			LLVMHalfType(), 1);
		(yyval.llvm_type_ref) = type;
	}
#line 7283 "parser.c" /* yacc.c:1646  */
    break;


#line 7287 "parser.c" /* yacc.c:1646  */
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
      yyerror (YY_("syntax error"));
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
        yyerror (yymsgp);
        if (yysyntax_error_status == 2)
          goto yyexhaustedlab;
      }
# undef YYSYNTAX_ERROR
#endif
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

  /* Pacify compilers like GCC when the user code never invokes
     YYERROR and the label yyerrorlab therefore never appears in user
     code.  */
  if (/*CONSTCOND*/ 0)
     goto yyerrorlab;

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


      yydestruct ("Error: popping",
                  yystos[yystate], yyvsp);
      YYPOPSTACK (1);
      yystate = *yyssp;
      YY_STACK_PRINT (yyss, yyssp);
    }

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END


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
  yyerror (YY_("memory exhausted"));
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
                  yytoken, &yylval);
    }
  /* Do not reclaim the symbols of the rule whose action triggered
     this YYABORT or YYACCEPT.  */
  YYPOPSTACK (yylen);
  YY_STACK_PRINT (yyss, yyssp);
  while (yyssp != yyss)
    {
      yydestruct ("Cleanup: popping",
                  yystos[*yyssp], yyvsp);
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
#line 4871 "parser.y" /* yacc.c:1906  */


