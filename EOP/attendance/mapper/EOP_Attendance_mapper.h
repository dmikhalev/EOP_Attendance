#ifndef EOP_EOP_ATTENDANCE_MAPPER_H
#define EOP_EOP_ATTENDANCE_MAPPER_H

#include "EOP/attendance/EOP_Attendance.h"
#include <third_party/mongoose.h>
#include <third_party/sqlite3.h>

EOP_Attendance to_model(struct mg_str json);

char *to_json(EOP_Attendance *attendance);

#endif //EOP_EOP_ATTENDANCE_MAPPER_H
