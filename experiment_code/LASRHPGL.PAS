(*-------------------------------------------------------------------*)
{                            unit LasrHPGL                            }
{                      Plotten auf HPLJ-4 in HPGL/2                   }
{                                                                     }
{                                                cRW  17.Feb 1994     }
(*-------------------------------------------------------------------*)
unit lasrhpgl;
interface

Type Plotformtype= (quer,hoch);
     Labeloritype= (rechts_drunter,rechts_mittig,rechts_drueber,
                     mitte_drunter, mitte_mittig, mitte_drueber,
                     links_drunter, links_mittig, links_drueber);
     txt         = string[255];

var PLotForm                          : PlotFormType;
    LiRa,VertikalRa,ZeiHoehe,ZeiBreite: real;
    ScXmin,ScXmax,ScYmin,ScYmax,
    dummy                             : integer;
    Plotscaled                        : boolean;
    PenSelected                       : Integer;
    HPLJ4                           : text;

procedure DecCheckZeroLimit(var dec:real;error:boolean);
procedure DecCheckUpLimit(var dec:real;error:boolean);
procedure DeccheckLowLimit(var dec:real;error:boolean);
procedure PlotWindow(Xll,Yll,Xur,Yur:real);
procedure PlotInit;
procedure PlotHclips(p1x,p1y,p2x,p2y:integer);
procedure ConvertPlotUnitToAbs(var x,y:integer;var LiRa,VeRa:real);
procedure ConvPlotUnitToAbs(x,y:integer; var x_,y_:real);
procedure PlotMetricHardclips(LiRa,VertikalRa,ZeiBreite,Zeihoehe:real);
procedure PlotMetricMenue;
procedure PlotScale(xmin,xmax,ymin,ymax:integer);     {relativer Scale!}
procedure Plotformat(pf:plotformtype);
procedure PlotFormatMenue;
procedure PlotScaleRelMenue;
procedure PlotScaleAbsWindow;
procedure PlotScaleAbsBlatt;
procedure PlotFrame;
procedure PlotDesAltChar(n:integer);
procedure PlotChar(spaces,lines:real);
procedure PlotDesStandChar(n:integer);
procedure PlotDefault;
procedure PlotAbsDir(angle:real);
procedure PlotRelDir(run,rise:integer);
procedure DefTerm(T:char);
procedure PlotLabelabs(labeldir:real;Labelori:Labeloritype;labmsg: txt);
procedure LineType(patnr:integer;patlen:real);
procedure PlotAbs(x1,y1:real);
procedure PlotRel(x1,y1:real);
procedure PenUp;
procedure PenDown;
procedure PlotSelectAltCharSet;
procedure PlotAbsCharSize(width,height:real);
procedure SetRelCharSize(width,height:real);
procedure PlotCharSlant(angle:real);
procedure PlotSymbMode(character:char);
procedure SelectPen(PenNo:integer);
procedure PlotSelectStandChar;
procedure MovePento(x1,y1:real);
procedure Plotto(x1,y1:real);
procedure PlotLine(x1,y1,x2,y2:real);
procedure PlotCircle(mpx,mpy,r:real);
procedure Plotarc(mpx,mpy,apx,apy,phi:real);
procedure HPLJ4_ready_msg(x,y:byte);


implementation
uses crt;

{------------------------------------------------------}
procedure DecCheckZeroLimit(var dec:real;error:boolean);
begin
error:=false;
if (dec<=0)  then begin
   write('Parameter zu klein ');
   error:=true;dec:=0 end
end;
{-----------------------------------------------------}
procedure DecCheckUpLimit(var dec:real;error:boolean);
begin
error:=false;
if (dec>127.9999)  then begin
   write('Parameter zu gro· ');
   error:=true;dec:=0 end
end;
{-----------------------------------------------------}
procedure DecCheckLowLimit(var dec:real;error:boolean);
begin
error:=false;
if (dec<-127.999)  then begin
  write('Parameter zu klein ');
  error:=true;dec:=127.999 end
end;
{---------------------------------------------------------------}
procedure PlotWindow(Xll,Yll,Xur,Yur:real);
begin
writeln(HPLJ4,'IW',xll:5:5,',',yll:5:5,',',xur:5:5,',',yur:5:5);
end;
{---------------------------------------------------------------}
procedure PlotInit;
  var  HPLJ4  : text;
