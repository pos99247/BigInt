/*===========================================================================
 * Project #1 - CSE40478
 *===========================================================================*/
#include <sstream>
#include <string>
using namespace std;

#include "UnitTest++/src/UnitTest++.h"

#include "BigInt.h"
using namespace Project1;

//=============================================================================
// Tests
//=============================================================================
//-----------------------------------------------------------------------------
// BigInt()
//-----------------------------------------------------------------------------
TEST(BigIntDefaultConstructor)
{
   BigInt bi1;
   ostringstream out;
   out << bi1;
   CHECK_EQUAL("0", out.str());
}

//-----------------------------------------------------------------------------
// BigInt(const BigInt &)
//-----------------------------------------------------------------------------
TEST(BigIntCopyConstructor_FromZero)
{
   BigInt bi1("0");
   BigInt bi2(bi1);
   ostringstream out;
   out << bi2;
   CHECK_EQUAL("0", out.str());
}

TEST(BigIntCopyConstructor_FromPositive)
{
   BigInt bi1("1234");
   BigInt bi2(bi1);
   ostringstream out;
   out << bi2;
   CHECK_EQUAL("1234", out.str());
}

TEST(BigIntCopyConstructor_FromNegative)
{
   BigInt bi1("-1234");
   BigInt bi2(bi1);
   ostringstream out;
   out << bi2;
   CHECK_EQUAL("-1234", out.str());
}

//-----------------------------------------------------------------------------
// BigInt(long long)
//-----------------------------------------------------------------------------
TEST(BigIntConstructor_FromLongLong_Negative)
{
   BigInt bi1(-1000000LL);
   ostringstream out;
   out << bi1;
   CHECK_EQUAL("-1000000", out.str());
}

TEST(BigIntConstructor_FromLongLong_Zero)
{
   BigInt bi1(0LL);
   ostringstream out;
   out << bi1;
   CHECK_EQUAL("0", out.str());
}

TEST(BigIntConstructor_FromLongLong_Positive)
{
   BigInt bi1(1000000LL);
   ostringstream out;
   out << bi1;
   CHECK_EQUAL("1000000", out.str());
}

//-----------------------------------------------------------------------------
// BigInt(string)
//-----------------------------------------------------------------------------
TEST(BigIntConstructor_FromString)
{
   BigInt bi1("1234567789012345678901234567890");
   ostringstream out;
   out << bi1;
   CHECK_EQUAL("1234567789012345678901234567890", out.str());
}

TEST(BigIntConstructor_FromString_Positive)
{
   BigInt bi1("+1234567789012345678901234567890");
   ostringstream out;
   out << bi1;
   CHECK_EQUAL("1234567789012345678901234567890", out.str());
}

TEST(BigIntConstructor_FromString_Negative)
{
   BigInt bi1("-1234567789012345678901234567890");
   ostringstream out;
   out << bi1;
   CHECK_EQUAL("-1234567789012345678901234567890", out.str());
}

TEST(BigIntConstructor_FromString_Zero)
{
   BigInt bi1("0");
   ostringstream out;
   out << bi1;
   CHECK_EQUAL("0", out.str());
}

TEST(BigIntConstructor_FromString_NegativeZero)
{
   BigInt bi1("-0");
   ostringstream out;
   out << bi1;
   CHECK_EQUAL("0", out.str());
}

TEST(BigIntConstructor_FromString_PositiveZero)
{
   BigInt bi1("+0");
   ostringstream out;
   out << bi1;
   CHECK_EQUAL("0", out.str());
}

TEST(BigIntConstructor_FromString_Empty)
{
	CHECK_THROW(BigInt(""), invalid_argument);
}

TEST(BitIntConstructor_FromString_MinusSignOnly)
{
	CHECK_THROW(BigInt("-"), invalid_argument);
}

TEST(BigIntConstructor_FromString_ZeroZero)
{
   CHECK_THROW(BigInt("00"), invalid_argument);
}

