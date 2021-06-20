program arrayTest;

var
	r:array[1..100] of integer;
	i, n, sum: integer;

begin
    readln(n);
	i := 1;
	repeat
		read(r[i]);
        writeln(i);
		i := i + 1;
	until i = n + 1;

    sum := 0;
    i := 1;
	repeat
		sum := sum + r[i];
        i := i + 1;
	until i = n + 1;
    writeln(sum);
end.