begin
  assign (HPLJ4,'LPT1');
  rewrite(HPLJ4);
  Write(HPLJ4, chr(27)+'&a1C');      { Cursor zur Anfangsspalte }
  Write(HPLJ4, chr(27)+'&a1R');      { Cursor zur Anfangszeile  }
  Write(HPLJ4,chr(27)+'%1B');        { Umschalten -> PCL/2 }
  writeln(HPLJ4,'IN;');
  PlotScaled:=false;PlotForm:=hoch;
  close(HPLJ4);
end;
{-----------------------------------------------------------------------}
procedure PlotHclips(p1x,p1y,p2x,p2y:integer);
begin
  writeln(HPLJ4,'IP',p1x,',',p1y,',',p2x,',',p2y,';');
end;
{--------------------------------------------------------------------}
procedure ConvertPlotUnitToAbs(var x,y:integer;var LiRa,VeRa:real);
var temp: real;
begin
    LiRa:=191.5/7650*x+6;
    VeRa:=272/10850*y+12;
    if PlotForm=quer then begin
      Temp:=LiRa;LiRa:=VeRa;VeRa:=temp
    end;
end;
{--------------------------------------------------------------------}
procedure ConvPlotUnitToAbs(x,y:integer; var x_,y_:real);
var temp: real;
begin
    x_:=191.5/7650*x+6;
    y_:=272/10850*x+12;
    if PlotForm=hoch then begin
      Temp:=x_;x_:=y_;y_:=temp
    end;
end;
{--------------------------------------------------------------------}

procedure PlotMetricHardclips(LiRa,VertikalRa,ZeiBreite,Zeihoehe:real);
var p1x,p1y,p2x,p2y:integer;
begin
  if PlotForm=hoch then begin
    p1x:=round((LiRa-6)/191.5*7650);
    p1y:=round((VertikalRa-12)/272*10850);
    p2x:=round(p1x+ZeiBreite/191.5*7650);
    p2y:=round(p1y+ZeiHoehe/272*10850);
  end
  else begin
    p1x:=round((VertikalRa-12)/272*10850);
    p1y:=round((LiRa-6)/191.5*7650);
    p2x:=round(p1x+ZeiBreite/191.5*7650);
    p2y:=round(p1y+ZeiHoehe/272*10850);
  end;
    PlotHclips(p1x,p1y,p2x,p2y);
    PlotWindow(p1x,p1y,p2x,p2y)
end;
{----------------------------------------------------------------------------}

procedure PlotMetricMenue;
var  ende                 :boolean;
     p1x,p1y,p2x,p2y,x,y  :integer;
     a                    : char;         

begin
  ClrScr;
  ende:=false;
  x := 5; y := 5;
  GotoXY(5,2);writeln('HardClip Einstellungen bei Hochformat : ');
  while (ende<>true) do
    begin
    GotoXY(x,y);writeln ('<1>   Linker Rand   ',liRa:3:1);
    GotoXY(x+25,y);writeln ('  [mm] ');
    if (Plotform=quer) then begin
    GotoXY(x,y+1);writeln ('<2>   Unterer Rand  ',VertikalRa:3:1) end;
    if (Plotform=hoch) then begin
    GotoXY(x,y+1);writeln ('<2>   Oberer Rand   ',VertikalRa:3:1) end;
    GotoXY(x+25,y+1);writeln ('  [mm] ');
    GotoXY(x,y+2);writeln ('<3>   Breite        ',ZeiBreite:3:1);
    GotoXY(x+25,y+2);writeln ('  [mm] ');
    GotoXY(x,y+3);writeln ('<4>   Hoehe         ',ZeiHoehe:3:1);
    GotoXY(x+25,y+3);writeln ('  [mm] ');
    GotoXY(x,y+4);writeln ('<0>   Ende');
    GotoXY(x,y+5);write ('bitte wÑhlen ! [0..4] ');
    repeat a := ReadKey until a in ['1'..'4'];
    gotoxy(x+21,y+5);write('  ');
    case a of
      '0': ende:=true;
      '1': begin
         GotoXY(x+20,y);write('      ');gotoxy(x+20,y);readln(LiRa);
         end;
      '2': begin
         GotoXY(x+20,y+1);write('      ');gotoxy(x+20,y+1);readln(VertikalRa);
         end;
      '3': begin
         GotoXY(x+20,y+2);write('      ');gotoxy(x+20,y+2);readln(ZeiBreite);
         end;
      '4': begin
         GotoXY(x+20,y+3);write('      ');gotoxy(x+20,y+3);readln(ZeiHoehe);
         end;
    end;
  end;
