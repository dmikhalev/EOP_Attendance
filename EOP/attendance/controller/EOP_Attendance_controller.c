#include <EOP/attendance/service/EOP_Attendance_service.h>
#include <EOP/attendance/mapper/EOP_Attendance_mapper.h>

static bool EOP_Attendance_is_post(struct mg_str method) {
    return strncmp("POST", method.buf, strlen("POST")) == 0;
}

static bool EOP_Attendance_is_get(struct mg_str method) {
    return strncmp("GET", method.buf, strlen("GET")) == 0;
}

static bool EOP_Attendance_is_put(struct mg_str method) {
    return strncmp("PUT", method.buf, strlen("PUT")) == 0;
}

static bool EOP_Attendance_is_delete(struct mg_str method) {
    return strncmp("DELETE", method.buf, strlen("DELETE")) == 0;
}

static void EOP_Attendance_error_replay(struct mg_connection *pConnection) {
    mg_http_reply(pConnection, 400, "", "Error");
}

static void EOP_Attendance_success_200_replay(struct mg_connection *pConnection) {
    mg_http_reply(pConnection, 200, "", "Success");
}

static void EOP_Attendance_success_201_replay(struct mg_connection *pConnection) {
    mg_http_reply(pConnection, 201, "", "Success");
}

static void EOP_Attendance_handle_get_all(struct mg_connection *pConnection, struct mg_http_message *pMessage) {
    char *response = EOP_Attendance_Service_get_attendance_list(EOP_Attendance_Mapper_to_attendance(pMessage->body));
    if (response != NULL) {
        mg_http_reply(pConnection, 200, "Content-Type: application/json\r\n", response);
    } else {
        EOP_Attendance_error_replay(pConnection);
    }
}

static void EOP_Attendance_handle_create_one(struct mg_connection *pConnection, struct mg_http_message *pMessage) {
    if (EOP_Attendance_Service_save_attendance(EOP_Attendance_Mapper_to_attendance(pMessage->body)) == 0) {
        EOP_Attendance_success_201_replay(pConnection);
    } else {
        EOP_Attendance_error_replay(pConnection);
    }
}

static void EOP_Attendance_handle_create_list(struct mg_connection *pConnection, struct mg_http_message *pMessage) {
    if (EOP_Attendance_Service_save_attendance_list(pMessage->body) == 0) {
        EOP_Attendance_success_201_replay(pConnection);
    } else {
        EOP_Attendance_error_replay(pConnection);
    }
}

static void EOP_Attendance_handle_update(struct mg_connection *pConnection, struct mg_http_message *pMessage) {
    if (EOP_Attendance_Service_update_attendance(EOP_Attendance_Mapper_to_attendance(pMessage->body)) == 0) {
        EOP_Attendance_success_200_replay(pConnection);
    } else {
        EOP_Attendance_error_replay(pConnection);
    }
}

static void EOP_Attendance_handle_delete_attendance(struct mg_connection *pConnection, struct mg_http_message *pMessage) {
    if (EOP_Attendance_Service_delete_attendance(EOP_Attendance_Mapper_to_delete_attendance_request(pMessage->body)) ==
        0) {
        EOP_Attendance_success_200_replay(pConnection);
    } else {
        EOP_Attendance_error_replay(pConnection);
    }
}

static void EOP_Attendance_handle_delete_student_attendance(struct mg_connection *pConnection, struct mg_http_message *pMessage) {
    if (EOP_Attendance_Service_delete_student_attendance(
            EOP_Attendance_Mapper_to_delete_student_attendance_request(pMessage->body)) == 0) {
        EOP_Attendance_success_200_replay(pConnection);
    } else {
        EOP_Attendance_error_replay(pConnection);
    }
}

static void EOP_Attendance_handle_delete_subject_attendance(struct mg_connection *pConnection, struct mg_http_message *pMessage) {
    if (EOP_Attendance_Service_delete_subject_attendance(
            EOP_Attendance_Mapper_to_delete_subject_attendance_request(pMessage->body)) == 0) {
        EOP_Attendance_success_200_replay(pConnection);
    } else {
        EOP_Attendance_error_replay(pConnection);
    }
}