TEST(BigIntConstructor_FromString_TrailingGarbage)
{
	CHECK_THROW(BigInt("1234i"), invalid_argument);
}

TEST(BigIntConstructor_FromString_LeadingGarbage)
{
	CHECK_THROW(BigInt("i1234"), invalid_argument);
}

TEST(BigIntConstructor_FromString_InternalGarbage)
{
	CHECK_THROW(BigInt("12i34"), invalid_argument);
}

TEST(BigIntConstructor_FromString_LeadingWhitespace)
{
	CHECK_THROW(BigInt("   12345677890123456789012345678"), invalid_argument);
}

TEST(BigIntConstructor_FromString_TrailingWhitespace)
{
	CHECK_THROW(BigInt("12345677890123456789012345678   "), invalid_argument);
}

TEST(BigIntConstructor_FromString_InternalWhitespace)
{
	CHECK_THROW(BigInt("12345677890123 456789012345678"), invalid_argument);
}

//-----------------------------------------------------------------------------
// operator=
//-----------------------------------------------------------------------------
TEST(BigIntCopyAssignment_FromZero)
{
   BigInt bi1("0");
   BigInt bi2;
   bi2 = bi1;
   ostringstream out;
   out << bi2;
   CHECK_EQUAL("0", out.str());
}

TEST(BigIntCopyAssignment_FromPositive)
{
   BigInt bi1("1234");
   BigInt bi2;
   bi2 = bi1;
   ostringstream out;
   out << bi2;
   CHECK_EQUAL("1234", out.str());
}

TEST(BigIntCopyAssignment_FromNegative)
{
   BigInt bi1("-1234");
   BigInt bi2;
   bi2 = bi1;
   ostringstream out;
   out << bi2;
   CHECK_EQUAL("-1234", out.str());
}

//-----------------------------------------------------------------------------
// operator+=
//-----------------------------------------------------------------------------
TEST(BigIntOperatorAddAssign_BothPositive_Equal)
{
   BigInt bi1("123");
   BigInt bi2("123");
   bi1 += bi2;
   ostringstream out;
   out << bi1;
   CHECK_EQUAL("246", out.str());
}

TEST(BigIntOperatorAddAssign_LeftPositiveRightZero)
{
   BigInt bi1("123");
   BigInt bi2("0");
   bi1 += bi2;
   ostringstream out;
   out << bi1;
   CHECK_EQUAL("123", out.str());
}

TEST(BigIntOperatorAddAssign_LeftZeroRightPositive)
{
   BigInt bi1("0");
   BigInt bi2("123");
   bi1 += bi2;
   ostringstream out;
   out << bi1;
   CHECK_EQUAL("123", out.str());
}

TEST(BigIntOperatorAddAssign_BothPositive_SameLength)
{
   BigInt bi1("901");
   BigInt bi2("899");
   bi1 += bi2;
   ostringstream out;
   out << bi1;
   CHECK_EQUAL("1800", out.str());
}

TEST(BigIntOperatorAddAssign_BothPositive_LeftLonger)
{
   BigInt bi1("1070102");
   BigInt bi2("899923");
   bi1 += bi2;
   ostringstream out;
   out << bi1;
   CHECK_EQUAL("1970025", out.str());
}

TEST(BigIntOperatorAddAssign_BothPositive_RightLonger)
{
   BigInt bi1("899923");
   BigInt bi2("1070102");
   bi1 += bi2;
   ostringstream out;
   out << bi1;
   CHECK_EQUAL("1970025", out.str());
}

TEST(BigIntOperatorAddAssign_BothNegative_SameLength)
{
   BigInt bi1("-899");
   BigInt bi2("-901");
   bi1 += bi2;
   ostringstream out;
   out << bi1;
   CHECK_EQUAL("-1800", out.str());
}

TEST(BigIntOperatorAddAssign_BothNegative_LeftLonger)
{
   BigInt bi1("-1070102");
   BigInt bi2("-899923");
   bi1 += bi2;
   ostringstream out;
   out << bi1;
   CHECK_EQUAL("-1970025", out.str());
}

