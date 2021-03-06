<h2>Release 0.8 - Known Problems</h2>

The following is collected email of reported problems with release
0.8 of the Mercury distribution.  Included, where possible, are
patches.

<p>
<hr>
<p>
Subject: bug report - Inf and NaN
<br>
Date: Wed, 4 Oct 1995
<p>
The following module causes an "undefined variable Inf" error in the
generated C code, because 1E400 == Infinity, which gets printed as `Inf'.
<p>
<pre>
:- module hello.
:- interface.
:- import_module io.

:- pred main(io__state::di, io__state::uo) is det.

:- implementation.

main -->
	io__write_float(1E400),
	io__write_string("\n").
</pre>
<p>
<hr>
<p>
Subject: map__lookup failed in profiler
<br>
Date: Tue, 7 May 1996
<p>
When profiling programs that have been compiled on the Alpha using
shared libraries, the profiler will abort with a "Software Error:
map__lookup failed" message.  The work-around is to link with
`--static'.
<p>
This is actually due to a bug in the Alpha shared library mechanism,
which does not conform to the ANSI C standard.  So there is not
much we can do about this one.
<p>
<hr>
<p>
Subject: nit in error msg
<br>
Date: Thu, 16 May 1996
<p>
Here's another small error in an error message.  If you comment out
the [] clause for the functions car/1 or cdr/1, you get this message:
<p>
<pre>
fntest.m:023: In `car(in) = out':
fntest.m:023:   Error: determinism declaration not satisfied.
fntest.m:023:   Declared `det', inferred `semidet'.
fntest.m:023:   in argument 1 of clause head:
fntest.m:023:   unification of `HeadVar__1' and `[X | V_4]' can fail.
</pre>
<p>
It says Declared `det', inferred `semidet', but I never declared it at
all.  It's a bit misleading.  Certainly not a major problem, and the
later part of the message makes it quite clear what the problem is,
but I thought I'd point it out to you before I forgot it.

<p>
<hr>
<p>
Subject: missed mode error
<br>
Date: Tue, 28 May 1996
<p>
Another one for the bug report file:
<p>
The goal `some [X, Y] X \= Y' should be a mode error,
but the current mode checker doesn't report an error.
Instead, the compiler goes on to generate code which gives
the wrong answer.  For example, the following program prints out `no'.
The same problem also occurs with `some [X, Y] (X = Y -> fail ; true)'.
<p>
<pre>
:- module bug.
:- interface.
:- import_module io.

:- pred main(io__state::di, io__state::uo) is det.

:- implementation.

main --> 
	( { p } -> io__write_string("yes\n") ; io__write_string("no\n") ).

:- pred p is semidet.
p :-
	some [X, Y] X \= Y.
</pre>
<p>
The bug occurs only when the variables being unified inside a negated
context are not live, i.e. when it is the last occurrence of those variables.

<p>
<hr>
<p>
Subject: bug with PC values on Alpha
<br>
Date: Wed, 12 Jun 1996
<p>
On the alpha, if the Mercury runtime catches a signal, it
sometimes prints out the wrong value for the PC (program counter).
<p>
<hr>
Subject: inter-module optimization and abstract exported equivalence types.
<br>
Date: Thu, 19 Feb 1998
<p>
In some cases the compiler reports spurious ambiguity errors when compiling
with `--intermodule-optimization'. This is due to the definition of abstract
exported equivalence types being made visible by inter-module optimization.
In this example, with `--intermodule-optimization' the compiler sees the
declaration `:- type var == int' from term.m and then cannot determine whether
`Elem' has type `int' or `pair(int)'.
The work-around is to add an explicit type qualification.
<pre>
:- module foo.
:- interface.
:- import_module list, term.
:- pred test(list(var)::in) is det.
:- implementation.
:- import_module int, std_util.

test(Args0) :-
	MakeIndex =
		lambda([Elem0::in, Elem::out, Index0::in, Index::out] is det, (
			Elem = Elem0 - Index0,
			Index is Index0 + 1
		)),
	list__map_foldl(MakeIndex, Args0, _, 0, _).
</pre>
