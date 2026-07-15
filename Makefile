# systems-pickle — build every program in the course.
#
#   make            build everything into build/
#   make test       build, then smoke-test every program that can run headless
#   make clean      remove build/
#   make <name>     build one program, e.g. `make shapes`
#
# In 2019 each program was compiled by hand and the resulting binary was
# committed next to its source. Those binaries are gone; this file replaces
# them. CI runs `make test` on Linux, which is what proves the course still
# builds — see .github/workflows/build.yml.

CC       := cc
CXX      := c++
CFLAGS   := -std=c11 -Wall
CXXFLAGS := -std=c++17 -Wall
PTHREAD  := -pthread
B        := build

# OpenMP needs a flag the base compiler doesn't imply, and AppleClang has no
# OpenMP runtime at all unless you `brew install libomp`. Rather than make
# every macOS user pass a flag, probe the compiler once and adapt:
#   -fopenmp                        gcc, and clang with libomp on the path
#   -Xpreprocessor -fopenmp -lomp   AppleClang + homebrew libomp
#   (none)                          no OpenMP -> those 2 programs are skipped
# Override explicitly if the probe guesses wrong: make OPENMP="-fopenmp"
OMP_PROBE := $(shell printf '\#include <omp.h>\nint main(){return omp_get_num_threads();}\n' > .omp_probe.c 2>/dev/null; \
  if $(CXX) -fopenmp -x c++ .omp_probe.c -o /dev/null >/dev/null 2>&1; then echo 'FOPENMP'; \
  elif $(CXX) -Xpreprocessor -fopenmp -lomp -x c++ .omp_probe.c -o /dev/null >/dev/null 2>&1; then echo 'LIBOMP'; \
  else echo 'NONE'; fi; rm -f .omp_probe.c)

ifeq ($(OMP_PROBE),FOPENMP)
  OPENMP ?= -fopenmp
else ifeq ($(OMP_PROBE),LIBOMP)
  OPENMP ?= -Xpreprocessor -fopenmp -lomp
else
  OPENMP ?=
  HAVE_OMP := no
endif

# ---- single-file C programs -------------------------------------------------
C_PROGS := \
  pointersWStructs:labs_projects/pointersWStructs.c \
  testScanF:labs_projects/testScanF.c \
  lab1:lectures/Week1/lab1.c \
  lecture1:lectures/Week1/lecture1.c \
  lab2:lectures/Week2/lab2.c \
  lab2Numbers:lectures/Week2/lab2Numbers.c \
  lec3:lectures/Week2/lec3.c \
  lecture2:lectures/Week2/lecture2.c \
  lecture3:lectures/Week2/lecture3.c \
  lecture4:lectures/Week2/lecture4.c \
  baseConv:lectures/Week3/lab3/baseConv.c \
  bitset:lectures/Week3/lab3/bitset.c \
  lecture4.18:lectures/Week3/lecture4.18.c \
  linkedList:lectures/Week4/Huffman/linkedList.c \
  fp:lectures/Week4/lab4/fp.c \
  tc:lectures/Week4/lab4/tc.c \
  forkwaitexample:lectures/Week5/forkwaitexample.c \
  lecture6:lectures/Week5/lecture6.c \
  head:lectures/Week8/head.c \
  node:lectures/Week8/node.c

# ---- single-file C++ programs (threads need -pthread) ------------------------
CXX_PROGS := \
  th1:lectures/Week5/th1.cpp \
  th1-1:lectures/Week5/th1-1.cpp \
  th1-2:lectures/Week5/th1-2.cpp \
  threads:lectures/Week5/threads.cpp \
  pi:lectures/Week6/pi.cpp \
  pithread:lectures/Week6/pithread.cpp \
  allShapes:lectures/Week7/allShapes.cpp \
  cppOOP:lectures/Week7/cppOOP.cpp