PlotMetricHardclips(liRa,VertikalRa,ZeiBreite,Zeihoehe);
end;
{--------------------------------------------------------}
procedure PlotScale(xmin,xmax,ymin,ymax:integer);     {relativer Scale!}
var temp1,temp2:integer;
begin
  if plotform=quer then begin
     Temp1:=xmin;xmin:=ymax;
     temp2:=xmax;xmax:=ymin;
     ymin:=temp1;ymax:=temp2;
     end;
 ScXmin:=xmin;ScXmax:=xmax; ScYmin:=ymin;ScYmax:=ymax;
 writeln(HPLJ4,'SC',xmin,',',xmax,',',ymin,',',ymax,';');
 PlotScaled:=true;
end;
{----------------------------------------------------------------------------}
procedure Plotformat(pf:plotformtype);
begin
Plotform:=pf;
end;
{------------------------------------------------------}
procedure PlotFormatMenue;
var p1x,p2x,p1y,p2y,x,y  :integer;
    r                    :char;
begin
  ClrScr;
  x := 5;  y := 5;
    gotoXY(x,y);  write('<H> ochformat');
    gotoXY(x,y+1);write('    oder');
    gotoXY(x,y+2);write('<Q> uerformat ? ');
  repeat r:=ReadKey until UpCase(r) in ['Q','H'];
  if UpCase(r)='Q' then Plotformat(quer) else PlotFormat(hoch);
end;
{------------------------------------------------------}
procedure PlotScaleRelMenue;
var Xmin,xmax,ymin,ymax     : integer;
    rxmin,rymin,rxmax,rymax : real;
    a                       : char;
    ende                    : boolean;
begin
  ClrScr;
  GotoXY(5,5);writeln('Relative Skalierung (Hochformat)');
  ende:=false;
  while (ende<>true) do
    begin
    GotoXY(10,10);writeln ('< 1 >     Xmin    ',Xmin:4);
    GotoXY(10,11);writeln ('< 2 >     Xmax    ',Xmax:4);
    GotoXY(10,12);writeln ('< 3 >     Ymin    ',Ymin:4);
    GotoXY(10,13);writeln ('< 4 >     Ymax    ',Ymax:4);
    GotoXY(10,15);writeln ('< 0 >     Ende ');
    GotoXY(10,20);write ('bitte wÑhlen ! [0..4] ');ClrEol;
    repeat a:=ReadKey until a in ['0'..'4'];
    case a of
      '0': ende:=true;
      '1': begin
         GotoXY(25,10);ClrEol;readln(xmin);
         end;
      '2': begin
         GotoXY(25,11);ClrEol;readln(xmax);
         end;
      '3': begin
         GotoXY(25,12);ClrEol;readln(ymin);
         end;
      '4': begin
         GotoXY(25,13);ClrEol;readln(ymax);
         end;
    end;
  end;
  PlotScale(xmin,xmax,ymin,ymax);
end;
{-------------------------------------------------------------------------}
procedure PlotScaleAbsWindow;
var p1x,p1y,p2x,p2y,Xmin,xmax,ymin,ymax:integer;
    rxmin,rymin,rxmax,rymax:real;
begin
 {   GetPlotScalingPoints(p1x,p1y,p2x,p2y);  }
     rxmin:=(p1x/7650*191.5);
     rymin:=(p1y/10850*272);
     rxmax:=(p2x/7650*191.5);
     rymax:=(p2y/10850*272);
     rxmax:=rxmax-rxmin;
     rymax:=rymax-rymin;
     xmin:=0;ymin:=0;
     xmax:=round(rxmax);
     ymax:=round(rymax);
