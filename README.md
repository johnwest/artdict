#Artdict tool suits for creating of word index of great number of pdf files.
The index is keeped as C++-multimap (during program work) and as textfile on hard-drive.
Auto ptr's & C++11 modifications may be done in specific branch.
-------------------------
Note, you should have package 'poppler-utils' installed on your Linux (utility pdftotext).
The project's homepage is: http://linuxappfinder.com/package/poppler-utils
-------------------------
#1) DONT USE PROJECT ON YOUR PDF ARCHIVE!
ITS DUPLICATING ALL PDFS THAT contain spaces.
To make program rename pdf files, in pdft.sh change the line: cp "$str" "$str2"
to mv "$str" "$str2".
#2) NOTE that the Program at now doesn't support spaces in directories filenames.
-------------------------
I provide no warranty for the effects of using the Program. You use it on your own risk.

