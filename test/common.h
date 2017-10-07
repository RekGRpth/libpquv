#ifndef common_h
#define common_h

#include <assert.h>

#include <postgresql/libpq-fe.h>


#define panic(...) {                                            \
    fprintf(stderr, "%s:%d: ",                                  \
            __extension__ __FUNCTION__,__extension__ __LINE__); \
    fprintf(stderr, __VA_ARGS__); exit(1);                      \
}

#define info(...) { fprintf(stdout, __VA_ARGS__); exit(1); }

#define test_start() { printf("%s - starting\n", __extension__ __FUNCTION__); }
#define test_ok() { printf("%s - ok\n", __extension__ __FUNCTION__); }

#define some(x) char x[100]; snprintf(x, sizeof(x), #x "%.5u", rand() % 1000);

#define exec_and_expect_ok(...)                                             \
{                                                                           \
    char q[1024];                                            \
    snprintf(q, 1024, __VA_ARGS__);                          \
    PGresult* r = PQexec(conn, q);                                          \
    if(PQresultStatus(r) != PGRES_COMMAND_OK) {                             \
        panic("error while executing %s:%s\n", q, PQresultErrorMessage(r)); \
    }                                                                       \
    PQclear(r);                                                             \
}

#define exec_and_expect(e, ...)                                             \
{                                                                           \
    char q[1024];                                            \
    snprintf(q, 1024, __VA_ARGS__);                          \
    PGresult* r = PQexec(conn, q);                                          \
    if(PQresultStatus(r) != PGRES_TUPLES_OK) {                              \
        panic("error while executing %s:%s\n", q, PQresultErrorMessage(r)); \
    }                                                                       \
    e                                                                       \
    PQclear(r);                                                             \
}

const char* conninfo();

#define TABLE_NAME_LENGTH 8
void fresh_table(PGconn* conn, char* tbl, size_t n);

#endif
