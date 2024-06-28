# run `source runc.sh` and then use this funcion anywhere
runc() {
	local file_location=$1
	local file_name=${1:t}
	local file_directory=${1:h}
	local exe_file_name=${file_name:r}
	local is_local=""
	local exe_file_location=""

	if [[ $file_directory == "." ]] then 
		is_local=true
	else
		is_local=false
	fi

	if [[ $(ls $file_directory/ | grep -i -o "executables") == "" ]] then
		mkdir $file_directory/executables
		echo "New directory created $file_directory/executables"
	fi

	exe_file_location="$file_directory/executables/$exe_file_name"

	echo ""
	gcc $file_location -o $exe_file_location && $exe_file_location ${@:2}
	echo ""
}