PlotScale(xmin,xmax,ymin,ymax);
end;
{--------------------------------------------------------}
procedure PlotScaleAbsBlatt;
var Xmin,xmax,ymin,ymax:integer;
begin
   PlotHClips(0,0,7650,10850);
     xmin:=6;
     ymin:=12;
     xmax:=round(191.5+6);
     ymax:=round(272+12);
 writeln(HPLJ4,'SC',xmin,',',xmax,',',ymin,',',ymax,';');
 ScXmin:=xmin;ScXmax:=xmax; ScYmin:=ymin;ScYmax:=ymax;
 PlotScaled:=true;
end;
{--------------------------------------------------------}
procedure PlotFrame;
var p1x,p2x,p1y,p2y:integer;

 begin
if (Plotscaled=false) then PlotScaleRelMenue
else begin
  writeln(HPLJ4,'PU',Scxmin,',',scymin,';') ;
  writeln(HPLJ4,'PD;');
  writeln(HPLJ4,'PA',scxmax,',',scymin,',',scxmax,',',scymax,',',
          scxmin,',',scymax,',',scxmin,',',scymin,';');
  writeln(HPLJ4,'PU;');end;
end;
{---------------------------------------------------------}
procedure PlotDesAltChar(n:integer);
begin
writeln(HPLJ4,'CA',n,';');
end;
{---------------------------------------------------------}
procedure PlotChar(spaces,lines:real);
begin
writeln(HPLJ4,'CP',spaces:3:2,',',lines:3:2,';');
end;
{--------------------------------------------------------}
procedure PlotDesStandChar(n:integer);
begin
writeln(HPLJ4,'CS',n);
end;
{--------------------------------------------------------}
procedure PlotDefault;
begin
writeln(HPLJ4,'DF;');
end;
{--------------------------------------------------------}
procedure PlotAbsDir(angle:real);
var run,rise:integer;

begin
if (Plotform=hoch) then angle:=angle+90;
angle:=angle/180.0*PI;
run:=round(100*cos(angle));rise:=round(100*sin(angle));
writeln(HPLJ4,'DI',RUN,',',RISE,';');
end;
{------------------------------------------------------}
procedure PlotRelDir(run,rise:integer);
begin
writeln(HPLJ4,'DR',RUN,',',RISE,';');
end;
{------------------------------------------------------}
procedure DefTerm(T:char);
begin
writeln(HPLJ4,'DT',t);
end;
{------------------------------------------------------}
procedure PlotLabelabs(labeldir:real;Labelori:Labeloritype;labmsg: txt);
var height,width:real;
    error:boolean;
begin
Plotabsdir(labeldir);
case labelori of
links_drueber  : begin width:=0.33-length(labmsg);height:=0.25 end;
links_mittig   : begin width:=0.33-length(labmsg);height:=-0.25 end;
links_drunter  : begin width:=0.33-length(labmsg);height:=-0.83 end;
mitte_drueber  : begin width:=0.33-length(labmsg)/2.0;height:=0.25 end;
mitte_mittig   : begin width:=0.33-length(labmsg)/2.0;height:=-0.25 end;
mitte_drunter  : begin width:=0.33-length(labmsg)/2.0;height:=-0.83 end;
rechts_drueber : begin width:=0.33;height:=0.25 end;
rechts_mittig  : begin width:=0.33;height:=-0.25 end;
rechts_drunter : begin width:=0.33;height:=-0.83 end;
end;
{
DecCheckLowLimit(width,error);DecCheckUpLimit(width,error);
if(error=true) then writeln(' in Labelorigin ');
DecCheckLowLimit(height,error);DecCheckUpLimit(height,error);
if(error=true) then writeln(' in Labelorigin ');

Plotchar(width,height); }
writeln(HPLJ4,'LB',labmsg+chr(3));
end;
{---------------------------------------------------------}
procedure LineType(patnr:integer;patlen:real);
var error:boolean;

begin
  if patnr=0 then      writeln(HPLJ4,'LT')
             else begin
      DecCheckUpLimit(patlen,error);
      DecCheckZeroLimit(patlen,error);
      if patlen=0 then writeln(HPLJ4,'LT',patnr)
                  else writeln(HPLJ4,'LT',patnr,',',patlen:3:2)
      end;