TEST(BigIntOperatorAddAssign_BothNegative_RightLonger)
{
   BigInt bi1("-899923");
   BigInt bi2("-1070102");
   bi1 += bi2;
   ostringstream out;
   out << bi1;
   CHECK_EQUAL("-1970025", out.str());
}

TEST(BigIntOperatorAddAssign_LeftNegativeRightPositive_LeftShorter)
{
   BigInt bi1("-901");
   BigInt bi2("28260972");
   bi1 += bi2;
   ostringstream out;
   out << bi1;
   CHECK_EQUAL("28260071", out.str());
}

TEST(BigIntOperatorAddAssign_LeftNegativeRightPositive_RightShorter)
{
   BigInt bi1("-28260972");
   BigInt bi2("901");
   bi1 += bi2;
   ostringstream out;
   out << bi1;
   CHECK_EQUAL("-28260071", out.str());
}

TEST(BigIntOperatorAddAssign_LeftPositiveRightNegative_LeftShorter)
{
   BigInt bi1("901");
   BigInt bi2("-28260972");
   bi1 += bi2;
   ostringstream out;
   out << bi1;
   CHECK_EQUAL("-28260071", out.str());
}

TEST(BigIntOperatorAddAssign_LeftPositiveRightNegative_RightShorter)
{
   BigInt bi1("28260972");
   BigInt bi2("-901");
   bi1 += bi2;
   ostringstream out;
   out << bi1;
   CHECK_EQUAL("28260071", out.str());
}

//-----------------------------------------------------------------------------
// operator-=
//-----------------------------------------------------------------------------
TEST(BigIntOperatorSubtractAssign_BothPositive_Equal)
{
   BigInt bi1("123");
   BigInt bi2("123");
   bi1 -= bi2;
   ostringstream out;
   out << bi1;
   CHECK_EQUAL("0", out.str());
}

TEST(BigIntOperatorSubtractAssign_LeftPositiveRightZero)
{
   BigInt bi1("123");
   BigInt bi2("0");
   bi1 -= bi2;
   ostringstream out;
   out << bi1;
   CHECK_EQUAL("123", out.str());
}

TEST(BigIntOperatorSubtractAssign_LeftZeroRightPositive)
{
   BigInt bi1("0");
   BigInt bi2("123");
   bi1 -= bi2;
   ostringstream out;
   out << bi1;
   CHECK_EQUAL("-123", out.str());
}

TEST(BigIntOperatorSubtractAssign_BothPositive_SameLength_LeftLarger)
{
   BigInt bi1("901");
   BigInt bi2("899");
   bi1 -= bi2;
   ostringstream out;
   out << bi1;
   CHECK_EQUAL("2", out.str());
}

TEST(BigIntOperatorSubtractAssign_BothPositive_SameLength_LeftSmaller)
{
   BigInt bi1("899");
   BigInt bi2("901");
   bi1 -= bi2;
   ostringstream out;
   out << bi1;
   CHECK_EQUAL("-2", out.str());
}

TEST(BigIntOperatorSubtractAssign_BothPositive_LeftLonger)
{
   BigInt bi1("1070102");
   BigInt bi2("899923");
   bi1 -= bi2;
   ostringstream out;
   out << bi1;
   CHECK_EQUAL("170179", out.str());
}

TEST(BigIntOperatorSubtractAssign_BothPositive_RightLonger)
{
   BigInt bi1("899923");
   BigInt bi2("1070102");
   bi1 -= bi2;
   ostringstream out;
   out << bi1;
   CHECK_EQUAL("-170179", out.str());
}

TEST(BigIntOperatorSubtractAssign_BothNegative_SameLength_LeftLarger)
{
   BigInt bi1("-899");
   BigInt bi2("-901");
   bi1 -= bi2;
   ostringstream out;
   out << bi1;
   CHECK_EQUAL("2", out.str());
}

