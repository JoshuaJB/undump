# undump
This tool converts an ELF core dump into an executable ELF.
The output binary will attempt to resume at the exact same
location as where it crashed, with the same register, stack,
and heap state.

This is a port to x86_64 of the original public version of
undump which only supported i386.

## Usage
Core dumps often exclude the code segments from the original
binary, so you also have to give `undump` the path to the
executable that crashed.

`./undump <core dump> <original binary> <output binary>`

## Uses
This is really helpful if you need to execute functions from
the context of the core dump. Typically, when analyzing a
core dump in GDB, if you try to call a function it will
complain
`You can't do that without a process to debug.`

GDB seems to treat core dumps as immutable, and so it refuses
to call functions as they may (among other things) have
side effects.

`undump` can get around this by converting the program into
a normal ELF. This gets around GDB's issue with mutating a
core dump. The output binary from `undump` will likely crash
immediately with the same error as it did before if executed
normally, but that is not the point of `undump`. You want to
instead start GDB with the output binary and set a
breakpoint at exactly where your program crashed before.
Then, `run`. You should hit your breakpoint with the exact
same state as you had before in the core dump, but with the
added capability to mutate data and call functions in GDB.

This is particularly helpful if you have a GTK-based
text editor (such as `gedit`) crash and you need to call
`gtk_text_buffer_get_text()` to recover your unsaved
text from the core dump.

## TODO
1. Re-add library LOAD segments to the output binary
2. Correctly re-locate sections if the original binary required dynamic loading

## Additional Notes
As of Linux 5.8, there is a bug in the ELF loader which
prevents ELFs from having more than 156 program header
entries. You will get "Exec format error" when you try
to run the output binary when encountering this bug.
