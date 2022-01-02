#!/bin/bash

# GTESTS : format gtests files
clang-format gtests.cpp > _gtests.cpp
clang-format ../src/MacroHelper.hpp > ../src/_MacroHelper.hpp
clang-format ../src/FunctHelper.hpp > ../src/_FunctHelper.hpp
clang-format _FunctHelper.cpp > FunctHelper.cpp

# GTESTS : replace current gtests files with formatted
cp -f _gtests.cpp gtests.cpp
cp -f ../src/_MacroHelper.hpp ../src/MacroHelper.hpp
cp -f ../src/_FunctHelper.hpp ../src/FunctHelper.hpp
cp -f FunctHelper.cpp _FunctHelper.cpp

# GTESTS : remove temporary gtests files
rm _gtests.cpp
rm ../src/_MacroHelper.hpp
rm ../src/_FunctHelper.hpp
rm FunctHelper.cpp

# PROJECT : format project files
clang-format _GridClass.cpp > GridClass.cpp
clang-format _PrintClass.cpp > PrintClass.cpp
clang-format ../src/GridClass.hpp > ../src/_GridClass.hpp
clang-format ../src/PrintClass.hpp > ../src/_PrintClass.hpp

# PROJECT : replace current project files with formatted
cp -f GridClass.cpp _GridClass.cpp
cp -f PrintClass.cpp _PrintClass.cpp 
cp -f ../src/_GridClass.hpp ../src/GridClass.hpp 
cp -f ../src/_PrintClass.hpp ../src/PrintClass.hpp 

# PROJECT : remove temporary project files
rm GridClass.cpp
rm PrintClass.cpp
rm ../src/_GridClass.hpp
rm ../src/_PrintClass.hpp