end;
{---------------------------------------------------------}
procedure PlotAbs(x1,y1:real);
var temp:real;
begin
  if PlotForm=quer then begin
    temp:=x1; x1:=y1;y1:=temp;
  end;
  writeln(HPLJ4,'PA',x1:5:5,',',y1:5:5,';');
 end;
{-------------------------------------------------------}
procedure PlotRel(x1,y1:real);
var temp:real;
begin
  if PlotForm=quer then begin
    temp:=x1; x1:=y1;y1:=temp;
  end;
  writeln(HPLJ4,'PR',x1:5:5,',',y1:5:5,';');
end;
{-------------------------------------------------------}
procedure PenUp;
var status,err1  : byte;
begin
 writeln(HPLJ4,'PU;');
end;
{-------------------------------------------------------}
procedure PenDown;
begin
 writeln(HPLJ4,'PD',';');
end;
{-------------------------------------------------------}
procedure PlotSelectAltCharSet;

begin
 writeln(HPLJ4,'SA',';');
end;
{-------------------------------------------------------}
procedure PlotAbsCharSize(width,height:real);
var error: boolean;

begin
 deccheckUpLimit(width,error);  deccheckUpLimit(height,error);
 deccheckLowLimit(width,error); deccheckLowLimit(height,error);
 if (error=true) then writeln('in Charsize Anweisung');
 writeln(HPLJ4,'SI',width:3:4,',',height:3:4,';');
end;
{-------------------------------------------------------}
procedure SetRelCharSize(width,height:real);
var error:boolean;

begin
 deccheckUpLimit(width,error);  deccheckUpLimit(height,error);
 deccheckLowLimit(width,error); deccheckLowLimit(height,error);
 if (error=true) then writeln('in Charsize Anweisung');
 writeln(HPLJ4,'SR',width:3:4,',',height:3:4,';');
end;
{-------------------------------------------------------}
procedure PlotCharSlant(angle:real);
var error:boolean;
    tan:real;
begin
 angle:=3.14159265*angle/180;
 tan:=(sin(angle) / cos(angle));
 deccheckUpLimit(tan,error);
 if( error=true) then writeln('in CharSlant Anweisung ');
 deccheckLowLimit(tan,error);
 if( error=true) then writeln('in CharSlant Anweisung ');
 writeln(HPLJ4,'SL',tan:3:4);
end;
{-------------------------------------------------------}
procedure PlotSymbMode(character:char);

begin
 writeln(HPLJ4,'SM',character);
end;
{-------------------------------------------------------}
procedure SelectPen(PenNo:integer);

begin
  if PenNo<>PenSelected then begin
    PenSelected:=PenNo;
    writeln(HPLJ4,'SP',PenNo);
    end;
end;
{-------------------------------------------------------}
procedure PlotSelectStandChar;

begin
 writeln(HPLJ4,'SS');
end;
{-------------------------------------------------------}
procedure MovePento(x1,y1:real);

begin
 PenUp;
 PlotAbs(x1,y1);
end;
{-------------------------------------------------------}
procedure Plotto(x1,y1:real);
var x2,y2: integer;

begin
         PenDown;
         Plotabs(x1,y1)
end;
{-------------------------------------------------------}
procedure PlotLine(x1,y1,x2,y2:real);

begin
  PenUp;
  PlotAbs(x1,y1);
  PenDown;
  PlotAbs(x2,y2);
end;
{-------------------------------------------------------}
procedure PlotCircle(mpx,mpy,r:real);

begin
  penUp;
  PlotAbs(mpx,mpy);
  writeln(HPLJ4,'CI',r:5:5,';');
end;
{-------------------------------------------------------}
procedure Plotarc(mpx,mpy,apx,apy,phi:real);

begin
  PenUp;
  PlotAbs(apx,apy);
  PenDown;
  writeln(HPLJ4,'AA',mpx:5:5,',',mpy:5:5,',',phi:5:5,';');
end;
{-------------------------------------------------------}
procedure HPLJ4_ready_msg(x,y:byte);
var antwort:char;
begin
  GotoXY(x,y);
  writeln('HPLJ4 eingeschaltet? Irgendeine Taste drÅcken');
  antwort := ReadKey;
  GotoXY(x,y);
  writeln('                                             ');
end;
{-------------------------------------------------------}
end.