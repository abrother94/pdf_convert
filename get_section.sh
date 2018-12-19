#!/bin/bash

SECTION="$1"

#IS_FORMATED=`echo $SECTION |  egrep "^[0-9]{1,2}\.[0-9]{1,2}\.[0-9]{1,2}"` 

#if [ "$IS_FORMATED" = "" ];then
#    echo "Need enter  xx.xx.xx ME section number"
#    exit
#fi

LINE_TMP="chapter_line_me_tmp"
G988_TXT="g988.txt"

cmp_decimal()
{
    D1=$1
    D1="${D1//./}"
    D2=$2
    D2="${D2//./}"
    echo $D1 $D2
}

dump_me_setciotn()
{
    SECTION="$1"
    declare -A matrix

    while IFS=' ' read -r line_num section me_des;do
	matrix[${count},0]=$line_num
	matrix[${count},1]=$section
	matrix[${count},2]=$me_des
	count=$((count+1))
    done < $LINE_TMP

    for (( c=0; c < "${count}"; c++ ))
    do
	SA="${matrix[$c,2]}"
	DA="${SECTION}"
	if [ "${SA}" == "${DA}" ] ;then
	    echo "match[${matrix[$c,0]}]"
	    START=${matrix[$c,0]}
	    END=${matrix[$(($c+1)),0]}
	fi
    done

    ENDPAGE="$END"p

    echo [$START][$ENDPAGE]

    FSECTION="${SECTION//[ \/]/_}"
    `cat "$G988_TXT"| sed -n $START,$ENDPAGE > "ME_NAME/$FSECTION"`
}

show_me_name()
{
    count=0
    declare -A matrix_type_name

    # 8,9 section refert to ME attribe
    ME_TYPE_NAME=`cat $LINE_TMP | egrep "[8-9]{1,2}\.[0-9]{1,2}\.[0-9]{1,2}"`

    while IFS=' ' read -r int1 text1 me_des;do
	matrix[${count},2]=$me_des
	echo "[${matrix[$count,2]}]"
	dump_me_setciotn "${matrix[$count,2]}"
	count=$((count+1))
    done <<< "$ME_TYPE_NAME"
}

show_me_name

exit

file_line=`wc -l < $LINE_TMP`
file_linep="$file_line"p
org_final_page=`wc -l < "$G988_TXT"`
org_final_pagep="$org_final_page"p
final_line_1st=`sed -n $file_linep $LINE_TMP | awk -e '{print $1}'`

if [ "$START" = "$final_line_1st" ];then
    echo "Final chapter!!"
    echo "[$org_final_pagep]"
fi

START=`cat $LINE_TMP | grep "$SECTION" | awk -e '{print $1}'`
END_tmp=`cat $LINE_TMP | grep -n "$START" | awk -F: '{print $1}'`
ENDNUM=$(($END_tmp + 1))
PAGE_END="$ENDNUM"p
END=`cat $LINE_TMP | sed -n $PAGE_END  | awk '{print $1}' `
END=$(($END-1))
ENDPAGE="$END"p
echo [$START][$ENDPAGE]
`cat "$G988_TXT" | sed -n $START,$ENDPAGE > $SECTION`


