project := uuid++
version := 0.1.0

library := lib$(project)

install := $(library)
targets := $(install)

$(library).type := shared
$(library).libs := uuid

include $(DEVROOT)/include/mkbuild/base.mk
