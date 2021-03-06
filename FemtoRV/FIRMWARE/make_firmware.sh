echo "============> Compiling libs"
(cd LIBFEMTORV32;  make clean all) # Compile hardware support lib
(cd LIBFEMTOC;     make clean all) # Compile lib with printf() replacement function
(cd CRT_BAREMETAL; make clean all) # Compile C runtime for baremetal
# Note: I 'make clean' each time, because there is no much to recompile (and dependencies
# are not specified)...

EXE_BASENAME=`basename $1 | sed -e 's|\.c$||' -e 's|\.S$||'`
SOURCE_DIR=`dirname $1`
echo "============>" Making $EXE_BASENAME
(cd $SOURCE_DIR; make clean $EXE_BASENAME".hex")

rm -f firmware.hex firmware.txt
if [ -f  $SOURCE_DIR"/"$EXE_BASENAME".hex" ]; then
   cp $SOURCE_DIR"/"$EXE_BASENAME".hex" firmware.hex
   echo "source:" $1 > firmware.txt
   (cd $SOURCE_DIR; make show_config) >> firmware.txt
   echo "Generated firmware.hex"
   (cd $SOURCE_DIR; make show_config)

else
   echo "Something went wrong, change VERBOSE in make_firmware.sh and retry"
fi

## Display assembly
#$RVOBJCOPY -O binary BUILD/firmware.elf BUILD/firmware.bin
#$RVOBJDUMP -D -b binary -m riscv BUILD/firmware.bin 