static void EOP_Attendance_handle_count_visit(struct mg_connection *pConnection, struct mg_http_message *pMessage) {
    int count = EOP_Attendance_Service_get_count_visit(EOP_Attendance_Mapper_to_count_request(pMessage->body));
    mg_http_reply(pConnection, 200, "Content-Type: application/json\r\n", "%s", MG_ESC(count));
}

static void EOP_Attendance_handle_count_absence(struct mg_connection *pConnection, struct mg_http_message *pMessage) {
    int count = EOP_Attendance_Service_get_count_absence(EOP_Attendance_Mapper_to_count_request(pMessage->body));
    mg_http_reply(pConnection, 200, "Content-Type: application/json\r\n", "%s", MG_ESC(count));
}

static void EOP_Attendance_handle_attendance(struct mg_connection *pConnection, struct mg_http_message *pMessage) {
    // GET get all
    if (mg_match(pMessage->uri, mg_str("/api/attendance/all"), NULL) && EOP_Attendance_is_get(pMessage->method)) {
        EOP_Attendance_handle_get_all(pConnection, pMessage);
        return;
    }

    // POST create row
    if (mg_match(pMessage->uri, mg_str("/api/attendance/one"), NULL) && EOP_Attendance_is_post(pMessage->method)) {
        EOP_Attendance_handle_create_one(pConnection, pMessage);
        return;
    }

    // POST create rows
    if (mg_match(pMessage->uri, mg_str("/api/attendance/list"), NULL) && EOP_Attendance_is_post(pMessage->method)) {
        EOP_Attendance_handle_create_list(pConnection, pMessage);
        return;
    }

    // PUT create rows
    if (mg_match(pMessage->uri, mg_str("/api/attendance/update"), NULL) && EOP_Attendance_is_put(pMessage->method)) {
        EOP_Attendance_handle_update(pConnection, pMessage);
        return;
    }

    // DELETE delete attendance
    if (mg_match(pMessage->uri, mg_str("/api/attendance/delete"), NULL) && EOP_Attendance_is_delete(pMessage->method)) {
        EOP_Attendance_handle_delete_attendance(pConnection, pMessage);
        return;
    }

    // DELETE delete student attendance
    if (mg_match(pMessage->uri, mg_str("/api/attendance/delete/student"), NULL) &&
            EOP_Attendance_is_delete(pMessage->method)) {
        EOP_Attendance_handle_delete_student_attendance(pConnection, pMessage);
        return;
    }

    // DELETE delete subject attendance
    if (mg_match(pMessage->uri, mg_str("/api/attendance/delete/subject"), NULL) &&
            EOP_Attendance_is_delete(pMessage->method)) {
        EOP_Attendance_handle_delete_subject_attendance(pConnection, pMessage);
        return;
    }

    // GET get visit count
    if (mg_match(pMessage->uri, mg_str("/api/attendance/count/visit"), NULL) && EOP_Attendance_is_get(pMessage->method)) {
        EOP_Attendance_handle_count_visit(pConnection, pMessage);
        return;
    }

    // GET get absence count
    if (mg_match(pMessage->uri, mg_str("/api/attendance/count/absence"), NULL) &&
            EOP_Attendance_is_get(pMessage->method)) {
        EOP_Attendance_handle_count_absence(pConnection, pMessage);
        return;
    }
}

void EOP_Attendance_Controller_api_match(struct mg_connection *pConnection, struct mg_http_message *pMessage) {
    if (mg_match(pMessage->uri, mg_str("/api/attendance#"), NULL)) {
        EOP_Attendance_handle_attendance(pConnection, pMessage);
    } else {
        struct mg_http_serve_opts opts = {.root_dir = "."};     // For all other URLs,
        mg_http_serve_dir(pConnection, pMessage, &opts);    // Serve static files
    }
}
