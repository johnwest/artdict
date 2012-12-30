#!/bin/bash
k=-1;
str="";
find $1 -name "*.pdf" | while read -r pname;
do
 str=$str$pname
 if [[ "$pname" == *.pdf ]]
 then
 	str2=`echo $str | sed 's/[ \t]*//g'`
	if [[ $str != $str2 ]]
	then
		cp "$str" "$str2";
	fi
	(( k++ ));
	pdftotext $str2 $2"$k";
#awk -v "p=$str2" '{n = split(p,a,"/"); print a[n]}';
	echo "$str";
echo "$str" >> $2"$k";
	str="";
 fi
echo "$k" > ~/artdict/numfiles.txt
done
