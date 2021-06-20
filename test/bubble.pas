program test_bubble;
var
	r:array[1..100] of integer;
	i, j, n, temp: integer;
	flag: boolean;
	
begin
	readln(n);
	i := 1;
	repeat
		read(r[i]);
		i := i + 1;
	until i = n + 1;
	
	i := 1;
	
	repeat
		flag := true;
		j := n - 1;
		repeat
			if r[j+1]<r[j] then
	        begin
				writeln(i, j);
				temp := r[j+1];
				r[j+1] := r[j];
				r[j] := temp;
				flag := false;
	        end;
			j := j - 1;
		until j = i - 1;

		if flag then break;
		i := i + 1;
	until i = n;

	i := 1;
	repeat
		if i < n then write(r[i], ' ') else writeln(r[i]);
		i := i + 1;
	until i = n + 1;

end.