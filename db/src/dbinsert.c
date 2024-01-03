#include "../headers/dbinsert.h"




int db_connectdb() {
    struct dbconn_info *info = (struct dbconn_info *) malloc(sizeof(*info));
    info->user = get_property_from_file(NULL, "user");
    info->dbname = get_property_from_file(NULL, "dbname");
    info->password = get_property_from_file(NULL, "password");

    char con_inf[256] = {0};

    snprintf(con_inf, 256, "user=%s dbname=%s password=%s",
            get_property_from_file(NULL, "user"),
            get_property_from_file(NULL, "dbname"),
            get_property_from_file(NULL, "password")
            );

    PGconn *conn;

    return 0;
}
