
#USER DEFINED FUNCTIONS
run_c(){
  if [[ $# -lt 1 ]]
  then 
    echo "No argument provided, using main.c"
    local filename=$1
    local basename=${filename:r}
  else 
    local filename=$1
    local basename=${filename:r}
  fi

  echo $filename
  echo $basename
  
  #compile the file 
  clang -o $basename $filename

  if [[ $? -eq 0 ]]
  then 
    #compilation successful, run the program 
    echo "Compilation successful"
    
    # check if there are one more argument
    if [[ $# -eq 2 ]]
    then 
      ./$basename $2
      else
        ./$basename
    fi 

    else
      echo "Compilation failed check your code"
  fi 
  # rm $basename
    
}
