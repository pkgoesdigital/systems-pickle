#!/usr/bin/env sh
# Smoke-test every program the course builds.
#
# This is not a unit-test suite — these are lecture demos and labs, and most
# of them just print. The bar here is: it runs, it exits 0, and where there
# is a knowable right answer we check it. That's enough to catch the kind of
# rot this repo actually suffers from (compilers changing under it).
#
#   ./tests/smoke.sh            after `make`
#   make test                   builds first, then runs this
#
# Portability: `timeout` doesn't exist on macOS, so we use perl's alarm.

B=build
pass=0
fail=0
skip=0

# run <seconds> <name> <cmd...>  — run with a time limit, stdin closed
run() {
  _t=$1; shift
  _n=$1; shift
  _out=$(perl -e 'alarm shift; exec @ARGV' "$_t" "$@" </dev/null 2>&1)
  _rc=$?
  if [ $_rc -eq 0 ]; then
    printf 'PASS  %-18s\n' "$_n"
    pass=$((pass + 1))
  else
    printf 'FAIL  %-18s (exit %s)\n%s\n' "$_n" "$_rc" "$(echo "$_out" | head -5)"
    fail=$((fail + 1))
  fi
}

# expect <name> <cmd> <substring> — run and require the output to contain it
expect() {
  _n=$1; _c=$2; _want=$3
  _out=$(perl -e 'alarm 20; exec @ARGV' "$_c" </dev/null 2>&1)
  if echo "$_out" | grep -qF "$_want"; then
    printf 'PASS  %-18s (found "%s")\n' "$_n" "$_want"
    pass=$((pass + 1))
  else
    printf 'FAIL  %-18s (expected "%s")\n%s\n' "$_n" "$_want" "$(echo "$_out" | head -5)"
    fail=$((fail + 1))
  fi
}

skipped() {
  printf 'SKIP  %-18s (%s)\n' "$1" "$2"
  skip=$((skip + 1))
}

echo "== runs clean"
for p in lecture1 lecture2 lecture3 lecture4 lec3 lecture4.18 pointersWStructs \
         fp tc bitset baseConv linkedList cppOOP allShapes th1 th1-1 th1-2 \
         pi pithread; do
  [ -x "$B/$p" ] && run 20 "$p" "$B/$p"
done

echo
echo "== checked output"
# Week4 linked list: builds [1,2,3,4] then frees it
expect linkedList     "$B/linkedList"       "[1, 2, 3, 4, ]"
# Week3 base conversion: binary 11001 is 25. This one is worth pinning —
# binToDec() summed into an uninitialized int, so it was returning the right
# answer only by luck of what sat on the stack.
expect baseConv       "$B/baseConv"         "decimalToReturn: 25"
# Week6 pi approximations — both should land near 3.14
expect pi             "$B/pi"               "3.14"
expect pithread       "$B/pithread"         "3.14"
# Week7 polymorphism: a Rect 3x2 knows its own area
expect shapes         "$B/shapes"           "Rect with width of 3"
# Week7 virtual dispatch through a Shape* pointing at a Circle
expect shapes-virtual "$B/shapes"           "Circle with radius of 5"
# Week7: an Animal* holding a Cat still says meow (virtual dispatch)
expect animals        "$B/animals"          "meow"
# ...and the Duck quacks through the same base pointer
expect animals-duck   "$B/animals"          "quack"
# Week9 operator overloading: 5/3 * 1/1 == 5/3
expect rational       "$B/rational"         "5/3"

echo
echo "== reads stdin"
if [ -x "$B/lab2" ]; then
  _out=$(perl -e 'alarm 20; exec @ARGV' "$B/lab2" < labs_projects/inputFile 2>&1)
  if [ $? -eq 0 ]; then printf 'PASS  %-18s (fed labs_projects/inputFile)\n' lab2; pass=$((pass + 1))
  else printf 'FAIL  %-18s\n%s\n' lab2 "$(echo "$_out" | head -5)"; fail=$((fail + 1)); fi
