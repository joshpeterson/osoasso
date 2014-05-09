VALID_TOOLCHAINS := pnacl newlib glibc

NACL_SDK_ROOT ?= $(abspath $(CURDIR)/../development/nacl_sdk/pepper_33)
include $(NACL_SDK_ROOT)/tools/common.mk

LIBS = ppapi_cpp ppapi
# CFLAGS = -Wall -Wno-long-long -pthread -Werror -std=c++0x -O2
# Use gnu++11 for pnacl
CFLAGS = -Wall -Wno-long-long -pthread -Werror -std=gnu++11 -O2 --pnacl-exceptions=sjlj
LDFLAGS = --pnacl-exceptions=sjlj

TARGET = osoasso
SOURCES =	src/osoasso.cc\
			src/osoasso_instance.cc\
			src/sha1.cc\
			src/commit.cc\
			src/tag_repository.cc\
			src/command_parser.cc\
			src/command_factory.cc\
			src/command_dispatcher.cc\
			src/commit_factory.cc\
			src/project_manager.cc\
			src/help_manager.cc\
			src/log.cc\
			src/add.cc\
			src/subtract.cc\
			src/multiply.cc\
			src/random.cc\
			src/transpose.cc\
			src/random_symmetric.cc\
			src/identity.cc\
			src/jacobi_eigen_solver.cc

# Build rules generated by macros from common.mk:

$(foreach src,$(SOURCES),$(eval $(call COMPILE_RULE,$(src),$(CFLAGS))))

ifeq ($(CONFIG),Release)
$(eval $(call LINK_RULE,$(TARGET)_unstripped,$(SOURCES),$(LIBS),$(DEPS),$(LDFLAGS)))
$(eval $(call STRIP_RULE,$(TARGET),$(TARGET)_unstripped))
else
$(eval $(call LINK_RULE,$(TARGET),$(SOURCES),$(LIBS),$(DEPS), $(LDFLAGS)))
endif

$(eval $(call NMF_RULE,$(TARGET),))
