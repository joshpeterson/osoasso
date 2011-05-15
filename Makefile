# Makefile for the osoasso project.

.PHONY: all clean

# The files the project starts with.  Add your code files here!
CCFILES = src/osoasso.cc src/blob.cc test/test_blob.cc test/stress_test_blob.cc

#Add your includes here.
INCLUDES =

# These libraries are necessary for PPAPI (Pepper 2) and NaCl.
LDFLAGS = -lppruntime \
          -lppapi_cpp \
          -lplatform \
          -lgio \
          -lpthread \
          -lsrpc \
          $(ARCH_FLAGS)

# Add your .nmf files for each nexe you build here.
all: check_variables osoasso.nmf osoasso_dbg.nmf

# common.mk has rules to build .o files from .cc files.
-include common.mk

# Targets to create the manifests.
osoasso.nmf: osoasso_x86_32.nexe osoasso_x86_64.nexe
	@echo "Creating osoasso.nmf..."
	$(PYTHON) generate_nmf.py --nmf $@ \
	 --x86-64 osoasso_x86_64.nexe \
         --x86-32 osoasso_x86_32.nexe

osoasso_dbg.nmf: osoasso_x86_32_dbg.nexe \
        osoasso_x86_64_dbg.nexe
	@echo "Creating osoasso_dbg.nmf..."
	$(PYTHON) generate_nmf.py --nmf $@ \
	--x86-64 osoasso_x86_64_dbg.nexe \
        --x86-32 osoasso_x86_32_dbg.nexe

# Targets to create the nexes.
osoasso_x86_32.nexe: $(OBJECTS_X86_32)
	$(CPP) $^ $(LDFLAGS) -m32 -o $@
	$(NACL_STRIP) $@ -o $@

osoasso_x86_64.nexe: $(OBJECTS_X86_64)
	$(CPP) $^ $(LDFLAGS) -m64 -o $@
	$(NACL_STRIP) $@ -o $@

osoasso_x86_32_dbg.nexe: $(OBJECTS_X86_32_DBG)
	$(CPP) $^ $(LDFLAGS) -m32 -o $@

osoasso_x86_64_dbg.nexe: $(OBJECTS_X86_64_DBG)
	$(CPP) $^ $(LDFLAGS) -m64 -o $@

test_blob_x86_32_dbg.nexe: test/test_blob_x86_32_dbg.o src/blob_x86_32_dbg.o
	$(CPP) $^ $(LDFLAGS) -m32 -o $@

test_blob_x86_64_dbg.nexe: test/test_blob_x86_64_dbg.o src/blob_x86_64_dbg.o
	$(CPP) $^ $(LDFLAGS) -m64 -o $@

# Run the 32-bit version of the unit test with nacl-sel_ldr.
test32: test_blob_x86_32_dbg.nexe
	$(NACL_SEL_LDR32) test_blob_x86_32_dbg.nexe

# Run the 64-bit version of the unit test with nacl64-sel_ldr.
test64: test_blob_x86_64_dbg.nexe
	$(NACL_SEL_LDR64) test_blob_x86_64_dbg.nexe

# Run both the 32-bit and the 64-bit version of the tests.  Note that this is
# not included in the 'all' target because 32-bit platforms won't support the
# 64-bit test.
test: test32 test64

stress_test_blob_x86_32_dbg.nexe: test/stress_test_blob_x86_32_dbg.o src/blob_x86_32_dbg.o
	$(CPP) $^ $(LDFLAGS) -m32 -o $@

stress_test_blob_x86_64_dbg.nexe: test/stress_test_blob_x86_64_dbg.o src/blob_x86_64_dbg.o
	$(CPP) $^ $(LDFLAGS) -m64 -o $@

# Run the 32-bit version of the unit stress_test with nacl-sel_ldr.
stress_test32: stress_test_blob_x86_32_dbg.nexe
	$(NACL_SEL_LDR32) stress_test_blob_x86_32_dbg.nexe

# Run the 64-bit version of the unit stress_test with nacl64-sel_ldr.
stress_test64: stress_test_blob_x86_64_dbg.nexe
	$(NACL_SEL_LDR64) stress_test_blob_x86_64_dbg.nexe

# Run both the 32-bit and the 64-bit version of the stress_tests.  Note that this is
# not included in the 'all' target because 32-bit platforms won't support the
# 64-bit stress_test.
stress_test: stress_test32 stress_test64

# Target to clean up
clean:
	-$(RM) *.nmf *.o *.obj *.nexe

