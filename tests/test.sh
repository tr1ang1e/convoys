#!/bin/bash

errormassage()
{
  echo "- $1 compilation failed"
}

# default options
output=0              # 0 = to file ; 1 = to terminal

# arguments processing
if [[ -n $1 ]] 
then
  if [ $1 == "-term" ]
  then let output=1
  else
    echo "- wrong option"
    exit 1
  fi
fi

#compiler options
std="-std=c++20"
gtestlibs="-lgtest -lgtest_main -lpthread"
libpath="../lib/"
exename="_runtests"

#other variables
libname="test"      # spaces are permitted
control=0

echo -e

# compile GridClass class
if g++ $std -c _GridClass.cpp -o _GridClass.o
then 
  echo "+ class GridClass object file compilation succeed"
  let "control++"
else
  errormassage "class GridClass"
fi

# compile Print class
if g++ $std -c _Print.cpp -o _Print.o
then 
  echo "+ class Print object file compilation succeed"
  let "control++"
else
  errormassage "class Print"
fi

# compile FunctHelper
if g++ $std -c _FunctHelper.cpp -o _FunctHelper.o
then
  echo "+ helper object file compilation succeed"
  let "control++"
else
  errormassage "helper"
fi

# create static project library
if ar rc lib$libname.a _GridClass.o _Print.o _FunctHelper.o
then
  echo "+ project static library creation succeed"
  mv -f ./lib$libname.a "$libpath"
  let "control++"
else
  errormassage "project static library"
fi

# compile gtests
if g++ $std -c gtests.cpp -o _gtests.o
then 
  echo "+ gtests object file compilation succeed"
  let "control++"
else 
  errormassage "gtests"
fi

# if both project and gtests are compiled then build tests
if [[ $control -eq 5 ]]
then

  # if linking succeed
  if g++ _gtests.o $gtestlibs -L"$libpath" -l$libname -o $exename
  then

    echo "+ test building succeed"
    echo "+ running tests "

    # prepare logfile ang execute test
    logfile="./_testlog.txt"
    if [[ $output -eq 1 ]]
    then ./$exename                  # file output
    else ./$exename &> "$logfile"    # std  output
    fi
    result=$?    # $? contains the last command return code

    # if test succeed ( RUN_ALL_TESTS() returned 0 value )
    if [[ $result -ne 0 ]]
    then echo "- gtests failed"
    else  # print final test state
      if [[ $output -eq 0 ]]
      then
        echo "+ gtests succeed (> $logfile)"
        echo -e
        tostdout="Global test environment tear-down"
        awk "/.*${tostdout}.*/,/^$/" "$logfile"
      fi
    fi

  else errormassage "linking stage of"
  fi

fi

# clean directory
echo -e
if rm _gtests.o _Print.o _GridClass.o _FunctHelper.o
then echo "+ directory cleaned"
else echo "- directory not cleaned"
fi