TEST(BigIntOperatorSubtractAssign_BothNegative_SameLength_LeftSmaller)
{
   BigInt bi1("-901");
   BigInt bi2("-899");
   bi1 -= bi2;
   ostringstream out;
   out << bi1;
   CHECK_EQUAL("-2", out.str());
}

TEST(BigIntOperatorSubtractAssign_BothNegative_LeftLonger)
{
   BigInt bi1("-1070102");
   BigInt bi2("-899923");
   bi1 -= bi2;
   ostringstream out;
   out << bi1;
   CHECK_EQUAL("-170179", out.str());
}

TEST(BigIntOperatorSubtractAssign_BothNegative_RightLonger)
{
   BigInt bi1("-899923");
   BigInt bi2("-1070102");
   bi1 -= bi2;
   ostringstream out;
   out << bi1;
   CHECK_EQUAL("170179", out.str());
}

TEST(BigIntOperatorSubtractAssign_LeftNegativeRightPositive_LeftShorter)
{
   BigInt bi1("-901");
   BigInt bi2("28260972");
   bi1 -= bi2;
   ostringstream out;
   out << bi1;
   CHECK_EQUAL("-28261873", out.str());
}

TEST(BigIntOperatorSubtractAssign_LeftNegativeRightPositive_RightShorter)
{
   BigInt bi1("-28260972");
   BigInt bi2("901");
   bi1 -= bi2;
   ostringstream out;
   out << bi1;
   CHECK_EQUAL("-28261873", out.str());
}

TEST(BigIntOperatorSubtractAssign_LeftPositiveRightNegative_LeftShorter)
{
   BigInt bi1("901");
   BigInt bi2("-28260972");
   bi1 -= bi2;
   ostringstream out;
   out << bi1;
   CHECK_EQUAL("28261873", out.str());
}

TEST(BigIntOperatorSubtractAssign_LeftPositiveRightNegative_RightShorter)
{
   BigInt bi1("28260972");
   BigInt bi2("-901");
   bi1 -= bi2;
   ostringstream out;
   out << bi1;
   CHECK_EQUAL("28261873", out.str());
}

//-----------------------------------------------------------------------------
// operator+
//-----------------------------------------------------------------------------
TEST(BigIntOperatorAdd)
{
   BigInt bi1("123");
   BigInt bi2("456");
   BigInt bi3(bi1 + bi2);
   ostringstream out;
   out << bi3;
   CHECK_EQUAL("579", out.str());
}

TEST(BigIntOperatorAdd_CarryMostSignificantDigit)
{
	BigInt bi1("999");
	BigInt bi2("888");
	BigInt bi3(bi1 + bi2);
	ostringstream out;
	out << bi3;
	CHECK_EQUAL("1887", out.str());
}

TEST(BigIntOperatorAdd_FirstNumberNegative)
{
	BigInt bi1("-123");
	BigInt bi2("456");
	BigInt bi3(bi1 + bi2);
	ostringstream out;
	out << bi3;
	CHECK_EQUAL("333", out.str());
}

TEST(BigIntOperatorAdd_SecondNumberNegative)
{
	BigInt bi1("123");
	BigInt bi2("-456");
	BigInt bi3(bi1 + bi2);
	ostringstream out;
	out << bi3;
	CHECK_EQUAL("-333", out.str());
}

TEST(BigIntOperatorAdd_BothNumbersNegative)
{
	BigInt bi1("-123");
	BigInt bi2("-456");
	BigInt bi3(bi1 + bi2);
	ostringstream out;
	out << bi3;
	CHECK_EQUAL("-579", out.str());
}

TEST(BigIntOperatorAdd_LargeNumbers)
{
	BigInt bi1("111111111111111111111111111111111111111111111111111111111111");
	BigInt bi2("222222222222222222222222222222222222222222222222222222222222");
	BigInt bi3(bi1 + bi2);
	ostringstream out;
	out << bi3;
	CHECK_EQUAL("333333333333333333333333333333333333333333333333333333333333", out.str());
}

