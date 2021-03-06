<h2>New in release 0.9.1 of the Mercury distribution</h2>

This release is primarily a bug-fix release.  
It fixes some bugs with the binary distribution of 0.9,
stops the compiler accepting some incorrect inst declarations,
fixes a bug in exception handling and a problem with the source
distribution where `configure' did the wrong thing on some architectures
if you ran it twice.
<p>

In addition, Morphine has been added to the extras distribution.
Morphine is a trace analysis system, which allows Mercury programs to be
debugged and dynamically analyzed using a Prolog interface.  You need
the ECLiPSe Prolog system to use Morphine.  See the README file in the
Morpine directory for more details.


<h2>New in release 0.9 of the Mercury distribution</h2>

<h3>HIGHLIGHTS</h3>

Changes to the Mercury language:
<ul>
<li> The Mercury type system now supports existentially quantified types.
<li> We now allow abstract instance declarations.
<li> We now support a simple form of user-defined infix operators.
</ul>

Changes to the Mercury standard library:
<ul>
<li> Exception handling support is now part of the standard library.
<li> There are two new standard library modules `time' and `gc'.
<li> We've added function versions of many of the predicates in the
     Mercury standard library.
</ul>

New library packages in the Mercury extras distribution:
<ul>
<li> We've added support for optional lazy evaluation.
<li> The extras distribution now includes support for dynamic linking.
<li> We've added some bindings to POSIX.3 functionality.
</ul>

Changes to the Mercury implementation:
<ul>
<li> The Mercury debugger (mdb) is much improved.
     It now includes support for interactive queries, command-line editing
     and command-line history, display of source line numbers, and
     setting breakpoints on source line numbers.
     The GNU Emacs interface provides a source-linked debugger.
<li> We've removed the support for using a Prolog debugger on Mercury programs.
<li> Mmake, the Mercury make tool, now includes better support for
     installing libraries.
<li> We've added support for user-guided type specialization.
<li> Numerous bug fixes.
</ul>

<h3>DETAILED LISTING</h3>

<h4>Changes to the Mercury language:</h4>

<ul>
<li> The Mercury type system now supports existentially quantified types. <p>

  Existential types let you create heterogenous collections (e.g. lists
  containing objects of different types).  In combination with type
  classes, they allow you to write code in an OOP-like style.
  See the "Existential types" chapter of the Mercury Language Reference
  Manual for details. <p>

  Our current implementation still has a couple of important limitations;
  see the "Known bugs and limitations" section of the "Existential types"
  chapter of the Mercury Language Reference Manual. <p>

<li> We now allow abstract instance declarations. <p>

  You can declare in the interface of a module that a type is an
  instance of a particular type class, and provide the definition
  of that instance in the implementation section of that module. <p>

<li> We now support a simple form of user-defined infix operators. <p>
  
  Terms in the form of x `fun` y are transformed into fun(x, y).  `fun`
  is parsed as an infix operator with the highest possible precedence
  and left associativity. <p>

<li> We've made a small change to the rule for quantification of lambda
  expressions.   <p>

  The new rule is that all variables in the arguments of lambda
  expressions are treated as locally quantified to that lambda expression.
  For function lambda expressions, variables in the result term
  use the normal quantification rules.  See the "Data-terms" section
  of the "Syntax" chapter of the Mercury Language Reference Manual
  for details. <p>
  
  Previously, the exact quantification rule for lambda expressions was
  not documented, but the compiler would locally quantify variables in
  function return values, and it would only locally quantify variables
  occuring at the top level of an argument term, not those occurring in
  subterms.  Both of these were rather surprising for functional
  programmers. <p>

  It is possible that this change may break some existing code using
  predicate lambda expressions with compound terms as arguments, but we
  expect this to be extremely rare.  If it does occur, the compiler
  will issue a warning about variables having overlapping scopes, and
  the work-around is simple: use a fresh variable for the lambda
  predicate argument and unify it with the compound term in the body of
  the lambda expression. <p>

<li> The old-style syntax for predicate lambda expressions,
  `lambda([<var>Args</var>] is <var>Det</var>, <var>Goal</var>)',
  is now officially deprecated. <p>

  Please use the new syntax-style
  `(pred(<var>Args</var>) is <var>Det</var> :- <var>Goal</var>)'
  instead.  The compiler still supports the old-style syntax, but
  we plan to eventually drop this support in some future release. <p>

</ul>

<h4>Changes to the Mercury standard library:</h4>

