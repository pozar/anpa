#
#
# ANPA control file
#
#

SID1	KKSF-
SID2	KKSF-
DEFACT	/bin/cat %s >> /usr/local/etc/anpa/AP/anpa.default
BULLETIN	/bin/cat %s >> /usr/local/etc/anpa/AP/AP ; /usr/local/bin/print %s ;  /usr/sbin/sendmail eng-page < %s
# 'URGENT' is not implemented yet...
# URGENT	/bin/cat %s >> /usr/local/etc/anpa/AP/AP ; /usr/local/bin/print %s ;  /usr/sbin/sendmail eng-page < %s
# DEFACT	/bin/cat %s >> /dev/null

TABLE	A
START	0000
STOP	2359
SLD	v
SEL	0ca-p 0ca-n 0ca-k
CAT	pfnimsgv
ACTION	/bin/cat %s >> /usr/local/etc/anpa/AP/AP
ENDTABLE
# ACTION	/usr/sbin/sendmail <mailaddr> < %s

TABLE	B
START	0000
STOP	2359
SLD	v
SEL	0ca-h
CAT	p
ACTION	/bin/cat %s >> /usr/local/etc/anpa/AP/AP
ENDTABLE

TABLE	C
START	0000
STOP	2359
SLD	v
SEL	0ca-h 0ca-d 0bwcv 0p10v 0wacv
CAT	s
ACTION	/bin/cat %s >> /usr/local/etc/anpa/AP/AP
ENDTABLE

TABLE	D
START	0000
STOP	2359
SLD	v
SEL	0ca-d
CAT	jpfm
ACTION	/bin/cat %s >> /usr/local/etc/anpa/AP/AP
ENDTABLE

TABLE	E
START	0000
STOP	2359
SLD	v
SEL	1al--
CAT	hpfsbcel
ACTION	/bin/cat %s >> /usr/local/etc/anpa/AP/AP
ENDTABLE

TABLE	F
START	0000
STOP	2359
SLD	v
SEL	1nt--
CAT	awpidfsvb
ACTION	/bin/cat %s >> /usr/local/etc/anpa/AP/AP
ENDTABLE

# Weather definitions...
TABLE	G
START	0000
STOP	2359
SLD	v
SEL	2canf 2ca-f 2canm 2ca-m 2canl 2ca-l 2canr 2ca-r 2cang 2ca-g 2cant 2ca-t 2cano 2ca-o 2casg 2nwhp 2nwg-
CAT	o
ACTION	/bin/cat %s >> /usr/local/etc/anpa/AP/AP
ENDTABLE

# Utilities...
TABLE	H
START	0000
STOP	2359
SLD	v
SEL	c9501 02-09 6test 1alpr AC864 ac864 kksf- 0cas? 0can? 0cav? 0cag? 0ca-b 0ca-a 0bwcb 0p10b 0wacb 0ca-s 1ntp- 1als-
CAT	?
ACTION	/bin/cat %s >> /usr/local/etc/anpa/AP/AP
ENDTABLE

TABLE	I
START	0000
STOP	2359
SLD	v
SEL	1ski? 1alrt 1rad- 1rwe-
CAT	?
ACTION	/bin/cat %s >> /usr/local/etc/anpa/AP/AP
ENDTABLE

TABLE	J
START	0000
STOP	2359
SLD	v
SEL	1al-- 0ca-n 1np-- 1nt--
CAT	v
ACTION	/bin/cat %s >> /usr/local/etc/anpa/AP/AP
ENDTABLE

# Selector 	Description
# 1alb- 	AP-EBS BULLETIN TEST
TABLE	K
START	0000
STOP	2359
SLD	v
SEL	1alb-
CAT	v
ACTION	/bin/cat %s >> /usr/local/etc/anpa/AP/AP ; /usr/local/bin/print %s ;  /usr/sbin/sendmail eng-page < %s
ENDTABLE

# Selector      Description
# 0ca--         On The Net
TABLE	L
START	0000
STOP	2359
SLD	k
SEL	0ca--
CAT	n
ACTION	/bin/cat %s >> /usr/local/etc/anpa/AP/AP
ENDTABLE
#
# End of anpa.ctl file...
#
