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

# compile project
if g++ $std -c _exls.cpp -o _exls.o
then 
  echo "+ project object file compilation succeed"
  let "control++"
else
  errormassage "project"
fi

# compile gtests
if g++ $std -c _gtests.cpp -o _gtests.o
then 
  echo "+ gtests object file compilation succeed"
  let "control++"
else 
  errormassage "gtests"
fi

# if both project and gtests are compiled then build tests
if [[ $control -eq 2 ]]
then

  # if linking succeed
  if g++ _gtests.o _exls.o $gtestlibs -o $exename
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
  
  else errormassage "linking stage of"
  fi

fi