# systems-pickle 🥒

[![build](https://github.com/pkgoesdigital/systems-pickle/actions/workflows/build.yml/badge.svg)](https://github.com/pkgoesdigital/systems-pickle/actions/workflows/build.yml)

Systems programming in C and C++ (DU, 2019) — lecture code, labs, and
projects, modernized in 2026 so all of it builds and runs on a current
compiler.

```bash
make          # build all 34 programs into build/
make test     # build, then smoke-test everything that can run headless
make shapes   # build just one, then: ./build/shapes
make clean
```

macOS note: AppleClang ships no OpenMP runtime. Either `brew install libomp`
and `make OPENMP="-Xpreprocessor -fopenmp -lomp"`, or skip those two
programs with `make OPENMP=""`. Linux/gcc needs nothing — CI builds them.

## The course

| Week | Topic | Highlights |
|---|---|---|
| 1 | C basics, pointers | `lab1.c` (scores), `lecture1.c` (pointers, swap, arrays-are-pointers) |
| 2 | malloc, C strings, linked lists | `lab2.c` (word counts), `lecture2.c` (heap arrays), `lecture4.c` (linked list) |
| 3 | Bit manipulation, base conversion | `bitset.c`, `baseConv.c` |
| 4 | Type punning, Huffman coding | `fp.c`/`tc.c` (float/int bit layouts), `Huffman/` |
| 5 | Processes and threads | `forkwaitexample.c` (fork/waitpid/SIGCHLD), `threads.cpp` (parallel prime counting) |
| 6 | Parallelism | `pi.cpp` vs `pithread.cpp` vs `piomp.cpp` — same π, three ways |
| 7 | C++ OOP, OpenMP | `shapes` and `animals` (abstract base + virtual dispatch), `Lab06_OpenMp.cpp` |
| 8 | Sockets | `head.c` (server) + `node.c` (client) — see [lectures/Week8/README.md](lectures/Week8/README.md) |
| 9 | Operator overloading | `Rational.cpp` — `operator*`, `operator=`, `operator<<` |

`labs_projects/` holds the Java socket work (SocketPainter, sockets,
lab05_Threads) — Eclipse projects, not part of `make`.

## What was modernized (2026)

The 2019 code is preserved in git history. Everything below was fixed in
place so the course runs on a 2026 compiler:

- **13 committed binaries and 16 `.class` files are gone.** Every program
  was compiled by hand and its binary committed next to the source; those
  only ever ran on one 2019 laptop. The `Makefile` replaces them, and CI
  proves it on every push.
- **Implicit function declarations are now errors**, not warnings (clang 15+
  / gcc 14+). `head.c` called `read`/`write` with `<unistd.h>` commented
  out; `lecture3.c` called `malloc` without `<stdlib.h>`; `lecture6.c`
  included `<cis/wait.h>` (the department's course code, not a real header).
- **Case-sensitive includes.** `main.cpp` included `shape.h`/`circle.h`/
  `rectangle.h`; the files are `Shape.h`/`Circle.h`/`Rect.h`. That works on
  macOS and fails on Linux — which is where CI runs.
- **`shape.cpp`/`circle.cpp`/`rectangle.cpp` never compiled at all**: they
  re-declared whole classes instead of defining the methods, wrote
  `virtual` on out-of-class definitions, and named the class `shape` while
  the header said `Shape`.
- **Real bugs fixed**: a use-after-free in `main.cpp` (copying `*r1` after
  `delete r1`), a `printf("%d\n")` with no argument, `int temp == *pp`,
  `printf{...}`, an unterminated `printf("%d %d\n", a[0], *(a+1);`, an
  out-of-bounds `a[6]` on `int a[5]`, and a linked list whose `llAdd` took
  `LinkedList*` where its own comments explain it needs `LinkedList**`.
- **`head.c` now sets `SO_REUSEADDR`** so re-running the server doesn't die
  with "ERROR on binding" for a minute after each exit.
- **`threads.cpp` takes its range as arguments** (`./threads [min] [max]
  [threads]`, same defaults) so it can be exercised without counting every
  prime below a million.
- **Editor and OS cruft removed**: `*~` backups, `#autosave#` files,
  8 `.DS_Store`, `Thumbs.db`, a broken symlink, and a duplicate zip.

### Two files where the errors are the lesson

`cppOOP.cpp` and `lecture3.c` are live lecture transcriptions that
*deliberately* contain code the compiler must reject — assigning through a
`const&`, touching a private member, `Circle c3 = new Circle();`, writing to
a pointer just set to `NULL`. Those lines are now commented, each with a note
saying what happens if you uncomment it. The lesson survives; the file builds.

### Drafts kept, not deleted

Emacs autosaves that turned out to contain unique work are preserved as
`*.c.txt` rather than dropped:

- `Huffman/linkedList-huffman-draft.c.txt` — the tree-node (`.c`,
  `.frequency`) version of the list, mid-migration. It explains why
  `linkedList.h` had a `tnode` struct typedef'd as `LinkedList` while
  `linkedList.c` still used `.value`/`.next`. Both structs now coexist under
  their own names.
- `Huffman/hcompress-fragment.c.txt` — the only surviving trace of the
  `hcompress` assignment's `main()`.
- `Week7/Lab06_OpenMp-linux-draft.cpp.txt` — was named
  `pauklima@linux1.cs.du.edu`, an artifact of an `scp` that lost its
  argument and wrote the destination to a local file.
- `Week1/lab01Copy.c.txt` — an alternate draft of lab 1.

## Testing

`tests/smoke.sh` (run by `make test`) builds everything and then, for each
program that can run headless: runs it, requires exit 0, and where there is
a knowable answer, checks it — the linked list prints `[1, 2, 3, 4, ]`, both
π programs land on 3.14, an `Animal*` holding a `Cat` still says `meow`,
`Rational(5,3) * Rational(1,1)` is `5/3`. The Week 8 sockets are tested as a
pair: `head` in the background, `node` against it, asserting the message
crosses in both directions.

Two programs are skipped on purpose: `forkwaitexample` sleeps 25 seconds to
demonstrate `waitpid`, and `lecture6` `execvp`s a `./test` binary the notes
never included.
