#include <EOP/attendance/EOP_Attendance.h>
#include <EOP/attendance/db/dao/EOP_Attendance_Dao.h>
#include <EOP/attendance/controller/EOP_Attendance_controller.h>

static void EOP_Attendance_api_matcher(struct mg_connection *pConnection, struct mg_http_message *pMessage) {
    EOP_Attendance_Controller_api_match(pConnection, pMessage);
}

static EOP_Attendance_err_code EOP_Attendance_create_attendance_db(sqlite3 *db, char **err_msg) {
    return EOP_Attendance_Dao_create(db, err_msg);
}

static bool EOP_Attendance_is_ok(int rc) {
    return rc == SQLITE_OK;
}

static EOP_Attendance_err_code create_db() {
    sqlite3* db;
    char* err_msg = 0;
    int rc = sqlite3_open("attendance.db", &db);
    if (!EOP_Attendance_is_ok(rc)) {
        sqlite3_close(db);
        return 1;
    }

    rc = EOP_Attendance_create_attendance_db(db, &err_msg);
    if (!EOP_Attendance_is_ok(rc)) {
        printf("SQL error: %s\n", err_msg);
        sqlite3_free(err_msg);
        sqlite3_close(db);
        return 1;
    }
    sqlite3_close(db);
    return 0;
}

static void fn(struct mg_connection* c, int ev, void* ev_data) {
    if (ev == MG_EV_HTTP_MSG) {  // New HTTP request received
        struct mg_http_message* hm = (struct mg_http_message*)ev_data;// Parsed HTTP request
        EOP_Attendance_api_matcher(c, hm);
    }
}

int EOP_Attendance_start() {
    create_db();
    struct mg_mgr mgr;  // Mongoose event manager. Holds all connections
    mg_mgr_init(&mgr);  // Initialise event manager
    mg_http_listen(&mgr, "http://localhost:8083", fn, NULL);  // Setup listener

    for (;;) {
        mg_mgr_poll(&mgr, 1000);  // Infinite event loop
    }
    return 0;
}