#!/bin/bash
`ls ME_NAME > filelist.txt`

while read filename;
do  
    echo "get form $filename"
    STR=`./get_section.sh "ME_NAME/$filename"`
    STR_LEN=${#STR}
    if (( $STR_LEN > 45 ));then
	echo "[ME_NAME/$filename] STR[$STR] LEN[$STR_LEN]"
    fi
done < filelist.txt
