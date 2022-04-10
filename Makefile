project := uuid++

STD := c++20

library := lib$(project)

install := $(library)
targets := $(install)

$(library).type := shared
$(library).libs := uuid

test.libs := $(project) gtest gtest_main
test.deps := $(library)

include mkbuild/base.mk
