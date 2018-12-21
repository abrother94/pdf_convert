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

    while IFS=$'\n' read -r one_line ;do
	echo "one_line[$one_line]"
	matrix_g988_chapter_line_me[${matrix_all_g988_chapter_line_count},0]=`echo $one_line | awk -F"[9].[0-9]{1,2}.[0-9]{1,2}" '{print $1}' | sed -e 's/ *$//g'| sed -e 's/ /_/g'`
	matrix_g988_chapter_line_me[${matrix_all_g988_chapter_line_count},1]=`echo $one_line | awk -F"[9].[0-9]{1,2}.[0-9]{1,2}" '{print $2}' | sed -e 's/ //g'`
	echo "[${matrix_g988_chapter_line_me[${matrix_all_g988_chapter_line_count},0]}][${matrix_g988_chapter_line_me[${matrix_all_g988_chapter_line_count},1]}]"
	matrix_all_g988_chapter_line_count=$((matrix_all_g988_chapter_line_count+1))
    done <<< "$G988_ME_TYPE_NAME"
    #echo "matrix_all_g988_chapter_line_count[$matrix_all_g988_chapter_line_count]"
}


collect_all_content_section_line_index()
{
    while IFS=' ' read -r line_num section me_des;do
	matrix_chapter_line_me[${matrix_all_chapter_line_count},0]=$line_num
	matrix_chapter_line_me[${matrix_all_chapter_line_count},1]=$section
	matrix_chapter_line_me[${matrix_all_chapter_line_count},2]=`echo $me_des | sed -e 's/ /_/g'`
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
    local SECTION="$1"
    echo "dump name[$SECTION]"
    local c=0

    for (( c=0; c < "${matrix_all_chapter_line_count}"; c++ ))
    do
	SA="${matrix_chapter_line_me[$c,2]}"
	echo "SA[$SA]"
	DA="${SECTION}"
	if [ "${SA}" == "${DA}" ] ;then
	    echo "match[${matrix_chapter_line_me[$c,0]}]"
	    START=${matrix_chapter_line_me[$c,0]}
	    END=${matrix_chapter_line_me[$(($c+1)),0]}
	    END=$(($END-1))
	    break
	fi
    done

    ENDPAGE="$END"p
    echo [$START][$ENDPAGE]

    FSECTION="${SECTION//[ \/]/_}"
    RES=`cat "$G988_TXT"| sed -n $START,$ENDPAGE > "ME_NAME/$FSECTION"`
}

dump_all_me_1()
{
    local c=0
    echo "dump_all_me count[$matrix_all_g988_chapter_line_count]"
    for (( c=0; c < "${matrix_all_g988_chapter_line_count}"; c++ ))
    do
	NAME=${matrix_g988_chapter_line_me["$c",0]}
	echo "dump_all_me name[$NAME]"
        dump_me_setciotn "${NAME}"
    done
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

find_me_class_id()
{
    local me_name="$1"
    echo "dump name[$me_name]"
    local c=0

    for (( c=0; c < "${matrix_all_g988_chapter_line_count}"; c++ ))
    do
	SA="${matrix_g988_chapter_line_me[$c,0]}"
	DA="${me_name}"
	if [ "${SA}" == "${DA}" ] ;then
	    echo "${matrix_g988_chapter_line_me[$c,1]}"
	    break
	fi
    done
}


get_me_attributes_num()
{
    local name=$1
    count=`cat "$name" | egrep '(\(R\)|\(W\)|\(R, W\)|\(W, Set-by-create\)|\(R, W, Set-by-create\))' | wc -l`
    echo "[$count] attributes"
}

get_first_attribute_name()
{
    local name="$1"
    First_Attribute=`cat "$name" | tr '\n' ' ' | sed -e 's/ \+/ /g' |  sed '0,/Attributes/ s/^.*Attributes/Attributes/' |sed -n '/Attributes /,/:/p' | cut -d ":" -f1 | sed 's/Attributes //g' | sed 's/ /_/g'` 
    echo "$First_Attribute"
}

#collect_g988_me_content_section_line_index
#collect_all_content_section_line_index
#collect_me_content_section_line_index
#dump_all_me_1
#get_me_attributes_num "$SECTION"
#get_first_attribute_name "$SECTION"

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



#//GET ATTRIBUTE
#sed -n '/Managed entity id/,/Notifications/p' FILENAME


#//Find how many attributes
#cat ONT-G | egrep '(\(R\)|\(W\)|\(R, W\)|\(W, Set-by-create\)|\(R, W, Set-by-create\))' | wc -l
#//GET Read/Write type
#(\(R\)|\(W\)|\(R, W\)|\(W, Set-by-create\)|\(R, W, Set-by-create\))
#(R)
#(W)
#(R, W)
#(W, Set-by-create) 
#(R, W, Set-by-create)

#sed -n '/Managed entity id/,/Notifications/p' FI


#\([0-9]{1,100} (byte|bytes)\)

#(1 byte) (8 bytes) (22 bytes)



