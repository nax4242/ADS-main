# указывайте последнюю доступную вам версию CMake

cmake_minimum_required(VERSION 3.14)
set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

################################################################################
# убирает служебный проект ZERO_CHECK в Visual Studio (должно стоять до project)
set(CMAKE_SUPPRESS_REGENERATION ON)

# включает папки (фильтры) в обозревателе решений Visual Studio
set_property(GLOBAL PROPERTY USE_FOLDERS ON)
################################################################################

# название проекта
project(DataStructure)

# затем следует список инструкций для подключения проектов из подкаталогов

include(cmake/function.cmake)         # подхватываем функции, реализованные в файле function.cmake
                                      # для простоты мы объединили наборы команд для создания статической библиотеки
								      # и для создания исполняемого проекта в отдельные функции

add_subdirectory(lib_algorithms)    # подключаем дополнительный CMakeLists.txt из подкаталога с именем lib_easy_example

add_subdirectory(lib_vector)          # подключаем вектор

add_subdirectory(lib_stack_on_mass)   # подключаем стек на массиве

add_subdirectory(lib_queue_on_mass)   # подключаем очередь на массиве

add_subdirectory(lib_set)             # подключаем множество

add_subdirectory(lib_multi_stack)     # подключаем мульти стек

add_subdirectory(lib_list)            # подключаем односвязный список

add_subdirectory(main)                # подключаем дополнительный CMakeLists.txt из подкаталога с именем main

option(BTEST "build test?" ON)        # указываем подключаем ли google-тесты (ON или YES) или нет (OFF или NO)

if(BTEST)                             # если тесты подключены         
    set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
    add_subdirectory("third_party/gtest" EXCLUDE_FROM_ALL)
    enable_testing()
    add_subdirectory(tests)

###########################################################################
    # прячем gtest и gtest_main в папку third_party
    set_target_properties(gtest gtest_main PROPERTIES FOLDER "third_party")
###########################################################################

endif()

#################################################################
# ALL_BUILD, INSTALL, RUN_TESTS складываем в одну свёрнутую папку
set_property(GLOBAL PROPERTY PREDEFINED_TARGETS_FOLDER "CMake")

# стартовый проект для запуска по F5
set_property(DIRECTORY PROPERTY VS_STARTUP_PROJECT Application)
#################################################################