//-----------------------------------------------------------------------------
// operator-
//-----------------------------------------------------------------------------
TEST(BigIntOperatorSubtract)
{
   BigInt bi1("123");
   BigInt bi2("456");
   BigInt bi3(bi1 - bi2);
   ostringstream out;
   out << bi3;
   CHECK_EQUAL("-333", out.str());
}

TEST(BigIntOperatorSubtract_FirstNumberNegative)
{
	BigInt bi1("-123");
	BigInt bi2("456");
	BigInt bi3(bi1 - bi2);
	ostringstream out;
	out << bi3;
	CHECK_EQUAL("-579", out.str());
}

TEST(BigIntOperatorSubtract_SecondNumberNegative)
{
	BigInt bi1("123");
	BigInt bi2("-456");
	BigInt bi3(bi1 - bi2);
	ostringstream out;
	out << bi3;
	CHECK_EQUAL("579", out.str());
}

TEST(BigIntOperatorSubtract_BothNumbersNegative)
{
	BigInt bi1("-123");
	BigInt bi2("-456");
	BigInt bi3(bi1 - bi2);
	ostringstream out;
	out << bi3;
	CHECK_EQUAL("333", out.str());
}

TEST(BigIntOperatorSubtract_LargeNumbers)
{
	BigInt bi1("111111111111111111111111111111111111111111111111111111111111");
	BigInt bi2("222222222222222222222222222222222222222222222222222222222222");
	BigInt bi3(bi1 - bi2);
	ostringstream out;
	out << bi3;
	CHECK_EQUAL("-111111111111111111111111111111111111111111111111111111111111", out.str());
}

//-----------------------------------------------------------------------------
// operator==
//-----------------------------------------------------------------------------
TEST(BigIntOperatorEqual_BothPositive_Equal)
{
   BigInt bi1("456");
   BigInt bi2("456");
   CHECK(bi1 == bi2);
}

TEST(BigIntOperatorEqual_BothPositive_LeftShorter)
{
   BigInt bi1("12345");
   BigInt bi2("6789012345");
   CHECK(!(bi1 == bi2));
}

TEST(BigIntOperatorEqual_BothNegative_Equal)
{
   BigInt bi1("-456");
   BigInt bi2("-456");
   CHECK(bi1 == bi2);
}

TEST(BigIntOperatorEqual_BothNegative_LeftShorter)
{
   BigInt bi1("-12345");
   BigInt bi2("-6789012345");
   CHECK(!(bi1 == bi2));
}

TEST(BigIntOperatorEqual_LeftPositiveRightNegative_SameLength)
{
   BigInt bi1("456");
   BigInt bi2("-456");
   CHECK(!(bi1 == bi2));
}

TEST(BigIntOperatorEqual_LeftNegativeRightPositive_SameLength)
{
   BigInt bi1("-456");
   BigInt bi2("456");
   CHECK(!(bi1 == bi2));
}

//-----------------------------------------------------------------------------
// operator!=
//-----------------------------------------------------------------------------
TEST(BigIntOperatorNotEqual_BothPositive_Equal)
{
   BigInt bi1("456");
   BigInt bi2("456");
   CHECK(!(bi1 != bi2));
}

TEST(BigIntOperatorNotEqual_BothPositive_LeftShorter)
{
   BigInt bi1("12345");
   BigInt bi2("6789012345");
   CHECK(bi1 != bi2);
}

TEST(BigIntOperatorNotEqual_BothNegative_Equal)
{
   BigInt bi1("-456");
   BigInt bi2("-456");
   CHECK(!(bi1 != bi2));
}

TEST(BigIntOperatorNotEqual_BothNegative_LeftShorter)
{
   BigInt bi1("-12345");
   BigInt bi2("-6789012345");
   CHECK(bi1 != bi2);
}

TEST(BigIntOperatorNotEqual_LeftPositiveRightNegative_SameLength)
{
   BigInt bi1("456");
   BigInt bi2("-456");
   CHECK(bi1 != bi2);
}

