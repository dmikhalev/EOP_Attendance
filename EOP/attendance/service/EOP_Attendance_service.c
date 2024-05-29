#include <EOP/attendance/db/dao/EOP_Attendance_Dao.h>
#include <EOP/attendance/service//EOP_Attendance_service.h>

int save_attendance(EOP_Attendance attendance) {
    int result = EOP_Save_attendance(attendance);
    printf("Attendance saved");
    return result;
}

int save_attendance_list(struct mg_str attendanceList) {
    int result = EOP_Save_attendance_list(attendanceList);
    printf("Attendance list saved");
    return result;
}

char *get_attendance_list(EOP_Attendance filter) {
    printf("Getting attendance list");
    return EOP_Get_attendance_list(filter);
}

int update_attendance(EOP_Attendance attendance) {
    int result = EOP_Update_attendance(attendance);
    printf("Attendance updated");
    return result;
}

int delete_attendance(long attendance_id) {
    int result = EOP_Delete_attendance(attendance_id);
    printf("Attendance deleted");
    return result;
}