project := uuid++
summary := C++ wrapper for libuuid

STD := c++20

library := lib$(project)

install := $(library)
targets := $(install)

$(library).type := shared
$(library).libs := uuid

test.libs := $(project) gtest gtest_main
test.deps := $(library)

files = $(include) $(src) Makefile VERSION

include mkbuild/base.mk
