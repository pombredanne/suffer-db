#include <string.h>

#import "seatest.h"
#import "critbit.h"

void test_critbit_basic_ops() {
    critbit_tree tree = { NULL };
    char * results[3] = { NULL, NULL, NULL };

    cb_insert_str(&tree, "thefirstkey");
    cb_insert_str(&tree, "nope");
    cb_insert_str(&tree, "thelastkey");
    cb_find_prefix(&tree, "the", 3, (void const **) results, 3, 0);

    assert_string_equal("thefirstkey", results[0]);
    assert_string_equal("thelastkey", results[1]);
    assert_true(NULL == results[2]);

    cb_find_prefix(&tree, "", 0, (void const **) results, 3, 0);
    assert_string_equal("nope", results[0]);
    assert_string_equal("thefirstkey", results[1]);
    assert_string_equal("thelastkey", results[2]);
}

void test_critbit_can_store_null() {
    critbit_tree tree = { NULL };

    char * str = "k\0v";
    char * results[1] = { NULL };

    cb_insert(&tree, str, 4);
    cb_find_prefix(&tree, "", 0, (void const **) results, 1, 0);
    assert_int_equal('k', results[0][0]);
    assert_int_equal('\0', results[0][1]);
    assert_int_equal('v', results[0][2]);
    assert_int_equal('\0', results[0][3]);
}

typedef struct {
    int n;
    const char * matches[3];
    const char * keys[3];
    size_t keylens[3];
} test_foreach;

int test_iterator(const void * match, const void * key, size_t keylen, void * arg_) {
    test_foreach * arg = (test_foreach *)arg_;
    int i = arg->n++;
    arg->matches[i] = match;
    arg->keys[i] = key;
    arg->keylens[i] = keylen;
    return 0;
}

void test_critbit_find_all() {
    critbit_tree tree = { NULL };

    test_foreach arg = {
        0,
        { NULL, NULL, NULL },
        { NULL, NULL, NULL },
        { 0, 0, 0 }
    };

    cb_insert(&tree, "nope", 5);
    cb_insert(&tree, "str:one\0uno\0", 12);
    cb_insert(&tree, "str:two\0dos\0", 12);
    cb_insert(&tree, "str:three\0tres\0", 15);
    cb_foreach(&tree, "str:", 4, test_iterator, &arg);

    assert_int_equal(3, arg.n);
    assert_string_equal("str:one", arg.matches[0]);
    assert_string_equal("str:three", arg.matches[1]);
    assert_string_equal("str:two", arg.matches[2]);
    assert_string_equal("str:", arg.keys[0]);
    assert_string_equal("str:", arg.keys[1]);
    assert_string_equal("str:", arg.keys[2]);
    assert_int_equal(4, arg.keylens[0]);
    assert_int_equal(4, arg.keylens[1]);
    assert_int_equal(4, arg.keylens[2]);
}

void test_fixture_critbit() {
    test_fixture_start();      
    run_test(test_critbit_basic_ops);
    run_test(test_critbit_can_store_null);
    run_test(test_critbit_find_all);
    test_fixture_end();       
}

void all_tests() {
    test_fixture_critbit();   
}

int main(int argc, char ** argv) {
    return run_tests(all_tests);
}
