#include <criterion/criterion.h>
#include <fnmatch.h>

#include "../src/my_fnmatch.h"

Test(Basic, simple_test)
{
    int value = my_fnmatch("SALUT", "HELLO");
    int exp = fnmatch("SALUT", "HELLO",0);
    cr_assert_eq(value,exp);
}

Test(suite, simple_test)
{
	int value = my_fnmatch("To???to", "ToACUto");
	int exp = fnmatch("To???to", "ToACUto",0);
	cr_assert_eq(value, exp);
}

Test(suite1, simple_test)
{
    int value = my_fnmatch("Toto?", "Toto");
    int exp = fnmatch("Toto?", "Toto",0);
    cr_assert_eq(value, exp);
}

Test(suite2, simple_test)
{
    int value = my_fnmatch("Toto?", "Toto");
    int exp = fnmatch("Toto?", "Toto",0);
    cr_assert_eq(value, exp);
}

Test(suite3, simple_test)
{
    int value = my_fnmatch("?Toto?oui", "KTotoKoui");
    int exp = fnmatch("?Toto?oui", "KTotoKoui",0);
    cr_assert_eq(value,exp);
}

Test(suite4, simple_test)
{
    int value = my_fnmatch("Totooooo*","Totooooo");
    int exp =  fnmatch("Totooooo*","Totooooo",0);
    cr_assert_eq(value,exp);
}

Test(suite5, simple_test)
{
    int value = my_fnmatch("totoo*abc", "totooACUabc");
    int exp = fnmatch("totoo*abc","totooACUabc",0);
    cr_assert_eq(value,exp, "Expected : %d Got : %d",exp,value);
}

Test(suite6, simple_test)
{
    int value = my_fnmatch("toto*abc", "totoGfd");
    int exp = fnmatch("toto*abc", "totoGfd",0);
    cr_assert_eq(value,exp, "Expected : %d Got : %d",exp,value);
}

Test(suite7, double_test)
{
    int value = my_fnmatch("toto*abc?", "totoGfdabcK");
    int exp = fnmatch("toto*abc?", "totoGfdabcK",0);
    cr_assert_eq(value,exp, "Expected : %d Got : %d",exp,value);
}

Test(suite8, double_test)
{
    int value = my_fnmatch("toto*abc?dfg", "totoGfdabcKdfg");
    int exp = fnmatch("toto*abc?dfg", "totoGfdabcKdfg",0);
    cr_assert_eq(value,exp, "Expected : %d Got : %d",exp,value);
}

Test(suite9, double_test)
{
    int value = my_fnmatch("toto*abc?df*g", "totoGfdabcKdffgg");
    int exp = fnmatch("toto*abc?df*", "totoGfdabcKdffgg",0);
    cr_assert_eq(value,exp, "Expected : %d Got : %d",exp,value);
}

Test(suite10, simple_test)
{
    int value = my_fnmatch("to\\?abce", "to\\?abcde");
    int exp = fnmatch("to\\?abce", "to\\?abcde",0);
    cr_assert_eq(value, exp, "Exp : %d", exp);
}

Test(suite11, triple_test)
{
    int value = my_fnmatch("to*bg?K\\? io","toabdbgKK\\? io");
    int exp = fnmatch("to*bg?K\\? io","toabdbgKK\\? io",0);
    cr_assert_eq(value,exp);
}

Test(suite12, simple_test)
{
    int value = my_fnmatch("ACU[UUU", "ACU]UUU");
    int exp = fnmatch("ACU[UUU", "ACU]UUU",0);
    cr_assert_eq(value,exp, "Expected : %d Got : %d",exp,value);
}

Test(suite13, simple_test)
{
    int value = my_fnmatch("[ACUU[UU", "[ACUU[UU");
    int exp = fnmatch("[ACUU[UU", "[ACUU[UU",0);
    cr_assert_eq(value,exp, "Expected : %d Got : %d",exp,value);
}

Test(suite14, simple_test)
{
    int value = my_fnmatch("ACU[]UU", "ACU[]UU");
    int exp = fnmatch("ACU[]UU", "ACU[]UU",0);
    cr_assert_eq(value,exp, "Expected : %d Got : %d",exp,value);
}

Test(suite15, simple_test)
{
    int value = my_fnmatch("ACU[]UU", "ACU[UUU");
    int exp = fnmatch("ACU[]UU", "ACU[UUU",0);
    cr_assert_eq(value,exp, "Expected : %d Got : %d",exp,value);
}

Test(suite16, simple_test)
{
    int value = my_fnmatch("AC[AEIOU]POPO","ACUPOPO");
    int exp = fnmatch("AC[AEIOU]POPO","ACUPOPO",0);
    cr_assert_eq(value,exp, "Expected : %d Got : %d",exp,value);
}

Test(suite17, double_test)
{
    int value = my_fnmatch("AC[UJ]OUI[]", "ACUOUI[]");
    int exp = fnmatch("AC[UJ]OUI[]", "ACUOUI[]",0);
    cr_assert_eq(value,exp, "Expected : %d Got : %d",exp,value);
}

Test(suite18, hard_test)
{
    int value = my_fnmatch("A*OUI?[]OK[ABCDE] 42", "ABCOUIK[]OKA 42");
    int exp = fnmatch("A*OUI?[]OK[ABCDE] 42", "ABCOUIK[]OKA 42",0);
    cr_assert_eq(value,exp, "Expected : %d Got : %d",exp,value);
}

Test(suite19, simple_test)
{
    int value = my_fnmatch("AC[!AEIOU]POPO","ACUPOPO");
    int exp = fnmatch("AC[!AEIOU]POPO","ACUPOPO",0);
    cr_assert_eq(value,exp, "Expected : %d Got : %d",exp,value);
}

Test(suite20, simple_test)
{
    int value = my_fnmatch("AC[!AEIOU]POPO","ACZPOPO");
    int exp = fnmatch("AC[!AEIOU]POPO","ACZPOPO",0);
    cr_assert_eq(value,exp, "Expected : %d Got : %d",exp,value);
}

Test(suite21, simple_test)
{
    int value = my_fnmatch("AC[A-D]POPO","ACBPOPO");
    int exp = fnmatch("AC[A-D]POPO","ACBPOPO",0);
    cr_assert_eq(value,exp, "Expected : %d Got : %d",exp,value);
}

Test(suite22, simple_test)
{
    int value = my_fnmatch("?A??", "A");
    int exp = fnmatch("?A??", "A",0);
    cr_assert_eq(value,exp, "Expected : %d Got : %d",exp,value);
}

Test(suite23, simple_test)
{
    int value = my_fnmatch("AC[!A-D]POPO","ACEPOPO");
    int exp = fnmatch("AC[!A-D]POPO","ACEPOPO",0);
    cr_assert_eq(value,exp, "Expected : %d Got : %d",exp,value);
}

Test(suite24, simple_test)
{
    int value = my_fnmatch("AC[!A-D]POPO","ACEPOPO");
    int exp = fnmatch("AC[!A-D]POPO","ACEPOPO",0);
    cr_assert_eq(value,exp, "Expected : %d Got : %d",exp,value);
}

