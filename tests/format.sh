#!/bin/bash

# GTESTS : format gtests files
clang-format gtests.cpp > _gtests.cpp
clang-format ../src/MacroHelper.hpp > ../src/_MacroHelper.hpp
clang-format ../src/FunctHelper.hpp > ../src/_FunctHelper.hpp

# GTESTS : replace current gtests files with formatted
cp -f _gtests.cpp gtests.cpp
cp -f ../src/_MacroHelper.hpp ../src/MacroHelper.hpp
cp -f ../src/_FunctHelper.hpp ../src/FunctHelper.hpp

# GTESTS : remove temporary gtests files
rm _gtests.cpp
rm ../src/_MacroHelper.hpp
rm ../src/_FunctHelper.hpp

# PROJECT : format project files
clang-format _GreedClass.cpp > GreedClass.cpp
clang-format _Print.cpp > Print.cpp
clang-format ../src/GreedClass.hpp > ../src/_GreedClass.hpp
clang-format ../src/Print.hpp > ../src/_Print.hpp

# PROJECT : replace current project files with formatted
cp -f GreedClass.cpp _GreedClass.cpp
cp -f Print.cpp _Print.cpp 
cp -f ../src/_GreedClass.hpp ../src/GreedClass.hpp 
cp -f ../src/_Print.hpp ../src/Print.hpp 

# PROJECT : remove temporary project files
rm GreedClass.cpp
rm Print.cpp
rm ../src/_GreedClass.hpp
rm ../src/_Print.hpp