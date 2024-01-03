#include "../headers/dbinsert.h"
#include <libpq-fe.h>

#define PROPERTY_LEN 2048


PGconn *db_connectdb() {
    char con_inf[256] = {0};

    snprintf(con_inf, 256, "user=%s dbname=%s password=%s",
            get_property_from_file(NULL, "user"),
            get_property_from_file(NULL, "dbname"),
            get_property_from_file(NULL, "password")
            );

    PGconn *conn = PQconnectdb(con_inf);
    if (PQstatus(conn) != CONNECTION_OK) {
        fprintf(stderr, "Connection to db error %s", PQerrorMessage(conn));
    }

    return conn;
}

//TODO (maxim) need to write whis functional!
int db_insert_ticker_response(Property **response, PGconn *conn) {
    char *insert_msg = (char *) malloc(PROPERTY_LEN);
    tryp(insert_msg);

    PGresult *res;
    
    strcpy(insert_msg, "%s");

    




    return 0;
};
