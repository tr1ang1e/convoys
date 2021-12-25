#!/bin/bash

errormassage()
{
  echo "- $1 compilation failed"
}

#compiler options
std="-std=c++20"
gtestlibs="-lgtest -lgtest_main -lpthread"
exename="_runtests"

echo -e
control=0

# compile Count class
if g++ $std -c _Count.cpp -o _Count.o
then 
  echo "+ class Count object file compilation succeed"
  let "control++"
else
  errormassage "class Count"
fi

# compile Print class
if g++ $std -c _Print.cpp -o _Print.o
then 
  echo "+ class Print object file compilation succeed"
  let "control++"
else
  errormassage "class Print"
fi

# create static project library
if ar rc libproject.a _Count.o _Print.o
then
  echo "+ project static library creation succeed"
  mv -f ./libproject.a ../src/
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
if [[ $control -eq 4 ]]
then

  # if linking succeed
  if g++ _gtests.o $gtestlibs -L../src/ -lproject -o $exename
  then

    echo "+ test building succeed"
    echo "+ running test "

    # prepare logfile ang execute test
    logfile="./_testlog.txt"
    result=`./$exename &> "$logfile"` 

    # if test succeed ( RUN_ALL_TESTS() returned 0 value )
    if [[ $result -ne 0 ]]
    then echo "- gtests crashed"
    else  # print final test state
      echo "+ gtests succeed (> $logfile)"
      echo -e
      tostdout="Global test environment tear-down"
      awk "/.*${tostdout}.*/,/^$/" "$logfile"
    fi
  
    # clean directory
    echo -e
    if rm _gtests.o _Print.o _Count.o
    then echo "+ directory cleaned"
    else echo "- directory not cleaned"
    fi

  else errormassage "linking stage of"
  fi

fi