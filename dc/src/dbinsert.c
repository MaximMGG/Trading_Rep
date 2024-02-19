#include "../headers/dbinsert.h"
#include <libpq-fe.h>

#define PROPERTY_LEN 1024

static PGconn *conn = NULL;

PGconn *db_connectdb(str *con) {

    conn = PQconnectdb(con->str);
    if (PQstatus(conn) != CONNECTION_OK) {
        fprintf(stderr, "Connection to db error %s", PQerrorMessage(conn));
    }

    return conn;
}

int db_insert_ticker_response(str *resp) {
    PGresult *res;
    res = PQexec(conn, resp->str);

    if (PQresultStatus(res) != PGRES_COMMAND_OK) {
        fprintf(stderr, "Con not insert in db %s\n", PQerrorMessage(conn));
    }
    PQclear(res);
    return 0;
};

void db_finish(PGconn *conn) {
    PQfinish(conn);
}
