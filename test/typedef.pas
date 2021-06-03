program typedef;
type
    byte = 0..255;
    signedbyte = -128..127;
    string = packed array [1..255] of char;
    x = Integer;
    y = x;
    a = Array [1..10] of Integer;
    
    c = File of a;
    TMonthType = (January, February, March, April,May, June, July, August, September, October, November, December);
    b = record
            x: Integer;
            y: Char
        end;
    TSpecialWord = record
        case Byte of
        0: (Word_value: Word);                      // 7
        1: (Byte_low, Byte_high: Byte);             // 7, 0
        2: (Bits: bitpacked array [0..15] of 0..1); // 1, 1, 1, 0, 0, ...
    end;