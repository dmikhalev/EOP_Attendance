#include <third_party/mongoose.h>
#include <third_party/sqlite3.h>
#include <EOP/attendance/EOP_Attendance.h>


static int create_db() {
    sqlite3 *db;
    char *err_msg = 0;
    int rc = sqlite3_open("attendance.db", &db);
    if (rc != SQLITE_OK) {
        sqlite3_close(db);
        return 1;
    }

    rc = create_attendance_db(db, &err_msg);
    if (rc != SQLITE_OK) {
        printf("SQL error: %s\n", err_msg);
        sqlite3_free(err_msg);
        sqlite3_close(db);
        return 1;
    }
    sqlite3_close(db);
    return 0;
}

static void fn(struct mg_connection *c, int ev, void *ev_data) {
    if (ev == MG_EV_HTTP_MSG) {  // New HTTP request received
        struct mg_http_message *hm = (struct mg_http_message *) ev_data;// Parsed HTTP request
        api_matcher(c, hm);
    }
}

int main() {
    create_db();
    struct mg_mgr mgr;  // Mongoose event manager. Holds all connections
    mg_mgr_init(&mgr);  // Initialise event manager
    mg_http_listen(&mgr, "http://localhost:8083", fn, NULL);  // Setup listener

    for (;;) {
        mg_mgr_poll(&mgr, 1000);  // Infinite event loop
    }
    return 0;
}


