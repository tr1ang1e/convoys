#!/bin/bash

# GTESTS : format gtests files
clang-format gtests.cpp > _gtests.cpp
clang-format ../src/helper.hpp > ../src/_helper.hpp

# GTESTS : replace current gtests files with formatted
cp -f _gtests.cpp gtests.cpp
cp -f ../src/_helper.hpp ../src/helper.hpp

# GTESTS : remove temporary gtests files
rm _gtests.cpp
rm ../src/_helper.hpp

# PROJECT : format project files
clang-format _Count.cpp > Count.cpp
clang-format _Print.cpp > Print.cpp
clang-format ../src/Count.hpp > ../src/_Count.hpp
clang-format ../src/Print.hpp > ../src/_Print.hpp

# PROJECT : replace current project files with formatted
cp -f Count.cpp _Count.cpp
cp -f Print.cpp _Print.cpp 
cp -f ../src/_Count.hpp ../src/Count.hpp 
cp -f ../src/_Print.hpp ../src/Print.hpp 

# PROJECT : remove temporary project files
rm Count.cpp
rm Print.cpp
rm ../src/_Count.hpp
rm ../src/_Print.hpp