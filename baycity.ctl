#
#
# Baycity control file
#
#

SID1	KKSF-
SID2	KKSF-
DEFACT	/bin/cat %s >> /u/staff/pozar/src/anpa/anpa.out
# BULLETIN	/bin/cat %s >> /usr/local/etc/anpa/AP/AP ; /usr/local/bin/print %s ;  /usr/sbin/sendmail eng-page < %s
# 'URGENT' is not implemented yet...
# URGENT	/bin/cat %s >> /usr/local/etc/anpa/AP/AP ; /usr/local/bin/print %s ;  /usr/sbin/sendmail eng-page < %s
# DEFACT	/bin/cat %s >> /dev/null

TABLE	A
START	0000
STOP	2359
SLD	v
SEL	0xxx 
CAT	z
ACTION	/bin/cat %s >> /usr/local/etc/anpa/baycity/baycity
ENDTABLE
# ACTION	/usr/sbin/sendmail <mailaddr> < %s

#
# End of baycity.ctl file...
#
