
add_library(EOP_Attendance
        EOP_Attendance.c
        EOP_Attendance.h
        controller/controllers_register.c
        controller/controllers_register.h
        db/tables/EOP_Attendance_Table.c
        db/tables/EOP_Attendance_Table.h
        db/dao/EOP_Attendance_Dao.c
        db/dao/EOP_Attendance_Dao.h
        mapper/EOP_Attendance_mapper.c
        mapper/EOP_Attendance_mapper.h
        service/EOP_Attendance_service.c
        service/EOP_Attendance_service.h
)

target_include_directories(EOP_Attendance PUBLIC ${CMAKE_SOURCE_DIR})
