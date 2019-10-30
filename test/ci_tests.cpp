#include <iostream>
#include <acutest.h>

#include <Expr.hpp>

void test_plus(void) {
    Expr expr("5+9");
    TEST_CHECK(expr.eval() == 14.0);
}

void test_minus(void) {
    Expr expr("5-9");
    TEST_CHECK(expr.eval() == -4.0);
}

void test_times(void) {
    Expr expr("5*9");
    TEST_CHECK(expr.eval() == 45.0);
}

void test_divide(void) {
    Expr expr("4/2");
    TEST_CHECK(expr.eval() == 2.0);
}

void test_pow(void) {
    Expr expr("2^10");
    TEST_CHECK(expr.eval() == 1024.0);
}

void test_para(void) {
    Expr expr("(5+9)*2");
    TEST_CHECK(expr.eval() == 28.0);

    Expr expr2("5+9*2");
    TEST_CHECK(expr2.eval() == 23.0);
}

TEST_LIST = {
        { "test_plus", test_plus },
        { "test_minus", test_minus },
        { "test_times", test_times },
        { "test_divide", test_divide },
        { "test_pow", test_pow },
        { "test_para", test_para },
        { NULL, NULL }
};