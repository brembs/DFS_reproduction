{----------------------------------------------------------------}
{----------------------------------------------------------------}
{---------           ******************              ------------}
{---------           *  V2.0 14.9.95  *              ------------}
{---------           ******  R.W. *****              ------------}
{----------------------------------------------------------------}
{-------------------Stand: 14.09.95---MD-------------------------}
unit messrout;
interface
type bf = (rev,rec_rev,forw,rec_forw,fast_rev,fast_forw,stop);
     strtype = string[5];


function binwert(relaisnummer:byte):byte;
procedure ResetML;                    { R E S E T ml}
procedure SetRelais(relaisnummer:byte;status:boolean);
function ArenaPos(ar:byte) :integer;
function ArenaPos45(ar:byte) :integer;
function IntegratorOutput(ar:byte) : integer;
function YawTorque:integer;
function Drehmoment: real;
procedure SetTorqueOffset(offs:integer);
procedure SetArenaSpeed(ar:byte;speed:integer);
procedure SetArenaPos(ar: byte; pos: integer);
procedure SetArenaPos45(ar: byte; pos: integer);
procedure Arenaspeed_On (ar: byte);
procedure Arenaspeed_Off (ar: byte);
{  procedure Arenapos_On (ar: byte);
procedure Arenapos_Off (ar:byte); }
procedure ClosedLoop_on(ar:byte);
procedure ClosedLoop_off(ar:byte);
procedure inversecoupling(ar:byte);
procedure normalcoupling(ar:byte);
procedure lampe_an;
procedure lampe_aus;
procedure Openshutter;
procedure CloseShutter;
procedure BlowFly;
procedure ArenaColor0;
procedure ArenaColor1;
procedure SetIntegratorZero(ar:byte);
procedure ArCol (col:byte);
implementation
uses crt,mlablib;

var err1,zustand,tape_ctrl,t_c,rel1,rel2   : byte;
    res                                    : char;
    relais_set                             : array[0..15] of boolean;
    ClosedLoop                             : array[1..2] of boolean;
    dPsi,position                          : integer;

const ok : byte = 0;

{-----------------------------------------------------------}
function binwert(relaisnummer:byte):byte;
begin
    case relaisnummer of
    0: binwert:=1;
    1: binwert:=2;
    2: binwert:=4;
    3: binwert:=8;
    4: binwert:=16;
    5: binwert:=32;
    6: binwert:=64;
    7: binwert:=128;
    else begin
           writeln('falsches bitnummer  in function binwert : Programmabruch !!!');
          delay (4000);
           Halt;
         end;
    end;
  end;
{-----------------------------------------------------------}
procedure ResetML;
var err1,zustand,i:byte;
    vau:integer;
begin
  mladr:=$380;
  mlresunblock(err1);
  while err1<>0 do begin
    mlsync(zustand);
    write(zustand);
    mlreset( err1);
    writeln(err1);
  end;
  for i:=0 to 15 do relais_set[i]:=false;
  rel1 := 0;
  rel2 := 0;
  mldigout1(err1,rel1);
  mldigout2(err1,rel2);
 (******
   for i:=0 to 7 do begin
    rel1:=rel1 xor binwert(i);
    mldigout1(err1,rel1);
   end;
   for i:=8 to 15 do begin
    rel2:=rel2 xor binwert(i-8);
    mldigout2(err1,rel2);
   end;
  ******)
  vau:=2047;
  vau:=vau shl 4;
  mlda12out(err1,1,vau);
  mlda12out(err1,2,vau);
end;
{---------------------------------------------------------------}
procedure SetRelais(relaisnummer:byte;status:boolean);
var wert:byte;

