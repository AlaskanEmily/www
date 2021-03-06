<h2>New in release 0.11 of the Mercury distribution</h2>

<h3>HIGHLIGHTS</h3>

Changes to the Mercury language:
<ul>
<li> Support for constrained polymorphic modes.
<li> Addition of state variable syntax.
<li> Improved support for higher-order functions.
<li> Predicate and function equivalence type and mode declarations.
<li> Support for defining predicates or functions
  using different clauses for different modes.
<li> Support for Haskell-like "@" expressions.
<li> Generalized foreign language interface.
</ul>

<p>

Changes to the Mercury compiler:
<ul>
<li> A new `--make' option, for simpler building of programs.
<li> A new `--smart-recompilation' option, for fine-grained dependency tracking.
<li> A new optional warning: `--warn-non-tail-recursion'.
<li> A new optimization: `--constraint-propagation'.
<li> A new optimization: `--loop-invariants'.
<li> Support for arbitrary mappings from module name to source file name. 
</ul>

<p>

Portability improvements:
<ul>
<li> Mac OS X is now supported "out-of-the-box".
<li> On Windows we now support generating non-Cygwin executables.
<li> Better conformance to ANSI/ISO C.
</ul>

<p>

Changes to the compiler back-ends:
<ul>
<li> The native code Linux/x86 back-end is now "release quality".
<li> The .NET CLR back-end is much improved.
</ul>

<p>

Major improvements to the Mercury debugger, including:
<ul>
<li> Support for source-linked debugging using vim (rather than emacs).
<li> Command-line completion.
<li> Ability to display values of higher-order terms.
<li> Declarative debugging.
<li> Support for transparent retries across I/O.
</ul>

<p>

A new profiler, which we call the Mercury deep profiler or mdprof:
<ul>
<li> Supports both time and memory profiling.
<li> Gathers information about individual call sites as well as procedures.
<li> Eliminates the assumption that all calls to a procedure have equal cost.
<li> Allows users to explore the gathered data interactively with a web browser.
</ul>

<p>

Numerous minor improvements to the Mercury standard library.

<p>

A new testing tool in the extras distribution.

<h3>DETAILED LISTING</h3>

Changes to the Mercury language:

<ul>

<li> We have added support for constrained polymorphic modes.  See the section
  on Constrained Polymorphic Modes in the Modes chapter of the Mercury Language
  Reference Manual.

<li> A more general alternative to DCG syntax has been added to the language
  to simplify the manipulation of threaded state.  See the section on State
  Variables in the Syntax chapter in the Mercury Language Reference Manual.

<li> If a higher-order function term has inst 'ground' it is now assumed to have
  the standard higher-order function inst 'func(in, .., in) = out is det'.
  This makes higher-order functional programming much easier, particularly when
  passing functions to polymorphic predicates.

  This change is not completely backwards compatible since, for safety,
  we must now disallow calls that would cause a variable that has a
  nonstandard function inst to become 'ground'.

<li> Predicate and function type and mode declarations can now be expressed
  in terms of higher-order predicate and function types and insts, rather
  than explicitly listing the argument types and modes.  This is useful
  where several predicates or functions must have the the same type and
  mode signature.

  <p>

  For example:
  <pre>
	:- type foldl_pred(T, U) == pred(T, U, U).
	:- inst foldl_pred == (pred(in, in, out) is det).
	:- pred p `with_type` foldl_pred(T, U) `with_inst` foldl_pred.
  </pre>
 
  <p>

  For more information see the "Predicate and function type declarations"
  section of the "Types" chapter and the "Predicate and function mode
  declarations" section of the "Modes chapter" of the Mercury Language
  Reference Manual.

<li> The constructor for lists is now called '[|]' rather than '.'.
  `./2' will eventually become the module qualification operator.
  This change only affects programs which use `./2' explicitly.
  Programs which only use the `[H | T]' syntax will be unaffected.