# ---- OpenMP programs --------------------------------------------------------
# IntroToPPOpenMp only uses #pragma omp (ignored without the flag), so it
# builds either way. The other two #include <omp.h> and need a real runtime.
OMP_PROGS := IntroToPPOpenMp:lectures/Week7/IntroToPPOpenMp.c
ifneq ($(HAVE_OMP),no)
  OMP_PROGS += \
    piomp:lectures/Week6/piomp.cpp \
    Lab06_OpenMp:lectures/Week7/Lab06_OpenMp.cpp
endif

# ---- multi-file programs (declared explicitly below) -------------------------
MULTI := shapes animals rational

# Files with no main() — they can't link into a program, so they are only
# compiled, to prove they still build. lecture5.c is Huffman prep notes;
# duSocket.c is the socket helper for head.c/node.c.
COMPILE_ONLY := lectures/Week3/lecture5.c lectures/Week8/duSocket.c

ALL_NAMES := $(foreach p,$(C_PROGS) $(CXX_PROGS) $(OMP_PROGS),$(word 1,$(subst :, ,$(p)))) $(MULTI)
ALL := $(addprefix $(B)/,$(ALL_NAMES))

.PHONY: all test clean compile-only $(ALL_NAMES)
all: $(ALL) compile-only
	@echo "built $(words $(ALL)) programs into $(B)/"
ifeq ($(HAVE_OMP),no)
	@echo ""
	@echo "NOTE: no OpenMP runtime found, so piomp and Lab06_OpenMp were skipped."
	@echo "      On macOS: brew install libomp && make"
endif

compile-only: | $(B)
	@for f in $(COMPILE_ONLY); do \
	  echo "$(CC) $(CFLAGS) -c $$f"; \
	  $(CC) $(CFLAGS) -c $$f -o $(B)/$$(basename $$f .c).o || exit 1; \
	done

$(B):
	@mkdir -p $(B)

# Generate a rule per single-file program from the name:source lists above.
define C_RULE
$(B)/$(word 1,$(subst :, ,$(1))): $(word 2,$(subst :, ,$(1))) | $(B)
	$(CC) $(CFLAGS) $$< -o $$@
$(word 1,$(subst :, ,$(1))): $(B)/$(word 1,$(subst :, ,$(1)))
endef
define CXX_RULE
$(B)/$(word 1,$(subst :, ,$(1))): $(word 2,$(subst :, ,$(1))) | $(B)
	$(CXX) $(CXXFLAGS) $(PTHREAD) $$< -o $$@
$(word 1,$(subst :, ,$(1))): $(B)/$(word 1,$(subst :, ,$(1)))
endef
define OMP_RULE
$(B)/$(word 1,$(subst :, ,$(1))): $(word 2,$(subst :, ,$(1))) | $(B)
	$(CXX) $(CXXFLAGS) $(PTHREAD) $(OPENMP) -x c++ $$< -o $$@
$(word 1,$(subst :, ,$(1))): $(B)/$(word 1,$(subst :, ,$(1)))
endef

$(foreach p,$(C_PROGS),$(eval $(call C_RULE,$(p))))
$(foreach p,$(CXX_PROGS),$(eval $(call CXX_RULE,$(p))))
$(foreach p,$(OMP_PROGS),$(eval $(call OMP_RULE,$(p))))

# Week7 shape hierarchy: Shape (abstract) <- Circle, Rect
$(B)/shapes: lectures/Week7/shape.cpp lectures/Week7/circle.cpp lectures/Week7/rectangle.cpp lectures/Week7/main.cpp | $(B)
	$(CXX) $(CXXFLAGS) -Ilectures/Week7 $^ -o $@
shapes: $(B)/shapes

# Week7 AnimalsLab: Animal (abstract) <- Cat, Dog, Duck
$(B)/animals: $(wildcard lectures/Week7/AnimalsLab/*.cpp) | $(B)
	$(CXX) $(CXXFLAGS) -Ilectures/Week7/AnimalsLab $^ -o $@
animals: $(B)/animals

# Week9 operator overloading
$(B)/rational: lectures/Week9/Rational.cpp lectures/Week9/main.cpp | $(B)
	$(CXX) $(CXXFLAGS) -Ilectures/Week9 $^ -o $@
rational: $(B)/rational

test: all
	@./tests/smoke.sh

clean:
	rm -rf $(B)
