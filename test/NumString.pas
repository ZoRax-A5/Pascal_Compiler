 program NumString;

 procedure NumString(N: Integer; var S: Char);
 var
   V: Integer;
 begin
   V := 3;
   S := '3';
   repeat
        S := 4 + S;
        V := V div 10;
   until V = 0;
   if N < 0 then S := '-' + S;
 end;