fi
if [ -x "$B/testScanF" ]; then
  _out=$(echo "2 3" | perl -e 'alarm 20; exec @ARGV' "$B/testScanF" 2>&1)
  if echo "$_out" | grep -qF "2 + 3 = 5"; then printf 'PASS  %-18s (2 + 3 = 5)\n' testScanF; pass=$((pass + 1))
  else printf 'FAIL  %-18s (expected "2 + 3 = 5")\n%s\n' testScanF "$_out"; fail=$((fail + 1)); fi
fi
if [ -x "$B/lab1" ]; then
  _out=$(printf '5\n7\n9\n' | perl -e 'alarm 20; exec @ARGV' "$B/lab1" 2>&1)
  if [ $? -eq 0 ]; then printf 'PASS  %-18s (fed 3 scores)\n' lab1; pass=$((pass + 1))
  else printf 'FAIL  %-18s\n%s\n' lab1 "$(echo "$_out" | head -5)"; fail=$((fail + 1)); fi
fi
if [ -x "$B/lab2Numbers" ]; then
  _out=$(printf '5\n7\n9\n' | perl -e 'alarm 20; exec @ARGV' "$B/lab2Numbers" 2>&1)
  if [ $? -eq 0 ]; then printf 'PASS  %-18s (fed 3 numbers)\n' lab2Numbers; pass=$((pass + 1))
  else printf 'FAIL  %-18s\n%s\n' lab2Numbers "$(echo "$_out" | head -5)"; fail=$((fail + 1)); fi
fi

echo
echo "== threading / OpenMP (small ranges so they finish)"
# The 2019 defaults sweep 1000..1,000,000 with naive trial division; the
# range is a CLI arg now, so the smoke test uses a small one.
[ -x "$B/threads" ] && run 30 threads "$B/threads" 1000 20000 4
[ -x "$B/IntroToPPOpenMp" ] && run 30 IntroToPPOpenMp "$B/IntroToPPOpenMp"
[ -x "$B/piomp" ] && expect piomp "$B/piomp" "3.14"

echo
echo "== Week8 sockets (head + node, end to end on port 8098)"
# Neither program can be tested alone: head blocks in accept() until node
# connects. So run the pair — head in the background, node against it — and
# check the message actually crossed the socket in both directions.
if [ -x "$B/head" ] && [ -x "$B/node" ]; then
  _hlog=$(mktemp)
  "$B/head" > "$_hlog" 2>&1 &
  _hpid=$!
  sleep 1
  _nout=$(echo "hello from node" | perl -e 'alarm 15; exec @ARGV' "$B/node" 2>&1)
  sleep 1
  kill "$_hpid" 2>/dev/null
  wait "$_hpid" 2>/dev/null

  if grep -qF "Here is the message: hello from node" "$_hlog"; then
    printf 'PASS  %-18s (node -> head delivered)\n' "sockets-send"
    pass=$((pass + 1))
  else
    printf 'FAIL  %-18s (head never got the message)\n%s\n' "sockets-send" "$(cat "$_hlog")"
    fail=$((fail + 1))
  fi

  if echo "$_nout" | grep -qF "I got your message"; then
    printf 'PASS  %-18s (head -> node replied)\n' "sockets-reply"
    pass=$((pass + 1))
  else
    printf 'FAIL  %-18s (node never got the reply)\n%s\n' "sockets-reply" "$_nout"
    fail=$((fail + 1))
  fi
  rm -f "$_hlog"
fi

echo
echo "== skipped by design"
skipped forkwaitexample "sleeps 25s on purpose to demo waitpid/SIGCHLD"
skipped lecture6        "execvp()s ./test, which the notes never included"
# Builds (that is what CI proves), but as submitted blocking() recomputes
# numPrimesInRange(start, stop) inside every one of ~1e6 iterations, so it
# cannot finish. Left as-is on purpose — see the header of Lab06_OpenMp.cpp.
[ -x "$B/Lab06_OpenMp" ] && skipped Lab06_OpenMp "quadratic as submitted; see its header comment"

echo
echo "-------------------------------"
printf '%d passed, %d failed, %d skipped\n' "$pass" "$fail" "$skip"
[ "$fail" -eq 0 ] || exit 1
