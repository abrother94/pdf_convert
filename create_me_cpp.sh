#!/bin/bash
SECTION="$1"

. E_OMCI/include/Temp.hpp
. E_OMCI/src/Temp.ppc

CPP_OUTPUT_PATH="E_OMCI/src"
INC_OUTPUT_PATH="E_OMCI/include"
CID=`./get_section.sh "$SECTION" me_class`
ME_NAME=`./get_section.sh "$SECTION" me_name`
ATT_MODE_T_AC=`./get_section.sh "$SECTION" action` 
ATTRIB_NUM=`./get_section.sh "$SECTION" attribute_num`

INC_OUTPUT_FILE_NAME="$ME_NAME".hpp
CPP_OUTPUT_FILE_NAME="$ME_NAME".cpp

INC_OUTPUT_FILE="$INC_OUTPUT_PATH/$INC_OUTPUT_FILE_NAME"
CPP_OUTPUT_FILE="$CPP_OUTPUT_PATH/$CPP_OUTPUT_FILE_NAME"

if [ -e "$INC_OUTPUT_FILE" ];then 
    echo "Alreay have $INC_OUTPUT_FILE file!!!!!"
    exit
fi

if [ -e "$CPP_OUTPUT_FILE" ];then 
    echo "Alreay have $CPP_OUTPUT_FILE file!!!!!"
    exit
fi

echo "ME_NAME[$ME_NAME]"

# Auto create hpp cpp file #
HEAD_TEMP "$ME_NAME" "$ATTRIB_NUM" >> "$INC_OUTPUT_FILE" 
CPP_TEMP  "$ME_NAME" "$ATTRIB_NUM" >> "$CPP_OUTPUT_FILE" 

echo "Create [$INC_OUTPUT_FILE] !"
echo "Create [$CPP_OUTPUT_FILE] !"

exit