<li> We've added a new kind of expression to the language.
  A unification expression, written `X @ Y', unifies X and Y
  and returns the result.

  <p>

  Unification expressions are most useful when writing switches:
  <pre>
	p(X, X) :- X = f(_, _).
  </pre>
  can now be written as
  <pre>
	p(X @ f(_, _), X).
  </pre>

  <p>

  See the "Data-terms" section of the "Syntax" chapter of the
  Mercury Language Reference Manual for more details.

<li> We've extended the language to allow you to specify different clauses
  for different modes of a predicate or function.  This is done by
  putting mode annotations in the head of each clause.
  For example, you can write
  <pre>
	:- mode p(in).
	:- mode p(out).
	p(X::in) :- ... /* clause for the `in' mode */
	p(X::out) :- ... /* clause for the `out' mode */
  </pre>

  <p>

  For predicates or functions which have different clauses for different
  modes, you need to either (1) add a `pragma promise_pure' declaration
  for the predicate or function, and ensure that the declarative semantics
  remains the same in each mode, or (2) declare the predicate as impure.

<li> We now allow `:- pragma promise_semipure' declarations. For more
  information, see the "Impurity" chapter of the Mercury Language
  Reference Manual.

<li> We've added `:- pragma c_import_module' declarations, which are
  used to make the C declarations for predicates and functions with
  `:- pragma export' declarations in the imported module visible
  to any C code in the importing module. `mmake' uses
  `:- pragma c_import_module' declarations to make sure that the
  header file for the imported module is built before it is needed,
  which it can't do if the header file is explicitly #included.

<li> The foreign language interface has been generalized to support
  interfacing with languages other than C.

  <p>

  In particular, the Mercury compiler's .NET back-end now supports
  interfacing with C#, IL, and "Managed C++" (C++ with Microsoft's
  extensions for the .NET CLR).  Mercury procedures can be defined
  using inline code fragments written in any of these languages.

  <p>

  For details, see the new "Foreign language interface" chapter of
  the Mercury Language Reference Manual.

<li> We've removed the undocumented operators `export_adt', `export_cons',
  `export_module', `export_op', `export_pred', `export_sym', `export_type',
  `import_adt', `import_cons', `import_op', `import_pred', `import_sym',
  `import_type' `use_adt', `use_cons', `use_op', `use_pred', `use_sym'
  and `use_type'. These operators were reserved for module system
  extensions which are unlikely to be implemented.

</ul>

<p>

Changes to the Mercury standard library:

<ul>

<li> The Prolog-style term comparison operators @&lt;, @=&lt;, @&gt;, @&gt;=
  are now builtin.

<li> A new builtin function ordering/2 has been added.

<li> We've added a function to io.m to construct io__error codes from error
  messages: `io__make_io_error'.

<li> The assumptions that we make about user supplied comparison predicates and
  functions have been relaxed to allow more general orderings.  The new
  assumptions are documented in builtin.m.