begin
  case relaisnummer of
    0..7: begin
            case status of
              false: if relais_set[relaisnummer] then begin
                      rel1:=rel1 xor binwert(relaisnummer);
                      relais_set[relaisnummer]:=false;
                     end;
              true : begin
                      rel1:=rel1 or binwert(relaisnummer);
                      relais_set[relaisnummer]:=true;
                     end;
            end;   {case}
            mldigout1(err1,rel1);
          end;
    8..15:begin
            case status of
              false: if relais_set[relaisnummer] then begin
                      rel2:=rel2 xor binwert(relaisnummer-8);
                      relais_set[relaisnummer]:=false;
                     end;
              true : begin
                      rel2:=rel2 or binwert(relaisnummer-8);
                      relais_set[relaisnummer]:=true;
                     end;
            end;  {case}
            mldigout2(err1,rel2);
          end;
   else begin
        writeln('falsches Relais wurde angesteuert : Programmabruch !!!');
        delay (4000);
        Halt;
        end;
  end;
end;
{---------------------------------------------------------------}
function ArenaPos(ar:byte) :integer;
var pa: integer;
begin                             { A R E N A P O S }
  case ar of
    1:  mlad12in(err,pa,3);
    2:  mlad12in(err,pa,4);
    else begin
      clrScr;
      writeln(' Falsche Arenanummer : ',ar, ' !');
      Halt;
    end;
  end;
  ArenaPos:=2047-(pa shr 4);
end;
{---------------------------------------------------------------}
function ArenaPos45(ar:byte) :integer;
var pa: integer;
begin                             { A R E N A P O S }
  case ar of
    1:  mlad12in(err,pa,3);
    2:  mlad12in(err,pa,4);
    else begin
      clrScr;
      writeln(' Falsche Arenanummer : ',ar, ' !');
      Halt;
    end;
  end;
  position :=(2047-(pa shr 4))-512;
  if position <-2048 then inc(position,4096);
  ArenaPos45 := position;
end;
{-------------------------------------------------------------}
function IntegratorOutput(ar:byte) : integer;
var sp: integer;
begin
  case ar of                      
    1:  mlad12in(err,sp,0);
    2:  mlad12in(err,sp,1);
    else begin
      clrScr;
      writeln(' Falsche Arenanummer : ',ar, ' !');
      Halt;
    end;
  end;
  if err<>ok then mlError(err);
  IntegratorOutput := sp shr 4;
end;
{-------------------------------------------------------------}
function YawTorque:integer;
var T_ad:integer;
begin                            { T  (rohdaten torque)  }
  mlad12in(err,T_ad,2);
  YawTorque:=(T_ad shr 4)-2060;
end;
{-------------------------------------------------------------}
function Drehmoment: real;
var d:integer;
begin                            { D R E H M O M E N T }
  Drehmoment:=80.0*YawTorque/2060;            {in mDyncm}
end;
{--------------------------------------------}
procedure SetTorqueOffset(offs:integer);
begin
   offs := offs shl 4;
   mlda12out (err,1,offs);
