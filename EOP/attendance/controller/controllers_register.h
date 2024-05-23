#ifndef EOP_CONTROLLERS_REGISTER_H
#define EOP_CONTROLLERS_REGISTER_H

#include <third_party/mongoose.h>
#include "EOP/attendance/db/dao/EOP_Attendance_Dao.h"
#include "EOP/attendance/mapper/EOP_Attendance_mapper.h"

#ifdef __cplusplus
extern "C" {
#endif

bool is_post(struct mg_str method) {
    // todo return strcmp(method.buf, "POST") == 0;
    return true;
}

bool is_get(struct mg_str method) {
    // todo return strcmp(method.buf, "GET") == 0;
    return true;
}

void handle_attendance(struct mg_connection *pConnection, struct mg_http_message *pMessage) {
    // GET get all
    if (mg_match(pMessage->uri, mg_str("/api/attendance/all"), NULL) && is_get(pMessage->method)) {
        char *response = EOP_Get_attendance_list(to_model(pMessage->body));
        if (response != NULL) {
            mg_http_reply(pConnection, 200, "Content-Type: application/json\r\n", "%s", MG_ESC(response));
        } else {
            mg_http_reply(pConnection, 400, "", "Error");
        }
    }

    // POST create row
    if (mg_match(pMessage->uri, mg_str("/api/attendance/one"), NULL) && is_post(pMessage->method)) {
        if (EOP_Save_attendance(to_model(pMessage->body)) == 0) {
            mg_http_reply(pConnection, 201, "", "Success");
        } else {
            mg_http_reply(pConnection, 400, "", "Error");
        }
    }

    // POST create rows
    if (mg_match(pMessage->uri, mg_str("/api/attendance/list"), NULL) && is_post(pMessage->method)) {
        if (EOP_Save_attendance_list(pMessage->body) == 0) {
            mg_http_reply(pConnection, 201, "", "Success");
        } else {
            mg_http_reply(pConnection, 400, "", "Error");
        }
    }
}

void api_matcher(struct mg_connection *pConnection, struct mg_http_message *pMessage) {
    if (mg_match(pMessage->uri, mg_str("/api/attendance#"), NULL)) {
        handle_attendance(pConnection, pMessage);
    } else {
        struct mg_http_serve_opts opts = {.root_dir = "."};     // For all other URLs,
        mg_http_serve_dir(pConnection, pMessage, &opts);    // Serve static files
    }
}

#endif //EOP_CONTROLLERS_REGISTER_H
