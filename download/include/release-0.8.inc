<h2>New in release 0.8 of the Mercury distribution</h2>

<h3>Changes to the Mercury language:</h3>

<ul>
<li> The type system now includes support for Haskell-style type classes. <p>

  Type classes let you specify an interface and then provide multiple
  different implementations of that interface.  They're similar to
  abstract base classes in C++ or "interfaces" in Java.
  See the "Type classes" chapter of the Mercury Language Reference Manual
  for details. <p>

  Unlike Haskell 1.4, Mercury supports multi-parameter type classes,
  but we do not (yet) support constructor classes, and nor do we
  support default methods. <p>

<li> Mode inference can now infer "mostly-unique" modes as well as
  "unique" modes. <p>

<li> You can now declare both committed-choice ("cc") and backtracking (non-cc)
  modes for the same predicate. <p>
  
  Determinism analysis will pick the appropriate one to use for each
  call based on the context. <p>

<li> The module system now includes support for sub-modules. <p>

  The aim of this extension is twofold.  One aim is to provide more
  fine-grained encapsulation control: nested sub-modules within a
  single source file provide a convenient method for encapsulating
  units smaller than a source file.  The other aim is to provide better
  support for structuring large software packages that consist of many
  source files.  Sub-modules can be defined in separate files, with
  separate compilation, which means that you can also use this feature
  to combine a group of existing Mercury modules into a single logical
  package, with proper namespace control and encapsulation. <p>

  See the "Modules" chapter of the Mercury language reference manual
  for details. <p>