end;
{--------------------------------------------}
procedure SetArenaSpeed(ar:byte;speed:integer);
begin
   speed:=speed shl 4;
   case ar of
      1: mlda12out (err,2,speed);
  {    2: mlda12out (err,#,speed);  ...needs multiplexer }
       else begin                                  { A R E N A S P E E D }
       clrScr;                                           {O U T}
       writeln('falsche Arenanummer:',ar,'!');
       Halt;
       end;
   end;
 end;
{-------------------------------------------------------------}
procedure SetArenaPos(ar: byte; pos: integer);
var
   OldLoop: array[1..2] of boolean;
begin
 if (ar=2) then begin
  ClrScr;                                  
  GotoXY(15,10);
  writeln('procedure SetArenaPos not yet implemented!');
  repeat until KeyPressed;
  EXIT;
 end;

  OldLoop[ar] := false;
  if ClosedLoop[ar] then begin
    OldLoop[ar] := true;
    ClosedLoop_off(ar);
  end;
  ArenaSpeed_on(ar);
  repeat
   dPsi := (ArenaPos(ar)-pos);
   if dPsi>1000 then dPsi := 1000;
   if dPsi<-1000 then dPsi := -1000;
   SetArenaSpeed(ar,2047 + dPsi);
  until dPsi=5;
  SetArenaSpeed(ar,2047);
  ArenaSpeed_off(ar);
  if OldLoop[ar] then begin
     ClosedLoop_on(ar);
  end;
end;
{-------------------------------------------------------------}
procedure SetArenaPos45(ar: byte; pos: integer);
var
   OldLoop: array[1..2] of boolean;
begin
 pos := pos + 512;
 if pos>2047 then pos:=pos-4096;
 if (ar=2) then begin
  ClrScr;                                  
  GotoXY(15,10);
  writeln('procedure SetArenaPos not yet implemented!');
  repeat until KeyPressed;
  EXIT;
 end;

  OldLoop[ar] := false;
  if ClosedLoop[ar] then begin
    OldLoop[ar] := true;
    ClosedLoop_off(ar);
  end;
  ArenaSpeed_on(ar);
  repeat
   dPsi := (ArenaPos(ar)-pos);
   if (abs(dPsi)>2000) then dPsi:=-dPsi; {...falls es ber die echte Nullstelle geht!}
   if dPsi>300 then dPsi := 1000;
   if dPsi<-300 then dPsi := -1000;
   SetArenaSpeed(ar,2047 + 2*dPsi);
  until dPsi=0;
  SetArenaSpeed(ar,2047);
  ArenaSpeed_off(ar);
  if OldLoop[ar] then begin
     ClosedLoop_on(ar);
  end;
end;
{-----------------------------------------------------}
procedure Arenaspeed_On (ar: byte);
var i:integer;
begin
    case ar of
    1   : begin
                setrelais(2,true);       { internal bias-switch }
                SetRelais(3,true);      { internal bias-switch }
                SetRelais(5,true);      { output to motor control unit }
          end;
    2   : begin
                setrelais(6,true);
                SetRelais(7,true);
                SetRelais(9,true);
          end;
   12,21: begin
                setrelais(2,true);
                SetRelais(3,true);
                SetRelais(5,true);
                setrelais(6,true);
                SetRelais(7,true);
                SetRelais(9,true);
           end;
   else begin
           ClrScr;
           writeln('falsche Arenanummer:',ar,'!');
           halt;
        end;
   end;
end;
{------------------------------------------------------}
procedure Arenaspeed_Off (ar: byte);
var i:integer;
begin
    case ar of
       1: begin
                setrelais(2,false);
                SetRelais(3,false);
                if not Relais_set[4] then SetRelais(5,false);
          end;
       2: begin
                setrelais(6,false);
                SetRelais(7,false);
                if not Relais_set[8] then SetRelais(9,false);
          end;
   12,21: begin
                setrelais(2,false);
                SetRelais(3,false);
                if not Relais_set[4] then SetRelais(5,false);
                setrelais(6,false);
                SetRelais(7,false);
                if not Relais_set[8] then SetRelais(9,false);
          end;
   else begin
           ClrScr;
           writeln('falsche Arenanummer:',ar,'!');
           halt;
        end;
   end;
end;
{------------------------------------------------------}
(*************
procedure Arenapos_On (ar: byte);
begin

    case ar of
       1:      SetRelais(4,false);
       2:      SetRelais(5,false);
   12,21: begin
               SetRelais(4,false);
               SetRelais(5,false);
          end;
      else begin
        ClrScr;
        writeln('falsche Arenanummer:',ar,'!');
        halt;
        end;
     end;
end;
{------------------------------------------------------}
procedure Arenapos_Off (ar:byte);
begin

    case ar of
       1:    SetRelais(4,true);
       2:    SetRelais(5,true);
   21,12: begin
             SetRelais(4,true);
             SetRelais(5,true);
           end;

      else begin
        ClrScr;
        writeln('falsche Arenanummer:',ar,'!');
        halt;
        end;
     end;
end;
**************)
{-----------------------------------------------------}
procedure ClosedLoop_on(ar:byte);
var i:integer;
begin

    case ar of
    1   : begin
               SetRelais(4,true);
               SetRelais(5,true);
               ClosedLoop[1] := true;
          end;
    2   : begin
               SetRelais( 8,true);
               SetRelais(9,true);
               ClosedLoop[2] := true;
          end;

   21,12: begin
               SetRelais(4,true);
               SetRelais(5,true);
               SetRelais(8,true);
               SetRelais(9,true);
               ClosedLoop[1] := true;
               ClosedLoop[2] := true;
          end;

      else begin
        ClrScr;
        writeln('falsche Arenanummer:',ar,'!');
        halt;
        end;
     end;
end;
{-----------------------------------------------------}
procedure ClosedLoop_off(ar:byte);
var i:integer;
begin

 case ar of
    1   : begin
               SetRelais(4,false);
               ClosedLoop[1] := false;
               if not Relais_set[3] then SetRelais(5,false);
          end;
    2   : begin
               SetRelais(8,false);
                ClosedLoop[2] := false;
                if not Relais_set[7] then SetRelais(9,false);
          end;

   21,12: begin
               SetRelais(4,false);
               SetRelais(8,false);
               ClosedLoop[1] := false;
               ClosedLoop[2] := false;
               if not Relais_set[3] then SetRelais(5,false);
               if not Relais_set[7] then SetRelais(9,false);
          end;

      else begin
        ClrScr;
        writeln('falsche Arenanummer:',ar,'!');
        halt;
        end;
     end;
end;
{----------------------------------------------}
procedure InverseCoupling(ar:byte);
var i:integer;
begin
{
   case ar of
   1  : setrelais(4,true);
   2  : setrelais(5,true);
   12,21: begin
            setrelais(4,true);
            setrelais(5,true);
          end;
  end;}
end;
{------------------------------------------------}
procedure normalcoupling(ar:byte);
var i:integer;
begin
{
   case ar of
   1  : setrelais(4,false);
   2  : setrelais(5,false);
   12,21: begin
            setrelais(4,false);
            setrelais(5,false);
          end;
  end;}
end;
{-----------------------------------------------}
procedure lampe_an;
begin
       setrelais(0,true);
end;
{------------------------------------------------}
procedure lampe_aus;
begin
       setrelais(0,false);
end;
{------------------------------------------------}
procedure Openshutter;
begin
       setrelais(1,true);
end;
{-------------------------------------------------}
procedure Closeshutter;
begin
       setrelais(1,false);
end;
{-------------------------------------------------}
procedure BlowFly;
begin
       setrelais(10,true);
       delay(300);
       setrelais(10,false);
end;
{-------------------------------------------------}
procedure ArenaColor0;
begin
setrelais(11,false);
end;
{-------------------------------------------------}
procedure ArenaColor1;
begin
setrelais(11,true);
end;
{-------------------------------------------------}
procedure ArCol (col:byte);
begin
  if (col=1) then Arenacolor0 else Arenacolor1;
end;
{-------------------------------------------------}
procedure SetIntegratorZero(ar:byte);
var ch  : char;
    i   : word;
    sum : real;
begin
 ClrScr;
 if not ar in [1.. 2] then begin
   writeln('falsche Arenanummer:',ar,'!');
   halt;
 end;
 GotoXY(5,4);writeln('Connect "Tacho"-Input to ground !');
 GotoXY(5,5);writeln('Adjust "ZERO INTEGR" with screwdriver, until');
 GotoXY(5,6);writeln('number on screen (below) keeps constant !');
  SetRelais(4*ar,false);     { internal torque-switch connected to ground}
  SetRelais(4*ar-1,false);   { internal bias-switch connected to ground }
  SetRelais(4*ar+1,true);    { integrator free }
 repeat
   sum := 0;
   for i:=1 to 500 do sum := sum + IntegratorOutput(ar);
   sum := sum/500;
   GotoXY(10,10); ClrEol;
   write(sum:4:0);
 until KeyPressed;
 writeln;
 ClrScr;
 SetRelais(4*ar+1,false);     { Integrator blocked}
end;
{-----------------------------------------------------}
end.
