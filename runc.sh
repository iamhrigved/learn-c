#!/bin/bash

# run `source runc.sh` and then use this funcion anywhere
runc() {
	local file_location=$1
    local file_type=$(echo $file_location | sed "s/.*\.\(.*\)/\1/" | sed "s/p/+/g") # `c` or `cpp`
	local file_name=${1:t}
	local file_directory=${1:h}
	local exe_file_name=${file_name:r}

    # if the file compiles without any errors this will run
    local run() {
            # if executables directory does not exist
            if [[ $(ls $file_directory/ | grep -i -o "executables") == "" ]] then;
                mkdir $file_directory/executables &&
                echo "New directory created $file_directory/executables"
            fi

            mv ./a.out ./executables/$exe_file_name
            echo "" # printing new lines
            ./executables/$exe_file_name $@
            echo ""
    }
    echo "g++ $file_location -x $file_type && run $@"
    g++ $file_location -x $file_type && run $@
}
