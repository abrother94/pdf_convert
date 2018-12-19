#/bin/bash
# take off "Rec. XXX"
if [ -f g988tmp.txt ];then
    rm g988tmp.txt 
fi

if [ -f g988.txt ];then
    rm g988.txt 
fi
./convert_pdf.sh
# Will create g988tmp.txt
cat g988tmp.txt  | sed "/Rec. ITU-T G.984.4/d" > g988.txt
# Record section and line position 

if [ -f chapter_line_me_tmp ];then
    rm chapter_line_me_tmp
fi
cat g988.txt | egrep -n '^[0-9]{1,2}\.' | awk -F":" '{print $1 " " $2}' > chapter_line_me_tmp
