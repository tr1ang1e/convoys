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
lib="../lib/"
exename="_runtests"

echo -e
control=0

# compile GreedClass class
if g++ $std -c _GreedClass.cpp -o _GreedClass.o
then 
  echo "+ class GreedClass object file compilation succeed"
  let "control++"
else
  errormassage "class GreedClass"
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
if ar rc libproject.a _GreedClass.o _Print.o
then
  echo "+ project static library creation succeed"
  mv -f ./libproject.a "$lib"
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
  if g++ _gtests.o $gtestlibs -L"$lib" -lproject -o $exename
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
    then echo "- gtests filed"
    else  # print final test state
      if [[ $output -eq 0 ]]
      then
        echo "+ gtests succeed (> $logfile)"
        echo -e
        tostdout="Global test environment tear-down"
        awk "/.*${tostdout}.*/,/^$/" "$logfile"
      fi
    fi
  
    # clean directory
    echo -e
    if rm _gtests.o _Print.o _GreedClass.o
    then echo "+ directory cleaned"
    else echo "- directory not cleaned"
    fi

  else errormassage "linking stage of"
  fi

fi