TEST(BigIntOperatorNotEqual_LeftNegativeRightPositive_SameLength)
{
   BigInt bi1("-456");
   BigInt bi2("456");
   CHECK(bi1 != bi2);
}

//-----------------------------------------------------------------------------
// operator<
//-----------------------------------------------------------------------------
TEST(BigIntOperatorLessThan_BothPositive_Equal)
{
   BigInt bi1("456");
   BigInt bi2("456");
   CHECK(!(bi1 < bi2));
}

TEST(BigIntOperatorLessThan_BothPositive_SameLength_LeftSmaller)
{
   BigInt bi1("12345");
   BigInt bi2("67890");
   CHECK(bi1 < bi2);
}

TEST(BigIntOperatorLessThan_BothPositive_LeftShorter)
{
   BigInt bi1("12345");
   BigInt bi2("6789012345");
   CHECK(bi1 < bi2);
}

TEST(BigIntOperatorLessThan_BothNegative_Equal)
{
   BigInt bi1("-456");
   BigInt bi2("-456");
   CHECK(!(bi1 < bi2));
}

TEST(BigIntOperatorLessThan_BothNegative_SameLength_LeftSmaller)
{
   BigInt bi1("-67890");
   BigInt bi2("-12345");
   CHECK(bi1 < bi2);
}

TEST(BigIntOperatorLessThan_BothNegative_LeftShorter)
{
   BigInt bi1("-12345");
   BigInt bi2("-6789012345");
   CHECK(!(bi1 < bi2));
}

TEST(BigIntOperatorLessThan_LeftPositiveRightNegative_SameLength)
{
   BigInt bi1("456");
   BigInt bi2("-456");
   CHECK(!(bi1 < bi2));
}

TEST(BigIntOperatorLessThan_LeftNegativeRightPositive_SameLength)
{
   BigInt bi1("-456");
   BigInt bi2("456");
   CHECK(bi1 < bi2);
}

//-----------------------------------------------------------------------------
// operator<=
//-----------------------------------------------------------------------------
TEST(BigIntOperatorLessThanEqual_BothPositive_Equal)
{
   BigInt bi1("456");
   BigInt bi2("456");
   CHECK(bi1 <= bi2);
}

TEST(BigIntOperatorLessThanEqual_BothPositive_SameLength_LeftSmaller)
{
   BigInt bi1("12345");
   BigInt bi2("67890");
   CHECK(bi1 <= bi2);
}

TEST(BigIntOperatorLessThanEqual_BothPositive_LeftShorter)
{
   BigInt bi1("12345");
   BigInt bi2("6789012345");
   CHECK(bi1 <= bi2);
}

TEST(BigIntOperatorLessThanEqual_BothNegative_Equal)
{
   BigInt bi1("-456");
   BigInt bi2("-456");
   CHECK(bi1 <= bi2);
}

TEST(BigIntOperatorLessThanEqual_BothNegative_SameLength_LeftSmaller)
{
   BigInt bi1("-67890");
   BigInt bi2("-12345");
   CHECK(bi1 <= bi2);
}

TEST(BigIntOperatorLessThanEqual_BothNegative_LeftShorter)
{
   BigInt bi1("-12345");
   BigInt bi2("-6789012345");
   CHECK(!(bi1 <= bi2));
}

TEST(BigIntOperatorLessThanEqual_LeftPositiveRightNegative_SameLength)
{
   BigInt bi1("456");
   BigInt bi2("-456");
   CHECK(!(bi1 <= bi2));
}

TEST(BigIntOperatorLessThanEqual_LeftNegativeRightPositive_SameLength)
{
   BigInt bi1("-456");
   BigInt bi2("456");
   CHECK(bi1 <= bi2);
}

//-----------------------------------------------------------------------------
// operator>
//-----------------------------------------------------------------------------
TEST(BigIntOperatorGreaterThan_BothPositive_Equal)
{
   BigInt bi1("456");
   BigInt bi2("456");
   CHECK(!(bi1 > bi2));
}

