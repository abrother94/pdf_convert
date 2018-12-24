#!/bin/bash

get_me_attributes_num()
{
    local name=$1
    count=`cat "$name" | sed -n '/Managed entity [iI][dD]:/,/Actions/p ; /Actions/q' | egrep '(\(R\)|\(W\)|\(R, W\)|\(W, Set-by-create\)|\(R, Set-by-create\)|\(R, W, Set-by-create\))' | wc -l`
    echo $count
}

get_me_attributes_section()
{
    local name=$1
    count=`sed '/Actions/q' "$name"`
    echo $count
}

PARAM="$1"
`ls ME_NAME > filelist.txt`

while read filename;
do  
    #get_me_attributes_section "ME_NAME/$filename"
    #ACT=`sed -i "/.*\([A-Za-z]: [A-Za-z]\).*/,/Actions/ s/: /:  /g" ME_NAME/$filename` 
    #REST=`cat ME_NAME/$filename | sed -e "s/$RELPACE/$RES/g "`
    #RESE=`sed -i  "s/$RELPACE/$RES/g " ME_NAME/$filename`
    param_num=$(get_me_attributes_num "ME_NAME/$filename")
    if (( $param_num > 17 || $PARAM > $param_num ));then
        echo "get_me_attributes_section[ME_NAME/$filename]"
	echo "[$param_num] over 17 parameters"
    fi
    STR=`./get_section.sh "ME_NAME/$filename" "$PARAM"`
    STR_LEN=${#STR}
    #if (( $STR_LEN > 70 ));then
    # 	echo "[ME_NAME/$filename] STR[$STR] LEN[$STR_LEN]"
    #exit
    #fi
done < filelist.txt