<li> The builtin predicates !/0 and !/2 from Mercury's Prolog heritage have been
  removed (`!' is now a prefix operator used in the state variable syntax).

<li> We have added the type class `pprint__doc/1' and a new concatenation
  operator, `++/2', which should make it easier to construct doc values.
<li> Performance bugs in `pprint__to_doc' have now been fixed.  Even
  very large terms can now be converted to docs and pretty printed without
  causing a machine to thrash or run out of memory.

<li> `io__read_file' and `io__read_file_as_string' now have better error
  handling. The result types have changed, so code using these predicates
  will need minor modifications.
<li> We've added predicates `io__input_stream_foldl', `io__input_stream_foldl_io'
  and `io__input_stream_foldl2_io', which apply a predicate to each character
  of an input stream in turn.
<li> We've added predicates `io__binary_input_stream_foldl',
  `io__binary_input_stream_foldl_io' and `io__binary_input_stream_foldl2_io',
  which apply a predicate to each byte of a binary input stream in turn.
<li> We've added versions of `io__print', `io__write' and `io__write_univ'
  that allow the caller to specify how they should treat values of noncanonical
  types, e.g. types in which a single semantic value may have more than one
  syntactic expression.
<li> We've added four new predicates to allow programs to retrieve current
  streams: `io__current_input_stream', `io__current_output_stream',
  `io__current_binary_input_stream', and `io__current_binary_output_stream'.
<li> We've added a predicate to io.m to return the last modification time
  of a file: `io__file_modification_time'.
<li> We've added cc_multi modes to io__write_list/5 and io__write_list/6.
<li> You can now close stdin, stdout and stderr.

<li> We've added four functions to list.m for mapping functions over
  corresponding members of lists: list__map_corresponding/3,
  list__map_corresponding3/4, list__filter_map_corresponding/3
  and list__filter_map_corresponding3/4.
<li> We've added some other new functions to list.m, namely
  list__last_det/2, list__split_last/3 and list__split_last_det/3.
<li> We've added cc_multi modes to list__foldl/4 and list__foldr/4.
<li> We've added a predicate list__map_foldl2.
<li> As mentioned above, the constructor for lists has changed from './2'
  to `[|]/2'. This change affects the behaviour of the term manipulation
  predicates in the standard library when dealing with values of
  type `term__term/1' representing lists. The affected predicates are
  parser__read_term, parser__read_term_from_string, term__type_to_term,
  term__term_to_type, term_io__read_term and term_io__write_term.
  Also beware that std_util__functor and std_util__deconstruct now
  return `[|]' rather than `.' for lists, and calls to std_util__construct
  which construct lists may need to be updated.
<li> We've added the predicate list__is_empty/1 and list__is_not_empty/1.
<li> We've added the predicate list__remove_adjacent_dups/3.

<li> We've added a function version of error/1, called func_error/1, to require.m.

<li> ops.m now defines a typeclass which can be used to define operator
  precedence tables for use by parser.m and term_io.m. See
  samples/calculator2.m for an example program.

  The `ops__table' type has been renamed `ops__mercury_op_table'.
  `ops__init_op_table' has been renamed `ops__init_mercury_op_table'.
  `ops__max_priority' is now a function taking an operator table argument.

<li> The predicates and functions in int.m, float.m, math.m and array.m now
  generate exceptions rather than program aborts on domain errors and
  out-of-bounds array accesses. There are new functions
  `float__unchecked_quotient/2', `int__unchecked_quotient/2' and
  `int__unchecked_rem/2' for which no checking is performed and the
  behaviour if the right operand is zero is undefined.

<li> We've removed the reverse modes of the arithmetic functions in
  float.m and extras/complex_numbers.  (Because of rounding errors,
  the functions aren't actually reversible.)

<li> float__pow now works for negative exponents, and runs much faster
  for large exponents.

<li> We've removed the destructive update modes of string__set_char,
  string__set_char_det and string__unsafe_set_char. The compiler
  currently always stores constant strings in static data, even
  if they are passed to procedures with mode `di', so any attempt
  to update a constant string will cause a crash. Fixing this properly
  will be a lot of work, so for now we have just removed the modes.

<li> We've added string__suffix, string__words/1, string__foldr,
  string__foldl_substring and string__foldr_substring.

<li> The exception module has a new predicate `try_store', which is
  like `try_io', but which works with stores rather than io__states.

<li> We've fixed a bug in time.m. Type `tm' didn't store the day of the month,
  which meant that the functions which required that field (e.g. time__asctime,
  time__mktime) did not work.

  <p>

  The order of the fields of type `time__tm' has been changed so that
  comparison of values of type `tm' whose `tm_dst' fields are identical
  is equivalent to comparison of the times those values represent.

<li> std_util.m now contains predicates and functions `map_maybe',
  `fold_maybe', `map_fold_maybe' and `map_fold2_maybe', which are
  analogues of `list__map', `list__foldl', `list__map_foldl' and
  `list__map_foldl2' operating on values of type `maybe' instead
  of `list'.

<li> We've added a predicate to io.m to return the last modification time
  of a file (io__file_modification_time).

<li> There is a variant of io__call_system, io__call_system_return_signal
  which on interrupt returns the number of the signal which interrupted
  the command rather than just an error message.

<li> We've added added several new predicates for deconstructing terms to
  std_util.m. `named_argument' and `det_named_argument' are analogous
  to `argument' and `det_argument' respectively, but specify the desired
  argument by its name, not its position. We have also added committed choice
  version of all the predicates that deconstruct terms. These differ from the
  existing versions in that they do not abort when called upon to deconstruct
  non-canonical terms, such as values of types with user-defined equality.

<li> We've added a new predicate `intersect_list' in each of the modules
  implementing sets in the Mercury standard library.

<li> We've added a predicate version of `set__fold'.

<li> We've added function versions of `builtin__unsafe_promise_unique',
  `ops__init_op_table' and `ops__max_priority'.

<li> We've added a version of `getopt__process_options' which returns
  the option arguments.

<li> `getopt__process_options' has been modified to allow negation of
  accumulating options. Negating an accumulating option empties
  the accumulated list of strings.

<li> We've added some functions to the term_io module to return printable
  representations of term components as strings.

<li> We've made the outputs of the string concatenation primitives unique.

<li> New convenience/readability predicates `int__even/1' and `int__odd/1'.

<li> New predicate benchmark_det_io for benchmarking code that performs I/O.

<li> We've removed the long obsolete `int__builtin_*' and
  `float__builtin_float_*' predicates, which were synonyms
  for the arithmetic functions dating from when Mercury didn't
  have functions. 

<li> We've added int:'/'/2 as a synonym for int:'//'/2 and false/0 as a
  built-in synonym for fail/0 (both left-overs from Mercury's Prolog
  heritage.)

<li> dir:'/'/2 is now a synonym for `dir__make_path_name'.
  
<li> We've removed the long obsolete predicates `io__read_anything',
  `io__write_anything', and `io__print_anything', which were long ago
  renamed as `io__read', `io__write', and `io__print' respectively.

<li> We've added random__random/5, which produces a random integer in a
  given range, and random__randcount/3, which returns the number of
  distinct random numbers that can be generated.

</ul>

<p>

Changes to the extras distribution:

<ul>

<li> There's a new testing tool called "quickcheck", which is similar to
  Haskell's "QuickCheck".  See quickcheck/tutes/index.html.

<li> The interface to Moose has been changed in a non-backwards compatible
  way to support user-defined modes for the parser state and integrate
  better with lex.

</ul>

<p>

Changes to the Mercury compiler:

<ul>

<li> There is a new `--make' option which performs most of the functions
  of Mmake.  The advantages of `mmc --make' are that no `mmake depend'
  step is necessary and the dependencies are more accurate.  Parallel
  builds are not yet supported.  See the "Using Mmake" chapter of the
  "Mercury User's Guide" for details.

<li> The Mercury compiler can now perform smart recompilation, enabled by the
  `--smart-recompilation' option. With smart recompilation, when the
  interface of a module changes, only modules which use the changed
  declarations are recompiled. Smart recompilation does not yet work
  with `--intermodule-optimization'.

<li> The Mercury compiler can now handle arbitrary mappings from source files
  to module names.  If the program contains modules for which the source
  file name does not match the module name, before generating the
  dependencies the command `mmc -f SOURCES' must be run, where `SOURCES'
  is a list of the names of all of the source files.  If the names of the
  source files all match the contained module names, `mmc -f' need not be run.

<li> There is a new `--use-grade-subdirs' option which is similar to
  `--use-subdirs', but allows multiple grades to be built in a
  directory at the same time.  `--use-grade-subdirs' does not
  work with Mmake (it does work with `mmc --make').

<li> The compiler and scripts accept a `--mercury-stdlib-dir' option,
  which overrides the configured location of the Mercury standard
  library.  There is also an environment variable MERCURY_STDLIB_DIR
  which has the same effect.  The environment variables which were
  previously used to override the location of the standard library
  (MERCURY_ALL_C_INCL_DIRS, MERCURY_ALL_MC_C_INCL_DIRS, MERCURY_INT_DIR,
  MERCURY_C_LIB_DIR, MERCURY_MOD_LIB_MODS, MERCURY_TRACE_LIB_MODS) are
  now deprecated, and will be removed in a future release.
  MERCURY_C_INCL_DIR has already been removed.

<li> We've added a new compiler option `--warn-non-tail-recursion', which
  causes the compiler to issue a warning about any directly recursive
  call that is not a tail call.

<li> The automatically generated header files for modules containing
  `pragma export' declarations are now named `<var>module</var>.mh', not
  `<var>module</var>.h'. This avoids conflicts with system header files.

<li> We've fixed a long-standing bug in the handling of module imports.
  Previously, if `module1' imported `module2' which imported `module3' in
  its interface section, then any types, insts, modes and typeclasses defined
  in the interface of `module3' could be used in `module1' even
  if `module1' did not import `module3' directly.

  <p>

  This change will break some existing programs, but that is easily fixed
  by adding any necessary `:- import_module' or `:- use_module' declarations.

<li> Options for the Mercury runtime can now be set at compile time using
  the new `--runtime-flags' option of ml and c2init.

<li> We've added a new optimization pass -- constraint propagation.

  <p>

  Constraint propagation attempts to transform the code so
  that goals which can fail are executed as early as possible.
  It is enabled with the `--constraint-propagation' option
  (or `--local-constraint-propagation' for a more restricted
  version of the transformation).

<li> The Mercury compiler can now perform inter-module optimization using
  information from transitively imported modules. This is especially
  useful for back-ends which do not support abstract equivalence types
  properly (for example the .NET backend). To disable this behaviour and
  only optimize using information from directly imported modules, use the
  option `--no-read-opt-files-transitively'.

<li> For each `--Xflags' option there is now a `--Xflag' option which allows a
  single quoted argument to be passed to the invoked program.  This is useful
  where the argument is a directory name containing spaces.

<li> The `--convert-to-goedel' option has been removed.
  It never really worked anyway.

</ul>

<p>

Portability improvements:

<ul>

<li> Mac OS X is now supported "out-of-the-box".

  <p>

  See README.MacOSX for details.

<li> On Windows we now support generating non-Cygwin executables.

  <p>

  The Mercury compiler source distribution can be configured using
  `configure --with-cc="gcc -mno-cygwin"'.  This option ensures
  that the Mercury libraries are only linked with the standard
  Windows libraries, not the Cygwin Unix emulation library,
  so Mercury programs don't need Cygwin, and use DOS/Windows-style
  path names rather than Cygwin's Unix-style path names.

  <p>
  
  Note that you still need Cygwin to install and use Mercury.
  The change is that the programs which you build using Mercury
  don't need Cygwin anymore.

<li> Better conformance to ANSI/ISO C.

  <p>

  We now pass all the tests in the Mercury test suite
  when the compiler is built with the "lcc" C compiler,
  which is more strict about ANSI/ISO C conformance than GNU C.
  This should also make it easier to port to other C compilers.

</ul>

<p>

Changes to the Mercury debugger:

<ul>

<li> The debugger can now print goals just as Prolog debuggers do. At an exit
  port of e.g. append, the command "print goal" will print the current goal
  in a form such as "append([1], [2], [1, 2])".

<li> You can now navigate terms in the debugger by argument name as well as by
  argument number.

<li> The debugger can now print higher order values.

<li> The debugger can now print type_info structures. However, since such
  structures are normally of interest to implementors only, the debugger
  will print such values only if the user gives the command "print_optionals
  on".

<li> The debugger can now perform command line completion when compiled
  with GNU Readline support enabled.

<li> We've added a 'view' command to `mdb', which opens a `vim' window and
  in it displays the current source location, updated at each event.  This
  requires X11 and a version of `vim' with the `clientserver' feature
  enabled.

<li> The `--window' mdb option now creates a window for mdb, not
  the program.  The main advantage of the new behaviour is that
  redirection of the program's input and output works.  The old
  behaviour is still available with `mdb --program-in-window'.

<li> The debugger now includes support for declarative debugging.  The `dd'
  command starts diagnosis at any exit, fail or exception port in mdb.  See
  the Mercury User's Guide for more details.

<li> When a program is compiled in a debugging grade, the debugger can be
  asked, via the command `table_io start', to make I/O primitives (such as
  io__open_file, io__write_string etc) idempotent. This means that a given
  call to e.g. io__open_file will open the specified file only once,
  even if retry commands cause the call to be executed more than once.

</ul>

<p>

A new profiler, which we call the Mercury deep profiler or mdprof:

<ul>

<li> The old Mercury profiler is based on the technology of the standard Unix
  profiler gprof. This technology makes the assumption that all calls to a
  given C function (in Mercury, a given function or predicate in a given mode)
  have the same cost, whether the cost being measured is CPU time, memory cells
  allocated, memory words allocated etc. In C programs, this assumption is
  usually close enough to correct for the output of gprof to be useful. In
  Mercury, due to the presence of parametric polymorphism and the significantly
  higher frequency of higher order code, different call sites are far more
  likely to have distinct performance characteristics than in C, so the output
  of a gprof-style profiler is usually not accurate enough to be useful.

  <p>

  The new profiler records, for each of its measurements, not just the current
  predicate/function and its caller, but the entire chain of ancestors. This
  "deep context" is what gives the profiler its name. Actually, to keep
  overheads down, we don't walk the stack at every measurement; we just
  associate the current context with each measurement, and update the current
  context when it changes. Given this fact, it costs very little extra to
  record measurements on every aspect of performance (counts of calls, exits,
  fails and redos, counts of memory cells and memory words allocated, and time
  spent). We thus have only one deep profiling grade component, .profdeep,
  as opposed to the old profiler which has several grade components
  for different subsets of these measurements.

<li> The deep context recorded by the deep profiler records the identities of
  the call sites as well as the identities of predicates and functions
  in the list of ancestors. If a predicate p contains two calls to predicate q,
  this allows the deep profiler to report that one call to q costs next to
  nothing while the other one is a major performance problem.

<li> The deep profiler gathers so much data that giving it to the user all at once
  would swamp the user with too much information. We therefore implemented the
  deep profiler as a CGI program. Users can use thus use a web browser to
  explore the information contained in profiling data files.

<li> The deep profiler currently does not handle programs that catch exceptions.

<li> Further information about the deep profiler is available in the paper
  "Deep profiling: engineering a profiler for a declarative programming
  language" by Thomas C. Conway and Zoltan Somogyi, available
  <a href="http://www.cs.mu.oz.au/mercury/information/papers.html#mu_01_24">here</a>.

</ul>

<p>

Changes to the compiler back-ends:

<ul>

<li> The native code Linux/x86 back-end is now "release quality".

  <p>

  The native code back-end, which was first released in Mercury 0.10,
  compiles directly to assembler, rather than than going via C.
  This back-end is enabled using the `--target asm' option.  It is
  implemented by linking the Mercury compiler with the (relatively)
  language independent GNU Compiler Collection back-end.  In other words,
  it is a Mercury front-end for GCC.

  <p>

  This release is the first to be based on an officially released
  version of GCC (it is based on GCC 3.2).  In this release, the native
  code back-end now passes all of the applicable tests in the Mercury test
  suite, including bootstraping the Mercury compiler.  Currently it is only
  supported on i*86-pc-linux-gnu (Intel x86-based PCs running Linux).

  <p>

  For details, see <a href="http://www.cs.mu.oz.au/mercury/download/gcc-backend.html">this link</a>.

<li> .NET CLR back-end much improved.

  <p>

  The .NET CLR back-end, which generates MSIL code for Microsoft's new
  .NET Common Language Runtime, has been substantially improved.
  Mercury data structures are mapped to .NET CLR data types in a more
  natural and more efficient manner.  A lot more of the standard library
  is now supported.  Text files on Windows are now output with proper
  Windows CR-LF line endings.  Many bugs have been fixed.

  <p>

  This back-end supports the whole of the Mercury language, but the
  Mercury standard library implementation for the .NET CLR is still
  not yet complete.  The .NET CLR back-end now passes about half of
  the tests in the Mercury test suite.

  <p>

  This back-end is selected when you use the `--grade il' option.

  <p>

  See <a href="http://www.cs.mu.oz.au/mercury/dotnet.html">here</a> and/or
  <a href="http://www.cs.mu.oz.au/mercury/information/dotnet/mercury_and_dotnet.html">here</a>.

</ul>
