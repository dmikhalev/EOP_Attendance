#include <EOP/attendance/EOP_Attendance.h>
#include <EOP/attendance/db/dao/EOP_Attendance_Dao.h>
#include <EOP/attendance/controller/controllers_register.h>

void api_matcher(struct mg_connection *pConnection, struct mg_http_message *pMessage) {
    api_match(pConnection, pMessage);
}

int create_attendance_db(sqlite3 *db, char **err_msg) {
    return EOP_Attendance_Dao_create(db, err_msg);
}