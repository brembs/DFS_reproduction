unit HCopyVGA;    { verschiedene HardCopies Åber NEC P6 }    { VGA }
                        { (c) R.W. 19. Juni 1991 }
interface

const VerySmall   = 1;
      small       = 2;
      mediumSize  = 3;
      large       = 4;
      VeryLarge   = 5;
      HighDensity = 1;
      LowDensity  = 2;

var   PrinterOut  : boolean;

 procedure Hardcopy(size,density : integer);
 procedure Hcopy8;
 procedure Hcopy24;

implementation
uses crt,printer,graph;

var i,j,k,mode,leftMargin,
    DotColumns,Xstep,Ystep,
    Yact                : integer;
    Cbyte               : byte;
    Pbyte               : array[1..3] of byte;
    ESC,c               : char;
    break               : boolean;
const Bits              : array[0..7] of byte=(128,64,32,16,8,4,2,1);
(*-------------------------------------*)
procedure interrupt;
begin
 c := readKey;
 if c=ESC then break := true;
end;
(*-------------------------------------*)
procedure PrintError;
begin
 PrinterOut := true;
 break := true;
end;
(*-------------------------------------*)
Procedure Hcopy8;
var u,v : integer;
begin
{$I-}  write(lst,ESC,'3',#24); {$I+}   { Vorgabe des Zeilenvorschubs }
 if IOresult <> 0 then PrintError;
 if break then EXIT;
  Yact:=0;
  repeat
    write(lst,ESC,'*',chr(mode),chr(lo(DotColumns)),chr(hi(DotColumns)));
    if LeftMargin>0 then for k:=1 to LeftMargin do write(lst,chr(0));
    j:=0;
    repeat
        Cbyte:=0;
        k := 0;
        for i := 0 to 7 do begin
         for u:=1 to Xstep do begin
          for v:=1 to Ystep do begin
           if GetPixel(j+u-1,Yact+k+v-1)<>0 then Cbyte:=Cbyte or Bits[i];
          end;  {v}
         end;   {u}
         k := k + Ystep;
        end;
        write(lst,chr(Cbyte));
        j := j + Xstep;
    until j>=640;
    if KeyPressed then interrupt;
    if break then EXIT;
    Yact := Yact+8*Ystep;
    write(lst,chr(13),chr(10));
  until (Yact>480);
end;
{*----------------------------------------------------------*}
Procedure Hcopy24;
var   n,m,p  : integer;

begin
{$I-}  write(lst,ESC,'3',#24); {$I+}   { Vorgabe des Zeilenvorschubs }
 if IOresult <> 0 then PrintError;
 if break then EXIT;
  Yact:=0;
  repeat
    write(lst,ESC,'*',chr(mode),chr(lo(DotColumns)),chr(hi(DotColumns)));
    if LeftMargin>0 then for k:=1 to LeftMargin do write(lst,chr(0));
    j := 0;
    m := 0;
    p := 0;
    repeat
        k := 0;
        n := 0;
        repeat
         Cbyte:=0;
         for i := 0 to 7 do begin
          if GetPixel(j,Yact+k)<>0 then Cbyte:=Cbyte or Bits[i];
          n := n+1;
          if (n mod Ystep)=0 then k := k + 1;
         end;
         inc(p); if (p=4) then p := 1;
         Pbyte[p] := Cbyte;
        until n=24;
    {    for i:=3 DownTo 1 do write(lst,chr(Pbyte[i]));  }
        for i:=1 to 3 do write(lst,chr(Pbyte[i]));
        m := m+1;
        if (m mod Xstep)=0 then j := j + 1;
    until j>=640;
    if KeyPressed then interrupt;
    if break then EXIT;
    Yact := Yact+trunc(24/Ystep);
    write(lst,chr(13),chr(10));
  until (Yact>480);
end;
{*----------------------------------------------------------*}
procedure HardCopy(size,density : integer);
begin
 ESC := chr(27);
 break := false;
 PrinterOut := false;
 if (size in [1..4]) or (density in [1,2]) then begin
  if density=LowDensity then begin
   case size of
   small     : begin
                mode       := 3;
                LeftMargin := 450;
                DotColumns := 1090;
                Xstep      := 1;
                Ystep      := 2;
               end;
   mediumSize :begin
                mode       := 4;
                LeftMargin := 100;
                DotColumns := 380;
                Xstep      := 2;
                Ystep      := 2;
               end;
   large     : begin
                mode       := 1;
                LeftMargin := 150;
                DotColumns := 790;
                Xstep      := 1;
                Ystep      := 1;
               end;
   VeryLarge : begin
                mode       := 6;
                LeftMargin := 0;
                DotColumns := 560;
                Xstep      := 1;
                Ystep      := 1;
               end;
   end;   { case }
   Hcopy8;
  end;    { density }

  if density=HighDensity then begin
   case size of
   VerySmall : begin
                mode       := 40;
                LeftMargin := 900;
                DotColumns := 940;
                Xstep      := 1;
                Ystep      := 1;
               end;
   small     : begin
                mode       := 40;
                LeftMargin := 900;
                DotColumns := 1580;
                Xstep      := 2;
                Ystep      := 1;
               end;
   mediumSize :begin
                mode       := 39;
                LeftMargin := 450;
                DotColumns := 790;
                Xstep      := 1;
                Ystep      := 2;
               end;
   large     : begin
                mode       := 40;
                LeftMargin := 1350;
{                DotColumns := 2530;  }
                DotColumns := 2370;
                Xstep      := 3;
                Ystep      :=2;
               end;
   VeryLarge : begin
                mode       := 39;
                LeftMargin := 0;
                DotColumns := 1360;
                Xstep      := 2;
                Ystep      := 3;
               end;
   end;   { case }
   Hcopy24;
  end;    { density }
end;     { size or density }
end;
{*----------------------------------------------------------*}
end.