<li> We have made more improvements to the C interface. <p>

  The C interface now includes support for defining procedures
  that can have multiple solutions (i.e. those whose determinism
  is `nondet' or `multi') in C. <p>

  Also there's a new declaration, `pragma import', which is a bit
  like the existing `pragma c_code' declaration except that
  instead of giving a C code fragment, you just give the name
  of a C function.  `pragma import' is like the inverse of the
  existing `pragma export' declaration. <p>

<li> We have added support for automatic tabling (memoization). <p>

  See the "Tabled evaluation" subsection of the "Implementation-dependent
  pragmas" section of the "Pragmas" chapter of the Mercury language
  reference manual. <p>

<li> We have added (tentative) support for exception handling. <p>

  The interface to exception handling is actually via an `exception.m'
  library module rather than a new language construct.  
  For now, this module is located in the `extras/exceptions'
  directory, which is part of the `mercury-extras' distribution,
  but our intent is to eventually migrate this into the Mercury
  standard library if experience with its use proves positive. <p>

  The exception handling interface uses committed choice nondeterminism
  to avoid some semantic problems with previous exception handling
  proposals. <p>

  See the documentation in the interface of `exception.m' for details. <p>

</ul>

<h3>Changes to the Mercury standard library:</h3>

<ul>
<li> There is also a new builtin function promise_only_solution/1,
  for calling `cc_multi' or `cc_nondet' code from `det' or `semidet'
  procedures.  See the "builtin" chapter of the Mercury Library
  Reference Manual for details. <p>

<li> The getopt module now supports a new type of option data, namely
  `maybe_int(maybe(int))', to allow optional arguments with integer values.
  There is also a new corresponding lookup predicate,
  getopt__lookup_maybe_int_option/3.  <p>

  See the "getopt" chapter of the Mercury Library Reference Manual for
  details. <p>

<li> Support for memory profiling: new predicates report_full_memory_stats/0
  in benchmarking.m and io__report_full_memory_stats/2 in io.m. <p>

  See the "benchmarking" chapter of the Mercury Library Reference Manual
  for details. <p>

<li> Miscellaneous new predicates. <p>

  The Mercury standard library now includes the following new predicates: <p>

	  bag__det_remove_list/3 <br>
	  bag__least_upper_bound/3 <br>
	  bag__remove_list/3 <br>
	  det_univ_to_type/2 <br>
	  eqvclass__same_eqvclass_list/2 <br>
	  io__read_line_as_string/{3,4} <br>
	  list__take_upto/3 <br>
	  map__det_insert_from_assoc_list/3 <br>
	  map__det_intersect/5 <br>
	  map__det_union/5 <br>
	  map__intersect/4 <br>
	  map__sorted_keys/2 <br>
	  map__to_sorted_assoc_list/2 <br>
	  map__union/4 <br>
	  relation__add_values/4 <br>
	  relation__compose/3 <br>
	  relation__from_assoc_list/2 <br>
	  set__count/2 <br>
	  set_ordlist__count/2 <br>
	  store__new_cyclic_mutvar/4 <br>
	  varset__select/3 <p>

  In addition, there are four new system constants added to the float
  library module, float__radix, float__mantissa_digits, float__min_exponent
  and float__max_exponent.  There are also predicate equivalents for these. <p>

  Also the old relation__to_assoc_list/2 predicate has been renamed as
  relation__to_key_assoc_list/2; there is a new relation__to_assoc_list/2
  predicate with a different type for the second argument. <p>

  See the Mercury Library Reference Manual for details. <p>

<li> A few library procedures that have implicit side effects and are thus 
  intended for debugging use only have been declared `impure'.
  You will need to write `impure' before every call to these procedures
  and typically you will need to add a `pragma promise_pure' declaration
  for the callers. <p>

  The predicates affected are report_stats/0 and report_full_memory_stats/0
  in library/benchmarking.m; unsafe_dump/2, unsafe_dump_float/1, and
  unsafe_dump_tableaus/0 in extras/clpr/dump.m; and debug_freeze/3
  and debug_freeze/4 in extras/trailed_update/var.m. <p>

<li> The interface to the predicate term__compare/4 was found to be error-prone,
  and so we are phasing it out; it is declared with `pragma obsolete'
  in this version, so any use of it will now result in a warning, and
  the predicate will be removed entirely in some future version. <p>

</ul>

<h3>Changes to the Mercury implementation:</h3>

<ul>
<li> We've added a new source-to-source transformation - deforestation. <p>

  Deforestation transforms conjunctions to avoid the construction
  of intermediate data structures and to avoid multiple traversals
  over data structures. Deforestation is enabled at optimization level
  `-O3' or higher, or by using the `--deforestation' option. <p>

<li> The compiler can now perform type specialization. <p>

  Type specialization removes the overhead of polymorphic code, including
  code which uses type classes. The disadvantage is increased code size.
  Currently we do not perform inter-module type specialization.
  Type specialization is enabled by using the `--type-specialization' option.
  <p>

<li> We've added support for "transitive" inter-module analysis. <p>

  With the previous support for inter-module optimization, when
  analysing a module, the compiler could make use of information
  about the modules that it imports directly, but not about
  modules that are imported indirectly.  "Transitive" inter-module
  analysis gives the compiler information about indirectly
  imported modules. <p>

  However, currently this is only used for termination analysis;
  optimizations such as inlining still use only ordinary inter-module
  analysis, not transitive inter-module analysis. <p>

<li> Array bounds checking can now be disabled. <p>

  To disable array bounds checking, you must compile with
  `--intermodule-optimization' enabled and you must also
  define the C macro ML_OMIT_ARRAY_BOUNDS_CHECKS (e.g. by using
  `MGNUCFLAGS=-DML_OMIT_ARRAY_BOUNDS_CHECKS' in your Mmakefile). 
  <p>

<li> Domain checking for higher mathematical operations can now be disabled.
     <p>

  To disable domain  checking, you must compile with
  `--intermodule-optimization' enabled and you must also
  define the C macro ML_OMIT_MATH_DOMAIN_CHECKS (e.g. by using
  `MGNUCFLAGS=-DML_OMIT_MATH_DOMAIN_CHECKS' in your Mmakefile).  <p>

  See the Mercury Library Reference Manual for details. <p>

<li> We've added some primitive debugging support. <p>

  The runtime system now includes a "four-port" style debugger
  (actually with eight ports).
  To use this debugger, you need to build your program with debugging
  enabled, which is normally done using the `--debug' (or `-g') option,
  and then run it using the `mdb' command, e.g. `mdb a.out'.
  Type `h' at the `mdb>' prompt for a list of the available commands,
  or see the "Debugging" chapter of the Mercury User's Guide for further
  details. <p>

<li> The support for debugging using Prolog now includes support for
  detailed control over how terms are printed out during debugging. <p>

  See the "Using Prolog" section of the Mercury User's Guide for details.
  However, for most purposes we now recommend using the native Mercury
  debugger rather than debugging using Prolog. <p>

<li> The Mercury profiler has a number of new features. <p>

  The profiler now supports profiling just user time, or profiling
  real (elapsed) time, rather than profiling user + system time.
  We've also added support for memory profiling. <p>

  See the "Profiling" chapter of the Mercury User's Guide for details. <p>

<li> Profiling should now work on MS Windows. <p>

  To enable profiling on MS Windows, you need to have Sergey
  Okhapkin's latest version of gnu-win32 that includes his patch to add
  support for setitimer().  Sergey's "CoolView" version of cygwin.dll
  is available via <http://miracle.geol.msu.ru/sos/>; his patch will
  probably also be included in the next (b19) release of gnu-win32.
  Note that on Windows, you must use the Mercury runtime system's `-Tr'
  (profile real time) option; profiling just user time or user + system
  time is still not supported on Windows, because to the best of our
  knowledge Windows doesn't provide the necessary system calls. <p>

<li> Intermediate files can be placed in subdirectories. <p>

  If you use the `--use-subdirs' option to `mmake' or `mmc',
  then they will create the various intermediate files used
  by the Mercury implementation in a subdirectory called `Mercury'
  rather than in the current directory.  (For `mmake', if there
  is already a `Mercury' subdirectory, then this option is the default.)
  This keeps your source directories much less cluttered. <p>

<li> Mmake has a new variable GRADEFLAGS for specifying options that
  affect the grade (compilation model). <p>

  This means that for example to enable profiling, you can build with
  `GRADEFLAGS = --profiling' in your Mmakefile, rather than having to
  use the more obscure incantation `GRADE = asm_fast.gc.prof'. <p>

<li> Mmake now supports per-file settings of MCFLAGS and other *FLAGS
  variables. <p>

  For example, if you want to disable singleton variable warnings just
  for a single module `horrible_code.m', you can just include the line <p>

	  MCFLAGS-horrible_code = --no-warn-singleton-variables <p>

  in your Mmakefile. <p>

<li> Mmake now warns about variables which are defined but not used. <p>

  To disable this warning, use the `-w-' or `--no-warn-undef-variables'
  option. <p>

<li> The components of the argument to the `--grade' option and of the `GRADE'
  Mmake variable may now be given in any order. The compiler also has a
  new option `--output-grade-string' which prints the canonical grade string
  for the set of options with which the compiler was invoked. <p>

<li> Mmake now runs a bit faster, particularly on Windows. <p>

<li> We've made a few small improvements to the efficiency of the generated
     code. <p>

<li> The system has been ported to Linux/PPC. <p>

<li> The system has been ported to work with version b19 of cygwin32
  (this port has not been tested well, though). 
  See README.MS-Windows for details. <p>

<li> We've updated to version 4.13alpha2 of the Boehm garbage collector. <p>

<li> We've made the MERCURY_OPTIONS environment variable somewhat easier to
     use. <p>

<li> Mtags is now able to produce tags for typeclass declarations.  It is
  also able to produce tags files in the extended format supported by
  recent versions of Vim and Elvis.  Do `mtags --help' for more
  information. <p>

<li> Numerous bug fixes. <p>

</ul>
