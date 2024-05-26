#include <EOP/attendance/db/dao/EOP_Attendance_Dao.h>


bool is_post(struct mg_str method) {
    // todo return strcmp(method.buf, "POST") == 0;
    return true;
}

bool is_get(struct mg_str method) {
    // todo return strcmp(method.buf, "GET") == 0;
    return true;
}

bool is_put(struct mg_str method) {
    // todo return strcmp(method.buf, "PUT") == 0;
    return true;
}

bool is_delete(struct mg_str method) {
    // todo return strcmp(method.buf, "DELETE") == 0;
    return true;
}

void handle_get_all(struct mg_connection *pConnection, struct mg_http_message *pMessage) {
    char *response = EOP_Get_attendance_list(to_model(pMessage->body));
    if (response != NULL) {
        mg_http_reply(pConnection, 200, "Content-Type: application/json\r\n", "%s", MG_ESC(response));
    } else {
        mg_http_reply(pConnection, 400, "", "Error");
    }
}

void handle_create_one(struct mg_connection *pConnection, struct mg_http_message *pMessage) {
    if (EOP_Save_attendance(to_model(pMessage->body)) == 0) {
        mg_http_reply(pConnection, 201, "", "Success");
    } else {
        mg_http_reply(pConnection, 400, "", "Error");
    }
}

void handle_create_list(struct mg_connection *pConnection, struct mg_http_message *pMessage) {
    if (EOP_Save_attendance_list(pMessage->body) == 0) {
        mg_http_reply(pConnection, 201, "", "Success");
    } else {
        mg_http_reply(pConnection, 400, "", "Error");
    }
}

void handle_update(struct mg_connection *pConnection, struct mg_http_message *pMessage) {
    if (EOP_Update_attendance(to_model(pMessage->body)) == 0) {
        mg_http_reply(pConnection, 200, "", "Success");
    } else {
        mg_http_reply(pConnection, 400, "", "Error");
    }
}

void handle_delete(struct mg_connection *pConnection, struct mg_http_message *pMessage) {
    if (EOP_Delete_attendance(mg_json_get_long(pMessage->body, "$.id", -1)) == 0) {
        mg_http_reply(pConnection, 200, "", "Success");
    } else {
        mg_http_reply(pConnection, 400, "", "Error");
    }
}

void handle_attendance(struct mg_connection *pConnection, struct mg_http_message *pMessage) {
    // GET get all
    if (mg_match(pMessage->uri, mg_str("/api/attendance/all"), NULL) && is_get(pMessage->method)) {
        handle_get_all(pConnection, pMessage);
    }

    // POST create row
    if (mg_match(pMessage->uri, mg_str("/api/attendance/one"), NULL) && is_post(pMessage->method)) {
        handle_create_one(pConnection, pMessage);
    }

    // POST create rows
    if (mg_match(pMessage->uri, mg_str("/api/attendance/list"), NULL) && is_post(pMessage->method)) {
        handle_create_list(pConnection, pMessage);
    }

    // PUT create rows
    if (mg_match(pMessage->uri, mg_str("/api/attendance/update"), NULL) && is_put(pMessage->method)) {
        handle_update(pConnection, pMessage);
    }

    // DELETE create rows
    if (mg_match(pMessage->uri, mg_str("/api/attendance/delete"), NULL) && is_delete(pMessage->method)) {
        handle_delete(pConnection, pMessage);
    }
}

void api_match(struct mg_connection *pConnection, struct mg_http_message *pMessage) {
    if (mg_match(pMessage->uri, mg_str("/api/attendance#"), NULL)) {
        handle_attendance(pConnection, pMessage);
    } else {
        struct mg_http_serve_opts opts = {.root_dir = "."};     // For all other URLs,
        mg_http_serve_dir(pConnection, pMessage, &opts);    // Serve static files
    }
}
