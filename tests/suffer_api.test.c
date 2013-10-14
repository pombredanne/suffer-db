#include <stdlib.h>
#include <string.h>
#import "seatest.h"
#import "suffer_api.h"

bool testiter1(const void * key, size_t klen, const void * val, size_t kval, void * arg) {
    int * count = (int *)arg;
    (*count)++;
    assert_string_equal("This is the key", key);
    assert_string_equal("This is the value", val);
    return false;
}
void test_suffer_simple_in_out() {
    suffer_db db;
    suffer_init(&db);
    char * key = "This is the key";
    char * val = "This is the value";
    suffer_add(&db, key, strlen(key), val, strlen(val));
    int items = 0;
    suffer_get(&db, key, strlen(key), testiter1, &items);
    assert_int_equal(1, items);
}

void test_suffer_missing() {
    suffer_db db;
    suffer_init(&db);
}

void test_fixture_suffer_api() {
    test_fixture_start();      
    run_test(test_suffer_simple_in_out);
    run_test(test_suffer_missing);
    test_fixture_end();       
}

void all_tests() {
    test_fixture_suffer_api();   
}

int main(int argc, char ** argv) {
    return run_tests(all_tests);
}