<ul>
<li> Exception handling support is now part of the standard library. <p>

  The module `exception', which was previously part of the "extras"
  distribution, has been moved into the standard library.
  The predicate error/1 now throws an exception rather than just
  terminating execution. <p>

  However, many of the operations in the standard library still handle
  errors by aborting execution rather than by throwing exceptions. <p>

<li> There's a new standard library module `time'. <p>

  The `time' module provides an interface to the ANSI/ISO C <time.h>
  functions, and to the POSIX times() function.  Thanks to Tomas By
  for contributing the original version of this module. <p>

<li> There's a new standard library module `gc', for controlling the
  garbage collector. <p>

  Currently it contains only one predicate, `garbage_collect',
  which forces a garbage collection.  We may add more later. <p>

<li> We've added some new predicates to the Mercury standard library:
	array__map/3,
	bag__count_value/3,
	std_util__do_while/4.
 <p>
<li> We've added function versions of many of the predicates in the
  Mercury standard library. <p>

  One small drawback of this change is that it is not completely
  backwards compatible; in certain circumstances, there is a potential
  ambiguity between a function call and a partially applied predicate,
  and for some occurrences of this the compiler may not be able to
  resolve the ambiguity unless the user provides additional type
  declarations (or the like).  But such cases should be quite rare,
  and when they do occur the fix is easy, so we thought the clear
  advantages of using a functional syntax were well worth this minor
  glitch in backwards compatibility. <p>

<li> The following predicates have been replaced by functions with
  the same names, and will be removed in a future release. <p>

  The predicate versions were intended for use in programs which needed
  to work in both Prolog and Mercury, but executing Mercury programs using
  Prolog is no longer supported. <p>

	float__ceiling_to_int/2,
	float__floor_to_int/2,
	float__round_to_int/2,
	float__truncate_to_int/2,
	float__abs/2,
	float__max/3,
	float__min/3,
	float__pow/3,
	float__hash/2,
	float__max/1,
	float__min/1,
	float__epsilon/1,
	float__radix/1,
	float__mantissa_digits/1,
	float__min_exponent/1,
	float__max_exponent/1.
 <p>
<li> The implementations of `int:&gt;&gt;/2' and `int:&lt;&lt;/2' have been changed to
  define the results for negative shift counts and shift counts greater than
  the word size. <p>

  For efficiency, we also provide the functions `int:unchecked_left_shift/2'
  and `int:unchecked_right_shift/2' that, like the previous implementations
  of `int:&gt;&gt;/2' and `int:&lt;&lt;/2', do not check for these cases. <p>

<li> `int:^/2' and `integer:^/2' have been replaced by `int__xor/2' and
  `integer__xor/2', and will be removed in a future release.
  The operator `^' will be used by record syntax. <p>

</ul>

<h4>New library packages in the Mercury extras distribution:</h4>

<ul>
<li> We've added support for optional lazy evaluation. <p>

  The extras distribution now includes a new module `lazy',
  which provides support for optional lazy evaluation
  via a type `lazy(T)', with `delay' and `force' operations.
  There's also a `lazy_list' module which uses the `lazy' module.
  See the files in extras/lazy_evaluation for details. <p>

<li> The extras distribution now includes support for dynamic linking. <p>

  The interface is based on the C functions dlopen(), dlsym(), and co.,
  which are supported by most modern Unix systems.
  See the files in extras/dynamic_linking for details. <p>

<li> We've added some bindings to POSIX.3 functionality. <p>

  At this stage it's quite incomplete.
  See the files in extras/posix for details. <p>

</ul>

<h4>Changes to the Mercury implementation:</h4>

<ul>
<li> Mmake, the Mercury make tool, now includes better support for
  installing libraries. <p>

  It's now much easier to build and install libraries in several
  different grades (e.g. for debugging, time profiling, and memory
  profiling) or for more than one architecture. <p>

  See the "Supporting multiple grades and architectures" section
  of the "Libraries" chapter of the Mercury User's Guide. <p>

<li> We've fixed a bug in switch detection. <p>

  This change may break some code written for Mercury 0.8. Some
  disjunctions which Mercury 0.8 found to have determinism `det'
  now have determinism `nondet'. <p>

  Mercury 0.8 (but not Mercury 0.7) allowed switches where a unification
  to test the switched-on variable against a function symbol occurred after
  the first call in the disjunct. Doing this may remove infinite loops,
  violating the strict sequential semantics (see the "Semantics" chapter
  of the Mercury Language Reference Manual). <p>

  To fix switches for which determinism errors are now reported, simply
  reorder the goals in each disjunct so that only unifications occur
  before the test of the switched-on variable. <p>

<li> The Mercury debugger (mdb) now includes support for interactive queries.
     <p>

  See the "Interactive query commands" subsection of the "Debugger commands"
  section of the "Debugging" chapter of the Mercury User's Guide for details.
  <p>

<li> The Mercury debugger (mdb) now optionally supports command-line editing
  and command-line history. <p>

  This support uses the GNU Readline library.  For the source distribution,
  the Mercury configure script will detect whether readline has been
  installed and will only enable the command-line editing and history
  support if readline has been installed.  For the binary distribution,
  if the binary distribution was built with readline, then you will
  need to install GNU readline in order to use the debugger. <p>

  For information on where to obtain GNU Readline, see the INSTALL file. <p>

<li> The Mercury debugger (mdb) now displays source line numbers and allows
  setting breakpoints on source line numbers. <p>

  The GNU Emacs interface takes advantage of this to provide a
  source-linked debugger. <p>

<li> We've removed the support for using a Prolog debugger on Mercury programs.
     <p>

  Now that we have a working Mercury debugger, there's no longer any need to
  use a Prolog debugger for debugging Mercury code. <p>

  Normally we would warn at least one or two releases in advance, if
  any feature is to be removed.  However, in this case

	<ul>
  	<li> it was an implementation feature rather than a language feature;
	<li> the cost of maintaining the feature was quite high;
	<li> the feature was already broken is various ways [one being that it
	  doesn't work with recent versions of SICStus Prolog, due to
	  those versions removing support for a SICStus Prolog feature
	  (save/1), apparently without any advance notice]; and
	<li> a simple work-around is available if anything breaks as a result
	  of the feature being removed. 
	</ul>

  In the unlikely event that anyone happened to have any makefiles or
  scripts that depended on the support for using Prolog, they can
  install the latest Mercury distribution and still continue to use the
  Prolog support from Mercury 0.8, just by including the `bin'
  directories for both versions in their PATH, with the more recent one
  first, of course. <p>

<li> We've added support for user-guided type specialization. <p>

  See the "Type specialization" section of the "Pragmas" chapter of the
  Mercury Language Reference Manual for details.

<li> Numerous bug fixes. <p>

</ul>
