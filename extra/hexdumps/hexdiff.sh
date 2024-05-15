#!/bin/sh

#get hex dumps of png and compare
xxd -c 1 fromweb.png | cut -d ' ' -f 2 >web.hex
xxd -c 1 page/flowers3.png | cut -d ' ' -f 2 >org.hex
diff web.hex org.hex 

#turns out there was one 0x00 char at the begining that was fucking everything up