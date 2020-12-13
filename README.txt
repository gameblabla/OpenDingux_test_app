This is a simple app that demonstrate how to use SDL 1.2
on OpenDingux devices (GCW0/RG-350/RG-350M/RG-280V/RG-350P).

You can detect the analog sticks, input and stuff.

How to compile
===============

For now i assume that you have access to a linux computer or a linux VM.
This may work for WSL2 as well but it wasn't tested.

Stock firmware (2014 based)
___________________________

Download this toolchain :
http://www.gcw-zero.com/files/opendingux-gcw0-toolchain.2014-08-20.tar.bz2

And extract it to /opt.
In /opt/gcw0-toolchain, you should have a following folder called "usr". If that's the case, you're good.

Then open up a terminal in this folder and compile it with :
make -f Makefile.gcw0

Once compilation is sucessful, package everything up with :
./package

You can now push your OPK to your console either via FTP (to /media/apps) with an FTP client like Filezilla
or alternatively, use the external sd card slot and put the OPK in a folder called "apps".


Beta/Nightly firmware
___________________________

Download this toolchain :
http://od.abstraction.se/opendingux/opendingux-gcw0-toolchain.2020-10-01.tar.gz

And extract it to /opt.
In /opt/gcw0-toolchain, you should have the following files:
bin
etc
include
lib
lib64
libexec
man
mipsel-buildroot-linux-musl
mipsel-gcw0-linux-uclibc
relocate-sdk.sh
sbin
share
usr

Then open up a terminal in this folder and compile it with :
make -f Makefile.gcw0

Once compilation is sucessful, package everything up with :
./package

You can now push your OPK to your console either via MTP (connect your console to your PC, make sure to use USB2 on the RG-350),
and put it in "Apps".
or alternatively, use the external sd card slot and put the OPK in a folder called "apps".