TEST(BigIntOperatorGreaterThan_BothPositive_SameLength_LeftSmaller)
{
   BigInt bi1("12345");
   BigInt bi2("67890");
   CHECK(!(bi1 > bi2));
}

TEST(BigIntOperatorGreaterThan_BothPositive_LeftShorter)
{
   BigInt bi1("12345");
   BigInt bi2("6789012345");
   CHECK(!(bi1 > bi2));
}

TEST(BigIntOperatorGreaterThan_BothNegative_Equal)
{
   BigInt bi1("-456");
   BigInt bi2("-456");
   CHECK(!(bi1 > bi2));
}

TEST(BigIntOperatorGreaterThan_BothNegative_SameLength_LeftSmaller)
{
   BigInt bi1("-67890");
   BigInt bi2("-12345");
   CHECK(!(bi1 > bi2));
}

TEST(BigIntOperatorGreaterThan_BothNegative_LeftShorter)
{
   BigInt bi1("-12345");
   BigInt bi2("-6789012345");
   CHECK(bi1 > bi2);
}

TEST(BigIntOperatorGreaterThan_LeftPositiveRightNegative_SameLength)
{
   BigInt bi1("456");
   BigInt bi2("-456");
   CHECK(bi1 > bi2);
}

TEST(BigIntOperatorGreaterThan_LeftNegativeRightPositive_SameLength)
{
   BigInt bi1("-456");
   BigInt bi2("456");
   CHECK(!(bi1 > bi2));
}

//-----------------------------------------------------------------------------
// operator>=
//-----------------------------------------------------------------------------
TEST(BigIntOperatorGreaterThanEqual_BothPositive_Equal)
{
   BigInt bi1("456");
   BigInt bi2("456");
   CHECK(bi1 >= bi2);
}

TEST(BigIntOperatorGreaterThanEqual_BothPositive_SameLength_LeftSmaller)
{
   BigInt bi1("12345");
   BigInt bi2("67890");
   CHECK(!(bi1 >= bi2));
}

TEST(BigIntOperatorGreaterThanEqual_BothPositive_LeftShorter)
{
   BigInt bi1("12345");
   BigInt bi2("6789012345");
   CHECK(!(bi1 >= bi2));
}

TEST(BigIntOperatorGreaterThanEqual_BothNegative_Equal)
{
   BigInt bi1("-456");
   BigInt bi2("-456");
   CHECK(bi1 >= bi2);
}

TEST(BigIntOperatorGreaterThanEqual_BothNegative_SameLength_LeftSmaller)
{
   BigInt bi1("-67890");
   BigInt bi2("-12345");
   CHECK(!(bi1 >= bi2));
}

TEST(BigIntOperatorGreaterThanEqual_BothNegative_LeftShorter)
{
   BigInt bi1("-12345");
   BigInt bi2("-6789012345");
   CHECK(bi1 >= bi2);
}

TEST(BigIntOperatorGreaterThanEqual_LeftPositiveRightNegative_SameLength)
{
   BigInt bi1("456");
   BigInt bi2("-456");
   CHECK(bi1 >= bi2);
}

TEST(BigIntOperatorGreaterThanEqual_LeftNegativeRightPositive_SameLength)
{
   BigInt bi1("-456");
   BigInt bi2("456");
   CHECK(!(bi1 >= bi2));
}

//-----------------------------------------------------------------------------
// operator<<
//-----------------------------------------------------------------------------
TEST(BigIntOperatorInsert)
{
   BigInt bi1("-1234567890");
   ostringstream out;
   out << bi1;
   CHECK(out.str() == "-1234567890");
}

//-----------------------------------------------------------------------------
// operator>>
//-----------------------------------------------------------------------------
TEST(BigIntOperatorExtract)
{
   BigInt bi1;
   istringstream in("-1234567890");
   in >> bi1;
   CHECK(bi1 == BigInt("-1234567890"));
}

//=============================================================================
// Program entrypoint
//=============================================================================
int main()
{
   return UnitTest::RunAllTests();
}