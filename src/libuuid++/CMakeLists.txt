target_sources(uuid++
    PRIVATE
        uuid.cpp
)

if(PROJECT_TESTING)
    target_sources(uuid++.test
        PRIVATE
            uuid.test.cpp
    )
endif()
