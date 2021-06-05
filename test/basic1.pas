program basic1;
label steam zls;
const
    ci = 3;
    str = 'string';

var
    a, b: integer;
procedure count (m, n:integer);
begin
    if m > n then
        writeln('m is larger')
    else
        writeln('n is larger');
end;

function WF: Integer;
begin
    WF := '17';
end;

begin
    { this is a comment }
    a := 3;
    b := a + 3;
    c := a * 5;
    d := b / 2;

    steam: a := a + 1;

    if (a < b) then
       goto steam
    else
        count(a, b);
     
end.