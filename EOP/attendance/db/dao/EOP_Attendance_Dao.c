#include <EOP/attendance/db/dao/EOP_Attendance_Dao.h>

EOP_Attendance_err_code EOP_Attendance_Dao_create(sqlite3 *db, char **err_msg) {
    return sqlite3_exec(db, EOP_Attendance_Table_create, 0, 0, err_msg);
}

static bool isOk(int rc) {
    return rc == SQLITE_OK;
}

static int check_error(int rc, sqlite3 *db) {
    if (rc != SQLITE_DONE) {
        printf("SQL error");
        sqlite3_free(0);
        sqlite3_close(db);
        return 1;
    }
    return 0;
}

EOP_Attendance_err_code EOP_Attendance_Dao_save_attendance(EOP_Attendance attendance) {
    sqlite3 *db;
    int rc = sqlite3_open("attendance.db", &db);
    if (!isOk(rc)) {
        sqlite3_close(db);
        return 1;
    }

    sqlite3_stmt *stmt;
    sqlite3_prepare_v2(db,
                       "INSERT INTO attendance (student_id, subject_id, course, is_visit, \"date\") VALUES (?, ?, ?, ?, ?)",
                       -1, &stmt, 0);
    sqlite3_bind_int(stmt, 1, attendance.student_id);
    sqlite3_bind_int(stmt, 2, attendance.subject_id);
    sqlite3_bind_int(stmt, 3, attendance.course);
    sqlite3_bind_int(stmt, 4, attendance.is_visit);
    sqlite3_bind_text(stmt, 5, attendance.date, -1, SQLITE_TRANSIENT);

    rc = sqlite3_step(stmt);
    sqlite3_finalize(stmt);
    if (check_error(rc, db) == 1) return 1;
    sqlite3_close(db);
    return 0;
}

EOP_Attendance_err_code EOP_Attendance_Dao_save_attendance_list(struct mg_str attendanceList) {
    sqlite3 *db;
    int rc = sqlite3_open("attendance.db", &db);
    if (!isOk(rc)) {
        sqlite3_close(db);
        return 1;
    }

    size_t ofs = 0;
    struct mg_str key, val;
    while ((ofs = mg_json_next(attendanceList, ofs, &key, &val)) > 0) {
        sqlite3_stmt *stmt;
        sqlite3_prepare_v2(db,
                           "INSERT INTO attendance (student_id, subject_id, course, is_visit, \"date\") VALUES (?, ?, ?, ?, ?)",
                           -1, &stmt, 0);
        EOP_Attendance attendance = EOP_Attendance_Mapper_to_attendance(val);
        sqlite3_bind_int(stmt, 1, attendance.student_id);
        sqlite3_bind_int(stmt, 2, attendance.subject_id);
        sqlite3_bind_int(stmt, 3, attendance.course);
        sqlite3_bind_int(stmt, 4, attendance.is_visit);
        sqlite3_bind_text(stmt, 5, attendance.date, -1, SQLITE_TRANSIENT);

        rc = sqlite3_step(stmt);
        sqlite3_finalize(stmt);
        if (check_error(rc, db) == 1) return 1;
    }
    sqlite3_close(db);
    return 0;
}

char *EOP_Attendance_Dao_get_attendance_list(EOP_Attendance filter) {
    sqlite3 *db;
    int rc = sqlite3_open("attendance.db", &db);
    if (!isOk(rc)) {
        sqlite3_close(db);
        return NULL;
    }

    sqlite3_stmt *stmt;
    sqlite3_prepare_v2(db,
                       "SELECT id, student_id, subject_id, course, is_visit, date\n"
                       "FROM attendance\n"
                       "WHERE (?1 = -1 OR ?1 = student_id)\n"
                       "  AND (?2 = -1 OR ?2 = subject_id)\n"
                       "  AND (?3 = -1 OR ?3 = course)\n"
                       "  AND (?4 IS NULL OR ?4 = is_visit)\n"
                       "  AND (?5 IS NULL OR ?5 = date)",
                       -1, &stmt, 0);
    sqlite3_bind_int(stmt, 1, filter.student_id);
    sqlite3_bind_int(stmt, 2, filter.subject_id);
    sqlite3_bind_int(stmt, 3, filter.course);
    sqlite3_bind_int(stmt, 4, filter.is_visit);
    sqlite3_bind_text(stmt, 5, filter.date, -1, SQLITE_TRANSIENT);

    rc = sqlite3_step(stmt);
    char response[256 * 100];
    while (rc == SQLITE_ROW) {
        EOP_Attendance attendance;
        attendance.id = sqlite3_column_int(stmt, 0);
        attendance.student_id = sqlite3_column_int(stmt, 1);
        attendance.subject_id = sqlite3_column_int(stmt, 2);
        attendance.course = sqlite3_column_int(stmt, 3);
        attendance.is_visit = sqlite3_column_int(stmt, 4);
        attendance.date = sqlite3_column_text(stmt, 5);
        rc = sqlite3_step(stmt);
        if (rc == SQLITE_ROW) {
            sprintf(response, "%s\n%s,", response, EOP_Attendance_Mapper_to_json(&attendance));
        } else {
            sprintf(response, "%s\n%s", response, EOP_Attendance_Mapper_to_json(&attendance));
        }
    }
    sprintf(response, "%s\n]", response);
    sqlite3_finalize(stmt);
    if (check_error(rc, db) == 1) return "";
    sqlite3_close(db);

    return response;
}

