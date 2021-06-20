program Ex;
	var x : integer; y : boolean;
begin
   	 x:=0;
	repeat
		y:=true; x:= x+7;
		if x < 50 then y:= false;
   		if x >=50 then y:= true;
	until y;
    	writeln('ALL=',x);
end.
