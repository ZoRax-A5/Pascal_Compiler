program whileStmt;

var 
s :real;
n :integer;
begin
    s:=0.0;
    n:=0;
    while s<=10 do
        begin
            n:=n+1;
            s:=s+1/n;
        end;
    writeln('n=',n);
end.
