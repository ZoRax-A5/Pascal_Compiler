program ifStmt;

label steam;
const
    a = 3;
    str = 'string';
var
    a, b: integer;



function WF: Integer;
begin
WF := '17';
end;

begin
    a := 3;
    b := 4;
    if (a < b) then
        a := a - 1
    else
        a := a + 1;
end.