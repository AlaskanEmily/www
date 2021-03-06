<h2>New in release 0.6 of the Mercury distribution</h2>

<ul>
<li>
We now provide preliminary support for type and mode inference.
<p>
The `:- pred' and `:- mode' declarations are now optional for
predicates that are local to a module; the compiler will infer
the types and modes automatically.
<p>
This support is not yet complete, and so type and mode inference are
not enabled by default.  They can be enabled using the `--infer-types'
and `--infer-modes' options.  The limitations of the current
implementation are: (1) type inference loops for certain very rare
type-incorrect programs; (2) mode inference doesn't support
reordering; (3) there are some modes which the current mode inference
algorithm is not capable of inferring.
<p>
Note that omitting type and mode declarations can significantly
reduce the quality of the compiler's error messages; if you have
trouble understanding an error message, then it is a good idea to add
explicit type and mode declarations.

<li>
We now support functional syntax.
<p>
Functions can be declared with `:- func' declarations,
and defined using equations or conditional equations,
in a similar manner to the way predicates are declared
with `:- pred' declarations and defined using facts and rules.
Terms can contain function calls and if-then-elses.
For example:
<p>
<pre>
   :- func sum(list(int)) = int.   
   sum([]) = 0.                            % unconditional equations
   sum([X|Xs]) = X + sum(Xs).              % using function calls

   :- func max(int, int) = int.
   max(X, Y) = Max :-                      % conditional equation
           (X >= Y -> Max = X ; Max = Y).

   :- func min(int, int) = int.
   min(X, Y) = (if X >= Y then X else Y).  % unconditional equation
                                           % using if-then-else expression
</pre>
<p>
By default, functions are assumed to have a single det mode with
all arguments input and the result output, but you can override
this default by supplying explicit mode declarations; for example,
this allows you to use functions in a backwards mode to compute the
function inverse. 
<p>
Zero-arity functions can be used to define constants.
<p>
<pre>
   :- func pi = float.
   pi = 3.14159265359.
</pre>
<p>
We also support higher-order functions and function lambda expressions.
See the Mercury language reference manual for details.
<p>
The support for functions is not quite complete; there is one minor
limitation and one major one.  The minor limitation is that the C
interface does not yet support Mercury functions.  (Fortunately there
is an easy work-around - since the C interface does support predicates,
you can just make your Mercury function call a Mercury predicate.)
The major limitation is that there is currently no support for
debugging programs using functional syntax; obviously using a Prolog
system won't work, since Prolog doesn't support functions.

<li>
We now support overloading of predicates (and functions) with the
same name and arity defined in different modules. 
<p>
Previously, an explicit module qualifier was required to resolve the
ambiguity; now, the type-checker will use the types to resolve the
ambiguity, if possible.  (Note that you cannot define more than one
predicate with the same name and arity in the same module.  Allowing
that would add considerable complexity to the syntax, and would be
of arguable utility, so we do not anticipate lifting that restriction.)

<li>
We now support defining types with the same name in different modules.
<p>
Previously this resulted in multiply defined symbol errors in certain
circumstances, e.g. when profiling.

<li>
We have removed the limitations on the number and order of arguments in
higher-order predicate calls.

<li>
Support for floating point is much improved.
<p>
The above-mentioned support for functional syntax and overloading
have enabled major improvements in the interface used for floating
point.  You can now use the usual arithmetic and comparison
operators, rather than the cumbersome builtin_float_plus (etc.)
predicates that were used previously.  We have also improved code
generation for floating point operations, by avoiding many
unnecessary boxing/unboxing operations, and by making the
`--static-ground-terms' optimization apply also to floating point
constants.  These two optimizations improved performance on the
realistic "pseudoknot" benchmark by nearly a factor of four.
(There's still plenty of room for performance improvements, however.)

<li>
We now support reverse mode arithmetic.
<p>
This means that a goal such as `A is B + C' can be used not only to compute
A from B and C, but also to compute B from A and C, or to compute C from
A and B.

<li>
We have added some new compiler options to simplify the choice of which
optimization options to enable.

<ul>
<li>
You can now use `-O<var>n</var>' to select an optimization level between
-1 and 6.
The default level is `-O2'; if you want to minimise compilation
time, compile with `-O0', which disables all optimizations except those
that actually improve overall compilation speed.

<li>
You can now use `--optimize-space' to select optimization for space,
instead of optimization for time (which is the default).
</ul>

<li>
We have continued to improve the compiler's optimization.
<p>
As well as the above-mentioned improvements to float-point code generation:

<ul>
<li>
We now specialise calls to higher-order predicates within the same module
in the case when the higher-order arguments have known values.
This optimization is enabled by the `--optimize-higher-order' option.

<li>
We now specialise calls to predicates within the same module which have
unused arguments.  This often happens for polymorphic predicates, since
the compiler introduces type_info arguments which are often unused.
This optimization is enabled by the `--optimize-unused-args' option.

<li>
The `--inlining' option now governs the settings of three separate options.
One, `--inline-simple', reproduces the previous behaviour of `--inlining':
it inlines procedures whose definition is simple (e.g. a conjunction of
builtins). Another, `--inline-single-use', tells the compiler to inline
all procedures that are called exactly once. The compiler can also
inline procedures called more than once as long as they are not too
big; the argument of the option `--inline-threshold' sets a limit
on the size of the procedure definition (roughly in terms of the number
of logical connectives it has) multiplied by the number of calls to
the predicate.

<li>
There's a new option `--optimize-dead-proc' option to eliminate unused
procedures within a module.  This is useful even if the original source
code didn't contain any unused procedures, since inlining and code
specialisation can make a procedure unused even if there original source
had calls to that procedure.

<li>
There's a new option `--split-c-files' which causes the compiler to put
each C function in its own C file, so that the linker can link in only
what is used, and a new Mmake target `foo.split' for
building a version of `foo' compiled with `--split-c-files'.
(`--split-c-files' has much the same effect as `--optimize-dead-proc',
except that it works globally, not just within a module.)
On platforms for which we don't support shared libraries, installing
a split version of the Mercury library fixes the problem of dumb Unix
linkers dragging in nearly the entire library even if most of it is
unused, and so reduces the size of a hello world program from >400k
to around 120k.

<li>
The code generator generates special code for dense switches in
which all the output variables are constant terms.  Instead of
generating dense jump tables, it puts the answers in static constant
arrays, and retrieves them using array indexing, avoiding
an expensive jump and reducing code size.

<li>
The code generator now emits better code for constructing deeply nested
terms, and avoids some unnecessary register shuffling.

<li>
The value numbering optimization now processes code sequences
containing several heap allocations.

<li>
The `--pred-value-number' option now works.  If it is given, and
value numbering notices that a value is available from a location
that is faster to access than the one from which another code
sequence retrieves the value, this other code sequence will be
reoptimized taking this into account.
</ul>

<li>
We now support a C-to-Mercury interface, ie. we allow C code to call
Mercury predicates, using a new `pragma export' declaration.
(Unfortunately, this is not yet documented.  There is however a
fairly detailed and reasonably well-documented example in the
samples/c_interface/c_calls_mercury directory.)

<li>
We have added a little bit of inline assembler code for the Alpha so
that we can support the use of gcc non-local gotos and asm labels.
This improved both code size and execution speed for the Alpha port
by about 20-25%.

<li>
We have ported the Mercury implementation to RS/6000 systems running AIX.
(Thanks to Andreas Kuehlmann.)

<li>
We have made a few changes to the Mercury standard library.
The changes are listed here, but see the library reference manual for
details such as documentation on the new predicates.

<ul>
<li>
The getopt library is now more flexible.  It can handle command
line switches (such as `-O2') that affect the values of many
options, and it can handle long options that specify a value after
an equal sign, in the GNU style (e.g. `--optimization-level=2').

<li>
We have added a few new predicates using higher order facilities:
list__map/3, list__filter/3, list__filter/4, list__foldl/4,
list__foldr/4, list__sort/4 and list__merge/4 in list.m and
maybe_pred/3 in std_util.m. 

<li>
There are a couple of new all-solutions predicates in std_util.m:
solutions_set/2 and unsorted_solutions/2. 

<li>
We have added some additional predicates for handling association lists:
assoc_list__search/3 and assoc_list__remove/4.

<li>
There are a few new predicates for converting floats to ints:
float__ceiling_to_int/2, float__floor_to_int/2
float__round_to_int/2, and float__truncate_to_int/2.

<li>
There are quite a few changes to the graph module.  The interface has been
made more consistent with the rest of the library.  The predicate
graph__lookup_node/3 has been replaced by two predicates:
graph__search_node/3 which is nondet and returns all the nodes with
matching data, and graph__find_matching_nodes/3 which is det and
returns all the nodes with matching data.

<li>
We have renamed the varset__lookup predicates to varset__search in order to
conform to our general naming convention.

<li>
We have removed the (undocumented) library predicate list__map_maybe/3.

<li>
The set module is now implemented using sorted lists rather than
unsorted lists.  (The interface is still the same.)  The old
unsorted lists representation is still available, in the
set_unordlist module.
</ul>
</ul>
