#ifndef EOP_EOP_ATTENDANCE_CONTROLLER_H
#define EOP_EOP_ATTENDANCE_CONTROLLER_H

#include <third_party/mongoose.h>
#include <EOP/attendance/db/dao/EOP_Attendance_Dao.h>
#include <EOP/attendance/mapper/EOP_Attendance_mapper.h>

#ifdef __cplusplus
extern "C" {
#endif


void EOP_Attendance_Controller_api_match(struct mg_connection *pConnection, struct mg_http_message *pMessage);

#ifdef __cplusplus
}
#endif

#endif //EOP_EOP_ATTENDANCE_CONTROLLER_H
