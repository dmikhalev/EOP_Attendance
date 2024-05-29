#ifndef EOP_COURSE_Table_H
#define EOP_COURSE_Table_H


#define ATTENDANCE "attendance"

char *EOP_Attendance_Table_create = "CREATE TABLE IF NOT EXISTS " ATTENDANCE " (\n"
                                    "    id INTEGER PRIMARY KEY AUTOINCREMENT,\n"
                                    "    student_id INTEGER,\n"
                                    "    subject_id INTEGER,\n"
                                    "    course INTEGER,\n"
                                    "    is_visit BOOLEAN,\n"
                                    "    date DATE"
                                    ")";

#endif //EOP_COURSE_Table_H
