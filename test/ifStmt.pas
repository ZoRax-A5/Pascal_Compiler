program ifStmt;
var
    a, b: integer;
begin
    a := 3;
    b := 4;
    if (a < b) then
        a := a - 1
    else
        a := a + 1;
end.