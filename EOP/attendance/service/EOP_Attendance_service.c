#include <EOP/attendance/db/dao/EOP_Attendance_Dao.h>
#include <EOP/attendance/service/EOP_Attendance_service.h>

static int validate_id(long id) {
    if (id < 1) {
        printf("incorrect id");
        return 1;
    }
    return 0;
}

static int validate_student_id(long student_id) {
    if (student_id < 1) {
        printf("incorrect student_id");
        return 1;
    }
    return 0;
}

static int validate_subject_id(long subject_id) {
    if (subject_id < 1) {
        printf("incorrect subject_id");
        return 1;
    }
    return 0;
}

static int validate_course(int course) {
    if (course < 1) {
        printf("incorrect course");
        return 1;
    }
    return 0;
}

static int validate_date(const char *date) {
    if (strlen(date) < 8 || strlen(date) > 10) {
        printf("incorrect date");
        return 1;
    }
    return 0;
}

static int validate_attendance(EOP_Attendance attendance) {
    if (validate_student_id(attendance.student_id) == 1) return 1;
    if (validate_subject_id(attendance.subject_id) == 1) return 1;
    if (validate_course(attendance.course) == 1) return 1;
    if (validate_date(attendance.date) == 1) return 1;
    return 0;
}


static int validate_count_request(Count_request request) {
    if (validate_student_id(request.student_id) == 1) return 1;
    if (validate_subject_id(request.subject_id) == 1) return 1;
    if (validate_course(request.course) == 1) return 1;
    return 0;
}

static int validate_delete_attendance_request(Delete_attendance_request request) {
    if (validate_id(request.id) == 1) return 1;
    return 0;
}

static int validate_delete_student_attendance_request(Delete_student_attendance_request request) {
    if (validate_student_id(request.student_id) == 1) return 1;
    return 0;
}

static int validate_delete_subject_attendance_request(Delete_subject_attendance_request request) {
    if (validate_subject_id(request.subject_id) == 1) return 1;
    return 0;
}

int EOP_Attendance_Service_save_attendance(EOP_Attendance attendance) {
    if (validate_attendance(attendance) == 1) return 1;
    int result = EOP_Attendance_Dao_save_attendance(attendance);
    printf("Attendance saved");
    return result;
}

int EOP_Attendance_Service_save_attendance_list(struct mg_str attendanceList) {
    int result = EOP_Attendance_Dao_save_attendance_list(attendanceList);
    printf("Attendance list saved");
    return result;
}

char *EOP_Attendance_Service_get_attendance_list(EOP_Attendance filter) {
    printf("Getting attendance list");
    return EOP_Attendance_Dao_get_attendance_list(filter);
}

int EOP_Attendance_Service_update_attendance(EOP_Attendance attendance) {
    if (validate_attendance(attendance) == 1) return 1;
    if (validate_id(attendance.id) == 1) return 1;
    int result = EOP_Attendance_Dao_update_attendance(attendance);
    printf("Attendance updated");
    return result;
}

int EOP_Attendance_Service_delete_attendance(Delete_attendance_request request) {
    if (validate_delete_attendance_request(request) == 1) return 1;
    int result = EOP_Attendance_Dao_delete_attendance(request.id);
    printf("Attendance deleted");
    return result;
}

int EOP_Attendance_Service_delete_student_attendance(Delete_student_attendance_request request) {
    if (validate_delete_student_attendance_request(request) == 1) return 1;
    int result = EOP_Attendance_Dao_delete_student_attendance(request.student_id);
    printf("Student attendance deleted");
    return result;
}

int EOP_Attendance_Service_delete_subject_attendance(Delete_subject_attendance_request request) {
    if (validate_delete_subject_attendance_request(request) == 1) return 1;
    int result = EOP_Attendance_Dao_delete_subject_attendance(request.subject_id);
    printf("Subject attendance deleted");
    return result;
}

int EOP_Attendance_Service_get_count_visit(Count_request request) {
    if (validate_count_request(request) == 1) return 1;
    int result = EOP_Attendance_Dao_get_visit_count(request);
    printf("Visit count calculated");
    return result;
}

int EOP_Attendance_Service_get_count_absence(Count_request request) {
    if (validate_count_request(request) == 1) return 1;
    int result = EOP_Attendance_Dao_get_absence_count(request);
    printf("Absence count calculated");
    return result;
}