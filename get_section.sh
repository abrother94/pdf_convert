#!/bin/bash

SECTION="$1"

#IS_FORMATED=`echo $SECTION |  egrep "^[0-9]{1,2}\.[0-9]{1,2}\.[0-9]{1,2}"` 

#if [ "$IS_FORMATED" = "" ];then
#    echo "Need enter  xx.xx.xx ME section number"
#    exit
#fi
#cmp_decimal()
#{
#    D1=$1
#    D1="${D1//./}"
#    D2=$2
#    D2="${D2//./}"
#    echo $D1 $D2
#}

LINE_TMP="chapter_line_me_tmp"
G988_TXT="g988.txt"


declare -A matrix_g988_chapter_line_me
matrix_all_g988_chapter_line_count=0

declare -A matrix_chapter_line_me
matrix_all_chapter_line_count=0

declare -A matrix_chapter_line_me_content
matrix_chapter_line_me_content_count=0


collect_g988_me_content_section_line_index()
{
    # 8,9 section refert to ME attribe
    G988_ME_TYPE_NAME=`cat g988.txt | grep "Index" -A200 | egrep '[9]\.[0-9]{1,2}\.[0-9]{1,2}'`

    while IFS=' ' read -r me_des section class_id ;do
	matrix_g988_chapter_line_me[${matrix_all_g988_chapter_line_count},0]=$me_des
	matrix_g988_chapter_line_me[${matrix_all_g988_chapter_line_count},1]=$section
	matrix_g988_chapter_line_me[${matrix_all_g988_chapter_line_count},2]=$class_id
	matrix_all_g988_chapter_line_count=$((matrix_all_g988_chapter_line_count+1))
    done <<< "$G988_ME_TYPE_NAME"
    echo "matrix_all_g988_chapter_line_count[$matrix_all_g988_chapter_line_count]"
}


collect_all_content_section_line_index()
{
    while IFS=' ' read -r line_num section me_des;do
	matrix_chapter_line_me[${matrix_all_chapter_line_count},0]=$line_num
	matrix_chapter_line_me[${matrix_all_chapter_line_count},1]=$section
	matrix_chapter_line_me[${matrix_all_chapter_line_count},2]=$me_des
	matrix_all_chapter_line_count=$((matrix_all_chapter_line_count+1))
    done < $LINE_TMP
}

collect_me_content_section_line_index()
{
    # 8,9 section refert to ME attribe
    ME_TYPE_NAME=`cat $LINE_TMP | egrep "[9]{1,2}\.[0-9]{1,2}\.[0-9]{1,2}"`

    while IFS=' ' read -r line_num section me_des;do
	matrix_chapter_line_me_content[${matrix_chapter_line_me_content_count},0]=$line_num
	matrix_chapter_line_me_content[${matrix_chapter_line_me_content_count},1]=$section
	matrix_chapter_line_me_content[${matrix_chapter_line_me_content_count},2]=$me_des
	matrix_chapter_line_me_content_count=$((matrix_chapter_line_me_content_count+1))
    done <<< "$ME_TYPE_NAME"
}


dump_me_setciotn()
{
    SECTION="$1"
    echo "dump name[$SECTION]"
    local c=0

    for (( c=0; c < "${matrix_all_chapter_line_count}"; c++ ))
    do
	SA="${matrix_chapter_line_me[$c,2]}"
	DA="${SECTION}"
	if [ "${SA}" == "${DA}" ] ;then
	    echo "match[${matrix_chapter_line_me[$c,0]}]"
	    START=${matrix_chapter_line_me[$c,0]}
	    END=${matrix_chapter_line_me[$(($c+1)),0]}
	    break
	fi
    done

    ENDPAGE="$END"p
    echo [$START][$ENDPAGE]

    FSECTION="${SECTION//[ \/]/_}"
    RES=`cat "$G988_TXT"| sed -n $START,$ENDPAGE > "ME_NAME/$FSECTION"`
}

dump_all_me()
{
    local c=0
    echo "dump_all_me count[$matrix_chapter_line_me_content_count]"
    for (( c=0; c < "${matrix_chapter_line_me_content_count}"; c++ ))
    do
	NAME=${matrix_chapter_line_me_content["$c",2]}
	echo "dump_all_me name[$NAME]"
        dump_me_setciotn "${NAME}"
    done
}


collect_g988_me_content_section_line_index
collect_all_content_section_line_index
collect_me_content_section_line_index

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


