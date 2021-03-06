Boolean expressions need to be 'correct' in order for the search
system to use them.
The expression you entered has errors in it.<p>
Examples of correct expressions are: <b>cat and dog</b>, <b>cat
not dog</b>, <b>cat or (dog not nose)</b>.<br>Note that
the operator <b>not</b> has the meaning of 'without'.
<blockquote><b>
$(SYNTAXERROR)
</b></blockquote>
<hr noshade size=4>
<form method="get" action="$(CGI)">
<font size=-1>
<input type=hidden name=config value=$(CONFIG)>
<input type=hidden name=restrict value="$(RESTRICT)">
<input type=hidden name=exclude value="$(EXCLUDE)">
Match: $(METHOD)
Format: $(FORMAT)
Sort: $(SORT)
<br>
Refine search:
<input type="text" size="30" name="words" value="$(WORDS)">
<input type="submit" value="Search">
</select>
</font>
</form>
<hr noshade size=4>
<a href="http://www.htdig.org/">
<img src="/doc/htdig/images/htdig.gif" border=0>ht://Dig $(VERSION)</a>
