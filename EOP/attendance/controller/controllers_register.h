#ifndef EOP_CONTROLLERS_REGISTER_H
#define EOP_CONTROLLERS_REGISTER_H

#include <third_party/mongoose.h>
#include <EOP/attendance/db/dao/EOP_Attendance_Dao.h>
#include <EOP/attendance/mapper/EOP_Attendance_mapper.h>

#ifdef __cplusplus
extern "C" {
#endif

void handle_attendance(struct mg_connection *pConnection, struct mg_http_message *pMessage);

void api_match(struct mg_connection *pConnection, struct mg_http_message *pMessage);

#endif //EOP_CONTROLLERS_REGISTER_H