EOP_Attendance_err_code EOP_Attendance_Dao_update_attendance(EOP_Attendance attendance) {
    sqlite3 *db;
    int rc = sqlite3_open("attendance.db", &db);
    if (!isOk(rc)) {
        sqlite3_close(db);
        return 1;
    }

    sqlite3_stmt *stmt;
    sqlite3_prepare_v2(db,
                       "UPDATE attendance SET student_id = ?, subject_id = ?, course = ?, is_visit = ?, \"date\" = ? WHERE id = ?",
                       -1, &stmt, 0);
    sqlite3_bind_int(stmt, 1, attendance.student_id);
    sqlite3_bind_int(stmt, 2, attendance.subject_id);
    sqlite3_bind_int(stmt, 3, attendance.course);
    sqlite3_bind_int(stmt, 4, attendance.is_visit);
    sqlite3_bind_text(stmt, 5, attendance.date, -1, SQLITE_TRANSIENT);
    sqlite3_bind_int(stmt, 6, attendance.id);

    rc = sqlite3_step(stmt);
    sqlite3_finalize(stmt);
    if (check_error(rc, db) == 1) return 1;
    sqlite3_close(db);
    return 0;
}

EOP_Attendance_err_code EOP_Attendance_Dao_delete_attendance(long attendance_id) {
    sqlite3 *db;
    int rc = sqlite3_open("attendance.db", &db);
    if (!isOk(rc)) {
        sqlite3_close(db);
        return 1;
    }

    sqlite3_stmt *stmt;
    sqlite3_prepare_v2(db,
                       "DELETE FROM attendance WHERE id = ?",
                       -1, &stmt, 0);
    sqlite3_bind_int(stmt, 1, attendance_id);

    rc = sqlite3_step(stmt);
    sqlite3_finalize(stmt);
    if (check_error(rc, db) == 1) return 1;
    sqlite3_close(db);
    return 0;
}

EOP_Attendance_err_code EOP_Attendance_Dao_delete_student_attendance(long student_id) {
    sqlite3 *db;
    int rc = sqlite3_open("attendance.db", &db);
    if (!isOk(rc)) {
        sqlite3_close(db);
        return 1;
    }

    sqlite3_stmt *stmt;
    sqlite3_prepare_v2(db,
                       "DELETE FROM attendance WHERE student_id = ?",
                       -1, &stmt, 0);
    sqlite3_bind_int(stmt, 1, student_id);

    rc = sqlite3_step(stmt);
    sqlite3_finalize(stmt);
    if (check_error(rc, db) == 1) return 1;
    sqlite3_close(db);
    return 0;
}

EOP_Attendance_err_code EOP_Attendance_Dao_delete_subject_attendance(long subject_id) {
    sqlite3 *db;
    int rc = sqlite3_open("attendance.db", &db);
    if (!isOk(rc)) {
        sqlite3_close(db);
        return 1;
    }

    sqlite3_stmt *stmt;
    sqlite3_prepare_v2(db,
                       "DELETE FROM attendance WHERE subject_id = ?",
                       -1, &stmt, 0);
    sqlite3_bind_int(stmt, 1, subject_id);

    rc = sqlite3_step(stmt);
    sqlite3_finalize(stmt);
    if (check_error(rc, db) == 1) return 1;
    sqlite3_close(db);
    return 0;
}

int EOP_Attendance_Dao_get_visit_count(EOP_Attendance_Count_request request) {
    sqlite3 *db;
    int rc = sqlite3_open("attendance.db", &db);
    if (!isOk(rc)) {
        sqlite3_close(db);
        return -1;
    }

    sqlite3_stmt *stmt;
    sqlite3_prepare_v2(db,
                       "SELECT count(*)\n"
                       "FROM attendance\n"
                       "WHERE (?1 = -1 OR ?1 = student_id)\n"
                       "  AND (?2 = -1 OR ?2 = subject_id)\n"
                       "  AND (?3 = -1 OR ?3 = course)\n"
                       "  AND is_visit = 1\n",
                       -1, &stmt, 0);
    sqlite3_bind_int(stmt, 1, request.student_id);
    sqlite3_bind_int(stmt, 2, request.subject_id);
    sqlite3_bind_int(stmt, 3, request.course);

    rc = sqlite3_step(stmt);
    int result = sqlite3_column_int(stmt, 0);
    sqlite3_finalize(stmt);
    if (check_error(rc, db) == 1) return -1;
    sqlite3_close(db);
    return result;
}

int EOP_Attendance_Dao_get_absence_count(EOP_Attendance_Count_request request) {
    sqlite3 *db;
    int rc = sqlite3_open("attendance.db", &db);
    if (!isOk(rc)) {
        sqlite3_close(db);
        return -1;
    }

    sqlite3_stmt *stmt;
    sqlite3_prepare_v2(db,
                       "SELECT count(*)\n"
                       "FROM attendance\n"
                       "WHERE (?1 = -1 OR ?1 = student_id)\n"
                       "  AND (?2 = -1 OR ?2 = subject_id)\n"
                       "  AND (?3 = -1 OR ?3 = course)\n"
                       "  AND is_visit = 0\n",
                       -1, &stmt, 0);
    sqlite3_bind_int(stmt, 1, request.student_id);
    sqlite3_bind_int(stmt, 2, request.subject_id);
    sqlite3_bind_int(stmt, 3, request.course);

    rc = sqlite3_step(stmt);
    int result = sqlite3_column_int(stmt, 0);
    sqlite3_finalize(stmt);
    if (check_error(rc, db) == 1) return -1;
    sqlite3_close(db);
    return result;
}