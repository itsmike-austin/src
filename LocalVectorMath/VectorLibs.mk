MAKE = nmake

DLLS 	= AdvancedAlignedVector \
	  AdvancedUnalignedVector \
	  AlignedVector \
	  UnalignedVector \
	  VectorAsm \
	  VectorStd

$(DLLS).dll:
  @$(MAKE) -nologo -f $*.mk setup
  @$(MAKE) -nologo -f $*.mk
  @$(MAKE) -nologo -f $*.mk setup
  @$(MAKE) -nologo -f $*.mk DEBUG=1
  @$(MAKE) -nologo -f $*.mk clear

all: $(DLLS)

clear:
	@if exist *.exp del *.exp
	@if exist *.map del *.map

clean:
  @if exist *.obj del *.obj
  @if exist *.bsc del *.bsc
  @if exist *.dsp del *.dsp
  @if exist *.dsw del *.dsw
  @if exist *.exe del *.exe
  @if exist *.exp del *.exp
  @if exist *.map del *.map
  @if exist *.mdp del *.mdp
  @if exist *.ncb del *.ncb
  @if exist *.opt del *.opt
  @if exist *.pch del *.pch
  @if exist *.pdb del *.pdb
  @if exist *.plg del *.plg
  @if exist *.res del *.res
  @if exist *.res del *.sbr
  @if exist *.vcp del *.vcp
  @if exist *.ilk del *.ilk
  @if exist *~ del *~
  @if exist "#"* del "#"*
  @if exist resource.h del resource.h
  @if exist $(TDIR) rd /q/s $(TDIR)
  @if exist debug rd /q/s debug
  @if exist release rd /q/s release

# Target to clean up all generated files.
cleanall:
  @if exist *.aps del *.aps
  @if exist *.bsc del *.bsc
  @if exist *.dll del *.dll
  @if exist *.dsp del *.dsp
  @if exist *.dsw del *.dsw
  @if exist *.exe del *.exe
  @if exist *.exp del *.exp
  @if exist *.lib del *.lib
  @if exist *.mak del *.mak
  @if exist *.map del *.map
  @if exist *.mdp del *.mdp
  @if exist *.ncb del *.ncb
  @if exist *.obj del *.obj
  @if exist *.opt del *.opt
  @if exist *.pch del *.pch
  @if exist *.pdb del *.pdb
  @if exist *.plg del *.plg
  @if exist *.res del *.res
  @if exist *.sbr del *.sbr
  @if exist *.vcp del *.vcp
  @if exist *~ del *~
  @if exist resource.h del resource.h
  @if exist *.manifest del *.manifest
  @if exist $(TDIR) rd /q/s $(TDIR)
  @if exist debug rd /q/s debug
  @if exist release rd /q/s release

