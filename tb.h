#ifndef __TB_H
#define __TB_H

#include <math.h>
#include <float.h>
//#define DBL_EPSILON 1.0E-10

#define TB_VAR(suite) int suite##_tb_tests, suite##_tb_fails

#define TB_VAR_RESET(suite) suite##_tb_tests = 0; suite##_tb_fails = 0

#define TB_RESULT(suite) 	printf("%s TB RESULT: ", #suite); \
	if (suite##_tb_fails == 0) \
		printf("SUCCESS"); \
	else \
		printf("FAILURE"); \
	printf(" %i/%i\n", suite##_tb_fails, suite##_tb_tests)

#define TB_HEADER(str) \
	printf("%s:%u (%s) %s test-bench\n", __FILE__, __LINE__, __func__, str)

#define	TB_TEST_SILENT(suite) suite##_tb_tests++

#define TB_TEST(suite, test, str) \
	{ \
	if (test) \
	{ \
		printf("%s:%u (%s) ERROR %s\n", __FILE__, __LINE__, __func__, str); \
		suite##_tb_fails++; \
	} \
	suite##_tb_tests++; \
        }

#define TB_TEST_EXPECT_M_INT(suite, val, expect, str)	\
	{ \
	if (val != expect) \
	{ \
		printf("%s:%u (%s) ERROR %s %i (expected %i)\n", __FILE__, __LINE__, __func__, str, val, expect); \
		suite##_tb_fails++; \
	} \
	suite##_tb_tests++; \
        }

#define TB_TEST_EXPECT_N_INT(suite, val, expect, str)	\
	{ \
	if (val == expect) \
	{ \
		printf("%s:%u (%s) ERROR %s %i (expected other than %i)\n", __FILE__, __LINE__, __func__, str, val, expect); \
		suite##_tb_fails++; \
	} \
	suite##_tb_tests++; \
	}

#define TB_TEST_EXPECT_M_LONG(suite, val, expect, str)	\
	{ \
	if (val != expect) \
	{ \
		printf("%s:%u (%s) ERROR %s %li (expected %li)\n", __FILE__, __LINE__, __func__, str, val, expect); \
		suite##_tb_fails++; \
	} \
	suite##_tb_tests++; \
        }

#define TB_TEST_EXPECT_N_LONG(suite, val, expect, str)	\
	{ \
	if (val == expect) \
	{ \
		printf("%s:%u (%s) ERROR %s %li (expected other than %li)\n", __FILE__, __LINE__, __func__, str, val, expect); \
		suite##_tb_fails++; \
	} \
	suite##_tb_tests++; \
	}

#define TB_TEST_EXPECT_M_ULONG(suite, val, expect, str)	\
	{ \
	if (val != expect) \
	{ \
		printf("%s:%u (%s) ERROR %s %lui (expected %lui)\n", __FILE__, __LINE__, __func__, str, val, expect); \
		suite##_tb_fails++; \
	} \
	suite##_tb_tests++; \
        }

#define TB_TEST_EXPECT_N_ULONG(suite, val, expect, str)	\
	{ \
	if (val == expect) \
	{ \
		printf("%s:%u (%s) ERROR %s %lui (expected other than %lui)\n", __FILE__, __LINE__, __func__, str, val, expect); \
		suite##_tb_fails++; \
	} \
	suite##_tb_tests++; \
	}

#define TB_TEST_EXPECT_M_LONGLONG(suite, val, expect, str)	\
	{ \
	if (val != expect) \
	{ \
		printf("%s:%u (%s) ERROR %s %lli (expected %lli)\n", __FILE__, __LINE__, __func__, str, val, expect); \
		suite##_tb_fails++; \
	} \
	suite##_tb_tests++; \
        }

#define TB_TEST_EXPECT_N_LONGLONG(suite, val, expect, str)	\
	{ \
	if (val == expect) \
	{ \
		printf("%s:%u (%s) ERROR %s %lli (expected other than %lli)\n", __FILE__, __LINE__, __func__, str, val, expect); \
		suite##_tb_fails++; \
	} \
	suite##_tb_tests++; \
	}

#define TB_TEST_EXPECT_M_UINT(suite, val, expect, str)	\
	{ \
	if (val != expect) \
	{ \
		printf("%s:%u (%s) ERROR %s %u (expected %u)\n", __FILE__, __LINE__, __func__, str, val, expect); \
		suite##_tb_fails++; \
	} \
	suite##_tb_tests++; \
        }

#define TB_TEST_EXPECT_N_UINT(suite, val, expect, str)	\
	{ \
	if (val == expect) \
	{ \
		printf("%s:%u (%s) ERROR %s %u (expected other than %u)\n", __FILE__, __LINE__, __func__, str, val, expect); \
		suite##_tb_fails++; \
	} \
	suite##_tb_tests++; \
        }

#define TB_TEST_EXPECT_M_DBL(suite, val, expect, str)	\
	{								\
		if (fabs(val - expect) > (expect*DBL_EPSILON))		\
		{							\
			printf("%s:%u (%s) ERROR %s %e (expected %e)\n", __FILE__, __LINE__, __func__, str, val, expect); \
			suite##_tb_fails++;				\
		}							\
		suite##_tb_tests++;					\
        }

#define TB_TEST_EXPECT_N_DBL(suite, val, expect, str)	\
	{								\
		if (fabs(val - expect) <= expect*DBL_EPSILON)		\
		{							\
			printf("%s:%u (%s) ERROR %s %e (expected other than %e)\n", __FILE__, __LINE__, __func__, str, val, expect); \
			suite##_tb_fails++;				\
		}							\
		suite##_tb_tests++;					\
        }

#define TB_TEST_EXPECT_M_DBL_ZERO(suite, val, str)			\
	{								\
		if (fabs(val) > (DBL_EPSILON))				\
		{							\
			printf("%s:%u (%s) ERROR %s %e (expected 0.0)\n", __FILE__, __LINE__, __func__, str, val); \
			suite##_tb_fails++;				\
		}							\
		suite##_tb_tests++;					\
        }

#define TB_TEST_EXPECT_N_DBL_ZERO(suite, val, str)			\
	{								\
		if (fabs(val) <= DBL_EPSILON)				\
		{							\
			printf("%s:%u (%s) ERROR %s %e (expected other than 0.0)\n", __FILE__, __LINE__, __func__, str, val); \
			suite##_tb_fails++;				\
		}							\
		suite##_tb_tests++;					\
        }

#define TB_TEST_EXPECT_M_DBL_ZERO_PREC(suite, val, prec, str)		\
	{								\
		if (fabs(val) > prec)					\
		{							\
			printf("%s:%u (%s) ERROR %s %e (expected 0.0)\n", __FILE__, __LINE__, __func__, str, val); \
			suite##_tb_fails++;				\
		}							\
		suite##_tb_tests++;					\
        }

#define TB_TEST_EXPECT_N_DBL_ZERO_PREC(suite, val, prec, str)		\
	{								\
		if (fabs(val) <= prec)					\
		{							\
			printf("%s:%u (%s) ERROR %s %e (expected other than 0.0)\n", __FILE__, __LINE__, __func__, str, val); \
			suite##_tb_fails++;				\
		}							\
		suite##_tb_tests++;					\
        }

#define TB_TEST_EXPECT_M_DBL_PREC(suite, val, expect, prec, str)	\
	{								\
		if (fabs(val - expect) > (expect*prec))		\
		{							\
			printf("%s:%u (%s) ERROR %s %e (expected %e)\n", __FILE__, __LINE__, __func__, str, val, expect); \
			suite##_tb_fails++;				\
		}							\
		suite##_tb_tests++;					\
        }

#define TB_TEST_EXPECT_N_DBL_PREC(suite, val, expect, prec, str)	\
	{								\
		if (fabs(val - expect) <= expect*prec)		\
		{							\
			printf("%s:%u (%s) ERROR %s %e (expected other than %e)\n", __FILE__, __LINE__, __func__, str, val, expect); \
			suite##_tb_fails++;				\
		}							\
		suite##_tb_tests++;					\
        }

#define TB_TEST_EXPECT_M_DBL_PRECWRAP(suite, val, expect, prec, wrap, str) \
	{								\
		double err1, err2;					\
		int div;						\
		err1 = fabs(val - expect);				\
		div = (int)((err1) / wrap);			\
		if (div < 0) div = -1;					\
		if (div > 0) div = +1;					\
		err2 = fabs(err1 - wrap*div);				\
		if (err2 > (expect*prec))				\
		{							\
			printf("%e %e %i %e %e\n", fabs(val - expect), err1, div, err2, expect*prec); \
			printf("%s:%u (%s) ERROR %s %e (expected %e)\n", __FILE__, __LINE__, __func__, str, val, expect); \
			suite##_tb_fails++;				\
		}							\
		suite##_tb_tests++;					\
        }

#define TB_TEST_EXPECT_N_DBL_PRECWRAP(suite, val, expect, prec, wrap, str) \
	{								\
		double err1, err2;					\
		int div;						\
		err1 = fabs(val - expect);				\
		div = (int)((err1 + 0.5*wrap) / wrap);			\
		err2 = fabs(err1 - wrap*div);				\
		if (err2 <= expect*prec)				\
		{							\
			printf("%s:%u (%s) ERROR %s %e (expected other than %e)\n", __FILE__, __LINE__, __func__, str, val, expect); \
			suite##_tb_fails++;				\
		}							\
		suite##_tb_tests++;					\
        }

#define TB_TEST_EXPECT_M_PTR(suite, val, expect, str)	\
	{ \
	if (val != expect) \
	{ \
		printf("%s:%u (%s) ERROR %s %p (expected %p)\n", __FILE__, __LINE__, __func__, str, val, expect); \
		suite##_tb_fails++; \
	} \
	suite##_tb_tests++; \
        }

#define TB_TEST_EXPECT_N_PTR(suite, val, expect, str)	\
	{ \
	if (val == expect) \
	{ \
		printf("%s:%u (%s) ERROR %s %p (expected other than %p)\n", __FILE__, __LINE__, __func__, str, val, expect); \
		suite##_tb_fails++; \
	} \
	suite##_tb_tests++; \
        }

#endif // __TB_H
