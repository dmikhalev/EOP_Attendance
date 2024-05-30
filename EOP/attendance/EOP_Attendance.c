#include <EOP/attendance/EOP_Attendance.h>
#include <EOP/attendance/db/dao/EOP_Attendance_Dao.h>
#include <EOP/attendance/controller/EOP_Attendance_controller.h>

void EOP_Attendance_api_matcher(struct mg_connection *pConnection, struct mg_http_message *pMessage) {
    EOP_Attendance_Controller_api_match(pConnection, pMessage);
}

int EOP_Attendance_create_attendance_db(sqlite3 *db, char **err_msg) {
    return EOP_Attendance_Dao_create(db, err_msg);
}