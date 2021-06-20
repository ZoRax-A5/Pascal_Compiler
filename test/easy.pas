program easy;
type
    x = Integer;
    y = x;
var
    a : Integer;
    b : real;
    c : char;
    d : boolean;
    e : real;
    f : x;
procedure mine(x,y:Integer; c:real);
begin
    c := 3;
end;
begin
    { this is a comment }
    f := 3;
    a := -3;
    b := 3.2;
    a := b;
    c := 'c';
    d := true;
    e := a+b;
    e := 3+b;
    e := 3+3.2;
    e := a+b+3;
    e := a*b;
    if a < b then
       a := 1
    else
       b := 2.3;

    repeat
        a := a + 1;
        b := a * b;
    until a = 19;

    while a < 30 do
        a := a + 1;
end.