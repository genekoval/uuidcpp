project := uuid++

library := lib$(project)

install := $(library)
targets := $(install)

$(library).type := shared
$(library).libs := uuid

include mkbuild/base.mk
