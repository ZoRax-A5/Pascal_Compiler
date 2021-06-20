program func;
var
   a,b,c,min:Integer;


procedure findMin(x, y, z: integer;var m:integer); 
begin
   if x < y then
      m := x
   else
      m := y;
   if z <m then
      m := z;
   writeln(m);
end;

function max(num1, num2: integer): integer;
var
   result: integer;

begin
   if (num1 > num2) then
      result := num1
   
   else
      result := num2;
   max := result;
end;

begin
   a := 1;
   b := 2;
   c := 3;
   min := 4;
   findMin(a, b, c, min);
   writeln(min);
end.