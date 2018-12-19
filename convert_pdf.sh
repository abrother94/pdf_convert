#!/usr/bin/python
import sys,os
import pdftotext
# Load your PDF and create to txt file
with open("g988.pdf", "rb") as f:
    pdf = pdftotext.PDF(f)

f1=open('./g988tmp.txt', 'w+')
for page in pdf:
    f1.write(page.encode('utf-8'))
f1.close()
