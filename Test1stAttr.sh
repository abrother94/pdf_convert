#!/bin/bash
PARAM="$1"
`ls ME_NAME > filelist.txt`

while read filename;
do  
    echo "get form $filename"
    STR=`./get_section.sh "ME_NAME/$filename" "$PARAM"`
    STR_LEN=${#STR}
    if (( $STR_LEN > 50 ));then
	echo "[ME_NAME/$filename] STR[$STR] LEN[$STR_LEN]"
	exit
    fi
done < filelist.txt
