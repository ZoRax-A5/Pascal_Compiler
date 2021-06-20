program easy;

const
    aa = 5;
    bb = 'c';
    cc = 3.2;
type
    x = Integer;
    y = x;
var
    a : Integer;
    b : x;
    c : real;
    d : real;
    n : Integer;
    is_small : boolean;
    char_mine : char;
procedure mine(x,y:Integer; c:real);
begin
    c := 3;
end;

function Compare(x,y:Integer):boolean;
begin
    if x < y then
        Compare := true
    else
        Compare := false;
end;

function Is_equal(x,y:Integer):boolean;
begin
    if x = y then
        Is_equal := true
    else
        Is_equal := false;
end;

begin
    { this is a comment }
    c := 3.2;
    a := 5;
    b := 6;
    d := 3.2;
    readln(n);
    if Compare(a,n) then
        writeln(a)
    else 
        writeln(n);
    
    char_mine := bb;
    d := d+aa;
    writeln(d);
    if Is_equal(aa,a) then
        writeln(bb)
    else
        writeln(cc);

    repeat
        b := b+1;
    until b = 19;

    while Compare(n,b) do
        n := n + 1;
    writeln(n);
    is_small := Compare(a,aa);
end.