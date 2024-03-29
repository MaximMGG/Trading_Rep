#ifndef _DB_INSERT_H_
#define _DB_INSERT_H_
#include <util/util.h>
#include <util/pr_map.h>
#include <libpq-fe.h>
#include <stdio.h>
#include "../../service/headers/getservice.h"
#include <util/m_string.h>


struct dbconn_info {
    char *user;
    char *dbname;
    char *password;
};

//init connect to db
int db_connectdb(str *con);
//free resourses
void db_finish();

//insert in db Response **resp
int db_insert_ticker_response(str *resp);


#endif //_DB_INSERT_H_
