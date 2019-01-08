#!/bin/bash
SECTION="$1"
OUTPUT_PATH="E_OMCI/src/S_ME"
CID=`./get_section.sh "$SECTION" me_class`
ME_NAME=`./get_section.sh "$SECTION" me_name`
ATTRIB_NUM=`./get_section.sh "$SECTION" attribute_num`

OUTPUT_FILE_NAME="$CID"_"$ME_NAME"
OUTPUT_FILE="$OUTPUT_PATH/$OUTPUT_FILE_NAME"

echo "CID[$CID]"
echo "ME_NAME[$ME_NAME]"
echo "ATTRIB_NUM[$ATTRIB_NUM]"
echo "OUTPUT_FILE[$OUTPUT_FILE]"

J_B_START()
{
    echo "{" >> ${OUTPUT_FILE}
}
J_B_END()
{
    echo "}" >> ${OUTPUT_FILE}
}

J_COMMA()
{
    echo "," >> ${OUTPUT_FILE}
}

J_A_START()
{
    echo "\"Attrs_info\":[" >> ${OUTPUT_FILE}
}

J_A_END()
{
    echo "]" >> ${OUTPUT_FILE}

}

ATTRIB_SET()
{
    local ID=$1
    local NAME="$2"
    local SIZE="$3"
    local ACCESS="$4"
    J_B_START
echo "
\"Id\"     : $ID ,
\"Name\"   : \"$NAME\" ,
\"Size\"   : \"$SIZE\" ,
\"Access\" : \"$ACCESS\" 
" >> ${OUTPUT_FILE}
    J_B_END
}

#Create file from here#
`rm ${OUTPUT_FILE}`

J_B_START

J_A_START
ATTRIB_SET "1" "NAMEaA" "(56)" "RW"
J_A_END

J_B_END

