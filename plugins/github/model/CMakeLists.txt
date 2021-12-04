set(ODB_SOURCES
        include/model/comment.h
        include/model/commit.h
        include/model/commitfile.h
        include/model/issue.h
        include/model/label.h
        include/model/milestone.h
        include/model/person.h
        include/model/pull.h
        include/model/pullfile.h
        include/model/review.h)

generate_odb_files("${ODB_SOURCES}")

add_odb_library(githubmodel ${ODB_CXX_SOURCES})
add_dependencies(githubmodel model)

install_sql()